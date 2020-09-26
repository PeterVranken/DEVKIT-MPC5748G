#ifndef CDR_SEARCHIFLAG_INCLUDED
#define CDR_SEARCHIFLAG_INCLUDED
/**
 * @file cdr_searchIFlag.h
 * Definition of global interface of module cdr_searchIFlag.c
 *
 * Copyright (C) 2020 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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


/*
 * Global type definitions
 */


/*
 * Global data declarations
 */


/*
 * Global prototypes
 */

/** Find the least (most) significant asserted bit in a binary word. */
unsigned int cdr_findAssertedBitInWord(const uint32_t word, const unsigned int width);


/*
 * Global inline functions
 */


#endif  /* CDR_SEARCHIFLAG_INCLUDED */
