#ifndef F2D_FLOAT2DOUBLE_INCLUDED
#define F2D_FLOAT2DOUBLE_INCLUDED
/**
 * @file f2d_float2Double.h
 * Declaration of global assembler function f2d, which converts a floating point value into
 * a true 64 Bit double, despite of compilation switch -fshort-double. This function is
 * required to wrap floating point arguments of printf, which would otherwise be provided
 * as 32 Bit arguments: Our calling code uses -fshort-double but the called code (printf
 * itself) has not been compiled with this switch.
 *   @remark
 * Using f2d is possible only due to a faked return code type. (Honestly specifying double
 * would again lead to a 32 Bit processing of it due to -fshort-double.) The purposely
 * wrong return type makes GCC emit a warning for each printf with floating point
 * formatting characters. By inclusion of this header this normally very helpful warning is
 * turned off! So don't include this file if it is not really required.
 *
 * Copyright (C) 2017 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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


/*
 * Defines
 */


/*
 * Global type definitions
 */


/*
 * Global data declarations
 */


/*
 * Global prototypes
 */

/** Convert a float into a true 64 Bit double, despite of compile switch -fshort-double.
    Can be used to wrap floating point arguments of printf in such code, which is compiled
    using switch -fshort-double.
      @remark Note, the intentionally bad specification of the return value. The
    specification of a 64 Bit integer hinders the compiler to mutilate the returned
    double. */
extern int64_t /* double */ f2d(float f);

/* The purposely used wrong return type of f2d will make the compiler emit ugly warnings
   about a wrong argument type. We switch this warning off here; if, in a given compilation
   unit, you don't want to use floating point output with printf, then you will not require
   this header and should not include it in that compilation unit to let the warning be
   enabled for all other use of printf. */
#pragma GCC diagnostic ignored "-Wformat"

#endif  /* F2D_FLOAT2DOUBLE_INCLUDED */
