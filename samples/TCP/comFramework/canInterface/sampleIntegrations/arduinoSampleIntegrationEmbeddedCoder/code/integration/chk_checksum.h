#ifndef CHK_CHECKSUM_INCLUDED
#define CHK_CHECKSUM_INCLUDED
/**
 * @file chk_checksum.h
 * Definition of global interface of module chk_checksum.c
 *
 * Copyright (C) 2015 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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

#include "types.h"


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

/** Update a sequence counter. */
void chk_updateSequenceCounter(uint8_t *pCnt, uint8_t from, uint8_t to);

/** Validation of sequence of reception of frame. */
boolean_t chk_validateSequenceCounter( uint8_t sqc
                                     , uint8_t *pSqcLast
                                     , uint8_t from
                                     , uint8_t to
                                     , boolean_t reinitSQCValidation
                                     );

/** Validate the checksum of a checksum protected chunk of data. */
boolean_t chk_validateChecksum( const void *pData
                              , uint8_t sizeOfData
                              , uint8_t idxChecksumByte
                              , uint8_t startValue
                              );

/** Compute the one Byte checksum for a chunk of data. */
void chk_computeChecksum( void *pData
                        , uint8_t sizeOfData
                        , uint8_t idxChecksumByte
                        , uint8_t startValue
                        );

#endif  /* CHK_CHECKSUM_INCLUDED */
