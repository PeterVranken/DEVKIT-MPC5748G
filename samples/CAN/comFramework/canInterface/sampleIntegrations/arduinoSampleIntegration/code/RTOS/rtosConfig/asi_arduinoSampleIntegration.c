/**
 * @file asi_arduinoSampleIntegration.c
 *   
 * This is the main entry point into the sample integration and application of the
 * comFramework CAN interface on an Arduino Atmega2560 RTuinOS platform. Initialization,
 * root task functions and the idle loop of the RTOS are implemented here.
 *
 * @remark TBC
 *   The compilation of this sample requires linkage against the stdio library with
 * floating point support for printf & co. The selection of this library is done in the
 * makefile "callback" into tc14.mk (see above).
 *
 * Copyright (C) 2015-2022 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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
 *
 * Module interface
 *   setup
 *   loop
 * Local functions
 *   blink
 *   taskOnCanReceive
 *   task10ms
 *   task100ms
 */

/*
 * Include files
 */

#include <stdlib.h>
#include <Arduino.h>

#include "rtos.h"
#include "rtos_assert.h"
#include "gsl_systemLoad.h"
#include "stdout.h"
#include "csh_canShield.h"
#include "pck_packCanFrame.h"
#include "apt_applicationTask.h"
#include "dpy_display.h"
#include "sim_simulateCanReception.h"


/*
 * Defines
 */

/** Debugging support: Normally all results are printed from the idle task. The use of
    printf for this reporting can be inhibited in order to make the stdout stream and the
    Serial object behind printf (temporarily) available to other tasks for sake of program
    debugging. */
#define ENABLE_PRINTF_FOR_IDLE_TASK     1

/** Stack size of the task, which simulates CAN reception events. */
#define STACK_SIZE_TASK_ON_CAN_RECEIVE  256

/** Stack size of the regular 10 ms application task. */
#define STACK_SIZE_TASK_10MS            256

/** Stack size of the regular 100 ms application task. */
#define STACK_SIZE_TASK_100MS           256


/** Pin 13 has an LED connected on most Arduino boards. */
#define LED 13

/** The index to the task objects as needed for requesting the overrun counter or the stack
    usage.
      @remark The order of enumeration values matters: The task are ordered in falling
    priority, see implementation of \a setup. */
enum { idxTaskOnCanReceive = 0
     , idxTask10ms
     , idxTask100ms
     , noTasks
     };


/*
 * Local type definitions
 */


/*
 * Local prototypes
 */


/*
 * Data definitions
 */

/* Count the loops of the tasks, for debugging only. */
#ifdef DEBUG
volatile unsigned long _cntOnCanReceive = 0;
volatile unsigned long _cnt10ms = 0;
volatile unsigned long _cnt100ms = 0;
#endif

/*
 * Function implementation
 */

/**
 * Trivial routine that flashes the LED a number of times to give simple feedback. The
 * routine is blocking.
 *   @param noFlashes
 * The number of times the LED is lit.
 */
static void blink(uint8_t noFlashes)
{
#define TI_FLASH 150

    while(noFlashes-- > 0)
    {
        digitalWrite(LED, HIGH);  /* Turn the LED on. (HIGH is the voltage level.) */
        delay(TI_FLASH);          /* The flash time. */
        digitalWrite(LED, LOW);   /* Turn the LED off by making the voltage LOW. */
        delay(TI_FLASH);          /* Time between flashes. */
    }
    delay(1000-TI_FLASH);         /* Wait for a second after the last flash - this command
                                     could easily be invoked immediately again and the
                                     bursts need to be separated. */
#undef TI_FLASH
}



/**
 * The implementation of the root timing of the CAN reception simulation task. The task is
 * frequently activated and has the highest priority. It is however somewhat irregular in
 * order to simulate unpredictive timing effects like jitter of a true physical CAN bus.\n
 *   The actual simulation of CAN reception and CAN data handling is done in another
 * external function, which is called fom here. This function belongs to the simulation
 * module of this application.
 *   @param initialResumeCondition
 * The vector of events which made the task due the very first time.
 */

static void taskOnCanReceive(uint16_t initialResumeCondition)
{
    ASSERT(initialResumeCondition == RTOS_EVT_DELAY_TIMER);
    
    uintTime_t noTicksTillNextReception;
    do
    {
#ifdef DEBUG
        ++ _cntOnCanReceive;
#endif
        /* The fastest regular CAN message we have has a 10 ms period. We vary the call of
           the simulation code equally distributed from 4 .. 16 ms, which gives a pretty
           irregular timing of the CAN reception simulation. In mean we realize a calling
           frequency of 10 ms. The simulation can count its invocations and take this as
           its 10 ms time base. */
        sim_simulateCanReception();

        /* The ticks computation depends on the assumption of a 2ms clock tick, which we
           have only roughly. This means a static timing error, which is however not seen
           by our application as it doesn't have an absolute reference clock. Instead all
           task timing has the same 2% of deviation. */
           
        /* -1: The already running time slice must be subtracted. */
        noTicksTillNextReception = 2 + rand() % 7 - 1;
    }
    while(rtos_waitForEvent(RTOS_EVT_DELAY_TIMER, /* all */ false, noTicksTillNextReception));
    ASSERT(false);
    
#undef MS_10
} /* End of taskOnCanReceive */





/**
 * The implementation of the regular 10 ms application task. It has an infinite loop,
 * always waiting for the next 10 ms clock tick and then invoking the external application
 * task function.
 *   @param initialResumeCondition
 * The vector of events which made the task due the very first time.
 */

static void task10ms(uint16_t initialResumeCondition)
{
#define MS_10   (uintTime_t)(10.0e-3/RTOS_TIC + 0.5)

    ASSERT(initialResumeCondition == RTOS_EVT_DELAY_TIMER  &&  MS_10 <= 127);
    
    do
    {
#ifdef DEBUG
        ++ _cnt10ms;
#endif
        /* Call external application task function. */
        apt_task10ms();
    }        
    while(rtos_suspendTaskTillTime(MS_10));
    ASSERT(false);
    
#undef MS_10
} /* End of task10ms */





/**
 * The implementation of the regular 100 ms application task. It has an infinite loop,
 * always waiting for the next 100 ms clock tick and then invoking the external application
 * task function.
 *   @param initialResumeCondition
 * The vector of events which made the task due the very first time.
 */

static void task100ms(uint16_t initialResumeCondition)
{
#define MS_100   (uintTime_t)(100.0e-3/RTOS_TIC + 0.5)

    ASSERT(initialResumeCondition == RTOS_EVT_DELAY_TIMER  &&  MS_100 <= 127);
    
    do
    {
#ifdef DEBUG
        ++ _cnt100ms;
#endif
        /* Call external application task function. */
        apt_task100ms();
    }        
    while(rtos_suspendTaskTillTime(MS_100));
    ASSERT(false);
    
#undef MS_100
} /* End of task100ms */





/**
 * The initalization of the RTOS tasks and general board initialization.
 */

void setup()
{
#if defined(DEBUG)  || ENABLE_PRINTF_FOR_IDLE_TASK
    /* Redirect stdout into Serial at 9600 bps. */
    init_stdout(9600);

    /* Print greeting to the console window. */
    puts_progmem(rtos_rtuinosStartupMsg);
#endif

    /* Print greeting on the LCD. */
    dpy_printGreeting();

    /* Initialize the digital pin as an output. The LED is used for most basic feedback about
       operability of code. */
    pinMode(LED, OUTPUT);

    /* Write the invariant parts of the display once. This needs to be done here, before
       multitasking begins. */
    dpy_printBackground();

    /* Configure all tasks. */
    ASSERT(noTasks == RTOS_NO_TASKS);
    
    /* Configure the task of highest priority: It simulates the CAN reception and would be
       configured in RTuinOS as CAN interrupt handler in a platform with true CAN
       hardware. */
    uint8_t idxTask = idxTaskOnCanReceive;
    ASSERT(idxTask < RTOS_NO_TASKS);
    static uint8_t stackTaskOnCanReceive_[STACK_SIZE_TASK_ON_CAN_RECEIVE];
    rtos_initializeTask( idxTask       
                       , /* taskFunction */     taskOnCanReceive
                       , /* priority */         RTOS_NO_PRIO_CLASSES-idxTask-1
                       , /* pStackArea */       &stackTaskOnCanReceive_[0]
                       , /* stackSize */        sizeof(stackTaskOnCanReceive_)
                       , /* startEventMask */   RTOS_EVT_DELAY_TIMER
                       , /* startByAllEvents */ false
                       , /* startTimeout */     0
                       );

    /* Configure the regular 10 ms task. */
    idxTask = idxTask10ms;
    ASSERT(idxTask < RTOS_NO_TASKS);
    static uint8_t stackTask10ms_[STACK_SIZE_TASK_10MS];
    rtos_initializeTask( /* idxTask */          idxTask10ms
                       , /* taskFunction */     task10ms
                       , /* prioClass */        RTOS_NO_PRIO_CLASSES-idxTask-1
                       , /* pStackArea */       &stackTask10ms_[0]
                       , /* stackSize */        sizeof(stackTask10ms_)
                       , /* startEventMask */   RTOS_EVT_DELAY_TIMER
                       , /* startByAllEvents */ false
                       , /* startTimeout */     0
                       );

    /* Configure the regular 100 ms task. */
    idxTask = idxTask100ms;
    ASSERT(idxTask < RTOS_NO_TASKS);
    static uint8_t stackTask100ms_[STACK_SIZE_TASK_100MS];
    rtos_initializeTask( /* idxTask */          idxTask100ms
                       , /* taskFunction */     task100ms
                       , /* prioClass */        RTOS_NO_PRIO_CLASSES-idxTask-1
                       , /* pStackArea */       &stackTask100ms_[0]
                       , /* stackSize */        sizeof(stackTask100ms_)
                       , /* startEventMask */   RTOS_EVT_DELAY_TIMER
                       , /* startByAllEvents */ false
                       , /* startTimeout */     0
                       );

    /* Initialize the (simulated) CAN shield. */
    csh_initModule();
    
    /* Initialize the APSW. */
    apt_taskInit();

} /* End of setup */




/**
 * The application owned part of the idle task. This routine is repeatedly called whenever
 * there's some execution time left. It's interrupted by any other task when it becomes
 * due.
 *   @remark
 * Different to all other tasks, the idle task routine may and should return. (The task as
 * such doesn't terminate). This has been designed in accordance with the meaning of the
 * original Arduino loop function.
 */

void loop()
{
    /* Give an alive sign. */
    blink(3);
    
#if ENABLE_PRINTF_FOR_IDLE_TASK
    printf("RTuinOS is idle\n");
#endif

    /* Compute the CPU load and write the result into a global variable. No
       access synchronization is needed here since writing and reading a uint8 is atomic. */
    const uint8_t cpuLoad = gsl_getSystemLoad();

#if ENABLE_PRINTF_FOR_IDLE_TASK
    printf("CPU load: %.1f %%\n", (double)cpuLoad/2.0);
#ifdef DEBUG
    cli();
    const unsigned long cntOnCanReceive = _cntOnCanReceive
                      , cnt10ms = _cnt10ms
                      , cnt100ms = _cnt100ms;
    sei();    
    printf("Task counts: CAN reception: %lu, 10ms: %lu, 100ms: %lu\n"    
          , cntOnCanReceive
          , cnt10ms
          , cnt100ms
          );
#endif
    uint8_t u;
    for(u=0; u<RTOS_NO_TASKS; ++u)
    {
        printf( "Task %u: Unused stack area %u Byte, overrun counter: %u\n"
              , u
              , rtos_getStackReserve(u)
              , rtos_getTaskOverrunCounter(/* idxTask */ u, /* doReset */ false)
              );
    }
    cli();
    const cbk_stsTransmission_t stsTransmission_1024 = pck_API_PT_StateEcu01_1024.stsTransmission
                              , stsTransmission_1040 = pck_API_PT_StateEcu02_1040.stsTransmission
                              , stsTransmission_2032 = pck_API_PT_UserLimits_2032.stsTransmission;
    const uint16_t noQueueFullEvents = apt_noLostFrameEvents;
    sei();
    printf( "Can status: StateEcu01, 1024: %u, StateEcu01, 1040: %u, UserLimits, 2032: %u,"
            " lost events: %u\n"
          , (unsigned)stsTransmission_1024
          , (unsigned)stsTransmission_1040
          , (unsigned)stsTransmission_2032
          , noQueueFullEvents
          );
    
    /* The results are computed in the 10ms task. We need mutual exclusion, when accessing
       the data. */
    cli();
    const pck_PT_InfoPowerDisplay_1536_t PT_InfoPowerDisplay_1536 = pck_API_PT_InfoPowerDisplay_1536
                                                              .signals;
    const signed int torque = (int)PCK_PT_1040_TORQUE_BIN_TO_FLT
                                            (pck_API_PT_StateEcu02_1040.signals.torque)
                   , speedOfRotation = (int)PCK_PT_1024_SPEEDOFROTATION_BIN_TO_FLT
                                        (pck_API_PT_StateEcu01_1024.signals.speedOfRotation);
    const signed long power = (long)PCK_PT_1536_POWER_BIN_TO_FLT(PT_InfoPowerDisplay_1536.power);
    sei();
    if(PT_InfoPowerDisplay_1536.state != 1 /* valid or (saturated) overflow */)
    {
        printf( "Current power: %li kW (%li PS), %i Nm at %i rpm\n"
              , power / 1000
              , power / 735
              , torque
              , speedOfRotation
              );
    }
    else
        printf("Current power currently not available due to CAN transmission problems\n");
#endif

} /* End of loop */




