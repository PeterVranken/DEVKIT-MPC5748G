/**
 * @file re_regExpCompiler.c
 * Implementation of a simple regular expression matcher.
 *
 * Normal, printable characters, except for special characters mentioned below (e.g.,
 * parenthesis, anchors, etc.), match the character itself.
 *
 * Some special characters can match the character itself, if they are escaped with the
 * backslash. Moreover, some escape sequences are a short form of commonly used character
 * sets:
 *   \d: Character set [0-9]
 *   \h: Character set [0-9a-zA-Z]
 *   \a: Character set [a-z]
 *   \A: Character set [a-zA-Z]
 *   \s: Character set [ \t\f\r]
 *   \f: Character 0x0C
 *   \r: Character 0x0D
 *   \n: Character 0x0A
 *   \t: Character 0x09
 *   \xHH: Character with ASCII code 0xHH (H being a hex digit)
 *   \N: Character set [\r\n]
 *   \i: Character set [a-zA-Z_]
 *   \I: Character set [a-zA-Z_0-9] (\i\I* denotes a valid identifier)
 *   \\: Character '\' itself
 *
 * .: The dot matches every character but a newline.
 *
 * Anchors ^, $: They match at the beginning and end of the input stream, respectively, but
 * they don't consume any input character.
 *
 * [abc1-9x-z]: Character sets. All listed single characters, or the characters in the
 * ranges x-y, both including, match. If the first mentioned character is ']' then it isn't
 * the closing bracket but a character in the set. A valid set would be, e.g., []a], which
 * matches ']' and 'a', whereas [a]] is not a valid set. Character sets support a few
 * escape sequences to get special characters into the set. These are: \f, \r, \n, \t, \xHH
 * and \\. Caution, the ']' can't be the first character of a range, i.e., []-}] would
 * match only three single characters but not all from ']' till '}'. Write []^-}] instead.
 *
 * [^abc1-9x-z]: Inverse character sets. All but the listed single characters and the
 * characters in the ranges x-y, both including, match. The caret behind the opening
 * bracket itself does not belong to the set. If the first mentioned character is ']' then
 * it isn't the closing bracket but a character in the set. A valid set would be, e.g., [^]a],
 * which matches everything but ']' and 'a', whereas [^a]] is not a valid set.
 *
 * (): Parenthesis can be used to define sequences, which are subject to repetitions or to
 * structure OR expressions.
 *
 * ?, *, +, {n}, {m,M}: Repetition indicators. They can be attached to a single immediate
 * match element (mostly the dot or a literal character) or to a sequence formed with
 * parenthesis, i.e., placed behind the closing pararenthesis. When using the form with the
 * braces, then the element, which the repetition indicator is attached to needs to match
 * the input exactely n times or m..M times, both including. We have these constraints:\n
 *   1) 1 <= n <= 254\n
 *   2) Either 0 <= m <  M <= 255\n
 *      or     0 <  m <= M <  255\n
 * Note, M = 255 doesn't mean 255 times but it is the way to state "infinite" or
 * "unbounded". ?, *, + are common abbreviations only; they stand for {0,1}, {0,255} and
 * {1,255}, respectively. Note, the parser doesn't accept any white space; { 1, 2}, {1,2 },
 * etc., is considered a syntax error.
 *
 * Repetition indicators must not be applied to elements, which are potentially empty. This
 * would shape an inifinite number of possible match paths and the matcher would soon run
 * out of memory. Expressions like "(.?)+", "(x*)?" or "(x?|y)+" are invalid. Note, a
 * repetition with upper bounds would still be possible without out-of-memory but is
 * nonetheless rejected as those constructs are anyway useless and likely not meant by
 * intention.
 *
 * ?: Non-greedy match. This symbol can be attached to any of the repetition indicators in
 * order to make it "non-greedy". The repeated element is matched against the input only as
 * often as minimally needed to successfully match the entire regular expression. Note, for
 * many use cases, there is no difference in the final match result but non-greedy matching
 * tends to require less runtime memory for matching (on cost of a tendency to need more
 * CPU time). On an embedded target, the preferred use of non-greedy repetitions can help
 * to optimize RAM consumption.
 *
 * |: OR expression. Only one of the operands needs to match. The operator has the lowest
 * priority, which means that "abc|xyz" is equivalent to "(abc)|(xyz)" but not to
 * "ab(c|x)yz". More operands are allowed, "a|b|c" would be valid.
 *
 * <>: Capture groups. They are the means to bring the matches of particular
 * sub-expressions into the final result. They are addressed to by zero based index and,
 * after matching, this index is required for fetching such a result. The index of capture
 * groups is the order of appearance of their opening angular brackets in the regular
 * expression. Capture groups form a valid pair of parenthesis, which can't overlap with
 * other pairs of parenthesis. An expression like "a<b(cd>)+" or "a{3,<4}x>" is undefined,
 * whereas "a<b(cd)+>" and "<a{3,4}x>" were correct (and probably meant). Capture groups
 * can't have a repetition indicator but they may be used in the inner of a loop. In which
 * case a successfully matching expression can have many values of the capture group in its
 * result. However, normal use cases won't require this. If no capture group is inside a
 * loop then the maximum number of results is bounded and known, which supports the memory
 * configuration for the matcher result.
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
 *   re_compEmitCode
 *   re_compile
 *   usage
 *   main
 * Local functions
 *   isCOk
 *   getToken
 *   printIStream
 *   printCompiledIStream
 *   insertCodeAt
 *   compileUInt
 *   compileRepetition
 *   isSpecialChar
 *   getNextIdxLoop
 *   getNextIdxCaptureGroup
 *   compileImmediate
 *   compileSequence
 *   compileOrExpr
 *   exportCompiledExpression
 *   usage
 */

/*
 * Include files
 */

#include "re_regExpCompiler.h"

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <assert.h>

#include "re_charSet.h"
#include "re_regExpMatcher.h"

/*
 * Defines
 */

#define MAX_LEN_ISTREAM     1000u

/** The number of operands, which are allowed for an OR expression. This number of integers
    is stored on the stack of the compiler and in the worst case for each recursion level.
    As long as the compiler is just run on the development machine, this stack usage is
    uncritical and the value can be chosen beyond good and evil. If the compiler should run
    on a memory constrained embedded target then the value should better be configured as
    little as reasonably possible. A value of three will already suffice for the majority of
    real expressions. */
#ifdef __WINNT
# define MAX_NO_OR_OPERANDS  50u
#else
# define MAX_NO_OR_OPERANDS  4u
#endif

#if RE_REQUIRE_MAIN != 0
/** Maximum number of character sets, which may be used in a single regular expression. The
    footprint of a single charset is sizeof(uint16_t) or 2 Byte.\n
      The macro is used only in the optional main function for the configuration of the
    run of the compiler. */
# define RE_MAX_NO_CHAR_SETS_IN_REGEXP      100u
#endif

#if RE_REQUIRE_MAIN != 0
/** Maximum number of different character sets, which may be used in a single regular
    expression. The footprint of a single charset is sizeof(re_charSet_t) or 32 Byte.\n
      The macro is used only in the optional main function for the configuration of the
    run of the compiler. */
# define RE_MAX_NO_DIFF_CHAR_SETS_IN_REGEXP 50u
#endif

/** Common expression: Check of compiler's main status variable to see if we can still
    continue. */
#define COMP_OK     (isCOk(pCompiler))

/*
 * Local type definitions
 */


/*
 * Local prototypes
 */

#if RE_REQUIRE_COMPILER == 1
static void compileOrExpr(struct re_compiler_t * const pCompiler, bool *pPotentiallyEmpty);
#endif

/*
 * Data definitions
 */

/*
 * Function implementation
 */

#if RE_REQUIRE_COMPILER == 1
/**
 * Common expression: Check of compiler's main status variable to see if we can still
 * continue.
 *   @return
 * Get \a true if there is still no compilation error. In case of \a false, compilation
 * can't be proceeded.
 *   @param[in] pCompiler
 * The compiler by reference.
 */
static inline bool isCOk(struct re_compiler_t * const pCompiler)
{
    return pCompiler->err == re_errComp_success;
}


/**
 * In states, where the compiler expects a specific character, it may use this function to
 * read from the input stream. The function checks for presence of the needed character and
 * advances the stream pointer.
 *   @return
 * Get \a true if the wanted character was seen in the stream, \a false otherwise. The
 * stream pointer has not been advanced in case of \a false and nor has an error message
 * been raised.
 *   @param[in] pCompiler
 * The compiler by reference. The object contains the access elements to the input stream.
 *   @param c
 * The expected character.
 */
static inline bool getToken(struct re_compiler_t * const pCompiler, uint8_t c)
{
    if(*pCompiler->pC == c)
    {
        ++ pCompiler->pC;
        return true;
    }
    else
        return false;
}
#endif


#if RE_REQUIRE_MAIN == 1
/**
 * Display all instructions in a compiled instruction stream.
 *   @param ostream
 * An output FILE stream, which to write the information in. Pass stdout in the simplest case.
 *   @param iStream
 * The compiled instruction stream to display, i.e., an array with the byte-encoded
 * instructions.
 *   @param lenIStream
 * The size of the instruction stream in Byte (not number of instructions).
 *   @param asCCode
 * The instruction stream can be printed for human reading or as a fragment of valid C
 * source code (to bring a compiled expression into an embedded software).
 */
static void printIStream( FILE *ostream
                        , const uint8_t *iStream
                        , unsigned int lenIStream
                        , bool asCCode
                        )
{
    const char *s1, *s2, *s3, *s4;
    if(asCCode)
    {
        s1 = "    /* ";
        s2 = " */";
        s3 = ",";
        s4 = "//";
    }
    else
    {
        s1 = "";
        s2 = "  ";
        s3 = "";
        s4 = ";";
    }

    /* Display all instructions in the compiled instruction stream. */
    const uint8_t *pI = iStream;
    unsigned int lenI;
    for(unsigned int idxI=0u; idxI<lenIStream; idxI+=lenI)
    {
        lenI = 1u;
/// @todo Add disassembly bytes
        switch(*pI)
        {
        case I_ILLEGAL:
            fprintf(ostream, "%s%04u%s  I_ILLEGAL%s\n", s1, idxI, s2, s3);
            break;
        case I_DIGIT:
            fprintf(ostream, "%s%04u%s  I_DIGIT%s\n", s1, idxI, s2, s3);
            break;
        case I_HEXDIGIT:
            fprintf(ostream, "%s%04u%s  I_HEXDIGIT%s\n", s1, idxI, s2, s3);
            break;
        case I_SPC:
            fprintf(ostream, "%s%04u%s  I_SPC%s\n", s1, idxI, s2, s3);
            break;
        case I_AZ:
            fprintf(ostream, "%s%04u%s  I_AZ%s\n", s1, idxI, s2, s3);
            break;
        case I_LTR:
            fprintf(ostream, "%s%04u%s  I_LTR%s\n", s1, idxI, s2, s3);
            break;
        case I_ID1ST:
            fprintf(ostream, "%s%04u%s  I_ID1ST%s\n", s1, idxI, s2, s3);
            break;
        case I_ID:
            fprintf(ostream, "%s%04u%s  I_ID%s\n", s1, idxI, s2, s3);
            break;
        case I_CRLF:
            fprintf(ostream, "%s%04u%s  I_CRLF%s\n", s1, idxI, s2, s3);
            break;
        case I_ANY:
            fprintf(ostream, "%s%04u%s  I_ANY%s\n", s1, idxI, s2, s3);
            break;
        case I_CARET:
            fprintf(ostream, "%s%04u%s  I_CARET%s\n", s1, idxI, s2, s3);
            break;
        case I_DOLLAR:
            fprintf(ostream, "%s%04u%s  I_DOLLAR%s\n", s1, idxI, s2, s3);
            break;
        case OP_LOOP:
        case OP_LOOPNG:
            {
                const bool isGreedy = *pI == OP_LOOP;
                lenI = 6u;
                unsigned int len = * ++pI;
                len = (len<<8) + (* ++pI);
                const unsigned int min = * ++pI;
                const unsigned int max = * ++pI;
                const unsigned int idxLoop = * ++pI;
                fprintf( ostream
                       , "%s%04u%s  I_LOOP%s(%u, %u, %u, %u)%s\t%s -> %u\n"
                       , s1
                       , idxI
                       , s2
                       , isGreedy? "": "_NG"
                       , idxLoop
                       , len
                       , min
                       , max
                       , s3
                       , s4
                       , idxI+lenI+len
                       );
            }
            break;
        case OP_LOOPEND:
            {
                lenI = 3u;
                unsigned int len = * ++pI;
                len = (len<<8) + (* ++pI);
                /// @todo Code cleanup: Use fetchLoop and display loop idx
                fprintf( ostream
                       , "%s%04u%s  I_LOOPEND(%u)%s\t%s <- %u\n"
                       , s1
                       , idxI
                       , s2
                       , len
                       , s3
                       , s4
                       , idxI-len-6u
                       );
            }
            break;
        case OP_OR:
            {
                lenI = 3u;
                unsigned int len = * ++pI;
                len = (len<<8) + (* ++pI);
                fprintf( ostream
                       , "%s%04u%s  I_OR(%u)%s\t%s -> %u\n"
                       , s1
                       , idxI
                       , s2
                       , len
                       , s3
                       , s4
                       , idxI+lenI+len
                       );
            }
            break;
        case OP_JMP:
            {
                lenI = 3u;
                unsigned int dist = * ++pI;
                dist = (dist<<8) + (* ++pI);
                fprintf( ostream
                       , "%s%04u%s  I_JMP(%u)%s\t%s -> %u\n"
                       , s1
                       , idxI
                       , s2
                       , dist
                       , s3
                       , s4
                       , idxI+lenI+dist
                       );
            }
            break;
        case OP_CAP:
            {
                lenI = 2u;
                unsigned int idxCGrp = * ++pI;
                fprintf(ostream, "%s%04u%s  I_CAP(%u)%s\n", s1, idxI, s2, idxCGrp, s3);
            }
            break;
        case OP_CAPEND:
            {
                lenI = 2u;
                unsigned int idxCGrp = * ++pI;
                fprintf(ostream, "%s%04u%s  I_CAPEND(%u)%s\n", s1, idxI, s2, idxCGrp, s3);
            }
            break;

        case OP_CHARSET:
            {
                lenI = 3u;
                unsigned int dist = * ++pI;
                dist = (dist<<8) + (* ++pI);
                fprintf( ostream
                       , "%s%04u%s  I_CHARSET(%u)%s\t%s -> %u\n"
                       , s1
                       , idxI
                       , s2
                       , dist
                       , s3
                       , s4
                       , idxI+lenI+dist
                       );
            }
            break;

        case OP_ESC:
            lenI = 2u;
            fprintf(ostream, "%s%04u%s  I_LIT_ESC('\\x%02X')%s\n", s1, idxI, s2, * ++pI, s3);
            break;
        default /* I_LIT */:
            assert((*pI & ~0x7Fu) == 0);
            if(isprint(*pI))
                fprintf(ostream, "%s%04u%s  I_LIT('%c')%s\n", s1, idxI, s2, *pI, s3);
            else
                fprintf(ostream, "%s%04u%s  I_LIT('\\x%02X')%s\n", s1, idxI, s2, *pI, s3);

        } /* switch(Which opcode?) */

        ++ pI;

    } /* for(All instructions in fragment of compiled expression) */
} /* printIStream */


/**
 * Display the compiled instruction stream. Instructions and constant data are displayed.
 *   @param ostream
 * An output FILE stream, which to write the information in. Pass stdout in the simplest case.
 *   @param pRe
 * The compiled regular expression by reference, which constains the instruction stream to
 * display.
 *   @param asCCode
 * The instruction stream can be printed for human reading or as a fragment of valid C
 * source code (to bring a compiled expression into an embedded software).
 */
static void printCompiledIStream( FILE *ostream
                                , const struct re_compiledRegExp_t * const pRe
                                , bool asCCode
                                )
{
    printIStream(ostream, pRe->iStream, pRe->lenIStream, asCCode);

    /* The sequence of matcher instructions can be followed by some constant data needed by
       those instructions. */
    unsigned int idxIOfCharSet = pRe->lenIStream;
    for(unsigned idxCS=0u; idxCS<pRe->noCharSets; ++idxCS)
    {
        re_printCharSetBinary(ostream, pRe, idxCS, idxIOfCharSet, asCCode);
        idxIOfCharSet += sizeof(re_charSet_t);
    }
} /* printCompiledIStream */
#endif


#if RE_REQUIRE_COMPILER == 1
/**
 * Insert a code fragments into the already existing instruction stream.
 *   @param pCompiler
 * The compiler object by reference.
 *   @param code
 * A byte array containing \a noBytes instruction bytes. All of these will be copied into
 * the existing instruction stream.
 *   @param noBytes
 * The number of instruction bytes to insert. No bytes are copied and an error is raised if
 * this number of additional instruction bytes exceeds the capacity of the instruction
 * stream buffer.
 *   @param insertAt
 * The position of the first inserted byte as zero based byte index in the stream. Bytes at
 * and after that prosition will be moved towards higher addresses (indexes). Range is
 * 0..pCompiler->re.lenIStream, both including. If pCompiler->re.lenIStream is passed in
 * then "inserting" reduces to simple appending.
 */
static inline void insertCodeAt( struct re_compiler_t * const pCompiler
                               , const uint8_t * const code
                               , unsigned int noBytes
                               , unsigned int insertAt
                               )
{
    assert(noBytes >= 1u);
    assert(pCompiler->err == re_errComp_success);
    assert(insertAt <= pCompiler->re.lenIStream);
    if(pCompiler->re.lenIStream + noBytes <= pCompiler->maxLenIStream)
    {
        if(insertAt < pCompiler->re.lenIStream)
        {
            memmove( &pCompiler->re.iStream[insertAt+noBytes]
                   , &pCompiler->re.iStream[insertAt]
                   , pCompiler->re.lenIStream - insertAt
                   );

            /* Inform dependent modules about the re-organization of already emitted code. */
            re_onInstructionMove(pCompiler, /*idxIFrom*/ insertAt, /*distance*/ noBytes);
        }
        memcpy(&pCompiler->re.iStream[insertAt], code, noBytes);
        pCompiler->re.lenIStream += noBytes;
    }
    else
    {
        printf( "insertCodeAt: Compiled expression doesn't fit into buffer of length %u\n"
              , pCompiler->maxLenIStream
              );
        pCompiler->err = re_errComp_maxLenIStreamExceeded;
    }
} /* insertCodeAt */


/**
 * Read an unsigned integer number from the input stream. Up to nine digits are supported.
 *   @return
 * Get \a true if a suitable number could be read.
 *   @param pCompiler
 * The compiler, which, e.g., contains the input stream.
 *   @param pUIntNum
 * The read number is returned by reference.
 *   @param minValue
 * The read number * \a pUIntNum needs to be in the range \a minValue ..  \a maxValue, both
 * including.
 *   @param maxValue
 * The read number * \a pUIntNum needs to be in the range \a minValue ..  \a maxValue, both
 * including. It is \a minValue <= \a maxValue and \a maxValue <= 999999999.
 */
static bool compileUInt( struct re_compiler_t * const pCompiler
                       , unsigned int * const pUIntNum
                       , unsigned int minValue
                       , unsigned int maxValue
                       )
{
    /* We use atoi for the conversion, which doesn't return overflow information. The
       longest, safely convertible number is 10^floor(log10(2^31-1))-1, so we need to limit
       this function accordingly. */
    assert(minValue <= maxValue  &&  maxValue <= 999999999u);
    #define MAX_LEN_NUM_LITERAL 9

    char numStr[MAX_LEN_NUM_LITERAL+1u];
    bool success = true;
    unsigned int idxD = 0u;
    while(isdigit((int)*pCompiler->pC))
    {
        if(idxD < MAX_LEN_NUM_LITERAL)
            numStr[idxD++] = *pCompiler->pC;
        else
            success = false;

        ++ pCompiler->pC;
    }
    if(success)
        success = idxD > 0u;
    if(success)
    {
        assert(idxD < sizeof(numStr));
        numStr[idxD] = '\0';
        *pUIntNum = (unsigned)atoi(numStr);
        success = *pUIntNum >= minValue  &&  *pUIntNum <= maxValue;
    }

    return success;

    #undef MAX_LEN_NUM_LITERAL
} /* compileUInt */



/**
 * Check for and read a repetition operator from the input stream, i.e., ? or * or * or {n}
 * or {n,m}, with or without the non-greedy appendix ?. No code is emitted, only the parse
 * results are returned.
 *   @return
 * Get \a true if a repetition operator followed up in the input stream and could be
 * read.
 *   @param pCompiler
 * The compiler, which e.g., contains the input stream. An error is raised in the object if
 * a repetition operator was seen in the input stream but it could not be successfully
 * read.
 *   @param pMin
 * The read minimum number of repetitions is returned by reference.
 *   @param pMin
 * The read maximum number of repetitions is returned by reference.
 *   @param pIsGreedy
 * The information, whether the repeated matching is greedy, is returned by reference.
 */
static bool compileRepetition( struct re_compiler_t * const pCompiler
                             , unsigned int * const pMin
                             , unsigned int * const pMax
                             , bool * const pIsGreedy
                             )
{
    bool gotRepetition = false;
    const char c = *pCompiler->pC;
    if(c == '?')
    {
        ++ pCompiler->pC;
        *pMin = 0u;
        *pMax = 1u;
        gotRepetition = true;
    }
    else if(c == '*')
    {
        ++ pCompiler->pC;
        *pMin = 0u;
        *pMax = UINT_MAX;
        gotRepetition = true;
    }
    else if(c == '+')
    {
        ++ pCompiler->pC;
        *pMin = 1u;
        *pMax = UINT_MAX;
        gotRepetition = true;
    }
    else if(c == '{')
    {
        ++ pCompiler->pC;
        if(compileUInt(pCompiler, pMin, /*min*/ 0, /*max*/ 254))
        {
            if(*pCompiler->pC == ',')
            {
                ++ pCompiler->pC;

                /* The range 0..0 is useless, would irritate the matcher and is not
                   allowed. */
                const unsigned int min = *pMin > 0u? *pMin: 1u;

                if(compileUInt(pCompiler, pMax, min, /*max*/ 255))
                {
                    if(*pCompiler->pC == '}')
                    {
                        ++ pCompiler->pC;

                        /* The user specifies "infinite" as 255 but this function encodes
                           it as UINT_MAX. */
                        if(*pMax == UINT8_MAX)
                            *pMax = UINT_MAX;

                        gotRepetition = true;
                    }
                    else
                        pCompiler->err = re_errComp_repMissingRBrace;
                }
                else
                    pCompiler->err = re_errComp_repBadNumberOrOutOfRange;
            }
            else if(*pCompiler->pC == '}')
            {
                ++ pCompiler->pC;

                /* The range 0..0 is useless, would irritate the matcher and is not
                   allowed. */
                if(*pMin == 0u)
                    pCompiler->err = re_errComp_repBadNumberOrOutOfRange;
                else
                {
                    /* A single number means the exact number of repetitions. */
                    *pMax = *pMin;
                    gotRepetition = true;
                }
            }
            else
                pCompiler->err = re_errComp_repBadSeparatorOrMissingRBrace;
        }
        else
            pCompiler->err = re_errComp_repBadNumberOrOutOfRange;
    }

    if(gotRepetition)
    {
        const char cNG = *pCompiler->pC;

        /* The non greedy variants are expressed by an appended question mark. */
        const bool isGreedy = cNG != '?';
        if(!isGreedy)
            ++pCompiler->pC;
        *pIsGreedy = isGreedy;

        assert(COMP_OK && *pMin <= *pMax  &&  *pMin < UINT8_MAX
               &&  (*pMax < UINT8_MAX  ||  *pMax == UINT_MAX)
              );
        return true;
    }
    else
        return false;

} /* compileRepetition */


/**
 * Check a character for having a special meaning in the context of a regular expression.
 *   @return
 * Get \a true if \a c is a special character, which can't be matched as such in the input
 * stream. If \a false is returned then \a c can be matched literally.
 *   @param c
 * The character to check.
 */
static inline bool isSpecialChar(char c)
{
    static const char specialCharAry[] = { '.', '*', '+', '(', ')', '{', '}', '[', ']', '?',
                                           '<', '>', '|', '^', '$',
                                           '\0'
                                         };
    const char *pC = &specialCharAry[0];
    while(*pC != '\0')
    {
        if(*pC == c)
            return true;
        else
            ++ pC;
    }
    return false;

} /* isSpecialChar */


/**
 * All loops in the regular expression get a unique ID. It is implemented as zero based
 * index, dealt out in the order of appearance of the loops in the expression. This
 * function returns the next ID to be used.
 *   @return
 * Get the enxt ID to use. The ID space is limited and an error can result if no more ID is
 * available.
 *   @param pCompiler
 * The compiler object by reference.
 */
static unsigned int getNextIdxLoop(struct re_compiler_t * const pCompiler)
{
    /* The limitation to 255 is required as we use a single byte to encode the index in the
       related instructions. */
    const unsigned int idx = pCompiler->nextIdxLoop;
    if(pCompiler->nextIdxLoop < UINT8_MAX)
        ++ pCompiler->nextIdxLoop;
    else
        pCompiler->err = re_errComp_maxNoLoopsExceeded;

    return idx;
} /* getNextIdxLoop */



/**
 * All capture groups in the regular expression get a unique ID. It is implemented as zero
 * based index, dealt out in the order of appearance of the opening brackets of the groups
 * in the expression. This function returns the next ID to be used.
 *   @return
 * Get the next ID to use. The ID space is limited and an error can result if no more ID is
 * available.
 *   @param pCompiler
 * The compiler object by reference.
 */
static unsigned int getNextIdxCaptureGroup(struct re_compiler_t * const pCompiler)
{
    /* The limitation to 255 is required as we use a single byte to encode the index in the
       related instructions. */
    const unsigned int idx = pCompiler->re.noCaptureGrps;
    if(idx < UINT8_MAX)
        ++ pCompiler->re.noCaptureGrps;
    else
        pCompiler->err = re_errComp_maxNoCaptureGroupsExceeded;

    return idx;

} /* getNextIdxCaptureGroup */


/**
 * Check for and compile an immediate match element. This is normally a literal character,
 * but can also be an escaped character (a character, which would have a special meaning if
 * not escaped) or the anchors, beginning and end of input.
 *   @return
 * Get \a true if the input continues with a symbol that checks for the match with a single
 * character, i.e., mostly a simple literal. \a false indicates that the input rather
 * contains a special character, e.g., an opeing parenthesis to beginn a new
 * sub-expression.
 *   @param pCompiler
 * The compiler object by reference.
 *   @param pPotentiallyEmpty
 * The function indicates by reference, whether the immediate match is possible even
 * without consuming a character from the matched string. (This is possible for the
 * anchors.)
 *   @note
 * Even if the function returns true it doesn't guarantee that it wouldn't set a compiler
 * error. \a true doesn't mean success but just that there is no alternative input
 * interpretation.
 */
static bool compileImmediate( struct re_compiler_t * const pCompiler
                            , bool * const pPotentiallyEmpty
                            )
{
    bool gotImmediate = false;
    const char c = *pCompiler->pC;

    if(re_compileCharSet(pCompiler))
    {
        *pPotentiallyEmpty = false;
        gotImmediate = true;
    }
    else if(c == '\\')
    {
        ++ pCompiler->pC;
        const char c = * pCompiler->pC++;
        uint8_t iStream[2];
        unsigned int lenIStream = 1u;
        switch(c)
        {
        case 'd':  iStream[0] = I_DIGIT; break;
        case 'h':  iStream[0] = I_HEXDIGIT; break;
        case 's':  iStream[0] = I_SPC; break;
        case 'a':  iStream[0] = I_AZ; break;
        case 'A':  iStream[0] = I_LTR; break;
        case 'i':  iStream[0] = I_ID1ST; break;
        case 'I':  iStream[0] = I_ID; break;
        case 'f':  iStream[0] = I_LIT('\f'); break;
        case 'r':  iStream[0] = I_LIT('\r'); break;
        case 'n':  iStream[0] = I_LIT('\n'); break;
        case 'N':  iStream[0] = I_CRLF; break;
        case '\\': iStream[0] = I_LIT('\\'); break;

        case 'x':
            if(re_compileHexByte(pCompiler, &iStream[0]) && (iStream[0] & ~0x7Fu) != 0u)
            {
                iStream[1] = iStream[0];
                iStream[0] = OP_ESC;
                lenIStream = LEN_I_LIT_ESC;
            }
            break;

        default:
            /* Parenthesis and other characters which are normally operators can be
               matched literally, too, if they are escaped. (The escape character itself
               can be matched in the same way, see above.) */
            if(isSpecialChar(c))
                iStream[0] = I_LIT(c);
            else
                pCompiler->err = re_errComp_invalidEscape;
        }
        if(COMP_OK)
        {
            re_compEmitCode(pCompiler, iStream, lenIStream);
            *pPotentiallyEmpty = false;
            gotImmediate = true;
        }
        else
            *pPotentiallyEmpty = true;
    }
    else if(isprint((int)c) && !isSpecialChar(c))
    {
        ++ pCompiler->pC;

        uint8_t iStream[2];
        unsigned lenIStream;
        if(((unsigned)c & 0x80) == 0u)
        {
            lenIStream = 1u;
            iStream[0] = I_LIT(c);
        }
        else
        {
            lenIStream = 2u;
            iStream[0] = OP_ESC;
            iStream[1] = c;
        }
        re_compEmitCode(pCompiler, /* code */ iStream, lenIStream);
        *pPotentiallyEmpty = false;
        gotImmediate = true;
    }
    else if(getToken(pCompiler, '.'))
    {
        const uint8_t instruction = I_ANY;
        re_compEmitCode(pCompiler, /* code */ &instruction, 1u);
        *pPotentiallyEmpty = false;
        gotImmediate = true;
    }
    else if(getToken(pCompiler, '^'))
    {
        const uint8_t instruction = I_CARET;
        re_compEmitCode(pCompiler, /* code */ &instruction, 1u);
        *pPotentiallyEmpty = true;
        gotImmediate = true;
    }
    else if(getToken(pCompiler, '$'))
    {
        const uint8_t instruction = I_DOLLAR;
        re_compEmitCode(pCompiler, /* code */ &instruction, 1u);
        *pPotentiallyEmpty = true;
        gotImmediate = true;
    }
    else
        *pPotentiallyEmpty = true;

    return gotImmediate;

} /* compileImmediate */


/**
 * Compile a sequence of matching elements, i.e., literal characters, loops and anchors. A
 * sequence forms the operands of an OR.
 *   @param pCompiler
 * The compiler object by reference.
 *   @param pPotentiallyEmpty
 * The function indicates by reference, whether the immediate match is possible even
 * without consuming a character from the matched string. (This is possible for the
 * anchors and for loops with a minimum of zero repetitions.)
 */
static void compileSequence(struct re_compiler_t * const pCompiler, bool *pPotentiallyEmpty)
{
    *pPotentiallyEmpty = true;

    /* Remind the beginning of the sequence so that we can later see if it is not empty. */
    const unsigned int idxISeq = pCompiler->re.lenIStream;
    do
    {
        bool potentiallyEmpty = true;

        /* Remind the beginning of the code of the next immediate or a potential nested
           sequence. If we later find a repetition indicator then we will have to insert
           the loop instruction here. */
        const unsigned int idxIRepeatable = pCompiler->re.lenIStream;

        bool haveRepeatable = false;
        if(compileImmediate(pCompiler, &potentiallyEmpty))
            haveRepeatable = true;
        else if(COMP_OK && getToken(pCompiler, '('))
        {
            compileOrExpr(pCompiler, &potentiallyEmpty);
            if(COMP_OK)
            {
                if(getToken(pCompiler, ')'))
                    haveRepeatable = true;
                else
                    pCompiler->err = re_errComp_missingRParen;
            }
        }
        /// @todo Replace preliminary capture group syntax with help of token scanner and escape
        else if(COMP_OK && getToken(pCompiler, '<'))
        {
            const unsigned int idxCGrp = getNextIdxCaptureGroup(pCompiler);
            const uint8_t iStream[] = {I_CAP(idxCGrp)};
            re_compEmitCode(pCompiler, /* code */ iStream, sizeof(iStream));

            compileOrExpr(pCompiler, &potentiallyEmpty);
            if(COMP_OK)
            {
                if(getToken(pCompiler, '>'))
                {
                    *pPotentiallyEmpty = *pPotentiallyEmpty && potentiallyEmpty;
                    const uint8_t iStream[] = {I_CAPEND(idxCGrp)};
                    re_compEmitCode(pCompiler, /* code */ iStream, sizeof(iStream));
                }
                else
                    pCompiler->err = re_errComp_missingRParen;
            }
        }
        else
        {
            /* There's nothing in the input, which can be consumed for a sequence. This is
               an error only, if we didn't consume anything so far - a sequence can't be
               empty. */
            if(COMP_OK &&  idxISeq == pCompiler->re.lenIStream)
                pCompiler->err = re_errComp_unspecifiedSyntaxErr;

            break;
        }

        /* A group (if it is not a pure cature group) or a single character match may have
           a repetition indication. */
        if(COMP_OK && haveRepeatable)
        {
            unsigned int min, max;
            bool isGreedy;
            if(compileRepetition(pCompiler, &min, &max, &isGreedy))
            {
                /* It is not allowed to repeat an expression, which matches against the
                   empty string. This leads to infinite ambiguitied in the matcher. */
                if(COMP_OK && potentiallyEmpty)
                    pCompiler->err = re_errComp_potentiallyEmptyBodyOfLoop;

                if(COMP_OK)
                {
                    const unsigned int lenBody = pCompiler->re.lenIStream - idxIRepeatable;
                    assert(lenBody > 0u);
                    uint8_t iStream[6];
                    iStream[0] = isGreedy? OP_LOOP:  OP_LOOPNG;
                    iStream[1] = lenBody >> 8;
                    iStream[2] = lenBody & 0xFFu;
                    iStream[3] = min;
                    iStream[4] = (uint8_t)(max>=UINT8_MAX? UINT8_MAX: max);
/// @todo TBC Why do we need a loop idx for simple, unbounded loops? This unnecessarily exhausts our limited number space of indexes. If changed then modify help text of error code re_errComp_maxNoLoopsExceeded, too
                    iStream[5] = getNextIdxLoop(pCompiler);
                    insertCodeAt(pCompiler, iStream, sizeof(iStream), /*at*/ idxIRepeatable);

                    /* The loop is terminated by an instruction for repeating the body code. */
                    iStream[0] = OP_LOOPEND;
                    re_compEmitCode(pCompiler, /* code */ iStream, 3u);

                    if(min == 0u)
                        potentiallyEmpty = true;
                }
            }
        }

        *pPotentiallyEmpty = *pPotentiallyEmpty && potentiallyEmpty;
    }
    while(COMP_OK);

} /* compileSequence */


/**
 * Compile an OR expression.
 *   @param pCompiler
 * The compiler object by reference.
 *   @param pPotentiallyEmpty
 * The function indicates by reference, whether the immediate match is possible even
 * without consuming a character from the matched string. This is possible if at least one
 * operand of the found OR is potentially empty.
 */
static void compileOrExpr(struct re_compiler_t * const pCompiler, bool *pPotentiallyEmpty)
{
    /* Even if this code is not primarily meant for execution on an embedded system with
       constrained memory, we limit the number of syntax recursions, effectively the
       allowed levels of parentheses, in order to get reasonable feedback in case of
       unreasonable input. */
    if(pCompiler->recursionDepth < pCompiler->maxAllowedRecursionDepth)
    {
        ++ pCompiler->recursionDepth;
        if(pCompiler->recursionDepth > pCompiler->maxRecursionDepth)
            pCompiler->maxRecursionDepth = pCompiler->recursionDepth;
    }
    else
    {
        assert(pCompiler->err == re_errComp_success);
        pCompiler->err = re_errComp_maxRecursionDepthExceeded;
        return;
    }

    *pPotentiallyEmpty = false;

    _Static_assert(MAX_NO_OR_OPERANDS >= 2, "Invalid configuration");
    unsigned int idxIJmpAry[MAX_NO_OR_OPERANDS-1u];
    unsigned int noIJmp = 0u;
    do
    {
        /* Remind the beginning of some code, which may later be recognized as an
           alternative of an OR clause. If we confirm this later then we will have to
           insert the OR instruction here. */
        const unsigned int idxIOrOperand = pCompiler->re.lenIStream;

        bool potentiallyEmpty;
        compileSequence(pCompiler, &potentiallyEmpty);
        *pPotentiallyEmpty = *pPotentiallyEmpty || potentiallyEmpty;
        if(COMP_OK)
        {
            /* The OR operation has lowest priority. It may combine different sequences;
               abc|def means (abc)|(def) but not ab(c|d)ef. */
            if(getToken(pCompiler, '|'))
            {
                /* +3: At the end of the alternative we have a jump instruction of this
                   length. */
                const unsigned int lenOrOperand = pCompiler->re.lenIStream
                                                  - idxIOrOperand + 3u;
                assert(lenOrOperand > 0u);
                uint8_t iStreamOr[] = {I_OR(lenOrOperand)};
                insertCodeAt( pCompiler
                            , iStreamOr
                            , sizeof(iStreamOr)
                            , /*insertAt*/ idxIOrOperand
                            );

                /* At the end of the (not last) alternative we need a jump to the end
                   of the entire OR clause. The jump distance is not known yet, so we
                   insert the instruction with a preliminary value and remind it for
                   later update. */
                if(noIJmp < sizeof(idxIJmpAry)/sizeof(idxIJmpAry[0]))
                {
                    idxIJmpAry[noIJmp++] = pCompiler->re.lenIStream;
                    uint8_t iStreamJmp[] = {I_JMP(0u)};
                    re_compEmitCode(pCompiler, iStreamJmp, sizeof(iStreamJmp));
                }
                else
                    pCompiler->err = re_errComp_maxNoOrAlternativesExceeded;
            }
            else
                break;
        }
    }
    while(COMP_OK);

    /* Now update the jump instructions, if any. */
    while(COMP_OK &&  noIJmp > 0u)
    {
        /* 3: Length of jump instruction itself. */
        const unsigned int idxIJmp = idxIJmpAry[--noIJmp];
        assert(pCompiler->re.iStream[idxIJmp] == OP_JMP);
        const unsigned int dist = pCompiler->re.lenIStream - (idxIJmp + 3u);
        assert(dist < UINT16_MAX);
        pCompiler->re.iStream[idxIJmp+1u] = (dist & 0xFF00u) >> 8;
        pCompiler->re.iStream[idxIJmp+2u] = (dist & 0x00FFu) >> 0;
    }

    -- pCompiler->recursionDepth;
} /* compileOrExpr */


/**
 * Append a code fragment to the already existing instruction stream.
 *   @param pCompiler
 * The compiler object by reference.
 *   @param code
 * A byte array containing \a noBytes instruction bytes. All of these will be copied to
 * the tail of the current instruction stream.
 *   @param noBytes
 * The number of instruction bytes to append. No bytes are copied and an error is raised if
 * this number of additional instruction bytes exceeds the capacity of the instruction
 * stream buffer.
 */
void re_compEmitCode( struct re_compiler_t * const pCompiler
                    , const uint8_t * const code
                    , unsigned int noBytes
                    )
{
    insertCodeAt(pCompiler, code, noBytes, /* insertAt */ pCompiler->re.lenIStream);

} /* re_compEmitCode */


/**
 * Main API: Call of the regular expression compiler.
 *   @param[in,out] pCompiler
 * The compiler object by reference.\n
 *   On entry, all fields have been configured, which relate to the user specified memory
 * spaces, i.e., the pointers to the memory areas to be used and the capacities of these
 * areas. This relates to the instruction stream buffer (re.istream and .maxLenIStream) and
 * the temporary storage for character sets (idxICharSetAry, maxNoICharSet and charSetMem,
 * maxNoCharSets).\n
 *   On exit, the compiler contains the compiled regular expression (re), the status
 * field, err, which potentially indicates a compilation error and the actually required
 * recursion depth.
 *   @param[in] regExpAsString
 * The regular expression to compile.
 *   @param[in] matchAnywhere
 * If \a true then the compiled regular expression can match at any position in the
 * input character stream. If \a false the it needs to match from the beginning of the
 * input stream. Note, that this behavior can be influenced by the regular instruction
 * itself, i.e., by using the anchor character ^.
 *   @param[in] maxAllowedRecursionDepth
 * The compiler uses recursion if the regular expression uses nested levels of parenthesis.
 * On an embedded system this can mean a potential robustness issue. To also support
 * embeded systems, the compiler has a limitation of recursions. If the stated maximum
 * would normally be exceeded for successful compilation, the compiler instead aborts the
 * compilation with according error code.\n
 *   As a rule of thumb, the required depth is equal to the maximum number of nested
 * paranethesis levels.
 */
bool re_compile( struct re_compiler_t * const pCompiler
               , const char *regExpAsString
               , bool matchAnywhere
               , unsigned int maxAllowedRecursionDepth
               )
{
    /* First do a plausibility check if the compiler object has been properly
       pre-configured by the user.
         Note, we shortly disable the C compiler's warning about suggested use of
       parenthesis as it would make the anyway complex condition entirely unreadable. */
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wparentheses"
    if(pCompiler->re.iStream == NULL
       ||  pCompiler->maxLenIStream < 10u  ||  pCompiler->maxLenIStream > UINT16_MAX
       ||  pCompiler->idxICharSetAry == NULL
           &&  (pCompiler->maxNoICharSet != 0u  ||  pCompiler->maxNoCharSets != 0u)
       ||  pCompiler->idxICharSetAry != NULL
           &&  (pCompiler->maxNoICharSet < 1u  ||  pCompiler->maxNoICharSet > UINT16_MAX)
       ||  pCompiler->charSetMem == NULL
           &&  (pCompiler->maxNoICharSet != 0u  ||  pCompiler->maxNoCharSets != 0u)
       ||  pCompiler->charSetMem != NULL
           &&  (pCompiler->maxNoCharSets < 1u  ||  pCompiler->maxNoCharSets >= UINT16_MAX)
       ||  pCompiler->idxICharSetAry == NULL  &&  pCompiler->charSetMem != NULL
       ||  pCompiler->idxICharSetAry != NULL  &&  pCompiler->charSetMem == NULL
       ||  maxAllowedRecursionDepth < 1u  ||  maxAllowedRecursionDepth > 1000u
      )
    {
        pCompiler->err = re_errComp_badMemoryConfiguration;
    }
    else
        pCompiler->err = re_errComp_success;
    #pragma GCC diagnostic pop

    /* Reset the counters. */
    if(COMP_OK)
    {
        pCompiler->re.lenIStream = 0u;

        pCompiler->cStream = regExpAsString;
        pCompiler->pC = regExpAsString;

        /* Index 0 is reserved for implementing "matchAnywhere", see below. */
        pCompiler->nextIdxLoop = matchAnywhere? 1u: 0u;

        pCompiler->noICharSet = 0u;
        pCompiler->re.noCharSets = 0u;
        pCompiler->re.noCaptureGrps = 0u;

        pCompiler->recursionDepth = 0u;
        pCompiler->maxRecursionDepth = 0u;
        pCompiler->maxAllowedRecursionDepth = maxAllowedRecursionDepth;

        if(*pCompiler->pC != '\0')
        {
            bool potentiallyEmpty __attribute__((unused));
            compileOrExpr(pCompiler, &potentiallyEmpty);
            if(COMP_OK &&  *pCompiler->pC != '\0')
                pCompiler->err = re_errComp_notAllInputConsumed;

            /* Matching anywhere is implemented by preceding the user specified regular
               expression with the non-greedy consume-everything, ".*?". This is
               however not required (and would lead to higher matching effort) if the
               compiled expression anyway begins with the anchor instruction. */
            if(COMP_OK && matchAnywhere
               &&  pCompiler->re.lenIStream >= 1  &&  *pCompiler->re.iStream != I_CARET
              )
            {
                static const uint8_t iStream[10] =
                {
                    I_LOOP_NG(0, 1, 0, 255),
                    I_ANY,
                    I_LOOPEND(1),
                };
                insertCodeAt(pCompiler, iStream, sizeof(iStream), /*at*/ 0);
            }

            if(COMP_OK)
                re_writeCharSets(pCompiler);
        }
        else
            pCompiler->err = re_errComp_emptyRegularExpr;
    }

    return COMP_OK;

} /* re_compile */
#endif


#if RE_REQUIRE_MAIN == 1
/**
 * Export a successfully compiled regular expression as fragment of valid C code, which
 * allows integration of the expression into some embedded software program.
 *   @param ostream
 * The code is written into this stream.
 *   @param pRe
 * The compiler object by reference after successful compilation, so that it contains the
 * compiled regular expression to export.
 *   @param namespc
 * The namespace used for the the global, regular expression related elements in the
 * exported C source code snippet. The passed string will precede the name of all of these
 * elements.
 *   @param nameRe
 * The regular expression needs to have a (short) name; it is used to make the generated C
 * code elements specific for the given expression. This way, several regular expression
 * can co-exist in the global namespace of C.
 */
void exportCompiledExpression( FILE *file
                             , const struct re_compiler_t * const pCompiler
                             , const char *namespc
                             , const char *nameRe
                             )
{
    fprintf( file
           , "/** The instruction stream of compiled regular expression %s. The regular\n"
             "    expression is:\\n\n"
             "    %s */\n"
             "static const uint8_t %s%s_iStream[%u] =\n"
             "{\n"
           , nameRe
           , pCompiler->cStream
           , namespc
           , nameRe
           , (unsigned)(pCompiler->re.lenIStream
                        + pCompiler->re.noCharSets*sizeof(re_charSet_t)
                       )
           );
    printCompiledIStream(file, &pCompiler->re, /*asCCode*/ true);
    fprintf( file
           , "};\n"
             "\n"
             "/** The compiled regular expression %s:\\n\n"
             "    %s */\n"
             "static const struct re_compiledRegExp_t %s%s =\n"
             "{\n"
             "    .iStream       = (uint8_t*)&re_%s_iStream[0],\n"
             "    .lenIStream    = %uu,\n"
             "    .noCaptureGrps = %uu,\n"
             "    .noCharSets    = %uu,\n"
             "};\n"
             "\n"
             "\n"
           , nameRe
           , pCompiler->cStream
           , namespc
           , nameRe
           , nameRe
           , pCompiler->re.lenIStream
           , pCompiler->re.noCaptureGrps
           , pCompiler->re.noCharSets
           );

} /* exportCompiledExpression */



/**
 * Print a usage message.
 */
static void usage(void)
{
    const static char *usageMsg =
      "usage: regExpDemo <options> <inputStrings>\n"
      "  <options>: A combination of different options. An option is a named switch\n"
      "with a value. Boolean switches have the implcit value true, other switches have\n"
      "the next, blank separated command line argument as value.\n"
      "  <inputStrings>: The first command line argument, which is not a switch and\n"
      "all further arguments are considered input strings, which are matched against\n"
      "the regular expression, that has been specified with option -re.\n"
      "  Options are:\n"
      "  -help: Boolean, print this text.\n"
      "  -h: Same as -help.\n"
      "  -re: Define regular expression. Next argument is the regular expression. This\n"
      "option is mandatory unless help is requested.\n"
      "  -file: The successfully compiled regular expression is exported as a C source\n"
      "code snippet, which enables integration of compiled expressions into an\n"
      "embedded software program. Next argument is the file path and name.\n"
      "  Note, the compilation of the exported code snippet requires the preceding\n"
      "inclusion of header file \"re_regExpMatcher.h\".\n"
      "  -append: Boolean and useful only in combination with -file. If given, then the\n"
      "C source code snippet is appended to the denoted file. This allows collecting many\n"
      "compiled regular expressions in one and the same file by repeated runs of the\n"
      "application.\n"
      "  -name: Next argument is the name of the regular expression in the exported C\n"
      "source code snippet. Using different names allows collecting many compiled regular\n"
      "expressions in one and the same file by repeated runs of the application.\n"
      "  -namespc: Next argument is the namespace used for the global, regular expression\n"
      "related elements in the exported C source code snippet. The passed string will\n"
      "precede the name of all of these elements. Optional, default is the empty string.\n";

    puts(usageMsg);

} /* usage */


/**
 * There are different intended use cases. One of it is using the compiler solely on the
 * development machine to generate compiled regular expressions, which are then used for
 * matching on an embedded target machine (which should not be loaded with compilation
 * memory and computation). For this use case, a C main function can be compiled, which
 * takes the regular expression on the command line for compilation and which allows to
 * export the compiled expression in a format, which is easy to integrated on the embedded
 * target. Moreover, the command line allows matching, too, in order to check the regular
 * expression for correctness (and before exporting it).
 *   @return
 * The function returns zero if everything succeeds and -1 otherwise.
 *   @param noArgs
 * The number of provided command line arguments.
 *   @param pArgStr
 * An array of argument pointers. Each entry is one command line argument as pointer to a
 * character (string).
 */
int main(int noArgs, const char * const * pArgStr)
{
    /* Step 1 of 4: Command line evaluation. */
    assert(noArgs > 0);
    signed int idxArg = 1
             , idxArg1stInputString = noArgs;
    const char * const * pAStr = pArgStr;
    const char *regExpStr = NULL
             , *regExpName = NULL
             , *regExpNamespc = NULL
             , *codeFileName = NULL;
    bool appendToCodeFile = false
       , help = false;
    while(idxArg < noArgs)
    {
        const char *arg = * ++pAStr;
        if(idxArg < noArgs  &&  (strcmp(arg, "-h") == 0  ||  strcmp(arg, "-help") == 0))
        {
            help = true;
            idxArg += 1u;
        }
        else if(idxArg+1 < noArgs  &&  strcmp(arg, "-re") == 0)
        {
            regExpStr = * ++pAStr;
            idxArg += 2u;
        }
        else if(idxArg+1 < noArgs  &&  strcmp(arg, "-file") == 0)
        {
            codeFileName = * ++pAStr;
            idxArg += 2u;
        }
        else if(idxArg+1 < noArgs  &&  strcmp(arg, "-name") == 0)
        {
            regExpName = * ++pAStr;
            idxArg += 2u;
        }
        else if(idxArg+1 < noArgs  &&  strcmp(arg, "-namespc") == 0)
        {
            regExpNamespc = * ++pAStr;
            idxArg += 2u;
        }
        else if(idxArg < noArgs  &&  strcmp(arg, "-append") == 0)
        {
            appendToCodeFile = true;
            idxArg += 1u;
        }
        else if(arg[0] != '-')
        {
            idxArg1stInputString = idxArg;
            break;
        }
        else
        {
            help = true;
            break;
        }
    }

    /* The regular expression is a mandatory argument. */
    if(regExpStr == NULL)
    {
        printf("No regular expression is given on the command line.\n");
        help = true;
    }
    
    /* File name and regular expression name are both optional but not independently from
       one another. */
    if((codeFileName == NULL) != (regExpName == NULL))
    {
        printf("If a file name is specified for export of the compiled regular expression\n"
               "then the name of the regular expression needs to be specified, too, and\n"
               "vice versa.\n"
              );
        help = true;
    }

    if(help)
    {
        usage();
        return -1;
    }

    /* Step 2 of 4: Compilation of regular expression. */
    printf("main: Try to compile regexp %s\n", regExpStr);
    uint8_t iStream[MAX_LEN_ISTREAM];
    for(unsigned idxI=0u; idxI<sizeof(iStream)/sizeof(iStream[0]); ++idxI)
        iStream[idxI] = I_ILLEGAL;
    uint16_t idxICharSetAry[RE_MAX_NO_CHAR_SETS_IN_REGEXP];
    uint8_t charSetMem[RE_MAX_NO_DIFF_CHAR_SETS_IN_REGEXP * sizeof(re_charSet_t)];
    struct re_compiler_t compiler =
    {
        .re =
        {
            .iStream = &iStream[0],
            .lenIStream = 0u,
            .noCharSets = 0u,
        },
        .maxLenIStream = sizeof(iStream)/sizeof(*iStream),

        .cStream = NULL,
        .pC = NULL,

        .nextIdxLoop = 0u,
        .recursionDepth = 0u,

        .idxICharSetAry = idxICharSetAry,
        .noICharSet = 0u,
        .maxNoICharSet = sizeof(idxICharSetAry)/sizeof(idxICharSetAry[0]),

        .charSetMem = charSetMem,
        .maxNoCharSets = sizeof(charSetMem)/sizeof(re_charSet_t),

        .maxRecursionDepth = 0u,
        .maxAllowedRecursionDepth = 0u,
        .err = re_errComp_success,
    };
    re_compile(&compiler, regExpStr, /*matchAnywhere*/ true, /*maxAllowedRecursionDepth*/ 10u);
    assert(compiler.recursionDepth == 0u);
    assert(compiler.err != re_errComp_success  ||  *compiler.pC == '\0');
    printf( "main: Compilation %s. Error: %u\n"
            "  Recursions needed: %u\n"
          , compiler.err == re_errComp_success? "succeeded": "failed"
          , compiler.err
          , compiler.maxRecursionDepth
          );

    /* Step 3 of 4: Export of compiled regular expression. (As listing to the console and
       optionally as C source code to a user chosen file. */
    int err = 0;
    if(compiler.err == re_errComp_success)
    {
        printf( "main: Compiled expression:\n");
        printCompiledIStream(stdout, &compiler.re, /*asCCode*/ false);

        if(codeFileName != NULL  &&  regExpName != NULL)
        {
            const char * const namespc = regExpNamespc != NULL? regExpNamespc: "";
            FILE *file = fopen(codeFileName, appendToCodeFile? "a": "w");
            if(file != NULL)
            {
                exportCompiledExpression(file, &compiler, namespc, regExpName);
                fclose(file);
                printf( "The compiled regular expression has been exported to file %s\n"
                      , codeFileName
                      );
            }
            else
            {
                err = -3;
                printf( "Can't export the compiled regular expression. Failed to open"
                        " file %s\n"
                      , codeFileName
                      );
            } /* if(File could be successfully opened?) */
        } /* if(Export of compiled expression demanded on command line?) */
    }
    else
        err = -2;

    /* Step 4 of 4: Use of compiled regular expression for testing; all further input
       arguments are matched against the expression. */
    if(err == 0  &&  idxArg1stInputString < noArgs)
    {
        pAStr = pArgStr + idxArg1stInputString;
        struct re_matcherStackElement_t matcherPathElementAry[50];
        struct re_matcherCGrpStackElement_t matcherCGrpStack[20];

        /* The user needs to pre-configure the matcher object with respect to the memory
           configuration. The other fields don't care. This is a static descision; we need
           to do this once for all later uses of the matcher object. */
        struct re_matcher_t matcher =
        {
            /* The needed size of the memory for path alternatives depends on both, the
               regular expression and the input stream to match against it. It is hard to
               predict and the value, we see here is arbitrarily chosen. On an embedded
               target, this can become a critical optimization. */
            .matcherPathStack = matcherPathElementAry,
            .maxNoPathElements = sizeof(matcherPathElementAry)
                                 / sizeof(*matcherPathElementAry),

            /* The needed size of the memory for capture groups is most often predictable
               for a given regular expression. For most use-cases (if not used inside the
               body of unbounded loops), it barely depends on the input stream. The memory
               should suffice for the number of groups used in the regular expression. */
            .cGrpStack = matcherCGrpStack,
            .maxNoCapturedGrps = sizeof(matcherCGrpStack)/sizeof(matcherCGrpStack[0]),
        };

        /* All remaining command line arguments are considered strings to be matched
           against the regular expression. */
        for(idxArg=idxArg1stInputString; idxArg<noArgs; ++idxArg)
        {
            const char * const arg = * pAStr++;
            const bool patternMatches = re_matchCString(&matcher, &compiler.re, arg);
            assert(patternMatches == (matcher.err == re_errMatch_success));
            printf( "Matching %s against %s %s (error %u)\n"
#if RE_MATCHER_COMPILE_STATISTICS != 0
                    "  Instructions needed: %u\n"
                    "  Path stack elements needed: %u\n"
#endif
                  , arg
                  , regExpStr
                  , patternMatches? "succeeded": "failed"
                  , (unsigned)matcher.err
#if RE_MATCHER_COMPILE_STATISTICS != 0
                  , matcher.noInstructions
                  , matcher.maxUsePathElements
#endif
                  );

            if(matcher.err == re_errMatch_success)
            {
                printf("Unconsumed input: '%s'\n", matcher.pC);

                /* Print all captured groups. */
                if(matcher.noCapturedGrps > 0)
                {
                    printf("%u captured groups:\n", matcher.noCapturedGrps);
                    for(unsigned int idxG=0u; idxG<compiler.re.noCaptureGrps; ++idxG)
                    {
                        const unsigned int noMatches = re_getNoMatchesCaptureGrp( &matcher
                                                                                , idxG
                                                                                );
                        #define MAX_SHOWN_MATCH_CHARS   20
                        char buf[MAX_SHOWN_MATCH_CHARS+1];
                        for(unsigned int idxM=0u; idxM<noMatches; ++idxM)
                        {
                            unsigned int idx1stChar, idxEnd;
                            bool gotMatch = re_getMatchOfCaptureGrp( &matcher
                                                                   , &idx1stChar
                                                                   , &idxEnd
                                                                   , idxG
                                                                   , idxM
                                                                   );
                            assert(gotMatch);
                            gotMatch = re_copyMatchOfCaptureGrp( &matcher
                                                               , buf
                                                               , idxG
                                                               , idxM
                                                               , sizeof(buf)
                                                               );
                            assert(gotMatch);
                            printf( "  Group %u, match %u, from %u to %u: '%s'\n"
                                  , idxG + 1u
                                  , idxM + 1u
                                  , idx1stChar
                                  , idxEnd
                                  , buf
                                  );
                        } /* For(All matches of the given group) */
                        #undef MAX_SHOWN_MATCH_CHARS

                    } /* for(All capture groups in the regular expression) */
                }
             }
             else
                err = -4;
        }
    } /* if(User wants to match her/his regexp against at least one input argument.) */

    return err;

} /* main */
#endif
