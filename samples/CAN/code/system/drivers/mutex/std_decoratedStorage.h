#ifndef STD_DECORATEDSTORAGE_INCLUDED
#define STD_DECORATEDSTORAGE_INCLUDED
/**
 * @file std_decoratedStorage.h
 * Definition of intrinsic functions for atomic, cross-core load/store operations.
 *
 * Copyright (C) 2018-2020 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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
/* Module inline interface
 *   std_getCoreID
 *   std_storeWordAtomic
 *   std_cmpAndStoreWordAtomic
 *   std_loadWordAtomic
 *   std_setBitInByteAtomic
 *   std_xorByteAtomic
 *   std_fullMemoryBarrier
 */

/*
 * Include files
 */

#include <stdint.h>
#include <stdbool.h>


/*
 * Defines
 */

/** The number of cores in the MCU. */
#define STD_MAX_NO_CORES    (3u)


/*
 * Global type definitions
 */


/*
 * Global data declarations
 */


/*
 * Global prototypes
 */


/*
 * Global inline functions.
 */
 
/**
 * Get the ID of the core, the code is running on, which invcokes this function.
 *   @return
 * Get either 0 for core Z4A, 1 for core Z4B or 2 for core Z2.
 */
static inline uint32_t std_getCoreID(void)
{   
    uint32_t coreID;
    asm volatile ( /* AssemblerTemplate */
                   "mfspr %0, 286 /* SPR 286=PIR, processor ID */\n\t"
                 : /* OutputOperands */ "=r" (coreID)
                 : /* InputOperands */
                 : /* Clobbers */
                 );
    return coreID;
    
} /* End of std_getCoreID */



/**
 * Store a 32 Bit word at a given address in an atomic and uncached way. After return from
 * this function the word will really be in main memory from where it can be read from the
 * same or another core using std_loadWordAtomic().\n
 *   This function can be used to send a single word message from one core to another core.
 *   @param word
 * The 32 Bit value, which is stored in the main momory at given address in an atomic
 * operation and without considering a possible data cache between CPU and main memory.
 *   @param address
 * The address in main memory at which to store \a word. It doesn't matter whether the
 * memory region is cached or cache inhibitted.
 */
static inline void std_storeWordAtomic(uint32_t word, uint32_t *address)
{
    /* Decoration for storing a complete word by bit insertion: SRTBIT=0 and BFW=0. See RM
       18.3.1. */
    const uint32_t decoration = 0x00000000;
    
    /* See https://gcc.gnu.org/onlinedocs/gcc/Extended-Asm.html */
    asm volatile ( /* AssemblerTemplate */
                   "stwdcbx %0, %1, %2\n\t"
                 : /* OutputOperands */
                 : /* InputOperands */ "r" (word), "r" (decoration), "r" (address)
                 : /* Clobbers */ "memory"
                 );
} /* End of std_storeWordAtomic */



/**
 * Conditionally store a 32 Bit word at a given address in an atomic and uncached way.
 * After return from this function and if the condition was met the word will really be in
 * main memory from where it can be read from the same or another core using
 * std_loadWordAtomic().\n
 *   The condition for storing is that the word \a cmp is found in the target memory word
 * immediately before storing word \a word. Note that \a cmp is a 28 Bit word only,
 * although the function permits - if condition is met - to write all 32 bits. This can
 * lead to a deadlock; once the most significant bits are set, the condition will never be
 * met again for further conditional writes.\n
 *   This function can be used for test and swap operations but not just like that: The
 * annoying drawback is that we get no information whether the condition was met or not. A
 * read-back operation is needed to find out and this operation and the read-back are by
 * nature not atomic any more.
 *   @param word
 * The 32 Bit value, which is possibly stored in the main memory at given address in an
 * atomic operation and without considering a possible data cache between CPU and main
 * memory.
 *   @param cmp
 * This 28 Bit value needs to be found in memory in order to release the storage of \a
 * word.
 *   @param address
 * The address in main memory to which to compare \a cmp and to which to conditionally
 * store \a word. It doesn't matter whether the memory region is cached or cache
 * inhibited.
 */
static inline void std_cmpAndStoreWordAtomic(uint32_t word, uint32_t cmp, uint32_t *address)
{
    /* Decoration for CAST operation: 0x90000000 OR operand cmp. See RM 18.3.1.1. */
    
    /* See https://gcc.gnu.org/onlinedocs/gcc/Extended-Asm.html */
    asm volatile
        ( /* AssemblerTemplate */
#ifdef DEBUG
          "e_srwi.     %3, %1, 24\n\t"
          "se_bne      .  /* assert(Decoration field is empty, binary OR is okay) */\n\t"
#endif
          "e_oris  %1, 0x9000\n\t"
          "stwdcbx %0, %1, %2\n\t"
        : /* OutputOperands */ 
        : /* InputOperands */ "r" (word), "r" (cmp), "r" (address)
#ifdef DEBUG
        : /* Clobbers */ "memory", "cr0", "r"
#else
        : /* Clobbers */ "memory", "cr0"
#endif
        );
} /* End of std_cmpAndStoreWordAtomic */


    
/**
 * Counterpart of std_storeWordAtomic(): Load a 32 Bit word from a given address in an
 * atomic and uncached way. The function will really read the value from main memory and
 * not from a data cache possibly between CPU and main memory.\n
 *   This function can be used to receive a single word message from another core.
 *   @return
 * Get the value of the 32 Bit word, which is stored in the main memory at given address.
 *   @param address
 * The address in main memory. It doesn't matter whether the memory region is cached or
 * cache inhibitted.
 */
static inline uint32_t /* word */ std_loadWordAtomic(uint32_t *address)
{
    /* Decoration for simply loading a complete word. See RM 18.3.1.2.1. */
    const uint32_t decoration = 0x00000000;
    
    /* See https://gcc.gnu.org/onlinedocs/gcc/Extended-Asm.html */
    uint32_t word;
    asm volatile ( /* AssemblerTemplate */
                   "lwdcbx %0, %1, %2\n\t"
                 : /* OutputOperands */ "=r" (word)
                 : /* InputOperands */ "r" (decoration), "r" (address)
                 : /* Clobbers */ "memory"
                 );
    return word;

} /* End of std_loadWordAtomic */



/**
 * Set a selected bit in an 8 Bit word at a given address in an atomic and uncached way.
 * After return from this function the modified word will really be in main memory from
 * where it can be read from the same or another core using std_loadByteAtomic().\n
 *   This function can be used to implement the acquisition of a mutex in a vector of up to
 * 8 mutexes.
 *   @return
 * The function returns the 8 Bit word from before the function execution. For the
 * principal use case of implementing mutexes, a return value with the given bit NOT set
 * means that the mutex could be acquired.
 *   @param bit
 * The index of the bit to be set in the byte. Note, the counting is the normal PowerPC
 * counting, bit 0 designates the MSB and bit 7 designates the LSB.
 *   @param address
 * The address in main memory at which to store \a word.
 */
static inline uint8_t std_setBitInByteAtomic(unsigned int bit, uint8_t *address)
{
    /* Assertion required: A bad argument value would modify the instruction if we get an
       overlap with the topmost four decoration bits. */
    assert(bit < 32);
    
    /* Decoration for Load-and-Set-1 (LAS1), see RM 18.3.1.2.3. */
    const uint32_t decoration = 0x60000000 | (bit << 22);
    
    /* See https://gcc.gnu.org/onlinedocs/gcc/Extended-Asm.html */
    uint8_t wordPriorToCall;
    asm volatile ( /* AssemblerTemplate */
                   "lbdcbx %0, %1, %2\n\t"
                 : /* OutputOperands */ "=r" (wordPriorToCall)
                 : /* InputOperands */ "r" (decoration), "r" (address)
                 : /* Clobbers */ "memory"
                 );
    return wordPriorToCall;

} /* End of std_setBitInByteAtomic */



/**
 * XOR an 8 Bit word with specified operand at a given address in an atomic and uncached
 * way. After return from this function the modified word will really be in main memory
 * from where it can be read from the same or another core using std_loadByteAtomic().\n
 *   This function can be used to implement the release of a set of mutexes in a vector of
 * up to 8 mutexes.
 *   @param operand
 * The operand of the XOR. For the principal use case of a mutex implementation this word
 * would contain a 1 bit for all previously acquired and now released mutexes and 0 bits
 * anywhere else.
 *   @param address
 * The address in main memory at which to apply the XOR operation. It doesn't matter
 * whether the memory region is cached or cache inhibited.
 */
static inline void std_xorByteAtomic(uint8_t operand, uint8_t *address)
{
    /* Decoration for Logical Exclusive-OR (XOR), see RM 18.3.1.1.3. */
    const uint32_t decoration = 0xf0000000;
    
    /* See https://gcc.gnu.org/onlinedocs/gcc/Extended-Asm.html */
    asm volatile ( /* AssemblerTemplate */
                   "stbdcbx %0, %1, %2\n\t"
                 : /* OutputOperands */
                 : /* InputOperands */ "r" (operand), "r" (decoration), "r" (address)
                 : /* Clobbers */ "memory"
                 );

} /* End of std_xorByteAtomic */



/**
 * The basic operations for implementing mutual exclusion typically require a memory
 * barrier. We offer a full barrier, which may sometimes be too strong but is simple, safe
 * and straightforward in use.\n
 *   This memory barrier should be combined with the atomic operations, such that the
 * actions, which are signalled with the atomic operation have really completed before the
 * signal is raised.
 */
static inline void std_fullMemoryBarrier(void) 
{
    /* See https://gcc.gnu.org/onlinedocs/gcc/Extended-Asm.html */
    asm volatile ( /* AssemblerTemplate */
                   "msync\n\t"
                 : /* OutputOperands */
                 : /* InputOperands */
                 : /* Clobbers */ "memory"
                 );

} /* End of std_fullMemoryBarrier */


#endif  /* STD_DECORATEDSTORAGE_INCLUDED */
