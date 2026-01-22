/* This file defines the memory map of physical memory for the linker. We have a single
   contiguous ROM area, where the linker will place the text sections and an also
   contiguous RAM area, where all data sections go.
     A alternative memory partitioning is defined in the other file memoryMapRAM.ld, which
   allows code execution from RAM (for ease of development and debugging). Some makefile
   conditional code decides whether this file or the other memory map definition is read by
   the linker. */
ASSERT(ld_linkInRAM == 0, "This memory map is intended for build in ROM only")
ld_textSegStartAddr =  0x00f90000;
ld_textSegSize      =  0x01580000 - 0x00f90000;
ld_dataSegStartAddr =  0x40000000;
ld_dataSegSize      =  3*256k ;
