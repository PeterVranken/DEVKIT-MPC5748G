#ifndef INC_INTCINTERRUPTCONTROLLER_INCLUDED
#define INC_INTCINTERRUPTCONTROLLER_INCLUDED
/**
 * @file inc_INTCInterruptController.h
 * Definition of global interface of module inc_INTCInterruptController.c
 *
 * Copyright (C) 2018 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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
 *   ihw_installINTCInterruptHandler
 *   ihw_suspendAllInterrupts
 *   ihw_resumeAllInterrupts
 *   ihw_enterCriticalSection
 *   ihw_leaveCriticalSection
 */

/*
 * Include files
 */

#include <stdint.h>
#include <stdbool.h>

#include "typ_types.h"


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
 * Global inline functions
 */

/**
 * Disable all External Interrupts. This is done unconditionally, there's no nesting
 * counter.
 *   @remark Note, suspending all External Interrupts does not affect all other interrupts
 * (effectively CPU traps), like Machine Check interrupt.
 *   @remark The function can be called on every core and relates to that core only.
 */
static TYP_ALWAYS_INLINE void inc_suspendAllInterrupts()
{
    asm volatile ( /* AssemblerTemplate */
                   "wrteei 0\n"
                 : /* OutputOperands */
                 : /* InputOperands */
                 : /* Clobbers */
                 );
} /* End of inc_suspendAllInterrupts */



/**
 * Enable all External Interrupts. This is done unconditionally, there's no nesting
 * counter.
 *   @remark The function can be called on every core and relates to that core only.
 */
static TYP_ALWAYS_INLINE void inc_resumeAllInterrupts()
{
    /// @todo wrteei is execution synchronizing and doesn't require an addition msync. See EREF 2.0, 4.5.4.5. Look for CRM, e200z4, too, there is a more condensed, even simpler understandable, similar statement. Same for other location in this file and in mutex.h
    asm volatile ( /* AssemblerTemplate */
                   "msync\n\t"
                   "wrteei 1\n"
                 : /* OutputOperands */
                 : /* InputOperands */
                 : /* Clobbers */
                 );
} /* End of inc_resumeAllInterrupts */



/**
 * Start the code of a critical section, thus code, which operates on data, that must not
 * be touched from another execution context at the same time.\n
 *   The critical section is implemented by globally disabling all interrupts.
 *   @return
 * The machine status register content of before disabling the interrupts is returned. The
 * caller will safe it and pass it back to inc_leaveCriticalSection() at the end of the
 * critical section. This way the nestability is implemented.
 *   @remark
 * The main difference of this function in comparison to inc_suspendAllInterrupts() is the
 * possibility to nest the calls at different hierarchical code sub-function levels.
 *   @remark The function can be called on every core and relates to that core only. A
 * critical section with code running on another core cannot be implemented using this
 * function.
 */
static TYP_ALWAYS_INLINE uint32_t inc_enterCriticalSection()
{
    uint32_t msr;
    asm volatile ( /* AssemblerTemplate */
                   "mfmsr %0 /* Save the current state of the MSR */\n\t"
                   "wrteei 0 /* Stop processing of External Interrupts */\n\t"
                 : /* OutputOperands */ "=r" (msr)
                 : /* InputOperands */
                 : /* Clobbers */
                 );
    return msr;

} /* End of inc_enterCriticalSection */



/**
 * End the code of a critical section, thus code, which operates on data, that must not
 * be touched from another execution context at the same time.\n
 *   The critical section is implemented by globally disabling all interrupts.
 *   @param msr
 * The machine status register content as it used to be at entry into the critical section.
 * See inc_enterCriticalSection() for more.
 *   @remark The function can be called on every core and relates to that core only. A
 * critical section with code running on another core cannot be implemented using this
 * function.
 */
static TYP_ALWAYS_INLINE void inc_leaveCriticalSection(uint32_t msr)
{
    asm volatile ( /* AssemblerTemplate */
                   "msync   /* Accomplish all load/store before ending the critical section */\n\t"
                   "wrtee   %0 /* Restore MSR[EE] */\n"
                 : /* OutputOperands */
                 : /* InputOperands */ "r" (msr)
                 : /* Clobbers */
                 );
} /* End of inc_leaveCriticalSection */



/*
 * Global prototypes
 */

/** Initialize the interrupt controller INTC. */
void inc_initINTCInterruptController(void);

/** Let the client code install an interrupt handler. */
void inc_installINTCInterruptHandler( void (*interruptHandler)(void)
                                    , unsigned int processorID
                                    , unsigned int vectorNum
                                    , unsigned char psrPriority
                                    , bool isPreemptable
                                    );

#endif  /* INC_INTCINTERRUPTCONTROLLER_INCLUDED */
