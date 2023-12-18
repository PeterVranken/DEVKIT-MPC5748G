#ifndef HWC_HARDWARECONFIGURATION_INCLUDED
#define HWC_HARDWARECONFIGURATION_INCLUDED
/**
 * @file hwc_hardwareConfiguration.h
 * Global hardware configuration. This file is read by both C and assembly code to make the
 * source code independent from the chosen hardware configuration.
 *
 * @remark The file needs to be compatible with the assembler syntax. Complex C
 * expressions, which may be desirable to express dependencies between different settings
 * or to exploit releationships between settings, must not been used. If such dependecies
 * exist then appropriate constructs will be applied somewhere in the C code to
 * double-check and ensure that all such dependencies between the #define's made here are
 * respected. Such constructs can be preprocessor conditionals or static or run-time
 * assertions, whatever is appropriate.
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


/*
 * Defines
 */

/** Switch instruction cache on. */
#define HWC_ENABLE_ICACHE               1

/** Switch data cache on. */
#define HWC_ENABLE_DCACHE               1

/** Switch branch prediction on. */
#define HWC_ENABLE_BRANCH_PREDICTION    1

/** Configuration of HID0. See CRM, section 2.4.11 Hardware Implementation Dependent
    Register 0 (HID0), p. 48ff. Note, the CRM is not specific for the derivative, MPC5748G.
    This derivative doesn't support the following bits:\n
      - HWC_AT_BIT(0, 8)    // DOZE, Configure for Doze power management mode 
      - HWC_AT_BIT(0, 9)    // NAP, Configure for Nap power management mode 
      - HWC_AT_BIT(0, 10)   // SLEEP, Configure for Sleep power management mode 
      - HWC_AT_BIT(1, 17)   // TBEN, enable Time Base 
      - HWC_AT_BIT(0, 18)   // SEL_TBCLK, select Time Base clock. 0: Core clock 
      - HWC_AT_BIT(0, 23)   // DAPUEN, Debug APU enable */
#define HWC_HID0                                                                            \
            (HWC_AT_BIT(0, 0)       /* EMCP, Enable machine check pin (p_mcp_b) */          \
             | HWC_AT_BIT(0, 14)    /* ICR, Interrupt inputs clear reservation */           \
             | HWC_AT_BIT(1, 15)    /* NHR, Not hardware reset */                           \
             | HWC_AT_BIT(0, 19)    /* DCLREE, Debug Interrupt clears MSR[EE] */            \
             | HWC_AT_BIT(0, 20)    /* DCLRCE, Debug Interrupt clears MSR[CE] */            \
             | HWC_AT_BIT(0, 21)    /* CICLRDE, Critical Interrupt clears MSR[DE] */        \
             | HWC_AT_BIT(0, 22)    /* MCCLRDE, Machine Check Interrupt clears MSR[DE] */   \
             | HWC_AT_BIT(1, 31)    /* NOPTI, no-op for cache touch instructions */         \
            )

/** Configuration of HID0. See CRM, section 2.4.12 Hardware Implementation Dependent
    Register 1 (HID1), p. 50f. Note, the CRM is not specific for the derivative, MPC5748G.
    This derivative doesn't support the following bits:\n
      - HWC_AT_BIT(0x00, 23)  // SYSCTL, system control, 8 Bit output port */
#define HWC_HID1                                                                            \
            (HWC_AT_BIT(0, 22)      /* HP_NOR, bus prio elevation for other exceptions */   \
             | HWC_AT_BIT(0, 23)    /* HP_NMI, bus prio elevation for NMI and CI */         \
             | HWC_AT_BIT(0, 24)    /* ATS, atomic status (read-only of reservation status) */\
            )

/** Helper macro: Place a certain bit field at a particular bit in a 32 Bit word.
      @param field The bit field contents
      @param at The index 0..31 of the bit in the 32 Bit word, where the least significant
    bit of \a field is placed. The index uses the Power Architecture counting, where 0
    means the most significant bit. */
#define HWC_AT_BIT(field, at)   ((field)<<(31-(at)))


/*
 * Global type definitions
 */


/*
 * Global data declarations
 */


/*
 * Global prototypes
 */



#endif  /* HWC_HARDWARECONFIGURATION_INCLUDED */
