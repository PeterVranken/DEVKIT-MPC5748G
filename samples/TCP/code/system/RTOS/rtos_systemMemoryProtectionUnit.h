#ifndef RTOS_SYSTEMMEMORYPROTECTIONUNIT_INCLUDED
#define RTOS_SYSTEMMEMORYPROTECTIONUNIT_INCLUDED
/**
 * @file rtos_systemMemoryProtectionUnit.h
 * Definition of global interface of module rtos_systemMemoryProtectionUnit.c
 *
 * Copyright (C) 2018-2019 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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

/*
 * Include files
 */


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

/** Configure and initialize the memory protection unit, MPU. */
void rtos_osInitMPU(void);

/** Check is a pointer value is valid for writing in the context of a given process. */
bool rtos_checkUserCodeWritePtr(unsigned int PID, const void *address, size_t noBytes);


/*
 * Global static inline functions
 */


#endif  /* RTOS_SYSTEMMEMORYPROTECTIONUNIT_INCLUDED */
