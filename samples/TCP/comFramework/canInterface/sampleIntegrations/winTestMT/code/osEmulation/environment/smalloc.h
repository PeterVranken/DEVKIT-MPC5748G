#ifndef SMALLOC_INCLUDED
#define SMALLOC_INCLUDED
/**
 * @file smalloc.h
 * Definition of inline function smalloc (safe malloc).
 *
 * Copyright (C) 2013 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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
 *   smalloc
 *   stralloccpy
 * Local functions
 */

/*
 * Include files
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


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
 * Inline function implementations
 */

/**
 * Safe malloc: The return value NULL of malloc can't be handled at all but safe abortion
 * of this (nearly neglectible improbable) situation is a minimum requirement. This
 * function does the same as malloc does but aborts the application in case of "no memory"
 * with a (developer) hint where the problem occurs.
 *   @return
 * The pointer to the allocated memory is returned.
 *   @param noBytes
 * The number of requested bytes
 *   @param fileName
 * The name of the source file, where the function is used. Simply pass the macro __FILE__.
 *   @param line
 * The source code line number, where smalloc is called. Simply pass the macro __LINE__.
 */ 

static inline void *smalloc(size_t noBytes, const char * const fileName, unsigned long line)
{
    void *pMem = malloc(noBytes);    
    if(pMem == NULL)
    {
        fprintf( stderr
               , "malloc: Out of memory in %s, line %lu. Application is aborted\n"
               , fileName
               , line
               );
        exit(-1);
    }    
    
    return pMem;

} /* End of smalloc */




/**
 * Copy a string into a newly allocated chunk of memory. Unavailability of memory is
 * handled by error message and application abort, see void *smalloc(size_t, const char *
 * const, unsigned long) for details.
 *   @return
 * The malloc allocate memory chunk, which is initialized with a copy of the passed string,
 * is returned. Use void free(void*) to free the memeory after use.
 *   @param str
 * The string to copy.
 */ 

static inline char *stralloccpy(const char * const str)
{
    char * const strNew = smalloc(strlen(str)+1, __FILE__, __LINE__);
    strcpy(strNew, str);
    return strNew;
    
} /* End of stralloccpy */




/*
 * Global prototypes
 */




#endif  /* SMALLOC_INCLUDED */
