/*
 * Copyright 2017-2019 NXP
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
 * @file enet_hw_access.c
 *
 * @page misra_violations MISRA-C:2012 violations
 *
 * @section [global]
 * Violates MISRA 2012 Required Rule 11.6, Cast from pointer to unsigned long,
 * cast from unsigned long to pointer and cast from unsigned int to pointer.
 * The cast is required to perform a conversion between a pointer
 * and an unsigned long define, representing an address or vice versa.
 *
 * @section [global]
 * Violates MISRA 2012 Advisory Rule 11.4, Conversion between a pointer and
 * integer type.
 * The cast is required to initialize a pointer with an unsigned long define,
 * representing an address.
 *
 */

#include "enet_hw_access.h"

/*******************************************************************************
 * Variables
 ******************************************************************************/

/* Wrap-around value for timeout */
#define ENET_TIMEOUT_WRAP  0xFFFFFFFFU

/*******************************************************************************
 * Private Functions
 ******************************************************************************/

 /*FUNCTION**********************************************************************
 *
 * Function Name : ENET_Timeout
 * Description   : Checks for timeout condition
 *
 *END**************************************************************************/
static bool ENET_Timeout(uint32_t startTime, uint32_t timeout)
{
    uint32_t currentTime;
    bool retVal;

    currentTime = OSIF_GetMilliseconds();
    if (currentTime >= startTime)
    {
        retVal = ((currentTime - startTime) > timeout) ? true : false;
    }
    else
    {
        /* wrap around */
        retVal = ((ENET_TIMEOUT_WRAP - startTime + currentTime) > timeout) ? true : false;
    }
    return retVal;
}

/*******************************************************************************
 * Code
 ******************************************************************************/

/*FUNCTION**********************************************************************
 *
 * Function Name : ENET_ConfigBufferDescriptors
 * Description   : Configures the receive and transmit buffer descriptors.
 *
 *END**************************************************************************/
void ENET_ConfigBufferDescriptors(ENET_Type * base,
                                  uint8_t ring,
                                  const enet_buffer_config_t *bufferConfig,
                                  uint16_t buffSize)
{
    /* Initializes transmit buffer descriptor rings start address, two start address should be aligned. */
    if (ring == 0U)
    {
        base->ETDSR = (uint32_t)bufferConfig->txRingAligned;
        base->ERDSR = (uint32_t)bufferConfig->rxRingAligned;
        base->EMRBR = buffSize;
    }
}

#if FEATURE_ENET_HAS_RX_CONFIG

/*FUNCTION**********************************************************************
 *
 * Function Name : ENET_ConfigReceiveControl
 * Description   : Configures the receive block.
 *
 *END**************************************************************************/
void ENET_ConfigReceiveControl(ENET_Type *base,
                               const enet_config_t *config)
{
    uint32_t rcr = 0;
    uint32_t tcr = base->TCR;

    /* Configures MAC receive controller with user configure structure. */
    rcr = FEC_RCR_FCE(((config->rxConfig & (uint32_t)ENET_RX_CONFIG_ENABLE_FLOW_CONTROL) != 0UL) ? 1UL : 0UL) |
          FEC_RCR_BC_REJ(((config->rxConfig & (uint32_t)ENET_RX_CONFIG_REJECT_BROADCAST_FRAMES) != 0UL) ? 1UL : 0UL) |
          FEC_RCR_PROM(((config->rxConfig & (uint32_t)ENET_RX_CONFIG_ENABLE_PROMISCUOUS_MODE) != 0UL) ? 1UL : 0UL) |
          FEC_RCR_MII_MODE(1U) |
		  FEC_RCR_RMII_MODE((config->miiMode == ENET_RMII_MODE) ? 1UL : 0UL) |
          FEC_RCR_RMII_10T((config->miiSpeed == ENET_MII_SPEED_10M) ? 1UL : 0UL) |
          FEC_RCR_MAX_FL(config->maxFrameLen);

#if defined(SIU_FECCR_FM)
    /* Declare SIU_Type to configuration for FEC mode */
    SIU_Type * const siuBase = SIU;
    /* Set mode operation for FEC module, write bit FM in the SIU_FECCR register:
     * 1 - MII mode
     * 0 - RMII mode */
    siuBase->FECCR = (siuBase->FECCR & ~SIU_FECCR_FM_MASK) | SIU_FECCR_FM((config->miiMode == ENET_MII_MODE) ? 1UL : 0UL);
#endif

    /* Receive setting for half duplex. */
    if (config->miiDuplex == ENET_MII_HALF_DUPLEX)
    {
        rcr |= FEC_RCR_DRT(1);
    }
    /* Sets internal loopback. */
    if ((config->rxConfig & (uint32_t)ENET_RX_CONFIG_ENABLE_MII_LOOPBACK) != 0U)
    {
        rcr |= FEC_RCR_LOOP(1);
        rcr &= ~FEC_RCR_DRT_MASK;
    }
    base->RCR = rcr;

    /* Configures duplex mode. */
    tcr &= ~FEC_TCR_FDEN_MASK;
    tcr |= FEC_TCR_FDEN(config->miiDuplex);
    base->TCR = tcr;
}

#endif /* FEATURE_ENET_HAS_RX_CONFIG */

/*FUNCTION**********************************************************************
 *
 * Function Name : ENET_WriteManagementConfig
 * Description   : Configures the MII management interface.
 *
 *END**************************************************************************/
void ENET_WriteManagementConfig(ENET_Type * base,
                                              uint32_t miiSpeed,
											  uint32_t holdTime,
											  bool miiPreambleDisabled)
{
	uint32_t config;

	(void)holdTime;

	config = FEC_MSCR_MII_SPEED(miiSpeed) | FEC_MSCR_DIS_PRE(miiPreambleDisabled ? 1UL : 0UL);
	base->MSCR = config;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : ENET_WriteManagementFrame
 * Description   : Writes a MII management frame.
 *
 *END**************************************************************************/
status_t ENET_WriteManagementFrame(ENET_Type * base,
                                   uint8_t phyAddr,
                                   uint8_t phyReg,
                                   enet_mmfr_op_type_t opType,
                                   uint16_t data,
                                   bool clause45,
                                   uint32_t startTime,
                                   uint32_t timeoutMs)
{
    status_t status = STATUS_TIMEOUT;

    base->MMFR = (clause45 ? ENET_MMFR_ST(ENET_MMFR_START_INDICATION_45) : ENET_MMFR_ST(ENET_MMFR_START_INDICATION)) |
                              ENET_MMFR_OP(opType) |
                              ENET_MMFR_PA(phyAddr) |
                              ENET_MMFR_RA(phyReg) |
                              ENET_MMFR_TA(ENET_MMFR_TURN_AROUND) |
                              ENET_MMFR_DATA(data);

    /* Wait for completion */
    do
    {
        if ((ENET_GetInterruptStatus(base) & ENET_EIR_MII_MASK) != 0U)
        {
            status = STATUS_SUCCESS;
            /* Clear the flag */
            ENET_ClearInterruptStatus(base, ENET_EIR_MII_MASK);
            break;
        }
    }
    while (!ENET_Timeout(startTime, timeoutMs));

    return status;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : ENET_ConfigCounters
 * Description   : Enables/Disables the MIB counters
 *
 *END**************************************************************************/
void ENET_ConfigCounters(uint8_t instance,
                         bool enable)
 {
	ENET_Type *base = s_enetBases[instance];
	static const uint32_t s_fecAddrs[] = FEC_BASE_ADDRS;

    if (enable)
    {
    	uint32_t i;
    	uint32_t mibAddr = s_fecAddrs[instance] + FEATURE_ENET_MIB_COUNTERS_OFFSET;
    	volatile uint32_t *counter = (volatile uint32_t *)mibAddr;

    	base->MIBC |= FEC_MIBC_MIB_DIS_MASK;

        /* Clear counters - clear all RAM MIB counters locations */
    	for (i = 0; i < FEATURE_ENET_MIB_COUNTERS_SIZE; i++)
    	{
    		counter[i] = 0;
    	}

    	base->MIBC &= ~FEC_MIBC_MIB_DIS_MASK;
    }
    else
    {
        base->MIBC |= FEC_MIBC_MIB_DIS_MASK;
    }
 }

/*FUNCTION**********************************************************************
 *
 * Function Name : ENET_SetSpeed
 * Description   : Sets the speed of the MII interface
 *
 *END**************************************************************************/
void ENET_SetSpeed(ENET_Type * base,
                             enet_mii_speed_t speed)
{
    base->RCR &= ~FEC_RCR_RMII_10T_MASK;
    base->RCR |= FEC_RCR_RMII_10T(speed);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : ENET_TransmitIRQHandler
 * Description   : Handler for ENET transmission interrupts.
 * This handler invokes the installed callback, if available, and clears the
 * interrupt flags.
 *
 *END**************************************************************************/
void ENET_TransmitIRQHandler(uint8_t instance)
{
    ENET_Type *base = s_enetBases[instance];

    /* Check if the transmit interrupt happen. */
    if ((((uint32_t)ENET_TX_BUFFER_INTERRUPT | (uint32_t)ENET_TX_FRAME_INTERRUPT) & base->EIR) != 0U)
    {
        /* Callback function. */
        if (g_enetState[instance]->callback != NULL)
        {
            g_enetState[instance]->callback(instance, ENET_TX_EVENT, 0U);
        }
        /* Clear the transmit interrupt event. */
        base->EIR = (uint32_t)ENET_TX_FRAME_INTERRUPT | (uint32_t)ENET_TX_BUFFER_INTERRUPT;

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
}

/*FUNCTION**********************************************************************
 *
 * Function Name : ENET_ReceiveIRQHandler
 * Description   : Handler for ENET reception interrupts.
 * This handler extracts the received frame and invokes the installed callback,
 * if available. After the callback completes, the buffers will be marked as
 * empty and the interrupt flags will be cleared.
 *
 *END**************************************************************************/
void ENET_ReceiveIRQHandler(uint8_t instance)
{
    ENET_Type *base = s_enetBases[instance];

    /* Check if the receive interrupt happen. */
    if ((((uint32_t)ENET_RX_BUFFER_INTERRUPT | (uint32_t)ENET_RX_FRAME_INTERRUPT) & base->EIR) != 0U)
    {
        /* Callback function. */
        if (g_enetState[instance]->callback != NULL)
        {
            g_enetState[instance]->callback(instance, ENET_RX_EVENT, 0U);
        }
        /* Clear the receive interrupt event. */
        base->EIR = (uint32_t)ENET_RX_FRAME_INTERRUPT | (uint32_t)ENET_RX_BUFFER_INTERRUPT;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : ENET_ErrorIRQHandler
 * Description   : Handler for ENET error interrupts.
 * This handler invokes the installed callback, if available, and clears the
 * interrupt flags.
 *
 *END**************************************************************************/
void ENET_ErrorIRQHandler(uint8_t instance)
{
    ENET_Type *base = s_enetBases[instance];

    uint32_t errMask = (uint32_t)ENET_BABR_INTERRUPT | (uint32_t)ENET_BABT_INTERRUPT | (uint32_t)ENET_EBERR_INTERRUPT |
                       (uint32_t)ENET_LATE_COLLISION_INTERRUPT |
                       (uint32_t)ENET_RETRY_LIMIT_INTERRUPT | (uint32_t)ENET_UNDERRUN_INTERRUPT;

    if ((errMask & base->EIR) != 0U)
    {
        /* Callback function. */
        if (g_enetState[instance]->callback != NULL)
        {
            g_enetState[instance]->callback(instance, ENET_ERR_EVENT, 0);
        }
        /* Clear the error interrupt event. */
        errMask &= base->EIR;
        base->EIR = errMask;
    }
}

/*******************************************************************************
 * EOF
 ******************************************************************************/
