/**
 * @file sup_startup.S
 * VLE assembler implementation of startup code for MPC5748G. The code has been designed
 * for use with GCC for PowerPC EABI.\n
 *   On core 0, the startup code:\n
 *   - Zeroizes all GPR\n
 *   - Initializes the exception vectors (IVOR)\n
 *   - Disables the reset escalation (DEBUG compilation only)\n
 *   - Disables the watchdog, which is running by default\n
 *   - Zeroizes all physical RAM and copies the ROM mirrors of the initialized data sections\n
 *   - Enables Critical Interrupt handling\n
 *   - Enables branch target prediction\n
 *   - Enables instruction and data caches\n
 *   - Initializes the stack\n
 *   - Presets the small data pointers r2 and r13\n
 *   - Branches into the C main function\n
 *   For the other two cores it the list is a bit shorter:\n
 *   - Zeroizes all GPR\n
 *   - Initializes the exception vectors (IVOR)\n
 *   - Enables Critical Interrupt handling\n
 *   - Enables branch target prediction\n
 *   - Enables instruction and data caches\n
 *   - Initializes the stack\n
 *   - Presets the small data pointers r2 and r13\n
 *   - Branches into their C main function\n
 *   The further HW initialization is left to the C code and needs to be called from the
 * begining of the main function of core 0, prior to the start of the other cores. A
 * minumum configuration would be:\n
 *   - All clock settings (on entry into main we still run on the fast internal RC
 *     oscillator)\n
 *   - Peripheral bridges\n
 *   - Interrupt controller for External Interrupts\n
 *
 * Copyright (C) 2017-2018 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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
 *   sup_startup
 *   sup_IVOR0trap .. sup_IVOR15trap
 *   sup_IVOR32trap .. sup_IVOR34trap
 * Local functions
 *   zeroizeRegisters
 *   disableWatchdogs
 *   initExceptionHandlers
 *   zeroizeSRAM
 *   initSDataRegisters
 */

#ifndef __VLE__
# error This file is intended for compilation for VLE instruction set only
#endif

/*
 * Include files
 */

#include "hwc_hardwareConfiguration.h"
#include "rtos.config.h"
#include "rtos_ivorHandler.h"


/*
 * Defines
 */

/* The definition of the boot sector (at 0x00f90000). The data contents are defined here
   and the location of the boot sector is defined in the linker control file.
     See MCU reference manual, 57.1.3, p. 2838ff */
#define RCHW_BOOT_ID    0x005A  /* Fixed, hard-coded value */
#define RCHW_VALUE      (RCHW_BOOT_ID)

#define ENABLE_CPU0     0x0002
#define ENABLE_CPU1     0x0008
#define ENABLE_CPU2     0x0001


/*
 * External function declarations
 */

/** C main function. */
.extern main

/** C implementation of RAM initialization. */
.extern suc_initializeRam


/*
 * Data declarations
 */

/** Interface with the C code: For the sub-ordinated cores, Z4B and Z2, the entry point
    into the C code cannot be the normal main function; the C compiler unconditionally
    generates the call of __eabi(), the C run time initialization, as part of the machine
    code that implements the entry into main. We must of course not execute this
    initialization for each core. Instead, the main function for the other cores is passed
    explicitly to the startup code. The variables main_Z4B and main_Z2 hold the function
    pointers for cores Z4B and Z2, respectively. They are set by the C function
    startSecondaryCore(), which initiates the start of these cores.\n
      Note, although this effectively is cross-core communication we don't have any issues
    with it; the sub-ordinated core is not yet running, has not filled any data into its
    cache and the output write buffers of the initiating Z4A core will be written through
    its cache into external memory long before the started core actually reaches the
    location in the startup code where the function pointer is read.
      Declaration in C code:\n
      extern void (*volatile sup_main_Z4B)(signed int noArgs, const char *argAry[]);\n
      extern void (*volatile sup_main_Z2)(signed int noArgs, const char *argAry[]); */
    .global     sup_main_Z4B, sup_main_Z2
    .section    .bss.startup
    .p2align    2
sup_main_Z4B:
    .ds.l       1
sup_main_Z2:
    .ds.l       1


/*
 * Function implementation
 */

/**
 * The boot sector contents are defined here. The binary build-up of the sector (and where
 * in memory it can be placed) is described in RM, section 57, p. 2837.\n
 *   Note: It's untransparent why we need to configure here in the boot sector, which CPUs
 * to start and from where, while the secondary cores Z4B and Z2 are explicitly started by
 * code executed by the main core Z4A. The start code executed by Z4A explicitly sets the
 * reset vector for the others and the related configuration data found here is redundant.
 * And indeed, if we don't enable Z4B and Z2 here in the boot sector they still startup
 * properly, when Z4A initiates their startup.
 */
    .section    .bafData, "a"
    .global     sup_bafData         /* Nice to have this in the map file */
sup_bafData:
    /* MCU specific magic word at beginning of boot sector. */
    .dc.w       RCHW_VALUE
    .dc.w       ENABLE_CPU0 | ENABLE_CPU1 | ENABLE_CPU2

    /* Reset vector for core 2. */
    .org        sup_bafData + 0x04, 0xff
    .dc.l       sup_startUp

    /* Reset vector for core 0. */
    .org        sup_bafData + 0x10, 0xff
    .dc.l       sup_startUp

    /* Reset vector for core 1. */
    .org        sup_bafData + 0x14, 0xff
    .dc.l       sup_startUp


/**
 *   @func sup_startUp
 * Reset address: All machine code execution starts here. The label sup_startUp is
 * specified in the BAF data block in the boot sector to make this happen after reset.
 */

    .section    .text.startup, "ax"

    .extern     ld_stackStartOSAllCores /* Absolute start of all OS stack memory. */
    .extern     ld_stackSizeOSAllCores  /* End address of all OS stack memory. */
    .extern     ld_stackEndOSCore0  /* End address or top of OS stack on core Z4A. */
    .extern     ld_stackEndOSCore1  /* End address or top of OS stack on core Z4B. */
    .extern     ld_stackEndOSCore2  /* End address or top of OS stack on core Z2. */
    
    .global     sup_startUp
    .p2align    2
sup_startUp:
    e_bl        zeroizeRegisters    /* Clear all GPR and all relevant SPR */

    /* Basic core configuration, HID0/1: See hwc_hardwareConfiguration.h */
    e_lis       r3, HWC_HID0@h
    e_or2i      r3, HWC_HID0@l
    mtspr       1008, r3        /* Configure Hardware implementation dependent 0 (HID0) */
    e_lis       r3, HWC_HID1@h
    e_or2i      r3, HWC_HID1@l
    mtspr       1009, r3        /* Configure Hardware implementation dependent 1 (HID1) */

    mfspr       r3, 286             /* SPR 286 = PIR, processor ID */
    e_bl        initExceptionHandlers   /* Register all IVOR exceptions of the core in r3 */

    se_cmpli    r3, 1               /* Next steps only once by first core, which is 0 */
    se_bge      su_endInitWDAndRam

#ifdef DEBUG
    /* Disable the destructive reset for development. */
    e_lis       r4, 0xfffa8608@ha   /* fffa8608 = 'Destructive' Reset Escalation Threshold */
    se_li       r5, 0               /* Register (MC_RGM_DRET) */
    e_stb       r5, 0xfffa8608@l(r4)/* DRET = 0: Disable escalation of destructive resets */
#endif
    e_bl        disableWatchdogs    /* The watchdogs are disabled now */
    e_bl        zeroizeSRAM         /* Clear all RAM to avoid ECC errors */
su_endInitWDAndRam:

    /* Exception handlers are installed, memory is accessible - there's no reason to wait
       any longer with enabling the higher prior interrupts (critical and machine
       check). We have the minimum functionality of an empty trap handler, which reports
       the problem to the SW developer.
         Note, the external interrupts are not enabled yet. They are entirely managed by
       the application software. */
    mfmsr       r0
    e_or2is     r0, 0x0002      /* CE: Critical interrupts */
    e_or2i      r0, 0x1000      /* ME: Machine check */
    mtmsr       r0

#if HWC_ENABLE_BRANCH_PREDICTION == 1
    /* Enable the Branch Target Buffer (BTB) for branch prediction. Clear all buffer
       entries, which might be arbitrarily set after reset, and enable all branch
       predictions. See CoreRM, sections 2.4.13, p. 81ff, and 4.4.2, p. 140.
         0x200: BBFI, Branch target buffer flash invalidate
         0x1: BPEN, Branch target buffer prediction enable */
    e_li        r0, 0x201
    mtspr       1013, r0        /* SPR 1013, Branch Unit Control and Status Register (BUCSR) */
    se_isync
#endif

    /* Load the processor ID into a non-volatile, short addressable register. */
    mfspr       r31, 286    /* SPR 286 = PIR, processor ID */
    se_cmpli    r31, 2
    se_beq      su_noInitCacheForZ2 /* Core 2 (Z2) has no caches, skip initialization */
    se_bgt      .           /* assert(PID <= 2) */

    /* Enable instruction and data caches. The procedure is described in the e200z4 Power
       Architecture Core Reference Manual, section 9.6, p. 552ff. 9.6.1 Cache
       Enable/Disable and 9.6.5 Cache Invalidation apply. */
#if HWC_ENABLE_ICACHE == 1
su_icache_cfg:
    /* Core RM, 9.6.5: Instruction cache invalidation. */
    se_li       r0, 0x2     /* SPR 1011: L1CSR1, Cache control and status register 1, Bit 1 */
    mtspr       1011, r0    /* Set bit L1CSR1[ICINV] to start the invalidation of the
                               entire instruction cache. All other bits remain zero, which
                               is their reset default value */

su_icache_waitForInvalidation:
    sync            /* EREF 2.0, 4.5.4.3, table 4-3, demands a sync prio to mfspr L1CSR0/1 */
    mfspr       r0, 1011    /* Read L1CSR1, invalidation busy bit 0x2 will be reset by HW
                               on completion, abort bit 0x4 may be set before */
    se_btsti    r0, 29      /* Test for abort */
    se_beq      su_icache_noAbort
    se_bclri    r0, 29      /* Explicitly clear the abort flag by SW */
    mtspr       1011, r0
    se_b        su_icache_cfg   /* Start over, retry */

su_icache_noAbort:
    se_btsti    r0, 30      /* Test still busy flag */
    se_bne      su_icache_waitForInvalidation   /* Busy wait for completion. */

    /* Core RM, 9.6.1: Data cache enabling */
    se_bseti    r0, 31      /* Set bit L1CSR1[CDE], data cache enable */
    se_isync
    msync
    mtspr       1011, r0
    se_isync        /* EREF 2.0, 4.5.4.3, table 4-3, demands an isync after mfspr L1CSR0/1.
                       We do this only here, where cache enabling has a context altering
                       effect. */
#endif
#if HWC_ENABLE_DCACHE == 1
    .extern     rtos_initializeDCache
    e_lis       r0, rtos_initializeDCache@ha
    e_add16i    r0, r0, rtos_initializeDCache@l /* r0: Function address for reenable D cache */
    se_mtlr     r0
    se_blrl
#endif
su_noInitCacheForZ2:

    /* The initial setting of the stack pointer. The stack rises towards lower addresses so
      the initial value is the end of the reserved RAM area. The value is provided by the
      linker, which is in charge to do the reservation but 16 Bytes are subtracted in order
      to implements some EABI requirements concerning the logical bottom of the stack.
        Note, there are some strict alignment constraints (8 Byte aligned values needed),
      which need to be ensured in the linker script file. They are not checked here and
      will in case cause an exception. */
    se_cmpli    r31, 2     /* Loading sp depends on which core executes this code. */
    se_blt      sub_core1LoadSP
sub_core2LoadSP:
    e_lis       sp, (ld_stackEndOSCore2-16)@h
    e_or2i      sp, (ld_stackEndOSCore2-16)@l
    se_b        sub_endCore0InitStack
sub_core1LoadSP:
    se_cmpli    r31, 1
    se_blt      sub_core0InitStack
    e_lis       sp, (ld_stackEndOSCore1-16)@h
    e_or2i      sp, (ld_stackEndOSCore1-16)@l
    se_b        sub_endCore0InitStack
sub_core0InitStack:
    e_lis       sp, (ld_stackEndOSCore0-16)@h
    e_or2i      sp, (ld_stackEndOSCore0-16)@l

    /* Fill the stack with a byte pattern. This pattern is used later to measure the
       current stack usage. */
    e_lis       r3, ld_stackStartOSAllCores@h
    e_or2i      r3, ld_stackStartOSAllCores@l
    e_lis       r4, ld_stackEndOSAllCores@h
    e_or2i      r4, ld_stackEndOSAllCores@l
    se_sub      r4, r3
    se_srwi     r4, 0x2             /* Divide length in Byte by 2^2=4 */
    se_mtctr    r4
    e_lis       r4, 0xa5a5a5a5@h    /* Load pattern into r4 */
    e_or2i      r4, 0xa5a5a5a5@l
su_loopFillStack:
    e_stw       r4, 0(r3)           /* Write the four pattern bytes in r4 */
    se_addi     r3, 4               /* Increment write pointer */
    e_bdnz      su_loopFillStack    /* Branch on counter register not zero */
sub_endCore0InitStack:

    /* Taken from NXP sample MPC5643L-LINFlex-UART-DMA-CW210, file __start.c, l. 186ff:
       "Prepare a terminating stack record."
         Note, we'd set the stack pointer 16 Bytes below the end of the RAM area, so we
       have enough head room to do so. */
    se_li       r3, 0       /* Clear r3 */
    e_stw       r3, 0(sp)   /* Initial stack frame link pointer is set to NULL */
    se_subi     r3, 1       /* Load 0xffffffff into r3 */
    e_stw       r3, 4(sp)   /* By convention, initialize return address from first stack
                               frame to -1. Has actually no effect */

    /* Load r2 and r13 for small, fast data access */
    e_bl        initSDataRegisters

    /* Core 0 only: Copy the mirror of the initialized RAM sections from flash ROM to the
       RAM - all global C data will have the wanted initial values. */
    se_cmpli    r31, 1
    se_bge      sub_endInitRam
    e_lis       r3, suc_initializeRam@h /* Copying the RAM blocks is implemented */
    e_or2i      r3, suc_initializeRam@l /* in C code. Load function address */
    se_mtlr     r3
    se_blrl
sub_endInitRam:

    /* Load the pointer to the kernel instance data set, which is individual to each core. */
    mfspr       r3, SPR_PIR
    se_cmpli    r3, 1
    se_bge      su_isNotCore0
#if RTOS_RUN_SAFE_RTOS_ON_CORE_0 == 1
    .extern     rtos_kernelInstanceData_core0
    e_lis       r3, rtos_kernelInstanceData_core0@ha
    e_add16i    r3, r3, rtos_kernelInstanceData_core0@l
#else
    se_li       r3, 0   /* pInstanceData = NULL; */
#endif
    se_b        su_loadKernelInstancePtr
su_isNotCore0:
    se_bgt      su_isNotCore1
#if RTOS_RUN_SAFE_RTOS_ON_CORE_1 == 1
    .extern     rtos_kernelInstanceData_core1
    e_lis       r3, rtos_kernelInstanceData_core1@ha
    e_add16i    r3, r3, rtos_kernelInstanceData_core1@l
#else
    se_li       r3, 0   /* pInstanceData = NULL; */
#endif
    se_b        su_loadKernelInstancePtr
su_isNotCore1:
    se_cmpli    r3, 2
    se_bne      .       /* assert(idxCore == 0, 1 or 2) */
#if RTOS_RUN_SAFE_RTOS_ON_CORE_2 == 1
    .extern     rtos_kernelInstanceData_core2
    e_lis       r3, rtos_kernelInstanceData_core2@ha
    e_add16i    r3, r3, rtos_kernelInstanceData_core2@l
#else
    se_li       r3, 0   /* pInstanceData = NULL; */
#endif
su_loadKernelInstancePtr:
    mtspr       SPR_G3_CDATA, r3

    /* Calling main: Load EABI function argument registers with argc=1, argv[0]=processor
       name. */
    se_mr       r3, r31 /* r31 = SPR 286 = PIR, processor ID */
    se_slwi     r3, 2   /* Pointer offset: * sizeof(char*) */
    e_lis       r4, su_argv@ha
    e_add16i    r4, r4, su_argv@l
    se_add      r4, r3
    se_li       r3, 1   /* 1 element in argv, the current processor. */
    se_cmpli    r31, 1
    se_bge      su_main4zBOrZ2
    e_lis       r5, main@h	/* Fixed main function for Z4A */
    e_or2i      r5, main@l
    se_mtlr     r5
    se_blrl
    se_b        su_endMain
su_main4zBOrZ2:
    se_bgt      su_mainZ2
    e_lis       r5, sup_main_Z4B@ha
    e_lwz       r5, sup_main_Z4B@l(r5)
    se_mtlr     r5
    se_blrl
    se_b        su_endMain
su_mainZ2:
    e_lis       r5, sup_main_Z2@ha
    e_lwz       r5, sup_main_Z2@l(r5)
    se_mtlr     r5
    se_blrl

su_endMain:
    /* We enter an infinite loop if someone should try to leave main - which is not
       intended. The external interrupts are disabled so that possible RTOS code would not
       make some other portions of code become active any more. */
    wrteei      0
su_waitForever:
    e_b         su_waitForever

    .section    .rodata.startup
    .balign     4
su_argv:
    .dc.l       su_argv_z40
    .dc.l       su_argv_z41
    .dc.l       su_argv_z2

su_argv_z40:
    .ascii      "Z4A\0"

su_argv_z41:
    .ascii      "Z4B\0"

su_argv_z2:
    .ascii      "Z2\0"

    .section    .text.startup

/* End of sup_startUp */



/**
 *   @func zeroizeRegisters
 * First step of MCU startup is to bring all relevant registers into a defined state. We
 * set all of them to zero.
 */
zeroizeRegisters:

    /* Initialize the 32-bits of GPR0 to GPR31.
         Note, the e200z420 core of the MPC5748G has no SPE unit and therefore only 32 Bit
       registers. No clearing of the upper 32 Bit is required as for the MPC5643L. */
    se_li   r0, 0
    se_li   r1, 0
    se_li   r2, 0
    se_li   r3, 0
    se_li   r4, 0
    se_li   r5, 0
    se_li   r6, 0
    se_li   r7, 0
    se_mtar r8, r0
    se_mtar r9, r0
    se_mtar r10, r0
    se_mtar r11, r0
    se_mtar r12, r0
    se_mtar r13, r0
    se_mtar r14, r0
    se_mtar r15, r0
    se_mtar r16, r0
    se_mtar r17, r0
    se_mtar r18, r0
    se_mtar r19, r0
    se_mtar r20, r0
    se_mtar r21, r0
    se_mtar r22, r0
    se_mtar r23, r0
    se_li   r24, 0
    se_li   r25, 0
    se_li   r26, 0
    se_li   r27, 0
    se_li   r28, 0
    se_li   r29, 0
    se_li   r30, 0
    se_li   r31, 0

    mtcr    r0
    mtxer   r0          /* SPR1 */
    mtctr   r0          /* SPR9 */

    mtspr   272, r0     /* SPRG0-3 */
    mtspr   273, r0
    mtspr   274, r0
    mtspr   275, r0
    mtspr   256, r0     /* USPRG0  */
    mtspr   26, r0      /* SRR0-1  */
    mtspr   27, r0
    mtspr   58, r0      /* CSRR0-1 */
    mtspr   59, r0
    mtspr   570, r0     /* MCSRR0-1 */
    mtspr   571, r0
    mtspr   574, r0     /* DSRR0-1 */
    mtspr   575, r0
    mtspr   572, r0     /* MCSR    */
    mtspr   573, r0     /* MCAR    */
    mtspr   61, r0      /* DEAR    */
    mtspr   62, r0      /* ESR     */
    mtspr   63, r0      /* IVPR    */
    mtspr   308, r0     /* DBCR0-2 and 4-8 */
    mtspr   309, r0
    mtspr   310, r0
    mtspr   563, r0
    mtspr   564, r0
    mtspr   603, r0
    mtspr   596, r0
    mtspr   597, r0

    mtpmr   400, r0     /* PMGC0. Particularly bit PMIE, "Performance monitor interrupt
                           enable", needs to be zero. */

    se_blr

/* End of zeroizeRegisters */



/**
 *   @func disableWatchdogs
 * Disable the watchdogs (external SWT and core internal, TCR). Actually, out of reset only
 * one is running and this one is disabled.
 */
disableWatchdogs:
    /* Load base address of SWT_0, see RM, section 52, p. 2745ff. */
    e_lis   r3, 0xfc05
    //e_or2i  r3, 0x0000

    /* Write magic sequence 0xc520, 0xd928 to service register to unlock the soft lock
       (locked on reset). This permits to access the control register. */
    e_li    r4, 0xc520
    e_stw   r4, 16(r3)
    e_li    r4, 0xd928
    e_stw   r4, 16(r3)

    /* Write to control register. In particular, reset bit 0, WEN, Watchdog ENable.
         0xff000000: Retain reset setting, all masters are allowed to access the SWT
         0x100: RIA, retain reset setting, reset device if invalid access to register
       occurs
         0x8: Reserved bit, set because it is set on reset, too.
         0x2: FRZ, retain reset setting, stop SWT timer if devices goes into debug mode. */
    e_lis   r4, 0xff00
    e_or2i  r4, 0x010a
    e_stw   r4, 0(r3)

    se_blr

/* End of disableWatchdogs */



/**
 *   @func initExceptionHandlers
 * Set up the MCU's interrupt table. This relates to the 12 built-in exception handlers,
 * not to the External Interrupts the application code will mainly use. (The External
 * Interrupts are one of the 12 exceptions set here.) We assign empty handlers to most
 * exceptions. These handlers loop infinitely so that you will see a caught exception in
 * the debugger.
 *   @return
 * The function returns the processor ID, i.e. r3 will not be changed.
 *   @param r3
 * r3 contains the processor ID in the range of 0..2.
 */
initExceptionHandlers:

#if RTOS_RUN_SAFE_RTOS_ON_CORE_0 == 1
# define CORE0_IVOR_TABLE  rtos_ivorVectorTableRTOS
#else
# define CORE0_IVOR_TABLE  rtos_ivorVectorTableCore0
#endif
#if RTOS_RUN_SAFE_RTOS_ON_CORE_1
# define CORE1_IVOR_TABLE  rtos_ivorVectorTableRTOS
#else
# define CORE1_IVOR_TABLE  rtos_ivorVectorTableCore1
#endif
#if RTOS_RUN_SAFE_RTOS_ON_CORE_2
# define CORE2_IVOR_TABLE  rtos_ivorVectorTableRTOS
#else
# define CORE2_IVOR_TABLE  rtos_ivorVectorTableCore2
#endif

    /* Write the common most significant 24 bits of all the exception handler addresses. */
    se_cmpli    r3, 1
    se_bge      ieh_core1Or2
    e_lis       r0, CORE0_IVOR_TABLE@h    /* Core 0, Z4A */
    e_or2i      r0, CORE0_IVOR_TABLE@l

    se_b        ieh_writeIVPR

ieh_core1Or2:
    se_bgt      ieh_core2
    e_lis       r0, CORE1_IVOR_TABLE@h    /* Core 1, Z4B */
    e_or2i      r0, CORE1_IVOR_TABLE@l
    se_b        ieh_writeIVPR

ieh_core2:
    e_lis       r0, CORE2_IVOR_TABLE@h    /* Core 2, Z2 */
    e_or2i      r0, CORE2_IVOR_TABLE@l

ieh_writeIVPR:
    mtspr       63, r0      /* IVPR */

    /* The IVOR handlers require to restore the SDA pointers in r2 and r13 since they could
       have been clobbered by the preempted, untrusted user code. We place the values in
       the general purpose special registers, which are not accessible from user mode. In
       these registers the values stay all time long. */
    e_lis       r0, _SDA_BASE_@h
    e_or2i      r0, _SDA_BASE_@l
    mtspr       SPR_G1_SDA, r0
    e_lis       r0, _SDA2_BASE_@h
    e_or2i      r0, _SDA2_BASE_@l
    mtspr       SPR_G2_SDA2, r0

    se_blr

#undef CORE0_IVOR_TABLE
#undef CORE1_IVOR_TABLE
#undef CORE2_IVOR_TABLE
/* End of initExceptionHandlers */


/**
 *   @func zeroizeSRAM
 * Zeroize all SRAM cells. All bytes from ld_memRamStart and ld_memRamStart+ld_memRamSize are
 * written to zero.\n
 *   ld_memRamStart needs to be 8 Byte aligned. ld_memRamSize is rounded downwards to a
 * multiple of 8. (Remaining bytes wouldn't be touched and couldn't be used due to
 * resulting ECC errors.)
 *   @todo
 * An optimization could be zeroizing only the used RAM cells. The according labels are
 * exported by the linker. The stack portion of the RAM will anyway be initialized twice;
 * first here and later it is filled with the fill pattern required for computation of
 * stack consumption. This change would not only speed up the system start but install an
 * additional fault recognition: A read access to an unused memory address would be
 * reported as ECC error.
 */
    .extern     ld_memRamStart, ld_memRamSize
zeroizeSRAM:
    e_lis       r3, ld_memRamStart@h
    e_or2i      r3, ld_memRamStart@l
    e_lis       r4, ld_memRamSize@h
    e_or2i      r4, ld_memRamSize@l
    se_srwi     r4, 3       /* Divide length in Byte by 2^3=8 */
    se_mtctr    r4
    se_li       r31, 0
    se_li       r30, 0

zreg_loop:
    /* RM, 72.5: ECC SRAM must be initialized with 64-bit writes on 64-bit aligned
       addresses; the use of e_stmw is recommended for this purpose. */
    e_stmw      r30, 0(r3)  /* Write registers 30 and 31 in one instruction, thus 8 Byte */
    se_addi     r3, 8
    e_bdnz      zreg_loop

    se_blr

/* End of zeroizeSRAM */




/**
 * Prepare some registers as required by the PowerPC eabi for the implementation of fast
 * small data access.
 */
    .extern     _SDA_BASE_, _SDA2_BASE_
initSDataRegisters:
    e_lis       r13, _SDA_BASE_@h       /* Load .sdata base into r13 */
    e_or2i      r13, _SDA_BASE_@l
    e_lis       r2, _SDA2_BASE_@h       /* Load .sdata2 base into r2 */
    e_or2i      r2, _SDA2_BASE_@l

    se_blr

/* End of initSDataRegisters */
