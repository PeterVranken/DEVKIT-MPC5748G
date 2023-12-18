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
 * @file enet_hw_access.h
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

#ifndef ENET_HW_ACCESS_H
#define ENET_HW_ACCESS_H

#include <stdlib.h>

#include "typ_types.h"
#include "rcf_rtmConfig.h"
#include "device_registers.h"
#include "enet_driver.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

#define ENET_MMFR_START_INDICATION     (1U)
#define ENET_MMFR_START_INDICATION_45  (0U)
#define ENET_MMFR_TURN_AROUND       (2U)

/*! @brief Control and status region bit masks of the receive buffer descriptor. */
#define ENET_BUFFDESCR_RX_EMPTY_MASK 0x8000U
#define ENET_BUFFDESCR_RX_INUSE_MASK 0x4000U
#define ENET_BUFFDESCR_RX_WRAP_MASK  0x2000U
#define ENET_BUFFDESCR_RX_LAST_MASK  0x0800U

/*! @brief Control and status bit masks of the transmit buffer descriptor. */
#define ENET_BUFFDESCR_TX_READY_MASK        0x8000U
#define ENET_BUFFDESCR_TX_TO1_MASK          0x4000U
#define ENET_BUFFDESCR_TX_WRAP_MASK         0x2000U
#define ENET_BUFFDESCR_TX_TO2_MASK          0x1000U
#define ENET_BUFFDESCR_TX_LAST_MASK         0x0800U
#define ENET_BUFFDESCR_TX_TRANSMITCRC_MASK  0x0400U

/*! @brief Masks for the bits in the CRC-32 value */
#define ENET_CRC32_BIT_1_MASK       0x80000000UL
#define ENET_CRC32_BITS_2_6_MASK    0x7C000000UL
#define ENET_CRC32_BITS_2_6_SHIFT   26UL

#if FEATURE_ENET_HAS_ENHANCED_BD

#define ENET_RX_ENH_ERR_MASK    (0x86000030U)
#define ENET_TX_ENH_ERR_MASK    (0x00003F00U)

/*! @brief Control and status bit masks of the enhanced receive buffer descriptor. */
#define ENET_RX_ENH1_FRAG_MASK        0x00000001UL
#define ENET_RX_ENH1_IPV6_MASK        0x00000002UL
#define ENET_RX_ENH1_VPCP_MASK        0x0000E000UL
#define ENET_RX_ENH1_VPCP_SHIFT       13UL
#define ENET_RX_ENH1_INT_MASK         0x00800000UL
#define ENET_RX_ENH1_UNICAST_MASK     0x01000000UL
#define ENET_RX_ENH2_CSUM_MASK        0x0000FFFFUL
#define ENET_RX_ENH2_PROTO_MASK       0x00FF0000UL
#define ENET_RX_ENH2_PROTO_SHIFT      16UL
#define ENET_RX_ENH2_HLEN_MASK        0xF8000000UL
#define ENET_RX_ENH2_HLEN_SHIFT       27UL

/*! @brief Control and status bit masks of the enhanced transmit buffer descriptor. */
#define ENET_TX_ENH1_IINS_MASK        0x08000000UL
#define ENET_TX_ENH1_PINS_MASK        0x10000000UL
#define ENET_TX_ENH1_INT_MASK         0x40000000UL
#if FEATURE_ENET_HAS_TBS
#define ENET_TX_ENH1_UTLT_MASK        0x01000000UL
#endif /* FEATURE_ENET_HAS_CBS */
#if (FEATURE_ENET_RING_COUNT > 1U)
#define ENET_TX_ENH1_FTYPE_SHIFT      20U
#endif /* (FEATURE_ENET_RING_COUNT > 1U) */

#define ENET_RX_INTERRUPTS_MASK  (ENET_EIR_RXF_MASK | ENET_EIR_RXB_MASK)
#define ENET_TX_INTERRUPTS_MASK  (ENET_EIR_TXF_MASK | ENET_EIR_TXB_MASK)

#endif /* FEATURE_ENET_HAS_ENHANCED_BD */

/*!
 * @brief Management Frame operation type
 */
typedef enum
{
    ENET_MMFR_OP_ADDR = 0U,
    ENET_MMFR_OP_WRITE,
    ENET_MMFR_OP_READ,
    ENET_MMFR_OP_READ_45
} enet_mmfr_op_type_t;

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*! @brief Pointers to enet handles for each instance. */
extern enet_state_t *g_enetState[ENET_INSTANCE_COUNT];

/*! @brief Pointers to ENET bases for each instance. */
extern ENET_Type *const RODATA(s_enetBases)[];

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Configures the receive and transmit buffer descriptors.
 *
 * @param[in] base The base address of the module
 * @param[in] bufferConfig The configuration used for the receive and transmit descriptors
 * @param[in] buffSize The maximum buffer size
 */
void ENET_ConfigBufferDescriptors(ENET_Type * base,
                                  uint8_t ring,
                                  const enet_buffer_config_t *bufferConfig,
                                  uint16_t buffSize);

#if FEATURE_ENET_HAS_RX_CONFIG

/*!
 * @brief Configures the receive block.
 *
 * @param[in] base The base address of the module
 * @param[in] config The user configuration structure
 */
void ENET_ConfigReceiveControl(ENET_Type *base,
                               const enet_config_t *config);

#endif /* FEATURE_ENET_HAS_RX_CONFIG */

#if FEATURE_ENET_HAS_TX_CONFIG

/*!
 * @brief Configures the transmit block.
 *
 * @param[in] base The base address of the module
 * @param[in] config The user configuration structure
 */
void ENET_ConfigTransmitControl(ENET_Type *base,
                                const enet_config_t *config);

#endif /* FEATURE_ENET_HAS_TX_CONFIG */

/*!
 * @brief Resets the ENET module.
 *
 * @param[in] base The base address of the module
 */
static inline void ENET_Reset(ENET_Type *base)
{
    base->ECR |= ENET_ECR_RESET_MASK;
#if (defined(CORE_LITTLE_ENDIAN))
    base->ECR |= ENET_ECR_DBSWP_MASK;
#endif
#if FEATURE_ENET_HAS_ENHANCED_BD
    base->ECR |= ENET_ECR_EN1588_MASK;
#endif
}

/*!
 * @brief Indicates that the driver produced empty receive buffers with the empty bit set.
 *
 * @param[in] base The base address of the module
 * @param[in] ring The ring number
 */
static inline void ENET_ActivateReceive(ENET_Type *base, uint8_t ring)
{
    if (ring == 0U)
    {
        base->RDAR = ENET_RDAR_RDAR_MASK;
    }
#if (FEATURE_ENET_RING_COUNT > 1U)
    if (ring == 1U)
    {
        base->RDAR1 = ENET_RDAR_RDAR_MASK;
    }
#endif /* (FEATURE_ENET_RING_COUNT > 1U) */
#if (FEATURE_ENET_RING_COUNT > 2U)
    if (ring == 2U)
    {
        base->RDAR2 = ENET_RDAR_RDAR_MASK;
    }
#endif /* (FEATURE_ENET_RING_COUNT > 2U) */
}

/*!
 * @brief Indicates that the driver produced empty transmit buffers with the ready bit set.
 *
 * @param[in] base The base address of the module
 * @param[in] ring The ring number
 */
static inline void ENET_ActivateTransmit(ENET_Type *base, uint8_t ring)
{
    volatile uint32_t *tdar = NULL;

    if (ring == 0U)
    {
        tdar = &base->TDAR;
    }
#if (FEATURE_ENET_RING_COUNT > 1U)
    if (ring == 1U)
    {
        tdar = &base->TDAR1;
    }
#endif /* (FEATURE_ENET_RING_COUNT > 1U) */
#if (FEATURE_ENET_RING_COUNT > 2U)
    if (ring == 2U)
    {
        tdar = &base->TDAR2;
    }
#endif /* (FEATURE_ENET_RING_COUNT > 2U) */

#ifdef ERRATA_E7885
    /* See
       https://www.nxp.com/docs/pcn_attachments/17218_MPC5748G_1N81M_Errata_June_2016_Rev_2.pdf
       (visited Sep 28, 2023):
         ENET: Potential sequencing issue with TDAR in Multi-Queue mode
         Description: When the 10/100-Mbps Ethernet Media Access Control (ENET MAC) module
       is in Multi-queue mode, there is a potential sequencing issue between the module
       clearing the ENET Transmit Descriptor Active Register (ENET_TDARn_TDAR) bit and the
       software setting it. This can cause the module to hang.
         Workaround: ENET_TDARn_TDAR should be set by software after it is cleared by the
       ENET. This is achieved by introducing a short delay after a new Transmit Buffer
       Descriptor (TxBD) is prepared and written into a designated memory.
         - Software prepares a new TxBD and stores/writes it into a designated memory
         - Software introduces a delay by reading the relevant ENET_TDARn_TDAR 4 times, as
           seen below */
    uint8_t i;
    bool tdarTrigger = false;

    for (i = 0; i < 4U; i++)
    {
        if ((*tdar & ENET_TDAR_TDAR_MASK) == 0U)
        {
            tdarTrigger = true;
            break;
        }
    }
    if (tdarTrigger)
    {
#endif
    *tdar = ENET_TDAR_TDAR_MASK;
#ifdef ERRATA_E7885
    }
#endif
}

/*!
 * @brief Enables the specified interrupts.
 *
 * @param[in] base The base address of the module
 * @param[in] mask Mask representing the interrupts to be enabled
 */
static inline void ENET_EnableInterrupts(ENET_Type *base,
                                         uint32_t mask)
{
    base->EIMR |= mask;
}

/*!
 * @brief Disables the specified interrupts.
 *
 * @param[in] base The base address of the module
 * @param[in] mask Mask representing the interrupts to be disabled
 */
static inline void ENET_DisableInterrupts(ENET_Type *base,
                                          uint32_t mask)
{
    base->EIMR &= ~mask;
}

/*!
 * @brief Gets a mask of the interrupts flags which are set.
 *
 * @param[in] base The base address of the module
 * @return Mask representing the interrupt flags set
 */
static inline uint32_t ENET_GetInterruptStatus(const ENET_Type *base)
{
    return base->EIR;
}

/*!
 * @brief Clears the interrupts flags according to the received mask.
 *
 * @param[in] base The base address of the module
 * @param[in] mask Mask representing the interrupt flags to be cleared
 */
static inline void ENET_ClearInterruptStatus(ENET_Type *base,
                                             uint32_t mask)
{
    base->EIR = mask;
}

/*!
 * @brief Enables the ENET module.
 *
 * @param[in] base The base address of the module
 */
static inline void ENET_Enable(ENET_Type *base)
{
    base->ECR |= ENET_ECR_ETHEREN_MASK;
}

/*!
 * @brief Disables the ENET module.
 *
 * @param[in] base The base address of the module
 */
static inline void ENET_Disable(ENET_Type *base)
{
    base->ECR &= ~ENET_ECR_ETHEREN_MASK;
}

#if FEATURE_ENET_HAS_ACCELERATOR

/*!
 * @brief Configures transmit accelerator functions.
 *
 * @param[in] base The base address of the module
 * @param[in] txAccelerConfig Transmit accelerator functions to be applied
 */
static inline void ENET_ConfigTransmitAccelerator(ENET_Type * base,
                                                  uint8_t txAccelerConfig)
{
    base->TACC = txAccelerConfig;

    /* Enable store and forward when accelerator is enabled */
    if (((uint32_t)txAccelerConfig & ((uint32_t)ENET_TX_ACCEL_INSERT_IP_CHECKSUM | (uint32_t)ENET_TX_ACCEL_INSERT_PROTO_CHECKSUM)) != 0U)
    {
        base->TFWR = ENET_TFWR_STRFWD_MASK;
    }
}

/*!
 * @brief Configures receive accelerator functions.
 *
 * @param[in] base The base address of the module
 * @param[in] rxAccelerConfig Receive accelerator functions to be applied
 */
static inline void ENET_ConfigReceiveAccelerator(ENET_Type * base,
                                                 uint8_t rxAccelerConfig)
{
    base->RACC = rxAccelerConfig;

    /* Enable store and forward when accelerator is enabled */
    if (((uint32_t)rxAccelerConfig & ((uint32_t)ENET_RX_ACCEL_ENABLE_IP_CHECK | (uint32_t)ENET_RX_ACCEL_ENABLE_PROTO_CHECK)) != 0U)
    {
        base->RSFL = 0;
    }
}

#endif /* FEATURE_ENET_HAS_ACCELERATOR */

/*!
 * @brief Sets the lower 32 bits of the MAC physical address.
 *
 * @param[in] base The base address of the module
 * @param[in] addrLower The lower 32 bits of the MAC physical address
 */
static inline void ENET_SetPhyAddrLower(ENET_Type * base,
                                        uint32_t addrLower)
{
    base->PALR = addrLower;
}

/*!
 * @brief Sets the upper 16 bits of the MAC physical address.
 *
 * @param[in] base The base address of the module
 * @param[in] addrUpper The upper 16 bits of the MAC physical address
 */
static inline void ENET_SetPhyAddrUpper(ENET_Type * base,
                                        uint32_t addrUpper)
{
    base->PAUR = addrUpper << ENET_PAUR_PADDR2_SHIFT;
}

/*!
 * @brief Gets the lower 32 bits of the MAC physical address.
 *
 * @param[in] base The base address of the module
 * @return The lower 32 bits of the MAC physical address
 */
static inline uint32_t ENET_GetPhyAddrLower(const ENET_Type * base)
{
    return base->PALR;
}

/*!
 * @brief Gets the upper 16 bits of the MAC physical address.
 *
 * @param[in] base The base address of the module
 * @return The upper 16 bits of the MAC physical address
 */
static inline uint32_t ENET_GetPhyAddrUpper(const ENET_Type * base)
{
    return (base->PAUR & ENET_PAUR_PADDR2_MASK) >> ENET_PAUR_PADDR2_SHIFT;
}

/*!
 * @brief Writes a MII management frame.
 *
 * @param[in] base The base address of the module
 * @param[in] phyAddr The address of the PHY
 * @param[in] phyReg The address of the register to be accessed
 * @param[in] opType The operation type (read/write)
 * @param[in] data Data to be written, ignored if the operation is a read one
 * @param[in] clause45 True if the management frame is a clause 45 one, false for clause 22
 * @param[in] startTime Time when the operation was started
 * @param[in] timeoutMs Timeout for the management operation (in milliseconds)
 * @return STATUS_SUCCESS if the operation completed succesfully, STATUS_TIMEOUT
 * if the specified timeout expired before completing the operation.
 */
status_t ENET_WriteManagementFrame(ENET_Type * base,
                                             uint8_t phyAddr,
                                             uint8_t phyReg,
                                             enet_mmfr_op_type_t opType,
                                             uint16_t data,
                                             bool clause45,
                                             uint32_t startTime,
                                             uint32_t timeoutMs);

/*!
 * @brief Reads the data field of a MII management frame.
 *
 * @param[in] base The base address of the module
 * @return The read data
 */
static inline uint16_t ENET_ReadManagementFrameData(const ENET_Type * base)
{
    return (uint16_t)(base->MMFR & ENET_MMFR_DATA_MASK);
}

/*!
 * @brief Configures the MII management interface.
 *
 * @param[in] base The base address of the module
 * @param[in] miiSpeed MII Speed
 * @param[in] holdTime Hold time
 * @param[in] miiPreambleDisabled Enable/Disable MII preamble
 */
void ENET_WriteManagementConfig(ENET_Type * base,
                                uint32_t miiSpeed,
                                uint32_t holdTime,
                                bool miiPreambleDisabled);

/*!
 * @brief Adds an address to the hash table used in the address recognition
 * process for receive frames with multicast destination address.
 *
 * @param[in] base The base address of the module
 * @param[in] crc The CRC-32 of the MAC address
 */
static inline void ENET_AddToGroupHashTable(ENET_Type * base,
                                            uint32_t crc)
{
    if ((crc & ENET_CRC32_BIT_1_MASK) != 0U)
    {
        base->GAUR |= (1UL << ((crc & ENET_CRC32_BITS_2_6_MASK) >> ENET_CRC32_BITS_2_6_SHIFT));
    }
    else
    {
        base->GALR |= (1UL << ((crc & ENET_CRC32_BITS_2_6_MASK) >> ENET_CRC32_BITS_2_6_SHIFT));
    }
}

/*!
 * @brief Removes an address from the hash table used in the address recognition
 * process for receive frames with multicast destination address.
 *
 * @param[in] base The base address of the module
 * @param[in] crc The CRC-32 of the MAC address
 */
static inline void ENET_RemoveFromGroupHashTable(ENET_Type * base,
                                                 uint32_t crc)
{
    if ((crc & ENET_CRC32_BIT_1_MASK) != 0U)
    {
        base->GAUR &= ~(1UL << ((crc & ENET_CRC32_BITS_2_6_MASK) >> ENET_CRC32_BITS_2_6_SHIFT));
    }
    else
    {
        base->GALR &= ~(1UL << ((crc & ENET_CRC32_BITS_2_6_MASK) >> ENET_CRC32_BITS_2_6_SHIFT));
    }
}

/*!
 * @brief Adds an address to the hash table used in the address recognition
 * process for receive frames with unicast destination address.
 *
 * @param[in] base The base address of the module
 * @param[in] crc The CRC-32 of the MAC address
 */
static inline void ENET_AddToIndividualHashTable(ENET_Type * base,
                                                 uint32_t crc)
{
    if ((crc & ENET_CRC32_BIT_1_MASK) != 0U)
    {
        base->IAUR |= (1UL << ((crc & ENET_CRC32_BITS_2_6_MASK) >> ENET_CRC32_BITS_2_6_SHIFT));
    }
    else
    {
        base->IALR |= (1UL << ((crc & ENET_CRC32_BITS_2_6_MASK) >> ENET_CRC32_BITS_2_6_SHIFT));
    }
}

/*!
 * @brief Removes an address from the hash table used in the address recognition
 * process for receive frames with unicast destination address.
 *
 * @param[in] base The base address of the module
 * @param[in] crc The CRC-32 of the MAC address
 */
static inline void ENET_RemoveFromIndividualHashTable(ENET_Type * base,
                                                      uint32_t crc)
{
    if ((crc & ENET_CRC32_BIT_1_MASK) != 0U)
    {
        base->IAUR &= ~(1UL << ((crc & ENET_CRC32_BITS_2_6_MASK) >> ENET_CRC32_BITS_2_6_SHIFT));
    }
    else
    {
        base->IALR &= ~(1UL << ((crc & ENET_CRC32_BITS_2_6_MASK) >> ENET_CRC32_BITS_2_6_SHIFT));
    }
}

/*!
 * @brief Enables/Disables the MIB counters.
 *
 * Note: When enabling the counters, their values are reset.
 *
 * @param[in] instance Instance number
 * @param[in] enable Enable/Disable MIB counters
 */
void ENET_ConfigCounters(uint8_t instance, bool enable);

/*!
 * @brief Sets the speed of the MII interface
 *
 * @param[in] instance Instance number
 * @param[in] speed MII speed
 */
void ENET_SetSpeed(ENET_Type * base, enet_mii_speed_t speed);

#if defined(__cplusplus)
}
#endif

#endif  /* ENET_HW_ACCESS_H */

/*******************************************************************************
 * EOF
 ******************************************************************************/
