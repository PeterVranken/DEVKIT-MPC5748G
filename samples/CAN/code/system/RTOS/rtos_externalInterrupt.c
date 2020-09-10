/**
 * @file rtos_externalInterrupt.c
 * This module holds a few routines, which are needed to configure the handling of External
 * Interrupts (IVOR #4). The interrupt controller is initialized and the operating system
 * code has the chance to register the handlers for particular I/O interrupts.\n
 *   The code in this module used to be part of the startup code in the other samples.
 *
 * Copyright (C) 2017-2020 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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
 *   rtos_osInitINTCInterruptController
 *   rtos_osRegisterInterruptHandler
 *   rtos_dummyINTCInterruptHandler
 * Module inline interface
 * Local functions
 */

/*
 * Include files
 */


#include <limits.h>
#include <assert.h>

#include "typ_types.h"
#include "MPC5748G.h"
#include "rtos.h"
#include "rtos_externalInterrupt.h"


/*
 * Defines
 */

/** Helper macro: An OS handler from the interrupt service has configurable properties,
    which are encoded in unused bits of the address of the handler function. The macro
    helps composing the needed handler representation. */
#define IRQ_HANDLER(fct, isPreemptable) (void (*)())                                \
                                        (isPreemptable? (uintptr_t)(fct)+(1u<<31u)  \
                                                      : (uintptr_t)(fct)            \
                                        )

/*
 * Local type definitions
 */


/*
 * Local prototypes
 */

/** The empty default interrupt service routine. */
void rtos_dummyINTCInterruptHandler(void);


/*
 * Data definitions
 */

/** The table of pointers to the actual IRQ service routines is implemented in the
    assembler code (There we have better control of the required alignment constraints.)\n
      Note, the specified functions are normal, proper C functions; no considerations about
    specific calling conventions (e.g. without stack frame) or according type decorations
    need to be made. */
extern rtos_interruptServiceRoutine_t rtos_INTCInterruptHandlerAry[753];


#if DEBUG
/** The assembly code in rtos_ivorHandler.S, which defines the table of External Interrupt
    handlers exports the end of the table area in order to support some consistency tests.
    The declaration is not needed besides an assertion and is therefore not made public. We
    require an external declaration to become able to access it. */
extern rtos_interruptServiceRoutine_t rtos_endOfINTCInterruptHandlerAry[0];

/** If an interrupt is enabled in an I/O device but there's no handler registered at the
    INTC then a dummy handler is installed, which will halt the software in an assertion
    and report the causing interrupt in this global variable.
      @remark This is a development tool only and not compiled in PRODUCTION compilation.
      @todo This variable should reside in shared, uncached memory. */
volatile uint32_t SECTION(.data.OS.rtos_idxUnregisteredInterrupt)
                                                rtos_idxUnregisteredInterrupt = UINT_MAX;

/** If a an unregistered interrupt service has been reported by \a inc_idxUnregisteredInterrupt    then this variable holds the ID of the processor core, which had taken the interrupt.
      @todo This variable should reside in shared, uncached memory. */
/// @todo Looks like a bug not to put this in OS memory?
/// @todo Bad naming: inc_ vs. rtos_ 
volatile uint32_t inc_pirUnregisteredInterrupt = UINT32_MAX;

#endif


/*
 * Function implementation
 */

/**
 * Dummy interrupt handler. On initialization of the INTC (see
 * rtos_osInitINTCInterruptController()), this function is put into all interrupt vectors
 * in the table.\n
 *   The dummy handler can't reasonably service the interrupt. It would need to know the
 * source of interrupt to acknowledge the interrupt there (mostly the interrupt bit in the
 * status word of an I/O device needs to be cleared). Without doing this acknowledge, the
 * same interrupt would be served immediately again after return from the handler. This is
 * effectively an infinite loop. Better to report this as a problem - in DEBUG compilation
 * an assertion fires. In PRODUCTION compilation it does nothing and returns but the
 * initialization has given it a priority that will make the interrupt never be served at
 * all.\n
 *   To implement a real service, you would replace the default handler by your service
 * implementation using rtos_osRegisterInterruptHandler().
 *   @remark
 * The implementation is not reentrant. If the exceptional unregistered interrupt appears
 * coincidentally on more than one core then the recording of PIR and ISR number fails.
 */
void rtos_dummyINTCInterruptHandler(void)
{
    /* If this assertion fired then you enabled an interrupt on hardware level (I/O device
       configuration) but you didn't use rtos_osRegisterInterruptHandler() in your code to
       install an adequate service handler for it.
         You can find the address of the interrupt vector in register INTC_IACKR_PRC0, or
       0xfff48010. Subtract the address of the SW vector table rtos_INTCInterruptHandlerAry
       (see application map file) and divide by word size 4; this yields the interrupt
       index, which can be resolved to the interrupt source with help of the MCU reference
       manual, section 28.7, table 28-4. */
#if DEBUG
    /* We put the causing interrupt into a global debug variable for convenience and
       acknowledge the interrupt for this core. */
    uint32_t IACKR;
/// @todo Do we need the switch? Didn't we install the handler only for servicing at core 0?
    switch(inc_pirUnregisteredInterrupt=rtos_osGetIdxCore())
    {
/// @todo IACKRn must not be evaluated because of the side effect in the INTC. (Priority stack is manipulated)
    case 0 /* Z4A */:
        IACKR = INTC->IACKR0;
        break;
    case 1 /* Z4B */:
        IACKR = INTC->IACKR1;
        break;
    case 2 /* Z2 */:
        IACKR = INTC->IACKR2;
        break;
    default:
        IACKR = 0;
    }
    
    rtos_idxUnregisteredInterrupt = (IACKR - (uint32_t)&rtos_INTCInterruptHandlerAry[0]) / 4;
    
    /** @todo The use of assertions is critical in a safety design. See file
        assert_config.h for details. Here, we a have particular additional complextiy: If
        the assertion is configured not to halt the SW execution then we have corrupted the
        internal prio stack of the INTC and we can't safely continue.\n
          Double-check and read the IACKRn only in case of a compatible assert
        configuration. */
    assert(false);
#endif
} /* End of rtos_dummyINTCInterruptHandler */



/**
 * Initialize the interrupt controller INTC. The interrupt table with all interrupt service
 * descriptors is initialized to contain a dummy ISR for all interrupts and it is then
 * registered at the hardware device INTC for use.\n
 *   The interrupt default handler is rtos_dummyINTCInterruptHandler(). It does nothing in
 * PRODUCTION compilation but an assertion will fire in DEBUG compilation in order to
 * indicate the missing true handler for an enabled interrupt. The dummy interrupt handlers
 * are registered for handling by core 0.\n
 *   Note, this function temporarily clears the enable External Interrupts bit in the
 * machine status register but won't have changed it on return. Usually, you will call it
 * at system startup time, when all interrupts are still disabled, then call
 * rtos_osRegisterInterruptHandler() repeatedly for all interrupts your code is interested
 * in, then start the other cores and eventually enable the interrupt processing at the
 * CPUs.
 *   @remark
 * This function must be called from supervisor mode only.
 */
void rtos_osInitINTCInterruptController(void)
{
    assert((unsigned long)&rtos_endOfINTCInterruptHandlerAry
           - (unsigned long)&rtos_INTCInterruptHandlerAry[0]
           == sizeof(rtos_INTCInterruptHandlerAry)
          );

    /* Prepare the vector table with all interrupts being served by our problem reporting
       dummy handler. */
    unsigned int u;
    for(u=0; u<sizeOfAry(rtos_INTCInterruptHandlerAry); ++u)
    {
/// @todo This can become a sub-routine, which can then be applied in registerService to check user input
        /* Handlers for MCU-internally unconnected IRQs must not be registered. This yields
           a machine check exception. See RM, section 23, table 23-1, p. 523 for the list
           of connected IRQs. The gaps in the sequence of "Vector numbers" in the table are
           unconnected interrupts. */
        if(u >= 24  &&  u <= 31
           ||  u == 35
           ||  u >= 48  &&  u <= 51
           ||  u >= 85  &&  u <= 184
           ||  u >= 186  &&  u <= 189
           ||  u >= 194  &&  u <= 200
           ||  u >= 219  &&  u <= 223
           ||  u >= 247  &&  u <= 249
           ||  u == 256
           ||  u == 303
           ||  u == 312
           ||  u == 321
           ||  u == 330
           ||  u == 339
           ||  u >= 348  &&  u <= 371
           ||  u >= 374  &&  u <= 375
           ||  u >= 430  &&  u <= 439
           ||  u == 441
           ||  u == 443
           ||  u == 445
           ||  u >= 447  &&  u <= 452
           ||  u >= 463  &&  u <= 479
           ||  u >= 481  &&  u <= 487
           ||  u >= 491  &&  u <= 495
           ||  u >= 528  &&  u <= 547
           ||  u >= 551  &&  u <= 553
           ||  u >= 557  &&  u <= 559
           ||  u >= 563  &&  u <= 564
           ||  u >= 575  &&  u <= 577
           ||  u >= 587  &&  u <= 589
           ||  u >= 599  &&  u <= 601
           ||  u >= 611  &&  u <= 613
           ||  u >= 623  &&  u <= 625
           ||  u >= 635  &&  u <= 637
           ||  u >= 647  &&  u <= 649
           ||  u >= 659  &&  u <= 667
           ||  u >= 672  &&  u <= 679
           ||  u == 681
           ||  u >= 684  &&  u <= 685
           ||  u >= 688  &&  u <= 689
           ||  u >= 696  &&  u <= 700
           ||  u >= 703  &&  u <= 705
          )
        {
            continue;
        }

        /* Note, in DEBUG compilation we configure the dummy handler with a priority that
           will make it used; the reason is that the dummy handler - although it can't
           really do the job of interrupt servicing - can report the problem of a bad
           interrupt configuration in the user code. (It's assumed that debugger is
           available during development time.) In PRODUCTION compilation, the dummy handler
           will never serve because of the priority being zero. */
        rtos_osRegisterInterruptHandler( &rtos_dummyINTCInterruptHandler
                                       , /* processorID */ 0
                                       , /* vectorNum */ u
#ifdef DEBUG
                                       , /* psrPriority */ 1
#else
                                       , /* psrPriority */ 0
#endif
                                       , /* isPreemptable */ false
                                       );
    } /* for(All entries in the INTC vector table) */

    /* Normally, this function should always be called at the very first beginning, when
       all interrupts are still globally disabled at the CPUs. However, we make it safe
       against deviating code constructs if we locally disable all interrupts. */
    uint32_t msr = rtos_osEnterCriticalSection();

    /* Block Configuration register, INTC_BCR
         HVEN0, HVEN1, HVEN2: 0 for SW vector mode, 1 for HW vector mode. */
    INTC->BCR = INTC_BCR_HVEN0(0) | INTC_BCR_HVEN1(0) | INTC_BCR_HVEN2(0);

    /* The address of our vector table is stored in field VTBA of the interrupt acknowledge
       register. Only the most significant 20 Bit will matter, the reset will at run-time
       be replaced by the index of the pending interrupt.
         Normally, the interrupt vector table, which consumes a lot of expensive RAM, is
       used for all three cores. The working assumption is that a given interrupt will be
       served either by one or another core, so that no conflicts occur.
         This assumption is checked by assertion in inc_installINTCInterruptHandler. */
    INTC->IACKR0 =
    INTC->IACKR1 =
    INTC->IACKR2 = (uint32_t)&rtos_INTCInterruptHandlerAry[0];

    /* The current priority is set to 0 for all cores. */
    INTC->CPR0 = INTC_CPR0_PRI(0);
    INTC->CPR1 = INTC_CPR0_PRI(0);
    INTC->CPR2 = INTC_CPR0_PRI(0);

    /* Restore the machine status register including the enable external interrupt bit.
       For the normal, intended use case this won't have an effect. */
    rtos_osLeaveCriticalSection(msr);

} /* End of rtos_osInitINTCInterruptController */




/**
 * This function can be used to install an interrupt service for a given I/O device
 * and a given core. It will also set the Priority Select Register for the I/O device's
 * IRQ to the desired value.
 *   @param pInterruptHandler
 * The interrupt service routine by reference. An ordinary C function in the user code area,
 * which is called when the according interrupt is served.
 *   @param processorID
 * The interrupt is assigned to the processor of this ID. Allowed are: 0 for Z4A, 1 for Z4B
 * or 2 for Z2.\n
 *   Note, the implementation avoids having different vector tables for the three cores.
 * The work assumption is that an I/O interrupt will normally be served by either one or
 * another core. The INTC HW permits signalling any interrupt to any set of cores. Both
 * statements are combined in that setting an interrupt vector to a core A will cause an
 * assertion if the same interrupt had been registered already before for another core B
 * and the registration for A had specified another interrupt service routine.\n
 *   In the rare case of needing one interrupt on different cores the ISR needs
 * to query the processor ID so that the implementation of the handler can become
 * processor dependent.
 *   @param vectorNum
 * All possible external interrupt sources are hardwired to the interrupt controller. They
 * are indentified by index. The table, which interrupt source (mostly I/O device) is
 * connected to the controller at which index can be found in the MCU reference manual,
 * section 23.1.2, table 23-1, p. 523ff.
 *   @param psrPriority
 * The priority at which the interrupt is served. Range is 0..15, checked by assertion. 0
 * is useless, it would never be served, 1 is the lowest real priority and 15 the highest.
 * Preemption of a handler (if enabled), which serves an interrupt of priority n will be
 * possible only by another interrupt of priority n+1 or higher.
 *   @param isPreemptable
 * For each interrupt it can be said, whether it is preemptable by other interrupts of
 * higher priority or not. If this is \a false then the interrupt handler will always be
 * entered with the status bit EE reset in the machine status register MSR of the servicing
 * core.\n
 *   Note, a handler, which has been declared non-premptable is allowed to set the EE bit
 * itself. It can thus first do some operations without any race-conditions with other
 * interrupts and then continue without further locking normal interrupt processing.
 *   @remark
 * The function can be used at any time. It is possible to exchange a handler at run-time,
 * while interrrupts are being processed, but only on the processor, which invokes this
 * function. However, the normal use case will rather be to call this function for all
 * required interrupts and only then call the other function inc_resumeAllInterrupts() on
 * all the processors.\n
 *   This function must not be called for an interrupt vector number n from within an ISR
 * of that interrupt vector number and it must not be called from processor i for processor
 * j!=i, if that processor is running.
 *   @remark
 * On an MPC5748G, all cores share the function code. A core should use this function to
 * install its ISRs, regardless whether or not it runs the RTOS. A typical scenario
 * would be running the RTOS only on one core, but the others should still use this
 * function to install their ISRs.
 *   @remark
 * This function must be called from supervisor mode only.
 */
void rtos_osRegisterInterruptHandler( const rtos_interruptServiceRoutine_t pInterruptHandler
                                    , unsigned int processorID
                                    , unsigned int vectorNum
                                    , unsigned int psrPriority
                                    , bool isPreemptable
                                    )
{
    assert(processorID <= 2  &&  vectorNum < sizeOfAry(rtos_INTCInterruptHandlerAry)
           &&  psrPriority <= 15
          );
    
    /* Compute the function pointer in the ISR Handler table. We use the uppermost bit of
       the address to store the preemption information. This convention is known and
       considered by the assembler code that implements the common part of all INTC
       interrupts. */
    assert(((uintptr_t)pInterruptHandler & 0x80000000u) == 0);
    void (*pDecoratedInterruptHandler)(void);
/// @todo Check: Why do we have a macro IRQ_Handler with argument isPreemtable but we still need an if?   
    if(isPreemptable)
        pDecoratedInterruptHandler = IRQ_HANDLER(pInterruptHandler, isPreemptable);
    else    
        pDecoratedInterruptHandler = pInterruptHandler;
    
    /* We permit to use this function at any time, i.e. even while interrupts may occur. We
       need to disable them shortly to avoid inconsistent states (vector and priority).
         Note, this means still doesn't make it safe to exchange an interrupt handler on
       another, already running core. This is not detected and can cause a crash. */
    uint32_t msr = rtos_osEnterCriticalSection();

    /* The mask in register PSR to select the interrupt for the given core.
          Caution: After reset, all interrupts are associated with core 0. This can be
       filtered out by inspecting the field PRI, which is set to zero after reset. PRI=zero
       effectively means no interrupt assignment and then we don't need to consider the set
       of cores so far. */
    const uint32_t psrPrcSelNew = 0x2000u << (2-processorID)
                 , psrPrcSelSoFar = (INTC->PSR[vectorNum] & INTC_PSR_PRIN_MASK) != 0
                                    ? INTC->PSR[vectorNum]
                                      & (INTC_PSR_PRC_SELN0_MASK
                                         | INTC_PSR_PRC_SELN1_MASK
                                         | INTC_PSR_PRC_SELN2_MASK
                                        )
                                    : 0;
    assert((psrPrcSelNew 
            & (INTC_PSR_PRC_SELN0_MASK | INTC_PSR_PRC_SELN1_MASK | INTC_PSR_PRC_SELN2_MASK)
           ) != 0
          );

    /* Normal situation: The vector is set once but we still have the preliminarily
       registered dummy handler in place. */
    const bool isStillDummyISR = rtos_INTCInterruptHandlerAry[vectorNum]
                                 == rtos_dummyINTCInterruptHandler;

#ifdef DEBUG
    /* We have one vector table shared between all cores. If a handler is assigned to more
       than one core then both cores need to use the same service routine. This is checked
       in DEBUG compilation. */
    if(rtos_INTCInterruptHandlerAry[vectorNum] != pDecoratedInterruptHandler
       && !isStillDummyISR
      )
    {
        /* The ISR is changed. It's likely an implementation error if the new core
           assignment deviates from the elder one. The user may have misunderstood the
           single-handler-table concept: First he registers an IRQ with ISR A on core i and
           then the same IRQ with another ISR B on core i != j. This is not supported and
           reported by assertion.
             The assertion doesn't fire if for a single core the existing registration of
           the IRQ with an ISR A is changed to another ISR B. */
        assert(psrPrcSelSoFar == psrPrcSelNew);
    }
#endif    

    /* Set the function pointer in the ISR Handler table. */
    rtos_INTCInterruptHandlerAry[vectorNum] = pDecoratedInterruptHandler;

    /* Set priority and core in the PSR. The use case of signalling one and the same IRQ to
       one and the same ISR on different cores at a time is supported by or'ing the core
       flags. The previous core is however dropped if it is just the initial registration of
       the dummy handler. */
    INTC->PSR[vectorNum] = (uint16_t)(psrPrcSelNew
                                      | (!isStillDummyISR? psrPrcSelSoFar: 0u)
                                      | INTC_PSR_PRIN(psrPriority)
                                     );

    rtos_osLeaveCriticalSection(msr);

} /* End of rtos_osRegisterInterruptHandler */



