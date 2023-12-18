#ifndef TYPES_INCLUDED
#define TYPES_INCLUDED
/**
 * @file types.h
 * Definition of global, basic types.
 *
 * Copyright (C) 2013-2015 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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

#include "rtwtypes.h"

/*
 * Defines
 */

#ifdef __GNUC__

/** Intentionally unused objects in the C code can be marked using this define. A compiler
    warning is avoided. */
#define ATTRIB_UNUSED __attribute__((unused))

#ifdef NDEBUG
/** Objects in the C code intentionally unused in the production compilation can be marked
    using this define. A compiler warning is avoided. */
# define ATTRIB_DBG_ONLY ATTRIB_UNUSED
#else
/** Objects in the C code intentionally unused in the production compilation can be marked
    using this define. A compiler warning is avoided. */
# define ATTRIB_DBG_ONLY
#endif

#else
# define ATTRIB_UNUSED
# define ATTRIB_DBG_ONLY
#endif


/*
 * Global type definitions
 */

/* Most of the base types are already defined in rtwtypes.h */
# if 0
typedef bool bool_T;
typedef uint8_t uint8_T;
typedef int8_t int8_T;
typedef uint16_t uint16_T;
typedef int16_t int16_T;
typedef uint32_t uint32_T;
typedef int32_t int32_T;
#endif
typedef uint64_t uint64_T;
typedef int64_t int64_T;


/*
 * Global data declarations
 */


/*
 * Global prototypes
 */



#endif  /* TYPES_INCLUDED */
