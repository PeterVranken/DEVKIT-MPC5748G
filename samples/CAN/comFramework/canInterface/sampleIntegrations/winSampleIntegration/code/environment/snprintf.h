#ifndef SNPRINTF_INCLUDED
#define SNPRINTF_INCLUDED
/**
 * @file snprintf.h
 * Definition of global interface of module snprintf.c
 *
 * Copyright (C) 2014-2016 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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
/* Module interface
 *   snprintf_patchMinGW64
 */

/*
 * Include files
 */

#include <stdio.h>
#include <stdarg.h>


/*
 * Defines
 */

/* Find out if we have a revision of GCC, which requires a patch of snprintf. */
#if defined(__GNUC__)                                                                       \
    && (defined(__MINGW64__)                                                                \
        ||  __GNUC__ == 5  &&  __GNUC_MINOR__ == 3  &&  __GNUC_PATCHLEVEL__ == 0            \
        ||  __GNUC__ == 8  &&  __GNUC_MINOR__ == 1  &&  __GNUC_PATCHLEVEL__ == 0            \
       )
# define DO_PATCH_SNPRINTF
#endif

#ifdef DO_PATCH_SNPRINTF
/** Overload orignal, buggy function snprintf with patched function. */
# define snprintf snprintf_patchMinGW64
#endif


/*
 * Global type definitions
 */


/*
 * Global data declarations
 */


/*
 * Global inline interface
 */


#ifdef DO_PATCH_SNPRINTF
/**
 * The built-in version of snprintf in GCC MinGW 4.8.1 does not work correctly. It fails to
 * terminate a truncated string with the null character. Instead of writing \a n-1
 * characters plus the null termination it writes the first \a n characters. Consequently,
 * the caller sees the wrong result string, probably being longer than the permitted buffer
 * length \a n.\n
 *   This patched function first calls the invalid built-in (actually the also invalid
 * derivate vsnprintf) and then it unconditionally writes a null character into the very
 * last buffer place. This is not what a correct implementation of snprintf is expected to
 * do but it has the same behavior if the return value is not evaluated in the respect of a
 * guaranteed number of untouched characters at the buffer end.\n
 *   The correct handling of the return value has not been investigated in detail as it is
 * irrelevant for the given application. However, we had the impression that the return
 * value of the built-in function is also incorrect in the respect of returning -1 in case
 * of truncated output.
 *   @return
 * The return value of the built-in vsnprintf is returned by the patched function. This
 * value is probably not what's documented for snprintf (see above).
 *   @param string
 * The result string, which is always null terminated, if only \a bufSize is greater than
 * null. Pass a buffer, which has room for at least \a bufSize characters.
 *   @param bufSize
 * The maximum number of written characters, including the terminating null character.
 *   @param formatString
 * The printf style format string.
 *   @param ...
 * The variable argument list to satisfy all formatting characters in \a formatString.
 */ 

static inline signed int snprintf_patchMinGW64( char * __restrict__ string
                                              , size_t bufSize
                                              , const char * __restrict__ formatString
                                              , ...
                                              )
{
    signed int retVal;
    if(bufSize > 0)
    {
        va_list argptr;
        va_start(argptr, formatString);
        retVal = vsnprintf(string, bufSize, formatString, argptr);
        
        /* The Windows MinGw port of GCC doesn't write a terminating null character at the
           end of the string. Add it now. */
        *(string+bufSize-1) = '\0';

        va_end(argptr);
    }
    else
        retVal = 0;
    
    return retVal;
    
} /* End of snprintf_patchMinGW64 */

#undef DO_PATCH_SNPRINTF
#endif



/*
 * Global prototypes
 */



#endif  /* SNPRINTF_INCLUDED */
