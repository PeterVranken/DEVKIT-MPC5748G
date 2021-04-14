/**
 * @file rtos_systemMemoryProtectionUnit.c
 * Configuration and initialization of the Memory Protection Unit (MPU). The
 * configuration is chosen static in this sample. The initially chosen configuration is
 * never changed during run-time.\n
 *   The configuration uses a descriptor for all ROM, which is occupied by the compiled
 * code: All processes have read and execution access. Write access, although it can't do
 * any harm is forbidden: According run-time failure reporting will point to definite
 * implementation errors.\n
 *   The configuration has one descriptor for all RAM, which is occupied by the compiled
 * code. All processes have read access and only the OS process has write and execute
 * access, too.\n
 *   The configuration has one descriptor for the entire peripheral address space. The OS
 * process has read and write access.\n
 *   Each of the four user processes has three descriptors, all of them for RAM write and
 * execute access. There's a descriptor for the initialized data and bss, one for the small
 * data and bss and one for the small data 2 and bss 2.\n
 *   The configuration has one descriptor for a chunk of memory, which all user processes
 * have read and write access to. This memory is meant for inter-process communication and
 * must evidently never be used to hold data, which is essential for the health of a
 * process and in particular for the process, that implements supervisory safety tasks.\n
 *   The static configuration of the MPU is the explanation for the fixed number of four
 * supported processes (#RTOS_NO_PROCESSES). For the partitioning of the RAM space, we need
 * three descriptors per user process and one for the OS and we have 16 descriptors
 * available. From the remaining three, we have spend one for shared data. Two descriptors
 * are still available.\n
 *   CAUTION: The mentioned memory chunks or areas are puzzled by the linker. The MPU
 * configuration makes no hard coded assumptions about memory arrangement and distribution
 * or addresses and sizes of the chunks. It reads address and length of the memory chunks
 * from linker provided symbols. Insofar do we have a very tight relationship between the
 * implementation of this module and the linker script, which must be obeyed when doing
 * maintenance work at either side.
 *
 * Alternative configurations, which may find their use case and do not break the safety
 * concept:
 *   - The OS process doesn't necessarily need execution access for RAM. There
 * are typically driver implementation patterns, which require RAM execution rights, but it
 * is mostly about initialization and could be done prior to calling the MPU configuration.\n
 *   - The user processes won't normally need execution rights for their RAM\n
 *   - It is possible to let a process with higher privileges have access to the memories
 * of all processes with lower privileges. Below, it is explained how to do this\n
 *   - If the number of processes is reduced (a safety concept requires two processes at
 * minimum) then each process could have up to six descriptors. This would enable a
 * configuration with disjunct small data and bss chunks so that the waste of data image
 * ROM disappears, which the current configuration has (see linker script for details)\n
 *   - The shared memory section can be disabled if not required for the inter-process
 * communication\n
 *   - A fifth process could be defined using the unused descriptors. Most code barely
 * makes use of SDA2 and since we mostly use explicit data object placing it's definitely
 * not essential. This way it would even be possible to define up to seven processes, each
 * using two descriptors.\n
 *   - A difficult topic is the placing of the small data 2 and bss 2 sections. It is
 * possible to locate them into the ROM. This is likely not fully compliant with the EABI
 * but for all normal embedded applications alright. In which case we had four free
 * descriptors and could implement two more processes. A similar concept for increasing the
 * number of processes would be entirely switching off the short addressing modes. This is a
 * matter of the compiler command line
 *
 * Copyright (C) 2018-2020 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */
/* Module interface
 *   rtos_osInitMPU
 *   rtos_checkUserCodeWritePtr
 * Local functions
 *   writeRAMAreaDescriptor
 */

/*
 * Include files
 */

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>

#include "MPC5748G.h"
#include "typ_types.h"

#include "rtos.h"
#include "rtos_kernelInstanceData.h"
#include "rtos_systemMemoryProtectionUnit.h"


/*
 * Defines
 */

/** Development support: If this define is set to one than the entire RAM is writable for
    all processes. */
#define RTOS_DISARM_RAM_MPU     0


/*
 * Local type definitions
 */


/*
 * Local prototypes
 */


/*
 * Data definitions
 */


/*
 * Function implementation
 */

/**
 * Configure and initialize the memory protection units SMPU_0 and SMPU_1. The
 * configuration is static; a set of regions suitable for the RTOS (and its project
 * dependent configuration) is defined and then the unit is enabled.\n
 *   See module description for more details.
 *   @remark
 * The processes are shared between the cores and, as a consequence, one static MPU
 * configuration is used to control the behavior of all three cores. Regardless, how many
 * cores are run, this function must be called only once and it must be called when the
 * first of the three cores starts up.
 */
void rtos_osInitMPU(void)
{
    /* This function must not be used repeatedly during system initialization. See RM
       21.3.1, p. 491: GVLD should still be in reset state, SMPU disabled. */
    assert((SMPU_0->CES0 & SMPU_CES0_GVLD_MASK) == 0
           &&  (SMPU_1->CES0 & SMPU_CES0_GVLD_MASK) == 0
          );

    /* RM, 21.1, table 21-1, p. 475f: SMPU0 handles PFLASH, PBRIDGE_A, PBRIDGE_B accessed
       by XBAR0 masters plus debug interfaces. The connected masters are:
         Z4a (M0), Z4b (M1), Z2 (M2), HSM (M3), DMA (M4), Z4a debug (M8), Z4b debug (M9),
       Z2 debug (M10)
         SMPU1 handles all 3 SRAM blocks accessed by XBAR1 masters plus debug interfaces.
       The connected masters are:
         Z4a (M0), Z4b (M1), Z2 (M2), HSM (M3), DMA (M4), Ethernet (M5), FlexRay(M6), MLB
       (M7), Z4a debug (M8), Z4b debug (M9), Z2 debug (M10), USB0 (M11), USB1 (M12), uSDHC
       (M13) */

    /* All regions grant the same access to all relevant bus masters. The access word (we
       use format 1) has two bits for each master which form the index to select one out of
       three possible combinations of read/write/execute right for supervisor and user mode.
       For RAM (protected by SMPU_1) we use three access right patterns:
         - rwx for SV and r for U       (all used RAM and for all user processes)
         - rwx for SV and rwx for U     (process owned RAM, decided by PID)
         - rwx for SV and rw for U      (shared RAM and for all user processes)
       For ROM and peripherals (protected by SMPU_1) we need:
         - rx for SV and for U          (all used ROM)
         - rw for SV, no access for U   (peripherals)
         The access pattern is defined by six bits in this order: SVR, SVW, SVX, UR, UW,
       UX.
         Masters 0 .. 15 are ordered from left to right, i.e. from most to least
       significant. The relevant masters are the three cores and DMA: M0, M1, M2, M4, M8,
       M9, M10. In this sample, we don't use the other bus masters (security core and
       certain I/O devices) and for now, they don't get access.
         Remark: We use two overlapping regions for most RAM. One spawns all of the RAM and
       grants read access to anybody (and write access to OS code), the other ones relate
       to small areas, which grant write access to one of the processes. This technique
       makes it difficult to get cache inhibitted RAM: The large global read access area
       must of course not disable the cache and -- since CI=1 has lower priority than CI=0
       (see RM 21.4.2, p. 506) -- this can't be altered by the overlapping area. To provide
       cached and uncached RAM we split the large global read area into two MPU areas. */
#define WORD3_ACCESS_SET_RAM            RGD_WRD3(074u, 077u, 076u, /* CI */ 0u)
#define WORD3_ACCESS_SET_RAM_CI         RGD_WRD3(074u, 077u, 076u, /* CI */ 1u)
#define WORD2_ALL_RAM                   RGD_WRD2(/* idxPattern */ 1u)
#define WORD2_PROCESS_RAM               RGD_WRD2(/* idxPattern */ 2u)
#define WORD2_SHARED_RAM                RGD_WRD2(/* idxPattern */ 3u)
#define WORD3_ACCESS_SET_ROM_PERIPHRALS RGD_WRD3(055u, 060u, 050u, /* CI */ 0u)
#define WORD2_ALL_ROM                   RGD_WRD2(/* idxPattern */ 1u)
#define WORD2_PERIPHRALS                RGD_WRD2(/* idxPattern */ 2u)
#define WORD2_RESERVED_BLOCK            RGD_WRD2(/* idxPattern */ 3u) /* See below */

    /* Support macro for sake of readability of code below: One particular access pattern
       is applied to all bus masters. */
    #define RGD_WRD2(idxPattern) ((((idxPattern)&0x3u)<<(15*2))     \
                                  | (((idxPattern)&0x3u)<<(14*2))   \
                                  | (((idxPattern)&0x3u)<<(13*2))   \
                                  | (((idxPattern)&0x3u)<<(11*2))   \
                                  | (((idxPattern)&0x3u)<<(7*2))    \
                                  | (((idxPattern)&0x3u)<<(6*2))    \
                                  | (((idxPattern)&0x3u)<<(5*2))    \
                                 )

    /* Macro to form the WORD 3 of a region descriptor from the up to three access
       patterns. Note, cache inhibit must not be used because we have overlapping regions
       defined. See 21.3.10. */
    #define RGD_WRD3(accset1, accset2, accset3, cacheInhibit)                               \
                ((((accset1)&0x3fu)<<26) | (((accset2)&0x3fu)<<20) | (((accset3)&0x3fu)<<14)\
                 | ((/*FMT*/ 1u)<<4) | (((cacheInhibit)&1u)<<1)                             \
                )

    /* Macro for readability of code below: Construct region descriptor word 4 from the
       field values, we are interested in. (The PID mask doesn't care in our code and is
       generally set to "all PID bits matter".) See RM 21.3.11.
         PID 0 menas the kernel process. The differentiation between kernel and user
       processes is however not made by PID but by SV vs. user mode. Therefore, we take
       PID=0 in this macro as switch for disabling PID comparison.
         Note, only the cores access memory with a PID. For all other masters the PID
       condition is always true (RM 21.4.1.1, p. 504f). */
    #define WORD4_PIT_AWARE(pid)        (((pid)<<24) | ((pid)>0? 1u: 0u))
    #define WORD4_NO_PID_COMPARISON     (0u)

    /* Region descriptor, word 5: We use one and the same value for all of them: The
       descriptor is enabled and locked against any future change. */
    #define WORD5_LOCK_AND_ENABLE       (SMPU_WORD5_LCK(3) | SMPU_WORD5_VLD(1))

    unsigned int r = 0;

#if !defined(LINK_IN_RAM) /* See below, RAM configuration, otherwise */
    /* We consider the entire flash ROM, as far as used in this sample, as one memory
       region. We use linker defined symbols to find the boundaries. They need to be
       aligned compatible with the constraints of the SMPU. All start and end addresses
       have a granularity of 16 Byte. By hardware, the least significant five bits of a
       start address are set to zero and to all ones for an end address. This requires
       according alignment operations in the linker script. This is checked by assertion. */
    extern uint8_t ld_romStart[0], ld_romEnd[0];
    assert(((uintptr_t)ld_romStart & 0xf) == 0  &&  ((uintptr_t)ld_romEnd & 0xf) == 0);

    /* All used flash ROM.
         All masters and processes (i.e. user mode code) get full read and execute rights.
       Write access is forbidden in order to detect programming errors. */
    SMPU_0->RGD[r].WORD0 = (uintptr_t)ld_romStart;  /* Start address of region. */
    SMPU_0->RGD[r].WORD1 = (uintptr_t)ld_romEnd-1;  /* End address of region, including. */
    SMPU_0->RGD[r].WORD2 = WORD2_ALL_ROM;
    SMPU_0->RGD[r].WORD3 = WORD3_ACCESS_SET_ROM_PERIPHRALS;
    SMPU_0->RGD[r].WORD4 = WORD4_NO_PID_COMPARISON;
    SMPU_0->RGD[r].WORD5 = WORD5_LOCK_AND_ENABLE;   /* Enable region descriptor. */
    ++ r;
#endif

    /* All peripheral address space (256MB) except for last 16k block, labeled "Reserved"
       in RM 3.6.1, Table 3-5, p. 133.
         All masters get read and write access in supervisor mode. The processes running in
       user mode don't get access. */
    SMPU_0->RGD[r].WORD0 = 0xf0000000u;             /* Start address of region. */
    SMPU_0->RGD[r].WORD1 = 0xffffc000u - 1u;        /* End address of region, including. */
    SMPU_0->RGD[r].WORD2 = WORD2_PERIPHRALS;
    SMPU_0->RGD[r].WORD3 = WORD3_ACCESS_SET_ROM_PERIPHRALS;
    SMPU_0->RGD[r].WORD4 = WORD4_NO_PID_COMPARISON;
    SMPU_0->RGD[r].WORD5 = WORD5_LOCK_AND_ENABLE;   /* Enable region descriptor. */
    ++ r;

    /* The last 16k block in the peripheral address space, labeled "Reserved" in RM 3.6.1,
       Table 3-5, p. 133, seems to be accessed by instruction reads. This is not documented
       but has been seen in the debugger. Most likely, it even is a side effect of setting
       break points in the debugger at critical code points and will not happen in normal
       code execution. A critical point was a breakpoint at the beginning of the IVOR #1
       handler. The MPU protection exception was followed by an immediate second one, when
       the breakpoint was hit; an instruction read at 0xffffc004 was tried but rejected by
       the MPU (peripheral space has no execution access rights). This immediate second
       exception destroyed the MCSRRi registers and disable code continuation after the
       break.
         As a counter measure, all masters get read and excution access rights in
       supervisor mode. The processes running in user mode still don't get any access. This
       can only partly avoid the effect.
         The effect appears only if the debugger is asked to display the related registers
       at a break, e.g. MCSSR0. If this display is not demanded then the code execution can
       be safely continued. */
    SMPU_0->RGD[r].WORD0 = 0xffffc000u;             /* Start address of region. */
    SMPU_0->RGD[r].WORD1 = 0xffffffffu;             /* End address of region, including. */
    SMPU_0->RGD[r].WORD2 = WORD2_RESERVED_BLOCK;
    SMPU_0->RGD[r].WORD3 = WORD3_ACCESS_SET_ROM_PERIPHRALS;
    SMPU_0->RGD[r].WORD4 = WORD4_NO_PID_COMPARISON;
    SMPU_0->RGD[r].WORD5 = WORD5_LOCK_AND_ENABLE;   /* Enable region descriptor. */
    ++ r;

    /* End of configuration of SMPU0 for ROM and peripherals. */
    assert(r <= 16);
    r = 0;

    /// @todo TBC: Does DMA use SV rights? Otherwise don't handle all masters same
    /* All used SRAM for operating system kernel and processes.
         All masters and the kernel have full access (RWX) for all used RAM. The processes
       have general read access. (They get write and execute rights only to their own
       portion of RAM, which is specified in different region descriptors.)
         The entire used RAM is split in two: We have a cached and an uncached portion. The
       latter degrades system performance but is still useful for simple cross-core
       communication.
         We use linker defined symbols to find the boundaries of the region. In the linker
       script, they need to be aligned compatible with the constraints of the MPU. This is
       checked by assertion. */
    extern uint8_t ld_cachedRamStart[0], ld_cachedRamEnd[0];
    assert(((uintptr_t)ld_cachedRamStart & 0xf) == 0
           &&  ((uintptr_t)ld_cachedRamEnd & 0xf) == 0
          );
    SMPU_1->RGD[r].WORD0 = (uintptr_t)ld_cachedRamStart;/* Start address of region. */
    SMPU_1->RGD[r].WORD1 = (uintptr_t)ld_cachedRamEnd-1;/* End address of region, including. */
    SMPU_1->RGD[r].WORD2 = WORD2_ALL_RAM;
    SMPU_1->RGD[r].WORD3 = WORD3_ACCESS_SET_RAM;
    SMPU_1->RGD[r].WORD4 = WORD4_NO_PID_COMPARISON;
    SMPU_1->RGD[r].WORD5 = WORD5_LOCK_AND_ENABLE;   /* Enable region descriptor. */
    ++ r;
    extern uint8_t ld_uncachedRamStart[0], ld_uncachedRamEnd[0];
    assert(((uintptr_t)ld_uncachedRamStart & 0xf) == 0
           &&  ((uintptr_t)ld_uncachedRamEnd & 0xf) == 0
          );
    SMPU_1->RGD[r].WORD0 = (uintptr_t)ld_uncachedRamStart;/* Start address of region. */
    SMPU_1->RGD[r].WORD1 = (uintptr_t)ld_uncachedRamEnd-1;/* End address of region, incl. */
    SMPU_1->RGD[r].WORD2 = WORD2_ALL_RAM;
    SMPU_1->RGD[r].WORD3 = WORD3_ACCESS_SET_RAM_CI;
    SMPU_1->RGD[r].WORD4 = WORD4_NO_PID_COMPARISON;
    SMPU_1->RGD[r].WORD5 = WORD5_LOCK_AND_ENABLE;   /* Enable region descriptor. */
    ++ r;

    /* It would be very easy to offer a compile time switch to select a hierarchical memory
       access model, where process with ID i has write access to the memory of process with
       ID j if i>=j. This will require just a few alternative lines of code here. All
       processes would use ld_sdaP1Start, ld_sda2P1Start and ld_dataP1Start instead of
       ld_sdaPiStart, ld_sda2PiStart and ld_dataPiStart, respectively, in their
       descriptors.
         The reason not to do so is the huge amount of additional testing, which would be
       required. */

#if RTOS_DISARM_RAM_MPU == 1
    /* Full rwx access rights for all used RAM for all user processes. Here, we disable the
       PID awareness. */
    extern uint8_t ld_ramStart[0], ld_ramEnd[0];
    assert(((uintptr_t)ld_ramStart & 0xf) == 0  &&  ((uintptr_t)ld_ramEnd & 0x0f) == 0);
    SMPU_1->RGD[r].WORD0 = (uintptr_t)ld_ramStart;  /* Start address of region. */
    SMPU_1->RGD[r].WORD1 = (uintptr_t)ld_ramEnd-1;  /* End address of region, including. */
    SMPU_1->RGD[r].WORD2 = WORD2_PROCESS_RAM;
    SMPU_1->RGD[r].WORD3 = WORD3_ACCESS_SET_RAM;
    SMPU_1->RGD[r].WORD4 = WORD4_NO_PID_COMPARISON;
    SMPU_1->RGD[r].WORD5 = WORD5_LOCK_AND_ENABLE;   /* Enable region descriptor. */
    ++ r;
#else
    /* RAM access for process i. */
#define CONFIG_REGIONS_PROC_RAM(pid)                                                \
        {                                                                           \
            CONFIG_REGION_DESC_PROC_RAM(pid, /* section */ data, /* CI? (no) */)    \
            CONFIG_REGION_DESC_PROC_RAM(pid, /* section */ sda , /* CI? (no) */)    \
            CONFIG_REGION_DESC_PROC_RAM(pid, /* section */ sda2, /* CI? */ _CI)     \
        }

/// @todo Many (sda) regions are empty. Use an if to avoid spending a descriptor: This makes it particularly easy to have more than 4 processes by intentionally not using sda2
#define CONFIG_REGION_DESC_PROC_RAM(pid, section, CI)                                       \
        {                                                                                   \
            extern uint8_t ld_##section##P##pid##Start[0], ld_##section##P##pid##End[0];    \
            assert(((uintptr_t)ld_##section##P##pid##Start & 0xf) == 0                      \
                   &&  ((uintptr_t)ld_##section##P##pid##End & 0xf) == 0                    \
                  );                                                                        \
            SMPU_1->RGD[r].WORD0 = (uintptr_t)ld_##section##P##pid##Start;/* from */        \
            SMPU_1->RGD[r].WORD1 = (uintptr_t)ld_##section##P##pid##End-1;/* to, incl. */   \
            SMPU_1->RGD[r].WORD2 = WORD2_PROCESS_RAM;                                       \
            SMPU_1->RGD[r].WORD3 = WORD3_ACCESS_SET_RAM##CI;                                \
            SMPU_1->RGD[r].WORD4 = WORD4_PIT_AWARE(pid);                                    \
            SMPU_1->RGD[r].WORD5 = WORD5_LOCK_AND_ENABLE;   /* Enable region descriptor. */ \
            ++ r;                                                                           \
        }

    CONFIG_REGIONS_PROC_RAM(/* pid */ 1)
    CONFIG_REGIONS_PROC_RAM(/* pid */ 2)
    CONFIG_REGIONS_PROC_RAM(/* pid */ 3)
    CONFIG_REGIONS_PROC_RAM(/* pid */ 4)

#undef CONFIG_REGIONS_PROC_RAM
#undef CONFIG_REGION_DESC_PROC_RAM

    /* A shared memory area. All processes can write. */
    extern uint8_t ld_dataSharedStart[0], ld_dataSharedEnd[0];
    assert(((uintptr_t)ld_dataSharedStart & 0xf) == 0
           &&  ((uintptr_t)ld_dataSharedEnd & 0xf) == 0
          );
    SMPU_1->RGD[r].WORD0 = (uintptr_t)ld_dataSharedStart;   /* Start address data + bss */
    SMPU_1->RGD[r].WORD1 = (uintptr_t)ld_dataSharedEnd-1;   /* End address, including. */
    SMPU_1->RGD[r].WORD2 = WORD2_SHARED_RAM;
    SMPU_1->RGD[r].WORD3 = WORD3_ACCESS_SET_RAM_CI;
    SMPU_1->RGD[r].WORD4 = WORD4_NO_PID_COMPARISON;
    SMPU_1->RGD[r].WORD5 = WORD5_LOCK_AND_ENABLE;           /* Enable region descriptor. */
    ++ r;

#endif /* RTOS_DISARM_RAM_MPU */

#if defined(LINK_IN_RAM) /* See above, ROM/peripherals configuration, otherwise */
    /* We consider the entire test and constant data segment, as far as used in this
       sample, as one memory region. We use linker defined symbols to find the boundaries.
       They need to be aligned compatible with the constraints of the SMPU. All start and
       end addresses have a granularity of 16 Byte. By hardware, the least significant five
       bits of a start address are set to zero and to all ones for an end address. This
       requires according alignment operations in the linker script. This is checked by
       assertion. */
    extern uint8_t ld_romStart[0], ld_romEnd[0];
    assert(((uintptr_t)ld_romStart & 0xf) == 0  &&  ((uintptr_t)ld_romEnd & 0xf) == 0);

    /* All used flash ROM contents, however held in RAM.
         All masters and processes (i.e. user mode code) get full read and execute rights.
       Write access is forbidden in order to detect programming errors. */
    SMPU_1->RGD[r].WORD0 = (uintptr_t)ld_romStart;  /* Start address of region. */
    SMPU_1->RGD[r].WORD1 = (uintptr_t)ld_romEnd-1;  /* End address of region, including. */
    SMPU_1->RGD[r].WORD2 = WORD2_ALL_ROM;
    SMPU_1->RGD[r].WORD3 = WORD3_ACCESS_SET_ROM_PERIPHRALS;
    SMPU_1->RGD[r].WORD4 = WORD4_NO_PID_COMPARISON;
    SMPU_1->RGD[r].WORD5 = WORD5_LOCK_AND_ENABLE;   /* Enable region descriptor. */
    ++ r;
#endif

    assert(r <= 16);

    /* RM 21.3.1, p. 491: After configuring all region descriptors, we can globally enable
       both MPUs. */
    SMPU_0->CES0 = SMPU_CES0_MERR(0xffff)   /* Reset all possibly pending errors. */
                   | SMPU_CES0_GVLD(1);     /* Globally enable the MPU. */
    SMPU_1->CES0 = SMPU_CES0_MERR(0xffff)   /* Reset all possibly pending errors. */
                   | SMPU_CES0_GVLD(1);     /* Globally enable the MPU. */

} /* End of rtos_osInitMPU */




/**
 * Helper function, mainly intended to support safe system call handler implementation:
 * Check if a pointer value is valid for writing in the context of a given process.\n
 *   A system call handler must never trust a user code provided pointer; evidently not for
 * write access but not even for read operation (a read into the address space of
 * peripherals can have a side effect). The user code could make the system call handler
 * overwrite some non-process owned data objects, cause an access violation in the
 * supervisor code or manipulate some peripherals.\n
 *   Normally, it's strongly disencouraged having pointers as arguments of system calls at
 * all. If not avoidable, one can use this helper function to check that a pointer points
 * into permitted address space and that all bytes of a data object pointed at are still in
 * that address space. Here for write access.\n
 *   Permitted address space is anywhere, where the process may write without causing an
 * exception or any kind of side effect. In particular, this means the process' own RAM and
 * the shared RAM.
 *   @return
 * Get \a true if the pointer may be used for write access and \a false otherwise.
 *   @param PID
 * The ID of the process the query relates to. Range is 1..4.
 *   @param address
 * The pointer value, or the beginning of the chunk of memory, which needs to be entirely
 * located in writable memory.
 *   @param noBytes
 * The size of the chunk of memory to be checked. Must not be less than one. (Checked by
 * assertion).
 *   @remark
 * The counterpart function rtos_checkUserCodeReadPtr() is implemented as inline function
 * in the RTOS API header file, rtos.h.
 *   @remark
 * Although this function is intended for use inside a system call handler it can be safely
 * used from user code, too.
 */
bool rtos_checkUserCodeWritePtr(unsigned int PID, const void *address, size_t noBytes)
{
    const uint8_t * const p = (uint8_t*)address;

    /* The function doesn't support the kernel process with ID zero. We consider the index
       offset by one. */
    const unsigned int idxP = PID-1;
    if(idxP >= RTOS_NO_PROCESSES)
        return false;

    /* All relevant RAM areas are defined in the linker script. We can access the
       information by declaring the linker defined symbols. */

#if RTOS_DISARM_RAM_MPU == 1
    extern uint8_t ld_ramStart[0], ld_ramEnd[0];
    return p >= ld_ramStart  &&  p+noBytes <= ld_ramEnd;
#else
    extern uint8_t ld_dataSharedStart[0], ld_dataSharedEnd[0];
    if(p >= ld_dataSharedStart  &&  p+noBytes <= ld_dataSharedEnd)
        return true;

    extern uint8_t ld_sdaP1Start[0], ld_sdaP1End[0]
                 , ld_sda2P1Start[0], ld_sda2P1End[0]
                 , ld_dataP1Start[0], ld_dataP1End[0];

    extern uint8_t ld_sdaP2Start[0], ld_sdaP2End[0]
                 , ld_sda2P2Start[0], ld_sda2P2End[0]
                 , ld_dataP2Start[0], ld_dataP2End[0];

    extern uint8_t ld_sdaP3Start[0], ld_sdaP3End[0]
                 , ld_sda2P3Start[0], ld_sda2P3End[0]
                 , ld_dataP3Start[0], ld_dataP3End[0];

    extern uint8_t ld_sdaP4Start[0], ld_sdaP4End[0]
                 , ld_sda2P4Start[0], ld_sda2P4End[0]
                 , ld_dataP4Start[0], ld_dataP4End[0];

    #define from    0
    #define to      1

    #define SDA     0
    #define SDA2    1
    #define DATA    2

    #define addrAry(prc, boundary)                  \
                { [SDA]  = ld_sda##prc##boundary    \
                , [SDA2] = ld_sda2##prc##boundary   \
                , [DATA] = ld_data##prc##boundary   \
                }
    #define addrPrcAryAry(prc)   {[from] = addrAry(prc, Start), [to] = addrAry(prc, End)}

    static const uint8_t const *ramAreaAryAryAry_[/* idxP */ RTOS_NO_PROCESSES]
                                                 [/* from/to */ 2]
                                                 [/* Area */ 3] =
                                                            { [/*idxP*/ 0] = addrPrcAryAry(P1)
                                                            , [/*idxP*/ 1] = addrPrcAryAry(P2)
                                                            , [/*idxP*/ 2] = addrPrcAryAry(P3)
                                                            , [/*idxP*/ 3] = addrPrcAryAry(P4)
                                                            };
    return p >= ramAreaAryAryAry_[idxP][from][SDA]
           &&  p+noBytes <= ramAreaAryAryAry_[idxP][to][SDA]
           ||  p >= ramAreaAryAryAry_[idxP][from][SDA2]
               &&  p+noBytes <= ramAreaAryAryAry_[idxP][to][SDA2]
           ||  p >= ramAreaAryAryAry_[idxP][from][DATA]
               &&  p+noBytes <= ramAreaAryAryAry_[idxP][to][DATA];

    #undef from
    #undef to
    #undef SDA
    #undef SDA2
    #undef DATA
    #undef addrAry
    #undef addrPrcAryAry
#endif
} /* End of rtos_checkUserCodeWritePtr */



