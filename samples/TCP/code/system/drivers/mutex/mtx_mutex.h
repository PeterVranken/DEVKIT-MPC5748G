#ifndef MTX_MUTEX_INCLUDED
#define MTX_MUTEX_INCLUDED
/**
 * @file mtx_mutex.h
 * A little set of reusable, operating system independent synchronization objects. The
 * implementation of these objects founds on the decorated load and store operations, a set
 * of atomic machine instructions.\n
 *   Only simple mutex types can be offered. A basic problem of the decorated store
 * operations inhibits more complex types. The conditional store operation, which strongly
 * resembles the prototypical exchange-register-and-memory operation doesn't tell about the
 * success and the register-and-memory-exchanging load operation does do this
 * unconditional. In the former case, the operation does take the right decision but
 * doesn't let the user know its decision and the latter operation may take the wrong
 * decision but keeps the user informed about that. In the former case a second operation
 * is required to find out and in the second case a second operation is required to
 * conditionally correct. By principal, this second operation is no longer atomic and
 * counting semaphores for example can't be implemented without additional means. It would
 * be a drastic improvement if the conditional store would affect the CPU's condition
 * register.\n
 *   The issue with the "additional means" is their dependency on the operating system and
 * the resulting non-generality. Here, we offer an implementation of a nestable mutex,
 * which is intended for implementing a critical section valid for the execution contexts
 * on all three cores. The implementation combines decorated store with interrupt
 * suspension. Pros and cons are discussed in the function.
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
/* Module inline interface
 *   mtx_acquireMutex
 *   mtx_releaseMutex
 *   mtx_osEnterIntercoreCriticalSection
 *   mtx_osLeaveIntercoreCriticalSection
 *   mtx_osAcquireNestedMutex
 *   mtx_osReleaseNestedMutex
 */

/*
 * Include files
 */

#include <stdint.h>
#include <stdbool.h>

#include "std_decoratedStorage.h"


/*
 * Defines
 */

/** Initial value of a variable of type mtx_mutex_t, which should be initially available to
    all cores. */
#define MTX_MUTEX_INITIALLY_RELEASED (0x00)

/** Initial value of a variable of type mtx_mutex_t, which should be initially acquired by
    one core. */
#define MTX_MUTEX_INITIALLY_ACQUIRED (0x01)

/** Initial value of a variable of type mtx_nestedMutex_t, which should be initially
    available to all cores. */
#define MTX_NESTED_MUTEX_INITIALLY_RELEASED { .mutex = MTX_MUTEX_INITIALLY_RELEASED     \
                                            , .cntInvocationAry =                       \
                                                {[0 ... ((STD_MAX_NO_CORES)-1u)] = 0}   \
                                            }

/** Initial value of a variable of type mtx_intercoreCriticalSection_t. */
#define MTX_INTERCORE_CRITICAL_SECTION  { .mutex = MTX_MUTEX_INITIALLY_RELEASED     \
                                        , .cntInvocationAry =                       \
                                            {[0 ... ((STD_MAX_NO_CORES)-1u)] = 0}   \
                                        , .msr = 0                                  \
                                        }


/*
 * Global type definitions
 */

/** The type of a single, Boolean mutex, which can be acquired by one core at a time. */
typedef uint8_t mtx_mutex_t;

/** The type of a single, Boolean mutex, which can be acquired by one core at a time. The
    mutex has an incocation counter so that several contexts on the same core can compete
    for the mutex without risking a dead lock. */
typedef struct mtx_nestedMutex_t
{
    /** The mutex for mutual exclusion of cores. */
    mtx_mutex_t mutex;

    /** The invocation counters for handling competing access from execution contexts on
        one and the same core. */
    uint16_t cntInvocationAry[STD_MAX_NO_CORES];

} mtx_nestedMutex_t;


/** The type of a critical section, which provides mutual exclusion of all contexts on any
    core. */
typedef struct mtx_intercoreCriticalSection_t
{
    /** The mutex for mutual exclusion of cores. */
    mtx_mutex_t mutex;

    /** The invocation counters for handling competing access from execution contexts on
        one and the same core. */
    uint16_t cntInvocationAry[STD_MAX_NO_CORES];

    /** The status of the MSR[EE] bit on entry into the critical section; used to restore
        this state finally. */
    uint32_t msr;

} mtx_intercoreCriticalSection_t;


/*
 * Global data declarations
 */


/*
 * Global prototypes
 */


/*
 * Global inline functions.
 */

/**
 * Acquire a single mutex.
 *   @return
 * \a true, if mutex could be acquired, \a false if it is currently owned by someone
 * else.\n
 *   Note the function return value is useless (always \a true) if \a wait is \a true and
 * should not be used in this case.
 *   @param pMutex
 * The mutex object by reference.
 *   @param wait
 * If \a true then the mutex becomes a spin lock; the function cycles forever or until the
 * mutex became free and could be locked in the next attempt. There's no arbitration, if
 * more than one core compete for the mutex then starvation is not excluded.
 *   @remark
 * This function can be called from all contexts, in supervisor or user mode.
 *   @remark
 * This function can be called from competing cores or from competing tasks on the same
 * core.\n
 *   Note, if \a wait is \a true then using the function from competing tasks on one and
 * the same core is likely not what you want; mostly tasks are scheduled priority based and
 * waiting could easily mean waiting for a task, which is never scheduled while waiting.
 */
static inline bool mtx_acquireMutex(mtx_mutex_t *pMutex, bool wait)
{
    do
    {
        if((std_setBitInByteAtomic(/* bit */ 7, /* address */ pMutex) & 0x01) == 0)
        {
            /* No operation initiated prior to the acquisition of the mutex should be
               completed after entry into the critical section, which is spawn with the
               mutex. The memory barrier here is meant a kind of instruction flush
               operation. */
            std_fullMemoryBarrier();

            return true;
        }
    }
    while(wait);

    return false;

} /* End of mtx_acquireMutex */



/**
 * Release a previously acquired, single mutex.
 *   @param pMutex
 * The mutex object by reference.
 *   @remark
 * This function is meant a basic implementation only. It doesn't perform any checks. If a
 * mutex is released which had not been successfully acquired before using
 * mtx_acquireMutex() then the mutual exclusion functionality will fail.
 *   @remark
 * This function can be called from all contexts, in supervisor or user mode.
 */
static inline void mtx_releaseMutex(mtx_mutex_t *pMutex)
{
    /* A memory barrier here ensures that all operations inside the critical section, which
       is spawn with the mutex, have completed before we return the mutex. */
    std_fullMemoryBarrier();

    /* We can unconditionally reset the bit: We own the mutex and nobody else will
       interfere on the given bit. */
    std_xorByteAtomic(/* operand */ 0x01, /* address */ pMutex);

} /* End of mtx_releaseMutex */



/**
 * A core-to-core critical section.\n
 *   A context, which returns from this function can be sure that it is the only one on all
 * three cores, which has access to the protected resource, which is typically a shared
 * short section of code. Other contexts on the same local core are disabled by suspension
 * of the handling of External Interrupts and contexts on the other cores are either
 * spinning in a busy wait loop if they compete for the protected resource or they are
 * unaffected otherwise.\n
 *   The critical section is left with the counterpart function
 * mtx_osLeaveIntercoreCriticalSection().\n
 *   The operation is nestable. A context already being inside the critical section may
 * call this function again, however it'll end the critical section only after as many
 * invocations of mtx_osLeaveIntercoreCriticalSection() as invocations of this function.\n
 *   The operation is not nestable with respect to another critical section. A context
 * already being inside critical section A must not try entering critical section B, this
 * will normally cause a deadlock.\n
 *   @param pCritSec
 * The status of the critical section is kept in a critical section object. The one in use
 * is passed in by reference.
 *   @remark
 * The time between enter and leave needs to be very short because of the blocking of all
 * local contexts and competing contexts on other cores.
 *   @remark
 * The function is left with MSR[EE] = 0. The execution requires supervisor mode. Any
 * attempt to call it from a user mode context will cause a privileged exception.
 *   @remark
 * The function will in no wait keep track or supervise the correct pairing in use.
 * Operation will simply fail if this is not ensured.
 */
static inline void mtx_osEnterIntercoreCriticalSection
                                                (mtx_intercoreCriticalSection_t *pCritSec)
{
    uint32_t msr;

    /* Suspend all interrupts if not yet done by client code prior to invocation. */
    asm volatile ( /* AssemblerTemplate */
                   "mfmsr   %0\n\t"
                   "wrteei  0    /* Disable processing of External IRQs */\n\t"
                 : /* OutputOperands */ "=r" (msr)
                 : /* InputOperands */
                 : /* Clobbers */
                 );

    /* Check invocation counter to see if our core already owns the mutex. The counter is
       core-specific and therefore context-switch-safe due to the local interrupt
       inhibition. */
    const unsigned int idxCore = std_getCoreID();
    assert(idxCore <= STD_MAX_NO_CORES);
    if(pCritSec->cntInvocationAry[idxCore]++ == 0)
    {
        /* Calling core doesn't own the mutex, get it. The wait time is unpredictable. */
        mtx_acquireMutex(&pCritSec->mutex, /* wait */ true);

        /* Store MSR for later restoration of MSR[EE]. */
        pCritSec->msr = msr;
    }
    else
    {
        /* Calling core already owns the mutex, counter is incremented, no further action. */
    }

    /* Leave function with MSR[EE] = 0. */

} /* End of mtx_osEnterIntercoreCriticalSection */



/**
 * The function ends a core-to-core critical section shaped with the counterpart
 * mtx_osEnterIntercoreCriticalSection(). The status of External Interrupt handling on entry
 * into mtx_osEnterIntercoreCriticalSection() is restored - but only if this to the last
 * call in case of nested invocations.
 *   See mtx_osEnterIntercoreCriticalSection() for details.
 *   @param pCritSec
 * The status of the critical section is kept in a critical section object. The one, which
 * was used in the corresponding call of mtx_osEnterIntercoreCriticalSection() is passed in
 * by reference.
 *   @remark
 * The execution of the function requires supervisor mode. Any attempt to call it from a
 * user mode context will cause a privileged exception.
 *   @remark
 * The function will in no wait keep track or supervise the correct pairing in use.
 * Operation will simply fail if this is not ensured.
 */
static inline void mtx_osLeaveIntercoreCriticalSection
                                                (mtx_intercoreCriticalSection_t *pCritSec)
{
    const unsigned int idxCore = std_getCoreID();
    if(--pCritSec->cntInvocationAry[idxCore] == 0)
    {
        /* We really leave the critical section. Make the mutex available to other cores. */
        mtx_releaseMutex(&pCritSec->mutex);

        /* Restore the interrupt suspension state to how it used to be on first entry into
           mtx_osEnterIntercoreCriticalSection(). */
        asm volatile ( /* AssemblerTemplate */
                       "wrtee   %0   /* Restore MSR[EI] */\n\t"
                     : /* OutputOperands */
                     : /* InputOperands */ "r" (pCritSec->msr)
                     : /* Clobbers */
                     );
    }
    else
    {
        /* There at least one remaining nesting level. The critical section is not yet
           left, we still require the mutex. A DEBUG test aims at finding unproperly
           paired/placed calls of enter and leave. */
        assert((int16_t)pCritSec->cntInvocationAry[idxCore] >= 0);
    }
} /* End of mtx_osLeaveIntercoreCriticalSection */



/**
 * A nestable core-to-core mutex with invocation counter.\n
 *   If a resource is shared between cores and we use a normal mutex then we cannot apply
 * the busy-wait for the mutex if there is a chance that more than one execution contexts
 * on the requesting core compete for the mutex: competing contexts on one core are
 * typically priority scheduled and if context A executes busy-waiting for the mutex,
 * which context B currently owns, then it'll likely have the higher priority than B and B
 * is never scheduled again and we have dead lock.\n
 *   Unfortunately, this scenario is quite common. We can apply this more complex type of
 * mutex. It busy-waits if the mutex is currently owned by another core and will return
 * after an unpredictable while, when the mutex become free again. If the mutex is free or
 * already owned by the requesting core it'll return immediate.
 *   @param pMutex
 * The mutex object by reference.
 *   @remark
 * The execution of the function requires supervisor mode. Any attempt to call it from a
 * user mode context will cause a privileged exception.
 *   @remark
 *   The implementation of this mutex is involved with an unsolvable problem. The
 * acquisition of the mutex can be done while context switching (tasks, interrupts)
 * continues to happen normally on the local core or while context switching is
 * inhibited.\n
 *   In the former case a context switch can occur after getting the mutex and all other
 * cores need to busy-wait for the completion of (maybe even unrelated) contexts on the
 * mutex-owning core. If these contexts include true tasks then the delay will likely be
 * unacceptable.\n
 *   In the latter case the inhibit time on the local core for other (maybe unrelated)
 * contexts suffers from the unfair arbitration of the mutex. If two or more cores heavily
 * compete then one or two of them might in the worst case never get the mutex. This is by
 * principle, and insofar acceptable for the competing contexts, but unacceptable for other,
 * unrelated contexts.\n
 *   A sub-ordinated problem is that the implementation of inhibition of context switches
 * strongly depends on the operating system and no general implementation can be offered.\n
 *   Consequently, this function must not be considered a generally usable library
 * function. It needs to be applied with outermost care and will likely require changes
 * depending on the environment and the use case.\n
 *   The current implementation inhibits context switches during mutex acquisition. It uses
 * interrupt suspension for this purpose. Interrupt suspension is done with nesting. If
 * interrupts are suspended already on entry then they will stay so after exit and the code
 * between this function and its counterpart, mtx_osReleaseNestedMutex(), becomes a perfect
 * critical section between all contexts on all cores - however with the disadvantage of an
 * unpredictable maximum duration due to the unfair arbitration.
 */
static inline void mtx_osAcquireNestedMutex(mtx_nestedMutex_t *pMutex)
{
    uint32_t msr;

    /* Suspend all interrupts if not yet done by client code prior to invocation. */
    asm volatile ( /* AssemblerTemplate */
                   "mfmsr   %0\n\t"
                   "wrteei  0    /* Disable processing of External IRQs */\n\t"
                 : /* OutputOperands */ "=r" (msr)
                 : /* InputOperands */
                 : /* Clobbers */
                 );

    /* Check invocation counter to see if our core already owns the mutex. The counter is
       core-specific and therefore context-switch-safe due to the interrupt inhibition. */
    const unsigned int idxCore = std_getCoreID();
    assert(idxCore <= STD_MAX_NO_CORES);
    if(pMutex->cntInvocationAry[idxCore]++ == 0)
    {
        /* Calling core doesn't own the mutex, get it. The wait time is unpredictable. */
        mtx_acquireMutex(&pMutex->mutex, /* wait */ true);
    }
    else
    {
        /* Calling core already owns the mutex, counter is incremented, no further action. */
    }

    /* Restore the interrupt suspension state to how it used to be on entry. */
    asm volatile ( /* AssemblerTemplate */
                   "wrtee   %0   /* Restore MSR[EI] */\n\t"
                 : /* OutputOperands */
                 : /* InputOperands */ "r" (msr)
                 : /* Clobbers */
                 );
} /* End of mtx_osAcquireNestedMutex */


/// @todo Doc function
// * No test if mutex is really owned by the calling core!
// *   @remark
// * The execution of the function requires supervisor mode. Any attempt to call it from a
// * user mode context will cause a privileged exception.
static inline void mtx_osReleaseNestedMutex(mtx_nestedMutex_t *pMutex)
{
    uint32_t msr;

    /* Suspend all interrupts if not yet done by client code prior to invocation. */
    asm volatile ( /* AssemblerTemplate */
                   "mfmsr   %0\n\t"
                   "wrteei  0    /* Disable processing of External IRQs */\n\t"
                 : /* OutputOperands */ "=r" (msr)
                 : /* InputOperands */
                 : /* Clobbers */
                 );

    const unsigned int idxCore = std_getCoreID();
    if(--pMutex->cntInvocationAry[idxCore] == 0)
    {
        /* There's no context any more on the calling core which requires the mutex, release
           it. */
        mtx_releaseMutex(&pMutex->mutex);
    }
    else
    {
        /* At least one context on the calling core still requires the mutex, counter has
           been decremented, no further action. A DEBUG test aims at finding unproperly
           paired/placed calls of acquire and release. */
        assert((int16_t)pMutex->cntInvocationAry[idxCore] >= 0);
    }

    /* Restore the interrupt suspension state to how it used to be on entry. */
    asm volatile ( /* AssemblerTemplate */
                   "wrtee   %0   /* Restore MSR[EI] */\n\t"
                 : /* OutputOperands */
                 : /* InputOperands */ "r" (msr)
                 : /* Clobbers */
                 );
} /* End of mtx_osReleaseNestedMutex */

#endif  /* MTX_MUTEX_INCLUDED */
