/**
 * @file suc_startup.c
 * Funktions from the startup procedure, which can be implemented in C instead of assembler
 * are collected in this file.\n
 *   Note, the code found here is not executed under the normal boundary conditions. It is
 * called prior to the entry into main() and before global data and the C run time
 * libraries are initialized or C++ constructors are executed. Therefore, the
 * implementation must not make use of these facilities.
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
 *   suc_initializeRam
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

#include "typ_types.h"
#include "suc_startup.h"


/*
 * Defines
 */
 

/*
 * Local type definitions
 */
 
 
/*
 * Local prototypes
 */

/** The table of RAM blocks to initialize is defined in terms of objects of this type. */
typedef struct ramBlockDesc_t
{
    /** The pointer to the RAM block to be initialized. The pointer value shall be 4 Byte
        aligned. The pointer is NULL in the last entry of the table. */
    uint32_t *pRamBlock;
    
    /** The pointer to the ROM area, which contains the needed initial RAM block contents.
        The pointer value shall be 4 Byte aligned. The value is undefined in the last table
        entry. */
    const uint32_t *pRomMirror;
    
    /** The size of the RAM block in Byte. The value is 0 the last table entry. */
    uint32_t sizeOfRamBlock;

} ramBlockDesc_t;


/*
 * Data definitions
 */
 
/** The table of pointers to RAM blocks, which need to be initialized, is not defined
    anywhere in the source files but generated by the linker. We reference it here as an
    external symbol. */
extern const ramBlockDesc_t ld_initializedRamBlockAry[];


/*
 * Function implementation
 */

/**
 * Fill the initialized RAM area with the initial data contents. The linker creates a ROM
 * section for each initialized RAM section, which contains the wanted initial contents.
 * This function reads a table of RAM block descriptors and copies the data from ROM to RAM.
 */
void suc_initializeRam(void)
{
    /* This macro supports safe implementation of the RAM initialization in C. It double
       checks if the binary build-up of the used C structures match with the linker
       generated data. */
    _Static_assert( sizeof(ramBlockDesc_t) == 12  &&  offsetof(ramBlockDesc_t, pRamBlock) == 0
                    &&  offsetof(ramBlockDesc_t, pRomMirror) == 4
                    &&  offsetof(ramBlockDesc_t, sizeOfRamBlock) == 8
                  , "Consistency check between C code and linker script failed"
                  );
    
    const ramBlockDesc_t *pRamBlkDesc = &ld_initializedRamBlockAry[0];
    while(pRamBlkDesc->pRamBlock != NULL)
    {
        uint32_t *pDest = pRamBlkDesc->pRamBlock;
        const uint32_t *pSrc = pRamBlkDesc->pRomMirror;
        unsigned int u = pRamBlkDesc->sizeOfRamBlock;

        /* The simple copy routine here imposes some alignment constraints. */
        assert(((uintptr_t)pDest & (_Alignof(uint32_t)-1)) == 0
               &&  ((uintptr_t)pSrc & (_Alignof(uint32_t)-1)) == 0
               &&  u % sizeof(uint32_t) == 0
              );
              
        /* Rescale no Byte to no words. */
        u /= sizeof(uint32_t);

        while(u-- > 0)
        {
            *pDest = *pSrc;
            ++ pDest;
            ++ pSrc;

        } /* while(All words of the RAM block) */

        /* Next RAM block. */
        ++ pRamBlkDesc;

    } /* While(All RAM blocks) */
} /* End of suc_initializeRam */




