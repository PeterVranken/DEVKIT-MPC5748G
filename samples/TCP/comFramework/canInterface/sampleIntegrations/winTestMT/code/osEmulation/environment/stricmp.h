#ifndef STRICMP_INCLUDED
#define STRICMP_INCLUDED
/**
 * @file stricmp.h
 *   Implementation of stricmp for environments, which do not provide this standard
 * function.
 *
 * Copyright (C) 2014 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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
 *   stricmp
 */

/*
 * Include files
 */

#include <string.h>
#include <ctype.h>
#include "types.h"


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
 * Global inline interface
 */

#if defined(__GNUC__) &&                                                            \
    (__GNUC__ == 4  &&  __GNUC_MINOR__ == 5  &&  __GNUC_PATCHLEVEL__ == 2           \
     ||  __GNUC__ == 5  &&  __GNUC_MINOR__ == 3  &&  __GNUC_PATCHLEVEL__ == 0       \
    )

/**
 * Case insensitive string compare.
 *   @return
 * The difference of the first differing pair of characters at the same position in the two
 * strings.
 *   @param a
 * First operand of the returned difference.
 *   @param b
 * Second operand of the returned difference.
 *   @remark
 * Based on http://stackoverflow.com/questions/5820810/case-insensitive-string-comp-in-c,
 * visited on Feb 1, 2014.
 */ 

static signed int stricmp(char const *a, char const *b)
{
    while(true)
    {
        signed int d = tolower(*a) - tolower(*b);
        if(d != 0 || *a == 0)
            return d;

        ++ a;
        ++ b;
    }
    
} /* End of stricmp */
#endif /* function not available in GCC 4.5.2 */



/*
 * Global prototypes
 */




#endif  /* STRICMP_INCLUDED */
