/**
 * @file rtos_ivorHandler.S
 * VLE assembler implementation of IVOR exception handlers for safe-RTOS. Effectively, this
 * file is the essence of the safe-RTOS kernel.\n
 *   Used for MPC5748G and compatible with all its cores. The code has been designed for
 * use with GCC for PowerPC EABI.\n
 *   Much of the documentation in this source file refers to either "Core RM" or CRM. Meant
 * is in either case: "e200z4 Power Architecture Core Reference Manual", Supports
 * e200z446n3, e200z4RM Rev. 0 10/2009, e.g.
 * https://github.com/PeterVranken/TRK-USB-MPC5643L/blob/master/doc/e200zCore/e200z4-PowerArchitectureCoreReferenceManual.pdf
 *   Unfortunately, the quoted core reference manual doesn't perfectly fit to the Z4/Z2
 * cores of the MPC5748G. Another useful source of information is the MCU reference manual,
 * section "Chapter 58-64: Core Modules". The correct core reference manuals are not
 * publically available but can be requested at NXP. The titles are:
 *   - "Zen z4204n3 Embedded Processor", Implementation Definition, Rev 1.95 - Feb. 16, 2013
 *   - "Zen z210n3 Embedded Processor", Implementation Definition, Rev 1.95 - Feb. 16, 2013
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
/* Module interface
 *   rtos_initializeDCache
 *   rtos_ivor0Handler
 *   rtos_ivor1Handler
 *   rtos_ivor2Handler
 *   rtos_ivor3Handler
 *   rtos_ivor4Handler
 *   rtos_osRunInitTask
 *   rtos_osRunUserTask
 *   rtos_terminateUserTask
 *   rtos_scBscHdlr_terminateUserTask
 *   rtos_osSystemCallBadArgument
 *   rtos_scBscHdlr_sysCallUndefined
 *   rtos_ivor5Handler
 *   rtos_getInstancePtr
 *   rtos_getIdxCore
 *   rtos_getCoreStatusRegister
 *   rtos_ivor6Handler
 *   rtos_ivor7Handler
 *   rtos_ivor8Handler
 *   rtos_systemCall
 *   rtos_ivor9Handler
 *   rtos_ivor10And11Handler
 * Local functions
 */

#ifndef __VLE__
# error This file is intended for compilation for VLE instruction set only
#endif

/*
 * Include files
 */

#include "hwc_hardwareConfiguration.h"
#include "rtos_systemCall.h"
#include "rtos_ivorHandler.h"


/*
 * Defines
 */

/** Address of interrupt controller INTC in memory map. */
#define INTC            0xfc040000

/** Address of INTC current priority register in memory map, for processor 0. The
    registers for the others cores are expected at subsequent 4 Byte addresses. */
#define INTC_CPR0       (INTC+0x10)

/** Address of INTC interrupt acknowledge register in memory map, for processor 0. The
    registers for the others cores are expected at subsequent 4 Byte addresses. */
#define INTC_IACKR0     (INTC+0x20)

#if 0
/** Address of INTC interrupt acknowledge register in memory map, for processor 1. */
#define INTC_IACKR1     (INTC+0x24)

/** Address of INTC interrupt acknowledge register in memory map, for processor 2. */
#define INTC_IACKR2     (INTC+0x28)
#endif

/** Address of INTC end of interrupt register in memory map, for processor 0. The
    registers for the others cores are expected at subsequent 4 Byte addresses. */
#define INTC_EOIR0      (INTC+0x30)

#if 0
/** Address of INTC end of interrupt register in memory map, for processor 1. */
#define INTC_EOIR1      (INTC+0x34)

/** Address of INTC end of interrupt register in memory map, for processor 2. */
#define INTC_EOIR2      (INTC+0x38)
#endif


/** SPR index of SRR0. */
#define SPR_SRR0    26

/** SPR index of SRR0. */
#define SPR_SRR1    27

/** SPR index of process ID. */
#define SPR_PID0    48

/** SPR index of Exception Syndrome Register. */
#define SPR_ESR     62

/** SPR index of SPE /EFPU Status and Control Register. */
#define SPR_SPEFSCR 512

/** SPR index of Machine Check Save/Restore Register 0. */
#define SPR_MCSRR0  570

/** SPR index of Machine Check Save/Restore Register 1. */
#define SPR_MCSRR1  571

/** SPR index of Machine Check Syndrome Register. */
#define SPR_MCSR    572

/** SPR index of Machine Check Address Register. */
#define SPR_MCAR    573

/** SPR index of Time Base (lower) register. */
//#define SPR_TBL     284

/* The MPC5748G doesn't have the core counter Timebase. We need to apply an core-external
   I/O device as substitute. All cores will access the free running counter register of
   STM_0. It's configured to run at 80 Mhz. */

/** Peripheral STM_0 base address */
#define STM_0_BASE          (0xfc068000)

/** Free running 32 Bit counter at 80 MHz. */
#define STM_0_CNT           (STM_0_BASE+0x4)

/** Preprocessor computation of address of symbol s, which yields same result as assembler
    compile-time expression s@ha. */
#define AT_HA(s)    (((s)+0x8000)>>16)


/*
 * External function declarations
 */


/*
 * Data declarations
 */

/** The table of function pointers to the actual IRQ service descritors is implemented here
    in the assembler code, where we have better control of the required alignment
    constraints.
      See RM 23.1.2, Table 23-1, for the list of interrupt sources and vectors.*/
    .section    .INTCInterruptServiceAry, "a"
    .extern     rtos_dummyINTCInterruptHandler
    .global     rtos_INTCInterruptHandlerAry, rtos_endOfINTCInterruptHandlerAry
    .p2align    12  /* RM, 23.6.6: 12 Bit alignment required by INTC hardware. The
                       statement makes the implementation safe but does not say anything
                       about efficient memory allocation. To avoid a big waste of memory
                       the section allocation in the linker file should be made on an
                       according memory address, too. */
rtos_INTCInterruptHandlerAry:
    .rept       753
    .dc.l       rtos_dummyINTCInterruptHandler
    .endr
rtos_endOfINTCInterruptHandlerAry:

/* End of rtos_INTCInterruptHandlerAry */



/*
 * Function implementation
 */

#if HWC_ENABLE_DCACHE
/**
 *   @func rtos_initializeDCache
 * This function disables the D-cache, invalidates all contents and re-enables it.
 *   @remark
 * Besides altering the concerned D-cache special purpose registers, the function makes use
 * of GPR r0, which is not restored on exit. The only other altered register is CR0.\n
 *   The function returns to the address in LR.
 *   @remark
 * This function is shared with the startup code. Any interface change needs to be
 * double-checked with the startup code environment, too.
 */
    .section    .text.rtos_initializeDCache
    .global     rtos_initializeDCache
    .balign     2
rtos_initializeDCache:

    /* Disable the data cache. */
    mfspr       r0, 1010    /* Read L1CSR0, contains enable bit for cache */
    se_bclri    r0, 31      /* Clear bit L1CSR0[CDE], data cache enable */
    se_isync                /* CRM e200z7: isync required */
    msync
    mtspr       1010, r0

idc_cfg:
    /* CRM, 11.7: Cache operation. */
    se_li       r0, 0x2     /* SPR 1010: L1CSR0, Cache control and status register 0, Bit 30 */
    mtspr       1010, r0    /* Set bit L1CSR0[DCINV] to start the invalidation of the
                               entire data cache. All other bits remain zero, which is
                               their reset default value */
idc_waitForInvalidation:
    sync                /* EREF 2.0, 4.5.4.3, table 4-3, demands a sync prio to mfspr L1CSRi */
    mfspr       r0, 1010    /* Read L1CSR0, invalidation busy bit 0x2 will be reset by HW
                               on completion, abort bit 0x4 may be set before */
    se_btsti    r0, 29      /* Test for abort */    
    se_beq      idc_noAbort
    se_bclri    r0, 29      /* Explicitly clear the abort flag by SW */
    mtspr       1010, r0
    se_b        idc_cfg     /* Start over, retry */

idc_noAbort:
    se_btsti    r0, 30      /* Test still busy flag */
    se_bne      idc_waitForInvalidation /* Busy wait for completion. */
    
    se_bseti    r0, 31      /* Set bit L1CSR0[CDE], data cache enable */
    se_isync                /* CRM e200z7: isync required */
    msync
    mtspr       1010, r0
    se_isync        /* EREF 2.0, 4.5.4.3, table 4-3, demands an isync after mfspr L1CSR0/1.
                       We do this only here, where cache enabling has a context altering
                       effect. */
    se_blr          /* Done, return to caller via LR */
    
/* End of rtos_initializeDCache */
#endif



/**
 *   @func rtos_ivor1Handler
 * This is the interrupt handler for the MCU trap #1, Machine Check. See Core RM, 5.1.2,
 * Table 5-3, p.164f for the association of exception types to chosen IVOR handler and
 * Core RM, 5.7.2, p. 174, for this particular handler. In the context of this software,
 * this exception handler relates to memory access violations reported by the core-external
 * MPU. (There's no other source of machine check exceptions.)
 *   @remark
 * Different to all other exceptions in our context, the MPU raised external bus error
 * exceptions are "imprecise". They occur not as part of execution of the failing
 * instruction but a few, however undefined number of instructions later (in all tests and
 * experiments we saw no more than one instruction of delay). This makes them resemble the
 * asynchronous exceptions, e.g. IVOR #4. In our context, a normal, "precise" exception is
 * easy handled. We just abort the running task - by nature it the one, which is preempted
 * by the exception. For external bus errors it's a challenge to relate the exception to
 * the failing task.\n
 *   The idea: The switch from one task to another context is always initiated by an
 * exception, IVOR #4 or IVOR #8. These context switches are coherently connected to a
 * switch from user to supervisor mode. In the IVOR #1 handler we can inspect the execution
 * mode of the preempted context. If it is user mode then we have the simple situation from
 * the precise exceptions. If it is supervisor mode and if we are in the entry code of
 * IVOR #4 or #8 then we know that the failing task belongs to the still set process ID. We
 * abort both, the begun IVOR handler and the task it has preempted. We may do so: The IVOR
 * #4 entry code has not yet touched the INTC and acknowledged the IRQ and so the handler
 * will be called immediately again after return from the aborted task. The system call
 * belongs to the code sequence of the anyway aborted task and any attempt to continue or
 * even repeat it would be a logical fault.
 */
    .section    .text.ivor
    .global     rtos_ivor1Handler
    .p2align    4

rtos_ivor1Handler:
    /* We don't need a preamble with storage of register contents of preempted context: We
       are anyway going to abort the execution of that context.
         We must not rely on any register content as got from the preempted context: It
       can be corrupted as effect of the fault, which let to the exception. This holds in
       particular for the EABI registers r2 and r13 and the stack pointer. */

#if HWC_ENABLE_DCACHE
    /* As long as there is no HW issue, all of the ME exceptions are caused by an MPU
       protection fault. Unfortunately the MPU sits behind core and cache and if the D
       cache is enabled, a protection fault causing store will still change the cache
       contents - effectively the store was successful despite of the MPU exception. We
       need to invalidate the related cache line(s). Basically, the MPU records, which
       effective address was hit but the z4 core has several store buffers and each of them
       can make a forbidden access, while the MPU only stores the last recent failure.
       Therefore, it is not possible to safely identify the violated cache line(s) and we
       have to invalidate the entire cache. */
    mfspr       r0, SPR_PIR             /* r0: idxCore */
    se_cmpli    r0, 2                   /* No caches in core 2, Z2 */
    se_beq      ivr1_z2HasNoDCache      /* Skip call of cache reinitialization */
    e_lis       r0, rtos_initializeDCache@ha
    e_add16i    r0, r0, rtos_initializeDCache@l /* r0: Function address for reenable cache */
    se_mtlr     r0                      /* LR is not needed any more and can be altered */
    se_blrl
ivr1_z2HasNoDCache:
#endif

    /* Usually, all MC exceptions will originate from user code - all supervisor code
       belongs to the sphere of trusted code and is expected to be error-free. Check it. */
    mfspr       r0, SPR_MCSRR1
    se_btsti    r0, 17      /* Test bit "problem state" */
    se_bne      ivr1_isUserCodeIvor1Exception

    /* Supervisor mode may be active if but only if we encounter a double exception. A
       double exception will occur if a core detected failure is made at an MPU protected,
       unavailable address.
         The precise, synchronously appearing CPU exception is followed by an imprecise (CPU
       external) exception from the MPU. In which case the Machine Check exception here has
       interrupted the just beginning exception handler of the earlier exception from the
       CPU.
         Examples: Execution of a privileged instruction in process RAM (no execution rights
       for RAM granted by MPU) or misaligned data access in RAM of other process.
         All of our anticipated exceptions lead to the same action, error counting and task
       abort. Therefore we don't need special handling for the double exception and proceed
       as usual. However, we want to recognize this situation in order to still have a
       distinction of user code faults and faults in the "trusted" OS code: Normally, any
       exception of SV code points to a severe fault in the operating system itself (kernel
       or I/O driver).
         If we recognize the latter then we can halt the software execution and delegate the
       problem to the next safety catch level: A watchdog will bring the system into the safe
       state. Not recognizing the problem means opening a door to let the SW do unsafe
       things.
         The way we recognize the double exception is looking at the address at which the MC
       exception preempted. If it is the beginning of another IVOR exception then we decide
       for double exception. Since the preempted exception is closer to the root cause of the
       fault we resume the execution of that exception.
         The imprecise MC exception can sometimes hit the beginning execution of an IVOR #4,
       too. This is by chance and not a nested fault recognition. If we resumed the IVOR
       handler in this case, too, then we would ignore a process fault and eventually return
       to the failing task. Now, the decision is to really count an MC exception as failure
       cause and abort the failing task. The begun IVOR #4 handler is not resumed. The
       interrupt is still asserted and is taken by the CPU a second time at next occasion. */

    /* Note, we don't make use of short addressing modes, neither for handler addresses nor
       for counter variables, to keep code independent from location and to spare expensive
       SDA RAM, respectively. There's no need for speed optimized code here, it'll normally
       never be executed and even if then it will rather save CPU execution time (by
       aborting a task) than producing additional load. */

    mfspr       r3, SPR_MCSRR0  /* Address, where this Machine Check interrupt preempted */

    /* Note: Code execution failed when we put a breakpoint here. (Using NXP S32DS Design
       Studio, V2.1.) The execution of the breakpoint caused a new MC exception, which
       overwrote MCSRR0/1 so that code continuation was impossible. The new exception
       address was 0xffffc000 and the MPU indicated an (illegal) instruction fetch in SV
       mode. The reason stayed unclear and the consequence is that you must not try to step
       through this code section. */ 

    e_lis       r0, rtos_ivorVectorTableEntry4@ha
    e_add16i    r0, r0, rtos_ivorVectorTableEntry4@l    /* r0: Address External IRQ handler */
    se_cmp      r0, r3          /* r3=SPR_MCSRR0 and r0 need to match to satisfy */

    /* r0 == r3: IVOR #4 started handling an unknown, unrelated I/O interrupt when being
       preempted by the imprecise IVOR #1 because of a fault. We let IVOR #1 handle the
       problem. The IVOR #4 is not continued. The interrupt is still asserted and the CPU
       will return to the IVOR #4 handler as soon as the fault handling proceeds to the
       point where MSR[EE] returns to 1. */
    se_beq      ivr1_isUserCodeIvor1Exception

    /* If we get here then we have a preemption of supervisor code, which may be either a
       rare but normal double exception or a fault in the OS. If it is a double exception
       then the address of preemption shall be at the beginning of an exception handler and
       that handler shall have preempted user code. Both conditions need to be met to
       decide for user code preemption.
         The common condition - first exception preempted either user or OS code - can be
       checked once and before we look for the particular addresses. */

    mfspr       r0, SPR_SRR1    /* MSR of task, which a potential other IVOR has preempted */
    se_btsti    r0, 17          /* Test bit "problem state" */
    se_beq      rtos_ivr1_isOSCodeException /* It's already clear, it can't be a double
                                               exception */
ivr1_testIvor2:
    e_lis       r0, rtos_ivorVectorTableEntry2@ha
    e_add16i    r0, r0, rtos_ivorVectorTableEntry2@l  /* r0: Address Instruction Storage IRQ handler */
    se_cmp      r0, r3          /* Both need to match to satisfy */

    /* r0 == r3: IVOR #2 started handling the ECU exception when being preempted by the
       imprecise IVOR #1. IVOR #1 doesn't handle the problem but returns to the preempted
       IVOR #2. */
    se_beq      ivr1_continuePreemptedIvor

    /* Note, on the MPC5748G, the interrupts vectors have a distance of 16 Byte. Instead of
       loading each addreses we could use an incremental "se_addi r0, 16". However, the
       IVOR #1 handler is in no way time critical and such code wouldn't be compatible
       with the z4/z7 cores of most other derivatives. */

    e_lis       r0, rtos_ivorVectorTableEntry3@ha
    e_add16i    r0, r0, rtos_ivorVectorTableEntry3@l /* r0: Addr. Instr. Storage IRQ handler */
    se_cmp      r0, r3          /* Both need to match to satisfy */

    /* r0 == r3: IVOR #3 started handling the ECU exception when being preempted by the
       imprecise IVOR #1. IVOR #1 doesn't handle the problem but returns to the preempted
       IVOR #3. */
    se_beq      ivr1_continuePreemptedIvor

    e_lis       r0, rtos_ivorVectorTableEntry5@ha
    e_add16i    r0, r0, rtos_ivorVectorTableEntry5@l  /* r0: Address Alignment IRQ handler */
    se_cmp      r0, r3          /* Both need to match to satisfy */

    /* r0 == r3: IVOR #5 started handling the ECU exception when being preempted by the
       imprecise IVOR #1. IVOR #1 doesn't handle the problem but returns to the preempted
       IVOR #5. */
    se_beq      ivr1_continuePreemptedIvor

    e_lis       r0, rtos_ivorVectorTableEntry6@ha
    e_add16i    r0, r0, rtos_ivorVectorTableEntry6@l  /* r0: Address Program IRQ handler */
    se_cmp      r0, r3          /* Both need to match to satisfy */
    se_bne      ivr1_testIvor7

    /* r0 == r3: IVOR #6 started handling the ECU exception when being preempted by the
       imprecise IVOR #1. IVOR #1 doesn't handle the problem but returns to the preempted
       IVOR #6. */
    se_b        ivr1_continuePreemptedIvor

ivr1_isUserCodeIvor1Exception:
    e_lis       r0, 0x32f0  /* 0x32efffff: Mask to reset anticipated exception syndromes */
    se_subi     r0, 1
    mtspr       SPR_MCSR, r0 /* SPR 572 = MCSR, MC syndrome register. Acknowledge exception. */
    e_li        r0, 0x1000  /* Reload MSR: CE=EE=0 but ME=1 */
    mtmsr       r0
    se_li       r3, RTOS_CAUSE_TASK_ABBORTION_MACHINE_CHECK
    e_b         rut_endUserTaskByException   /* Do same as system call "task abort" */

    .global     rtos_ivr1_isOSCodeException   /* Just to have it in the map file */
rtos_ivr1_isOSCodeException:
    se_bne      .   /* Halt SW execution if it is a non-interpretable preemption of SV code */

ivr1_testIvor7:
    e_lis       r0, rtos_ivorVectorTableEntry7@ha
    e_add16i    r0, r0, rtos_ivorVectorTableEntry7@l  /* r0: Address FPU unavailable handler */
    se_cmp      r0, r3          /* Both need to match to satisfy */
    se_bne      ivr1_testIvor8

    /* r0 == r3: IVOR #7 started handling the ECU exception when being preempted by the
       imprecise IVOR #1. IVOR #1 doesn't handle the problem but returns to the preempted
       IVOR #7. */

ivr1_continuePreemptedIvor:
    e_lis       r0, 0x32f0  /* 0x32efffff: Mask to reset anticipated exception syndromes */
    se_subi     r0, 1
    mtspr       SPR_MCSR, r0 /* SPR 572 = MCSR, MC syndrome register. Acknowledge exception. */
    se_rfmci

ivr1_testIvor8:
    e_lis       r0, rtos_ivorVectorTableEntry8@ha
    e_add16i    r0, r0, rtos_ivorVectorTableEntry8@l    /* r0: Address System call handler */
    se_cmp      r0, r3          /* Both need to match to satisfy */

    /* r0 == r3: An IVOR #8 system call had started execution when being preempted by the
       imprecise IVOR #1. IVOR #8 doesn't need to be proceeded, it surely belongs to the
       failing task, which is aborted by the exception. */
    se_beq      ivr1_isUserCodeIvor1Exception

    e_lis       r0, rtos_ivorVectorTableEntry9@ha
    e_add16i    r0, r0, rtos_ivorVectorTableEntry9@l    /* r0: Address Debug IRQ handler */
    se_cmp      r0, r3          /* Both need to match to satisfy */

    /* r0 == r3: IVOR #9 started handling the exception when being preempted by the
       imprecise IVOR #1. IVOR #1 doesn't handle the problem but returns to the preempted
       IVOR #9. */
    se_beq      ivr1_continuePreemptedIvor  
    
    e_lis       r0, rtos_ivorVectorTableEntry10@ha
    e_add16i    r0, r0, rtos_ivorVectorTableEntry10@l   /* r0: Address EFP Data IRQ handler */
    se_cmp      r0, r3          /* Both need to match to satisfy */
    
    /* r0 == r3: IVOR #10 started handling the FPU execution when being preempted by the
       imprecise IVOR #1. The FPU exception must not be proceeded, it surely belongs to the
       failing task, which is aborted by this MC exception but the FPU exception handler
       would return to that task without any further action. */
    se_beq      ivr1_isUserCodeIvor1Exception
    
    e_lis       r0, rtos_ivorVectorTableEntry11@ha
    e_add16i    r0, r0, rtos_ivorVectorTableEntry11@l   /* r0: Address EFP Round IRQ handler */
    se_cmp      r0, r3          /* Both need to match to satisfy */
  
    /* r0 == r3: IVOR #11 started handling the FPU execution when being preempted by the
       imprecise IVOR #1. The FPU exception must not be proceeded, it surely belongs to the
       failing task, which is aborted by this MC exception but the FPU exception handler
       would return to that task without any further action. */
    se_beq      ivr1_isUserCodeIvor1Exception
    
    /* All anticipated cases have been checked in which we may occasionally see an MC
       exception in supervisor mode. Non of these cases applies and we need to halt SW
       execution. */
    se_b        rtos_ivr1_isOSCodeException

/* End of rtos_ivor1Handler */


/**
 *   @func rtos_ivor2Handler
 * This is the interrupt handler for the MCU trap #2, Data Storage Interrupt. See Core
 * RM, 5.7.3, p. 181. This exception relates to (see CRM, 5.1.2, Table 5-3, p. 164f):
 *  - Access control.
 *  - Byte ordering due to misaligned access across page boundary to pages with mismatched
 *    E bits
 *  - Cache locking exception - this is forbidden in user code
 */
    .section    .text.ivor
    .global     rtos_ivor2Handler
    .p2align    4
rtos_ivor2Handler:
    /* We don't need a preamble with storage of register contents of preempted context: We
       are anyway going to abort the execution of that context.
         We must not rely on any register content as got from the preempted context: It
       can be corrupted as effect of the fault, which let to the exception. This holds in
       particular for the EABI registers r2 and r13 and the stack pointer. */
    mfspr       r0, SPR_SRR1    /* Load MSR of preempted process */
    se_btsti    r0, 17      /* Test bit "problem state" */
    se_beq      .           /* assert(Problem state == user) */
    mfspr       r0, SPR_ESR
    e_lis       r3, 0xff4d  /* 0x00b200a0: Mask of possibly set ESR bits */
    e_or2i      r3, 0xff5f
    se_and      r0, r3
    mtspr       SPR_ESR, r0 /* SPR 62 = ESR, exception syndrome register. Acknowledge excep. */

    /* MSR is in desired state: EE=PR=0, CE and ME not affected by exception */

    se_li       r3, RTOS_CAUSE_TASK_ABBORTION_DI_STORAGE
    e_b         rut_endUserTaskByException   /* Do same as system call "task abort" */

/* End of rtos_ivor2Handler */





/**
 *   @func rtos_ivor3Handler
 * This is the interrupt handler for the MCU trap #3, Instruction Storage Interrupt. See Core
 * RM, 5.7.4, p. 181. This exception relates to (see CRM, 5.1.2, Table 5-3, p. 164f):
 *  - Access control.
 *  - Byte ordering due to misaligned instruction across page boundary to pages with
 *    mismatched VLE bits, or access to page with VLE set, and E indicating little-endian.
 *  - Misaligned Instruction fetch due to a change of flow to an odd half-word instruction
 *    boundary on a Power ISA (non-VLE) instruction page
 *   We don't have any Book E pages defined but the exception has been observed when trying
 * to execute peripheral address space.
 */
    .section    .text.ivor
    .global     rtos_ivor3Handler
    .p2align    4
rtos_ivor3Handler:
    /* We don't need a preamble with storage of register contents of preempted context: We
       are anyway going to abort the execution of that context.
         We must not rely on any register content as got from the preempted context: It
       can be corrupted as effect of the fault, which let to the exception. This holds in
       particular for the EABI registers r2 and r13 and the stack pointer. */
    mfspr       r0, SPR_SRR1    /* Load MSR of preempted process */
    se_btsti    r0, 17      /* Test bit "problem state" */
    se_beq      .           /* assert(Problem state == user) */
    mfspr       r0, SPR_ESR
    se_bclri    r0, 14      /* 0x00020022: Mask of possibly set ESR bits */
    se_bclri    r0, 26
    se_bclri    r0, 30
    mtspr       SPR_ESR, r0 /* SPR 62 = ESR, exception syndrome register. Acknowledge excep. */

    /* MSR is in desired state: EE=PR=0, CE and ME not affected by exception */

    se_li       r3, RTOS_CAUSE_TASK_ABBORTION_DI_STORAGE
    e_b         rut_endUserTaskByException   /* Do same as system call "task abort" */

/* End of rtos_ivor3Handler */





/**
 *   @func rtos_ivor4Handler
 * This is the interrupt handler for the MCU trap #4, External Interrupts. See Core RM,
 * 5.7.5, p. 183. This trap relates to interrupts controlled by the INTC (see CRM, 5.1.2,
 * Table 5-3, p. 164f). The INTC provides the vector to the appropriate service function
 * and handles the preemption or mutual exclusion of interrupts by providing an effective
 * priority scheme.\n
 *   The handler implementation here will save the CPU context onto the stack, read the
 * service function pointer and call this function. It'll then acknowledge the interrupt
 * (thereby triggering the priority handling of the INTC) restore the context and return
 * from interrupt.
 */
    .section    .text.ivor
    .global     rtos_ivor4Handler
    .extern     rtos_noEventsPending
    .p2align    4
rtos_ivor4Handler:

    /* Define the stack frame contents as offsets of data objects. Note the minimum offset
       of 8 due to the storage of stack pointer and link register. */
    #define O_SP            (8+0)   /* Process stack pointer */
    #define O_PID           (8+4)   /* Process ID, 1 Byte */
    #define O_SRRi          (8+8)   /* SRR0, SRR1: 2*4=8 Byte */
    #define O_CR            (8+16)  /* EABI volatile, CR, LR, CTR, XER: 4*4=16 Byte */
    #define O_R00           (8+32)  /* EABI volatile, r0, r3-r12: 11*4=44 Byte */
    #define SIZE_OF_PAYLOAD 76      /* Size of user data in stack frame */

    /* Size of stack frame: Room for SP and LR and uprounding to multiple of 8. */
    #define S_I4_StFr   ((((SIZE_OF_PAYLOAD)+15)/8)*8)
    #define O_LR        (SIZE_OF_SF+4)

    /* The stack is changed to the supervisor (SV) stack but only if we are currently
       executing a user task (as opposed to having preempted an ISR). The distinction is
       made with the CPU's register PID: A user task has a process ID other than zero.
         The value of the SV sp as it was on last recent switch to user (U) mode sp is
       stored in a global variable (SPR_G0_SVSP).
         Safety: The stack pointer (sp) switching needs to be done without using any
       current GPR contents: If we really come from U mode any expectations about their
       contents can be wrong due to whatever SW faults in the U code.
         A way to do is to apply the two EABI registers r2 and r13: Their nominal value is
       known (and can thus be restored later) and if the U code should have altered them,
       it's anyway one of the severe SW errors we have to deal with. If we later return to
       the U code with altered values it will not cause a failure but just alter the
       consequence of the true fault in the U code. */
    mfcr        r13
    mfspr       r2, SPR_PID0
    se_cmpli    r2, 1                   /* Test PID for special value 0, meaning OS */
    se_blt      ivr4_noSwitchSP
    mtcr        r13                     /* Restore CR for saving in stack frame, below */
    se_mtar     r13, sp                 /* Temporarily save sp@entry */
    mfspr       sp, SPR_G0_SVSP         /* Get SV sp@task start from global storage. */
    se_lwz      sp, RUT_O_pPDESC(sp)    /* sp: Pointer to descriptor of preempted process */
    e_stw       r13, O_PDESC_USP(sp)    /* sp@entry saved in process desc */
    mfspr       sp, SPR_G0_SVSP         /* Restore SV sp from global storage. */
    e_stw       r13, (O_SP-S_I4_StFr)(sp)   /* sp@entry saved in stack frame for later rfi */
    se_b        ivr4_endSwitchSP

    /** @todo Here, and having access to the pointer to the task and process information,
        we could easily implement an on-task-preemption hook or action. Together with the
        anyway existing on-task-resume hook or action it would be easy to implement
        execution budget supervision for tasks. */

ivr4_noSwitchSP:
    mtcr        r13
    e_stw       sp, (O_SP-S_I4_StFr)(sp) /* sp@entry saved in stack frame for later rfi */

ivr4_endSwitchSP:
    e_stwu      sp, -S_I4_StFr(sp)  /* Create stack frame for IVOR #4 handler */

    /* Store the process ID on entry. */
    se_stb      r2, O_PID(sp)    /* r2[24:31] stored in stack frame */

    /* Write kernel PID 0 to avoid repeated stack switching. This needs to be done prior to
       EE=1.
         Note, a sync operation is not required since we are not switching to another,
       PID-aware memory region. MMU and MPU grant all required permissions in SV mode. */
    se_li       r2, 0
    mtspr       SPR_PID0, r2

    /* Restore the changed EABI registers to their nominal value (which is the lost value
       at least for error free U code). This needs to be done prior to EE=1.*/
    mfspr       r2, SPR_G2_SDA2         /* Load .sdata2 base into r2 */
    mfspr       r13, SPR_G1_SDA         /* Load .sdata base into r13 */

    /* Store all GPRegisters and SPR, which are volatile according to the EABI. */
    e_stmvgprw  O_R00(sp)    /* r0, r3-r12: 11*4 Byte */
    e_stmvsprw  O_CR(sp)     /* CR, LR, CTR, XER: 4*4 Byte */
    e_stmvsrrw  O_SRRi(sp)   /* SRR0/SRR1: 2*4 Byte */

    /* Clear request to processor; afterwards, r3 contains the address of the ISR. On a
       multi-core derivative, the register to read, IACKR, is found for the calling core i
       at this address: INTC base + 10h offset + (4d × i), where i=0d to 1d (e.g. RM
       MPC5775B/E, 15.7.3, p545f). */
    mfspr       r3, SPR_PIR                 /* r3: idxCore */
    se_slwi     r3, 2                       /* r3: idxCore*sizeof(INTC_IACKRi) */
    e_add2is    r3, INTC_IACKR0@ha          /* Read pointer into ISR Vector Table
                                               rtos_INTCInterruptHandlerAry */
    e_lwz       r3, INTC_IACKR0@l(r3)       /* Load INTC_IACKR, which clears request to
                                               processor */
    se_lwz      r3, 0x0(r3)         /* Read address of interrupt service routine from
                                       ISR Vector Table using pointer  */

    /* For preemptable interrupt handlers set the EE bit in the MSR. The property
       preemptability of a handler is encoded as MSBit of the function pointer. */
    se_btsti    r3, 0
    se_beq      rtos_isr_endIfPreemptable
    se_bclri    r3, 0   /* Clear the flag bit to get the proper address back. */
    wrteei      1       /* Enable processor recognition of interrupts. */
rtos_isr_endIfPreemptable:
    se_mtlr     r3      /* Branch to ISR handler address found in service descriptor */
    se_blrl             /* Branch to ISR, but return here */

    /* Write 0 to INTC_EOIR, informing INTC to restore priority as it was on entry to this
       handler. On a multi-core derivative, the register to read, EOIR, is found for the
       calling core i at this address: INTC base + 18h offset + (4d × i), where i=0d to 1d
       (e.g. RM MPC5775B/E, 15.7.4, p546). */
    se_li       r3, 0
    mfspr       r4, SPR_PIR                 /* r4: idxCore */
    se_slwi     r4, 2                       /* r4: idxCore*sizeof(INTC_EOIR_PRCi) */
    e_add2is    r4, INTC_EOIR0@ha           /* Load upper half of INTC_EOIR address */
    wrteei      0   /* Disable interrupt processing prior to IRQ acknowledge at INTC */
    e_stw       r3, INTC_EOIR0@l(r4)        /* Write 0 to INTC_EOIR */

    /* The decision about task switches is taken in the C code implementation of the
       scheduler, rtos_osProcessTriggeredEvents(). However, before we do the expensive
       function call we evaluate an indicator.
         The pointer either points to an event to schedule or it is set to 0xffff_ffff. */
    mfspr       r5, SPR_G3_CDATA            /* r5: rtos_osGetInstancePtr() */
    e_lwz       r3, O_ID_NEXT_EV_TO_SCH(r5) /* r3: Event requires scheduling? */
    e_cmp16i    r3, -1
    se_beq      iv4_noCallOfScheduler
    
    /* We check for possible task switch because of an event being set in the ISR only if
       we return from the last ISR - but not (yet) if this is the return from a potential
       preempting, nested ISR. On a multi-core derivative, the register to check, CPR, is
       found for the calling core i at this address: INTC base + 8h offset + (4d × i),
       where i=0d to 1d (e.g. RM MPC5775B/E, 15.7.2, p544f). */
#if AT_HA(INTC_CPR0) != AT_HA(INTC_EOIR0)
# error Expect all INTC_xxx@ha to be identical. Code needs adaptation
#endif
    e_lwz       r4, INTC_CPR0@l(r4)     /* r4: Current IRQ priority in INTC */
    se_cmpli    r4, 1                   /* No activity if we are still in a nested ISR. */
    se_bge      iv4_noCallOfScheduler
    
    /* Run the scheduler if we have the indication of newly triggered events. This may
       involve a recursion inside of which new tasks are run.
         Note, to avoid stack overflow we need to enter the function still within the
       critical section, which we had started before signalling end of IRQ to the INTC. */
    se_subi     r4, 1               /* r4: UINT_MAX, i.e. indication of "pointer unset" */
    e_stw       r4, O_ID_NEXT_EV_TO_SCH(r5)     /* Clear pointer to triggered Event */
    e_bl        rtos_osProcessTriggeredEvents   /* r3: Event to be scheduler first */
    
iv4_noCallOfScheduler:
    /* Restore the process ID. A sync operation is not required since we are not switching
       to another, PID-aware memory region. MMU and MPU grant all required permissions in
       SV mode. */
    se_lbz      r0, O_PID(sp)   /* PID0 (1 Byte) loaded from stack frame */
    se_cmpi     r0, 0           /* Check if we return to the kernel process */
    mtspr       SPR_PID0, r0
    se_beq      iv4_retToPreemptedCtxt  /* CR0: Holds PID0!=0. 0: Return to other OS context */

    /* If we get here then we need to check the abort conditions of the otherwise resumed
       user task. */

    e_lwz       r3, (RUT_O_pPDESC+S_I4_StFr)(sp)/* Find pProcessDesc in parent stack frame */
    se_lbz      r3, O_PDESC_ST(r3)      /* r3: Process state: 0=stopped */
    se_cmpi     r3, 0
    se_beq      rut_endUserTaskByException  /* r3: 0=RTOS_CAUSE_TASK_ABBORTION_PROCESS_ABORT */
#if RTOS_CAUSE_TASK_ABBORTION_PROCESS_ABORT != 0
# error Inconsistency in interface definition of assembler code
#endif

    e_lwz       r3, (RUT_O_tiAvl+S_I4_StFr)(sp)/* Find max end time in parent stack frame */
    se_cmpi     r3, 0                   /* r3: End time, deadline. 0=Monitoring off */
    se_beq      iv4_retToPreemptedCtxt  /* Return to other OS context. */

#if 0 /* Other Z4/Z7 cores use: */
    mfspr       r4, SPR_TBL /* r4: Current time */
#else
    e_lis       r4, STM_0_CNT@ha    /* STM_0_CNT: Free running counter at 80 MHz. */
    e_lwz       r4, STM_0_CNT@l(r4) /* r4: Current time */
    se_sub      r3, r4      /* r3: Remaining time budget */
#endif
    se_cmpi     r3, 0       /* Compare: Budget >= 0? Wraps only after about 26s at 80 Mhz */
    se_bge      iv4_retToPreemptedCtxt  /* Yes, end time >= current time, okay. */
    se_li       r3, RTOS_CAUSE_TASK_ABBORTION_DEADLINE
    se_b        rut_endUserTaskByException

iv4_retToPreemptedCtxt:
    /* Restore all GPRs and SPRs, which are volatile according to the EABI. */
    e_lmvgprw   O_R00(sp)    /* r0, r3-r12: 11*4 Byte */
    e_lmvsprw   O_CR(sp)     /* CR, LR, CTR, XER: 4*4 Byte. Could be done earlier, when
                                   still EE=1 */
    e_lmvsrrw   O_SRRi(sp)   /* SRR0/SRR1: 2*4 Byte */

    /* Remove the no longer needed stack frame by restoring the stack pointer. This can
       mean a switch back to the user task's sp. */
    se_lwz      sp, O_SP(sp)

    #undef O_SP
    #undef O_PID
    #undef O_pISD
    #undef O_SRRi
    #undef O_CR
    #undef O_R00
    #undef SIZE_OF_PAYLOAD
    #undef S_I4_StFr
    #undef O_LR

    /* End of interrupt, restore MSR and PC from the SRR0/1. */
    se_rfi

/* End of rtos_ivor4Handler */



/**
 *   @func rtos_osRunUserTask
 * Entry point from C source code: Function rtos_osRunUserTask.\n
 *   Some C code running in SV mode can call this function to execute a C function as
 * single-shot user task. The function is executed once in user mode and under given PID.
 * rtos_osRunUserTask handles the return from this executed C function, which requires a
 * switch back to supervisor mode and it implements the unconditional abortion of the
 * function (in case of errors or on explicit demand).\n
 *   rtos_osRunUserTask can be called from the OS context only, e.g. ISRs and/or the OS owned
 * idle task.
 *   @return
 * The function normally returns the return value got from the C executed function in r3.\n
 *   If it is aborted by an exception, then the one's complement of the error code defined in
 * rtos_ivorHandler.h is returned instead (see #RTOS_CAUSE_TASK_ABBORTION_PROCESS_ABORT and
 * following), which is the same as UINT_MAX-errorCode.\n
 *   The return value is declared signed in the C interface and user code should only return
 * positive integers. This convention allows to easily check for abnormal task termination:
 * A negative value is returned.
 *   @param pUserTaskConfig
 * r3 contains the pointer to a struct of type rtos_userTaskConfig_t holding the constant
 * configuration data of the task, where e.g. the pointer to the C function to execute can
 * be found. This object is read only and needs to be located in a memory area, where it
 * can not be changed by any task code.
 *   @param taskParam
 * r4 contains a 32 Bit value, which is forwarded to the executed C function as second
 * argument. (Its first argument is the process ID.)
 */
    .section    .text.rtos_osRunUserTask
    .global     rtos_osRunUserTask, rtos_osRunInitTask
    .balign     2

    /* The stack frame of this function is accessed from different code locations, e.g. to
       implement task abortion. Therefore the details of the stack frame contents (field
       offsets) are globally defined in the header file.
         Size of stack frame: Room for SP and LR and uprounding to multiple of 8. */
    #define SIZE_OF_SF      ((((RUT_SIZE_OF_SF_PAYLOAD)+15)/8)*8)
    #define O_LR            (SIZE_OF_SF+4)

rtos_osRunUserTask:
    /* Compute the pointer to the process descriptor from the PID in the task configuration. */
    se_lbz      r6, O_TCONF_pid(r3)
    se_mtar     r8, r6                  /* r8: Aimed PID for task */
    se_subi     r6, 1                   /* r6: idxProcess */
#ifdef DEBUG
    se_cmpli    r6, 3
    se_bgt      .                       /* assert(PID >= 1  &&  PID <= 4); */
#endif
#if SIZE_OF_PROCESS_DESC == 64
    se_slwi     r6, 6
#else
# error Optimize multiplication with constant
    e_mull2i    r6, SIZE_OF_PROCESS_DESC
#endif
    mfspr       r7, SPR_G3_CDATA        /* r7: rtos_osGetInstancePtr() = processAry */
#if O_ID_PROC_ARY != 0
# error Expect processAry to be first element of instance data structure
#endif
    se_add      r6, r7                  /* r6: &processAry[PID] */

    /* We check the process abort condition. The scheduler will set the process abort
       flag asynchronous to the actual task execution. So it may be set even before we
       enter the task. */
    se_lbz      r7, O_PDESC_ST(r6)      /* r7: Process status, 0=stopped */
    se_cmpi     r7, 0
    se_bne      rut_continueTaskExecution
    e_li        r3, ~RTOS_CAUSE_TASK_ABBORTION_PROCESS_ABORT /* Load agreed function result */
    se_blr                          /* Do not execute function, return immediately */

/**
 * Continuation of code before and entry point from C source code: Function
 * rtos_osRunInitTask().\n
 *   This function is nearly the same as rtos_osRunUserTask() with the only exception that
 * the process state is not evaluated; the init function must be called while the process
 * is not yet enabled.\n
 *   For copy the function entry code rather than making a dynmic descision - it are just a
 * few instructions to duplicate.
 */
rtos_osRunInitTask:
    /* Compute the pointer to the process descriptor from the PID in the task configuration. */
    se_lbz      r6, O_TCONF_pid(r3)
    se_mtar     r8, r6                  /* r8: Aimed PID for task */
    se_subi     r6, 1                   /* r6: idxProcess */
#ifdef DEBUG
    se_cmpli    r6, 3
    se_bgt      .                       /* assert(PID >= 1  &&  PID <= 4); */
#endif
#if SIZE_OF_PROCESS_DESC == 64
    se_slwi     r6, 6
#else
# error Optimize multiplication with constant
    e_mull2i    r6, SIZE_OF_PROCESS_DESC
#endif
    mfspr       r7, SPR_G3_CDATA        /* r7: rtos_osGetInstancePtr() = processAry */
#if O_ID_PROC_ARY != 0
# error Expect processAry to be first element of instance data structure
#endif
    se_add      r6, r7                  /* r6: &processAry[PID] */

rut_continueTaskExecution:
    /* Create stack frame and save stack pointer and return address. */
    e_stwu      sp, -SIZE_OF_SF(sp)
    se_mflr     r0
    #if O_LR <= 60
    se_stw      r0, O_LR(sp)
    #else
    e_stw       r0, O_LR(sp)
    #endif

    /* We prepare the abort condition. It may be that we have to set a time budget. */
    se_lwz      r0, O_TCONF_tiMax(r3)   /* Load time budget specified for task */
    se_cmpi     r0, 0                   /* Deadline monitoring demanded? Not if zero */
    se_beq      rut_noTimeBudget        /* No termination condition to be prepared */
#if 0 /* Other Z4/Z7 cores use: */
    mfspr       r7, SPR_TBL             /* r7: Current time */
#else
    e_lis       r7, STM_0_CNT@ha        /* STM_0_CNT: Free running counter at 80 MHz. */
    e_lwz       r7, STM_0_CNT@l(r7)     /* r7: Current time */
#endif
    se_add      r0, r7                  /* r0: End of permitted time */
    se_bseti    r0, 31                  /* Avoid end time 0, which means "no monitoring" */
rut_noTimeBudget:
    se_stw      r0, RUT_O_tiAvl(sp)     /* Store time budget for check at task resume */
    se_stw      r6, RUT_O_pPDESC(sp)    /* Store the pointer to save computation later. */

    /* A user task is started. For a "safe" RTOS it is inevitable that all user accessible
       registers are stored in user inaccessible RAM and restored after return from the
       user code. (For a conventional RTOS it would suffice to rely on the EABI and save
       only the volatile registers.) The common part of the IVOR #4 handler has already saved
       the volatile registers, now we do the same for the non volatile. */
    e_stmw      r14, RUT_O_NVGPR(sp)

    /* Store the current task priority at task start. This is a prerequiste of a protected
       implementation of the system calls for the priority ceiling protocol. */
    mfspr       r7, SPR_G3_CDATA        /* r7: rtos_osGetInstancePtr() */
    e_lwz       r7, O_ID_CUR_PRIO(r7)   /* r7: rtos_kernelInstanceData_coreN.currentPrio */
    se_stw      r7, RUT_O_CPR(sp)       /* Store it for use by PCP system call */

    /* Let LR point to a system call for task termination. This permits the user code to
       end a task gracefully by return. */
    e_lis       r7, rtos_terminateUserTask@ha
    e_la        r7, rtos_terminateUserTask@l(r7)
    se_mtlr     r7

    /* The value of the SV sp at start of user task (i.e. the pointer to the stack frame of
       this function) is globally stored. The stack frame contents are accessed by several
       services, which relate to the now started task, task abortion in the first place.
         The now started task (temporarily) supersedes a previously started other task of
       lower priority and we save the stack frame pointer of the other task until
       termination of the now started task.
         The new global pointer is at the same time the correct SV sp value when it comes
       to a preemption of the now started task. */
    mfspr       r7, SPR_G0_SVSP         /* Find SV sp value of last user task preemption */
    se_stw      r7, RUT_O_SVSP(sp)      /* in global storage. Store it in stack frame */

    /* Because the save location for the SV sp is a global data object, we need to do
       - saving SV sp in global object
       - loading U sp
       - saving U sp in local stack frame for later restoring
       - putting process ID in PID0
       in a critical section. Doing all of this means shaping the new user code context
       (even if it is still executed in SV mode), which may be safely preempted by IVOR #4
       interrupts of higher priority. */
    wrteei      0
    mtspr       SPR_G0_SVSP, sp         /* Store SV sp value in freed global storage */

    /* Set aimed process ID in CPU. A sync operation is not required since we do not depend
       on switching to another, PID-aware memory region descriptor. MMU and MPU grant all
       required permissions in SV mode. The se_rfi at latest synchronizes for all what
       matters to the new user task. */
    mtspr       SPR_PID0, r8

    /* We take the start value of the U sp for the now started user task from its process
       descriptor, still held in r6. */
    se_lwz      r7, O_PDESC_USP(r6)    /* Save the U sp in the local stack frame: We need
                                          to be able to restore this value as process U sp
                                          (for future task starts in this process) in case
                                          of task abortion.
                                            Note, the value stored in the process
                                          descriptor is invalid even on graceful return
                                          from the user task: Intermittent preemptions of
                                          the ending task will have overwritten the value. */
    se_stw      r7, RUT_O_USP(sp)
    se_mr       sp, r7      /* Switch to U sp. Local stack frame is no longer accessible. */

    /* The user context is shaped. We could allow preemptions again but the next
       instructions require a critical section again to protect the global SRRi registers. */

    /* We will use the se_rfi instruction for the branch to the user specified handler and
       the simultaneous switch to U mode. It changes execution mode and MSR[EE] flag at the
       same instance and forces reloading of future instructions (sync instruction), which
       is essential for immediately applying the memory protection rules of the new user
       context.
         We load the handler address into SRR0 and execution mode settings into SRR1. */
    se_lwz      r7, O_TCONF_pFct(r3)/* r3: Still holds address of task config */
    mtspr       SPR_SRR0, r7
    e_li        r7, 0xd000          /* MSR: EE=1, Machine check IRQ and problem state */
    mtspr       SPR_SRR1, r7

    /* Run user task code in U mode. */
    se_mfar     r3, r8  /* 1st argument: PID. r4 still holds C code specified 2nd argument */
    se_rfi


/**
 * Entry point from C source code: Function rtos_terminateUserTask(). See alias
 * rtos_terminateTask() in rtos.h, too.
 */
    .section    .text.ivor
    .global     rtos_terminateUserTask
rtos_terminateUserTask:
    se_mr       r4, r3  /* Return value of user function becomes argument of sys call */
    se_li       r3, 0   /* Still part of user task code: System call 0 to terminate/abort */
    se_sc               /* a task. */

    /* All code down here is executed in SV mode, but coming from user process. A "safe"
       implementation must not do any memory access, which is based on register values
       coming from the user code. Particularly, sp and the SDA pointers r2 and r13 must not
       be trusted.
         It is essential that EE=0 still holds and until we have returned to the kernel
       mode (PID0=0) and have restored the global context data. */
    .global     rtos_scBscHdlr_terminateUserTask    /* Global as it is element of table of
                                                       system calls */
rtos_scBscHdlr_terminateUserTask:
    /* Here we get from the common part of the IVOR #8 handler (system call). */
    mfspr       sp, SPR_G0_SVSP     /* Restore SV sp */
    e_lwz       r6, RUT_O_pPDESC(sp)/* r6: Retrieved address of process descriptor */
    se_cmpi     r4, 0               /* Arg of sys call < 0: User reported errore */
    se_bge      rut_endWithoutErr   /* Skip counting cause of termination: Normal situation */
    se_li       r3, RTOS_CAUSE_TASK_ABBORTION_USER_ABORT    /* Array idx for err counter */
    e_li        r4, ~RTOS_CAUSE_TASK_ABBORTION_USER_ABORT /* r4: ret code of osRunUserTask() */
    se_b        rut_endWithErr

    .global     rtos_osSystemCallBadArgument
rtos_osSystemCallBadArgument:
    /* Here we can jump from a system call handler implementation if an error appears,
       which is a) anticipatable by the calling user task and b) hinders the system call
       from succesful completion. The result is that the user task is aborted and the error
       is counted as #RTOS_CAUSE_TASK_ABBORTION_SYS_CALL_BAD_ARG. Condition a) is required
       for a task must be aborted only if the fault is clearly at the side of the user
       code. It'll mostly be something like argument out of specified range. */

    .global     rtos_scBscHdlr_sysCallUndefined
rtos_scBscHdlr_sysCallUndefined:
    /* This is the system call handler for otherwise empty entries in the system call
       table, i.e. it is the system call default handler. The user task, which invoked the
       system call is aborted and the error is counted in the process the task belongs to. */
    se_li       r3, RTOS_CAUSE_TASK_ABBORTION_SYS_CALL_BAD_ARG

rut_endUserTaskByException:
    /* If an exception jumps here, it'll have loaded r3 with its ID, the cause of
       termination. */
    mfspr       sp, SPR_G0_SVSP     /* Restore SV sp */

    /* In case of unexpected task termination, rtos_osRunUserTask returns the negative
       errorCode. A negative number is chosen to have a intuitive distinction from user
       code returned normal (=positive) return values. Note, we need to use the one's
       complement since the error codes form a zero based index. 0: return -1, 1: return
       -2, a.s.o. */
    se_mr       r4, r3
    se_not      r4

    /* Count the cause of the termination. */
    e_lwz       r6, RUT_O_pPDESC(sp)/* r6: Retrieved address of process descriptor */
rut_endWithErr:
#ifdef DEBUG
    se_cmpli    r3, RTOS_NO_CAUSES_TASK_ABORTION
    se_bge      .                   /* assert(idxCause < RTOS_NO_CAUSES_TASK_ABORTION) */
#endif
    se_slwi     r3, 2               /* Size of counter is 4 Byte */
    se_addi     r3, O_PDESC_CNTTARY /* Add offset of array of cause counters in descriptor */
    lwzx        r5, r6, r3
    e_addi.     r5, r5, 1
    se_beq      rut_saturateCnt     /* Avoid wrapping around of failure counter */
    stwx        r5, r6, r3
rut_saturateCnt:
    se_lwz      r5, O_PDESC_CNTTOT(r6)
    e_addi.     r5, r5, 1
    se_beq      rut_saturateTotalCnt   /* Avoid wrapping around of failure counter */
    se_stw      r5, O_PDESC_CNTTOT(r6)
rut_saturateTotalCnt:

rut_endWithoutErr:
    mfspr       r2, SPR_G2_SDA2     /* Repair possibly destroyed .sdata2 base in r2 */
    mfspr       r13, SPR_G1_SDA     /* Repair possibly destroyed .sdata base in r13 */

    /* The remaining GPR, etc., don't require restore or repair, they will be restored in
       the normal function prologues, here and in the IVOR #4 handler, which we will return
       to. */

    /* Reset the process ID in the CPU to OS. A sync operation is not required since we do
       not depend on switching to another, PID-aware memory region descriptor. (MMU and MPU
       have a descriptor, which grants all required permissions in SV mode.) */
    se_li       r3, 0
    mtspr       SPR_PID0, r3

    /* Restore the saved value of the SV sp. Now, it is the value at which this user task
       had switched to the U sp and we will now restore the according value from the next
       user task down the calling hierarchy. */
    se_lwz      r3, RUT_O_SVSP(sp)
    mtspr       SPR_G0_SVSP, r3

    /* Restore the U sp in the process descriptor. It is the value to use for newly started
       tasks in this process. The location to store can be found easily as we still have
       the pointer to the process descriptor in r6. */
    se_lwz      r3, RUT_O_USP(sp)
    se_stw      r3, O_PDESC_USP(r6) /* U sp as we had started the now ending task with */

    /* Process context is completely reset to kernel mode. We can again permit preemptions. */
    wrteei      1
    
    /* The end of the user task is not necessarily the end of processing the causing event;
       several tasks can be associated with a single event, which means that they are
       consecutively run in one and the same OS context. We must not rely on the current
       priority value as left by the ending task. We need to restore already before a
       potential entry in a subsequent user task. Note, these operations are nearly always
       useless. */
    se_lwz      r0, RUT_O_CPR(sp)       /* r0: Prio of user task start */
    mfspr       r5, SPR_G3_CDATA        /* r5: rtos_osGetInstancePtr() */
    e_lwz       r3, O_ID_CUR_PRIO(r5)   /* r3: Current prio value, to be checked */
    se_cmpl     r0, r3
#ifdef DEBUG
    se_bgt      .                       /* assert(prio@TaskStart <= rtos_currentPrio); */
#endif
    se_beq      rut_noRestoreCPR        /* r0==r3: No restore of current prio required */
    e_stw       r0, O_ID_CUR_PRIO(r5)   /* Restore priority in global instance data */
    .extern     rtos_osGetEventByPriority
    e_bl        rtos_osGetEventByPriority/* r3: prio before restore -> pEvent with that prio */
    wrteei      0             /* Call of rtos_osProcessTriggeredEvents requires MSR[EE] = 0 */
    e_bl        rtos_osProcessTriggeredEvents /* Check for possible task switches */
    wrteei      1
rut_noRestoreCPR:

    /* Restore the non volatile registers. This would not be required for a gracefully
       terminating, error free user task, but is essential for failing or aborted tasks. We
       need to do this always since there's no means to make this distinction. */
    e_lmw       r14, RUT_O_NVGPR(sp)

    se_mr       r3, r4  /* Arg of sys call to terminate is still in r4 but returned in r3 */

    /* Remove the no longer needed stack frame and return. */
    #if O_LR <= 60
    se_lwz      r0, O_LR(sp)
    #else
    e_lwz       r0, O_LR(sp)
    #endif
    se_mtlr     r0
    #if SIZE_OF_SF <= 32
    se_addi     sp, SIZE_OF_SF
    #else
    e_add16i    sp, sp, SIZE_OF_SF
    #endif
    se_blr

    #undef SIZE_OF_SF
    #undef O_LR

/* End of rtos_osRunUserTask */



/**
 *   @func rtos_ivor5Handler
 * This is the interrupt handler for the MCU trap #5, Alignment. See Core RM, 5.7.6,
 * p. 183. This exception relates to (see CRM, 5.1.2, Table 5-3, p. 164f):
 *   - lmw, stmw not word aligned
 *   - lwarx or stwcx. not word aligned, lharx or sthcx. not half-word aligned
 *   - dcbz with disabled cache, or to W or I storage
 *   - SPE ld and st instructions not properly aligned
 */
    .section    .text.ivor
    .global     rtos_ivor5Handler
    .p2align    4
rtos_ivor5Handler:
    /* We don't need a preamble with storage of register contents of preempted context: We
       are anyway going to abort the execution of that context.
         We must not rely on any register content as got from the preempted context: It
       can be corrupted as effect of the fault, which let to the exception. This holds in
       particular for the EABI registers r2 and r13 and the stack pointer. */
    mfspr       r0, SPR_SRR1    /* Load MSR of preempted process */
    se_btsti    r0, 17      /* Test bit "problem state" */
    se_beq      .           /* assert(Problem state == user) */
    e_lis       r3, 0xff7f  /* 0x008000a0: Mask of possibly set ESR bits: VLEMI (26, 0x20), */
    e_or2i      r3, 0xff5f  /* SPE (24, 0x80) ST (8, 0x00800000) */
    mfspr       r0, SPR_ESR
    se_and      r0, r3
    mtspr       SPR_ESR, r0 /* SPR 62 = ESR, exception syndrome register. Acknowledge excep. */

    /* MSR is in desired state: EE=PR=0, CE and ME not affected by exception */

    se_li       r3, RTOS_CAUSE_TASK_ABBORTION_ALIGNMENT
    e_b         rut_endUserTaskByException   /* Do same as system call "task abort" */

/* End of rtos_ivor5Handler */




/**
 *   @func rtos_getInstancePtr
 * All data in use by the kernel is bundled in a large struct. If the RTOS is run on an MCU
 * with several cores then each core uses its own dedicated instance of this struct. This
 * function returns the struct to use by reference.
 *   @return
 * Get the instance pointer to the RTOS data set.
 *   @remark
 * This function may be called from all contexts. However, OS contexts shouldn't
 * because of the performance penalty. They should only use rtos_osGetInstancePtr()
 * instead.
 *   @remark
 * The MPC5748G doesn't have the read-only user SPRG registers, which the RTOS normally
 * applies to make the instance pointer permanently available in a performant way. We use
 * the IVOR #6 handler as a kind of cheaper system call for the implementation of this
 * frequently called function; we try and if we fail then the IVOR #6 handler completes the
 * operation in the desired way. The penalty for the normal IVOR #6 operation is irrelevant
 * since the handler is not part of normal data flow.
 */
    .section    .text
    .global     rtos_getInstancePtr
    .balign     2
rtos_getInstancePtr:
    /* We put a synchronization instruction here in order to make all pending exceptions
       happen before we by intention provoke a privileged exception. Without the mbar it
       could rarely happen that an MPU exception is masked by the privileged exception
       caused here. A memory protection exception from an error shortly before the call of
       this function could be delayed beyond the privileged instruction mfspr, which we
       have a few lines down here. The entry into the IVOR #6 handler will force the
       pending MPU exception to occur, the IVOR #1 handler will preempt the beginning IVOR
       #6 handler and it'll analyse this as a rare but normal double exception.
       Consequently it returns to the preempted IVOR #6 and let it go. The IVOR #6 doesn't
       see any particular problem and would complete the action of rtos_getInstancePtr.
         Note, this situation wouldn't be harmful or even safety critical; it just meant
       that a bad instruction is skipped without recording the event or punishing the
       related process. */
    mbar
gip_srr0AtUserCodeException:
    mfspr       r3, SPR_G3_CDATA    /* OS code in SV mode will simply load the instance ptr */
    se_blr                          /* ... and return. User code won't get here: exception */

/* End of rtos_getInstancePtr */



/**
 *   @func rtos_getIdxCore
 * This function returns the contents of CPU read-only register PIR.
 *   @return
 * Get the index of the core the calling code is running on. The range is 0..2, meaning
 * Z4A, Z4B, Z2, respectively.
 *   @remark
 * This function may be called from all contexts. However, OS contexts shouldn't because of
 * the performance penalty. They should only use the intrinsic rtos_osGetIdxCore() instead.
 */
    .section    .text
    .global     rtos_getIdxCore
    .balign     2
rtos_getIdxCore:
    /* We put a synchronization instruction here in order to make all pending exceptions
       happen before we by intention provoke a privileged exception. Without the mbar it
       could rarely happen that an MPU exception is masked by the privileged exception
       caused here. A memory protection exception from an error shortly before the call of
       this function could be delayed beyond the privileged instruction mfspr, which we
       have a few lines down here. The entry into the IVOR #6 handler will force the
       pending MPU exception to occur, the IVOR #1 handler will preempt the beginning IVOR
       #6 handler and it'll analyse this as a rare but normal double exception.
       Consequently it returns to the preempted IVOR #6 and let it go. The IVOR #6 doesn't
       see any particular problem and would complete the action of rtos_getIdxCore.
         Note, this situation wouldn't be harmful or even safety critical; it just meant
       that a bad instruction is skipped without recording the event or punishing the
       related process. */
    mbar
gic_srr0AtUserCodeException:
    mfspr       r3, SPR_PIR     /* OS code in SV mode will simply load the processor ID */
    se_blr                      /* ... and return. User code won't get here: exception */

/* End of rtos_getIdxCore */



/**
 *   @func rtos_getCoreStatusRegister
 * Get the value of the msr. This is an entry point to C code, which can be called from
 * supervisor and user mode.
 *   @return
 * Get the current contents of register MSR on the code executing core.
 *   @remark
 * This function can be called from OS and user code. OS code should however better use an
 * intrinsic to read the MSR and in order to save the function call overhead.
 */
    .global     rtos_getCoreStatusRegister
    .balign     2
rtos_getCoreStatusRegister:
    mbar        /* See explanation in rtos_getInstancePtr */
gcs_srr0AtUserCodeException:
    mfmsr       r3      /* OS code in SV mode will simply read the MSR */
    se_blr              /* ... and return. User code won't get here: exception */

/* End of rtos_getCoreStatusRegister. */



/**
 *   @func rtos_ivor6Handler
 * This is the interrupt handler for the MCU trap #6, Progam Interrupt. See Core RM, 5.7.7,
 * p. 184. This exception relates to (see CRM, 5.1.2, Table 5-3, p. 164f):
 *   - Illegal, privileged, trap, FP enabled, AP enabled, unimplemented operation
 */
    .section    .text.ivor
    .global     rtos_ivor6Handler
    .p2align    4
rtos_ivor6Handler:
    /* We don't need a preamble with storage of register contents of preempted context: We
       are anyway going to abort the execution of that context.
         We must not rely on any register content as got from the preempted context: It
       can be corrupted as effect of the fault, which let to the exception. This holds in
       particular for the EABI registers r2 and r13 and the stack pointer. */

    /* See rtos_getInstancePtr: Maybe we got here because user code has called this
       function - which is legal. If so, we have to complete the function call. We do it
       first as it has the highest priority; rtos_getInstancePtr() is a frequently called
       system function. */
    e_lis       r3, gip_srr0AtUserCodeException@ha
    e_add16i    r0, r3, gip_srr0AtUserCodeException@l
    mfspr       r3, SPR_SRR0    /* r3: Point of exception */
    se_cmpl     r3, r0          /* Is it in function rtos_getInstancePtr? */
    se_bne      iv6_checkForGetIdxCore  /* No, go ahead */
    se_mflr     r3              /* r3: Wanted return address from function */
    mtspr       SPR_SRR0, r3    /* We want to return with rfi in order to restore the msr */
    se_li       r3, 0           /* ESR: PPR, VLEMI = 0x04000020 are set (RM 62.8.5.7) */
    mtspr       SPR_ESR, r3     /* Fastest way to clear the bits, clearing irrelated bits
                                   is tolerated for sake of higher function performance. */
    mfspr       r3, SPR_G3_CDATA  /* r3: Instance pointer for return to user code */
    se_rfi                      /* End the call of rtos_getInstancePtr with result */

iv6_checkForGetIdxCore:
    /* See rtos_getIdxCore: Maybe we got here because user code has called that
       function - which is legal. If so, we have to complete the function call. */
    se_addi     r0, (gic_srr0AtUserCodeException-gip_srr0AtUserCodeException)
    mfspr       r3, SPR_SRR0    /* r3: Point of exception */
    se_cmpl     r3, r0          /* Is it in function rtos_getIdxCore? */
    se_bne      iv6_checkForGetCoreStatusRegister   /* No, go ahead */
    se_mflr     r3              /* r3: Wanted return address from function */
    mtspr       SPR_SRR0, r3    /* We want to return with rfi in order to restore the msr */
    se_li       r3, 0           /* ESR: PPR, VLEMI = 0x04000020 are set (RM 62.8.5.7) */
    mtspr       SPR_ESR, r3     /* Fastest way to clear the bits, clearing irrelated bits
                                   is tolerated for sake of higher function performance. */
    mfspr       r3, SPR_PIR     /* r3: MSR at point of exception for return to user code */
    se_rfi                      /* End the call of rtos_getIdxCore with result */
        
iv6_checkForGetCoreStatusRegister:
    /* See rtos_getCoreStatusRegister: Maybe we got here because user code has called that
       function - which is legal. If so, we have to complete the function call. */
    se_addi     r0, (gcs_srr0AtUserCodeException-gic_srr0AtUserCodeException)
    mfspr       r3, SPR_SRR0    /* r3: Point of exception */
    se_cmpl     r3, r0          /* Is it in function rtos_getCoreStatusRegister? */
    se_bne      iv6_isTrueIvor6Exception    /* No, handle as process fault */
    se_mflr     r3              /* r3: Wanted return address from function */
    mtspr       SPR_SRR0, r3    /* We want to return with rfi in order to restore the msr */
    se_li       r3, 0           /* ESR: PPR, VLEMI = 0x04000020 are set (RM 62.8.5.7) */
    mtspr       SPR_ESR, r3     /* Fastest way to clear the bits, clearing irrelated bits
                                   is tolerated for sake of higher function performance. */
    mfspr       r3, SPR_SRR1    /* r3: MSR at point of exception for return to user code */
    se_rfi                      /* End the call of rtos_getCoreStatusRegister with result */
        
iv6_isTrueIvor6Exception:
    mfspr       r0, SPR_SRR1    /* Load MSR of preempted process */
    se_btsti    r0, 17          /* Test bit "problem state" */
    se_beq      .               /* assert(Problem state == user) */
    e_lis       r3, 0xf0fb      /* 0x0f040020: Mask of possibly set ESR bits */
    e_or2i      r3, 0xffdf
    mfspr       r0, SPR_ESR
    se_and      r0, r3
    mtspr       SPR_ESR, r0 /* SPR 62 = ESR, exception syndrome register. Acknowledge excep. */
    /* MSR is in desired state: EE=PR=0, CE and ME not affected by exception */

    se_li       r3, RTOS_CAUSE_TASK_ABBORTION_PROGRAM_INTERRUPT
    e_b         rut_endUserTaskByException   /* Do same as system call "task abort" */

/* End of rtos_ivor6Handler */



/**
 *   @func rtos_ivor7Handler
 * This is the interrupt handler for the MCU trap #7, Performance Monitor interrupt. See RM
 * 59.5.5.8, p. 2906. This exception relates to performanc emonitor events, if they are not
 * re-directed to the debug interrupt #9 by setting PMGC0[UDI]=1.\n
 *   We have globally disabled the performance monitor by setting PMGC0[PMIE]=0 and won't
 * ever see this exception.
 */
    .section    .text.ivor
    .global     rtos_ivor7Handler
    .p2align    4
rtos_ivor7Handler:
    /* We have globally disabled the performance monitor by setting PMGC0[PMIE]=0 and should
       never see this exception. We consider it a fatal error if we ever get here and want
       to halt the SW execution in this case.
         MSR[EE] is 0 on entry. */
    se_beq      .           /* assert(false); PMGC0[PMIE]=0, we must not see this exception */

/* End of rtos_ivor7Handler */



/**
 *   @func rtos_ivor8Handler
 * This is the interrupt handler for the MCU trap #8, System Call. See CRM, 5.7.9,
 * p. 184.\n
 *   In our RTOS we have a static ROM table of system call handlers.\n
 *   The main purpose of the system call is the switch to the supervisor mode. For many
 * simple operation system services this plus a few machine instructions, e.g. to read an
 * I/O register value can be enough as an implementation. However, more complex services,
 * which it is desirable for to do the implementation in C code, require more preparatory
 * work. Therefore, we define a system call not simply as a function pointer but as a
 * pointer to a descriptor objects. Through the properties of the object we can specify the
 * complexity of and required support for the service implementation.
 *   @param r3
 * r3: The index of the system call in the range 0 .. #RTOS_NO_SYSTEM_CALLS.
 *   @param rn
 * r4 .. r10: The GPR 4 till 10 contain the permitted up to 7 function arguments. Each of
 * them needs to have up to 32 Bit. 64 Bit arguments are not supported for function calls.
 */
    .section    .text.ivor
    .global     rtos_ivor8Handler
    .p2align    4

rtos_ivor8Handler:

    /* It is a most typically occuring error to make a system call from operating system
       code (as the system call instruction is somewhere hidden in a normally looking C
       style function) and we add an according assertion here; if we wait until the code
       really fails then it's much harder to debug the cause. If your code hangs in this
       assertion then you just have to inspect the SPR SRR0 or the call stack to find the
       code location, which had run made the system call although in was executed in
       supervisor mode. */
#ifdef DEBUG
    e_cmpl16i   r3, RTOS_SYSCALL_ASSERT_FUNC    /* A few system calls may safely be done */
    se_beq      ivr8_isSVEnabledSysCall         /* from SV code. We check them explicitly. */
    mfspr       r0, SPR_SRR1    /* Load MSR of preempted process */
    se_btsti    r0, 17          /* Test bit "problem state" */
    se_beq      .               /* assert(Problem state == user); (see above) */
ivr8_isSVEnabledSysCall:
#endif

#if RTOS_NO_SYSTEM_CALLS > 0  &&  RTOS_NO_SYSTEM_CALLS <= 65535
# if RTOS_NO_SYSTEM_CALLS <= 32
    se_cmpli    r3, RTOS_NO_SYSTEM_CALLS      /* Index out of range? */
# else
    e_cmpl16i   r3, RTOS_NO_SYSTEM_CALLS      /* Index out of range? */
# endif
#else
# error Number of system calls out of range
#endif
    e_bge       rtos_osSystemCallBadArgument  /* Index out of range: Abort task */

#if SIZE_OF_SC_DESC != 8
# error Assembler code requires adaptation. (Multiplication index with size of struct)
#endif
#if !(E_SCDESC_basicHdlr < E_SCDESC_simpleHdlr  &&  E_SCDESC_simpleHdlr < E_SCDESC_fullHdlr)
# error Assembler code requires adaptation. (Definition of properties of system call handler)
#endif

    e_slwi      r0, r3, 3                   /* r0: idxSC*SIZE_OF_SC_DESC */
    mfspr       r3, SPR_G3_CDATA            /* r3: rtos_osGetInstancePtr() */
    e_lwz       r3, O_ID_SYS_CALL_TBL(r3)   /* r3: &systemCallDescAry[0] */
    se_add      r3, r0                      /* r3: &systemCallDescAry[idxSysCall] */

    se_lwz      r0, O_SCDESC_confCls(r3)    /* r0: Conformance class of system call handler. */
    se_cmpli    r0, E_SCDESC_simpleHdlr
    se_bge      ivr8_noStartBasicHandler

    /* Start of an assembler implemented, basic handler: No stack, no preemption. Intended
       for short, efficient handlers, which consist of only a few machine instructions in
       supervisor mode. No return here, they will have to take care for the se_rfi
       themselves.
         Note, we jump on the volatile CTR register in order to not destroy the LR
       register. This allows having short system calling code without stack frame for the
       most efficient basic system call handlers. */
ivr8_startBasicHandler:
    se_lwz      r3, O_SCDESC_sr(r3) /* r3: Address of handler implementation, replaces 1st */
    se_mtctr    r3                  /* function argument, which is anyway obsolete inside
                                       the handler */
    se_bctr             /* Nothing to clean up, callee should terminate with se_rfi ... */

ivr8_noStartBasicHandler:
    se_bgt      ivr8_startFullHandler


    /* Start of a simple handler: It has a stack and will return here, but allows no
       preemptions. The process ID remains set. Intended for fast executing handlers, which
       are implemented in C. */
ivr8_startSimpleHandler:
    se_lwz      r3, O_SCDESC_sr(r3) /* r3: Address of handler implementation, replaces 1st */
    se_mtlr     r3                  /* function argument, which is anyway obsolete inside
                                       the handler */

    /* Load the supervisor stack pointer and save the U sp. We can leave the PID in place
       because we do not allow preemptions (which would do the same and corrupt the
       stack). */
    se_mr       r0, sp
    mfspr       sp, SPR_G0_SVSP         /* Restore SV sp */
    mfspr       r2, SPR_G2_SDA2         /* Repair possibly destroyed .sdata2 base in r2 */
    mfspr       r13, SPR_G1_SDA         /* Repair possibly destroyed .sdata base in r13 */

    /* Define the stack frame contents as offsets of data objects. Note the minimum offset
       of 8 due to the storage of stack pointer and link register. */
    #define O_USP           (8+0)
    #define SIZE_OF_PAYLOAD 4  /* Size of user data in stack frame */

    /* Size of stack frame: Room for SP and LR and uprounding to multiple of 8. */
    #define SIZE_OF_SF      ((((SIZE_OF_PAYLOAD)+15)/8)*8)
    #define O_LR            (SIZE_OF_SF+4)

    /* Create stack frame and save stack pointer and stack pointer at entry into system
       call.
         We don't save the return address: There are no preemptions which could overwrite
       it in SRR0. */
    e_stwu      sp, -SIZE_OF_SF(sp)
    se_stw      r0, O_USP(sp)   /* r0: Stack pointer value at entry into sys call */

    /* Call specified handler function as a normal function call. */
    mfspr       r3, SPR_PID0    /* Provide process ID as first handler argument */
    se_blrl

    /* Remove the no longer needed stack frame by restoring the stack pointer at entry. */
    se_lwz      sp, O_USP(sp)

    #undef O_USP
    #undef SIZE_OF_PAYLOAD
    #undef SIZE_OF_SF
    #undef O_LR
    se_rfi

ivr8_noStartSimpleHandler:

    /* Start of a normal handler: It has a stack and will return here and allows
       preemptions by interrupts of higher priority. The process ID is reset to kernel,
       which is a prerequiste for preemptions. Intended for longer lasting, C
       implemented handlers, which can compensate by preemptability for the higher overhead
       and the longer run-time. */
ivr8_startFullHandler:
    se_lwz      r3, O_SCDESC_sr(r3) /* r3: Address of handler implementation, replaces 1st */
    se_mtlr     r3                  /* function argument, which is anyway obsolete inside
                                       the handler */
    
    /* ivr8_switchBasicToFullHandler: Entry point for mixed mode system call handlers. A
       handler can be declared a basic handler and decide later to become fully conformant
       depending on what it needs to do.
         Use case: A handler is responsible for occasional actions. The decision, whether
       to do it now is simple and can be done in a basic handler. The action is complex and
       implemented in C. The overhead for a fully conformant handler is spent only when the
       decision is occasionally taken.
         lr: Address of normal C function, which is executed as full conformant part of the
       system call. The system call ends with return from this function and the return
       value from the function is the return value of the system call.
         r3: Doesn't care, will be overwritten.
         r4 .. r10: The C function receives the PID as first argument. The further up to 7
       32 Bit arguments are taken from r4 till r10. */
    .global     rtos_ivr8_switchBasicToFullHandler
rtos_ivr8_switchBasicToFullHandler:

    /* Load the supervisor stack pointer and save the U sp. */
    se_mr       r0, sp
    mfspr       sp, SPR_G0_SVSP         /* Restore SV sp */
    mfspr       r2, SPR_G2_SDA2         /* Repair possibly destroyed .sdata2 base in r2 */
    mfspr       r13, SPR_G1_SDA         /* Repair possibly destroyed .sdata base in r13 */

    /* Create stack frame and save stack pointer and stack pointer at entry into system
       call and return address/machine state. */
    se_lwz      r3, RUT_O_pPDESC(sp)/* r3: Pointer to process descriptor of calling task */
    e_stwu      sp, -IV8_SIZE_OF_SF(sp)
    se_stw      r0, IV8_O_USP(sp)   /* r0: Stack pointer value at entry into sys call */
    se_stw      r0, O_PDESC_USP(r3) /* Publish current U sp in process descriptor: to be used
                                       when it comes to new task starts after EE=1 */
    e_stmvsrrw  IV8_O_SRRi(sp)      /* SRR0/SRR1: 2*4 Byte */

    /* Save process ID, then reset the PID in the CPU to kernel state. A sync instruction
       is not required since we are and stay in supervisor mode, which is configured in MMU
       and MPU regardless of PID. */
    mfspr       r3, SPR_PID0
    se_stw      r3, IV8_O_PID(sp)
    se_li       r0, 0
    mtspr       SPR_PID0, r0

    /* Now we are safe to re-enable preemptions. */
    wrteei      1

    /* Call specified handler function as a normal function call.
         First function argument r3 is the process ID of the calling task.
         Register r4 .. r10 have not been changed since entry into the system call IVOR #8
       handler and still hold the user supplied function arguments of the system call. */
    se_blrl

    /* Restore status from the saved information in the stack frame. This requires a
       critical section.
         Note: r3 holds the system call result and must not be altered. */
    wrteei      0

    /** Here, we could test the process status. A full system call handler permits
        preemtion, therefore a task of higher priority could have run meanwhile and stopped
        the process of the here ending system call. Similarly, we could check for task
        deadline exceedance. The information is found sp-relative in the parent stack
        frame.
          @todo Decide, whether this is required for safety or whether we can wait for the
        next IVOR #4 preemption to check for process termination.
          @todo Remarks in rtos_scSmplHdlr_suspendProcess and rtos_suspendProcess point to
        this issue and should be removed if a check is added here. */

    se_lwz      r0, IV8_O_PID(sp)
    mtspr       SPR_PID0, r0
    e_lmvsrrw   IV8_O_SRRi(sp)      /* SRR0/SRR1: 2*4 Byte */

    /* O_PDESC_USP or processAry[].userSP doesn't need restauration: We will surely
       return to a user mode context and at its first future preemption the switch to SV sp
       will anyway update this field. It can't happen that a non-sp-switching preemption
       happens as next, which would make use of the bad, not restored field. */

    /* Remove the no longer needed stack frame by restoring the stack pointer at entry. */
    se_lwz      sp, IV8_O_USP(sp)
    se_rfi

/* End of rtos_ivor8Handler */



/**
 *   @func rtos_systemCall
 * General system call code, usable for all system call handlers. The system call index \a
 * idxSysCall is expected in r3, the variable function argument list in the remaining
 * volatile EABI registers r4..r10. The system call code can be invoked as C function using
 * the following signature:\n
 *   extern uint32_t rtos_systemCall(uint32_t idxSysCall, ...);\n
 * where ... are the function specific arguments of the call. Only register passing in the
 * volatile GPR is supported.\n
 *   The C API of the RTOS offers this C prototpye to the client code of the RTOS.
 *   @remark
 * This function must be called from the user task context only. Any attempt to use it from
 * OS code will lead to undefined behavior.
 */
    .section    .text
    .globl      rtos_systemCall
    .balign     2
#define SIZE_OF_STACKFRAME  8

rtos_systemCall:
    e_stwu      sp, -SIZE_OF_STACKFRAME(sp)
    se_mflr     r0
    se_stw      r0, (SIZE_OF_STACKFRAME+4)(sp)

    /* Raise a software interrupt. The contents of the GPR are not changed, i.e. all the
       (eight supported) function arguments in GPR 3..10 go to the system call
       implementation. */
    se_sc

    /* Destroy stack frame and return. */
    se_lwz      r0, (SIZE_OF_STACKFRAME+4)(sp)
    se_mtlr     r0
    se_addi     sp, SIZE_OF_STACKFRAME
    se_blr

#undef SIZE_OF_STACKFRAME
/* End of rtos_systemCall */



/**
 *   @func rtos_ivor9Handler
 * This is the interrupt handler for the MCU trap #9, Debug Interrupt. See RM, 62.8.5.10,
 * p. 3137. This exception relates to (see CRM, 5.1.2, Table 5-3, p. 165):
 *   - Trap, instruction address compare, data address compare, instruction
 *     complete, branch taken, return from interrupt, interrupt taken, debug
 *     counter, external debug event, unconditional debug event
 *   We don't have the debug APU features enabled (see HID0, CRM 2.4.11, p.48ff), it's not
 * even present on the MPC5748G, and would get the preemption status in CSRR0/1. However
 * MSR[DE] is always zero, so we will never see this exception.
 *   Note, the ESR, exception syndrome register, is not affected.
 */
    .section    .text.ivor
    .global     rtos_ivor9Handler
    .p2align    4
rtos_ivor9Handler:
    wrteei      0           /* By default, debug interrupts don't disable External Interrupt
                               handling. We consider it a fatal error if we ever get here
                               and want to halt the SW execution in this case. Therefore we
                               disable interrupt handling. See HID0, DCLREE and DCLRCE, too */
    se_beq      .           /* assert(false); MSR[DE] = 0, we must not see this exception */

/* End of rtos_ivor9Handler */




/**
 *   @func rtos_ivor10And11Handler
 * This is the interrupt handler for the MCU trap #10, EFP Floating-point Data Interrupt,
 * and at the same time for IVOR #11, EFP Floating-point Round Interrupt. See RM 59.5.5.11
 * and 59.5.5.12, p. 2909f and CRM, 5.7.19 and 5.7.20, p. 195, 6.2.5.2 and 6.2.5.3, p.
 * 210.\n
 *   The embedded floating-point data exception vector is used for enabled floating-point
 * invalid operation/input error, underflow, overflow, and divide by zero exceptions
 * (collectively called floating-point data exceptions).\n
 *   The embedded floating-point round exception occurs if the SPEFSCR[FINXE] bit is set,
 * no floating-point data exception is taken, and either the unrounded result of an
 * operation is not exact, an overflow occurs and overflow exceptions are disabled (FOVF or
 * FOVFH set with FOVFE cleared), or an underflow occurs and underflow exceptions are
 * disabled (FUNF set with FUNFE cleared). The embedded floating-point round exception will
 * not occur if an enabled embedded floating-point data exception occurs.\n
 *   The exceptions #10 and #11 differ from others. We have disabled both of them by setting
 * (See CRM, 6.2.1 and Table 6-1, p. 205ff, for a description of the FPU control and status
 * bits):\n
 *   - SPEFSCR[FINXE] = 0 (Embedded Floating-point Inexact Exception Enable)\n
 *   - SPEFSCR[FINVE] = 0 (Embedded Floating-point Invalid Operation / Input Error\n
 *     Exception Enable)\n
 *   - SPEFSCR[FDBZE] = 0 (Embedded Floating-point Divide by Zero Exception Enable)\n
 *   - SPEFSCR[FUNFE] = 0 (Embedded Floating-point Underflow Exception Enable)\n
 *   - SPEFSCR[FOVFE] = 0 (Embedded Floating-point Overflow Exception Enable)\n
 *   Unfortunately, the configuration register is user accessible and user code can
 * reenable the exceptions. We implement the handler by returning to the failing context.
 * We must not punish the failing context by task abortion as usually done, since there's
 * no evidence that the task, which enables the exceptions (worth being punished) is
 * identical to the task (later) causing the exception. We must not even put the typical
 * "assert(problem state == user)" since even operating system code could run an FPU
 * instruction after some user code had enabled the exceptions.
 *   @remark
 * The exceptions #10 and #11 are not raised on core 2, Z2. The Z2 core doesn't have a
 * EFPU (RM 59.5.5.11 and RM 59.5.5.12).
 */
    .section    .text.ivor
    .global     rtos_ivor10And11Handler
    .p2align    4
rtos_ivor10And11Handler:
    mfspr       r2, SPR_ESR
    se_bclri    r2, 24      /* 0x000000a0: Mask of possibly set ESR bits */
    se_bclri    r2, 26
    mtspr       SPR_ESR, r2 /* SPR 62 = ESR, exception syndrome register. Acknowledge excep. */
    se_li       r2, 0
    mtspr       SPR_SPEFSCR, r2 /* r2: 0. Repair bad FPU configuration */
    mfspr       r2, SPR_G2_SDA2 /* Restore r2 after use */
    se_rfi      /* Continue exception causing context. The FPU instruction will be repeated. */

/* End of rtos_ivor10And11Handler */

