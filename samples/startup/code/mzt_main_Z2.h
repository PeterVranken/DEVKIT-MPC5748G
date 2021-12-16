#ifndef MZT_MAIN_Z2_INCLUDED
#define MZT_MAIN_Z2_INCLUDED
/**
 * @file mzt_main_Z2.h
 * Definition of global interface of module mzt_main_Z2.c
 *
 * Copyright (C) 2018 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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
#include <math.h>

#include "mtx_mutex.h"

/*
 * Defines
 */


/*
 * Global type definitions
 */

/** Test data container for mutex test. Contains some fields with redundant data, which
    have to be updated in an atomic fashion in order to avoid inconsistencies. */
typedef struct mzt_dataMutexTest_t 
{
    /** Cycle counters for successful access to the shared object, per core. */
    unsigned long long cntCore0Success, cntCore1Success, cntCore2Success;
    
    /** Total access count, needs to be same as sum of core related counts. */
    unsigned long long totalCntSuccess;
    
} mzt_dataMutexTest_t ;


/*
 * Global data declarations
 */

/** Counter, which is incremented in forever spinning main function. */
extern uint32_t mzt_cntMainLoopsCore2;

/** A mutex to share some test data container between all cores. */
extern mtx_nestedMutex_t mzt_mtxDataMutexTest;

/** Test data container for mutex test. Note, this object needs to reside in uncached
    memory. */
extern volatile mzt_dataMutexTest_t mzt_dataMutexTest;


/*
 * Global prototypes
 */

/** Interrupt handler that serves the interrupt of Programmable Interrupt Timer 4. */
void mzt_interruptPIT4Handler(void);

/** C entry function for Z2 core. */
void mzt_main_Z2(signed int noArgs, const char *argAry[]);


#endif  /* MZT_MAIN_Z2_INCLUDED */
