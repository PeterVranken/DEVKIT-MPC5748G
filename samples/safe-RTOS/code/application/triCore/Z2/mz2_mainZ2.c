/**
 * @file mz2_mainZ2.c
 * C entry function for the third core, Z2. It runs safe-RTOS with the same simple sample
 * application as core Z4B, "initial". It drives the last available user LED on the
 * evaluation board.
 *
 * Copyright (C) 2020-2024 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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
 *   mz2_onButtonChangeCallback
 *   mz2_mainZ2
 * Local functions
 *   isrPit4
 *   isrPit5
 *   isrPit6
 *   task1ms
 *   taskOs1ms
 */

/*
 * Include files
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>

#include "MPC5748G.h"
#include "typ_types.h"
#include "ccl_configureClocks.h"
#include "xbs_crossbarSwitch.h"

#include "rtos.h"
#include "gsl_systemLoad.h"
#include "lbd_ledAndButtonDriver.h"
#include "sio_serialIO.h"
#include "del_delay.h"
#include "stm_systemTimer.h"
#include "icn_interCoreNotification.h"
#include "m4b_mainZ4B.h"
#include "mz2_mainZ2.h"


/*
 * Defines
 */

/** The demo can be compiled with a ground load. Most tasks produce some CPU load if this
    switch is set to 1. */
#define TASKS_PRODUCE_GROUND_LOAD   1


/*
 * Local type definitions
 */

/** The enumeration of all events, tasks and priorities, to have them as symbols in the
    source code. Most relevant are the event IDs. Actually, these IDs are provided by the
    RTOS at runtime, when creating the event. However, it is guaranteed that the IDs, which
    are dealt out by rtos_osCreateEventProcessor() form the series 0, 1, 2, .... So we don't need
    to have a dynamic storage of the IDs; we define them as constants and double-check by
    assertion that we got the correct, expected IDs from rtos_osCreateEventProcessor(). Note, this
    requires that the order of creating the events follows the order here in the
    enumeration.\n
      Here, we have the IDs of the created events. They occupy the index range starting
    from zero. */
enum
{
    /** Regular timer event. */
    idEv1ms = 0,

    /** The number of tasks to register. */
    noRegisteredEvents
};


/** The RTOS uses constant priorities for its events, which are defined here.\n
      Note, the priority is a property of an event rather than of a task. A task implicitly
    inherits the priority of the event it is associated with. */
enum
{
    prioTaskIdle = 0,            /* Prio 0 is implicit, cannot be chosen explicitly */
    prioEv1ms = 1,
};


/** In safe-RTOS a task belongs to a process, characterized by the PID, 1..4. The
    relationship is defined here.\n
      Note, a process needs to be configured in the linker script (actually: assignment of
    stack space) before it can be used. */
enum
{
    pidOs = 0,              /* kernel always and implicitly has PID 0 */
    pidTask1ms = 1,         /* Don't use P2, there are failures injected in core 0 */
    pidTaskOs1ms = pidOs,   /* A kernel or operating system task, e.g. to implement a
                               polling I/O driver. */
    pidTaskIdle = pidOs     /* PID 0 is implicit, idle belongs to the kernel */
};


/*
 * Local prototypes
 */


/*
 * Data definitions
 */

/** Counter of regular 1ms user isr. */
volatile unsigned long SECTION(.uncached.OS.mz2_cntIsr1ms) mz2_cntIsr1ms = 0;

/** Counter of regular 100us user isr. */
volatile unsigned long SECTION(.uncached.OS.mz2_cntIsr100us) mz2_cntIsr100us = 0;

/** Counter of regular 33us user isr. */
volatile unsigned long SECTION(.uncached.OS.mz2_cntIsr33us) mz2_cntIsr33us = 0;

/** Counter of cyclic 1ms user task. */
volatile unsigned long SECTION(.uncached.P1.mz2_cntTask1ms) mz2_cntTask1ms = 0;

/** Counter of cyclic 1ms OS task. */
volatile unsigned long SECTION(.uncached.OS.mz2_cntTaskOs1ms) mz2_cntTaskOs1ms = 0;

/** Counter of cycles of infinite main loop. */
volatile unsigned long SECTION(.uncached.OS.mz2_cntTaskIdle) mz2_cntTaskIdle = 0;

/** Total counter of task failures in P1 on second core. */
volatile unsigned int SECTION(.uncached.OS.mz2_cntTaskFailuresP1) mz2_cntTaskFailuresP1 = 0;

/** Counter of notifications , which could not be delivered from Z2 to Z4B because the
    preceding notification had not been fully processed yet. */
volatile unsigned int UNCACHED_OS(mz2_noNotificationsLoss) = 0;

/** Activation loss counter for process 1 on the second core. */
volatile unsigned int SECTION(.uncached.OS.mz2_cntActivationLossFailures)
                                                        mz2_cntActivationLossFailures = 0;

/** Stack reserve of process p1 on the second core. */
volatile unsigned int SECTION(.uncached.OS.mz2_stackReserveP1) mz2_stackReserveP1 = 0;

/** Stack reserve of kernel process on the second core. */
volatile unsigned int SECTION(.uncached.OS.mz2_stackReserveOS) mz2_stackReserveOS = 0;

/** The average CPU load produced by all ISRs in tens of percent. */
volatile unsigned int SECTION(.uncached.OS.mz2_cpuLoadZ2) mz2_cpuLoadZ2 = 1000;


/*
 * Function implementation
 */

/**
 * A regularly triggered interrupt handler for the timer PIT4. The interrupt does nothing
 * but counting a variable. It is triggered at high frequency and asynchronously to the
 * other ISRs and clocks on the other cores.
 */
static void isrPit4(void)
{
    ++ mz2_cntIsr1ms;

    /* RM 51.4.11, p. 2738f: Acknowledge the timer interrupt in the causing HW device. Can
       be done as this is "trusted code" that is running in supervisor mode. */
    PIT->TIMER[4].TFLG = PIT_TFLG_TIF(1);

} /* End of isrPit4 */



/**
 * A regularly triggered interrupt handler for the timer PIT5. The interrupt does nothing
 * but counting a variable. It is triggered at high frequency and asynchronously to the
 * other ISRs and clocks on the other cores.
 */
static void isrPit5(void)
{
    ++ mz2_cntIsr100us;

    /* RM 51.4.11, p. 2738f: Acknowledge the timer interrupt in the causing HW device. Can
       be done as this is "trusted code" that is running in supervisor mode. */
     PIT->TIMER[5].TFLG = PIT_TFLG_TIF(1);

} /* End of isrPit5 */



/**
 * A regularly triggered interrupt handler for the timer PIT6. The interrupt does nothing
 * but counting a variable. It is triggered at high frequency and asynchronously to the
 * other ISRs and clocks on the other cores.
 */
static void isrPit6(void)
{
    ++ mz2_cntIsr33us;

    /* RM 51.4.11, p. 2738f: Acknowledge the timer interrupt in the causing HW device. Can
       be done as this is "trusted code" that is running in supervisor mode. */
    PIT->TIMER[6].TFLG = PIT_TFLG_TIF(1);

} /* End of isrPit6 */



/**
 * Task function, cyclically activated every Millisecond. The LED D4 is switched on and off.
 *   @return
 * If the task function returns a negative value then the task execution is counted as
 * error in the process.
 *   @param PID
 * A user task function gets the process ID as first argument.
 *   @param taskParam
 * A variable task parameter. Here just used for testing.
 */
static int32_t task1ms(uint32_t PID ATTRIB_UNUSED, uint32_t taskParam ATTRIB_DBG_ONLY)
{
    assert(taskParam == 0);

    /* Make spinning of the task observable in the debugger. */
    ++ mz2_cntTask1ms;

#if TASKS_PRODUCE_GROUND_LOAD == 1
    /* Produce a bit of CPU load. This call simulates some true application software. */
    del_delayMicroseconds(/* fullLoadThisNoMicroseconds */ 50 /* approx. 5% load */);
#endif

#if 0
    /* Inject an error from time to time. */
    static unsigned int SDATA_P1(idxErr_) = 0;
    if((mz2_cntTask1ms & 0x3) == 0)
        m4b_injectError(&idxErr_);
#endif

    return 0;

} /* End of task1ms */



/**
 * OS task function, cyclically activated every Millisecond. Used to clock the step
 * functions of our I/O drivers.\n
 *   This task is run in supervisor mode and it has no protection. The implementation
 * belongs into the sphere of trusted code.
 *   @param taskParam
 * A variable task parameter. Here just used for testing.
 */
static void taskOs1ms(uint32_t taskParam ATTRIB_DBG_ONLY)
{
    assert(taskParam == 0);

    /* Make spinning of the task observable in the debugger. */
    ++ mz2_cntTaskOs1ms;

    /** Regularly called step function of the I/O driver. */
    lbd_osTask1ms();

#if TASKS_PRODUCE_GROUND_LOAD == 1
    /* Produce a bit of CPU load. This call simulates some true application software. */
    del_delayMicroseconds(/* fullLoadThisNoMicroseconds */ 75 /* approx. 7.5% load */);
#endif

    /* Test button input: The current status is echoed as LED status. */
//    lbd_osSetLED(lbd_led_5_DS6,  /* isOn */ lbd_osGetButton(lbd_bt_button_SW2));

    /* Communicate the current number of recognized failures to the reporting task running
       on the boot core. */
    mz2_cntTaskFailuresP1 = rtos_getNoTotalTaskFailure(pidTask1ms);
    mz2_cntActivationLossFailures = rtos_getNoActivationLoss(idEv1ms);

    /* Try the inter-core notification driver: We send an event to activate a task on core
       Z4B. The notification parameter is a simple sequence 0, 1, 2, ..., which is
       double-checked at the receiver side for validation that all notifications were
       delivered. */
    if(icn_osIsNotificationPending(ICN_ID_NOTIFICATION_Z2_TO_Z4B))
        ++ mz2_noNotificationsLoss;
    else
    {
        icn_osSendNotification( ICN_ID_NOTIFICATION_Z2_TO_Z4B
                              , /* notificationParam */ 
                                mz2_cntTaskOs1ms-1-mz2_noNotificationsLoss
                              );
    }
} /* End of taskOs1ms */



/**
 * Test of LED and button driver: This callback is invoked on every state change of any of
 * the supported (two) buttons.
 *   @return
 * The function always returns zero (no error).
 *   @param PID
 * PID of process, which is registered for the callback.
 *   @param buttonState
 * Current state of both buttons and changes in the instance of calling. See enum
 * lbd_buttonStateMask_t for details.
 *   @remark
 * This function must never be called directly. It has been made public for the only reason
 * that the boot core needs to know it for the initialization call of the I/O driver.
 */
int32_t mz2_onButtonChangeCallback( uint32_t PID ATTRIB_UNUSED
                                  , uint8_t buttonState ATTRIB_UNUSED
                                  )
{
#if 0
    /* Test button input: The current status is echoed as LED status. */
    if((buttonState & lbd_btStMask_btnSw1_down) != 0)
        lbd_setLED(lbd_led_6_DS5,  /* isOn */ true);
    else if((buttonState & lbd_btStMask_btnSw1_released) != 0)
        lbd_setLED(lbd_led_6_DS5,  /* isOn */ false);
#endif

    return 0;

} /* End of mz2_onButtonChangeCallback */



/**
 * This demonstration software uses a number of fast interrupts to produce system load and
 * prove stability. The interrupts are timer controlled (for simplicity) but the
 * activations are chosen as asynchronous to the operating system clock as possible to
 * provoke a most variable preemption pattern.
 */
static void osInstallInterruptServiceRoutines(void)
{
    /* Disable timers during configuration. RM, 51.4.1, p. 2731.
         Disable all PIT timers during configuration. Note, this is a global setting for
       all sixteen timers. Accessing the bits makes this rountine have race conditions with
       the RTOS initialization that uses timer #RTOS_CORE_0_IDX_OF_PID_TIMER. Both routines
       must not be called in concurrency. */
    PIT->MCR = PIT_MCR_MDIS(1) | PIT_MCR_FRZ(1);

    /* Install the ISRs now that all timers are stopped.
         Vector numbers: See MCU reference manual, section 28.7, table 28-4. */
    const unsigned int processorID = rtos_osGetIdxCore();
    rtos_osRegisterInterruptHandler( &isrPit4
                                   , processorID
                                   , /* vectorNum */ PIT_Ch4_IRQn
                                   , /* psrPriority */ 1
                                   , /* isPreemptable */ true
                                   );
    rtos_osRegisterInterruptHandler( &isrPit5
                                   , processorID
                                   , /* vectorNum */ PIT_Ch5_IRQn
                                   , /* psrPriority */ 2
                                   , /* isPreemptable */ true
                                   );
    rtos_osRegisterInterruptHandler( &isrPit6
                                   , processorID
                                   , /* vectorNum */ PIT_Ch6_IRQn
                                   , /* psrPriority */ 3
                                   , /* isPreemptable */ true
                                   );

    /* Peripheral clock has been initialized to 40 MHz. The timers count at this rate. To
       get a 1ms interrupt tick we need to count till 40000.
         The RTOS on the other cores operates in ticks of 1ms. We use prime numbers to get
       good asynchronity with that activity.
         -1: See RM, 51.6 */
    PIT->TIMER[4].LDVAL = 39979-1;/* Interrupt rate approx. 1kHz */
    PIT->TIMER[5].LDVAL = 3989-1; /* Interrupt rate approx. 10kHz */
    PIT->TIMER[6].LDVAL = 1321-1; /* Interrupt rate approx. 30kHz */

    /* Enable timer operation. This operation affects all timer channels.
         PIT_MCR_FRZ: For this multi-core MCU it is not so easy to decide whether or not to
       let the timers be stopped on debugger entry: Any stopped core will halt the timers,
       regardless whether that core is related to the timer or not (and how should the
       debugger know...). Both possibilities can be annoying or advantageous, depending on
       the situation. */
    PIT->MCR = PIT_MCR_MDIS(0) | PIT_MCR_FRZ(1);

    /* Clear possibly pending interrupt flags. */
    PIT->TIMER[4].TFLG = PIT_TFLG_TIF(1);
    PIT->TIMER[5].TFLG = PIT_TFLG_TIF(1);
    PIT->TIMER[6].TFLG = PIT_TFLG_TIF(1);

    /* Enable interrupts by the timers and start them. See RM 51.4.10. */
    PIT->TIMER[4].TCTRL = PIT_TCTRL_CHN(0) | PIT_TCTRL_TIE(1) | PIT_TCTRL_TEN(1);
    PIT->TIMER[5].TCTRL = PIT_TCTRL_CHN(0) | PIT_TCTRL_TIE(1) | PIT_TCTRL_TEN(1);
    PIT->TIMER[6].TCTRL = PIT_TCTRL_CHN(0) | PIT_TCTRL_TIE(1) | PIT_TCTRL_TEN(1);

} /* End of osInstallInterruptServiceRoutines */



/**
 * C entry function for the third core, Z2. It runs safe-RTOS with the same simple sample
 * application as core Z4B, "initial". It drives the last available user LED on the
 * evaluation board.
 *   @param noArgs
 * Number of arguments in \a argAry. Is actually always equal to one.
 *   @param argAry
 * Array of string arguments to the function. Actually, always a single string which equals
 * the name of the core, which is started.
 *   @remark
 * Actually, the function is a _Noreturn. We don't declare it as such in order to avoid a
 * compiler warning.
 */
void /* _Noreturn */ mz2_mainZ2( int noArgs ATTRIB_DBG_ONLY
                               , const char *argAry[] ATTRIB_DBG_ONLY
                               )
{
    assert(noArgs == 1  &&  strcmp(argAry[0], "Z2") == 0);

#if 0 /* Here, on the third core, we must not make use of the serial output. It is
         basically alright to make use of the sio API but blocking by busy wait is involved
         with hard to predict impact on the RTOS timing. Moreover, the use of the C library
         is strongly deprecated - it is not proven that it has been configured and compiled
         for multi-core use. Simple functions without static data will properly work, but
         nothing can be said about the printf and stream function families, which make use
         of buffers and heap. */

    /* Demonstrate the use of the serial interface. Note, the function is never blocking
       and we have left it for a long time before the character are visible in the console
       window. Never blocking: If the buffer has not enough space then an according number
       of characters is dropped rather than the function waiting for the buffer becoming
       empty. */
    #define GREETING "Hello World\r\n"
    sio_osWriteSerial(GREETING, /* noBytes */ sizeof(GREETING)-1);
    fputs("fputs saying " GREETING, stdout);
    printf("printf saying %s", GREETING);
    #undef GREETING
#endif

    /* Create the events that trigger application tasks at the RTOS. Note, we do not really
       respect the ID, which is assigned to the event by the RTOS API rtos_osCreateEventProcessor().
       The returned value is redundant. This technique requires that we create the events
       in the right order and this requires in practice a double-check by assertion - later
       maintenance errors are unavoidable otherwise. */
    bool initOk = true;
    unsigned int idEvent;
    if(rtos_osCreateEventProcessor
                        ( &idEvent
                        , /* tiCycleInMs */               1
                        , /* tiFirstActivationInMs */     10
                        , /* priority */                  prioEv1ms
                        , /* minPIDToTriggerThisEvProc */ RTOS_EVENT_PROC_NOT_USER_TRIGGERABLE
                        , /* timerUsesCountableEvents */  false
                        , /* taskParam */                 0
                        )
       == rtos_err_noError
      )
    {
        assert(idEvent == idEv1ms);

        if(rtos_osRegisterOSTask(idEv1ms, taskOs1ms) != rtos_err_noError)
            initOk = false;

        if(rtos_osRegisterUserTask( idEv1ms
                                  , task1ms
                                  , pidTask1ms
                                  , /* tiTaskMaxInUs */ 0
                                  )
           != rtos_err_noError
          )
        {
            initOk = false;
        }
    }
    else
        initOk = false;

    /* The last check ensures that we didn't forget to register a task. */
    assert(idEvent == noRegisteredEvents-1);

    /* Configure the interrupts, which we have justto produce some load and disturbance. */
    osInstallInterruptServiceRoutines();

    /* Initialize the RTOS kernel. The global interrupt processing is resumed if it
       succeeds. The step involves a configuration check. We must not startup the SW if the
       check fails. */
    if(!initOk ||  rtos_osInitKernel() != rtos_err_noError)
        while(true)
            ;

    /* The rest of the code is placed in an infinite loop; it becomes the RTOS' idle task. */
    while(true)
    {
        /* Compute the average CPU load. Note, this operation lasts about 1.5s and has a
           significant impact on the cycling speed of this infinite loop. Furthermore, it
           measures only the load produced by the interrupts but not that of the rest of
           the code in the idle loop. */
        mz2_cpuLoadZ2 = gsl_osGetSystemLoad();

        /* We have only one LED left for this core. We let it blink as usually but since it
           should be a failure indication, we enable the activity only if everything looks
           alright. Particularly, the interrupts should work properly.
             We assume, that the idle loop takes between 1 and 2s. */
        bool isSystemAlive = mz2_cpuLoadZ2 < 1000
                             &&  mz2_cpuLoadZ2 > 0;

        static unsigned long SDATA_OS(cntIsr1ms_) = 0;
        unsigned long tmpCnt = mz2_cntIsr1ms;
        if(tmpCnt < cntIsr1ms_+1000u  ||  tmpCnt > cntIsr1ms_+2000u)
            isSystemAlive = false;
        cntIsr1ms_ = tmpCnt;

        static unsigned long SDATA_OS(cntIsr100us_) = 0;
        tmpCnt = mz2_cntIsr100us;
        if(tmpCnt < cntIsr100us_+10000u  ||  tmpCnt > cntIsr100us_+20000u)
            isSystemAlive = false;
        cntIsr100us_ = tmpCnt;

        static unsigned long SDATA_OS(cntIsr33us_) = 0;
        tmpCnt = mz2_cntIsr33us;
        if(tmpCnt < cntIsr33us_+30000u  ||  tmpCnt > cntIsr33us_+60000u)
            isSystemAlive = false;
        cntIsr33us_ = tmpCnt;

        static unsigned long SDATA_OS(cntTask1ms_) = 0;
        tmpCnt = mz2_cntTask1ms;
        if(tmpCnt < cntTask1ms_+1000u  ||  tmpCnt > cntTask1ms_+2000u)
            isSystemAlive = false;
        cntTask1ms_ = tmpCnt;

        static unsigned long SDATA_OS(cntTaskOs1ms_) = 0;
        tmpCnt = mz2_cntTaskOs1ms;
        if(tmpCnt < cntTaskOs1ms_+1000u  ||  tmpCnt > cntTaskOs1ms_+2000u)
            isSystemAlive = false;
        cntTaskOs1ms_ = tmpCnt;

        static bool SBSS_OS(isOn_) = false;
        isOn_ = isSystemAlive && !isOn_;
        lbd_osSetLED(lbd_led_4_DS7, isOn_);

        /* Communicate some status information to the reporting task running on the boot
           core. */
        mz2_stackReserveP1 = rtos_getStackReserve(pidTask1ms);
        mz2_stackReserveOS = rtos_getStackReserve(pidOs);

        /* Make spinning of the idle task observable in the debugger. */
        ++ mz2_cntTaskIdle;

    } /* End of inifinite idle loop of bare metal application. */

} /* End of mz2_mainZ2 */
