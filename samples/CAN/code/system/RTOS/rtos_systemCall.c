/**
 * @file rtos_systemCall.c
 * Implementation of the system call table as a const data object in ROM. The information
 * about the table contents is taken from dedicated header files, named *_defSysCalls.h,
 * which have to be provided by all units that offer at least one system call.
 *
 * Copyright (C) 2019-2020 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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
/* Module interface
 *   rtos_osInitSystemCalls
 * Module inline interface
 * Local functions
 */

/*
 * Include files
 */

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <assert.h>

#include "typ_types.h"
#include "rtos.h"
#include "rtos_kernelInstanceData.h"
#include "rtos_systemCall.h"

/*
 * Include section for I/O driver header files.
 *   The header files, which are included here declare the system calls, which are
 * implemented by the I/O drivers. Using preprocessor constructs we check for multiple
 * definitions of the same system call and we can add missing ones.
 */
#include "assert_defSysCalls.h"
#include "rtos_ivorHandler_defSysCalls.h"
#include "rtos_priorityCeilingProtocol_defSysCalls.h"
#include "rtos_process_defSysCalls.h"
#include "rtos_runTask_defSysCalls.h"
#include "rtos_scheduler_defSysCalls.h"

/* The include directives of all system call headers from code, whichis external to the
   RTOS are collected in a globally accessible header file. The next include will add the
   system call table entries from all the I/O drivers. */
#include "rtos_config_defSysCalls.h"


/*
 * Defines
 */

/** This table entry is used for those system table entries, which are not defined by any
    included I/O driver header file. The dummy table entry points to a no-operation
    service, which silently returns to the caller. */
#define RTOS_SYSCALL_DUMMY_TABLE_ENTRY  \
                        RTOS_SC_TABLE_ENTRY(rtos_scBscHdlr_sysCallUndefined, BASIC)

/* The preprocessor code down here filters all system call table entries, which are not
   defined by any of the included I/O driver header files and makes them become the dummy
   entry #RTOS_SYSCALL_DUMMY_TABLE_ENTRY. */
#if RTOS_RUN_SAFE_RTOS_ON_CORE_0 == 1
# if !defined(RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0000)     \
     || !defined(RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0001)  \
     || !defined(RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0002)  \
     || !defined(RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0003)  \
     || !defined(RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0004)  \
     || !defined(RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0005)
#  error One of the kernels core system calls 0..5 has not been defined for core 0. \
         Please check your RTOS code
# endif
# ifndef RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0006
#  define RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0006    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0007
#  define RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0007    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0008
#  define RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0008    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0009
#  define RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0009    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0010
#  define RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0010    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0011
#  define RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0011    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0012
#  define RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0012    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0013
#  define RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0013    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0014
#  define RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0014    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0015
#  define RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0015    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0016
#  define RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0016    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0017
#  define RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0017    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0018
#  define RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0018    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0019
#  define RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0019    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0020
#  define RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0020    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0021
#  define RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0021    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0022
#  define RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0022    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0023
#  define RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0023    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0024
#  define RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0024    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0025
#  define RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0025    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0026
#  define RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0026    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0027
#  define RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0027    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0028
#  define RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0028    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0029
#  define RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0029    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0030
#  define RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0030    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0031
#  define RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0031    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0032
#  define RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0032    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0033
#  define RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0033    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0034
#  define RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0034    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0035
#  define RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0035    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0036
#  define RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0036    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0037
#  define RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0037    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0038
#  define RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0038    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0039
#  define RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0039    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0040
#  define RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0040    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0041
#  define RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0041    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0042
#  define RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0042    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0043
#  define RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0043    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0044
#  define RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0044    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0045
#  define RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0045    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0046
#  define RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0046    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0047
#  define RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0047    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0048
#  define RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0048    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0049
#  define RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0049    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0050
#  define RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0050    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0051
#  define RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0051    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0052
#  define RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0052    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0053
#  define RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0053    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0054
#  define RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0054    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0055
#  define RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0055    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0056
#  define RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0056    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0057
#  define RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0057    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0058
#  define RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0058    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0059
#  define RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0059    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0060
#  define RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0060    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0061
#  define RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0061    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0062
#  define RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0062    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0063
#  define RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0063    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
#endif /* RTOS is configured to run on core 0, Z4A */

#if RTOS_RUN_SAFE_RTOS_ON_CORE_1 == 1
# if !defined(RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0000)     \
     || !defined(RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0001)  \
     || !defined(RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0002)  \
     || !defined(RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0003)  \
     || !defined(RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0004)  \
     || !defined(RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0005)
#  error One of the kernels core system calls 0..5 has not been defined for core 1. \
         Please check your RTOS code
# endif
# ifndef RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0006
#  define RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0006    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0007
#  define RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0007    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0008
#  define RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0008    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0009
#  define RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0009    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0010
#  define RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0010    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0011
#  define RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0011    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0012
#  define RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0012    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0013
#  define RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0013    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0014
#  define RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0014    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0015
#  define RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0015    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0016
#  define RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0016    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0017
#  define RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0017    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0018
#  define RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0018    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0019
#  define RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0019    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0020
#  define RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0020    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0021
#  define RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0021    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0022
#  define RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0022    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0023
#  define RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0023    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0024
#  define RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0024    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0025
#  define RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0025    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0026
#  define RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0026    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0027
#  define RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0027    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0028
#  define RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0028    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0029
#  define RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0029    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0030
#  define RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0030    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0031
#  define RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0031    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0032
#  define RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0032    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0033
#  define RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0033    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0034
#  define RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0034    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0035
#  define RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0035    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0036
#  define RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0036    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0037
#  define RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0037    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0038
#  define RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0038    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0039
#  define RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0039    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0040
#  define RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0040    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0041
#  define RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0041    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0042
#  define RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0042    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0043
#  define RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0043    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0044
#  define RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0044    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0045
#  define RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0045    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0046
#  define RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0046    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0047
#  define RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0047    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0048
#  define RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0048    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0049
#  define RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0049    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0050
#  define RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0050    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0051
#  define RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0051    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0052
#  define RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0052    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0053
#  define RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0053    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0054
#  define RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0054    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0055
#  define RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0055    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0056
#  define RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0056    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0057
#  define RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0057    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0058
#  define RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0058    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0059
#  define RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0059    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0060
#  define RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0060    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0061
#  define RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0061    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0062
#  define RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0062    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0063
#  define RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0063    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
#endif /* RTOS is configured to run on core 0, Z4B */

#if RTOS_RUN_SAFE_RTOS_ON_CORE_2 == 1
# if !defined(RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0000)     \
     || !defined(RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0001)  \
     || !defined(RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0002)  \
     || !defined(RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0003)  \
     || !defined(RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0004)  \
     || !defined(RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0005)
#  error One of the kernels core system calls 0..5 has not been defined for core 2. \
         Please check your RTOS code
# endif
# ifndef RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0006
#  define RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0006    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0007
#  define RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0007    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0008
#  define RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0008    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0009
#  define RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0009    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0010
#  define RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0010    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0011
#  define RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0011    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0012
#  define RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0012    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0013
#  define RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0013    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0014
#  define RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0014    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0015
#  define RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0015    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0016
#  define RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0016    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0017
#  define RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0017    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0018
#  define RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0018    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0019
#  define RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0019    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0020
#  define RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0020    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0021
#  define RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0021    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0022
#  define RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0022    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0023
#  define RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0023    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0024
#  define RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0024    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0025
#  define RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0025    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0026
#  define RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0026    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0027
#  define RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0027    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0028
#  define RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0028    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0029
#  define RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0029    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0030
#  define RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0030    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0031
#  define RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0031    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0032
#  define RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0032    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0033
#  define RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0033    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0034
#  define RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0034    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0035
#  define RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0035    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0036
#  define RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0036    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0037
#  define RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0037    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0038
#  define RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0038    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0039
#  define RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0039    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0040
#  define RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0040    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0041
#  define RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0041    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0042
#  define RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0042    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0043
#  define RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0043    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0044
#  define RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0044    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0045
#  define RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0045    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0046
#  define RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0046    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0047
#  define RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0047    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0048
#  define RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0048    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0049
#  define RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0049    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0050
#  define RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0050    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0051
#  define RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0051    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0052
#  define RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0052    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0053
#  define RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0053    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0054
#  define RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0054    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0055
#  define RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0055    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0056
#  define RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0056    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0057
#  define RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0057    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0058
#  define RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0058    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0059
#  define RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0059    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0060
#  define RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0060    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0061
#  define RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0061    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0062
#  define RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0062    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
# ifndef RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0063
#  define RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0063    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
#endif /* RTOS is configured to run on core 2, Z2 */

/* Here we have a (weak) test for inconsistencies. */
#if defined(RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0064)
    || defined(RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0064)
    || defined(RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0064)
    || defined(RTOS_CORE_3_SYSCALL_TABLE_ENTRY_0000)
    ||  RTOS_NO_SYSTEM_CALLS != 64
# error The number of system calls has been inconsistently changed. Code maintenance \
        is required. See #RTOS_NO_SYSTEM_CALLS and definition of rtos_systemCallDescAry
#endif


/** Initializer expression for the data object that implements the system call table of a
    single core.\n
      Note, the initializer expression requires maintenance if the size
    #RTOS_NO_SYSTEM_CALLS of the system call table is changed */
#define SYS_CALL_TABLE_DATA(idxCore)                                    \
    {                                                                   \
        [0] = RTOS_CORE_##idxCore##_SYSCALL_TABLE_ENTRY_0000            \
        , [1] = RTOS_CORE_##idxCore##_SYSCALL_TABLE_ENTRY_0001          \
        , [2] = RTOS_CORE_##idxCore##_SYSCALL_TABLE_ENTRY_0002          \
        , [3] = RTOS_CORE_##idxCore##_SYSCALL_TABLE_ENTRY_0003          \
        , [4] = RTOS_CORE_##idxCore##_SYSCALL_TABLE_ENTRY_0004          \
        , [5] = RTOS_CORE_##idxCore##_SYSCALL_TABLE_ENTRY_0005          \
        , [6] = RTOS_CORE_##idxCore##_SYSCALL_TABLE_ENTRY_0006          \
        , [7] = RTOS_CORE_##idxCore##_SYSCALL_TABLE_ENTRY_0007          \
        , [8] = RTOS_CORE_##idxCore##_SYSCALL_TABLE_ENTRY_0008          \
        , [9] = RTOS_CORE_##idxCore##_SYSCALL_TABLE_ENTRY_0009          \
        , [10] = RTOS_CORE_##idxCore##_SYSCALL_TABLE_ENTRY_0010         \
        , [11] = RTOS_CORE_##idxCore##_SYSCALL_TABLE_ENTRY_0011         \
        , [12] = RTOS_CORE_##idxCore##_SYSCALL_TABLE_ENTRY_0012         \
        , [13] = RTOS_CORE_##idxCore##_SYSCALL_TABLE_ENTRY_0013         \
        , [14] = RTOS_CORE_##idxCore##_SYSCALL_TABLE_ENTRY_0014         \
        , [15] = RTOS_CORE_##idxCore##_SYSCALL_TABLE_ENTRY_0015         \
        , [16] = RTOS_CORE_##idxCore##_SYSCALL_TABLE_ENTRY_0016         \
        , [17] = RTOS_CORE_##idxCore##_SYSCALL_TABLE_ENTRY_0017         \
        , [18] = RTOS_CORE_##idxCore##_SYSCALL_TABLE_ENTRY_0018         \
        , [19] = RTOS_CORE_##idxCore##_SYSCALL_TABLE_ENTRY_0019         \
        , [20] = RTOS_CORE_##idxCore##_SYSCALL_TABLE_ENTRY_0020         \
        , [21] = RTOS_CORE_##idxCore##_SYSCALL_TABLE_ENTRY_0021         \
        , [22] = RTOS_CORE_##idxCore##_SYSCALL_TABLE_ENTRY_0022         \
        , [23] = RTOS_CORE_##idxCore##_SYSCALL_TABLE_ENTRY_0023         \
        , [24] = RTOS_CORE_##idxCore##_SYSCALL_TABLE_ENTRY_0024         \
        , [25] = RTOS_CORE_##idxCore##_SYSCALL_TABLE_ENTRY_0025         \
        , [26] = RTOS_CORE_##idxCore##_SYSCALL_TABLE_ENTRY_0026         \
        , [27] = RTOS_CORE_##idxCore##_SYSCALL_TABLE_ENTRY_0027         \
        , [28] = RTOS_CORE_##idxCore##_SYSCALL_TABLE_ENTRY_0028         \
        , [29] = RTOS_CORE_##idxCore##_SYSCALL_TABLE_ENTRY_0029         \
        , [30] = RTOS_CORE_##idxCore##_SYSCALL_TABLE_ENTRY_0030         \
        , [31] = RTOS_CORE_##idxCore##_SYSCALL_TABLE_ENTRY_0031         \
        , [32] = RTOS_CORE_##idxCore##_SYSCALL_TABLE_ENTRY_0032         \
        , [33] = RTOS_CORE_##idxCore##_SYSCALL_TABLE_ENTRY_0033         \
        , [34] = RTOS_CORE_##idxCore##_SYSCALL_TABLE_ENTRY_0034         \
        , [35] = RTOS_CORE_##idxCore##_SYSCALL_TABLE_ENTRY_0035         \
        , [36] = RTOS_CORE_##idxCore##_SYSCALL_TABLE_ENTRY_0036         \
        , [37] = RTOS_CORE_##idxCore##_SYSCALL_TABLE_ENTRY_0037         \
        , [38] = RTOS_CORE_##idxCore##_SYSCALL_TABLE_ENTRY_0038         \
        , [39] = RTOS_CORE_##idxCore##_SYSCALL_TABLE_ENTRY_0039         \
        , [40] = RTOS_CORE_##idxCore##_SYSCALL_TABLE_ENTRY_0040         \
        , [41] = RTOS_CORE_##idxCore##_SYSCALL_TABLE_ENTRY_0041         \
        , [42] = RTOS_CORE_##idxCore##_SYSCALL_TABLE_ENTRY_0042         \
        , [43] = RTOS_CORE_##idxCore##_SYSCALL_TABLE_ENTRY_0043         \
        , [44] = RTOS_CORE_##idxCore##_SYSCALL_TABLE_ENTRY_0044         \
        , [45] = RTOS_CORE_##idxCore##_SYSCALL_TABLE_ENTRY_0045         \
        , [46] = RTOS_CORE_##idxCore##_SYSCALL_TABLE_ENTRY_0046         \
        , [47] = RTOS_CORE_##idxCore##_SYSCALL_TABLE_ENTRY_0047         \
        , [48] = RTOS_CORE_##idxCore##_SYSCALL_TABLE_ENTRY_0048         \
        , [49] = RTOS_CORE_##idxCore##_SYSCALL_TABLE_ENTRY_0049         \
        , [50] = RTOS_CORE_##idxCore##_SYSCALL_TABLE_ENTRY_0050         \
        , [51] = RTOS_CORE_##idxCore##_SYSCALL_TABLE_ENTRY_0051         \
        , [52] = RTOS_CORE_##idxCore##_SYSCALL_TABLE_ENTRY_0052         \
        , [53] = RTOS_CORE_##idxCore##_SYSCALL_TABLE_ENTRY_0053         \
        , [54] = RTOS_CORE_##idxCore##_SYSCALL_TABLE_ENTRY_0054         \
        , [55] = RTOS_CORE_##idxCore##_SYSCALL_TABLE_ENTRY_0055         \
        , [56] = RTOS_CORE_##idxCore##_SYSCALL_TABLE_ENTRY_0056         \
        , [57] = RTOS_CORE_##idxCore##_SYSCALL_TABLE_ENTRY_0057         \
        , [58] = RTOS_CORE_##idxCore##_SYSCALL_TABLE_ENTRY_0058         \
        , [59] = RTOS_CORE_##idxCore##_SYSCALL_TABLE_ENTRY_0059         \
        , [60] = RTOS_CORE_##idxCore##_SYSCALL_TABLE_ENTRY_0060         \
        , [61] = RTOS_CORE_##idxCore##_SYSCALL_TABLE_ENTRY_0061         \
        , [62] = RTOS_CORE_##idxCore##_SYSCALL_TABLE_ENTRY_0062         \
        , [63] = RTOS_CORE_##idxCore##_SYSCALL_TABLE_ENTRY_0063         \
    }


/*
 * Local type definitions
 */


/*
 * Local prototypes
 */

/** The assembler implementation of the no operation dummy system call.\n
      Note, despite of the C style prototype, this is not a C callable function. The calling
    convention is different to C. This is the reason, why we declare it here instead of
    publishing it globally in rtos_ivorHandler.h. */
extern void rtos_scBscHdlr_sysCallUndefined(void);


/*
 * Data definitions
 */

#if RTOS_RUN_SAFE_RTOS_ON_CORE_0 == 1
/** The global, constant table of system call descriptors for core 0, Z4A.\n
      Note, the initializer expression requires maintenance if the size
    #RTOS_NO_SYSTEM_CALLS of the system call table is changed */
const rtos_systemCallDesc_t rtos_systemCallDescAry_core0[RTOS_NO_SYSTEM_CALLS]
        SECTION(.text.ivor.rtos_systemCallDesc_core0) = SYS_CALL_TABLE_DATA(/* idxCore */ 0);
#endif
#if RTOS_RUN_SAFE_RTOS_ON_CORE_1 == 1
/** The global, constant table of system call descriptors for core 1, Z4B.\n
      Note, the initializer expression requires maintenance if the size
    #RTOS_NO_SYSTEM_CALLS of the system call table is changed */
const rtos_systemCallDesc_t rtos_systemCallDescAry_core1[RTOS_NO_SYSTEM_CALLS]
        SECTION(.text.ivor.rtos_systemCallDesc_core1) = SYS_CALL_TABLE_DATA(/* idxCore */ 1);
#endif
#if RTOS_RUN_SAFE_RTOS_ON_CORE_2 == 1
/** The global, constant table of system call descriptors for core 2, Z2.\n
      Note, the initializer expression requires maintenance if the size
    #RTOS_NO_SYSTEM_CALLS of the system call table is changed */
const rtos_systemCallDesc_t rtos_systemCallDescAry_core2[RTOS_NO_SYSTEM_CALLS]
        SECTION(.text.ivor.rtos_systemCallDesc_core2) = SYS_CALL_TABLE_DATA(/* idxCore */ 2);
#endif


/*
 * Function implementation
 */

/**
 * Initialization of system call mechanism. It performs some consistency checks to early
 * catch typical user configuration errors and selects the right system call table for the
 * calling core.
 */
void rtos_osInitSystemCalls(void)
{
    /* The C code has an interface with the assembler code. It is used to exchange process
       and task related information. The interface is modeled twice, once as structs for C
       code and once as set of preprocessor macros, which hold size of data structures and
       offsets of fields. Here, we have macros, which support double-checking the
       equivalence of both definitions. The compiler will abort the compilation if there is
       a static inconsistency. A few more conditions require run-time checking. */
    assert(RTOS_CONSTRAINTS_INTERFACE_C_AS_SYS_CALL);
    _Static_assert( RTOS_STATIC_CONSTRAINTS_INTERFACE_C_AS_SYS_CALL
                  , "Interface check C to assembly failed for module rtos_rtos_ivorHandler.S"
                  );
    
    /* Install the pointer to this core's system call table in the RTOS instance data. */
    rtos_kernelInstanceData_t * const pIData = rtos_osGetInstancePtr();
    switch(rtos_osGetIdxCore())
    {
#if RTOS_RUN_SAFE_RTOS_ON_CORE_0 == 1
    case 0:
        pIData->systemCallDescAry = &rtos_systemCallDescAry_core0[0];
        break;
#endif        

#if RTOS_RUN_SAFE_RTOS_ON_CORE_1 == 1
    case 1:
        pIData->systemCallDescAry = &rtos_systemCallDescAry_core1[0];
        break;
#endif        

#if RTOS_RUN_SAFE_RTOS_ON_CORE_2 == 1
    case 2:
        pIData->systemCallDescAry = &rtos_systemCallDescAry_core2[0];
        break;
#endif        

    default:
        /* The caling core doesn't run the RTOS. The instance data pointer should be on
           default value. No action required. */
        assert(pIData == NULL);
        
        /* This function must not be called from a core not running the RTOS. */
        assert(false);
    }
} /* End of rtos_osInitSystemCalls */