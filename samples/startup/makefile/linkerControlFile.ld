/*
 * GNU GCC Memory map for Freescale MPC5748G
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

/* Entry Point */
ENTRY(sup_startUp)

/* Choose heap and stack sizes. */
ld_heapSize  = 8192;
ld_stackSizeCore0 = 4096;
ld_stackSizeCore1 = 4096;
ld_stackSizeCore2 = 4096;

MEMORY
{
    /* RM, sec. 3.2: f8c000 is the first inspected boot sector. However, this area
       is marked "Small HSM Code Block". According to RM, 3.3, table 3-2, f90000 is the
       beginning of the generally usable flash ROM and it's at the same time the second
       boot sector. */
    memBoot(rx):  org = 0x00f90000, len = 0x18
    memFlash(rx): org = 0x00f90000 + LENGTH(memBoot), len = 0x01580000 - ORIGIN(memFlash)
    memData(rwx): org = 0x40000000, len = 3*256K
}

/* Export the location of the physical storage space as far as required by the startup
   code. */
ld_memRamStart = ORIGIN(memData);
ld_memRamSize = LENGTH(memData);
ld_memRamEnd = ld_memRamStart + ld_memRamSize;

SECTIONS
{
    /* The boot sector contains a few memory word specifying the core to be started and its
       reset vectors. */
    .bafData :
    {
        ld_romStart = ABSOLUTE(.);
        KEEP(*(.bafData))

    } > memBoot

    .text_vle :
    {
        INPUT_SECTION_FLAGS (SHF_PPC_VLE)

        /* Some empty fragments from the C library go here. */
        *(.rela.dyn)
        *(.rela.got2)
        *(.rela.text)
        *(.rela.text.*)
        *(.rela.rodata.*)

        /* The IVOR vector table and the main IVOR handler, external Interrupts, #4, are
           ordered such that we have little loss of memory due to alignments constraints
           and a short distances to allow short branch operations for the main core. */
        *(.text.ivorTable.Core2)
        *(.text.ivorTable.Core1)
        *(.text.ivorTable.Core0)
        *(.text.ivor4Handler.Core0)
        *(.text.ivor4Handler.Core1)
        *(.text.ivor4Handler.Core2)

        *(.text.startup) /* First code instructions after reset go here. */
        *(.text.*)
        *(.text)
        KEEP(*(.init))
        KEEP(*(.fini))
        . = ALIGN(16);

    } > memFlash

    INCLUDE makefile/crtSupport.ld

    .rodata :
    {
        *(.rodata)
        *(.rodata.*)

        /* Leave this section 4 Byte aligned so that the subsequent load sections have this
           alignment. Our startup code requires this alignment. */
        . = ALIGN(4);

    } > memFlash


    /* The External Interrupt vector table requires a 16 Bit alignment. This is ensured
       by an assembler statement but this can mean a waste of up to 64k of RAM if the
       section location is not at such a boundary. To eliminate this risk, we place the
       table's section at absolute address at the beginning of the RAM. */
    .INTCInterruptHandlerAry ORIGIN(memData) :
    {
        ld_INTCInterruptHandlerAryStart = ABSOLUTE(.);
        
        *(.INTCInterruptHandlerAry)
        *(.INTCInterruptHandlerAry.*)

        /* Our ROM to RAM copy routine in the startup code copies always 4 Byte at once.
           The end address of the copied area should thus be a multiple of 4. */
        . = ALIGN(4);

        ld_INTCInterruptHandlerAryEnd = ABSOLUTE(.);
        
    } >memData AT>memFlash

    .data : ALIGN(8)
    {
        ld_ramStart = ABSOLUTE(.);
        ld_dataStart = ABSOLUTE(.);

        *(.data)
        *(.data.*)

/* @todo Double-check and document */
        *(.got2)
        *(.got2.*)
        *(.tm_clone_table)
        *(.tm_clone_table.*)
        *(.jcr)
        *(.jcr.*)

        /* Our ROM to RAM copy routine in the startup code copies always 4 Byte at once.
           The end address of the copied area should thus be a multiple of 4. */
        . = ALIGN(4);

        ld_dataEnd = ABSOLUTE(.);

    } >memData AT>memFlash

    .sdata : ALIGN(8)
    {
        ld_sdataStart = ABSOLUTE(.);

        /* Some empty fragments from the C library go here. */
        *(.rela.sdata)
        *(.rela.sdata.*)

        *(.sdata)
        *(.sdata.*)

        /* Our ROM to RAM copy routine in the startup code copies always 4 Byte at once.
           The end address of the copied area should thus be a multiple of 4. */
        . = ALIGN(4);

        ld_sdataEnd = ABSOLUTE(.);

    } >memData AT>memFlash

    /* Order of small data sections: The two sX and the two sX2 should be close together
       since they use the same _SDA_BASE_ pointer, or _SDA2_BASE_, respectively. */
    .sbss (NOLOAD) : ALIGN(4)
    {
        *(.sbss)
        *(.sbss.*)

    } >memData


    .sdata2 : ALIGN(8)
    {
        ld_sdata2Start = ABSOLUTE(.);

        *(.sdata2)
        *(.sdata2.*)

        /* Our ROM to RAM copy routine in the startup code copies always 4 Byte at once.
           The end address of the copied area should thus be a multiple of 4. */
        . = ALIGN(4);

        ld_sdata2End = ABSOLUTE(.);

    } >memData AT>memFlash

    .sbss2 (NOLOAD) : ALIGN(4)
    {
        *(.sbss2)
        *(.sbss2.*)

    } >memData

    .bss (NOLOAD) : ALIGN(4)
    {
        *(.bss)
        *(.bss.*)

        *(COMMON)

        /* Stack needs to be 8 Byte aligned. We even use 16 Byte alignment so that all
           boundaries become compatible with the system memory protection unit (SMPU). */
        . = ALIGN(16);
        ld_stackStart = ABSOLUTE(.);
        
        . += ld_stackSizeCore0;
        . = ALIGN(16);
        ld_stackEndCore0 = ABSOLUTE(.);
        
        . += ld_stackSizeCore1;
        . = ALIGN(16);
        ld_stackEndCore1 = ABSOLUTE(.);
        
        . += ld_stackSizeCore2;
        . = ALIGN(16);
        ld_stackEndCore2 = ABSOLUTE(.);
        
        ld_stackEnd = ABSOLUTE(.);

    } > memData

        
    /* At the end of the used RAM we install an uncached chunk of memory, intended for
       data exchange between the three cores. The boundaries of this chunk need to be
       16 Byte aligned for the SMPU and 32 Byte aligned for the cache controller, which
       uses the section address as end of range of operation.
         Note: The configuration of the SMPU is kept simple in this sample. It knowns
       two RAM areas, the first with cache, the second without. No memory allocation
       must follow this chunk, any access to it would cause a protection error. */
    .uncachedData : ALIGN(32)
    {
        ld_uncachedRamStart = ABSOLUTE(.);
        ld_uncachedDataStart = ABSOLUTE(.);

        /* The compiler won't place any data object here just like that. We define a
           section name and explict direction into this section will be required to place
           an object in this area. */
        *(.uncached)
        *(.uncached.data)
        *(.uncached.data.*)

        /* Our ROM to RAM copy routine in the startup code copies always 4 Byte at once.
           The end address of the copied area should thus be a multiple of 4. */
        . = ALIGN(4);
        ld_uncachedDataEnd = ABSOLUTE(.);

    } >memData AT>memFlash

    .uncachedBss (NOLOAD) : ALIGN(4)
    {
        /* The size of the ring buffer used for serial output in Bit. */
        ld_noBitsDmaRingBuffer = ABSOLUTE(10);

        /* The heap area for the C library. We place it in the cache inhibitted, shared RAM
           area since we want to use the library from all cores. This is still
           experimental. So far it is completely unclear how reentrance is achieved by the
           C lib implementation and if this concept still holds for different cores. */
        . = ALIGN(8);
        ld_sbrkStart = ABSOLUTE(.);
        . += ld_heapSize - (1 << ld_noBitsDmaRingBuffer);
        . = ALIGN(1 << ld_noBitsDmaRingBuffer);
        ld_sbrkEnd = ABSOLUTE(.);

        /* The DMA ring buffer is put at the end of the heap area. It has a very high
           alignment requirement: log2(sizeOfBuffer) least significant bits need to be zero
           in its address. If we align after the heap area then the gap is not lost but
           becomes additional heap space.
             Note, the section alignment hard-coded here in the file therefore limits the
           size of the buffer, which is chosen in the C source code. Assertions in the C
           code are required to ensure the crosswise consistency of C source code and
           linker control file. */
        *(.heap.dmaRingBuffer)
        *(.heap.dmaRingBuffer.*)

        /* The compiler won't place any data object here just like that. We define a
           section name and explict direction into this section will be required to place
           an object in this area. */
        *(.uncached.bss)
        *(.uncached.bss.*)

        /* Require 16 Byte alignment for SMPU. We still use the 32 Byte alignment of the
           cache controller in case we will once have an section behing here. */
        . = ALIGN(32);
        ld_uncachedRamEnd = ABSOLUTE(.);

    } >memData

    /* Create a table of all initialized memory area. The startup code uses this table to
       copy the ROM mirror contents to the RAM blocks. */
    .initializeRAM_array : ALIGN(4)
    {
        ld_initializedRamBlockAry = ABSOLUTE(.);

        LONG(ld_INTCInterruptHandlerAryStart)
        LONG(LOADADDR(.INTCInterruptHandlerAry))
        LONG(ld_INTCInterruptHandlerAryEnd - ld_INTCInterruptHandlerAryStart)
        
        LONG(ld_dataStart)
        LONG(LOADADDR(.data))
        LONG(ld_dataSize)

        LONG(ld_sdataStart)
        LONG(LOADADDR(.sdata))
        LONG(ld_sdataSize)

        LONG(ld_sdata2Start)
        LONG(LOADADDR(.sdata2))
        LONG(ld_sdata2Size)

        LONG(ld_uncachedDataStart)
        LONG(LOADADDR(.uncachedData))
        LONG(ld_uncachedDataSize)

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
         The ROM end is moved to a multiple of 32 Byte. It is exported to the memory
       protection unit (SMPU) configuration and this is a constrained of the SMPU devices. */
    .dummyROM : { . = ALIGN(32); ld_romEnd = ABSOLUTE(.); } >memFlash

    /* Read the end of the used RAM into a linker label.
         Our assembler startup code rounds the Ram end address downwards to the next
       multiple of 16 Byte when zeroizing the RAM. To avoid non zero but used RAM cells
       we align here to the next such boundary.
         @todo Enable the alignment statement if the startup code is switched to zeroize
       the used RAM only (open TODO in assembly code). Currently it zeroizes all physical
       RAM. */
    .dummyRAM : { /* . = ALIGN(16); */ ld_ramEnd = ABSOLUTE(.); } >memData

    /* Compute the used portions of RAM and ROM, so that they appear in the map file and
       can be used from the startup and application code. */
    ld_dataSize = ld_dataEnd - ld_dataStart;
    ld_uncachedDataSize = ld_uncachedDataEnd - ld_uncachedDataStart;
    ld_sdataSize = ld_sdataEnd - ld_sdataStart;
    ld_sdata2Size = ld_sdata2End - ld_sdata2Start;
    ld_stackSize = ld_stackEnd - ld_stackStart;
    ld_uncachedRamSize = ld_uncachedRamEnd - ld_uncachedRamStart;
    ld_ramSize = ld_ramEnd - ld_ramStart;
    ld_romSize = ld_romEnd - ld_romStart;
}
