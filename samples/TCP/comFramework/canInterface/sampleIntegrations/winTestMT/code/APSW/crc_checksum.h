#ifndef CRC_CHECKSUM_INCLUDED
#define CRC_CHECKSUM_INCLUDED
/**
 * @file crc_checksum.h
 * Definition of global interface of module crc_checksum.c
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

/*
 * Include files
 */

#include "stdint.h"


/*
 * Defines
 */

/** The check value of the CRC checksum. See uint8_t crc_checksumSAEJ1850_8Bit(const
    void *, unsigned int) for details. */
#define CRC_SAE_J1850_8BIT_CHECK_VALUE (0x3b)

/** The magic number of the CRC checksum. See uint8_t crc_checksumSAEJ1850_8Bit(const
    void *, unsigned int) for details. */
#define CRC_SAE_J1850_8BIT_MAGIC_NUMBER (0xc4)


/*
 * Global type definitions
 */


/*
 * Global data declarations
 */


/*
 * Global prototypes
 */

/** Compute the 8 Bit checksum according to SAE J1850. */
uint8_t crc_checksumSAEJ1850_8Bit(const void *pByteSequence, unsigned int noBytes);


#endif  /* CRC_CHECKSUM_INCLUDED */
