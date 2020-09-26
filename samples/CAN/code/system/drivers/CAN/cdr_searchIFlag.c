/**
 * @file cdr_searchIFlag.c
 * This file implements a specialized binary search, which is required to find the least
 * significant asserted bit in a binary number. The interrupt flags share a register and
 * only one is served at a time. The least significant of the set bits is the one to
 * identify. We can do this in a fixed number of tests, where we check the input vector
 * with iteratively smallered masks.
 *
 * Copyright (C) 2020 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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
 * Local functions
 */

/*
 * Include files
 */

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "cdr_searchIFlag.h"


/*
 * Defines
 */
 
/** The search can be compiled to find either the most or the least significant bit. */
#define SEARCH_LSB              1

/** The algorithm operates on a pre-defined tree of masks. The tree is a compile-time
    constant with a fixed size. This limits the number of bits, which can be distiguished.
    Effectively, this is the width of the input word, which we look for the bit in.\n
      Note, necer change this definition. Change #MAX_WORD_SIZE_POW_2 is case. */
#define MAX_WORD_SIZE           (1u<<(MAX_WORD_SIZE_POW_2))

/** The word size #MAX_WORD_SIZE is a power of two. The actual value is controled
    indirectly through this definition.\n
      Note, never change this value without redefining the constant tree of masks
    accordinly. */
#define MAX_WORD_SIZE_POW_2     5


/*
 * Local type definitions
 */
 
 
/*
 * Local prototypes
 */
 
 
/*
 * Data definitions
 */
 
#if SEARCH_LSB == 1
/** This array implements the binary tree of iteratively narrowed test masks for the
    greatest supported word size and to find the least significant asserted bit. */
static const uint32_t _maskAry[MAX_WORD_SIZE-1] =
{
    [0] = 0x0000ffff,
    [1] = 0x00ff0000,
    [2] = 0x0f000000,
    [3] = 0x30000000,
    [4] = 0x40000000,
    [5] = 0x10000000,
    [6] = 0x03000000,
    [7] = 0x04000000,
    [8] = 0x01000000,
    [9] = 0x000f0000,
    [10] = 0x00300000,
    [11] = 0x00400000,
    [12] = 0x00100000,
    [13] = 0x00030000,
    [14] = 0x00040000,
    [15] = 0x00010000,
    [16] = 0x000000ff,
    [17] = 0x00000f00,
    [18] = 0x00003000,
    [19] = 0x00004000,
    [20] = 0x00001000,
    [21] = 0x00000300,
    [22] = 0x00000400,
    [23] = 0x00000100,
    [24] = 0x0000000f,
    [25] = 0x00000030,
    [26] = 0x00000040,
    [27] = 0x00000010,
    [28] = 0x00000003,
    [29] = 0x00000004,
    [30] = 0x00000001,
};
#else
/** This array implements the binary tree of iteratively narrowed test masks for the
    greatest supported word size and to find the most significant asserted bit. */
static const uint32_t _maskAry[MAX_WORD_SIZE-1] =
{
    [0] = 0xffff0000,
    [1] = 0xff000000,
    [2] = 0xf0000000,
    [3] = 0xc0000000,
    [4] = 0x80000000,
    [5] = 0x20000000,
    [6] = 0x0c000000,
    [7] = 0x08000000,
    [8] = 0x02000000,
    [9] = 0x00f00000,
    [10] = 0x00c00000,
    [11] = 0x00800000,
    [12] = 0x00200000,
    [13] = 0x000c0000,
    [14] = 0x00080000,
    [15] = 0x00020000,
    [16] = 0x0000ff00,
    [17] = 0x0000f000,
    [18] = 0x0000c000,
    [19] = 0x00008000,
    [20] = 0x00002000,
    [21] = 0x00000c00,
    [22] = 0x00000800,
    [23] = 0x00000200,
    [24] = 0x000000f0,
    [25] = 0x000000c0,
    [26] = 0x00000080,
    [27] = 0x00000020,
    [28] = 0x0000000c,
    [29] = 0x00000008,
    [30] = 0x00000002,
};
#endif

/** Tree \a _maskAry contains all required sub-trees. Here, we hold the needed start points. */
static const uint32_t _maskAryStartAry[MAX_WORD_SIZE_POW_2+1] =
{
    [0] = 0, /** Not needed, word size 1=2^0 is forbidden input. */
    [1] = 30,
    [2] = 28,
    [3] = 24,
    [4] = 16,
    [5] = 0,
};


/*
 * Function implementation
 */

/**
 * Find the least or most significant asserted bit in a binary word. Least or most is a
 * compile-time setting of this function, please refer to #SEARCH_LSB to find out.
 *   @return
 * Get the index of the identified bit. Index 0 means the right-most bit in the tested \a
 * word.\n
 *   Caution, the result of the operation is undefined if no single bit is set in \a word.
 * The function doesn't report this situation. The result for \a word equal to zero depends
 * on the search target. If #SEARCH_LSB is 1 then it returns (2 ^ \a widthAsPow2)-1 and
 * otherwise 0.
 *   @param word
 * This is the tested input word. The bit is searched in this word. The range is
 * 1..0xffffffff. Note, the function result is undefined for \a word being zero.
 *   @param widthAsPow2
 * The search can be bounded to the (2 ^ \a widthAsPow2) right-most bits in \a word. The other
 * bits of \a word don't care in this case. Range is 1..5.
 */
unsigned int cdr_findAssertedBitInWord(const uint32_t word, const unsigned int widthAsPow2)
{
    assert(widthAsPow2 <= MAX_WORD_SIZE_POW_2);

#if SEARCH_LSB == 1
    #define CMP_OP ==
#else
    #define CMP_OP !=
#endif
    unsigned int idxBit = 0;

    /* The index into the array, where we find the next element in the tree, i.e. the left
       or right child of the current element. */
    assert(widthAsPow2 < (sizeof(_maskAryStartAry)/sizeof(_maskAryStartAry[0])));
    unsigned int idxMask = _maskAryStartAry[widthAsPow2];
    uint32_t testedBitPos = 1u<<(widthAsPow2-1u);

    while(testedBitPos > 0)
    {
        uint32_t mask = _maskAry[idxMask];
        if((word & mask) CMP_OP 0)
        {
            /* The bit is in the upper half of the tested bit's scope. */
            idxBit |= testedBitPos;
            
            /* The right child of a tree element is found in the next array element. */
            ++ idxMask;
        }
        else
        {
            /* The bit is in the lower half of the tested bit's scope. The according bit
               doesn't need to be handled, we had initialized all bits to zero. */
               
            /* The left child of a tree element is found a power of two ahead, this is the
               current value of testedBitPos. */
            idxMask += testedBitPos;
        }
        
        testedBitPos >>= 1u;

    } /* while(Yet another bitposition to test) */

    return idxBit;

} /* End of cdr_findAssertedBitInWord */    

