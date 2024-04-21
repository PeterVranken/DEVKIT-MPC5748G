#ifndef RE_REGEXP_COMPILER_INCLUDED
#define RE_REGEXP_COMPILER_INCLUDED
/**
 * @file re_regExpCompiler.h
 * Definition of global interface of module re_regExpCompiler.c
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

#include "re_regExpMatcher.h"

/*
 * Defines
 */

/** A main function can be compiled, which integrates compiler and matcher into a simple
    application, which demonstartes the use of both, which supports testing regular
    expressions during development and which allows exporting compiled regular expressions
    as C source code for integration in embedded software programs.
      This switch enables or diables the compilation of the main function. Set this
    configuration switch to either 1 or 0 to do so, respectively. */
#ifndef RE_REQUIRE_MAIN
# define RE_REQUIRE_MAIN        0
#endif

/* The main function requires compilation of compiler and matcher. */
#if RE_REQUIRE_MAIN != 0
# undef RE_REQUIRE_COMPILER
# undef RE_REQUIRE_MATCHER
# define RE_REQUIRE_COMPILER    1
# define RE_REQUIRE_MATCHER     1
#endif

/* Check for bad, useless configuration. */
#if RE_REQUIRE_COMPILER == 0  &&  RE_REQUIRE_MATCHER == 0
# error At least one out of compiler or matcher needs to be configured for compilation
#endif

/*
 * Global type definitions
 */

/** Enumeration of all possible compiler errors. */
enum re_compilerError_t
{
    /** No error, compilation of regular expression was possible. */
    re_errComp_success,                         /* 0 */

    /** On entry into the compilation, re_compile(), the compiler object needs to be
        properly configured with user provided pre-allocated memory space, which is needed
        for the compilation. This is checked and this error code is set in case the
        configuration is found implausible. */
    re_errComp_badMemoryConfiguration,          /* 1 */

    /** The regular expression ended without finding the matching closing parenthesis,
        which can be a closing normal parenthesis or a closing angular bracket of the
        capture group. Note, getting this error does not necessarily mean that there is no
        such character but it can be on a bad level, e.g., by swapping different kinds of
        parenthesis. */
    re_errComp_missingRParen,                   /* 2 */

    /** The repetition operators must not be applied to sub-expressions, which can
        potentially match no single input character. This would lead to an infinite number
        of possible matches and the matcher would soon run out of memory. An example would
        be (x?)+ */
    re_errComp_potentiallyEmptyBodyOfLoop,      /* 3 */

    /** Not all of the characters of the regular expression form a valid expression. There
        is at least one trailing character, which can't be interpreted by the compiler. An
        ordinary syntax error can be the reason, e.g., a closing parenthesis if there were
        no opening pendant. */
    re_errComp_notAllInputConsumed,             /* 4 */

    /** For the compiler should be run on an embedded system it has a protection against
        too many stack consuming recursions. The actual maximum is user specified. Very
        complex expressions, typically with many nested levels of parenthesis, can fail to
        compile becaused more recursion levels as allowed would be needed. */
    re_errComp_maxRecursionDepthExceeded,       /* 5 */

    /** The empty string has been passed in as regular expression. */
    re_errComp_emptyRegularExpr,                /* 6 */

    /** Syntax error: The compiler has no interpretation for the next character of the
        regular expression being compiled. */
    re_errComp_unspecifiedSyntaxErr,            /* 7 */

    /** The compiler uses some user provided, pre-allocated memory space for the compiled
        regular expression. This error code is returned if that memory should be too
        little. */
    re_errComp_maxLenIStreamExceeded,           /* 8 */

    /** The compiler uses some pre-allocated memory space for temporary storage of
        information about half-way compiled OR expressions. This error code is returned if
        that memory should be too little. See #MAX_NO_OR_OPERANDS for a related
        configuration item. */
    re_errComp_maxNoOrAlternativesExceeded,     /* 9 */

    /** Bounded loop using the repetition operator {n,m} have some constraints. Among more,
        n must not exceed m, m must not exceed 255. If these constraints are hurt or if n
        or m can't be properly parsed, then this error code is returned. The most probable
        reason is the use of blanks, which is not permitted; n and m are both one to three
        digits but nothing else. */
    re_errComp_repBadNumberOrOutOfRange,        /* 10 */

    /** After successful parsing of {n of a repetition operator, the compiler fails to read
        either a comma or the immediately closing brace. The most probable reason is the use
        of blanks, which is not permitted. */
    re_errComp_repBadSeparatorOrMissingRBrace,  /* 11 */

    /** After successful parsing of {n,m of a repetition operator, the compiler fails to
        read the closing brace. The most probable reason is the use of blanks, which is
        not permitted. */
    re_errComp_repMissingRBrace,                /* 12 */

    /** It is generally not allowed to have more than 255 loops in a regular expression.
        This eror code is returned if the limit should be exceeded. */
    re_errComp_maxNoLoopsExceeded,              /* 13 */

    /** It is generally not allowed to have more than 255 capture groups in a regular
        expression. This eror code is returned if the limit should be exceeded. */
    re_errComp_maxNoCaptureGroupsExceeded,      /* 14 */

    /** A special character c can be brought into the regular expression for ordinary,
        immediate match by putting \c into the regular expression. However, the escape
        character back-slash cannot be used with any character. This error code is emitted
        if it is found to be combined with an unexpected character. Mostly, the back-slash
        is simply superfluous in this case. */
    re_errComp_invalidEscape,                   /* 15 */

    /** The compiler uses some user provided, pre-allocated memory space for temporary
        storage of information about half-way compiled character ranges. This error code is
        returned if that memory should be too little. */
    re_errComp_charSetMaxNoSetsExceeded,        /* 16 */

    /** Syntax error: The compiler fails to read the closing rectangular bracket, while
        parsing a character range. */
    re_errComp_charSetMissingRParen,            /* 17 */

    /** A character range contains the construct x-y, but character x has a character code
        greater or equal than character y. */
    re_errComp_charSetBadRange,                 /* 18 */
};

/** The regular expression compiler. The object contains a combination of configuration
    and runtime data. The user has to prepare the use of the compiler object by
    specifying the pre-allocated memory areas for the compilation. The runtime data is
    initialized and maintained by the compiler code. */
struct re_compiler_t
{
    /** The compiled regular expression is build up in this field. After compilation, the
        resulting compiled regular expression is fetched from here by the user.\n
          This field should be evaluated by the user after compilation. Most typical, it'll
        be passed on to the matcher for matching the regular expression to some input
        character strings.
          @caution This field contains the nested field \a iStream, which is one of the
        user configured memory areas. Prior to calling the compiler the first time, the
        user has to set that field to a caller provided memory area of sufficient size. It
        is not changed during the run of the compiler. The other field \a maxLenIStream
        specifies the size of the provided memory. */
    struct re_compiledRegExp_t re;

    /** The size of the user provided memory space for compilation, i.e., the number of
        bytes in \a re.iStream.\n
          This is a user configured field, to be set prior to using the compiler the first
        time. It is not changed during the run of the compiler. */
    unsigned int maxLenIStream;

    /** The input character stream with the regular expression to compile. Actually a
        zero terminated C string. */
    const char *cStream;

    /** The read position in the input stream. */
    const char *pC;

    /** The next loop ID to be used during compilation. */
    unsigned int nextIdxLoop;

    /** User provided memory for temporary storage of character set instructions. May be
        NULL if at the same time \a charSetMem is NULL, \a maxNoICharSet is zero and \a
        maxNoCharSets is zero. If NULL then any regular expression using at least one
        character set will make the compilation fail.\n
          This is a user configured field, to be set prior to using the compiler the first
        time. It is not changed during the run of the compiler.\n
          The required number of words in the array should be chosen in the magnitude of
        the expected number of character sets in the compiled regular expression(s). It is
        configured in the other field \a maxNoICharSet. */
    uint16_t *idxICharSetAry;

    /** The current number of instructions stored in \a idxICharSetAry. */
    unsigned int noICharSet;

    /** The capacity of \a idxICharSetAry, i.e., the number of words, which can be stored
        in the array. At the same time the maximum number of character sets, which may be
        used in the regular expression.\n
          This is a user configured field, to be set prior to using the compiler the first
        time. It is not changed during the run of the compiler. */
    unsigned int maxNoICharSet;

    /** User provided memory for temporary storage of the character sets. May be
        NULL if at the same time \a idxICharSetAry is NULL, \a maxNoICharSet is zero and \a
        maxNoCharSets is zero. If NULL then any regular expression using at least one
        character set will make the compilation fail.\n
          This is a user configured field, to be set prior to using the compiler the first
        time. It is not changed during the run of the compiler.\n
          The size in Byte of the user provided memory area is \a maxNoCharSets *
        sizeof(re_charSet_t).\n
          Note, there is no alignment constraint for the address of the provided memory. */
    uint8_t *charSetMem;

    /** The capacity of \a charSetMem, i.e., the number of character sets, which fit into
        the user provided memory. (The size in Byte of \a charSetMem is
        sizeof(re_charSet_t) times greater.) At the same time the maximum number of
        different character sets, which may be used in the regular expression.\n
          This is a user configured field, to be set prior to using the compiler the first
        time. It is not changed during the run of the compiler. */
    unsigned int maxNoCharSets;

    /** The current recursion depth of the compilation process. It is needed as the user
        can limit the maximum depth in order to avoid excessive memory consumption in case
        of a pathologic regular expression. */
    unsigned int recursionDepth;

    /** After compilation, this field holds the recursion depth actually required for the
        given regular expression. This field should be evaluated by the user after
        compilation. */
    unsigned int maxRecursionDepth;

    /** The maximum allowed recursion depth. Regular expressions requiring a higher value
        would make the compilation fail. */
    unsigned int maxAllowedRecursionDepth;

    /** Principal state information of the compiler: Still successful? Or an error message
        otherwise. This field should be evaluated by the user after compilation. */
    enum re_compilerError_t err;
};


/*
 * Global data declarations
 */


/*
 * Global prototypes
 */

#if RE_REQUIRE_COMPILER == 1
/** Write ohne or more instructions to the instruction stream. */
void re_compEmitCode( struct re_compiler_t *pCompiler
                    , const uint8_t *code
                    , unsigned int noBytes
                    );

/** Compile a regular expression. */
bool re_compile( struct re_compiler_t * const pCompiler
               , const char *regExpAsString
               , bool matchAnywhere
               , unsigned int maxAllowedRecursionDepth
               );
#endif

#if RE_REQUIRE_MAIN == 1
/** Run demo application with compiler and matcher. */
int main(int noArgs, const char * const *pArgStr);
#endif


/*
 * Global inline functions
 */


#endif  /* RE_REGEXP_COMPILER_INCLUDED */
