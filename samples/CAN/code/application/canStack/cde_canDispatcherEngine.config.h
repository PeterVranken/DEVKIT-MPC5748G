#ifndef CDE_CANDISPATCHERENGINE_CONFIG_INCLUDED
#define CDE_CANDISPATCHERENGINE_CONFIG_INCLUDED
/**
 * @file cde_canDispatcherEngine.config.h
 * The integration environment dependent, static configuration of the CAN interface.
 *
 * Copyright (C) 2015-2020 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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

#include <assert.h>



/* The software is written as portable as possible. This requires the awareness of the C
   language standard it is compiled with. */
#if defined(__STDC_VERSION__)
# if (__STDC_VERSION__)/100 == 2011
#  define _STDC_VERSION_C11
# elif (__STDC_VERSION__)/100 == 1999
#  define _STDC_VERSION_C99
# endif
#endif



/*
 * Configuration\n
 *   The defines and typedefs found in this section are the configuration of the CAN
 * interface for the integration into a specific platform.
 */

/*
 * The list of required include files as far as they are configuration: In most embedded
 * platforms the basic types are addressed to under names like uint8, sint16, int16_t, etc.
 *   The implementation of the CAN interface tries to avoid these types in order to benefit
 * from the C type concept, which leaves it open to the platform which widths are suitable
 * for the basic types. Particularly on small 8 or 16 systems this will save a significant
 * amount of expensive RAM.\n
 *   However, at the interface to the platform environment the use of such types is likely.
 * If a type definition is needed then you would place an according include statement
 * here.\n
 *   Moreover, down here there are references to the types of some operating system elements
 * like bus and frame handles. To resolve these references it's likely that you need to
 * include some related headers. The include statements should be placed here.
 */
#include "typ_types.h"


/** Many error conditions, which are static in the sense that they can only appear due to
    real errors in the implementation code (as opposed to errors caused by run-time data)
    are checked by assertions. This relates to the implementation of the engine itself, but
    - much more important - to the implementation of the integration code, mainly the event
    callbacks, too. Here, the most typical errors will be caught the first time the code is
    executed. This concept of static error checks makes it inevitable to have an assertion
    mechanism. Most platforms will offer an assertion. #CDE_ASSERT(boolean_t) needs to
    expand to the assertion on your platform. */
#define CDE_ASSERT(booleanInvariant)    assert(booleanInvariant)


/** The type of a frame handle. The handle is needed to distinguish all frames in the
    context of an engine. If the engine dispatches the frames of a single bus then it can
    be identical to the CAN ID but it can also be a linear index across all received frames
    or whatever. The choice of the handle should be made such that the use of a hash table
    can be avoided at runtime. It is assumed, that the CAN API of the underlying system
    uses some kind of handle for frames and this handle is simply passed through by the
    dispatcher engine.\n
      @todo Use the typedef to make our internally used \a cde_osHandleFrame_t identical to
    the operating system's given CAN frame handle or identifier type. */
typedef unsigned int cde_osHandleFrame_t;


/** The memory allocation mechanism depends on the alignment of machine words.
      @todo Specify the alignment, which suits to all basic machine words, e.g. 4 for most
    32 Bit architectures. The define needs to expand to a integer literal, which designates
    a power of two, mostly one out of 1, 2 or 4. */
#define CDE_COMMON_MACHINE_ALIGNMENT 4u


/** The thread-safe implementation of the dispatcher queue builds on atomic read and write
    on a numeric type. Basically any atomic unsigned integer available on the target
    platform can be typedef'ed here; however, the maximum length of the queue is given by
    the range of this type - thus don't use a too short integer type if you have the
    choice. unsigned int will be approriate on most 32 and 16 Bit platforms and unsigned
    char on a typical 8 Bit platform. */
typedef unsigned int cde_atomicUnsignedInt_t;


/** The thread-safe implementation of the dispatcher queue builds on defined memory
    ordering; machine operations are expected to happen in the order of C code statements.
    This is not easy to achieve in C as the language semantics doesn't have awareness of
    concurrency (before C11). The solution will always be target and compiler dependent.
    Here, we offer a macro, which is meant to implement a full memory barrier on the
    target.\n
      Fortunately, when using GCC there is a platform independent solution. See
    http://gcc.gnu.org/onlinedocs/gcc-4.4.3/gcc/Atomic-Builtins.html for details. */
#ifdef _STDC_VERSION_C11
# define CDE_MEMORY_BARRIER_FULL() {atomic_thread_fence(memory_order_seq_cst);}
#elif __GNUC__
# define CDE_MEMORY_BARRIER_FULL() __sync_synchronize()
#else  
# error Macro CDE_MEMORY_BARRIER_FULL() needs to be defined for your target
#endif


/** Some few pieces of code require mutual exclusion of the APSW tasks and the interrupts
    or event callbacks, which are involved in the CAN handling. Which mechanisms to apply
    is fully platform dependent. There might be a mutex mechanism, a \a Get/ReleaseResource
    function pair, a function pair like Suspend/ReleaseAllInterrupts or what else.
    Configure the next define such that mutual exclusion is turned on.\n
      It is not necessary, that the implementation supports nested pairs of enter/leave
    critical section.\n
      The implementation requires mutual exclusion only for heap operations; all
    dispatchers (which are typically running in different task contexts) share the same
    heap. After system initialization, when race conditions begin to matter, the only
    client of heap operations is the timer creation API, cde_createPeriodicTimer() and
    cde_createSingleShotTimer(). Timer objects are never returned to the heap after use
    but recycled through thread-local pools. Therefore, the number of heap operations is
    low, has a known upper bounds and they typically take place in the first cycles of
    operation. This makes the expense of acquiring a lock a minor aspect of the
    implementation. Even a busy-waiting spin-lock can be adequate.\n
      However, to optimally benefit from the concept of static, deterministic memory
    allocation it's anyway recommended not to use the timer creation API outside the
    interface initialization. The initialization is done in a single-threaded context, free
    of race conditions. Therefore, if the recommendation is obeyed then the critical
    section macro may expand to nothing. */
#define cde_enterCriticalSection()

/** Some few pieces of code require mutual exclusion of the APSW tasks and the interrupts,
    which are involved in the CAN handling. Which mechanisms to apply is fully platform
    dependent. There might be a mutex mechanism, a \a Get/ReleaseResource function pair, a
    function pair like Suspend/ReleaseAllInterrupts or what else. Configure the next define
    such that mutual exclusion is turned off.\n
      If the timer creation API is not used after the interface initialization then this
    macro should expand to nothing as it is by default. See #cde_enterCriticalSection for a
    more in depths consideration. */
#define cde_leaveCriticalSection()

/** Tailoring of the API: The query function for the index of the bus (the index serves as
    the handle of buses), is not always required and can be switched off at compile time.
    This will safe \a sizeof(unsigned int) Byte per registered frame.\n
      The define is set to either 1 or 0. */
#define CDE_ENABLE_API_GET_INDEX_BUS            ((DEBUG)==1)

/** Tailoring of the API: The query function for the OS frame handle,
    cde_getOsHandleFrame(), is not always required and can be switched off at compile time.
    This will safe \a sizeof(cde_osHandleFrame_t) Byte per registered frame.\n
      The define is set to either 1 or 0. */
#define CDE_ENABLE_API_GET_OS_HANDLE_FRAME      0

/** Tailoring of the API: The query function for the transmission direction, \a
    cde_isInboundTransmission, is not always required and can be switched off at compile
    time. This will safe \a sizeof(boolean_t) Byte per registered frame.\n
      The define is set to either 1 or 0. */
#define CDE_ENABLE_API_IS_INBOUND_TRANSMISSION  ((DEBUG)==1)

/** Tailoring of the API: The timer context data is not always required and can be switched
    off at compile time. This will safe \a sizeof(void*) Byte per created timer. An
    alternative to applying user provided data can be quering the timer handle to identify
    it, please refer to cde_getHandleTimer().\n
      The define is set to either 1 or 0. */
#define CDE_ENABLE_TIMER_CONTEXT_DATA           1

#endif  /* CDE_CANDISPATCHERENGINE_CONFIG_INCLUDED */
