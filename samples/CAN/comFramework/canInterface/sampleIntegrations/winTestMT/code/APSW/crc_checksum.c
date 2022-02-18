/**
 * @file crc_checksum.c
 * Computation of 8 Bit checksum according to SAE J1850
 *
 * Copyright (C) 2016 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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
 *   crc_checksumSAEJ1850_8Bit
 *   main
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

#include "crc_checksum.h"


/*
 * Defines
 */
 
/** A selfcontained test application can be compiled from this module if this define is
    made. Comment it out for normal use of the source file. */
//#define COMPILE_TEST


/*
 * Local type definitions
 */
 
 
/*
 * Local prototypes
 */
 
 
/*
 * Data definitions
 */
 

static const uint8_t _dataTableSAEJ1850[256] =
    { 0x00, 0x1d, 0x3a, 0x27, 0x74, 0x69, 0x4e, 0x53, 0xe8, 0xf5, 0xd2, 0xcf, 0x9c, 0x81
    , 0xa6, 0xbb, 0xcd, 0xd0, 0xf7, 0xea, 0xb9, 0xa4, 0x83, 0x9e, 0x25, 0x38, 0x1f, 0x02
    , 0x51, 0x4c, 0x6b, 0x76, 0x87, 0x9a, 0xbd, 0xa0, 0xf3, 0xee, 0xc9, 0xd4, 0x6f, 0x72
    , 0x55, 0x48, 0x1b, 0x06, 0x21, 0x3c, 0x4a, 0x57, 0x70, 0x6d, 0x3e, 0x23, 0x04, 0x19
    , 0xa2, 0xbf, 0x98, 0x85, 0xd6, 0xcb, 0xec, 0xf1, 0x13, 0x0e, 0x29, 0x34, 0x67, 0x7a
    , 0x5d, 0x40, 0xfb, 0xe6, 0xc1, 0xdc, 0x8f, 0x92, 0xb5, 0xa8, 0xde, 0xc3, 0xe4, 0xf9
    , 0xaa, 0xb7, 0x90, 0x8d, 0x36, 0x2b, 0x0c, 0x11, 0x42, 0x5f, 0x78, 0x65, 0x94, 0x89
    , 0xae, 0xb3, 0xe0, 0xfd, 0xda, 0xc7, 0x7c, 0x61, 0x46, 0x5b, 0x08, 0x15, 0x32, 0x2f
    , 0x59, 0x44, 0x63, 0x7e, 0x2d, 0x30, 0x17, 0x0a, 0xb1, 0xac, 0x8b, 0x96, 0xc5, 0xd8
    , 0xff, 0xe2, 0x26, 0x3b, 0x1c, 0x01, 0x52, 0x4f, 0x68, 0x75, 0xce, 0xd3, 0xf4, 0xe9
    , 0xba, 0xa7, 0x80, 0x9d, 0xeb, 0xf6, 0xd1, 0xcc, 0x9f, 0x82, 0xa5, 0xb8, 0x03, 0x1e
    , 0x39, 0x24, 0x77, 0x6a, 0x4d, 0x50, 0xa1, 0xbc, 0x9b, 0x86, 0xd5, 0xc8, 0xef, 0xf2
    , 0x49, 0x54, 0x73, 0x6e, 0x3d, 0x20, 0x07, 0x1a, 0x6c, 0x71, 0x56, 0x4b, 0x18, 0x05
    , 0x22, 0x3f, 0x84, 0x99, 0xbe, 0xa3, 0xf0, 0xed, 0xca, 0xd7, 0x35, 0x28, 0x0f, 0x12
    , 0x41, 0x5c, 0x7b, 0x66, 0xdd, 0xc0, 0xe7, 0xfa, 0xa9, 0xb4, 0x93, 0x8e, 0xf8, 0xe5
    , 0xc2, 0xdf, 0x8c, 0x91, 0xb6, 0xab, 0x10, 0x0d, 0x2a, 0x37, 0x64, 0x79, 0x5e, 0x43
    , 0xb2, 0xaf, 0x88, 0x95, 0xc6, 0xdb, 0xfc, 0xe1, 0x5a, 0x47, 0x60, 0x7d, 0x2e, 0x33
    , 0x14, 0x09, 0x7f, 0x62, 0x45, 0x58, 0x0b, 0x16, 0x31, 0x2c, 0x97, 0x8a, 0xad, 0xb0
    , 0xe3, 0xfe, 0xd9, 0xc4
    };
 
/*
 * Function implementation
 */

/**
 * Compute the 8 Bit checksum according to SAE J1850. The checksum is computed by feeding
 * the CRC algorithm byte by byte.
 *   @return
 * Get the CRC of the sequence. For protection, the returned checkum should be appended to
 * the sequence as an additional byte prior to submitting the sequence. For validation of a
 * sequence with appended checksum the function result should have the check value 0x3b.
 *   @param pByteSequence
 * The first byte of the protected bytes sequence by reference.
 *   @param noBytes
 * The length of the sequence.
 */

uint8_t crc_checksumSAEJ1850_8Bit(const void *pByteSequence, unsigned int noBytes)
{
    unsigned int crc = 0xff
               , u;
    const uint8_t *pByte = (const uint8_t*)pByteSequence;
    for(u=0; u<noBytes; ++u)
    {
        unsigned int idx = crc ^ *pByte;
        ++ pByte;
        assert(idx <= 255);
        crc = _dataTableSAEJ1850[idx];
    }
    
    crc ^= 0xff;
    assert(crc <= 256);    

    return (uint8_t)crc;
    
} /* End of crc_checksumSAEJ1850_8Bit */



#ifdef COMPILE_TEST
/**
 * Simple test function. Build it under Windows using:
 *   gcc -DDEBUG -DCOMPILE_TEST -o crcTest.exe crc_checksum.c
 * Linux users will omit the extension .exe.
 *   @return
 * Always 0. Any problem is reported by assertion. Therefore, only compile in DEBUG
 * configuration!
 */

int main()
{
    /* This example is taken from AUTOSAR, Specification of CRC Routines, V 4.2.0., p. 19 */
    uint8_t sequence[] = { 0, 0, 0, 0
                         , /* placeholder for crc */ 0
                         };
    #define LENGTH_OF_SEQUENCE  (sizeof(sequence)-1)
    #define IDX_OF_CRC          (sizeof(sequence)-1)
    
    sequence[IDX_OF_CRC] = crc_checksumSAEJ1850_8Bit(sequence, LENGTH_OF_SEQUENCE);
    printf("CRC is 0x%02x\n", (unsigned)sequence[IDX_OF_CRC]);
    
    assert(crc_checksumSAEJ1850_8Bit(sequence, LENGTH_OF_SEQUENCE+1) ^ 0xff
           == CRC_SAE_J1850_8BIT_MAGIC_NUMBER
          );
    assert(crc_checksumSAEJ1850_8Bit(sequence, LENGTH_OF_SEQUENCE+1)
           == CRC_SAE_J1850_8BIT_CHECK_VALUE
          );
    
    return 0;
    
    #undef LENGTH_OF_SEQUENCE
    #undef IDX_OF_CRC
} /* End of main */
#endif // COMPILE_TEST
