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
  

/*
 * Global data declarations
 */


/*
 * Global prototypes
 */

/** One time initialization of DMA device. */
void dma_osInitDMADriver(void);

/** Request a channel from a DMA device for exclusive use. */
bool dma_osAcquireDMAChannel(unsigned int idxDMADevice, unsigned int idxChannel);

/** Return a channel from a DMA device after use. */
void dma_osReleaseDMAChannel(unsigned int idxDMADevice, unsigned int idxChannel);

/** Get the pointer to the DMA channel register file. */
dma_dmaTransferCtrlDesc_t *dma_osGetDMAChannel( unsigned int idxDMADevice
                                              , unsigned int idxChannel
                                              );

/*
 * Global inline functions
 */


#endif  /* DMA_DMADRIVER_INCLUDED */
