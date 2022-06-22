/* This file defines a memory partioning, which places the exectable code (text sections)
   into RAM. Instead of a flashable binary, we get an equivalent binary that can be loaded
   into RAM by the debugger. Using RAM can have these advantages:
   - We save flash ROM programming cycles, which are limited
   - It reduces the turnaround time between code changes. Loading RAM is faster than
     erasing and re-flashing
   - The risk of bricking the CPU is lower if we work on code, which is critical in this
     respect; e.g. self-tests, security, reset logic, reset escalation
   The major drawback is the software size; code and data need to fit into RAM. We use a
   hardcoded distribution of both, 75% for code, 25% for data.
     Some makefile conditional code decides whether this file or the "normal" memory map
   definition memoryMapROM.ld is read by the linker. */
ASSERT(ld_linkInRAM == 1, "This memory map is intended for build in ROM only")
ld_textSegStartAddr = 0x40000000 ;
ld_textSegSize      = 2*256k ;
ld_dataSegStartAddr = ld_textSegStartAddr + ld_textSegSize ;
ld_dataSegSize      = 3*256k - ld_textSegSize ;
