#ifndef RTOS_INCLUDED
#define RTOS_INCLUDED
/**
 * @file rtos.h
 *
 * Public interface of safe-RTOS. The functions, which are published here as prototypes or
 * which are implemented here as inline functions, are intended for use. Most typical, an
 * operating system (sometimes called Basic Software) will be built on this interface.
 *
 * safe-RTOS application interface:
 *
 *   System configuration and initialization:
 *
 *     rtos_osCreateEvent
 *     rtos_osRegisterInitTask
 *     rtos_osRegisterUserTask
 *     rtos_osRegisterOSTask
 *     rtos_osInitINTCInterruptController
 *     rtos_osRegisterInterruptHandler
 *     rtos_osGrantPermissionRunTask
 *     rtos_osGrantPermissionSuspendProcess
 *     rtos_osInitKernel
 *   
 *   Control tasks and processes:
 *
 *     rtos_osTriggerEvent
 *     rtos_triggerEvent (inline)
 *     rtos_osRunTask (inline)
 *     rtos_runTask (inline)
 *     rtos_terminateTask (inline)
 *     rtos_osSuspendProcess
 *     rtos_suspendProcess (inline)
 * 
 *   Critical sections:
 *
 *     rtos_osSuspendAllInterrupts (inline)
 *     rtos_osResumeAllInterrupts (inline)
 *     rtos_osEnterCriticalSection (inline)
 *     rtos_osLeaveCriticalSection (inline)
 *     rtos_osSuspendAllTasksByPriority
 *     rtos_osResumeAllTasksByPriority
 *     rtos_suspendAllTasksByPriority
 *     rtos_resumeAllTasksByPriority
 * 
 *   System call interface: 
 *
 *     rtos_systemCall
 *     rtos_osSystemCallBadArgument
 *     rtos_checkUserCodeReadPtr (inline)
 *     rtos_checkUserCodeWritePtr
 *
 *   Query system state:
 *
 *     rtos_osGetIdxCore (inline)
 *     rtos_getIdxCore
 *     rtos_getCoreStatusRegister
 *     rtos_osGetAllInterruptsSuspended (inline)
 *     rtos_isProcessSuspended
 * 
 *   Diagnostic interface:
 *
 *     rtos_getNoActivationLoss
 *     rtos_getNoTotalTaskFailure
 *     rtos_getNoTaskFailure
 *     rtos_getStackReserve
 *
 * Copyright (C) 2017-2020 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>

#include "MPC5748G.h"
#include "typ_types.h"
#include "rtos.config.h"


/*
 * Defines
 */

/** The number of configured processes. The definition is not core specific -- processes
    are shared between cores.\n
      Although it looks like a matter of application dependent configuration, this is a
    fixed setting in our RTOS. We have the HW constraint of a limited number of memory
    region descriptors in MMU and MPU. Four processes can be comfortably supported with
    enough descriptors each. Having less regions per process is possible with reduced
    programming comfort and so we could have more processes even without changing the
    run-time code (i.e. implementation of dynamic change of regions). However, the aimed
    use cases of this RTOS, applications with higher safety integrity level, can be handled
    with two or three processes so that pre-configured four should always be fine.\n
      The big advantage of having a fixed number of processes is the avoidance of
    configuration changes. The MMU and MPU configuration would need changes on C code level
    and the linker script would need more or altered section filters.\n
      No using all pre-configured processes doesn't matter. Just use a process in a task
    specification or leave it. An unused process doesn't produce any overhead. */
#define RTOS_NO_PROCESSES           4

/** The number of cores in the MCU and the maximum number of cores that can run the RTOS.
    If an MCU derivative should have a deviating number of cores then a source code
    migration is required. This is not a variable configuration setting. */
#define RTOS_NO_CORES           3

/** This event ID is returned if creation of a new event is impossible. The ID is unusable,
    no task can be created specifying this event ID. */
#define RTOS_INVALID_EVENT_ID       (RTOS_MAX_NO_EVENTS)

/** Deadline monitoring for tasks is supported up to a task maximum execution time of this
    number of Microseconds: (2^31-1)*1e6/f_c, f_c is 80e6 (clock rate of STM timers).\n
      The macro denotes a technical limitation. It is not a configurable item and must not
    be changed. */
#define RTOS_TI_DEADLINE_MAX_IN_US  26843545

/** An RTOS event can normally be triggered by user tasks belonging to a process of
    sufficient privileges. See field \a minPIDToTriggerThisEvent of struct \a
    rtos_eventDesc_t. If it should not be accessible even by the process of highest
    privileges than #RTOS_EVENT_NOT_USER_TRIGGERABLE can be specified for \a
    minPIDToTriggerThisEvent. */
#define RTOS_EVENT_NOT_USER_TRIGGERABLE ((RTOS_NO_PROCESSES)+1u)

/** The number of different kinds of process errors, which let to task abortion. */
#define RTOS_NO_ERR_PRC                 13

/** The enumeration of different kinds of process errors, which lead to task abortion.\n
      Here: Process abort from user/scheduler. */
#define RTOS_ERR_PRC_PROCESS_ABORT      0

/** Kind of process error: Exception IVOR #1, Machine check, mostly memory protection. */
#define RTOS_ERR_PRC_MACHINE_CHECK      1

/** Kind of process error: Task exceeded deadline. */
#define RTOS_ERR_PRC_DEADLINE           2

/** Kind of process error: Exception IVOR #2 or #3, MMU storage error. */
#define RTOS_ERR_PRC_DI_STORAGE         3

/** Kind of process error: Task referred to invalid system call or an existing system call
    has been made with invalid arguments. */
#define RTOS_ERR_PRC_SYS_CALL_BAD_ARG   4

/** Kind of process error: Exception IVOR #5, Alignment. */
#define RTOS_ERR_PRC_ALIGNMENT          5

/** Kind of process error: Exception IVOR #6, mostly illegal instruction. */
#define RTOS_ERR_PRC_PROGRAM_INTERRUPT  6

/** Kind of process error: Exception IVOR #7, Book E FPU instructions. */
#define RTOS_ERR_PRC_FPU_UNAVAIL        7

/** Kind of process error: Exception IVOR #13, TBL data access mismatch. */
#define RTOS_ERR_PRC_TBL_DATA           8

/** Kind of process error: Exception IVOR #14, TBL instr access mismatch. */
#define RTOS_ERR_PRC_TBL_INSTRUCTION    9

/** Kind of process error: Exception IVOR #32, use of SPE instruction. */
#define RTOS_ERR_PRC_SPE_INSTRUCTION    10

/** Kind of process error: User code returned error code. */
#define RTOS_ERR_PRC_USER_ABORT         11

/** Kind of process error: Not yet in use, reserved for extensions. */
#define RTOS_ERR_PRC_RESERVED           12


/** Helper macro for I/O driver implementation. If the driver wants to declare a system
    call then it'll define RTOS_SYSCALL_TABLE_ENTRY_dddd to be
    #RTOS_SC_TABLE_ENTRY(addrOfFct, confClass), where \a dddd is the decimal representation
    of the system call index, \a addrOfFct is the address of the handler, which implements
    the system call, and \a confClass its conformance class.
      @param addrOfFct Address of handler implementation
      @param confClass One out of BASIC (see #RTOS_HDLR_CONF_CLASS_BASIC), SIMPLE (see
    #RTOS_HDLR_CONF_CLASS_SIMPLE) or FULL (see #RTOS_HDLR_CONF_CLASS_FULL) */
#define RTOS_SC_TABLE_ENTRY(addrOfFct, confClass)                       \
            { .addressOfFct = (uint32_t)addrOfFct                       \
            , .conformanceClass = RTOS_HDLR_CONF_CLASS_##confClass      \
            }

/** Helper for data initialization: Task time budgets are internally represented in STM
    counter ticks. Using this macro one can specify it more conveniently in Milliseconds.
    The macro just converts its argument from Milliseconds to clock ticks. */
/// @todo We need a compile-time consistency check of this macro that uses a literal. The check shall compare the macro with the "official" macros in module ccl_configureClocks
#define RTOS_TI_MS2TICKS(tiInMs) ((tiInMs)*80000u)

/** Helper for data initialization: Task time budgets are internally represented in STM(0)
    counter ticks. Using this macro one can specify it more conveniently in Microseconds. The
    macro just converts its argument from Microseconds to clock ticks. */
/// @todo We need a compile-time consistency check of this macro that uses a literal. The check shall compare the macro with the "official" macros in module ccl_configureClocks
#define RTOS_TI_US2TICKS(tiInUs) ((tiInUs)*80u)

/** Index of core Z4 A or value of read-only register PIR on this core and return value of
    function rtos_osGetIdxCore() if called from this core. */
#define RTOS_CORE_Z4A   0u

/** Index of core Z4 B or value of read-only register PIR on this core and return value of
    function rtos_osGetIdxCore() if called from this core. */
#define RTOS_CORE_Z4B   1u

/** Index of core Z2 or value of read-only register PIR on this core and return value of
    function rtos_osGetIdxCore() if called from this core. */
#define RTOS_CORE_Z2    2u

/** \cond Two nested macros are used to convert a constant expression to a string which can be
    used e.g. as part of some inline assembler code.\n
      If for example PI is defined to be (355/113) you could use STR(PI) instead of
    "(355/113)" in the source code. ARG2STR is not called directly. */
#define ARG2STR(x) #x
#define STR(x) ARG2STR(x)
/** \endcond */


/*
 * Global type definitions
 */

/** Type of a single interrupt service as registered with function
    rtos_osRegisterInterruptHandler(). */
typedef void (*rtos_interruptServiceRoutine_t)(void);


/** This enumeration collects the errors, which are recognized during system configuration
    and initialization. */
typedef enum rtos_errorCode_t
{
    rtos_err_noError = 0        /// Not an error, function cuceeded
    , rtos_err_tooManyEventsCreated /// Can't create no more than #RTOS_MAX_NO_EVENTS events
    , rtos_err_invalidEventPrio /// Priority needs to be in range [1; #RTOS_MAX_LOCKABLE_TASK_PRIORITY)
    , rtos_err_badEventTiming   /// Inconsistent or bad timing configuration stated for event
    , rtos_err_eventNotTriggerable  /// Bad configuration makes event unusable
    , rtos_err_configurationOfRunningKernel /// Attempt to (re-)configure a running kernel
    , rtos_err_badEventId       /// The ID of the event is invalid. No such event exists
    , rtos_err_badProcessId     /// The ID of the process is invalid. No such process exists
    , rtos_err_tooManyTasksRegistered   /// More than #RTOS_MAX_NO_TASKS registered
    , rtos_err_noEvOrTaskRegistered /// No event and/or no task defined at start of system
    , rtos_err_eventWithoutTask /// A useless event exists, which has no task to activate
    , rtos_err_badTaskFunction  /// Bad task function NULL specified
    , rtos_err_taskBudgetTooBig     /// Task budget greater than #RTOS_TI_DEADLINE_MAX_IN_US
    , rtos_err_initTaskRedefined /// Attempt to redefine an already defined initialization task
    , rtos_err_initTaskFailed /// Process initialization function failed or returned neg. value
    , rtos_err_prcStackInvalid  /// Configured stack misaligned or too small
    , rtos_err_taskBelongsToInvalidPrc  /// Task assigned to not configured process
    , rtos_err_highPrioTaskInLowPrivPrc /// Task of highest prio belongs to process of low privileges
    , rtos_err_runTaskBadPermission /// "Unsafe" permissions granted to rtos_runTask()
    , rtos_err_suspendPrcBadPermission/// "Unsafe" permissions granted to rtos_suspendProcess()

    , rtor_err_noErrorCodes

} rtos_errorCode_t;



/** Specification of a task function. Objects of this type are used internally by the
    scheduler for the regularly or event triggered user mode and OS tasks but also visibly
    by the client code, when running a user mode task using rtos_runTask(). */
typedef struct rtos_taskDesc_t
{
    /** Address of task function, which is run in user mode and with process ID \a PID.\n
          Note, the signature of a task function differs. An initialization task and a user
        mode task function can signal an error by return value, while a scheduled OS task
        function can't. A task function started with rtos_runTask() or with
        rtos_osRunTask() has a caller provided argument, which is not available to
        regularly scheduled tasks.\n
          In the assembler code, this field is addressed to by offset O_TCONF_pFct. */
    uintptr_t addrTaskFct;

    /** Time budget for the user task in ticks of TBL (i.e. 8.33ns). This budget is
        granted for each activation of the task. The budget relates to deadline monitoring,
        i.e. it is a world time budget, not an execution time budget.\n
          Macros #RTOS_TI_MS2TICKS and #RTOS_TI_US2TICKS can be used to state the time
        budget in Milli- or Mircoseconds.\n
          A value of zero means that deadline monitoring is disabled for the task.\n
          In the assembler code, this field is addressed to by offset O_TCONF_tiMax. */
    uint32_t tiTaskMax;

    /** The process ID of the userTask in the range 1..#RTOS_NO_PROCESSES (PID 0 is reserved
        for kernel operation). At the same time index into the array of process
        descriptors.\n
          In the assembler code, this field is addressed to by offset O_TCONF_pid. */
    uint8_t PID;

} rtos_taskDesc_t;


/*
 * Global data declarations
 */


/*
 * Global prototypes
 */

/** Creation of an event. The event can be cyclically triggering or software triggerd. */
rtos_errorCode_t rtos_osCreateEvent( unsigned int *pEventId
                                   , unsigned int tiCycleInMs
                                   , unsigned int tiFirstActivationInMs
                                   , unsigned int priority
                                   , unsigned int minPIDToTriggerThisEvent
                                   , uintptr_t taskParam
                                   );

/** Task registration for user mode or operating system initialization task. */
rtos_errorCode_t rtos_osRegisterInitTask( int32_t (*initTaskFct)(uint32_t PID)
                                        , unsigned int PID
                                        , unsigned int tiMaxInUs
                                        );

/** Task registration for scheduled user mode tasks. */
rtos_errorCode_t rtos_osRegisterUserTask( unsigned int idEvent
                                        , int32_t (*userModeTaskFct)( uint32_t PID
                                                                    , uintptr_t taskParam
                                                                    )
                                        , unsigned int PID
                                        , unsigned int tiMaxInUs
                                        );

/** Task registration for scheduled operating system tasks. */
rtos_errorCode_t rtos_osRegisterOSTask( unsigned int idEvent
                                      , void (*osTaskFct)(uintptr_t taskParam)
                                      );

/** Initialize the interrupt controller INTC. */
void rtos_osInitINTCInterruptController(void);

/** Install an interrupt service for a given I/O device. */
void rtos_osRegisterInterruptHandler( rtos_interruptServiceRoutine_t interruptServiceRoutine
                                    , unsigned int processorID
                                    , unsigned int vectorNum
                                    , unsigned int psrPriority
                                    , bool isPreemptable
                                    );

/** Grant permission to particular processes for using the service rtos_runTask(). */
void rtos_osGrantPermissionRunTask(unsigned int pidOfCallingTask, unsigned int targetPID);

/**
 * Operating system initialization function: Grant permissions for using the service
 * rtos_suspendProcess() to particular processes. By default, the use of that service is not
 * allowed.\n
 *   By principle, offering service rtos_suspendProcess() makes all processes vulnerable,
 * which are allowed as target for the service. A failing, straying process can always hit
 * some ROM code executing the system call with arbitrary register contents, which can then
 * lead to immediate task abortion in and suspension of an otherwise correct process.\n
 *   This does not generally break the safety concept, the potentially harmed process can
 * for example be anyway supervised by another, non-suspendable supervisory process.
 * Consequently, we can offer the service at least on demand. A call of this function
 * enables the service for a particular pair of calling process and targeted process.
 *   @param pidOfCallingTask
 * The tasks belonging to process with PID \a pidOfCallingTask are granted permission to
 * suspend another process. The range is 1 .. #RTOS_NO_PROCESSES, which is double-checked by
 * assertion.
 *   @param targetPID
 * The process with PID \a targetPID is suspended. The range is 1 .. maxPIDInUse-1, which is
 * double-checked later.
 *   @remark
 * It would break the safety concept if we permitted the process with highest privileges to
 * become the target of the service. This is double-checked not here (when it is not yet
 * defined, which particular process that will be) but as part of the RTOS startup
 * procedure; a bad configuration can therefore lead to a later reported run-time error.
 *   @remark
 * This function must be called from the OS context only. It is intended for use in the
 * operating system initialization phase. It is not reentrant. The function needs to be
 * called prior to rtos_osInitKernel().
 */
void rtos_osGrantPermissionSuspendProcess( unsigned int pidOfCallingTask
                                         , unsigned int targetPID
                                         );

/** Kernel initialization. */
rtos_errorCode_t rtos_osInitKernel(void);

/** Software triggered task activation. Can be called from OS context (incl. interrupts). */
bool rtos_osTriggerEvent(unsigned int idEvent, uintptr_t taskParam);

/** Enter critical section; partially suspend task scheduling. */
uint32_t rtos_osSuspendAllTasksByPriority(uint32_t suspendUpToThisTaskPriority);

/** Leave critical section; resume scheduling of tasks. */
void rtos_osResumeAllTasksByPriority(uint32_t resumeDownToThisTaskPriority);

/**
 * Priority ceiling protocol, partial scheduler lock: All tasks up to the specified task
 * priority level won't be served by the CPU. This function is intended for implementing
 * mutual exclusion of sub-sets of tasks: Call it with the highest priority of all tasks,
 * which should be locked, i.e. which compete for the resource or critical section to
 * protect. This may still lock other, not competing tasks, but at least all non competing
 * tasks of higher priority and the interrupt handlers will be served.\n
 *   To release the protected resource or to leave the critical section, call the
 * counterpart function rtos_resumeAllTasksByPriority(), which restores the original
 * task priority level.\n
 *   The priority can be raised only up to #RTOS_MAX_LOCKABLE_TASK_PRIORITY. An attempt to
 * raise it beyond this limit will lead to an #RTOS_ERR_PRC_SYS_CALL_BAD_ARG exception.\n
 *   Safety rationale: A user task cannot shape a critical section with the RTOS scheduler,
 * nor with the user task of priority above #RTOS_MAX_LOCKABLE_TASK_PRIORITY and nor with
 * an ISR. (The attempt to shape a critical section with a task above
 * #RTOS_MAX_LOCKABLE_TASK_PRIORITY is caught in DEBUG compilation, see
 * rtos_resumeAllTasksByPriority().) The intention is to inhibit a task from blocking a
 * safety task.
 *   @return
 * Get the task priority level at entry into this function (and into the critical section).
 * This priority level needs to be restored on exit from the critical section using system
 * call rtos_resumeAllTasksByPriority().
 *   @param suspendUpToThisPriority
 * \a suspendUpToThisPriority is the aimed task priority level. All tasks up to and
 * including this priority will be locked. They won't get the CPU until the priority level
 * is lowered again.
 *   @remark
 * The critical section shaped with this API from an user mode task guarantees mutual
 * exclusion with critical section code shaped with the other API
 * rtos_osSuspendAllTasksByPriority() from an OS task.
 *   @remark
 * To support the use case of nested calls of OSEK/VDX like GetResource/ReleaseResource
 * functions, this function compares the stated value to the current task priority level.
 * If \a suspendUpToThisPriority is less than the current value then the current value is
 * not altered. The function still returns the current value and the calling code doesn't
 * need to take care: It can unconditionally end a critical section with
 * rtos_resumeAllTasksByPriority() stating the returned task priority level value. (The
 * resume function will have no effect in this case.) This makes the OSEK like functions
 * usable without deep inside or full transparency of the priority levels behind the scene;
 * just use the pairs of Get-/ResumeResource, be they nested or not.
 *   @remark
 * The expense in terms of CPU consumption of using this function is significant enough to
 * better avoid nested pairs of Get-/ResumeResource. As long as all resource and task
 * relationships are static, it'll be possible to replace nested pairs of function calls
 * by a single one with combined, maximum priority.
 *   @remark
 * The use of this function to implement critical sections is usually quite static. For any
 * protected entity (usually a data object or I/O device) the set of competing tasks
 * normally is a compile time known. The priority level to set for entry into the critical
 * section is the maximum of the priorities of all tasks in the set. The priority level to
 * restore on exit from the critical section is the priority of the calling task. All of
 * this static knowledge would typically be put into encapsulating macros that actually
 * invoke this function. (OSEK/VDX like environments would use this function pair to
 * implement the GetResource/ReleaseResource concept.)
 *   @remark
 * The raised priority is implicitly restored at the end of the task. It is not possible to
 * consider this function a mutex, which can be acquired in one task activation and which
 * can be releases in an arbitrary later task activation or from another task.
 *   @remark
 * This function must be called from the user task context only. Any attempt to use it from
 * OS code will lead to a crash.
 */
uint32_t rtos_suspendAllTasksByPriority(uint32_t suspendUpToThisPriority);


/**
 * This function is called to end a critical section of code, which requires mutual
 * exclusion of two or more tasks. It is the counterpart of function
 * rtos_suspendAllTasksByPriority(), refer to that function for more details.\n
 *   The priority can be lowered only down to the initial task priority. An attempt to
 * lower it below the initial task priority will lead to an #RTOS_ERR_PRC_SYS_CALL_BAD_ARG
 * exception.
 *   @param resumeDownToThisPriority
 * All tasks above this task priority level are resumed again. All tasks up to and
 * including this task priority remain locked.\n
 *   The intended use of this function is to restore the priority level of a task after use
 * of a resource, which had been protected by an earlier call of the counterpart function
 * rtos_suspendAllTasksByPriority(). Normally, \a resumeDownToThisPriority will be set
 * to the value returned by the other function (or by a constant since this value is a
 * compile-time known in most use cases).
 *   @remark
 * To support the use case of nested calls of OSEK/VDX like GetResource/ReleaseResource
 * functions, this function compares the stated prioity value to the current priority
 * level. If \a resumeDownToThisPriority is greater than the current value then the current
 * value is not altered.
 *   @remark
 * It is impossible to shape a critical section with the safety task of priority above
 * #RTOS_MAX_LOCKABLE_TASK_PRIORITY and the attempt will always mean a functional error in
 * the design of the application code. To support debugging, this error is caught in DEBUG
 * compilation: Then the function throws a #RTOS_ERR_PRC_SYS_CALL_BAD_ARG exception if \a
 * resumeDownToThisPriority is greater than #RTOS_MAX_LOCKABLE_TASK_PRIORITY. In PRODUCTION
 * compilation, we have the normal behavior of silently ignoring attempts to actually raise
 * the priority.
 *   @remark
 * Besides the likely unwanted impact on the scheduling, it doesn't harm if a user task
 * calls rtos_suspendAllTasksByPriority() to raise the priority but doesn't lower it
 * later using this function. The effect of rtos_suspendAllTasksByPriority() will end
 * with the termination of the task. If a critical section is required at the end of a task
 * function it may even be advantageous to not call rtos_resumeAllTasksByPriority() in
 * order to save the overhead of the involved system call.
 *   @remark
 * Due to the task switch is can initiate, this function is implemented as a system call of
 * full conformance class and this means significant overhead. It should be applied with
 * care to for frequently aqcuired resources or for very short critical sections.\n
 *   Alternatives are: Look-free programming techniques or dedicated system calls for the
 * given purpose.
 *   @remark
 * This function must be called from the user task context only. Any attempt to use it from
 * OS code will lead to a crash.
 */
void rtos_resumeAllTasksByPriority(uint32_t resumeDownToThisPriority);


/**
 * System call; entry point into operating system function for user code.
 *   @return
 * The return value depends on the system call.
 *   @param idxSysCall
 * Each system call is identified by an index. The index is an unsigned integer. The number
 * is the index into system call descriptor table \a rtos_systemCallDescAry.\n
 *   See manual,
 * https://github.com/PeterVranken/TRK-USB-MPC5643L/blob/master/LSM/safe-RTOS-VLE/doc/manual/manual.pdf,
 * section System calls of RTOS, Table 1, p. 17, for a list of system calls offered by the
 * RTOS kernel. More system calls will be offered by your operating system, which builds on
 * this safe-RTOS, please refer to your device driver documentation.\n
 *   The further function arguments depend on the particular system call.
 *   @param ...
 * The remaining arguments are passed register based to the system call implementation.
 * "Register based" means that the number of arguments is restricted to 7 values of 8..32
 * Bit each or accordingly lesser arguments if 64 Bit arguments are in use that require
 * two registers each.
 *   @remark
 * It depends on the particular system call, which context this function may be called
 * from. Nearly all system calls will be restricted to be called from user code. Only a few,
 * like the assert function, are accessible from operating system code, too. Please, refer
 * to the documentation of the particular system call.
 *   @remark
 * The C signature for system calls is formally not correct. The assembly code, which
 * implements this function, only supports function arguments in CPU registers, which
 * limits the total number to eight. The ... stands for 0..7 arguments of up to 32 Bit. If
 * a system call function has more arguments or if it are 64 Bit arguments then the
 * assembly code may not propagate all arguments properly to the actually implementing
 * system call handler and the behavior will be undefined!
 */
uint32_t rtos_systemCall(uint32_t idxSysCall, ...);


/** Check if a pointer value is valid for writing in the context of a given process. */
bool rtos_checkUserCodeWritePtr(unsigned int PID, const void *address, size_t noBytes);

/**
 * C signature for an assembly code entry point, which ends a system call handler with user
 * task termination and counted process error. Must be used solely from within the
 * implementation of a system call and only if the abortion is due to a clear fault in the
 * calling user code.
 */
_Noreturn void rtos_osSystemCallBadArgument(void);


/** Get the current number of failed event triggers since start of the RTOS scheduler. */
unsigned int rtos_getNoActivationLoss(unsigned int idEvent);

/** Get the number of task failures counted for the given process since start of the kernel. */
unsigned int rtos_getNoTotalTaskFailure(unsigned int PID);

/** Get the number of task failures of given category for the given process. */
unsigned int rtos_getNoTaskFailure(unsigned int PID, unsigned int kindOfErr);

/** How many bytes of the stack area of a process are still unused on the calling core? */
unsigned int rtos_getStackReserve(unsigned int PID);

/** Kernel function to suspend a process. */
void rtos_osSuspendProcess(uint32_t PID);

/** Kernel function to read the suspend status of a process. */
bool rtos_isProcessSuspended(uint32_t PID);

/**
 *   @func rtos_getIdxCore
 * This function returns the contents of CPU read-only register PIR.
 *   @return
 * Get the index of the core the calling code is running on. The range is 0..2, meaning
 * Z4A, Z4B, Z2, respectively. (The convenience macros #RTOS_CORE_Z4A,  #RTOS_CORE_Z4B
 * and #RTOS_CORE_Z2 can be used.)
 *   @remark
 * This function may be called from all contexts. However, OS contexts shouldn't because of
 * the performance penalty. They should only use the intrinsic rtos_osGetIdxCore() instead.
 */
unsigned int rtos_getIdxCore(void);


/**
 *   @func rtos_getCoreStatusRegister
 * Get the value of the msr. This is an entry point to C code, which can be called from
 * supervisor and user mode.
 *   @return
 * Get the current contents of CPU register MSR on the code executing core.
 *   @remark
 * This function can be called from OS and user code. OS code should however better use an
 * intrinsic to read the MSR and in order to save the function call overhead.
 */
uint32_t rtos_getCoreStatusRegister(void);



/*
 * Inline functions
 */

/**
 * This function returns the content of the read-only CPU register PIR.
 *   @return
 * Get the zero based index of the core the calling code is excuted on. The range depends
 * on the derivative of the MCU.\n
 *   The convenience macros #RTOS_CORE_Z4A,  #RTOS_CORE_Z4B and #RTOS_CORE_Z2 can be used
 * to evaluate the function result.
 *   @remark
 * This function may be called from all supervisor contexts, i.e. OS tasks and ISRs. A call
 * from a user task will cause an exception.
 */
static inline unsigned int rtos_osGetIdxCore(void)
{
#define RTOS_SPR_PIR 286 /* SPR index of PIR. */

    uint32_t idxCore;
    asm volatile ( /* AssemblerTemplate */
                   "mfspr   %0, " STR(RTOS_SPR_PIR) "\n\t"
                 : /* OutputOperands */ "=r" (idxCore)
                 : /* InputOperands */
                 : /* Clobbers */
                 );
    return (unsigned int)idxCore;

} /* End of rtos_osGetIdxCore */



/**
 * Start a user task. A user task is a C function, which is executed in user mode and in a
 * given process context. The call is synchronous; the calling OS context is immediately
 * preempted and superseded by the started task. The calling OS context is resumed when the
 * task function ends - be it gracefully or by exception/abortion.\n
 *   The started task inherits the priority of the calling OS context. It can be preempted
 * only by contexts of higher priority.
 *   @return
 * The executed task function can return a value, which is propagated to the calling OS
 * context if it is positive. A returned negative task function result is interpreted as
 * failing task and rtos_osRunTask() returns #RTOS_ERR_PRC_USER_ABORT instead.
 * Furthermore, this event is counted as process error in the target process.
 *   @param pUserTaskConfig
 * The read-only configuration data for the task. In particular the task function pointer
 * and the ID of the target process.
 *   @param taskParam
 * This argument is meaningless to the function. The value is just passed on to the started
 * task function. The size is large enough to convey a pointer.
 *   @remark
 * This function must be called from the OS context only. Any attempt to use it in user
 * code will lead to a privileged exception.
 *   @remark
 * The function is intended to implement safe user code callbacks from interrupt events.
 * However, deadline monitoring fails for the task execution if the ISR, which makes use of
 * this API has a priority equal to or above the kernel priority
 * #RTOS_KERNEL_IRQ_PRIORITY_CORE_0 (or #RTOS_KERNEL_IRQ_PRIORITY_CORE_1, or
 * #RTOS_KERNEL_IRQ_PRIORITY_CORE_2, if the RTOS is running on core 1 or 2, respectively).
 * This would likely break the aimed safety concept; an infinite loop in the user code could
 * make the system hang. In most situations, a reasonable safety requirement will prohibit
 * the use of this function from any ISR with such a high priority.
 */
static inline int32_t rtos_osRunTask( const rtos_taskDesc_t *pUserTaskConfig
                                    , uintptr_t taskParam
                                    )
{
    /* The function is assembler implemented, the C function is just a wrapper for
       convenient calling within the expected namespace. Direct calling of the assembly
       code function is unwanted because of the name: In the assembler module the name "run
       user task" makes sense but for the user of the RTOS it doesn't: To him there is no
       distinction of starting either OS or user tasks, all tasks he knows are "user
       tasks". */
    extern int32_t rtos_osRunUserTask(const struct rtos_taskDesc_t *, uint32_t);
    return rtos_osRunUserTask(pUserTaskConfig, taskParam);

} /* End of rtos_osRunTask */



/**
 * Start a user task. A user task is a C function, which is executed in user mode and in a
 * given process context. The call is synchronous; the calling user context is immediately
 * preempted and superseded by the started task. The calling user context is resumed when the
 * task function ends - be it gracefully or by exception/abortion.\n
 *   The started task inherits the priority of the calling context. It can be preempted
 * only by contexts of higher priority.\n
 *   The function requires sufficient privileges. See rtos_osGrantPermissionRunTask() for
 * details. The task cannot be started in the OS context.\n
 *   The function cannot be used recursively. The created task cannot in turn make use of
 * rtos_runTask().
 *   @return
 * The executed task function can return a value, which is propagated to the calling user
 * context if it is positive. A returned negative task function result is interpreted as
 * failing task and rtos_runTask() returns #RTOS_ERR_PRC_USER_ABORT instead.
 * Furthermore, this event is counted as process error in the target process.
 *   @param pUserTaskConfig
 * The read-only configuration data for the task. In particular the task function pointer
 * and the ID of the target process.
 *   @param taskParam
 * This argument is meaningless to the function. The value is just passed on to the started
 * task function. The size is large enough to convey a pointer.
 *   @remark
 * This function must be called from a user process context only. Any attempt to use it in
 * supervisor code will lead to a crash.
 */
static inline int32_t rtos_runTask( const rtos_taskDesc_t *pUserTaskConfig
                                  , uintptr_t taskParam
                                  )
{
    #define RTOS_IDX_SC_RUN_TASK    4
    return (int32_t)rtos_systemCall(RTOS_IDX_SC_RUN_TASK, pUserTaskConfig, taskParam);

} /* End of rtos_runTask */



/**
 * End/abort the calling task immediately. A user task may use this system call at any time
 * and from any nested sub-routine. The task execution is immediately aborted. The function
 * does not return.
 *   @param taskReturnValue
 * The task can return a value to its initiator, i.e. to the context who had applied
 * rtos_osRunTask() or rtos_runTask() to create the task. The value is signed and (only)
 * the sign is meaningful to the assembly code to create/abort a task:\n
 *   The requested task abortion is considered an error and counted in the owning process
 * if the returned value is negative. In this case, the calling context won't receive the
 * value but the error code #RTOS_ERR_PRC_USER_ABORT.\n
 *   The requested task abortion is not considered an error if \a taskReturnValue is
 * greater or equal to zero. The value is propagated to the task creating context.
 *   @remark
 * If the function is called from inside a critical section, which had been started using
 * rtos_suspendAllTasksByPriority(), then the critical section is implicitly ended by
 * this function call.
 *   @remark
 * This function must be called from the user task context only. Any attempt to use it from
 * OS code will lead to a crash. There's no equivalent of this function for OS code. An OS
 * task can't be ended prematurely.
 */
static inline _Noreturn void rtos_terminateTask(int32_t taskReturnValue)
{
    extern _Noreturn void rtos_terminateUserTask(int32_t);
    rtos_terminateUserTask(taskReturnValue);

} /* End of rtos_terminateTask */



/**
 * Disable all External Interrupts. This is done unconditionally, there's no nesting
 * counter.
 *   @remark Note, suspending all External Interrupts does not affect all other interrupts
 * (effectively CPU traps), like Machine Check interrupt.
 *   @remark
 * This function must be called from the OS context only. Any attempt to use it in user
 * code will lead to a privileged exception.
 */
static ALWAYS_INLINE void rtos_osSuspendAllInterrupts(void)
{
    /* The completion synchronizing character of the wrteei instruction forms the memory
       barrier, which ensures that all memory operations before the now entered critical
       section are completed before we enter (see core RM, 4.6.1, p. 151). The "memory"
       constraint ensures that the compiler won't reorder instructions from behind the
       wrteei to before it. */
    asm volatile ( /* AssemblerTemplate */
                   "wrteei 0\n"
                 : /* OutputOperands */
                 : /* InputOperands */
                 : /* Clobbers */ "memory"
                 );
} /* End of rtos_osSuspendAllInterrupts */



/**
 * Enable all External Interrupts. This is done unconditionally, there's no nesting
 * counter.
 *   @remark
 * This function must be called from the OS context only. Any attempt to use it in user
 * code will lead to a privileged exception.
 *   @remark
 * This function can be called even from non safe-RTOS applications if they run in
 * supervisor mode.
 */
static ALWAYS_INLINE void rtos_osResumeAllInterrupts(void)
{
    /* The completion synchronizing character of the wrteei instruction forms the memory
       barrier, which ensures that all memory operations inside the now left critical
       section are completed before we leave (see core RM, 4.6.1, p. 151). The "memory"
       constraint ensures that the compiler won't reorder instructions from before the
       wrteei to behind it. */
    asm volatile ( /* AssemblerTemplate */
                   "wrteei 1\n"
                 : /* OutputOperands */
                 : /* InputOperands */
                 : /* Clobbers */ "memory"
                 );
} /* End of rtos_osResumeAllInterrupts */




/**
 * Get the current state of the MSR[EE] status bit.
 *   @return
 * Get \a true if the processing of External Interrupts is currently enabled and \a false
 * otherwise.
 *   @remark
 * This function must be used from OS tasks and ISRs only. Calling it from a user task will
 * cause a privileged instruction exception and an error is counted for the process.
 *   @remark
 * This function can be called even from non safe-RTOS applications if they run in
 * supervisor mode.
 */
static ALWAYS_INLINE bool rtos_osGetAllInterruptsSuspended(void)
{
    uint32_t msr;
    asm volatile ( /* AssemblerTemplate */
                   "mfmsr %0\n\t"
                 : /* OutputOperands */ "=r" (msr)
                 : /* InputOperands */
                 : /* Clobbers */ "memory"
                 );
    return (msr & 0x00008000) == 0;

} /* End of rtos_osGetAllInterruptsSuspended */



/**
 * Start the code of a critical section, thus code, which operates on data, that must not
 * be touched from another execution context at the same time.\n
 *   The critical section is implemented by globally disabling all interrupts.
 *   @return
 * The machine status register content of before disabling the interrupts is returned. The
 * caller will safe it and pass it back to rtos_osLeaveCriticalSection() at the end of the
 * critical section. This way the nestability is implemented.
 *   @remark
 * The main difference of this function in comparison to rtos_osSuspendAllInterrupts() is the
 * possibility to nest the calls at different hierarchical code sub-function levels.
 *   @remark
 * This function must be called from the OS context only. Any attempt to use it in user
 * code will lead to a privileged exception.
 *   @remark
 * This function can be called even from non safe-RTOS applications if they run in
 * supervisor mode.
 */
static ALWAYS_INLINE uint32_t rtos_osEnterCriticalSection(void)
{
    /* The completion synchronizing character of the mfmsr instruction forms the memory
       barrier, which ensures that all memory operations before the now entered critical
       section are completed before we enter (see core RM, 4.6.1, p. 151). The "memory"
       constraint ensures that the compiler won't reorder instructions from behind the
       wrteei to before it. */
    uint32_t msr;
    asm volatile ( /* AssemblerTemplate */
                   "mfmsr %0\n\t"
                   "wrteei 0\n\t"
                 : /* OutputOperands */ "=r" (msr)
                 : /* InputOperands */
                 : /* Clobbers */ "memory"
                 );
    return msr;

} /* End of rtos_osEnterCriticalSection */



/**
 * End the code of a critical section, thus code, which operates on data, that must not
 * be touched from another execution context at the same time.\n
 *   The critical section is implemented by globally disabling all interrupts.
 *   @param msr
 * The machine status register content as it used to be at entry into the critical section.
 * See rtos_osEnterCriticalSection() for more.
 *   @remark
 * This function must be called from the OS context only. Any attempt to use it in user
 * code will lead to a privileged exception.
 *   @remark
 * This function can be called even from non safe-RTOS applications if they run in
 * supervisor mode.
 */
static ALWAYS_INLINE void rtos_osLeaveCriticalSection(uint32_t msr)
{
    /* The completion synchronizing character of the wrtee instruction forms the memory
       barrier, which ensures that all memory operations inside the now left critical
       section are completed before we leave (see core RM, 4.6.1, p. 151). The "memory"
       constraint ensures that the compiler won't reorder instructions from before the
       wrtee to behind it. */
    asm volatile ( /* AssemblerTemplate */
                   "wrtee %0 /* Restore MSR[EE] */\n\t"
                 : /* OutputOperands */
                 : /* InputOperands */ "r" (msr)
                 : /* Clobbers */ "memory"
                 );
} /* End of rtos_osLeaveCriticalSection */



/**
 * Trigger an event to activate all associated tasks. A event, which had been registered
 * with cycle time zero is normally not executed. It needs to be triggered with this
 * function in order to make its associated tasks run once, i.e. to make its task functions
 * executed once as result of this call.\n
 *   This function must only be called from user tasks, which belong to a process with
 * sufficient privileges. The operation is permitted only for tasks belonging to those
 * processes, which have an ID that is greater of equal to the minimum specified for the
 * event in question. Otherwise an exception is raised, which aborts the calling task.\n
 *   If the calling task belongs to the set of tasks associated with \a idEvent, then it'll
 * have no effect but an accounted activation loss; an event can re-triggered only after
 * all associated activations have been completed. There is no activation queuing. The
 * function returns \a false in this case.\n
 *   Note, the system respects the priorities of the activated tasks. If a task of priority
 * higher than the activating task is activated by the triggered event then the activating
 * task is immediately preempted to the advantage of the activated task. Otherwise the
 * activated task is chained and executed after the activating task.
 *   @return
 * There is no activation queuing. Consequently, triggering the event can fail if at least
 * one of the associated tasks has not yet completed after the previous trigger of the
 * event. The function returns \a false and the activation loss counter of the event is
 * incremented. (See rtos_getNoActivationLoss().) In this situation, the new trigger is
 * entirely lost, i.e. none of the associated tasks will be activated by the new trigger.
 *   @param idEvent
 * The ID of the event to activate as it had been got by the creation call for that event.
 * (See rtos_osCreateEvent().)
 *   @param taskParam
 * All associated tasks will receive this value, when they are called because of this
 * trigger.\n
 *   The value is ignored if the function returns \a false.
 *   @remark
 * The function is indented to start a non cyclic task by application software trigger but
 * can be applied to cyclic tasks, too. In which case the task function of the cyclic task
 * would be invoked once additionally. Note, that an event activation loss is not unlikely
 * in this case; the cyclic task may currently be busy.
 *   @remark
 * It may look like an inconsistent API design if all associated tasks receive the same
 * value \a taskParam from the triggering event. The service could easily offer an API,
 * which provides an individual value to each associated task. The only reason not to do
 * so is the additional overhead in combination with the very few imaginable use cases.
 * In most cases an explicitly triggered event will have just one associated task; events
 * with more than one task will mostly be regular timer tasks, which make rarely use of the
 * task parameter.
 *   @remark
 * If \a idEvent addresses a regular, time triggered event and if triggering succeeds, then
 * the regular tasks will receive the passed value from now on. (Instead of the initial
 * value specified at event creation time, see rtos_osCreateEvent().) Note, there's likely
 * no use case for this, it's just a side effect of the implementation. However, it should
 * not do any harm, because mostly regular tasks don't make use of the task parameter and
 * mostly this service is not permitted for such events. If it could be harmful, e.g. if a
 * timer event exceptionally makes use of the task parameter, then explicit triggering of
 * the event using this service needs to be inhibitted.
 *   @remark
 * It is not forbidden but useless to let a task activate itself by triggering the event it
 * is associated with. This will have no effect besides incrementing the activation loss
 * counter for that event.
 *   @remark
 * This function must be called from the user task context only. Any attempt to use it from
 * OS code will lead to a crash.
 */
static inline bool rtos_triggerEvent(unsigned int idEvent, uintptr_t taskParam)
{
    #define RTOS_IDX_SC_TRIGGER_EVENT   3
    return (bool)rtos_systemCall(RTOS_IDX_SC_TRIGGER_EVENT, idEvent, taskParam);

} /* End of rtos_triggerEvent */


/**
 * Helper function, mainly intended to support safe system call handler implementation:
 * Check if a pointer value is valid for reading in the context of a given process.\n
 *   A system call handler must never trust a user code provided pointer; evidently not for
 * write access but not even for read operation (a read into the address space of
 * peripherals can have a side effect). The user code could make the system call handler
 * overwrite some non-process owned data objects, cause an access violation in the
 * supervisor code or manipulate some peripherals by side effect of a read-register
 * operation.\n
 *   Normally, it's strongly disencouraged having pointers as arguments of system calls at
 * all. If not avoidable, one can use this helper function to check that a pointer points
 * into permitted address space and that all bytes of a data object pointed at are still in
 * that address space. Here for read access.\n
 *   Permitted address space is anywhere, where supervisor code may read without causing an
 * exception or any kind of side effect. In particular, these are the used portions of RAM
 * and ROM.
 *   @return
 * Get \a true if the pointer may be used for read access and \a false otherwise.
 *   @param address
 * The pointer value, or the beginning of the chunk of memory, which needs to be entirely
 * located in readable memory.
 *   @param noBytes
 * The size of the chunk of memory to be checked. Must not be less than one. (Checked by
 * assertion).
 *   @remark
 * Use the counterpart function rtos_checkUserCodeWritePtr() if a system call handler
 * should do a write access via a user code provided pointer.
 *   @remark
 * Although this function is intended for use inside a system call handler it can be safely
 * used from user code, too.
 */
static inline bool rtos_checkUserCodeReadPtr(const void *address, size_t noBytes)
{
    const uint8_t * const p = (uint8_t*)address;
    extern uint8_t ld_ramStart[0], ld_ramEnd[0], ld_romStart[0], ld_romEnd[0];

    return p >= ld_ramStart  &&  p+noBytes <= ld_ramEnd
           ||  p >= ld_romStart  &&  p+noBytes <= ld_romEnd;

} /* End of rtos_checkUserCodeReadPtr */



/**
 * System call to suspend a process. All currently running tasks belonging to the process
 * are aborted and the process is stopped forever (i.e. there won't be further task starts
 * or I/O driver callback invocations).\n
 *   Suspending a process of PID i is permitted only to processes of PID j>i.
 *   @param PID
 * The ID of the process to suspend. Needs to be not zero (OS process) and lower than the
 * ID of the calling process. Otherwise the calling task is aborted with exception
 * #RTOS_ERR_PRC_SYS_CALL_BAD_ARG.
 *   @remark
 * Tasks of the suspended process can continue running for a short while until their abort
 * conditions are checked the next time. The likelihood of such a continuation is little
 * and the duration is in the magnitude of a Millisecond.
 *   @remark
 * This function must be called from the user task context only. Any attempt to use it from
 * OS code will lead to a crash.
 */
static inline void rtos_suspendProcess(uint32_t PID)
{
    #define RTOS_IDX_SC_SUSPEND_PROCESS     5
    rtos_systemCall(RTOS_IDX_SC_SUSPEND_PROCESS, PID);

} /* End of rtos_suspendProcess */


#endif  /* RTOS_INCLUDED */
