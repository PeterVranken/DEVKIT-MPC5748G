#ifndef RTOS_CONFIG_DEFSYSCALLS_INCLUDED
#define RTOS_CONFIG_DEFSYSCALLS_INCLUDED
/**
 * @file rtos_config_defSysCalls.h
 * This file lists includes all header files with system call table entries, which are
 * added to the system call table by the various I/O drivers.\n
 *   This file is included by rtos_systemCall.c in order to build the system call table
 * at compilation time.
 * 
 * @note This file must not contain anything other than the include directives of all
 * system call defining header files.
 *
 * Copyright (C) 2021-2023 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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
 * System call include files
 */

#include "stm_systemTimer_defSysCalls.h"
#include "lbd_ledAndButtonDriver_defSysCalls.h"
#include "sio_serialIO_defSysCalls.h"
#include "cdr_canDriver_defSysCalls.h"
#include "pwm_pwmIODriver_defSysCalls.h"
#include "cdr_queuedSending_defSysCalls.h"
#include "eth_ethernet_defSysCalls.h"

#endif  /* RTOS_CONFIG_DEFSYSCALLS_INCLUDED */
