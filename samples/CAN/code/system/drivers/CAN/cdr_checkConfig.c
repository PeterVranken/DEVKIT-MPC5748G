/**
 * @file cdr_checkConfig.c
 * This module offers a function to run some plausibility checks on the driver cofiguration
 * data set. It doesn't contain functional code. In case a bad configuration item is found,
 * the function returns an error code in PRODUCTION compilation and it halts the SW
 * execution by assertion in DEBUG compilation.\n
 *   Since the configuration data set is constant and the function solely checks facts that
 * are decided at compile-time, the recommendation is to call the check function only from
 * the DEBUG compilation.
 *
 * Copyright (C) 2020-2021 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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
#include <string.h>
#include <assert.h>

#include "typ_types.h"
#include "rtos.h"
#include "cdr_canDriverAPI.h"
#include "cdr_canDriver.config.inc"
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
#if defined (MCU_MPC5775B)  ||  defined (MCU_MPC5775E)
_Static_assert( CDR_ENABLE_USE_OF_CAN_4 == 0  &&  CDR_ENABLE_USE_OF_CAN_5 == 0
                &&  CDR_ENABLE_USE_OF_CAN_6 == 0  &&  CDR_ENABLE_USE_OF_CAN_7 == 0
              , "MPC5775B/E: Only four CAN devices are available but more have been configured"
              );
#endif
_Static_assert( CAN_RXIMR_COUNT == CDR_NO_HW_MAILBOXES_PER_CAN_DEVICE
              , "Inconsistent macro setting for available number of mailboxes"
              );
_Static_assert( !CDR_ENABLE_MCU_PINS_FOR_EVAL_BOARD ||  CDR_ENABLE_USE_OF_CAN_0 == 1
              , "MCU pin enabling and routing is only possible for CAN device 0"
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
    
    /* A buffer for checking consistent specification of API buffer indexes. */
    unsigned int noUserEnabledRxMBs = 0;
    uint8_t isAPIBufferInUse[CDR_NO_RX_USER_CODE_POLLING_MAILBOXES];
    memset(isAPIBufferInUse, 0, sizeof(isAPIBufferInUse));

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

        /* The number of mailboxes is hardware limited. */
        ASSERT(pDevCfg->noMailboxes <= CDR_NO_HW_MAILBOXES_PER_CAN_DEVICE);
        
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
           not available with FIFO enabled. idxFirstNormalMailbox can have the values 0, 8,
           10, 12, .., 38. */
        const unsigned int idxFirstNormalMailbox = cdr_getIdxOfFirstNormalMailbox(pDevCfg);
        ASSERT(idxFirstNormalMailbox <= 0
#if defined(MCU_MPC5748G)
               ||  pDevCfg->irqGroupMB0_3.irqPrio == 0
                   &&  pDevCfg->irqGroupMB4_7.irqPrio == 0
#else /* MPC5775B/E */
               ||  pDevCfg->irqMB0.irqPrio == 0
                   &&  pDevCfg->irqMB1.irqPrio == 0
                   &&  pDevCfg->irqMB2.irqPrio == 0
                   &&  pDevCfg->irqMB3.irqPrio == 0
                   &&  pDevCfg->irqMB4.irqPrio == 0
                   &&  pDevCfg->irqMB5.irqPrio == 0
                   &&  pDevCfg->irqMB6.irqPrio == 0
                   &&  pDevCfg->irqMB7.irqPrio == 0
#endif
              );
#if defined(MCU_MPC5775B) ||  defined(MCU_MPC5775E)
        ASSERT(idxFirstNormalMailbox <= 8
               ||  pDevCfg->irqMB8.irqPrio == 0
                   &&  pDevCfg->irqMB9.irqPrio == 0
              );
#endif
        ASSERT(idxFirstNormalMailbox <= 10
#if defined(MCU_MPC5748G)
               ||  pDevCfg->irqGroupMB8_11.irqPrio == 0
#else /* MPC5775B/E */
               ||  pDevCfg->irqMB10.irqPrio == 0
                   &&  pDevCfg->irqMB11.irqPrio == 0
#endif
              );
#if defined(MCU_MPC5775B) ||  defined(MCU_MPC5775E)
        ASSERT(idxFirstNormalMailbox <= 12
               ||  pDevCfg->irqMB12.irqPrio == 0
                   &&  pDevCfg->irqMB13.irqPrio == 0
              );
#endif
        ASSERT(idxFirstNormalMailbox <= 14
#if defined(MCU_MPC5748G)
               ||  pDevCfg->irqGroupMB12_15.irqPrio == 0
#else /* MPC5775B/E */
               ||  pDevCfg->irqMB14.irqPrio == 0
                   &&  pDevCfg->irqMB15.irqPrio == 0
#endif
              );
        ASSERT(idxFirstNormalMailbox <= 30  ||  pDevCfg->irqGroupMB16_31.irqPrio == 0);
        ASSERT(idxFirstNormalMailbox <= 38);

        /* The target core for any IRQ needs to be in range. */
        ASSERT( pDevCfg->irqGroupFIFO.idxTargetCore < RTOS_NO_CORES
                &&  pDevCfg->irqGroupError.idxTargetCore < RTOS_NO_CORES
                &&  pDevCfg->irqGroupBusOff.idxTargetCore < RTOS_NO_CORES
#if defined(MCU_MPC5748G)
                &&  pDevCfg->irqGroupMB0_3.idxTargetCore < RTOS_NO_CORES
                &&  pDevCfg->irqGroupMB4_7.idxTargetCore < RTOS_NO_CORES
                &&  pDevCfg->irqGroupMB8_11.idxTargetCore < RTOS_NO_CORES
                &&  pDevCfg->irqGroupMB12_15.idxTargetCore < RTOS_NO_CORES
#else /* MPC5775B/E */
                &&  pDevCfg->irqMB0.idxTargetCore < RTOS_NO_CORES
                &&  pDevCfg->irqMB1.idxTargetCore < RTOS_NO_CORES
                &&  pDevCfg->irqMB2.idxTargetCore < RTOS_NO_CORES
                &&  pDevCfg->irqMB3.idxTargetCore < RTOS_NO_CORES
                &&  pDevCfg->irqMB4.idxTargetCore < RTOS_NO_CORES
                &&  pDevCfg->irqMB5.idxTargetCore < RTOS_NO_CORES
                &&  pDevCfg->irqMB6.idxTargetCore < RTOS_NO_CORES
                &&  pDevCfg->irqMB7.idxTargetCore < RTOS_NO_CORES
                &&  pDevCfg->irqMB8.idxTargetCore < RTOS_NO_CORES
                &&  pDevCfg->irqMB9.idxTargetCore < RTOS_NO_CORES
                &&  pDevCfg->irqMB10.idxTargetCore < RTOS_NO_CORES
                &&  pDevCfg->irqMB11.idxTargetCore < RTOS_NO_CORES
                &&  pDevCfg->irqMB12.idxTargetCore < RTOS_NO_CORES
                &&  pDevCfg->irqMB13.idxTargetCore < RTOS_NO_CORES
                &&  pDevCfg->irqMB14.idxTargetCore < RTOS_NO_CORES
                &&  pDevCfg->irqMB15.idxTargetCore < RTOS_NO_CORES
#endif
                &&  pDevCfg->irqGroupMB16_31.idxTargetCore < RTOS_NO_CORES
                &&  pDevCfg->irqGroupMB32_63.idxTargetCore < RTOS_NO_CORES
#if defined(MCU_MPC5748G)
                &&  pDevCfg->irqGroupMB64_95.idxTargetCore < RTOS_NO_CORES
#endif
              );

        /* The INTC priority of any IRQ needs to be in range. */
        ASSERT( pDevCfg->irqGroupFIFO.irqPrio <= 15
                &&  pDevCfg->irqGroupError.irqPrio <= 15
                &&  pDevCfg->irqGroupBusOff.irqPrio <= 15
#if defined(MCU_MPC5748G)
                &&  pDevCfg->irqGroupMB0_3.irqPrio <= 15
                &&  pDevCfg->irqGroupMB4_7.irqPrio <= 15
                &&  pDevCfg->irqGroupMB8_11.irqPrio <= 15
                &&  pDevCfg->irqGroupMB12_15.irqPrio <= 15
#else /* MPC5775B/E */
                &&  pDevCfg->irqMB0.irqPrio <= 15
                &&  pDevCfg->irqMB1.irqPrio <= 15
                &&  pDevCfg->irqMB2.irqPrio <= 15
                &&  pDevCfg->irqMB3.irqPrio <= 15
                &&  pDevCfg->irqMB4.irqPrio <= 15
                &&  pDevCfg->irqMB5.irqPrio <= 15
                &&  pDevCfg->irqMB6.irqPrio <= 15
                &&  pDevCfg->irqMB7.irqPrio <= 15
                &&  pDevCfg->irqMB8.irqPrio <= 15
                &&  pDevCfg->irqMB9.irqPrio <= 15
                &&  pDevCfg->irqMB10.irqPrio <= 15
                &&  pDevCfg->irqMB11.irqPrio <= 15
                &&  pDevCfg->irqMB12.irqPrio <= 15
                &&  pDevCfg->irqMB13.irqPrio <= 15
                &&  pDevCfg->irqMB14.irqPrio <= 15
                &&  pDevCfg->irqMB15.irqPrio <= 15
#endif
                &&  pDevCfg->irqGroupMB16_31.irqPrio <= 15
                &&  pDevCfg->irqGroupMB32_63.irqPrio <= 15
#if defined(MCU_MPC5748G)
                &&  pDevCfg->irqGroupMB64_95.irqPrio <= 15
#endif
              );

        /* Error interrupts: We have some simple internal handling and the notification is
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
            ASSERT(pDevCfg->irq##group.irqPrio > 0                                          \
                   &&  (pDevCfg->irq##group.osCallbackOnRx != NULL                          \
                        ||  pDevCfg->irq##group.osCallbackOnTx != NULL                      \
                       )                                                                    \
                   ||  pDevCfg->irq##group.irqPrio == 0                                     \
                       &&  (pDevCfg->irq##group.osCallbackOnRx == NULL                      \
                            &&  pDevCfg->irq##group.osCallbackOnTx == NULL                  \
                           )                                                                \
                  );
        ASSERT_IRQ_HAS_CB(GroupFIFO)
#if defined(MCU_MPC5748G)
        ASSERT_IRQ_HAS_CB(GroupMB0_3)
        ASSERT_IRQ_HAS_CB(GroupMB4_7)
        ASSERT_IRQ_HAS_CB(GroupMB8_11)
        ASSERT_IRQ_HAS_CB(GroupMB12_15)
#else /* MPC5775B/E */
        ASSERT_IRQ_HAS_CB(MB0)
        ASSERT_IRQ_HAS_CB(MB1)
        ASSERT_IRQ_HAS_CB(MB2)
        ASSERT_IRQ_HAS_CB(MB3)
        ASSERT_IRQ_HAS_CB(MB4)
        ASSERT_IRQ_HAS_CB(MB5)
        ASSERT_IRQ_HAS_CB(MB6)
        ASSERT_IRQ_HAS_CB(MB7)
        ASSERT_IRQ_HAS_CB(MB8)
        ASSERT_IRQ_HAS_CB(MB9)
        ASSERT_IRQ_HAS_CB(MB10)
        ASSERT_IRQ_HAS_CB(MB11)
        ASSERT_IRQ_HAS_CB(MB12)
        ASSERT_IRQ_HAS_CB(MB13)
        ASSERT_IRQ_HAS_CB(MB14)
        ASSERT_IRQ_HAS_CB(MB15)
#endif
        ASSERT_IRQ_HAS_CB(GroupMB16_31)
        ASSERT_IRQ_HAS_CB(GroupMB32_63)
#if defined(MCU_MPC5748G)
        ASSERT_IRQ_HAS_CB(GroupMB64_95)
#endif
        #undef ASSERT_IRQ_HAS_CB
        
        /* Check the configuration of privileges for the user code API. */
        unsigned int idxMB;
        for(idxMB=0; idxMB<CDR_NO_HW_MAILBOXES_PER_CAN_DEVICE; ++idxMB)
        {
            const struct cdr_mailboxAccessConfig_t configMB =
                                                pDevCfg->userAccessMailboxAry[idxMB];

            /* We don't want to see polling enabled mailboxes out of range or with mailbox
               indexes, which point into the FIFO memory area. */
            ASSERT(idxMB >= idxFirstNormalMailbox  &&  idxMB < pDevCfg->noMailboxes
                   ||  configMB.minPIDToAccess == 0 &&  configMB.idxAPIBuffer == 0
                       &&  !configMB.useAsRxMailbox
                  );

#if CDR_NO_RX_USER_CODE_POLLING_MAILBOXES > 0
            /* If polling is enabled then a unique, in-range index of an API buffer needs
               to be specified. */
            if(configMB.minPIDToAccess > 0  && configMB.useAsRxMailbox)
            {
                /* The mailbox is intended for Rx use and requires an API buffer. */
                ++ noUserEnabledRxMBs;

                /* The specified index of the API buffer is in range. */
                ASSERT(configMB.idxAPIBuffer < CDR_NO_RX_USER_CODE_POLLING_MAILBOXES);

                /* The API buffer index has not be specified yet for an ealier visited
                   mailbox. */
                assert(sizeOfAry(isAPIBufferInUse) == CDR_NO_RX_USER_CODE_POLLING_MAILBOXES);
                ASSERT(isAPIBufferInUse[configMB.idxAPIBuffer] == 0);
                isAPIBufferInUse[configMB.idxAPIBuffer] = 1;
            }
            else
            {
                /* The mailbox is intended for user code Tx access or not at all for user
                   access. It doesn't have an associated API buffer. */
                ASSERT(configMB.idxAPIBuffer == 0);
            }
#else
            /* No Rx operation possible at all if no API buffers are declared. */
            ASSERT(configMB.idxAPIBuffer == 0  &&  !configMB.useAsRxMailbox);
#endif
        }
    } /* End for(All enabled CAN devices) */

    /* All requested API buffers for user-code enabled mailboxes should really be in use to
       avoid a waste of memory. */
    ASSERT(noUserEnabledRxMBs == CDR_NO_RX_USER_CODE_POLLING_MAILBOXES);
    
    return true;

    #undef NO_HW_MAILBOXES_PER_CAN_DEVICE
} /* End of cdr_checkDriverConfiguration */




