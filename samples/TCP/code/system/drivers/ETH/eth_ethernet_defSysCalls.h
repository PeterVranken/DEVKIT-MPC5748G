#ifndef ETH_ETHERNET_DEFSYSCALLS_INCLUDED
#define ETH_ETHERNET_DEFSYSCALLS_INCLUDED
/**
 * @file eth_ethernet_defSysCalls.h
 * Declaration of system calls offered by and implemented in module eth_ethernet.c. This
 * header file has to be included by source file rtos_systemCall.c, which collects all system
 * call declarations and assembles the const table of system call descriptors.
 *
 * Copyright (C) 2019-2023 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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

#include "rtos.h"
#include "eth_ethernet.h"


/*
 * Defines
 */


#if !defined(RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0045)    \
    && !defined(RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0045) \
    && !defined(RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0045)
    
# if ETH_SYSCALL_SET_MULTICAST_FORWARD != 45
#  error Inconsistent definition of system call
# endif

/* The system call must be used only from the very core, which runs the Ethernet driver. */
# define RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0045 \
                            RTOS_SC_TABLE_ENTRY(eth_scSmplHdlr_setMulticastForward, SIMPLE)
# define RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0045   RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# define RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0045   RTOS_SYSCALL_DUMMY_TABLE_ENTRY

#else
# error System call 0045 is ambiguously defined

/* We purposely redefine the table entry and despite of the already reported error; this
   makes the compiler emit a message with the location of the conflicting previous
   definition.*/
# define RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0045   RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# define RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0045   RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# define RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0045   RTOS_SYSCALL_DUMMY_TABLE_ENTRY
#endif


#if !defined(RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0046)    \
    && !defined(RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0046) \
    && !defined(RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0046)
    
# if ETH_SYSCALL_PROVIDE_RX_BUFF != 46
#  error Inconsistent definition of system call
# endif

/* The system call is only available only on the very core, which serves the serial input
   interrupts. The others will be redirected to the illegal system call exception. */
# define RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0046 \
                        RTOS_SC_TABLE_ENTRY(eth_scSmplHdlr_releaseRxFramePayloadBuffer, SIMPLE)
# define RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0046 RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# define RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0046 RTOS_SYSCALL_DUMMY_TABLE_ENTRY

#else
# error System call 0046 is ambiguously defined

/* We purposely redefine the table entry and despite of the already reported error; this
   makes the compiler emit a message with the location of the conflicting previous
   definition.*/
# define RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0046   RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# define RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0046   RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# define RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0046   RTOS_SYSCALL_DUMMY_TABLE_ENTRY
#endif


#if !defined(RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0047)    \
    && !defined(RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0047) \
    && !defined(RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0047)
    
# if ETH_SYSCALL_READ_FRAME != 47
#  error Inconsistent definition of system call
# endif

/* The system call is only available only on the very core, which serves the serial input
   interrupts. The others will be redirected to the illegal system call exception. */
# define RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0047 \
                            RTOS_SC_TABLE_ENTRY(eth_scSmplHdlr_readFrame, SIMPLE)
# define RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0047 RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# define RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0047 RTOS_SYSCALL_DUMMY_TABLE_ENTRY

#else
# error System call 0047 is ambiguously defined

/* We purposely redefine the table entry and despite of the already reported error; this
   makes the compiler emit a message with the location of the conflicting previous
   definition.*/
# define RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0047   RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# define RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0047   RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# define RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0047   RTOS_SYSCALL_DUMMY_TABLE_ENTRY
#endif


#if !defined(RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0048)    \
    && !defined(RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0048) \
    && !defined(RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0048)
    
# if ETH_SYSCALL_SEND_FRAME != 48
#  error Inconsistent definition of system call
# endif

/* The system call is only available only on the very core, which serves the serial input
   interrupts. The others will be redirected to the illegal system call exception. */
# define RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0048 \
                            RTOS_SC_TABLE_ENTRY(eth_scSmplHdlr_sendFrame, SIMPLE)
# define RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0048 RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# define RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0048 RTOS_SYSCALL_DUMMY_TABLE_ENTRY

#else
# error System call 0048 is ambiguously defined

/* We purposely redefine the table entry and despite of the already reported error; this
   makes the compiler emit a message with the location of the conflicting previous
   definition.*/
# define RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0048   RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# define RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0048   RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# define RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0048   RTOS_SYSCALL_DUMMY_TABLE_ENTRY
#endif


#if !defined(RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0049)    \
    && !defined(RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0049) \
    && !defined(RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0049)
    
# if ETH_SYSCALL_IS_TRANSMISSION_COMPLETED != 49
#  error Inconsistent definition of system call
# endif

/* The system call is only available only on the very core, which serves the serial input
   interrupts. The others will be redirected to the illegal system call exception. */
# define RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0049 \
                            RTOS_SC_TABLE_ENTRY(eth_scSmplHdlr_isTransmissionCompleted, SIMPLE)
# define RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0049 RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# define RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0049 RTOS_SYSCALL_DUMMY_TABLE_ENTRY

#else
# error System call 0049 is ambiguously defined

/* We purposely redefine the table entry and despite of the already reported error; this
   makes the compiler emit a message with the location of the conflicting previous
   definition.*/
# define RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0049   RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# define RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0049   RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# define RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0049   RTOS_SYSCALL_DUMMY_TABLE_ENTRY
#endif


/*
 * Global type definitions
 */


/*
 * Global data declarations
 */


/*
 * Global prototypes
 */

/* System call of Ethernet driver function ENET_DRV_SetMulticastForward(). */
void eth_scSmplHdlr_setMulticastForward( uint32_t pidOfCallingTask
                                       , unsigned int idxEthDev
                                       , const uint8_t macAddr[6]
                                       , bool enable
                                       );

/* System call of Ethernet driver function ENET_DRV_ProvideRxBuff(). */
void eth_scSmplHdlr_releaseRxFramePayloadBuffer( uint32_t pidOfCallingTask
                                               , unsigned int idxEthDev
                                               , unsigned int idxRing
                                               , void *pBufferMem
                                               );

/* System call of Ethernet driver function ENET_DRV_ReadFrame(). */
const struct eth_bufferDesc_t *eth_scSmplHdlr_readFrame( uint32_t pidOfCallingTask
                                                       , unsigned int idxEthDev
                                                       , unsigned int idxRing
                                                       );

/* System call of Ethernet driver function ENET_DRV_SendFrame(). */
uintptr_t eth_scSmplHdlr_sendFrame( uint32_t pidOfCallingTask
                                  , unsigned int idxEthDev
                                  , unsigned int idxRing
                                  , const void * const payloadData
                                  , unsigned int sizeOfPayloadData
                                  );

/* System call of Ethernet driver function ENET_DRV_GetTransmitStatus(). */
bool eth_scSmplHdlr_isTransmissionCompleted(uint32_t pidOfCallingTask, uintptr_t hTxFrame);

/*
 * Global inline functions
 */


#endif  /* ETH_ETHERNET_DEFSYSCALLS_INCLUDED */
