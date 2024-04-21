/**
 * @file re_regExpMatcher.c
 * Implementation of a simple regular expression matcher. The matcher operates on
 * expressions, which have been compiled before using the compiler in file
 * re_regExpCompiler.c.
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
 *   re_match
 *   re_matchCString
 *   re_getNoMatchesCaptureGrp
 *   re_getMatchOfCaptureGrp
 *   re_copyMatchOfCaptureGrp
 * Local functions
 *   iFetchLoop
 *   iFetchLoopEnd
 *   iFetchOr
 *   iFetchJmp
 *   iFetchCap
 *   iFetchCapEnd
 *   iFetchLit
 *   immediateMatch
 *   pruneAlternative
 *   pushAlternative
 *   popAlternative
 *   pushLoop
 *   getCurrentLoopState
 *   pushCGrpStart
 *   storeCGrpEnd
 *   matchLoop
 *   matchLoopEnd
 */

/// @todo Possible improvements:\n
//   At compilation time, it should be easy to maintain a lower bounds for the number of
// still required input characters. If no unbounded loops occur, even an upper bounds is
// possible. At matching time, the number of still unconsumed characters is known, so some
// pruning of the alternatives becomes possible. Could significantly reduce the number of
// alternatives, which are typically stored for the common pattern ".*".\n
//   At compilation time, calculating the bounds for the entire expression and path
// alternatives (legs of the OR and the body of a loop) can be solved with a graph
// representation of the expression, where the transitions are constrained with the min
// and max of loop cycles. Backtracking will find the shortest paths. However, at runtime,
// the still remaining values are harder to keep up-to-date. It is not static information,
// which could just be attached to the instruction stream. It depends much on the already
// taken number of cycles in the potentially nested loops. Is it possible to attach static
// information, which is used as a delta on each actually taken branch decision? E.g. If
// we decide to either leave or continue a loop then the delta would be the (static) value
// for the body of that loop. If we match a literal then the delta is 1, etc.\n
//   At many points a statement should be possible about the set of characters, which is
// possible for the next input character. With a one-character look-ahead some pruning of
// alternatives became possible. Example: RE=".*(x|y)+". Our naive recursion, just looking
// at the ".*" in the first step, will consider all substrings of the input as an
// alternative, which start with the first input character. With one-character look-ahead,
// only the few out of these would remain as alternatives, which end with either x or y.\n
//   Same idea, a bit extended: For each statement, a list of characters is maintained,
// which is surely required in the rest of the input. It is a rather cheap operation to
// relate this information to the last input character, which can be safely consumed by
// the statement. Example: RE=".*a.*b.*c" The input would be scanned from its back for the
// first occurances of c, b, a and the initial ".*" could be bounded to the character in
// front of the found a.
//   Pruning of alternative paths would be supported by another definition of the loop
// instructions. Loops with at least 1 cycle, ()+ or (){1,...}, don't require an opening
// instruction. If the body begins with a literal character then the single instruction
// look-ahead would optimize such loops, too.

/*
 * Include files
 */

#include "re_regExpMatcher.h"

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <assert.h>

#include "re_charSet.h"

/*
 * Defines
 */

/** As development support, a printf-like function may be used to log progress of matching
    with respect to the use of alternative paths, mainly pushing still untried alternatives
    onto the stack and later popping them, when needed, because all others did fail
    before.\n
      Either define a logging function with printf signature or define to nothing. */
#define TRACE_ALT(...)  //printf(__VA_ARGS__)

/** As development support, a printf-like function may be used to log progress of matching
    capture groups, mainly pushing started groups onto the stack and later popping them,
    when being discarded because of a chosen alternative matching path.\n
      Either define a logging function with printf signature or define to nothing. */
#define TRACE_CAP(...)  //printf(__VA_ARGS__)


/** Common expression: Check of matcher's main status variable to see if we can still
    continue. */
#define MATCHER_OK  (pMatcher->err == re_errMatch_success)

/*
 * Local type definitions
 */

/** Type of an instruction stream. Effectively a Byte array. */
typedef const uint8_t *iStream_t;

/** This struct represents the information, which is encoded in a loop instruction. */
struct iLoop_t
{
    /** Is the loop greedy? */
    bool isGreedy;
    
    /** The number of instruction bytes of the repeatedly matched loop body. */
    unsigned int lenIBody;
    
    /** The minimum required matches of the loop body. */
    unsigned int min;
    
    /** The maximum allowed matches of the loop body. */
    unsigned int max;
    
    /** The ID of the loop among all loops in the regular expression. */
    unsigned int idxLoop;
};

/** This struct represents the information, which is encoded in a loop termination
    instruction. */
struct iLoopEnd_t
{
    /** This field represents the information, which is encoded in the loop instruction
        at the beginning of the loop. */
    struct iLoop_t iLoop;
    
    /** Pointer to the first instruction of the repeatedly matching loop body. */
    iStream_t pIBody;
};

/** This struct represents the information, which is encoded in an OR instruction. */
struct iOr_t
{
    /** The primary alternative of the OR decision begins after this instruction and has
        this number of instruction bytes. */
    unsigned int lenAlternative;
};

/** This struct represents the information, which is encoded in a jump instruction. */
struct iJmp_t
{
    /** The jump distance in Byte, counting from behind the jump instruction.\n
          Note, the distance is unsigned as jumps are only used inside OR expressions and
        reaching till the end of the expression. */
    unsigned int dist;
};

/** This struct represents the information, which is encoded in a capture group start
    instruction. */ 
struct iCap_t
{
    /** The ID of the beginning capture group, which is implemented as zero based index
        among all capture groups. */
    unsigned int idxCGrp;
};

/** This struct represents the information, which is encoded in a capture group termination
    instruction. */ 
struct iCapEnd_t
{
    /** The ID of the ending capture group, which is implemented as zero based index among
        all capture groups. */
    unsigned int idxCGrp;
};

_Static_assert(sizeof(struct re_matcherPathElement_t)==6, "Unexpected size");
_Static_assert( offsetof(struct re_matcherPathElement_t, idxI)
                == offsetof(struct re_matcherPathElement_t, idxI_s)
                &&  offsetof(struct re_matcherPathElement_t, idxC)
                    == offsetof(struct re_matcherPathElement_t, idxC_s)
                &&  offsetof(struct re_matcherPathElement_t, noCapturedGrps)
                    == offsetof(struct re_matcherPathElement_t, noCapturedGrps_s)
              , "Binary buildup of struct not suited to do a safe type conversion"
              );

/*
 * Local prototypes
 */

/*
 * Data definitions
 */

/*
 * Function implementation
 */

#if RE_REQUIRE_MATCHER == 1
/**
 * Instruction fetch if the instruction pointer points at a loop instruction. Otherwise the
 * function has no effect.
 *   @return
 * Get \a true if the current instruction is the beginning of a loop.
 *   @param pILoop
 * The representation of the loop instruction is returned by reference if the function
 * returns \a true.
 *   @param pIStream
 * The current instruction pointer by reference. If the function returns \a true
 * then the instruction pointer has been advanced until behind the loop instruction.
 * Otherwise it has not been moved.
 */
static bool iFetchLoop(struct iLoop_t * const pILoop, iStream_t * const pIStream)
{
    const uint8_t *pI = *pIStream;
    bool success = false;

    if(*pI == OP_LOOP  ||  *pI == OP_LOOPNG)
    {
        pILoop->isGreedy = * pI++ == OP_LOOP;
        pILoop->lenIBody = * pI++;
        pILoop->lenIBody = (pILoop->lenIBody<<8) + (* pI++);
        pILoop->min = * pI++;
        pILoop->max = * pI++;
        pILoop->idxLoop = * pI++;

        /* Minimum needs to be less or equal than maximum and it can't be infinite. Maximum
           is greater or equal to one. */
        assert(pILoop->min <= pILoop->max  &&  pILoop->min != 0xFFu  &&  pILoop->max > 0x0u);

        /* A loop of length zero is not allowed. */
        assert(pILoop->lenIBody > 0u);

        *pIStream = pI;
        success = true;
    }

    return success;

} /* iFetchLoop */


/**
 * Instruction fetch if the instruction pointer points at a loop termination instruction.
 * Otherwise the function has no effect.
 *   @return
 * Get \a true if the current instruction is the end of a loop.
 *   @param pILoopEnd
 * The representation of the loop termination instruction is returned by reference if the
 * function returns \a true.
 *   @param pIStream
 * The current instruction pointer by reference. If the function returns \a true
 * then the instruction pointer has been advanced until behind the loop termination
 * instruction. Otherwise it has not been moved.
 */
static bool iFetchLoopEnd(struct iLoopEnd_t * const pILoopEnd, iStream_t * const pIStream)
{
    const uint8_t *pI = *pIStream;
    bool success = false;

    if(*pI == OP_LOOPEND)
    {
        unsigned int lenIBody = * ++pI;
        lenIBody = (lenIBody<<8) + (* ++pI);

        /* First, we go back to the loop instruction. Fetching it will then adjust the
           pointer pILoopEnd->pIBody as expected to the beginning of the loop body. */
        pILoopEnd->pIBody = ++pI - lenIBody - LEN_I_LOOPEND - LEN_I_LOOP;
#ifndef DEBUG
        __attribute__((unused))
#endif
        const bool isLoop = iFetchLoop(&pILoopEnd->iLoop, &pILoopEnd->pIBody);
        assert(isLoop);

        *pIStream = pI;
        success = true;
    }

    return success;

} /* iFetchLoopEnd */


/**
 * Instruction fetch if the instruction pointer points at an OR instruction. Otherwise the
 * function has no effect.
 *   @return
 * Get \a true if the current instruction is the beginning of an OR alternative.
 *   @param pIOr
 * The representation of the OR instruction is returned by reference if the function
 * returns \a true.
 *   @param pIStream
 * The current instruction pointer by reference. If the function returns \a true then the
 * instruction pointer has been advanced until behind the OR instruction. Otherwise it has
 * not been moved.
 */
static bool iFetchOr(struct iOr_t * const pIOr, iStream_t * const pIStream)
{
    const uint8_t *pI = *pIStream;
    bool success = false;

    if(*pI == OP_OR)
    {
        ++ pI;
        pIOr->lenAlternative = * pI++;
        pIOr->lenAlternative = (pIOr->lenAlternative<<8) + (* pI++);

        /* An alternative of length zero is not allowed. */
        assert(pIOr->lenAlternative > 0u);

        *pIStream = pI;
        success = true;
    }

    return success;

} /* iFetchOr */


/**
 * Instruction fetch if the instruction pointer points at a jump instruction. Otherwise the
 * function has no effect.
 *   @return
 * Get \a true if the current instruction is a jump instruction.
 *   @param pIJmp
 * The representation of the jump instruction is returned by reference if the function
 * returns \a true.
 *   @param pIStream
 * The current instruction pointer by reference. If the function returns \a true
 * then the instruction pointer has been advanced until behind the jump instruction.
 * Otherwise it has not been moved.
 */
static bool iFetchJmp(struct iJmp_t * const pIJmp, iStream_t * const pIStream)
{
    const uint8_t *pI = *pIStream;
    bool success = false;

    if(*pI == OP_JMP)
    {
        ++ pI;
        pIJmp->dist = * pI++;
        pIJmp->dist = (pIJmp->dist<<8) + (* pI++);

        /* An alternative of length zero is not allowed. */
        assert(pIJmp->dist > 0u);

        *pIStream = pI;
        success = true;
    }

    return success;

} /* iFetchJmp */


/**
 * Instruction fetch if the instruction pointer points at a beginning-of-capture-group
 * instruction. Otherwise the function has no effect.
 *   @return
 * Get \a true if the current instruction is the beginning of a capture group.
 *   @param pICap
 * The representation of the beginning-of-capture-group instruction is returned by
 * reference if the function returns \a true.
 *   @param pIStream
 * The current instruction pointer by reference. If the function returns \a true then the
 * instruction pointer has been advanced until behind the beginning-of-capture-group
 * instruction. Otherwise it has not been moved.
 */
static bool iFetchCap(struct iCap_t * const pICap, iStream_t * const pIStream)
{
    const uint8_t *pI = *pIStream;
    bool success = false;

    if(*pI == OP_CAP)
    {
        ++ pI;
        pICap->idxCGrp = * pI++;

        *pIStream = pI;
        success = true;
    }

    return success;

} /* iFetchCap */


/**
 * Instruction fetch if the instruction pointer points at a end-of-capture-group
 * instruction. Otherwise the function has no effect.
 *   @return
 * Get \a true if the current instruction is the end of a capture group.
 *   @param pICapEnd
 * The representation of the end-of-capture-group instruction is returned by reference if
 * the function returns \a true.
 *   @param pIStream
 * The current instruction pointer by reference. If the function returns \a true then the
 * instruction pointer has been advanced until behind the end-of-capture-group instruction.
 * Otherwise it has not been moved.
 */
static bool iFetchCapEnd(struct iCapEnd_t * const pICapEnd, iStream_t * const pIStream)
{
    const uint8_t *pI = *pIStream;
    bool success = false;

    if(*pI == OP_CAPEND)
    {
        ++ pI;
        pICapEnd->idxCGrp = * pI++;

        *pIStream = pI;
        success = true;
    }

    return success;

} /* iFetchCapEnd */


/**
 * Instruction fetch if the instruction pointer points at a literal character match
 * instruction. Otherwise the function has no effect.
 *   @return
 * Get \a true if the current instruction is a literal character match instruction.
 *   @param pCLit
 * The character to match is returned by reference if the function returns \a true.
 *   @param pIStream
 * The current instruction pointer by reference. If the function returns \a true then the
 * instruction pointer has been advanced until behind the match literal instruction.
 * Otherwise it has not been moved.
 */
static bool iFetchLit(char * const pCLit, iStream_t * const pIStream)
{
    bool success = false;
    const uint8_t i = **pIStream;
    if((i & ~0x7F) == 0)
    {
        *pCLit = (char)i;
        ++ *pIStream;
        success = true;
    }
    else if(i == OP_ESC)
    {
        ++ *pIStream;
        *pCLit = (char)**pIStream;
        ++ *pIStream;
        success = true;
    }

    return success;

} /* iFetchLit */


/**
 * Check the instruction pointer for an immediate match instruction and if so, execute it,
 * i.e., try the match with the current input character.\n
 *   An immediate match is anything, which can be decided immediately by checking the
 * current input character, e.g., a literal match or a character set match, among more.
 *   @return
 * The function returns \a true if the current instruction is an immediate match and if there
 * is a match with the current input character.
 *   @param pShouldMatch
 * The function returns by reference whether the current instruction is an immediate match.
 * If * \a pShouldMatch is \a false on exit then the matcher needs to consider an other
 * instruction.
 *   @param[in,out] ppI
 * The current instruction pointer by reference. It is not moved if it doesn't point to an
 * immediate match instruction on entry. Otherwise it has been advanced behind the found
 * and executed instruction.
 */
static bool immediateMatch(bool * const pShouldMatch, iStream_t * const ppI, char c)
{
    bool shouldMatch, isMatching;

    char literalChar;
    if(iFetchLit(&literalChar, ppI))
    {
        shouldMatch = true;
        isMatching = c == literalChar;
    }
    else if(**ppI == OP_CHARSET)
    {
        shouldMatch = true;

        /* 3: Length of instruction. The distance to the chararcter set counts from
           behind the instruction. */
        const uint8_t *cs = (*ppI)++ + 3;
        cs += (* (*ppI)++) << 8u;
        cs += (* (*ppI)++);
        isMatching = re_isCharInCharSet(cs, c);
    }
    else
    {
        shouldMatch = true;
        switch(**ppI)
        {
        case I_ANY:
            /* Here, we take the decision, whether '.' matches newlines. */
            isMatching = c != '\n';
            break;

        case I_DIGIT:
            isMatching = isdigit((int)c);
            break;

        case I_HEXDIGIT:
            isMatching = isdigit((int)c)
                         ||  (toupper((int)c) >= 'A'  &&  toupper((int)c) <= 'F');
            break;

        case I_SPC:
            isMatching = c == ' '  ||  c == '\t'  ||  c == '\f'  ||  c == '\r';
            break;

        case I_AZ:
            isMatching = c >= 'a'  &&  c <= 'z';
            break;

        case I_LTR:
            isMatching = isalpha((int)c);
            break;

        case I_ID1ST:
            isMatching = isalpha((int)c) || c == '_';
            break;

        case I_ID:
            isMatching = isalpha((int)c) || isdigit((int)c) || c == '_';
            break;

        case I_CRLF:
            isMatching = c == '\r'  ||  c == '\n';
            break;

        default:
            shouldMatch = false;
            isMatching = false;

        } /* End of switch(Which instruction?) */

        if(shouldMatch)
            ++ *ppI;

    } /* End of if/else(Which instruction?) */

    *pShouldMatch = shouldMatch;
    return isMatching;

} /* immediateMatch */


/**
 * Helper function for pushAlternative(): An alternative path is checked for obvious
 * unsuitability. Some easy criteria are tested to see if it is already now evident that
 * the alternative won't match the input stream.
 *   @return
 * Get \a true if the alternative path will surely not match the input stream. If \a false is
 * returned then is undecided, the path may or may not match.
 *   @param pMatcher
 * The matcher object by reference.
 *   @param pI
 * The first instruction of the alternative path to be checked. It is checked against the
 * current input stream, which is element of the matcher object.
 */
static bool pruneAlternative( struct re_matcher_t *pMatcher
                            , const uint8_t *pI
                            )
{
    const uint8_t * const pEndI = pMatcher->pRe->iStream + pMatcher->pRe->lenIStream;

    /* We may advance pI over I_CAP, I_CAPEND.
         2: Length of both the skipped instructions. */
    while(pI < pEndI  &&  (*pI == OP_CAP  ||  *pI == OP_CAPEND))
        pI += 2u;

    bool doPrune = false;
    if(pI < pEndI)
    {
        bool shouldMatch;
        const bool wouldMatch = immediateMatch(&shouldMatch, &pI, *pMatcher->pC);
        if(shouldMatch)
            doPrune = !wouldMatch;
        else if(*pI == I_CARET)
            doPrune = pMatcher->pC != pMatcher->cStream;
        else if(*pI == I_DOLLAR)
            doPrune = pMatcher->pC != pMatcher->cStream + pMatcher->lenCStream;
    }

    return doPrune;

} /* pruneAlternative */


/**
 * Store an alternative path on the stack of those. An alternative path is a still possible
 * way to match other then the currently tried one and with lower priority, e.g., the
 * second or third alternative in an OR expression, while we are currently trying the first
 * one. These alternative are stored in a stack and they are taken from the stack as next
 * option if the current match path fails.
 *   @param pMatcher
 * The matcher object by reference.
 *   @param pI
 * The first instruction of the alternative path to be stored. It would be checked against
 * the current read-position of the input stream, which is element of the matcher object.
 */ 
static void pushAlternative(struct re_matcher_t *pMatcher, const uint8_t * const pI)
{
    /* A common kind of alternatives results from skipping some arbitray characters till a
       specific character of interest, e.g. ".+xyz". A one character look-ahead can sort
       such an alternative out if the specific character doesn't follow up. */
    if(pruneAlternative(pMatcher, pI))
    {
        TRACE_ALT( "    Prune alternative at instruction byte %i\n"
                 , (int)(pI - pMatcher->pRe->iStream)
                 );
        return;
    }

    signed int idxI = pI - pMatcher->pRe->iStream;
    /* The maximum size of all our doing is 16 Bit. This has been checked already at
       compilation time and so we can have an assertion here. */
    assert(idxI >= 0  &&  (unsigned)idxI <= pMatcher->pRe->lenIStream);

    signed int idxC = pMatcher->pC - pMatcher->cStream;
    /* The maximum string to match against the regular expression has a size of 64k. */
    assert(idxC >= 0);
    if(idxC > UINT16_MAX)
    {
        idxC = UINT16_MAX;
        pMatcher->err = re_errMatch_inputStringTooLong;
    }

    /* A single byte is used to encode the index of a capture group. Greater indexes
       can't occur in a compiled regular expression. */
    assert(pMatcher->noCapturedGrps <= UINT8_MAX);

    /* A path alternative consists of instruction pointer, input stream pointer and stack
       pointer of open cature groups, all implemented as integers. We use stack compression
       to optimize stack usage for typical loops like .*, where all of the values increment
       by the same delta in each iteration. In the first iteration, the three absolute
       values are stored on the stack, together with an aditional repetition counter r=0.
         In the next iteration, the three values are stored in a new stack element as delta
       to the previous one and together with r=1. The next iteration would not push a new
       stack element but just increment r in the top element.
         r=0 means for a statck element, its other three values are meant absolute.
         r>0 means the other three values are deltas with respect to the preceding stack
       element.
         Push: An new, absolute element is pushed if the stack is empty or if it is not
       possible as delta. The information is stored as delta if r(n-1)=0 or if r(n-1)>0 AND
       all current deltas are identical to those of n-1 AND r(n-1)<UINT8_MAX (the
       implementation maximum of r). In the last case just increment r(n-1).
         Pop: Return and pop if head element is absolute. If relative, fetch the absolute
       values from element n-1 and add r(n) times the deltas of head element n. Decrement r
       and pop it if r becomes zero. */

    /* The compacted stack storage allows three decisions. If the top element is a normal,
       absolute element, then we push a new, relative one. If the top-level is a relative
       one, then we try to reuse it by simply incrementing the ref counter. Otherwise we
       push a new absolute element. */
    bool pushNewAbsElem = false;
    bool pushNewRelElem = false;
    struct re_matcherStackElement_t *pTopUnion;
    struct re_matcherPathElement_t *pTopElem;
    if(pMatcher->noPathElements > 0u)
    {
        pTopUnion = &pMatcher->matcherPathStack[pMatcher->noPathElements-1u];
        if(pTopUnion->isPathElem)
        {
            pTopElem = &pTopUnion->pathAlternative;

            /* We have a path alternative, not a counter state object. Check if absolute or
               relative. */
            if(pTopElem->cntRelative == 0u)
            {
                /* It is an absolute path element and we have to push a new element, which
                   is relative to the found top element. */
                pushNewRelElem = true;
            }
            else
            {
                /* The top element is relative. We need to check if we can reuse it. If
                   not, we need to push a new absolute element. */
                assert(pMatcher->noPathElements >= 2u  && (pTopUnion-1)->isPathElem);
                const struct re_matcherPathElement_t * const pAnchorElem =
                                                            &(pTopUnion-1)->pathAlternative;
                assert(pAnchorElem->cntRelative == 0u);

                const signed int f = (int)(pTopElem->cntRelative + 1u);
                if(pAnchorElem->idxI + f*pTopElem->idxI_s == idxI
                   &&  pAnchorElem->idxC + f*pTopElem->idxC_s == idxC
                   &&  pAnchorElem->noCapturedGrps + f*pTopElem->noCapturedGrps_s
                       == (int)pMatcher->noCapturedGrps
                   &&  pTopElem->cntRelative < UINT8_MAX
                  )
                {
                    /* All distances from n-2 to n-1 are same from n-1 to n: We can reuse
                       the delta element by simply incrementing the ref counter. And we are
                       done. */
                    ++ pTopElem->cntRelative;
                    TRACE_ALT( "    Reuse %u of relative stack element: %i, %i\n"
                             , pTopElem->cntRelative
                             , pTopElem->idxI_s
                             , pTopElem->idxC_s
                             );
                }
                else
                    pushNewAbsElem = true;

            } /* if(Top element is absolute or relative?) */
        }
        else
        {
            /* The top doesn't contain a path element, so we need to start over with a new
               absolute element. */
            pushNewAbsElem = true;

        } /* if(Is top element a path element?) */

        /* In case we need to push a new one: Is there still enough stack space left? */
        if((pushNewAbsElem || pushNewRelElem)
           && pMatcher->noPathElements >= pMatcher->maxNoPathElements
          )
        {
            pushNewAbsElem =
            pushNewRelElem = false;
            if(MATCHER_OK)
                pMatcher->err = re_errMatch_stateBufferOverflow;
        }
    }
    else
    {
        /* The stack is still empty, so we need to begin with an absolute element. Stack
           check not needed in this case. */
        pushNewAbsElem = true;
        pTopUnion = &pMatcher->matcherPathStack[-1];
    }

    if(pushNewAbsElem)
    {
        ++ pTopUnion;
        ++ pMatcher->noPathElements;
#if RE_MATCHER_COMPILE_STATISTICS != 0
        if(pMatcher->noPathElements > pMatcher->maxUsePathElements)
            ++ pMatcher->maxUsePathElements;
#endif
        struct re_matcherPathElement_t * const pNewPathElem = &pTopUnion->pathAlternative;

        pTopUnion->isPathElem = true;
        pNewPathElem->idxI = idxI;
        pNewPathElem->idxC = idxC;
        pNewPathElem->noCapturedGrps = pMatcher->noCapturedGrps;
        pNewPathElem->cntRelative = 0u;

    }
    else if(pushNewRelElem)
    {
        assert(!pushNewAbsElem);
        ++ pMatcher->noPathElements;
#if RE_MATCHER_COMPILE_STATISTICS != 0
        if(pMatcher->noPathElements > pMatcher->maxUsePathElements)
            ++ pMatcher->maxUsePathElements;
#endif
        struct re_matcherStackElement_t * const pNewTopUnion = pTopUnion + 1;
        struct re_matcherPathElement_t * const pNewPathElem = &pNewTopUnion->pathAlternative;

        /* Note, the distances are stored as unsigned although they are actually signed. We
           silently use the uint variables as union of signed and unsigned integers. */
        pNewTopUnion->isPathElem = true;
        pNewPathElem->idxI = idxI - pTopElem->idxI;
        pNewPathElem->idxC = idxC - pTopElem->idxC;
        pNewPathElem->noCapturedGrps = pMatcher->noCapturedGrps - pTopElem->noCapturedGrps;
        pNewPathElem->cntRelative = 1u;
        TRACE_ALT( "    Push new relative stack element: %u+(%i), %u+(%i)\n"
                 , pTopElem->idxI
                 , pNewPathElem->idxI_s
                 , pTopElem->idxC
                 , pNewPathElem->idxC_s
                 );
    }

#if RE_MATCHER_COMPILE_STATISTICS != 0
    assert(pMatcher->noPathElements <= pMatcher->maxUsePathElements);
#endif
} /* pushAlternative */


/**
 * Counterpart of pushAlternative(): Fetch the last recently pushed, valid alternative path
 * from the stack of those. Note, not all alternatives, which were pushed will be fetched
 * again. If an alternative is proven to fail then pushAlternative() won't store but drop
 * it.
 *   @param pMatcher
 * The matcher object by reference. The operation is mostly done inside this obejct. It
 * contains the stack of alternatives and it contains the state, which is updated according
 * to the popped alternative. On exit, the matcher will naturally continue matching
 * according to the new, popped path alternative.
 *   @param ppI
 * The instruction pointer is not element of the matcher object. It is updated by reference
 * according to the popped alternative.
 */
static bool popAlternative(struct re_matcher_t * const pMatcher, const uint8_t ** const ppI)
{
    assert(MATCHER_OK);
    while(pMatcher->noPathElements > 0u)
    {
        struct re_matcherStackElement_t * const pStackElem =
                                    &pMatcher->matcherPathStack[pMatcher->noPathElements-1u];
        if(pStackElem->isPathElem)
        {
            /* We use stack compression to optimize stack usage for typical loops like .*.
               See pushAlternative for details. */
       
            struct re_matcherPathElement_t * const pAlt = &pStackElem->pathAlternative;
            if(pAlt->cntRelative == 0u)
            {
                /* This is an absolute path element. The contained values are as is. */
                *ppI = pMatcher->pRe->iStream + pAlt->idxI;
                pMatcher->pC = pMatcher->cStream + pAlt->idxC;
                pMatcher->noCapturedGrps = (unsigned)pAlt->noCapturedGrps;

                /* The element is no longer required and taken from the stack. */
                -- pMatcher->noPathElements;
            }
            else
            {
                /* We have a relative element. The contained values are relative to the
                   stack element one level deeper. */
                assert(pMatcher->noPathElements > 0u  &&  (pStackElem-1)->isPathElem);
                const struct re_matcherPathElement_t * const pAnchorElem =
                                                            &(pStackElem-1)->pathAlternative;
                const signed int f = (int)pAlt->cntRelative;
                *ppI = pMatcher->pRe->iStream + (pAnchorElem->idxI + f*pAlt->idxI_s);
                pMatcher->pC = pMatcher->cStream + (pAnchorElem->idxC + f*pAlt->idxC_s);
                pMatcher->noCapturedGrps = (unsigned)(pAnchorElem->noCapturedGrps
                                                      + f*pAlt->noCapturedGrps_s
                                                     );

                /* The reference counter decides whether the element is still required or
                   can be taken from the stack. */
                if(--pAlt->cntRelative == 0u)
                    -- pMatcher->noPathElements;
            }
            return true;
        }
        else
        {
            /* The tp of stack contains a loop state. It is no longer needed and is silently
               popped. */
            -- pMatcher->noPathElements;
        }
    }

    return false;

} /* popAlternative */


/**
 * Store some loop counting information. The information is pushed onto the same stack as
 * is used for path alternatives. This is the simplest way of keeping track, which loop
 * entry belongs to which path; if a path is discarded due to a failed match then the loop
 * information objects which relate to this path will be implicitely popped from the stack,
 * too. This is the reason, why there is no function popLoop().
 *   @param pMatcher
 * The matcher object by reference. It contains the stack, where to push the information.
 *   @param idxLoop
 * The ID of the loop, which the pushed information relates to.
 *   @param cnt
 * The state of the loop, which is pushed. The number of cycles already matched.
 *   @note
 * Sharing the same stack between path alternatives and loop information is not optimally
 * with respect to use of memory and CPU. A loop info object is significantly smaller than
 * a path object but it'll use the same space on the stack. (On the other hand, a dedicated
 * loop stack would need additional data structure elements for the synchronization of both
 * the stacks.) CPU load is wasted as access to the loop information requires a linear
 * search for the right object, which could be avoided with a dedicated data structure.
 * However, the effect is very little in practice and even zero for most loops - as only
 * the less common bounded loops make use of the loop information object.
 */
static void pushLoop( struct re_matcher_t * const pMatcher
                    , uint8_t idxLoop
                    , uint8_t cnt
                    )
{
    assert(MATCHER_OK);
    if(pMatcher->noPathElements < pMatcher->maxNoPathElements)
    {
        struct re_matcherStackElement_t * const pStackElem =
                                    &pMatcher->matcherPathStack[pMatcher->noPathElements++];
#if RE_MATCHER_COMPILE_STATISTICS != 0
        if(pMatcher->noPathElements > pMatcher->maxUsePathElements)
            ++ pMatcher->maxUsePathElements;
#endif
        pStackElem->isPathElem = false;

        struct re_matcherLoopState_t * const pLoop = &pStackElem->loopState;
        pLoop->idxLoop = idxLoop;
        pLoop->noCycles = cnt;
    }
    else if(MATCHER_OK)
        pMatcher->err = re_errMatch_stateBufferOverflow;

} /* pushLoop */


/**
 * Read the stored state information of a given loop. The operation relates to the last
 * recently stored cycle count, which had been stored for the given loop using pushLoop().
 *   Note, the operation involves a linear search for the stored loop information object
 * down the stack of path alternatives and loop infor objects.
 *   @return
 * The loop state information is returned by reference or NULL if no state information had
 * been pushed for the given loop.\n
 *   Note, this situation is surely an implementation error and caught by assertion in
 * DEBUG compilation.
 *   @param pMatcher
 * The matcher object by reference. It contains the stack, where to look for the
 * information.
 *   @param idxLoop
 * The ID of the loop. The last recently stored state of this loop is addressed. (Note,
 * that elder infrmation for the same loop can still be found on the stack, due to an
 * earlier cycle of an outer loop.)
 */
static struct re_matcherLoopState_t *getCurrentLoopState( struct re_matcher_t * const pMatcher
                                                        , unsigned int idxLoop
                                                        )
{
    assert(MATCHER_OK);
    unsigned int idxStackElem = pMatcher->noPathElements;
    while(idxStackElem > 0u)
    {
        struct re_matcherStackElement_t * const pStackElem =
                                                &pMatcher->matcherPathStack[-- idxStackElem];

        /// @todo We should count the cycles for looking for the loop state. We could
        // alternatively use a stack per loop, which would reduce this search to an O(1)
        // operation. However, does the implementation effort really pay off?

        /* We are inspecting only the stack entries containing loop states. */
        if(!pStackElem->isPathElem)
        {
            struct re_matcherLoopState_t * const pLoop = &pStackElem->loopState;
            if(pLoop->idxLoop == idxLoop)
            {
                /* The top-most match for the given loop is what we look for. */
                return pLoop;
            }
        }
    }
    assert(false);
    return NULL;

} /* getCurrentLoopState */


/**
 * If the current matching path encounters the beginning of a capture group then this
 * function is used to store the current input stream position, i.e., the character by
 * reference, which is the first one of the capture group match.
 *   @param pMatcher
 * The matcher object by reference. It contains a stack, where the capture group matches
 * are pushed.
 *   @param idxCGrp
 * The ID of the group. Effectively a zero based index among all groups in the regular
 * expression.
 */
static void pushCGrpStart( struct re_matcher_t * const pMatcher
                         , unsigned int idxCGrp
                         )
{
    assert(MATCHER_OK);
    if(pMatcher->noCapturedGrps < pMatcher->maxNoCapturedGrps)
    {
        struct re_matcherCGrpStackElement_t * const pStackElem =
                                            &pMatcher->cGrpStack[pMatcher->noCapturedGrps++];
        assert(idxCGrp < UINT8_MAX);
        pStackElem->idxCGrp = (uint8_t)idxCGrp;

        /* The maximum string to match against the regular expression has a size of 64k. */
        signed int idxC = pMatcher->pC - pMatcher->cStream;
        assert(idxC >= 0);
        if(idxC >= UINT16_MAX)
        {
            idxC = UINT16_MAX - 1u;
            pMatcher->err = re_errMatch_inputStringTooLong;
        }
        pStackElem->idxCStreamFrom = (uint16_t)idxC;
        pStackElem->idxCStreamTo   = (uint16_t)idxC;
    }
    else if(MATCHER_OK)
        pMatcher->err = re_errMatch_captureGroupBufferOverflow;

} /* pushCGrpStart */


/**
 * If the current matching path encounters the end of a capture group then this
 * function is used to store the current input stream position, i.e., the character by
 * reference, which denotes the end of capture group match (not including).
 *   @param pMatcher
 * The matcher object by reference. It contains the stack, where the capture group matches
 * are pushed.
 *   @param idxCGrp
 * The ID of the group. Effectively a zero based index among all groups in the regular
 * expression.
 */
static void storeCGrpEnd( struct re_matcher_t * const pMatcher
                        , unsigned int idxCGrp
                        )
{
    assert(MATCHER_OK);
    assert(pMatcher->noCapturedGrps <= pMatcher->maxNoCapturedGrps);

    /* The maximum string to match against the regular expression has a size of 64k. */
    signed int idxC = pMatcher->pC - pMatcher->cStream;
    assert(idxC >= 0);
    if(idxC >= UINT16_MAX)
    {
        idxC = UINT16_MAX - 1u;
        pMatcher->err = re_errMatch_inputStringTooLong;
    }

    /* The reported end of capture group belongs to the top-most still unsatisfied entry
       for the given group index. */
    unsigned int idxStackElem = pMatcher->noCapturedGrps;
#ifndef DEBUG
    __attribute__((unused))
#endif
    bool entryFound = false;
    while(idxStackElem > 0u)
    {
        struct re_matcherCGrpStackElement_t * const pStackElem =
                                                        &pMatcher->cGrpStack[--idxStackElem];

        /// @todo We should count the cycles for looking for the capture group. We could
        // alternatively use a stack per group, which would reduce this search to an O(1)
        // operation. However, does the implementation effort really pay off?

        if(pStackElem->idxCGrp == idxCGrp)
        {
            pStackElem->idxCStreamTo = (uint16_t)idxC;
            entryFound = true;
            break;
        }
    }
    assert(entryFound);

} /* storeCGrpEnd */


/**
 * Execution of the loop instruction. Mainly the initialization of the loop counter (if
 * applicable as for bounded loops) and the decision, where to continue matching and what
 * is an alternative match path: For greedy loops, matching continues with the body of the
 * loop and it is an alternative to continue matching behind the loop and for non-greedy
 * loops it is just vice versa.
 *   @param pMatcher
 * The matcher object by reference.
 *   @param pILoop
 * The loop instruction, which had been fetched just before at the current instruction
 * pointer location (and which had caused the branch into this function).
 *   @param[in,out] ppI
 * The instruction pointer. On entry it points behind the just fetched loop instruction,
 * i.e., at the first instruction of the loop body. On exit, it may point somewhere else,
 * depending on the details of the loop, i.e., behind the loop in case of a non-greedy
 * loop.
 */
static void matchLoop( struct re_matcher_t * const pMatcher
                     , const struct iLoop_t * const pILoop
                     , const uint8_t ** const ppI
                     )
{
    const uint8_t *pI = *ppI;
    const bool isAltBehindLoop = pILoop->isGreedy &&  pILoop->min == 0u
             , isAltBody = !pILoop->isGreedy &&  pILoop->min == 0u
             , isCntLoop = pILoop->min > 1u
                           ||  (pILoop->max > 1u  &&  pILoop->max < UINT8_MAX);
    if(isCntLoop)
    {
        TRACE_ALT( "%2u, Push counter value 0 at entry in loop %u at %u\n"
                 , pMatcher->noPathElements
                 , pILoop->idxLoop
                 , (unsigned)(pI-6-pMatcher->pRe->iStream)
                 );
        pushLoop(pMatcher, pILoop->idxLoop, /* cnt */ 0u);
    }

    if(isAltBehindLoop)
    {
        assert(!isAltBody);
        TRACE_ALT( "%2u, Push alternative 'behind' at entry in loop %u at %u:"
                   " %02X, '%s'\n"
                 , pMatcher->noPathElements
                 , pILoop->idxLoop
                 , (unsigned)(pI-6-pMatcher->pRe->iStream)
                 , *(pI+pILoop->lenIBody+3)
                 , pMatcher->pC
                 );
        pushAlternative(pMatcher, pI+pILoop->lenIBody+3);
    }
    else if(isAltBody)
    {
        TRACE_ALT( "%2u, Push alternative 'body' at entry in loop %u at %u:"
                   " %02X, '%s'\n"
                 , pMatcher->noPathElements
                 , pILoop->idxLoop
                 , (unsigned)(pI-6-pMatcher->pRe->iStream)
                 , *pI
                 , pMatcher->pC
                 );
        pushAlternative(pMatcher, pI);
    }

    if(!isAltBody)
    {
        /* Most common situation: Match body of loop. Instruction pointer already
           points there, nothing to do. */
    }
    else
    {
        /* Matching the body is just an alternative: A non-greedy loop first tries
           to match without the loop body. */
        pI += pILoop->lenIBody + 3u;
    }

    *ppI = pI;

} /* matchLoop */


/**
 * Execution of the loop end instruction. Mainly the check of the loop counter (if
 * applicable as for bounded loops) and the decision, where to continue matching and what
 * is an alternative match path: For greedy loops, matching continues again with the body
 * of the loop and it is an alternative to continue matching behind the loop and for
 * non-greedy loops it is just vice versa.
 *   @param pMatcher
 * The matcher object by reference.
 *   @param pILoop
 * The loop end instruction, which had been fetched just before at the current instruction
 * pointer location (and which had caused the branch into this function).
 *   @param[in,out] ppI
 * The instruction pointer. On entry it points behind the just fetched loop end
 * instruction, i.e., at the first instruction behind the loop. On exit, it may point
 * somewhere else, depending on the details of the loop, i.e., to the loop body in case of
 * a greedy loop.
 */
static void matchLoopEnd( struct re_matcher_t * const pMatcher
                        , const struct iLoopEnd_t * const pILoopEnd
                        , const uint8_t ** const ppI
                        )
{
    const uint8_t *pI = *ppI;

    const bool is01Loop = pILoopEnd->iLoop.min == 0u
                          &&  pILoopEnd->iLoop.max == 1u
             , isCntLoop = !is01Loop
                           &&  (pILoopEnd->iLoop.min > 1u
                                ||  pILoopEnd->iLoop.max < UINT8_MAX
                               );
    unsigned int cnt =  1u;
    struct re_matcherLoopState_t *pLoopState = NULL;
    if(isCntLoop)
    {
        pLoopState = getCurrentLoopState(pMatcher, pILoopEnd->iLoop.idxLoop);
        cnt += pLoopState->noCycles;
        TRACE_ALT( "%2u, New counter value %u at end of loop %u at %u\n"
                 , pMatcher->noPathElements
                 , cnt
                 , pILoopEnd->iLoop.idxLoop
                 , (unsigned)(pI-3-pMatcher->pRe->iStream)
                 );
    }
    const bool cntPermitsTwoPaths = !(isCntLoop || is01Loop)
                                    ||  (cnt >= pILoopEnd->iLoop.min
                                         &&  cnt < pILoopEnd->iLoop.max
                                        )
             , cntForcesBreak = cnt >= pILoopEnd->iLoop.max
             , isAltBehindLoop = pILoopEnd->iLoop.isGreedy && cntPermitsTwoPaths
             , isAltBody = !pILoopEnd->iLoop.isGreedy && cntPermitsTwoPaths
             , contBehindLoop = isAltBody || cntForcesBreak
             , updateCnt = isCntLoop && !cntForcesBreak;

    if(updateCnt)
    {
        TRACE_ALT( "%2u, Update counter value to %u at end of loop %u at %u\n"
                 , pMatcher->noPathElements
                 , cnt
                 , pILoopEnd->iLoop.idxLoop
                 , (unsigned)(pI-3-pMatcher->pRe->iStream)
                 );
        assert(pILoopEnd->iLoop.idxLoop == pLoopState->idxLoop);
        assert(cnt < UINT8_MAX);
        pLoopState->noCycles = (uint8_t)cnt;
    }

    if(isAltBehindLoop)
    {
        assert(!isAltBody);
        TRACE_ALT( "%2u, Push alternative 'behind' at end of loop %u at %u:"
                   " %02X, '%s'\n"
                 , pMatcher->noPathElements
                 , pILoopEnd->iLoop.idxLoop
                 , (unsigned)(pI-3-pMatcher->pRe->iStream)
                 , *pI
                 , pMatcher->pC
                 );
        pushAlternative(pMatcher, pI);
    }
    else if(isAltBody)
    {
        TRACE_ALT( "%2u, Push alternative 'body' at end of loop %u at %u: %02X, '%s'\n"
                 , pMatcher->noPathElements
                 , pILoopEnd->iLoop.idxLoop
                 , (unsigned)(pI-3-pMatcher->pRe->iStream)
                 , *pILoopEnd->pIBody
                 , pMatcher->pC
                 );
        pushAlternative(pMatcher, pILoopEnd->pIBody);
    }

    if(contBehindLoop)
    {
        /* Either the maximum cycles is reached, or, for now, a non-greedy loop
           tries continuing behind the loop. */
    }
    else
    {
        /* There is an other matching cycle, so jump back to the beginning of the
           loop body. */
        pI = pILoopEnd->pIBody;
    }

    *ppI = pI;

} /* matchLoopEnd */



/**
 * Main API: Call of the regular expression matcher. The input to match is an arbitrary
 * character sequence. 
 *   @return
 * The matcher returns \a true if the regular expression matches the input stream. If the
 * compiler had been used to generate the compiled expression then it depends on the
 * compilation argument \a matchAnywhere (see re_compile()) if this means a match anywhere
 * in the input stream or only from the beginning of the input stream.
 *   @param[in,out] pMatcher
 * The matcher object by reference.\n
 *   On entry, all fields have been configured, which relate to the user specified memory
 * spaces, i.e., the pointers to the memory areas to be used and the capacities of these
 * areas. This relates to the buffer for path alternatives (.matcherPathStack and
 * .maxNoPathElements) and the storage for capture groups (.cGrpStack and
 * .maxNoCapturedGrps).\n
 *   On exit, the matcher contains the status field, err, which potentially indicates a
 * matching error, the contents of the capture groups and some statistic values about
 * matching effort and actually required memory space for the path alternatives.
 *   @param[in] pCompiledRe
 * The compiled regular expression by reference. Normally either the result from a
 * successful run of the compiler (see re_compile()) or a regular expression, which had
 * been exported as source code by the compiler (see main()).
 *   @param[in] inputStream
 * The input to match as a character string in random access memory. Usually, this will
 * just be a C string but this is not a must. The regular expression may contain match
 * requests even for zero bytes. The end of the input character string is therefore not a
 * zero byte but specified by \a lenInputStream.
 *   @param[in] lenInputStream
 * The number of characters of the input; see \a inputStream also.
 */
bool re_match( struct re_matcher_t * const pMatcher
             , const struct re_compiledRegExp_t * const pCompiledRe
             , const char * const inputStream
             , unsigned int lenInputStream
             )
{
    /* First do a plausibility check if the matcher object has been properly pre-configured
       by the user. */
    if(pMatcher->matcherPathStack == NULL  ||  pMatcher->maxNoPathElements < 10u
       ||  (pMatcher->cGrpStack == NULL) != (pMatcher->maxNoCapturedGrps == 0u)
       ||  pMatcher->maxNoCapturedGrps > UINT8_MAX
      )
    {
        pMatcher->err = re_errMatch_badMemoryConfiguration;
    }
    else
        pMatcher->err = re_errMatch_success;

    /* Configure input stream and reset the counters. */
    pMatcher->pRe = pCompiledRe;
    pMatcher->cStream = inputStream;
    pMatcher->lenCStream = lenInputStream;
    pMatcher->pC = inputStream;
    pMatcher->noPathElements = 0u;
    pMatcher->noCapturedGrps = 0u;
#if RE_MATCHER_COMPILE_STATISTICS != 0
    pMatcher->noInstructions = 0u;
    pMatcher->maxUsePathElements = 0u;
#endif

    const char * const endCStream = pMatcher->pC + pMatcher->lenCStream;
    const uint8_t *pI = pMatcher->pRe->iStream;
    const uint8_t * const pEndIStream = pI + pMatcher->pRe->lenIStream;

    bool isMatching = true;
    while(MATCHER_OK  &&  pI < pEndIStream)
    {
#if RE_MATCHER_COMPILE_STATISTICS != 0
        /* We maintain an instruction counter in order to have a cost for the match
           process. Could be useful for the evaluation of the quality of a regexp for a
           given purpose. */
        ++ pMatcher->noInstructions;
#endif
        /* The space for the different potential instructions can be combined, they are
           used either or. The arbitrary, useless and superfluous initializer expression is
           only due to avoidance of warnings with some compilers ("potential use of
           uninitialized variable"). */
        union
        {
            struct iLoop_t loop;
            struct iLoopEnd_t loopEnd;
            struct iOr_t or;
            struct iJmp_t jmp;
            struct iCap_t cap;
            struct iCapEnd_t capEnd;
        } instr = {.or = {.lenAlternative = 0u,},};

        if(iFetchLoop(&instr.loop, &pI))
            matchLoop(pMatcher, &instr.loop, &pI);
        else if(iFetchLoopEnd(&instr.loopEnd, &pI))
            matchLoopEnd(pMatcher, &instr.loopEnd, &pI);
        else if(iFetchOr(&instr.or, &pI))
        {
            TRACE_ALT( "%2u, Push alternative of OR at %u: %02X, '%s'\n"
                     , pMatcher->noPathElements
                     , (unsigned)(pI-3-pMatcher->pRe->iStream)
                     , *(pI+instr.or.lenAlternative)
                     , pMatcher->pC
                     );
            pushAlternative(pMatcher, pI+instr.or.lenAlternative);
        }
        else if(iFetchJmp(&instr.jmp, &pI))
        {
            pI += instr.jmp.dist;
            TRACE_ALT("Jump to end of OR at %u\n", (unsigned)(pI-pMatcher->pRe->iStream));
            assert(isMatching);
        }
        else if(iFetchCap(&instr.cap, &pI))
        {
            TRACE_CAP( "Capture group %u at %u starts with '%s'\n"
                     , instr.cap.idxCGrp
                     , (unsigned)(pI-2-pMatcher->pRe->iStream)
                     , pMatcher->pC
                     );
            pushCGrpStart(pMatcher, instr.cap.idxCGrp);
            assert(isMatching);
        }
        else if(iFetchCapEnd(&instr.capEnd, &pI))
        {
            TRACE_CAP( "Capture group %u at %u ends before '%s'\n"
                     , instr.cap.idxCGrp
                     , (unsigned)(pI-2-pMatcher->pRe->iStream)
                     , pMatcher->pC
                     );
            storeCGrpEnd(pMatcher, instr.cap.idxCGrp);
            assert(isMatching);
        }
        else if(*pI == I_CARET)
        {
            ++ pI;
            isMatching = pMatcher->pC == pMatcher->cStream;
        }
        else if(*pI == I_DOLLAR)
        {
            ++ pI;
            isMatching = pMatcher->pC == endCStream;
        }
        else if(pMatcher->pC < endCStream)
        {
            /* If we get here, then we have an immediate match with a consumed input
               character. Matching of an alternative has failed if we get here but the
               input stream is exhausted. */
            const char c = * pMatcher->pC++;
            bool shouldMatch;
            isMatching = immediateMatch(&shouldMatch, &pI, c);

            /* If the assertion fires then we have an illegal instruction stream. This must
               never happen in a valid integration of the regular expression code and is
               not a runtime error but a static implementation error. It points to some
               inconsistency between calling the compiler and passing the data to the
               matcher. */
            assert(shouldMatch);

            TRACE_ALT( isprint((int)c)? "%s %c\n": "%s \\x%02X\n"
                     , isMatching? "Consumed": "Rejected"
                     , (unsigned)c
                     );
        }
        else
        {
            assert(pMatcher->pC == endCStream);
            isMatching = false;

        } /* End of if/else(Which instruction?) */

        /* Fetching the next instruction: As long as we match the input, we take the next
           one. Otherwise we switch to an already seen and buffered alternative. If there
           is no such alternative than the regular expressions eventually doesn't match. */
        if(isMatching)
        {
            /* We are still in a matching path. */
        }
        else if(MATCHER_OK)
        {
            /* The current alternative failed to match. We switch to another one. */
            if(!popAlternative(pMatcher, &pI))
                pMatcher->err = re_errMatch_inputDoesNotMatch;
            else
            {
                TRACE_ALT( "%2u, Fetching alternative: %02X, '%s'\n"
                         , pMatcher->noPathElements
                         , *pI
                         , pMatcher->pC
                         );
                isMatching = true;
            }
        }
    } /* while(Next instruction) */

    assert(pI <= pEndIStream);

    /* Process may have been aborted due to out-of-memory, while we were still in a match. */
    if(!MATCHER_OK)
        isMatching = false;

    assert(!isMatching  ||  pI == pEndIStream);
    return isMatching;

} /* re_match */



/**
 * Main API: Call of the regular expression matcher. The input to match is a zero
 * terminated C string.
 *   @return
 * The matcher returns \a true if the regular expression matches the input stream. If the
 * compiler had been used to generate the compiled expression then it depends on the
 * compilation argument \a matchAnywhere (see re_compile()) if this means a match anywhere
 * in the input stream or only from the beginning of the input stream.
 *   @param[in,out] pMatcher
 * The matcher object by reference.\n
 *   On entry, all fields have been configured, which relate to the user specified memory
 * spaces, i.e., the pointers to the memory areas to be used and the capacities of these
 * areas. This relates to the buffer for path alternatives (.matcherPathStack and
 * .maxNoPathElements) and the storage for capture groups (.cGrpStack and
 * .maxNoCapturedGrps).\n
 *   On exit, the matcher contains the status field, err, which potentially indicates a
 * matching error, the contents of the capture groups and some statistic values about
 * matching effort and actually required memory space for the path alternatives.
 *   @param[in] pCompiledRe
 * The compiled regular expression by reference. Normally either the result from a
 * successful run of the compiler (see re_compile()) or a regular expression, which had
 * been exported as source code by the compiler (see main()).
 *   @param[in] inputStream
 * The input to match as a zero terminated C character string in random access memory.
 */
bool re_matchCString( struct re_matcher_t * const pMatcher
                    , const struct re_compiledRegExp_t * const pCompiledRe
                    , const char * const inputStream
                    )
{
    return re_match(pMatcher, pCompiledRe, inputStream, strlen(inputStream));

} /* re_matchCString */


/**
 * Fetching match results after successful matching: Get the number of matches for a given
 * capture group.
 *   @return
 * The number of matches is returned. Zero is returned if there is no match or if no such
 * capture group is known or if the match result is not re_errMatch_success.
 *   @param[in] pMatcher
 * The matcher object by reference. The object must not have been modified after the
 * successful run of the matcher.
 *   @param idxCGrp
 * The zero based index of the capture group. The indexes numerate the capture groups in
 * order of appearance of the opening brackets in the regular expression.
 */
unsigned int re_getNoMatchesCaptureGrp( struct re_matcher_t * const pMatcher
                                      , unsigned int idxCGrp
                                      )
{
    if(pMatcher->err != re_errMatch_success)
        return 0u;

    /* The matches of the different groups don't have a pre-determined order. We need to
       iterate the entire list of matches. */
    unsigned int noMatches = 0u;   
    const struct re_matcherCGrpStackElement_t *pStackElem = &pMatcher->cGrpStack[0]
                                            , * const pEndStack = 
                                                        pStackElem+pMatcher->noCapturedGrps;
    while(pStackElem < pEndStack)
    {
        if(pStackElem->idxCGrp == idxCGrp)
            ++ noMatches;
        
        ++ pStackElem;
    }
    
    return noMatches;

} /* re_getNoMatchesCaptureGrp */


/**
 * Fetching match results after successful matching: Get a particular match for a given
 * capture group.
 *   @return
 * The function returns \a true if it has found the requested match and \a false otherwise.
 *   @param[in] pMatcher
 * The matcher object by reference. The object must not have been modified after the
 * successful run of the matcher.
 *   @param[in] idxCGrp
 * The zero based index of the capture group. The indexes numerate the capture groups in
 * order of appearance of the opening brackets in the regular expression.
 *   @param[out] pIdx1stChar
 * The function result is returned as pair of zero based character indexes. The indexes
 * relate to the original input character string, which had been passed to either
 * re_match() or re_matchCString(), argument \a inputStream.\n
 *   If the requested match exists then this is the index of the first character by
 * reference, which matched against the capture group.
 *   @param[out] pIdxEnd
 * The index of the end of the requested match by reference.\n
 *   If the requested match exists then this is the index of the first character, which
 * didn't match any more against the capture group, i.e., the index points to the end of
 * the match.\n
 *   If the requested match doesn't exist then * \a pIdx1stChar and * \a pIdx1stChar are
 * identical on exit. The function return value can be used to distinguish between "no
 * match" and "empty string matched". (In ether case, both returned indexes are identical.)
 *   @param[in] idxMatch
 * For typical regular expressions, a capture group will have either no or one match.
 * However, if a capture group is used inside a loop, any number of matches are imaginable.
 * This index addresses to different matches of group \a idxCGrp in the order they have on
 * the match path. re_getNoMatchesCaptureGrp() can be used to find out, how many matches
 * actually exist for the given group.
 */
bool re_getMatchOfCaptureGrp( struct re_matcher_t * const pMatcher
                            , unsigned int * const pIdx1stChar
                            , unsigned int * const pIdxEnd
                            , unsigned int idxCGrp
                            , unsigned int idxMatch
                            )
{
    if(pMatcher->err == re_errMatch_success)
    {
        /* The matches of the different groups don't have a pre-determined order. We need
           to iterate the entire list of matches. */
        unsigned int noMatches = 0u;   
        const struct re_matcherCGrpStackElement_t *pStackElem = &pMatcher->cGrpStack[0]
                                                , * const pEndStack = 
                                                        pStackElem+pMatcher->noCapturedGrps;
        while(pStackElem < pEndStack)
        {
            if(pStackElem->idxCGrp == idxCGrp)
            {
                if(noMatches == idxMatch)
                {
                    *pIdx1stChar = (unsigned)pStackElem->idxCStreamFrom;
                    *pIdxEnd     = (unsigned)pStackElem->idxCStreamTo;
                    return true;
                }

                ++ noMatches;
            }
            ++ pStackElem;
        }
    } /* if(Match has succeeded?) */    
    
    *pIdx1stChar = 0u;
    *pIdxEnd     = 0u;
    return false;

} /* re_getNoMatchesCaptureGrp */


/**
 * Fetching match results after successful matching: Get a particular match for a given
 * capture group as copied C string. The function differs from the similar
 * re_getNoMatchesCaptureGrp() in that it copies the matching characters into a caller
 * provided buffer.
 *   @return
 * The function returns \a true if it has found the requested match and \a false otherwise.
 *   @param[in] pMatcher
 * The matcher object by reference. The object must not have been modified after the
 * successful run of the matcher. And, particularly, the character input stream, which had
 * been passed to the matcher object for matching must not have been modified meanwhile.
 *   @param[in] pMatchBuf
 * The requested match result is copied into this user provided buffer. The result is
 * returned as zero terminated C string in this buffer, which is assumed to have a capacity
 * of at least \a sizeOfMatchBuf charaters, including the terminating zero byte.\n
 *   Please note, the regular expression matcher doesn't work with zero terminated strings.
 * It can match zero bytes as any other character. This will invalidate this function, if
 * the requested match can potentially contain a zero byte. However, in the vast majority
 * of use cases, this won't be the case.\n
 *   If the requested match doesn't exist then the empty string is copied into \a
 * pMatchBuf. The function return value can be used to distinguish between "no match" and
 * "empty string matched".
 *   @param[in] idxMatch
 * For typical regular expressions, a capture group will have either no or one match.
 * However, if a capture group is used inside a loop, any number of matches are imaginable.
 * This index addresses to different matches of group \a idxCGrp in the order they have on
 * the match path. re_getNoMatchesCaptureGrp() can be used to find out, how many matches
 * actually exist for the given group.
 *   @param[in] sizeOfMatchBuf
 * The capacity of the provided buffer \a pMatchBuf in Byte.
 */
bool re_copyMatchOfCaptureGrp( struct re_matcher_t * const pMatcher
                             , char * const pMatchBuf
                             , unsigned int idxCGrp
                             , unsigned int idxMatch
                             , unsigned int sizeOfMatchBuf
                             )
{
    assert(pMatchBuf != NULL  &&  sizeOfMatchBuf > 0u);

    unsigned int idx1stChar, idxEnd;
    const bool gotMatch = re_getMatchOfCaptureGrp( pMatcher
                                                 , &idx1stChar
                                                 , &idxEnd
                                                 , idxCGrp
                                                 , idxMatch
                                                 );
    assert(idxEnd >= idx1stChar);
    unsigned int noCharsToCpy = idxEnd - idx1stChar;
    
    /* There must not be an overflow as the original indexes had been limited to the
       implementation range of uint16_t. */
    assert(noCharsToCpy < UINT_MAX);
    
    if(noCharsToCpy + 1u > sizeOfMatchBuf)
        noCharsToCpy = sizeOfMatchBuf - 1u;

    /* We provide the result as zero terminated C string, although the matcher is not
       restricted to input of such format. If the matching has to deal with zero bytes
       in the input stream then this function may potentially not behave as expected. */
    memcpy(pMatchBuf, pMatcher->cStream+idx1stChar, noCharsToCpy);
    pMatchBuf[noCharsToCpy] = '\0';

    return gotMatch;

} /* re_copyMatchOfCaptureGrp */
#endif