/**
 * @file rtos_rtosEmulation.c
 * Simple emulation of an RTOS.\n
 *   This is a function free, simple emulation of the scheduler of an RTOS, which can be
 * used as testing platform for RTOS developments. The emulation only provides the service
 * of regular tasks. (Event tasks are easy to add, but a common reusable pattern is hard to
 * anticipate.) The major difference to an RTOS is that priorities of the threads are
 * undefined. Any inter-thread communication, which bases on asymmetric priorities in a
 * strictly priority based scheduler, will fail to run in this emulation. This applies to
 * many lock-free techniques like double-buffering under control of Boolean flags, which
 * are commonly used by model based auto-coding.\n
 *   The OS emulation has the following properties: Any number of threads can be started
 * with individual task function and cycle time. A timing statistics is computed for all
 * tasks and regularly printed by the main thread. The application cycles infinitely until
 * a task function returns the demand to terminate.\n
 *   The implementation is POSIX based and basically portable; a C11 compiler is required.
 * The timing statistics uses a high resolution timer, when compiled under Windows and the
 * results are accurate. Other systems use the POSIX timer service, which has the
 * granularity of the operating system scheduler and the results are somewhat worse.
 *
 * Copyright (C) 2016-2017 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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
 *   rtos_initModule
 *   rtos_getTime
 *   rtos_runScheduler
 * Local functions
 *   getTime
 *   triggerMainThread
 *   thread
 *   taskTimer
 *   printTaskTiming
 */

/*
 * Include files
 */

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdatomic.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <math.h>
#ifdef __WINNT__
# include <Windows.h>
#endif
#include <pthread.h>
#include <assert.h>

#include "sup_startup.h"
#include "rtos_rtosEmulation.h"



/*
 * Defines
 */

/** The cycle time in which the task timing statistics is printed to the console. THe unit
    is ms. For reasonable output, the chosen value needs to be significantly larger than
    the cycle time of the slowest user task.\n
      A value of zero will disable the console output at all. (But not the internal data
    acquisition.) */
#define CYCLE_TIME_TASK_STATISTICS_MS   10000

/** Development support: The basically infinite run of the application can be limited to a
    number of cycles. During development it may be useful to set this value to about 10.
    The unit in the time domain is in the range from 200ms to 2s, depending on the value of
    the other macro #CYCLE_TIME_TASK_STATISTICS_MS.\n
      After development, it should be set back to zero, which disables the stop condition. */
#define TEST_NO_CYCLES_TO_RUN   0

/* There are subtle differences in the interface to pthreads between the different releases
   of GCC. We support different revisions by some conditional defines. */
#if __GNUC__ == 4  &&  __GNUC_MINOR__ == 8  &&  __GNUC_PATCHLEVEL__ == 1  && __MINGW64__ == 1
# define _GNUC_I686_4_8_1_MINGW64_
#elif __GNUC__ == 8  &&  __GNUC_MINOR__ == 1  &&  __GNUC_PATCHLEVEL__ == 0  && __MINGW32__ == 1
# define _GNUC_I686_8_1_0_MINGW32_
#endif

#if ATOMIC_INT_LOCK_FREE != 2
# error Require lock free, thread safe access to variables of type int and shorter
#endif


/*
 * Local type definitions
 */

/** Some statistics data about thread timing accuracy. */
typedef struct threadTiming_t
{
    /** The number of summed values. */
    unsigned int noSamples;

    /** We mainly look at the sequence of distances in time of two neighboured task
        triggers. This is the sum of the values since last reset. */
    double sumOfDeltaTimes;

    /** We mainly look at the sequence of distances in time of two neighboured task
        triggers. This is the sum of the squared values since last reset. */
    double sumOfSquaredDeltaTimes;

    /** The number of resynchronizations of the local thread timers with the global system
        clock. This is the never reset total number since start of application. */
    unsigned long totalNoResync;

} threadTiming_t;


/** The parameter data structure for a new thread. */
typedef struct threadData_t
{
    /** The name of the thread, needed for feedback. */
    const char *name;

    /** The thread is designed as a regularly executed task function. Here is the nominal
        cycle time in ms. The value is in the range >1 ms. */
    unsigned int tiCycleMs;

    /** The thread is designed as a regularly executed task function. Here is the task
        function. The thread terminates if it returns false. */
    rtos_taskFctResult_t (*fctTask)();

    /* Command to terminate the thread, normally false. Note, no atomic flag is required
       here, because the thread is only reading the flag and the main thread is the only
       writer. */
    volatile bool terminate;

    /** Some statistics data about thread timing accuracy. It is modeled atomic so that it
        can be printed regularly in the main thread. */
    _Atomic volatile threadTiming_t threadTiming;

    /** A command to reset the accumulation of thread timing data. Restart accumation with
        zero samples if found to be true.
          Note, the asymmetric definition of test, set and clear operations on atomic
        Booleans forces the use of the Boolean value false as a signal. It is therefore not
        possible to implement a reset signal; we can only implement the "do not reset" - or
        continue with other words. This is no functional limitation but counterintuitive. */
    volatile atomic_flag continueThreadTiming;

    /** The pthreads thread object. No race conditions here, this field is only written and
        read by the coordinating main thread. */
    pthread_t thread;

} threadData_t;


/*
 * Local prototypes
 */


/*
 * Data definitions
 */

/** This is the event, which is sent regularly to the main thread in order to time its
    output. It is posted by the fastest cyclic task. */
static pthread_cond_t _evTimer = PTHREAD_COND_INITIALIZER;

/** This is a Boolean signal, which is sent to the main thread when a task function had
    requested the end of scheduling. Note, no atomic flag is required here, because no
    read-modify-write is required. */
static volatile bool _endOfScheduling = false;


/*
 * Function implementation
 */

/**
 * Get the current system time in a format, which is compatible with the POSIX pthreads
 * interface.
 *   @param pTi
 * The current time is returned by reference in * \a pTi.
 *   @return
 * The function doesn't report the success. The implementation depends on the compiler
 * version and some implementation can hypothetically report a problem. These problems are
 * caught by assertion only.
 */

static inline void getTime(struct timespec *pTi)
{
    /* The query function for the absolute time needed by the pthreads methods is
       clock_gettime; unfortunately do several Windows ports of GCC not implement this
       function. For these versions, there is a specific Windows funtion as substitute.
         Another idea is the use of the standard C function time() but it must be used with
       awareness of the little resolution of 1s only. */
#if defined(_GNUC_I686_4_8_1_MINGW64_)  ||  defined(_GNUC_I686_8_1_0_MINGW32_)
    int rc ATTRIB_DBG_ONLY;
    rc = clock_gettime(CLOCK_REALTIME, pTi);
    assert(rc == 0);
#elif 0
    /* This can be used with the TDM port of GCC but seems to work wth the mingw64 ports of
       GCC, too. */
    const unsigned long long tiInMs = _pthread_time_in_ms();
    pTi->tv_sec = tiInMs / 1000ull;
    pTi->tv_nsec = (long)(tiInMs - 1000ull*pTi->tv_sec) * 1000000l;
#elif 0
    // Extract from pthread.h:
    //  /* Returns the first parameter "abstime" modified to represent the current
    //   * system time. If "relative" is not NULL it represents an interval to add to
    //   * "abstime".
    //   */
    //  __PTW32_DECLSPEC struct timespec *pthread_win32_getabstime_np
    //                                      ( struct timespec *, const struct timespec *);
    pthread_win32_getabstime_np(pTi, NULL);

    // At https://docs.oracle.com/cd/E19455-01/806-5257/6je9h032r/index.html, Nov 14, 2016,
    // we find the use of the C lib function time() as time reference. This has a
    // resolution of seconds, which means a [0..1)s gap once at the beginning of
    // processing:
    //
    //   pthread_timestruc_t to;
    //   pthread_mutex_t m;
    //   pthread_cond_t c;
    //   ...
    //   pthread_mutex_lock(&m);
    //   to.tv_sec = time(NULL) + TIMEOUT;
    //   to.tv_nsec = 0;
    //   while (cond == FALSE) {
    //       err = pthread_cond_timedwait(&c, &m, &to);
    //       if (err == ETIMEDOUT) {
    //           /* timeout, do something */
    //           break;
    //       }
    //   }
    //   pthread_mutex_unlock(&m);
#else
# error Select the right code to initialize the time in the format of the pthread library
#endif
} /* End of getTime */



/**
 * Send a clock tick to the main thread. It'll then do one cycle, will likely print the
 * thread statistics and check for an application termination request by a thread.
 */
static void triggerMainThread()
{
    pthread_cond_signal(&_evTimer);
    
} /* End of triggerMainThread */



/**
 * The operating system emulation consists of a number of regularly executed threads. The
 * basic pattern of such a thread is implemented in this function.
 *   @return
 * NULL
 *   @param pData
 * The parameter data of the thread is passed in as a void pointer. Main elements of the
 * parameter data are cycle time and task function.
 */

static void *thread(void *pThreadParamData)
{
    threadData_t * const pThreadParam = (threadData_t*)pThreadParamData;

    /* The nominal task cycle time is given in ms. The time format requires a split in
       seconds and the fraction of a second in nano seconds. */
    time_t tiCycleS = (time_t)(pThreadParam->tiCycleMs / 1000);
    signed long tiCycleNs = (long)(pThreadParam->tiCycleMs - tiCycleS*1000);
    assert(tiCycleNs >= 0  &&  tiCycleNs < 1000);
    tiCycleNs *= 1000000;

    /* The task function must not be empty. */
    rtos_taskFctResult_t (* const fctTask)() = pThreadParam->fctTask;
    assert(fctTask != NULL);

    /* We will apply pthread_cond_timedwait for scheduling the regular task function. This
       method expects an absolute time designation. We request "now" as starting point of
       the series of scheduled times. */
    struct timespec tiDue;
    getTime(&tiDue);

    /* Adjustments of the system clock (we use world times) lead to a missynchronization
       with the locally incremented due time. We check occasionally under control of a
       counter for this misssynchronization. How often, is set here. */
    #define RESYNC_CHECK_INTERVAL_MS    5000 /* ms */
    const unsigned cntResyncMax = pThreadParam->tiCycleMs > 0
                                  ? (RESYNC_CHECK_INTERVAL_MS+pThreadParam->tiCycleMs-1)
                                    / pThreadParam->tiCycleMs
                                  : 1000000;
    assert(cntResyncMax > 0);
    unsigned int cntResync = cntResyncMax;
    #undef RESYNC_CHECK_INTERVAL_MS

    /* The task timing supervision uses a clock independent from the pthreads clocking. We
       benefit from the Windows high resolution counter.
         The flow of the statistic data is uni-directional from here to the main thread.
       Therefore, we can implement the data source as a local thread object, update this
       local object and copy it atomically into the shared memory with the main thread. The
       local object is initialized once from the shared object. */
    double tiLastTaskTrigger = rtos_getTime();
    threadTiming_t threadTiming = atomic_load(&pThreadParam->threadTiming);

    /* Aquire the mutex, which is required to operate the pthread_cond_timedwait inside the
       loop. */
    pthread_cond_t condition = PTHREAD_COND_INITIALIZER;
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
    int rc ATTRIB_DBG_ONLY = pthread_mutex_lock(&mutex);
    assert(rc == 0);

    /* Run the task function and schedule the next invokation as long as it returns true. */
    rtos_taskFctResult_t taskFctRes = rtos_taskFctResult_endOfScheduling;
    while(!pThreadParam->terminate
          &&  (taskFctRes=fctTask()) == rtos_taskFctResult_continueScheduling
         )
    {
        /* Compute target time for task suspend command by incrementing the last
           recent target time by the nominal task cycle time. Consider the two-word
           representation of the time. We need to implement the carry operation.
             An overflow of the time designation is out of scope of this software; it is
           more than twenty years ahead. */
        tiDue.tv_sec += tiCycleS;
        if((tiDue.tv_nsec+=tiCycleNs) >= 1000000000l)
        {
            tiDue.tv_nsec -= 1000000000l;
            tiDue.tv_sec  += 1;
        }
        assert(tiDue.tv_nsec >= 0  &&  tiDue.tv_nsec < 1000000000l);

        /* We don't use a Boolean condition here and just want to react on the
           timeout.
             After return from wait is the mutex still locked, which is fine for the next
           cycle. */
        rc = pthread_cond_timedwait(&condition, &mutex, &tiDue);
#ifdef _GNUC_I686_4_8_1_MINGW64_
        /* A system signal would make this assertion fire. */
        assert(rc == ETIMEDOUT);
#endif
        /* This is the awake point for the next cycle; take the time for the timing
           statistics. There's a race condition: The measurement statement can be delayed
           by preemption by another task. This is not a real problem; such a preemption
           effectively moves the begin of the real thread activities and it is logically
           not a fault to display this shift a thread timing inaccuracy - even if doesn't
           come from the pthreads library implementation. */
        const double now = rtos_getTime();

        /* Occasionally take the pthreads time for resychronization. Resychronization may
           become necessary because of permanent task overload or because of adjustments of
           the sytem clock (e.g. after a Windows Sleep or Hibernate). */
        bool resyncDone = false;
        if(--cntResync == 0)
        {
            struct timespec tiNow;
            getTime(&tiNow);

            /* tiNow should be "identical" to tiDue. If it deviates significantly we
               assign the current value to the locally updated one. The deviation is taken
               such that highly accurate operation considering the nano seconds are not
               required. The effectivly possible deviation without triggering a
               resynchronization is in the range (-MAX_DEVIATION_S-1, MAX_DEVIATION_S+1)
               seconds. */
            const time_t tiDelta = tiDue.tv_sec - tiNow.tv_sec;
            #define MAX_DEVIATION_S     1 /* Unit s */
            _Static_assert(MAX_DEVIATION_S > 0, "Bad specification of time deviation");
            if(abs(tiDelta) > MAX_DEVIATION_S)
            {
                tiDue = tiNow;
                resyncDone = true;
            }
            #undef MAX_DEVIATION_S

            /* Reload the counter. */
            cntResync = cntResyncMax;
        }

        /* Update the task timing data. Modify the local copy and store it atomically in
           the shared memory.*/
        const double tiDelta = now - tiLastTaskTrigger;
        if(!atomic_flag_test_and_set(&pThreadParam->continueThreadTiming))
        {
            threadTiming.noSamples = 0;
            threadTiming.sumOfDeltaTimes = 0.0;
            threadTiming.sumOfSquaredDeltaTimes = 0.0;
        }
        ++ threadTiming.noSamples;
        threadTiming.sumOfDeltaTimes += tiDelta;
        threadTiming.sumOfSquaredDeltaTimes += tiDelta*tiDelta;
        if(resyncDone)
            ++ threadTiming.totalNoResync;
        atomic_store(&pThreadParam->threadTiming, threadTiming);

        tiLastTaskTrigger = now;

    } /* End while(Regularly call task function) */

    pthread_mutex_unlock(&mutex);
    pthread_mutex_destroy(&mutex);

    /* If the task requested the end of scheduling then signal this to the parent thread.
         CAUTION: While the signalling though the volatile boolean is safe is the attempt
       to make the signalling immediately happen unsafe. Mostly, it'll work as expected:
       the main thread will wait for its next timer tick, triggerMainThread() will deliver
       this tick and the main thread will do the rest of the communication to stop the
       other threads as soon as possible. In rare case however it'll be in the middle of
       its normal timer tick doing and not receive this signal. Two considerations:
         The chance of this really happening is extremly little because the distance in
       execution time between testing the flag and entering the wait-for-signal command is
       very small.
         If it happens it cannot be considered a fault. We didn't make a specification or
       promise how soon the termination of the other tasks will happen and there is only
       the danger of delaying it by one regular timer tick. In general and even if this
       special situation doesn't happen, the reaction time depends on the particular task
       cycle times.
         Summarizing, we accept this effect and don't consider it a bug. */
    _endOfScheduling = true;
    triggerMainThread();
    
    return NULL;

} /* End of thread */



/**
 * Task function, which is regularly executed. Used as a timer for the main thread: It
 * sends an event in every invokation.
 *   @return
 * \a rtos_taskFctResult_continueScheduling until the termination condition of the
 * application is reached. Then it returns once \a
 * rtos_taskFctResult_continueScheduling_endOfScheduling.
 */

static rtos_taskFctResult_t taskTimer()
{
    triggerMainThread();

    static unsigned long cntCalls = 0;
    ++ cntCalls;

    return cntCalls <= ((unsigned long)TEST_NO_CYCLES_TO_RUN-1)
           ? rtos_taskFctResult_continueScheduling
           : rtos_taskFctResult_endOfScheduling;

} /* End of taskTimer */



#if CYCLE_TIME_TASK_STATISTICS_MS > 0
/**
 * Display task timing statistics and command a reset of the data, i.e. a new observation
 * time window shall begin.
 *   @param threadDataAry
 * The array of all thread data, not only timing related.
 *   @param noThreads
 * The number of entries in the array \a threadDataAry.
 */

static void printTaskTiming(threadData_t threadDataAry[], unsigned int noThreads)
{
    if(log_checkLogLevel(sup_hGlobalLogger, log_info))
    {
        /** The required buffer size is an estimation only; this is why we add a reserve of
            500 characters. Despite of the field sizes in the fomatting string can due to
            longer input the actual output always be much larger. This requires a safe
            usage of snprintf in order to avoid a buffer overflow. (Truncation of output is
            however unavoidable in this situation.) */
#define SEP_LINE "-------------------------------------------------------------------\n"
#define BUF_SIZE (sizeof(SEP_LINE)*(3+noThreads)+500)
#define _printf(format, ...)                                                                \
            if(sizeRemain > 0)                                                              \
            {                                                                               \
                /* Caution, here we use a GCC extension, the ##. Without it the ellipsis */ \
                /* cannot expand to the empty list of arguments - which we need for the */  \
                /* separator lines. */                                                      \
                signed int rc = snprintf(pWr, sizeRemain, format, ## __VA_ARGS__);          \
                if(rc >= 0  &&  (size_t)rc <= sizeRemain)                                   \
                {                                                                           \
                    pWr += rc;                                                              \
                    sizeRemain -= rc;                                                       \
                }                                                                           \
                else                                                                        \
                    sizeRemain = 0;                                                         \
            }
        
        char msgBuf[BUF_SIZE]
           , *pWr = &msgBuf[0];
        size_t sizeRemain = BUF_SIZE;

        _printf("%s: Task timing data:\n", __func__);
        _printf("-------------------------------------------------------------------\n");
        _printf( "|%-22s|%-6s|%-9s|%-8s|%-7s|%-8s|\n"
               , "Name"
               , "#"
               , "mean [ms]"
               , "std [ms]"
#if defined(__GNUC__) && __GNUC__ == 8  &&  __GNUC_MINOR__ == 1  &&  __GNUC_PATCHLEVEL__ == 0
                 /* Usually, an embedded string argument is not recursively checked for
                    formatting characters and a contained % doesn't required quoting
                    in order to be printed literally. However, this is required by the
                    MinGW64 port of GCC - and not even for all revisions. */
               , "std [%%]"
#else
               , "std [%]" /* This should be correct C behavior. */
#endif
               , "# resync"
               );
        unsigned int u;
        for(u=0; u<noThreads; ++u)
        {
            /* Make a thread safe copy of the current data. */
            const threadTiming_t taskTiming = atomic_load(&threadDataAry[u].threadTiming);

            /* Demand deletion of the read data. Here we have a negligible race condition: Data
               collected between the atomic load and the completion of this statement is lost,
               it's not in any displayed statistics. */
            atomic_flag_clear(&threadDataAry[u].continueThreadTiming);

            double noSamples = taskTiming.noSamples;
            if(noSamples <= 0.0)
                noSamples = 1.0;

            const double mean = taskTiming.sumOfDeltaTimes/noSamples;

            double std = taskTiming.sumOfSquaredDeltaTimes/noSamples - mean*mean;
            /* std should theoretically never be negative. Due to rounding effects this can
               however happen and sqrt would return a NaN. */
            if(std > 0.0)
                std = sqrt(std);
            else
                std = 0.0;

            double stdRelPerc = 100.0 * std;
            if(mean != 0.0)
                stdRelPerc /= mean;
            else
                stdRelPerc = std==0.0? 0.0: 100.0;

            _printf( "|%-22s|%-6u|%-9.1f|%-8.3f|%-7.3f|%-8lu|\n"
                   , threadDataAry[u].name
                   , taskTiming.noSamples
                   , mean * 1000.0
                   , std * 1000.0
                   , stdRelPerc
                   , taskTiming.totalNoResync
                   );

        } /* for(All threads) */

        _printf("-------------------------------------------------------------------\n");

        log_log(sup_hGlobalLogger, log_info, msgBuf);

#undef SEP_LINE
#undef BUF_SIZE
#undef _printf
    }
} /* End of printTaskTiming */
#endif



/**
 * Initialize the module. This function must be called prior to the start of the schulder
 * (rtos_runScheduler), thus in a race condition free, single-threaded context.
 */

void rtos_initModule()
{
    /* Reset the time to zero. */
    rtos_getTime();

} /* End of rtos_initModule */



/**
 * Get the world time from the Windows high resolution timer, which is elapsed since the
 * first call after the start of the application.
 *   @return
 * The time in s since the very first invocation of this function.
 *   @remark
 * Normally this function is reentrant and thread-safe. Only the very first invocation,
 * which defines the time=zero starting point is not reentrant and must be completed in a
 * race condition free environment.
 *   @remark
 * The implementation invokes the Windows high resolution timer. On non Windows systems the
 * local function getTime() is called instead. By experience, this has a much worse
 * resolution, which is likely the same as the time quantum of the operating system.
 */

double rtos_getTime()
{
    static bool bFirstTime_ = true;
    static double ti0_ = 0.0;
#ifdef __WINNT__
    static double dFrequency_ = 1.0;
#endif

    if(bFirstTime_)
    {
        bFirstTime_ = false;
#ifdef __WINNT__
        LARGE_INTEGER llFrequency;
        QueryPerformanceFrequency(&llFrequency);
        dFrequency_ = (double)llFrequency.QuadPart;
#endif
        ti0_ = rtos_getTime();
    }
#ifdef __WINNT__
    LARGE_INTEGER llTime;
    QueryPerformanceCounter(&llTime);
    return (double)llTime.QuadPart/dFrequency_ - ti0_;
#else
    struct timespec now;
    getTime(&now);
    return ((double)now.tv_sec + (double)now.tv_nsec*1e-9) - ti0_;
#endif
} /* End of rtos_getTime */



/**
 * The scheduling process is run. All specified threads begin to cycle and call their task
 * functions regularly at individual rates.\n
 *   The functions returns onyl after end of scheduling, when all threads have terminated.
 * The end of scheduling can be requested by any of the task functions by return value, see
 * rtos_taskFctResult_t. However, after returning rtos_taskFctResult_endOfScheduling
 * scheduling continues until all other threads reacted on the termination request, too.
 * This will normally happen at their next due time.
 *   @return
 * \a true if all threads could be started. If the start of at least one thread fails
 * (error condition of pthreads library) then scheduling is not started and the function
 * immediately returns \a false.
 *   @param noThreads
 * The number of tasks specified in \a threadSpecificationAry.
 *   @param threadSpecificationAry
 * A array or list of specifications of threads to be scheduled. Mainly a task function and
 * a cycle time.
 *   @param threadAry
 * A caller provided array of thread handles or NULL if not required. The function will
 * create a dedicated thread for each of the specified reagular tasks. The threads are
 * implemented as POSIX thread using the pthreads library. If the caller wants to deal with
 * the API exposed by this libary he might require the handles of the created threads. If
 * this parameter is not NULL the \a noThreads handles of the create threads are written
 * into this array. The task functions can read from this array to find their handle.\n
 *   There's a one-by-one relation ship between the elements in this array and in \a
 * threadSpecificationAry. The n-th specified thread will find its handle as n-th element
 * of \a threadAry.\n
 *   Note, it is not possible to safely provide the handle of thread n to another thread
 * m<n, which is created earlier than n. In the short time span when m is already created
 * but n is not yet, is the entry of thread n invalid. There's no possibility to give an
 * upper time bounds how long this phase endures. If it is essential that a thread can
 * access the handles of others with greater index then some explicit synchronization code
 * will be required between these threads at startup.
 */

bool rtos_runScheduler( unsigned int noThreads
                      , const rtos_threadSpecification_t threadSpecificationAry[]
                      , pthread_t threadAry[]
                      )
{
#ifdef __WINNT__
    /* Windows: The task scheduler normally uses a clock tick of about 15ms. There's
       however an OS call to lower this value. We can achieve a much better timing accuracy
       by setting the value to 1ms.
         Caution: This impact Windows behavior globally! All applications get the new
       timing. */
    const UINT tiOsTick = 1;
    MMRESULT mmRes = timeBeginPeriod(/* uPeriodMs */ tiOsTick);
    LOG_WARN( sup_hGlobalLogger
            , "%s: Windows time quantum set to %u ms%s"
            , __func__
            , (unsigned)tiOsTick
            , mmRes == TIMERR_NOERROR? "": " failed"
            );
#endif

    /* Fill the internal thread list with the user specified data. */
    threadData_t threadDataAry[noThreads+1];
    unsigned int u;
    for(u=0; u<noThreads; ++u)
    {
        /* Note, .continueThreadTiming = ATOMIC_INIT_FLAG (=false) effectively lets the
           process start with a reset command of the timing data gathering. */
        threadDataAry[u] = (threadData_t){ .name = threadSpecificationAry[u].name
                                         , .tiCycleMs = threadSpecificationAry[u].tiCycleMs
                                         , .fctTask = threadSpecificationAry[u].fctTask
                                         , .terminate = false
                                         , .continueThreadTiming = ATOMIC_FLAG_INIT
                                         , .threadTiming =
                                           { .noSamples = 0
                                           , .sumOfDeltaTimes = 0.0
                                           , .sumOfSquaredDeltaTimes = 0.0
                                           }
                                         };
    }

    /* An additional task to start is used as a timer for this main thread. It simply sends
       an event in every cycle. This event is used to trigger the output of the task timing
       data.
         If the value is very large then we let the task cycle more often in order to
       maintain the responsiveness of the application (e.g. termination). */
#define MAX_USER_TI_CYCLE_TIMER_TASK    2000 /* ms */
#define MAX_TI_CYCLE_TIMER_TASK         1000 /* ms */
#define MIN_TI_CYCLE_TIMER_TASK         200  /* ms */
    unsigned int tiCycleTimerTask = CYCLE_TIME_TASK_STATISTICS_MS;
    if(tiCycleTimerTask > MAX_USER_TI_CYCLE_TIMER_TASK)
        tiCycleTimerTask = MAX_TI_CYCLE_TIMER_TASK;
    else if(tiCycleTimerTask < MIN_TI_CYCLE_TIMER_TASK)
        tiCycleTimerTask = MIN_TI_CYCLE_TIMER_TASK;
#undef MAX_USER_TI_CYCLE_TIMER_TASK
#undef MAX_TI_CYCLE_TIMER_TASK

    threadDataAry[u] = (threadData_t){ .name = "timerTask"
                                     , .tiCycleMs = tiCycleTimerTask
                                     , .fctTask = taskTimer
                                     , .terminate = false
                                     , .continueThreadTiming = ATOMIC_FLAG_INIT
                                     , .threadTiming =
                                       { .noSamples = 0
                                       , .sumOfDeltaTimes = 0.0
                                       , .sumOfSquaredDeltaTimes = 0.0
                                       }
                                     };

    /* Start all threads including the internally defined. */
    assert(u == noThreads);
    _endOfScheduling = false;
    for(u=0; u<noThreads+1; ++u)
    {
        LOG_DEBUG( sup_hGlobalLogger
                 ,  "%s: Creating thread %u with cycle time %u ms"
                 , __func__
                 , u
                 , threadDataAry[u].tiCycleMs
                 );
        fflush(stdout);
        
        /* To avoid race-conditions it is essential to place the user provided array
           threadAry in the pthreads library call. But if it is NULL or if the loop
           reached the internally defined thread this array can't be used. This makes
           the following code a bit clumsy. */
        pthread_t * pThread
                , tmpThread;
        if(threadAry &&  u < noThreads)
            pThread = &threadAry[u]; 
        else
            pThread = &tmpThread;
        int rc = pthread_create(pThread, NULL, &thread, (void*)&threadDataAry[u]);
        threadDataAry[u].thread = *pThread;
        
        if(rc)
        {
            LOG_ERROR( sup_hGlobalLogger
                     , "%s: Can't create thread, return code from pthread_create() is %d"
                     , __func__
                     , rc
                     );
            fflush(stdout);
            break;
        }
    }

    const unsigned int noRunningThreads = u;
    if(noRunningThreads == noThreads+1)
    {
        /* Enter a (nearly infinite) loop, which is timed by the slowest of the regular tasks:
           The statistic task data is printed in every tic. */
#if CYCLE_TIME_TASK_STATISTICS_MS > 0
        unsigned long cntTimerTask = 0
                    , cntDisplayCycles = 0;
        unsigned int tiTimerTask = 0;
        const unsigned int tiDisplay = CYCLE_TIME_TASK_STATISTICS_MS >= MIN_TI_CYCLE_TIMER_TASK
                                       ? CYCLE_TIME_TASK_STATISTICS_MS
                                       : MIN_TI_CYCLE_TIMER_TASK;
#endif
#undef MIN_TI_CYCLE_TIMER_TASK

        /* We need the uprounded cycle time of the timer task in s for the timeout value. */
        const unsigned int tiCycleTimerTaskInS = (tiCycleTimerTask + 999)/1000;
        assert(tiCycleTimerTaskInS >= 1);

        pthread_mutex_t mutexDummy = PTHREAD_MUTEX_INITIALIZER;
        pthread_mutex_lock(&mutexDummy);
        while(!_endOfScheduling)
        {
            /* Race condition: When the end of scheduling is signalled by a thread while
               the timer task is supended, then it won't become awake again and won't send
               the event. Here, we would wait forever. We need a timeout.
                 The named return value ETIMEDOUT to indicate a timeout seems to be not
               supported by GCC 5.3.0. Normally, the function will return zero. The condition
               !=0 can replace the comparison with the missing named values. */
            struct timespec tiMax;
            getTime(&tiMax);
            tiMax.tv_sec += tiCycleTimerTaskInS+1;
            pthread_cond_timedwait(&_evTimer, &mutexDummy, &tiMax);

#if CYCLE_TIME_TASK_STATISTICS_MS > 0
            ++ cntTimerTask;
            if(tiTimerTask >= tiDisplay)
            {
                ++ cntDisplayCycles;
                LOG_DEBUG( sup_hGlobalLogger
                         , "%s: Cycle %lu (%.1f h)"
                         , __func__
                         , cntDisplayCycles
                         , (double)cntTimerTask * (double)tiCycleTimerTask / (1000.0*3600.0)
                         );
                fflush(stdout);
                printTaskTiming(threadDataAry, noThreads+1);
                tiTimerTask -= tiDisplay;
            }
            tiTimerTask += tiCycleTimerTask;
            assert(tiTimerTask < 2*tiDisplay);
#endif
        }

        pthread_mutex_unlock(&mutexDummy);
        pthread_mutex_destroy(&mutexDummy);
    }

    /* Don't use pthread_exit in main: It doesn't return and subsequent code is not
       executed. Use join for all pending threads and return normally.
         The loop iterates all successfully started user defined threads and the additional
       timer thread. */
    for(u=0; u<noRunningThreads; u++)
    {
        /* Send a termination command to the thread. Note, no atomic flag is required here,
           because we are the only writer and the thread is the only reader. */
        threadDataAry[u].terminate = true;

        LOG_DEBUG( sup_hGlobalLogger
                 , "%s: Waiting for termination of thread %u ..."
                 , __func__
                 , u
                 );
        fflush(stdout);
        pthread_join(threadDataAry[u].thread, NULL);
//        printf("%s: thread (%u) has joined\n", __func__, u);
//        fflush(stdout);
    }

#ifdef __WINNT__
    /* Windows: Reset the clock tick of the task scheduler. */
    mmRes = timeEndPeriod(/* uPeriodMs */ tiOsTick);
    if(mmRes != TIMERR_NOERROR)
        LOG_ERROR(sup_hGlobalLogger, "%s: Resetting Windows time quantum failed", __func__);
#endif

    return noRunningThreads == noThreads+1;

} /* End of rtos_runScheduler */

