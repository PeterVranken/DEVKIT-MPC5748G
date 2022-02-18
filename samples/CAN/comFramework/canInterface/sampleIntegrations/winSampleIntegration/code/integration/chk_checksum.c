/**
 * @file chk_checksum.c
 * Some basic checksum and seqeunce counter related routines. No great importance has been
 * attached to the checksum computation as such - we chose for the most simple arithmetic
 * sum -; what's important here only is the way the integration process will add a checksum
 * computation to the project, how it interfaces with the auto-generated code and how it
 * relates to the frame properties in the CAN database. In practice you would probably
 * replace the computation with a more sophisticated CRC algorithm.
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
/* Module interface
 *   chk_validateSequenceCounter
 *   chk_updateSequenceCounter
 *   chk_validateChecksum
 *   chk_computeChecksum
 * Local functions
 */

/*
 * Include files
 */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "chk_checksum.h"


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


/**
 * Validation of sequence of reception of frame. The sequence counter in the frame is
 * tested against its preceeding value. Sequence counters up to eight Bit are supported,
 * which are held in a single byte.
 *   @return 
 * \a true, if validation succeeded or was inhibited, else \a in case of a sequence error.
 *   @param sqc
 * The received sequence counter value, which is compared against the previously received
 * value. 
 *   @param pSqcLast
 * The previously received sequence counter value by reference. It is updated as part of
 * the function operation. The caller will use a static variable for this one.
 *   @param from
 * The start value of a cycle of the counter. Normally a cyclically incrementing seqeunce
 * counter is assumed but if \a from is larger than \a to then the counter is expected to
 * decrement cyclically.
 *   @param to
 * The end value of a cycle of the counter.
 *   @param reinitSQCValidation
 * If we would unconditionally compare the sequence counter with the last recently
 * received value we would see unwanted sequence error artefacts always after any other
 * error, which inibited the decoding of the predecessors's sequence counter values. If there
 * were those errors, the caller should pass \a true to restart the sequence counter
 * validation rather than getting a validation result immediately in this tic. The same
 * holds for the very first call of this function for a given frame after system startup.
 */

bool chk_validateSequenceCounter( uint8_t sqc
                                , uint8_t *pSqcLast
                                , unsigned int from
                                , unsigned int to
                                , bool reinitSQCValidation
                                )
{
    bool sqcOk;
    if(!reinitSQCValidation)
    {
        if(from < to)
        {
            sqcOk =(*pSqcLast < to  &&  sqc == *pSqcLast+1)
                   || (*pSqcLast == to  &&  sqc == from);
        }
        else if(to < from)
        {
            sqcOk = (*pSqcLast > to  &&  sqc == *pSqcLast-1)
                    || (*pSqcLast == to  &&  sqc == from);
        }
        else
            sqcOk = sqc == from;
    }
    else
        sqcOk = true;
        
    /* Update the state variable. */
    *pSqcLast = sqc;

    return sqcOk;
    
} /* End of chk_validateSequenceCounter */





/**
 * Update the sequence counter. In this sample environment we support cyclic counters in
 * either up- or down direction.
 *   @param pCnt
 * The update is done by reference to an eight Bit counter.
 *   @param from
 * The start value of a cycle of the counter. If \a from is larger than \a to then the
 * counter is cyclically decremented.
 *   @param to
 * The end value of a cycle of the counter.
 */

void chk_updateSequenceCounter(uint8_t *pCnt, unsigned int from, unsigned int to)
{
    /* Update the sequence counter. */
    if(from < to)
    {
        if(*pCnt < to)
            ++ *pCnt;
        else
            *pCnt = from;
    }
    else
    {
        if(*pCnt > to)
           -- *pCnt;
        else
           *pCnt = from;
    }
} /* End of chk_updateSequenceCounter */





/**
 * Validate whether the checksum found as one byte of a chunk of data matches against all
 * the rest of the chunk. The routine implements a simple arithmetic sum as checksum.
 *   @return
 * \a true, if checksum matches, else \a false.
 *   @param pData
 * The pointer to the data chunk.
 *   @param sizeOfData
 * The number of bytes ofthe data chunk.
 *   @param idxChecksumByte
 * The checksum needs to be an entire byte of the data chunk. Pass the index of this byte.
 *   @param startValue
 * The checksum computation is determined by the start value, which is chosen individually
 * for different data chunks in order to detect unwanted mistaking of data chunks.
 */

bool chk_validateChecksum( const void *pData
                         , unsigned int sizeOfData
                         , unsigned int idxChecksumByte ATTRIB_DBG_ONLY
                         , uint8_t startValue
                         )
{
    /* By definition, the checksum of a null chunk is okay. */
    if(sizeOfData == 0)
        return true;

    assert(idxChecksumByte < sizeOfData);

    /* Our checksum is defined such that the 8 Bit sum of all bytes including the checksum
       byte is equal to 255. */
    unsigned int u;
    uint8_t sum = startValue;
    const uint8_t *p = (const uint8_t*)pData;
    for(u=0; u<sizeOfData; ++u)
        sum += * p++;

    return sum == 255;

} /* End of chk_validateChecksum */




/**
 * Compute the one Byte checksum for a chunk of data. The routine implements a simple
 * arithmetic sum as checksum.
 *   @param pData
 * The pointer to the data chunk. The checksum byte doesn't care before entry into this
 * function and is written by this function.
 *   @param sizeOfData
 * The number of bytes of the data chunk.
 *   @param idxChecksumByte
 * The checksum needs to be an entire byte of the data chunk. Pass the index of this byte.
 *   @param startValue
 * The checksum computation is determined by the start value, which is chosen individually
 * for different data chunks in order to detect unwanted mistaking of data chunks.
 */

void chk_computeChecksum( void *pData
                        , unsigned int sizeOfData
                        , unsigned int idxChecksumByte
                        , uint8_t startValue
                        )
{
    /* The checksum of a null chunk is undefined, no operation. */
    if(sizeOfData == 0)
        return;

    assert(idxChecksumByte < sizeOfData);

    /* Our checksum is defined such that the 8 Bit sum of all bytes including the checksum
       byte is equal to 255. */
    unsigned int u;
    uint8_t checksum = 255;
    ((char*)pData)[idxChecksumByte] = startValue;
    const uint8_t *p = (const uint8_t*)pData;
    for(u=0; u<sizeOfData; ++u)
        checksum -= * p++;
    ((char*)pData)[idxChecksumByte] = checksum;
    assert(chk_validateChecksum(pData, sizeOfData, idxChecksumByte, startValue));

} /* End of chk_computeChecksum */




