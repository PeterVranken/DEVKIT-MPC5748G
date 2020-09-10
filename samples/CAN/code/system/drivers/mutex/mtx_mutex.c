/**
 * @file mtx_mutex.c
 * Implementation of basic mutex and semphore functions for MPC5748G and MPC5744P and all
 * other family members, which provide the Decorated Memory Storage Controller for their
 * RAM.
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
/* Module interface
 * Local functions
 */

/*
 * Include files
 */

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "std_decoratedStorage.h"
#include "mtx_mutex.h"


/*
 * Defines
 */
 

/*
 * Local type definitions
 */
 
 
/*
 * Local prototypes
 */
 
 
/*
 * Data definitions
 */
 
 
/*
 * Function implementation
 */


#if 0
/* Sketch of semaphore implementation using decorated CAST operation. The problem arises
   from the fact that the success of the swap operation is not reported. We need to read
   back to see. To distinguish our store from those with same value by another core we need
   to limit the value range and to spend the other bits for ownership of a value:
     In the sketch the semaphore value range is 5 Bit, 0..31. Mask is 0x1f.
     Bit 7, 0x80 means value is owned by core 0.
     Bit 6, 0x40 means value is owned by core 1.
     Bit 5, 0x20 means value is owned by core 2.
     The new value is written together with an ownership bit. This can be done at once in
   an atomic fashion. A core will not change a value explicitly owned by another core and
   this makes it possible to do the read-back and further manipulations without the
   atomicity, i.e. harmful interference of another core. In order to not block the entire
   process, the last step - when all decisions are taken - is to deletion of the ownership
   bit.
     @remark Since this is a busy-wait non-atomic implementation (i.e. busy wait for access
   to the semaphore not for the availability of the protected resources) it must not be
   used without another core-local critical section, e.g. suspend all interrupts. Otherwise
   either another core needs to await the completion of unrelated local scheduling
   activities or we can run destroy the counter value because of competing accesses to the
   semaphore from contexts preempting one other on the local core.
     @remark Effectively the proposed implementation is a combination of a core-selective
   mutex and a counter. Using the normal mutex and a normal shared-memory variable for
   counting would be just the same. No need to implement this sketch. */
    extern uint8_t semaphore; /* Shared variable between the tree cores. */
    const unsigned int maskSemValue = 0x1f
                     , maskCore0 = 0x80
                     , maskCore1 = 0x40
                     , maskCore2 = 0x20;
    const unsigned int maskThisCore = maskCore0; /* In this sketch we assume being core 0. */
    enum {busy, noResourceAvailable, resourceSuccessfullyAcquired} result = busy;
    do
    {
        /* Read current value of semphore. The ownership can now be ignored; if it is set
           then only temporarily for a few clock ticks. We can do our preparatory steps in
           parallel to another core completing its action. */
        uint32_t semTmp = std_loadByteAtomic(&semaphore) & maskSemValue;
        if(semTmp > 0)
        {
            /* We will try to write the decremented value back. This can fail because:
                 - A temporarily set ownership has not been cleared yet
                 - Another core has meanwhile successfuly changed the semaphore */
            std_cmpAndStoreByteAtomic( /* writeData */ (semTmp-1) | maskThisCore
                                     , /* cmpData */ semTmp
                                     , /* Address */ &semaphore
                                     );
            -- semTmp;
            
            /* Get success by reading and comparing. Although this is not atomic with the
               store a harmful misinterpretation is impossible due to the ownership flag,
               which is never set by another core (convention). */
            if(std_loadByteAtomic(&semaphore) == semTmp | maskThisCore)
            {
                /* Semaphore successfully accessed, resource acquired. */
                result = resourceSuccessfullyAcquired;

                /* Now we clear the ownership. No core will alter the semaphore as long as
                   the ownership flag of another core is set. Therefore we can safely reset
                   the flag with an operation, which is not atomic with the preceding
                   ones. */ 
                std_storeByteAtomic(semTmp, &semaphore);

                /* We are done. */
            }
            else
            {
                /* The attempt to access the semphore failed due to simulataneous access by
                   another core. We need to start over. */
                assert(result == busy);
            }
        }
        else
        {
            /* All resources are currently in use. This function does not block until one
               gets free. The situation is reported by result value. */
            result = noResourceAvailable;
            
            /* We are done. */
        }
    }
    while(result == busy);
    
#endif




