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
#include "typ_types.h"

/*******************************************************************************
 * Variables
 ******************************************************************************/

/* Wrap-around value for timeout */
#define ENET_TIMEOUT_WRAP  0xFFFFFFFFU

ENET_Type *const RODATA(s_enetBases)[] = ENET_BASE_PTRS;

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
    const uint32_t currentTime = rcf_getSystemTime();
    return (int32_t)(currentTime - (startTime + timeout)) > 0;
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
        base->TDSR = (uint32_t)bufferConfig->txRingAligned;
        base->RDSR = (uint32_t)bufferConfig->rxRingAligned;
        base->MRBR = buffSize;
    }
#if (FEATURE_ENET_RING_COUNT > 1U)
    if (ring == 1U)
    {
        base->TDSR1 = (uint32_t)bufferConfig->txRingAligned;
        base->RDSR1 = (uint32_t)bufferConfig->rxRingAligned;
        base->MRBR1 = buffSize;
        base->DMACFG[0] = ENET_DMACFG_DMA_CLASS_EN_MASK;
    }
#endif /* (FEATURE_ENET_RING_COUNT > 1U) */
#if (FEATURE_ENET_RING_COUNT > 2U)
    if (ring == 2U)
    {
        base->TDSR2 = (uint32_t)bufferConfig->txRingAligned;
        base->RDSR2 = (uint32_t)bufferConfig->rxRingAligned;
        base->MRBR2 = buffSize;
        base->DMACFG[1] = ENET_DMACFG_DMA_CLASS_EN_MASK;
    }
#endif /* (FEATURE_ENET_RING_COUNT > 2U) */
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

    /* Configures MAC receive controller with user configure structure. */
    rcr = ENET_RCR_NLC(((config->rxConfig & (uint32_t)ENET_RX_CONFIG_ENABLE_PAYLOAD_LEN_CHECK) != 0UL) ? 1UL : 0UL) |
          ENET_RCR_CFEN(((config->rxConfig & (uint32_t)ENET_RX_CONFIG_ENABLE_FLOW_CONTROL) != 0UL) ? 1UL : 0UL) |
          ENET_RCR_CRCFWD(((config->rxConfig & (uint32_t)ENET_RX_CONFIG_STRIP_CRC_FIELD) != 0UL) ? 1UL : 0UL) |
          ENET_RCR_FCE(((config->rxConfig & (uint32_t)ENET_RX_CONFIG_ENABLE_FLOW_CONTROL) != 0UL) ? 1UL : 0UL) |
          ENET_RCR_PAUFWD(((config->rxConfig & (uint32_t)ENET_RX_CONFIG_FORWARD_PAUSE_FRAMES) != 0UL) ? 1UL : 0UL) |
          ENET_RCR_PADEN(((config->rxConfig & (uint32_t)ENET_RX_CONFIG_REMOVE_PADDING) != 0UL) ? 1UL : 0UL) |
          ENET_RCR_BC_REJ(((config->rxConfig & (uint32_t)ENET_RX_CONFIG_REJECT_BROADCAST_FRAMES) != 0UL) ? 1UL : 0UL) |
          ENET_RCR_PROM(((config->rxConfig & (uint32_t)ENET_RX_CONFIG_ENABLE_PROMISCUOUS_MODE) != 0UL) ? 1UL : 0UL) |
          ENET_RCR_MII_MODE(1U) |
#if FEATURE_ENET_HAS_RGMII
		  ENET_RCR_RGMII_EN((config->miiMode == ENET_RGMII_MODE) ? 1UL : 0UL) |
#endif /* FEATURE_ENET_HAS_RGMII */
          ENET_RCR_RMII_MODE((config->miiMode == ENET_RMII_MODE) ? 1UL : 0UL) |
          ENET_RCR_RMII_10T((config->miiSpeed == ENET_MII_SPEED_10M) ? 1UL : 0UL) |
          ENET_RCR_MAX_FL(config->maxFrameLen);

    /* Receive setting for half duplex. */
    if (config->miiDuplex == ENET_MII_HALF_DUPLEX)
    {
        rcr |= ENET_RCR_DRT(1);
    }
    /* Sets internal loopback. */
    if ((config->rxConfig & (uint32_t)ENET_RX_CONFIG_ENABLE_MII_LOOPBACK) != 0U)
    {
        rcr |= ENET_RCR_LOOP(1);
        rcr &= ~ENET_RCR_DRT_MASK;
    }
    base->RCR = rcr;

#if FEATURE_ENET_HAS_SPEED_1000M
    if (config->miiSpeed == ENET_MII_SPEED_1000M)
    {
    	base->ECR |= ENET_ECR_SPEED(1U);
    }
#endif /* FEATURE_ENET_HAS_SPEED_1000M */
}

#endif /* FEATURE_ENET_HAS_RX_CONFIG */

#if FEATURE_ENET_HAS_TX_CONFIG

/*FUNCTION**********************************************************************
 *
 * Function Name : ENET_ConfigTransmitControl
 * Description   : Configures the transmit block.
 *
 *END**************************************************************************/
void ENET_ConfigTransmitControl(ENET_Type *base,
                                const enet_config_t *config)
{
    uint32_t tcr = base->TCR;

    /* Configures MAC transmit controller: duplex mode, mac address insertion. */
    tcr &= ~(ENET_TCR_FDEN_MASK | ENET_TCR_CRCFWD_MASK | ENET_TCR_ADDINS_MASK);
    tcr |= ENET_TCR_FDEN(config->miiDuplex) |
           ENET_TCR_CRCFWD(((config->txConfig & (uint32_t)ENET_TX_CONFIG_DISABLE_CRC_APPEND) != 0UL) ? 1UL : 0UL) |
           ENET_TCR_ADDINS(((config->txConfig & (uint32_t)ENET_TX_CONFIG_ENABLE_MAC_ADDR_INSERTION) != 0UL) ? 1UL : 0UL);

    base->TCR = tcr;

#if (FEATURE_ENET_RING_COUNT > 1U)
    /* By default, use round robin arbitration scheme */
       base->QOS = ENET_QOS_TX_SCHEME(1U);
#endif /* (FEATURE_ENET_RING_COUNT > 1U) */
}

#endif /* FEATURE_ENET_HAS_TX_CONFIG */

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
	
	config = ENET_MSCR_MII_SPEED(miiSpeed) | ENET_MSCR_DIS_PRE(miiPreambleDisabled ? 1UL : 0UL) | ENET_MSCR_HOLDTIME(holdTime);
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
                                   uint32_t startTimeInTicks,
                                   uint32_t timeoutInTicks)
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
    while (!ENET_Timeout(startTimeInTicks, timeoutInTicks));

    return status;
    
} /* ENET_WriteManagementFrame */



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

    if (enable)
    {
        /* Clear counters - MIB_CLEAR bit needs to be set, then cleared */
        base->MIBC |= ENET_MIBC_MIB_CLEAR_MASK;
        (void) base->MIBC;
        base->MIBC &= ~ENET_MIBC_MIB_CLEAR_MASK;

        base->MIBC &= ~ENET_MIBC_MIB_DIS_MASK;
    }
    else
    {
        base->MIBC |= ENET_MIBC_MIB_DIS_MASK;
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
    if (speed == ENET_MII_SPEED_10M)
    {
    	base->RCR |= ENET_RCR_RMII_10T_MASK;
    }
	else
	{
		base->RCR &= ~ENET_RCR_RMII_10T_MASK;
	}
#if FEATURE_ENET_HAS_SPEED_1000M
    if (speed == ENET_MII_SPEED_1000M)
    {
    	base->ECR |= ENET_ECR_SPEED_MASK;
    }
	else
    {
    	base->ECR &= ~ENET_ECR_SPEED_MASK;
    }
#endif /* FEATURE_ENET_HAS_SPEED_1000M */
}


/*******************************************************************************
 * EOF
 ******************************************************************************/
