/**
 * @file rtos_priorityCeilingProtocol.c
 * Implementation of Priority Ceiling Protocol as system call, such that it becomes
 * available to the user task code.\n
 *   The implementation basically changes the current priority variable of the scheduler.
 * It adds protection code, such that bad use of the system calls by the user task can't be
 * harmful. In particular, it must be avoided that the current priority can be lowered by a
 * task.
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
 *   rtos_scBscHdlr_suspendAllTasksByPriority
 *   rtos_suspendAllTasksByPriority
 *   rtos_osGetEventByPriority
 *   rtos_scBscHdlr_resumeAllTasksByPriority
 *   rtos_resumeAllTasksByPriority
 * Local functions
 */

#ifndef __VLE__
# error This file is intended for compilation for VLE instruction set only
#endif

/*
 * Include files
 */

#include "rtos_priorityCeilingProtocol.h"
#include "rtos_ivorHandler.h"
#include "rtos.config.h"


/*
 * Defines
 */


/*
 * External function declarations
 */


/*
 * Data declarations
 */



/*
 * Function implementation
 */

/**
 *   @func rtos_scBscHdlr_suspendAllTasksByPriority
 * Change the current priority of the calling user task context, only upwards and only up
 * to a value of #RTOS_MAX_LOCKABLE_TASK_PRIORITY.\n
 *    Any attempt to change \a suspendUpToThisPriority beyond #RTOS_MAX_LOCKABLE_TASK_PRIORITY
 * will lead to an #RTOS_CAUSE_TASK_ABBORTION_SYS_CALL_BAD_ARG exception.\n
 *    The attempt to lower the current priority is silently ignored.
 *   @return
 * On return, r3 contains the priority level at entry into this function (and into the
 * critical section). This priority level needs to be restored on exit from the critical
 * section, when rtos_scBscHdlr_resumeAllTasksByPriority is called.
 *   @param addressOfHandler
 * On entry, r3 holds the address of this system call handler. Not used.
 *   @param suspendUpToThisPriority
 * On entry, r4 holds the aimed priority level. All tasks up to and including this priority
 * will be locked. The CPU will not handle them until the priority level is lowered again.
 *   @remark
 * This is the implementation of a system call handler. The code must not be invoked
 * directly. The system call handler is compliant with the basic conformance class. It is
 * entirely executed with EE=0 and must not rely on sp, r2 and r13.
 */
    .section    .text.ivor
    .extern     rtos_osSystemCallBadArgument
    .globl      rtos_scBscHdlr_suspendAllTasksByPriority
    .balign     2

rtos_scBscHdlr_suspendAllTasksByPriority:
    
     /** @remark Configuration setting RTOS_MAX_LOCKABLE_TASK_PRIORITY can be made core
         dependend if this is required: Just make this function implementation and
         rtos_scBscHdlr_resumeAllTasksByPriority a macro and have an instantiation per
         core running the RTOS. The system call table would need to declare the handler per core.
         (Currently it declares the same function for all cores.) */

    /* The yielded priority must be within the permitted range: Not at level of safety
       tasks or above and not below the level we had at entry into the task.
         The first condition needs to be checked, we would otherwise break the
       safety-concept.
         The second condition is always fulfilled, since we only change upwards. A check in
       DEBUG compilation is relative expensive and typical client code faults, which lead
       to this situation, are anyway caught by the DEBUG code in
       rtos_scBscHdlr_resumeAllTasksByPriority. So we don't do. */
#if RTOS_MAX_LOCKABLE_TASK_PRIORITY <= 32
    se_cmpli    r4, RTOS_MAX_LOCKABLE_TASK_PRIORITY /* Upper boundary */
#else
    e_cmpl16i   r4, RTOS_MAX_LOCKABLE_TASK_PRIORITY /* Upper boundary */
#endif
    e_bgt       rtos_osSystemCallBadArgument  /* r4>MAX: Abort task, demanded prio too high */
   
    mfspr       r5, SPR_G3_CDATA        /* r5: rtos_osGetInstancePtr() */
    e_lwz       r3, O_ID_CUR_PRIO(r5)   /* r3: Current prio value, before change. For return */
    se_cmpl     r4, r3
    se_ble      sat_return              /* r4<=r3: No change of current prio */
    e_stw       r4, O_ID_CUR_PRIO(r5)   /* Store checked, demanded val in prio var */
sat_return:
    se_rfi

/* End of rtos_scBscHdlr_suspendAllTasksByPriority */


    

/**
 *   @func rtos_suspendAllTasksByPriority
 * System call code for rtos_scBscHdlr_suspendAllTasksByPriority(). Function details
 * can be found there.
 *   @return
 * On return, r3 contains the priority level at entry into this function.
 *   @param suspendUpToThisPriority
 * On entry, r3 holds the aimed priority level.
 *   @remark
 * This code must be executed in user mode only. Any attempt to call from supervisor mode
 * can crash the system. In supervisor code, use rtos_osSuspendAllTasksByPriority()
 * instead.
 */
    .section    .text.rtos_suspendAllTasksByPriority
    .globl      rtos_suspendAllTasksByPriority
    .balign     2
rtos_suspendAllTasksByPriority:
    se_mr       r4, r3
    se_li       r3, RTOS_SYSCALL_SUSPEND_ALL_TASKS_BY_PRIORITY
    se_sc
    se_blr      /* This system call doesn't touch the LR */
    
/* End of rtos_suspendAllTasksByPriority */



/**
 * eventDesc_t *rtos_osGetEventByPriority(uint32_t priority);
 *
 * Helper: Get the first event in the global event list, which has the given or a smaller
 * priority. All its successors in the list will have either the same or a lower priority
 * as the returned event. All its predecessors will have a higher priority.
 *   @return
 * r3: Get the address of the wanted event.\n
 *   Note, \a priority may be a non existing value and the returned event's priority is
 * lower than \a priority.\n
 *   Note, if all actual events have a priority higher than \a priority then the returned
 * event will be the guard element at the end of the list, which has the impossible low
 * task priority value 0.
 *   @param priority
 * r3: The wanted priority. It needs to be a possbible value in the range
 * 1..#RTOS_MAX_TASK_PRIORITY. It is not necessary that there is at least one event having
 * this priority.
 *   @remark
 * This function is implemented for the use in a system call of basic conformance class.
 * There are stronger implementation constraints than the normal EABI constraints:
 * - Stack pointer must not be used for load/store
 * - GPR 6+7 must not be altered
 *   @remark
 * The function can be called from assembly and C code but only from supervisor contexts,
 * ISRs and OS tasks.
 */
    .section    .text.ivor
    .globl      rtos_osGetEventByPriority
    .balign     2
    
rtos_osGetEventByPriority:

#ifdef DEBUG
    se_cmpli    r3, 1   /* assert(priority >= 1  &&  priority <= RTOS_MAX_TASK_PRIORITY); */
    se_blt      .
# if RTOS_MAX_TASK_PRIORITY <= 32
    se_cmpli    r3, RTOS_MAX_TASK_PRIORITY
# else
    e_cmpl16i   r3, RTOS_MAX_TASK_PRIORITY
#endif
    se_bgt      .
#endif
    se_slwi     r3, 2   /* r3: priority*4; each array element is a pointer */
    mfspr       r5, SPR_G3_CDATA        /* r5+O_ID_MAP_PRIO_TO_EV: &mapPrioToEvent[0] */
    se_add      r5, r3
    e_lwz       r3, O_ID_MAP_PRIO_TO_EV(r5) /* r3: rtos_mapPrioToEvent[priority] */
    se_blr

/* End of rtos_osGetEventByPriority */



/**
 *   @func rtos_scBscHdlr_resumeAllTasksByPriority
 * Change the current priority of the calling user task context, only downwards and only down
 * to P0, where P0 is the initial priority of the system calling user task, which had been
 * statically agreed on by task configuration.\n
 *   Any attempt to change the priority beyond P0 will lead to an
 * #RTOS_CAUSE_TASK_ABBORTION_SYS_CALL_BAD_ARG exception.\n
 *   The attempt to raise the current priority is silently ignored.\n
 *   In DEBUG compilation only, it is validated that the aimed priority is not higher than
 * the allowed maximum #RTOS_MAX_LOCKABLE_TASK_PRIORITY. If so, it'll lead to an
 * #RTOS_CAUSE_TASK_ABBORTION_SYS_CALL_BAD_ARG exception. The assertion is meant to find
 * typical client code errors, when a task of too high priority tries getting a resource,
 * while resource sharing with such a task is forbidden (in order to not inhibit a safety
 * supervisory task from being accurately scheduled).
 *   @param addressOfHandler
 * On entry, r3 holds the address of this system call handler. Not used.
 *   @param resumeDownToThisPriority
 * On entry, r4 holds the aimed priority level. All tasks at or above this level will be
 * schedulded again. Tasks lower than this priority will still be locked.
 *   @remark
 * This is the implementation of a system call handler. The code must not be invoked
 * directly. The system call handler is basically compliant with the basic conformance
 * class. However, if it decides that a recursive run of the scheduler is required then it
 * switches to full conformance in order to do do.
 */
    .section    .text.ivor
    .extern     rtos_osSystemCallBadArgument
    .globl      rtos_scBscHdlr_resumeAllTasksByPriority
    .balign     2

rtos_scBscHdlr_resumeAllTasksByPriority:

    /* The yielded priority must be within the permitted range: Not at level of safety
       tasks or above and not below the level we had at entry into the task.
         The first condition is always fulfilled, since we only change downwards but we can
       check it in DEBUG compilation to support debugging of the (then faulty) client code,
       which passes a wrong value.
         The second condition needs to be always checked, a violation is possible in case
       of faulty client code and it would be catastrophic. */
#ifdef DEBUG
# if RTOS_MAX_LOCKABLE_TASK_PRIORITY <= 32
    se_cmpli    r4, RTOS_MAX_LOCKABLE_TASK_PRIORITY /* Upper boundary */
# else
    e_cmpl16i   r4, RTOS_MAX_LOCKABLE_TASK_PRIORITY /* Upper boundary */
# endif
    e_bgt       rtos_osSystemCallBadArgument /* r4>MAX: Abort task, demanded prio too high */
#endif
    mfspr       r3, SPR_G0_SVSP /* r3: SV sp when we entered the now system calling user task*/
    se_lwz      r3, RUT_O_CPR(r3)   /* r3: Prio of task start */
    se_cmpl     r4, r3
    e_blt       rtos_osSystemCallBadArgument    /* r4<r3: Abort task: Demanded prio too low */

    /* The function allows to change the task priority only downwards. It is not an error
       if the aimed priority is above from or same as current one: This happens if several
       critical sections or get/release resource pairs are nested. */
    mfspr       r5, SPR_G3_CDATA        /* r5: rtos_osGetInstancePtr() */
    e_lwz       r3, O_ID_CUR_PRIO(r5)   /* r3: Current prio value, before change */
    se_cmpl     r4, r3
    se_bge      rat_return              /* r4>=r3: No change of current prio */
    e_stw       r4, O_ID_CUR_PRIO(r5)   /* Store checked, demanded value in prio var */
    se_mr       r7, r4      /* r6+r7 are persistent with respect to next function call */
    se_bl       rtos_osGetEventByPriority   /* r3: prio@entry -> pEvent with that prio */
    
    /* We will now visit the returned event, and all of its successors, to see whether at
       least one has been triggered. If so, we need to recursively call the scheduler to
       process this event (and maybe others, which can be left to the scheduler). The
       iteration ends when we see an event of priority lower than or equal to the new,
       restored current priority; the current scheduler instance (which brought us here)
       will take care. */
    se_mr       r4, r3      /* r4: pEv under progress */
    
#ifdef DEBUG
    /* The iteration ends at latest at the guard element at the end of the list, which has
       priority zero. Moreover, before that we need to stop at an event of currently
       scheduled priority. We can add an assertion. */
    se_mr       r3, r7      /* r3: restored value of current prio */
    se_bl       rtos_osGetEventByPriority   /* r3: restored prio -> pEvent with that prio */
    se_mr       r5, r3      /* r5: Guard pointer for assertion */
#endif

rat_loopNextEvent:
#ifdef DEBUG
    se_cmpl     r4, r5
    se_bgt      .           /* assert(pEvUnderProgess <= pEvRestoredPrio); */
#endif
    se_lwz      r3, PCP_O_EVDESC_prio(r4)   /* r3: The event's priority */
    se_cmpl     r3, r7      /* gt: Event is still to be considered */
    se_ble      rat_return  /* First event in scope of current scheduler reached */
#ifdef DEBUG
    se_cmpl     r4, r5
    se_bge      .           /* assert(pEvUnderProgess < pEvRestoredPrio); */
#endif
    se_lbz      r3, PCP_O_EVDESC_state(r4)  /* r3: The event's state */
    se_cmpli    r3, PCP_E_EVST_triggered
#ifdef DEBUG
    se_bgt      .           /* assert(pEv->state != evState_inProgress); */
#endif
    se_beq      rat_callSchedulerRecursively    /* Seeing one demanding event is sufficient
                                                   to decide. */
#if PCP_SIZE_OF_EV_DESC <= 32
    se_addi     r4, PCP_SIZE_OF_EV_DESC     /* r4: Points to next event in list */
#else
    e_add16i    r4, r4, PCP_SIZE_OF_EV_DESC /* r4: Points to next event in list */
#endif
    se_b        rat_loopNextEvent           /* Check next event's state */

rat_callSchedulerRecursively:

    /* Now we know, that we need to trigger the scheduler. This requires a full conformance
       handler but we are here in a basic handler. We switch from basic to full,
       effectively a full context switch.
          r4 points to the first event to be considered by the new scheduler instance. */
    .extern     rtos_ivr8_switchBasicToFullHandler
    e_bl        rtos_ivr8_switchBasicToFullHandler  /* Context switch to full conformance
                                                       and return here. r4..r10 are retained */
    /* Here we are in a full conformance handler. r3 contains the PID of calling process. */
    
    .extern     rtos_osProcessTriggeredEvents
    se_mr       r3, r4      /* r3: PID -> pEvent with prio@entry */
    wrteei      0           /* Call of rtos_osProcessTriggeredEvents requires MSR[EE] = 0 */
    e_b         rtos_osProcessTriggeredEvents /* Check for possible task switches and return
                                                 from system call */
rat_return:
#ifdef DBG_COUNT_SCHEDULER_CALLS
    /* Count executions of system call handler as basic handler. */
    e_lwz       r3, _cntResumeNoScheduler@sda21(r13)
    se_addi     r3, 1
    e_stw       r3, _cntResumeNoScheduler@sda21(r13)
#endif
    se_rfi
    
/* End of rtos_scBscHdlr_resumeAllTasksByPriority */



/**
 *   @func rtos_resumeAllTasksByPriority
 * System call code for rtos_scBscHdlr_resumeAllTasksByPriority(). Function details
 * can be found there.
 *   @param resumeDownToThisPriority
 * On entry, r3 holds the aimed priority level.
 *   @remark
 * This code must be executed in user mode only. Any attempt to call from supervisor mode
 * can crash the system. In supervisor code, use rtos_osResumeAllTasksByPriority()
 * instead.
 */
    .section    .text.rtos_resumeAllTasksByPriority
    .globl      rtos_resumeAllTasksByPriority
    .balign     2
    
    /* Define the stack frame contents as offsets of data objects. Note the minimum offset
       of 8 due to the storage of stack pointer and link register. */
    //#define O_myVar         (8+0)
    #define SIZE_OF_PAYLOAD 0  /* Size of user data in stack frame */

    /* Size of stack frame: Room for SP and LR and uprounding to multiple of 8. */
    #define SIZE_OF_SF  ((((SIZE_OF_PAYLOAD)+15)/8)*8)
    #define O_LR        (SIZE_OF_SF+4)

rtos_resumeAllTasksByPriority:
    /* Create stack frame and save stack pointer and return address. */
    e_stwu      sp, -SIZE_OF_SF(sp)
    se_mflr     r0
    se_stw      r0, O_LR(sp)
    
    se_mr       r4, r3
    se_li       r3, RTOS_SYSCALL_RESUME_ALL_TASKS_BY_PRIORITY
    se_sc

    /* Remove the no longer needed stack frame and return. */
    se_lwz      r0, O_LR(sp)
    se_mtlr     r0
    se_addi     sp, SIZE_OF_SF
    se_blr


    #undef SIZE_OF_PAYLOAD
    #undef SIZE_OF_SF
    #undef O_LR

/* End of rtos_resumeAllTasksByPriority */

  

