/**
 * @file gsl_systemLoad.c
 *   Measure the current CPU load produced by the application code. A support function for
 * the use with the PowerPC RTOS.
 *   @see uint8_t gsl_osGetSystemLoad(void)
 *
 * This file is an adoption from the Arduino RTOS RTuinOS. The original file has been
 * downloaded from https://svn.code.sf.net/p/rtuinos/code/trunk/code/RTOS/gsl_systemLoad.c
 * on Nov 15, 2017.\n
 *   The major difference of this implementation to the original RTuinOS source is the
 * change to the native 32 Bit data type for the calculations. The Arduino function
 * delayMicroseconds() has been replaced by the PowerPC substitute del_delayMicroseconds().
 *
 * Copyright (C) 2012-2020 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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
 *   gsl_osGetSystemLoad
 * Local functions
 */

/*
 * Include files
 */

#include <assert.h>

#include "typ_types.h"
#include "del_delay.h"
#include "ccl_configureClocks.h"
#include "stm_systemTimer.h"
#include "gsl_systemLoad.h"


/*
 * Defines
 */
 
/** The function of this module is based on the exactely known execution time of a delay
    function. If this macro is set to one then the actual execution time of this function
    is measured and reported (to the debugger). The acutal delay can then be tuned based on
    the results. The CPU load result is invalid in this case and the normal setting for
    this define will be zero.
      @remark Caution, if calibration mode is on then the function is no longer reentrant,
    but it is usually run on more than one core at a time. The cores will overwrite one
    another's results.
      @remark Setting this module into calibration mode requires that no watchdog is
    active. */
#define MODULE_CALIBRATION_MODE     0

/** Averaging time window of gsl_osGetSystemLoad(void) in ms. The window should contain a
    full cycle of tasks activations. To avoid integer overflows, the window size must be
    significantly below 27s. We prefer a prime number to get most likely a sliding window
    with respect to the typical RTOS configurations with their regular tasks as multiples
    of a Millisecond (better average). */
#define TI_WINDOW_LEN_MS            1493u

#if MODULE_CALIBRATION_MODE == 1
# include "rtos.h"
#endif


/*
 * Local type definitions
 */
 
 
/*
 * Local prototypes
 */
 
 
/*
 * Data definitions
 */
 
#if MODULE_CALIBRATION_MODE == 1
/** This is a global array, which exists only if the module is compiled in calibration
    mode. Calibration mode is for development only. Instead of measuring the CPU load the
    internally used delay function is checked. The actually yielded delay times are
    measured and stored in this array for inspection. The unit is the STM counter period
    (12.5 ns on our platform) and the accurate, expected time is 100ms. */
static uint32_t DATA_OS(gsl_tiCalResult)[32];
#endif
 
/*
 * Function implementation
 */

/**
 * A diagnostic function, which can be used to estimate the current system load. The
 * function executes some test code of known CPU execution time and relates this known time
 * to the measured, actually elapsed world time. The function needs to be called from the
 * idle task only. Now the mentioned ratio is a measure for the system load: The lesser the
 * system idles the longer it'll take to execute the test code.\n
 *   On principal, the execution time of the function depends on the system load and can
 * raise to infinite if the load approaches 100%. This effect is lowered by splitting the
 * test code in pieces and ending the measurement if enough pieces have been executed to
 * get the desired resolution. Nonetheless, the effect remains and no upper boundary can
 * be given for the execution time of this function if the system load is close to 100%.\n
 *   Normally, the execution time of this function is about 1 second. This long time is
 * needed to have a sufficient averaging effect; typically the CPU consumption by the tasks
 * is quite irregular due to the complex task activation pattern of the scheduler. The
 * averaging time can be changed at compile time, please see macro #TI_WINDOW_LEN_MS.
 *   @return
 * The system load is returned with a resolution 0.1%, i.e. as an integer number in the
 * range 0..1000.
 *   @remark
 * The function execution takes a long time (above 1s). It must only be called from the
 * idle task and only if there are no other essential jobs for the idle task.
 *   @remark
 * The function will never return if the CPU load is 100% and it might take an arbitrary
 * long time to return if it is close to 100%. The calling code must anticipate this, e.g.
 * by presetting the result variable with 100% prior to calling this function.
 *   @remark
 * If the idle task contains other code besides repeatedly calling this function, then the
 * execution time of that code is not considered by the measurement, it does not contribute
 * to the returned CPU load result.
 */
unsigned int gsl_osGetSystemLoad(void)
{
#define IDX_STM_TIMER       0
#define STM_TIMER_CLK       STM_TIMER_0_CLK
#define TI_STEP_IN_MS       100u

    uint32_t step = 0;
    uint32_t tiEnd;
    uint32_t tiStart = stm_osGetSystemTime(IDX_STM_TIMER);
    uint32_t tiEndMin = tiStart + (uint32_t)((uint64_t)TI_WINDOW_LEN_MS
                                             * (uint64_t)STM_TIMER_CLK
                                             / 1000ull
                                            );
    
#if MODULE_CALIBRATION_MODE == 1
    /* In calibration mode the actual delay times are measured and stored in a cyclically
       addressed array. Using the debugger the last recent number of values can be read
       out. The accuracy can be evaluated and an average error can be tuned. */
    static unsigned int SBSS_OS(idxCalResult_) = 0;
#endif

    do
    {
        /* Count the steps. */
        ++ step;

#if MODULE_CALIBRATION_MODE == 1
        uint32_t msr = rtos_osEnterCriticalSection();
        uint32_t tiDelayTimeAct = stm_osGetSystemTime(IDX_STM_TIMER);
#endif
        /* One step is exactly 100 ms of code execution time - regardless of how long this
           will take because of interruptions by ISRs and other tasks. */
        del_delayMicroseconds(/* tiInUs */ TI_STEP_IN_MS*1000u);

#if MODULE_CALIBRATION_MODE == 1
        uint32_t tiDelayTimeEnd = stm_osGetSystemTime(IDX_STM_TIMER);
        rtos_osLeaveCriticalSection(msr);
        
        tiDelayTimeAct = tiDelayTimeEnd - tiDelayTimeAct;
        assert(idxCalResult_ < sizeOfAry(gsl_tiCalResult));
        gsl_tiCalResult[idxCalResult_] = tiDelayTimeAct;
        idxCalResult_ = (idxCalResult_+1) % sizeOfAry(gsl_tiCalResult);
#endif

        tiEnd = stm_osGetSystemTime(IDX_STM_TIMER);
    }
    while((int32_t)(tiEnd - tiEndMin) < 0);
    
    /* The measured, elapsed time in STM counter ticks, 12.5 ns on our platform. */
    uint32_t tiWorld = tiEnd - tiStart;
    
    /* In order to avoid overflows of the 32 Bit range we reduce the time resolution by 1000
       for the rest of the computation. Down here all time units are 1000 STM counter periods
       or 12.5us. */
    tiWorld = (tiWorld + 500)/1000;
       
    /* The consumed CPU time in unit 1000 STM counter ticks. */
#if STM_TIMER_CLK % 1000000u != 0
# error Chosen implementation does not fit to configured timing values
#endif
    uint32_t tiCpu = step * (TI_STEP_IN_MS * (STM_TIMER_CLK / 1000000u));
    if(tiWorld >= 1000u*tiCpu)
    {
        /* If the elapsed time is too large, we can limit the result by rounding to 100%.
           The chosen boundary is to round all above 99.9% to 100%. Since we use 0.1% as
           resolution of the result, the rounded range can anyway not be distinguished from
           100%. */
        return 1000; 
    }
    else if(tiWorld <= tiCpu)
    {
        /* Theoretically, the consumed CPU time can't be greater than the measured, elapsed
           time. However, we have some limitations of accuracy, e.g. the accuracy of the
           delay function, so that this rule could be hurt. We need a limiting statement to
           safely avoid an overrun. */
        return 0;
    }    
    else
    {
        /* Normal situation. The system load is all the time, which was not spent in the
           idle task inside this test routine in relation to the elapsed world time, or
           (Elapsed time - Consumed CPU time)/Elapsed time respectively. This is taken by
           1000 to get the desired resolution of 0.1%. */
        return 1000u - (1000*tiCpu/tiWorld);
    }
#undef TI_STEP_IN_MS
#undef IDX_STM_TIMER
#undef STM_TIMER_CLK
} /* End of gsl_osGetSystemLoad */




