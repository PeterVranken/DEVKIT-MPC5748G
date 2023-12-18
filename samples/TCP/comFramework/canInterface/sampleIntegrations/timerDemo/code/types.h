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

/*
 * Defines
 */

/// @todo find solution
#define ATTRIB_UNUSED __attribute__((unused))
#ifdef DEBUG
# define ATTRIB_DBG_ONLY
#else
# define ATTRIB_DBG_ONLY    ATTRIB_UNUSED
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



#endif  /* TYPES_INCLUDED */
