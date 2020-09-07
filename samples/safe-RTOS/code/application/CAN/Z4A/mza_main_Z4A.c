/**
 * @file mza_main_Z4A.c
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
 *   main
 * Local functions
 *   taskInitProcess
 *   task1ms
 *   taskOs1ms
 *   startSecondaryCore
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
#include "cdr_canDriver.h"
#include "mza_main_Z4A.h"


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
    pidTask1ms = 1,
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
volatile unsigned long SBSS_OS(mai_cntTaskIdle) = 0;

/** Counter of cyclic 1ms user task. */
volatile unsigned long long SBSS_P1(mai_cntTask1ms) = 0;  

/** Counter of cyclic 1ms OS task. */
volatile unsigned long long SBSS_OS(mai_cntTaskOs1ms) = 0;

/** The average CPU load produced by all tasks and interrupts in tens of percent. */
unsigned int DATA_OS(mai_cpuLoad) = 1000;

/** Interface with assembly code: Here's a variable in the assembly startup code, which
    takes the addresses of the C main function to be invoked on core Z4B. It needs to be
    initialized prior to starting the core. Z4B and Z2 may use the same function.
      @todo Why can't we place the declaration locally into the function where it is used?
    The compiler rejects it due to the section attribute. */
extern void (*volatile SECTION(.bss.startup) sup_main_Z4B)(signed int, const char **);

/** Interface with assembly code: Here's a variable in the assembly startup code, which
    takes the addresses of the C main function to be invoked on core Z2. It needs to be
    initialized prior to starting the core. Z4B and Z2 may use the same function. */
extern void (*volatile SECTION(.bss.startup) sup_main_Z2)(signed int, const char **);


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
    static unsigned int SHARED(cnt_) = 0;
    ++ cnt_;

//    /* Only process 1 has access to the C lib (more precise: to those functions of the C
//       lib, which write to lib owned data objects) and can write a status message. */
//    if(PID == 1)
//        iprintf("taskInitPID%lu(): %u\r\n", PID, cnt_);

    return cnt_ == PID? 0: -1;

} /* End of taskInitProcess */



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
    ++ mai_cntTask1ms;

#if TASKS_PRODUCE_GROUND_LOAD == 1
    /* Produce a bit of CPU load. This call simulates some true application software. */
    del_delayMicroseconds(/* fullLoadThisNoMicroseconds */ 50 /* approx. 5% load */);
#endif

    static int SBSS_P1(cntIsOn_) = 0;
    if(++cntIsOn_ >= 500)
    {
        cntIsOn_ = -500;
        printf("This is call %llu of task1ms\r\n", mai_cntTask1ms);
    }
    lbd_setLED(lbd_led_0_DS11, /* isOn */ cntIsOn_ >= 0);

    /* Inject some errors. */
    if((mai_cntTask1ms & 0x3ff) == 0)
    {
        static volatile unsigned int DATA_P2(foreignData) ATTRIB_UNUSED;
        foreignData = (unsigned int)mai_cntTask1ms;
    }
    if((mai_cntTask1ms & 0x7ff) == 1)
    {
        struct rtos_kernelInstanceData_t;
        static volatile const struct rtos_kernelInstanceData_t *pInstance ATTRIB_UNUSED;
        extern const struct rtos_kernelInstanceData_t *rtos_getInstancePtr(void);
        pInstance = rtos_getInstancePtr();
        static volatile uint8_t DATA_P1(coreId) ATTRIB_UNUSED;
        coreId = rtos_osGetIdxCore();
    }

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
    ++ mai_cntTaskOs1ms;

    /** Regularly called step function of the I/O driver. */
    lbd_osTask1ms();

#if TASKS_PRODUCE_GROUND_LOAD == 1
    /* Produce a bit of CPU load. This call simulates some true application software. */
    del_delayMicroseconds(/* fullLoadThisNoMicroseconds */ 75 /* approx. 7.5% load */);
#endif

    /* Test button input: The current status is echoed as LED status. */
    lbd_osSetLED(lbd_led_7_DS4,  /* isOn */ lbd_osGetButton(lbd_bt_button_SW2));
              
    static int SBSS_P1(cntIsOn_) = 0;
    if(++cntIsOn_ >= 500)
    {
        cntIsOn_ = -500;

        printf("This is call %llu of taskOs1ms\r\n", mai_cntTaskOs1ms);
    }
    lbd_osSetLED(lbd_led_1_DS10, /* isOn */ cntIsOn_ >= 0);
    
    /// @todo Temoprily used only: Send a CAN message.
    if((mai_cntTaskOs1ms % 10) == 1)
        cdr_osTestSend_task10ms();

} /* End of taskOs1ms */



#if 0
/**
 * Start a secondary core. The initial core is already started and it is the one, which will
 * execute this function. Never call the function from another core than Z4A.
 *   @param idxCore
 * Which core to start? Permitted indexes are 1 for the Z4B core and 2 for the Z2 core.
 *   @param main
 * The main function to be used for the secondary core. Although it might be tempting to
 * have one and the same main function for all cores, the normal function main must not be
 * passed: The compiler generates special code on entry into C's main() to initialize the C
 * runtime. If C's main() is called for more than a single core then this initializtaion
 * happens repeatedly and maybe even coincidentally; either of this can make the runtime
 * fail.
 */
static void startSecondaryCore( unsigned int idxCore
                              , void (*main)(signed int, const char *[])
                              )
{
    /* The entry point into the C code cannot be the normal main function for the other
       cores. The C compiler unconditionally generates the call of the C run time
       initialization as part of the machine code that implements the entry into main. We
       must of course not execute this initialization three times. Instead, we pass the
       main function for the other cores explicitly to the startup code. Although this
       effectively is cross-core communication we don't have any issues with it; the other
       core is not yet running, has not filled any data into its cache and the output write
       buffers of the Z4A core, which executes this code here will be written through its
       cache into external memory long before the other core actually reaches the location
       in the startup code where the function pointer is read. */

    /* Interface with assembly startup code. (There's no header file for the assembly
       startup code.): The entry point into code execution after reset. Common for all
       three cores. */
    extern void _Noreturn sup_startUp(void);
    
    /* Prepare core start: Enter code start address and set allowed run modes. */
    switch(idxCore)
    {
    case 1 /* Z4B */:
        /* Pass the pointer to the C code entry to the assembly startup code being executed
           on the other core. Note, all core use the same startup code. This code is
           conditionally in that it reads a core dependent address of the C main function
           to use. */
        sup_main_Z4B = main;
        std_fullMemoryBarrier();

        /* RM 38.3.91, p. 1209: The core is enabled in all run modes. Caution, the RM names
           the three cores 1, 2 and 3, while in SW (as the argument of this function does)
           we normally count from zero. */
        MC_ME->CCTL2 = 0x00fc;

        /* RM, 38.3.94, p. 1214: Reset vector for core 1. Why do we need to set this
           vector? It had already been entered in the boot sector, the BAF. */
        MC_ME->CADDR2 = (uint32_t)sup_startUp | MC_ME_CADDR2_RMC(1);

        break;

    case 2 /* Z2 */:
        /* Pass the pointer to the C code entry to the assembly startup code being executed
           on the other core. See case Z4B for details. */ 
        sup_main_Z2 = main;
        std_fullMemoryBarrier();

        /* RM 38.3.92, p. 1211: The core is enabled in all run modes. */
        MC_ME->CCTL3 = 0x00fc;

        /* RM, 38.3.95, p. 1215: Reset vector for core 2. */
        MC_ME->CADDR3 = (uint32_t)sup_startUp | MC_ME_CADDR3_RMC(1);

        break;

    default:
        /* Core 0 is always running and there are no other cores on this hardware. */
        assert(false);
    }

    /* RM 38.3.94: Another core is started on the next run mode change. We trigger a
       transition from DRUN to DRUN. On return from this function call, the other core is
       running in parallel. */
    ccl_triggerTransitionToModeDRUN();

} /* End of startSecondaryCore */
#endif


/**
 * C entry function main. Is used for and only for Z4A core.
 *   @return
 * Actually, the function is a _Noreturn. We don't declare it as such in order to avoid a
 * compiler warning. 
 *   @param noArgs
 * Number of arguments in \a argAry. Is actually always equal to one.
 *   @param argAry
 * Array of string arguments to the function. Actually, always a single string which equals
 * the name of the core, which is started.
 */
int /* _Noreturn */ main(int noArgs ATTRIB_DBG_ONLY, const char *argAry[] ATTRIB_DBG_ONLY)
{
    assert(noArgs == 1  && strcmp(argAry[0], "Z4A") == 0);

    /* Complete the core HW initialization - as far as not yet done by the assembly startup
       code. */
    
    /* All clocks run at full speed, including all peripheral clocks. */
    ccl_configureClocks();          
    
    /* Interrupts become usable and configurable by SW. */
    rtos_osInitINTCInterruptController();
    
    /* Configuration of cross bars: All three cores need efficient access to ROM and RAM.
       By default, the cores generally have strictly prioritized access to all memory slave
       ports in order Z4A, I-Bus, Z4A, D-Bus, Z4B, I-Bus, Z4B, D-Bus, Z2, I-Bus, Z2, D-Bus.
       While not optimal it is at least acceptable for most ports - with the exception of
       slave port 3 of cross bar 0: This port is the only path for the D buses of Z4B and
       Z2 (see RM, 16.1.1, table 16-1, p. 409) and Z2 suffers from starvation if Z4B is
       heavily transferring data. This can happen in our example, where all cores are
       spinning in a tiny loop to increment some counters in RAM. The minimum action to
       take is setting this port to round robin arbitration. */
    xbs_configCrossbarSwitch(/* isZ2IOCore */ true);

    /* The core is now running in the desired state. I/O driver initialization follows to
       the extend required by this simple sample. */
    
    /* Start the system timers for execution time measurement.
         Caution: On the MPC5748G, this is not an opton but an essential prerequisite for
       running safe-RTOS. The MPC5748G has a simplified z4 core without the timebase
       feature. The system timer is used as substitute. The driver needs to be started and
       it must be neither changed nor re-configured without carefully double-checking the
       side-effects on the kernel! */
    stm_osInitSystemTimers();
    
    /* Initialize the button and LED driver for the eval board. Shape access to the eight
       user LEDs and two user buttons. */
    lbd_osInitLEDAndButtonDriver( /* onButtonChangeCallback_core0 */ onButtonChangeCallback
                                , /* PID_core0 */                    1
                                , /* onButtonChangeCallback_core1 */ NULL
                                , /* PID_core1 */                    0
                                , /* onButtonChangeCallback_core2 */ NULL
                                , /* PID_core2 */                    0   
                                , /* tiMaxTimeInUs */                1000
                                );

    /* Initialize the serial output channel as prerequisite of using printf. */
    sio_osInitSerialInterface(/* baudRate */ 115200);

    /* Initialze the CAN driver. */
    cdr_osInitCanDriver();

    /* Route the CLOCKOUTs 0 and 1 from the clock generation module to the external pins
       PG7 and PG6, respectively. They are available at connector J3-16 and J3-14. The
       devided core clocks should be visible as a 10 and a 2 MHz signal. */
    SIUL2->MSCR[103 /* PG7 */] =
                SIUL2_MSCR_SSS(3)   /* CLOCKOUT0 */
                | SIUL2_MSCR_SRC(3) /* Slew rate: Full drive without SR control */
                | SIUL2_MSCR_OBE(1) /* Enable output buffer */
                | SIUL2_MSCR_ODE(0) /* Disable open drain, drive both edges */
                | SIUL2_MSCR_SMC(1) /* Safe mode as after reset */
                | SIUL2_MSCR_APC(0) /* No analog I/O */
                | SIUL2_MSCR_IBE(0) /* Disable input buffer */
                | SIUL2_MSCR_HYS(1) /* Hysteresis as after reset */
                | SIUL2_MSCR_PUE(0) /* Pull up/down is disabled */
                | SIUL2_MSCR_PUS(0) /* Pull up/down doesn't care, is disabled */
                ;
    SIUL2->MSCR[102 /* PG6 */] =
                SIUL2_MSCR_SSS(3)   /* CLOCKOUT1 */
                | SIUL2_MSCR_SRC(3) /* Slew rate: Full drive without SR control */
                | SIUL2_MSCR_OBE(1) /* Enable output buffer */
                | SIUL2_MSCR_ODE(0) /* Disable open drain, drive both edges */
                | SIUL2_MSCR_SMC(1) /* Safe mode as after reset */
                | SIUL2_MSCR_APC(0) /* No analog I/O */
                | SIUL2_MSCR_IBE(0) /* Disable input buffer */
                | SIUL2_MSCR_HYS(1) /* Hysteresis as after reset */
                | SIUL2_MSCR_PUE(0) /* Pull up/down is disabled */
                | SIUL2_MSCR_PUS(0) /* Pull up/down doesn't care, is disabled */
                ;

#if 0
    /* After HW initialization, we can start the other cores. Note, there's no guarantee in
       which time order they will arrive in their main. */
    startSecondaryCore(/* idxCore */ 1 /* Z4B */, mzb_main_Z4B);
    startSecondaryCore(/* idxCore */ 2 /* Z2 */, mzt_main_Z2);
#endif

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

    /* The code down here becomes the idle task of the RTOS. We enter an infinite loop,
       where some background can be placed. */
    while(true)
    {
        /* Compute the average CPU load. Note, this operation lasts about 1s and has a
           significant impact on the cycling speed of this infinite loop. Furthermore, it
           measures only the load produced by the tasks and system interrupts but not that
           of the rest of the code in the idle loop. */
        mai_cpuLoad = gsl_osGetSystemLoad();

        char msg[128];
        const int noChar = sniprintf( msg, sizeof(msg)
                                    , "CPU load: %u%%\r\n"
                                    , (mai_cpuLoad+5)/10
                                    );
        assert((unsigned)noChar < sizeOfAry(msg));
        //sio_osWriteSerial(msg, (unsigned)noChar);
        sio_osWriteSerial(msg, (unsigned)noChar);

        static bool SBSS_OS(isOn_) = false;
        lbd_osSetLED(lbd_led_2_DS9, isOn_ = !isOn_);

        /* Make spinning of the idle task observable in the debugger. */
        ++ mai_cntTaskIdle;

        /* Supervisor code like an OS or the idle task must not use the C lib's I/O
           functions like printf because they go into a system call handler of class full,
           which is not permitted for use from supervisor code. */
        //sio_osWriteSerial(SIO_STR(Hello World!));
        sio_osWriteSerial("Hello World!\r\n", sizeof("Hello World!\r\n")-1);

    } /* End of inifinite idle loop of RTOS. */

    /* We never get here. Just to avoid a compiler warning. */
    return -1;

} /* End of main */
