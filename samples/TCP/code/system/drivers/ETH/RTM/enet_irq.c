/*
 * Copyright 2017 NXP
 * All rights reserved.
 *
 * THIS SOFTWARE IS PROVIDED BY NXP "AS IS" AND ANY EXPRESSED OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL NXP OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */
 
 /*!
 * @file enet_irq.c
 *
 * @page misra_violations MISRA-C:2012 violations
 *
 * @section [global]
 * Violates MISRA 2012 Advisory Rule 8.7, external could be made static.
 * The functions are called by the interrupt controller when the appropriate event
 * occurs.
 *
 */

#include "enet_irq.h"
#include "enet_hw_access.h"

#if (defined(MPC577x_SERIES) || defined(CPU_MPC5746R) || defined(CPU_MPC5745R) || defined(CPU_MPC5743R))

/*******************************************************************************
 * Default interrupt handlers signatures
 ******************************************************************************/
#if (ENET_INSTANCE_COUNT > 0U)
void FEC_TXF_IRQHandler(void);
void FEC_RXF_IRQHandler(void);
void FEC_ERR_IRQHandler(void);
#endif /* (ENET_INSTANCE_COUNT > 0U) */

/*******************************************************************************
 * Code
 ******************************************************************************/
 
#if (ENET_INSTANCE_COUNT > 0U)

/* Implementation of FEC0 IRQ handler for transmit interrupts. */
void FEC_TXF_IRQHandler(void)
{
    ENET_TransmitIRQHandler(0);
}

/* Implementation of FEC0 IRQ handler for receive interrupts. */
void FEC_RXF_IRQHandler(void)
{
    ENET_ReceiveIRQHandler(0);
}

/* Implementation of FEC0 IRQ handler for error interrupts. */
void FEC_ERR_IRQHandler(void)
{
    ENET_ErrorIRQHandler(0);
}

#endif /* (ENET_INSTANCE_COUNT > 0U) */

#elif (defined(MPC574x_SERIES) || defined(S32R_SERIES))

/*******************************************************************************
 * Default interrupt handlers signatures
 ******************************************************************************/
#if (ENET_INSTANCE_COUNT > 0U)
void ENET0_Tx_IRQHandler(void);
void ENET0_Rx_IRQHandler(void);
void ENET0_Err_IRQHandler(void);
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
void ENET1_Err_IRQHandler(void);
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

/*******************************************************************************
 * Code
 ******************************************************************************/

#if FEATURE_ENET_HAS_SLEEP_WAKEUP
/*FUNCTION**********************************************************************
 *
 * Function Name : ENET_WakeIRQHandler
 * Description   : Handler for ENET wakeup interrupts. This an IRQ from Group 0, interrupt
 * mask bits #ENET_WAKEUP_INTERRUPT (aka #ENET_EIR_WAKEUP_MASK).
 * This handler invokes the configured callback, and clears the interrupt flags. Also, the
 * ENET module is set to normal operation mode.
 *
 *END**************************************************************************/
static inline void ENET_WakeIRQHandler(uint8_t instance)
{
    ENET_Type *base = s_enetBases[instance];

    if (((uint32_t)ENET_WAKEUP_INTERRUPT & base->EIR) != 0U)
    {
        ENET_DRV_SetSleepMode(instance, false);
        
        /* Callback function. */
        DEV_ASSERT(g_enetState[instance]->isrWakeup != NULL);
        g_enetState[instance]->isrWakeup();
        
        /* Clear the wakeup interrupt event. */
        base->EIR = (uint32_t)ENET_WAKEUP_INTERRUPT;
    }
}
#endif /* FEATURE_ENET_HAS_SLEEP_WAKEUP */


/*FUNCTION**********************************************************************
 *
 * Function Name : ENET_ErrorIRQHandler
 * Description : Handler for ENET error interrupts. This an IRQ from Group 0, interrupt
 * mask bits #ENET_PAYLOAD_RX_INTERRUPT, #ENET_RETRY_LIMIT_INTERRUPT and several others.
 * (All those from Group 0, which relate to an error situation.) See RM48, 42.5.1,
 * pp.1535ff, for a description of all IRQ mask bits and RM48, 42.1.1, Tables 42-1f,
 * pp.1516f for an overview which of these belong to IRQ group 0.
 * This handler invokes the configured callback, and clears the interrupt flags.
 *
 *END**************************************************************************/
static inline void ENET_ErrorIRQHandler(uint8_t instance)
{
    ENET_Type *base = s_enetBases[instance];

    const uint32_t errMask = (uint32_t)ENET_BABR_INTERRUPT
                             | (uint32_t)ENET_BABT_INTERRUPT 
                             | (uint32_t)ENET_EBERR_INTERRUPT 
                             | (uint32_t)ENET_PAYLOAD_RX_INTERRUPT 
                             | (uint32_t)ENET_LATE_COLLISION_INTERRUPT 
                             | (uint32_t)ENET_RETRY_LIMIT_INTERRUPT 
                             | (uint32_t)ENET_UNDERRUN_INTERRUPT;
    const uint32_t maskedEIR = errMask & base->EIR;
    if(maskedEIR != 0U)
    {
        /* Callback function. */
        DEV_ASSERT(g_enetState[instance]->isrErr != NULL);
        g_enetState[instance]->isrErr(maskedEIR);
        
        /* Clear the error interrupt event. */
        base->EIR = maskedEIR;
    }
} /* ENET_ErrorIRQHandler */


#if FEATURE_ENET_HAS_ADJUSTABLE_TIMER
/*FUNCTION**********************************************************************
 *
 * Function Name : ENET_TimerIRQHandler
 * Description   : Handler for ENET timer interrupts. This an IRQ from Group 0, interrupt
 * mask bit #ENET_EIR_TS_TIMER_MASK.
 * This handler invokes the configured callback, and clears the interrupt flags.
 *
 *END**************************************************************************/
static inline void ENET_TimerIRQHandler(uint8_t instance)
{
    ENET_Type *base = s_enetBases[instance];

    if ((base->EIR & ENET_EIR_TS_TIMER_MASK) != 0U)
    {
        /* Callback function. */
        DEV_ASSERT(g_enetState[instance]->isrTimer != NULL);
        g_enetState[instance]->isrTimer();

        /* Clear the timer interrupt event. */
        base->EIR = (uint32_t)ENET_EIR_TS_TIMER_MASK;
    }
}
#endif /* FEATURE_ENET_HAS_ADJUSTABLE_TIMER */


/*FUNCTION**********************************************************************
 *
 * Function Name : ENET_ReceiveIRQHandler
 * Description   : Handler for ENET reception interrupts.
 * This handler invokes the configured callback, and clears the interrupt flags.
 *
 *END**************************************************************************/
static inline void ENET_ReceiveIRQHandler(uint8_t instance)
{
    ENET_Type *base = s_enetBases[instance];

    /* Check if one of the receive interrupts happened. */
    const uint32_t maskedEIR = ((uint32_t)ENET_RX_BUFFER_INTERRUPT
                                | (uint32_t)ENET_RX_FRAME_INTERRUPT
                               )
                               & base->EIR;
    if(maskedEIR != 0U)
    {
        /* Callback function. */
        DEV_ASSERT(g_enetState[instance]->isrRx != NULL);
        g_enetState[instance]->isrRx(maskedEIR);

        /* Clear the receive interrupt event. */
        base->EIR = maskedEIR;
    }
} /* ENET_ReceiveIRQHandler */


/*FUNCTION**********************************************************************
 *
 * Function Name : ENET_TransmitIRQHandler
 * Description   : Handler for ENET transmission interrupts.
 * This handler invokes the configured callback, and clears the interrupt flags.
 *
 *END**************************************************************************/
static inline void ENET_TransmitIRQHandler(uint8_t instance)
{
    ENET_Type *base = s_enetBases[instance];

    /* Check if one of the transmit interrupts happened. */
    const uint32_t maskedEIR = ((uint32_t)ENET_TX_BUFFER_INTERRUPT
                                | (uint32_t)ENET_TX_FRAME_INTERRUPT
                               )
                               & base->EIR;
    if(maskedEIR != 0U)
    {
#warning Check code, for Rx and Tx: Reset of IRQ bit prior to callback may be wrong
        /* Callback function. */
        DEV_ASSERT(g_enetState[instance]->isrTx != NULL);
        g_enetState[instance]->isrTx(maskedEIR);

        /* Clear the transmit interrupt event. */
        base->EIR = maskedEIR;

#ifdef ERRATA_E6358
        if (base->TDAR == 0U)
        {
            const enet_buffer_descriptor_t *bd;
            bool inUse = false;
            bool finished = false;

            bd = g_enetState[instance]->txBdBase[0U];

            /* Go through all buffer descriptors */
            while (!finished)
            {
                /* Check if the buffer descriptor is still in use. */
                if ((bd->control & ENET_BUFFDESCR_TX_READY_MASK) != 0U)
                {
                    inUse = true;
                    break;
                }

                /* This was the last buffer in the ring. */
                if ((bd->control & ENET_BUFFDESCR_TX_WRAP_MASK) != 0U)
                {
                    finished = true;
                }

                bd++;
            }

            if (inUse)
            {
                /* Set TDAR bit, as packets are still waiting for transmission */
                base->TDAR = ENET_TDAR_TDAR_MASK;
            }
        }
#endif /* ERRATA_E6358 */
    }
} /* ENET_TransmitIRQHandler */


#if FEATURE_ENET_HAS_RECEIVE_PARSER
/*FUNCTION**********************************************************************
 *
 * Function Name : ENET_ParserIRQHandler
 * Description   : Handler for ENET receive parser.
 * This handler invokes the configured callback, and clears the interrupt flags.
 *
 *END**************************************************************************/
static inline void ENET_ParserIRQHandler(uint8_t instance)
{
    ENET_Type *base = s_enetBases[instance];

    const uint32_t parserMask = (uint32_t)ENET_PARSERERR_INTERRUPT 
                                | (uint32_t)ENET_PARSRF_INTERRUPT;
    const uint32_t maskedEIR = parserMask & base->EIR;
    if(maskedEIR != 0U)
    {
        /* Callback function. */
        DEV_ASSERT(g_enetState[instance]->isrParser != NULL);
        g_enetState[instance]->isrParser(maskedEIR);
        
        /* Clear the parser interrupt event. */
        base->EIR = maskedEIR;
    }
}
#endif /* FEATURE_ENET_HAS_RECEIVE_PARSER */


#if (FEATURE_ENET_RING_COUNT > 1U)

/*FUNCTION**********************************************************************
 *
 * Function Name : ENET_Receive1IRQHandler
 * Description   : Handler for ENET reception interrupts for ring 1.
 * This handler invokes the configured callback, and clears the interrupt flags.
 *
 *END**************************************************************************/
static inline void ENET_Receive1IRQHandler(uint8_t instance)
{
    ENET_Type *base = s_enetBases[instance];

    /* Check if one of the receive interrupts happened. */
    const uint32_t maskedEIR = ((uint32_t)ENET_RX_BUFFER_1_INTERRUPT
                                | (uint32_t)ENET_RX_FRAME_1_INTERRUPT
                               )
                               & base->EIR;
    if(maskedEIR != 0U)
    {
        /* Callback function. */
        DEV_ASSERT(g_enetState[instance]->isrRxRing1 != NULL);
        g_enetState[instance]->isrRxRing1(maskedEIR);

        /* Clear the receive interrupt event. */
        base->EIR = maskedEIR;
    }
} /* ENET_Receive1IRQHandler */



/*FUNCTION**********************************************************************
 *
 * Function Name : ENET_Transmit1IRQHandler
 * Description   : Handler for ENET transmission interrupts for ring 1.
 * This handler invokes the configured callback, and clears the interrupt flags.
 *
 *END**************************************************************************/
static inline void ENET_Transmit1IRQHandler(uint8_t instance)
{
    ENET_Type *base = s_enetBases[instance];

    /* Check if one of the transmit interrupts happened. */
    const uint32_t maskedEIR = ((uint32_t)ENET_TX_BUFFER_1_INTERRUPT
                                | (uint32_t)ENET_TX_FRAME_1_INTERRUPT
                               )
                               & base->EIR;
    if(maskedEIR != 0U)
    {
        /* Callback function. */
        DEV_ASSERT(g_enetState[instance]->isrTxRing1 != NULL);
        g_enetState[instance]->isrTxRing1(maskedEIR);
        
        /* Clear the transmit interrupt event. */
        base->EIR = maskedEIR;
    }
} /* ENET_Transmit1IRQHandler */

#endif /* (FEATURE_ENET_RING_COUNT > 1U) */


#if (FEATURE_ENET_RING_COUNT > 2U)

/*FUNCTION**********************************************************************
 *
 * Function Name : ENET_Receive2IRQHandler
 * Description   : Handler for ENET reception interrupts for ring 2.
 * This handler invokes the configured callback, and clears the interrupt flags.
 *
 *END**************************************************************************/
static inline void ENET_Receive2IRQHandler(uint8_t instance)
{
    ENET_Type *base = s_enetBases[instance];

    /* Check if one of the receive interrupts happened. */
    const uint32_t maskedEIR = ((uint32_t)ENET_RX_BUFFER_2_INTERRUPT
                                | (uint32_t)ENET_RX_FRAME_2_INTERRUPT
                               )
                               & base->EIR;
    if(maskedEIR != 0U)
    {
        /* Callback function. */
        DEV_ASSERT(g_enetState[instance]->isrRxRing2 != NULL);
        g_enetState[instance]->isrRxRing2(maskedEIR);

        /* Clear the receive interrupt event. */
        base->EIR = maskedEIR;
    }
} /* ENET_Receive2IRQHandler */



/*FUNCTION**********************************************************************
 *
 * Function Name : ENET_Transmit2IRQHandler
 * Description   : Handler for ENET transmission interrupts for ring 2.
 * This handler invokes the configured callback, and clears the interrupt flags.
 *
 *END**************************************************************************/
static inline void ENET_Transmit2IRQHandler(uint8_t instance)
{
    ENET_Type *base = s_enetBases[instance];

    /* Check if one of the transmit interrupts happened. */
    const uint32_t maskedEIR = ((uint32_t)ENET_TX_BUFFER_2_INTERRUPT
                                | (uint32_t)ENET_TX_FRAME_2_INTERRUPT
                               )
                               & base->EIR;
    if(maskedEIR != 0U)
    {
        /* Callback function. */
        DEV_ASSERT(g_enetState[instance]->isrTxRing2 != NULL);
        g_enetState[instance]->isrTxRing2(maskedEIR);

        /* Clear the transmit interrupt event. */
        base->EIR = maskedEIR;
    }
} /* ENET_Transmit2IRQHandler */

#endif /* (FEATURE_ENET_RING_COUNT > 2U) */


#if (ENET_INSTANCE_COUNT > 0U)

/* Implementation of ENET0 IRQ handler for error interrupts. */
void ENET0_Group0_IRQHandler(void)
{
    ENET_WakeIRQHandler(0);
    ENET_ErrorIRQHandler(0);
    ENET_TimerIRQHandler(0);
}

/* Implementation of ENET0 IRQ handler for receive interrupts. */
void ENET0_Rx_IRQHandler(void)
{
    ENET_ReceiveIRQHandler(0);
}

/* Implementation of ENET0 IRQ handler for transmit interrupts. */
void ENET0_Tx_IRQHandler(void)
{
    ENET_TransmitIRQHandler(0);
}

#if FEATURE_ENET_HAS_RECEIVE_PARSER
/* Implementation of ENET0 IRQ handler for the receive parser. */
void ENET0_Parser_IRQHandler(void)
{
    ENET_ParserIRQHandler(0);
}
#endif /* FEATURE_ENET_HAS_RECEIVE_PARSER */

/* Implementation of ENET0 IRQ handler for timer interrupts. */
void ENET0_Timer_IRQHandler(void)
{
    /* TBC: Here, we have a problem. The original NXP code calls function
       ENET_TimerIRQHandler(), which is implemented as an ISR for Group 0, "Periodic Timer
       Overflow", EIR mask bit TS_TIMER = 0x0000.8000. It's unlikely, that it is correct to
       use the same handler for IRQ Group 4. Why should two ISR be triggered by one and the
       same IRQ bit? This makes no sense. Register EIR has 29 mask bits, but RM48, Table
       42-1f, pp.1516f, lists 30 IRQs. It is possible, that Group4 relates not to a bit
       from EIR but to bit ENETx_TCSRn[TF], n=0..3, which would mean that four possible IRQ
       sources would have to be checked and serviced in case by the handler.
         In enet_driver.h, we find:
         typedef void (*enet_timer_callback_t)(uint8_t instance, uint8_t channels);
         The explanation indicates, that this is the intended ISR for IRQs from Group 4.
       Untill clarification, we simply put an assertion. */
    DEV_ASSERT(false);
    //ENET_TimerIRQHandler(0);
}

#if (FEATURE_ENET_RING_COUNT > 1U)

/* Implementation of ENET0 IRQ handler for receive interrupts for ring 1. */
void ENET0_Rx_1_IRQHandler(void)
{
    ENET_Receive1IRQHandler(0);
}

/* Implementation of ENET0 IRQ handler for transmit interrupts for ring 1. */
void ENET0_Tx_1_IRQHandler(void)
{
    ENET_Transmit1IRQHandler(0);
}

#endif /* (FEATURE_ENET_RING_COUNT > 1U) */

#if (FEATURE_ENET_RING_COUNT > 2U)

/* Implementation of ENET0 IRQ handler for receive interrupts for ring 2. */
void ENET0_Rx_2_IRQHandler(void)
{
    ENET_Receive2IRQHandler(0);
}

/* Implementation of ENET0 IRQ handler for transmit interrupts for ring 2. */
void ENET0_Tx_2_IRQHandler(void)
{
    ENET_Transmit2IRQHandler(0);
}

#endif /* (FEATURE_ENET_RING_COUNT > 2U) */

#endif /* (ENET_INSTANCE_COUNT > 0U) */

#if (ENET_INSTANCE_COUNT > 1U)

/* Implementation of ENET1 IRQ handler for error interrupts. */
void ENET1_Group0_IRQHandler(void)
{
    ENET_WakeIRQHandler(1);
    ENET_ErrorIRQHandler(1);
    ENET_TimerIRQHandler(1);
}

/* Implementation of ENET1 IRQ handler for receive interrupts. */
void ENET1_Rx_IRQHandler(void)
{
    ENET_ReceiveIRQHandler(1);
}

/* Implementation of ENET1 IRQ handler for transmit interrupts. */
void ENET1_Tx_IRQHandler(void)
{
    ENET_TransmitIRQHandler(1);
}

#if FEATURE_ENET_HAS_RECEIVE_PARSER

/* Implementation of ENET0 IRQ handler for the receive parser. */
void ENET1_Parser_IRQHandler(void)
{
    ENET_ParserIRQHandler(1);
}

#endif /* FEATURE_ENET_HAS_RECEIVE_PARSER */

/* Implementation of ENET1 IRQ handler for timer interrupts. */
void ENET1_Timer_IRQHandler(void)
{
    /* Code is wrong. See ENET0_Timer_IRQHandler() for details. */
    DEV_ASSERT(false);
    //ENET_TimerIRQHandler(1);
}

#if (FEATURE_ENET_RING_COUNT > 1U)

/* Implementation of ENET1 IRQ handler for receive interrupts for ring 1. */
void ENET1_Rx_1_IRQHandler(void)
{
    ENET_Receive1IRQHandler(1);
}

/* Implementation of ENET1 IRQ handler for transmit interrupts for ring 1. */
void ENET1_Tx_1_IRQHandler(void)
{
    ENET_Transmit1IRQHandler(1);
}

#endif /* (FEATURE_ENET_RING_COUNT > 1U) */

#if (FEATURE_ENET_RING_COUNT > 2U)

/* Implementation of ENET1 IRQ handler for receive interrupts for ring 2. */
void ENET1_Rx_2_IRQHandler(void)
{
    ENET_Receive2IRQHandler(1);
}

/* Implementation of ENET1 IRQ handler for transmit interrupts for ring 2. */
void ENET1_Tx_2_IRQHandler(void)
{
    ENET_Transmit2IRQHandler(1);
}

#endif /* (FEATURE_ENET_RING_COUNT > 2U) */

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

/*******************************************************************************
 * Code
 ******************************************************************************/
 
#if (ENET_INSTANCE_COUNT > 0U)

/* Implementation of ENET0 IRQ handler for transmit interrupts. */
void ENET_TX_IRQHandler(void)
{
    ENET_TransmitIRQHandler(0);
}

/* Implementation of ENET0 IRQ handler for receive interrupts. */
void ENET_RX_IRQHandler(void)
{
    ENET_ReceiveIRQHandler(0);
}

/* Implementation of ENET0 IRQ handler for error interrupts. */
void ENET_ERR_IRQHandler(void)
{
    ENET_ErrorIRQHandler(0);
}

/* Implementation of ENET0 IRQ handler for wakeup interrupts. */
void ENET_WAKE_IRQHandler(void)
{
    ENET_WakeIRQHandler(0);
}

/* Implementation of ENET0 IRQ handler for timer interrupts. */
void ENET_TIMER_IRQHandler(void)
{
    ENET_TimerIRQHandler(0);
}

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

/*******************************************************************************
 * Code
 ******************************************************************************/
 
#if (ENET_INSTANCE_COUNT > 0U)

/* Implementation of ENET0 IRQ handler for transmit interrupts. */
void ENET_TX_IRQHandler(void)
{
    ENET_TransmitIRQHandler(0);
#if (FEATURE_ENET_RING_COUNT > 1U)
	ENET_Transmit1IRQHandler(0);
#endif /* (FEATURE_ENET_RING_COUNT > 1U) */
#if (FEATURE_ENET_RING_COUNT > 2U)
	ENET_Transmit2IRQHandler(0);
#endif /* (FEATURE_ENET_RING_COUNT > 2U) */
}

/* Implementation of ENET0 IRQ handler for receive interrupts. */
void ENET_RX_IRQHandler(void)
{
    ENET_ReceiveIRQHandler(0);
#if (FEATURE_ENET_RING_COUNT > 1U)
    ENET_Receive1IRQHandler(0);
#endif /* (FEATURE_ENET_RING_COUNT > 1U) */
#if (FEATURE_ENET_RING_COUNT > 2U)
    ENET_Receive2IRQHandler(0);
#endif /* (FEATURE_ENET_RING_COUNT > 2U) */
}

/* Implementation of ENET0 IRQ handler for error interrupts. */
void ENET_Err_IRQHandler(void)
{
    ENET_ErrorIRQHandler(0);
	ENET_ParserIRQHandler(0);
	ENET_WakeIRQHandler(0);
}

/* Implementation of ENET0 IRQ handler for timer interrupts. */
void ENET_Timer_IRQHandler(void)
{
    ENET_TimerIRQHandler(0);
}

#endif /* (ENET_INSTANCE_COUNT > 0U) */

#else
    #error "No valid CPU defined!"
#endif

/*******************************************************************************
 * EOF
 ******************************************************************************/
