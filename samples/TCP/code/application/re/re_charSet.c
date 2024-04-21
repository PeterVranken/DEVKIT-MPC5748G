/**
 * @file re_charSet.c
 * Handling of character sets in the regular expression.
 *
 * Copyright (C) 2024 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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
 *   re_compileHexByte
 *   re_compileCharSet
 *   re_onInstructionMove
 *   re_writeCharSets
 *   re_printCharSetBinary
 *   re_isCharInCharSet
 * Local functions
 *   getInputChar
 *   getAddrOfCharSet
 *   getAddrOfCharSetInRe
 *   storeCharSet
 *   findCharSet
 *   initializeCharSet
 *   addChar
 *   addCharRange
 */

/*
 * Include files
 */

#include "re_charSet.h"

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <assert.h>

#include "re_regExpMatcher.h"

#if RE_REQUIRE_COMPILER == 1
# include "re_regExpCompiler.h"
#endif

/*
 * Defines
 */

/** Common expression: Check of compiler's main status variable to see if we can still
    continue. */
#define COMP_OK     (pCompiler->err == re_errComp_success)


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

#if RE_REQUIRE_COMPILER == 1
/**
 * Read an unsigned integer number from the input stream. Two hex digits are expected in
 * the input stream at the current read position.
 *   @return
 * Get \a true if a suitable number could be read. It is assumed that no other alternative
 * is currently possible, so compilation has failed if \a false is returned.
 *   @param pCompiler
 * The compiler, which contains the input stream to read from.
 *   @param pC
 * The read number is returned by reference as a (matchable) character.
 */
bool re_compileHexByte(struct re_compiler_t * const pCompiler, uint8_t * const pC)
{
    bool success = true;
    
    int c1 = toupper((int)* pCompiler->pC);
    if(isdigit(c1))
        c1 -= '0';
    else if(c1 >= 'A'  &&  c1 <= 'F')
        c1 -= 'A' - 10;
    else
        success = false;

    int c2;
    if(success)
    {
        c2 = toupper((int)* ++pCompiler->pC);
        if(isdigit(c2))
            c2 -= '0';
        else if(c2 >= 'A'  &&  c2 <= 'F')
            c2 -= 'A' - 10;
        else
            success = false;
    }

    if(success)
    {
        ++ pCompiler->pC;
        assert((c1 << 4) + c2 <= UINT8_MAX);
        *pC = (uint8_t)((c1 << 4) + c2);
        return true;
    }
    else
    {
        /* This function is solely used to compile escaped character codes in the form
           \xHH. */
        assert(pCompiler->err == re_errComp_success);
        pCompiler->err = re_errComp_invalidEscape;
        return false;
    }
} /* re_compileHexByte */


/**
 * Read next character from the input stream. This reading considers the potentially use
 * escape representation of non-printable characters, like \r or \n.
 *   @return
 * The function returns \a true if a character could be returned or \a false in case of
 * errors or if the end of input stream is reached.
 *   @param pCompiler
 * The regular expression compiler is passed in by reference. It contains the access to the
 * input stream, provides access to the assembled instruction stream and allows to set an
 * error message if the operation fails.
 *   @param pC
 * The read character is returned by reference.
 */
static bool getInputChar(struct re_compiler_t * const pCompiler, uint8_t * const pC)
{
    uint8_t c = *pCompiler->pC;
    if(c == '\0')
        goto unexpectedEOF;
    else
        ++ pCompiler->pC;

    /* A few special characters can be accessed by escape sequences. */
    if(c == '\\')
    {
        c = *pCompiler->pC;
        if(c == '\0')
            goto unexpectedEOF;
        else
            ++ pCompiler->pC;

        switch(c)
        {
        case 'f':  c = '\f'; break;
        case 'r':  c = '\r'; break;
        case 'n':  c = '\n'; break;
        case 't':  c = '\t'; break;
        case '\\': c = '\\'; break;

        case 'x':
            if(!re_compileHexByte(pCompiler, &c))
                return false;
            else
                break;

        default:
            pCompiler->err = re_errComp_invalidEscape;
        }
    }

    *pC = c;
    return COMP_OK;

unexpectedEOF:
    pCompiler->err = re_errComp_charSetMissingRParen;
    return false;

} /* getInputChar */


/**
 * Calculate the memory address of the first data byte of the n-th compiled character set
 * of a compiler.
 *   @return
 * Get the address as pointer to char.
 *   @param pCompiler
 * The regular expression compiler is passed in by reference. It contains the already
 * compiled character sets.
 *   @param idxCS
 * The character set by zero based index. Since this is just the address caculation, it
 * doesn't matter if such a character set had already been stored or not yet.
 */
static inline uint8_t *getAddrOfCharSet( const struct re_compiler_t * const pCompiler
                                       , unsigned int idxCS
                                       )
{
    return  pCompiler->charSetMem + idxCS*sizeof(re_charSet_t);
}
#endif

/**
 * Calculate the memory address of the first data byte of the n-th compiled character set
 * in a compiled regular expression.
 *   @return
 * Get the address as pointer to char.
 *   @param pRe
 * The compiled regular expression compiler is passed in by reference. It contains the
 * already compiled character sets.
 *   @param idxCS
 * The character set by zero based index. Since this is just the address calculation, it
 * doesn't matter if such a character set had already been stored or not yet.
 */
static inline const uint8_t *getAddrOfCharSetInRe
                                        ( const struct re_compiledRegExp_t * const pRe
                                        , unsigned int idxCS
                                        )
{
    return pRe->iStream + pRe->lenIStream + idxCS*sizeof(re_charSet_t);
}


#if RE_REQUIRE_COMPILER == 1
/**
 * Store a character set in the array of already compiled ones.
 *   @param pCompiler
 * The regular expression compiler is passed in by reference. It contains the already
 * compiled character sets.
 *   @param cs
 * The character set to store.
 */
static uint16_t storeCharSet(struct re_compiler_t * const pCompiler, re_charSet_t cs)
{
    assert(COMP_OK);
    if(pCompiler->re.noCharSets < pCompiler->maxNoCharSets)
    {
        memcpy(getAddrOfCharSet(pCompiler, pCompiler->re.noCharSets), cs, sizeof(re_charSet_t));
        return pCompiler->re.noCharSets++;
    }
    else
    {
        pCompiler->err = re_errComp_charSetMaxNoSetsExceeded;
        return UINT16_MAX;
    }
} /* storeCharSet */


/**
 * Try to identify a character set in the array of already compiled ones.
 *   @return
 * If the identical character set had already been compiled before then the function
 * returns its zero based index in the array of compiled sets. If \a cs is a new character
 * set then it returns UINT16_MAX, which is an invalid index.
 *   @param pCompiler
 * The regular expression compiler is passed in by reference. It contains the already
 * compiled character sets.
 *   @param cs
 * The character set to look for.
 */
static uint16_t findCharSet(struct re_compiler_t * const pCompiler, re_charSet_t cs)
{
    for(unsigned int idxCS=0u; idxCS<pCompiler->re.noCharSets; ++idxCS)
        if(memcmp(cs, getAddrOfCharSet(pCompiler, idxCS), sizeof(re_charSet_t)) == 0)
            return idxCS;
    return UINT16_MAX;

} /* findCharSet */


/**
 * Initialize a character set.
 *   @param charSet
 * The character set to initialize.
 *   @param isInitiallyEmpty
 * The set can be initially empty (\a true) or pre-filled with all characters (\a false).
 */
static inline void initializeCharSet(re_charSet_t charSet, bool isInitiallyEmpty)
{
    memset(charSet, isInitiallyEmpty? 0: (int)UINT8_MAX, sizeof(re_charSet_t));
}


/**
 * Consider a character in a character set. Add or remove it from the set.
 *   @param charSet
 * The character set to update.
 *   @param doAdd
 * \a true for adding, \a false for removing the character from the set.
 *   @param c
 * The character to add or remove.
 */
static void addChar(re_charSet_t charSet, bool doAdd, uint8_t c)
{
    if(doAdd)
        charSet[(unsigned)c/8u] |= (1u<<(c & 7u));
    else
        charSet[(unsigned)c/8u] &= ~(1u<<(c & 7u));

} /* addChar */



/**
 * Consider a range of characters in a character set. Add or remove all of them to or from
 * the set.
 *   @param charSet
 * The character set to update.
 *   @param doAdd
 * \a true for adding, \a false for removing the character from the set.
 *   @param cFrom
 * The first character to add or remove.
 *   @param cTo
 * The last character to add or remove (including).
 */
static void addCharRange(re_charSet_t charSet, bool doAdd, uint8_t cFrom, uint8_t cTo)
{
    assert((unsigned)cFrom <= (unsigned)cTo  &&  (unsigned)cTo <= UINT8_MAX);
    for(unsigned int c=(unsigned)cFrom; c<=(unsigned)cTo; ++c)
       addChar(charSet, doAdd, (uint8_t)c);

} /* addChar */



/**
 * Check input for a character set and compile it if present.
 *   @return
 * The function returns \a true if a character set was found and processed. If it returns
 * \a false and if no error has been reported then the compiler needs to consider another
 * interpretation of the input.
 *   @param pCompiler
 * The regular expression compiler is passed in by reference. It contains the access to the
 * input stream, provides access to the assembled instruction stream and allows to set an
 * error message if the operation fails.
 */
bool re_compileCharSet(struct re_compiler_t * const pCompiler)
{
    assert(COMP_OK);
    if(*pCompiler->pC == '[')
    {
        ++ pCompiler->pC;

        #define GET_CHAR(pC) {if(!getInputChar(pCompiler, pC)) return false;}

        uint8_t c;
        GET_CHAR(&c)
        const bool isPositive = c != '^';
        if(!isPositive)
            GET_CHAR(&c)

        re_charSet_t cs;
        initializeCharSet(cs, /*isInitiallyEmpty*/ isPositive);

        /* To bring the closing bracket into the set, regular expression mostly allow them
           to be the first entry in the set. This can be decided from the closing bracket
           as empty sets are not allowed. We must not check the first character for
           terminating the set.
             Note, putting this code here means that the initial closing rectangular
           bracket can't at the same time be the beginning of a range, e.g., []-}] would
           mean three characters ], -, } but not ]...}. */
        if(c == ']')
        {
            addChar(cs, isPositive, c);
            GET_CHAR(&c)
        }

        uint8_t c1;
        enum {stGotNone, stGot1st, stGotHyphen} st = stGotNone;
        while(COMP_OK)
        {
            if(st == stGotNone)
            {
                if(c == ']')
                    break;
                else
                {
                    c1 = c;
                    st = stGot1st;
                }
            }
            else if(st == stGot1st)
            {
                if(c == ']')
                {
                    addChar(cs, isPositive, c1);
                    break;
                }
                else if(c == '-')
                    st = stGotHyphen;
                else
                {
                    addChar(cs, isPositive, c1);
                    c1 = c;
                }
            }
            else
            {
                assert(st == stGotHyphen);
                if(c == ']')
                {
                    addChar(cs, isPositive, c1);
                    addChar(cs, isPositive, '-');
                    break;
                }
                else
                {
                    if(c >= c1)
                        addCharRange(cs, isPositive, c1, c);
                    else
                        pCompiler->err = re_errComp_charSetBadRange;
                    st = stGotNone;
                }
            }
            GET_CHAR(&c)
        }

        /* Some typical character sets like [0-9] or [a-z] tend to appear more than once in
           real regular expressions. We look for already defined identical sets in order to
           avoid storage of duplicates. Otherwise we simply add it to our compile-time
           buffer. */
        uint16_t idxCS = UINT16_MAX;
        if(COMP_OK)
        {
            idxCS = findCharSet(pCompiler, cs);
            if(idxCS == UINT16_MAX)
                idxCS = storeCharSet(pCompiler, cs);
        }

        /* If we didn't see a memory overflow then we can finally add the matcher code to
           the instruction stream. */
        if(COMP_OK)
        {
            uint8_t iStream[3];
            assert(idxCS < pCompiler->re.noCharSets
                   &&  pCompiler->re.noCharSets <= pCompiler->maxNoCharSets
                  );
            iStream[0] = OP_CHARSET;

            /* The address of the char set is preliminary. For now, we use the zero based
               index of the set. Later, a relocation of the instruction will be required. */
            iStream[1] = idxCS >> 8;
            iStream[2] = idxCS & 0xFFu;

            /* To enable the later relocation of the emitted instruction we need to save a
               reference to it. */
            if(pCompiler->noICharSet < pCompiler->maxNoICharSet)
            {
                assert(pCompiler->re.lenIStream <= UINT16_MAX);
                pCompiler->idxICharSetAry[pCompiler->noICharSet++] = pCompiler->re.lenIStream;
            }
            else
                pCompiler->err = re_errComp_charSetMaxNoSetsExceeded;

            if(COMP_OK)
                re_compEmitCode(pCompiler, /* code */ iStream, sizeof(iStream));
        }

        return true;

        #undef GET_CHAR
    }
    else
        return false;

} /* re_compileCharSet */



/**
 * Notify a move of some already compiled code, which may require relocation. (This may
 * happen, e.g, due to only afterwards recognized loop constructs.)
 *   @param pCompiler
 * The regular expression compiler is passed in by reference. It contains the access to the
 * input stream, provides access to the assembled instruction stream and allows to set an
 * error message if the operation fails.
 *   @param idxIFrom
 * The index of the the first instruction, which is moved towards a higher address (or
 * index).
 *   @param distance
 * All instructions, starting with index \a idxIFrom, are moved by this number of Byte.
 */
void re_onInstructionMove( struct re_compiler_t * const pCompiler
                         , unsigned int idxIFrom
                         , unsigned int distance
                         )
{
    /* The location of the char set instructions, which are in the moved portion of the
       instruction stream, have changed and we have to correct the references, which we had
       saved during compilation so far. */
    assert(COMP_OK);
    for(unsigned int idxICS=0u; idxICS<pCompiler->noICharSet; ++idxICS)
        if(pCompiler->idxICharSetAry[idxICS] >= idxIFrom)
            pCompiler->idxICharSetAry[idxICS] += distance;

} /* re_onInstructionMove */


/**
 * At the end of successful compilation, this function can dump the compiled character sets
 * to the end of the instruction stream and eventually relocate the instructions using the
 * sets.
 *   @param pCompiler
 * The regular expression compiler is passed in by reference. Compilation needs to have
 * completed so that it contains all the compiled character sets, which are dumped now.
 */
void re_writeCharSets(struct re_compiler_t * const pCompiler)
{
    assert(COMP_OK);

    const unsigned int absAddr1stCS = pCompiler->re.lenIStream;
    for(unsigned int idxCS=0u; idxCS<pCompiler->re.noCharSets; ++idxCS)
    {
        re_compEmitCode( pCompiler
                       , /*code*/ getAddrOfCharSet(pCompiler, idxCS)
                       , sizeof(re_charSet_t)
                       );
    } /* for(All compiled character sets to dump) */

    /* In the for loop before, we "abused" the instruction pointer as data address for
       dumping the character sets and now we need to restore it. */
    const unsigned int noDataBytes = pCompiler->re.noCharSets * sizeof(re_charSet_t);
    pCompiler->re.lenIStream -= noDataBytes;
    assert(pCompiler->re.lenIStream == absAddr1stCS);

    /* Now we eventually know, where in instruction memory the character set sits and
       we can relocate all instructions, which make use of it. */
    for(unsigned int idxICS=0u; idxICS<pCompiler->noICharSet; ++idxICS)
    {
        /* We had written the instruction with the index of the character set as
           preliminary address information. */
        const unsigned int idxICharSet = pCompiler->idxICharSetAry[idxICS];
        assert(idxICharSet + 3u <= pCompiler->re.lenIStream
               &&  pCompiler->re.iStream[idxICharSet+0u] == OP_CHARSET
              );
        const unsigned int prelimAddrCS = (pCompiler->re.iStream[idxICharSet+1u] << 8)
                                          + pCompiler->re.iStream[idxICharSet+2u];
        assert(prelimAddrCS < pCompiler->re.noCharSets);
        const unsigned int absAddrCS = absAddr1stCS + prelimAddrCS * sizeof(re_charSet_t);
        assert(absAddrCS < UINT16_MAX);
        /* 3: Length of the instruction; the relative address counts from behind. */
        const unsigned int relAddrCS = absAddrCS - idxICharSet - 3u;
        assert(relAddrCS < UINT16_MAX);
        pCompiler->re.iStream[idxICharSet+1u] = (relAddrCS & 0xFF00u) >> 8;
        pCompiler->re.iStream[idxICharSet+2u] = (relAddrCS & 0x00FFu) >> 0;

    } /* for(All instructions, which reference the given character set) */

} /* re_writeCharSets */
#endif


#if RE_REQUIRE_MAIN == 1
/**
 * Display all data bytes of a character set in a compiled regular expression.
 *   @param ostream
 * An output FILE stream, which to write the information in. Pass stdout in the simplest case.
 *   @param pRe
 * The compiled regular expression is passed in by reference. Compilation needs to have
 * completed so that it contains all the compiled character sets. One of these is printed
 * now.
 *   @param idxCS
 * The character set by zero based index in all compiled charsets.
 *   @param firstAddr
 * The address in an instruction stream, where the compiled charater set is located,
 * actually a byte index.
 *   @param asCCode
 * The data bytes can be printed for human reading or as a fragment of valid C source
 * code (to bring a compiled expression into an embedded software).
 */
void re_printCharSetBinary( FILE *ostream
                          , const struct re_compiledRegExp_t * const pRe
                          , unsigned int idxCS
                          , unsigned int firstAddr
                          , bool asCCode
                          )
{
    const char *s1, *s2, *s3;
    if(asCCode)
    {
        s1 = "    /* ";
        s2 = " */";
        s3 = ",";
    }
    else
    {
        s1 = "";
        s2 = "  ";
        s3 = "";
    }

    const uint8_t * const charSet = getAddrOfCharSetInRe(pRe, idxCS);
    _Static_assert(sizeof(re_charSet_t) == 8u*4u, "printf format string doesn't fit");
    for(unsigned int u=0u; u<8u; ++u)
    {
        fprintf( ostream
               , asCCode? "%s%04u%s  I_DC(0x%02X, 0x%02X, 0x%02X, 0x%02X)%s\n"
                        : "%s%04u%s  I_DC(%02X, %02X, %02X, %02X)%s\n"
               , s1
               , firstAddr + u*4u
               , s2
               , (unsigned)charSet[u*4u + 0u]
               , (unsigned)charSet[u*4u + 1u]
               , (unsigned)charSet[u*4u + 2u]
               , (unsigned)charSet[u*4u + 3u]
               , s3
               );
    }
} /* re_printCharSetBinary */
#endif


#if RE_REQUIRE_MATCHER == 1
/**
 * Check for a character if it is in the character set.
 *   @return
 * Get \a true if the set \a charSet contains \a c, \a false if not.
 *   @param charSet
 * The character set.
 *   @param c
 * The character to check.
 */
bool re_isCharInCharSet(const re_charSet_t charSet, uint8_t c)
{
    return (charSet[(unsigned)c/8u] & (1u<<(c & 7u))) != 0u;

} /* re_isCharInCharSet */
#endif