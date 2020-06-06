/**
 * @file rtos_process.c
 * This module implements the process related functionality like querying the number of
 * errors, recognized and counted for a process and suspension of a (failing) process.
 *
 * Copyright (C) 2019-2020 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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
 *   rtos_osInitProcesses
 *   rtos_osGrantPermissionSuspendProcess
 *   rtos_scSmplHdlr_suspendProcess
 *   rtos_osReleaseProcess
 *   rtos_osSuspendProcess
 *   rtos_isProcessSuspended
 *   rtos_getNoTotalTaskFailure
 *   rtos_getNoTaskFailure
 *   rtos_getStackReserve
 * Module inline interface
 * Local functions
 */

/*
 * Include files
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <assert.h>

#include "typ_types.h"
#include "rtos_process.h"
#include "rtos_process_defSysCalls.h"
#include "rtos_kernelInstanceData.h"
#include "rtos.h"
#include "rtos_systemCall.h"
#include "rtos_ivorHandler.h"


/*
 * Defines
 */

/* The user API header file rtos.h doesn't recursively include all headers of all
   implementing files. Therefore it needs to make some assumptions about basically variable
   but normally never changed constants. These assumptions need of course to be double
   checked. We do this here at compile time of the RTOS. */
#if RTOS_IDX_SC_SUSPEND_PROCESS != RTOS_SYSCALL_SUSPEND_PROCESS
# error Inconsistent definitions made in C modules and RTOS API header file rtos.h
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

/* We need to reference the linker provided information about the location of the stacks. */
#if RTOS_NO_CORES != 3
# error Code needs migration to a maximum of other than 3 cores
#endif
extern uint32_t ld_stackStartOSCore0[], ld_stackEndOSCore0[]
              , ld_stackStartP1Core0[], ld_stackEndP1Core0[]
              , ld_stackStartP2Core0[], ld_stackEndP2Core0[]
              , ld_stackStartP3Core0[], ld_stackEndP3Core0[]
              , ld_stackStartP4Core0[], ld_stackEndP4Core0[]
              , ld_stackStartOSCore1[], ld_stackEndOSCore1[]
              , ld_stackStartP1Core1[], ld_stackEndP1Core1[]
              , ld_stackStartP2Core1[], ld_stackEndP2Core1[]
              , ld_stackStartP3Core1[], ld_stackEndP3Core1[]
              , ld_stackStartP4Core1[], ld_stackEndP4Core1[]
              , ld_stackStartOSCore2[], ld_stackEndOSCore2[]
              , ld_stackStartP1Core2[], ld_stackEndP1Core2[]
              , ld_stackStartP2Core2[], ld_stackEndP2Core2[]
              , ld_stackStartP3Core2[], ld_stackEndP3Core2[]
              , ld_stackStartP4Core2[], ld_stackEndP4Core2[]
              ;

/** An array of process stack areas, per core and process. Here we have the start addresses
    of the stacks. The process index is zero based and index 0 is the kernel. Which menas
    that the PID can be used as index. */
static uint32_t * const _stackCoresStartAry[RTOS_NO_CORES][1+RTOS_NO_PROCESSES] =
    { /* Core */ [0] = { /* Process */ [0] = ld_stackStartOSCore0
                       , /* Process */ [1] = ld_stackStartP1Core0
                       , /* Process */ [2] = ld_stackStartP2Core0
                       , /* Process */ [3] = ld_stackStartP3Core0
                       , /* Process */ [4] = ld_stackStartP4Core0
                       }
    , /* Core */ [1] = { /* Process */ [0] = ld_stackStartOSCore1
                       , /* Process */ [1] = ld_stackStartP1Core1
                       , /* Process */ [2] = ld_stackStartP2Core1
                       , /* Process */ [3] = ld_stackStartP3Core1
                       , /* Process */ [4] = ld_stackStartP4Core1
                       }
    , /* Core */ [2] = { /* Process */ [0] = ld_stackStartOSCore2
                       , /* Process */ [1] = ld_stackStartP1Core2
                       , /* Process */ [2] = ld_stackStartP2Core2
                       , /* Process */ [3] = ld_stackStartP3Core2
                       , /* Process */ [4] = ld_stackStartP4Core2
                       }
    };

/** An array of process stack areas, per core and process. Here we have the end addresses
    of the stacks. */
static const uint32_t * const _stackCoresEndAry[RTOS_NO_CORES][1+RTOS_NO_PROCESSES] =
    { /* Core */ [0] = { /* Process */ [0] = ld_stackEndOSCore0
                       , /* Process */ [1] = ld_stackEndP1Core0
                       , /* Process */ [2] = ld_stackEndP2Core0
                       , /* Process */ [3] = ld_stackEndP3Core0
                       , /* Process */ [4] = ld_stackEndP4Core0
                       }
    , /* Core */ [1] = { /* Process */ [0] = ld_stackEndOSCore1
                       , /* Process */ [1] = ld_stackEndP1Core1
                       , /* Process */ [2] = ld_stackEndP2Core1
                       , /* Process */ [3] = ld_stackEndP3Core1
                       , /* Process */ [4] = ld_stackEndP4Core1
                       }
    , /* Core */ [2] = { /* Process */ [0] = ld_stackEndOSCore2
                       , /* Process */ [1] = ld_stackEndP1Core2
                       , /* Process */ [2] = ld_stackEndP2Core2
                       , /* Process */ [3] = ld_stackEndP3Core2
                       , /* Process */ [4] = ld_stackEndP4Core2
                       }
    };

/*
 * Function implementation
 */

/**
 * Initialize the data structure with all process descriptors on the calling core. This
 * mainly means to initialize the stack memory on the calling core. (Processes are shared
 * between the core but their implementation requires an own stack on each of the cores.)
 * Each core needs to call this function.
 *   @return 
 * The function returns a non zero value from enumeration \a rtos_errorCode_t if a
 * configuration error is detected. The software must not start up in this case. Normally,
 * you will always receive a \a rtos_err_noError (zero). Since it is only about static
 * configuration, the returned error may be appropriately handled by an assertion.
 *   @param isProcessConfiguredAry
 * This array contains an entry for each of the supported processes. After return, the
 * entry with index i tells, whether the process with PID i is configured for use. (Which
 * mainly relates to some stack space configured or not in the linker script.)\n
 *   Note, isProcessConfiguredAry[0] relates to the OS and will always be \a true.
 */
rtos_errorCode_t rtos_osInitProcesses(bool isProcessConfiguredAry[1+RTOS_NO_PROCESSES])
{
    rtos_kernelInstanceData_t * const pIData = rtos_osGetInstancePtr();

    /* The C code has an interface with the assembler code. It is used to exchange process
       and task related information. The interface is modeled twice, once as structs for C
       code and once as set of preprocessor macros, which hold size of data structures and
       offsets of fields. Here, we have macros, which support double-checking the
       equivalence of both definitions. The compiler will abort the compilation if there is
       a static inconsistency. A few more conditions require run-time checking. */
    assert(RTOS_CONSTRAINTS_INTERFACE_C_AS_PROCESS);
    _Static_assert( RTOS_STATIC_CONSTRAINTS_INTERFACE_C_AS_PROCESS
                  , "Interface check C to assembly failed for module"
                    " rtos_priorityCeilingProtocol.S"
                  );

    rtos_errorCode_t errCode = rtos_err_noError;

    /* If the kernel process wouldn't be configured correctly then we would never get here. */
    isProcessConfiguredAry[0] = true;
    
    /* Fill all process stacks with the empty-pattern, which is applied for computing the
       stack usage. */
    uint32_t * const * const stackStartAry = &_stackCoresStartAry[rtos_osGetIdxCore()][1];
    const uint32_t * const * const stackEndAry = &_stackCoresEndAry[rtos_osGetIdxCore()][1];
    unsigned int idxP
               , maxPIDInUse = 0;
    for(idxP=0; idxP<RTOS_NO_PROCESSES; ++idxP)
    {
        /* Disable the process by default. */
        pIData->processAry[idxP].state = 0;
        isProcessConfiguredAry[idxP+1] = false;

        /* Stack size: May be zero if process is not used at all. Otherwise we demand a
           reasonable minimum stack size - anything else is almost certain a configuration
           error. */
        const unsigned int sizeOfStack = (unsigned int)stackEndAry[idxP]
                                         - (unsigned int)stackStartAry[idxP];
        if(sizeOfStack > 0)
        {
#define MIN_REASONABLE_STACK_SIZE   256
#define MAX_REASONABLE_STACK_SIZE   0x10000

            if(sizeOfStack >= MIN_REASONABLE_STACK_SIZE
               &&  sizeOfStack <= MAX_REASONABLE_STACK_SIZE
               &&  ((uintptr_t)stackStartAry[idxP] & 0x7) == 0
               &&  (sizeOfStack & 0x7) == 0
              )
            {
                memset(stackStartAry[idxP], /* c */ 0xa5, sizeOfStack);
                stackStartAry[idxP][sizeOfStack/4 - 4] = 0u;
                stackStartAry[idxP][sizeOfStack/4 - 3] = 0xffffffffu;
                stackStartAry[idxP][sizeOfStack/4 - 2] = 0xffffffffu;
                stackStartAry[idxP][sizeOfStack/4 - 1] = 0xffffffffu;
                pIData->processAry[idxP].userSP = (uint32_t)stackEndAry[idxP] - 16;
                pIData->processAry[idxP].state = 1;

                /* Stack alright, process may be used. */
                isProcessConfiguredAry[idxP+1] = true;

                /* Keep track of the highest PID in use. */
                if(idxP+1 > maxPIDInUse)
                    maxPIDInUse = idxP+1;

#undef MIN_REASONABLE_STACK_SIZE
#undef MAX_REASONABLE_STACK_SIZE
            }
            else
                errCode = rtos_err_prcStackInvalid;
        }
        else
            pIData->processAry[idxP].userSP = 0;

        pIData->processAry[idxP].cntTotalTaskFailure = 0;
        memset( &pIData->processAry[idxP].cntTaskFailureAry[0]
              , /* c */ 0
              , sizeOfAry(pIData->processAry[idxP].cntTaskFailureAry)
              );
    } /* End for(All processes) */

    if(errCode == rtos_err_noError  &&  maxPIDInUse >= 1)
    {
        /* Caution: Maintenance of this code is required consistently with
           rtos_osGrantPermissionSuspendProcess() and rtos_scSmplHdlr_suspendProcess(). */
        assert(maxPIDInUse >= 1  &&  maxPIDInUse <= 4);
        const uint16_t mask = 0x1111 << (maxPIDInUse-1);
        if((pIData->suspendProcess_permissions & mask) != 0)
            errCode = rtos_err_suspendPrcBadPermission;
    }

    return errCode;

} /* End of rtos_osInitProcesses */



/**
 * Operating system initialization function: Grant permissions for using the service
 * rtos_suspendProcess to particular processes. By default, the use of that service is not
 * allowed.\n
 *   By principle, offering service rtos_suspendProcess makes all processes vulnerable,
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
                                         )
{
    /* targetPID <= 3: Necessary but not sufficient to double-check
       "targetPID <= maxPIDInUse-1". */
    assert(pidOfCallingTask >= 1  &&  pidOfCallingTask <= 4
           &&  targetPID >= 1  &&  targetPID <= 3
          );

    /* Caution, the code here depends on macro RTOS_NO_PROCESSES being four and needs to be
       consistent with the implementation of rtos_scSmplHdlr_suspendProcess(). */
#if RTOS_NO_PROCESSES != 4
# error Implementation requires the number of processes to be four
#endif
    const unsigned int idxCalledPrc = targetPID - 1u;
    const uint16_t mask = 0x1 << (4u*(pidOfCallingTask-1u) + idxCalledPrc);
    rtos_osGetInstancePtr()->suspendProcess_permissions |= mask;

} /* End of rtos_osGrantPermissionSuspendProcess */



/**
 * System call implementation to suspend a process. All currently running tasks belonging
 * to the process are aborted and the process is stopped forever (i.e. there won't be
 * further task starts or I/O driver callback invocations).\n
 *   Suspending a process of PID i is permitted only to processes of PID j>i.
 *   @param pidOfCallingTask
 * Process ID of calling user task.
 *   @param PID
 * The ID of the process to suspend. Needs to be not zero (OS process) and lower than the
 * ID of the calling process. Otherwise the calling task is aborted with exception
 * #RTOS_ERR_PRC_SYS_CALL_BAD_ARG.
 *   @remark
 * The system call is the implementation of a system call of conformance class "simple".
 * Such a system call can be implemented in C but it needs to be run with all interrupts
 * suspended. It cannot be preempted. Suitable for short running services only.\n
 *   @remark
 * Tasks of the suspended process can continue running for a short while until their abort
 * conditions are checked the next time. The likelihood of such a continuation is little
 * and the duration is in the magnitude of a Millisecond.
 *   @remark
 * This function must never be called directly. The function is only made for placing it in
 * the global system call table.
 */
void rtos_scSmplHdlr_suspendProcess(uint32_t pidOfCallingTask, uint32_t PID)
{
    /* This code depends on specific number of processes, we need a check. The
       implementation requires consistent maintenance with other function
       rtos_osGrantPermissionSuspendProcess() */
#if RTOS_NO_PROCESSES != 4
# error Implementation requires the number of processes to be four
#endif

    /* Now we can check the index of the target process. */
    const unsigned int idxCalledPrc = PID - 1u;
    if(idxCalledPrc > 3)
        rtos_osSystemCallBadArgument();

    const rtos_kernelInstanceData_t * const pIData = rtos_osGetInstancePtr();
    const uint16_t mask = 0x1 << (4u*(pidOfCallingTask-1u) + idxCalledPrc);
    if((pIData->suspendProcess_permissions & mask) != 0)
        rtos_osSuspendProcess(PID);
    else
    {
        /* The calling process doesn't have enough privileges to suspend the aimed process.
           This is a severe user code error, which is handled with an exception, task abort
           and counted error.
             Note, this function does not return. */
        rtos_osSystemCallBadArgument();
    }
} /* End of rtos_scSmplHdlr_suspendProcess */




/**
 * Kernel function to initially release a process. "Initially" means that no state machine
 * is implemented, which would allow to alternatingly suspend and resume the operation of a
 * process. After startup, all processes are suspended. When the kernel is initialized it
 * may call this function once for each of the processes. It must however never use it again
 * for a process, e.g. after a call of rtos_osSuspendProcess().
 *   @param PID
 * The ID of the process to suspend in the range 1..4. Checked by assertion.
 *   @remark
 * This function must be called from the OS context only. Any attempt to use it in user
 * code will lead to a privileged exception.
 */
void rtos_osReleaseProcess(uint32_t PID)
{
    /* The process array has no entry for the kernel process. An index offset by one
       results. */
    -- PID;

    rtos_kernelInstanceData_t * const pIData = rtos_osGetInstancePtr();
    assert(PID < sizeOfAry(pIData->processAry));
    pIData->processAry[PID].state = 1;

} /* End of rtos_osReleaseProcess */



/**
 * Kernel function to suspend a process. All currently running tasks belonging to the process
 * are aborted and the process is stopped forever (i.e. there won't be further task starts
 * or I/O driver callback invocations).\n
 *   If the kernel is started on more than one core and if several cores share the same
 * process then the function still relates to only those tasks of the process, which are
 * configured to run on the calling core.
 *   @param PID
 * The ID of the process to suspend in the range 1..4. Checked by assertion.
 *   @remark
 * Tasks of the suspended process can continue running for a short while until their abort
 * conditions are checked the next time. The likelihood of such a continuation is little
 * and the duration is in the magnitude of a Millisecond.
 *   @remark
 * This function must be called from the OS context only. Any attempt to use it in user
 * code will lead to a privileged exception.
 */
void rtos_osSuspendProcess(uint32_t PID)
{
    /* The process array has no entry for the kernel process. An index offset by one
       results. */
    -- PID;

    /* Form a safety perspective, it could be advantageous to stop the process on all
       cores. However, this is not implementable for the Z4 cores due to their D cache.
       We could write to the flag processAry[PID].state of another core but there's no
       guarantee that that core will see the change within a particular time span.
         We would need to use atomic read/writes or load/store with reservation in the
       kernel's assembly implementation or have a portion of the kernel instance data in
       the uncached memory. */

    rtos_kernelInstanceData_t * const pIData = rtos_osGetInstancePtr();
    assert(PID < sizeOfAry(pIData->processAry));
    pIData->processAry[PID].state = 0;

} /* End of rtos_osSuspendProcess */



/**
 * Kernel function to read the suspend status of a process. This function is a simple
 * counterpart to rtos_osSuspendProcess(). It will return \a true after the other function
 * had been called for the given process ID or if the process is not at all in use.
 *   @return
 * Get \a false as long as the process is still active, \a true otherwise.
 *   @param PID
 * The ID of the queried process in the range 1..4. Checked by assertion.
 *   @remark
 * This function can be called from OS and user context.
 */
bool rtos_isProcessSuspended(uint32_t PID)
{
    /* The process array has no entry for the kernel process. An index offset by one
       results. */
    -- PID;

    const rtos_kernelInstanceData_t * const pIData = rtos_getInstancePtr();
    assert(PID < sizeOfAry(pIData->processAry));
    return pIData->processAry[PID].state == 0;

} /* End of rtos_isProcessSuspended */



/**
 * Get the number of task failures (and task abortions at the same time) counted for the
 * given process since start of the kernel on the calling core.
 *   @return
 * Get total number of errors counted for process \a PID.\n
 *   If the kernel is started on more than one core and if several cores share the same
 * process then the function still returns only those process errors, which had been caught
 * on the calling core. Explicit cross-core communication will be required to query the
 * failures counted for the same process on another core, too.
 *   @param PID
 * The ID of the queried process in the range 1 .. RTOS_NO_PROCESSES. An out of range PID
 * will always yield UINT_MAX and an assertion fires in DEBUG compilation. An unused
 * process has no errors.
 *   @remark
 * This function can be called from both, a user task or the OS context.
 */
unsigned int rtos_getNoTotalTaskFailure(unsigned int PID)
{
    const rtos_kernelInstanceData_t * const pIData = rtos_getInstancePtr();
    if(--PID < RTOS_NO_PROCESSES)
        return pIData->processAry[PID].cntTotalTaskFailure;
    else
    {
        assert(false);
        return UINT_MAX;
    }
} /* End of rtos_getNoTotalTaskFailure */




/**
 * Get the number of task failures of given category counted for the given process since
 * start of the kernel on the calling core.
 *   @return
 * Get total number of errors of category \a kindOfErr counted for process \a PID.\n
 *   If the kernel is started on more than one core and if several cores share the same
 * process then the function still returns only those process errors, which had been caught
 * on the calling core. Explicit cross-core communication will be required to query the
 * failures counted for the same process on another core, too.
 *   @param PID
 * The ID of the queried process in the range 1 .. RTOS_NO_PROCESSES. An out of range PID
 * will always yield UINT_MAX and an assertion fires in DEBUG compilation. An unused
 * process has no errors.
 *   @param kindOfErr
 * The category of the error. See file rtos_ivorHandler.h,
 * #RTOS_ERR_PRC_MACHINE_CHECK and following, for the enumerated error causes.
 *   @remark
 * This function can be called from both, a user task or the OS context.
 */
unsigned int rtos_getNoTaskFailure(unsigned int PID, unsigned int kindOfErr)
{
    const rtos_kernelInstanceData_t * const pIData = rtos_getInstancePtr();
    if(--PID < RTOS_NO_PROCESSES
       &&  kindOfErr < sizeOfAry(pIData->processAry[PID].cntTaskFailureAry)
      )
    {
        return pIData->processAry[PID].cntTaskFailureAry[kindOfErr];
    }
    else
    {
        assert(false);
        return UINT_MAX;
    }
} /* End of rtos_getNoTaskFailure */



/**
 * Compute how many bytes of the stack area of a process are still unused on the calling
 * core. If the value is requested after an application has been run a long while and has
 * been forced to run through all its conditional code paths, it may be used to optimize
 * the static stack allocation. The function is useful only for diagnosis purpose as
 * there's no chance to dynamically increase or decrease the stack area at runtime.\n
 *   The function may be called from a task, ISR and from the idle task.\n
 *   The algorithm is as follows: The unused part of the stack is initialized with a
 * specific pattern word. This routine counts the number of subsequent pattern words down
 * from the (logical) top of the stack area. The result is returned as number of bytes.\n
 *   The returned result must not be trusted too much: It could of course be that a pattern
 * word is found not because of the initialization but because it has been pushed onto the
 * stack - in which case the return value is too great (too optimistic). The probability
 * that this happens is significantly greater than zero. The chance that two pattern words
 * had been pushed is however much less and the probability of three, four, five such words
 * in sequence is negligible. Any stack size optimization based on this routine should
 * therefore subtract e.g. eight bytes from the returned reserve and diminish the stack
 * outermost by this modified value.\n
 *   Be careful with operating system stack size optimization based only on this routine.
 * The OS stack takes all interrupt stack frames. Even if the application ran a long time
 * there's a significant probability that there has not yet been the deepest possible
 * nesting of interrupts in the very instance that the code execution was busy in the
 * deepest nested sub-routine of any of the service routines, i.e. when having the largest
 * imaginable stack consumption for the OS stack. (Actually, the likelihood of not seeing
 * this is rather close to one than close to zero.) A good suggestion therefore is to add
 * the product of ISR stack frame size with the number of IRQ priority levels in use to the
 * measured OS stack use and reduce the allocated stack memory only on this basis.\n
 *   The IRQ stack frame is 96 Byte for normal IRQs and 200 Byte for those, which may start
 * a user task (SW IRQs and I/O IRQs with callback into user code).\n
 *   In the worst case, with 15 IRQ priority levels, this can sum up to 3 kByte. The stack
 * reserve of a "safe" application should be in this order of magnitude.
 *   @return
 * The number of still unused stack bytes of the given process. See function description
 * for details.
 *   @param PID
 * The process ID the query relates to. (Each process has its own stack.) ID 0 relates to
 * the OS/kernel stack.
 *   @remark
 * The computation is a linear search for the first non-pattern word and thus relatively
 * expensive. It's suggested to call it only in some specific diagnosis compilation or
 * occasionally from the idle task.
 *   @remark
 * This function can be called from both, the OS context and a user task.
 *   @remark
 * This function my be called even from a core, which is not running safe-RTOS. Hoever, the
 * use is restricted to PID 0, the OS stack, which is the only one is use on such a core.
 */
unsigned int rtos_getStackReserve(unsigned int PID)
{
    if(PID <= RTOS_NO_PROCESSES)
    {
        /* We can safely do the operation only for the calling core. If we call this
           function regularly from core i then there's no guarantee that it doesn't have
           portions of the stack of core j still in its cache, while j has meanwhile
           changed its stack memory. i could see a too optimistic result - which is
           inacceptable as particularly the pessimistic readings are (safety) use case of
           this API. */
        const unsigned int idxCore = rtos_getIdxCore();
        assert(idxCore < RTOS_NO_CORES);
        
        /* Access core specific data. */
        uint32_t * const * const stackStartAry = &_stackCoresStartAry[idxCore][0];
        const uint32_t * const * const stackEndAry = &_stackCoresEndAry[idxCore][0];
        
        const uint32_t *sp = stackStartAry[PID];
        if((intptr_t)stackEndAry[PID] - (intptr_t)sp >= (intptr_t)sizeof(uint32_t))
        {
            /* The bottom of the stack is always initialized with a non pattern word (e.g.
               there's an illegal return address 0xffffffff). Therefore we don't need a
               limitation of the search loop - it'll always find a non-pattern word in the
               stack area. */
            while(*sp == 0xa5a5a5a5)
                ++ sp;
            return (uintptr_t)sp - (uintptr_t)stackStartAry[PID];
        }
        else
            return 0;
    }
    else
        return 0;

} /* End of rtos_getStackReserve */

