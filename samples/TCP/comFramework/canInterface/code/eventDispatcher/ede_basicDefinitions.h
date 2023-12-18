#ifndef EDE_BASICDEFINITIONS_INCLUDED
#define EDE_BASICDEFINITIONS_INCLUDED
/**
 * @file ede_basicDefinitions.h
 * Definition of basic data types and compiler dependent macros.
 *
 * Copyright (C) 2022 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>


/*
 * Defines
 */

/* The software is written as portable as possible. This requires the awareness of the C
   language standard it is compiled with - particularly the new stuff from the C11 standard
   strongly supports portability. (Effectively, not using C11 means that GCC will be
   required for a lower degree of portability.)
     If your environment supports C11 then you should use it and make this #define on the
   compiler's command line.
     With respect to the language feature C11 and C17 are identical. We combine the in one
   switch. */
#if defined(__STDC_VERSION__)
# if (__STDC_VERSION__)/100 == 2017
#  define _STDC_VERSION_C17
#  define _STDC_VERSION_C17_C11
# elif (__STDC_VERSION__)/100 == 2011
#  define _STDC_VERSION_C11
#  define _STDC_VERSION_C17_C11
# elif (__STDC_VERSION__)/100 == 1999
#  define _STDC_VERSION_C99
# endif
#endif

#if defined(__GNUC__) || defined(__arm__)

/** Intentionally unused objects in the C code can be marked using this define. A compiler
    warning is avoided. */
#define EDE_UNUSED __attribute__((unused))

#ifdef NDEBUG
/** Objects in the C code intentionally unused in the production compilation can be marked
    using this define. A compiler warning is avoided. */
# define EDE_DBG_ONLY EDE_UNUSED
#else
/** Objects in the C code intentionally unused in the production compilation can be marked
    using this define. A compiler warning is avoided. */
# define EDE_DBG_ONLY
#endif

#else
# define EDE_UNUSED
# define EDE_DBG_ONLY
#endif /* __GNUC__ */

/*
 * Global type definitions
 */


/*
 * Global data declarations
 */


/*
 * Global prototypes
 */



/*
 * Global inline functions
 */


#endif  /* EDE_BASICDEFINITIONS_INCLUDED */
