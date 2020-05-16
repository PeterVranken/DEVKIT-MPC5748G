/**
 * @file mzb_main_Z4B.c
 * C entry function for the Z4 A core. The core completes the HW initialization (clocks run
 * at full speed, peripheral bridge is widely opened, SMPU is configured) and initializes a
 * few I/O drivers, e.g. LED drivers and serial I/O with the host. Then it starts the
 * safe-RTOS kernel on the core Z4A. The other cores are not started in this initial
 * sample.\n
 *   Two regular tasks are spinning and driving an LED each. A third LED is commanded by
 * the idle task. Only if three LEDs are blinking everything is alright.\n
 *   Progress information is permanently written into the serial output channel. A terminal
 * on the development host needs to use these settings: 115000 Bd, 8 Bit data word, no
 * parity, 1 stop bit.
 *
 * Copyright (C) 2018-2020 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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
 *   mzb_main_Z4B
 * Local functions
 *   taskInitProcess
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
#include "mzb_main_Z4B.h"


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
    are dealt out by rtos_osCreateEvent() form the series 0, 1, 2, .... So we don't need
    to have a dynamic storage of the IDs; we define them as constants and double-check by
    assertion that we got the correct, expected IDs from rtos_osCreateEvent(). Note, this
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

/** Counter of cycles of infinite main loop. */
volatile unsigned long SBSS_OS(mzb_cntTaskIdle) = 0;

/** Counter of cyclic 1ms user task. */
volatile unsigned long long SBSS_P1(mzb_cntTask1ms) = 0;  

/** Counter of cyclic 1ms OS task. */
volatile unsigned long long SBSS_OS(mzb_cntTaskOs1ms) = 0;

/** The average CPU load produced by all tasks and interrupts in tens of percent. */
unsigned int DATA_OS(mzb_cpuLoad) = 1000;



/*
 * Function implementation
 */


/**
 * Initialization task of process \a PID.
 *   @return
 * The function returns the Boolean descision, whether the initialization was alright and
 * the system can start up. "Not alright" is expressed by a negative number, which hinders
 * the RTOS to startup.
 *   @param PID
 * The ID of the process, the task function is executed in.
 *   @remark
 * In this sample, we demonstrate that different processes' tasks can share the same task
 * function implementation. This is meant a demonstration of the technical feasibility but
 * not of good practice; the implementation needs to use shared memory, which may break a
 * safety constraint, and it needs to consider the different privileges of the processes.
 */
static int32_t taskInitProcess(uint32_t PID)
{
    static unsigned int cnt_ SECTION(.data.Shared.cnt_) = 0;
    ++ cnt_;

//    /* Only process 1 has access to the C lib (more precise: to those functions of the C
//       lib, which write to lib owned data objects) and can write a status message. */
//    if(PID == 1)
//        iprintf("taskInitPID%lu(): %u\r\n", PID, cnt_);

    return cnt_ == PID? 0: -1;

} /* End of taskInitProcess */



/**
 * Test of LED and button driver: This callback is invoke on every state change of any of
 * the supported (two) buttons.
 *   @return
 * The function always returns zero (no error).
 *   @param PID
 * PID of process, which is registered for the callback.
 *   @param buttonState
 * Current state of both buttons and changes in the instance of calling. See enum
 * lbd_buttonStateMask_t for details.
 */
static int32_t onButtonChangeCallback(uint32_t PID ATTRIB_UNUSED, uint8_t buttonState)
{
    /* Test button input: The current status is echoed as LED status. */
    if((buttonState & lbd_btStMask_btnSw1_down) != 0)
        lbd_setLED(lbd_led_6_DS5,  /* isOn */ true);
    else if((buttonState & lbd_btStMask_btnSw1_released) != 0)
        lbd_setLED(lbd_led_6_DS5,  /* isOn */ false);
              
    return 0;    

} /* End of onButtonChangeCallback */


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
static int32_t task1ms(uint32_t PID ATTRIB_UNUSED, uintptr_t taskParam ATTRIB_DBG_ONLY)
{
    assert(taskParam == 0);

    /* Make spinning of the task observable in the debugger. */
    ++ mzb_cntTask1ms;

#if TASKS_PRODUCE_GROUND_LOAD == 1
    /* Produce a bit of CPU load. This call simulates some true application software. */
    del_delayMicroseconds(/* fullLoadThisNoMicroseconds */ 50 /* approx. 5% load */);
#endif

    static int SBSS_P1(cntIsOn_) = 0;
    if(++cntIsOn_ >= 500)
    {
        cntIsOn_ = -500;
        printf("This is call %llu of task1ms\r\n", mzb_cntTask1ms);
    }
    lbd_setLED(lbd_led_2_DS9, /* isOn */ cntIsOn_ >= 0);

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
static void taskOs1ms(uintptr_t taskParam ATTRIB_DBG_ONLY)
{
    assert(taskParam == 0);

    /* Make spinning of the task observable in the debugger. */
    ++ mzb_cntTaskOs1ms;

    /** Regularly called step function of the I/O driver. */
    lbd_osTask1ms();

#if TASKS_PRODUCE_GROUND_LOAD == 1
    /* Produce a bit of CPU load. This call simulates some true application software. */
    del_delayMicroseconds(/* fullLoadThisNoMicroseconds */ 75 /* approx. 7.5% load */);
#endif

    /* Test button input: The current status is echoed as LED status. */
    lbd_osSetLED(lbd_led_5_DS6,  /* isOn */ lbd_osGetButton(lbd_bt_button_SW2));
              
    static int SBSS_P1(cntIsOn_) = 0;
    if(++cntIsOn_ >= 500)
    {
        cntIsOn_ = -500;

        printf("This is call %llu of taskOs1ms\r\n", mzb_cntTaskOs1ms);
    }
    lbd_osSetLED(lbd_led_1_DS10, /* isOn */ cntIsOn_ >= 0);
    
} /* End of taskOs1ms */



/**
 * C entry function main. Is used for and only for Z4B core.
 *   @param noArgs
 * Number of arguments in \a argAry. Is actually always equal to one.
 *   @param argAry
 * Array of string arguments to the function. Actually, always a single string which equals
 * the name of the core, which is started.
 *   @remark
 * Actually, the function is a _Noreturn. We don't declare it as such in order to avoid a
 * compiler warning. 
 */
void /* _Noreturn */ mzb_main_Z4B( int noArgs ATTRIB_DBG_ONLY
                                 , const char *argAry[] ATTRIB_DBG_ONLY
                                 )
{
    assert(noArgs == 1  && strcmp(argAry[0], "Z4B") == 0);

#if 0 /* Here, on the second core, we must not make use of the serial output. It is
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
    puts("puts saying " GREETING);
    printf("printf saying %s", GREETING);
    #undef GREETING
#endif    

    /* Register the process initialization tasks. */
    bool initOk = true;
    if(rtos_osRegisterInitTask(taskInitProcess, /* PID */ 1, /* tiTaskMaxInUS */ 1000)
       != rtos_err_noError
      )
    {
        initOk = false;
    }

    /* Create the events that trigger application tasks at the RTOS. Note, we do not really
       respect the ID, which is assigned to the event by the RTOS API rtos_osCreateEvent().
       The returned value is redundant. This technique requires that we create the events
       in the right order and this requires in practice a double-check by assertion - later
       maintenance errors are unavoidable otherwise. */
    unsigned int idEvent;
    if(rtos_osCreateEvent( &idEvent
                         , /* tiCycleInMs */              1
                         , /* tiFirstActivationInMs */    10
                         , /* priority */                 prioEv1ms
                         , /* minPIDToTriggerThisEvent */ RTOS_EVENT_NOT_USER_TRIGGERABLE
                         , /* taskParam */                0
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

    /* Initialize the RTOS kernel. The global interrupt processing is resumed if it
       succeeds. The step involves a configuration check. We must not startup the SW if the
       check fails. */
    if(!initOk ||  rtos_osInitKernel() != rtos_err_noError)
        while(true)
            ;

    /* Only after initialization of the RTOS, we start the next core. They is because the
       function to register the interrupt handlers at the global, shared interrupt
       controller is not cross-core safe under all circumstances. This was we simply avoid
       any race condition. */
#if 0
    startSecondaryCore(/* idxCore */ 2 /* Z2 */, mzt_main_Z2);
#endif

    /* The code down here becomes the idle task of the RTOS. We enter an infinite loop,
       where some background can be placed. */
    while(true)
    {
        /* Compute the average CPU load. Note, this operation lasts about 1s and has a
           significant impact on the cycling speed of this infinite loop. Furthermore, it
           measures only the load produced by the tasks and system interrupts but not that
           of the rest of the code in the idle loop. */
        mzb_cpuLoad = gsl_osGetSystemLoad();

        static bool SBSS_OS(isOn_) = false;
        lbd_osSetLED(lbd_led_3_DS8, isOn_ = !isOn_);

        /* Make spinning of the idle task observable in the debugger. */
        ++ mzb_cntTaskIdle;

    } /* End of inifinite idle loop of RTOS. */

    /* We never get here. Just to avoid a compiler warning. */
//    return -1;

} /* End of mzb_main_Z4B */
