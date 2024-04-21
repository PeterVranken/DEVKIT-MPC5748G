#ifndef RE_CHARSET_INCLUDED
#define RE_CHARSET_INCLUDED
/**
 * @file re_charSet.h
 * Definition of global interface of module re_charSet.c
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
#include <stdio.h>

#include "re_regExpMatcher.h"

#if RE_REQUIRE_COMPILER == 1
# include "re_regExpCompiler.h"
#endif

/*
 * Defines
 */


/*
 * Global type definitions
 */

/** The compiler-internal representation of a character set. */
typedef uint8_t re_charSet_t[(UINT8_MAX+1)/8u];


/*
 * Global data declarations
 */


/*
 * Global prototypes
 */

#if RE_REQUIRE_COMPILER == 1
/** Read an unsigned integer number from the input stream. Two hex digits are expected. */
bool re_compileHexByte(struct re_compiler_t *pCompiler, uint8_t *pC);

/** Parse a character set in the input stream. */
bool re_compileCharSet(struct re_compiler_t *pCompiler);

/** Notify a move of some already compiled code, which may require relocation. */
void re_onInstructionMove( struct re_compiler_t *pCompiler
                         , unsigned int idxIFrom
                         , unsigned int distance
                         );

/** Push all compiled char sets into the final instruction stream and relocate references. */
void re_writeCharSets(struct re_compiler_t *pCompiler);
#endif

#if RE_REQUIRE_MAIN == 1
/** Display all data bytes of a character set in a compiled regular expression. */
void re_printCharSetBinary( FILE *ostream
                          , const struct re_compiledRegExp_t * const pRe
                          , unsigned int idxCS
                          , unsigned int firstAddr
                          , bool asCCode
                          );
#endif

#if RE_REQUIRE_MATCHER == 1
/** Check for a character if it is in the character set. */
bool re_isCharInCharSet(const re_charSet_t charSet, uint8_t c);
#endif

/*
 * Global inline functions
 */


#endif  /* RE_CHARSET_INCLUDED */
