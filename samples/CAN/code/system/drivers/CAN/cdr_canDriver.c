/**
 * @file cdr_canDriver.c
 * CAN communication driver for DEVKIT-MPC5748G and safe-RTOS. Main file of implementation.
 * It instantiates the constant configuration data object, initializes the driver according
 * to the configuration settings and offer the global API functions.
 *
 * @remark The CAN driver has been developed for the MPC5748G but it can be used with the
 * MPC5775B/E, too, which have a very similar CAN device. The references to the MCU's
 * Reference Manual made below relate to the reference manual of the MPC5748G.
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
 *   cdr_getNoFIFOFilterEntries (global inline)
 *   cdr_getIdxOfFirstNormalMailbox (global inline)
 *   cdr_getMailboxByIdx (global inline)
 *   cdr_osInitCanDriver
 *   cdr_osMakeMailboxReservation
 *   cdr_osSendMessage_idMB
 *   cdr_osSendMessage
 *   cdr_osSendMessageEx
 *   cdr_osReadMessage_idMB
 *   cdr_osReadMessage
 *   cdr_testSend_task10ms
 * Local functions
 *   getFIFOFilterEntry
 *   configSIULForUseWithDEVKIT_MPC5748G
 *   configSIUForUseWithMPC5775BE_416DS
 *   getBaudRateSettings
 *   osPrepareSendMessage
 */

/*
 * Include files
 */

#include <stddef.h>
#include <string.h>
#include <limits.h>
#include <assert.h>

#include "cdr_canDriver.h"
#include "cde_canDriver.config.MCUDerivative.h"
#include "typ_types.h"
#include "siu_siuPortDriver.h"
#include "sio_serialIO.h"
#include "ccl_configureClocks.h"
#include "cdr_checkConfig.h"
#include "cdr_interruptServiceHandlers.h"
#include "cdr_canDriverAPI.h"


/*
 * Defines
 */

#if defined(MCU_MPC5748G)
/** Initializer expression for an entry of the array \a cdr_canDriverData. */
# define INIT_CAN_DEVICE_DATA(canDev)   \
    [cdr_canDev_##canDev] =             \
    {                                   \
        .isBusOff = false,              \
        .noRxFIFOOverflowEvents = 0,    \
        .noRxFIFOWarningEvents = 0,     \
        .noRxMsgsFIFO = 0,              \
    },
#elif defined(MCU_MPC5775B)  ||  defined(MCU_MPC5775E)
/** Initializer expression for an entry of the array \a cdr_canDriverData. */
# define INIT_CAN_DEVICE_DATA(canDev)   \
    [cdr_canDev_##canDev] =             \
    {                                   \
        .noRxFIFOOverflowEvents = 0,    \
        .noRxFIFOWarningEvents = 0,     \
        .noRxMsgsFIFO = 0,              \
    },
#endif


/*
 * Local type definitions
 */

/*
 * Local prototypes
 */


/*
 * Data definitions
 */

/* Read the source code include file, which defines the large configuration data set. */
#define CDR_IS_INCLUDED_FROM_DRIVER_IMPLEMENTATION
#include "cdr_canDriver.config.inc"

/** This is a lookup table, which maps a zero based CAN device index (enumeration
    cdr_enumCanDevice_t) to a CAN peripheral (according to MPC5748G.h) */
cdr_idCanDevice_t const RODATA(cdr_mapIdxToCanDevice)[cdr_canDev_noCANDevicesEnabled] =
{
#if CDR_ENABLE_USE_OF_CAN_0 == 1
    { .idxFlexCAN_x = 0u, .pCanDevice = CAN_0, },
#endif
#if CDR_ENABLE_USE_OF_CAN_1 == 1
    { .idxFlexCAN_x = 1u, .pCanDevice = CAN_1, },
#endif
#if CDR_ENABLE_USE_OF_CAN_2 == 1
    { .idxFlexCAN_x = 2u, .pCanDevice = CAN_2, },
#endif
#if CDR_ENABLE_USE_OF_CAN_3 == 1
    { .idxFlexCAN_x = 3u, .pCanDevice = CAN_3, },
#endif
#if CDR_ENABLE_USE_OF_CAN_4 == 1
    { .idxFlexCAN_x = 4u, .pCanDevice = CAN_4, },
#endif
#if CDR_ENABLE_USE_OF_CAN_5 == 1
    { .idxFlexCAN_x = 5u, .pCanDevice = CAN_5, },
#endif
#if CDR_ENABLE_USE_OF_CAN_6 == 1
    { .idxFlexCAN_x = 6u, .pCanDevice = CAN_6, },
#endif
#if CDR_ENABLE_USE_OF_CAN_7 == 1
    { .idxFlexCAN_x = 7u, .pCanDevice = CAN_7, },
#endif
};


/** The run-time data of the CAN driver.\n
      The principal structure of the object is an array of objects of class \a
    cdr_canDeviceData_t, which hold the run-time data for a single CAN device (the
    devices are operated widely independent from one another). */
cdr_canDriverData_t DATA_OS(cdr_canDriverData) =
{
#if CDR_ENABLE_USE_OF_CAN_0 == 1
    INIT_CAN_DEVICE_DATA(CAN_0)
#endif
#if CDR_ENABLE_USE_OF_CAN_1 == 1
    INIT_CAN_DEVICE_DATA(CAN_1)
#endif
#if CDR_ENABLE_USE_OF_CAN_2 == 1
    INIT_CAN_DEVICE_DATA(CAN_2)
#endif
#if CDR_ENABLE_USE_OF_CAN_3 == 1
    INIT_CAN_DEVICE_DATA(CAN_3)
#endif
#if CDR_ENABLE_USE_OF_CAN_4 == 1
    INIT_CAN_DEVICE_DATA(CAN_4)
#endif
#if CDR_ENABLE_USE_OF_CAN_5 == 1
    INIT_CAN_DEVICE_DATA(CAN_5)
#endif
#if CDR_ENABLE_USE_OF_CAN_6 == 1
    INIT_CAN_DEVICE_DATA(CAN_6)
#endif
#if CDR_ENABLE_USE_OF_CAN_7 == 1
    INIT_CAN_DEVICE_DATA(CAN_7)
#endif
};
#undef INIT_CAN_DEVICE_DATA


/*
 * Function implementation
 */


/**
 * Get an entry from the FIFO filter table. In our configuration, an entry is of type A
 * only. Effectively it is the CAN ID, which can be received through the FIFO. See RM
 * 43.4.43, Tables 43-17 and 43-18, on p. 1786 for details.
 *   @return
 * The pointer to the filter entry is returned. The result is undefined if the FIFO is not
 * enabled.
 *   @param pCanDevice
 * The CAN device in use is passed by reference. It'll be one entry out of #CAN_BASE_PTRS
 * (see MPC5748G.h); this is however not checked.
 *   @param idxFilterEntry
 * The index of the filter entry.\n
 * The range is 0..max, which is checked by assertion. "max" depends on the FIFO
 * configuration. In our default configuration (CTRL2[RFFN]=8) it is 71. See RM 43.4.14, p.
 * 1740.
 *   @remark
 * The current configuration of the device, e.g. FIFO enabled or not or the filter table
 * size, is not considered by the function. It just provides the simple address
 * calculation.
 */
static inline uint32_t *getFIFOFilterEntry( const CAN_Type * const pCanDevice
                                          , unsigned int idxFilterEntry
                                          )
{
    /* The filter table starts a byte offset 0xe0, the RAM starts at byte offset 0x80. */
    return (uint32_t*)((uint8_t*)&pCanDevice->RAMn[0]
                       + (0xe0 - 0x80)
                       + idxFilterEntry*sizeof(uint32_t)
                      );
} /* End of getFIFOFilterEntry */





#if CDR_ENABLE_MCU_PINS_FOR_EVAL_BOARD == 1  &&  CDR_ENABLE_USE_OF_CAN_0 == 1
# if defined(MCU_MPC5748G)
/**
 * Do the configuration of the MCU pins such that CAN device CAN_0 can communicated through
 * the CAN transceiver, which is mounted on the evaluation board DEVKIT_MPC5748G.\n
 *   The code in this function is not generally usable.
 */
static void configSIULForUseWithDEVKIT_MPC5748G(void)
{
    /* RM 15.2.11, Multiplexed Signal Configuration Register, p. 388ff: Route Tx output of
       device CAN_0 to MCU pin PB0, which is connected to the Tx input of the external
       transceiver chip on the board DEVKIT-MPC5748G. */
    const unsigned int idxSIUL_PB0 = 16
                     , idxSIUL_PB1 = 17
                     , idxIMCR_PB1 = 188;

    /* Configuration of Tx port. */
    const siu_portOutCfg_t outputCfg =
        {
          .idxPortSource_SSS = 1u, /* Source signal is CAN0_TX */
          .enableReadBack = false,
          .enableOpenDrain_ODE = false, /* Disable open drain, drive both edges */
          .maxSlewRate_SRC = 3u, /* Slew rate: Full drive without SR control */
        };

    /* Acquire Tx port for exclusive use with this driver. */
    bool gotIt ATTRIB_DBG_ONLY = siu_osAcquirePort(idxSIUL_PB0);
    assert(gotIt);

    /* Configure Tx port. */
    siu_osConfigureOutput(idxSIUL_PB0, &outputCfg);
    

    /* The Rx output of external transceiver chip is connected to pin PB1 of the MCU.
       Configure this pin as input.*/
    const siu_portInCfg_t inputCfg =
        { .enableHysteresis_HYS = true,
          .pullUpDownCfg = siu_pullRes_none,
          .idxMultiplexerRegister = idxIMCR_PB1,    /* Connect CAN0_RX with ... */
          .idxInputSource_MUXSELVALUE = 2u,         /* ... IO_PAD PB1 */
        };

    /* Acquire Rx port for exclusive use with this driver. */
    gotIt = siu_osAcquirePort(idxSIUL_PB1);
    assert(gotIt);

    /* Configure Rx port. */
    siu_osConfigureInput(idxSIUL_PB1, &inputCfg);

} /* End of configSIULForUseWithDEVKIT_MPC5748G */

# else

/**
 * Do the configuration of the MCU pins such that CAN device CAN_0 can communicated through
 * the CAN transceiver, which is mounted on the evaluation board MPC5775BE_416DS.\n
 *   The code in this function is not generally usable.
 */
static void configSIUForUseWithMPC5775BE_416DS(void)
{
    /* Enable the the MCU pins, which are connected to the CAN transceiver mounted on the
       evaluation board (see schematics of MPC5775BE-416DS, SPF-32229.pdf, p. 5).
         The configuration of in- and output pins is documented in the Excel workbook
       MPC5775B_MPC5775E_System_IO_Definition.xlsx; which is embedded into the MCU
       reference manual PDF file. In Acrobat Reader, click View/Show/Hide/Navigation
       Panes/Attachments to find the Excel workbook.
         In the Excel workbook, on worksheet "IO Signal Table", each line refers to one of
       the possible functions of a port. The port is found in column A and most relevant
       are the settings "SIU_A PCR#" in column B, and "PCR PA" in column C. They designate
       the index of the PCR register to use and the source selection, which is a major
       field of this register.
         The port has a fixed, hardwired, however chip-housing dependent one-by-one
       relation with a pin. This relation is found in columns I and J and on tab "416
       PBGA".
         The source selection relates to the connection from an I/O device to the output
       buffer of the port.
         To connect an input of an I/O device with a port, a selection of one out of
       different offered input sources needs to be made besides the port configuration
       itself. Selecting the wanted input means configuring an input multiplexer register.
       There are nine such registers and they contain a varying number of multiplexers
       each. You need to know, which multiplexer register to use and which multiplxer
       inside the register and which value to configure for this multiplexer. All of this
       is found either in the description of the registers (RM, sections 8.2.66ff) or by
       name of the signal in the Excel workbook
       MPC5775B_MPC5775E_System_IO_Definition.xlsx, worksheet "Input Muxing". In the Excel
       worksheet look for the wanted device (column B, "Instance") and/or for the wanted
       signal (column H, "Source Signal"). Columns D, E and F provide the needed three
       pieces of information for the multiplxer configuration. */
       
    /* Configuration of CAN Tx port: See file MPC5775B_MPC5775E_System_IO_Definition.xlsx,
       tab "IO Signal Table", row 663, for port CNTXA. Column B gives us the index of the
       PCR. Column C gives us as "Source Signal Select" for function CAN Tx of device 0
       (aka A).
         SIU->PCR: See RM, 8.2.13 Pad Configuration Register (SIU_PCRn), p. 241ff. */
    const siu_portOutCfg_t outputCfg =
        {
          .idxPortSource_PA = 1u, /* Source signal is FlexCAN A Transmit */
          .enableReadBack = false,
          .enableOpenDrain_ODE = false, /* Disable open drain, drive both edges */
          .driveStrength_DSC = 3u, /* 0..3: Drive strength from min to max */
          .maxSlewRate_SRC = 3u, /* Slew rate: Full drive without SR control */
        };

    /* Acquire Tx port for exclusive use with this driver. */
    bool gotIt ATTRIB_DBG_ONLY = siu_osAcquirePort(/* idxPort */ 83 /* CNTXA */);
    assert(gotIt);

    /* Configure Tx port. */
    siu_osConfigureOutput(/* idxPort */ 83 /* CNTXA */, &outputCfg);
    

    /* CAN Rx: See file MPC5775B_MPC5775E_System_IO_Definition.xlsx, tab "Input Muxing",
       row 33, for port CNRXA. We find multiplexer register no 1, MUXSEL=0, MUXSEL
       Value=1.
         See 8.2.67 Input Multiplexing Register1 (SIU_IMUX1), p. 375f, for setting of the
       multiplexer. The register description confirms the right understanding of the Excel
       table. */

    /* The Rx output of external transceiver chip is connected to pin AE19 (GPIO84) of the
       MCU. Configure this pin as input.*/
    const siu_portInCfg_t inputCfg =
        { .idxPortSource_PA = 1u,           /* Source 1: FlexCAN A Receive */
          .enableHysteresis_HYS = true,
          .pullUpDownCfg = siu_pullRes_none,
          .idxMultiplexerRegister = SIU_INPUT_MULTIPLEXER_UNUSED, /* No mux required. */
          .idxMultiplexer = 0u,
          .idxInputSource_MUXSELVALUE = 0u,
        };

    /* Acquire Rx port for exclusive use with this driver. */
    gotIt = siu_osAcquirePort(/* idxPort */ 84 /* CNRXA */);
    assert(gotIt);

    /* Configure Rx port. */
    siu_osConfigureInput(/* idxPort */ 84 /* CNRXA */, &inputCfg);

} /* End of configSIUForUseWithMPC5775BE_416DS */

# endif /* Which MCU derivative */
#endif /* CDR_ENABLE_USE_OF_CAN_0 == 1 */




/**
 * Helper function: Figure out, how to set the prescaler and counter registers of the
 * device to achieve a given Baud rate.\n
 *  The function doesn't return an error. All possible fault conditions have been checked
 * before.
 *   @param pPRESDIV
 * The required value PRESDIV is returned by reference.
 *   @param pPROPSEG
 * The required value PROPSEG is returned by reference.
 *   @param pPSEG1
 * The required value PSEG1 is returned by reference.
 *   @param pPSEG2
 * The required value PSEG2 is returned by reference.
 *   @param baudRate
 * The desired Baud rate in the unit 10 kBd.
 */
static void getBaudRateSettings( unsigned int * const pPRESDIV
                               , unsigned int * const pPROPSEG
                               , unsigned int * const pPSEG1
                               , unsigned int * const pPSEG2
                               , unsigned int baudRate
                               )
{
    /* Bit-Timing: See RM 43.5.9.7, p. 1823ff and in particular Figure 43-7, p. 1826.
         A CAN bit is splitted into two halfs to set the 1 or 3 sample points somewhere in
       the middle. All units are the "time quantum", which is the "serial clock", the input
       clock diveded by (PRESDIV+1). We choose 5 MHz as serial clock or 200ns as time
       quantum.
         The time span prior to sampling (in case of taking 1 sample) has a length of
       PROPSEG+PSEG1+3 quanta and the time after has PSEG2+1 quanta. (The constant
       addends result from the encoding of the registers; register+1 yields time
       designation.)
         Note, if three samples are taken then the additional two occur at two and one time
       quantum earlier than with one sample. */
    #define BD250_CAN_BD_RATE 250000
    #define BD250_PRESDIV     9
    #define BD250_PROPSEG     6
    #define BD250_PSEG1       3
    #define BD250_PSEG2       3
    _Static_assert( ((float)(BD250_PRESDIV+1)/CCL_XTAL_CLK) /* time quantum in s as float */
                    * (BD250_PROPSEG+BD250_PSEG1+3 + BD250_PSEG2+1) /* no quant. per CAN bit */
                    == 1.0f/BD250_CAN_BD_RATE
                  , "CAN timer configuration doesn't hit intended Baud rate 250 kBd"
                  );

    #define BD500_CAN_BD_RATE 500000
    #define BD500_PRESDIV     4
    #define BD500_PROPSEG     6
    #define BD500_PSEG1       3
    #define BD500_PSEG2       3
    _Static_assert( ((float)(BD500_PRESDIV+1)/CCL_XTAL_CLK) /* time quantum in s as float */
                    * (BD500_PROPSEG+BD500_PSEG1+3 + BD500_PSEG2+1) /* no quant. per CAN bit */
                    == 1.0f/BD500_CAN_BD_RATE
                  , "CAN timer configuration doesn't hit intended Baud rate 500 kBd"
                  );

    #define BD1000_CAN_BD_RATE 1000000
    #define BD1000_PRESDIV     4
    #define BD1000_PROPSEG     2
    #define BD1000_PSEG1       1
    #define BD1000_PSEG2       1
    _Static_assert( ((float)(BD1000_PRESDIV+1)/CCL_XTAL_CLK) /* time quantum in s as float */
                    * (BD1000_PROPSEG+BD1000_PSEG1+3 + BD1000_PSEG2+1) /* no quant. per bit */
                    == 1.0f/BD1000_CAN_BD_RATE
                  , "CAN timer configuration doesn't hit intended Baud rate 1 MBd"
                  );

    switch(baudRate)
    {
    case 25:
        *pPRESDIV = BD250_PRESDIV;
        *pPROPSEG = BD250_PROPSEG;
        *pPSEG1   = BD250_PSEG1;
        *pPSEG2   = BD250_PSEG2;
        break;

    default:
        assert(false);
    case 50:
        *pPRESDIV = BD500_PRESDIV;
        *pPROPSEG = BD500_PROPSEG;
        *pPSEG1   = BD500_PSEG1;
        *pPSEG2   = BD500_PSEG2;
        break;

    case 100:
        *pPRESDIV = BD1000_PRESDIV;
        *pPROPSEG = BD1000_PROPSEG;
        *pPSEG1   = BD1000_PSEG1;
        *pPSEG2   = BD1000_PSEG2;
        break;
    }



} /* End of getBaudRateSettings */



/**
 * Initialization of one CAN device. This function is called once per enabled CAN device
 * from the driver initialization.
 *   @return
 * \a true, if function succeeded, else \a false.
 *   @param idxCanDevice
 * The CAN device to initialize by index. The available index range depends on the
 * configuration of the set of enabled CAN devices, see e.g. #CDR_ENABLE_USE_OF_CAN_0. The
 * most convenient way to provide the appropriate index is using enumeration
 * cdr_enumCanDevice_t.
 *   @remark
 * Needs to be called from supervisor code only.
 */
static void initCanDevice(unsigned int idxCanDevice)
{
    /* Look up the CAN device and the related driver configuration. */
    _Static_assert( sizeOfAry(cdr_canDriverConfig) == sizeOfAry(cdr_mapIdxToCanDevice)
                  , "Invalid CAN driver configuration"
                  );
    assert(idxCanDevice < sizeOfAry(cdr_canDriverConfig));
    CAN_Type * const pCanDevice = cdr_mapIdxToCanDevice[idxCanDevice].pCanDevice;
    const cdr_canDeviceConfig_t * const pCanDevConfig = &cdr_canDriverConfig[idxCanDevice];

    /* RM 43.6.1, initialization: First, we need to bring the device in disabled mode to
       set the clock source. On leaving the disabled mode, the device automatically enters
       the freeze mode, which is a prerequisite for being able to write the majority of
       registers. After configuration of all needed registers, we leave the freeze mode and
       the device becomes active.
         Note, a (soft) reset of the device is possible. Maybe, we need to consider it if
       we implement a re-initialization of the driver. The current implementation is proven
       only after out-of-reset. */

    /* Demand disable mode by setting the bit MDIS and wait for acknowledge. */
    pCanDevice->MCR |= CAN_MCR_MDIS_MASK;
    #define STS_MASK_DISABLED   (CAN_MCR_MDIS_MASK | CAN_MCR_NOTRDY_MASK | CAN_MCR_LPMACK_MASK)
    while((pCanDevice->MCR & STS_MASK_DISABLED) != STS_MASK_DISABLED)
        ;
    #undef STS_MASK_DISABLED

    /* Select the clock input. The device can be clocked either by the peripheral clock or
       by the external crystal oscillator. The RM (43.5.9.7 Protocol timing, p. 1824)
       recommends the crystal clock because of lower jitter. Note, this setting must not be
       changed without adapting dependent settings below; in particular the time quantum
       must not be altered - most other timing parameter refer to it as unit.
         0: External crystal oscillator, 1: peripheral clock. */
#define CLKSRC  0
    pCanDevice->CTRL1 = pCanDevice->CTRL1 & ~CAN_CTRL1_CLKSRC_MASK | CAN_CTRL1_CLKSRC(CLKSRC);

    /* End the disabled mode, go into the freeze mode and wait for according acknowledge. */
    pCanDevice->MCR &= ~CAN_MCR_MDIS_MASK;
    #define STS_MASK_FROZEN (CAN_MCR_FRZACK_MASK | CAN_MCR_HALT_MASK | CAN_MCR_NOTRDY_MASK )
    while((pCanDevice->MCR & STS_MASK_FROZEN) != STS_MASK_FROZEN)
        ;
    #undef STS_MASK_FROZEN

    /* RM 43.4.12f and 43.4.21, Interrupt Flags 2/1/3 register (CAN_IFLAG2/1/3): We need to
       reset all interrupt flags prior to setting the number of mailboxes in use. */
    pCanDevice->IFLAG1 = CAN_IFLAG1_BUF31TO8I_MASK
                         | CAN_IFLAG1_BUF7I_MASK
                         | CAN_IFLAG1_BUF6I_MASK
                         | CAN_IFLAG1_BUF5I_MASK
                         | CAN_IFLAG1_BUF4TO1I_MASK
                         | CAN_IFLAG1_BUF0I_MASK
                         ;
#if defined(MCU_MPC5748G)
    pCanDevice->IFLAG2 = CAN_IFLAG2_BUF63TO32I_MASK;
    pCanDevice->IFLAG3 = CAN_IFLAG3_BUF95TO64_MASK;
#elif defined(MCU_MPC5775B) || defined(MCU_MPC5775E)
    pCanDevice->IFLAG2 = CAN_IFLAG2_BUFHI_MASK;
#else
# error Migration needed for this MCU derivative
#endif
    /* For now, we don't support CAN FD. A generic configuration is difficult due to the
       different message sizes and augmented bit rates. They depend on the concrete network
       and shaping an all supporting, generic API is difficult and would likely suffer from
       reduced usability. Moreover, CAN FD would not allow using the Rx queue, which is
       most suitable for our CAN stack. */
    pCanDevice->MCR = CAN_MCR_MDIS(0)       /* For now keep device disabled. */
                      | CAN_MCR_FRZ(1)      /* During configuration, we need to stay frozen */
                      | CAN_MCR_RFEN(pCanDevConfig->isFIFOEnabled)/* Enable FIFO? Note, FIFO
                                                                     not compatible with FD */
                      | CAN_MCR_HALT(1)     /* 1: Stay in halted mode for now */
#if defined(MCU_MPC5748G)
                      | CAN_MCR_WAKMSK(0)   /* No wakeup IRQ needed */
#endif
                      | CAN_MCR_SOFTRST(0)  /* No reset needed */
                      | CAN_MCR_SUPV(1)     /* No access by user mode code permitted */
#if defined(MCU_MPC5748G)
                      | CAN_MCR_SLFWAK(0)   /* Self wake up: We have no implementation of low
                                               power/active mode switches */
#endif
                      | CAN_MCR_WRNEN(0)    /// @todo TBC: Do we need a warn IRQ?
#if defined(MCU_MPC5748G)
                      | CAN_MCR_WAKSRC(0)   /* Wake-up source doesn't matter; we don't use
                                               wake-up for now. */
#else
                      | CAN_MCR_DOZE(0)     /* Doze mode enable: We use reset value 0, no. */
#endif
                      | CAN_MCR_SRXDIS(0)   /* Disable reception of Tx messages in other Rx
                                               mailbox? 0: No, Rx of own Tx is allowed */
                      | CAN_MCR_IRMQ(1)     /* Matching MB vs. FIFO: 1: Most natural
                                               descisions. See RM, Table 43-22, p. 1798. */
#if defined(MCU_MPC5748G)
                      | CAN_MCR_DMA(0)      /* DMA not compatible with FD */
                      | CAN_MCR_PNET_EN(0)  /* Pretended network functionality doesn't
                                               matter, we don't implement a halt state. */
#endif
                      | CAN_MCR_LPRIOEN(0)  /* 0: We use priority handling by CAN ID only */
                      | CAN_MCR_AEN(1)      /* 1: Overwriting a Tx MB is possible as long as
                                               serialization has not yet started. (43.5.7.1) */
#if defined(MCU_MPC5748G)
                      | CAN_MCR_FDEN(0)     /* 0: Standard CAN Protocol, 1: CAN FD */
#endif
                      | CAN_MCR_IDAM(0)     /* ID acceptance mode: 0: Mask of full length */
                      | CAN_MCR_MAXMB(pCanDevConfig->noMailboxes) /* MBs in use including
                                                                     those, whose space is
                                                                     occupied by FIFO and its
                                                                     filters. */
                      ;

    /* PE clock is the clock input chosen already before in bit CLKSRC. We use the external
       crystal i.e. 40 MHz on the board DEVKIT-MPC5748G. */
    _Static_assert( CCL_XTAL_CLK == 40000000u
                  , "Configuration of CAN driver doesn't suit for the given board"
                  );

    /* Get the bit timing controlling device parameters. The function call implements a
       table lookup for the supported Baud rates. */
    unsigned int PRESDIV
               , PROPSEG
               , PSEG1
               , PSEG2;
    getBaudRateSettings(&PRESDIV, &PROPSEG, &PSEG1, &PSEG2, pCanDevConfig->baudRate);

    /* RM 43.4.8 Error Counter, p. 1725f, reset all error counters. */
    pCanDevice->ECR = CAN_ECR_RXERRCNT(0)
                      | CAN_ECR_TXERRCNT(0)
#if defined(MCU_MPC5748G)
                      | CAN_ECR_RXERRCNT_FAST(0)
                      | CAN_ECR_TXERRCNT_FAST(0)
#endif
                      ;
    /* The error/status word CAN_ESR1 contains some interrupt flag bits, which we reset by
       w1c. We do this, before we enable the interrupts by setting CTRL1/2.*/
    pCanDevice->ESR1 = 0
#if defined(MCU_MPC5748G)
                       | CAN_ESR1_ERROVR_MASK
                       | CAN_ESR1_ERRINT_FAST_MASK
                       | CAN_ESR1_BOFFDONEINT_MASK
#endif
                       | CAN_ESR1_TWRNINT_MASK
                       | CAN_ESR1_RWRNINT_MASK
                       | CAN_ESR1_BOFFINT_MASK
                       | CAN_ESR1_ERRINT_MASK
#if defined(MCU_MPC5748G)
                       | CAN_ESR1_WAKINT_MASK
#endif
                       ;
    //pCanDevice->ESR2 is a read-only status register. (RM 43.4.15, p. 1742f.)

    unsigned int u;
    
#if defined(MCU_MPC5775B) || defined(MCU_MPC5775E)
    /* Initialize all device RAM by unconditional 32 Bit writes in order to avoid ECC
       errors with uninitialized cells (and arbitrarily set parity bits). See RM75, 37.5.13
       Detection and Correction of Memory Errors, pp.1756ff. */
    pCanDevice->CTRL2 = pCanDevice->CTRL2
                        | CAN_CTRL2_WRMFRZ(1); /* Device RAM writable in freeze mode? */
    const uint32_t no32BitWords = CAN_PHYSICAL_RAMn_COUNT;
    _Static_assert( sizeof(pCanDevice->RAMn[0u]) == 4u
                  , "Implementation doesn't support RAM configuration of given CAN device"  
                  );
    volatile uint32_t *pRAM = &pCanDevice->RAMn[0u];
    assert(((uintptr_t)pRAM & 0x00000003u) == 0);
    for(u=0u; u<no32BitWords; ++u)
        * pRAM++ = 0u;

    /* Reset possibly pending ECC errors prior to enabling the related IRQ. See RM75,
       37.4.27 Error Status Register (CAN_ERRSR), pp.1716f. */
    pCanDevice->ERRSR = CAN_ERRSR_HANCEIF_MASK
                        | CAN_ERRSR_FANCEIF_MASK
                        | CAN_ERRSR_CEIF_MASK
                        | CAN_ERRSR_HANCEIOF_MASK
                        | CAN_ERRSR_FANCEIOF_MASK
                        | CAN_ERRSR_CEIOF_MASK
                        ;
#endif /* ECC initialization for MCU_MPC5775B/E */

    /* The interrupt groups for CAN transmission errors (ERRINT and ERRINIT_FAST) and for the
       bus off related errors (bus off/on ad Rx/Tx warning) are enabled by configuration.
       If the priority is above zero, then they are enabled. */
    const bool enableERRIrq = pCanDevConfig->irqGroupError.irqPrio > 0
             , enableBOffIrq = pCanDevConfig->irqGroupBusOff.irqPrio > 0;

    /* RM 43.5.4, p. 1795ff, and in particular Table 43-22, p. 1798f, provide the best
       explanation of the arbitration bits CTRL1[IRMQ] and CTRL2[MRP]. They control, which
       messages go into individual mailboxes and which go into the shared FIFO. Our
       strategy (IRMQ=1, MRP=1) give priority to the MBs. We can have a number of MBs for
       one particular CAN ID and have the FIFO for many more, controlled by the FIFO
       filters.
         The major weakness of the FIFO in comparison to the MB is the acceptance mask.
       Most FIFO entries don't have an individual mask. In our configuration this has no
       negative impact as we anyway set all masks to "all CAN ID bits care", i.e. such that
       we have sharp filtering for particular CAN IDs.
         In our configuration and if the client code configures the driver to use same
       Rx notification callback and same IRQ level for MBs and FIFO then there won't be a
       noticeable difference between MB and FIFO - the only effect of the FIFO is the
       extension of the number of distinguishable, receivable CAN IDs. */
    pCanDevice->CTRL1 = CAN_CTRL1_PRESDIV(PRESDIV)  /* 0..255. SerClk = PEClk/(PRESDIV+1) =
                                                       8 MHz. */
                        | CAN_CTRL1_RJW(3)      /* Resync jump width=n+1, n=0..3. */
                        | CAN_CTRL1_PSEG1(PSEG1)/* PSEG1=n+1, n=0..7. */
                        | CAN_CTRL1_PSEG2(PSEG2)/* PSEG2=n+1, n=0..7. */
                        | CAN_CTRL1_BOFFMSK(enableBOffIrq? 1: 0) /* Bus off IRQ enable */
                        | CAN_CTRL1_ERRMSK(enableERRIrq? 1: 0)   /* Error IRQ enable */
                        | CAN_CTRL1_CLKSRC(CLKSRC) /* Clock: We write same value as above. */
                        | CAN_CTRL1_LPB(0)  /* Enable loop back, a test mode without I/O. */
                        | CAN_CTRL1_TWRNMSK(0)  /* Tx warning IRQ enable */
                        | CAN_CTRL1_RWRNMSK(0)  /* Rx warning IRQ enable */
                        | CAN_CTRL1_SMP(1)  /* 1: Take 3 instead of a single sample, average */
                        | CAN_CTRL1_BOFFREC(0)  /* 0: Enable automatic bus off recovery. */
                        | CAN_CTRL1_TSYN(0)     /* Reset time stamps on Rx in MB 0? */
                        | CAN_CTRL1_LBUF(0)     /* 0: We use priority handling by CAN ID */
                        | CAN_CTRL1_LOM(0)      /* Enable listen-only mode. */
                        | CAN_CTRL1_PROPSEG(PROPSEG)    /* PROPSEG=n+1, n=0..7. */
                        ;
    #undef CAN_BD_RATE
    #undef PRESDIV
    #undef PROPSEG
    #undef PSEG1
    #undef PSEG2

    /* RM 43.4.14, Control 2 register, p. 1739. */
    pCanDevice->CTRL2 =
#if defined(MCU_MPC5748G)
                        CAN_CTRL2_ERRMSK_FAST(0)    /* IRQ enable ERRINT */
                        | CAN_CTRL2_BOFFDONEMSK(enableBOffIrq? 1: 0) /* IRQ enable BOFFDONE */
#else
                        CAN_CTRL2_ECRWRE(0) /* ECC register write enable: Reset value 0 */
                        | CAN_CTRL2_WRMFRZ(1) /* Device RAM writable in freeze mode? */
#endif
                        | CAN_CTRL2_RFFN(pCanDevConfig->CTRL2_RFFN)/* Balance between FIFO
                                                                      and MBs, 43.4.14 */
                        | CAN_CTRL2_TASD(pCanDevConfig->CTRL2_TASD)/* 43.5.9.9, start time
                                                                      of arbitration */
                        | CAN_CTRL2_MRP(1)  /* 1: Consider MB before FIFO. 0: vice versa. */
                        | CAN_CTRL2_RRS(0)  /* Remote frame  handling as out of reset. */
                        | CAN_CTRL2_EACEN(0)/* Ignore RTR when matching MBs */
#if defined(MCU_MPC5748G)
                        | CAN_CTRL2_TIMER_SRC(0)/* 0: Don't occupy a PID for time stamps. */
                        | CAN_CTRL2_PREXCEN(0)  /* 0: No protocol exception */
                        | CAN_CTRL2_ISOCANFDEN(1)   /* RM 43.5.9.1, p. 1813: Using ISO CAN
                                                       FD is strongly recommended. */
                        | CAN_CTRL2_EDFLTDIS(0) /* 0: Edge filter enabled, as out of reset */
#endif
                        ;

    /* Reset CAN free running timer, which is used for time stamps on received messages. */
    pCanDevice->TIMER = CAN_TIMER_TIMER(0);

    /* The global mask registers CAN_RXMGMASK, CAN_RX14MASK and CAN_RX15MASK have no effect
       because we set MCR[IRMQ] (see above). Each mailbox has its own mask, see RM
       43.4.22, p. 1749f, CAN_RXIMRn. */

    /* RM 43.4.17, CAN_RXFGMASK. The register is the acceptance mask, which selects the
       do-care bits from some of the individual FIFO acceptance filters. See RM, p. 1740
       for a table. For example, with CTRL2[RFFN]=8, we use this global mask for filters
       24-71, whereas the first filters, 0-23, have individual acceptance masks (RM
       43.4.22, CAN_RXIMRn, n=0..23).
         We use filters with all ID bits (CTRL1[IDAM]=0) and we assert all bits in the mask
       to force a match of the entire ID for messages going into the FIFO. */
    pCanDevice->RXFGMASK = CAN_RXFGMASK_FGM_MASK;

    /* RM, 43.4.22, CAN_RXIMRn (Rx Individual Mask Registers): They are initialized
       together with the mail boxes. Each mail box has its corresponding mask register. */

    /* RM 43.4.19, CAN_CBT. This register would be used if CAN FD is enabled. It provides
       the same timing settings that we have already configured in CAN_CTRL1 (the clock
       divider and the segment lengths) but it spends broader ranges as needed for the CAN
       FD timing. Writing this register would internally overwrite the according settings
       made in CAN_CTRL1. */
    //pCanDevice->CBT =

    /* The interrupts are initially disabled with the exception of the Rx FIFO interrupt.
       The mailbox related interrupts can be decided only later, when actual CAN messages
       are registered for Tx or Rx. See RM 43.4.11/10/20.
         We enable all FIFO interrupts. */
    pCanDevice->IMASK1 = 0x000000e0; /* Why don't we have specific mask macros here? */
#if defined(MCU_MPC5748G)
    pCanDevice->IMASK2 = CAN_IMASK2_BUF63TO32M(0);
    pCanDevice->IMASK3 = CAN_IMASK3_BUF95TO64M(0);
#else
    pCanDevice->IMASK2 = CAN_IMASK2_BUFHM(0);
#endif
    /* The remaining registers are not touched for now. They relate to
       - pretended networking
       - CAN wake-up
       - CAN FD */

    /* RM, 43.4.22, p. 1749: We set all mailbox mask registers. Because we have plenty of
       mailboxes no sharing of mailboxes between several CAN IDs will ever be required and
       we set them all to "all CAN ID bits care". This makes using the CAN driver most
       simple. */
    for(u=0; u<CAN_RXIMR_COUNT; ++u)
        pCanDevice->RXIMR[u] = CAN_RXIMR_MI_MASK;

    /* RM, 43.5.8.2, p. 1812: Clear the FIFO. Before we need to clear all related three
       interrupt flags. IFLAG1: See RM 43.4.13, p. 1736ff. */
    pCanDevice->IFLAG1 = CAN_IFLAG1_BUF7I_MASK
                         | CAN_IFLAG1_BUF6I_MASK
                         | CAN_IFLAG1_BUF5I_MASK
                         ;
    pCanDevice->IFLAG1 = CAN_IFLAG1_BUF0I_MASK; /* This initiates the clear. */

    /* Initialize the FIFO filter table. See RM 43.4.43, p. 1785ff, for the binary
       structure.
         See RM 43.4.14, table on p. 1740, for the number of table entries depending on
       CTRL2[RFFN]. */
    const unsigned int noFilterTableEntries = cdr_getNoFIFOFilterEntries(pCanDevConfig);
    for(u=0; u<noFilterTableEntries; ++u)
    {
        /* The FIFO filters don't have a state "disabled" like normal mailboxes have. If we
           initialize them to zero then standard CAN ID 0 will be received. Although this
           is normally not in use and not an issue, it is a potential risk for attacs.
           Bursts of CAN ID 0 Rx messages could produce high interrupt load and even
           confuse some application SW, which gets a callback with a message notification
           for a message it had never registered.
             As a countermeasure we initialize the filter such that the situation becomes
           more unlikely. We set IDE bit to react only on the less common extended IDs and
           we set the bit RTR, which rejects normal data messages. Setting the filter to
           the CAN ID of lowest priority further lowers the risk of blocking by message
           burst. */
        *getFIFOFilterEntry(pCanDevice, u) =
                CAN_FIFOFILTER_RTR(1)/* 0: Accept normal data frames, 1: Remote fr. */
                | CAN_FIFOFILTER_IDE(1)  /* 0: Std CAN ID, 1: ext. 29 Bit CAN ID */
                | CAN_FIFOFILTER_RXIDA_EXT(0x1fffffffu) /* CAN ID, all 29 ext. bits */
                ;
    } /* End for(All FIFO filter table entries) */

    /* Reset all normal mailboxes. Caution, this code depends on the FIFO enable and the
       chosen size of the FIFO filter table, see RM 43.4.14, table on p. 1740. */
    const unsigned int idxFirstMB = cdr_getIdxOfFirstNormalMailbox(pCanDevConfig);
    volatile cdr_mailbox_t *pMB = cdr_getMailboxByIdx(pCanDevice, idxFirstMB);
    assert(!pCanDevConfig->isFIFOEnabled
           ||  (void*)getFIFOFilterEntry(pCanDevice, noFilterTableEntries) == (void*)pMB
          );
    for(u=idxFirstMB; u<CDR_NO_HW_MAILBOXES_PER_CAN_DEVICE; ++u, ++pMB)
    {
        /* See RM 43.4.40, p. 1771, for the fields of the mailbox. See Table 43-8, p.
           1772ff, for the Rx mailbox status and command CODEs. */
        pMB->csWord = CAN_MBCS_EDL(0)   /* Ext. data length. Should be 0 for non-FD frames. */
                      | CAN_MBCS_BRS(0) /* Bit rate switch: Only for CAN FD */
                      | CAN_MBCS_ESI(0) /* Error active/passive. TBC: encoding unclear */
                      | CAN_MBCS_CODE(0)/* 0, INACTIVE, makes it a disabled Rx mailbox */
                      | CAN_MBCS_SRR(1) /* Needs to be 1 for Tx, doesn't care for Rx */
                      | CAN_MBCS_IDE(0) /* 0: Std CAN ID, 1: ext. 29 Bit CAN ID */
                      | CAN_MBCS_RTR(0) /* Needed for Remote frames, 0 for normal data fr. */
                      | CAN_MBCS_DLC(0) /* Size of frame, doesn't care for Rx. */
                      | CAN_MBCS_TIME_STAMP(0)  /* Value doesn't care is set on transmission */
                      ;
        pMB->canId = CAN_MBID_PRIO(0)       /* We don't use the local prio value. */
                     | CAN_MBID_ID_EXT(0)   /* All 29 Bits of CAN ID set to zero for now. */
                     ;

    } /* End for(All normal MBs) */
    
    assert((void*)pMB == (void*)&pCanDevice->RAMn[CAN_PHYSICAL_RAMn_COUNT]);

    /* Install required interrupt handlers. By default, we have the three FIFO related
       IRQs. Later, at registration time of mailboxes, there may come many more. */
    cdr_osRegisterInterrupts(idxCanDevice);

    /* Finally, leave the freeze mode. Wait for state transition. */
    pCanDevice->MCR &= ~(CAN_MCR_FRZ_MASK | CAN_MCR_HALT_MASK);
    #define STS_MASK_RUNNING   (CAN_MCR_FRZACK_MASK | CAN_MCR_NOTRDY_MASK)
    while((pCanDevice->MCR & STS_MASK_RUNNING) != 0)
        ;
    #undef STS_MASK_RUNNING

#undef CLKSRC
} /* End of initCanDevice */




/**
 * Initialization of the CAN driver. Call this function once after startup of the software
 * and only from a single core.
 *   @remark
 * Needs to be called from supervisor code only.
 */
void cdr_osInitCanDriver(void)
{
    /* Check user provided driver configuration. Note, even a check only in DEBUG
       compilation is sufficient as it is all about static compile-time constant data.
       There won't ever be a problem in the PRODUCTION code if the check succeeded once in
       DEBUG compilation. */
    assert(cdr_checkDriverConfiguration());

    /* Check helper function by sample tests. */
#if defined(MCU_MPC5748G)
    assert((uintptr_t)getFIFOFilterEntry(CAN_0, 0) == 0xffec00e0u
           &&  (uintptr_t)getFIFOFilterEntry(CAN_0, 71) == 0xffec00e0u + 71*4
           &&  (uintptr_t)getFIFOFilterEntry(CAN_7, 71) == 0xfbecc0e0u + 71*4
          );
#else
    assert((uintptr_t)getFIFOFilterEntry(CAN_0, 0) == 0xfffc00e0u
           &&  (uintptr_t)getFIFOFilterEntry(CAN_0, 71) == 0xfffc00e0u + 71*4
           &&  (uintptr_t)getFIFOFilterEntry(CAN_1, 35) == 0xfffc40e0u + 35*4
           &&  (uintptr_t)getFIFOFilterEntry(CAN_2, 71) == 0xc3e600e0u + 71*4
           &&  (uintptr_t)getFIFOFilterEntry(CAN_3, 71) == 0xc3e640e0u + 71*4
          );
#endif
    unsigned int idxCanDev;
    for(idxCanDev=0; idxCanDev<(unsigned)cdr_canDev_noCANDevicesEnabled; ++idxCanDev)
        initCanDevice(idxCanDev);

#if CDR_ENABLE_MCU_PINS_FOR_EVAL_BOARD == 1  &&  CDR_ENABLE_USE_OF_CAN_0 == 1
    /* Configure the MCU pins so that the external circuitry is connected to the MCU
       internal CAN device we've just configured. */
# if defined(MCU_MPC5748G)
    configSIULForUseWithDEVKIT_MPC5748G();
# else
    configSIUForUseWithMPC5775BE_416DS();
# endif
#endif
} /* End of cdr_osInitCanDriver */





/**
 * Application dependent initialization of CAN communication: The driver will react only on
 * CAN message, it has agreed on with the application SW. This API is intended for making
 * such an agreement. By calling this function, the application requests one particular
 * CAN mailbox in the hardware for a particular message, for either reception or
 * transmission.
 *   @return
 * Mailbox reservation can fail. Mainly, because the number of outermost processable
 * messages is limited. The total number of all messages is limited by hardware and the
 * driver has no implementation of virtualization; if the Rx FIFO is enabled then numbers
 * of Rx and Tx messages even have different, indivdual limits.\n
 *   The function returns \a cdr_errApi_noError in case of success. In all other cases it
 * has not effect.\n
 *   All possible errors are static configuration errors in the client code. There's no
 * need to have a dynamic error check at run-time. The appropriate way to handle the return
 * code of this function is an assertion in DEBUG compilation. If it proves once that the
 * function returns \a cdr_errApi_noError then there's no risk to ever see another return
 * code in PRODUCTION compilation.
 *   @param idxCanDevice
 * The administration of messages and mailboxes is made independently for all enabled CAN
 * devices. This parameter chooses the affected CAN device.\n
 *   See enumeration \a cdr_enumCanDevice_t (actually a zero based index) for the set of
 * possible devices.\n
 *   @param hMB
 * The driver has a fixed structure of mailboxes. (A structure, which is modifiable by
 * configuration only to little extend: FIFO on/off, size of FIFO filter table).
 * Consequently, all mailboxes have a fixed index and we use this index as a handle to
 * refer to a particular mailbox. Usually, a driver will deal out a handle. Our driver
 * doesn't do but lets the client code choose the appropriate handle. The reason is that
 * the mailboxes have differing properties, which are known to the client code. By letting
 * it chosse the handle, hence the mailbox, it can decide, which mailbox suits best.
 * Relevant differences between mailboxes are:\n
 *   - The first n mailboxes belong to the Rx FIFO. They can't by used for transmission. n
 * depends on the configuration of the FIFO. The remaining, normal mailboxes are available
 * to Rx or Tx\n
 *   - The normal mailboxes are organized in groups of 4, 16 or 32. Each of these groups
 * can have a different interrupts, depending on the driver configuration. Different
 * interrupts means different priority, processed on different cores and/or using
 * different notification callbacks.\n
 *   The range of hMB is 0..N, where N depends on the chosen configuration.\n
 *   Details on how n and N relate to the made configuration can be found below.\n
 *   An out of range handle or using a handle, which had already been used in an earlier
 * call of this function, is considered an error.\n
 *   Note, each CAN device has its own, individual space of handle values.
 *   @param isExtId
 * Standard and extended CAN IDs partly share the same space of numbers. Hence, we need the
 * additional Boolean information, which of the two the ID \a canId belongs to.
 *   @param canId
 * The standard or extended ID of the CAN message, which the mailbox reservation is made
 * for.
 *   @param isReceived
 * The Boolean information, whether the mailbox is prepared for reception (\a true) of
 * transmission (\a false).
 *   @param TxDLC
 * The number of bytes of a Tx message in the range 0..8.\n
 *   The value doesn't care for Rx messages and it doesn't even care for Tx messages if
 * the send API cdr_osSendMessageEx() is exclusively used. The simple send API
 * cdr_osSendMessage(), however, will send the messages with this TxDLC. The range is 0..8.
 *   @param doNotify
 * The Boolean choice whether or not the completion of the mailbox activity will trigger an
 * interrupt. If set to \a true then an Rx mailbox will raise an interrupt if the reception
 * buffer has just been filled with a message from the bus and an Tx mailbox will raise the
 * interrupt when it has entirely serialized a message on the bus. By callback invokation,
 * the interrupt handler notifies the client code about the event and provides it the
 * required information (e.g. message payload for Rx mailboxes).\n
 *   The choice of the notification callback is made in the driver configuration. All
 * mailboxes of one group share the same callback.\n
 *   It is considered an error if a notification is requested for a mailbox that belongs to
 * a group, which is no interrupt configured for.
 *   @remark
 * The number n of FIFO mailboxes is 8*(CTRL2_RFFN+1) if the FIFO is enabled
 * (isFIFOEnabled=true) and 0 otherwise. CTRL2_RFFN and isFIFOEnabled are compile-time
 * constants in the driver configuration. Handle values 0..(n-1) make a CAN message
 * received via FIFO.\n
 *   The number m of normal mailboxes is (noMailboxes-8-2*CTRL2_RFFN) if the FIFO is
 * enabled (isFIFOEnabled=true) and noMailboxes otherwise. noMailboxes, CTRL2_RFFN and
 * isFIFOEnabled are compile-time constants in the driver configuration. Handle values
 * n..(n+m-1) place a CAN message in a normal mailbox. The massage can be either Rx or
 * Tx.\n
 *   The total number N=n+m of processable CAN messages is noMailboxes+6*CTRL2_RFFN if the
 * FIFO is enabled (isFIFOEnabled=true) and noMailboxes otherwise. noMailboxes, CTRL2_RFFN
 * and isFIFOEnabled are compile-time constants in the driver configuration. This number is
 * available as cdr_maxNoCanIds(), too.
 *   @remark
 * The hardware provides plenty of mailboxes. Therefore, we decided not to make the
 * acceptance mask available to the client code. This mask would allow sharing a mailbox
 * between a set of CAN messages with similar CAN IDs. This mechanism has some deficiencies
 * in terms of ease of use and wouldn't be available to all mailboxes in a homogenous way.
 */
cdr_errorAPI_t cdr_osMakeMailboxReservation( unsigned int idxCanDevice
                                           , unsigned int hMB
                                           , bool isExtId
                                           , unsigned int canId
                                           , bool isReceived
                                           , unsigned int TxDLC
                                           , bool doNotify
                                           )
{
    if(idxCanDevice >= sizeOfAry(cdr_canDriverConfig))
        return cdr_errApi_handleOutOfRange;

    CAN_Type * const pDevice = cdr_mapIdxToCanDevice[idxCanDevice].pCanDevice;
    const cdr_canDeviceConfig_t * const pDeviceConfig = &cdr_canDriverConfig[idxCanDevice];

    if(TxDLC > 8)
        return cdr_errApi_dlcOutOfRange;

    if(isExtId && (canId & 0xe0000000u) != 0  ||  !isExtId && (canId & 0xfffff800u) != 0)
        return cdr_errApi_badCanId;

    /* With enabled FIFO, the first mailboxes are not in normal operation and the
       configuration differs.
         The message handle space for the client code appends the normal mailboxes to the
       FIFO filter entries. */
    const unsigned int noFIFOMsgs = cdr_getNoFIFOFilterEntries(pDeviceConfig)
                     , additionalCapaFIFO = cdr_getAdditionalCapacityDueToFIFO(pDeviceConfig);
    if(hMB < noFIFOMsgs)
    {
        /* The reservation addresses to a FIFO Rx mailbox. Tx is forbidden and a
           notification request is essential, since FIFO mailboxes can't be read by
           polling. */

        /* In the FIFO context, the "mailbox handle" actually is the index of the FIFO
           filter table entry. */
        const unsigned int idxFilterEntry = hMB;

        if(!isReceived)
            return cdr_errApi_fifoMailboxUsedForTx;
        if(!doNotify)
            return cdr_errApi_fifoMailboxRequiresNotification;

        /* Check if the same mailbox had been requested already in an earlier function
           call. Although it would be technically possible to reconfigure a mailbox in a
           repeated call, it is nearly certain that this rather points to an error in the
           client code. This is why we don't allow it. */
        uint32_t const rxFilterBefore = *getFIFOFilterEntry(pDevice, idxFilterEntry);
        if(rxFilterBefore != (CAN_FIFOFILTER_RTR(1)
                              | CAN_FIFOFILTER_IDE(1)
                              | CAN_FIFOFILTER_RXIDA_EXT(0x1fffffffu)
                             )
          )
        {
            return cdr_errApi_mailboxReconfigured;
        }

        uint32_t const rxFilter = CAN_FIFOFILTER_RTR(0)
                                  | (isExtId
                                     ? (CAN_FIFOFILTER_IDE(1u)|CAN_FIFOFILTER_RXIDA_EXT(canId))
                                     : (CAN_FIFOFILTER_IDE(0u)|CAN_FIFOFILTER_RXIDA_STD(canId))
                                    );
        *getFIFOFilterEntry(pDevice, idxFilterEntry) = rxFilter;
    }
    else if(hMB < pDeviceConfig->noMailboxes + additionalCapaFIFO)
    {
        /* A normal mailbox is reserved. */

        /* hMB needs a simple transformation to become the index of the mailboxes in the
           device. */
        const unsigned int idxMB = hMB - additionalCapaFIFO;
        assert(idxMB < pDeviceConfig->noMailboxes);

        volatile cdr_mailbox_t * const pMB = cdr_getMailboxByIdx(pDevice, idxMB);

        if((pMB->csWord & (CAN_MBCS_CODE_MASK | CAN_MBCS_IDE_MASK)) != 0)
            return cdr_errApi_mailboxReconfigured;

        /* Check if demand for notification is plausible with respect to the driver
           configuration. Macro #CHECK_GROUP_IRQ returns true if there's no implausibility
           for IRQ group [from, to].
             (int)idxMB: The type cast in the condition has no impact on the result of the
           possible decisions but hinders the compiler from issuing a warning becasue of
           otherwise comparing an unsigned value on greater or equal to zero (always true,
           -Wtype-limits). */
        #define CHECK_GROUP_IRQ(from, to)                                                   \
                (!((int)idxMB >= (from)  &&  idxMB <= (to))                                 \
                 || (pDeviceConfig->irqGroupMB##from##_##to.irqPrio > 0                     \
                     && (isReceived? pDeviceConfig->irqGroupMB##from##_##to.osCallbackOnRx  \
                                     != NULL                                                \
                                   : pDeviceConfig->irqGroupMB##from##_##to.osCallbackOnTx  \
                                     != NULL                                                \
                        )                                                                   \
                    )                                                                       \
                )
#if defined(MCU_MPC5775B)  ||  defined(MCU_MPC5775E)
        #define CHECK_IRQ(checkAt)                                                          \
                (idxMB != (checkAt)                                                         \
                 || (pDeviceConfig->irqMB##checkAt.irqPrio > 0                              \
                     && (isReceived? pDeviceConfig->irqMB##checkAt.osCallbackOnRx           \
                                     != NULL                                                \
                                   : pDeviceConfig->irqMB##checkAt.osCallbackOnTx           \
                                     != NULL                                                \
                        )                                                                   \
                    )                                                                       \
                )
#endif
        if(doNotify
           && (!CHECK_GROUP_IRQ(16, 31)
               || !CHECK_GROUP_IRQ(32, 63)
#if defined(MCU_MPC5748G)
               || !CHECK_GROUP_IRQ(0, 3)
               || !CHECK_GROUP_IRQ(4, 7)
               || !CHECK_GROUP_IRQ(8, 11)
               || !CHECK_GROUP_IRQ(12, 15)
               || !CHECK_GROUP_IRQ(64, 95)
#else /* MPC5775B/E */
               || !CHECK_IRQ(0)
               || !CHECK_IRQ(1)
               || !CHECK_IRQ(2)
               || !CHECK_IRQ(3)
               || !CHECK_IRQ(4)
               || !CHECK_IRQ(5)
               || !CHECK_IRQ(6)
               || !CHECK_IRQ(7)
               || !CHECK_IRQ(8)
               || !CHECK_IRQ(9)
               || !CHECK_IRQ(10)
               || !CHECK_IRQ(11)
               || !CHECK_IRQ(12)
               || !CHECK_IRQ(13)
               || !CHECK_IRQ(14)
               || !CHECK_IRQ(15)
#endif
              )
          )
        {
            return cdr_errApi_notificationWithoutIRQ;
        }
        #undef CHECK_GROUP_IRQ
        #undef CHECK_IRQ

        /* Clear a possibly pending interrupt bit (RM 43.4.12/13/21, p. 1735ff) and enable
           the interrupt for the given mailbox (RM 43.4.11/10/20). */
        if(idxMB < 32)
        {
            const uint32_t mask = 1u << idxMB;
            pDevice->IFLAG1 =  mask; /* Clear IRQ bit by "w1c". */
            if(doNotify)
                pDevice->IMASK1 |= mask; /* Set IRQ enable bit. */
            else
                assert((pDevice->IMASK1 & mask) == 0);
        }
        else
#if defined(MCU_MPC5748G)
             if(idxMB < 64)
#endif
        {
            assert(idxMB < 64);
            const uint32_t mask = 1u << (idxMB-32u);
            pDevice->IFLAG2 =  mask; /* Clear IRQ bit by "w1c". */
            if(doNotify)
                pDevice->IMASK2 |= mask; /* Set IRQ enable bit. */
            else
                assert((pDevice->IMASK2 & mask) == 0);
        }
#if defined(MCU_MPC5748G)
        else
        {
            assert(idxMB < 96);
            const uint32_t mask = 1u << (idxMB-64u);
            pDevice->IFLAG3 =  mask; /* Clear IRQ bit by "w1c". */
            if(doNotify)
                pDevice->IMASK3 |= mask; /* Set IRQ enable bit. */
            else
                assert((pDevice->IMASK3 & mask) == 0);
        }
#endif

        const unsigned int CODE = isReceived
                                  ? 4   /* 0, EMPTY, makes it an empty, enabled Rx mailbox */
                                  : 8   /* 0, INACTIVE, makes it an empty, enable Tx mailbox */
                                  ;

        /* See RM 43.4.40, p. 1771, for the fields of the mailbox. See Table 43-8, p.
           1772ff, for the Rx mailbox status and command CODEs. */
        pMB->csWord = CAN_MBCS_EDL(0)   /* Ext. data length. Should be 0 for non-FD frames. */
                      | CAN_MBCS_BRS(0) /* Bit rate switch: Only for CAN FD */
                      | CAN_MBCS_ESI(0) /* Error active/passive. TBC: encoding unclear */
                      | CAN_MBCS_CODE(CODE)
                      | CAN_MBCS_SRR(1) /* Needs to be 1 for Tx, doesn't care for Rx */
                      | CAN_MBCS_IDE(isExtId? 1u: 0u)/* 0: Std CAN ID, 1: ext. 29 Bit CAN ID */
                      | CAN_MBCS_RTR(0) /* Needed for Remote frames, 0 for normal data fr. */
                      | CAN_MBCS_DLC(TxDLC) /* Size of frame, doesn't care for Rx. */
                      | CAN_MBCS_TIME_STAMP(0)  /* Value doesn't care is set on transmission */
                      ;
        pMB->canId = CAN_MBID_PRIO(0u)   /* We don't use the local prio value. */
                     | (isExtId? CAN_MBID_ID_EXT(canId): CAN_MBID_ID_STD(canId));
    }
    else
        return cdr_errApi_handleOutOfRange;

    return cdr_errApi_noError;

} /* End of cdr_osMakeMailboxReservation. */



/**
 * Comman part of the two APIs to send a Tx message. It checks the mailbox state and
 * prepares it for sending. It does not copy the payload and it doesn't trigger sending
 * yet.
 *   @return
 * The pointer to the affected mailbox if function succeeds, else \a NULL. The latter can
 * happen, if the buffer in the hardware is still occupied by the preceeding message, which
 * has not yet serialized on the CAN bus.\n
 *   If the function returns \a NULL then the caller must not proceed with sending.
 *   @param pIdMB
 * Object * \a pIdMB contains the information about the mailbox to operate on (i.e.
 * device, HW index of mailbox).
 *   @remark
 * It is permitted to call this function from the context of the notification IRQ for the
 * same message. This function can be used to implement a send queue: If it returns \a
 * false then the message is appended to the queue. The notification callback checks the
 * queue and sends the heading element - if any - using this function.
 */
static volatile cdr_mailbox_t *osPrepareSendMessage(const cdr_idMailbox_t * const pIdMB)
{
    CAN_Type * const pDevice = pIdMB->pDevice;
    const unsigned int idxMB = pIdMB->idxMailbox;

    /* Get the pointer to the mailbox in use. */
    volatile cdr_mailbox_t * const pTxMB = cdr_getMailboxByIdx(pDevice, idxMB);

    /* Read status word of MB and decide whether we may send (already again). */
    const uint32_t csWord = pTxMB->csWord
                 , CODE = (csWord & CAN_MBCS_CODE_MASK) >> CAN_MBCS_CODE_SHIFT;
    if(CODE == 8 /* TX ACTIVE */)
    {
        /* The MB is basically free. There's still an important consideration. Sending may
           be done with or without IRQ notification and in either case we need to
           acknowledge the interrupt from the preceeding Tx - otherwise the MB is blocked
           (RM 43.5.1, p. 1789). If notification is enabled then there are possible race
           conditions: Will the ISR or do we here reset the flag?
             The normal usecase of Tx notifications is virtualization of MBs by buffering:
           The application code interface "sends" the message by putting it in a SW buffer
           only. On each Tx notification from the CAN driver, the next element from the
           buffer is passed on to the driver, i.e. to this function. In this use case, the
           notification IRQ will always come prior to the next call of this function and
           so the interrupt is already negated on entry into this function.
             Consequently, if we unconditionally negate the flag here, then we either do,
           what we need to do (if no Tx notification is configured) or what is useless but
           doesn't do any harm (if no Tx notification is configured and already negated the
           flag). */

        /* Unconditionally clear a possibly pending interrupt bit (RM 43.4.12/13/21, p.
           1735ff) and thereby unlock the mailbox. */
        if(idxMB < 32)
        {
            const uint32_t mask = 1u << idxMB;
            pDevice->IFLAG1 =  mask; /* Clear IRQ bit by "w1c". */
        }
        else
#if defined(MCU_MPC5748G)
             if(idxMB < 64)
#endif
        {
            assert(idxMB < 64);
            const uint32_t mask = 1u << (idxMB-32u);
            pDevice->IFLAG2 =  mask; /* Clear IRQ bit by "w1c". */
        }
#if defined(MCU_MPC5748G)
        else
        {
            assert(idxMB < 96);
            const uint32_t mask = 1u << (idxMB-64u);
            pDevice->IFLAG3 =  mask; /* Clear IRQ bit by "w1c". */
        }
#endif

        /* Sending is possible, return mailbox for completion of operation. */
        return pTxMB;
    }
    else
    {
        /* Mailbox is still busy or not even a Tx mailbox. Nothing can be done. */
        return NULL;
    }
} /* End of osPrepareSendMessage */




/**
 * Send a Tx message. This API is an alias for cdr_osSendMessage() with slightly different
 * signature. This API is intended for internal use only. Behavior is otherwise identical
 * to cdr_osSendMessage(); please look there for details.
 *   @return
 * Get an error code, which reports success or different recognized error situations.
 *   @param pIdMB
 * Object * \a pIdMB contains the information about the mailbox to operate on (i.e.
 * device, HW index of mailbox).
 *   @param payload
 * The message content bytes to sent. The number of bytes to send is taken from the current
 * mailbox configuration. Normally, it'll be the never changed value aggreed on during the
 * reservation of the mailbox (see cdr_osMakeMailboxReservation()). However, if the
 * extended send API cdr_osSendMessageEx() is used alternatingly with this simple API then
 * the DLC will be applied, which had been set with the last recent call of the extended API.
 */
cdr_errorAPI_t cdr_osSendMessage_idMB( const cdr_idMailbox_t * const pIdMB
                                     , const uint8_t payload[]
                                     )
{
    /* Check and prepare the mailbox to be used and get the pointer to it. */
    volatile cdr_mailbox_t * const pTxMB = osPrepareSendMessage(pIdMB);

    /* Complete send operation if preparation reports success. */
    if(pTxMB != NULL)
    {
        /* Read the status word of the mailbox. */
        const uint32_t csWord = pTxMB->csWord;

        /* Copy sent data into the mailbox. */
        const unsigned int DLC = (csWord & CAN_MBCS_DLC_MASK) >> CAN_MBCS_DLC_SHIFT;
        assert(DLC <= 8);
        memcpy((void*)&pTxMB->payload[0], payload, DLC);

        /* Changeing the C/S word in the MB initiates the transmission. See RM, Table 43-9, p.
           1775, for the Tx mailbox status and command CODEs.
             A read-modify-write is required as we must not alter the bit IDE. */
        pTxMB->csWord = csWord | CAN_MBCS_CODE(12); /* CODE doesn't need masking: 8->12 */

        /* Sending is successfully initiated. */
        return cdr_errApi_noError;
    }
    else
    {
        /* Mailbox is still busy. Nothing to be done. */
        return cdr_errApi_txMailboxBusy;
    }
} /* End of cdr_osSendMessage_idMB */



/**
 * Send a Tx message. This API (as opposed to cdr_osSendMessageEx()) for the simple but
 * common use case where each CAN ID is connected to one particular mailbox (or message
 * handle).\n
 *   "Sending" means placing it into the mailbox, i.e. the reserved buffer
 * in the CAN device hardware. The hardware decides autonomously, when the buffer is
 * serialized on the CAN bus. Usually, this will happen much later then the return from
 * this function. (An interrupt can be configured to get a notification when it is
 * completed. See cdr_osMakeMailboxReservation() for details.)
 *   @return
 * \a cdr_errApi_noError, if function succeeded, \a cdr_errApi_txMailboxBusy, if the buffer
 * in the hardware is still occupied by the preceeding message, which iss not serialized on
 * the CAN bus yet or \a cdr_errApi_handleOutOfRange if the device index or mailbox
 * handle was invalid.\n
 *   If the function doesn't return \a cdr_errApi_noError then it had no effect.
 *   @param idxCanDevice
 * The administration of messages and mailboxes is made independently for all enabled CAN
 * devices. This parameter chooses the affected CAN device.\n
 *   See enumeration \a cdr_enumCanDevice_t (actually a zero based index) for the set of
 * possible devices.
 *   @param hMB
 * The message to send is identified by the handle of the mailbox it is associated with. A
 * message can be send only if it had been associated with a mailbox in the hardware, i.e.
 * a successful call of cdr_osMakeMailboxReservation() is prerequisite of using this
 * function. The handle to use here is the same as used when having done the related call
 * of cdr_osMakeMailboxReservation().
 *   @param payload
 * The message content bytes to send. The number of bytes to send is taken from the current
 * mailbox configuration. Normally, it'll be the never changed value aggreed on during the
 * reservation of the mailbox (see cdr_osMakeMailboxReservation()). However, if the
 * extended send API cdr_osSendMessageEx() is used alternatingly with this simple API then
 * the DLC will be applied, which had been set with the last recent call of the extended API.
 *   @remark
 * It is permitted to call this function from the context of the notification IRQ for the
 * same message.
 *   @remark
 * This API and cdr_osSendMessageEx() are alternatives. They access the same hardware and
 * have heavy race conditions. They must never be used at a time for one and the same
 * mailbox. Most use cases will lead to a general either or in the client code but the
 * non-overlapping over time, alternating use is permitted, too.
 *   @remark
 * This function is reentrant with respect to different addressed mailboxes. It can be
 * called from different cores. The behavior is undefined if called coincidentally from
 * different contexts but for the same mailbox.
 */
cdr_errorAPI_t cdr_osSendMessage( unsigned int idxCanDevice
                                , unsigned int hMB
                                , const uint8_t payload[]
                                )
{
    cdr_idMailbox_t idMB;
    if(cdr_mapMailboxHandleToId(&idMB, idxCanDevice, hMB))
        return cdr_osSendMessage_idMB(&idMB, payload);
    else
        return cdr_errApi_handleOutOfRange;

} /* End of cdr_osSendMessage */



/**
 * Send a Tx message. This API (as opposed to cdr_osSendMessage()) may be used if one and
 * the same mailbox is applied to transmit messages of variable length or with varying CAN
 * ID.\n
 *   "Sending" means placing it into the mailbox, i.e. the reserved buffer
 * in the CAN device hardware. The hardware decides autonomously, when the buffer is
 * serialized on the CAN bus. Usually, this will happen much later then the return from
 * this function. (An interrupt can be configured to get a notification when it is
 * completed. See cdr_osMakeMailboxReservation() for details.)
 *   @return
 * \a cdr_errApi_noError, if function succeeded, \a cdr_errApi_txMailboxBusy, if the buffer
 * in the hardware is still occupied by the preceeding message, which iss not serialized on
 * the CAN bus yet or \a cdr_errApi_handleOutOfRange if the device index or mailbox
 * handle was invalid.\n
 *   If the function doesn't return \a cdr_errApi_noError then it had no effect.
 *   @param idxCanDevice
 * The administration of messages and mailboxes is made independently for all enabled CAN
 * devices. This parameter chooses the affected CAN device.\n
 *   See enumeration \a cdr_enumCanDevice_t (actually a zero based index) for the set of
 * possible devices. An out of range situation is caught by assertion.
 *   @param hMB
 * The message to send is identified by the handle of the mailbox it is associated with. A
 * message can be send only if it had been associated with a mailbox in the hardware, i.e.
 * a successful call of cdr_osMakeMailboxReservation() is prerequisite of using this
 * function. The handle to use here is the same as used when having done the related call
 * of cdr_osMakeMailboxReservation(). An out of range situation is caught by assertion.
 *   @param isExtId
 * Standard and extended CAN IDs partly share the same space of numbers. Hence, we need the
 * additional Boolean information, which of the two the ID \a canId belongs to.
 *   @param canId
 * The standard or extended ID of the CAN message to send. See \a isExtId, too.
 *   @param DLC
 * The number of bytes to send in the range 0..8. An out of range situation is caught by
 * assertion.
 *   @param payload
 * The \a DLC message content bytes, which are sent.
 *   @remark
 * It is permitted to call this function from the context of the notification IRQ for the
 * same message. This function can be used to implement a send queue: If it returns \a
 * false then the message is appended to the queue. The notification callback checks the
 * queue and sends the heading element - if any - using this function.
 *   @remark
 * This API and cdr_osSendMessage() are alternatives. They access the same hardware and
 * have heavy race conditions. They must never be used at a time for one and the same
 * mailbox. Most use cases will lead to a general either or in the client code but the
 * non-overlapping over time, alternating use is permitted, too.
 *   @remark
 * This function is reentrant with respect to different addressed mailboxes. It can be
 * called from different cores. The behavior is undefined if called coincidentally from
 * different contexts but for the same mailbox.
 */
cdr_errorAPI_t cdr_osSendMessageEx( unsigned int idxCanDevice
                                  , unsigned int hMB
                                  , bool isExtId
                                  , unsigned int canId
                                  , unsigned int DLC
                                  , const uint8_t payload[]
                                  )
{
    cdr_idMailbox_t idMB;
    if(!cdr_mapMailboxHandleToId(&idMB, idxCanDevice, hMB))
        return cdr_errApi_handleOutOfRange;

    /* Check and prepare the mailbox to be used and get the pointer to it. */
    volatile cdr_mailbox_t * const pTxMB = osPrepareSendMessage(&idMB);

    /* Complete send operation if preparation reports success. */
    if(pTxMB != NULL)
    {
        /* Set the CAN ID to be used this time with the mailbox. */
        pTxMB->canId = CAN_MBID_PRIO(0u)   /* We don't use the local prio value. */
                       | (isExtId? CAN_MBID_ID_EXT(canId): CAN_MBID_ID_STD(canId));

        /* Copy sent data into the mailbox. */
        assert(DLC <= 8);
        memcpy((void*)&pTxMB->payload[0], payload, DLC);

        /* Changeing the C/S word in the MB initiates the transmission. See RM, Table 43-9, p.
           1775, for the Tx mailbox status and command CODEs. */
        pTxMB->csWord =
                CAN_MBCS_EDL(0)   /* Ext. data length. Should be 0 for non-FD frames. */
                | CAN_MBCS_BRS(0) /* Bit rate switch: Only for CAN FD */
                | CAN_MBCS_ESI(0) /* Error active/passive. TBC: encoding unclear */
                | CAN_MBCS_CODE(12)   /* 12, DATA, triggers Tx. */
                | CAN_MBCS_SRR(1) /* Needs to be 1 for Tx, doesn't care for Rx */
                | CAN_MBCS_IDE(isExtId? 1: 0) /* 0: Std CAN ID, 1: ext. 29 Bit CAN ID */
                | CAN_MBCS_RTR(0) /* Needed for Remote frames, 0 for normal data fr. */
                | CAN_MBCS_DLC(DLC) /* no FD: n=no bytes, FD: see RM, Table 43-10, p. 1777. */
                | CAN_MBCS_TIME_STAMP(0)  /* Value doesn't care if set on transmission */
                ;

        /* Sending is successfully initiated. */
        return cdr_errApi_noError;
    }
    else
    {
        /* Mailbox is still busy. Nothing to be done. */
        return cdr_errApi_txMailboxBusy;
    }
} /* End of cdr_osSendMessageEx */



/**
 * Read an Rx message from the mailbox. This variant of the function takes the resolved
 * mailbox identification as argument. The normal API function is \a cdr_osReadMessage().
 * (It resolves the mailbox identification and branches here.) Please find more detailled
 * information there.
 *   @return
 * If the function returns either \a cdr_errApi_noError or \a cdr_errApi_warningRxOverflow
 * then a new message had been arrived and the mailbox contents are returned to the
 * caller.\n
 *   \a cdr_errApi_noError should be the normal case, while \a cdr_errApi_warningRxOverflow
 * indicates that the call of the function came too late to read all incoming messages; at
 * least one preceeding message had been lost and overwritten by it successor.\n
 *   If no new data is available (no message had been received since the previous call of
 * this function for the same mailbox or the mailbox is instantly blocked by a
 * coincidental reception event) then the function returns \a cdr_errApi_rxMailboxEmpty.\n
 *   \a cdr_errApi_rxMailboxEmpty is returned, too, if one tries to read from a mailbox,
 * which had been configured for Tx.\n
 *   None of the other (pointer based) function results is set if the return code is other
 * than \a cdr_errApi_noError or \a cdr_errApi_warningRxOverflow.
 *   @param pIdMB
 * Object * \a pIdMB contains the information about the mailbox to operate on (i.e.
 * device, HW index of mailbox).
 *   @param pDLC
 * At entry into this function, * \a pDLC is the size in Byte of the output buffer \a
 * payload. No more than this number of payload bytes will be returned.\n
 *   After return, the caller will find the received number of bytes in * \a pDLC.
 *   @param payload
 * The received \a DLC message content bytes are placed into this buffer.
 *   @param pTimeStamp
 * The time of reception of the message is recorded by hardware and the value is returned
 * as * \a pTimeStamp. The absolute value has not meaning, time-base is a free running 16
 * Bit counter. The frequency of the timer is the CAN bit rate; having a bus with 500 kBd
 * the unit of the timer would be 2µs. The timer wraps around at 2^16-1.\n
 *   \a pTimeStamp can be NULL if the called doesn't want to make use of the time stamp.
 */
cdr_errorAPI_t cdr_osReadMessage_idMB( const cdr_idMailbox_t * const pIdMB
                                     , uint8_t * const pDLC
                                     , uint8_t payload[]
                                     , uint16_t * const pTimeStamp
                                     )
{
    CAN_Type * const pDevice = pIdMB->pDevice;
    const unsigned int idxMB = pIdMB->idxMailbox;

    /* Identify the interrupt bit that belongs to the given mailbox (RM 43.4.12/13/21, p.
       1735ff). */
    uint32_t irqMask;
    volatile uint32_t *pIFLAG;
    volatile uint32_t IMASK;
    if(idxMB < 32)
    {
        irqMask = 1u << idxMB;
        pIFLAG = &pDevice->IFLAG1;
        IMASK = pDevice->IMASK1;
    }
    else
#if defined(MCU_MPC5748G)
         if(idxMB < 64)
#endif
    {
        assert(idxMB < 64);
        irqMask = 1u << (idxMB-32u);
        pIFLAG = &pDevice->IFLAG2;
        IMASK = pDevice->IMASK2;
    }
#if defined(MCU_MPC5748G)
    else
    {
        assert(idxMB < 96);
        irqMask = 1u << (idxMB-64u);
        pIFLAG = &pDevice->IFLAG3;
        IMASK = pDevice->IMASK3;
    }
#endif

    /* To avoid race conditions, we don't allow using this API for mailboxes, which are
       configured to send an IRQ based notification. */
    if((IMASK & irqMask) != 0)
        return cdr_errApi_pollingOfMailboxWithIRQ;

    /* Poll for newly received input; a new message is reported by interrupt flag. */
    if((*pIFLAG & irqMask) != 0)
    {
        /* Get the pointer to the mailbox in use. */
        volatile cdr_mailbox_t * const pRxMB = cdr_getMailboxByIdx(pDevice, idxMB);

        /* Read status word of MB. Field CODE tells more about normal reception or
           overflow. */
        const uint32_t csWord = pRxMB->csWord
                     , CODE = (csWord & CAN_MBCS_CODE_MASK) >> CAN_MBCS_CODE_SHIFT;

        /* There is a little chance to access the mailbox during the move-in (likely of the
           successor message of the one, which had asserted the interrupt flag); the
           situation is recognized by a set LSB.
             From the perspective of the user interface, we handle this identical to the
           empty mailbox: Currently, the user can't get data. If it really is due to an
           overrun then he will necessarily see this in the next call of the polling
           method. */
        if(CODE == 2 /* FULL */  ||  CODE == 6 /* OVERRUN */)
        {
            const uint8_t DLC = (uint8_t)((pRxMB->csWord & CAN_MBCS_DLC_MASK)
                                          >> CAN_MBCS_DLC_SHIFT
                                         );

            /* Copy received bytes into caller provided result buffer. The loop considers
               both the provided buffer's size and the number of received bytes. The
               received DLC is limited to 8 by HW. */
            assert(DLC <= 8);
            unsigned int u = (unsigned)*pDLC;
            if((unsigned)DLC < u)
                u = (unsigned)DLC;
            while(u-- > 0)
                payload[u] = pRxMB->payload[u];
            *pDLC = DLC;

            /* Acknowledge the IRQ. */
            *pIFLAG = irqMask; /* Clear bit by "w1c" */

            /* RM 43.4.4, p. 1721f: Read the timer register to unlock the evaluated mailbox
               (side-effect of reading). See 43.5.7.3 Mailbox lock mechanism, p. 1808ff for
               more details. */
            (void)pDevice->TIMER;

            /* The time stamp of reception is returned on demand. */
            if(pTimeStamp != NULL)
            {
                *pTimeStamp = (uint16_t)((csWord & CAN_MBCS_TIME_STAMP_MASK)
                                         >> CAN_MBCS_TIME_STAMP_SHIFT
                                        );
            }

            /* RM 43.4.9, p. 1727: The error word CAN_ESR1 is related to the last recently
               received message but the bits are sticky. If the status is read by the CPU
               then they are reset otherwise they are held. So the CPU should read the word
               on each Rx event and relate the bits to the received message.
                 Careful: The bits are obviously meant to be read by interrupt (which is
               caused by them). Both at a time is impossible due to the reset-on-read and
               we tend to offer the interrupt. */

            return CODE == 2 /* FULL */? cdr_errApi_noError: cdr_errApi_warningRxOverflow;
        }
        else
            return cdr_errApi_rxMailboxEmpty;
    }
    else
        return cdr_errApi_rxMailboxEmpty;

} /* End of cdr_osReadMessage_idMB */




/**
 * Read an Rx message from the mailbox. This is the polling based receive API of the CAN
 * driver. The contents of the mailbox are returned if a message had been received since
 * the preceding invocation of this function for the same mailbox.\n
 *   Regularly polling a mailbox is an alternative to notification of reception by
 * interrupt and callback. For a given mailbox, either technologies can't be combined. This
 * is double-checked and the function returns \a cdr_errApi_pollingOfMailboxWithIRQ in case.
 *   @return
 * If the function returns either \a cdr_errApi_noError or \a cdr_errApi_warningRxOverflow
 * then a new message had been arrived and the mailbox contents are returned to the
 * caller.\n
 *   \a cdr_errApi_noError should be the normal case, while \a cdr_errApi_warningRxOverflow
 * indicates that the call of the function came too late to read all incoming messages; at
 * least one preceeding message had been lost and overwritten by it successor.\n
 *   If no new data is available (no message had been received since the previous call of
 * this function for the same mailbox or the mailbox is instantly blocked by a
 * coincidental reception event) then the function returns \a cdr_errApi_rxMailboxEmpty.
 *   \a cdr_errApi_rxMailboxEmpty is returned, too, if one tries to read from a mailbox,
 * which had been configured for Tx.\n
 *   None of the other (pointer based) function results is set if the return code is other
 * than \a cdr_errApi_noError or \a cdr_errApi_warningRxOverflow.
 *   @param idxCanDevice
 * The administration of messages and mailboxes is made independently for all enabled CAN
 * devices. This parameter chooses the affected CAN device.\n
 *   See enumeration \a cdr_enumCanDevice_t (actually a zero based index) for the set of
 * possible devices. An out of range situation is reported by return value \a
 * cdr_errApi_handleOutOfRange.\n
 *   \a cdr_errApi_pollingOfMailboxWithIRQ is returned if the read method is applied to a
 * mailbox, which had been configured for Tx.\n
 *   None of the other (pointer based) function results is set in case of an error.
 *   @param hMB
 * The message to send is identified by the handle of the mailbox it is associated with. A
 * message can be received only if it had been associated with a mailbox in the hardware, i.e.
 * a successful call of cdr_osMakeMailboxReservation() is prerequisite of using this
 * function. The handle to use here is the same as used when having done the related call
 * of cdr_osMakeMailboxReservation().\n
 *   Only normal mailboxe can be used for polling. The handle of a mailbox in the FIFO is
 * invalid. (I.e. handle value less than cdr_getNoFIFOFilterEntries().)\n
 *   An out of range situation is is reported by return value \a
 * cdr_errApi_handleOutOfRange. None of the other (pointer based) function results is
 * set in this case.
 *   @param pDLC
 * At entry into this function, * \a pDLC is the size in Byte of the output buffer \a
 * payload. No more than this number of payload bytes will be returned.\n
 *   After return, the caller will find the received number of bytes in * \a pDLC.
 *   @param payload
 * The received \a DLC message content bytes are placed into this buffer.
 *   @param pTimeStamp
 * The time of reception of the message is recorded by hardware and the value is returned
 * as * \a pTimeStamp. The absolute value has not meaning, time-base is a free running 16
 * Bit counter. The frequency of the timer is the CAN bit rate; having a bus with 500 kBd
 * the unit of the timer would be 2µs. The timer wraps around at 2^16-1.\n
 *   \a pTimeStamp can be NULL if the called doesn't want to make use of the time stamp.
 */
cdr_errorAPI_t cdr_osReadMessage( unsigned int idxCanDevice
                                , unsigned int hMB
                                , uint8_t * const pDLC
                                , uint8_t payload[]
                                , uint16_t * const pTimeStamp
                                )
{
    cdr_idMailbox_t idMB;
    if(cdr_mapMailboxHandleToId(&idMB, idxCanDevice, hMB))
        return cdr_osReadMessage_idMB(&idMB, pDLC, payload, pTimeStamp);
    else
        return cdr_errApi_handleOutOfRange;

} /* End of cdr_osReadMessage */



