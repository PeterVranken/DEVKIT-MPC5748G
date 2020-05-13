#ifndef TYP_TYPES_INCLUDED
#define TYP_TYPES_INCLUDED
/**
 * @file typ_types.h
 * Definition of global, basic types and convenience macros.
 *
 * Copyright (C) 2013-2020 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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

#ifdef __GNUC__

/** Intentionally unused objects in the C code can be marked using this define. A compiler
    warning is avoided. */
# define ATTRIB_UNUSED __attribute__((unused))

# ifdef NDEBUG
/** Objects in the C code intentionally unused in the production compilation can be marked
    using this define. A compiler warning is avoided. */
#  define ATTRIB_DBG_ONLY ATTRIB_UNUSED
# else
/** Objects in the C code intentionally unused in the production compilation can be marked
    using this define. A compiler warning is avoided. */
#  define ATTRIB_DBG_ONLY
# endif

/** Sometimes inlining functions is counterproductive, e.g. where we need function pointers
    in interfaces. This macro can hinder the compiler from inlining (static) functions. */
# define NO_INLINE __attribute__((noinline))

/** Some function may better be inlined even if the optimizer rates code size higher and
    wouldn't therefore inline it. */
# define ALWAYS_INLINE inline __attribute__((always_inline))

/** Place a piece of code or data objects into a sepcific linker section. */
# define SECTION(sectionName)  __attribute__((section (#sectionName)))

/** This abbreviating macro can be used to make the definition of simple, uninitialized
    data objects, which need to be located in the operating system memory, put e.g. "int
    BSS_OS(x);" instead of the more explicit "int x SECTION(.bss.OS.x);" into your source
    code.\n
      The macro cannot be applied to more complex definitions, e.g. with struct types or
    function pointers. */
# define BSS_OS(var)     SECTION(.bss.OS.var) var

/** Helper for definition of simple, OS owned, initialized data objects. See #BSS_OS for
    details. */
# define DATA_OS(var)    SECTION(.data.OS.var) var

/** Helper for definition of simple, OS owned, initialized data objects with short
    addressing mode. See #BSS_OS for details. */
# define SBSS_OS(var)    SECTION(.sbss.OS.var) var

/** Helper for definition of simple, OS owned, initialized data objects with short
    addressing mode. See #BSS_OS for details. */
# define SDATA_OS(var)   SECTION(.sdata.OS.var) var

/** Helper for definition of simple, process P1 owned, uninitialized data objects. See
    #BSS_OS for details. */
# define BSS_P1(var)     SECTION(.bss.P1.var) var

/** Helper for definition of simple, process P1 owned, initialized data objects. See
    #BSS_OS for details. */
# define DATA_P1(var)    SECTION(.data.P1.var) var

/** Helper for definition of simple, process P1 owned, initialized data objects with short
    addressing mode. See #BSS_OS for details. */
# define SBSS_P1(var)    SECTION(.sbss.P1.var) var

/** Helper for definition of simple, process P1 owned, initialized data objects with short
    addressing mode. See #BSS_OS for details. */
# define SDATA_P1(var)   SECTION(.sdata.P1.var) var

/** Helper for definition of simple, process P2 owned, uninitialized data objects. See
    #BSS_OS for details. */
# define BSS_P2(var)     SECTION(.bss.P2.var) var

/** Helper for definition of simple, process P2 owned, initialized data objects. See
    #BSS_OS for details. */
# define DATA_P2(var)    SECTION(.data.P2.var) var

/** Helper for definition of simple, process P2 owned, initialized data objects with short
    addressing mode. See #BSS_OS for details. */
# define SBSS_P2(var)    SECTION(.sbss.P2.var) var

/** Helper for definition of simple, process P2 owned, initialized data objects with short
    addressing mode. See #BSS_OS for details. */
# define SDATA_P2(var)   SECTION(.sdata.P2.var) var

/** Helper for definition of simple, process P3 owned, uninitialized data objects. See
    #BSS_OS for details. */
# define BSS_P3(var)     SECTION(.bss.P3.var) var

/** Helper for definition of simple, process P3 owned, initialized data objects. See
    #BSS_OS for details. */
# define DATA_P3(var)    SECTION(.data.P3.var) var

/** Helper for definition of simple, process P3 owned, initialized data objects with short
    addressing mode. See #BSS_OS for details. */
# define SBSS_P3(var)    SECTION(.sbss.P3.var) var

/** Helper for definition of simple, process P3 owned, initialized data objects with short
    addressing mode. See #BSS_OS for details. */
# define SDATA_P3(var)   SECTION(.sdata.P3.var) var

/** Helper for definition of simple, process P4 owned, uninitialized data objects. See
    #BSS_OS for details. */
# define BSS_P4(var)     SECTION(.bss.P4.var) var

/** Helper for definition of simple, process P4 owned, initialized data objects. See
    #BSS_OS for details. */
# define DATA_P4(var)    SECTION(.data.P4.var) var

/** Helper for definition of simple, process P4 owned, initialized data objects with short
    addressing mode. See #BSS_OS for details. */
# define SBSS_P4(var)    SECTION(.sbss.P4.var) var

/** Helper for definition of simple, process P4 owned, initialized data objects with short
    addressing mode. See #BSS_OS for details. */
# define SDATA_P4(var)   SECTION(.sdata.P4.var) var

/** Helper for definition of simple, shared, uninitialized data objects. See
    #BSS_OS for details. */
# define BSS_SHARED(var) SECTION(.bss.Shared.var) var

/** Helper for definition of simple, process P4 owned, initialized data objects. See
    #BSS_OS for details. */
# define DATA_SHARED(var)   SECTION(.data.Shared.var) var

#else
# error Configuration is required for your compiler
#endif

/** The number of elements of a one dimensional array. */
#define sizeOfAry(a)    (sizeof(a)/sizeof(a[0]))

/** Companion of C's offsetof: The size of a field inside a struct. */
#define sizeoffield(type, fieldName) (sizeof(((type*)0)->fieldName))

/** Support of uintX_t types, X=8, 16, 32: Get the implementation maximum of such a
    variable. */
#define UINT_T_MAX(var) ((uint32_t)((1ull<<(sizeof(var)*8u))-1ull))

/** Support of intX_t types, X=8, 16, 32: Get the implementation maximum of such a
    variable. */
#define INT_T_MAX(var)  ((int32_t)((1ul<<((sizeof(var)*8u)-1u))-1ul))

/** Support of intX_t types, X=8, 16, 32: Get the implementation minimum of such a
    variable. */
#define INT_T_MIN(var)  ((int32_t)(1ul<<((sizeof(var)*8u)-1u)))


/*
 * Global type definitions
 */

/* Some more basic types are defined using the naming scheme of stdint.h. */

/** 4 Byte, single precision floating point number type. */
typedef float float32_t;

/** 8 Byte, double precision floating point number type. */
typedef double float64_t;


/*
 * Global data declarations
 */


/*
 * Global prototypes
 */



#endif  /* TYP_TYPES_INCLUDED */
