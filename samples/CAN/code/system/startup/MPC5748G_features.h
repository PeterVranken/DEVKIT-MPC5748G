/*
** ###################################################################
**
**     Abstract:
**         Chip specific module features.
**
**     Copyright (c) 2015 Freescale Semiconductor, Inc.
**     Copyright 2016-2018 NXP
**     All rights reserved.
**
**     THIS SOFTWARE IS PROVIDED BY NXP "AS IS" AND ANY EXPRESSED OR
**     IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
**     OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
**     IN NO EVENT SHALL NXP OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
**     INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**     (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
**     SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
**     HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
**     STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
**     IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
**     THE POSSIBILITY OF SUCH DAMAGE.
**
**
** ###################################################################
*/

/*!
 * @file MPC5748G_features.h
 *
 * @page misra_violations MISRA-C:2012 violations
 *
 * @section [global]
 * Violates MISRA 2012 Advisory Rule 2.3, Global typedef not referenced.
 * Type used only in some modules of the SDK.
 *
 * @section [global]
 * Violates MISRA 2012 Advisory Rule 2.5, Global macro not referenced.
 * The macros defined are used to define features for each driver, so this might be reported
 * when the analysis is made only on one driver.
 *
 * @section [global]
 * Violates MISRA 2012 Advisory Directive 4.9, Function-like macro
 * These are very simple macros used for abstracting hw implementation.
 * They help make the code easy to understand.
 *
 * @section [global]
 * Violates MISRA 2012 Required Rule 5.1, identifier clash
 * The supported compilers use more than 31 significant characters for identifiers.
 *
 * @section [global]
 * Violates MISRA 2012 Required Rule 5.2, identifier clash
 * The supported compilers use more than 31 significant characters for identifiers.
 *
 * @section [global]
 * Violates MISRA 2012 Required Rule 5.4, identifier clash
 * The supported compilers use more than 31 significant characters for identifiers.
 *
 * @section [global]
 * Violates MISRA 2012 Required Rule 5.5, identifier clash
 * The supported compilers use more than 31 significant characters for identifiers.
 *
 */

#if !defined(MPC5748G_FEATURES_H)
#define MPC5748G_FEATURES_H

/* include device_registers.h for SIUL2 module configuration structures */
#include "device_registers.h"

/* ERRATA sections*/

/* @brief E8759: FlexCAN: FD frame format is not compliant to the new ISO/CD 11898-1: 2014-12-11
 * because CAN_CTRL2[ISOCANFDEN] bit cannot be set. The FD frame format is incompatible, the Cyclic
 * Redundancy Check [CRC] does not include the added stuff bit count field. The FD CRC computation
 * is incompatible, a different seed value is used. This errata applies to mask 1N81M for
 * MPC5748G CPU. */
#define ERRATA_E8759

/* @brief E10368 FlexCAN: Transition of the CAN FD operation enable bit may lead FlexCAN
 * logic to an inconsistent state. The activation or deactivation of the CAN FD operation by
 * setting or clearing the FDEN bit of the CAN_MCR register or by setting the FlexCAN soft
 * reset bit (SOFTRST) of the CAN_MCR register when the FDEN bit is enabled may cause an
 * internal FlexCAN register to become metastable. As result, the first CAN frame, transmitted
 * or received, may have corrupted data (ID and payload).
 * This errata applies to mask 0N78S for MPC5748G CPU.
 */
#define ERRATA_E10368

/* @brief E10595 FlexCAN: FLEXCAN1-7 modules will not work unless the Fast External Oscillator (FXOSC)
 * clock source is enabled. FXOSC clock should be enabled before using FLEXCAN1-7 modules by setting the
 * Oscillator Enable bit (FXOSCON) in the active mode configuration register (MC_ME_xxxx_MC).
 * This errata applies to mask 0N78S for MPC5748G CPU.
 */
#define ERRATA_E10595

/* @brief E7885: ENET: Potential sequencing issue with TDAR in Multi-Queue mode.
 * This errata applies to mask 1N81M for MPC5748G CPU. */
#define ERRATA_E7885

/* @brief E10200: STM: Reading the System Timer Module Count register may return
 * an incorrect value when STM is configured to use the FXOSC clock source
 * This errata applies to these products: MPC5748G, MPC5747G, MPC5746G, MPC5748C, MPC5747C*/
#define ERRATA_E10200

/* Mode Entry Module features */

/* @brief Key and inverted key values so write access to MCTL register is permitted */
#define FEATURE_MC_ME_KEY           (0x5AF0U)
#define FEATURE_MC_ME_KEY_INV       (0xA50FU)
/* @brief Mode entry has TEST mode */
#define FEATURE_MC_ME_HAS_TEST_MODE (0U)
/* @brief Mode entry has HALT mode */
#define FEATURE_MC_ME_HAS_HALT_MODE (0U)
/* @brief Mode entry has STOP0 mode */
#define FEATURE_MC_ME_HAS_STOP0_MODE (0U)
/* @brief Mode entry has STANDBY mode */
#define FEATURE_MC_ME_HAS_STANDBY_MODE (1U)
/* @brief Mode entry allow to configured flash bit field*/
#define FEATURE_MC_ME_HAS_FLAON_CONFIG (1U)
/* @brief Mode entry has FLASH in power down mode */
#define FEATURE_MC_ME_HAS_FLAON_PD_MODE (1U)
/* @brief Mode entry has FLASH in low power mode */
#define FEATURE_MC_ME_HAS_FLAON_LP_MODE (0U)
/* @brief Enable or disable SDPLL clock */
#define FEATURE_HAS_SDPLL_CLK_CONFIG (0U)
/* @brief Number of cores. */
#define NUMBER_OF_CORES (3u)

/* CMP module features */

/* @brief Comparator hard block offset control */
#define FEATURE_CMP_HAS_HARD_BLOCK_OFFSET   (0)
/* @brief Comparator fix DAC input to mux side */
#define FEATURE_CMP_DAC_FIX_SELECTION       (1)
/* @brief Comparator initialization delay */
#define FEATURE_CMP_HAS_INIT_DELAY          (0)

#define C0_RESET_VALUE (CMP_C0_DMAEN(0U) | CMP_C0_IER(0U) | CMP_C0_IEF(0U) | CMP_C0_CFR(1U) |                     \
                        CMP_C0_CFF(1U) | CMP_C0_FPR(0U) | CMP_C0_SE(0U) | CMP_C0_WE(0U) |                         \
                        CMP_C0_PMODE(0U) | CMP_C0_INVT(0U) | CMP_C0_COS(0U) | CMP_C0_OPE(0U) |                    \
                        CMP_C0_EN(0U) | CMP_C0_FILTER_CNT(0U) | CMP_C0_HYSTCTR(0U))

#define C1_RESET_VALUE (CMP_C1_INPSEL(0U) | CMP_C1_INNSEL(0U) | CMP_C1_CHN7(0U) | CMP_C1_CHN6(0U) |               \
                        CMP_C1_CHN5(0U) | CMP_C1_CHN4(0U) | CMP_C1_CHN3(0U) | CMP_C1_CHN2(0U) |                   \
                        CMP_C1_CHN1(0U) | CMP_C1_CHN0(0U) | CMP_C1_DACEN(0U) | CMP_C1_VRSEL(0U) |                 \
                        CMP_C1_PSEL(0U) | CMP_C1_MSEL(0U) |  CMP_C1_VOSEL(0U))

#define C2_RESET_VALUE (CMP_C2_RRE(0U) | CMP_C2_RRIE(0U) | CMP_C2_FXMP(0U) | CMP_C2_FXDACI(0U) | CMP_C2_FXMXCH(0U) |     \
                        CMP_C2_CH7F(1U) | CMP_C2_CH6F(1U) | CMP_C2_CH5F(1U) | CMP_C2_CH4F(1U) | CMP_C2_CH3F(1U) |        \
                        CMP_C2_CH2F(1U) | CMP_C2_CH1F(1U) | CMP_C2_CH0F(1U) | CMP_C2_NSAM(0U) | CMP_C2_NSAM(0U) |        \
                        CMP_C2_ACOn(0U))

#define CMP_C1_INPSEL_MASK      CMP_C1_DPSEL_MASK
#define CMP_C1_INPSEL_SHIFT     CMP_C1_DPSEL_SHIFT
#define CMP_C1_INPSEL_WIDTH     CMP_C1_DPSEL_WIDTH
#define CMP_C1_INPSEL           CMP_C1_DPSEL

#define CMP_C1_INNSEL_MASK      CMP_C1_DMSEL_MASK
#define CMP_C1_INNSEL_SHIFT     CMP_C1_DMSEL_SHIFT
#define CMP_C1_INNSEL_WIDTH     CMP_C1_DMSEL_WIDTH
#define CMP_C1_INNSEL           CMP_C1_DMSEL

#define CMP_DAC_SOURCE          1U
#define CMP_MUX_SOURCE          0U
#define CMP_DAC_RESOLUTION      63U

/* WDOG module features */

/* @brief The key values to clear Soft Lock bit */
#define FEATURE_WDOG_UNLOCK_VALUE1  (0xC520U)
#define FEATURE_WDOG_UNLOCK_VALUE2  (0xD928U)

/* SWI2C features */
#define SWI2C_INSTANCE_COUNT                   0xFFU

/* SWT module features */

/* @brief Support service mode watchpoint input */
#define FEATURE_SWT_SUPPORT_WATCHPOINT      (1U)
/* @brief Support for clock selection */
#define FEATURE_SWT_HAS_CLOCK_SELECT        (0U)
/* @brief Support for running in stop mode */
#define FEATURE_SWT_HAS_STOP_MODE           (1U)
/* @brief The key values to clear Soft Lock bit */
#define FEATURE_SWT_UNLOCK_VALUE1           (0xC520U)
#define FEATURE_SWT_UNLOCK_VALUE2           (0xD928U)
/* @brief The key values used for resetting the SWT counter in Fixed Service Sequence Mode */
#define FEATURE_SWT_FIXED_SERVICE_VALUE1    (0xA602U)
#define FEATURE_SWT_FIXED_SERVICE_VALUE2    (0xB480U)
/* @brief The reset value of the control register */
#define FEATURE_SWT_CR_RESET_VALUE          (0xFF00010AU)
/* @brief The reset value of the timeout register */
#define FEATURE_SWT_TO_RESET_VALUE          (0xA00U)
/* @brief The reset value of the window register */
#define FEATURE_SWT_WN_RESET_VALUE          (0x0U)
/* @brief The reset value of the service key register */
#define FEATURE_SWT_SK_RESET_VALUE          (0x0U)
/* @brief The minimum timeout value */
#define FEATURE_SWT_TO_MINIMUM_VALUE        (0x100U)
/* @brief Sets the master access protection field */
#define FEATURE_SWT_MAP_MASK                (0xFF000000U)
#define FEATURE_SWT_MAP_SHIFT               (24U)
#define FEATURE_SWT_MAP(x)                  (((uint32_t)(((uint32_t)(x)) << FEATURE_SWT_MAP_SHIFT)) & FEATURE_SWT_MAP_MASK)
/** Number of interrupt vector arrays for the SWT module. */
#define SWT_IRQS_ARR_COUNT                       (1u)
/** Number of interrupt channels for the SWT module. */
#define SWT_IRQS_CH_COUNT                        (1u)
/** Interrupt vectors for the SWT peripheral type */
#define SWT_IRQS                                 { SWT_0_IRQn, SWT_1_IRQn, SWT_2_IRQn, NotAvail_IRQn }

/* SMPU module features */

/* @brief Specifies the SMPU hardware and definition revision level */
#define FEATURE_SMPU_HARDWARE_REVISION_LEVEL (4U)
/* @brief Specifies the SMPU has process identifier feature */
#define FEATURE_SMPU_HAS_PROCESS_IDENTIFIER  (1U)
/* @brief Specifies the SMPU has owner lock feature */
#define FEATURE_SMPU_HAS_OWNER_LOCK          (1U)
/* @brief Specifies the SMPU has specific access feature */
#define FEATURE_SMPU_HAS_SPECIFIC_ACCESS_RIGHT_COUNT (3U)
/* @brief Specifies the SMPU support getting error detail */
#define FEATURE_SMPU_SUPPORT_GETTING_ERROR_DETAIL    (1U)
/* @brief Specifies the end address reset value */
#define FEATURE_SMPU_END_ADDRESS_RESET_VALUE (0xFU)
/* @brief Specifies the highest bus master */
#define FEATURE_SMPU_MAX_MASTER_NUMBER       (15U)
/* @brief Specifies total number of bus masters */
#define FEATURE_SMPU_MASTER_COUNT            (15U)
/* @brief The SMPU Logical Bus Master Number for Core Z4a master */
#define FEATURE_SMPU_MASTER_CORE_Z4A         (0U)
/* @brief The SMPU Logical Bus Master Number for Core Z4b master */
#define FEATURE_SMPU_MASTER_CORE_Z4B         (1U)
/* @brief The SMPU Logical Bus Master Number for Core Z2 master */
#define FEATURE_SMPU_MASTER_CORE_Z2          (2U)
/* @brief The SMPU Logical Bus Master Number for Hardware Security Mode master */
#define FEATURE_SMPU_MASTER_HSM              (3U)
/* @brief The SMPU Logical Bus Master Number for Enhanced Direct Memory Access master */
#define FEATURE_SMPU_MASTER_EDMA             (4U)
/* @brief The SMPU Logical Bus Master Number for Ethernet 0 master */
#define FEATURE_SMPU_MASTER_ENET0            (5U)
/* @brief The SMPU Logical Bus Master Number for FlexRay master */
#define FEATURE_SMPU_MASTER_FLEXRAY          (6U)
/* @brief The SMPU Logical Bus Master Number for Media Local Bus master */
#define FEATURE_SMPU_MASTER_MLB              (7U)
/* @brief The SMPU Logical Bus Master Number for Debugger Z4a master */
#define FEATURE_SMPU_MASTER_DEBUG_Z4A        (8U)
/* @brief The SMPU Logical Bus Master Number for Debugger Z4b master */
#define FEATURE_SMPU_MASTER_DEBUG_Z4B        (9U)
/* @brief The SMPU Logical Bus Master Number for Debugger Z2 master */
#define FEATURE_SMPU_MASTER_DEBUG_Z2         (10U)
/* @brief The SMPU Logical Bus Master Number for Universal Serial Bus 0 master */
#define FEATURE_SMPU_MASTER_USB0             (11U)
/* @brief The SMPU Logical Bus Master Number for Universal Serial Bus 1 master */
#define FEATURE_SMPU_MASTER_USB1             (12U)
/* @brief The SMPU Logical Bus Master Number for Secure Digital Host Controller master */
#define FEATURE_SMPU_MASTER_USDHC            (13U)
/* @brief The SMPU Logical Bus Master Number for Ethernet 1 master */
#define FEATURE_SMPU_MASTER_ENET1            (14U)
/* @brief The SMPU Logical Bus Masters */
#define FEATURE_SMPU_MASTER                      \
{                                                \
FEATURE_SMPU_MASTER_CORE_Z4A,  /* CORE Z4A */    \
FEATURE_SMPU_MASTER_CORE_Z4B,  /* CORE Z4B */    \
FEATURE_SMPU_MASTER_CORE_Z2,   /* CORE Z2 */     \
FEATURE_SMPU_MASTER_HSM,       /* HSM */         \
FEATURE_SMPU_MASTER_EDMA,      /* EDMA */        \
FEATURE_SMPU_MASTER_ENET0,     /* ENET 0 */      \
FEATURE_SMPU_MASTER_FLEXRAY,   /* FLEXRAY */     \
FEATURE_SMPU_MASTER_MLB,       /* MLB */         \
FEATURE_SMPU_MASTER_DEBUG_Z4A, /* DEBUG Z4A */   \
FEATURE_SMPU_MASTER_DEBUG_Z4B, /* DEBUG Z4B */   \
FEATURE_SMPU_MASTER_DEBUG_Z2,  /* DEBUG Z2 */    \
FEATURE_SMPU_MASTER_USB0,      /* USB 0 */       \
FEATURE_SMPU_MASTER_USB1,      /* USB 1 */       \
FEATURE_SMPU_MASTER_USDHC,     /* USDHC */       \
FEATURE_SMPU_MASTER_ENET1,     /* ENET1 */       \
}


/* SEMA42 module features */

/* @brief The SEMA42 Logical Bus Master Number for Core Z4a master */
#define FEATURE_SEMA42_MASTER_CORE_Z4A         (0U)
/* @brief The SEMA42 Logical Bus Master Number for Core Z4b master */
#define FEATURE_SEMA42_MASTER_CORE_Z4B         (1U)
/* @brief The SEMA42 Logical Bus Master Number for Core Z2 master */
#define FEATURE_SEMA42_MASTER_CORE_Z2          (2U)

/* @brief The SMPU Logical Bus Masters */
#define FEATURE_SEMA42_MASTER                      \
{                                                  \
FEATURE_SEMA42_MASTER_CORE_Z4A,  /* CORE Z4A */    \
FEATURE_SEMA42_MASTER_CORE_Z4B,  /* CORE Z4B */    \
FEATURE_SEMA42_MASTER_CORE_Z2,   /* CORE Z2 */     \
}


/* I2C module features */

/* @brief DMA instance used for I2C module */
#define I2C_DMA_INSTANCE                    (0U)

/* @brief DMA instance used for I2C module */
#define I2C_DMA_REQ                         {{(uint8_t)EDMA_REQ_I2C_0_TX,(uint8_t)EDMA_REQ_I2C_0_RX}, \
                                            {(uint8_t)EDMA_REQ_I2C_1_TX, (uint8_t)EDMA_REQ_I2C_1_RX}, \
                                            {(uint8_t)EDMA_REQ_I2C_2_TX, (uint8_t)EDMA_REQ_I2C_2_RX}, \
                                            {(uint8_t)EDMA_REQ_I2C_3_TX, (uint8_t)EDMA_REQ_I2C_3_RX}}

/* @brief Interrupt vectors for the I2C peripheral type */
#define I2C_IRQS                            {I2C0_IRQn, I2C1_IRQn, I2C2_IRQn, I2C3_IRQn}

/* @brief PCC clocks for I2C peripheral */
#define I2C_CLOCKS                          {IIC0_CLK, IIC1_CLK, IIC2_CLK, IIC3_CLK}

/* @brief SCL divider values */
#define NO_I2C_SCL_DIVIDERS                    71U

/* @brief SCL divider values */
#define I2C_SCL_DIVIDER                     {{0x0, 20U}, {0x1, 22U}, {0x2, 24U}, {0x3, 26U}, {0x4, 28U}, {0x5, 30U}, {0x9, 32U}, {0x6, 34U}, {0x0A, 36U}, {0x7, 40U}, \
                                            {0x0C, 44U}, {0x0D, 48U}, {0x43, 52U}, {0x0E, 56U}, {0x45, 60U}, {0x12, 64U}, {0x0F, 68U}, {0x13, 72U}, {0x14, 80U}, {0x15, 88U}, \
                                            {0x19, 96U}, {0x16, 104U}, {0x1A, 112U}, {0x85, 120U}, {0x17, 128U}, {0x4F, 136U}, {0x1C, 144U}, {0x1D, 160U}, {0x55, 176U}, \
                                            {0x1E, 192U}, {0x56, 208U}, {0x22, 224U}, {0x1F, 240U}, {0x23, 256U}, {0x8F, 272U}, {0x24, 288U}, {0x25, 320U}, {0x95, 352U}, \
                                            {0x26, 384U}, {0x96, 416U}, {0x2A, 448U}, {0x27, 480U}, {0x2B, 512U}, {0x2C, 576U}, {0x2D, 640U}, {0x2E, 768U}, {0x32, 896U}, \
                                            {0x2F, 960U}, {0x33, 1024U}, {0x34, 1152U}, {0x35, 1280U}, {0x36, 1536U}, {0x3A, 1792U}, {0x37, 1920U}, {0x3B, 2048U}, {0x3C, 2304U}, \
                                            {0x3D, 2560U}, {0x3E, 3072U}, {0x7A, 3584U}, {0x3F, 3840U}, {0x7B, 4096U}, {0x7C, 4608U}, {0x7D, 5120U}, {0x7E, 6144U}, {0xBA, 7168U}, \
                                            {0x7F, 7680U}, {0xBB, 8192U}, {0xBC, 9216U}, {0xBD, 10240U}, {0xBE, 12288U}, {0xBF, 15360U}}

/* CAN module features */

/** Interrupt vectors for the CAN peripheral type */
#define CAN_Rx_Warning_IRQS                      { CAN0_ORed_IRQn, CAN1_ORed_IRQn, \
                                                   CAN2_ORed_IRQn, CAN3_ORed_IRQn, \
                                                   CAN4_ORed_IRQn, CAN5_ORed_IRQn, \
                                                   CAN6_ORed_IRQn, CAN7_ORed_IRQn }

#define CAN_Tx_Warning_IRQS                      { CAN0_ORed_IRQn, CAN1_ORed_IRQn, \
                                                   CAN2_ORed_IRQn, CAN3_ORed_IRQn, \
                                                   CAN4_ORed_IRQn, CAN5_ORed_IRQn, \
                                                   CAN6_ORed_IRQn, CAN7_ORed_IRQn }

#define CAN_Wake_Up_IRQS                         { CAN0_Wake_Up_IRQn, NotAvail_IRQn, \
                                                   NotAvail_IRQn, NotAvail_IRQn, \
                                                   NotAvail_IRQn, NotAvail_IRQn, \
                                                   NotAvail_IRQn, NotAvail_IRQn }

#define CAN_Error_IRQS                           { CAN0_Error_IRQn, CAN1_Error_IRQn, \
                                                   CAN2_Error_IRQn, CAN3_Error_IRQn, \
                                                   CAN4_Error_IRQn, CAN5_Error_IRQn, \
                                                   CAN6_Error_IRQn, CAN7_Error_IRQn }

#define CAN_Bus_Off_IRQS                         { CAN0_ORed_IRQn, CAN1_ORed_IRQn, \
                                                   CAN2_ORed_IRQn, CAN3_ORed_IRQn, \
                                                   CAN4_ORed_IRQn, CAN5_ORed_IRQn, \
                                                   CAN6_ORed_IRQn, CAN7_ORed_IRQn }

#define CAN_ORed_00_03_MB_IRQS                   { CAN0_ORed_00_03_MB_IRQn, CAN1_ORed_00_03_MB_IRQn, \
                                                   CAN2_ORed_00_03_MB_IRQn, CAN3_ORed_00_03_MB_IRQn, \
                                                   CAN4_ORed_00_03_MB_IRQn, CAN5_ORed_00_03_MB_IRQn, \
                                                   CAN6_ORed_00_03_MB_IRQn, CAN7_ORed_00_03_MB_IRQn }

#define CAN_ORed_04_07_MB_IRQS                   { CAN0_ORed_04_07_MB_IRQn, CAN1_ORed_04_07_MB_IRQn, \
                                                   CAN2_ORed_04_07_MB_IRQn, CAN3_ORed_04_07_MB_IRQn, \
                                                   CAN4_ORed_04_07_MB_IRQn, CAN5_ORed_04_07_MB_IRQn, \
                                                   CAN6_ORed_04_07_MB_IRQn, CAN7_ORed_04_07_MB_IRQn }

#define CAN_ORed_08_11_MB_IRQS                   { CAN0_ORed_08_11_MB_IRQn, CAN1_ORed_08_11_MB_IRQn, \
                                                   CAN2_ORed_08_11_MB_IRQn, CAN3_ORed_08_11_MB_IRQn, \
                                                   CAN4_ORed_08_11_MB_IRQn, CAN5_ORed_08_11_MB_IRQn, \
                                                   CAN6_ORed_08_11_MB_IRQn, CAN7_ORed_08_11_MB_IRQn }

#define CAN_ORed_12_15_MB_IRQS                   { CAN0_ORed_12_15_MB_IRQn, CAN1_ORed_12_15_MB_IRQn, \
                                                   CAN2_ORed_12_15_MB_IRQn, CAN3_ORed_12_15_MB_IRQn, \
                                                   CAN4_ORed_12_15_MB_IRQn, CAN5_ORed_12_15_MB_IRQn, \
                                                   CAN6_ORed_12_15_MB_IRQn, CAN7_ORed_12_15_MB_IRQn }

#define CAN_ORed_16_31_MB_IRQS                   { CAN0_ORed_16_31_MB_IRQn, CAN1_ORed_16_31_MB_IRQn, \
                                                   CAN2_ORed_16_31_MB_IRQn, CAN3_ORed_16_31_MB_IRQn, \
                                                   CAN4_ORed_16_31_MB_IRQn, CAN5_ORed_16_31_MB_IRQn, \
                                                   CAN6_ORed_16_31_MB_IRQn, CAN7_ORed_16_31_MB_IRQn }

#define CAN_ORed_32_63_MB_IRQS                   { CAN0_ORed_32_63_MB_IRQn, CAN1_ORed_32_63_MB_IRQn, \
                                                   CAN2_ORed_32_63_MB_IRQn, CAN3_ORed_32_63_MB_IRQn, \
                                                   CAN4_ORed_32_63_MB_IRQn, CAN5_ORed_32_63_MB_IRQn, \
                                                   CAN6_ORed_32_63_MB_IRQn, CAN7_ORed_32_63_MB_IRQn }

#define CAN_ORed_64_95_MB_IRQS                   { CAN0_ORed_64_95_MB_IRQn, CAN1_ORed_64_95_MB_IRQn, \
                                                   CAN2_ORed_64_95_MB_IRQn, CAN3_ORed_64_95_MB_IRQn, \
                                                   CAN4_ORed_64_95_MB_IRQn, CAN5_ORed_64_95_MB_IRQn, \
                                                   CAN6_ORed_64_95_MB_IRQn, CAN7_ORed_64_95_MB_IRQn }

/* @brief Frames available in Rx FIFO flag shift */
#define FEATURE_CAN_RXFIFO_FRAME_AVAILABLE  (5U)
/* @brief Rx FIFO warning flag shift */
#define FEATURE_CAN_RXFIFO_WARNING          (6U)
/* @brief Rx FIFO overflow flag shift */
#define FEATURE_CAN_RXFIFO_OVERFLOW         (7U)
/* @brief Maximum number of Message Buffers supported for payload size 8 for CAN0 */
#define FEATURE_CAN0_MAX_MB_NUM             (96U)
/* @brief Maximum number of Message Buffers supported for payload size 8 for CAN1 */
#define FEATURE_CAN1_MAX_MB_NUM             (96U)
/* @brief Maximum number of Message Buffers supported for payload size 8 for CAN2 */
#define FEATURE_CAN2_MAX_MB_NUM             (96U)
/* @brief Maximum number of Message Buffers supported for payload size 8 for CAN3 */
#define FEATURE_CAN3_MAX_MB_NUM             (96U)
/* @brief Maximum number of Message Buffers supported for payload size 8 for CAN4 */
#define FEATURE_CAN4_MAX_MB_NUM             (96U)
/* @brief Maximum number of Message Buffers supported for payload size 8 for CAN5 */
#define FEATURE_CAN5_MAX_MB_NUM             (96U)
/* @brief Maximum number of Message Buffers supported for payload size 8 for CAN6 */
#define FEATURE_CAN6_MAX_MB_NUM             (96U)
/* @brief Maximum number of Message Buffers supported for payload size 8 for CAN7 */
#define FEATURE_CAN7_MAX_MB_NUM             (96U)
/* @brief Maximum number of Message Buffers supported for payload size 8 for any of the CAN instances */
#define FEATURE_CAN_MAX_MB_NUM              (96U)
/* @brief Array of maximum number of Message Buffers supported for payload size 8 for all the CAN instances */
#define FEATURE_CAN_MAX_MB_NUM_ARRAY        { FEATURE_CAN0_MAX_MB_NUM, \
                                              FEATURE_CAN1_MAX_MB_NUM, \
                                              FEATURE_CAN2_MAX_MB_NUM, \
                                              FEATURE_CAN3_MAX_MB_NUM, \
                                              FEATURE_CAN4_MAX_MB_NUM, \
                                              FEATURE_CAN5_MAX_MB_NUM, \
                                              FEATURE_CAN6_MAX_MB_NUM, \
                                              FEATURE_CAN7_MAX_MB_NUM }
/* @brief Has PE clock source select (bit field CAN_CTRL1[CLKSRC]). */
#define FEATURE_CAN_HAS_PE_CLKSRC_SELECT            (1)
/* @brief Has Pretending Networking mode */
#define FEATURE_CAN_HAS_PRETENDED_NETWORKING        (1)
/* @brief Has Stuff Bit Count Enable Bit */
#define FEATURE_CAN_HAS_STFCNTEN_ENABLE             (0)
/* @brief Has ISO CAN FD Enable Bit */
#define FEATURE_CAN_HAS_ISOCANFDEN_ENABLE           (1)
/* @brief Has Message Buffer Data Size Region 1 */
#define FEATURE_CAN_HAS_MBDSR1                      (1)
/* @brief Has Message Buffer Data Size Region 2 */
#define FEATURE_CAN_HAS_MBDSR2                      (1)
/* @brief Has Supervisor Mode MCR[SUPV]*/
#define FEATURE_CAN_HAS_SUPV             	        (1)
/* @brief Has DMA enable (bit field MCR[DMA]). */
#define FEATURE_CAN_HAS_DMA_ENABLE                  (1)
/* @brief DMA hardware requests for all FlexCAN instances */
#define FEATURE_CAN_EDMA_REQUESTS           { EDMA_REQ_FlexCAN_0, EDMA_REQ_FlexCAN_1, \
                                              EDMA_REQ_FlexCAN_2, EDMA_REQ_FlexCAN_3, \
                                              EDMA_REQ_FlexCAN_4, EDMA_REQ_FlexCAN_5, \
                                              EDMA_REQ_FLEXCAN_6, EDMA_REQ_FlexCAN_7 }
/* @brief Maximum number of Message Buffers IRQs */
#define FEATURE_CAN_MB_IRQS_MAX_COUNT       (7U)
/* @brief Has Wake Up Irq channels (CAN_Wake_Up_IRQS_CH_COUNT > 0u) */
#define FEATURE_CAN_HAS_WAKE_UP_IRQ         (1U)
/* @brief Message Buffers IRQs */
#define FEATURE_CAN_MB_IRQS                 { CAN_ORed_00_03_MB_IRQS, \
                                              CAN_ORed_04_07_MB_IRQS, \
                                              CAN_ORed_08_11_MB_IRQS, \
                                              CAN_ORed_12_15_MB_IRQS, \
                                              CAN_ORed_16_31_MB_IRQS, \
                                              CAN_ORed_32_63_MB_IRQS, \
                                              CAN_ORed_64_95_MB_IRQS }
/*! @brief FlexCAN Embedded RAM address offset */
#define FEATURE_CAN_RAM_OFFSET              (0x00000080u)
/* @brief Has Self Wake Up mode */
#define FEATURE_CAN_HAS_SELF_WAKE_UP        (0)
/* @brief Has Flexible Data Rate */
#define FEATURE_CAN_HAS_FD                  (1)
/* @brief The list contains definitions of the FD feature support on all instances */
#define FEATURE_CAN_INSTANCES_HAS_FD        {true, true, true, true, true, true, true, true}
/* @brief Clock name for the PE oscillator clock source */
#define FEATURE_CAN_PE_OSC_CLK_NAME         FXOSC_CLK
/* @bried FlexCAN has Detection And Correction of Memory Errors */
#define FEATURE_CAN_HAS_MEM_ERR_DET			(0)

/* CRC module features */

/* @brief CRC module use for C55. */
#define FEATURE_CRC_DRIVER_HARD_POLYNOMIAL
/* @brief Default CRC read transpose */
#define FEATURE_CRC_DEFAULT_READ_TRANSPOSE      false
/* @brief Default CRC write transpose */
#define FEATURE_CRC_DEFAULT_WRITE_TRANSPOSE     CRC_TRANSPOSE_BITS
/* @brief Default CRC bit mode polynomial */
#define FEATURE_CRC_DEFAULT_POLYNOMIAL          CRC_BITS_16_CCITT
/* @brief Default seed value is 0xFFFFU */
#define FEATURE_CRC_DEFAULT_SEED                (0xFFFFU)
/* @brief CRC-8-H2F Autosar polynomial support */
#define FEATURE_CRC_BITS_8_H2F                  (1U)

/* EMIOS module features */

/* @brief eMIOS disable channel register. */
#define FEATURE_EMIOS_UC_DISABLE
/* @brief eMIOS prescaler clock select bits. */
#define FEATURE_EMIOS_PRESCALER_SELECT_BITS
/* @brief EMIOS has channel pair in the IRQ interrupt. */
#define FEATURE_EMIOS_CHANNELS_PER_IRQ          (2U)
/* @brief EMIOS number channels maximum. */
#define FEATURE_EMIOS_CHANNEL_MAX_COUNT         (32U)
/* @brief EMIOS Output Pulse-Width Modulation with Trigger. */
#define FEATURE_EMIOS_MODE_OPWMT_SUPPORT        (1U)
/* @brief EMIOS channels and counter buses select. */
#define FEATURE_EMIOS_BUS_A_SELECT              (1U)
#define FEATURE_EMIOS_BUS_B_SELECT              (1U)
#define FEATURE_EMIOS_BUS_C_SELECT              (1U)
#define FEATURE_EMIOS_BUS_D_SELECT              (1U)
#define FEATURE_EMIOS_BUS_E_SELECT              (1U)
#define FEATURE_EMIOS_BUS_F_SELECT              (1U)
/* @brief EMIOS channels and counter buses offset. */
#define FEATURE_EMIOS_BUS_B_SELECT_OFFSET(x)    (x)
#define FEATURE_EMIOS_BUS_C_SELECT_OFFSET(x)    (x)
#define FEATURE_EMIOS_BUS_D_SELECT_OFFSET(x)    (x)
#define FEATURE_EMIOS_BUS_E_SELECT_OFFSET(x)    (x)
/* @brief EMIOS number of channels available. */
#define FEATURE_EMIOS_CH_7_0_ENABLE             (1U)
#define FEATURE_EMIOS_CH_15_8_ENABLE            (1U)
#define FEATURE_EMIOS_CH_23_16_ENABLE           (1U)
#define FEATURE_EMIOS_CH_31_24_ENABLE           (1U)
#define FEATURE_EMIOS_CH_COUNT                  ((FEATURE_EMIOS_CH_7_0_ENABLE   * 8U) + \
                                                 (FEATURE_EMIOS_CH_15_8_ENABLE  * 8U) + \
                                                 (FEATURE_EMIOS_CH_23_16_ENABLE * 8U) + \
                                                 (FEATURE_EMIOS_CH_31_24_ENABLE * 8U))
/** Interrupt vectors for the eMIOS peripheral type */
#define eMIOS_IRQS                                { { EMIOS0_00_01_IRQn, EMIOS0_02_03_IRQn, EMIOS0_04_05_IRQn, EMIOS0_06_07_IRQn, EMIOS0_08_09_IRQn, EMIOS0_10_11_IRQn, EMIOS0_12_13_IRQn, EMIOS0_14_15_IRQn, EMIOS0_16_17_IRQn, EMIOS0_18_19_IRQn, EMIOS0_20_21_IRQn, EMIOS0_22_23_IRQn, EMIOS0_24_25_IRQn, EMIOS0_26_27_IRQn, EMIOS0_28_29_IRQn, EMIOS0_30_31_IRQn }, \
                                                    { EMIOS1_00_01_IRQn, EMIOS1_02_03_IRQn, EMIOS1_04_05_IRQn, EMIOS1_06_07_IRQn, EMIOS1_08_09_IRQn, EMIOS1_10_11_IRQn, EMIOS1_12_13_IRQn, EMIOS1_14_15_IRQn, EMIOS1_16_17_IRQn, EMIOS1_18_19_IRQn, EMIOS1_20_21_IRQn, EMIOS1_22_23_IRQn, EMIOS1_24_25_IRQn, EMIOS1_26_27_IRQn, EMIOS1_28_29_IRQn, EMIOS1_30_31_IRQn }, \
                                                    { EMIOS2_00_01_IRQn, EMIOS2_02_03_IRQn, EMIOS2_04_05_IRQn, EMIOS2_06_07_IRQn, EMIOS2_08_09_IRQn, EMIOS2_10_11_IRQn, EMIOS2_12_13_IRQn, EMIOS2_14_15_IRQn, EMIOS2_16_17_IRQn, EMIOS2_18_19_IRQn, EMIOS2_20_21_IRQn, EMIOS2_22_23_IRQn, EMIOS2_24_25_IRQn, EMIOS2_26_27_IRQn, EMIOS2_28_29_IRQn, EMIOS2_30_31_IRQn } }

/* PWMPAL module features */
#define FEATURE_PWMPAL_EMIOS_HAS_CHANNEL_MAPPING    (0)

/* LINFlexD module features */

/* @brief LINFlexD separate interrupt lines for rx/tx/error. */
#define FEATURE_LINFLEXD_RX_TX_ERR_INT_LINES
/* @brief Clock names for LINFlexD */
#define LINFLEXD_CLOCK_NAMES {LIN0_CLK, LIN1_CLK, LIN2_CLK, LIN3_CLK, LIN4_CLK, LIN5_CLK, LIN6_CLK, LIN7_CLK, LIN8_CLK, \
                              LIN9_CLK, LIN10_CLK, LIN11_CLK, LIN12_CLK, LIN13_CLK, LIN14_CLK, LIN15_CLK, LIN16_CLK, LIN17_CLK}
/* @brief Address of the least significant byte in a 32-bit register (depends on endianess) */
#define FEATURE_LINFLEXD_LSB_ADDR(reg)  ((uint32_t)(&(reg)) + 3U)
/* @brief Address of the least significant word in a 32-bit register (depends on endianess) */
#define FEATURE_LINFLEXD_LSW_ADDR(reg)  ((uint32_t)(&(reg)) + 2U)
/* @brief LINFlexD instances have different memory maps, depending on the number of filters implemented */
#define FEATURE_LINFLEXD_HAS_DIFFERENT_MEM_MAP
/* @brief LINFlexD register layout with 0 filters implemented (instances 1-17) */
typedef struct {
  __IO uint32_t LINCR1;                            /**< LIN Control Register 1, offset: 0x0 */
  __IO uint32_t LINIER;                            /**< LIN Interrupt enable register, offset: 0x4 */
  __IO uint32_t LINSR;                             /**< LIN Status Register, offset: 0x8 */
  __IO uint32_t LINESR;                            /**< LIN Error Status Register, offset: 0xC */
  __IO uint32_t UARTCR;                            /**< UART Mode Control Register, offset: 0x10 */
  __IO uint32_t UARTSR;                            /**< UART Mode Status Register, offset: 0x14 */
  __IO uint32_t LINTCSR;                           /**< LIN Time-Out Control Status Register, offset: 0x18 */
  __IO uint32_t LINOCR;                            /**< LIN Output Compare Register, offset: 0x1C */
  __IO uint32_t LINTOCR;                           /**< LIN Time-Out Control Register, offset: 0x20 */
  __IO uint32_t LINFBRR;                           /**< LIN Fractional Baud Rate Register, offset: 0x24 */
  __IO uint32_t LINIBRR;                           /**< LIN Integer Baud Rate Register, offset: 0x28 */
  __IO uint32_t LINCFR;                            /**< LIN Checksum Field Register, offset: 0x2C */
  __IO uint32_t LINCR2;                            /**< LIN Control Register 2, offset: 0x30 */
  __IO uint32_t BIDR;                              /**< Buffer Identifier Register, offset: 0x34 */
  __IO uint32_t BDRL;                              /**< Buffer Data Register Least Significant, offset: 0x38 */
  __IO uint32_t BDRM;                              /**< Buffer Data Register Most Significant, offset: 0x3C */
  __IO uint32_t IFER;                              /**< Identifier Filter Enable Register, offset: 0x40 */
  __I  uint32_t IFMI;                              /**< Identifier Filter Match Index, offset: 0x44 */
  __IO uint32_t IFMR;                              /**< Identifier Filter Mode Register, offset: 0x48 */
  __IO uint32_t GCR;                               /**< Global Control Register, offset: 0x8C */
  __IO uint32_t UARTPTO;                           /**< UART Preset Timeout Register, offset: 0x90 */
  __I  uint32_t UARTCTO;                           /**< UART Current Timeout Register, offset: 0x94 */
  __IO uint32_t DMATXE;                            /**< DMA Tx Enable Register, offset: 0x98 */
  __IO uint32_t DMARXE;                            /**< DMA Rx Enable Register, offset: 0x9C */
} LINFlexD_0IFCR_Type;
/* @brief LINFlexD "instance-implemented filters" mapping */
#define FEATURE_LINFLEXD_INST_HAS_IFCR {true, false, false, false, false, false, false, false, false, \
                                        false, false, false, false, false, false, false, false, false}
/* @brief LINFlexD DMA support */
#define FEATURE_LINFLEXD_HAS_DMA_ENABLED
/* @brief LINFlexD DMA enabled instances */
#define FEATURE_LINFLEXD_INST_HAS_DMA {true, true, false, false, false, false, false, false, false, \
                                       false, false, false, false, false, false, false, false, false}
/** Interrupt vectors for the LINFlexD */
#define LINFLEXD_RX_IRQS {LINFLEXD0_RX_IRQn, LINFLEXD1_RX_IRQn, LINFLEXD2_RX_IRQn, \
                          LINFLEXD3_RX_IRQn, LINFLEXD4_RX_IRQn, LINFLEXD5_RX_IRQn, \
                          LINFLEXD6_RX_IRQn, LINFLEXD7_RX_IRQn, LINFLEXD8_RX_IRQn, \
                          LINFLEXD9_RX_IRQn, LINFLEXD10_RX_IRQn, LINFLEXD11_RX_IRQn, \
                          LINFLEXD12_RX_IRQn, LINFLEXD13_RX_IRQn, LINFLEXD14_RX_IRQn, \
                          LINFLEXD15_RX_IRQn, LINFLEXD16_RX_IRQn, LINFLEXD17_RX_IRQn}
#define LINFLEXD_TX_IRQS {LINFLEXD0_TX_IRQn, LINFLEXD1_TX_IRQn, LINFLEXD2_TX_IRQn, \
                          LINFLEXD3_TX_IRQn, LINFLEXD4_TX_IRQn, LINFLEXD5_TX_IRQn, \
                          LINFLEXD6_TX_IRQn, LINFLEXD7_TX_IRQn, LINFLEXD8_TX_IRQn, \
                          LINFLEXD9_TX_IRQn, LINFLEXD10_TX_IRQn, LINFLEXD11_TX_IRQn, \
                          LINFLEXD12_TX_IRQn, LINFLEXD13_TX_IRQn, LINFLEXD14_TX_IRQn, \
                          LINFLEXD15_TX_IRQn, LINFLEXD16_TX_IRQn, LINFLEXD17_TX_IRQn}
#define LINFLEXD_ERR_IRQS {LINFLEXD0_ERR_IRQn, LINFLEXD1_ERR_IRQn, LINFLEXD2_ERR_IRQn, \
                           LINFLEXD3_ERR_IRQn, LINFLEXD4_ERR_IRQn, LINFLEXD5_ERR_IRQn, \
                           LINFLEXD6_ERR_IRQn, LINFLEXD7_ERR_IRQn, LINFLEXD8_ERR_IRQn, \
                           LINFLEXD9_ERR_IRQn, LINFLEXD10_ERR_IRQn, LINFLEXD11_ERR_IRQn, \
                           LINFLEXD12_ERR_IRQn, LINFLEXD13_ERR_IRQn, LINFLEXD14_ERR_IRQn, \
                           LINFLEXD15_ERR_IRQn, LINFLEXD16_ERR_IRQn, LINFLEXD17_ERR_IRQn}

/* DMA module features */

/* @brief DMA hardware version 2. */
#define FEATURE_DMA_HWV2
/* @brief Number of DMA channels. */
#define FEATURE_DMA_CHANNELS (32U)
/* @brief Number of DMA virtual channels. */
#define FEATURE_DMA_VIRTUAL_CHANNELS (FEATURE_DMA_CHANNELS * DMA_INSTANCE_COUNT)
/* @brief Number of DMA interrupt lines. */
#define FEATURE_DMA_CHANNELS_INTERRUPT_LINES (32U)
/* @brief Number of DMA virtual interrupt lines. */
#define FEATURE_DMA_VIRTUAL_CHANNELS_INTERRUPT_LINES ((uint32_t)FEATURE_DMA_CHANNELS_INTERRUPT_LINES * (uint32_t)DMA_INSTANCE_COUNT)
/* @brief Number of DMA error interrupt lines. */
#define FEATURE_DMA_ERROR_INTERRUPT_LINES (1U)
/* @brief Number of DMA virtual error interrupt lines. */
#define FEATURE_DMA_VIRTUAL_ERROR_INTERRUPT_LINES ((uint32_t)FEATURE_DMA_ERROR_INTERRUPT_LINES * (uint32_t)DMA_INSTANCE_COUNT)
/* @brief DMA module has error interrupt. */
#define FEATURE_DMA_HAS_ERROR_IRQ
/* @brief DMA module separate interrupt lines for each channel */
#define FEATURE_DMA_SEPARATE_IRQ_LINES_PER_CHN
/* @brief Conversion from channel index to DCHPRI index. */
#define FEATURE_DMA_CHN_TO_DCHPRI_INDEX(x) (x)
/* @brief DMA channel groups count. */
#define FEATURE_DMA_CHANNEL_GROUP_COUNT (2U)
/* @brief Clock name for DMA */
#define FEATURE_DMA_CLOCK_NAMES {DMA0_CLK}
/* @brief Macros defined for compatibility with ARM platforms */
#define DMA_TCD_CITER_ELINKYES_CITER_LE_MASK   DMA_TCD_CITER_ELINKYES_CITER_MASK
#define DMA_TCD_CITER_ELINKYES_CITER_LE_SHIFT  DMA_TCD_CITER_ELINKYES_CITER_SHIFT
#define DMA_TCD_CITER_ELINKYES_CITER_LE_WIDTH  DMA_TCD_CITER_ELINKYES_CITER_WIDTH
#define DMA_TCD_CITER_ELINKYES_CITER_LE(x)     DMA_TCD_CITER_ELINKYES_CITER(x)
/* @brief DMA channel width based on number of TCDs: 2^N, N=4,5,... */
#define FEATURE_DMA_CH_WIDTH (5U)
/* @brief DMA channel to instance */
#define FEATURE_DMA_VCH_TO_INSTANCE(x) 	((x) >> (uint32_t)FEATURE_DMA_CH_WIDTH)
/* @brief DMA virtual channel to channel */
#define FEATURE_DMA_VCH_TO_CH(x)        ((x) & ((uint32_t)FEATURE_DMA_CHANNELS - 1U))
/* @brief DMA supports the following particular transfer size: */
#define FEATURE_DMA_TRANSFER_SIZE_8B
#define FEATURE_DMA_TRANSFER_SIZE_32B

 /** Number of interrupt vector arrays for the DMA module. */
#define DMA_IRQS_ARR_COUNT                       (2u)
 /** Number of interrupt channels for the CHN type of DMA module. */
#define DMA_CHN_IRQS_CH_COUNT                    (32u)
 /** Number of interrupt channels for the ERROR type of DMA module. */
#define DMA_ERROR_IRQS_CH_COUNT                  (1u)
/** Interrupt vectors for the DMA peripheral type */
#define DMA_CHN_IRQS                             { DMA0_IRQn, DMA1_IRQn, DMA2_IRQn, DMA3_IRQn, DMA4_IRQn, DMA5_IRQn, DMA6_IRQn, DMA7_IRQn, DMA8_IRQn, DMA9_IRQn, DMA10_IRQn, DMA11_IRQn, DMA12_IRQn, DMA13_IRQn, DMA14_IRQn, DMA15_IRQn, DMA16_IRQn, DMA17_IRQn, DMA18_IRQn, DMA19_IRQn, DMA20_IRQn, DMA21_IRQn, DMA22_IRQn, DMA23_IRQn, DMA24_IRQn, DMA25_IRQn, DMA26_IRQn, DMA27_IRQn, DMA28_IRQn, DMA29_IRQn, DMA30_IRQn, DMA31_IRQn }
#define DMA_ERROR_IRQS                           { DMA_Error_IRQn }

/* DMAMUX module features */

/* @brief DMAMUX peripheral is available in silicon. */
#define FEATURE_DMAMUX_AVAILABLE
/* @brief Number of DMA channels. */
#define FEATURE_DMAMUX_CHANNELS (16U)
/* @brief Has the periodic trigger capability */
#define FEATURE_DMAMUX_HAS_TRIG (1)
/* @brief Conversion from request source to the actual DMAMUX channel */
#define FEATURE_DMAMUX_REQ_SRC_TO_CH(x) ((x) & DMAMUX_CHCFG_SOURCE_MASK)
/* @brief Mapping between request source and DMAMUX instance */
#define FEATURE_DMAMUX_REQ_SRC_TO_INSTANCE(x) (((uint8_t)x) >> (uint8_t)DMAMUX_CHCFG_SOURCE_WIDTH)
/* @brief Conversion from eDMA channel index to DMAMUX channel. */
#define FEATURE_DMAMUX_DMA_CH_TO_CH(x) ((x) & (FEATURE_DMAMUX_CHANNELS - 1U))
/* @brief Conversion from DMAMUX channel DMAMUX register index. */
#define FEATURE_DMAMUX_CHN_REG_INDEX(x) (x)
/* @brief Clock names for DMAMUX */
#define FEATURE_DMAMUX_CLOCK_NAMES {DMAMUX0_CLK, DMAMUX1_CLK}
/*!
 * @brief Structure for the DMA hardware request
 *
 * Defines the structure for the DMA hardware request collections. The user can configure the
 * hardware request into DMAMUX to trigger the DMA transfer accordingly. The index
 * of the hardware request varies according  to the to SoC.
 */
typedef enum {
    EDMA_REQ_MUX_0_DISABLED = 0U,
    EDMA_REQ_ADC_0_MUX0 = 1U,
    EDMA_REQ_ADC_1_MUX0 = 2U,
    EDMA_REQ_CMP_0 = 3U,
    EDMA_REQ_BCTU_0 = 4U,
    EDMA_REQ_FlexCAN_0 = 5U,
    EDMA_REQ_FlexCAN_2 = 7U,
    EDMA_REQ_FlexCAN_4 = 9U,
    EDMA_REQ_SPI_0_TX = 12U,
    EDMA_REQ_SPI_0_RX = 13U,
    EDMA_REQ_SPI_0_CMD = 14U,
    EDMA_REQ_SPI_2_TX = 15U,
    EDMA_REQ_SPI_2_RX = 16U,
    EDMA_REQ_SPI_2_CMD = 17U,
    EDMA_REQ_SPI_4_TX = 18U,
    EDMA_REQ_SPI_4_RX = 19U,
    EDMA_REQ_SPI_4_CMD = 20U,
    EDMA_REQ_DSPI_0_TX = 21U,
    EDMA_REQ_DSPI_0_RX = 22U,
    EDMA_REQ_DSPI_0_CMD = 23U,
    EDMA_REQ_DSPI_0_DSI = 24U,
    EDMA_REQ_DSPI_2_TX = 25U,
    EDMA_REQ_DSPI_2_RX = 26U,
    EDMA_REQ_DSPI_2_CMD = 27U,
    EDMA_REQ_DSPI_2_DSI = 28U,
    EDMA_REQ_LIN_0_TX = 29U,
    EDMA_REQ_LIN_0_RX = 30U,
    EDMA_REQ_eMIOS_0_CH_A = 31U,
    EDMA_REQ_eMIOS_0_CH_B = 32U,
    EDMA_REQ_eMIOS_0_CH_C = 33U,
    EDMA_REQ_eMIOS_0_CH_D = 34U,
    EDMA_REQ_eMIOS_1_CH_A = 35U,
    EDMA_REQ_eMIOS_1_CH_B = 36U,
    EDMA_REQ_eMIOS_1_CH_C = 37U,
    EDMA_REQ_eMIOS_1_CH_D = 38U,
    EDMA_REQ_uSDHC = 39U,
    EDMA_REQ_I2C_0_TX = 40U,
    EDMA_REQ_I2C_0_RX = 41U,
    EDMA_REQ_I2C_2_TX = 42U,
    EDMA_REQ_I2C_2_RX = 43U,
    EDMA_REQ_CMP_2 = 44U,
    EDMA_REQ_FLEXCAN_6 = 45U,
    EDMA_REQ_eMIOS_2_CH_A = 47U,
    EDMA_REQ_eMIOS_2_CH_B = 48U,
    EDMA_REQ_eMIOS_2_CH_C = 49U,
    EDMA_REQ_eMIOS_2_CH_D = 50U,
    EDMA_REQ_SAI_0_TX = 51U,
    EDMA_REQ_SAI_0_RX = 52U,
    EDMA_REQ_SAI_2_TX = 53U,
    EDMA_REQ_SAI_2_RX = 54U,
    EDMA_REQ_ENET_MAC0_TIMER_CH_0 = 55U,
    EDMA_REQ_ENET_MAC0_TIMER_CH_1 = 56U,
    EDMA_REQ_ENET_MAC0_TIMER_CH_2 = 57U,
    EDMA_REQ_ENET_SWITCH_XLEARN_AVAIL = 59U,
    EDMA_REQ_FCCU = 61U,
    EDMA_REQ_MUX_0_ALWAYS_ENABLED_0 = 62U,
    EDMA_REQ_MUX_0_ALWAYS_ENABLED_1 = 63U,
    EDMA_REQ_MUX_1_DISABLED = 64U,
    EDMA_REQ_ADC_0_MUX1 = 65U,
    EDMA_REQ_ADC_1_MUX1 = 66U,
    EDMA_REQ_CMP_1 = 67U,
    EDMA_REQ_BCTU_1 = 68U,
    EDMA_REQ_FlexCAN_1 = 69U,
    EDMA_REQ_FlexCAN_3 = 71U,
    EDMA_REQ_FlexCAN_5 = 73U,
    EDMA_REQ_SPI_1_TX = 76U,
    EDMA_REQ_SPI_1_RX = 77U,
    EDMA_REQ_SPI_1_CMD = 78U,
    EDMA_REQ_SPI_3_TX = 79U,
    EDMA_REQ_SPI_3_RX = 80U,
    EDMA_REQ_SPI_3_CMD = 81U,
    EDMA_REQ_SPI_5_TX = 82U,
    EDMA_REQ_SPI_5_RX = 83U,
    EDMA_REQ_SPI_5_CMD = 84U,
    EDMA_REQ_DSPI_1_TX = 85U,
    EDMA_REQ_DSPI_1_RX = 86U,
    EDMA_REQ_DSPI_1_CMD = 87U,
    EDMA_REQ_DSPI_1_DSI = 88U,
    EDMA_REQ_DSPI_3_TX = 89U,
    EDMA_REQ_DSPI_3_RX = 90U,
    EDMA_REQ_DSPI_3_CMD = 91U,
    EDMA_REQ_DSPI_3_DSI = 92U,
    EDMA_REQ_LIN_1_TX = 93U,
    EDMA_REQ_LIN_1_RX = 94U,
    EDMA_REQ_eMIOS_0_CH_E = 95U,
    EDMA_REQ_eMIOS_0_CH_F = 96U,
    EDMA_REQ_eMIOS_0_CH_G = 97U,
    EDMA_REQ_eMIOS_0_CH_H = 98U,
    EDMA_REQ_eMIOS_1_CH_E = 99U,
    EDMA_REQ_eMIOS_1_CH_F = 100U,
    EDMA_REQ_eMIOS_1_CH_G = 101U,
    EDMA_REQ_eMIOS_1_CH_H = 102U,
    EDMA_REQ_I2C_1_TX = 103U,
    EDMA_REQ_I2C_1_RX = 104U,
    EDMA_REQ_I2C_3_TX = 105U,
    EDMA_REQ_I2C_3_RX = 106U,
    EDMA_REQ_FlexCAN_7 = 107U,
    EDMA_REQ_eMIOS_2_CH_E = 109U,
    EDMA_REQ_eMIOS_2_CH_F = 110U,
    EDMA_REQ_eMIOS_2_CH_G = 111U,
    EDMA_REQ_eMIOS_2_CH_H = 112U,
    EDMA_REQ_SAI_1_TX = 113U,
    EDMA_REQ_SAI_1_RX = 114U,
    EDMA_REQ_ENET_MAC1_TIMER_CH_0 = 115U,
    EDMA_REQ_ENET_MAC1_TIMER_CH_1 = 116U,
    EDMA_REQ_ENET_MAC1_TIMER_CH_2 = 117U,
    EDMA_REQ_MUX_1_ALWAYS_ENABLED_0 = 126U,
    EDMA_REQ_MUX_1_ALWAYS_ENABLED_1 = 127U
} dma_request_source_t;


/* HSM module features */

/* @brief HSM to HOST interface registers base address. */
#define HSM_BASE                               (0xFFF30000U)

/* @brief Slow IRC trimmed clock frequency(128KHz). */
#define FEATURE_IRCOSC0_FREQ (128000U)

/* @brief Fast IRC trimmed clock frequency(16MHz). */
#define FEATURE_IRCOSC1_FREQ  (16000000U)

/* @brief Slow XOSC clock frequency(32KHz). */
#define FEATURE_XOSC0_FREQ (32768U)

/* @brief Fast XOSC clock frequency(40MHz). */
#define FEATURE_XOSC1_FREQ  (40000000U)

/* @brief Fast ENET_RMII clock frequency(50MHz). */
#define FEATURE_ENET_RMII0_FREQ  (50000000U)

/* @brief LFAST_SYS_PIN source selector.
   0U -  No LFAST module */
#define FEATURE_LFAST_SOURCE_SYS_PIN    (0U)

/* @brief Define identifiers of auxiliary clock selectors */
#define NO_AC     0U
#define AC0__SC   1U
#define AC1__SC   2U
#define AC2__SC   3U
#define AC3__SC   4U
#define AC4__SC   5U
#define AC5__SC   6U
#define AC6__SC   7U
#define AC7__SC   8U
#define AC8__SC   9U
#define AC9__SC   10U
#define AC10__SC  11U
#define AC11__SC  12U
#define AC12__SC  13U
#define AC13__SC  14U
#define AC14__SC  15U
#define AC15__SC  16U
#define AC0__DC0  17U
#define AC0__DC1  18U
#define AC0__DC2  19U
#define AC0__DC3  20U
#define AC0__DC4  21U
#define AC1__DC0  22U
#define AC1__DC1  23U
#define AC1__DC2  24U
#define AC1__DC3  25U
#define AC2__DC0  26U
#define AC2__DC1  27U
#define AC2__DC2  28U
#define AC2__DC3  29U
#define AC3__DC0  30U
#define AC3__DC1  40U
#define AC3__DC2  41U
#define AC3__DC3  42U
#define AC4__DC0  43U
#define AC4__DC1  44U
#define AC4__DC2  45U
#define AC4__DC3  46U
#define AC5__DC0  47U
#define AC5__DC1  48U
#define AC5__DC2  49U
#define AC5__DC3  50U
#define AC6__DC0  51U
#define AC6__DC1  52U
#define AC6__DC2  53U
#define AC6__DC3  54U
#define AC7__DC0  55U
#define AC7__DC1  56U
#define AC7__DC2  57U
#define AC7__DC3  58U
#define AC8__DC0  59U
#define AC8__DC1  60U
#define AC8__DC2  61U
#define AC8__DC3  62U
#define AC9__DC0  63U
#define AC9__DC1  64U
#define AC9__DC2  65U
#define AC9__DC3  66U
#define AC10__DC0 67U
#define AC10__DC1 68U
#define AC10__DC2 69U
#define AC10__DC3 70U
#define AC11__DC0 71U
#define AC11__DC1 72U
#define AC11__DC2 73U
#define AC11__DC3 74U
#define AC12__DC0 75U
#define AC12__DC1 76U
#define AC12__DC2 77U
#define AC12__DC3 78U
#define AC13__DC0 79U
#define AC13__DC1 80U
#define AC13__DC2 81U
#define AC13__DC3 82U
#define AC14__DC0 83U
#define AC14__DC1 84U
#define AC14__DC2 85U
#define AC14__DC3 86U
#define AC15__DC0 87U
#define AC15__DC1 88U
#define AC15__DC2 89U
#define AC15__DC3 90U
#define CLKOUT_1  91U

#define SYSTEM_CLOCK_DIVIDER0_MASK (1U<<0U)
#define SYSTEM_CLOCK_DIVIDER1_MASK (1U<<1U)
#define SYSTEM_CLOCK_DIVIDER2_MASK (1U<<2U)
#define SYSTEM_CLOCK_DIVIDER3_MASK (1U<<3U)
#define SYSTEM_CLOCK_DIVIDER4_MASK (1U<<4U)
#define SYSTEM_CLOCK_DIVIDER5_MASK (1U<<5U)
#define SYSTEM_CLOCK_DIVIDER6_MASK (1U<<6U)

#define CMU_RCDIV_IS_NOT_SUPPORTED        (255U)
#define CMU_RCDIV_IS_SUPPORTED_BY_CMU0    (0U)
#define CMU_RCDIV_IS_SUPPORTED_BY_CMU1    (1U)
#define CMU_RCDIV_IS_SUPPORTED_BY_CMU2    (2U)
#define CMU_RCDIV_IS_SUPPORTED_BY_CMU3    (3U)
#define CMU_RCDIV_IS_SUPPORTED_BY_CMU4    (4U)
#define CMU_RCDIV_IS_SUPPORTED_BY_CMU5    (5U)
#define CMU_RCDIV_IS_SUPPORTED_BY_CMU6    (6U)
#define CMU_RCDIV_IS_SUPPORTED_BY_CMU7    (7U)
#define CMU_RCDIV_IS_SUPPORTED_BY_CMU8    (8U)
#define CMU_RCDIV_IS_SUPPORTED_BY_CMU9    (9U)
#define CMU_RCDIV_IS_SUPPORTED_BY_CMU10   (10U)
#define CMU_RCDIV_IS_SUPPORTED_BY_CMU11   (11U)
#define CMU_RCDIV_IS_SUPPORTED_BY_CMU12   (12U)

/* @brief List of the configurable system clock dividers. */
#define SYSTEM_CLOCK_DIVIDERS  (SYSTEM_CLOCK_DIVIDER0_MASK | SYSTEM_CLOCK_DIVIDER1_MASK | SYSTEM_CLOCK_DIVIDER2_MASK | SYSTEM_CLOCK_DIVIDER5_MASK)

/* @brief PLL input reference. */
#define FEATURE_PLL0_INPUT_REFERENCE  AC5__SC
#define FEATURE_PLL1_INPUT_REFERENCE  NO_AC

/* @brief PLL reduced frequency divider version. */
#define FEATURE_PLL_REDUCED_FREQ_DIV_VERSION (1U)

/* @brief FLEXCAN0 configurable interface clock. */
#define FEATURE_FLEXCAN0_CLK_CONFIGURABLE_INTERFACE_CLOCK (1U)

/* @brief PBRIDGEx system clock divider index. */
#define FEATURE_PBRIDGEx_CLK_SYSTEM_CLOCK_DIVIDER_INDEX (0U)

/* @brief PLL0_PHI1 reference entry value. */
#define FEATURE_PLL0_PHI1_REFERENCE_ENTRY_VALUE (0U)

/* @brief Synchronous mode for LIN is set using DCF clients */
#define FEATURE_LIN_SYNCHRONOUS_MODE		(0U)

/* @brief CMU reference. */
#define FEATURE_HAS_RCDIV				  CMU_RCDIV_IS_SUPPORTED_BY_CMU0
#define FEATURE_HAS_RCDIV1				  CMU_RCDIV_IS_NOT_SUPPORTED
#define FIRST_CMU						  CMU
#define CMU_RESET_DIVIDER_VALUE 		  (3U)

/* @brief ENET_RMII reference entry value. */
#define FEATURE_RMII_SOURCE_ENTRY_VALUE (1U)

#define FEATURE_FT_DIS_CHECK_SYSTEM_FREQUENCY   (160000000U)

#define FEATURE_HAS_SIRC_CLK             (1U)
#define FEATURE_HAS_SIRC_CLKS            (0U)
#define FEATURE_HAS_FIRC_CLK             (1U)
#define FEATURE_HAS_FIRC_CLKS            (1U)
#define FEATURE_HAS_IRCOSC_CLK           (0U)
#define FEATURE_HAS_IRCOSC_CLKS          (0U)
#define FEATURE_HAS_SXOSC_CLK            (1U)
#define FEATURE_HAS_SXOSC_CLKS           (0U)
#define FEATURE_HAS_FXOSC_CLK            (1U)
#define FEATURE_HAS_FXOSC_CLKS           (1U)
#define FEATURE_HAS_XOSC_CLK             (0U)
#define FEATURE_HAS_XOSC_CLKS            (0U)
#define FEATURE_HAS_PLL_PHI0_CLK         (1U)
#define FEATURE_HAS_PLL_PHI0_CLKS        (0U)
#define FEATURE_HAS_PLL_PHI1_CLK         (1U)
#define FEATURE_HAS_PLL_PHI1_CLKS        (0U)
#define FEATURE_HAS_PLL0_PHI0_CLK        (0U)
#define FEATURE_HAS_PLL0_PHI0_CLKS       (0U)
#define FEATURE_HAS_PLL0_PHI1_CLK        (0U)
#define FEATURE_HAS_PLL0_PHI1_CLKS       (0U)
#define FEATURE_HAS_PLL1_PHI0_CLK        (0U)
#define FEATURE_HAS_PLL1_PHI0_CLKS       (0U)
#define FEATURE_HAS_PLL1_PHI1_CLK        (0U)
#define FEATURE_HAS_PLL1_PHI1_CLKS       (0U)
#define FEATURE_HAS_SDPLL_CLK            (0U)
#define FEATURE_HAS_SDPLL_CLKS           (0U)
#define FEATURE_HAS_ENET_RMII_CLK        (1U)
#define FEATURE_HAS_ENET_RMII_CLKS       (0U)
#define FEATURE_HAS_SCS_CLK              (1U)
#define FEATURE_HAS_SCS_CLKS             (0U)
#define FEATURE_HAS_S160_CLK             (1U)
#define FEATURE_HAS_S160_CLKS            (0U)
#define FEATURE_HAS_S80_CLK              (1U)
#define FEATURE_HAS_S80_CLKS             (0U)
#define FEATURE_HAS_S40_CLK              (1U)
#define FEATURE_HAS_S40_CLKS             (1U)
#define FEATURE_HAS_F40_CLK              (1U)
#define FEATURE_HAS_F40_CLKS             (1U)
#define FEATURE_HAS_F80_CLK              (1U)
#define FEATURE_HAS_F80_CLKS             (1U)
#define FEATURE_HAS_FS80_CLK             (1U)
#define FEATURE_HAS_FS80_CLKS            (1U)
#define FEATURE_HAS_F20_CLK              (1U)
#define FEATURE_HAS_F20_CLKS             (0U)
#define FEATURE_HAS_PBRIDGEx_CLK         (0U)
#define FEATURE_HAS_PBRIDGEx_CLKS        (0U)
#define FEATURE_HAS_SYS_CLK              (0U)
#define FEATURE_HAS_SYS_CLKS             (0U)
#define FEATURE_HAS_HALFSYS_CLK          (0U)
#define FEATURE_HAS_HALFSYS_CLKS         (0U)
#define FEATURE_HAS_MOTC_CLK             (0U)
#define FEATURE_HAS_MOTC_CLKS            (0U)
#define FEATURE_HAS_PER_CLK              (0U)
#define FEATURE_HAS_PER_CLKS             (0U)
#define FEATURE_HAS_FXBAR_CLK            (0U)
#define FEATURE_HAS_FXBAR_CLKS           (0U)
#define FEATURE_HAS_SXBAR_CLK            (0U)
#define FEATURE_HAS_SXBAR_CLKS           (0U)
#define FEATURE_HAS_DMA_CLK              (0U)
#define FEATURE_HAS_DMA_CLKS             (0U)
#define FEATURE_HAS_CORE0_CLK            (0U)
#define FEATURE_HAS_CORE0_CLKS           (0U)
#define FEATURE_HAS_CORE1_CLK            (0U)
#define FEATURE_HAS_CORE1_CLKS           (0U)
#define FEATURE_HAS_CORE2_CLK            (0U)
#define FEATURE_HAS_CORE2_CLKS           (0U)
#define FEATURE_HAS_ADC_CLKS             (0U)
#define FEATURE_HAS_ADCSD_CLKS           (0U)
#define FEATURE_HAS_DSPI_CLKS            (0U)
#define FEATURE_HAS_DSPIM_CLKS           (0U)
#define FEATURE_HAS_ENET_CLKS            (0U)
#define FEATURE_HAS_ENET_TIME_CLKS       (1U)
#define FEATURE_HAS_EMIOS_CLKS           (0U)
#define FEATURE_HAS_ETPU_CLKS            (0U)
#define FEATURE_HAS_FLEXCAN_CLKS         (0U)
#define FEATURE_HAS_FLEXRAY_CLKS         (0U)
#define FEATURE_HAS_LFAST_CLKS           (0U)
#define FEATURE_HAS_LIN_CLKS             (0U)
#define FEATURE_HAS_RTI_CLKS             (0U)
#define FEATURE_HAS_SDHC_CLKS            (1U)
#define FEATURE_HAS_SENT_CLKS            (0U)
#define FEATURE_HAS_SGEN_CLKS            (0U)
#define FEATURE_HAS_SPI_CLKS             (1U)
#define FEATURE_HAS_SPT_CLKS             (0U)
#define FEATURE_HAS_CLKOUT0_CLKS         (1U)
#define FEATURE_HAS_CLKOUT1_CLKS         (1U)


#define FEATURE_PROTOCOL_CLOCK_FOR_ADC                 NO_AC
#define FEATURE_PROTOCOL_CLOCK_FOR_ADCSD               NO_AC
#define FEATURE_PROTOCOL_CLOCK_FOR_DSPI                NO_AC
#define FEATURE_PROTOCOL_CLOCK_FOR_DSPIM               NO_AC
#define FEATURE_PROTOCOL_CLOCK_FOR_ENET                NO_AC
#define FEATURE_PROTOCOL_CLOCK_FOR_ENET_TIME           AC2__SC
#define FEATURE_PROTOCOL_CLOCK_FOR_EMIOS               NO_AC
#define FEATURE_PROTOCOL_CLOCK_FOR_ETPU                NO_AC
#define FEATURE_PROTOCOL_CLOCK_FOR_FLEXCAN             NO_AC
#define FEATURE_PROTOCOL_CLOCK_FOR_FLEXRAY             NO_AC
#define FEATURE_PROTOCOL_CLOCK_FOR_LFAST               NO_AC
#define FEATURE_PROTOCOL_CLOCK_FOR_LIN                 NO_AC
#define FEATURE_PROTOCOL_CLOCK_FOR_RTI                 NO_AC
#define FEATURE_PROTOCOL_CLOCK_FOR_SDHC                AC4__SC
#define FEATURE_PROTOCOL_CLOCK_FOR_SENT                NO_AC
#define FEATURE_PROTOCOL_CLOCK_FOR_SGEN                NO_AC
#define FEATURE_PROTOCOL_CLOCK_FOR_SPI                 AC8__SC
#define FEATURE_PROTOCOL_CLOCK_FOR_SPT                 NO_AC
#define FEATURE_PROTOCOL_CLOCK_FOR_CLKOUT0             AC6__SC
#define FEATURE_PROTOCOL_CLOCK_FOR_CLKOUT1             AC6__SC
#define FEATURE_INTERFACE_CLOCK_FOR_ADC                NO_AC
#define FEATURE_INTERFACE_CLOCK_FOR_ADCSD              NO_AC
#define FEATURE_INTERFACE_CLOCK_FOR_DSPI               NO_AC
#define FEATURE_INTERFACE_CLOCK_FOR_DSPIM              NO_AC
#define FEATURE_INTERFACE_CLOCK_FOR_ENET               NO_AC
#define FEATURE_INTERFACE_CLOCK_FOR_ENET_TIME          AC2__SC
#define FEATURE_INTERFACE_CLOCK_FOR_EMIOS              NO_AC
#define FEATURE_INTERFACE_CLOCK_FOR_ETPU               NO_AC
#define FEATURE_INTERFACE_CLOCK_FOR_FLEXCAN            AC9__SC
#define FEATURE_INTERFACE_CLOCK_FOR_FLEXRAY            NO_AC
#define FEATURE_INTERFACE_CLOCK_FOR_LFAST              NO_AC
#define FEATURE_INTERFACE_CLOCK_FOR_LIN                NO_AC
#define FEATURE_INTERFACE_CLOCK_FOR_RTI                NO_AC
#define FEATURE_INTERFACE_CLOCK_FOR_SDHC               NO_AC
#define FEATURE_INTERFACE_CLOCK_FOR_SENT               NO_AC
#define FEATURE_INTERFACE_CLOCK_FOR_SGEN               NO_AC
#define FEATURE_INTERFACE_CLOCK_FOR_SPI                NO_AC
#define FEATURE_INTERFACE_CLOCK_FOR_SPT                NO_AC
#define FEATURE_FRACTIONAL_DIVIDER_FOR_ADC             NO_AC
#define FEATURE_FRACTIONAL_DIVIDER_FOR_ADCSD           NO_AC
#define FEATURE_FRACTIONAL_DIVIDER_FOR_DSPI            NO_AC
#define FEATURE_FRACTIONAL_DIVIDER_FOR_DSPIM           NO_AC
#define FEATURE_FRACTIONAL_DIVIDER_FOR_ENET            NO_AC
#define FEATURE_FRACTIONAL_DIVIDER_FOR_ENET_TIME       NO_AC
#define FEATURE_FRACTIONAL_DIVIDER_FOR_EMIOS           NO_AC
#define FEATURE_FRACTIONAL_DIVIDER_FOR_ETPU            NO_AC
#define FEATURE_FRACTIONAL_DIVIDER_FOR_FLEXCAN         NO_AC
#define FEATURE_FRACTIONAL_DIVIDER_FOR_FLEXRAY         NO_AC
#define FEATURE_FRACTIONAL_DIVIDER_FOR_LFAST           NO_AC
#define FEATURE_FRACTIONAL_DIVIDER_FOR_LIN             NO_AC
#define FEATURE_FRACTIONAL_DIVIDER_FOR_RTI             NO_AC
#define FEATURE_FRACTIONAL_DIVIDER_FOR_SDHC            NO_AC
#define FEATURE_FRACTIONAL_DIVIDER_FOR_SENT            NO_AC
#define FEATURE_FRACTIONAL_DIVIDER_FOR_SGEN            NO_AC
#define FEATURE_FRACTIONAL_DIVIDER_FOR_SPI             NO_AC
#define FEATURE_FRACTIONAL_DIVIDER_FOR_SPT             NO_AC
#define FEATURE_FRACTIONAL_DIVIDER_FOR_CLKOUT0         AC6__DC0
#define FEATURE_FRACTIONAL_DIVIDER_FOR_CLKOUT1         CLKOUT_1


/*! @brief Clock names. */
typedef enum {
    /* Clock sources */
    SIRC_CLK                       = 0u,      /*!< SIRC_CLK clock source                  */
    FIRC_CLK                       = 1u,      /*!< FIRC_CLK clock source                  */
    SXOSC_CLK                      = 2u,      /*!< SXOSC_CLK clock source                 */
    FXOSC_CLK                      = 3u,      /*!< FXOSC_CLK clock source                 */
    PLL_PHI0_CLK                   = 4u,      /*!< PLL_PHI0_CLK clock source              */
    PLL_PHI1_CLK                   = 5u,      /*!< PLL_PHI1_CLK clock source              */
    SIRC_UNDIVIDED_CLK             = 6u,      /*!< SIRC_UNDIVIDED_CLK clock source        */
    FIRC_UNDIVIDED_CLK             = 7u,      /*!< FIRC_UNDIVIDED_CLK clock source        */
    SXOSC_UNDIVIDED_CLK            = 8u,      /*!< SXOSC_UNDIVIDED_CLK clock source       */
    FXOSC_UNDIVIDED_CLK            = 9u,      /*!< FXOSC_UNDIVIDED_CLK clock source       */
    ENET_RMII_CLK                  = 10u,     /*!< ENET_RMII_CLK clock source             */
    END_OF_CLK_SOURCES             = 20u,      /*!< End of clock sources                  */
    /* System and common clocks */
    SCS_CLK                        = 21u,      /*!< SCS_CLK common clock                  */
    S160_CLK                       = 22u,      /*!< S160_CLK common clock                 */
    S80_CLK                        = 23u,      /*!< S80_CLK common clock                  */
    S40_CLK                        = 24u,      /*!< S40_CLK common clock                  */
    F40_CLK                        = 25u,      /*!< F40_CLK common clock                  */
    F80_CLK                        = 26u,      /*!< F80_CLK common clock                  */
    FS80_CLK                       = 27u,      /*!< FS80_CLK common clock                 */
    F20_CLK                        = 28u,      /*!< F20_CLK common clock                  */
    CORE_CLK                       = 29u,      /*!< CORE_CLK                              */
    END_OF_SYSTEM_CLKS             = 40u,      /*!< End of common and system clocks       */
    /* CLOCKOUTS */
    CLKOUT0                        = 41u,      /*!< CLKOUT0_CLK common clock              */
    CLKOUT1                        = 42u,      /*!< CLKOUT1_CLK common clock              */
    END_OF_CLOCKOUTS               = 50u,      /*!< End of CLOCKOUTS                      */
    CMP0_CLK                       = 51u,      /*!< CMP0_CLK clock source                 */
    CMP1_CLK                       = 52u,      /*!< CMP1_CLK clock source                 */
    CMP2_CLK                       = 53u,      /*!< CMP2_CLK clock source                 */
    CRC0_CLK                       = 54u,      /*!< CRC0_CLK clock source                 */
    SAI0_CLK                       = 55u,      /*!< SAI0_CLK clock source                 */
    SAI1_CLK                       = 56u,      /*!< SAI1_CLK clock source                 */
    SAI2_CLK                       = 57u,      /*!< SAI2_CLK clock source                 */
    WKPU0_CLK                      = 58u,      /*!< WKPU0_CLK clock source                */
    END_OF_S40_CLKS                = 59u,      /*!< End of S40_CLK clocks                 */
    DSPI0_CLK                      = 60u,      /*!< DSPI0_CLK clock source                */
    DSPI1_CLK                      = 61u,      /*!< DSPI1_CLK clock source                */
    ENET0_CLK                      = 62u,      /*!< ENET0_CLK clock source                */
    ENET1_CLK                      = 63u,      /*!< ENET1_CLK clock source                */
    IIC0_CLK                       = 64u,      /*!< IIC0_CLK clock source                 */
    IIC1_CLK                       = 65u,      /*!< IIC1_CLK clock source                 */
    IIC2_CLK                       = 66u,      /*!< IIC2_CLK clock source                 */
    IIC3_CLK                       = 67u,      /*!< IIC3_CLK clock source                 */
    LIN0_CLK                       = 68u,      /*!< LIN0_CLK clock source                 */
    PIT0_CLK                       = 69u,      /*!< PIT0_CLK clock source                 */
    SPI3_CLK                       = 70u,      /*!< SPI3_CLK clock source                 */
    SPI4_CLK                       = 71u,      /*!< SPI4_CLK clock source                 */
    SPI5_CLK                       = 72u,      /*!< SPI5_CLK clock source                 */
    END_OF_F40_CLKS                = 73u,      /*!< End of F40_CLK clocks                 */
    DSPI2_CLK                      = 74u,      /*!< DSPI2_CLK clock source                */
    DSPI3_CLK                      = 75u,      /*!< DSPI3_CLK clock source                */
    LIN1_CLK                       = 76u,      /*!< LIN1_CLK clock source                 */
    LIN2_CLK                       = 77u,      /*!< LIN2_CLK clock source                 */
    LIN3_CLK                       = 78u,      /*!< LIN3_CLK clock source                 */
    LIN4_CLK                       = 79u,      /*!< LIN4_CLK clock source                 */
    LIN5_CLK                       = 80u,      /*!< LIN5_CLK clock source                 */
    LIN6_CLK                       = 81u,      /*!< LIN6_CLK clock source                 */
    LIN7_CLK                       = 82u,      /*!< LIN7_CLK clock source                 */
    LIN8_CLK                       = 83u,      /*!< LIN8_CLK clock source                 */
    LIN9_CLK                       = 84u,      /*!< LIN9_CLK clock source                 */
    LIN10_CLK                      = 85u,      /*!< LIN10_CLK clock source                */
    LIN11_CLK                      = 86u,      /*!< LIN11_CLK clock source                */
    LIN12_CLK                      = 87u,      /*!< LIN12_CLK clock source                */
    LIN13_CLK                      = 88u,      /*!< LIN13_CLK clock source                */
    LIN14_CLK                      = 89u,      /*!< LIN14_CLK clock source                */
    LIN15_CLK                      = 90u,      /*!< LIN15_CLK clock source                */
    LIN16_CLK                      = 91u,      /*!< LIN16_CLK clock source                */
    LIN17_CLK                      = 92u,      /*!< LIN17_CLK clock source                */
    MLB0_CLK                       = 93u,      /*!< MLB0_CLK clock source                 */
    SPI1_CLK                       = 94u,      /*!< SPI1_CLK clock source                 */
    SPI2_CLK                       = 95u,      /*!< SPI2_CLK clock source                 */
    USBOTG0_CLK                    = 96u,      /*!< USBOTG0_CLK clock source              */
    USBSPH0_CLK                    = 97u,      /*!< USBSPH0_CLK clock source              */
    END_OF_F80_CLKS                = 98u,      /*!< End of F80_CLK clocks                 */
    ADC0_CLK                       = 99u,      /*!< ADC0_CLK clock source                 */
    ADC1_CLK                       = 100u,      /*!< ADC1_CLK clock source                 */
    BCTU0_CLK                      = 101u,      /*!< BCTU0_CLK clock source                */
    DMA0_CLK                       = 102u,      /*!< DMA0_CLK clock source                 */
    DMAMUX0_CLK                    = 103u,      /*!< DMAMUX0_CLK clock source              */
    DMAMUX1_CLK                    = 104u,      /*!< DMAMUX1_CLK clock source              */
    eMIOS0_CLK                     = 105u,      /*!< eMIOS0_CLK clock source               */
    eMIOS1_CLK                     = 106u,      /*!< eMIOS1_CLK clock source               */
    eMIOS2_CLK                     = 107u,      /*!< eMIOS2_CLK clock source               */
    FLEXRAY0_CLK                   = 108u,      /*!< FLEXRAY0_CLK clock source             */
    END_OF_FS80_CLKS               = 109u,      /*!< End of FS80_CLK clocks                */
    ENET0_TIME_CLK                 = 110u,      /*!< ENET0_TIME_CLK clock source           */
    ENET1_TIME_CLK                 = 111u,      /*!< ENET1_TIME_CLK clock source           */
    END_OF_ENET_TIME_CLKS          = 112u,      /*!< End of ENET_TIME_CLK clocks           */
    SDHC0_CLK                      = 113u,      /*!< SDHC0_CLK clock source                */
    END_OF_SDHC_CLKS               = 114u,      /*!< End of SDHC_CLK clocks                */
    SPI0_CLK                       = 115u,      /*!< SPI0_CLK clock source                 */
    END_OF_SPI_CLKS                = 116u,      /*!< End of SPI_CLK clocks                 */
    HSM0_CLK                       = 117u,      /*!< HSM0_CLK clock source                 */
    END_OF_FIRC_CLKS               = 118u,      /*!< End of FIRC_CLK clocks                */
    PITRTI0_CLK                    = 119u,      /*!< PITRTI0_CLK clock source              */
    END_OF_FXOSC_CLKS              = 120u,      /*!< End of FXOSC_CLK clocks               */
    FLEXCAN0_CLK                   = 121u,      /*!< FLEXCAN0_CLK clock source             */
    FLEXCAN1_CLK                   = 122u,      /*!< FLEXCAN1_CLK clock source             */
    FLEXCAN2_CLK                   = 123u,      /*!< FLEXCAN2_CLK clock source             */
    FLEXCAN3_CLK                   = 124u,      /*!< FLEXCAN3_CLK clock source             */
    FLEXCAN4_CLK                   = 125u,      /*!< FLEXCAN4_CLK clock source             */
    FLEXCAN5_CLK                   = 126u,      /*!< FLEXCAN5_CLK clock source             */
    FLEXCAN6_CLK                   = 127u,      /*!< FLEXCAN6_CLK clock source             */
    FLEXCAN7_CLK                   = 128u,      /*!< FLEXCAN7_CLK clock source             */
    MEMU0_CLK                      = 129u,      /*!< MEMU0_CLK clock source                */
    MEMU1_CLK                      = 130u,      /*!< MEMU1_CLK clock source                */
    RTC0_CLK                       = 131u,      /*!< RTC0_CLK clock source                 */
    SIUL0_CLK                      = 132u,      /*!< SIUL0_CLK clock source                */
    END_OF_PERIPHERAL_CLKS         = 133u,      /*!< End of peripheral clocks              */
    CLOCK_NAME_COUNT,
} clock_names_t;

#define MC_ME_INVALID_INDEX  MC_ME_PCTLn_COUNT

  /*! @brief MC_ME clock name mappings
   *  Mappings between clock names and peripheral clock control indexes.
   *  If there is no peripheral clock control index for a clock name,
   *  then the corresponding value is MC_ME_INVALID_INDEX.
   */
#define MC_ME_CLOCK_NAME_MAPPINGS \
{                                                                              \
MC_ME_INVALID_INDEX,                /*!< SIRC clock                                         0  */ \
MC_ME_INVALID_INDEX,                /*!< FIRC clock                                         1  */ \
MC_ME_INVALID_INDEX,                /*!< SXOSC clock                                        2  */ \
MC_ME_INVALID_INDEX,                /*!< FXOSC clock                                        3  */ \
MC_ME_INVALID_INDEX,                /*!< PLL_PHI0 clock                                     4  */ \
MC_ME_INVALID_INDEX,                /*!< PLL_PHI1 clock                                     5  */ \
MC_ME_INVALID_INDEX,                /*!< ENET_RMII clock                                    6  */ \
MC_ME_INVALID_INDEX,                /*!< No clock entry in clock_names_t                    7  */ \
MC_ME_INVALID_INDEX,                /*!< No clock entry in clock_names_t                    8  */ \
MC_ME_INVALID_INDEX,                /*!< No clock entry in clock_names_t                    9  */ \
MC_ME_INVALID_INDEX,                /*!< No clock entry in clock_names_t                    10  */ \
MC_ME_INVALID_INDEX,                /*!< No clock entry in clock_names_t                    11  */ \
MC_ME_INVALID_INDEX,                /*!< No clock entry in clock_names_t                    12  */ \
MC_ME_INVALID_INDEX,                /*!< No clock entry in clock_names_t                    13  */ \
MC_ME_INVALID_INDEX,                /*!< No clock entry in clock_names_t                    14  */ \
MC_ME_INVALID_INDEX,                /*!< No clock entry in clock_names_t                    15  */ \
MC_ME_INVALID_INDEX,                /*!< No clock entry in clock_names_t                    16  */ \
MC_ME_INVALID_INDEX,                /*!< No clock entry in clock_names_t                    17  */ \
MC_ME_INVALID_INDEX,                /*!< No clock entry in clock_names_t                    18  */ \
MC_ME_INVALID_INDEX,                /*!< No clock entry in clock_names_t                    19  */ \
MC_ME_INVALID_INDEX,                /*!< END_OF_CLK_SOURCES                                 20  */  \
MC_ME_INVALID_INDEX,                /*!< SCS_CLK clock                                      21  */ \
MC_ME_INVALID_INDEX,                /*!< S160_CLK clock                                     22  */ \
MC_ME_INVALID_INDEX,                /*!< S80_CLK clock                                      23  */ \
MC_ME_INVALID_INDEX,                /*!< S40_CLK clock                                      24  */ \
MC_ME_INVALID_INDEX,                /*!< F40_CLK clock                                      25  */ \
MC_ME_INVALID_INDEX,                /*!< F80_CLK clock                                      26  */ \
MC_ME_INVALID_INDEX,                /*!< FS80_CLK clock                                     27  */ \
MC_ME_INVALID_INDEX,                /*!< F20_CLK clock                                      28  */ \
MC_ME_INVALID_INDEX,                /*!< No clock entry in clock_names_t                    29  */ \
MC_ME_INVALID_INDEX,                /*!< No clock entry in clock_names_t                    30  */ \
MC_ME_INVALID_INDEX,                /*!< No clock entry in clock_names_t                    31  */ \
MC_ME_INVALID_INDEX,                /*!< No clock entry in clock_names_t                    32  */ \
MC_ME_INVALID_INDEX,                /*!< No clock entry in clock_names_t                    33  */ \
MC_ME_INVALID_INDEX,                /*!< No clock entry in clock_names_t                    34  */ \
MC_ME_INVALID_INDEX,                /*!< No clock entry in clock_names_t                    35  */ \
MC_ME_INVALID_INDEX,                /*!< No clock entry in clock_names_t                    36  */ \
MC_ME_INVALID_INDEX,                /*!< No clock entry in clock_names_t                    37  */ \
MC_ME_INVALID_INDEX,                /*!< No clock entry in clock_names_t                    38  */ \
MC_ME_INVALID_INDEX,                /*!< No clock entry in clock_names_t                    39  */ \
MC_ME_INVALID_INDEX,                /*!< END_OF_SYSTEM_CLOCKS                               40  */  \
MC_ME_INVALID_INDEX,                /*!< CLKOUT0_CLK clock                                  41  */ \
MC_ME_INVALID_INDEX,                /*!< CLKOUT1_CLK clock                                  42  */ \
MC_ME_INVALID_INDEX,                /*!< No clock entry in clock_names_t                    43  */ \
MC_ME_INVALID_INDEX,                /*!< No clock entry in clock_names_t                    44  */ \
MC_ME_INVALID_INDEX,                /*!< No clock entry in clock_names_t                    45  */ \
MC_ME_INVALID_INDEX,                /*!< No clock entry in clock_names_t                    46  */ \
MC_ME_INVALID_INDEX,                /*!< No clock entry in clock_names_t                    47  */ \
MC_ME_INVALID_INDEX,                /*!< No clock entry in clock_names_t                    48  */ \
MC_ME_INVALID_INDEX,                /*!< No clock entry in clock_names_t                    49  */ \
MC_ME_INVALID_INDEX,                /*!< END_OF_CLOCKOUTS                                   50  */  \
MC_ME_PCTL_CMP_0_INDEX,             /*!< CMP0 clock source                                  51 */ \
MC_ME_PCTL_CMP_1_INDEX,             /*!< CMP1 clock source                                  52 */ \
MC_ME_PCTL_CMP_2_INDEX,             /*!< CMP2 clock source                                  53 */ \
MC_ME_PCTL_CRC_INDEX,               /*!< CRC0 clock source                                  54 */ \
MC_ME_PCTL_SAI0_INDEX,              /*!< SAI0 clock source                                  55 */ \
MC_ME_PCTL_SAI1_INDEX,              /*!< SAI1 clock source                                  56 */ \
MC_ME_PCTL_SAI2_INDEX,              /*!< SAI2 clock source                                  57 */ \
MC_ME_PCTL_WKPU_INDEX,              /*!< WKPU0 clock source                                 58 */ \
MC_ME_INVALID_INDEX,                /*!< End of S40 clocks                                  59 */ \
MC_ME_PCTL_DSPI_0_INDEX,            /*!< DSPI0 clock source                                 60 */ \
MC_ME_PCTL_DSPI_1_INDEX,            /*!< DSPI1 clock source                                 61 */ \
MC_ME_PCTL_ENET_INDEX,              /*!< ENET0 clock source                                 62 */ \
MC_ME_PCTL_ENET_INDEX,              /*!< ENET1 clock source                                 63 */ \
MC_ME_PCTL_IIC_0_INDEX,             /*!< IIC0 clock source                                  64 */ \
MC_ME_PCTL_IIC_1_INDEX,             /*!< IIC1 clock source                                  65 */ \
MC_ME_PCTL_IIC_2_INDEX,             /*!< IIC2 clock source                                  66 */ \
MC_ME_PCTL_IIC_3_INDEX,             /*!< IIC3 clock source                                  67 */ \
MC_ME_PCTL_LIN_0_INDEX,             /*!< LIN0 clock source                                  68 */ \
MC_ME_PCTL_PIT_RTI_0_INDEX,         /*!< PIT0 clock source                                  69 */ \
MC_ME_PCTL_SPI3_INDEX,              /*!< SPI3 clock source                                  70 */ \
MC_ME_PCTL_SPI4_INDEX,              /*!< SPI4 clock source                                  71 */ \
MC_ME_PCTL_SPI5_INDEX,              /*!< SPI5 clock source                                  72 */ \
MC_ME_INVALID_INDEX,                /*!< End of F40 clocks                                  73 */ \
MC_ME_PCTL_DSPI_2_INDEX,            /*!< DSPI2 clock source                                 74 */ \
MC_ME_PCTL_DSPI_3_INDEX,            /*!< DSPI3 clock source                                 75 */ \
MC_ME_PCTL_LIN_1_INDEX,             /*!< LIN1 clock source                                  76 */ \
MC_ME_PCTL_LIN_2_INDEX,             /*!< LIN2 clock source                                  77 */ \
MC_ME_PCTL_LIN_3_INDEX,             /*!< LIN3 clock source                                  78 */ \
MC_ME_PCTL_LIN_4_INDEX,             /*!< LIN4 clock source                                  79 */ \
MC_ME_PCTL_LIN_5_INDEX,             /*!< LIN5 clock source                                  80 */ \
MC_ME_PCTL_LIN_6_INDEX,             /*!< LIN6 clock source                                  81 */ \
MC_ME_PCTL_LIN_7_INDEX,             /*!< LIN7 clock source                                  82 */ \
MC_ME_PCTL_LIN_8_INDEX,             /*!< LIN8 clock source                                  83 */ \
MC_ME_PCTL_LIN_9_INDEX,             /*!< LIN9 clock source                                  84 */ \
MC_ME_PCTL_LIN_10_INDEX,            /*!< LIN10 clock source                                 85 */ \
MC_ME_PCTL_LIN_11_INDEX,            /*!< LIN11 clock source                                 86 */ \
MC_ME_PCTL_LIN_12_INDEX,            /*!< LIN12 clock source                                 87 */ \
MC_ME_PCTL_LIN_13_INDEX,            /*!< LIN13 clock source                                 88 */ \
MC_ME_PCTL_LIN_14_INDEX,            /*!< LIN14 clock source                                 89 */ \
MC_ME_PCTL_LIN_15_INDEX,            /*!< LIN15 clock source                                 90 */ \
MC_ME_PCTL_LIN_16_INDEX,            /*!< LIN16 clock source                                 91 */ \
MC_ME_PCTL_LIN_17_INDEX,            /*!< LIN17 clock source                                 92 */ \
MC_ME_PCTL_MLB_INDEX,               /*!< MLB0 clock source                                  93 */ \
MC_ME_PCTL_SPI1_INDEX,              /*!< SPI1 clock source                                  94 */ \
MC_ME_PCTL_SPI2_INDEX,              /*!< SPI2 clock source                                  95 */ \
MC_ME_PCTL_USB_OTG_INDEX,           /*!< USBOTG0 clock source                               96 */ \
MC_ME_PCTL_USB_SPH_INDEX,           /*!< USBSPH0 clock source                               97 */ \
MC_ME_INVALID_INDEX,                /*!< End of F80 clocks                                  98 */ \
MC_ME_PCTL_ADC_0_INDEX,             /*!< ADC0 clock source                                  99 */ \
MC_ME_PCTL_ADC_1_INDEX,             /*!< ADC1 clock source                                  100 */ \
MC_ME_PCTL_BCTU_INDEX,              /*!< BCTU0 clock source                                 101 */ \
MC_ME_INVALID_INDEX,                /*!< DMA0 clock source                                  102 */ \
MC_ME_PCTL_DMAUX_INDEX,             /*!< DMAMUX0 clock source                               103 */ \
MC_ME_PCTL_DMAUX_INDEX,             /*!< DMAMUX1 clock source                               104 */ \
MC_ME_PCTL_eMIOS_0_INDEX,           /*!< eMIOS0 clock source                                105 */ \
MC_ME_PCTL_eMIOS_1_INDEX,           /*!< eMIOS1 clock source                                106 */ \
MC_ME_PCTL_eMIOS_2_INDEX,           /*!< eMIOS2 clock source                                107 */ \
MC_ME_PCTL_FlexRay_INDEX,           /*!< FLEXRAY0 clock source                              108 */ \
MC_ME_INVALID_INDEX,                /*!< End of FS80 clocks                                 109 */ \
MC_ME_INVALID_INDEX,                /*!< ENET0_TIME clock source                            110 */ \
MC_ME_INVALID_INDEX,                /*!< ENET1_TIME clock source                            111 */ \
MC_ME_INVALID_INDEX,                /*!< End of ENET_TIME clocks                            112 */ \
MC_ME_PCTL_SDHC_INDEX,              /*!< SDHC0 clock source                                 113 */ \
MC_ME_INVALID_INDEX,                /*!< End of SDHC clocks                                 114 */ \
MC_ME_PCTL_SPI0_INDEX,              /*!< SPI0 clock source                                  115 */ \
MC_ME_INVALID_INDEX,                /*!< End of SPI clocks                                  116 */ \
MC_ME_INVALID_INDEX,                /*!< HSM0 clock source                                  117 */ \
MC_ME_INVALID_INDEX,                /*!< End of FIRC clocks                                 118 */ \
MC_ME_PCTL_PIT_RTI_0_INDEX,         /*!< PITRTI0 clock source                               119 */ \
MC_ME_INVALID_INDEX,                /*!< End of FXOSC clocks                                120 */ \
MC_ME_PCTL_FLEXCAN_0_INDEX,         /*!< FLEXCAN0 clock source                              121 */ \
MC_ME_PCTL_FLEXCAN_1_INDEX,         /*!< FLEXCAN1 clock source                              122 */ \
MC_ME_PCTL_FLEXCAN_2_INDEX,         /*!< FLEXCAN2 clock source                              123 */ \
MC_ME_PCTL_FLEXCAN_3_INDEX,         /*!< FLEXCAN3 clock source                              124 */ \
MC_ME_PCTL_FLEXCAN_4_INDEX,         /*!< FLEXCAN4 clock source                              125 */ \
MC_ME_PCTL_FLEXCAN_5_INDEX,         /*!< FLEXCAN5 clock source                              126 */ \
MC_ME_PCTL_FLEXCAN_6_INDEX,         /*!< FLEXCAN6 clock source                              127 */ \
MC_ME_PCTL_FLEXCAN_7_INDEX,         /*!< FLEXCAN7 clock source                              128 */ \
MC_ME_PCTL_MEMU_0_INDEX,            /*!< MEMU0 clock source                                 129 */ \
MC_ME_PCTL_MEMU_1_INDEX,            /*!< MEMU1 clock source                                 130 */ \
MC_ME_PCTL_RTC_API_INDEX,           /*!< RTC0 clock source                                  131 */ \
MC_ME_INVALID_INDEX,                /*!< SIUL0 clock source                                 132 */ \
MC_ME_INVALID_INDEX                /*!< END_OF_PERIPHERAL_CLK_SOURCES                      133 */ \
}


  /*! @brief interface clocks
   *  Mappings between clock names and interface clocks.
   *  If no interface clock exists for a given clock name,
   *  then the corresponding value is CLOCK_NAME_COUNT.
   */
#define INTERFACE_CLOCKS \
{                                                                           \
CLOCK_NAME_COUNT,                /*!< SIRC clock                      0  */ \
CLOCK_NAME_COUNT,                /*!< FIRC clock                      1  */ \
CLOCK_NAME_COUNT,                /*!< SXOSC clock                     2  */ \
CLOCK_NAME_COUNT,                /*!< FXOSC clock                     3  */ \
CLOCK_NAME_COUNT,                /*!< PLL_PHI0 clock                  4  */ \
CLOCK_NAME_COUNT,                /*!< PLL_PHI1 clock                  5  */ \
CLOCK_NAME_COUNT,                /*!< ENET_RMII clock                 6  */ \
CLOCK_NAME_COUNT,                /*!< No clock entry in clock_names_t 7  */ \
CLOCK_NAME_COUNT,                /*!< No clock entry in clock_names_t 8  */ \
CLOCK_NAME_COUNT,                /*!< No clock entry in clock_names_t 9  */ \
CLOCK_NAME_COUNT,                /*!< No clock entry in clock_names_t 10  */ \
CLOCK_NAME_COUNT,                /*!< No clock entry in clock_names_t 11  */ \
CLOCK_NAME_COUNT,                /*!< No clock entry in clock_names_t 12  */ \
CLOCK_NAME_COUNT,                /*!< No clock entry in clock_names_t 13  */ \
CLOCK_NAME_COUNT,                /*!< No clock entry in clock_names_t 14  */ \
CLOCK_NAME_COUNT,                /*!< No clock entry in clock_names_t 15  */ \
CLOCK_NAME_COUNT,                /*!< No clock entry in clock_names_t 16  */ \
CLOCK_NAME_COUNT,                /*!< No clock entry in clock_names_t 17  */ \
CLOCK_NAME_COUNT,                /*!< No clock entry in clock_names_t 18  */ \
CLOCK_NAME_COUNT,                /*!< No clock entry in clock_names_t 19  */ \
CLOCK_NAME_COUNT,                /*!< END_OF_CLK_SOURCES              20  */ \
CLOCK_NAME_COUNT,                /*!< SCS_CLK clock                   21  */ \
CLOCK_NAME_COUNT,                /*!< S160_CLK clock                  22  */ \
CLOCK_NAME_COUNT,                /*!< S80_CLK clock                   23  */ \
CLOCK_NAME_COUNT,                /*!< S40_CLK clock                   24  */ \
CLOCK_NAME_COUNT,                /*!< F40_CLK clock                   25  */ \
CLOCK_NAME_COUNT,                /*!< F80_CLK clock                   26  */ \
CLOCK_NAME_COUNT,                /*!< FS80_CLK clock                  27  */ \
CLOCK_NAME_COUNT,                /*!< F20_CLK clock                   28  */ \
CLOCK_NAME_COUNT,                /*!< No clock entry in clock_names_t 29  */ \
CLOCK_NAME_COUNT,                /*!< No clock entry in clock_names_t 30  */ \
CLOCK_NAME_COUNT,                /*!< No clock entry in clock_names_t 31  */ \
CLOCK_NAME_COUNT,                /*!< No clock entry in clock_names_t 32  */ \
CLOCK_NAME_COUNT,                /*!< No clock entry in clock_names_t 33  */ \
CLOCK_NAME_COUNT,                /*!< No clock entry in clock_names_t 34  */ \
CLOCK_NAME_COUNT,                /*!< No clock entry in clock_names_t 35  */ \
CLOCK_NAME_COUNT,                /*!< No clock entry in clock_names_t 36  */ \
CLOCK_NAME_COUNT,                /*!< No clock entry in clock_names_t 37  */ \
CLOCK_NAME_COUNT,                /*!< No clock entry in clock_names_t 38  */ \
CLOCK_NAME_COUNT,                /*!< No clock entry in clock_names_t 39  */ \
CLOCK_NAME_COUNT,                /*!< END_OF_SYSTEM_CLOCKS            40  */ \
CLOCK_NAME_COUNT,                /*!< CLKOUT0_CLK clock               41  */ \
CLOCK_NAME_COUNT,                /*!< CLKOUT1_CLK clock               42  */ \
CLOCK_NAME_COUNT,                /*!< No clock entry in clock_names_t 43  */ \
CLOCK_NAME_COUNT,                /*!< No clock entry in clock_names_t 44  */ \
CLOCK_NAME_COUNT,                /*!< No clock entry in clock_names_t 45  */ \
CLOCK_NAME_COUNT,                /*!< No clock entry in clock_names_t 46  */ \
CLOCK_NAME_COUNT,                /*!< No clock entry in clock_names_t 47  */ \
CLOCK_NAME_COUNT,                /*!< No clock entry in clock_names_t 48  */ \
CLOCK_NAME_COUNT,                /*!< No clock entry in clock_names_t 49  */ \
CLOCK_NAME_COUNT,                /*!< END_OF_SYSTEM_CLOCKS            50  */ \
S40_CLK,                         /*!< CMP0 clock                      51 */ \
S40_CLK,                         /*!< CMP1 clock                      52 */ \
S40_CLK,                         /*!< CMP2 clock                      53 */ \
S40_CLK,                         /*!< CRC0 clock                      54 */ \
S40_CLK,                         /*!< SAI0 clock                      55 */ \
S40_CLK,                         /*!< SAI1 clock                      56 */ \
S40_CLK,                         /*!< SAI2 clock                      57 */ \
S40_CLK,                         /*!< WKPU0 clock                     58 */ \
CLOCK_NAME_COUNT,                /*!< End of S40 clocks               59 */ \
S40_CLK,                         /*!< DSPI0 clock                     60 */ \
S40_CLK,                         /*!< DSPI1 clock                     61 */ \
F40_CLK,                         /*!< ENET0 clock                     62 */ \
F40_CLK,                         /*!< ENET1 clock                     63 */ \
F40_CLK,                         /*!< IIC0 clock                      64 */ \
F40_CLK,                         /*!< IIC1 clock                      65 */ \
F40_CLK,                         /*!< IIC2 clock                      66 */ \
F40_CLK,                         /*!< IIC3 clock                      67 */ \
F20_CLK,                         /*!< LIN0 clock                      68 */ \
F40_CLK,                         /*!< PIT0 clock                      69 */ \
S40_CLK,                         /*!< SPI3 clock                      70 */ \
S40_CLK,                         /*!< SPI4 clock                      71 */ \
S40_CLK,                         /*!< SPI5 clock                      72 */ \
CLOCK_NAME_COUNT,                /*!< End of F40 clocks               73 */ \
S40_CLK,                         /*!< DSPI2 clock                     74 */ \
S40_CLK,                         /*!< DSPI3 clock                     75 */ \
F40_CLK,                         /*!< LIN1 clock                      76 */ \
F40_CLK,                         /*!< LIN2 clock                      77 */ \
F40_CLK,                         /*!< LIN3 clock                      78 */ \
F40_CLK,                         /*!< LIN4 clock                      79 */ \
F40_CLK,                         /*!< LIN5 clock                      80 */ \
F40_CLK,                         /*!< LIN6 clock                      81 */ \
F40_CLK,                         /*!< LIN7 clock                      82 */ \
F40_CLK,                         /*!< LIN8 clock                      83 */ \
F40_CLK,                         /*!< LIN9 clock                      84 */ \
F40_CLK,                         /*!< LIN10 clock                     85 */ \
F40_CLK,                         /*!< LIN11 clock                     86 */ \
F40_CLK,                         /*!< LIN12 clock                     87 */ \
F40_CLK,                         /*!< LIN13 clock                     88 */ \
F40_CLK,                         /*!< LIN14 clock                     89 */ \
F40_CLK,                         /*!< LIN15 clock                     90 */ \
F40_CLK,                         /*!< LIN16 clock                     91 */ \
F40_CLK,                         /*!< LIN17 clock                     92 */ \
F40_CLK,                         /*!< MLB0 clock                      93 */ \
S40_CLK,                         /*!< SPI1 clock                      94 */ \
S40_CLK,                         /*!< SPI2 clock                      95 */ \
F80_CLK,                         /*!< USBOTG0 clock                   96 */ \
F80_CLK,                         /*!< USBSPH0 clock                   97 */ \
CLOCK_NAME_COUNT,                /*!< End of F80 clocks               98 */ \
FS80_CLK,                        /*!< ADC0 clock                      99 */ \
FS80_CLK,                        /*!< ADC1 clock                      100 */ \
FS80_CLK,                        /*!< BCTU0 clock                     101 */ \
FS80_CLK,                        /*!< DMA0 clock                      102 */ \
FS80_CLK,                        /*!< DMAMUX0 clock                   103 */ \
FS80_CLK,                        /*!< DMAMUX1 clock                   104 */ \
FS80_CLK,                        /*!< eMIOS0 clock                    105 */ \
FS80_CLK,                        /*!< eMIOS1 clock                    106 */ \
FS80_CLK,                        /*!< eMIOS2 clock                    107 */ \
FS80_CLK,                        /*!< FLEXRAY0 clock                  108 */ \
CLOCK_NAME_COUNT,                /*!< End of FS80 clocks              109 */ \
F40_CLK,                         /*!< ENET0_TIME clock                110 */ \
F40_CLK,                         /*!< ENET1_TIME clock                111 */ \
CLOCK_NAME_COUNT,                /*!< End of ENET_TIME clocks         112 */ \
F40_CLK,                         /*!< SDHC0 clock                     113 */ \
CLOCK_NAME_COUNT,                /*!< End of SDHC clocks              114 */ \
S40_CLK,                         /*!< SPI0 clock                      115 */ \
CLOCK_NAME_COUNT,                /*!< End of SPI clocks               116 */ \
S80_CLK,                         /*!< HSM0 clock                      117 */ \
CLOCK_NAME_COUNT,                /*!< End of FIRC clocks              118 */ \
F40_CLK,                         /*!< PITRTI0 clock                   119 */ \
CLOCK_NAME_COUNT,                /*!< End of FXOSC clocks             120 */ \
FLEXCAN0_CLK,                    /*!< FLEXCAN0 clock                  121 */ \
FS80_CLK,                        /*!< FLEXCAN1 clock                  122 */ \
FS80_CLK,                        /*!< FLEXCAN2 clock                  123 */ \
FS80_CLK,                        /*!< FLEXCAN3 clock                  124 */ \
FS80_CLK,                        /*!< FLEXCAN4 clock                  125 */ \
FS80_CLK,                        /*!< FLEXCAN5 clock                  126 */ \
FS80_CLK,                        /*!< FLEXCAN6 clock                  127 */ \
FS80_CLK,                        /*!< FLEXCAN7 clock                  128 */ \
F80_CLK,                         /*!< MEMU0 clock                     129 */ \
FS80_CLK,                        /*!< MEMU1 clock                     130 */ \
S40_CLK,                         /*!< RTC0 clock                      131 */ \
F40_CLK,                         /*!< SIUL0 clock                     132 */ \
CLOCK_NAME_COUNT                /*!< END_OF_PERIPHERAL_CLK_SOURCES   133 */ \
}



  /*! @brief monitors clocks
   *  Mappings between clock names and cmu instances.
   *  If no cmu monitor exists for a given clock name,
   *  then the corresponding value is NULL.
   */
#define MONITORED_CLOCKS \
{                                                                           \
NULL,              /*!< SIRC clock                          0 */ \
CMU,               /*!< FIRC clock                          1 */ \
NULL,              /*!< SXOSC clock                         2 */ \
CMU,               /*!< FXOSC clock                         3 */ \
NULL,              /*!< PLL_PHI0 clock                      4 */ \
NULL,              /*!< PLL_PHI1 clock                      5 */ \
NULL,              /*!< ENET_RMII clock                     6 */ \
NULL,              /*!< No clock entry in clock_names_t     7  */ \
NULL,              /*!< No clock entry in clock_names_t     8  */ \
NULL,              /*!< No clock entry in clock_names_t     9  */ \
NULL,              /*!< No clock entry in clock_names_t     10  */ \
NULL,              /*!< No clock entry in clock_names_t     11  */ \
NULL,              /*!< No clock entry in clock_names_t     12  */ \
NULL,              /*!< No clock entry in clock_names_t     13  */ \
NULL,              /*!< No clock entry in clock_names_t     14  */ \
NULL,              /*!< No clock entry in clock_names_t     15  */ \
NULL,              /*!< No clock entry in clock_names_t     16  */ \
NULL,              /*!< No clock entry in clock_names_t     17  */ \
NULL,              /*!< No clock entry in clock_names_t     18  */ \
NULL,              /*!< No clock entry in clock_names_t     19  */ \
NULL,              /*!< END_OF_CLK_SOURCES                  20  */ \
NULL,              /*!< SCS clock                           21 */ \
NULL,              /*!< S160 clock                          22 */ \
NULL,              /*!< S80 clock                           23 */ \
NULL,              /*!< S40 clock                           24 */ \
NULL,              /*!< F40 clock                           25 */ \
NULL,              /*!< F80 clock                           26 */ \
NULL,              /*!< FS80 clock                          27 */ \
NULL,              /*!< F20 clock                           28 */ \
NULL,              /*!< No clock entry in clock_names_t     29  */ \
NULL,              /*!< No clock entry in clock_names_t     30  */ \
NULL,              /*!< No clock entry in clock_names_t     31  */ \
NULL,              /*!< No clock entry in clock_names_t     32  */ \
NULL,              /*!< No clock entry in clock_names_t     33  */ \
NULL,              /*!< No clock entry in clock_names_t     34  */ \
NULL,              /*!< No clock entry in clock_names_t     35  */ \
NULL,              /*!< No clock entry in clock_names_t     36  */ \
NULL,              /*!< No clock entry in clock_names_t     37  */ \
NULL,              /*!< No clock entry in clock_names_t     38  */ \
NULL,              /*!< No clock entry in clock_names_t     39  */ \
NULL,              /*!< END_OF_SYSTEM_CLOCKS                40  */ \
NULL,              /*!< CLK clock                           41 */ \
NULL,              /*!< CLK clock                           42 */ \
NULL,              /*!< No clock entry in clock_names_t     43  */ \
NULL,              /*!< No clock entry in clock_names_t     44  */ \
NULL,              /*!< No clock entry in clock_names_t     45  */ \
NULL,              /*!< No clock entry in clock_names_t     46  */ \
NULL,              /*!< No clock entry in clock_names_t     47  */ \
NULL,              /*!< No clock entry in clock_names_t     48  */ \
NULL,              /*!< No clock entry in clock_names_t     49  */ \
NULL,              /*!< END_OF_CLOCKOUTS                    50  */ \
NULL,              /*!< CMP0 clock                          51 */ \
NULL,              /*!< CMP1 clock                          52 */ \
NULL,              /*!< CMP2 clock                          53 */ \
NULL,              /*!< CRC0 clock                          54 */ \
NULL,              /*!< SAI0 clock                          55 */ \
NULL,              /*!< SAI1 clock                          56 */ \
NULL,              /*!< SAI2 clock                          57 */ \
NULL,              /*!< WKPU0 clock                         58 */ \
NULL,              /*!< End of S40 clocks                   59 */ \
NULL,              /*!< DSPI0 clock                         60 */ \
NULL,              /*!< DSPI1 clock                         61 */ \
NULL,              /*!< ENET0 clock                         62 */ \
NULL,              /*!< ENET1 clock                         63 */ \
NULL,              /*!< IIC0 clock                          64 */ \
NULL,              /*!< IIC1 clock                          65 */ \
NULL,              /*!< IIC2 clock                          66 */ \
NULL,              /*!< IIC3 clock                          67 */ \
NULL,              /*!< LIN0 clock                          68 */ \
NULL,              /*!< PIT0 clock                          69 */ \
NULL,              /*!< SPI3 clock                          70 */ \
NULL,              /*!< SPI4 clock                          71 */ \
NULL,              /*!< SPI5 clock                          72 */ \
NULL,              /*!< End of F40 clocks                   73 */ \
NULL,              /*!< DSPI2 clock                         74 */ \
NULL,              /*!< DSPI3 clock                         75 */ \
NULL,              /*!< LIN1 clock                          76 */ \
NULL,              /*!< LIN2 clock                          77 */ \
NULL,              /*!< LIN3 clock                          78 */ \
NULL,              /*!< LIN4 clock                          79 */ \
NULL,              /*!< LIN5 clock                          80 */ \
NULL,              /*!< LIN6 clock                          81 */ \
NULL,              /*!< LIN7 clock                          82 */ \
NULL,              /*!< LIN8 clock                          83 */ \
NULL,              /*!< LIN9 clock                          84 */ \
NULL,              /*!< LIN10 clock                         85 */ \
NULL,              /*!< LIN11 clock                         86 */ \
NULL,              /*!< LIN12 clock                         87 */ \
NULL,              /*!< LIN13 clock                         88 */ \
NULL,              /*!< LIN14 clock                         89 */ \
NULL,              /*!< LIN15 clock                         90 */ \
NULL,              /*!< LIN16 clock                         91 */ \
NULL,              /*!< LIN17 clock                         92 */ \
NULL,              /*!< MLB0 clock                          93 */ \
NULL,              /*!< SPI1 clock                          94 */ \
NULL,              /*!< SPI2 clock                          95 */ \
NULL,              /*!< USBOTG0 clock                       96 */ \
NULL,              /*!< USBSPH0 clock                       97 */ \
NULL,              /*!< End of F80 clocks                   98 */ \
NULL,              /*!< ADC0 clock                          99 */ \
NULL,              /*!< ADC1 clock                          100 */ \
NULL,              /*!< BCTU0 clock                         101 */ \
NULL,              /*!< DMA0 clock                          102 */ \
NULL,              /*!< DMAMUX0 clock                       103 */ \
NULL,              /*!< DMAMUX1 clock                       104 */ \
NULL,              /*!< eMIOS0 clock                        105 */ \
NULL,              /*!< eMIOS1 clock                        106 */ \
NULL,              /*!< eMIOS2 clock                        107 */ \
NULL,              /*!< FLEXRAY0 clock                      108 */ \
NULL,              /*!< End of FS80 clocks                  109 */ \
NULL,              /*!< ENET0_TIME clock                    110 */ \
NULL,              /*!< ENET1_TIME clock                    111 */ \
NULL,              /*!< End of ENET_TIME clocks             112 */ \
NULL,              /*!< SDHC0 clock                         113 */ \
NULL,              /*!< End of SDHC clocks                  114 */ \
NULL,              /*!< SPI0 clock                          115 */ \
NULL,              /*!< End of SPI clocks                   116 */ \
NULL,              /*!< HSM0 clock                          117 */ \
NULL,              /*!< End of FIRC clocks                  118 */ \
NULL,              /*!< PITRTI0 clock                       119 */ \
NULL,              /*!< End of FXOSC clocks                 120 */ \
NULL,              /*!< FLEXCAN0 clock                      121 */ \
NULL,              /*!< FLEXCAN1 clock                      122 */ \
NULL,              /*!< FLEXCAN2 clock                      123 */ \
NULL,              /*!< FLEXCAN3 clock                      124 */ \
NULL,              /*!< FLEXCAN4 clock                      125 */ \
NULL,              /*!< FLEXCAN5 clock                      126 */ \
NULL,              /*!< FLEXCAN6 clock                      127 */ \
NULL,              /*!< FLEXCAN7 clock                      128 */ \
NULL,              /*!< MEMU0 clock                         129 */ \
NULL,              /*!< MEMU1 clock                         130 */ \
NULL,              /*!< RTC0 clock                          131 */ \
NULL,              /*!< SIUL0 clock                         132 */ \
NULL,               /*!< END_OF_PERIPHERAL_CLK_SOURCES       133 */ \
}



/* Interrupt module features */

/* @brief Lowest interrupt request number. */
#define FEATURE_INTERRUPT_IRQ_MIN         (SS0_IRQn)
/* @brief Highest interrupt request number. */
#define FEATURE_INTERRUPT_IRQ_MAX         (EMIOS2_30_31_IRQn)
/* @brief Highest interrupt priority number. */
#define FEATURE_INTERRUPT_PRIO_MAX  (15u)
/* @brief Highest software interrupt request number. */
#define FEATURE_INTERRUPT_SOFTWARE_IRQ_MAX  (SS23_IRQn)
/* @brief Has software interrupt. */
#define FEATURE_INTERRUPT_HAS_SOFTWARE_IRQ  (1u)
/* @brief Has pending interrupt state. */
#define FEATURE_INTERRUPT_HAS_PENDING_STATE (0u)
/* @brief Has active interrupt state. */
#define FEATURE_INTERRUPT_HAS_ACTIVE_STATE  (0u)
/* @brief Default interrupt priority for enable interrupts. */
#define FEATURE_INTERRUPT_DEFAULT_PRIO  (1u)
/* @brief Multicore support for interrupts */
#define FEATURE_INTERRUPT_MULTICORE_SUPPORT  (1u)
/* @brief Mask to enable interrupts for all cores */
#define FEATURE_INTERRUPT_ENABLE_ON_ALL_CORES_MASK  (0xE000u)
/* @brief Available cores for this device */
#define FEATURE_INTERRUPT_CORE_0_ENABLED (1u)
#define FEATURE_INTERRUPT_CORE_1_ENABLED (1u)
#define FEATURE_INTERRUPT_CORE_2_ENABLED (1u)
/* @brief Registers in which the start of interrupt vector table needs to be configured */
#define FEATURE_INTERRUPT_INT_VECTORS {&INTC->IACKR0, &INTC->IACKR1, &INTC->IACKR2}

/* OSIF module features */

#define FEATURE_OSIF_USE_SYSTICK                         (0)
#define FEATURE_OSIF_USE_PIT                             (1)
#define FEATURE_OSIF_FREERTOS_ISR_CONTEXT_METHOD         (2)
#define OSIF_PIT (PIT)
#define OSIF_PIT_CHAN_ID_MAX (15u)
#define FEATURE_OSIF_PIT_FRZ_IN_DEBUG                    (1)

/* FLASH C55 module features */

/* @brief Type of flash module is C55FMC. */
#define FEATURE_FLS_C55_C55FMC (1U)
/* @brief Type of flash module is C55MP. */
#define FEATURE_FLS_C55_C55MP (0U)
/* @brief Type of flash module is C55FP. */
#define FEATURE_FLS_C55_C55FP (0U)
/* @brief Over-program protection enabled block. */
#define FEATURE_FLS_C55_HAS_OTP
/* @brief Has alternate interface. */
#define FEATURE_FLS_C55_HAS_ALTERNATE (0U)
/* @brief Has erase operation in the alternate interface. */
#define FEATURE_FLS_C55_HAS_ERASE_ALTERNATE (0U)
/* @brief The size of writes that are allowed. */
#define FLASH_C55_PROGRAMABLE_SIZE (0x80U)
/* @brief The address in the uTest space. */
#define FLASH_C55_INTERLOCK_WRITE_UTEST_ADDRESS (0x00400000U)
/* @brief The base address of the 16KB high block. */
#define FLASH_C55_16KB_HIGH_BASE_ADDRESS (0x00F80000U)
/* @brief The base address of the 32KB high block. */
#define FLASH_C55_32KB_HIGH_BASE_ADDRESS (0xFFFFFFFFU)
/* @brief The base address of the 64KB high block. */
#define FLASH_C55_64KB_HIGH_BASE_ADDRESS (0xFFFFFFFFU)
/* @brief The base address of the 16KB mid block. */
#define FLASH_C55_16KB_MID_BASE_ADDRESS (0x00F90000U)
/* @brief The base address of the 32KB mid block. */
#define FLASH_C55_32KB_MID_BASE_ADDRESS (0x00FB0000U)
/* @brief The base address of the 64KB mid block. */
#define FLASH_C55_64KB_MID_BASE_ADDRESS (0xFFFFFFFFU)
/* @brief The base address of the 16KB low block. */
#define FLASH_C55_16KB_LOW_BASE_ADDRESS (0x00F8C000U)
/* @brief The base address of the 32KB low block. */
#define FLASH_C55_32KB_LOW_BASE_ADDRESS (0x00FC0000U)
/* @brief The base address of the 64KB low block. */
#define FLASH_C55_64KB_LOW_BASE_ADDRESS (0x00FE0000U)
/* @brief The size of 16K block. */
#define FLASH_C55_16KB_SIZE (0x4000U)
/* @brief The size of 32K block. */
#define FLASH_C55_32KB_SIZE (0x8000U)
/* @brief The size of 64K block. */
#define FLASH_C55_64KB_SIZE (0x10000U)
/* @brief The base address of the 256KB block. */
#define FLASH_C55_256KB_BASE_ADDRESS (0x01000000U)
/* @brief The number of low block */
#define NUM_LOW_BLOCK                          10U
/* @brief The number of 16K low block */
#define NUM_16K_LOW_BLOCK                       2U
/* @brief The number of 32K low block */
#define NUM_32K_LOW_BLOCK                       4U
/* @brief The number of 64K low block */
#define NUM_64K_LOW_BLOCK                       4U

/* @brief The number of mid block */
#define NUM_MID_BLOCK                          10U
/* @brief The number of high block */
#define NUM_HIGH_BLOCK                         2U
/* @brief The number of 256k block */
#define NUM_256K_BLOCK_FIRST                    22U
#define NUM_256K_BLOCK_SECOND                   0U
#define NUM_256K_BLOCK                         (NUM_256K_BLOCK_FIRST + NUM_256K_BLOCK_SECOND)
#define NUM_BLOCK                              (NUM_LOW_BLOCK + NUM_MID_BLOCK + NUM_HIGH_BLOCK + NUM_256K_BLOCK)

#define LOW_BLOCK0_ADDR                        0x00F8C000U
#define LOW_BLOCK0_MASK                        (1UL << 0x0U)

#define LOW_BLOCK1_ADDR                        0x00404000U
#define LOW_BLOCK1_MASK                        (1UL << 0x1U)

#define LOW_BLOCK2_ADDR                        0x00FC0000U
#define LOW_BLOCK2_MASK                        (1UL << 0x2U)

#define LOW_BLOCK3_ADDR                        0x00FC8000U
#define LOW_BLOCK3_MASK                        (1UL << 0x3U)

#define LOW_BLOCK4_ADDR                        0x00FD0000U
#define LOW_BLOCK4_MASK                        (1UL << 0x4U)

#define LOW_BLOCK5_ADDR                        0x00FD8000U
#define LOW_BLOCK5_MASK                        (1UL << 0x5U)

#define LOW_BLOCK6_ADDR                        0x00FE0000U
#define LOW_BLOCK6_MASK                        (1UL << 0x6U)

#define LOW_BLOCK7_ADDR                        0x00610000U
#define LOW_BLOCK7_MASK                        (1UL << 0x7U)

#define LOW_BLOCK8_ADDR                        0x00FF0000U
#define LOW_BLOCK8_MASK                        (1UL << 0x8U)

#define LOW_BLOCK9_ADDR                        0x00620000U
#define LOW_BLOCK9_MASK                        (1UL << 0x9U)

/* Define Macros for mid blocks */
#define MID_BLOCK0_ADDR                        0x00F90000U
#define MID_BLOCK0_MASK                        (1UL << 0x0U)

#define MID_BLOCK1_ADDR                        0x00F94000U
#define MID_BLOCK1_MASK                        (1UL << 0x1U)

#define MID_BLOCK2_ADDR                        0x00F98000U
#define MID_BLOCK2_MASK                        (1UL << 0x2U)

#define MID_BLOCK3_ADDR                        0x00F9C000U
#define MID_BLOCK3_MASK                        (1UL << 0x3U)

#define MID_BLOCK4_ADDR                        0x00FA0000U
#define MID_BLOCK4_MASK                        (1UL << 0x4U)

#define MID_BLOCK5_ADDR                        0x00FA4000U
#define MID_BLOCK5_MASK                        (1UL << 0x5U)

#define MID_BLOCK6_ADDR                        0x00FA8000U
#define MID_BLOCK6_MASK                        (1UL << 0x6U)

#define MID_BLOCK7_ADDR                        0x00FAC000U
#define MID_BLOCK7_MASK                        (1UL << 0x7U)

#define MID_BLOCK8_ADDR                        0x00FB0000U
#define MID_BLOCK8_MASK                        (1UL << 0x8U)

#define MID_BLOCK9_ADDR                        0x00FB8000U
#define MID_BLOCK9_MASK                        (1UL << 0x9U)

/* Define Macros for high blocks */
#define HIGH_BLOCK0_ADDR                       0x00F80000U
#define HIGH_BLOCK0_MASK                       (1UL << 0x0U)

#define HIGH_BLOCK1_ADDR                       0x00F84000U
#define HIGH_BLOCK1_MASK                       (1UL << 0x1U)

/* Define Macros for 256k blocks */
#define N256K_BLOCK0_ADDR                       0x01000000U
#define N256K_BLOCK0_MASK                       (1UL << 0x0U)

#define N256K_BLOCK1_ADDR                       0x01040000U
#define N256K_BLOCK1_MASK                       (1UL << 0x1U)

#define N256K_BLOCK2_ADDR                       0x01080000U
#define N256K_BLOCK2_MASK                       (1UL << 0x2U)

#define N256K_BLOCK3_ADDR                       0x010C0000U
#define N256K_BLOCK3_MASK                       (1UL << 0x3U)

#define N256K_BLOCK4_ADDR                       0x01100000U
#define N256K_BLOCK4_MASK                       (1UL << 0x4U)

#define N256K_BLOCK5_ADDR                       0x01140000U
#define N256K_BLOCK5_MASK                       (1UL << 0x5U)

#define N256K_BLOCK6_ADDR                       0x01180000U
#define N256K_BLOCK6_MASK                       (1UL << 0x6U)

#define N256K_BLOCK7_ADDR                       0x011C0000U
#define N256K_BLOCK7_MASK                       (1UL << 0x7U)

#define N256K_BLOCK8_ADDR                       0x01200000U
#define N256K_BLOCK8_MASK                       (1UL << 0x8U)

#define N256K_BLOCK9_ADDR                       0x01240000U
#define N256K_BLOCK9_MASK                       (1UL << 0x9U)

#define N256K_BLOCK10_ADDR                      0x01280000U
#define N256K_BLOCK10_MASK                      (1UL << 0xAU)

#define N256K_BLOCK11_ADDR                      0x012C0000U
#define N256K_BLOCK11_MASK                      (1UL << 0xBU)

#define N256K_BLOCK12_ADDR                      0x01300000U
#define N256K_BLOCK12_MASK                      (1UL << 0xCU)

#define N256K_BLOCK13_ADDR                      0x01340000U
#define N256K_BLOCK13_MASK                      (1UL << 0xDU)

#define N256K_BLOCK14_ADDR                      0x01380000U
#define N256K_BLOCK14_MASK                      (1UL << 0xEU)

#define N256K_BLOCK15_ADDR                      0x013C0000U
#define N256K_BLOCK15_MASK                      (1UL << 0xFU)

#define N256K_BLOCK16_ADDR                      0x01400000U
#define N256K_BLOCK16_MASK                      (1UL << 0x10U)

#define N256K_BLOCK17_ADDR                      0x01440000U
#define N256K_BLOCK17_MASK                      (1UL << 0x11U)

#define N256K_BLOCK18_ADDR                      0x01480000U
#define N256K_BLOCK18_MASK                      (1UL << 0x12U)

#define N256K_BLOCK19_ADDR                      0x014C0000U
#define N256K_BLOCK19_MASK                      (1UL << 0x13U)

#define N256K_BLOCK20_ADDR                      0x01500000U
#define N256K_BLOCK20_MASK                      (1UL << 0x14U)

#define N256K_BLOCK21_ADDR                      0x01540000U
#define N256K_BLOCK21_MASK                      (1UL << 0x15U)
#define FLASH_BLOCK_ADDR_DEFINE \
{                               \
LOW_BLOCK0_ADDR, /* Low block 0 address */ \
LOW_BLOCK1_ADDR, /* Low block 1 address */ \
LOW_BLOCK2_ADDR, /* Low block 2 address */ \
LOW_BLOCK3_ADDR, /* Low block 3 address */ \
LOW_BLOCK4_ADDR, /* Low block 4 address */ \
LOW_BLOCK5_ADDR, /* Low block 5 address */ \
LOW_BLOCK6_ADDR, /* Low block 6 address */ \
LOW_BLOCK7_ADDR, /* Low block 7 address */ \
LOW_BLOCK8_ADDR, /* Low block 8 address */ \
LOW_BLOCK9_ADDR, /* Low block 9 address */ \
MID_BLOCK0_ADDR, /* Mid block 0 address */ \
MID_BLOCK1_ADDR, /* Mid block 1 address */ \
MID_BLOCK2_ADDR, /* Mid block 2 address */ \
MID_BLOCK3_ADDR, /* Mid block 3 address */ \
MID_BLOCK4_ADDR, /* Mid block 4 address */  \
MID_BLOCK5_ADDR, /* Mid block 5 address */  \
MID_BLOCK6_ADDR, /* Mid block 6 address */  \
MID_BLOCK7_ADDR, /* Mid block 7 address */  \
MID_BLOCK8_ADDR, /* Mid block 8 address */  \
MID_BLOCK9_ADDR, /* Mid block 8 address */  \
HIGH_BLOCK0_ADDR, /* high block 0 address */  \
HIGH_BLOCK1_ADDR, /* high block 1 address */  \
N256K_BLOCK0_ADDR, /* 256K block 0 address */  \
N256K_BLOCK1_ADDR, /* 256K block 1 address */  \
N256K_BLOCK2_ADDR, /* 256K block 2 address */  \
N256K_BLOCK3_ADDR, /* 256K block 3 address */  \
N256K_BLOCK4_ADDR, /* 256K block 4 address */  \
N256K_BLOCK5_ADDR, /* 256K block 5 address */  \
N256K_BLOCK6_ADDR, /* 256K block 6 address */  \
N256K_BLOCK7_ADDR, /* 256K block 7 address */  \
N256K_BLOCK8_ADDR, /* 256K block 8 address */  \
N256K_BLOCK9_ADDR, /* 256K block 9 address */  \
N256K_BLOCK10_ADDR, /* 256K block 10 address */  \
N256K_BLOCK11_ADDR, /* 256K block 11 address */  \
N256K_BLOCK12_ADDR, /* 256K block 12 address */  \
N256K_BLOCK13_ADDR, /* 256K block 13 address */  \
N256K_BLOCK14_ADDR, /* 256K block 14 address */  \
N256K_BLOCK15_ADDR, /* 256K block 15 address */  \
N256K_BLOCK16_ADDR, /* 256K block 16 address */  \
N256K_BLOCK17_ADDR, /* 256K block 17 address */  \
N256K_BLOCK18_ADDR, /* 256K block 18 address */  \
N256K_BLOCK19_ADDR, /* 256K block 19 address */  \
N256K_BLOCK20_ADDR, /* 256K block 20 address */  \
N256K_BLOCK21_ADDR /* 256K block 21 address */  \
}
#define FLASH_BLOCK_MASK_DEFINE \
{                              \
LOW_BLOCK0_MASK, /* Low block 0 mask */ \
LOW_BLOCK1_MASK, /* Low block 1 mask */ \
LOW_BLOCK2_MASK, /* Low block 2 mask */ \
LOW_BLOCK3_MASK, /* Low block 3 mask */ \
LOW_BLOCK4_MASK, /* Low block 4 mask */ \
LOW_BLOCK5_MASK, /* Low block 5 mask */ \
LOW_BLOCK6_MASK, /* Low block 6 mask */ \
LOW_BLOCK7_MASK, /* Low block 7 mask */ \
LOW_BLOCK8_MASK, /* Low block 8 mask */ \
LOW_BLOCK9_MASK, /* Low block 9 mask */ \
MID_BLOCK0_MASK, /* Mid block 0 mask */ \
MID_BLOCK1_MASK, /* Mid block 1 mask */ \
MID_BLOCK2_MASK, /* Mid block 2 mask */ \
MID_BLOCK3_MASK, /* Mid block 3 mask */ \
MID_BLOCK4_MASK, /* Mid block 4 mask */  \
MID_BLOCK5_MASK, /* Mid block 5 mask */  \
MID_BLOCK6_MASK, /* Mid block 6 mask */  \
MID_BLOCK7_MASK, /* Mid block 7 mask */  \
MID_BLOCK8_MASK, /* Mid block 8 mask */  \
MID_BLOCK9_MASK, /* Mid block 8 mask */  \
HIGH_BLOCK0_MASK, /* high block 0 mask */  \
HIGH_BLOCK1_MASK, /* high block 1 mask */  \
N256K_BLOCK0_MASK, /* 256K block 0 mask */  \
N256K_BLOCK1_MASK, /* 256K block 1 mask */  \
N256K_BLOCK2_MASK, /* 256K block 2 mask */  \
N256K_BLOCK3_MASK, /* 256K block 3 mask */  \
N256K_BLOCK4_MASK, /* 256K block 4 mask */  \
N256K_BLOCK5_MASK, /* 256K block 5 mask */  \
N256K_BLOCK6_MASK, /* 256K block 6 mask */  \
N256K_BLOCK7_MASK, /* 256K block 7 mask */  \
N256K_BLOCK8_MASK, /* 256K block 8 mask */  \
N256K_BLOCK9_MASK, /* 256K block 9 mask */  \
N256K_BLOCK10_MASK, /* 256K block 10 mask */  \
N256K_BLOCK11_MASK, /* 256K block 11 mask */  \
N256K_BLOCK12_MASK, /* 256K block 12 mask */  \
N256K_BLOCK13_MASK, /* 256K block 13 mask */  \
N256K_BLOCK14_MASK, /* 256K block 14 mask */  \
N256K_BLOCK15_MASK, /* 256K block 15 mask */  \
N256K_BLOCK16_MASK, /* 256K block 16 mask */  \
N256K_BLOCK17_MASK, /* 256K block 17 mask */  \
N256K_BLOCK18_MASK, /* 256K block 18 mask */  \
N256K_BLOCK19_MASK, /* 256K block 19 mask */  \
N256K_BLOCK20_MASK, /* 256K block 20 mask */  \
N256K_BLOCK21_MASK /* 256K block 21 mask */  \
}

/* EEE module features */

/*  @brief The block endurance for erasing successful */
#define BLOCK_MAX_ENDURANCE       (250000U)
/*  @brief The EEC error will occur in IVOR exception handler */
#define EEE_ERR_IVOR_EXCEPTION    (0)
/*  @brief The EEC error will set an ECC error in MCR register */
#define EEE_ERR_C55_MCR           (1)
/*  @brief Has 4 bytes ECC */
#define EEE_ECC4                  (0)
/*  @brief Has 8 bytes ECC */
#define EEE_ECC8                  (1)
/*  @brief Has 16 bytes ECC */
#define EEE_ECC16                 (0)
/*  @brief Has 32 bytes ECC */
#define EEE_ECC32                 (0)

/* SAI module features */

#define SAI0_CHANNEL_COUNT 4U
#define SAI1_CHANNEL_COUNT 1U
#define SAI2_CHANNEL_COUNT 1U
#define SAI_MAX_CHANNEL_COUNT 4U
/*! @brief SAI2 can be master */
#define FEATURE_SAI_SYNC_WITH_OTHER_INST
/*! @brief Fractional clock divider */
#define FEATURE_SAI_MSEL_FCD
/*! @brief Master clock from other instance's MCLK pins */
#define FEATURE_SAI_MSEL_OTHER_MCLK_PIN
/*! @brief Big endian */
#define FEATURE_SAI_BIG_ENDIAN

/* TDM module features */

/*! @brief TDR count */
#define TDR_COUNT 6U

/* ENET module features */

/** Interrupt vectors for the ENET peripheral type */
#define ENET_Err_IRQS                     { ENET0_GROUP0_IRQn, ENET1_GROUP0_IRQn }
#define ENET_Rx_IRQS                      { ENET0_GROUP1_IRQn, ENET1_GROUP1_IRQn }
#define ENET_Tx_IRQS                      { ENET0_GROUP2_IRQn, ENET1_GROUP2_IRQn }
#define ENET_Parser_IRQS                  { ENET0_GROUP3_IRQn, ENET1_GROUP3_IRQn }
#define ENET_Timer_IRQS                   { ENET0_GROUP4_IRQn, ENET1_GROUP4_IRQn }
#define ENET_Rx_1_IRQS                    { ENET0_GROUP5_IRQn, ENET1_GROUP5_IRQn }
#define ENET_Tx_1_IRQS                    { ENET0_GROUP6_IRQn, ENET1_GROUP6_IRQn }
#define ENET_Rx_2_IRQS                    { ENET0_GROUP7_IRQn, ENET1_GROUP7_IRQn }
#define ENET_Tx_2_IRQS                    { ENET0_GROUP8_IRQn, ENET1_GROUP8_IRQn }

/*! @brief ENET peripheral clock names */
#define FEATURE_ENET_CLOCK_NAMES { ENET0_CLK }

/*! @brief The transmission interrupts */
#define FEATURE_ENET_TX_IRQS        ENET_Tx_IRQS
/*! @brief The reception interrupts */
#define FEATURE_ENET_RX_IRQS        ENET_Rx_IRQS
/*! @brief The error interrupts */
#define FEATURE_ENET_ERR_IRQS       ENET_Err_IRQS
/*! @brief The timer interrupts */
#define FEATURE_ENET_TIMER_IRQS     ENET_Timer_IRQS
/*! @brief The parser interrupts */
#define FEATURE_ENET_PARSER_IRQS    ENET_Parser_IRQS

/*! @brief The transmission interrupts for ring 1 */
#define FEATURE_ENET_TX_1_IRQS        ENET_Tx_1_IRQS
/*! @brief The reception interrupts for ring 1 */
#define FEATURE_ENET_RX_1_IRQS        ENET_Rx_1_IRQS
/*! @brief The transmission interrupts for ring 2 */
#define FEATURE_ENET_TX_2_IRQS        ENET_Tx_2_IRQS
/*! @brief The reception interrupts for ring 2 */
#define FEATURE_ENET_RX_2_IRQS        ENET_Rx_2_IRQS

/*! @brief The maximum supported frequency for MDC, in Hz. */
#define FEATURE_ENET_MDC_MAX_FREQUENCY 2500000U

/*! @brief Minimum hold time on the MDIO output, in nanoseconds. */
#define FEATURE_ENET_MDIO_MIN_HOLD_TIME_NS 10U

/*! @brief Definitions used for aligning the data buffers */
#define FEATURE_ENET_BUFF_ALIGNMENT      (64UL)
/*! @brief Definitions used for aligning the buffer descriptors */
#define FEATURE_ENET_BUFFDESCR_ALIGNMENT (64UL)

/*! @brief Has receive frame parser feature. */
#define FEATURE_ENET_HAS_RECEIVE_PARSER (1)

/*! @brief Has enhanced buffer descriptors programming model. */
#define FEATURE_ENET_HAS_ENHANCED_BD    (1)

/*! @brief Default configuration for the PHY interface */
#define FEATURE_ENET_DEFAULT_PHY_IF     ENET_RMII_MODE

/*! @brief Has adjustable timer enabling IEEE 1588 support */
#define FEATURE_ENET_HAS_ADJUSTABLE_TIMER (1)

/*! @brief Has support for configuring the width of the output compare pulse */
#define FEATURE_ENET_HAS_TIMER_PULSE_WIDTH_CONTROL (1)

/*! @brief The number of available receive and transmit buffer descriptor rings */
#define FEATURE_ENET_RING_COUNT             (3U)

/*! @brief The number of available VLAN priority compare values per class */
#define FEATURE_ENET_CLASS_MATCH_CMP_COUNT  (4U)

/*! @brief Has credit-based shaper */
#define FEATURE_ENET_HAS_CBS                (1)

/*! @brief Has time-based shaper */
#define FEATURE_ENET_HAS_TBS                (1)

/*! @brief Has interrupt coalescing */
#define FEATURE_ENET_HAS_INTCOAL            (1)

/*! @brief Has RGMII mode for data interface */
#define FEATURE_ENET_HAS_RGMII              (0)

/*! @brief Has 1000-Mbit/s speed mode */
#define FEATURE_ENET_HAS_SPEED_1000M        (0)

/*! @brief Has Receive and Transmit accelerator */
#define FEATURE_ENET_HAS_ACCELERATOR		(1)

/*! @brief Has Sleep and Wakeup functionalities */
#define FEATURE_ENET_HAS_SLEEP_WAKEUP		(1)

/*! @brief Has configurable FIFO thresholds */
#define FEATURE_ENET_HAS_CONFIG_FIFO_THRESHOLDS	(1)

/*! @brief RX Configuration features */
#define FEATURE_ENET_HAS_RX_CONFIG					(1)
#define FEATURE_ENET_RX_CONFIG_PAYLOAD_LEN_CHECK	(1)
#define FEATURE_ENET_RX_CONFIG_STRIP_CRC_FIELD		(1)
#define FEATURE_ENET_RX_CONFIG_REMOVE_PADDING		(1)
#define FEATURE_ENET_RX_CONFIG_FORWARD_PAUSE_FRAMES	(1)

/*! @brief TX Configuration features */
#define FEATURE_ENET_HAS_TX_CONFIG	(1)

/* SIUL2 module feature */
/*! @brief SIUL2 module support Analog Pad */
#define FEATURE_SIUL2_HAS_ANALOG_PAD                    (1)
/*! @brief SIUL2 module Slew rate combine with Drive strength */
#define FEATURE_SIUL2_HAS_SLEW_RATE_WITH_DRIVE_STRENGTH (1)
/*! @brief SIUL2 module input source select bit width */
#define FEATURE_SIUL2_INPUT_SOURCE_SELECT_WIDTH         SIUL2_IMCR_SSS_WIDTH
/*! @brief SIUL2 module input mux numbers */
#define FEATURE_SIUL2_INPUT_MUX_WIDTH                   (8U)

/** GPIO - Register Layout Typedef */
typedef struct {
  __IO uint16_t PGPDO;          /**< SIUL2 Parallel GPIO Pad Data Out Register, array offset: 0x1700, array step: 0x2 */
       uint16_t RESERVED_PGPDO[SIUL2_PGPDO_COUNT - 1U];
  __I  uint16_t PGPDI;          /**< SIUL2 Parallel GPIO Pad Data In Register, array offset: 0x1740, array step: 0x2 */
       uint16_t RESERVED_PGPDI[SIUL2_PGPDI_COUNT - 1U];
  __O  uint32_t MPGPDO;        /**< SIUL2 Masked Parallel GPIO Pad Data Out Register, array offset: 0x1780, array step: 0x4 */
} GPIO_Type;

 /** Number of instances of the SIUL2 module. */
#define GPIO_INSTANCE_COUNT (17u)

/* SIUL2 - Peripheral instance base addresses */
/** Peripheral SIUL2 base address */
#define GPIO_BASE                               (0xFFFC1700u)
/** Peripheral SIUL2 base pointer */
#define GPIO                                    ((GPIO_Type *)GPIO_BASE)

 /* GPIO - Peripheral instance base addresses */
/** Peripheral PTA base address */
#define PTA_BASE                                 (0xFFFC1700u)
/** Peripheral PTA base pointer */
#define PTA                                      ((GPIO_Type *)PTA_BASE)
/** Peripheral PTB base address */
#define PTB_BASE                                 (0xFFFC1702u)
/** Peripheral PTB base pointer */
#define PTB                                      ((GPIO_Type *)PTB_BASE)
/** Peripheral PTC base address */
#define PTC_BASE                                 (0xFFFC1704u)
/** Peripheral PTC base pointer */
#define PTC                                      ((GPIO_Type *)PTC_BASE)
/** Peripheral PTD base address */
#define PTD_BASE                                 (0xFFFC1706u)
/** Peripheral PTD base pointer */
#define PTD                                      ((GPIO_Type *)PTD_BASE)
/** Peripheral PTE base address */
#define PTE_BASE                                 (0xFFFC1708u)
/** Peripheral PTE base pointer */
#define PTE                                      ((GPIO_Type *)PTE_BASE)
/** Peripheral PTF base address */
#define PTF_BASE                                 (0xFFFC170Au)
/** Peripheral PTF base pointer */
#define PTF                                      ((GPIO_Type *)PTF_BASE)
/** Peripheral PTG base address */
#define PTG_BASE                                 (0xFFFC170Cu)
/** Peripheral PTG base pointer */
#define PTG                                      ((GPIO_Type *)PTG_BASE)
/** Peripheral PTH base address */
#define PTH_BASE                                 (0xFFFC170Eu)
/** Peripheral PTH base pointer */
#define PTH                                      ((GPIO_Type *)PTH_BASE)
/** Peripheral PTI base address */
#define PTI_BASE                                 (0xFFFC1710u)
/** Peripheral PTI base pointer */
#define PTI                                      ((GPIO_Type *)PTI_BASE)
/** Peripheral PTJ base address */
#define PTJ_BASE                                 (0xFFFC1712u)
/** Peripheral PTJ base pointer */
#define PTJ                                      ((GPIO_Type *)PTJ_BASE)
/** Peripheral PTK base address */
#define PTK_BASE                                 (0xFFFC1714u)
/** Peripheral PTK base pointer */
#define PTK                                      ((GPIO_Type *)PTK_BASE)
/** Peripheral PTL base address */
#define PTL_BASE                                 (0xFFFC1716u)
/** Peripheral PTL base pointer */
#define PTL                                      ((GPIO_Type *)PTL_BASE)
/** Peripheral PTM base address */
#define PTM_BASE                                 (0xFFFC1718u)
/** Peripheral PTM base pointer */
#define PTM                                      ((GPIO_Type *)PTM_BASE)
/** Peripheral PTN base address */
#define PTN_BASE                                 (0xFFFC171Au)
/** Peripheral PTN base pointer */
#define PTN                                      ((GPIO_Type *)PTN_BASE)
/** Peripheral PTO base address */
#define PTO_BASE                                 (0xFFFC171Cu)
/** Peripheral PTO base pointer */
#define PTO                                      ((GPIO_Type *)PTO_BASE)
/** Peripheral PTP base address */
#define PTP_BASE                                 (0xFFFC171Eu)
/** Peripheral PTP base pointer */
#define PTP                                      ((GPIO_Type *)PTP_BASE)
/** Peripheral PTQ base address */
#define PTQ_BASE                                 (0xFFFC1720u)
/** Peripheral PTQ base pointer */
#define PTQ                                      ((GPIO_Type *)PTQ_BASE)
/** Array initializer of GPIO peripheral base addresses */
#define GPIO_BASE_ADDRS                          { PTA_BASE, PTB_BASE, PTC_BASE, PTD_BASE, \
                                                   PTE_BASE, PTF_BASE, PTG_BASE, PTH_BASE, \
                                                   PTI_BASE, PTJ_BASE, PTK_BASE, PTL_BASE, \
                                                   PTM_BASE, PTL_BASE, PTO_BASE, PTP_BASE, \
                                                   PTQ_BASE}
/** Array initializer of GPIO peripheral base pointers */
#define GPIO_BASE_PTRS                           { PTA, PTB, PTC, PTD, PTE, PTF, PTG, PTH, \
                                                   PTI, PTJ, PTK, PTL, PTM, PTN, PTO, PTP, \
                                                   PTQ }

/** PORT - Register Layout Typedef */
typedef struct {
  __IO  uint32_t MSCR[16];
} PORT_Type;

#define SIUL2_MSCR_BASE                          (SIUL2->MSCR)
#define SIUL2_IMCR_BASE                          (SIUL2->IMCR)
#define PORTA                                    ((PORT_Type *)(SIUL2_MSCR_BASE+0x00))
#define PORTB                                    ((PORT_Type *)(SIUL2_MSCR_BASE+0x10))
#define PORTC                                    ((PORT_Type *)(SIUL2_MSCR_BASE+0x20))
#define PORTD                                    ((PORT_Type *)(SIUL2_MSCR_BASE+0x30))
#define PORTE                                    ((PORT_Type *)(SIUL2_MSCR_BASE+0x40))
#define PORTF                                    ((PORT_Type *)(SIUL2_MSCR_BASE+0x50))
#define PORTG                                    ((PORT_Type *)(SIUL2_MSCR_BASE+0x60))
#define PORTH                                    ((PORT_Type *)(SIUL2_MSCR_BASE+0x70))
#define PORTI                                    ((PORT_Type *)(SIUL2_MSCR_BASE+0x80))
#define PORTJ                                    ((PORT_Type *)(SIUL2_MSCR_BASE+0x90))
#define PORTK                                    ((PORT_Type *)(SIUL2_MSCR_BASE+0xA0))
#define PORTL                                    ((PORT_Type *)(SIUL2_MSCR_BASE+0xB0))
#define PORTM                                    ((PORT_Type *)(SIUL2_MSCR_BASE+0xC0))
#define PORTN                                    ((PORT_Type *)(SIUL2_MSCR_BASE+0xD0))
#define PORTO                                    ((PORT_Type *)(SIUL2_MSCR_BASE+0xE0))
#define PORTP                                    ((PORT_Type *)(SIUL2_MSCR_BASE+0xF0))
#define PORTQ                                    ((PORT_Type *)(SIUL2_MSCR_BASE+0x100))
#define PORT_BASE_PTRS                           { PORTA, PORTB, PORTC, PORTD, PORTE, PORTF, \
                                                   PORTG, PORTH, PORTI, PORTJ, PORTK, PORTL, \
                                                   PORTM, PORTN, PORTO, PORTP, PORTQ }

/*                  PA3, PA6, PA7,  PA8, PA14, PC2, PC3, PC5, PC14,  PE4, PE10, PE12, PE14, PF15, PG1, PG8,*/
#define PORT_IRQS   {3,    6,   7,    8,   14,  34,  35,  37,   46,   68,   74,   76,   78,   95,  97, 104, \
                    11,   12,  36,   44,   47,  66,  70,  71,  203,  238,  236,  234,  232,  230, 227, 163}
/*                PA11, PA12, PC4, PC12, PC15, PE2, PE6, PE7, PM11, PO14, PO12, PO10,  PO8,  PO6, PO3, PK3 */

/* DSPI module feature */

/* Define the PCS allocation for each DSPI/SPI module */
#define FEATURE_DSPI_0_PCS_NUMBER 6
#define FEATURE_DSPI_1_PCS_NUMBER 5
#define FEATURE_DSPI_2_PCS_NUMBER 4
#define FEATURE_DSPI_3_PCS_NUMBER 2
#define FEATURE_SPI_0_PCS_NUMBER 4
#define FEATURE_SPI_1_PCS_NUMBER 4
#define FEATURE_SPI_2_PCS_NUMBER 4
#define FEATURE_SPI_3_PCS_NUMBER 4
#define FEATURE_SPI_4_PCS_NUMBER 1
#define FEATURE_SPI_5_PCS_NUMBER 1
#define FEATURE_DSPI_PCS_MAPPING {FEATURE_DSPI_0_PCS_NUMBER, FEATURE_DSPI_1_PCS_NUMBER, \
                                  FEATURE_DSPI_2_PCS_NUMBER, FEATURE_DSPI_3_PCS_NUMBER, \
                                  FEATURE_SPI_0_PCS_NUMBER, FEATURE_SPI_1_PCS_NUMBER, \
                                  FEATURE_SPI_2_PCS_NUMBER, FEATURE_SPI_3_PCS_NUMBER, \
                                  FEATURE_SPI_4_PCS_NUMBER, FEATURE_SPI_5_PCS_NUMBER}

/* Define the instance realocation */
#define FEATURE_DSPI_INSTANCES  {DSPI_0, DSPI_1, DSPI_2, DSPI_3, (DSPI_Type *)SPI_0_BASE, \
                                 (DSPI_Type *)SPI_1_BASE, (DSPI_Type *)SPI_2_BASE, \
                                 (DSPI_Type *)SPI_3_BASE, (DSPI_Type *)SPI_4_BASE, \
                                 (DSPI_Type *)SPI_5_BASE}

/* Define the initial values for state structures */
#define FEATURE_DSPI_INITIAL_STATE {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL}

/* Define clock sources for SPI/DSPI instances */
#define FEATURE_DSPI_CLOCK_MAPPING {DSPI0_CLK, DSPI1_CLK, DSPI2_CLK, DSPI3_CLK, SPI0_CLK, SPI1_CLK,\
	                              SPI2_CLK, SPI3_CLK, SPI4_CLK, SPI5_CLK}

/* Define margins of instances interval */
#define DSPI_LOWEST_INSTANCE 0U
#define DSPI_HIGHEST_INSTANCE 3U
#define SPI_LOWEST_INSTANCE 4U
#define SPI_HIGHEST_INSTANCE 10U

/* On this platform DSPI in extended mode is supported */
#define FEATURE_DSPI_HAS_EXTENDED_MODE 0U

/* Define FIFO size */
#define DSPI_FIFO_SIZE 4U

/* Each interrupt flag has it's own interrupt index */
#define FEATURES_DSPI_HAS_INDEPENDENT_INTERRUPTS 0U

/* Define interrupt vector for dspi */
#define FEATURES_DSPI_SEND_INTERUPT_VECTOR    { DSPI0_TxFifoNotfull_IRQn,  DSPI1_TxFifoNotfull_IRQn,  DSPI2_TxFifoNotfull_IRQn,  DSPI3_TxFifoNotfull_IRQn, SPI0_TxFifoNotfull_IRQn, \
                                                SPI1_TxFifoNotfull_IRQn,   SPI2_TxFifoNotfull_IRQn,   SPI3_TxFifoNotfull_IRQn,   SPI4_TxFifoNotfull_IRQn,  SPI5_TxFifoNotfull_IRQn}

#define FEATURES_DSPI_RECEIVE_INTERUPT_VECTOR { DSPI0_RxFifoNotempty_IRQn, DSPI1_RxFifoNotempty_IRQn, DSPI2_RxFifoNotempty_IRQn, DSPI3_RxFifoNotempty_IRQn, SPI0_RxFifoNotempty_IRQn,  \
                                                SPI1_RxFifoNotempty_IRQn,  SPI2_RxFifoNotempty_IRQn,  SPI3_RxFifoNotempty_IRQn,  SPI4_RxFifoNotempty_IRQn,  SPI5_RxFifoNotempty_IRQn}

#define FEATURES_DSPI_FAULT_INTERUPT_VECTOR   { DSPI0_FifoErr_IRQn,        DSPI1_FifoErr_IRQn,        DSPI2_FifoErr_IRQn,        DSPI3_FifoErr_IRQn,        SPI0_FifoErr_IRQn, \
                                                SPI1_FifoErr_IRQn,         SPI2_FifoErr_IRQn,         SPI3_FifoErr_IRQn,         SPI4_FifoErr_IRQn,         SPI5_FifoErr_IRQn}

/* RTC module features */
#define FEATURE_RTC_MINIMUM_API_VALUE (4UL)
#define FEATURE_RTC_SYNC_TICKS_VALUE  (6UL)
/** Number of interrupt vector arrays for the RTC module. */
#define RTC_IRQS_ARR_COUNT                       (2u)
/** Number of interrupt channels for the RTC module. */
#define RTC_IRQS_CH_COUNT                        (1u)
/** Number of interrupt channels for the API type of RTC module. */
#define RTC_API_IRQS_CH_COUNT                    (1u)
/** Interrupt vectors for the RTC peripheral type */
#define RTC_IRQS                                 { RTC0_IRQn }
#define RTC_API_IRQS                             { API0_IRQn }

/* USDHC module features */

/*! @brief USDHC peripheral clock names */
#define FEATURE_USDHC_CLOCK_NAMES { SDHC0_CLK }
/** Interrupt vectors for the uSDHC peripheral type */
#define uSDHC_IRQS                               { uSDHC0_IRQn }

/* MSCM module features */

/* @brief Has interrupt router control registers (IRSPRCn). */
#define FEATURE_MSCM_HAS_INTERRUPT_ROUTER                (0)
/* @brief Has directed CPU interrupt routerregisters (IRCPxxx). */
#define FEATURE_MSCM_HAS_CPU_INTERRUPT_ROUTER            (0)

/* STM module features */

/*! @brief STM module CR register has CSL bit-field */
#define FEATURE_STM_HAS_CLOCK_SELECTION                  (1U)
/*! @brief Number of interrupt vector for channels of the STM module */
#define FEATURE_STM_HAS_NUM_IRQS_CHANS  (4U)
/*! @brief Clock names for STM. */
#define STM_CLOCK_NAMES    { FS80_CLK, FXOSC_CLK }
/** Interrupt vectors for the STM peripheral type */
#define STM_IRQS                                 {{ STM0_Ch0_IRQn, STM0_Ch1_IRQn, STM0_Ch2_IRQn, STM0_Ch3_IRQn }, \
                                                  { STM1_Ch0_IRQn, STM1_Ch1_IRQn, STM1_Ch2_IRQn, STM1_Ch3_IRQn }, \
                                                  { STM2_Ch0_IRQn, STM2_Ch1_IRQn, STM2_Ch2_IRQn, STM2_Ch3_IRQn }}

/* BCTU module features */

/*! @brief Number of ADC instances which can be triggered by BCTU */
#define FEATURE_BCTU_NUM_ADC                             (2u)
#define FEATURE_BCTU_HAS_CCP                             (0U)

/* ADC module features */

#define FEATURE_ADC_HAS_CTU              (1)
#define FEATURE_ADC_HAS_CTU_TRIGGER_MODE (1)
#define FEATURE_ADC_HAS_EXT_TRIGGER      (0)
#define FEATURE_ADC_HAS_INJ_TRIGGER_SEL  (1)
#define FEATURE_ADC_HAS_THRHLR_ARRAY     (0)
#define FEATURE_ADC_HAS_CWSELR_UNROLLED  (0)
#define FEATURE_ADC_HAS_CALIBRATION_ALT  (0)
#define FEATURE_ADC_HAS_CLKSEL_EXTENDED  (0)

#define ADC_PRESAMPLE_VSS_HV            (ADC_PRESAMPLE_SRC0)     /* Presampling from VSS_HV_ADC0 */
#define ADC_PRESAMPLE_VDD_HV_DIV_8      (ADC_PRESAMPLE_SRC1)     /* Presampling from VDD_HV/ 8 */
#define ADC_PRESAMPLE_VREFL 	        (ADC_PRESAMPLE_SRC2)     /* Presampling from VREFL */
#define ADC_PRESAMPLE_VDD_HV_ADC1_REF   (ADC_PRESAMPLE_SRC3)     /* Presampling from VDD_HV ADC1 */

#define ADC_CLOCKS                      {ADC0_CLK, ADC1_CLK}

/* @brief Number of THRHLR registers. */
#define ADC_THRHLR_COUNT                (6u)
#define ADC_THRHLR_PER_INSTANCE_COUNT   {6u, 3u}
/* @brief Default values for sample time. */
#define ADC_DEF_SAMPLE_TIME_0           (0x14U)
#define ADC_DEF_SAMPLE_TIME_1           (0x14U)
#define ADC_DEF_SAMPLE_TIME_2           (0x14U)

#define FEATURE_ADC_BAD_ACCESS_PROT_CHANNEL  (1)
                                      /* 31-28   3-0  63-60  35-32 95-92  68-65
                                          \_/    \_/   \_/    \_/   \_/    \_/
                                           |......|     |......|     |......| */
#define FEATURE_ADC_CHN_AVAIL_BITMAP   {{0x003EFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu}, /* ADC0 */ \
                                        {0x0000FFFFu, 0x003EFFFFu, 0xFFFFFFFFu}  /* ADC1 */ \
                                       }

/* ADC PAL features */
#define ADC_PAL_BCTU_LIST_LAST_IRQn      				BCTU_ListLast_IRQn
#define ADC_PAL_BCTU_CONV_UPDATE_IRQ_UNROLLED           (0)


/* PIT module features */

/** Number of interrupt vector arrays for the PIT module. */
#define PIT_IRQS_ARR_COUNT                       (1u)
/** Number of interrupt channels for the PIT module. */
#define PIT_IRQS_CH_COUNT                        (17u)
/** Interrupt vectors for the PIT peripheral type */
#define PIT_IRQS                                 { { PIT_Ch0_IRQn, PIT_Ch1_IRQn, PIT_Ch2_IRQn, PIT_Ch3_IRQn, \
                                                     PIT_Ch4_IRQn, PIT_Ch5_IRQn, PIT_Ch6_IRQn, PIT_Ch7_IRQn, \
                                                     PIT_Ch8_IRQn, PIT_Ch9_IRQn, PIT_Ch10_IRQn, PIT_Ch11_IRQn, \
                                                     PIT_Ch12_IRQn, PIT_Ch13_IRQn, PIT_Ch14_IRQn, PIT_Ch15_IRQn, PIT_RTI_IRQn } }

/*! @brief PIT module has RTI channel */
#define FEATURE_PIT_HAS_RTI_CHANNEL    (1U)
/*! @brief Number of interrupt vector for channels of the PIT module */
#define FEATURE_PIT_HAS_NUM_IRQS_CHANS (PIT_IRQS_CH_COUNT)
/*! @brief PIT module has a peculiar instance */
#define FEATURE_PIT_HAS_PECULIAR_INSTANCE   (0U)
/*! @brief The default value of MDIS bit */
#define PIT_MCR_MDIS_DEFAULT                (1U)
/*! @brief PIT instance has not lifetime timer */
#define PIT_INSTANCE_HAS_NOT_LIFETIME_TIMER      (0U)

#if PIT_INSTANCE_HAS_NOT_LIFETIME_TIMER
/*! @brief PIT instance base has not lifetime timer */
#define PIT_INSTANCE_BASE_HAS_NOT_LIFETIME_TIMER   (PIT_0)
#endif

#if FEATURE_PIT_HAS_PECULIAR_INSTANCE
/*! @brief The peculiar instance */
#define PIT_PECULIAR_INSTANCE    (1U)
/*! @brief The number channel of the peculiar instance */
#define PIT_CHAN_NUM_OF_PECULIAR_INSTANCE   (4U)
#endif

#if FEATURE_PIT_HAS_RTI_CHANNEL
/*! @brief The default value of MDIS-RTI bit */
#define PIT_MCR_MDIS_RTI_DEFAULT            (1U)
/*! @brief Clock names for RTI. */
#define RTI_CLOCK_NAMES    {FXOSC_CLK}
#endif
/*! @brief Clock names for PIT. */
#define PIT_CLOCK_NAMES    {PIT0_CLK}

/* FCCU module features */
#define FEATURE_FCCU_UNLOCK_OP1                (0x913756AFU)
#define FEATURE_FCCU_UNLOCK_OP2                (0x825A132BU)
#define FEATURE_FCCU_UNLOCK_OP31               (0x29AF8752U)

#define FEATURE_FCCU_NCF_KEY                   (0xAB3498FEU)

#define FEATURE_FCCU_IRQ_EN_MASK               (0x9U)

#define FEATURE_FCCU_TRANS_UNLOCK              (0xBCU)
#define FEATURE_FCCU_PERMNT_LOCK               (0xFFU)
#define FEATURE_FCCU_EINOUT_EOUTX_MASK         (FCCU_EINOUT_EOUTX_MASK)

#define FEATURE_FCCU_MAX_FAULTS_NO             (uint8_t)(71U)
/* FCUU filter feature */
#define FEATURE_FCCU_FILTER_EN                 (1U)
/* FCCU open drain for the error indicating pin(s) */
#define FEATURE_FCCU_OPEN_DRAIN_EN             (1U)
/* FCCU mode controller status */
#define FEATURE_FCCU_CONTROL_MODE_EN           (1U)
/* FCCU redundancy control checker */
#define FEATURE_FCCU_RCC_EN                    (0U)

/* WKPU module features */

/* @brief WKPU core source. */
typedef enum
{
    WKPU_CORE0       = 0U,    /*!< Core 0 */
    WKPU_CORE1       = 1U,    /*!< Core 1 */
    WKPU_CORE2       = 2U    /*!< Core 2 */
} wkpu_core_t;

/* @brief The WKPU core array */
#define FEATURE_WKPU_CORE_ARRAY      \
{                                    \
    WKPU_CORE0,    /*!< Core 0 */    \
    WKPU_CORE1,    /*!< Core 1 */    \
    WKPU_CORE2     /*!< Core 2 */    \
}

/*! @brief WKPU module support reset to MC_RGM */
#define FEATURE_WKPU_SUPPORT_RESET_REQUEST              (1U)
/*! @brief WKPU module support external interrupt */
#define FEATURE_WKPU_SUPPORT_INTERRUPT_REQUEST          (2U)
/*! @brief The number core support for WKPU module */
#define FEATURE_WKPU_NMI_NUM_CORES                      (3U)
/*! @brief The reset position */
#define FEATURE_WKPU_RESET_POSITION                     (3U)
/*! @brief The distance between cores */
#define FEATURE_WKPU_CORE_OFFSET_SIZE                   (8U)
/*! @brief The maximum channel count */
#define FEATURE_WKPU_MAX_CHANNEL_COUNT                  (32U)
/*! @brief WKPU support non-maskable interrupt */
#define FEATURE_WKPU_SUPPORT_NON_MASK_INT               (1U)
/*! @brief WKPU support critical interrupt */
#define FEATURE_WKPU_SUPPORT_CRITICAL_INT               (2U)
/*! @brief WKPU support machine check request interrupt */
#define FEATURE_WKPU_SUPPORT_MACHINE_CHK_REQ            (3U)
/*! @brief WKPU  isn't generated NMI, critical interrupt, or machine check request  */
#define FEATURE_WKPU_SUPPORT_NONE_REQUEST               (4U)
/** Interrupt vectors for the WKPU peripheral type */
#define WKPU_IRQS                                { WKPU_07_00_IRQn, WKPU_15_08_IRQn, WKPU_23_16_IRQn, WKPU_31_24_IRQn }

/* PASS module features */

/* @brief Has Region 0 */
#define FEATURE_PASS_HAS_RL0                  (0U)
/* @brief Has Region 1 */
#define FEATURE_PASS_HAS_RL1                  (1U)
/* @brief Has Region 2 */
#define FEATURE_PASS_HAS_RL2                  (2U)
/* @brief Has Region 3 */
#define FEATURE_PASS_HAS_RL3                  (3U)
/* @brief Has Region 4 */
#define FEATURE_PASS_HAS_RL4                  (4U)

/* I2S module features */

#define I2S_TX_IRQS                              {I2S_0_Tx_IRQn, I2S_1_Tx_IRQn, I2S_2_Tx_IRQn}
#define I2S_RX_IRQS                              {I2S_0_Rx_IRQn, I2S_1_Rx_IRQn, I2S_2_Rx_IRQn}

#endif /* MPC5748G_FEATURES_H */

/*******************************************************************************
 * EOF
 ******************************************************************************/
