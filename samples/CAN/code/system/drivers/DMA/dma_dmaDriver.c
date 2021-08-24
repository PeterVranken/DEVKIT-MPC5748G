/**
 * @file dma_dmaDriver.c
 * I/O driver for eDMA dvices of MPC5748G and MPC5775B/E.\n
 *   The DMA device is special in comparison to most other device in that it is a shared
 * device, shared for operation with many other devices. The configuration of the DMA for
 * use with other I/O divices is specific to those other devices and should not be done or
 * maitained here in a general DMA driver. On the other hand, doing all DMA configuration
 * only in the context of the I/O drivers of those other devices is difficult due to
 * possible conflicts between different drivers - which shaould be kept self-contained and
 * independent as far as possible.\n
 *   This is the concept of overcoming the conflicting demands: The DMA device is basically
 * organized in so-called channels. Effectively, each channel is a separate and widely
 * independent DMA engine. Such an engine contains nearly all of the configuration, which
 * affects a particular other I/O device and which impacts the operation of that device.
 * Similarly, if the DMA is going to be used for ordinary memory content movements then
 * only the channel configuration suffices to define the given task. 
 *   The DMA device has only a few global configuration settings, which affect all
 * channels. This driver configures only these few settings but doesn't care about the
 * channel configuration. It offers a simple resource management for the channels. The
 * clients of the DMA driver, mainly other I/O drivers, can make reservations for specific
 * channels or can release them. This way, channels can be temporarily used or permanently
 * allocated by other I/O drivers.\n
 *   The few global configuration settings need to be done with the perspective on the
 * complete system. It's mainly about channel priority when several DMA channels want to
 * move data at the same time. The driver widely uses the default settings of the DMA
 * device and these should be suitable for most systems.
 *   The configuration of a DMA channel belongs into the scope of the client code, which
 * requests a channel, i.e. it's normally done inside another I/O driver and according to
 * the demands of that other I/O device.\n
 *   All configuration conflicts are avoided as long as all DMA channels are used solely
 * through this resource management.\n
 *   The use of the DMA controller is futhermore supported by offering a few APIs, which
 * hide some standard operations on DMA channels, like setting the transfer addresses or
 * enabling IRQs.
 *
 * @note References "RM48" in this module refer to "MPC5748G Reference Manual", document
 * number: MPC5748GRM, Rev. 6, 10/2017.
 *   References "RM75" in this module refer to "MPC5775E/MPC5775B Reference Manual",
 * document number: MPC5775E, Rev. 1, 05/2018.
 *
 * Copyright (C) 2021 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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
 *   dma_osInitDMADriver
 *   dma_osAcquireDMAChannel
 *   dma_osReleaseDMAChannel
 *   dma_osSetDMAChannelSourceAddress
 *   dma_osSetDMAChannelDestinationAddress
 *   dma_osSetDMAChannelNoMajorIterations
 *   dma_osEnableDMAChannelTriggerFromIODevice
 *   dma_getTransferControlDescriptor (inline)
 * Local functions
 *   getDMADevice
 *   getDMAChannel
 *   configDMA
 */

/*
 * Include files
 */

#include <limits.h>
#include <assert.h>

#include "dma_dmaDriver.h"
#include "typ_types.h"
#include "rtos.h"
#include "mtx_mutex.h"

#if defined(MCU_MPC5748G)  &&  defined(MCU_MPC5775B) \
    ||  !defined(MCU_MPC5748G)  &&  !defined(MCU_MPC5775B)
# error Bad configuration of supported MCU derivative. Double-check your include \
        statements above!
#endif


/*
 * Defines
 */
 
/** The number of 32 Bit words, which are required to spend one bit for each available
    DMA channel. */ 
#define SIZE_OF_CHN_ALLOCATION_ARY ((DMA_INSTANCE_COUNT*DMA_TCD_COUNT+31u)/32u)


/*
 * Local type definitions
 */
 
/* Unfortunately, NXP didn't name the type, which describes the DMA channel. For them, it's
   just a nested element of type DMA_Type. We have adopted and named their original
   definition, but this means hard and ugly type casts. A minimum consistency check of both
   definitions is comparison of their sizes and sample checks of some major field's
   offsets. */
_Static_assert( sizeof(dma_dmaTransferCtrlDesc_t) == sizeof(((const DMA_Type*)NULL)->TCD[0])
                &&  offsetof(dma_dmaTransferCtrlDesc_t, SADDR)
                    == (uintptr_t)&((const DMA_Type*)0u)->TCD[0].SADDR 
                       - offsetof(DMA_Type, TCD)
                &&  offsetof(dma_dmaTransferCtrlDesc_t, DADDR)
                    == (uintptr_t)&((const DMA_Type*)0u)->TCD[0].DADDR 
                       - offsetof(DMA_Type, TCD)
              , "Inconsistent adoption of NXP type TCD"
              );

/*
 * Local prototypes
 */
 
 
/*
 * Data definitions
 */
 
/** A bit vector with one bit per DMA channel. A set bit means that the channel is
    allocated by some (unknown, unidentified) client code. */
static uint32_t DATA_OS(_dmaChannelAllocationAry)[SIZE_OF_CHN_ALLOCATION_ARY] =
                                        { [0 ... (SIZE_OF_CHN_ALLOCATION_ARY-1u)] = UINT_MAX };

/*
 * Function implementation
 */

/**
 * Get a DMA device by index.
 *   @return
 * The DMA device is returned as pointer to the register file in the peripheral address
 * space.
 *   @param idxDMADevice
 * The request relates to one particular DMA device. The devices, which are available on
 * the given derivative are addressed to by zero based index. The range is
 * 0..#DMA_INSTANCE_COUNT. Violations are caught by assertion.
 */
static inline DMA_Type *getDMADevice(unsigned int idxDMADevice)
{
    /** A map, which relates a DMA device by index to the pointer to its register file. */
    static DMA_Type * const RODATA(dmaDeviceAry_)[DMA_INSTANCE_COUNT] = DMA_BASE_PTRS;

    assert(idxDMADevice < sizeOfAry(dmaDeviceAry_));
    return dmaDeviceAry_[idxDMADevice];
    
} /* End of getDMADevice */





/**
 * Get access to a DMA channel.\n
 *   The channel must have been acquired before, see dma_osAcquireDMAChannel().
 *   @return
 * The channel is returned as pointer to the register file in the peripheral address space.
 * The pointer is modelled as a struct, which is identical to the definition in the NXP
 * derivative header. The same names and support macros can be used to access the registers
 * and their fields.
 *   @param idxDMADevice
 * The requested channel belongs to one particular DMA device. The devices, which are
 * available on the given derivative are addressed to by zero based index. The range is
 * 0..#DMA_INSTANCE_COUNT. Violations are caught by assertion.
 *   @param idxChannel
 * The requested channel is addressed to by zero based index. The range is
 * 0..#DMA_TCD_COUNT. Violations or the attempt to access a non allocated channel are
 * caught by assertion and the function returns NULL in PRODUCTION compilation.
 */
static inline dma_dmaTransferCtrlDesc_t *getDMAChannel( unsigned int idxDMADevice
                                                      , unsigned int idxChannel
                                                      )
{
    DMA_Type * const pDMA = getDMADevice(idxDMADevice);
    
    assert(idxChannel < DMA_TCD_COUNT);
    return (dma_dmaTransferCtrlDesc_t*)&pDMA->TCD[idxChannel];
    
} /* End of getDMAChannel */




/**
 * Initialization of a single DMA device at system startup.
 *   @param pDMA
 * The DMA device by reference, which the operation relates to.
 */
static void configDMA(DMA_Type * const pDMA)
{
#ifdef MCU_MPC5748G
    /* Available for the MPC5748G only:
         Channel n Master ID Register (DMA_DCHMIDn), RM48 70.3.21: Not touched. Default
       value after reset is to let the DMA engine use its own identity when accessing the
       buses.
         EMI: By setting this bit in this register, we can make the DMA engine pretend
       being the core that writes (later) into the TCD channel registers. This will make DMA
       memory/peripheral accesses be handled as according accesses from the the DMA channel
       using CPU.
         All other bits are read only. */
    /// @todo If required, setting this bit should become an argument of the API to request a channel.
    //pDMA->DCHMID[idxChn] = DMA_DCHMID_EMI(1);
#endif

    /* RM48, section 70.3.5, pp.3492ff, and RM75, section 16.4.5, pp.623ff, Control
       Register (DMA_CR), group arbitration.
         GRPnPRI: Group priorities, needs to be different numbers in choseable order. We
       don't change the default after reset.
         EMLM: We don't use address offsets after minor and between two major loops, 0 means
       off.
         ERGA: 1: Round Robin for group arbitration, 0: Priority controlled
         ERCA: 1: Round Robin for channel arbitration, 0: Priority controlled
         EDBG: 1: Halt DMA when entering the debugger. By experience, for debugging of this
       multi-core this is rather counterproductive since mostly one or two cores are
       running while only one is being debugged.
         The other fields are zero after reset and we do neiter require nor change these
       values.
         Note, these settings affects all channels! */
    pDMA->CR = 0u
#ifdef MCU_MPC5775B
                | DMA_CR_GRP3PRI(3u)
                | DMA_CR_GRP2PRI(2u)
#endif
                | DMA_CR_GRP1PRI(1u)
                | DMA_CR_GRP0PRI(0u)
                | DMA_CR_EMLM(0u)
                | DMA_CR_ERGA(0u)
                | DMA_CR_ERCA(0u)
                | DMA_CR_EDBG(0u)   /* 0: Continue in debug, 1: don't start new channel */
                ;

    /* RM48, section 70.4.20, pp.3525ff, and RM75, section 16.4.26, pp.673ff, Channel n
       Priority Register (DMA_DCHPRIn): We use priority controlled channel arbitration. All
       active channels need to have different priorities. The standard configuration is to
       set the priority to the channel number. This is the reset default of the hardware
       and - in order to touch the global settings as little as possible - we are not going
       to change it. The reset default disables preemptability of all channels.
         Note, this configuration affects all channels! */
    unsigned int idxChn;
    for(idxChn=0; idxChn<DMA_DCHPRI_COUNT; ++idxChn)
    {
        /* ECP, 0x80: 1: Channel can be preempted, 0: cannot be preempted.
             DPA, 0x40: 0: Channel can preempt, 1: cannot preempt others.
             CHHPRI: Channel priority from 0..15. The macro DMA_DCHPRI_CHPRI filters the
           upper bits of the loop counter so that we get four groups with priority
           identical to channel index in group. */
        pDMA->DCHPRI[idxChn] = DMA_DCHPRI_ECP(0u)
                               | DMA_DCHPRI_DPA(0u)
                               | DMA_DCHPRI_CHPRI(idxChn);
    }
    
    /* RM75, 16.4.12 Clear Enable Request Register (DMA_CERQ). Disable requests for any DMA
       channel from the connected I/O devices. */
    pDMA->CERQ = DMA_CERQ_NOP(0u) | DMA_CERQ_CAER(1u) | DMA_CERQ_CERQ(0u);

    /* RM75, 16.4.14 Clear Enable Error Interrupt Register (DMA_CEEI). All error interrupts
       are disabled. */
    pDMA->CEEI = DMA_CEEI_NOP(0u) | DMA_CEEI_CAEE(1u) | DMA_CEEI_CEEI(0u);

    /* RM75, 16.4.15 Clear Interrupt Request Register (DMA_CINT). All possibly pending IRQs
       are cleared. */
    pDMA->CINT = DMA_CINT_NOP(0u) | DMA_CINT_CAIR(1u) | DMA_CINT_CINT(0u);

    /* RM75, 16.4.16 Clear Error Register (DMA_CERR). All error bits (or pending error
       interrupts) are reset. */
    pDMA->CERR = DMA_CERR_NOP(0u) | DMA_CERR_CAEI(1u) | DMA_CERR_CERR(0u);
    
} /* configDMA */



/**
 * Initialization of DMA device at system startup. This initialization needs to happen
 * before any client device can request a DMA channel using dma_acquireChannel() or make
 * use of it.
 */
void dma_osInitDMADriver(void)
{
    /* Mark all channels as currently unused. */
    unsigned int u;
    for(u=0u; u<sizeOfAry(_dmaChannelAllocationAry); ++u)
        _dmaChannelAllocationAry[u] = 0u;

#if defined(MCU_MPC5748G)
    configDMA(DMA);
#elif defined(MCU_MPC5775B)
    configDMA(DMA_0);
    configDMA(DMA_1);
#endif
} /* End of dma_osInitDMADriver */



/**
 * Request a channel from a DMA device for exclusive use.\n
 *   The client code of the DMA driver, e.g. the device driver for some DMA controlled
 * other I/O device, will call this function to gain access to one particular channel of
 * the DMA. It may use this channel until it calls the counterpart function
 * dma_osReleaseDMAChannel().\n
 *   No code, system wide, must ever touch a DMA channel without requesting access to that
 * channel using this API!
 *   @return
 * \a true, if function succeeded, else \a false. The channel may be used only if the
 * function returned \a true!
 *   @param pHDMAChn
 * If the function succeeds then it has filled * \a pHDMAChn with a handle for the requested
 * DMA channel. The handle is used by the other API functions. The handle * \a pHDMAChn is
 * set to invalid if the function returns \a false.\n
 *   The caller is in charge of allocating memory space for the handle object. It is not
 * allowed to pass NULL.
 *   @param idxDMADevice
 * The channel is requested from one particular DMA device. The devices, which are
 * available on the given derivative are addressed to by zero based index. The range is
 * 0..#DMA_INSTANCE_COUNT. Violations are caught by assertion and the function returns \a
 * false in PRODUCTION compilation.
 *   @param idxChannel
 * The requested channel is addressed to by zero based index. The range is
 * 0..#DMA_TCD_COUNT. Violations are caught by assertion and the function returns \a false
 * in PRODUCTION compilation.
 *   @param pChnCfg
 * Optionally, an initial configuration of the aquired channel can be passed in. (Or NULL
 * if not needed.) The specified register contents are written binary one to one into the
 * register file of the channel device.\n
 *   No such configuration is done, if the function fails to reserve the channel for the
 * client code.
 *   @param reset
 * If \a reset is \ true then some channel related status is reset prior to returning the
 * channel object. This includes DMA requests and error and interrupt (enable) bits. (RM75
 * 16.4.12 Clear Enable Request Register (DMA_CERQ), 16.4.14 Clear
 * Enable Error Interrupt Register (DMA_CEEI), 16.4.15 Clear Interrupt Request Register
 * (DMA_CINT) and 16.4.16 Clear Error Register (DMA_CERR).)\n
 *   No such configuration is done, if the function fails to reserve the channel for the
 * client code.
 *   @remark
 * On the MPC5748G, the function can be called from any OS context on any core at any time.
 *   @warning
 * On the MPC5775B/E, the function must be called from the boot core only, i.e.
 * rtos_osGetIdxCore() == 0. Any OS context on the boot core may call this function at any
 * time.
 *   @see dma_osReleaseDMAChannel()
 *   @todo
 * Some commonly used channel features could be configured in this function, e.g. use of
 * IRQ on transfer done, etc.
 */
bool dma_osAcquireDMAChannel( dma_dmaChannel_t * const pHDMAChn
                            , unsigned int idxDMADevice
                            , unsigned int idxChannel
                            , const dma_dmaTransferCtrlDesc_t * const pChnCfg
                            , bool reset
                            )
{
    /* In all supported derivatives, all DMA devices have the same number of channels. */
    if(idxDMADevice > DMA_INSTANCE_COUNT  ||  idxChannel > DMA_TCD_COUNT)
    {
        assert(pHDMAChn != NULL);
        *pHDMAChn = (dma_dmaChannel_t){.pDMA = NULL, .idxChn = 0, .pTCD = NULL};
        assert(false);
        return false;
    }
     
    /* This function needs to be thread-safe, even if it'll likely be called only during
       system start up, when there aren't competing contexts. Unfortunately, this is not
       guaranteed. */
#if defined(MCU_MPC5748G)
    static mtx_intercoreCriticalSection_t DATA_OS(critSec) = MTX_INTERCORE_CRITICAL_SECTION;
    mtx_osEnterIntercoreCriticalSection(&critSec);
#elif defined(MCU_MPC5775B)
    /* On MCU_MPC5775B, we don't have a multi-core concept for this driver yet. For now, we
       restrict the use of this function to the boot core. */
    assert(rtos_osGetIdxCore() == 0);
    const uint32_t stateOnEntry = rtos_osEnterCriticalSection();
#endif
    
    #define WORD_SIZE   (sizeof(_dmaChannelAllocationAry[0])*8u)
    const unsigned int idxLockBit = idxDMADevice*DMA_TCD_COUNT + idxChannel
                     , idxWord = idxLockBit/WORD_SIZE
                     , maskForBit = 1u << (idxLockBit - idxWord*WORD_SIZE);
    const uint32_t allocVec = _dmaChannelAllocationAry[idxWord];
    bool success;
    if((allocVec & maskForBit) == 0)
    {
        /* Channel is currently not reserved (by someone else). Put the reservation bit
           now. */
        _dmaChannelAllocationAry[idxWord] = allocVec | maskForBit;
        success = true;
    }
    else
    {
        /* Channel is occupied. Just return error. */
        success = false;
    }
    #undef WORD_SIZE
    
#if defined(MCU_MPC5748G)
    mtx_osLeaveIntercoreCriticalSection(&critSec);
#elif defined(MCU_MPC5775B)
    rtos_osLeaveCriticalSection(stateOnEntry);
#endif
    
    if(success)
    {
        /* Our handle is a shortcut to the register files of entire DMA device and the
           requested channel only. */
        pHDMAChn->pDMA = getDMADevice(idxDMADevice);
        pHDMAChn->idxChn = idxChannel;
        pHDMAChn->pTCD = getDMAChannel(idxDMADevice, idxChannel);
        assert((void*)pHDMAChn->pTCD == (void*)&pHDMAChn->pDMA->TCD[pHDMAChn->idxChn]);

        /* A (preliminary) channel configuration can be writen into the device if
           appropriate. */
        if(pChnCfg != NULL)
            *pHDMAChn->pTCD = *pChnCfg;

        /* Some volatile status bits related to the channel can be cleared. */
        if(reset)
        {
            DMA_Type * const pDMA = pHDMAChn->pDMA;

            /* RM75, 16.4.12 Clear Enable Request Register (DMA_CERQ). Disable the requests
               for this DMA channel. */
            pDMA->CERQ = DMA_CERQ_CERQ(idxChannel);

            /* RM75, 16.4.14 Clear Enable Error Interrupt Register (DMA_CEEI) for the given
               channel. */
            pDMA->CEEI = DMA_CEEI_CEEI(idxChannel);

            /* RM75, 16.4.15 Clear Interrupt Request Register (DMA_CINT). A possibly
               pending IRQ is cleared. */
            pDMA->CINT = DMA_CINT_CINT(idxChannel);

            /* RM75, 16.4.16 Clear Error Register (DMA_CERR). The error bit related to the
               requested channel is reset. */
            pDMA->CERR = DMA_CERR_CERR(idxChannel);
        }
    } /* if(Success? Will we do some first channel configuration?) */

    return success;
    
} /* End of dma_osAcquireDMAChannel */




/**
 * Return a channel from a DMA device after use so that it can be acquired and used by
 * other clients. Counterpart of dma_osAcquireDMAChannel().\n
 *   @param pHDMAChn
 * The handle of the affected channel by reference. The function invalidates the handle.
 *   @remark
 * The function doesn't keep tack who had allocated a channel and who returns it. Proper
 * use of the function is a prerequisite of conflict free operation of DMA channels but
 * this can't be checked by the function! Careful use is a must.
 *   @remark
 * On the MPC5748G, the function can be called from any OS context on any core at any time.
 *   @warning
 * On the MPC5775B/E, the function must be called from the boot core only, i.e.
 * rtos_osGetIdxCore() == 0. Any OS context on the boot core may call this function at any
 * time.
 *   @see dma_osAcquireDMAChannel()
 */
void dma_osReleaseDMAChannel(dma_dmaChannel_t * const pHDMAChn)
{
    /* Consistency check of handle. */
    assert((void*)pHDMAChn->pTCD == (void*)&pHDMAChn->pDMA->TCD[pHDMAChn->idxChn]);
    
    /* The identification of the DMA device by index would theoretically require a search
       in the array of all of them - the inverse operation to what is done in the channel
       acquisition. However, we know the characteristics of the (few) supported devices and
       a shortcut is possible. */
#if defined(MCU_MPC5748G)
    assert(pHDMAChn->pDMA == DMA);
    const unsigned int idxDMADevice = 0u;
#elif defined(MCU_MPC5775B)
    assert(pHDMAChn->pDMA == DMA_0  ||  pHDMAChn->pDMA == DMA_1);
    const unsigned int idxDMADevice = pHDMAChn->pDMA == DMA_0? 0u: 1u;
#else
# error Bad target board selection
#endif

    /// @todo Put some channel de-configuration code here, e.g.
    // - Disabling of all IRQs
    // - Reset of all pending IRQ and error bits
    // - Reset of addresses and counts to zero

    /* This function needs to be thread-safe, even if it'll likely be called only during
       system start up, when there aren't competing contexts. Unfortunately, this is not
       guaranteed. */
#if defined(MCU_MPC5748G)
    static mtx_intercoreCriticalSection_t DATA_OS(critSec) = MTX_INTERCORE_CRITICAL_SECTION;
    mtx_osEnterIntercoreCriticalSection(&critSec);
#elif defined(MCU_MPC5775B)
    /* On MCU_MPC5775B, we don't have a multi-core concept for this driver yet. For now, we
       restrict the use of this function to the boot core. */
    assert(rtos_osGetIdxCore() == 0);
    const uint32_t stateOnEntry = rtos_osEnterCriticalSection();
#endif
    
    #define WORD_SIZE   (sizeof(_dmaChannelAllocationAry[0])*8u)
    const unsigned int idxLockBit = idxDMADevice*DMA_TCD_COUNT + pHDMAChn->idxChn
                     , idxWord = idxLockBit/WORD_SIZE
                     , maskForBit = 1u << (idxLockBit - idxWord*WORD_SIZE);
    const uint32_t allocVec = _dmaChannelAllocationAry[idxWord];
    
    /* Just reset the reservation bit. */
    assert((allocVec & maskForBit) != 0);
    _dmaChannelAllocationAry[idxWord] = allocVec & ~maskForBit;
    #undef WORD_SIZE

#if defined(MCU_MPC5748G)
    mtx_osLeaveIntercoreCriticalSection(&critSec);
#elif defined(MCU_MPC5775B)
    rtos_osLeaveCriticalSection(stateOnEntry);
#endif
    
    /* Inavlidate the handle in order to make unwanted use more unlikely. */
    *pHDMAChn = (dma_dmaChannel_t){.pDMA = NULL, .idxChn = 0, .pTCD = NULL};
    
} /* End of dma_osReleaseDMAChannel */




/**
 * Set the source address of an upcoming DMA transfer.
 *   @param pHDMAChn
 * The handle of the affected channel by reference.
 *   @param pSourceOfTransfer
 * The later DMA transfer using this channel will start with reading * \a
 * pTransferDestination.
 */
void dma_osSetDMAChannelSourceAddress( const dma_dmaChannel_t * const pHDMAChn
                                     , const void *pSourceOfTransfer
                                     )
{
    /* Consistency check of handle. */
    assert((void*)pHDMAChn->pTCD == (void*)&pHDMAChn->pDMA->TCD[pHDMAChn->idxChn]);
    
    /* See RM75 16.4.27, TCD Source Address (DMA_TCDn_SADDR), p.674. */
    pHDMAChn->pTCD->SADDR = DMA_TCD_SADDR_SADDR((__IO uint32_t)pSourceOfTransfer);

} /* End of dma_osSetDMAChannelSourceAddress */




/**
 * Set the destination address of an upcoming DMA transfer.
 *   @param pHDMAChn
 * The handle of the affected channel by reference.
 *   @param pTransferDestination
 * The later DMA transfer using this channel will start writing to * \a
 * pTransferDestination.
 */
void dma_osSetDMAChannelDestinationAddress( const dma_dmaChannel_t * const pHDMAChn
                                          , void *pTransferDestination
                                          )
{
    /* Consistency check of handle. */
    assert((void*)pHDMAChn->pTCD == (void*)&pHDMAChn->pDMA->TCD[pHDMAChn->idxChn]);
    
    /* See RM75 16.4.34, p.679. */
    pHDMAChn->pTCD->DADDR = DMA_TCD_DADDR_DADDR((__IO uint32_t)pTransferDestination);
    
} /* End of dma_osSetDMAChannelDestinationAddress */




/**
 * Set the number of major iterations of an upcoming DMA transfer. Effectively, the DMA
 * channel's register fields CITER and BITER are both set to the value \a
 * noMajorIterations.\n
 *   This function only supports the standard use case of not using channel linkage (see RM75
 * 16.4.36, pp.680f for details). It assumes that this standard use case is configured for
 * the given DMA channel, otherwise an assertion fires in DEBUG configuration.
 *   @param pHDMAChn
 * The handle of the affected channel by reference.
 *   @param noMajorIterations
 * The number of major iterations, i.e. the number of repetitions of the complete minor
 * loop. After this number of major iterations, the DMA transfer has completed.\n
 *   The range is 0 .. 0x7fff. In DEBUG compilation, this is checked by assertion.
 */
void dma_osSetDMAChannelNoMajorIterations( const dma_dmaChannel_t * const pHDMAChn
                                         , unsigned int noMajorIterations
                                         )
{
    /* The number of iterations is limited. We double-check by assertion. */
    assert(noMajorIterations <= 0x7fffu);
    
    /* Consistency check of handle. */
    assert((void*)pHDMAChn->pTCD == (void*)&pHDMAChn->pDMA->TCD[pHDMAChn->idxChn]);
    
    /* The register CITER is a union of two variants. This function supports the standard
       use case. By assertzion, we double-check that this use case is really configured. */
    assert((pHDMAChn->pTCD->CITER.ELINKNO & DMA_TCD_CITER_ELINKNO_ELINK_MASK) 
           == DMA_TCD_CITER_ELINKNO_ELINK(0u)
          );

    /* Set the beginning and current major loop iteration counts. See RM75, 16.4.36,
       pp.680f. */
    const uint16_t xITER_ELINKNO = DMA_TCD_CITER_ELINKNO_ELINK(0u)
                                   | DMA_TCD_CITER_ELINKNO_CITER(noMajorIterations);
    pHDMAChn->pTCD->CITER.ELINKNO = xITER_ELINKNO;

    
    /* The counter reload value for the major loops needs to be initialized identical
       to CITER to avoid a configuration error. See RM75, 16.4.40. */
    pHDMAChn->pTCD->BITER.ELINKNO = xITER_ELINKNO;

} /* End of dma_osSetDMAChannelNoMajorIterations */




/**
 * Enable or disable the triggers of a DAM channel from an I/O device.\n
 *   In most applications of a DMA channel, the data is transfered from or to another I/O
 * device. In this case, the real-time contsraints of that device will control the speed of
 * the data transfer; the device will trigger the DMA to read or write another word if the
 * device has produced one or requires one for processing. This trigger is an internally
 * connected wire in the MCU and the DMA channel has a gate function to either accept the
 * triggers or to ignore them. This function opens or closes this gate.
 *   @param pHDMAChn
 * The handle of the affected channel by reference.
 *   @param enable
 * \a true will open the gate such that the triggers reach the DMA channel and continuous
 * data transfer from/to the I/O device becomes possible.\n
 *   \a false will close the gate such that the triggers can't reach the DMA channel. No
 * further data transfer from/to the I/O device will occur.\n
 *   @note
 * Just controlling the trigger gate of the DMA channel is normally not sufficient to
 * control the data flow. Some related setting changes of the connected I/O device may be
 * needed in a coherent way. See RM48 - in particular RM48, 70.5.8.1f - and RM75 for
 * details of the particular I/O device.
 *   @note
 * The other function dma_osGetDMAChannelEnableTriggerFromIODevice() may be used to query
 * the state of the gate, which is affected by this function. This may be useful as the
 * state of the gate can be changed by hardware, i.e. even if not making use of this
 * function.
 */
void dma_osEnableDMAChannelTriggerFromIODevice( const dma_dmaChannel_t * const pHDMAChn
                                              , bool enable
                                              )
{
    /* Consistency check of handle. */
    assert((void*)pHDMAChn->pTCD == (void*)&pHDMAChn->pDMA->TCD[pHDMAChn->idxChn]);
    
    if(enable)
    {
        /** See RM48, 70.3.9 Set Enable Request Register (DMA_SERQ), p.3504. */
        pHDMAChn->pDMA->SERQ = DMA_SERQ_SERQ(pHDMAChn->idxChn);
    }
    else
    {
        /** See RM48, 70.3.10 Clear Enable Request Register (DMA_CERQ), p.3505. */
        pHDMAChn->pDMA->CERQ = DMA_CERQ_CERQ(pHDMAChn->idxChn);
    }    
} /* End of dma_osEnableDMAChannelTriggerFromIODevice */




/**
 * Get the current status of the gate in the request line between an I/O device controlling
 * the DMA channel and the DMA channel, i.e. the status of the line, which would request
 * the next major loop iteration. Knowing the status of this gate (request currently
 * processed by the DMA channel or not) is required for coherent starting and stopping of
 * both, I/O device and DMA channel. See RM75, 16.6.8.2: Resume a previously stopped DMA
 * channel, for more details.\n
 *   Effectively, this function queries the appropriate ERQx register of the DMA device.\n
 *   Effectively, this function reports the result of its counterpart
 * dma_osEnableDMAChannelTriggerFromIODevice().
 *   @return
 * The function returns \a true if there is the transfer request output from the connected
 * I/O device is currently connected to the DMA channel, i.e. if the DMA channel would
 * currently serve upcoming transfer requests. Otherwise it returns \a false.
 *   @param pHDMAChn
 * The handle of the affected channel by reference.
 */
bool dma_osGetDMAChannelEnableTriggerFromIODevice(const dma_dmaChannel_t * const pHDMAChn)
{
    /* Consistency check of handle. */
    assert((void*)pHDMAChn->pTCD == (void*)&pHDMAChn->pDMA->TCD[pHDMAChn->idxChn]);
    
    uint32_t ERQ;
    unsigned int idxBit = pHDMAChn->idxChn;
    
#ifdef MCU_MPC5748G
    assert(idxBit < 32u);
    ERQ = pHDMAChn->pDMA->ERQ;
#elif defined(MCU_MPC5775B)
    if(idxBit < 32u)
        ERQ = pHDMAChn->pDMA->ERQL;
    else
    {
        idxBit -= 32u;
        assert(idxBit < 32u);
        ERQ = pHDMAChn->pDMA->ERQH;
    }
#endif    
    
    return ERQ & (1u<<idxBit) != 0u;
    
} /* dma_osGetDMAChannelEnableTriggerFromIODevice */



/**
 * Get the current status of the hardware connection between an I/O device controlling the
 * DMA channel and the DMA channel, i.e. the status of the line, which would request the
 * next major loop iteration. The status of this line (request pending yes or no) is
 * required for coherent starting and stopping of both, I/O device and DMA channel. See
 * RM75, 16.6.8.2: Resume a previously stopped DMA channel, for more details.\n
 *   Effectively, this function queries the appropriate HRSx register of the DMA device.
 *   @return
 * The function returns \a true if there is a pending transfer request from the connected
 * I/O device, i.e. if the channel's bit in register HRSx is asserted. Otherwise it returns
 * \a false.
 *   @param pHDMAChn
 * The handle of the affected channel by reference.
 */
bool dma_osGetDMAChannelPendingTriggerFromIODevice(const dma_dmaChannel_t * const pHDMAChn)
{
    /* Consistency check of handle. */
    assert((void*)pHDMAChn->pTCD == (void*)&pHDMAChn->pDMA->TCD[pHDMAChn->idxChn]);
    
    uint32_t HRS;
    unsigned int idxBit = pHDMAChn->idxChn;

#ifdef MCU_MPC5748G
    assert(idxBit < 32u);
    HRS = pHDMAChn->pDMA->HRS;
#elif defined(MCU_MPC5775B)
    if(idxBit < 32u)
        HRS = pHDMAChn->pDMA->HRSL;
    else
    {
        idxBit -= 32u;
        assert(idxBit < 32u);
        HRS = pHDMAChn->pDMA->HRSH;
    }
#endif    

    return HRS & (1u<<idxBit) != 0u;
    
} /* dma_osGetDMAChannelPendingTriggerFromIODevice */




