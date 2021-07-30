#ifndef DMA_DMADRIVER_INCLUDED
#define DMA_DMADRIVER_INCLUDED
/**
 * @file dma_dmaDriver.h
 * Definition of global interface of module dma_dmaDriver.c
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

/*
 * Include files
 */

#include <stdint.h>
#include <stdbool.h>

/** @todo Uncomment the very device header, which relates to the MCU in your project. */
//#include "MPC5775B.h"
#include "MPC5748G.h"


/*
 * Defines
 */

/** Initializer expression for new, empty, uninitialized, unusable DMA channel handle of
    type dma_dmaChannel_t. */
#define DMA_DMA_CHANNEL_UNINITIALIZED_OBJ   {.pDMA = NULL, .idxChn = 0, .pTCD = NULL,}


/*
 * Global type definitions
 */

/** The specification of the register file for a single DMA channel (a "transfer control
    descriptor" or TCM). Unfortunately, the derivative headers by NXP don't use a named
    type for their definition of the file set, so we need to have a copy of the same type
    and with a typedef, which makes it usable outside the definition of the complete DMA. */
typedef struct dma_dmaTransferCtrlDesc_t
{                                           /* offset: 0x1000, array step: 0x20 */
    __IO uint32_t SADDR;                             /**< TCD Source Address, array offset: 0x1000, array step: 0x20 */
    __IO uint16_t ATTR;                              /**< TCD Transfer Attributes, array offset: 0x1004, array step: 0x20 */
    __IO uint16_t SOFF;                              /**< TCD Signed Source Address Offset, array offset: 0x1006, array step: 0x20 */
    union {                                          /* offset: 0x1008, array step: 0x20 */
      __IO uint32_t MLNO;                              /**< TCD Minor Byte Count (Minor Loop Mapping Disabled), array offset: 0x1008, array step: 0x20 */
      __IO uint32_t MLOFFNO;                           /**< TCD Signed Minor Loop Offset (Minor Loop Mapping Enabled and Offset Disabled), array offset: 0x1008, array step: 0x20 */
      __IO uint32_t MLOFFYES;                          /**< TCD Signed Minor Loop Offset (Minor Loop Mapping and Offset Enabled), array offset: 0x1008, array step: 0x20 */
    } NBYTES;
    __IO uint32_t SLAST;                             /**< TCD Last Source Address Adjustment, array offset: 0x100C, array step: 0x20 */
    __IO uint32_t DADDR;                             /**< TCD Destination Address, array offset: 0x1010, array step: 0x20 */
    union {                                          /* offset: 0x1014, array step: 0x20 */
      __IO uint16_t ELINKNO;                           /**< TCD Current Minor Loop Link, Major Loop Count (Channel Linking Disabled), array offset: 0x1014, array step: 0x20 */
      __IO uint16_t ELINKYES;                          /**< TCD Current Minor Loop Link, Major Loop Count (Channel Linking Enabled), array offset: 0x1014, array step: 0x20 */
    } CITER;
    __IO uint16_t DOFF;                              /**< TCD Signed Destination Address Offset, array offset: 0x1016, array step: 0x20 */
    __IO uint32_t DLASTSGA;                          /**< TCD Last Destination Address Adjustment/Scatter Gather Address, array offset: 0x1018, array step: 0x20 */
    union {                                          /* offset: 0x101C, array step: 0x20 */
      __IO uint16_t ELINKNO;                           /**< TCD Beginning Minor Loop Link, Major Loop Count (Channel Linking Disabled), array offset: 0x101C, array step: 0x20 */
      __IO uint16_t ELINKYES;                          /**< TCD Beginning Minor Loop Link, Major Loop Count (Channel Linking Enabled), array offset: 0x101C, array step: 0x20 */
    } BITER;
    __IO uint16_t CSR;                               /**< TCD Control and Status, array offset: 0x101E, array step: 0x20 */

} dma_dmaTransferCtrlDesc_t;    
  

/** The representation of a DMA channel is used by the API of the DMA driver. */
typedef struct dma_dmaChannel_t
{
    /** The DMA device, pointer to the register file. */
    DMA_Type *pDMA;
    
    /** The index of the DMA channel in the DMA device.\n
          Note, pTCD == &pDMA->TCD[idxChn] is an invariant. */
    unsigned int idxChn;
    
    /** The register file of the DMA device, which relates to the DMA channel. */
    dma_dmaTransferCtrlDesc_t *pTCD;

} dma_dmaChannel_t;



/*
 * Global data declarations
 */


/*
 * Global prototypes
 */

/** One time initialization of DMA device. */
void dma_osInitDMADriver(void);

/** Request a channel from a DMA device for exclusive use. */
bool dma_osAcquireDMAChannel( dma_dmaChannel_t * const pHDMAChn
                            , unsigned int idxDMADevice
                            , unsigned int idxChannel
                            , const dma_dmaTransferCtrlDesc_t * const pChnCfg
                            , bool reset
                            );

/** Return a channel from a DMA device after use. */
void dma_osReleaseDMAChannel(dma_dmaChannel_t * const pHDMAChn);

/** Set the source address of an upcoming transfer. */
void dma_osSetDMAChannelSourceAddress( const dma_dmaChannel_t * const pHDMAChn
                                     , const void *pSourceOfTransfer
                                     );

/** Set the destination address of an upcoming transfer. */
void dma_osSetDMAChannelDestinationAddress( const dma_dmaChannel_t * const pHDMAChn
                                          , void *pTransferDestination
                                          );

/** Set the number of major iterations of an upcoming DMA transfer. */
void dma_osSetDMAChannelNoMajorIterations( const dma_dmaChannel_t * const pHDMAChn
                                         , unsigned int noMajorIterations
                                         );

/** Enable or disable the triggers of a DMA channel from an I/O device. */
void dma_osEnableDMAChannelTriggerFromIODevice( const dma_dmaChannel_t * const pHDMAChn
                                              , bool enable
                                              );

/** Get the current status of the gate in the request line between an I/O device and the
    DMA channel. */
bool dma_osGetDMAChannelEnableTriggerFromIODevice(const dma_dmaChannel_t * const pHDMAChn);

/** Get the current status of a possibly pending transfer request from the connected I/O
    device. */
bool dma_osGetDMAChannelPendingTriggerFromIODevice(const dma_dmaChannel_t * const pHDMAChn);


/*
 * Global inline functions
 */

/**
 * Get the register file of the DMA channel by reference.\n
 *   It is allowed and intended to directly manipulate the TCD registers of the DMA device
 * (i.e. effectively the DMA channel). The API of the DMA driver only supports some
 * standard use cases of DMA without doing so, all other, more specific DMA tasks wil
 * require full flexibility in accessing these registers. This function returns the pointer
 * to the register file for the given chanel.
 *   @return
 * Get the pointer to the TCD register file. The normal NXP macros and mechanisms can be
 * applied to access the registers and their fields.
 *   @param pHDMAChn
 * The handle of the affected channel by reference. The TCD of this channel is returned.
 */
static inline dma_dmaTransferCtrlDesc_t *dma_getTransferControlDescriptor
                                                (const dma_dmaChannel_t * const pHDMAChn)
{ 
    /* Consistency check of handle. */
    assert((void*)pHDMAChn->pTCD == (void*)&pHDMAChn->pDMA->TCD[pHDMAChn->idxChn]);
    return pHDMAChn->pTCD;

} /* End of dma_getTransferControlDescriptor */

#endif  /* DMA_DMADRIVER_INCLUDED */
