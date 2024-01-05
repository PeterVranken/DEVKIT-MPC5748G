#ifndef ETH_ETHERNET_INCLUDED
#define ETH_ETHERNET_INCLUDED
/**
 * @file eth_ethernet.h
 * Definition of global interface of module eth_ethernet.c
 *
 * Copyright (C) 2023 FEV.io GmbH, Germany (mailto:vranken@fev.io)
 *
 * All rights reserved. Reproduction in whole or in part is prohibited without the written
 * consent of the copyright owner.
 */

/*
 * Include files
 */

#include <assert.h>

#include "typ_types.h"
#include "rtos.h"

/*
 * Defines
 */

/** The driver enables only device ENET0, which is wired to the Ethernet plug on the
    DEVKIT-MPC5748G. The MAC address of Ethernet device ENET0 is set during driver
    initialization. The value to define is the initializer expression for an array of six
    integers. */
#define ETH_ENET0_MAC_ADDR          {0x12,0x34,0x56,0x78,0x9A,0xBC}

/** The driver uses only one of the three rings of buffer descriptors, which are available
    for the MPC5748G. This is the zero based index of the ring in use.
      @remark This item should be zero. Any other value requires careful code review; the
    three rings are not equivalent and it is not clear beforehand if ring 1 or 2 will work
    well without code modification. */
#define ETH_ENET0_IDX_RING_IN_USE   (0u)

/** @brief Number of receive buffer descriptors for ENET0 ring 0 */
#define ETH_ENET0_RING0_NO_RXBD     (6u)

/** @brief Number of transmit buffer descriptors for ENET0 ring 0 */
#define ETH_ENET0_RING0_NO_TXBD     (2u)


/** Index of system call for forwarding multicast traffic having a specific MAC address. */
#define ETH_SYSCALL_SET_MULTICAST_FORWARD       (45u)

/** Index of system call for returning an evaluated Rx buffer to the driver. */
#define ETH_SYSCALL_PROVIDE_RX_BUFF             (46u)

/** Index of system call for fetching a received frame from the Ethernet driver. */
#define ETH_SYSCALL_READ_FRAME                  (47u)

/** Index of system call for tranmission of a frame or frame fragment. */
#define ETH_SYSCALL_SEND_FRAME                  (48u)

/** Index of system call to query the progress of an earlier submitted Tx frame. */
#define ETH_SYSCALL_IS_TRANSMISSION_COMPLETED   (49u)

/*
 * Global type definitions
 */

/** Definition of return value of system call ETH_SYSCALL_READ_FRAME: The contents of a
    received Ethernet frame. */
struct eth_bufferDesc_t
{
    /** The payload data of the frame. */
    uint8_t *data;

    /* The number of bytes, which can be read via \a data. */
    uint16_t length;
};

/* Forward declarations needed for the APIs below. */
struct eth_enetBufferDesc_t;

/*
 * Global data declarations
 */


/*
 * Global prototypes
 */

/** Initialization of the Ethernet driver. */
void eth_osInitEthernetDriver( void (*isrRxFrame)(uint32_t EIR)
                             , void (*isrTxBuffer)(uint32_t EIR)
                             );

/*
 * Global inline functions
 */

/** 
 * System call of Ethernet driver function ENET_DRV_SetMulticastForward(). Enables/Disables
 * forwarding of multicast traffic having a specific MAC address as destination.
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
 * This function must be called only from the user task context executing in process
 * bsw_pidUser on core 0. Any attempt to use it from OS code or another core or process
 * will lead to undefined behavior.
 *   @remark
 * The API of the Ethernet driver is not reentrant. All function need to be called from the
 * same context or from context, which implement mutual exclusion. This holds in particular
 * for the paired calls of eth_readFrame() and eth_releaseRxFramePayloadBuffer().
 *   @see 
 * Please refer to OS pendant ENET_DRV_SetMulticastForward() for details.
 */
static inline void eth_setMulticastForward( unsigned int idxEthDev
                                          , const uint8_t macAddr[6]
                                          , bool enable
                                          )
{
    rtos_systemCall(ETH_SYSCALL_SET_MULTICAST_FORWARD, idxEthDev, macAddr, enable);

} /* eth_setMulticastForward */



/** 
 * System call of Ethernet driver function ENET_DRV_ReadFrame().\n
 *   The Ethernet driver receives and buffers inbound frames independently from the
 * application software. This API aims to fetch meanwhile received frames. If a frame had
 * been received then its payload is passed to the calling application code.
 *   @return
 * Get the received frame's payload memory space by reference. If the driver could return a
 * meanwhile recived frame then the returned pointer is the address of the first byte of
 * the frame contents.\n
 *   On return from the function, the ownership of the returned memory space is transferred
 * to the caller. He may use it for read and write access but should have the awareness
 * that keeping the memeory reduces the amount of buffer space the Ethernet driver has for
 * receiving more frames. Therefore, the caller should return the memory as soon as
 * reasonably possible, see eth_releaseRxFramePayloadBuffer().\n
 *   If the function can't return a frame then the return value is NULL. (A NULL pointer
 * must not be returned to the driver using eth_releaseRxFramePayloadBuffer().)
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
 *   @param pSizeOfPayloadData
 * Get the size of the returned memory area in Byte. * \a pSizeOfPayloadData is not touched
 * if no frame had been received, i.e., if the function returns NULL.\n
 *   Note, getting zero does not necessarily mean that no frame has been received. Check
 * the function return value for NULL to see if a frame has been returned.
 *   @remark
 * This function must be called only from the user task context executing in process
 * bsw_pidUser on core 0. Any attempt to use it from OS code or another core or process
 * will lead to undefined behavior.
 *   @remark
 * The API of the Ethernet driver is not reentrant. All function need to be called from the
 * same context or from context, which implement mutual exclusion. This holds in particular
 * for the paired calls of eth_readFrame() and eth_releaseRxFramePayloadBuffer().
 */
static inline void * eth_readFrame( unsigned int idxEthDev
                                  , unsigned int idxRing
                                  , unsigned int * const pSizeOfPayloadData
                                  )
{
    const struct eth_bufferDesc_t * const pFramePayloadDesc =
                    (const struct eth_bufferDesc_t *)rtos_systemCall( ETH_SYSCALL_READ_FRAME
                                                                    , idxEthDev
                                                                    , idxRing
                                                                    );

    /* Being here back in the supervised user code space, using the pointer is not an
       issue. */
    if(pFramePayloadDesc != NULL)
    {
        *pSizeOfPayloadData = (unsigned int)pFramePayloadDesc->length;
        assert(pFramePayloadDesc->data != NULL);
        return pFramePayloadDesc->data;
    }
    else
        return NULL;

} /* eth_readFrame */




/** 
 * System call of Ethernet driver function ENET_DRV_ProvideRxBuff().\n
 *   A memory buffer, which had been got from the Ethernet driver as result of
 * eth_readFrame() is returned to the driver after use. The buffer space becomes available
 * again for new received frames.
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
 *   @param pBufferMem
 * A buffer address, which had been got before from eth_readFrame().
 *   @remark
 * This function must be called from the user task context only executing on core 0. Any
 * attempt to use it from OS code or another core will lead to undefined behavior.
 *   @remark
 * Several more remarks apply to the use of this function. Please refer to OS pendant
 * ENET_DRV_() for details.
 */
static inline void eth_releaseRxFramePayloadBuffer( unsigned int idxEthDev
                                                  , unsigned int idxRing
                                                  , void * const pBufferMem
                                                  )
{
    rtos_systemCall(ETH_SYSCALL_PROVIDE_RX_BUFF, idxEthDev, idxRing, pBufferMem);

} /* eth_releaseRxFramePayloadBuffer */




/** 
 * System call of Ethernet driver function ENET_DRV_SendFrame().\n
 *   Some memory contents are submitted for transmission by the Ethernet driver. The
 * function is non blocking. When it successfully returns then it has programmed the MAC's
 * DMA to upload the data. (Which has not necessarily begun or even completed yet on exit
 * from this function.)\n
 *   By calling this function, the caller transfers ownership of the memory space at \a
 * payloadData to the Ethernet driver. The caller must no longer touch this memory. The
 * ownership of this memory space is returned back to the caller when he gets a success
 * message from the counterpart function eth_isTransmissionCompleted().
 *   @return
 * Get the handle \a hTxFrame of the frame or fragment if the transmission request has been
 * accepted by the Ethernet driver, i.e., the driver has had enough memory for queing the
 * request. This handle is required to query the progress of transmission using
 * eth_isTransmissionCompleted().\n
 *   Get zero, the invalid handle, if the driver's Tx queue is currently full. The frame or
 * fragment is lost if the caller doesn't submit it again after a while. The ownership of
 * the memory at \a payloadData has not been passed to the Ethernet driver.
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
 * must not be changed until the other function eth_isTransmissionCompleted() has confirmed
 * that the Ethernet driver has consumed the data.\n
 *   Note, for optimal performance, the payload data should be 64 Byte aligned. This is
 * however not a must, any address is allowed.
 *   @param sizeOfPayloadData
 * The number of bytes in \a payloadData.
 *   @remark
 * This function must be called only from the user task context executing in process
 * bsw_pidUser on core 0. Any attempt to use it from OS code or another core or process
 * will lead to undefined behavior.
 *   @remark
 * The API of the Ethernet driver is not reentrant. All function need to be called from the
 * same context or from context, which implement mutual exclusion. This holds in particular
 * for the paired calls of eth_sendFrame() and eth_isTransmissionCompleted().
 *   @remark
 * So far, submitting frame fragments has not be implemented yet. Each call of this
 * function will request to transmit an Ethernet frame having \a payloadData[] as content
 * data.
 *   
 */
static inline uintptr_t eth_sendFrame( unsigned int idxEthDev
                                     , unsigned int idxRing
                                     , const void * const payloadData
                                     , unsigned int sizeOfPayloadData
                                     )
{
    return (uintptr_t)rtos_systemCall( ETH_SYSCALL_SEND_FRAME
                                     , idxEthDev
                                     , idxRing
                                     , payloadData
                                     , sizeOfPayloadData
                                     );
} /* eth_sendFrame */




/**
 * System call of Ethernet driver function ENET_DRV_GetTransmitStatus().\n
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
 */
static inline bool eth_isTransmissionCompleted(uintptr_t hTxFrame)
{
    return (bool)rtos_systemCall(ETH_SYSCALL_IS_TRANSMISSION_COMPLETED, hTxFrame);

} /* eth_isTransmissionCompleted */

#endif  /* ETH_ETHERNET_INCLUDED */
