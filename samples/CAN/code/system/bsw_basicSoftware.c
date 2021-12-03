/**
 * @file bsw_basicSoftware.c
 * This is the top level implementation file of the operating system. It configures and
 * starts the real time kernel and sets up and provides all interfaces with the application
 * code.\n
 *   All of the code here and down here belongs to the trusted sphere. It is run in
 * supervisor mode and has the highest quality assurance level defined for the parts of the
 * aimed software.
 *
 * Copyright (C) 2020-2021 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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
 *   bsw_osCbOnCANRx_CAN_0
 *   bsw_osCbOnCANRx_CAN_1
 *   bsw_osCbOnCANRx_CAN_2
 *   bsw_osCbOnCANRx_CAN_3
 *   main
 *   startSecondaryCore
 *   main
 * Local functions
 *   cbOnCANRx
 */

/*
 * Include files
 */

#include "bsw_basicSoftware.h"

#include <string.h>
#include <assert.h>

#include "typ_types.h"
#include "ccl_configureClocks.h"
#include "xbs_crossbarSwitch.h"
#include "siu_siuPortDriver.h"
#include "dma_dmaDriver.h"
#include "sio_serialIO.h"
#include "rtos.h"
#include "gsl_systemLoad.h"
#include "lbd_ledAndButtonDriver.h"
#include "sio_serialIO.h"
#include "stm_systemTimer.h"
#include "cdr_canDriverAPI.h"
#include "pwm_pwmIODriver.h"

/*
 * Defines
 */

/* Check consistency of exported CAN bus enumeration with actual enumeration used in the
   CAN driver. */
_Static_assert( true
#if CDR_ENABLE_USE_OF_CAN_0 == 1
                &&  BSW_CAN_BUS_0 == cdr_canDev_CAN_0
#elif defined(BSW_CAN_BUS_0)
# error Inconsistency between API and implementation
#endif
#if CDR_ENABLE_USE_OF_CAN_3 == 1
                &&  BSW_CAN_BUS_1 == cdr_canDev_CAN_1
#elif defined(BSW_CAN_BUS_1)
# error Inconsistency between API and implementation
#endif
#if CDR_ENABLE_USE_OF_CAN_2 == 1
                &&  BSW_CAN_BUS_2 == cdr_canDev_CAN_2
#elif defined(BSW_CAN_BUS_2)
# error Inconsistency between API and implementation
#endif
#if CDR_ENABLE_USE_OF_CAN_1 == 1
                &&  BSW_CAN_BUS_3 == cdr_canDev_CAN_3
#elif defined(BSW_CAN_BUS_3)
# error Inconsistency between API and implementation
#endif
              , "Inconsistency between API and implementation"
              );


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
    /** Timer event to clock regular 1ms tasks. */
    idEv1ms = 0,

    /** Timer event to clock regular 10ms tasks. */
    idEv10ms,

    /** Timer event to clock regular 100ms tasks. */
    idEv100ms,

    /** Timer event to clock regular 1s tasks. */
    idEv1000ms,

    /** The number of tasks to register. */
    noRegisteredEvents
};


/** The RTOS uses constant priorities for its events, which are defined here.\n
      Note, the priority is a property of an event rather than of a task. A task implicitly
    inherits the priority of the event it is associated with. */
enum
{
    prioEv1ms = 1,
    prioEv10ms,
    prioEv100ms,
    prioEv1000ms,

    prioHighestForApplTasks = prioEv1000ms,
};



/*
 * Local prototypes
 */


/*
 * Data definitions
 */

/** The average CPU load produced by all tasks and interrupts in tens of percent. Can be
    read at any time by any context on any core. */
unsigned int UNCACHED_OS(bsw_cpuLoad) = 1000;


/*
 * Function implementation
 */

/**
 * This is the common portion of code for all CAN devices of the CAN RX FIFO callbacks from
 * the CAN driver. It receives the Rx data and forwards it to the application code in user
 * process \a bsw_pidUser.
 *   @param idxCanBus
 * The zeror based index of the receiving bus among all configured buses.
 *   @param hMB
 * The handle of the message as agreed on at message registration time is returned to
 * support a simple association of the Rx event with the transmitted data content.
 *   @param sizeOfPayload
 * The number of received content bytes. This number of bytes may be read via \a payload.
 *   @param payload
 * The received payload by reference.
 *   @remark
 * This function is called from one of the CAN device's interrupt contexts. The IRQ
 * priority is #CDR_IRQ_PRIO_CAN_RX for all (non polled) RX messages. It is executed
 * in supervisor mode. All Rx interrupts share this callback, so it needs to be reentrant
 * if two of them shouldn't have the same interrupt priority.
 */
static void cbOnCANRx( unsigned int idxCanBus
                     , unsigned int hMB
                     , unsigned int sizeOfPayload
                     , const uint8_t payload[8]
                     )
{
    /* The callback into a user process can take only a single (pojnter) argument. We need
       to pack all information into a struct so that we can provide its address to the user
       code. This pointer operation is uncritical with respect to our safety concept since
       the user code only needs read access. We can simply put the stuct here on our
       stack. */
    assert(hMB >= BSW_IDX_FIRST_RX_MAILBOX  &&  hMB <= BSW_IDX_LAST_RX_MAILBOX);
    const bsw_rxCanMessage_t rxCanMessage = { .idxCanBus = idxCanBus
                                            , .idxMailbox = hMB
                                            , .payload = payload
                                            , .sizeOfPayload = sizeOfPayload
                                            };

    /* Propagate the information into the user code in a way, which cannot violate the
       execution of the OS code. We catch all exceptions and we limit the execution time to
       avoid deadlocks. The time budget needs to consider preemptions b interrupts of
       higher priority and should not be too narrow. */
    static const rtos_taskDesc_t RODATA(userTaskConfig) =
                                            { .addrTaskFct = (uintptr_t)bsw_onRxCan
                                            , .tiTaskMax = RTOS_TI_US2TICKS(200u /* us */)
                                            , .PID = bsw_pidUser
                                            };
    rtos_osRunTask(&userTaskConfig, /* taskParam */ (uintptr_t)&rxCanMessage);

} /* End of cbOnCANRx */




/**
 * This is the callback from the CAN driver of the CAN RX FIFO of a single CAN device. It
 * receives the Rx data and forwards it to the common part of all the callbacks,
 * cbOnCANRx().
 *   @param hMB
 * The handle of the message as agreed on at message registration time is returned to
 * support a simple association of the Rx event with the transmitted data content.
 *   @param isExtId
 * Standard and extended CAN IDs partly share the same space of numbers. Hence, we need the
 * additional Boolean information, which of the two the ID \a canId belongs to.
 *   @param canId
 * The standard or extended ID of the transmitted CAN message.
 *   @param sizeOfPayload
 * The number of received content bytes. This number of bytes may be read via \a payload.
 *   @param payload
 * The received payload by reference.
 *   @param timeStamp
 * The time of completing the transmission of the message is recorded by hardware and the
 * value is forwarded to the callback. The absolute value has not meaning, time-base is a
 * free running 16 Bit counter. The frequency of the timer is the CAN bit rate; having a
 * bus with 500 kBd the unit of the timer would be 2µs. The timer wraps around at 2^16-1.
 *   @remark
 * This function is called from one of the CAN device's interrupt contexts. The IRQ
 * priority is #CDR_IRQ_PRIO_CAN_RX for all (non polled) RX messages. It is executed
 * in supervisor mode. All Rx interrupts share this callback, so it needs to be reentrant
 * if two of them shouldn't have the same interrupt priority.
 */
#define bsw_osCbOnCANRxCanN(dev)                                        \
void bsw_osCbOnCANRx_##dev( unsigned int hMB                            \
                          , bool isExtId ATTRIB_UNUSED                  \
                          , unsigned int canId ATTRIB_UNUSED            \
                          , unsigned int sizeOfPayload                  \
                          , const uint8_t payload[8]                    \
                          , unsigned int timeStamp ATTRIB_UNUSED        \
                          )                                             \
{                                                                       \
    cbOnCANRx(cdr_canDev_##dev, hMB, sizeOfPayload, payload);           \
}

#if CDR_ENABLE_USE_OF_CAN_0 == 1
bsw_osCbOnCANRxCanN(CAN_0)
#endif
#if CDR_ENABLE_USE_OF_CAN_1 == 1
bsw_osCbOnCANRxCanN(CAN_1)
#endif
#if CDR_ENABLE_USE_OF_CAN_2 == 1
bsw_osCbOnCANRxCanN(CAN_2)
#endif
#if CDR_ENABLE_USE_OF_CAN_3 == 1
bsw_osCbOnCANRxCanN(CAN_3)
#endif
#undef bsw_osCbOnCANRxCanN




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

    /* The interrupt controller is configured. This is the first driver initialization
       call: Many of the others will register their individual ISRs and this must not be
       done prior to initialization of the interrupt controller. */
    rtos_osInitINTCInterruptController();

    /* Start the system timers STM for execution time measurement.
         Caution: On the MPC5748G, this is not an option but an essential prerequisite for
       running safe-RTOS. The MPC5748G has a simplified z4 core without the timebase
       feature. The system timer is used as substitute. The driver needs to be started and
       it must be neither changed nor re-configured without carefully double-checking the
       side-effects on the kernel! */
    stm_osInitSystemTimers();

    /* Initialize the port driver. This should come early; most typical, many other I/O
       drivers will make use of pins and ports and therefore depend on the the port
       driver. */
    siu_osInitPortDriver();

    /* Initialize the DMA driver. This driver needs to be initialized prior to any other
       I/O driver, which makes use of a DMA channel. */
    dma_osInitDMADriver();

    /* Initialize the button and LED driver for the eval board. Shape access to the eight
       user LEDs and two user buttons. */
    lbd_osInitLEDAndButtonDriver( /* onButtonChangeCallback_core0 */ NULL//onButtonChangeCallback
                                , /* PID_core0 */                    0
                                , /* onButtonChangeCallback_core1 */ NULL
                                , /* PID_core1 */                    0
                                , /* onButtonChangeCallback_core2 */ NULL
                                , /* PID_core2 */                    0
                                , /* tiMaxTimeInUs */                1000
                                );

    /* Initialize the serial output channel as prerequisite of using printf. */
    sio_osInitSerialInterface(/* baudRate */ 115200);

    /* Initialize the CAN driver. */
    cdr_osInitCanDriver();

    /* Initialize the PWM driver. */
    pwm_osInitIODriver();

#if 0
    /* After HW initialization, we can start the other cores. Note, there's no guarantee in
       which time order they will arrive in their main. */
    startSecondaryCore(/* idxCore */ 1 /* Z4B */, mzb_main_Z4B);
    startSecondaryCore(/* idxCore */ 2 /* Z2 */, mzt_main_Z2);
#endif

#if 0
    /* Demonstrate the use of the serial interface. Note, the function is never blocking
       and we have left it for a long time before the characters are visible in the console
       window. Never blocking: If the buffer has not enough space then an according number
       of characters is dropped rather than the function waiting for the buffer becoming
       empty. */
    #define GREETING                                                                    \
      "DEVKIT-MPC5748G - CAN Demo  Copyright (C) 2020  Peter Vranken\r\n"               \
      "This program comes with ABSOLUTELY NO WARRANTY"                                  \
        /* "; for details type `show w'." */ "\r\n"                                     \
      "This is free software, and you are welcome to redistribute it"                   \
        /* "\r\nunder certain conditions; type `show c' for details" */ ".\r\n"
    sio_osWriteSerial(GREETING, /* noBytes */ sizeof(GREETING)-1);
    #undef GREETING
    #ifdef DEBUG
    sio_osWriteSerial(SIO_STR(Configuration: DEBUG));
    #else
    sio_osWriteSerial(SIO_STR(Configuration: PRODUCTION));
    #endif
#endif

    /* Register the process initialization tasks. They are located in the application code. */
    bool initOk = true;
    if(rtos_osRegisterInitTask( bsw_taskUserInit
                              , bsw_pidUser
                              , /* tiTaskMaxInUS */ BSW_TI_INIT_TASK_MAX_IN_US
                              )
       != rtos_err_noError
      )
    {
        initOk = false;
    }
    if(rtos_osRegisterInitTask( bsw_taskSafetyInit
                              , bsw_pidSafety
                              , /* tiTaskMaxInUS */ BSW_TI_INIT_TASK_MAX_IN_US
                              )
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
    #define CREATE_REGULAR_EVENT(tiInMs, tiFirstInMs)                                       \
    {                                                                                       \
        if(initOk                                                                           \
           && rtos_osCreateEvent                                                            \
                    ( &idEvent                                                              \
                    , /* tiCycleInMs */              (tiInMs)                               \
                    , /* tiFirstActivationInMs */    (tiFirstInMs)                          \
                    , /* priority */                 prioEv##tiInMs##ms                     \
                    , /* minPIDToTriggerThisEvent */ RTOS_EVENT_NOT_USER_TRIGGERABLE        \
                    , /* taskParam */                0                                      \
                    )                                                                       \
           != rtos_err_noError                                                              \
          )                                                                                 \
        {                                                                                   \
            initOk = false;                                                                 \
        }                                                                                   \
        else                                                                                \
            assert(idEvent == idEv##tiInMs##ms);                                            \
                                                                                            \
    } /* CREATE_REGULAR_EVENT */

    #define CREATE_USER_TASK(idEv, pid, taskFct)                                            \
        CREATE_TASK(rtos_osRegisterUserTask( (idEv)                                         \
                                           , (taskFct)                                      \
                                           , (pid)                                          \
                                           , /* tiTaskMaxInUs */ 0                          \
                                           )                                                \
                   )

    #define CREATE_OS_TASK(idEv, taskFct) CREATE_TASK(rtos_osRegisterOsTask((idEv), (taskFct)))

    #define CREATE_TASK(rtosApiCall)                                                        \
    {                                                                                       \
        if(initOk &&  (rtosApiCall) != rtos_err_noError)                                    \
            initOk = false;                                                                 \
    } /* CREATE_TASK */

    CREATE_REGULAR_EVENT(/* tiInMs */ 1, /* tiFirstInMs */ 0)
    CREATE_REGULAR_EVENT(/* tiInMs */ 10, /* tiFirstInMs */ 1)
    CREATE_REGULAR_EVENT(/* tiInMs */ 100, /* tiFirstInMs */ 5)
    CREATE_REGULAR_EVENT(/* tiInMs */ 1000, /* tiFirstInMs */ 55)

    /* OS task are created first. This ensures that they will get the CPU first when the
       triggering event is shared with user tasks. */
    //CREATE_OS_TASK(idEv1ms, bsw_taskOs1ms)
    //CREATE_OS_TASK(idEv10ms, bsw_taskOs10ms)
    //CREATE_OS_TASK(idEv100ms, bsw_taskOs100ms)
    //CREATE_OS_TASK(idEv1000ms, bsw_taskOs1000ms)

    /* User tasks in the safety process are created next. This ensures that they will get
       the CPU prior to the QM tasks in user process bsw_pidUser. */
    CREATE_USER_TASK(idEv1ms, bsw_pidSafety, bsw_taskSafety1ms)
    CREATE_USER_TASK(idEv10ms, bsw_pidSafety, bsw_taskSafety10ms)

    /* User tasks in the QM process are created last. They will be served latest when the
       triggering event is shared with OS or safety tasks. */
    CREATE_USER_TASK(idEv1ms, bsw_pidUser, bsw_taskUser1ms)
    CREATE_USER_TASK(idEv10ms, bsw_pidUser, bsw_taskUser10ms)
    CREATE_USER_TASK(idEv100ms, bsw_pidUser, bsw_taskUser100ms)
    CREATE_USER_TASK(idEv1000ms, bsw_pidUser, bsw_taskUser1000ms)

    /* The last check ensures that we didn't forget to register an event. */
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
        bsw_cpuLoad = gsl_osGetSystemLoad();

    } /* End of infinite idle loop of RTOS. */

    /* We never get here. Just to avoid a compiler warning. */
    return -1;

} /* End of main */

