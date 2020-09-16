/// @todo Clarify whether to use enum or unsigned int as device index. Make more transparent what device by enum is opposed to device by MPC pointer
/// @todo Check if we considered the dependencies on NO_MAILBOXES
/// @todo Read CAN error bits on each Rx and Tx event and put the result into the callbacks
/// @todo Check all global data objects if they are located in the right, protected section
/**
 * @file cdr_canDriver.c
 * CAN communication driver for DEVKIT-MPC5748G.
 *   The CAN device has two interesting but contradictory features: It supports sharing of
 * Rx mailboxes (MB) between several or many CAN IDs in the structure of a FIFO and it
 * supports CAN FD. Both features are essential but they can't be used at a time.
 * Therefore, the implementation needs to support two configuration and code structures.
 * The user needs to decide, which configuration to apply. Using the FIFO means other
 * interrupts and other constraints with respect to available CAN IDs.
 *
    The partitioning of the mailbox RAM space of the CAN device is difficult as it opens a
    large range of possible configurations. It is not easily possible to decide, which one
    is best and, as a matter of fact, it'll always depend on the given network database. At
    the moment it is unclear to which extend this flexibility needs to be visible in the
    driver configuration. In the current stage, we implement one configuratio, which will
    suffice in many cases. This macro can't be changes as there are mutual dependencies with
    other settings.\n
           The use of the FIFO is not possible with CAN FD. If we enable CAN FD then we have
        the additional complexity of mailboxes of different size. Their total number depends on
        the chosen sizes and this can be hardly decided without knowing the specific network
        database to serve. Anyway, the total number of supported mailboxes will be significantly
        lower so that sharing of mailboxes will become unavoidable. This means another strong
        dependency of the driver configuration on the given network database. A generic driver
        configuration will be hard to find with CAN FD.

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
 *   configSIULForUseWithDEVKIT_MPC5748G
 *   cdr_osInitCanDriver
 *   cdr_testSend_task10ms
 * Local functions
 *   cdr_osGetIdxOfFirstMailbox (global inline)
 *   cdr_osGetMailbox (global inline)
 *   getNoFIFOFilterEntries
 *   getFIFOFilterEntry
 */

/// @todo Define object, which makes ISR implementation independent from CAN device
// Error/event counters, callback pointers, etc. A trampoline of separate, macro generated
// trivial functions will select the right object by reference and jump into the common
// implementation.

/*
 * Include files
 */

#include <stddef.h>
#include <stdio.h> /// @todo Remove after temporary use in initial test code
#include <string.h>
#include <limits.h>
#include <assert.h>

#include "MPC5748G.h"
#include "cdr_MPC5748G_CAN.h"

#include "typ_types.h"
#include "sio_serialIO.h"
#include "ccl_configureClocks.h"
#include "cdr_checkConfig.h"
#include "cdr_interruptServiceHandlers.h"
#include "cdr_canDriver.h"


/*
 * Defines
 */

/** Initializer expression for an entry of the array \a cdr_canDriverData. */
#define INIT_CAN_DEVICE_DATA(canDev)    \
    [cdr_canDev_##canDev] =             \
    {                                   \
        .isBusOff = false,              \
        .noRxFIFOOverflowEvents = 0,    \
        .noRxFIFOWarningEvents = 0,     \
        .noRxMsgsFIFO = 0,              \
    },

/*
 * Local type definitions
 */

/*
 * Local prototypes
 */

/* Test of Rx by FIFO: A callback receives the Rx data. */
/// @todo remove after use
static void cbOnCANRx( bool isExtID
                     , unsigned int canId
                     , unsigned int DLC
                     , const uint8_t payload[8]
                     , unsigned int timeStamp
                     );


/*
 * Data definitions
 */

/* Read the source code include file, which defines the large configuration data set. */
#define CDR_IS_INCLUDED_FROM_DRIVER_IMPLEMENTATION
#include "cdr_canDriver.config.inc"

/** This is a lookup table, which maps a zero based CAN device index (enumeration
    cdr_canDevice_t) to a CAN peripheral (according to MPC5748G.h) */
CAN_Type * const cdr_mapIdxToCanDevice[cdr_canDev_noCANDevicesEnabled] =
{
#if CDR_ENABLE_USE_OF_CAN_0 == 1
    CAN_0,
#endif
#if CDR_ENABLE_USE_OF_CAN_1 == 1
    CAN_1,
#endif
#if CDR_ENABLE_USE_OF_CAN_2 == 1
    CAN_2,
#endif
#if CDR_ENABLE_USE_OF_CAN_3 == 1
    CAN_3,
#endif
#if CDR_ENABLE_USE_OF_CAN_4 == 1
    CAN_4,
#endif
#if CDR_ENABLE_USE_OF_CAN_5 == 1
    CAN_5,
#endif
#if CDR_ENABLE_USE_OF_CAN_6 == 1
    CAN_6,
#endif
#if CDR_ENABLE_USE_OF_CAN_7 == 1
    CAN_7,
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
 * Get the number of FIFO CAN ID filter entries in the filter table.
 *   @return
 * Get the number in the range 0..128.
 *   @param pCanDevConfig
 * The result depends on the device configuration. It is passed in by reference.
 */
static inline unsigned int getNoFIFOFilterEntries(const cdr_canDeviceConfig_t *pCanDevConfig)
{
    /* Initialize the FIFO filter table. See RM 43.4.43, p. 1785ff, for the binary
       structure.
         See RM 43.4.14, table on p. 1740, for the number of table entries depending on
       CTRL2[RFFN]. */
    return 8u*(pCanDevConfig->CTRL2_RFFN+1u);

} /* End of getNoFIFOFilterEntries */





/**
 * Get an entry from the FIFO filter table. In our configuration, an entry is of type A
 * only. Effectively it is the CAN ID, which can be received through the FIFO. See RM
 * 43.4.43, Tables 43-17 and 43-18, on p. 1786 for details.
 *   @return
 * The pointer to the filter entry is returned.
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
/// @todo Modify function signature so that the asertion becomes possible again
//    assert(idxFilterEntry < 8u*(CTRL2_RFFN+1u) /* see RM p. 1740 */);
    /* The filter table starts a byte offset 0xe0, the RAM starts at byte offset 0x80. */
    return (uint32_t*)((uint8_t*)&pCanDevice->RAMn[0]
                       + (0xe0 - 0x80)
                       + idxFilterEntry*sizeof(uint32_t)
                      );
} /* End of getFIFOFilterEntry */





/**
 * Do the configuration of the MCU pins such that CAN device CAN_0 can communicated through
 * the CAN transceiver, which is mounted on the board.\n
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
    SIUL2->MSCR[idxSIUL_PB0] =
                SIUL2_MSCR_SSS(1)   /* Source signal is CAN0_TX */
                | SIUL2_MSCR_SRC(3) /* Slew rate: Full drive without SR control */
                | SIUL2_MSCR_OBE(1) /* Enable output buffer */
                | SIUL2_MSCR_ODE(0) /* Disable open drain, drive both edges */
                | SIUL2_MSCR_SMC(1) /* Safe mode as after reset */
                | SIUL2_MSCR_APC(0) /* No analog I/O */
                | SIUL2_MSCR_IBE(0) /* Disable input buffer */
                | SIUL2_MSCR_HYS(1) /* Hysteresis as after reset */
                | SIUL2_MSCR_PUE(0) /* Pull up/down is disabled */
                | SIUL2_MSCR_PUS(0) /* Pull up/down doesn't care, is disabled */
                ;

    /* Rx output of external transceiver chip is connected to pin PB1 of the MCU. Configure
       this pin as input. */
    SIUL2->MSCR[idxSIUL_PB1] =
                SIUL2_MSCR_SSS(0)   /* Doesn't care for input */
                | SIUL2_MSCR_SRC(0) /* Doesn't care for input */
                | SIUL2_MSCR_OBE(0) /* Don't enable output buffer */
                | SIUL2_MSCR_ODE(0) /* Disable open drain, drive both edges */
                | SIUL2_MSCR_SMC(1) /* Safe mode as after reset */
                | SIUL2_MSCR_APC(0) /* No analog I/O */
                | SIUL2_MSCR_IBE(1) /* Enable input buffer */
                | SIUL2_MSCR_HYS(1) /* Hysteresis as after reset */
                | SIUL2_MSCR_PUE(0) /* Pull up/down is disabled */
                | SIUL2_MSCR_PUS(0) /* Pull up/down doesn't care, is disabled */
                ;

    /* RM 15.2.12, p. 391, input multiplexer: Rx output of external transceiver chip is
       connected to pin PB1 of the MCU. Route PB1 to the Rx input of CAN device CAN_0. */
    SIUL2->IMCR[idxIMCR_PB1] = SIUL2_IMCR_SSS(2);

} /* End of configSIULForUseWithDEVKIT_MPC5748G */




/**
 * Initialization of one CAN device.
 *   @return
 * \a true, if function succeeded, else \a false.
 *   @param idxCanDevice
 * The CAN device to initialize by index. The available index range depends on the
 * configuration of the set of enabled CAN devices, see e.g. #CDR_ENABLE_USE_OF_CAN_0. The
 * most convenient way to provide the appropriate index is using enumeration
 * cdr_canDevice_t.
 *   @remark
 * Needs to be called from supervisor code only.
 */
/// @todo Doc it
static void initCanDevice(unsigned int idxCanDevice)
{
    /* Look up the CAN device and the related driver configuration. */
    _Static_assert( sizeOfAry(cdr_canDriverConfig) == sizeOfAry(cdr_mapIdxToCanDevice)
                  , "Invalid CAN driver configuration"
                  );
    assert(idxCanDevice < sizeOfAry(cdr_canDriverConfig));
    CAN_Type * const pCanDevice = cdr_mapIdxToCanDevice[idxCanDevice];
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
    pCanDevice->IFLAG2 = CAN_IFLAG2_BUF63TO32I_MASK;
    pCanDevice->IFLAG3 = CAN_IFLAG3_BUF95TO64_MASK;

    /* For now, we don't support CAN FD. A generic configuration is difficult due to the
       different message sizes and augmented bit rates. They depend on the concrete network
       and shaping an all supporting, generic API is difficult and would likely suffer from
       reduced usability. Moreover, CAN FD would not allow using the Rx queue, which is
       most suitable for our CAN stack. */
    pCanDevice->MCR = CAN_MCR_MDIS(0)       /* For now keep device disabled. */
                      | CAN_MCR_FRZ(1)      /// @todo TBC: Needed for debugging? Do we stay frozen after debugger interaction?
                      | CAN_MCR_RFEN(1)     /* Don't use FIFO, not compatible with FD */
                      | CAN_MCR_HALT(1)     /* 1: Stay in halted mode for now */
                      | CAN_MCR_WAKMSK(0)   /* No wakeup IRQ needed */
                      | CAN_MCR_SOFTRST(0)  /* No reset needed */
                      | CAN_MCR_SUPV(1)     /* No access by user mode code permitted */
                      | CAN_MCR_SLFWAK(0)   /* Self wake up: We have no implementation of low
                                               power/active mode switches */
                      | CAN_MCR_WRNEN(0)    /// @todo TBC: Do we need a warn IRQ?
                      | CAN_MCR_WAKSRC(0)   /* Wake-up source doesn't matter; we don't use
                                               wake-up for now. */
                      | CAN_MCR_SRXDIS(0)   /* Disable reception of Tx messages in other Rx
                                               mailbox? 0: No, Rx of own Tx is allowed */
                      | CAN_MCR_IRMQ(1)     /* Matching MB vs. FIFO: 1: Most natural
                                               descisions. See RM, Table 43-22, p. 1798. */
                      | CAN_MCR_DMA(0)      /* DMA not compatible with FD */
                      | CAN_MCR_PNET_EN(0)  /* Pretended network functionality doesn't
                                               matter, we don't implement a halt state. */
                      | CAN_MCR_LPRIOEN(0)  /* 0: We use priority handling by CAN ID only */
                      | CAN_MCR_AEN(1)      /* 1: Overwriting a Tx MB is possible as long as
                                               serialization has not yet started. (43.5.7.1) */
                      | CAN_MCR_FDEN(0)     /// @todo To be supported once initial operation is proven for standard CAN
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
    #define CAN_BD_RATE 500000
    #define PRESDIV     4
    #define PROPSEG     6
    #define PSEG1       3
    #define PSEG2       3
    _Static_assert( ((float)(PRESDIV+1)/CCL_XTAL_CLK)   /* time quantum in s as float */
                    * (PROPSEG+PSEG1+3 + PSEG2+1)       /* no quantums per CAN bit */
                    == 1.0f/CAN_BD_RATE
                  , "CAN timer configuration doesn't hit intended Baud rate"
                  );

    /* RM 43.5.4, p. 1795ff, and in particular Table 43-22, p. 1798f, provide the best
       explanation of the arbitration bits CTRL1[IRMQ] and CTRL2[MRP]. They control, which
       messages go into individual mailboxes and which go into the shared FIFO. Our
       strategy (IRMQ=1, MRP=1) give priority to the MBs. We can have a number of MBs with
       mask for one particular CAN ID and we provide an open mask to the less prior FIFO.
       So the message goes into the MB is any is defined but arbitrary messages go into the
       FIFO.
         Note an additional complexity. If a message has a dedicated MB and it is received
       while the MB is still occupied by the predecessor then the newly received message is
       put in the FIFO. A polling strategy is hence not easily possible implementable, not
       even for messages with dedicated MB. */
    /// @todo This is potentially unsafe as all foreign message were received, too, and
    // produce interrupt and CPU load. Only suitable for initial testing

    pCanDevice->CTRL1 = CAN_CTRL1_PRESDIV(PRESDIV)  /* 0..255. SerClk = PEClk/(PRESDIV+1) =
                                                       8 MHz. */
                        | CAN_CTRL1_RJW(3)      /* Resync jump width=n+1, n=0..3. */
                        | CAN_CTRL1_PSEG1(PSEG1)/* PSEG1=n+1, n=0..7. */
                        | CAN_CTRL1_PSEG2(PSEG2)/* PSEG2=n+1, n=0..7. */
                        | CAN_CTRL1_BOFFMSK(0)  /* Bus off IRQ enable */
                        | CAN_CTRL1_ERRMSK(0)   /* Error IRQ enable */
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
    pCanDevice->CTRL2 = CAN_CTRL2_ERRMSK_FAST(0)    /* IRQ enable ERRINT */
                        | CAN_CTRL2_BOFFDONEMSK(0)  /* IRQ enable BOFFDONE */
                        | CAN_CTRL2_RFFN(pCanDevConfig->CTRL2_RFFN)/* Balance between FIFO
                                                                      and MBs, 43.4.14 */
                        | CAN_CTRL2_TASD(pCanDevConfig->CTRL2_TASD)/* 43.5.9.9, start time
                                                                       of arbitration */
                        | CAN_CTRL2_MRP(1)  /* 1: Consider MB before FIFO. 0: vice versa. */
                        | CAN_CTRL2_RRS(0)  /* Remote frame  handling as out of reset. */
                        | CAN_CTRL2_EACEN(0)/* Ignore RTR when matching MBs */
                        | CAN_CTRL2_TIMER_SRC(0)/* 0: Don't occupy a PID for time stamps. */
                        | CAN_CTRL2_PREXCEN(0)  /* 0: No protocol exception */
                        | CAN_CTRL2_ISOCANFDEN(1)   /* RM 43.5.9.1, p. 1813: Using ISO CAN
                                                       FD is strongly recommended. */
                        | CAN_CTRL2_EDFLTDIS(0) /* 0: Edge filter enabled, as out of reset */
                        ;

    /* Reset CAN free running timer, which is used for time stamps on received messages. */
    pCanDevice->TIMER = CAN_TIMER_TIMER(0);

    /* The global mask registers CAN_RXMGMASK, CAN_RX14MASK and CAN_RX15MASK have no effect
       because we set MCR[IRMQ] (see above). Each mailbox has its own mask as element of
       the mailbox itself. */

    /* RM 43.4.8 Error Counter, p. 1725f, reset all error counters. */
    pCanDevice->ECR = CAN_ECR_RXERRCNT_FAST(0)
                      | CAN_ECR_TXERRCNT_FAST(0)
                      | CAN_ECR_RXERRCNT(0)
                      | CAN_ECR_TXERRCNT(0)
                      ;

    /* The error/status word CAN_ESR1 contains some interrupt flag bits, which we reset by
       w1c. */
    pCanDevice->ESR1 = CAN_ESR1_ERROVR_MASK
                       | CAN_ESR1_ERRINT_FAST_MASK
                       | CAN_ESR1_BOFFDONEINT_MASK
                       | CAN_ESR1_TWRNINT_MASK
                       | CAN_ESR1_RWRNINT_MASK
                       | CAN_ESR1_BOFFINT_MASK
                       | CAN_ESR1_ERRINT_MASK
                       | CAN_ESR1_WAKINT_MASK
                       ;
    //pCanDevice->ESR2 is a read-only status register. (RM 43.4.15, p. 1742f.)

    /* RM 43.4.17, CAN_RXFGMASK. The register is the acceptance mask, which selects the
       do-care bits from some of the individual FIFO acceptance filters. See RM, p. 1740
       for a table. For CTRL2[RFFN]=8, we use this global mask for filters 24-71, whereas
       the first filters, 0-23, have individual acceptance masks (RM 43.4.22, CAN_RXIMRn,
       n=0..23).
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
    pCanDevice->IMASK2 = CAN_IMASK2_BUF63TO32M(0);
    pCanDevice->IMASK3 = CAN_IMASK3_BUF95TO64M(0);

    /* The remaining registers are not touched for now. They relate to
       - pretended networking
       - CAN wake-up
       - CAN FD */

    /* RM, 43.4.22, p. 1749: We need to program all mailbox mask registers explicitly. For
       now, we set them all to "all CAN ID bits care". */
    unsigned int u;
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
    const unsigned int noFilterTableEntries = getNoFIFOFilterEntries(pCanDevConfig);
    for(u=0; u<noFilterTableEntries; ++u)
    {
        *getFIFOFilterEntry(pCanDevice, u) =
                CAN_FIFOFILTER_RTR(0)/* 0: Accept normal data frames, 1: Remote fr. */
                | CAN_FIFOFILTER_IDE(0)  /* 0: Std CAN ID, 1: ext. 29 Bit CAN ID */
                | CAN_FIFOFILTER_RXIDA_EXT(0)    /* CAN ID, all 29 ext. bits */
                ;
    }

    /* Reset all normal mailboxes. Caution, this code depends on the FIFO enable and the
       chosen size of the FIFO filter table, see RM 43.4.14, table on p. 1740. */
    const unsigned int idxFirstMB = pCanDevConfig->isFIFOEnabled
                                    ? 8u + 2u*pCanDevConfig->CTRL2_RFFN
                                    : 0;
    _Static_assert(CAN_RXIMR_COUNT == 96, "Missing macro for available number of mailboxes");
    volatile cdr_mailbox_t *pMB = cdr_osGetMailbox(pCanDevice, idxFirstMB);
    assert((void*)getFIFOFilterEntry(pCanDevice, noFilterTableEntries) == (void*)pMB);
    for(u=idxFirstMB; u<CAN_RXIMR_COUNT; ++u, ++pMB)
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
        pMB->canId = CAN_MBID_PRIO(0)   /* We don't use the local prio value. */
                     | CAN_MBID_ID_EXT(0)   /* All 29 Bits of CAN ID set to zero for now. */
                     ;
//if(u==24) /* Initial Tx test */
//{
//    /* See RM, Table 43-9, p. 1775, for the Tx mailbox status and command CODEs. */
//    pMB->csWord = CAN_MBCS_EDL(0)   /* Ext. data length. Should be 0 for non-FD frames. */
//                  | CAN_MBCS_BRS(0) /* Bit rate switch: Only for CAN FD */
//                  | CAN_MBCS_ESI(0) /* Error active/passive. TBC: encoding unclear */
//                  | CAN_MBCS_CODE(8)/* 0, INACTIVE, makes it an empty, enable Tx mailbox */
//                  | CAN_MBCS_SRR(1) /* Needs to be 1 for Tx, doesn't care for Rx */
//                  | CAN_MBCS_IDE(0) /* 0: Std CAN ID, 1: ext. 29 Bit CAN ID */
//                  | CAN_MBCS_RTR(0) /* Needed for Remote frames, 0 for normal data fr. */
//                  | CAN_MBCS_DLC(0) /* Size of frame, doesn't care for Rx. */
//                  | CAN_MBCS_TIME_STAMP(0)  /* Value doesn't care is set on transmission */
//                  ;
//}
if(u==25) /* Initial Rx test */
{
    /* See RM 43.4.40, p. 1771, for the fields of the mailbox. See Table 43-8, p.
       1772ff, for the Rx mailbox status and command CODEs. */
    pMB->csWord = CAN_MBCS_EDL(0)   /* Ext. data length. Should be 0 for non-FD frames. */
                  | CAN_MBCS_BRS(0) /* Bit rate switch: Only for CAN FD */
                  | CAN_MBCS_ESI(0) /* Error active/passive. TBC: encoding unclear */
                  | CAN_MBCS_CODE(4)/* 0, EMPTY, makes it an empty, enabled Rx mailbox */
                  | CAN_MBCS_SRR(1) /* Needs to be 1 for Tx, doesn't care for Rx */
                  | CAN_MBCS_IDE(0) /* 0: Std CAN ID, 1: ext. 29 Bit CAN ID */
                  | CAN_MBCS_RTR(0) /* Needed for Remote frames, 0 for normal data fr. */
                  | CAN_MBCS_DLC(0) /* Size of frame, doesn't care for Rx. */
                  | CAN_MBCS_TIME_STAMP(0)  /* Value doesn't care is set on transmission */
                  ;
    pMB->canId = CAN_MBID_PRIO(0)   /* We don't use the local prio value. */
                 | CAN_MBID_ID_STD(0x80)  /* Standard CAN ID 128 enabled for Rx. */
                 ;
}
    } /* End for(All acceptance masks of the normal MBs) */
    assert((void*)pMB == (void*)&pCanDevice->RAMn[CAN_RAMn_COUNT]);

    /* The FIFO filters don't have a state "disabled" like normal mailboxes have. If we
       initialize them to zero then standad CAN ID 0 will be received. Although this is
       normally not in use and not an issue, it is a potential risk for attacs. Bursts of
       CAN ID 0 Rx messages could produce high interrupt laod and even confuse some
       application SW, which gets a callback with a message notification for a message it
       had never registered.
         As a countermeasure we initialize the filter such that the situation becomes more
       unlikely. We set IDE bit to react only on the less common extended IDs and we set
       the bit RTR, which rejects normal data messages. Setting the filter to the CAN ID of
       lowest priority further lowers the risk of blocking by message burst. */
    /// @todo Additional idea: Set all filters to the first registered message, when later doing first registration
    /// @todo Have config dependend no filters and add a loop

/// @todo Remove temporary test code.
*getFIFOFilterEntry(pCanDevice, 0) = CAN_FIFOFILTER_IDE(0)
                                     | CAN_FIFOFILTER_RXIDA_STD(0x81);
*getFIFOFilterEntry(pCanDevice, 1) = CAN_FIFOFILTER_IDE(0)
                                     | CAN_FIFOFILTER_RXIDA_STD(0x82);
*getFIFOFilterEntry(pCanDevice, 2) = CAN_FIFOFILTER_IDE(0)
                                     | CAN_FIFOFILTER_RXIDA_STD(0x83);
*getFIFOFilterEntry(pCanDevice, 71) = CAN_FIFOFILTER_IDE(0)
                                      | CAN_FIFOFILTER_RXIDA_STD(0x7ff);
*getFIFOFilterEntry(pCanDevice, 4) = CAN_FIFOFILTER_IDE(1)
                                     | CAN_FIFOFILTER_RXIDA_EXT(0x81);
*getFIFOFilterEntry(pCanDevice, 23) = CAN_FIFOFILTER_IDE(1)
                                      | CAN_FIFOFILTER_RXIDA_EXT(0x82);
*getFIFOFilterEntry(pCanDevice, 25) = CAN_FIFOFILTER_IDE(1)
                                      | CAN_FIFOFILTER_RXIDA_EXT(0x83);
*getFIFOFilterEntry(pCanDevice, 70) = CAN_FIFOFILTER_IDE(1)
                                      | CAN_FIFOFILTER_RXIDA_EXT(0x7ff);

    /* Configure the MCU pins so that the external circuitry is connected to the MCU
       internal CAN device we've just configured. */
    configSIULForUseWithDEVKIT_MPC5748G();

    /* Install required interrupt handlers. By default, we have the three FIFO related
       IRQs. Later, at registration time of mailboxes, there may come many more. */
    cdr_osRegisterInterrupts(idxCanDevice);

    /* Finally, leave the freeze mode. Wait for state transition. */
//    pCanDevice->MCR &= ~CAN_MCR_HALT_MASK;
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
 *   @return
 * \a true, if function succeeded, else \a false.
 *   @param pCanDevConfig
 * The driver configuration for the given CAN device by reference.
 *   @remark
 * Needs to be called from supervisor code only.
 */
/// @todo Doc it
void cdr_osInitCanDriver(void)
{
    /* Check user provided driver configuration. A check in DEBUG compilation is sufficient
       as it is all compile-time constant data. There won't ever be a problem in the
       PRODUCTION code if the check succeeded once in DEBUG compilation. */
    assert(cdr_checkDriverConfiguration());

    /* Check helper function by sample tests. */
    assert((uintptr_t)getFIFOFilterEntry(CAN_0, 0) == 0xffec00e0u
           &&  (uintptr_t)getFIFOFilterEntry(CAN_0, 71) == 0xffec00e0u + 71*4
           &&  (uintptr_t)getFIFOFilterEntry(CAN_7, 71) == 0xfbecc0e0u + 71*4
          );

    unsigned int idxCanDev;
    for(idxCanDev=0; idxCanDev<(unsigned)cdr_canDev_noCANDevicesEnabled; ++idxCanDev)
        initCanDevice(idxCanDev);

} /* End of cdr_osInitCanDriver */


/* RM 43.4.9, p. 1727: The error word CAN_ESR1 is related to the last recently received
   message but the bits are sticky. If the status is read by the CPU then they are reset
   otherwise they are held. So the CPU should read the word on each Rx event and relate the
   bits to the received message. */

/// @todo Configure a Tx mailbox and try sending regularly. Then configure Rx MB (no IRQ)
/// and try reception by polling. Take care that FIFO is still inactive. Then install the
/// FIFO IRQs and see if FIFO is working. Then try MB IRQs
void cdr_osTestSend_task10ms(cdr_canDevice_t canDevice)
{
    /* Make an integer from the zero based device enumeration. */
    const unsigned idxCanDevice = (unsigned)canDevice;

    static uint16_t SBSS_OS(cnt_) = 0;
    ++ cnt_;

    /* Initial test: Send a message every 10ms. */
    assert((unsigned)idxCanDevice == 0);

    /// @todo TBC: Do we need to initialize a mailbox for TX by setting CODE to INACTIVE (8)?
    /* A pointer to the device in operation and its configuration is basis of the next
       steps. */
    assert(idxCanDevice < sizeOfAry(cdr_canDriverConfig));
    CAN_Type * const pCanDevice = cdr_mapIdxToCanDevice[idxCanDevice];
    const cdr_canDeviceConfig_t * const pCanDevConfig = &cdr_canDriverConfig[idxCanDevice];

    /* Get the pointer to the mailbox in use: We take the first one behind the FIFO. */
    const unsigned int idxFirstMB = 8u + 2u*pCanDevConfig->CTRL2_RFFN // This could become a sub-routine
                     , idxRxMB = idxFirstMB + 1;
    volatile cdr_mailbox_t * const pTxMB = ((volatile cdr_mailbox_t*)&pCanDevice->RAMn[0])
                                           + idxFirstMB
                         , * const pRxMB = pTxMB + 1;

    /* We do all of this cyclically, so we acknowledge the previous message if any. If we
       wouldn't we couldn't proceed - the mailbox is locked.
         The bits in the IRQ flag register relate to the mailbox index in normal (not PPC)
       bit count order. */
    assert(idxFirstMB < 32); /* Mailbox associated with right flag register? */
    const uint32_t irqMask = 1u << idxFirstMB;
    static unsigned int SDATA_OS(noTxErr_) = UINT_MAX;/* Start with -1: In the first step
                                                         we will falsely count an error. */
    if((pCanDevice->IFLAG1 & irqMask) != 0)
        pCanDevice->IFLAG1 = irqMask; /* Clear bit by "w1c" */
    else
    {
        /* Interrupt flag should have been asserted but was negated. This is an error. */
        /// @todo We could check for field CODE being INACTIVE=8, too
        ++ noTxErr_;
    }

    /* Fill data in the mailbox. */
    //memcpy((void*)&pTxMB->payload[0], "Hello", 5);
    static unsigned int SDATA_OS(noRxEvent_) = 0;
    pTxMB->payload_u16[2] = (uint16_t)(noRxEvent_ & 0x0000ffffu);
    pTxMB->payload_u16[3] = cnt_;
    pTxMB->payload[3] = (uint8_t)(noTxErr_ & 0x000000ffu);

    /* Set the CAN ID. */
    #define CAN_ID  127
    pTxMB->canId = CAN_MBID_PRIO(0)   /* We don't use the local prio value. */
                   | CAN_MBID_ID_STD(CAN_ID)  /* We use the standard 11 Bit ID. */
                   ;

    /// @todo TBC RM p. 1788 is not so clear, whether we cann set all fields in C/S word at
    // once or if CODE needs to come later
    /* See RM, Table 43-9, p. 1775, for the Tx mailbox status and command CODEs. */
    pTxMB->csWord = CAN_MBCS_EDL(0)   /* Ext. data length. Should be 0 for non-FD frames. */
                    | CAN_MBCS_BRS(0) /* Bit rate switch: Only for CAN FD */
                    | CAN_MBCS_ESI(0) /* Error active/passive. TBC: encoding unclear */
                    | CAN_MBCS_CODE(12)   /* 12, DATA, triggers Tx. */
                    | CAN_MBCS_SRR(1) /* Needs to be 1 for Tx, doesn't care for Rx */
                    | CAN_MBCS_IDE(0) /* 0: Std CAN ID, 1: ext. 29 Bit CAN ID */
                    | CAN_MBCS_RTR(0) /* Needed for Remote frames, 0 for normal data fr. */
                    | CAN_MBCS_DLC(8) /* no FD: n=no bytes, FD: see RM, Table 43-10, p. 1777. */
                    | CAN_MBCS_TIME_STAMP(0)  /* Value doesn't care if set on transmission */
                    ;

    /* Poll for newly received input. */
    assert(idxRxMB < 32); /* Mailbox associated with right flag register? */
    const uint32_t irqMaskRx = 1u << idxRxMB;
    if((pCanDevice->IFLAG1 & irqMaskRx) != 0)
    {
        ++ noRxEvent_;

        const uint32_t CODE = (pRxMB->csWord & CAN_MBCS_CODE_MASK) >> CAN_MBCS_CODE_SHIFT;
        assert(CODE == 2 /* FULL */  ||  CODE == 6 /* OVERRUN */);
        const uint32_t DLC = (pRxMB->csWord & CAN_MBCS_DLC_MASK) >> CAN_MBCS_DLC_SHIFT;

        /* Copy first received bytes into Tx test message. 3 Bytes are left. */
        unsigned int u;
        for(u=0; u<3 && u<DLC; ++u)
            pTxMB->payload[u] = pRxMB->payload[u];

        /* Acknwoledge the IRQ. */
        /// @todo Find out, whether the order of IRQ ack. and MB unlock by reading timer matters
        pCanDevice->IFLAG1 = irqMaskRx; /* Clear bit by "w1c" */

        /* RM 43.4.4, p. 1721f: Read the timer register to unlock theevaluated mailbox
           (side-effect of reading). See 43.5.7.3 Mailbox lock mechanism, p. 1808ff for
           more details. */
        (void)pCanDevice->TIMER;
    }
} /* cdr_testSend_task10ms */


/// @todo Put the reference to this callback in the configuration table and use that
/* Test of Rx by FIFO: A callback receives the Rx data. */
static void cbOnCANRx( bool isExtId
                     , unsigned int canId
                     , unsigned int DLC
                     , const uint8_t payload[8]
                     , unsigned int timeStamp
                     )
{
    char msg[128]
       , *pWr = &msg[0];
    size_t noAvailChar = sizeof(msg);

    int noChars = sniprintf( pWr, noAvailChar
                           , " %u (%s) at %u us: %u Bytes"
                           , canId
                           , isExtId? "ext": "std"
                           , timeStamp/2 /* unit: 1/500000Bd */
                           , DLC
                           );
    if(noChars > 0)
    {
        pWr += (unsigned)noChars;
        noAvailChar -= (unsigned)noChars;
    }
    else
        return;

    unsigned int u;
    assert(DLC <= 8);
    for(u=0; u<DLC; ++u)
    {
        noChars = sniprintf(pWr, noAvailChar, " %02x", payload[u]);
        if(noChars > 0)
        {
            pWr += (unsigned)noChars;
            noAvailChar -= (unsigned)noChars;
        }
        else
            return;
    }

    noChars = sniprintf(pWr, noAvailChar, "\r\n");
    if(noChars > 0)
    {
        pWr += (unsigned)noChars;
        noAvailChar -= (unsigned)noChars;
    }
    else
        return;

    noChars = pWr - msg;
    assert((unsigned)noChars < sizeOfAry(msg));
    sio_osWriteSerial(msg, (unsigned)noChars);

} /* End of cbOnCANRx */
