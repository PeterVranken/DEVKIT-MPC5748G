/* Compile it, e.g., with:
   C:/ProgramFiles/mingw-x86_64-11.2.0-release-win32-sjlj-rt_v9-rev1/mingw64/bin/gcc -DDEBUG -o main.exe main.c
*/

#include "stdio.h"
#include "stdlib.h"
#include "stdint.h"
#include "stdbool.h"
#include <time.h>
#include "assert.h"

/* Function under test. */

/**
 * This function implements the increment of a counter (by one), which consists of an
 * arbitrary number of bits scattered over a 32 Bit word. Where the counter bits sit in the
 * word is expressed by a mask. The significance of counter bits has the same ordering as
 * for the bits in the word.\n
 *   All bits in the word, i.e., * \a pWord, which do not correspond to a bit set in the
 * mask are not affected by the operation.\n
 *   The current value of the counter, denoted by the mask bits, is incremented by one if
 * this is possible without overflow to zero. If the increment would overflow then the word
 * is not modified at all, i.e., the counter in the word is saturated at its implementation
 * maximum.\n
 *   Note, for single-bit masks, the operation is identical to:\n
 *   *pWord = *pWord | mask;\n
 *   @param pWord
 * The word, i.e., the container of the counter, by reference.
 *   @param mask
 * The bits in the mask denote the bits of the counter inside the word.
 */
static void incMaskCntr(uint32_t * const pWord, uint32_t mask)
{
    /* If we set beforehand all non-counter bits, then the normal increment of the word
       will ripple either into the counter or, if it has already all bits set, beyond it. */
    const uint32_t newMaskedVal = ((*pWord | ~mask) + 1u) & mask;
    if(newMaskedVal != 0u)
        *pWord = (*pWord & ~mask) | newMaskedVal;
}


static unsigned int noBitsSet(unsigned int mask)
{
    unsigned int noBits = 0u;
    while(mask != 0u)
    {
        if((mask & 1u) != 0u)
            ++ noBits;
        mask >>= 1u;
    }
    assert(noBits <= 31u);
    return noBits;
}


void main(void)
{
    uint32_t mask;
    for(mask=0u; mask<=UINT8_MAX; ++mask)
    {
        printf("mask: 0x%02X\n", mask);
        uint32_t initialVal;
        for(initialVal=0u; initialVal<=UINT8_MAX; ++initialVal)
        {
            /* The masked counter is initially zero. */
            const uint8_t wordInit = initialVal & ~mask;
            
            /* The masked counter allows this number of increments. */
            const unsigned int maxNoInc = mask>0u? (0x1u<<noBitsSet(mask))-1u: 0u;
            
            uint32_t word = wordInit;
            assert((wordInit & mask) == 0);
            assert((wordInit & ~mask) == (initialVal & ~mask));
            for(unsigned int inc=0u; inc<maxNoInc; ++inc)
            {
                incMaskCntr(&word, mask);
                assert((word & ~mask) == (initialVal & ~mask));
            }
            assert(word == (initialVal | mask));

            /* Masked counting is saturating? */
            uint32_t wordSat = word;
            incMaskCntr(&wordSat, mask);
            assert(word == wordSat);
            incMaskCntr(&wordSat, mask);
            assert(word == wordSat);
        }
    }
    
    /* For single-bit masks, we expect the operation to be identical to a binary OR. */
    srand(time(NULL));
    for(mask=1u; mask!=0u; mask<<=1u)
    {
        printf("mask: 0x%02X\n", mask);
        for(unsigned int u=0u; u<=1000u; ++u)
        {
            const uint32_t initialVal = (uint32_t)rand();
            uint32_t word = initialVal;
            incMaskCntr(&word, mask);
            assert(word == (initialVal | mask));
            incMaskCntr(&word, mask);
            assert(word == (initialVal | mask));
        }            
    }
    
    printf("Test successfully completed\n");
}
