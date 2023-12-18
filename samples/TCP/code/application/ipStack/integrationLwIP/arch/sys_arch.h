#ifndef SYS_ARCH_INCLUDED
#define SYS_ARCH_INCLUDED
/**
 * @file sys_arch.h
 * Definition of global interface of module sys_arch.c
 *
 * Copyright (C) 2023 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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

#include "lwip/arch.h"


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

/** Initialize sys arch layer. */
void sys_init(void);

/** Tick counter with unspecified resolution. */
u32_t sys_jiffies(void);

/** Returns the current time (since power-up) in Milliseconds. */
u32_t sys_now(void);


/*
 * Global inline functions
 */


#endif  /* SYS_ARCH_INCLUDED */
