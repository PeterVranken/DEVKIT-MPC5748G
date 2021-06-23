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
 * chanels or can release them. This way, channels can be temporarily used or permanently
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
 *   dma_osGetDMAChannel
 * Local functions
 *   configDMA
 */

/*
 * Include files
 */

#include <assert.h>

#include "typ_types.h"
#include "rtos.h"
#include "dma_dmaDriver.h"

#if defined(MCU_MPC5748G)  &&  defined(MCU_MPC5775B) \
    ||  !defined(MCU_MPC5748G)  &&  !defined(MCU_MPC5775B)
# error Bad configuration of supported MCU derivative. Double-check your include \
        statements above!
#endif


/*
 * Defines
 */
 

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
 
/** A map, which relates a DMA device by index to the pointer to its register file. */
static DMA_Type * const RODATA(_dmaDeviceAry)[DMA_INSTANCE_COUNT] = DMA_BASE_PTRS;

/** A bit vector with one bit per DMA channel. A set bit means that the channel is
    allocated by some (unknown, unidentified) client code. */
static uint32_t DATA_OS(_dmaChannelAllocationAry)[(DMA_INSTANCE_COUNT*DMA_TCD_COUNT+31u)/32u] =
                                                                                  { [0] = 0 };

 
/*
 * Function implementation
 */

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
        _dmaChannelAllocationAry[0u] = 0u;

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
 *   @param idxDMADevice
 * The channel is requested from one particular DMA device. The devices, which are
 * available on the given derivative are addressed to by zero based index. The range is
 * 0..#DMA_INSTANCE_COUNT. Violations are caught by assertion and the function returns \a
 * false in PRODUCTION compilation.
 *   @param idxChannel
 * The requested channel is addressed to by zero based index. The range is
 * 0..#DMA_TCD_COUNT. Violations are caught by assertion and the function returns \a false
 * in PRODUCTION compilation.
 *   @remark
 * The function can be called from all OS contexts on a single core. All other cores in the
 * system must not invoke this function simultaneously. Mutual exclusion of cores needs to
 * be implemented by the calling code. Disregarding this rule can result in two clients
 * both getting access to the same channel!
 *   @see dma_osReleaseDMAChannel()
 *   @todo
 * Some cmmonly used channel feature could be configured in this function, e.g. use of IRQ on
 * transfer done, etc.
 */
bool dma_osAcquireDMAChannel(unsigned int idxDMADevice, unsigned int idxChannel)
{
    /* In all supported derivatives, all DMA devices have the same number of channels. */
    if(idxDMADevice > DMA_INSTANCE_COUNT  ||  idxChannel > DMA_TCD_COUNT)
    {
        assert(false);
        return false;
    }
     
    /* This function needs to be thread-safe, even if it'll likely be called only during
       system start up, when there aren't competing contexts. Unfortunately, this is not
       guaranteed. */
    /// @todo All cores should have access, so we would need a system-wide mutual
    // exclusion. Unfortunately, the offered cross-core communication mechanisms differ for
    // the derivatives, which are supported here and - for now - we need to limit the use
    // of this API to a single core.
    const uint32_t stateOnEntry = rtos_osEnterCriticalSection();
    
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
    
    rtos_osLeaveCriticalSection(stateOnEntry);
    
    /// @todo Put some common, basic channel configuration here:
    // - Reset of pending error and IRQ bits
    // - Adresses to zero
    // - stuff requested by additional function arguments (see TODO above)

    return success;
    
} /* End of dma_osAcquireDMAChannel */




/**
 * Return a channel from a DMA device after use so that it can be acquired and used by
 * other clients. Counterpart of dma_osAcquireDMAChannel().\n
 *   @param idxDMADevice
 * The channel belongs to one particular DMA device. The devices, which are available on
 * the given derivative are addressed to by zero based index. The range is
 * 0..#DMA_INSTANCE_COUNT. Violations are caught by assertion.
 *   @param idxChannel
 * The requested channel is addressed to by zero based index. The range is
 * 0..#DMA_TCD_COUNT. Violations or the attempt to release a non allocated channel are
 * caught by assertion.
 *   @remark
 * The function can be called from all OS contexts on a single core. All other cores in the
 * system must not invoke this function simultaneously. Mutual exclusion of cores needs to
 * be implemented by the calling code. Disregarding this rule can result in two clients
 * both getting access to the same channel!
 *   @remark
 * The function doesn't keep tack who had allocated a channel and who returns it. Proper
 * use of the function is a prerequisite of conflict free operation of DMA channels but
 * this can't be checked by the function! Careful use is a must.
 *   @see dma_osAcquireDMAChannel()
 */
void dma_osReleaseDMAChannel(unsigned int idxDMADevice, unsigned int idxChannel)
{
    /* In all supported derivatives, all DMA devices have the same number of channels. */
    if(idxDMADevice > DMA_INSTANCE_COUNT  ||  idxChannel > DMA_TCD_COUNT)
    {
        assert(false);
    }
     
    /// @todo Put some channel de-configuration code here, e.g.
    // - Disabling of all IRQs
    // - Reset of all pending IRQ and error bits
    // - Reset of addresses and counts to zero

    /* This function needs to be thread-safe, even if it'll likely be called only during
       system start up, when there aren't competing contexts. Unfortunately, this is not
       guaranteed. */
    /// @todo All cores should have access, so we would need a system-wide mutual
    // exclusion. Unfortunately, the offered cross-core communication mechanisms differ for
    // the derivatives, which are supported here and - for now - we need to limit the use
    // of this API to a single core.
    const uint32_t stateOnEntry = rtos_osEnterCriticalSection();
    
    #define WORD_SIZE   (sizeof(_dmaChannelAllocationAry[0])*8u)
    const unsigned int idxLockBit = idxDMADevice*DMA_TCD_COUNT + idxChannel
                     , idxWord = idxLockBit/WORD_SIZE
                     , maskForBit = 1u << (idxLockBit - idxWord*WORD_SIZE);
    const uint32_t allocVec = _dmaChannelAllocationAry[idxWord];
    
    /* Just reset the reservation bit. */
    assert((allocVec & maskForBit) != 0);
    _dmaChannelAllocationAry[idxWord] = allocVec & ~maskForBit;
    #undef WORD_SIZE

    rtos_osLeaveCriticalSection(stateOnEntry);
    
} /* End of dma_osReleaseDMAChannel */




/**
 * Get access to a DMA channel.\n
 *   The channel must have been acquired before, see dma_osAcquireDMAChannel().
 *   @return
 * The channel is returned as pointer to the register file in the peripheral address space.
 * The pointer is modelled as a struct, whichis identical to the definition in the NXP
 * derivative header. The same names and support macros can be used to access the registers
 * and their fields.
 *   @param idxDMADevice
 * The requested channel belongs to one particular DMA device. The devices, which are
 * available on the given derivative are addressed to by zero based index. The range is
 * 0..#DMA_INSTANCE_COUNT. Violations are caught by assertion and the function returns NULL
 * in PRODUCTION compilation.
 *   @param idxChannel
 * The requested channel is addressed to by zero based index. The range is
 * 0..#DMA_TCD_COUNT. Violations or the attempt to access a non allocated channel are
 * caught by assertion and the function returns NULL in PRODUCTION compilation.
 */
dma_dmaTransferCtrlDesc_t *dma_osGetDMAChannel( unsigned int idxDMADevice
                                              , unsigned int idxChannel
                                              )
{
    assert(idxDMADevice < sizeOfAry(_dmaDeviceAry)  &&  idxChannel < DMA_TCD_COUNT);
    return (dma_dmaTransferCtrlDesc_t*)&_dmaDeviceAry[idxDMADevice]->TCD[idxChannel];

} /* End of dma_osGetDMAChannel */
