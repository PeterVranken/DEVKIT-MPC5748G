/**
 * @file eth_ethernet.c
 * Starting point of Ethernet driver. The actual driver implementation has been taken from
 * the NXP framework RTM 3.0.3. This file has been added to integrate the NXP
 * implementation into the DEVKIT_MPC5748G environment.\n
 *   The code in this file initializes the NXP driver with appropriate configuration, it
 * installs the interrupt handlers and it configures the MCU ports specifically for board
 * DEVKIT_MPC5748G.\n
 *   The run-time interfaces of the NXP implementation are not wrapped. They can be
 * directly used.
 *
 * @note References "RM48" (reference manual) in this module refer to "MPC5748G Reference
 * Manual", document number: MPC5748GRM, Rev. 7.1, 01/2019.
 *
 * Copyright (C) 2023-2024 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or any later
 * version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License
 * for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
/* Module interface
 *   eth_setMulticastForward (inline)
 *   eth_readFrame (inline)
 *   eth_releaseRxFramePayloadBuffer (inline)
 *   eth_sendFrame (inline)
 *   eth_isTransmissionCompleted (inline)
 *   eth_scSmplHdlr_setMulticastForward
 *   eth_scSmplHdlr_readFrame
 *   eth_scSmplHdlr_releaseRxFramePayloadBuffer
 *   eth_scSmplHdlr_sendFrame
 *   eth_scSmplHdlr_isTransmissionCompleted
 *   eth_osInitEthernetDriver
 * Local functions
 *   configSIULForUseWithDEVKIT_MPC5748G
 *   checkRxPayloadBufferPtr
 *   checkTxRingBufferElementPtr
 */

/*
 * Include files
 */

#include "eth_ethernet.h"

#include <stdlib.h>
#include <assert.h>

#include "typ_types.h"
#include "rtos.h"
#include "bsw_basicSoftware.h"
#include "enet_driver.h"
#include "enet_irq.h"
#include "siu_siuPortDriver.h"
#include "eth_ethernet_defSysCalls.h"
#include "lwipcfg.h"

/*
 * Defines
 */

/** @brief Number of rings in use. */
#define ENET0_NO_RINGS_IN_USE   (1u)


/*
 * Local type definitions
 */


/*
 * Local prototypes
 */


/*
 * Data definitions
 */

/** Runtime data of the driver for device ENET0. */
static enet_state_t BSS_OS(_enet0DriverRT);

/** Rx ring buffer in use. The device has three ring buffers but we use only ring 0. The
    ring buffer elements hold the administrative information about received Ethernet frames
    but not the data. The data area is referenced by pointer from the ring buffer element. */
_Alignas(FEATURE_ENET_BUFFDESCR_ALIGNMENT) static
        enet_buffer_descriptor_t UNCACHED_OS(_enet0Ring0RxBufDescAry)[ETH_ENET0_RING0_NO_RXBD];

/** Tx ring buffer in use. The device has three ring buffers but we use only ring 0. The
    ring buffer elements hold the administrative information about Ethernet frames to be
    sent out but not their payload data. The payload data area is referenced by pointer
    from the ring buffer element. */
_Alignas(FEATURE_ENET_BUFFDESCR_ALIGNMENT) static
        enet_buffer_descriptor_t UNCACHED_OS(_enet0Ring0TxBufDescAry)[ETH_ENET0_RING0_NO_TXBD];

/** A set of buffers of chunks of memory, each large enough to hold the payload of the
    largest possible Ethernet frames. All Rx ring buffer elements currently in use
    reference an element in this ring buffer. Although both ring buffers have the same
    number of elements, the relationsship is not one by one. An Rx ring buffer element can
    reference any element in \a _enet0RxFramePayloadBufAry. */
_Alignas(FEATURE_ENET_BUFF_ALIGNMENT) static uint8_t
    UNCACHED_P1(_enet0RxFramePayloadBufAry)[ETH_ENET0_RING0_NO_RXBD][ENET_BUFF_ALIGN(1518U)];

_Static_assert( sizeof(enet_buffer_descriptor_t) == 32u
              , "Unexpected size of buffer descriptor"
              );


/*
 * Function implementation
 */

/**
 * Do the configuration of the MCU pins for the use of device ENET0, which is connected to
 * the PHYS on evaluation board DEVKIT_MPC5748G.\n
 *   The code in this function is not generally usable.
 */
static void configSIULForUseWithDEVKIT_MPC5748G(void)
{
    /* The configuration of all outputs is identical. We just have to select the function
       individually. */
    siu_portOutCfg_t outputCfg =
        {
          .idxPortSource_SSS = 0u, /* Driving signal is set below */
          .enableReadBack = false,
          .enableOpenDrain_ODE = false, /* Disable open drain, drive both edges */
          .pullUpDownCfg = siu_pullRes_none,
          .maxSlewRate_SRC = 3u, /* Slew rate: Full drive without SR control */
        };
    #define CONFIG_PORT(idxSIUL, SSS)                                   \
    {                                                                   \
        /* Acquire output port for exclusive use with this driver. */   \
        const bool gotIt ATTRIB_DBG_ONLY = siu_osAcquirePort(idxSIUL);  \
        assert(gotIt);                                                  \
                                                                        \
        /* Configure port. */                                           \
        outputCfg.idxPortSource_SSS = (SSS);                            \
        siu_osConfigureOutput((idxSIUL), &outputCfg);                   \
    }
    CONFIG_PORT(/*idxSIUL*/ 112 /*PH0 */, /*SSS*/ 3u /*MII_RMII_0_TXD[1]*/)
    CONFIG_PORT(/*idxSIUL*/ 113 /*PH1 */, /*SSS*/ 4u /*MII_RMII_0_TXD[0]*/)
    CONFIG_PORT(/*idxSIUL*/ 114 /*PH2 */, /*SSS*/ 4u /*MII_RMII_0_TX_EN*/)
    #undef CONFIG_PORT

    /* The configuration of all inputs is identical. We just have to set the input
       multiplexing individually. */
    siu_portInCfg_t inputCfg =
        { .enableHysteresis_HYS = false,
          .pullUpDownCfg = siu_pullRes_none,
          .idxMultiplexerRegister = 0u,     /* Multiplexer is set below */
          .idxInputSource_MUXSELVALUE = 0u, /* Multiplexer selector is set below */
        };
    #define CONFIG_PORT(idxSIUL, idxMpx, mpxSel)                        \
    {                                                                   \
        /* Acquire input port for exclusive use with this driver. */    \
        const bool gotIt ATTRIB_DBG_ONLY = siu_osAcquirePort(idxSIUL);  \
        assert(gotIt);                                                  \
                                                                        \
        /* Configure port. */                                           \
        inputCfg.idxMultiplexerRegister     = (idxMpx);                 \
        inputCfg.idxInputSource_MUXSELVALUE = (mpxSel);                 \
        siu_osConfigureInput((idxSIUL), &inputCfg);                     \
    }
    CONFIG_PORT(/*idxSIUL*/ 9  /*PA9 */, /*idxMpx*/ 451u, /*sel*/ 1u /*MII_RMII_0_RXD[0]*/)
    CONFIG_PORT(/*idxSIUL*/ 8  /*PA8 */, /*idxMpx*/ 452u, /*sel*/ 1u /*MII_RMII_0_RXD[1]*/)
    CONFIG_PORT(/*idxSIUL*/ 11 /*PA11*/, /*idxMpx*/ 455u, /*sel*/ 1u /*MII_RMII_0_RX_ER*/)
    CONFIG_PORT(/*idxSIUL*/ 95 /*PF15*/, /*idxMpx*/ 457u, /*sel*/ 1u /*MII_RMII_0_RX_DV*/)
    CONFIG_PORT(/*idxSIUL*/ 97 /*PG1 */, /*idxMpx*/ 449u, /*sel*/ 1u /*MII_RMII_0_RX_CLK*/)
    #undef CONFIG_PORT

} /* configSIULForUseWithDEVKIT_MPC5748G */


/**
 * Check the validity of a pointer to an Rx payload buffer. Such pointers are passed
 * to the client code as a result of eth_readFrame and the the client code need to return
 * it to the driver. Our safety concept must not trust the returned pointers as the client
 * resides in the QM process P1. We can accept the pointer only if it is valid. The
 * Ethernet driver manages the payload buffers as a array of such. The addresses of the
 * array elements are valid pointers.
 *   @return
 * Get \a true if \a payloadData holds the address of some memory, which may be used by the
 * Ethernet driver without breaking the safety concept. This does not necessarily mean that
 * the pointer is fully correct. It only means that using the pointer will do no harm. (In
 * the context of safety concept, data clutter in process P1 is no issue as long as the
 * freedom from interference with kernel or other user processes is not endangered.)
 *   @param payloadData
 * The potential address of a payload buffer, which is to be checked. Normally a
 * pointer, which had been returned by eth_readFrame().
 */
static inline bool checkRxPayloadBufferPtr(void * const payloadData)
{
    /* A full check is not required, if the Ethernet driver will write somewhere in the
       middle of the array, accross the boundaries of its elements, then it'll destroy
       other frame's payload or its payload will be overwritten by newly received once.
       Which all doesn't matter as long as the driver continues stable operation (we need
       an alignment check for this) and no unrelated memories, in particular no memory of
       other processes, can be touched. Therefore, a combination of range and alignment
       check suffices. */
    return (uint8_t*)payloadData <= &_enet0RxFramePayloadBufAry[ETH_ENET0_RING0_NO_RXBD-1][0]
           &&  (uint8_t*)payloadData >= &_enet0RxFramePayloadBufAry[0][0]
           &&  ((uintptr_t)payloadData & (FEATURE_ENET_BUFF_ALIGNMENT-1UL)) == 0u;
           
} /* checkRxPayloadBufferPtr */


/**
 * Check the validity of a pointer to a Tx ring buffer element. Such pointers are passed
 * to the client code as a handle of a particular ring buffer element and when the client
 * code makes use of the handle (e.g., to query the transmission state of the related
 * frame) then this function can be used to find out, whether the pointer indeed points to
 * such an element.
 *   @return
 * Get \a true if \a pRingBufElem holds the address of a configured ring buffer element. If
 * the function returns \a true then the same pointer can be safely used with function
 * eth_isTransmissionCompleted().
 *   @param pRingBufElem
 * The potential address of a ring buffer element, which is to be checked. Normally a
 * pointer, which had been returned by eth_sendFrame() as ring buffer element handle.
 */
static inline bool checkTxRingBufferElementPtr
                                    (const struct eth_enetBufferDesc_t * const pRingBufElem)
{
/** Tx ring buffer in use. The device has three ring buffers but we use only ring 0. The
    ring buffer elements hold the administrative information about Ethernet frames to be
    sent out but not their payload data. The payload data area is referenced by pointer
    from the ring buffer element. */
#if ETH_ENET0_RING0_NO_TXBD <= 4
    return false
# if ETH_ENET0_RING0_NO_TXBD >= 1
           ||  pRingBufElem == &_enet0Ring0TxBufDescAry[0]
# endif
# if ETH_ENET0_RING0_NO_TXBD >= 2
           ||  pRingBufElem == &_enet0Ring0TxBufDescAry[1]
# endif
# if ETH_ENET0_RING0_NO_TXBD >= 3
           ||  pRingBufElem == &_enet0Ring0TxBufDescAry[2]
# endif
# if ETH_ENET0_RING0_NO_TXBD >= 4
           ||  pRingBufElem == &_enet0Ring0TxBufDescAry[3]
# endif
           ;
#else
    /* For the general case, we need to do an active address calculation. We may safely
       exploit the power-of-two size of the buffer element, because it is a hardware given.
       However, a check is still essential in order not to jeopardize portability. */
    const unsigned int sizeOfRingBufElem = 32u;
    _Static_assert( sizeof(struct eth_enetBufferDesc_t) == sizeOfRingBufElem
                  , "Implementation is inappropriate for the given MAC hardware"
                  );

    /* Note, we do not apply C's pointer difference (which would not require the size check
       for 32 Byte) as it will implicitely do some rounding, which would obscure wrong
       addresses, i.e., corrupted pointers pointing into the middle of a ring buffer
       element. */
    const uintptr_t addrBase    = (uintptr_t)&_enet0Ring0TxBufDescAry[0]
                  , addrToCheck = (uintptr_t)pRingBufElem
                  , addrDiff    = addrToCheck - addrBase;

# if 0
    /* The next operations will work independetly of the size-check but without the
       power-of-two condition, they are quite expensive. For this reason, we have placed
       the assertion. If it would fire after a migration to another hardware then one has
       to carefully decide what to do, whether the general implentation should be applied.
       It may, e.g., be a better idea to extend the other implementation with explicit
       comparisons or to introduce a binary search for medium array sizes. */
    const uintptr_t idxRingBufElem = addrDiff / sizeOfRingBufElem;
    return idxRingBufElem < ETH_ENET0_RING0_NO_TXBD
           &&  addrBase + idxRingBufElem*sizeOfRingBufElem == addrToCheck;
# else
    /* If we anyway restrict the solution to power-of-two sizes, then we can use this
       optimized code, which would fail for other ring buffer element sizes. */
    return (addrDiff & 31u) == 0u  &&  addrDiff < sizeof(_enet0Ring0TxBufDescAry);
# endif
#endif
} /* checkTxRingBufferElementPtr */



/**
 * System call of Ethernet driver function ENET_DRV_SetMulticastForward(); a function,
 * which is otherwise available only to OS code. Enables/Disables forwarding of multicast
 * traffic having a specific MAC address as destination.
 *   @return
 * NULL if no input is avaliable yet, otherwise \a str. See sio_osGetLine() for details.
 *   @param pidOfCallingTask
 * The process ID of the calling task. This system call is available only to the QM
 * process, \a bsw_pidUser. An exception is raised if another process try to make the system
 * call.
 *   @param idxEthDev
 * The index of the MAC, used for the communication. The MPC5748G has two MACs but the
 * specified index needs to address to a configured device. Otherwise, an exception is
 * raised.\n
 *   In this project, only device 0 is enabled.
 *   @param macAddr
 * The MAC address as an array of six bytes.
 *   @param enable
 * \a true to enable, \a false to disable forwarding of multicast traffic.
 *   @remark
 * This function must never be called directly. The function is only made for placing it in
 * the global system call table.
 */
void eth_scSmplHdlr_setMulticastForward( uint32_t pidOfCallingTask
                                       , unsigned int idxEthDev
                                       , const uint8_t macAddr[6]
                                       , bool enable
                                       )
{
    /* Check all kinds of input argument errors, which can make the OS code potentially
       fail. Also exclude input, which is forbidden by design, e.g., violation of granted
       privileges. */
    if(pidOfCallingTask == bsw_pidUser
       &&  idxEthDev == 0u
       &&  rtos_checkUserCodeReadPtr(macAddr, /*noBytes*/ 6u)
      )
    {
        /* All arguments are alright, we can safely delegate the request to the OS
           implementation. */
        ENET_DRV_SetMulticastForward(idxEthDev, macAddr, enable);
    }
    else
    {
        /* There is a severe user code error, which is handeld with an exception, task
           abort and counted error. */
        rtos_osSystemCallBadArgument();
    }
} /* eth_scSmplHdlr_setMulticastForward */


/**
 * System call of Ethernet driver function ENET_DRV_ReadFrame(); a function,
 * which is otherwise available only to OS code.\n
 *   This function reads the first (eldest) received Ethernet frame in the given Rx ring.
 *   @return
 *   If the function succeeds, then it returns a buffer description object with data
 * pointer and length by reference. The buffer descriptor describes the frame's payload:
 * Field \a data will point to a memory area containing the frame data. Field \a length
 * contains the number of frame content bytes.\n
 *   The returned information (pointer and length) is valid until the next invocation of
 * this API function. The memory area it points to, i.e., the frame's payload, is valid
 * until the memory area is returned to the driver using eth_releaseRxFramePayloadBuffer().\n
 *   Caution, as soon the application finishes processing the buffer, it needs to release
 * it using system call eth_releaseRxFramePayloadBuffer().\n
 *   If no Rx frame is currently buffered then the function returns NULL.
 *   @param pidOfCallingTask
 * The process ID of the calling task. This system call is available only to the QM
 * process, \a bsw_pidUser. An exception is raised if another process try to make the system
 * call.
 *   @param idxEthDev
 * The zero based index of the MAC, used for the communication. The MPC5748G has two MACs
 * but the specified index needs to address to a configured device. Otherwise, an exception
 * is raised.\n
 *   In this project, only device 0 is enabled.
 *   @param idxRing
 * The zero based index of the ring buffer (or Rx queue) of the MAC, which is used for
 * reception of frames. The MACs in the MPC5748G have three ring buffers, but the
 * specified index needs to address to a configured ring. Otherwise, an exception is
 * raised.\n
 *   In this project, only ring 0 is in use.
 *   @param pFrameDesc
 * The descriptor of the returned frame data by reference.
 *   @remark
 * This function must never be called directly. The function is only made for placing it in
 * the global system call table.
 */
const struct eth_bufferDesc_t *eth_scSmplHdlr_readFrame( uint32_t pidOfCallingTask
                                                       , unsigned int idxEthDev
                                                       , unsigned int idxRing
                                                       )
{
    /* Check all kinds of input argument errors, which can make the OS code potentially
       fail. Also exclude input, which is forbidden by design, e.g., violation of granted
       privileges. */
    if(pidOfCallingTask == bsw_pidUser  &&  idxEthDev == 0u  &&  idxRing == 0u)
    {
        /* The justification, why we us a static buffer for returning the information to
           the caller, is the system call interface. If we return information by reference
           then the destination pointer needs to be checked for write access by the calling
           process - which is a rather expensive operation. A normal return value is
           implicitly safe and doesn't cost overhead. Using a static buffer makes the
           function non-reentrant but the driver API is anyway not reentrant so this is not
           at all a deterioration. */
        static enet_buffer_t DATA_OS(framePayloadDesc_);

        /* All arguments are alright, we can safely delegate the request to the OS
           implementation. */
        const status_t sts = ENET_DRV_ReadFrame( idxEthDev
                                               , idxRing
                                               , &framePayloadDesc_
                                               , /*pInfo*/ NULL
                                               );
        if(sts == STATUS_SUCCESS)
            return &framePayloadDesc_;
        else
            return NULL;
    }
    else
    {
        /* There is a severe user code error, which is handeld with an exception, task
           abort and counted error. */
        rtos_osSystemCallBadArgument();
    }
} /* eth_scSmplHdlr_readFrame */



/**
 * System call of Ethernet driver function ENET_DRV_ProvideRxBuff(); a function,
 * which is otherwise available only to OS code.\n
 *   This function provides a buffer which can further be used by the reception
 * mechanism in order to store the received data.
 *   Note, the buffer is specified by address only. The length is implicit and needs to
 * large enough for a frame of maximum MTU.
 *   @param pidOfCallingTask
 * The process ID of the calling task. This system call is available only to the QM
 * process, \a bsw_pidUser. An exception is raised if another process try to make the system
 * call.
 *   @param idxEthDev
 * The zero based index of the MAC, used for the communication. The MPC5748G has two MACs
 * but the specified index needs to address to a configured device. Otherwise, an exception
 * is raised.\n
 *   In this project, only device 0 is enabled.
 *   @param idxRing
 * The zero based index of the ring buffer (or Rx queue) of the MAC, which is used for
 * reception of frames. The MACs in the MPC5748G have three ring buffers, but the
 * specified index needs to address to a configured ring. Otherwise, an exception is
 * raised.\n
 *   In this project, only ring 0 is in use.
 *   @param macAddr
 * The MAC address as an array of six bytes.
 *   @param pFramePayloadBuf
 *
 *   @remark
 * This function must never be called directly. The function is only made for placing it in
 * the global system call table.
 */
void eth_scSmplHdlr_releaseRxFramePayloadBuffer( uint32_t pidOfCallingTask
                                               , unsigned int idxEthDev
                                               , unsigned int idxRing
                                               , void * const pFramePayloadBuf
                                               )
{
    /* Check all kinds of input argument errors, which can make the OS code potentially
       fail. Also exclude input, which is forbidden by design, e.g., violation of granted
       privileges. */
    if(pidOfCallingTask == bsw_pidUser
       &&  idxEthDev == 0u
       &&  idxRing == 0u
       &&  checkRxPayloadBufferPtr(pFramePayloadBuf)
      )
    {
        /* All arguments are alright, we can safely delegate the request to the OS
           implementation. */
        ENET_DRV_ProvideRxBuff(idxEthDev, idxRing, pFramePayloadBuf);
    }
    else
    {
        /* There is a severe user code error, which is handeld with an exception, task
           abort and counted error. */
        rtos_osSystemCallBadArgument();
    }
} /* eth_scSmplHdlr_releaseRxFramePayloadBuffer */



/**
 * System call of Ethernet driver function ENET_DRV_SendFrame(); a function,
 * which is otherwise available only to OS code.\n
 *   This function hands an Ethernet frame, or a fragment of it, over to the Ethernet
 * driver for transmission.
 *   @return
 * Get the handle \a hTxFrame of the frame or fragment if the transmission request has been
 * accepted by the Ethernet driver, i.e., the driver has had enough memory for queing the
 * request. This handle is required to query the progress of transmission using
 * eth_isTransmissionCompleted().\n
 *   Get zero, the invalid handle, if the driver's Tx queue is currently full. The frame or
 * fragment is lost if the caller doesn't submit it again after a while. The ownership of
 * the memory at \a payloadData has not been passed to the Ethernet driver.
 *   @param pidOfCallingTask
 * The process ID of the calling task. This system call is available only to the QM
 * process, \a bsw_pidUser. An exception is raised if another process try to make the system
 * call.
 *   @param idxEthDev
 * The zero based index of the MAC, used for the communication. The MPC5748G has two MACs
 * but the specified index needs to address to a configured device. Otherwise, an exception
 * is raised.\n
 *   In this project, only device 0 is enabled.
 *   @param idxRing
 * The zero based index of the ring buffer (or Rx queue) of the MAC, which is used for
 * reception of frames. The MACs in the MPC5748G have three ring buffers, but the
 * specified index needs to address to a configured ring. Otherwise, an exception is
 * raised.\n
 *   In this project, only ring 0 is in use.
 *   @param payloadData
 * The frame's payload data by read reference. Note, the memory is read at an unspecified
 * time after entry into this function. If the function succeeds, then the memory contents
 * must not be changed until the other system call eth_isTransmissionCompleted() has
 * confirmed that the Ethernet driver has consumed the data.
 *   @param sizeOfPayloadData
 * The number of bytes in \a payloadData.
 *   @remark
 * This function must never be called directly. The function is only made for placing it in
 * the global system call table.
 */
uintptr_t eth_scSmplHdlr_sendFrame( uint32_t pidOfCallingTask
                                  , unsigned int idxEthDev
                                  , unsigned int idxRing
                                  , const void * const payloadData
                                  , unsigned int sizeOfPayloadData
                                  )
{
    /* Check all kinds of input argument errors, which can make the OS code potentially
       fail. Also exclude input, which is forbidden by design, e.g., violation of granted
       privileges. */
    if(pidOfCallingTask == bsw_pidUser
       &&  idxEthDev == 0u
       &&  idxRing == 0u
       &&  rtos_checkUserCodeReadPtr(payloadData, sizeOfPayloadData)
      )
    {
        /* All arguments are alright, we can safely delegate the request to the OS
           implementation. */
           
        /// @todo Design error in driver API. Dedicated buffer descriptors are required for
        // read and write buffers. Otherwise no proper use of const is possible. We are
        // forced to cast the const away.
        const enet_buffer_t frameDesc = { .data = (uint8_t*)payloadData,
                                          .length = sizeOfPayloadData,
                                        };
        struct eth_enetBufferDesc_t *pRingBufferElement;
        ENET_DRV_SendFrame( &pRingBufferElement
                          , (uint8_t)idxEthDev
                          , (uint8_t)idxRing
                          , &frameDesc
                          , /*pOptions*/ NULL
                          );
        return (uintptr_t)pRingBufferElement;
    }
    else
    {
        /* There is a severe user code error, which is handeld with an exception, task
           abort and counted error. */
        rtos_osSystemCallBadArgument();
    }
} /* eth_scSmplHdlr_sendFrame */



/**
 * System call of Ethernet driver function ENET_DRV_GetTransmitStatus(); a function,
 * which is otherwise available only to OS code.\n
 *   The Ethernet Tx path uses two memory buffers for transmitting a frame (or a fragment
 * of it). It has frame descriptors and it uses the frame content data. The buffer space
 * for the frame descriptor is owned by the driver, whereas the buffer space for the frame
 * contents is provided by the client code. A frame descriptor references the frame content
 * data. Both memory spaces need to be unmodified until the DMA of the MAC has consumed all
 * the data. The progress of "consuming" is queried by this function.\n
 *   Please note, this function has an important side-effect. Querying the status of the
 * buffer releases at the same time the frame descriptor for reuse by the driver. The
 * client code needs to call this function until the function returns a \a true before the
 * buffer space for the descriptor of the frame in progress can be reused again for the
 * transmission of another frame.
 *   @return
 * Get \a true if the transmission of the given frame (or fragment) has proceeded to the
 * extend that the buffer memory has been released by the driver. The buffer space for the
 * frame contents can be reused by the caller and the buffer space for the frame descriptor
 * will be reused by the driver in a future call of eth_sendFrame(). Note, this does not
 * necessarily mean that the frame has already been entirely sent on the physical bus.\n
 *   As long as the function returns \a false, the memory inside the frame content buffer
 * must not be altered by the caller; the Ethernet driver's DMA has not read it entirely
 * yet. This relates to the memory space, which had been passed to eth_sendFrame(), when
 * submitting the frame \a hTxFrame.
 *   @param hTxFrame
 * The handle of a pending frame as got from eth_sendFrame(), when submitting the frame for
 * transmission. The query relates to this particular frame.
 *   @remark
 * This function must be called only from the user task context executing in process
 * bsw_pidUser on core 0. Any attempt to use it from OS code or another core or process
 * will lead to undefined behavior.
 *   @remark
 * The API of the Ethernet driver is not reentrant. All function need to be called from the
 * same context or from context, which implement mutual exclusion. This holds in particular
 * for the paired calls of eth_sendFrame() and eth_isTransmissionCompleted().
 *   @param pidOfCallingTask
 * The process ID of the calling task. This system call is available only to the QM
 * process, \a bsw_pidUser. An exception is raised if another process try to make the system
 * call.
 *   @param hTxFrame
 * The handle of a pending frame as got from eth_sendFrame(), when submitting the frame for
 * transmission. The query relates to this particular frame. Actually, the handle is the
 * address of the frame descriptor.
 *   @remark
 * This function must never be called directly. The function is only made for placing it in
 * the global system call table.
 */
bool eth_scSmplHdlr_isTransmissionCompleted(uint32_t pidOfCallingTask, uintptr_t hTxFrame)
{
    /* The handle of a frame transmission job actually is the address of the MAC's ring
       buffer element in use for the transmission. */
    struct eth_enetBufferDesc_t * const pRingBufElem = (struct eth_enetBufferDesc_t *)hTxFrame;

    /* Check all kinds of input argument errors, which can make the OS code potentially
       fail. Also exclude input, which is forbidden by design, e.g., violation of granted
       privileges. */
    if(pidOfCallingTask == bsw_pidUser  && checkTxRingBufferElementPtr(pRingBufElem))
    {
        /* All arguments are alright, we can safely delegate the request to the OS
           implementation. */
        const status_t sts = ENET_DRV_GetTransmitStatus(pRingBufElem, /*pInfo*/ NULL);
        return sts == STATUS_SUCCESS;
    }
    else
    {
        /* There is a severe user code error, which is handeld with an exception, task
           abort and counted error. */
        rtos_osSystemCallBadArgument();
    }
} /* eth_scSmplHdlr_isTransmissionCompleted */



/**
 * Initialization of the Ethernet driver. Call this function once after startup of the
 * software and only from a single core, which is at the same time the core, which receives
 * the interrupts and the only core, which may use the driver API.
 *   @param isrRxFrame
 * This callback is invoked after a frame had been received in ring 0. The handler can then
 * use the driver API to fetch the received data. Must not be NULL.
 *   @param isrRxFrame
 * This callback is invoked after a Tx buffer had been sent. The handler can then use the
 * driver API to submit the next Tx buffer. Must not be NULL.
 *   @remark
 * Needs to be called from supervisor code only.
 */
void eth_osInitEthernetDriver(void (*isrRxFrame)(uint32_t), void (*isrTxBuffer)(uint32_t))
{
    /* Enable and configure the I/O ports. */
    configSIULForUseWithDEVKIT_MPC5748G();

    /* Module configuration structure. */
    const enet_config_t enet0DriverCfg =
    {
#if FEATURE_ENET_HAS_ACCELERATOR
        .rxAccelerConfig = (uint8_t)(ENET_RX_ACCEL_ENABLE_IP_CHECK
                                     | ENET_RX_ACCEL_ENABLE_PROTO_CHECK
                                     | ENET_RX_ACCEL_REMOVE_PAD
                                    ),
        .txAccelerConfig = (uint8_t)(ENET_TX_ACCEL_INSERT_IP_CHECKSUM
                                     | ENET_TX_ACCEL_INSERT_PROTO_CHECKSUM
                                    ),
#endif /* FEATURE_ENET_HAS_ACCELERATOR */

        /* Basic configuration */
        .maxFrameLen = 1518U,

        /* MII configuration */
        .miiMode = ENET_RMII_MODE,
        .miiSpeed = ENET_MII_SPEED_100M,
        .miiDuplex = ENET_MII_FULL_DUPLEX,

        /* Receive and transmit special configurations */
#if FEATURE_ENET_HAS_RX_CONFIG
        /* MAC receive special configuration. A binary OR of the values enumerated in
           enet_rx_special_config_t. Note, STRIP_CRC_FIELD or ENETx_RCR[CRCFWD] actually is
           a "doesn't care" if REMOVE_PADDING or ENETx_RCR[PADEN] is given (see RM48,
           p.1551). */
        .rxConfig = (uint32_t)(ENET_RX_CONFIG_ENABLE_PAYLOAD_LEN_CHECK
                               | ENET_RX_CONFIG_REMOVE_PADDING
                               | ENET_RX_CONFIG_STRIP_CRC_FIELD
                              ),
#endif
#if FEATURE_ENET_HAS_TX_CONFIG
        /* MAC transmit special configuration. A binary OR of the values enumerated in
           enet_tx_special_config_t. */
        .txConfig = 0,//ENET_TX_CONFIG_ENABLE_MAC_ADDR_INSERTION,
#endif
        /* Out driver configuration suitable for the integration with lwIP uses Rx and Tx
           interrupts with ring buffer 0. Set the ISRs accordingly. */
        .interrupts = ENET_RX_FRAME_INTERRUPT | ENET_TX_BUFFER_INTERRUPT,
        .isrErr = NULL,
        .isrRx = isrRxFrame,
        .isrTx = isrTxBuffer,
        .isrParser = NULL,
        .isrTimer = NULL,
        .isrRxRing1 = NULL,
        .isrTxRing1 = NULL,
        .isrRxRing2 = NULL,
        .isrTxRing2 = NULL,

        /* The number of rings to be used by the driver. */
        .ringCount = ENET0_NO_RINGS_IN_USE,
    };

    /* Buffer configuration structures, one per ring. */
    const enet_buffer_config_t enet0BuffCfgAry[ENET0_NO_RINGS_IN_USE] =
    {
        [0] =
        {
            ETH_ENET0_RING0_NO_RXBD,
            ETH_ENET0_RING0_NO_TXBD,
            &_enet0Ring0RxBufDescAry[0],
            &_enet0Ring0TxBufDescAry[0],
            &_enet0RxFramePayloadBufAry[0][0],
        },
#if ENET0_NO_RINGS_IN_USE != 1
# error Extend initializer expression
#endif
    };

    /* Only RMII mode is supported on DEV-KIT */
    assert(enet0DriverCfg.miiMode == ENET_RMII_MODE);

    /* Initialize driver for one particular ENET instance. */
    const uint8_t macAddr[6] = ETH_ENET0_MAC_ADDR;
    ENET_DRV_Init( /* idxEnetInstance */ 0u
                 , &_enet0DriverRT
                 , &enet0DriverCfg
                 , enet0BuffCfgAry
                 , macAddr
                 );
} /* eth_osInitEthernetDriver */
