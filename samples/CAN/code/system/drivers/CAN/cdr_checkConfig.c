/**
 * @file cdr_checkConfig.c
 * This module offers a function to runsome plausibility checks on the driver cofiguration
 * data set. It doesn't contain functional code. Since the configuration data set is
 * constant, the recommendation is to call the check function only from the DEBUG
 * compilation.
 *
 * Copyright (C) 2020 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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
 *   cdr_checkDriverConfiguration
 * Local functions
 */

/*
 * Include files
 */

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "typ_types.h"
#include "rtos.h"
#include "cdr_canDriverAPI.h"
#include "cdr_checkConfig.h"


/*
 * Defines
 */
 

/*
 * Local type definitions
 */
 
 
/*
 * Local prototypes
 */
 
 
/*
 * Data definitions
 */
 
 
/*
 * Compile-time code checks
 */
 
_Static_assert( sizeOfAry(cdr_canDriverConfig) == sizeOfAry(cdr_mapIdxToCanDevice)
              , "Invalid CAN driver configuration"
              );
_Static_assert( cdr_canDev_noCANDevicesEnabled <= CAN_INSTANCE_COUNT
              , "Inconsistent configuration, too many CAN devices enabled"
              );
_Static_assert( CDR_NO_CAN_DEVICES_ENABLED == cdr_canDev_noCANDevicesEnabled
              , "Implementation error: Inconsistent header files"
              );
_Static_assert( sizeOfAry(cdr_canDriverConfig) == cdr_canDev_noCANDevicesEnabled
              , "Inconsistent definition of number of enabled CAN devices"
              );
_Static_assert( sizeOfAry(cdr_canDriverConfig) == sizeOfAry(cdr_mapIdxToCanDevice)
              , "Inconsistent definition of data objects. Check source code"
              );
/* Check our own definition of a struct, which should match the memory layout of a CAN
   mailbox for non-FC frames. */
_Static_assert( sizeof(cdr_mailbox_t) == 16  &&  offsetof(cdr_mailbox_t, payload) == 8
                &&  offsetof(cdr_mailbox_t, payload_u16) == 8
                &&  offsetof(cdr_mailbox_t, payload_u32) == 8
              , "Bad model of CAN mailbox"
              );


 
/*
 * Function implementation
 */

/**
 * This function contains a lot of self tests of the driver configuration.\n
 *   @return
 * \a true, if all tests succeeded, \a false if an error or inconsistency was found in the
 * configuration.
 *   @remark
 * The configuration is a compile-time constant. It makes little sense to unconditionally
 * and always call this function. The recommendation is to call it only in DEBUG
 * compilation but not in production code.
 */
bool cdr_checkDriverConfiguration(void)
{
    /* In DEBUG compilation it is useful to halt the anyway in-operational SW immediately
       to support to identification of the particular problem in the debugger. In
       PRODUCTION, we just return false and the SW must not start up. */
    #define ASSERT(cond)    if(!(cond)){assert(false); return false;}
    
    /* To support debugging, we make the device index static in DEBUG compilation. */
#ifdef DEBUG
    static unsigned int DATA_OS(idxDev);
#else
    unsigned int idxDev;
#endif
    for(idxDev=0; idxDev<(unsigned)cdr_canDev_noCANDevicesEnabled; ++idxDev)
    {
        const cdr_canDeviceConfig_t * const pDevCfg = &cdr_canDriverConfig[idxDev];

        /* The number of mailboxes is hardware limited. Unfortunately, we don't have found a
           related macro in the NXP derivative header. */
        ASSERT(pDevCfg->noMailboxes <= 96);
        
        /* The FIFO requires at least 6 Mailboxes and more, dependent on the size of the
           filter table. */
        ASSERT(cdr_getIdxOfFirstMailbox(pDevCfg) <= pDevCfg->noMailboxes);
        
        /* Technically feasible: No single CAN message can be configured. Nonetheless, we
           rate this an error. */
        ASSERT(pDevCfg->isFIFOEnabled ||  pDevCfg->noMailboxes > 0);
        
        /* CAN error interrupts are configured but not implemented yet. */
        ASSERT(pDevCfg->irqGroupErrorIrqPrio == 0);
        
        /* FIFO is enabled but mailboxes interrupts are configured for mailboxes, which are
           not available with FIFO enabled. */
        const unsigned int idxFirstNormalMailbox = cdr_getIdxOfFirstMailbox(pDevCfg);
        ASSERT(idxFirstNormalMailbox <= 3  ||  pDevCfg->irqGroupMB0_3IrqPrio == 0);
        ASSERT(idxFirstNormalMailbox <= 7  ||  pDevCfg->irqGroupMB4_7IrqPrio == 0);
        ASSERT(idxFirstNormalMailbox <= 11  ||  pDevCfg->irqGroupMB8_11IrqPrio == 0);
        ASSERT(idxFirstNormalMailbox <= 15  ||  pDevCfg->irqGroupMB12_15IrqPrio == 0);
        ASSERT(idxFirstNormalMailbox <= 31  ||  pDevCfg->irqGroupMB16_31IrqPrio == 0);
        ASSERT(idxFirstNormalMailbox <= 38);
        
        /* The target core for any IRQ needs to be in range. */
        ASSERT( pDevCfg->irqGroupFIFOTargetCore < RTOS_NO_CORES
                &&  pDevCfg->irqGroupErrorTargetCore < RTOS_NO_CORES
                &&  pDevCfg->irqGroupMB0_3TargetCore < RTOS_NO_CORES
                &&  pDevCfg->irqGroupMB4_7TargetCore < RTOS_NO_CORES
                &&  pDevCfg->irqGroupMB8_11TargetCore  < RTOS_NO_CORES
                &&  pDevCfg->irqGroupMB12_15TargetCore < RTOS_NO_CORES
                &&  pDevCfg->irqGroupMB16_31TargetCore < RTOS_NO_CORES
                &&  pDevCfg->irqGroupMB32_63TargetCore < RTOS_NO_CORES
                &&  pDevCfg->irqGroupMB64_95TargetCore < RTOS_NO_CORES
              );

        /* The INTC priority of any IRQ needs to be in range. */
        ASSERT( pDevCfg->irqGroupFIFOIrqPrio <= 15
                &&  pDevCfg->irqGroupErrorIrqPrio <= 15
                &&  pDevCfg->irqGroupMB0_3IrqPrio <= 15
                &&  pDevCfg->irqGroupMB4_7IrqPrio <= 15
                &&  pDevCfg->irqGroupMB8_11IrqPrio <= 15
                &&  pDevCfg->irqGroupMB12_15IrqPrio <= 15
                &&  pDevCfg->irqGroupMB16_31IrqPrio <= 15
                &&  pDevCfg->irqGroupMB32_63IrqPrio <= 15
                &&  pDevCfg->irqGroupMB64_95IrqPrio <= 15
              );

        /* If we have a FIFO then we need to have an enabled IRQ, too. And the opposite. */
        ASSERT(!pDevCfg->isFIFOEnabled  &&  pDevCfg->irqGroupFIFOIrqPrio == 0
               ||  pDevCfg->isFIFOEnabled  &&  pDevCfg->irqGroupFIFOIrqPrio > 0
              );
        
        /* If we have a FIFO then we need to have an Rx callback, too. */
        ASSERT(!pDevCfg->isFIFOEnabled  ||  pDevCfg->osCallbackOnRx != NULL);
        
        /* If we have a mailbox IRQ enabled then we need to have a callback, too. */
        ASSERT(!(pDevCfg->irqGroupFIFOIrqPrio > 0
                 ||  pDevCfg->irqGroupErrorIrqPrio > 0
                 ||  pDevCfg->irqGroupMB0_3IrqPrio > 0
                 ||  pDevCfg->irqGroupMB4_7IrqPrio > 0
                 ||  pDevCfg->irqGroupMB8_11IrqPrio > 0
                 ||  pDevCfg->irqGroupMB12_15IrqPrio > 0
                 ||  pDevCfg->irqGroupMB16_31IrqPrio > 0
                 ||  pDevCfg->irqGroupMB32_63IrqPrio > 0
                 ||  pDevCfg->irqGroupMB64_95IrqPrio > 0
                )
               ||  pDevCfg->osCallbackOnRx != NULL  ||  pDevCfg->osCallbackOnTx != NULL
              );

    } /* End for(All enabled CAN devices) */

    return true;

} /* End of cdr_checkDriverConfiguration */




