#ifndef CDR_INTERRUPT_SERVICE_HANDLERS_MPC5748G_INCLUDED
#define CDR_INTERRUPT_SERVICE_HANDLERS_MPC5748G_INCLUDED
/**
 * @file cdr_interruptServiceHandlers.MPC5748G.h
 * The CAN devices are source of many interrupts (20 for the MPC5775B/E and a few less for
 * the MPC5748G). This number times the number of availbale CN devices makes it useful to
 * hide some code in preprocessor macros, so that we implement a macro once instead of
 * different structurally identical functions and operations dozens of times.\n
 *   Unfortunately, the supported MCUs are quite different in the sets of supported
 * interrupts so that these macros differ accordingly. In order to not overlaod the
 * implementation too much, the definitions of the needed macros have been collected in
 * this dedicated, separate header file.
 *
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

/*
 * Include files
 */

#include "typ_types.h"


/*
 * Defines
 */

/** This macro defines all the ISRs for a single CAN device. The implementation contains
    those operations, which base on the implicit knowledge about the interrupt. E.g. a
    mailbox interrupt, which implicitly knows, which mailbox it belongs to and which can
    therefore implicitly know, which flag register and which flag bit to use. This implicit
    knowledge is then forwarded by function argument to the common implementation of the
    ISR. This common implementation is made in normal way in file
    cdr_interruptServiceHandlers.c. */
#if defined(MCU_MPC5748G)

# define IMPLEMENTATION_OF_DEVICE_ISRS(idxCanDev)                                           \
ISR_GROUP_RX_FIFO(CAN_##idxCanDev)                                                          \
ISR_GROUP_ERROR(CAN_##idxCanDev)                                                            \
ISR_GROUP_BUS_OFF(CAN_##idxCanDev)                                                          \
ISR_GROUP_MAILBOX(CAN_##idxCanDev, /* idxIFLAG */ 1, /* idxFrom */ 0, /* idxTo */ 3, 2)     \
ISR_GROUP_MAILBOX(CAN_##idxCanDev, /* idxIFLAG */ 1, /* idxFrom */ 4, /* idxTo */ 7, 2)     \
ISR_GROUP_MAILBOX(CAN_##idxCanDev, /* idxIFLAG */ 1, /* idxFrom */ 8, /* idxTo */ 11, 2)    \
ISR_GROUP_MAILBOX(CAN_##idxCanDev, /* idxIFLAG */ 1, /* idxFrom */ 12, /* idxTo */ 15, 2)   \
ISR_GROUP_MAILBOX(CAN_##idxCanDev, /* idxIFLAG */ 1, /* idxFrom */ 16, /* idxTo */ 31, 4)   \
ISR_GROUP_MAILBOX(CAN_##idxCanDev, /* idxIFLAG */ 2, /* idxFrom */ 32, /* idxTo */ 63, 5)   \
ISR_GROUP_MAILBOX(CAN_##idxCanDev, /* idxIFLAG */ 3, /* idxFrom */ 64, /* idxTo */ 95, 5)

#elif defined(MCU_MPC5775B)  ||  defined(MCU_MPC5775E)

# define IMPLEMENTATION_OF_DEVICE_ISRS(idxCanDev)                                           \
ISR_GROUP_RX_FIFO(CAN_##idxCanDev)                                                          \
ISR_GROUP_ERROR(CAN_##idxCanDev)                                                            \
ISR_GROUP_BUS_OFF(CAN_##idxCanDev)                                                          \
ISR_MAILBOX(CAN_##idxCanDev, /* idxMB */ 0)                                                 \
ISR_MAILBOX(CAN_##idxCanDev, /* idxMB */ 1)                                                 \
ISR_MAILBOX(CAN_##idxCanDev, /* idxMB */ 2)                                                 \
ISR_MAILBOX(CAN_##idxCanDev, /* idxMB */ 3)                                                 \
ISR_MAILBOX(CAN_##idxCanDev, /* idxMB */ 4)                                                 \
ISR_MAILBOX(CAN_##idxCanDev, /* idxMB */ 5)                                                 \
ISR_MAILBOX(CAN_##idxCanDev, /* idxMB */ 6)                                                 \
ISR_MAILBOX(CAN_##idxCanDev, /* idxMB */ 7)                                                 \
ISR_MAILBOX(CAN_##idxCanDev, /* idxMB */ 8)                                                 \
ISR_MAILBOX(CAN_##idxCanDev, /* idxMB */ 9)                                                 \
ISR_MAILBOX(CAN_##idxCanDev, /* idxMB */ 10)                                                \
ISR_MAILBOX(CAN_##idxCanDev, /* idxMB */ 11)                                                \
ISR_MAILBOX(CAN_##idxCanDev, /* idxMB */ 12)                                                \
ISR_MAILBOX(CAN_##idxCanDev, /* idxMB */ 13)                                                \
ISR_MAILBOX(CAN_##idxCanDev, /* idxMB */ 14)                                                \
ISR_MAILBOX(CAN_##idxCanDev, /* idxMB */ 15)                                                \
ISR_GROUP_MAILBOX(CAN_##idxCanDev, /* idxIFLAG */ 1, /* idxFrom */ 16, /* idxTo */ 31, 4)   \
ISR_GROUP_MAILBOX(CAN_##idxCanDev, /* idxIFLAG */ 2, /* idxFrom */ 32, /* idxTo */ 63, 5)

#else
# error No implementation available for selected MCU derivative
#endif



/** Helper macro to maintian readability of initializer expression of a constant table of
    interrupt handlers, needed for registration of ISRs. See cdr_setOfCanDeviceISRs_t also,
    the type of an entry of such table. */
#if defined(MCU_MPC5748G)
# define SET_OF_DEVICE_ISRS(canDev)                 \
    { .isrGroupFIFO = isrGroupRxFIFO_##canDev,      \
      .isrGroupError = isrGroupError_##canDev,      \
      .isrGroupBusOff = isrGroupBusOff_##canDev,    \
      .isrGroupMB0_3 = isrGroupMB0_3_##canDev,      \
      .isrGroupMB4_7 = isrGroupMB4_7_##canDev,      \
      .isrGroupMB8_11 = isrGroupMB8_11_##canDev,    \
      .isrGroupMB12_15 = isrGroupMB12_15_##canDev,  \
      .isrGroupMB16_31 = isrGroupMB16_31_##canDev,  \
      .isrGroupMB32_63 = isrGroupMB32_63_##canDev,  \
      .isrGroupMB64_95 = isrGroupMB64_95_##canDev,  \
    },
#else /* MPC5775B/E */
# define SET_OF_DEVICE_ISRS(canDev)                 \
    { .isrFIFORx = isrRxFIFORx_##canDev,            \
      .isrFIFOWarning = isrRxFIFOWarning_##canDev,  \
      .isrFIFOOverflow = isrRxFIFOOverflow_##canDev,\
      .isrGroupError = isrGroupError_##canDev,      \
      .isrGroupBusOff = isrGroupBusOff_##canDev,    \
      .isrMB0 = isrMB0_##canDev,                    \
      .isrMB1 = isrMB1_##canDev,                    \
      .isrMB2 = isrMB2_##canDev,                    \
      .isrMB3 = isrMB3_##canDev,                    \
      .isrMB4 = isrMB4_##canDev,                    \
      .isrMB5 = isrMB5_##canDev,                    \
      .isrMB6 = isrMB6_##canDev,                    \
      .isrMB7 = isrMB7_##canDev,                    \
      .isrMB8 = isrMB8_##canDev,                    \
      .isrMB9 = isrMB9_##canDev,                    \
      .isrMB10 = isrMB10_##canDev,                  \
      .isrMB11 = isrMB11_##canDev,                  \
      .isrMB12 = isrMB12_##canDev,                  \
      .isrMB13 = isrMB13_##canDev,                  \
      .isrMB14 = isrMB14_##canDev,                  \
      .isrMB15 = isrMB15_##canDev,                  \
      .isrGroupMB16_31 = isrGroupMB16_31_##canDev,  \
      .isrGroupMB32_63 = isrGroupMB32_63_##canDev,  \
    },
#endif


#if defined(MCU_MPC5748G)
/** Interrupt offsets, taken from MCU reference manual, see 23.1.2 INTC interrupt
    sources, p. 523ff, Table 23-1.
      The interrupts are regularly defined, therefore we can compute the wanted
    number. The only exception is the very first IRQ, related to pretended network,
    which is available only in device CAN_0. */
# define IDX_IRQ_CAN_FIFO(idxDev)               (IDX_IRQ_CAN_MB(idxDev, /* idxMB */ 5))
# define IDX_IRQ_CAN_ERROR(idxDev)              (CAN0_Error_IRQn + 12*(idxDev))
# define IDX_IRQ_CAN_BOFF_OR_TX_WARN(idxDev)    (CAN0_ORed_IRQn + 12*(idxDev))
# define IDX_IRQ_CAN_MB(idxDev, idxMB)                                                    \
                        (CAN0_ORed_00_03_MB_IRQn + 12u*(idxDev)                           \
                         + ((idxMB)<16u? (idxMB)/4u: ((idxMB)<32u? 4u: (idxMB-32)/32u+5u))\
                        )
#else /* MPC5775B/E */

/** Interrupt offsets, taken from MCU MPC5775B reference manual, see 4.2 Interrupt vector
    assignments, p. 100ff, Table 4-4.
      The interrupts are identically defined for all devices, therefore we can compute the
    wanted number from the base index. */
# define IDX_IRQ_CAN_FIFO_RX(idxDev)        (IDX_IRQ_CAN_MB(idxDev, /* idxMB */ 5))
# define IDX_IRQ_CAN_FIFO_WARN(idxDev)      (IDX_IRQ_CAN_MB(idxDev, /* idxMB */ 6))
# define IDX_IRQ_CAN_FIFO_FULL(idxDev)      (IDX_IRQ_CAN_MB(idxDev, /* idxMB */ 7))
# define IDX_IRQ_CAN_ERROR(idxDev)          (IDX_IRQ_CAN(idxDev) + 1u)
# define IDX_IRQ_CAN_BOFF_OR_TX_WARN(idxDev)(IDX_IRQ_CAN(idxDev) + 0u)
# define IDX_IRQ_CAN_MB(idxDev, idxMB)      (IDX_IRQ_CAN(idxDev) + 3u                       \
                                             + ((idxMB)<16u? idxMB: ((idxMB)<32u? 16u: 17u))\
                                            )
# define IDX_IRQ_CAN(idxDev)                (idxDev<=1? (idxDev==0? 152: 280)               \
                                                      : (idxDev==2? 173: 308)               \
                                            )
#endif /* Which MCU derivative? */


/*
 * Global type definitions
 */

/** This is an entry of a table, which holds pointers to all required CAN ISRs of the MCU.
    Such an array entry holds the ISRs for one enabled CAN device. A table with such
    entries is needed for a function that registers the CAN interrupts. The alternative
    would be a long list of dedicated calls of the register-function. Either solutions
    won't make a significant difference in terms of ROM consumption. */
typedef struct cdr_setOfCanDeviceISRs_t
{
#if defined(MCU_MPC5748G)
    void (*isrGroupFIFO)(void);   /** Hdlr for all Rx FIFO related interrupts. */
#else /* MPC5775B/E */
    void (*isrFIFORx)(void);      /** Hdlr for Rx FIFO on-reception interrupt. */
    void (*isrFIFOWarning)(void); /** Hdlr for Rx FIFO nearly-full interrupt. */
    void (*isrFIFOOverflow)(void);/** Hdlr for Rx FIFO overfull interrupt. */
#endif
    void (*isrGroupError)(void);  /** Hdlr for all interrupts ERRINT and ERRINT_FAST. */
    void (*isrGroupBusOff)(void); /** Hdlr for all Bus off and warning interrupts. */
#if defined(MCU_MPC5748G)
    void (*isrGroupMB0_3)(void);  /** Hdlr for all Rc/Tx interrupts of mailboxes 0..3. */
    void (*isrGroupMB4_7)(void);  /** Hdlr for all Rc/Tx interrupts of mailboxes 4..7. */
    void (*isrGroupMB8_11)(void); /** Hdlr for all Rc/Tx interrupts of mailboxes 8..11. */
    void (*isrGroupMB12_15)(void);/** Hdlr for all Rc/Tx interrupts of mailboxes 12..15. */
#else /* MPC5775B/E */
    void (*isrMB0)(void);         /** Hdlr for Rc/Tx interrupts of mailbox 0. */
    void (*isrMB1)(void);         /** Hdlr for Rc/Tx interrupts of mailbox 1. */
    void (*isrMB2)(void);         /** Hdlr for Rc/Tx interrupts of mailbox 2. */
    void (*isrMB3)(void);         /** Hdlr for Rc/Tx interrupts of mailbox 3. */
    void (*isrMB4)(void);         /** Hdlr for Rc/Tx interrupts of mailbox 4. */
    void (*isrMB5)(void);         /** Hdlr for Rc/Tx interrupts of mailbox 5. */
    void (*isrMB6)(void);         /** Hdlr for Rc/Tx interrupts of mailbox 6. */
    void (*isrMB7)(void);         /** Hdlr for Rc/Tx interrupts of mailbox 7. */
    void (*isrMB8)(void);         /** Hdlr for Rc/Tx interrupts of mailbox 8. */
    void (*isrMB9)(void);         /** Hdlr for Rc/Tx interrupts of mailbox 9. */
    void (*isrMB10)(void);        /** Hdlr for Rc/Tx interrupts of mailbox 10. */
    void (*isrMB11)(void);        /** Hdlr for Rc/Tx interrupts of mailbox 11. */
    void (*isrMB12)(void);        /** Hdlr for Rc/Tx interrupts of mailbox 12. */
    void (*isrMB13)(void);        /** Hdlr for Rc/Tx interrupts of mailbox 13. */
    void (*isrMB14)(void);        /** Hdlr for Rc/Tx interrupts of mailbox 14. */
    void (*isrMB15)(void);        /** Hdlr for Rc/Tx interrupts of mailbox 15. */
#endif
    void (*isrGroupMB16_31)(void);/** Hdlr for all Rc/Tx interrupts of mailboxes 16..31. */
    void (*isrGroupMB32_63)(void);/** Hdlr for all Rc/Tx interrupts of mailboxes 32..63. */
#if defined(MCU_MPC5748G)
    void (*isrGroupMB64_95)(void);/** Hdlr for all Rc/Tx interrupts of mailboxes 64..95. */
#endif
} cdr_setOfCanDeviceISRs_t;


/*
 * Global data declarations
 */


/*
 * Global prototypes
 */



/*
 * Global inline functions
 */


#endif  /* CDR_INTERRUPT_SERVICE_HANDLERS_MPC5748G_INCLUDED */
