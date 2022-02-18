#ifndef ASW_APSW_INCLUDED
#define ASW_APSW_INCLUDED
/**
 * @file asw_APSW.h
 * Definition of global interface of module asw_APSW.c
 *
 * Copyright (C) 2017-2022 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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

#include "cdt_canDataTables.h"

/*
 * Defines
 */

/* The software is written as portable as reasonably possible. This requires the awareness
   of the C language standard it is compiled with. */
#if defined(__STDC_VERSION__)
# if (__STDC_VERSION__)/100 == 2011
#  define _STDC_VERSION_C11
# elif (__STDC_VERSION__)/100 == 1999
#  define _STDC_VERSION_C99
# endif
#endif


/*
 * Global type definitions
 */


/*
 * Global data declarations
 */


/*
 * Global prototypes
 */

/** Associate a CAN message with the appropriate task to process its content data. */
unsigned int asw_getAssociatedTaskOfMessage(const cdt_canFrame_t *pFrDescCde);

/** This function imitates the behavior of a regular APSW task with 10ms cycle time. */
void asw_taskApsw_10ms();

/** This function imitates the behavior of a regular APSW task with 100ms cycle time. */
void asw_taskApsw_100ms();


#endif  /* ASW_APSW_INCLUDED */
