#ifndef RTOS_RTOSEMULATION_INCLUDED
#define RTOS_RTOSEMULATION_INCLUDED
/**
 * @file rtos_rtosEmulation.h
 * Definition of global interface of module rtos_rtosEmulation.c
 *
 * Copyright (C) 2016 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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

#include <pthread.h>


/*
 * Defines
 */

/* The software is written as portable as reasonably possible. This requires the awareness
   of the C language standard it is compiled with. */
#if defined(__STDC_VERSION__)
# if (__STDC_VERSION__)/100 == 2011
#  define _STDC_VERSION_C11
# elif (__STDC_VERSION__)/100 == 1999
#  define _STDC_VERSION_C99
# endif
#endif


/*
 * Global type definitions
 */

/** The possible return values of a regularly invoked task function. */
typedef enum rtos_taskFctResult_t
{
    /** Normal operation, continue. */
    rtos_taskFctResult_continueScheduling,
    
    /** This is the last invokation of the task function. The thread, which times and
        triggers the task function will end. Scheduling continue for all remaining threads
        and their task functions. */
    rtos_taskFctResult_endOfThread,

    /** This is the last invokation of the task function. The thread, which times and
        triggers the task function will end. All other threads will receive a request to
        terminate, but scheduling continues until all threads have evaluated the signal.
        This means effectivly for a thread that it reaches its next due time and awakes. */
    rtos_taskFctResult_endOfScheduling

} rtos_taskFctResult_t;



/** The user made specification of a regularly invoked task. */
typedef struct rtos_threadSpecification_t
{
    /** The name of the thread (for diagnostic output). */
    const char *name;

    /** The regularly called task function. */
    rtos_taskFctResult_t (*fctTask)();

    /** The nominal cycle time of the thread. Function \a fctTask will be invoked every
        \a taskCycleTimeMs Milliseconds.\p
          Normally, the value is greater than zero. Although this will likely be a failure
        in a real application the emulation accepts a value of zero. Now, no real timing
        control is done, the task is cycling without delay. Each task with cycle time zero
        will consume all available computation time of an entire CPU core. This mode may
        sometimes be advantageous for testing purpose, to get the maximum throughput and the
        maximum number of task switches. Note, the printed task statistics must be doubted
        in this case. */
    unsigned int tiCycleMs;

} rtos_threadSpecification_t;



/*
 * Global data declarations
 */


/*
 * Global prototypes
 */

/** Initialize the module. */
void rtos_initModule();
 
/** Get the world time from the Windows high resolution timer. */
extern double rtos_getTime();

/** Run the scheduling process. */
extern bool rtos_runScheduler( unsigned int noThreads
                             , const rtos_threadSpecification_t threadSpecificationAry[]
                             , pthread_t threadAry[]
                             );

#endif  /* RTOS_RTOSEMULATION_INCLUDED */
