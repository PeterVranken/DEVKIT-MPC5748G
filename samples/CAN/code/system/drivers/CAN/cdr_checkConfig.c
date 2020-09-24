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

        /* We have a fixed set of supported Baud rates only. */
        ASSERT(pDevCfg->baudRate == 25  ||  pDevCfg->baudRate == 50
               ||  pDevCfg->baudRate == 100
              );

        /* The number of mailboxes is hardware limited. Unfortunately, we don't have found a
           related macro in the NXP derivative header. */
        ASSERT(pDevCfg->noMailboxes <= 96);
        
        /* The FIFO requires at least 6 Mailboxes and more, dependent on the size of the
           filter table. */
        ASSERT(cdr_getIdxOfFirstNormalMailbox(pDevCfg) <= pDevCfg->noMailboxes);
        
        /* Technically feasible: No single CAN message can be configured. Nonetheless, we
           rate this an error. */
        ASSERT(pDevCfg->isFIFOEnabled ||  pDevCfg->noMailboxes > 0);
        
        /* Our different index and table sizes computing convenience functions, like
           cdr_getAdditionalCapacityDueToFIFO() require a "neutral setting" of the FIFO
           filter table size if FIFO is not enabled. */
        ASSERT(pDevCfg->isFIFOEnabled  &&  pDevCfg->CTRL2_RFFN <= 15
               ||  !pDevCfg->isFIFOEnabled  &&  pDevCfg->CTRL2_RFFN == 0
              );
        
        /* FIFO is enabled but mailboxes interrupts are configured for mailboxes, which are
           not available with FIFO enabled. */
        const unsigned int idxFirstNormalMailbox = cdr_getIdxOfFirstNormalMailbox(pDevCfg);
        ASSERT(idxFirstNormalMailbox <= 3  ||  pDevCfg->irqGroupMB0_3.irqPrio == 0);
        ASSERT(idxFirstNormalMailbox <= 7  ||  pDevCfg->irqGroupMB4_7.irqPrio == 0);
        ASSERT(idxFirstNormalMailbox <= 11  ||  pDevCfg->irqGroupMB8_11.irqPrio == 0);
        ASSERT(idxFirstNormalMailbox <= 15  ||  pDevCfg->irqGroupMB12_15.irqPrio == 0);
        ASSERT(idxFirstNormalMailbox <= 31  ||  pDevCfg->irqGroupMB16_31.irqPrio == 0);
        ASSERT(idxFirstNormalMailbox <= 38);
        
        /* The target core for any IRQ needs to be in range. */
        ASSERT( pDevCfg->irqGroupFIFO.idxTargetCore < RTOS_NO_CORES
                &&  pDevCfg->irqGroupError.idxTargetCore < RTOS_NO_CORES
                &&  pDevCfg->irqGroupBusOff.idxTargetCore < RTOS_NO_CORES
                &&  pDevCfg->irqGroupMB0_3.idxTargetCore < RTOS_NO_CORES
                &&  pDevCfg->irqGroupMB4_7.idxTargetCore < RTOS_NO_CORES
                &&  pDevCfg->irqGroupMB8_11.idxTargetCore < RTOS_NO_CORES
                &&  pDevCfg->irqGroupMB12_15.idxTargetCore < RTOS_NO_CORES
                &&  pDevCfg->irqGroupMB16_31.idxTargetCore < RTOS_NO_CORES
                &&  pDevCfg->irqGroupMB32_63.idxTargetCore < RTOS_NO_CORES
                &&  pDevCfg->irqGroupMB64_95.idxTargetCore < RTOS_NO_CORES
              );

        /* The INTC priority of any IRQ needs to be in range. */
        ASSERT( pDevCfg->irqGroupFIFO.irqPrio <= 15
                &&  pDevCfg->irqGroupError.irqPrio <= 15
                &&  pDevCfg->irqGroupBusOff.irqPrio <= 15
                &&  pDevCfg->irqGroupMB0_3.irqPrio <= 15
                &&  pDevCfg->irqGroupMB4_7.irqPrio <= 15
                &&  pDevCfg->irqGroupMB8_11.irqPrio <= 15
                &&  pDevCfg->irqGroupMB12_15.irqPrio <= 15
                &&  pDevCfg->irqGroupMB16_31.irqPrio <= 15
                &&  pDevCfg->irqGroupMB32_63.irqPrio <= 15
                &&  pDevCfg->irqGroupMB64_95.irqPrio <= 15
              );

        /* Error interrupts: We have some simple internal handling and the notification in
           just an option. However, there's no Tx notification and the optional
           notification must not be configured if the interrupt is configured off. */
        ASSERT(!(pDevCfg->irqGroupError.irqPrio == 0
                 &&  pDevCfg->irqGroupError.osCallbackOnError != NULL
                )
               &&  pDevCfg->irqGroupError.osCallbackOnTx == NULL
              );

        /* Bus off interrupts: Same considerations as for error interrupts. */
        ASSERT(!(pDevCfg->irqGroupBusOff.irqPrio == 0
                 &&  pDevCfg->irqGroupBusOff.osCallbackOnBusOff != NULL
                )
               &&  pDevCfg->irqGroupBusOff.osCallbackOnTx == NULL
              );

        /* If we have a FIFO then we need to have an enabled IRQ, too. And the opposite. */
        ASSERT(!pDevCfg->isFIFOEnabled  &&  pDevCfg->irqGroupFIFO.irqPrio == 0
               ||  pDevCfg->isFIFOEnabled  &&  pDevCfg->irqGroupFIFO.irqPrio > 0
              );
        
        /* If we have a FIFO then we need to have an Rx callback, too. The Tx callback is
           not defined for the FIFO group. */
        ASSERT(!pDevCfg->isFIFOEnabled  &&  pDevCfg->irqGroupFIFO.osCallbackOnRx == NULL
               ||  pDevCfg->isFIFOEnabled  &&  pDevCfg->irqGroupFIFO.osCallbackOnRx != NULL
              );
        ASSERT(pDevCfg->irqGroupFIFO.osCallbackOnTx == NULL);
        
        /* If we have a mailbox IRQ enabled then we need to have a callback, too. */
        #define ASSERT_IRQ_HAS_CB(group)                                                    \
            ASSERT(pDevCfg->irqGroup##group.irqPrio > 0                                     \
                   &&  (pDevCfg->irqGroup##group.osCallbackOnRx != NULL                     \
                        ||  pDevCfg->irqGroup##group.osCallbackOnTx != NULL                 \
                       )                                                                    \
                   ||  pDevCfg->irqGroup##group.irqPrio == 0                                \
                       &&  (pDevCfg->irqGroup##group.osCallbackOnRx == NULL                 \
                            &&  pDevCfg->irqGroup##group.osCallbackOnTx == NULL             \
                           )                                                                \
                  );
        ASSERT_IRQ_HAS_CB(FIFO)
        ASSERT_IRQ_HAS_CB(MB0_3)
        ASSERT_IRQ_HAS_CB(MB4_7)
        ASSERT_IRQ_HAS_CB(MB8_11)
        ASSERT_IRQ_HAS_CB(MB12_15)
        ASSERT_IRQ_HAS_CB(MB16_31)
        ASSERT_IRQ_HAS_CB(MB32_63)
        ASSERT_IRQ_HAS_CB(MB64_95)
        #undef ASSERT_IRQ_HAS_CB
        
    } /* End for(All enabled CAN devices) */

    return true;

} /* End of cdr_checkDriverConfiguration */




