#ifndef RE_REGEXP_MATCHER_INCLUDED
#define RE_REGEXP_MATCHER_INCLUDED
/**
 * @file re_regExpMatcher.h
 * Definition of global interface of module re_regExpMatcher.c
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

/*
 * Include files
 */

#include <stdint.h>
#include <stdbool.h>

/*
 * Defines
 */

/** The compiler and matcher can be compiled independently to support the use case of
    having only compiled expressions in an embedded software program but not the
    compiler.\n
      This switch enables or diables the compilation of the compiler. Set this configuration
    switch to either 1 or 0 to do so, respectively. */
#ifndef RE_REQUIRE_COMPILER
# define RE_REQUIRE_COMPILER    1
#endif

/** The compiler and matcher can be compiled independently to support the use case of
    having only compiled expressions in an embedded software program but not the
    compiler.\n
      This switch enables or diables the compilation of the matcher. Set this configuration
    switch to either 1 or 0 to do so, respectively. */
#ifndef RE_REQUIRE_MATCHER
# define RE_REQUIRE_MATCHER     1
#endif

/** If set not zero then some code is compiled which allows to rate the efficiency of the
    compiled expression for a given match. */
#define RE_MATCHER_COMPILE_STATISTICS  1

/* The instructions to build a compiled regular expression. */
#define I_ILLEGAL           (0x80u)
#define OP_LOOP             (0x81u)
#define OP_LOOPNG           (0x82u)
#define I_LOOP(idxLoop,len,min,max) (OP_LOOP),(((len)&0xFF00u)>>8),(((len)&0xFFu)),(min),(max),(idxLoop)
#define I_LOOP_NG(idxLoop,len,min,max) (OP_LOOPNG),(((len)&0xFF00u)>>8),(((len)&0xFFu)),(min),(max),(idxLoop)
#define OP_LOOPEND          (0x83u)
#define I_LOOPEND(lenBody)  (OP_LOOPEND),(((lenBody)&0xFF00u)>>8),(((lenBody)&0xFFu))
#define OP_OR               (0x84u)
#define I_OR(len)           (OP_OR),(((len)&0xFF00u)>>8),(((len)&0xFFu))
#define OP_JMP              (0x85u)
#define I_JMP(dist)         (OP_JMP),(((dist)&0xFF00u)>>8),(((dist)&0xFFu))
#define OP_CAP              (0x86u)
#define I_CAP(idx)          (OP_CAP),(idx)
#define OP_CAPEND           (0x87u)
#define I_CAPEND(idx)       (OP_CAPEND),(idx)
#define OP_CHARSET          (0x88u)
#define I_CHARSET(dist)     (OP_CHARSET),(((dist)&0xFF00u)>>8),(((dist)&0xFFu))
#define I_LIT(a)            ((a)&0x7Fu)
#define OP_ESC              (0x89u)
#define I_LIT_ESC(a)        (OP_ESC),(a)
#define I_DIGIT             (0x8Au)
#define I_HEXDIGIT          (0x8Bu)
#define I_SPC               (0x8Cu)
#define I_AZ                (0x8Du)
#define I_LTR               (0x8Eu)
#define I_ID1ST             (0x8Fu)
#define I_ID                (0x90u)
#define I_CRLF              (0x91u)
#define I_ANY               (0x92u)
#define I_CARET             (0x93u)
#define I_DOLLAR            (0x94u)
#define I_DC(a,b,c,d)       (a),(b),(c),(d)

/* The lengths of the instructions. */
#define LEN_I_ILLEGAL       1u
#define LEN_I_LOOP          6u
#define LEN_I_LOOP_NG       6u
#define LEN_I_LOOPEND       3u
#define LEN_I_OR            3u
#define LEN_I_JMP           3u
#define LEN_I_CAP           2u
#define LEN_I_CAPEND        2u
#define LEN_I_CHARSET       3u
#define LEN_I_LIT           1u
#define LEN_I_LIT_ESC       2u
#define LEN_I_DIGIT         1u
#define LEN_I_HEXDIGIT      1u
#define LEN_I_SPC           1u
#define LEN_I_AZ            1u
#define LEN_I_LTR           1u
#define LEN_I_ID1ST         1u
#define LEN_I_ID            1u
#define LEN_I_CRLF          1u
#define LEN_I_ANY           1u
#define LEN_I_CARET         1u
#define LEN_I_DOLLAR        1u
#define LEN_I_DC            4u

/*
 * Global type definitions
 */

/** Enumeration of all possible matcher errors. */
enum re_matcherError_t {

    /** No error, matching of the regular expression against the input character stream was
        possible. */
    re_errMatch_success,
    
    /** The matching process completed without runtime error but the regular expression
        didn't match against the input character stream. */
    re_errMatch_inputDoesNotMatch,
    
    /** The matching process didn't complete. The matcher ran out of memory. The capacity
        of field \a matcherPathStack in the matcher object was to little for the given
        combination of regular expression and input character stream. */
    re_errMatch_stateBufferOverflow,

    /** The matching process didn't complete. The matcher ran out of memory. The capacity
        of field \a cGrpStack in the matcher object was to little for the given combination
        of regular expression and input character stream. */
    re_errMatch_captureGroupBufferOverflow,
    
    /** The matching process didn't complete. The input character string is too long for
        matching. (Internal data representation, which uses 16 Bit for character stream
        handling, has overflown.) */
    re_errMatch_inputStringTooLong,
    
    /** Initially, the matcher checks the pre-allocated, user provided memory
        configuration. This is a plausibility check of the fields \a matcherPathStack, \a
        maxNoPathElements, \a cGrpStack and \a maxNoCapturedGrps. This error is raised if
        some suspicious configuration is found and matching doesn't even commence. */
    re_errMatch_badMemoryConfiguration,
};

/** The compiled regular expression. */
struct re_compiledRegExp_t
{
    /** The instruction stream, including constant data. Prior to compilation, this is a
        user configured field; the user provides the memory space for the comilation of the
        regular expression. */
    uint8_t *iStream;

    /** The number of instruction bytes in the instruction stream. This count does not
        include the constant data bytes at the end of the instruction stream. */
    unsigned int lenIStream;

    /** The number of capture groups in the regular expression. */
    unsigned int noCaptureGrps;

    /** The number of character sets used in the instruction stream. */
    unsigned int noCharSets;
};

/// @todo Make all of the matcher private, but add a constructor to make this possible

/** The state of a (bounded) loop. */
struct re_matcherLoopState_t
{
    /** The unique ID if the loop among all loops used in the regular expression. */
    uint8_t idxLoop;
    
    /** The number of already matched cycles of the loop. */
    uint8_t noCycles;
};

/** The state information of the mathcer, which enables it to continue an alternative path
    from an already visited node. */
struct re_matcherPathElement_t
{
    union
    {
        /** The instruction counter pointing to the instruction, from where to take the
            alternative path. */
        uint16_t idxI;

        /** Other encoding of same information as \a idxI; here as a signed delta with
            respect to the next stacked element. */
        int16_t idxI_s;
    };
    union
    {
        /** The input stream counter pointing to the first character to match on the
            alternative path. */
        uint16_t idxC;

        /** Other encoding of same information as \a idxC; here as a signed delta with
            respect to the next stacked element. */
        int16_t idxC_s;
    };
    union
    {
        /** The stack pointer into stack of already matched groups; this pointer value
            reverts the stack to all those groups, which began already before the node,
            where the alternative path branches. */
        uint8_t noCapturedGrps;

        /** Other encoding of same information as \a noCapturedGrps; here as a signed delta
            with respect to the next stacked element. */
        int8_t noCapturedGrps_s;
    };
    uint8_t cntRelative;
};

/** An element of the state information of the matcher.
      @remark Pushing different kinds of satte information onto the same stack simplifies
    the coordination but wastes memory space as the required union contains elements of
    significantls differt in size. Binary stack encoding would help or separate stacks. */
struct re_matcherStackElement_t
{
    union
    {
        /** This state element is an still available optional other path through the graph. */
        struct re_matcherPathElement_t pathAlternative;

        /** This state element is the counter of a bounded loop. */
        struct re_matcherLoopState_t loopState;
    };

    /** Flag to decide of which kind the state lement is. */
    bool isPathElem;
};

/** Representation of a matched capture group. */
struct re_matcherCGrpStackElement_t
{
    /** The first character in the input stream by zero based index, which belongs into the
        capture group. */
    uint16_t idxCStreamFrom;

    /** The first character in the input stream by zero based index, which does no longer
        belong into the capture group. Or UINT16_MAX while the end of the capture group as
        not been matched yet. */
    uint16_t idxCStreamTo;

    /** The ID of the capture group, which is the zero based index of groups, dealt out in
        the order of appearance of opening brackets in the regular expression. User handle
        to fetch group information after matching. */
    uint8_t idxCGrp;
};

/** The matcher, which processes a compiled regular expression and the character input
    stream. */
struct re_matcher_t
{
    /** The compiled regular expression by reference. Note, the contents of this field will
        usually be a result of the run of the regular expression compiler. */
    const struct re_compiledRegExp_t *pRe;

    /** The input character string to match.\n
          Note, the input stream is not necessarily a zero terminated C string. See other
        field \a lenCStream.
          @caution The matched input is not copied by the matcher. The memory contents, the
        pointer references, need to stay unmodified not only during matching but even
        beyond in order to safely fetch the results for capture groups; capture groups
        don't store text but only the references into the input character string! */
    const char *cStream;

    /** The number of input characters, which \a cStream provides. The match fails if this
        number of characters has been matched before all of the regular expression has been
        processed. */
    unsigned int lenCStream;

    /** The current position the matching process. Points to the next character in \a
        cStream, which has to match next. */
    const char *pC;

    /** The state information of the matcher. Mostly it is information about still possible
        alternative paths through the entire graph of match paths.\n
          This is a user configured field, to be set prior to using the matcher the first
        time. It is not changed during the run of the matcher. */
    struct re_matcherStackElement_t *matcherPathStack;

    /** The memory for state information, i.e., the memory space \a matcherPathStack, is
        provided by the user of the matcher. This field informs about the capacity of the
        provided array of elements. Basically, any number is allowed. However, the smaller
        the array the higher the risk that the matcher aborts matching without having a
        result yet and because of running out of memory.\n
          This is a user configured field, to be set prior to using the matcher the first
        time. It is not changed during the run of the matcher. */
    unsigned int maxNoPathElements;

    /** The current number of elements stored in \a matcherPathStack. */
    unsigned int noPathElements;

    /** State information of the matcher: Already partly or entirely matched capture
        groups.\n
          This is a user configured field, to be set prior to using the matcher the first
        time. It is not changed during the run of the matcher.\n
          The field can be configured NULL if \a maxNoCapturedGrps is zero. The matcher
        will still work well for all regular expressions, which don't make use of capture
        groups. */
    struct re_matcherCGrpStackElement_t *cGrpStack;

    /** The memory for capture groups, i.e., the memory space \a cGrpStack, is provided by
        the user of the matcher. This field informs about the capacity of the provided
        array of elements. Basically, any number is allowed. However, the smaller the array
        the higher the risk that the matcher aborts matching without having a result yet
        and because of running out of memory.\n
          This is a user configured field, to be set prior to using the matcher the first
        time. It is not changed during the run of the matcher. */
    unsigned int maxNoCapturedGrps;

    /** The current number of elements stored in \a cGrpStack. */
    unsigned int noCapturedGrps;

    /** Principal state information of the matcher: Still successful? Or an error message
        otherwise. */
    enum re_matcherError_t err;

#if RE_MATCHER_COMPILE_STATISTICS != 0
    /** Diagnostic information: Number of instructions needed to complete the matcher
        result. The number is measure for the efficiency of the regular expression to match
        the given input. This field should be evaluated by the user after matching. */
    unsigned int noInstructions;

    /** Diagnostic information: The number of elements from \a matcherPathStack, which were
        actually use to complete matching the given input. Basically, \a maxNoPathElements
        could be reduced to this number to successfully repeat the match. However, other
        input would typically require another number of elements and could fail in this
        case. This field should be evaluated by the user after matching. */
    unsigned int maxUsePathElements;
#endif
};



/*
 * Global data declarations
 */


/*
 * Global prototypes
 */

#if RE_REQUIRE_MATCHER == 1
/** Call of the matcher for an arbitrary input characer sequence. */
bool re_match( struct re_matcher_t *pMatcher
             , const struct re_compiledRegExp_t *pCompiledRe
             , const char *inputStream
             , unsigned int lenInputStream
             );

/** Call of the matcher for a zero terminated C string. */
bool re_matchCString( struct re_matcher_t * const pMatcher
                    , const struct re_compiledRegExp_t * const pCompiledRe
                    , const char * const inputStream
                    );

/** After matching: Get no. matches of capture group. */
unsigned int re_getNoMatchesCaptureGrp( struct re_matcher_t * const pMatcher
                                      , unsigned int idxCGrp
                                      );

/** After matching: Get match result of capture group by character indexes. */
bool re_getMatchOfCaptureGrp( struct re_matcher_t *pMatcher
                            , unsigned int *pIdx1stChar
                            , unsigned int *pIdxEnd
                            , unsigned int idxCGrp
                            , unsigned int idxMatch
                            );

/** After matching: Fetch match result of capture group into local buffer. */
bool re_copyMatchOfCaptureGrp( struct re_matcher_t * const pMatcher
                             , char * const pMatchBuf
                             , unsigned int idxCGrp
                             , unsigned int idxMatch
                             , unsigned int sizeOfMatchBuf
                             );
#endif

/*
 * Global inline functions
 */


#endif  /* RE_REGEXP_MATCHER_INCLUDED */
