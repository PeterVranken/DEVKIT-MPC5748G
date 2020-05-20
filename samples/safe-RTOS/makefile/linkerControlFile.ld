/*
 * GNU GCC Memory map for Freescale MPC5748G
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

/* Entry Point */
ENTRY(sup_startUp)

/* Choose heap and stack sizes. */
ld_heapSize         = 8k;

ld_stackSizeOSCore0 = 8k;
ld_stackSizeOSCore1 = 4k;
ld_stackSizeOSCore2 = 4k;

ld_stackSizeP1Core0 = 2k;
ld_stackSizeP1Core1 = 2k;
ld_stackSizeP1Core2 = 0;

ld_stackSizeP2Core0 = 2k;
ld_stackSizeP2Core1 = 0;
ld_stackSizeP2Core2 = 0;

ld_stackSizeP3Core0 = 2k;
ld_stackSizeP3Core1 = 2k;
ld_stackSizeP3Core2 = 0;

ld_stackSizeP4Core0 = 0;
ld_stackSizeP4Core1 = 0;
ld_stackSizeP4Core2 = 0;


/* We use the simple conditional operator the linker script syntax offers for switching
   from normal build of a flashable binary to an equivalent binary that can be loaded into
   RAM by the debugger. Using RAM can have these advantages:
   - We save flash ROM programming cycles, which are limited
   - It reduces the turnaround time between code changes. Loading RAM is faster than
     erasing and re-flashing
   - The risk of bricking the CPU is lower if we work on code, which is critical in this
     respect; e.g. self-tests, security, reset logic, reset escalation
   The major drawback is the software size; code and data need to fit into RAM. We use a
   hardcoded distribution of both, 67% for code, 33% for data.
     Note, the switch ld_linkInRAM is set by the makefile using the linker command line
   option --defsym. */
ld_textSegStartAddr = ld_linkInRAM==1? 0x40000000 : 0x00f90000;
ld_textSegSize      = ld_linkInRAM==1? 2*256k : 0x01580000 - 0x00f90000;
ld_dataSegStartAddr = ld_linkInRAM==1? ld_textSegStartAddr + ld_textSegSize : 0x40000000;
ld_dataSegSize      = ld_linkInRAM==1? 3*256k - ld_textSegSize : 3*256k ;


/* Definition of memory regions using absolute addresses of physical memories. */
MEMORY
{
    /* RM, sec. 3.2: f8c000 is the first inspected boot sector. However, this area
       is marked "Small HSM Code Block". According to RM, 3.3, table 3-2, f90000 is the
       beginning of the generally usable flash ROM and it's at the same time the second
       boot sector. */
    memBoot(rx):  org = ld_textSegStartAddr, len = 0x18
    memFlash(rx): org = ld_textSegStartAddr + LENGTH(memBoot),
                        len = ld_textSegSize - LENGTH(memBoot)
    memData(rwx): org = ld_dataSegStartAddr, len = ld_dataSegSize
}

/* Export the location of the physical storage space as far as required by the startup
   code. */
ld_memRamStart = ORIGIN(memData);
ld_memRamSize = LENGTH(memData);
ld_memRamEnd = ld_memRamStart + ld_memRamSize;

SECTIONS
{
    /* The boot sector contains a few memory words specifying the core to be started and its
       reset vectors. */
    .bafData :
    {
        ld_romStart = ABSOLUTE(.);
        KEEP(*(.bafData))

    } > memBoot

    .text_vle :
    {
        INPUT_SECTION_FLAGS (SHF_PPC_VLE)

        /* The IVOR vector table and the main IVOR handler, external Interrupts, #4, are
           ordered such that we have little loss of memory due to alignments constraints
           and a short distances to allow immediate branch operations. */
        *(.text.ivorTable.Core0)
        *(.text.ivorTable.Core1)
        *(.text.ivorTable.Core2)
        *(.text.ivorTable.rtos)
        *(.text.ivor)
        *(.text.ivor.*)

        *(.text.startup) /* First code instructions after reset go here. */
        *(.text.*)
        *(.text)
        KEEP(*(.init))
        KEEP(*(.fini))

        /* Some empty fragments from the C library go here. */
        *(.rela.dyn)
        *(.rela.dyn.*)
        *(.rela.got2)
        *(.rela.got2.*)
        *(.rela.text)
        *(.rela.text.*)

    } > memFlash

    INCLUDE makefile/crtSupport.ld

    .rodata : ALIGN(4)
    {
        /* Normal, const data from C source files goes here. */
        *(.rodata)
        *(.rodata.*)

        /* Some empty fragments from the C library go here. */
        *(.rela.rodata)
        *(.rela.rodata.*)

        /* Leave this section 4 Byte aligned so that the subsequent load sections have this
           alignment. Our startup code requires this alignment. */
        . = ALIGN(4);

    } > memFlash

    /* Read the beginning of the used RAM into a linker label. */
    .dummyRAMInit (NOLOAD) :
    { 
        ld_ramStart = ABSOLUTE(.);
        ld_cachedRamStart = ABSOLUTE(.);

    } >memData

    /* The External Interrupt vector table requires a 16 Bit alignment. This is ensured
       by an assembler statement but this can mean a waste of up to 64k of RAM if the
       section location is not at such a boundary. To eliminate this risk, we place the
       table's section at absolute address at the beginning of the RAM. */
    .INTCInterruptServiceAry ORIGIN(memData) :
    {
        ld_INTCInterruptServiceAryStart = ABSOLUTE(.);
        
        *(.INTCInterruptServiceAry)
        *(.INTCInterruptServiceAry.*)

        /* Our ROM to RAM copy routine in the startup code copies always 4 Byte at once.
           The end address of the copied area should thus be a multiple of 4. */
        . = ALIGN(4);

        ld_INTCInterruptServiceAryEnd = ABSOLUTE(.);
        
    } >memData AT>memFlash

    INCLUDE makefile/processRAM.ld

    /* Create a table of all initialized memory area. The startup code uses this table to
       copy the ROM mirror contents to the RAM blocks. */
    .initializeRAM_array : ALIGN(4)
    {
        ld_initializedRamBlockAry = ABSOLUTE(.);

        LONG(ld_INTCInterruptServiceAryStart)
        LONG(LOADADDR(.INTCInterruptServiceAry))
        LONG(ld_INTCInterruptServiceAryEnd - ld_INTCInterruptServiceAryStart)

        INCLUDE makefile/processRAMInitAry.ld

        /* The end of the list is indicated by a NULL pointer. */
        LONG(0)
        LONG(0)
        LONG(0)

    } > memFlash

    /* The DWARF debug sections are explicitly mentioned to avoid default orphan section
       placing so that we can benefit from orphan section warnings. */
    .PPC.EMB.apuinfo 0 : { *(.PPC.EMB.apuinfo) }
    .boffs           0 : { KEEP (*(.boffs)) }
    .comment         0 : { *(.comment) }
    .gnu.attributes  0 : { *(.gnu.attributes) }
    .debug           0 : { *(.debug) }
    .debug_abbrev    0 : { *(.debug_abbrev) }
    .debug_aranges   0 : { *(.debug_aranges) }
    .debug_frame     0 : { *(.debug_frame) }
    .debug_funcnames 0 : { *(.debug_funcnames) }
    .debug_info      0 : { *(.debug_info) }
    .debug_line      0 : { *(.debug_line) }
    .debug_loc       0 : { *(.debug_loc) }
    .debug_macinfo   0 : { *(.debug_macinfo) }
    .debug_macro     0 : { *(.debug_macro) }
    .debug_pubnames  0 : { *(.debug_pubnames) }
    .debug_ranges    0 : { *(.debug_ranges) }
    .debug_sfnames   0 : { *(.debug_sfnames) }
    .debug_srcinfo   0 : { *(.debug_srcinfo) }
    .debug_str       0 : { *(.debug_str) }
    .debug_typenames 0 : { *(.debug_typenames) }
    .debug_varnames  0 : { *(.debug_varnames) }
    .debug_weaknames 0 : { *(.debug_weaknames) }
    .glink           0 : { *(.glink) }
    .iplt            0 : { *(.iplt); *(.rela.iplt) }
    .line            0 : { *(.line) }
    .version_info    0 : { *(.version_info) }

    /* Read the end of the used flash ROM into a linker label.
         The ROM end is moved to a multiple of 16 Byte. It is exported to the memory
       protection unit (SMPU) configuration and this is a constrained of the SMPU devices.
         Another constraint is the cache, which reads 32 Byte at once to fill a cache line. */
    .dummyROM : { . = ALIGN(32); ld_romEnd = ABSOLUTE(.); } >memFlash

    /* Read the end of the used RAM into a linker label.
         Our assembler startup code rounds the Ram end address downwards to the next
       multiple of 16 Byte when zeroizing the RAM. To avoid non zero but used RAM cells
       we align here to the next such boundary.
         Another constraint is the SMPU, which require a multiple of 16 Byte.
         Another constraint is the cache, which reads 32 Byte at once to fill a cache line. */
    .dummyRAM (NOLOAD) :
    {
        . = ALIGN(32);
        ld_uncachedRamEnd = ABSOLUTE(.);
        ld_ramEnd = ABSOLUTE(.);

    } >memData

    /* Compute the sizes of the memory chunks of the processes, which are configured in the
       MPU. The computed sizes are not required in the code but it is useful to have them
       listed in the map file. */
    ld_dataP1Size = ld_dataP1End - ld_dataP1Start;
    ld_sdaP1Size = ld_sdaP1End - ld_sdaP1Start;
    ld_sda2P1Size = ld_sda2P1End - ld_sda2P1Start;

    ld_dataP2Size = ld_dataP2End - ld_dataP2Start;
    ld_sdaP2Size = ld_sdaP2End - ld_sdaP2Start;
    ld_sda2P2Size = ld_sda2P2End - ld_sda2P2Start;

    ld_dataP3Size = ld_dataP3End - ld_dataP3Start;
    ld_sdaP3Size = ld_sdaP3End - ld_sdaP3Start;
    ld_sda2P3Size = ld_sda2P3End - ld_sda2P3Start;

    ld_dataP4Size = ld_dataP4End - ld_dataP4Start;
    ld_sdaP4Size = ld_sdaP4End - ld_sdaP4Start;
    ld_sda2P4Size = ld_sda2P4End - ld_sda2P4Start;

    ld_dataSharedSize = ld_dataSharedEnd - ld_dataSharedStart;

    /* Compute the used portions of RAM and ROM, so that they appear in the map file and
       can be used from the startup and application code. */
    ld_ramSize = ld_ramEnd - ld_ramStart;
    ld_romSize = ld_romEnd - ld_romStart;
}
