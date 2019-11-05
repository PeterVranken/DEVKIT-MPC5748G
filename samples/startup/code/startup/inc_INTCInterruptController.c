/**
 * @file inc_initMcuCoreHW.c
 * The interrupt controller is configured and enabled here.
 *
 * Copyright (C) 2017-2018 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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
 *   inc_dummyINTCInterruptHandler
 *   inc_initINTCInterruptController
 *   inc_installINTCInterruptHandler
 * Local functions
 */

/*
 * Include files
 */

#include <stdint.h>
#include <limits.h>
#include <assert.h>

#include "typ_types.h"
#include "MPC5748G.h"
#include "std_decoratedStorage.h"
#include "inc_INTCInterruptController.h"


/*
 * Defines
 */


/*
 * Local type definitions
 */


/*
 * Local prototypes
 */

/** The empty default interrupt service routine. */
void inc_dummyINTCInterruptHandler(void);


/*
 * Data definitions
 */

/** The table of function pointers into the actual IRQ handlers is implemented in the
    assembler code (There we have better control of the required alignment constraints.)\n
      Note, the entries in the table are normal, proper C functions; no considerations
    about specific calling conventions (e.g. without stack frame) or according type
    decorations need to be made. */
extern void (*int_INTCInterruptHandlerAry[753])(void);

#if DEBUG
/** If an interrupt is enabled in an I/O device but there's no handler registered at the
    INTC then a dummy handler is installed, which will halt the software in an assertion
    and report the causing interrupt in this global variable.
      @remark This is a development tool only and not compiled in PRODUCTION compilation.
      @todo This variable should reside in shared, unchaced memory. */
volatile uint32_t inc_idxUnregisteredInterrupt = UINT32_MAX;

/** If a an unregistered interrupt service has been reported by \a inc_idxUnregisteredInterrupt    then this variable holds the ID of the processor core, which had taken the interrupt.
      @todo This variable should reside in shared, unchaced memory. */
volatile uint32_t inc_pirUnregisteredInterrupt = UINT32_MAX;

#endif


/*
 * Function implementation
 */

/**
 * Dummy interrupt handler. On initialization of the INTC
 * (initINTCInterruptController()), this function is put into all 256 interrupt vectors
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
 * implementation using inc_installINTCInterruptHandler().
 *   @remark
 * The implementtaion is not reentrant. If the exceptional unregistered interrupt appears
 * coincidentally on more than one core then the recording of PIR and ISR number fails.
 */
void inc_dummyINTCInterruptHandler(void)
{
    /* If this assertion fired then you enabled an interrupt on hardware level (I/O device
       configuration) but you didn't use inc_installINTCInterruptHandler() in your code to
       install an adequate service handler for it.
         You can find the address of the interrupt vector in register INTC_IACKR_PRC0, or
       0xfff48010. Subtract the address of the SW vector table int_INTCInterruptHandlerAry
       (see application map file) and devide by word size 4; this yields the interrupt
       index, which can be resolved to the interrupt source with help of the MCU reference
       manual, section 28.7, table 28-4. */
#if DEBUG
    /* We put the causing interrupt into a global debug variable for convenience and
       acknowledge the interrupt for this core. */
    uint32_t IACKR;
    switch(inc_pirUnregisteredInterrupt=std_getCoreID())
    {
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
    
    inc_idxUnregisteredInterrupt = (IACKR - (uint32_t)&int_INTCInterruptHandlerAry[0]) / 4;
    
    assert(false);
#endif
} /* End of inc_dummyINTCInterruptHandler */



/**
 * Initialize the interrupt controller INTC. The interrupt table with all user code
 * handlers is initialized to contain a dummy handler for all interrupts and it is then
 * registered at the hardware device INTC for use.\n
 *   The interrupt default handler is inc_dummyINTCInterruptHandler(). It does nothing in
 * PRODUCTION compilation but an assertion will fire in DEBUG compilation in order to
 * indicate the missing true handler for an enabled interrupt. The dummy interrupt handlers
 * are registers for handling by core 0.\n
 *   Note, this function locally sets but on return it'll not have changed the enable
 * external interrupts bit in the machine status register. You will call it normally at
 * system startup time, when all interrupts are still disabled, then call
 * inc_installINTCInterruptHandler() repeatedly for all interrupts your code is interested
 * in, then start the other cores and eventually enable the interrupt processing at the
 * CPUs.
 */
void inc_initINTCInterruptController(void)
{
    /* Prepare the vector table with all interrupts being served by our problem reporting
       dummy handler. */
    unsigned int u;
    for(u=0; u<sizeOfAry(int_INTCInterruptHandlerAry); ++u)
    {
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
        inc_installINTCInterruptHandler( inc_dummyINTCInterruptHandler
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
    uint32_t msr = inc_enterCriticalSection();

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
    INTC->IACKR2 = (uint32_t)&int_INTCInterruptHandlerAry[0];

    /* The current priority is set to 0 for all cores. */
    INTC->CPR0 = INTC_CPR0_PRI(0);
    INTC->CPR1 = INTC_CPR0_PRI(0);
    INTC->CPR2 = INTC_CPR0_PRI(0);

    /* Restore the machine status register including the enable external interrupt bit.
       For the normal, intended use case this won't have an effect. */
    inc_leaveCriticalSection(msr);
    
} /* End of inc_initINTCInterruptController */




/**
 * This function can be used to install an interrupt handler for a given interrupt vector
 * and a given core. It will also set the Priority Select Register for the source to the
 * one given.
 *   @param interruptHandler
 * The interrupt handler. An ordinary C function in the user code area, which is called
 * when the according interrupt is served.
 *   @param processorID
 * The interrupt is assigned to the processor of this ID. Allowed are: 0 for Z4A, 1 for Z4B
 * or 2 for Z2.\n
 *   Note, the implementation avoids having different vector tables for the three cores.
 * The work assumption is that an I/O interrupt will normally be served by either one or
 * another core. The INTC HW permits signalling any interrupt to any set of cores. Both
 * statements are combined in that setting an interrupt vector to a core A will cause an
 * assertion if the same interrupt had been registered already before for another core B
 * and the registration for A had specified another interrupt service routine.\n
 *   In the rare case of needing one interrupt for different cores the ISR need to query
 * the processor ID so that the implementation of the same handler can become processor
 * dependent.
 *   @param vectorNum
 * All possible external interrupt sources are hardwired to the interrupt controller. They
 * are indentified by index. The table, which interrupt source (mostly I/O device) is
 * connected to the controller at which index can be found in the MCU reference manual,
 * section 23.1.2, table 23-1, p. 523ff.
 *   @param psrPriority
 * The priority at which the interrupt is served. 0..15. 0 is useless, it would never be
 * served, 1 is the lowest real priority and 15 the highest. Preemption of a handler (if
 * enabled), which serves an interrupt of priority n will be possible only by another
 * interrupt of priority n+1 or higher.
 *   @param isPreemptable
 * For each interrupt it can be sayed, whether it is preemptable by other interrupts of
 * higher priority or not. If this is \a false then the interrupt handler will always be
 * entered with the status bit EE reset in the machine status register MSR.\n
 *   Note, a handler, which has been declared non-premptable is allowed to set the EE bit
 * itself. It can thus first do some operations without any race-conditions with other
 * interrupts and then continue without further locking normal interrupt processing.
 *   @remark
 * The function can be used at any time. It is possible to exchange a handler at run-time,
 * while interrrupts are being processed, but only on the processor, which invokes this
 * function. However, the normal use case will rather be to call this function for all
 * required interrupts and only then call the other function inc_resumeAllInterrupts() on
 * the processors.\n
 *   This function must not be called for an interrupt number n from the context of that
 * interrupt n and it must be called from processor i for processor j!=i, if that processor
 * is running.
 */
void inc_installINTCInterruptHandler( void (*interruptHandler)(void)
                                    , unsigned int processorID
                                    , unsigned int vectorNum
                                    , unsigned char psrPriority
                                    , bool isPreemptable
                                    )
{
    assert(processorID <= 2  &&  vectorNum < sizeOfAry(int_INTCInterruptHandlerAry));
    
    /* Compute the function pointer in the ISR Handler table. We use the uppermost bit of
       the address to store the preemption information. This convention is known and
       considered by the assembler code that implements the common part of all INTC
       interrupts. */
    assert(((uintptr_t)interruptHandler & 0x80000000) == 0);
    void (*decoratedInterruptHandler)(void);
    if(isPreemptable)
        decoratedInterruptHandler = (void (*)(void))((uintptr_t)interruptHandler | 0x80000000);
    else    
        decoratedInterruptHandler = interruptHandler;
    
    /* We permit to use this function at any time, i.e. even while interrupts may occur. We
       need to disable them shortly to avoid inconsistent states (vector and priority).
         Note, this means still doesn't make it safe to exchange a interrupt handler on
       another, already running core. This is not detected and can cause a crash. */
    uint32_t msr = inc_enterCriticalSection();

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
    const bool isStillDummyISR = int_INTCInterruptHandlerAry[vectorNum]
                                 == inc_dummyINTCInterruptHandler;
#ifdef DEBUG
    /* We have one vector table shared between all cores. If a handler is assigned to more
       than one core then both cores need to use the same service routine. This is checked
       in DEBUG compilation. */
    if(int_INTCInterruptHandlerAry[vectorNum] != decoratedInterruptHandler
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
    int_INTCInterruptHandlerAry[vectorNum] = decoratedInterruptHandler;

    /* Set priority and core in the PSR. The use case of signalling one and the same IRQ to
       one and the same ISR on different cores at a time is supported by or'ing the core
       flags. The previous core is however dropped if it just the initial registration of
       the dummy handler. */
    INTC->PSR[vectorNum] = (uint16_t)(psrPrcSelNew
                                      | (!isStillDummyISR? psrPrcSelSoFar: 0u)
                                      | INTC_PSR_PRIN(psrPriority)
                                     );

    inc_leaveCriticalSection(msr);
    
} /* End of inc_installINTCInterruptHandler */



