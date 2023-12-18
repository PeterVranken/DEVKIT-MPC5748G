#ifndef TYPES_INCLUDED
#define TYPES_INCLUDED
/**
 * @file types.h
 * Definition of primitive base types as used in the generated code. This file is part of
 * the sample but it is not generated. It serves as an example of such a basic header,
 * which is probably found in all embedded environments, where auto-generated sources files
 * are integrated.\n
 *   There's one specific issue with this file. The definition of the Boolean type needs to
 * resolve into an unsigned integer (as usual). The code generator handles signals of all
 * target types - including Boolean - uniquely by masking and shifting. Therefore, it'll
 * generate shift operations on Booleans, which is unacceptable for the abstract concept of
 * a Boolean but technically alright as long as the rule above is obeyed.
 *
 * Copyright (C) 2015 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

/*
 * Include files
 */


/*
 * Defines
 */


/*
 * Global type definitions
 */

/** The definition of the Boolean type.
      @remark The primitive Boolean type needs to resolve into an unsigned integer. The
    code generator handles signals of all target types - including Boolean - uniquely by
    masking and shifting. Therefore, it'll generate shift operations on Booleans, which
    technically alright as long as this rule is obeyed. */
typedef unsigned char Bool;

typedef unsigned char UInt8;
typedef unsigned short UInt16;
typedef unsigned long UInt32;
typedef unsigned long long UInt64;
typedef signed char Int8;
typedef signed short Int16;
typedef signed long Int32;
typedef signed long long Int64;
typedef float Float32;
typedef double Float64;


/*
 * Global data declarations
 */


/*
 * Global prototypes
 */



#endif  /* TYPES_INCLUDED */
