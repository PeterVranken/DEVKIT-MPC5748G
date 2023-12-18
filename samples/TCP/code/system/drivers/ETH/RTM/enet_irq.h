#ifndef ENET_IRQ_INCLUDED
#define ENET_IRQ_INCLUDED
/**
 * @file enet_irq.h
 * Definition of global interface of module enet_irq.c
 *
 * Copyright (C) 2023 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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

#include "rcf_rtmConfig.h"
#include "device_registers.h"


/*
 * Defines
 */


/*
 * Global type definitions
 */


/*
 * Global data declarations
 */


/*
 * Global prototypes
 */

#if (defined(MPC577x_SERIES) || defined(CPU_MPC5746R) || defined(CPU_MPC5745R) || defined(CPU_MPC5743R))

/*******************************************************************************
 * Default interrupt handlers signatures
 ******************************************************************************/
#if (ENET_INSTANCE_COUNT > 0U)
void FEC_TXF_IRQHandler(void);
void FEC_RXF_IRQHandler(void);
void FEC_ERR_IRQHandler(void);
#endif /* (ENET_INSTANCE_COUNT > 0U) */

#elif (defined(MPC574x_SERIES) || defined(S32R_SERIES))

/*******************************************************************************
 * Default interrupt handlers signatures
 ******************************************************************************/
#if (ENET_INSTANCE_COUNT > 0U)
void ENET0_Tx_IRQHandler(void);
void ENET0_Rx_IRQHandler(void);
void ENET0_Group0_IRQHandler(void);
void ENET0_Timer_IRQHandler(void);
#if (FEATURE_ENET_RING_COUNT > 1U)
void ENET0_Tx_1_IRQHandler(void);
void ENET0_Rx_1_IRQHandler(void);
#endif /* (FEATURE_ENET_RING_COUNT > 1U) */
#if (FEATURE_ENET_RING_COUNT > 2U)
void ENET0_Tx_2_IRQHandler(void);
void ENET0_Rx_2_IRQHandler(void);
#endif /* (FEATURE_ENET_RING_COUNT > 2U) */
#if FEATURE_ENET_HAS_RECEIVE_PARSER
void ENET0_Parser_IRQHandler(void);
#endif /* FEATURE_ENET_HAS_RECEIVE_PARSER */
#endif /* (ENET_INSTANCE_COUNT > 0U) */

#if (ENET_INSTANCE_COUNT > 1U)
void ENET1_Tx_IRQHandler(void);
void ENET1_Rx_IRQHandler(void);
void ENET1_Group0_IRQHandler(void);
void ENET1_Timer_IRQHandler(void);
#if (FEATURE_ENET_RING_COUNT > 1U)
void ENET1_Tx_1_IRQHandler(void);
void ENET1_Rx_1_IRQHandler(void);
#endif /* (FEATURE_ENET_RING_COUNT > 1U) */
#if (FEATURE_ENET_RING_COUNT > 2U)
void ENET1_Tx_2_IRQHandler(void);
void ENET1_Rx_2_IRQHandler(void);
#endif /* (FEATURE_ENET_RING_COUNT > 2U) */
#if FEATURE_ENET_HAS_RECEIVE_PARSER
void ENET1_Parser_IRQHandler(void);
#endif /* FEATURE_ENET_HAS_RECEIVE_PARSER */
#endif /* (ENET_INSTANCE_COUNT > 1U) */

#elif (defined(CPU_S32K148) || defined(CPU_SJA1110))

/*******************************************************************************
 * Default interrupt handlers signatures
 ******************************************************************************/
#if (ENET_INSTANCE_COUNT > 0U)
void ENET_TX_IRQHandler(void);
void ENET_RX_IRQHandler(void);
void ENET_ERR_IRQHandler(void);
void ENET_WAKE_IRQHandler(void);
void ENET_TIMER_IRQHandler(void);
#endif /* (ENET_INSTANCE_COUNT > 0U) */

#elif (defined(S32V23x_SERIES))

/*******************************************************************************
 * Default interrupt handlers signatures
 ******************************************************************************/
#if (ENET_INSTANCE_COUNT > 0U)
void ENET_TX_IRQHandler(void);
void ENET_RX_IRQHandler(void);
void ENET_Err_IRQHandler(void);
void ENET_Timer_IRQHandler(void);
#endif /* (ENET_INSTANCE_COUNT > 0U) */

#else
    #error "No valid CPU defined!"
#endif


/*
 * Global inline functions
 */


#endif  /* ENET_IRQ_INCLUDED */
