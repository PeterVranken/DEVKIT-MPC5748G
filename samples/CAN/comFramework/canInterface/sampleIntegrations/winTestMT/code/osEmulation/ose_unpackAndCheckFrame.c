/**
 * @file ose_unpackAndCheckFrame.c
 * 
 * This module contains the set of functions for the end-to-end validation of the CAN
 * frames. A CRC checking function is generated for each CAN frame.
 *
 * This file has been created with comFramework - codeGenerator version 1.10.6,
 * see http://sourceforge.net/projects/comframe/
 *
 * Copyright (C) 2022 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "types.h"
#include "cap_canApi.h"
#include "e2e_frameProtection.h"
#include "ose_unpackAndCheckFrame.h"


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
 * Do unpacking and E2E validation of frame frame_x2044.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B1_frame_x2044_x2044(const uint8_t frameContent[4])
{
    /* Unpack the data locally. */
    cap_B1_frame_x2044_x2044_t frameStructLocal;
    cap_unpack_B1_frame_x2044_x2044(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B1_frame_x2044_x2044(&frameStructLocal);

} /* End of ose_unpackAndCheck_B1_frame_x2044_x2044 */


/**
 * Do unpacking and E2E validation of frame frame_1049.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B1_frame_1049_1049(const uint8_t frameContent[7])
{
    /* Unpack the data locally. */
    cap_B1_frame_1049_1049_t frameStructLocal;
    cap_unpack_B1_frame_1049_1049(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B1_frame_1049_1049(&frameStructLocal);

} /* End of ose_unpackAndCheck_B1_frame_1049_1049 */


/**
 * Do unpacking and E2E validation of frame frame_1834.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B1_frame_1834_1834(const uint8_t frameContent[6])
{
    /* Unpack the data locally. */
    cap_B1_frame_1834_1834_t frameStructLocal;
    cap_unpack_B1_frame_1834_1834(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B1_frame_1834_1834(&frameStructLocal);

} /* End of ose_unpackAndCheck_B1_frame_1834_1834 */


/**
 * Do unpacking and E2E validation of frame frame_1053.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B1_frame_1053_1053(const uint8_t frameContent[7])
{
    /* Unpack the data locally. */
    cap_B1_frame_1053_1053_t frameStructLocal;
    cap_unpack_B1_frame_1053_1053(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B1_frame_1053_1053(&frameStructLocal);

} /* End of ose_unpackAndCheck_B1_frame_1053_1053 */


/**
 * Do unpacking and E2E validation of frame frame_693.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B1_frame_693_693(const uint8_t frameContent[8])
{
    /* Unpack the data locally. */
    cap_B1_frame_693_693_t frameStructLocal;
    cap_unpack_B1_frame_693_693(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B1_frame_693_693(&frameStructLocal);

} /* End of ose_unpackAndCheck_B1_frame_693_693 */


/**
 * Do unpacking and E2E validation of frame frame_1143.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B1_frame_1143_1143(const uint8_t frameContent[5])
{
    /* Unpack the data locally. */
    cap_B1_frame_1143_1143_t frameStructLocal;
    cap_unpack_B1_frame_1143_1143(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B1_frame_1143_1143(&frameStructLocal);

} /* End of ose_unpackAndCheck_B1_frame_1143_1143 */


/**
 * Do unpacking and E2E validation of frame frame_453.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B1_frame_453_453(const uint8_t frameContent[6])
{
    /* Unpack the data locally. */
    cap_B1_frame_453_453_t frameStructLocal;
    cap_unpack_B1_frame_453_453(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B1_frame_453_453(&frameStructLocal);

} /* End of ose_unpackAndCheck_B1_frame_453_453 */


/**
 * Do unpacking and E2E validation of frame frame_403.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B1_frame_403_403(const uint8_t frameContent[8])
{
    /* Unpack the data locally. */
    cap_B1_frame_403_403_t frameStructLocal;
    cap_unpack_B1_frame_403_403(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B1_frame_403_403(&frameStructLocal);

} /* End of ose_unpackAndCheck_B1_frame_403_403 */


/**
 * Do unpacking and E2E validation of frame frame_766.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B1_frame_766_766(const uint8_t frameContent[7])
{
    /* Unpack the data locally. */
    cap_B1_frame_766_766_t frameStructLocal;
    cap_unpack_B1_frame_766_766(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B1_frame_766_766(&frameStructLocal);

} /* End of ose_unpackAndCheck_B1_frame_766_766 */


/**
 * Do unpacking and E2E validation of frame frame_1271.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B1_frame_1271_1271(const uint8_t frameContent[6])
{
    /* Unpack the data locally. */
    cap_B1_frame_1271_1271_t frameStructLocal;
    cap_unpack_B1_frame_1271_1271(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B1_frame_1271_1271(&frameStructLocal);

} /* End of ose_unpackAndCheck_B1_frame_1271_1271 */


/**
 * Do unpacking and E2E validation of frame frame_332.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B1_frame_332_332(const uint8_t frameContent[5])
{
    /* Unpack the data locally. */
    cap_B1_frame_332_332_t frameStructLocal;
    cap_unpack_B1_frame_332_332(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B1_frame_332_332(&frameStructLocal);

} /* End of ose_unpackAndCheck_B1_frame_332_332 */


/**
 * Do unpacking and E2E validation of frame frame_602.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B1_frame_602_602(const uint8_t frameContent[7])
{
    /* Unpack the data locally. */
    cap_B1_frame_602_602_t frameStructLocal;
    cap_unpack_B1_frame_602_602(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B1_frame_602_602(&frameStructLocal);

} /* End of ose_unpackAndCheck_B1_frame_602_602 */


/**
 * Do unpacking and E2E validation of frame frame_1605.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B1_frame_1605_1605(const uint8_t frameContent[7])
{
    /* Unpack the data locally. */
    cap_B1_frame_1605_1605_t frameStructLocal;
    cap_unpack_B1_frame_1605_1605(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B1_frame_1605_1605(&frameStructLocal);

} /* End of ose_unpackAndCheck_B1_frame_1605_1605 */


/**
 * Do unpacking and E2E validation of frame frame_1731.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B1_frame_1731_1731(const uint8_t frameContent[8])
{
    /* Unpack the data locally. */
    cap_B1_frame_1731_1731_t frameStructLocal;
    cap_unpack_B1_frame_1731_1731(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B1_frame_1731_1731(&frameStructLocal);

} /* End of ose_unpackAndCheck_B1_frame_1731_1731 */


/**
 * Do unpacking and E2E validation of frame frame_1529.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B1_frame_1529_1529(const uint8_t frameContent[7])
{
    /* Unpack the data locally. */
    cap_B1_frame_1529_1529_t frameStructLocal;
    cap_unpack_B1_frame_1529_1529(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B1_frame_1529_1529(&frameStructLocal);

} /* End of ose_unpackAndCheck_B1_frame_1529_1529 */


/**
 * Do unpacking and E2E validation of frame frame_808.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B1_frame_808_808(const uint8_t frameContent[6])
{
    /* Unpack the data locally. */
    cap_B1_frame_808_808_t frameStructLocal;
    cap_unpack_B1_frame_808_808(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B1_frame_808_808(&frameStructLocal);

} /* End of ose_unpackAndCheck_B1_frame_808_808 */


/**
 * Do unpacking and E2E validation of frame frame_1181.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B1_frame_1181_1181(const uint8_t frameContent[6])
{
    /* Unpack the data locally. */
    cap_B1_frame_1181_1181_t frameStructLocal;
    cap_unpack_B1_frame_1181_1181(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B1_frame_1181_1181(&frameStructLocal);

} /* End of ose_unpackAndCheck_B1_frame_1181_1181 */


/**
 * Do unpacking and E2E validation of frame frame_1725.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B1_frame_1725_1725(const uint8_t frameContent[6])
{
    /* Unpack the data locally. */
    cap_B1_frame_1725_1725_t frameStructLocal;
    cap_unpack_B1_frame_1725_1725(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B1_frame_1725_1725(&frameStructLocal);

} /* End of ose_unpackAndCheck_B1_frame_1725_1725 */


/**
 * Do unpacking and E2E validation of frame frame_208.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B1_frame_208_208(const uint8_t frameContent[6])
{
    /* Unpack the data locally. */
    cap_B1_frame_208_208_t frameStructLocal;
    cap_unpack_B1_frame_208_208(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B1_frame_208_208(&frameStructLocal);

} /* End of ose_unpackAndCheck_B1_frame_208_208 */


/**
 * Do unpacking and E2E validation of frame frame_2047.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B1_frame_2047_2047(const uint8_t frameContent[8])
{
    /* Unpack the data locally. */
    cap_B1_frame_2047_2047_t frameStructLocal;
    cap_unpack_B1_frame_2047_2047(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B1_frame_2047_2047(&frameStructLocal);

} /* End of ose_unpackAndCheck_B1_frame_2047_2047 */


/**
 * Do unpacking and E2E validation of frame frame_590.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B1_frame_590_590(const uint8_t frameContent[7])
{
    /* Unpack the data locally. */
    cap_B1_frame_590_590_t frameStructLocal;
    cap_unpack_B1_frame_590_590(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B1_frame_590_590(&frameStructLocal);

} /* End of ose_unpackAndCheck_B1_frame_590_590 */


/**
 * Do unpacking and E2E validation of frame frame_1419.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B1_frame_1419_1419(const uint8_t frameContent[6])
{
    /* Unpack the data locally. */
    cap_B1_frame_1419_1419_t frameStructLocal;
    cap_unpack_B1_frame_1419_1419(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B1_frame_1419_1419(&frameStructLocal);

} /* End of ose_unpackAndCheck_B1_frame_1419_1419 */


/**
 * Do unpacking and E2E validation of frame frame_x0.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B1_frame_x0_x0(const uint8_t frameContent[7])
{
    /* Unpack the data locally. */
    cap_B1_frame_x0_x0_t frameStructLocal;
    cap_unpack_B1_frame_x0_x0(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B1_frame_x0_x0(&frameStructLocal);

} /* End of ose_unpackAndCheck_B1_frame_x0_x0 */


/**
 * Do unpacking and E2E validation of frame frame_1630.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B1_frame_1630_1630(const uint8_t frameContent[7])
{
    /* Unpack the data locally. */
    cap_B1_frame_1630_1630_t frameStructLocal;
    cap_unpack_B1_frame_1630_1630(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B1_frame_1630_1630(&frameStructLocal);

} /* End of ose_unpackAndCheck_B1_frame_1630_1630 */


/**
 * Do unpacking and E2E validation of frame frame_1033.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B1_frame_1033_1033(const uint8_t frameContent[5])
{
    /* Unpack the data locally. */
    cap_B1_frame_1033_1033_t frameStructLocal;
    cap_unpack_B1_frame_1033_1033(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B1_frame_1033_1033(&frameStructLocal);

} /* End of ose_unpackAndCheck_B1_frame_1033_1033 */


/**
 * Do unpacking and E2E validation of frame frame_803.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B1_frame_803_803(const uint8_t frameContent[4])
{
    /* Unpack the data locally. */
    cap_B1_frame_803_803_t frameStructLocal;
    cap_unpack_B1_frame_803_803(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B1_frame_803_803(&frameStructLocal);

} /* End of ose_unpackAndCheck_B1_frame_803_803 */


/**
 * Do unpacking and E2E validation of frame frame_106.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B1_frame_106_106(const uint8_t frameContent[5])
{
    /* Unpack the data locally. */
    cap_B1_frame_106_106_t frameStructLocal;
    cap_unpack_B1_frame_106_106(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B1_frame_106_106(&frameStructLocal);

} /* End of ose_unpackAndCheck_B1_frame_106_106 */


/**
 * Do unpacking and E2E validation of frame frame_905.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B1_frame_905_905(const uint8_t frameContent[8])
{
    /* Unpack the data locally. */
    cap_B1_frame_905_905_t frameStructLocal;
    cap_unpack_B1_frame_905_905(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B1_frame_905_905(&frameStructLocal);

} /* End of ose_unpackAndCheck_B1_frame_905_905 */


/**
 * Do unpacking and E2E validation of frame frame_0.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B1_frame_0_0(const uint8_t frameContent[7])
{
    /* Unpack the data locally. */
    cap_B1_frame_0_0_t frameStructLocal;
    cap_unpack_B1_frame_0_0(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B1_frame_0_0(&frameStructLocal);

} /* End of ose_unpackAndCheck_B1_frame_0_0 */


/**
 * Do unpacking and E2E validation of frame frame_1885.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B1_frame_1885_1885(const uint8_t frameContent[4])
{
    /* Unpack the data locally. */
    cap_B1_frame_1885_1885_t frameStructLocal;
    cap_unpack_B1_frame_1885_1885(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B1_frame_1885_1885(&frameStructLocal);

} /* End of ose_unpackAndCheck_B1_frame_1885_1885 */


/**
 * Do unpacking and E2E validation of frame frame_1415.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B1_frame_1415_1415(const uint8_t frameContent[5])
{
    /* Unpack the data locally. */
    cap_B1_frame_1415_1415_t frameStructLocal;
    cap_unpack_B1_frame_1415_1415(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B1_frame_1415_1415(&frameStructLocal);

} /* End of ose_unpackAndCheck_B1_frame_1415_1415 */


/**
 * Do unpacking and E2E validation of frame frame_915.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B1_frame_915_915(const uint8_t frameContent[6])
{
    /* Unpack the data locally. */
    cap_B1_frame_915_915_t frameStructLocal;
    cap_unpack_B1_frame_915_915(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B1_frame_915_915(&frameStructLocal);

} /* End of ose_unpackAndCheck_B1_frame_915_915 */


/**
 * Do unpacking and E2E validation of frame frame_349.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B1_frame_349_349(const uint8_t frameContent[6])
{
    /* Unpack the data locally. */
    cap_B1_frame_349_349_t frameStructLocal;
    cap_unpack_B1_frame_349_349(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B1_frame_349_349(&frameStructLocal);

} /* End of ose_unpackAndCheck_B1_frame_349_349 */


/**
 * Do unpacking and E2E validation of frame frame_25.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B2_frame_25_25(const uint8_t frameContent[5])
{
    /* Unpack the data locally. */
    cap_B2_frame_25_25_t frameStructLocal;
    cap_unpack_B2_frame_25_25(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B2_frame_25_25(&frameStructLocal);

} /* End of ose_unpackAndCheck_B2_frame_25_25 */


/**
 * Do unpacking and E2E validation of frame frame_1641.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B2_frame_1641_1641(const uint8_t frameContent[5])
{
    /* Unpack the data locally. */
    cap_B2_frame_1641_1641_t frameStructLocal;
    cap_unpack_B2_frame_1641_1641(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B2_frame_1641_1641(&frameStructLocal);

} /* End of ose_unpackAndCheck_B2_frame_1641_1641 */


/**
 * Do unpacking and E2E validation of frame frame_669.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B2_frame_669_669(const uint8_t frameContent[6])
{
    /* Unpack the data locally. */
    cap_B2_frame_669_669_t frameStructLocal;
    cap_unpack_B2_frame_669_669(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B2_frame_669_669(&frameStructLocal);

} /* End of ose_unpackAndCheck_B2_frame_669_669 */


/**
 * Do unpacking and E2E validation of frame frame_1401.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B2_frame_1401_1401(const uint8_t frameContent[6])
{
    /* Unpack the data locally. */
    cap_B2_frame_1401_1401_t frameStructLocal;
    cap_unpack_B2_frame_1401_1401(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B2_frame_1401_1401(&frameStructLocal);

} /* End of ose_unpackAndCheck_B2_frame_1401_1401 */


/**
 * Do unpacking and E2E validation of frame frame_1340.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B2_frame_1340_1340(const uint8_t frameContent[6])
{
    /* Unpack the data locally. */
    cap_B2_frame_1340_1340_t frameStructLocal;
    cap_unpack_B2_frame_1340_1340(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B2_frame_1340_1340(&frameStructLocal);

} /* End of ose_unpackAndCheck_B2_frame_1340_1340 */


/**
 * Do unpacking and E2E validation of frame frame_1151.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B2_frame_1151_1151(const uint8_t frameContent[7])
{
    /* Unpack the data locally. */
    cap_B2_frame_1151_1151_t frameStructLocal;
    cap_unpack_B2_frame_1151_1151(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B2_frame_1151_1151(&frameStructLocal);

} /* End of ose_unpackAndCheck_B2_frame_1151_1151 */


/**
 * Do unpacking and E2E validation of frame frame_1730.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B2_frame_1730_1730(const uint8_t frameContent[8])
{
    /* Unpack the data locally. */
    cap_B2_frame_1730_1730_t frameStructLocal;
    cap_unpack_B2_frame_1730_1730(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B2_frame_1730_1730(&frameStructLocal);

} /* End of ose_unpackAndCheck_B2_frame_1730_1730 */


/**
 * Do unpacking and E2E validation of frame frame_46.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B2_frame_46_46(const uint8_t frameContent[6])
{
    /* Unpack the data locally. */
    cap_B2_frame_46_46_t frameStructLocal;
    cap_unpack_B2_frame_46_46(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B2_frame_46_46(&frameStructLocal);

} /* End of ose_unpackAndCheck_B2_frame_46_46 */


/**
 * Do unpacking and E2E validation of frame frame_1939.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B2_frame_1939_1939(const uint8_t frameContent[8])
{
    /* Unpack the data locally. */
    cap_B2_frame_1939_1939_t frameStructLocal;
    cap_unpack_B2_frame_1939_1939(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B2_frame_1939_1939(&frameStructLocal);

} /* End of ose_unpackAndCheck_B2_frame_1939_1939 */


/**
 * Do unpacking and E2E validation of frame frame_659.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B2_frame_659_659(const uint8_t frameContent[6])
{
    /* Unpack the data locally. */
    cap_B2_frame_659_659_t frameStructLocal;
    cap_unpack_B2_frame_659_659(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B2_frame_659_659(&frameStructLocal);

} /* End of ose_unpackAndCheck_B2_frame_659_659 */


/**
 * Do unpacking and E2E validation of frame frame_981.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B2_frame_981_981(const uint8_t frameContent[6])
{
    /* Unpack the data locally. */
    cap_B2_frame_981_981_t frameStructLocal;
    cap_unpack_B2_frame_981_981(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B2_frame_981_981(&frameStructLocal);

} /* End of ose_unpackAndCheck_B2_frame_981_981 */


/**
 * Do unpacking and E2E validation of frame frame_708.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B2_frame_708_708(const uint8_t frameContent[8])
{
    /* Unpack the data locally. */
    cap_B2_frame_708_708_t frameStructLocal;
    cap_unpack_B2_frame_708_708(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B2_frame_708_708(&frameStructLocal);

} /* End of ose_unpackAndCheck_B2_frame_708_708 */


/**
 * Do unpacking and E2E validation of frame frame_1618.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B2_frame_1618_1618(const uint8_t frameContent[4])
{
    /* Unpack the data locally. */
    cap_B2_frame_1618_1618_t frameStructLocal;
    cap_unpack_B2_frame_1618_1618(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B2_frame_1618_1618(&frameStructLocal);

} /* End of ose_unpackAndCheck_B2_frame_1618_1618 */


/**
 * Do unpacking and E2E validation of frame frame_1956.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B2_frame_1956_1956(const uint8_t frameContent[5])
{
    /* Unpack the data locally. */
    cap_B2_frame_1956_1956_t frameStructLocal;
    cap_unpack_B2_frame_1956_1956(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B2_frame_1956_1956(&frameStructLocal);

} /* End of ose_unpackAndCheck_B2_frame_1956_1956 */


/**
 * Do unpacking and E2E validation of frame frame_463.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B2_frame_463_463(const uint8_t frameContent[4])
{
    /* Unpack the data locally. */
    cap_B2_frame_463_463_t frameStructLocal;
    cap_unpack_B2_frame_463_463(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B2_frame_463_463(&frameStructLocal);

} /* End of ose_unpackAndCheck_B2_frame_463_463 */


/**
 * Do unpacking and E2E validation of frame frame_954.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B2_frame_954_954(const uint8_t frameContent[8])
{
    /* Unpack the data locally. */
    cap_B2_frame_954_954_t frameStructLocal;
    cap_unpack_B2_frame_954_954(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B2_frame_954_954(&frameStructLocal);

} /* End of ose_unpackAndCheck_B2_frame_954_954 */


/**
 * Do unpacking and E2E validation of frame frame_1126.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B2_frame_1126_1126(const uint8_t frameContent[7])
{
    /* Unpack the data locally. */
    cap_B2_frame_1126_1126_t frameStructLocal;
    cap_unpack_B2_frame_1126_1126(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B2_frame_1126_1126(&frameStructLocal);

} /* End of ose_unpackAndCheck_B2_frame_1126_1126 */


/**
 * Do unpacking and E2E validation of frame frame_729.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B2_frame_729_729(const uint8_t frameContent[6])
{
    /* Unpack the data locally. */
    cap_B2_frame_729_729_t frameStructLocal;
    cap_unpack_B2_frame_729_729(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B2_frame_729_729(&frameStructLocal);

} /* End of ose_unpackAndCheck_B2_frame_729_729 */


/**
 * Do unpacking and E2E validation of frame frame_2045.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B2_frame_2045_2045(const uint8_t frameContent[5])
{
    /* Unpack the data locally. */
    cap_B2_frame_2045_2045_t frameStructLocal;
    cap_unpack_B2_frame_2045_2045(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B2_frame_2045_2045(&frameStructLocal);

} /* End of ose_unpackAndCheck_B2_frame_2045_2045 */


/**
 * Do unpacking and E2E validation of frame frame_1901.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B2_frame_1901_1901(const uint8_t frameContent[7])
{
    /* Unpack the data locally. */
    cap_B2_frame_1901_1901_t frameStructLocal;
    cap_unpack_B2_frame_1901_1901(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B2_frame_1901_1901(&frameStructLocal);

} /* End of ose_unpackAndCheck_B2_frame_1901_1901 */


/**
 * Do unpacking and E2E validation of frame frame_381.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B2_frame_381_381(const uint8_t frameContent[8])
{
    /* Unpack the data locally. */
    cap_B2_frame_381_381_t frameStructLocal;
    cap_unpack_B2_frame_381_381(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B2_frame_381_381(&frameStructLocal);

} /* End of ose_unpackAndCheck_B2_frame_381_381 */


/**
 * Do unpacking and E2E validation of frame frame_796.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B2_frame_796_796(const uint8_t frameContent[6])
{
    /* Unpack the data locally. */
    cap_B2_frame_796_796_t frameStructLocal;
    cap_unpack_B2_frame_796_796(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B2_frame_796_796(&frameStructLocal);

} /* End of ose_unpackAndCheck_B2_frame_796_796 */


/**
 * Do unpacking and E2E validation of frame frame_1652.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B2_frame_1652_1652(const uint8_t frameContent[7])
{
    /* Unpack the data locally. */
    cap_B2_frame_1652_1652_t frameStructLocal;
    cap_unpack_B2_frame_1652_1652(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B2_frame_1652_1652(&frameStructLocal);

} /* End of ose_unpackAndCheck_B2_frame_1652_1652 */


/**
 * Do unpacking and E2E validation of frame frame_1442.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B2_frame_1442_1442(const uint8_t frameContent[2])
{
    /* Unpack the data locally. */
    cap_B2_frame_1442_1442_t frameStructLocal;
    cap_unpack_B2_frame_1442_1442(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B2_frame_1442_1442(&frameStructLocal);

} /* End of ose_unpackAndCheck_B2_frame_1442_1442 */


/**
 * Do unpacking and E2E validation of frame frame_661.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B3_frame_661_661(const uint8_t frameContent[4])
{
    /* Unpack the data locally. */
    cap_B3_frame_661_661_t frameStructLocal;
    cap_unpack_B3_frame_661_661(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B3_frame_661_661(&frameStructLocal);

} /* End of ose_unpackAndCheck_B3_frame_661_661 */


/**
 * Do unpacking and E2E validation of frame frame_1084.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B3_frame_1084_1084(const uint8_t frameContent[4])
{
    /* Unpack the data locally. */
    cap_B3_frame_1084_1084_t frameStructLocal;
    cap_unpack_B3_frame_1084_1084(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B3_frame_1084_1084(&frameStructLocal);

} /* End of ose_unpackAndCheck_B3_frame_1084_1084 */


/**
 * Do unpacking and E2E validation of frame frame_1170.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B3_frame_1170_1170(const uint8_t frameContent[8])
{
    /* Unpack the data locally. */
    cap_B3_frame_1170_1170_t frameStructLocal;
    cap_unpack_B3_frame_1170_1170(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B3_frame_1170_1170(&frameStructLocal);

} /* End of ose_unpackAndCheck_B3_frame_1170_1170 */


/**
 * Do unpacking and E2E validation of frame frame_1696.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B3_frame_1696_1696(const uint8_t frameContent[7])
{
    /* Unpack the data locally. */
    cap_B3_frame_1696_1696_t frameStructLocal;
    cap_unpack_B3_frame_1696_1696(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B3_frame_1696_1696(&frameStructLocal);

} /* End of ose_unpackAndCheck_B3_frame_1696_1696 */


/**
 * Do unpacking and E2E validation of frame frame_1398.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B3_frame_1398_1398(const uint8_t frameContent[8])
{
    /* Unpack the data locally. */
    cap_B3_frame_1398_1398_t frameStructLocal;
    cap_unpack_B3_frame_1398_1398(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B3_frame_1398_1398(&frameStructLocal);

} /* End of ose_unpackAndCheck_B3_frame_1398_1398 */


/**
 * Do unpacking and E2E validation of frame frame_1425.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B3_frame_1425_1425(const uint8_t frameContent[5])
{
    /* Unpack the data locally. */
    cap_B3_frame_1425_1425_t frameStructLocal;
    cap_unpack_B3_frame_1425_1425(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B3_frame_1425_1425(&frameStructLocal);

} /* End of ose_unpackAndCheck_B3_frame_1425_1425 */


/**
 * Do unpacking and E2E validation of frame frame_1154.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B3_frame_1154_1154(const uint8_t frameContent[5])
{
    /* Unpack the data locally. */
    cap_B3_frame_1154_1154_t frameStructLocal;
    cap_unpack_B3_frame_1154_1154(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B3_frame_1154_1154(&frameStructLocal);

} /* End of ose_unpackAndCheck_B3_frame_1154_1154 */


/**
 * Do unpacking and E2E validation of frame frame_1404.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B3_frame_1404_1404(const uint8_t frameContent[8])
{
    /* Unpack the data locally. */
    cap_B3_frame_1404_1404_t frameStructLocal;
    cap_unpack_B3_frame_1404_1404(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B3_frame_1404_1404(&frameStructLocal);

} /* End of ose_unpackAndCheck_B3_frame_1404_1404 */


/**
 * Do unpacking and E2E validation of frame frame_1374.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B3_frame_1374_1374(const uint8_t frameContent[7])
{
    /* Unpack the data locally. */
    cap_B3_frame_1374_1374_t frameStructLocal;
    cap_unpack_B3_frame_1374_1374(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B3_frame_1374_1374(&frameStructLocal);

} /* End of ose_unpackAndCheck_B3_frame_1374_1374 */


/**
 * Do unpacking and E2E validation of frame frame_820.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B3_frame_820_820(const uint8_t frameContent[4])
{
    /* Unpack the data locally. */
    cap_B3_frame_820_820_t frameStructLocal;
    cap_unpack_B3_frame_820_820(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B3_frame_820_820(&frameStructLocal);

} /* End of ose_unpackAndCheck_B3_frame_820_820 */


/**
 * Do unpacking and E2E validation of frame frame_1713.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B3_frame_1713_1713(const uint8_t frameContent[7])
{
    /* Unpack the data locally. */
    cap_B3_frame_1713_1713_t frameStructLocal;
    cap_unpack_B3_frame_1713_1713(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B3_frame_1713_1713(&frameStructLocal);

} /* End of ose_unpackAndCheck_B3_frame_1713_1713 */


/**
 * Do unpacking and E2E validation of frame frame_1485.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B3_frame_1485_1485(const uint8_t frameContent[7])
{
    /* Unpack the data locally. */
    cap_B3_frame_1485_1485_t frameStructLocal;
    cap_unpack_B3_frame_1485_1485(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B3_frame_1485_1485(&frameStructLocal);

} /* End of ose_unpackAndCheck_B3_frame_1485_1485 */


/**
 * Do unpacking and E2E validation of frame frame_1385.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B3_frame_1385_1385(const uint8_t frameContent[6])
{
    /* Unpack the data locally. */
    cap_B3_frame_1385_1385_t frameStructLocal;
    cap_unpack_B3_frame_1385_1385(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B3_frame_1385_1385(&frameStructLocal);

} /* End of ose_unpackAndCheck_B3_frame_1385_1385 */


/**
 * Do unpacking and E2E validation of frame frame_2017.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B3_frame_2017_2017(const uint8_t frameContent[8])
{
    /* Unpack the data locally. */
    cap_B3_frame_2017_2017_t frameStructLocal;
    cap_unpack_B3_frame_2017_2017(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B3_frame_2017_2017(&frameStructLocal);

} /* End of ose_unpackAndCheck_B3_frame_2017_2017 */


/**
 * Do unpacking and E2E validation of frame frame_523.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B3_frame_523_523(const uint8_t frameContent[7])
{
    /* Unpack the data locally. */
    cap_B3_frame_523_523_t frameStructLocal;
    cap_unpack_B3_frame_523_523(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B3_frame_523_523(&frameStructLocal);

} /* End of ose_unpackAndCheck_B3_frame_523_523 */


/**
 * Do unpacking and E2E validation of frame frame_807.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B3_frame_807_807(const uint8_t frameContent[8])
{
    /* Unpack the data locally. */
    cap_B3_frame_807_807_t frameStructLocal;
    cap_unpack_B3_frame_807_807(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B3_frame_807_807(&frameStructLocal);

} /* End of ose_unpackAndCheck_B3_frame_807_807 */


/**
 * Do unpacking and E2E validation of frame frame_1637.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B3_frame_1637_1637(const uint8_t frameContent[5])
{
    /* Unpack the data locally. */
    cap_B3_frame_1637_1637_t frameStructLocal;
    cap_unpack_B3_frame_1637_1637(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B3_frame_1637_1637(&frameStructLocal);

} /* End of ose_unpackAndCheck_B3_frame_1637_1637 */


/**
 * Do unpacking and E2E validation of frame frame_1784.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B3_frame_1784_1784(const uint8_t frameContent[4])
{
    /* Unpack the data locally. */
    cap_B3_frame_1784_1784_t frameStructLocal;
    cap_unpack_B3_frame_1784_1784(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B3_frame_1784_1784(&frameStructLocal);

} /* End of ose_unpackAndCheck_B3_frame_1784_1784 */


/**
 * Do unpacking and E2E validation of frame frame_649.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B3_frame_649_649(const uint8_t frameContent[7])
{
    /* Unpack the data locally. */
    cap_B3_frame_649_649_t frameStructLocal;
    cap_unpack_B3_frame_649_649(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B3_frame_649_649(&frameStructLocal);

} /* End of ose_unpackAndCheck_B3_frame_649_649 */


/**
 * Do unpacking and E2E validation of frame frame_1801.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B4_frame_1801_1801(const uint8_t frameContent[8])
{
    /* Unpack the data locally. */
    cap_B4_frame_1801_1801_t frameStructLocal;
    cap_unpack_B4_frame_1801_1801(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B4_frame_1801_1801(&frameStructLocal);

} /* End of ose_unpackAndCheck_B4_frame_1801_1801 */


/**
 * Do unpacking and E2E validation of frame frame_1926.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B4_frame_1926_1926(const uint8_t frameContent[8])
{
    /* Unpack the data locally. */
    cap_B4_frame_1926_1926_t frameStructLocal;
    cap_unpack_B4_frame_1926_1926(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B4_frame_1926_1926(&frameStructLocal);

} /* End of ose_unpackAndCheck_B4_frame_1926_1926 */


/**
 * Do unpacking and E2E validation of frame frame_986.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B4_frame_986_986(const uint8_t frameContent[8])
{
    /* Unpack the data locally. */
    cap_B4_frame_986_986_t frameStructLocal;
    cap_unpack_B4_frame_986_986(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B4_frame_986_986(&frameStructLocal);

} /* End of ose_unpackAndCheck_B4_frame_986_986 */


/**
 * Do unpacking and E2E validation of frame frame_998.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B4_frame_998_998(const uint8_t frameContent[8])
{
    /* Unpack the data locally. */
    cap_B4_frame_998_998_t frameStructLocal;
    cap_unpack_B4_frame_998_998(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B4_frame_998_998(&frameStructLocal);

} /* End of ose_unpackAndCheck_B4_frame_998_998 */


/**
 * Do unpacking and E2E validation of frame frame_743.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B4_frame_743_743(const uint8_t frameContent[5])
{
    /* Unpack the data locally. */
    cap_B4_frame_743_743_t frameStructLocal;
    cap_unpack_B4_frame_743_743(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B4_frame_743_743(&frameStructLocal);

} /* End of ose_unpackAndCheck_B4_frame_743_743 */


/**
 * Do unpacking and E2E validation of frame frame_655.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B4_frame_655_655(const uint8_t frameContent[5])
{
    /* Unpack the data locally. */
    cap_B4_frame_655_655_t frameStructLocal;
    cap_unpack_B4_frame_655_655(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B4_frame_655_655(&frameStructLocal);

} /* End of ose_unpackAndCheck_B4_frame_655_655 */


/**
 * Do unpacking and E2E validation of frame frame_1332.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B4_frame_1332_1332(const uint8_t frameContent[8])
{
    /* Unpack the data locally. */
    cap_B4_frame_1332_1332_t frameStructLocal;
    cap_unpack_B4_frame_1332_1332(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B4_frame_1332_1332(&frameStructLocal);

} /* End of ose_unpackAndCheck_B4_frame_1332_1332 */


/**
 * Do unpacking and E2E validation of frame frame_86.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B4_frame_86_86(const uint8_t frameContent[5])
{
    /* Unpack the data locally. */
    cap_B4_frame_86_86_t frameStructLocal;
    cap_unpack_B4_frame_86_86(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B4_frame_86_86(&frameStructLocal);

} /* End of ose_unpackAndCheck_B4_frame_86_86 */


/**
 * Do unpacking and E2E validation of frame frame_1002.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B4_frame_1002_1002(const uint8_t frameContent[6])
{
    /* Unpack the data locally. */
    cap_B4_frame_1002_1002_t frameStructLocal;
    cap_unpack_B4_frame_1002_1002(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B4_frame_1002_1002(&frameStructLocal);

} /* End of ose_unpackAndCheck_B4_frame_1002_1002 */


/**
 * Do unpacking and E2E validation of frame frame_1957.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B4_frame_1957_1957(const uint8_t frameContent[6])
{
    /* Unpack the data locally. */
    cap_B4_frame_1957_1957_t frameStructLocal;
    cap_unpack_B4_frame_1957_1957(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B4_frame_1957_1957(&frameStructLocal);

} /* End of ose_unpackAndCheck_B4_frame_1957_1957 */


/**
 * Do unpacking and E2E validation of frame frame_969.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B4_frame_969_969(const uint8_t frameContent[8])
{
    /* Unpack the data locally. */
    cap_B4_frame_969_969_t frameStructLocal;
    cap_unpack_B4_frame_969_969(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B4_frame_969_969(&frameStructLocal);

} /* End of ose_unpackAndCheck_B4_frame_969_969 */


/**
 * Do unpacking and E2E validation of frame frame_739.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B4_frame_739_739(const uint8_t frameContent[6])
{
    /* Unpack the data locally. */
    cap_B4_frame_739_739_t frameStructLocal;
    cap_unpack_B4_frame_739_739(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B4_frame_739_739(&frameStructLocal);

} /* End of ose_unpackAndCheck_B4_frame_739_739 */


/**
 * Do unpacking and E2E validation of frame frame_484.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B4_frame_484_484(const uint8_t frameContent[3])
{
    /* Unpack the data locally. */
    cap_B4_frame_484_484_t frameStructLocal;
    cap_unpack_B4_frame_484_484(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B4_frame_484_484(&frameStructLocal);

} /* End of ose_unpackAndCheck_B4_frame_484_484 */


/**
 * Do unpacking and E2E validation of frame frame_1970.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B4_frame_1970_1970(const uint8_t frameContent[6])
{
    /* Unpack the data locally. */
    cap_B4_frame_1970_1970_t frameStructLocal;
    cap_unpack_B4_frame_1970_1970(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B4_frame_1970_1970(&frameStructLocal);

} /* End of ose_unpackAndCheck_B4_frame_1970_1970 */


/**
 * Do unpacking and E2E validation of frame frame_163.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B4_frame_163_163(const uint8_t frameContent[6])
{
    /* Unpack the data locally. */
    cap_B4_frame_163_163_t frameStructLocal;
    cap_unpack_B4_frame_163_163(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B4_frame_163_163(&frameStructLocal);

} /* End of ose_unpackAndCheck_B4_frame_163_163 */


/**
 * Do unpacking and E2E validation of frame frame_948.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B4_frame_948_948(const uint8_t frameContent[8])
{
    /* Unpack the data locally. */
    cap_B4_frame_948_948_t frameStructLocal;
    cap_unpack_B4_frame_948_948(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B4_frame_948_948(&frameStructLocal);

} /* End of ose_unpackAndCheck_B4_frame_948_948 */


/**
 * Do unpacking and E2E validation of frame frame_853.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B4_frame_853_853(const uint8_t frameContent[8])
{
    /* Unpack the data locally. */
    cap_B4_frame_853_853_t frameStructLocal;
    cap_unpack_B4_frame_853_853(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B4_frame_853_853(&frameStructLocal);

} /* End of ose_unpackAndCheck_B4_frame_853_853 */


/**
 * Do unpacking and E2E validation of frame frame_1444.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B4_frame_1444_1444(const uint8_t frameContent[8])
{
    /* Unpack the data locally. */
    cap_B4_frame_1444_1444_t frameStructLocal;
    cap_unpack_B4_frame_1444_1444(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B4_frame_1444_1444(&frameStructLocal);

} /* End of ose_unpackAndCheck_B4_frame_1444_1444 */


/**
 * Do unpacking and E2E validation of frame frame_570.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B5_frame_570_570(const uint8_t frameContent[7])
{
    /* Unpack the data locally. */
    cap_B5_frame_570_570_t frameStructLocal;
    cap_unpack_B5_frame_570_570(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B5_frame_570_570(&frameStructLocal);

} /* End of ose_unpackAndCheck_B5_frame_570_570 */


/**
 * Do unpacking and E2E validation of frame frame_1406.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B5_frame_1406_1406(const uint8_t frameContent[6])
{
    /* Unpack the data locally. */
    cap_B5_frame_1406_1406_t frameStructLocal;
    cap_unpack_B5_frame_1406_1406(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B5_frame_1406_1406(&frameStructLocal);

} /* End of ose_unpackAndCheck_B5_frame_1406_1406 */


/**
 * Do unpacking and E2E validation of frame frame_201.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B5_frame_201_201(const uint8_t frameContent[6])
{
    /* Unpack the data locally. */
    cap_B5_frame_201_201_t frameStructLocal;
    cap_unpack_B5_frame_201_201(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B5_frame_201_201(&frameStructLocal);

} /* End of ose_unpackAndCheck_B5_frame_201_201 */


/**
 * Do unpacking and E2E validation of frame frame_1951.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B5_frame_1951_1951(const uint8_t frameContent[8])
{
    /* Unpack the data locally. */
    cap_B5_frame_1951_1951_t frameStructLocal;
    cap_unpack_B5_frame_1951_1951(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B5_frame_1951_1951(&frameStructLocal);

} /* End of ose_unpackAndCheck_B5_frame_1951_1951 */


/**
 * Do unpacking and E2E validation of frame frame_154.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B5_frame_154_154(const uint8_t frameContent[4])
{
    /* Unpack the data locally. */
    cap_B5_frame_154_154_t frameStructLocal;
    cap_unpack_B5_frame_154_154(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B5_frame_154_154(&frameStructLocal);

} /* End of ose_unpackAndCheck_B5_frame_154_154 */


/**
 * Do unpacking and E2E validation of frame frame_1043.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B5_frame_1043_1043(const uint8_t frameContent[8])
{
    /* Unpack the data locally. */
    cap_B5_frame_1043_1043_t frameStructLocal;
    cap_unpack_B5_frame_1043_1043(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B5_frame_1043_1043(&frameStructLocal);

} /* End of ose_unpackAndCheck_B5_frame_1043_1043 */


/**
 * Do unpacking and E2E validation of frame frame_306.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B5_frame_306_306(const uint8_t frameContent[6])
{
    /* Unpack the data locally. */
    cap_B5_frame_306_306_t frameStructLocal;
    cap_unpack_B5_frame_306_306(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B5_frame_306_306(&frameStructLocal);

} /* End of ose_unpackAndCheck_B5_frame_306_306 */


/**
 * Do unpacking and E2E validation of frame frame_37.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B5_frame_37_37(const uint8_t frameContent[7])
{
    /* Unpack the data locally. */
    cap_B5_frame_37_37_t frameStructLocal;
    cap_unpack_B5_frame_37_37(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B5_frame_37_37(&frameStructLocal);

} /* End of ose_unpackAndCheck_B5_frame_37_37 */


/**
 * Do unpacking and E2E validation of frame frame_1351.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B5_frame_1351_1351(const uint8_t frameContent[5])
{
    /* Unpack the data locally. */
    cap_B5_frame_1351_1351_t frameStructLocal;
    cap_unpack_B5_frame_1351_1351(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B5_frame_1351_1351(&frameStructLocal);

} /* End of ose_unpackAndCheck_B5_frame_1351_1351 */


/**
 * Do unpacking and E2E validation of frame frame_1458.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B5_frame_1458_1458(const uint8_t frameContent[7])
{
    /* Unpack the data locally. */
    cap_B5_frame_1458_1458_t frameStructLocal;
    cap_unpack_B5_frame_1458_1458(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B5_frame_1458_1458(&frameStructLocal);

} /* End of ose_unpackAndCheck_B5_frame_1458_1458 */


/**
 * Do unpacking and E2E validation of frame frame_809.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B5_frame_809_809(const uint8_t frameContent[6])
{
    /* Unpack the data locally. */
    cap_B5_frame_809_809_t frameStructLocal;
    cap_unpack_B5_frame_809_809(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B5_frame_809_809(&frameStructLocal);

} /* End of ose_unpackAndCheck_B5_frame_809_809 */


/**
 * Do unpacking and E2E validation of frame frame_1752.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B5_frame_1752_1752(const uint8_t frameContent[8])
{
    /* Unpack the data locally. */
    cap_B5_frame_1752_1752_t frameStructLocal;
    cap_unpack_B5_frame_1752_1752(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B5_frame_1752_1752(&frameStructLocal);

} /* End of ose_unpackAndCheck_B5_frame_1752_1752 */


/**
 * Do unpacking and E2E validation of frame frame_170.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B5_frame_170_170(const uint8_t frameContent[8])
{
    /* Unpack the data locally. */
    cap_B5_frame_170_170_t frameStructLocal;
    cap_unpack_B5_frame_170_170(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B5_frame_170_170(&frameStructLocal);

} /* End of ose_unpackAndCheck_B5_frame_170_170 */


/**
 * Do unpacking and E2E validation of frame frame_1732.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B5_frame_1732_1732(const uint8_t frameContent[5])
{
    /* Unpack the data locally. */
    cap_B5_frame_1732_1732_t frameStructLocal;
    cap_unpack_B5_frame_1732_1732(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B5_frame_1732_1732(&frameStructLocal);

} /* End of ose_unpackAndCheck_B5_frame_1732_1732 */


/**
 * Do unpacking and E2E validation of frame frame_550.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B6_frame_550_550(const uint8_t frameContent[6])
{
    /* Unpack the data locally. */
    cap_B6_frame_550_550_t frameStructLocal;
    cap_unpack_B6_frame_550_550(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B6_frame_550_550(&frameStructLocal);

} /* End of ose_unpackAndCheck_B6_frame_550_550 */


/**
 * Do unpacking and E2E validation of frame frame_168.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B6_frame_168_168(const uint8_t frameContent[7])
{
    /* Unpack the data locally. */
    cap_B6_frame_168_168_t frameStructLocal;
    cap_unpack_B6_frame_168_168(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B6_frame_168_168(&frameStructLocal);

} /* End of ose_unpackAndCheck_B6_frame_168_168 */


/**
 * Do unpacking and E2E validation of frame frame_66.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B6_frame_66_66(const uint8_t frameContent[8])
{
    /* Unpack the data locally. */
    cap_B6_frame_66_66_t frameStructLocal;
    cap_unpack_B6_frame_66_66(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B6_frame_66_66(&frameStructLocal);

} /* End of ose_unpackAndCheck_B6_frame_66_66 */


/**
 * Do unpacking and E2E validation of frame frame_1387.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B6_frame_1387_1387(const uint8_t frameContent[6])
{
    /* Unpack the data locally. */
    cap_B6_frame_1387_1387_t frameStructLocal;
    cap_unpack_B6_frame_1387_1387(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B6_frame_1387_1387(&frameStructLocal);

} /* End of ose_unpackAndCheck_B6_frame_1387_1387 */


/**
 * Do unpacking and E2E validation of frame frame_441.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B6_frame_441_441(const uint8_t frameContent[5])
{
    /* Unpack the data locally. */
    cap_B6_frame_441_441_t frameStructLocal;
    cap_unpack_B6_frame_441_441(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B6_frame_441_441(&frameStructLocal);

} /* End of ose_unpackAndCheck_B6_frame_441_441 */


/**
 * Do unpacking and E2E validation of frame frame_1716.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B6_frame_1716_1716(const uint8_t frameContent[8])
{
    /* Unpack the data locally. */
    cap_B6_frame_1716_1716_t frameStructLocal;
    cap_unpack_B6_frame_1716_1716(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B6_frame_1716_1716(&frameStructLocal);

} /* End of ose_unpackAndCheck_B6_frame_1716_1716 */


/**
 * Do unpacking and E2E validation of frame frame_941.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B6_frame_941_941(const uint8_t frameContent[7])
{
    /* Unpack the data locally. */
    cap_B6_frame_941_941_t frameStructLocal;
    cap_unpack_B6_frame_941_941(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B6_frame_941_941(&frameStructLocal);

} /* End of ose_unpackAndCheck_B6_frame_941_941 */


/**
 * Do unpacking and E2E validation of frame frame_1640.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B6_frame_1640_1640(const uint8_t frameContent[7])
{
    /* Unpack the data locally. */
    cap_B6_frame_1640_1640_t frameStructLocal;
    cap_unpack_B6_frame_1640_1640(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B6_frame_1640_1640(&frameStructLocal);

} /* End of ose_unpackAndCheck_B6_frame_1640_1640 */


/**
 * Do unpacking and E2E validation of frame frame_1575.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B6_frame_1575_1575(const uint8_t frameContent[8])
{
    /* Unpack the data locally. */
    cap_B6_frame_1575_1575_t frameStructLocal;
    cap_unpack_B6_frame_1575_1575(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B6_frame_1575_1575(&frameStructLocal);

} /* End of ose_unpackAndCheck_B6_frame_1575_1575 */


/**
 * Do unpacking and E2E validation of frame frame_1272.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B6_frame_1272_1272(const uint8_t frameContent[6])
{
    /* Unpack the data locally. */
    cap_B6_frame_1272_1272_t frameStructLocal;
    cap_unpack_B6_frame_1272_1272(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B6_frame_1272_1272(&frameStructLocal);

} /* End of ose_unpackAndCheck_B6_frame_1272_1272 */


/**
 * Do unpacking and E2E validation of frame frame_913.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B6_frame_913_913(const uint8_t frameContent[7])
{
    /* Unpack the data locally. */
    cap_B6_frame_913_913_t frameStructLocal;
    cap_unpack_B6_frame_913_913(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B6_frame_913_913(&frameStructLocal);

} /* End of ose_unpackAndCheck_B6_frame_913_913 */


/**
 * Do unpacking and E2E validation of frame frame_1165.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B6_frame_1165_1165(const uint8_t frameContent[4])
{
    /* Unpack the data locally. */
    cap_B6_frame_1165_1165_t frameStructLocal;
    cap_unpack_B6_frame_1165_1165(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B6_frame_1165_1165(&frameStructLocal);

} /* End of ose_unpackAndCheck_B6_frame_1165_1165 */


/**
 * Do unpacking and E2E validation of frame frame_895.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B6_frame_895_895(const uint8_t frameContent[3])
{
    /* Unpack the data locally. */
    cap_B6_frame_895_895_t frameStructLocal;
    cap_unpack_B6_frame_895_895(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B6_frame_895_895(&frameStructLocal);

} /* End of ose_unpackAndCheck_B6_frame_895_895 */


/**
 * Do unpacking and E2E validation of frame frame_666.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B6_frame_666_666(const uint8_t frameContent[3])
{
    /* Unpack the data locally. */
    cap_B6_frame_666_666_t frameStructLocal;
    cap_unpack_B6_frame_666_666(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B6_frame_666_666(&frameStructLocal);

} /* End of ose_unpackAndCheck_B6_frame_666_666 */


/**
 * Do unpacking and E2E validation of frame frame_1495.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B6_frame_1495_1495(const uint8_t frameContent[8])
{
    /* Unpack the data locally. */
    cap_B6_frame_1495_1495_t frameStructLocal;
    cap_unpack_B6_frame_1495_1495(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B6_frame_1495_1495(&frameStructLocal);

} /* End of ose_unpackAndCheck_B6_frame_1495_1495 */


/**
 * Do unpacking and E2E validation of frame frame_1175.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B6_frame_1175_1175(const uint8_t frameContent[5])
{
    /* Unpack the data locally. */
    cap_B6_frame_1175_1175_t frameStructLocal;
    cap_unpack_B6_frame_1175_1175(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B6_frame_1175_1175(&frameStructLocal);

} /* End of ose_unpackAndCheck_B6_frame_1175_1175 */


/**
 * Do unpacking and E2E validation of frame frame_1277.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B6_frame_1277_1277(const uint8_t frameContent[2])
{
    /* Unpack the data locally. */
    cap_B6_frame_1277_1277_t frameStructLocal;
    cap_unpack_B6_frame_1277_1277(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B6_frame_1277_1277(&frameStructLocal);

} /* End of ose_unpackAndCheck_B6_frame_1277_1277 */


/**
 * Do unpacking and E2E validation of frame frame_1593.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B6_frame_1593_1593(const uint8_t frameContent[5])
{
    /* Unpack the data locally. */
    cap_B6_frame_1593_1593_t frameStructLocal;
    cap_unpack_B6_frame_1593_1593(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B6_frame_1593_1593(&frameStructLocal);

} /* End of ose_unpackAndCheck_B6_frame_1593_1593 */


/**
 * Do unpacking and E2E validation of frame frame_1980.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B6_frame_1980_1980(const uint8_t frameContent[7])
{
    /* Unpack the data locally. */
    cap_B6_frame_1980_1980_t frameStructLocal;
    cap_unpack_B6_frame_1980_1980(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B6_frame_1980_1980(&frameStructLocal);

} /* End of ose_unpackAndCheck_B6_frame_1980_1980 */


/**
 * Do unpacking and E2E validation of frame frame_1287.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B6_frame_1287_1287(const uint8_t frameContent[8])
{
    /* Unpack the data locally. */
    cap_B6_frame_1287_1287_t frameStructLocal;
    cap_unpack_B6_frame_1287_1287(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B6_frame_1287_1287(&frameStructLocal);

} /* End of ose_unpackAndCheck_B6_frame_1287_1287 */


/**
 * Do unpacking and E2E validation of frame frame_189.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B6_frame_189_189(const uint8_t frameContent[2])
{
    /* Unpack the data locally. */
    cap_B6_frame_189_189_t frameStructLocal;
    cap_unpack_B6_frame_189_189(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B6_frame_189_189(&frameStructLocal);

} /* End of ose_unpackAndCheck_B6_frame_189_189 */


/**
 * Do unpacking and E2E validation of frame frame_494.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B6_frame_494_494(const uint8_t frameContent[5])
{
    /* Unpack the data locally. */
    cap_B6_frame_494_494_t frameStructLocal;
    cap_unpack_B6_frame_494_494(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B6_frame_494_494(&frameStructLocal);

} /* End of ose_unpackAndCheck_B6_frame_494_494 */


/**
 * Do unpacking and E2E validation of frame frame_1045.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B6_frame_1045_1045(const uint8_t frameContent[4])
{
    /* Unpack the data locally. */
    cap_B6_frame_1045_1045_t frameStructLocal;
    cap_unpack_B6_frame_1045_1045(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B6_frame_1045_1045(&frameStructLocal);

} /* End of ose_unpackAndCheck_B6_frame_1045_1045 */


/**
 * Do unpacking and E2E validation of frame frame_1469.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B6_frame_1469_1469(const uint8_t frameContent[8])
{
    /* Unpack the data locally. */
    cap_B6_frame_1469_1469_t frameStructLocal;
    cap_unpack_B6_frame_1469_1469(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B6_frame_1469_1469(&frameStructLocal);

} /* End of ose_unpackAndCheck_B6_frame_1469_1469 */


/**
 * Do unpacking and E2E validation of frame frame_1684.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B6_frame_1684_1684(const uint8_t frameContent[8])
{
    /* Unpack the data locally. */
    cap_B6_frame_1684_1684_t frameStructLocal;
    cap_unpack_B6_frame_1684_1684(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B6_frame_1684_1684(&frameStructLocal);

} /* End of ose_unpackAndCheck_B6_frame_1684_1684 */


/**
 * Do unpacking and E2E validation of frame frame_1614.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B6_frame_1614_1614(const uint8_t frameContent[8])
{
    /* Unpack the data locally. */
    cap_B6_frame_1614_1614_t frameStructLocal;
    cap_unpack_B6_frame_1614_1614(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B6_frame_1614_1614(&frameStructLocal);

} /* End of ose_unpackAndCheck_B6_frame_1614_1614 */


/**
 * Do unpacking and E2E validation of frame frame_747.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B6_frame_747_747(const uint8_t frameContent[6])
{
    /* Unpack the data locally. */
    cap_B6_frame_747_747_t frameStructLocal;
    cap_unpack_B6_frame_747_747(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B6_frame_747_747(&frameStructLocal);

} /* End of ose_unpackAndCheck_B6_frame_747_747 */


/**
 * Do unpacking and E2E validation of frame frame_1013.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B6_frame_1013_1013(const uint8_t frameContent[2])
{
    /* Unpack the data locally. */
    cap_B6_frame_1013_1013_t frameStructLocal;
    cap_unpack_B6_frame_1013_1013(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B6_frame_1013_1013(&frameStructLocal);

} /* End of ose_unpackAndCheck_B6_frame_1013_1013 */


/**
 * Do unpacking and E2E validation of frame frame_582.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B6_frame_582_582(const uint8_t frameContent[4])
{
    /* Unpack the data locally. */
    cap_B6_frame_582_582_t frameStructLocal;
    cap_unpack_B6_frame_582_582(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B6_frame_582_582(&frameStructLocal);

} /* End of ose_unpackAndCheck_B6_frame_582_582 */


/**
 * Do unpacking and E2E validation of frame frame_291.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B6_frame_291_291(const uint8_t frameContent[7])
{
    /* Unpack the data locally. */
    cap_B6_frame_291_291_t frameStructLocal;
    cap_unpack_B6_frame_291_291(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B6_frame_291_291(&frameStructLocal);

} /* End of ose_unpackAndCheck_B6_frame_291_291 */


/**
 * Do unpacking and E2E validation of frame frame_137.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B6_frame_137_137(const uint8_t frameContent[6])
{
    /* Unpack the data locally. */
    cap_B6_frame_137_137_t frameStructLocal;
    cap_unpack_B6_frame_137_137(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B6_frame_137_137(&frameStructLocal);

} /* End of ose_unpackAndCheck_B6_frame_137_137 */


/**
 * Do unpacking and E2E validation of frame frame_782.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B7_frame_782_782(const uint8_t frameContent[6])
{
    /* Unpack the data locally. */
    cap_B7_frame_782_782_t frameStructLocal;
    cap_unpack_B7_frame_782_782(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B7_frame_782_782(&frameStructLocal);

} /* End of ose_unpackAndCheck_B7_frame_782_782 */


/**
 * Do unpacking and E2E validation of frame frame_1867.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B7_frame_1867_1867(const uint8_t frameContent[4])
{
    /* Unpack the data locally. */
    cap_B7_frame_1867_1867_t frameStructLocal;
    cap_unpack_B7_frame_1867_1867(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B7_frame_1867_1867(&frameStructLocal);

} /* End of ose_unpackAndCheck_B7_frame_1867_1867 */


/**
 * Do unpacking and E2E validation of frame frame_61.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B7_frame_61_61(const uint8_t frameContent[7])
{
    /* Unpack the data locally. */
    cap_B7_frame_61_61_t frameStructLocal;
    cap_unpack_B7_frame_61_61(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B7_frame_61_61(&frameStructLocal);

} /* End of ose_unpackAndCheck_B7_frame_61_61 */


/**
 * Do unpacking and E2E validation of frame frame_1403.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B7_frame_1403_1403(const uint8_t frameContent[8])
{
    /* Unpack the data locally. */
    cap_B7_frame_1403_1403_t frameStructLocal;
    cap_unpack_B7_frame_1403_1403(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B7_frame_1403_1403(&frameStructLocal);

} /* End of ose_unpackAndCheck_B7_frame_1403_1403 */


/**
 * Do unpacking and E2E validation of frame frame_158.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B7_frame_158_158(const uint8_t frameContent[8])
{
    /* Unpack the data locally. */
    cap_B7_frame_158_158_t frameStructLocal;
    cap_unpack_B7_frame_158_158(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B7_frame_158_158(&frameStructLocal);

} /* End of ose_unpackAndCheck_B7_frame_158_158 */


/**
 * Do unpacking and E2E validation of frame frame_1052.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B7_frame_1052_1052(const uint8_t frameContent[3])
{
    /* Unpack the data locally. */
    cap_B7_frame_1052_1052_t frameStructLocal;
    cap_unpack_B7_frame_1052_1052(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B7_frame_1052_1052(&frameStructLocal);

} /* End of ose_unpackAndCheck_B7_frame_1052_1052 */


/**
 * Do unpacking and E2E validation of frame frame_1297.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B7_frame_1297_1297(const uint8_t frameContent[7])
{
    /* Unpack the data locally. */
    cap_B7_frame_1297_1297_t frameStructLocal;
    cap_unpack_B7_frame_1297_1297(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B7_frame_1297_1297(&frameStructLocal);

} /* End of ose_unpackAndCheck_B7_frame_1297_1297 */


/**
 * Do unpacking and E2E validation of frame frame_1829.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B7_frame_1829_1829(const uint8_t frameContent[8])
{
    /* Unpack the data locally. */
    cap_B7_frame_1829_1829_t frameStructLocal;
    cap_unpack_B7_frame_1829_1829(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B7_frame_1829_1829(&frameStructLocal);

} /* End of ose_unpackAndCheck_B7_frame_1829_1829 */


/**
 * Do unpacking and E2E validation of frame frame_1281.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B7_frame_1281_1281(const uint8_t frameContent[6])
{
    /* Unpack the data locally. */
    cap_B7_frame_1281_1281_t frameStructLocal;
    cap_unpack_B7_frame_1281_1281(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B7_frame_1281_1281(&frameStructLocal);

} /* End of ose_unpackAndCheck_B7_frame_1281_1281 */


/**
 * Do unpacking and E2E validation of frame frame_678.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B7_frame_678_678(const uint8_t frameContent[2])
{
    /* Unpack the data locally. */
    cap_B7_frame_678_678_t frameStructLocal;
    cap_unpack_B7_frame_678_678(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B7_frame_678_678(&frameStructLocal);

} /* End of ose_unpackAndCheck_B7_frame_678_678 */


/**
 * Do unpacking and E2E validation of frame frame_1157.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B7_frame_1157_1157(const uint8_t frameContent[3])
{
    /* Unpack the data locally. */
    cap_B7_frame_1157_1157_t frameStructLocal;
    cap_unpack_B7_frame_1157_1157(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B7_frame_1157_1157(&frameStructLocal);

} /* End of ose_unpackAndCheck_B7_frame_1157_1157 */


/**
 * Do unpacking and E2E validation of frame frame_111.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B7_frame_111_111(const uint8_t frameContent[8])
{
    /* Unpack the data locally. */
    cap_B7_frame_111_111_t frameStructLocal;
    cap_unpack_B7_frame_111_111(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B7_frame_111_111(&frameStructLocal);

} /* End of ose_unpackAndCheck_B7_frame_111_111 */


/**
 * Do unpacking and E2E validation of frame frame_509.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B7_frame_509_509(const uint8_t frameContent[6])
{
    /* Unpack the data locally. */
    cap_B7_frame_509_509_t frameStructLocal;
    cap_unpack_B7_frame_509_509(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B7_frame_509_509(&frameStructLocal);

} /* End of ose_unpackAndCheck_B7_frame_509_509 */


/**
 * Do unpacking and E2E validation of frame frame_199.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B7_frame_199_199(const uint8_t frameContent[4])
{
    /* Unpack the data locally. */
    cap_B7_frame_199_199_t frameStructLocal;
    cap_unpack_B7_frame_199_199(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B7_frame_199_199(&frameStructLocal);

} /* End of ose_unpackAndCheck_B7_frame_199_199 */


/**
 * Do unpacking and E2E validation of frame frame_1931.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B7_frame_1931_1931(const uint8_t frameContent[5])
{
    /* Unpack the data locally. */
    cap_B7_frame_1931_1931_t frameStructLocal;
    cap_unpack_B7_frame_1931_1931(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B7_frame_1931_1931(&frameStructLocal);

} /* End of ose_unpackAndCheck_B7_frame_1931_1931 */


/**
 * Do unpacking and E2E validation of frame frame_1524.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B7_frame_1524_1524(const uint8_t frameContent[6])
{
    /* Unpack the data locally. */
    cap_B7_frame_1524_1524_t frameStructLocal;
    cap_unpack_B7_frame_1524_1524(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B7_frame_1524_1524(&frameStructLocal);

} /* End of ose_unpackAndCheck_B7_frame_1524_1524 */


/**
 * Do unpacking and E2E validation of frame frame_924.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B7_frame_924_924(const uint8_t frameContent[8])
{
    /* Unpack the data locally. */
    cap_B7_frame_924_924_t frameStructLocal;
    cap_unpack_B7_frame_924_924(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B7_frame_924_924(&frameStructLocal);

} /* End of ose_unpackAndCheck_B7_frame_924_924 */


/**
 * Do unpacking and E2E validation of frame frame_1022.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B7_frame_1022_1022(const uint8_t frameContent[7])
{
    /* Unpack the data locally. */
    cap_B7_frame_1022_1022_t frameStructLocal;
    cap_unpack_B7_frame_1022_1022(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B7_frame_1022_1022(&frameStructLocal);

} /* End of ose_unpackAndCheck_B7_frame_1022_1022 */


/**
 * Do unpacking and E2E validation of frame frame_793.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B7_frame_793_793(const uint8_t frameContent[7])
{
    /* Unpack the data locally. */
    cap_B7_frame_793_793_t frameStructLocal;
    cap_unpack_B7_frame_793_793(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B7_frame_793_793(&frameStructLocal);

} /* End of ose_unpackAndCheck_B7_frame_793_793 */


/**
 * Do unpacking and E2E validation of frame frame_465.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B7_frame_465_465(const uint8_t frameContent[3])
{
    /* Unpack the data locally. */
    cap_B7_frame_465_465_t frameStructLocal;
    cap_unpack_B7_frame_465_465(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B7_frame_465_465(&frameStructLocal);

} /* End of ose_unpackAndCheck_B7_frame_465_465 */


/**
 * Do unpacking and E2E validation of frame frame_294.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B7_frame_294_294(const uint8_t frameContent[8])
{
    /* Unpack the data locally. */
    cap_B7_frame_294_294_t frameStructLocal;
    cap_unpack_B7_frame_294_294(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B7_frame_294_294(&frameStructLocal);

} /* End of ose_unpackAndCheck_B7_frame_294_294 */


/**
 * Do unpacking and E2E validation of frame frame_593.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B7_frame_593_593(const uint8_t frameContent[5])
{
    /* Unpack the data locally. */
    cap_B7_frame_593_593_t frameStructLocal;
    cap_unpack_B7_frame_593_593(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B7_frame_593_593(&frameStructLocal);

} /* End of ose_unpackAndCheck_B7_frame_593_593 */


/**
 * Do unpacking and E2E validation of frame frame_1475.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B7_frame_1475_1475(const uint8_t frameContent[8])
{
    /* Unpack the data locally. */
    cap_B7_frame_1475_1475_t frameStructLocal;
    cap_unpack_B7_frame_1475_1475(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B7_frame_1475_1475(&frameStructLocal);

} /* End of ose_unpackAndCheck_B7_frame_1475_1475 */


/**
 * Do unpacking and E2E validation of frame frame_192.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B7_frame_192_192(const uint8_t frameContent[6])
{
    /* Unpack the data locally. */
    cap_B7_frame_192_192_t frameStructLocal;
    cap_unpack_B7_frame_192_192(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B7_frame_192_192(&frameStructLocal);

} /* End of ose_unpackAndCheck_B7_frame_192_192 */


/**
 * Do unpacking and E2E validation of frame frame_1954.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B7_frame_1954_1954(const uint8_t frameContent[6])
{
    /* Unpack the data locally. */
    cap_B7_frame_1954_1954_t frameStructLocal;
    cap_unpack_B7_frame_1954_1954(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B7_frame_1954_1954(&frameStructLocal);

} /* End of ose_unpackAndCheck_B7_frame_1954_1954 */


/**
 * Do unpacking and E2E validation of frame frame_1993.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B7_frame_1993_1993(const uint8_t frameContent[8])
{
    /* Unpack the data locally. */
    cap_B7_frame_1993_1993_t frameStructLocal;
    cap_unpack_B7_frame_1993_1993(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B7_frame_1993_1993(&frameStructLocal);

} /* End of ose_unpackAndCheck_B7_frame_1993_1993 */


/**
 * Do unpacking and E2E validation of frame frame_392.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B8_frame_392_392(const uint8_t frameContent[8])
{
    /* Unpack the data locally. */
    cap_B8_frame_392_392_t frameStructLocal;
    cap_unpack_B8_frame_392_392(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B8_frame_392_392(&frameStructLocal);

} /* End of ose_unpackAndCheck_B8_frame_392_392 */


/**
 * Do unpacking and E2E validation of frame frame_33.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B8_frame_33_33(const uint8_t frameContent[4])
{
    /* Unpack the data locally. */
    cap_B8_frame_33_33_t frameStructLocal;
    cap_unpack_B8_frame_33_33(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B8_frame_33_33(&frameStructLocal);

} /* End of ose_unpackAndCheck_B8_frame_33_33 */


/**
 * Do unpacking and E2E validation of frame frame_1076.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B8_frame_1076_1076(const uint8_t frameContent[4])
{
    /* Unpack the data locally. */
    cap_B8_frame_1076_1076_t frameStructLocal;
    cap_unpack_B8_frame_1076_1076(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B8_frame_1076_1076(&frameStructLocal);

} /* End of ose_unpackAndCheck_B8_frame_1076_1076 */


/**
 * Do unpacking and E2E validation of frame frame_24.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B8_frame_24_24(const uint8_t frameContent[6])
{
    /* Unpack the data locally. */
    cap_B8_frame_24_24_t frameStructLocal;
    cap_unpack_B8_frame_24_24(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B8_frame_24_24(&frameStructLocal);

} /* End of ose_unpackAndCheck_B8_frame_24_24 */


/**
 * Do unpacking and E2E validation of frame frame_880.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B8_frame_880_880(const uint8_t frameContent[8])
{
    /* Unpack the data locally. */
    cap_B8_frame_880_880_t frameStructLocal;
    cap_unpack_B8_frame_880_880(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B8_frame_880_880(&frameStructLocal);

} /* End of ose_unpackAndCheck_B8_frame_880_880 */


/**
 * Do unpacking and E2E validation of frame frame_646.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B8_frame_646_646(const uint8_t frameContent[5])
{
    /* Unpack the data locally. */
    cap_B8_frame_646_646_t frameStructLocal;
    cap_unpack_B8_frame_646_646(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B8_frame_646_646(&frameStructLocal);

} /* End of ose_unpackAndCheck_B8_frame_646_646 */


/**
 * Do unpacking and E2E validation of frame frame_85.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B8_frame_85_85(const uint8_t frameContent[8])
{
    /* Unpack the data locally. */
    cap_B8_frame_85_85_t frameStructLocal;
    cap_unpack_B8_frame_85_85(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B8_frame_85_85(&frameStructLocal);

} /* End of ose_unpackAndCheck_B8_frame_85_85 */


/**
 * Do unpacking and E2E validation of frame frame_696.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B8_frame_696_696(const uint8_t frameContent[3])
{
    /* Unpack the data locally. */
    cap_B8_frame_696_696_t frameStructLocal;
    cap_unpack_B8_frame_696_696(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B8_frame_696_696(&frameStructLocal);

} /* End of ose_unpackAndCheck_B8_frame_696_696 */


/**
 * Do unpacking and E2E validation of frame frame_991.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B8_frame_991_991(const uint8_t frameContent[5])
{
    /* Unpack the data locally. */
    cap_B8_frame_991_991_t frameStructLocal;
    cap_unpack_B8_frame_991_991(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B8_frame_991_991(&frameStructLocal);

} /* End of ose_unpackAndCheck_B8_frame_991_991 */


/**
 * Do unpacking and E2E validation of frame frame_632.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B8_frame_632_632(const uint8_t frameContent[8])
{
    /* Unpack the data locally. */
    cap_B8_frame_632_632_t frameStructLocal;
    cap_unpack_B8_frame_632_632(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B8_frame_632_632(&frameStructLocal);

} /* End of ose_unpackAndCheck_B8_frame_632_632 */


/**
 * Do unpacking and E2E validation of frame frame_1388.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B8_frame_1388_1388(const uint8_t frameContent[7])
{
    /* Unpack the data locally. */
    cap_B8_frame_1388_1388_t frameStructLocal;
    cap_unpack_B8_frame_1388_1388(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B8_frame_1388_1388(&frameStructLocal);

} /* End of ose_unpackAndCheck_B8_frame_1388_1388 */


/**
 * Do unpacking and E2E validation of frame frame_755.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B8_frame_755_755(const uint8_t frameContent[5])
{
    /* Unpack the data locally. */
    cap_B8_frame_755_755_t frameStructLocal;
    cap_unpack_B8_frame_755_755(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B8_frame_755_755(&frameStructLocal);

} /* End of ose_unpackAndCheck_B8_frame_755_755 */


/**
 * Do unpacking and E2E validation of frame frame_966.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B8_frame_966_966(const uint8_t frameContent[8])
{
    /* Unpack the data locally. */
    cap_B8_frame_966_966_t frameStructLocal;
    cap_unpack_B8_frame_966_966(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B8_frame_966_966(&frameStructLocal);

} /* End of ose_unpackAndCheck_B8_frame_966_966 */


/**
 * Do unpacking and E2E validation of frame frame_1961.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B8_frame_1961_1961(const uint8_t frameContent[8])
{
    /* Unpack the data locally. */
    cap_B8_frame_1961_1961_t frameStructLocal;
    cap_unpack_B8_frame_1961_1961(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B8_frame_1961_1961(&frameStructLocal);

} /* End of ose_unpackAndCheck_B8_frame_1961_1961 */


/**
 * Do unpacking and E2E validation of frame frame_1687.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B8_frame_1687_1687(const uint8_t frameContent[8])
{
    /* Unpack the data locally. */
    cap_B8_frame_1687_1687_t frameStructLocal;
    cap_unpack_B8_frame_1687_1687(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B8_frame_1687_1687(&frameStructLocal);

} /* End of ose_unpackAndCheck_B8_frame_1687_1687 */


/**
 * Do unpacking and E2E validation of frame frame_1663.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B8_frame_1663_1663(const uint8_t frameContent[4])
{
    /* Unpack the data locally. */
    cap_B8_frame_1663_1663_t frameStructLocal;
    cap_unpack_B8_frame_1663_1663(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B8_frame_1663_1663(&frameStructLocal);

} /* End of ose_unpackAndCheck_B8_frame_1663_1663 */


/**
 * Do unpacking and E2E validation of frame frame_1510.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B8_frame_1510_1510(const uint8_t frameContent[8])
{
    /* Unpack the data locally. */
    cap_B8_frame_1510_1510_t frameStructLocal;
    cap_unpack_B8_frame_1510_1510(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B8_frame_1510_1510(&frameStructLocal);

} /* End of ose_unpackAndCheck_B8_frame_1510_1510 */


/**
 * Do unpacking and E2E validation of frame frame_1460.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B8_frame_1460_1460(const uint8_t frameContent[4])
{
    /* Unpack the data locally. */
    cap_B8_frame_1460_1460_t frameStructLocal;
    cap_unpack_B8_frame_1460_1460(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B8_frame_1460_1460(&frameStructLocal);

} /* End of ose_unpackAndCheck_B8_frame_1460_1460 */


/**
 * Do unpacking and E2E validation of frame frame_653.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B8_frame_653_653(const uint8_t frameContent[7])
{
    /* Unpack the data locally. */
    cap_B8_frame_653_653_t frameStructLocal;
    cap_unpack_B8_frame_653_653(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B8_frame_653_653(&frameStructLocal);

} /* End of ose_unpackAndCheck_B8_frame_653_653 */


/**
 * Do unpacking and E2E validation of frame frame_699.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B8_frame_699_699(const uint8_t frameContent[4])
{
    /* Unpack the data locally. */
    cap_B8_frame_699_699_t frameStructLocal;
    cap_unpack_B8_frame_699_699(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B8_frame_699_699(&frameStructLocal);

} /* End of ose_unpackAndCheck_B8_frame_699_699 */


/**
 * Do unpacking and E2E validation of frame frame_970.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B8_frame_970_970(const uint8_t frameContent[3])
{
    /* Unpack the data locally. */
    cap_B8_frame_970_970_t frameStructLocal;
    cap_unpack_B8_frame_970_970(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B8_frame_970_970(&frameStructLocal);

} /* End of ose_unpackAndCheck_B8_frame_970_970 */


/**
 * Do unpacking and E2E validation of frame frame_305.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B8_frame_305_305(const uint8_t frameContent[5])
{
    /* Unpack the data locally. */
    cap_B8_frame_305_305_t frameStructLocal;
    cap_unpack_B8_frame_305_305(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B8_frame_305_305(&frameStructLocal);

} /* End of ose_unpackAndCheck_B8_frame_305_305 */


/**
 * Do unpacking and E2E validation of frame frame_309.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B8_frame_309_309(const uint8_t frameContent[6])
{
    /* Unpack the data locally. */
    cap_B8_frame_309_309_t frameStructLocal;
    cap_unpack_B8_frame_309_309(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B8_frame_309_309(&frameStructLocal);

} /* End of ose_unpackAndCheck_B8_frame_309_309 */


/**
 * Do unpacking and E2E validation of frame frame_231.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B8_frame_231_231(const uint8_t frameContent[1])
{
    /* Unpack the data locally. */
    cap_B8_frame_231_231_t frameStructLocal;
    cap_unpack_B8_frame_231_231(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B8_frame_231_231(&frameStructLocal);

} /* End of ose_unpackAndCheck_B8_frame_231_231 */


/**
 * Do unpacking and E2E validation of frame frame_1530.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B8_frame_1530_1530(const uint8_t frameContent[7])
{
    /* Unpack the data locally. */
    cap_B8_frame_1530_1530_t frameStructLocal;
    cap_unpack_B8_frame_1530_1530(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B8_frame_1530_1530(&frameStructLocal);

} /* End of ose_unpackAndCheck_B8_frame_1530_1530 */


/**
 * Do unpacking and E2E validation of frame frame_1676.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B9_frame_1676_1676(const uint8_t frameContent[7])
{
    /* Unpack the data locally. */
    cap_B9_frame_1676_1676_t frameStructLocal;
    cap_unpack_B9_frame_1676_1676(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B9_frame_1676_1676(&frameStructLocal);

} /* End of ose_unpackAndCheck_B9_frame_1676_1676 */


/**
 * Do unpacking and E2E validation of frame frame_1491.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B9_frame_1491_1491(const uint8_t frameContent[6])
{
    /* Unpack the data locally. */
    cap_B9_frame_1491_1491_t frameStructLocal;
    cap_unpack_B9_frame_1491_1491(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B9_frame_1491_1491(&frameStructLocal);

} /* End of ose_unpackAndCheck_B9_frame_1491_1491 */


/**
 * Do unpacking and E2E validation of frame frame_1536.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B9_frame_1536_1536(const uint8_t frameContent[4])
{
    /* Unpack the data locally. */
    cap_B9_frame_1536_1536_t frameStructLocal;
    cap_unpack_B9_frame_1536_1536(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B9_frame_1536_1536(&frameStructLocal);

} /* End of ose_unpackAndCheck_B9_frame_1536_1536 */


/**
 * Do unpacking and E2E validation of frame frame_621.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B9_frame_621_621(const uint8_t frameContent[4])
{
    /* Unpack the data locally. */
    cap_B9_frame_621_621_t frameStructLocal;
    cap_unpack_B9_frame_621_621(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B9_frame_621_621(&frameStructLocal);

} /* End of ose_unpackAndCheck_B9_frame_621_621 */


/**
 * Do unpacking and E2E validation of frame frame_538.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B9_frame_538_538(const uint8_t frameContent[8])
{
    /* Unpack the data locally. */
    cap_B9_frame_538_538_t frameStructLocal;
    cap_unpack_B9_frame_538_538(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B9_frame_538_538(&frameStructLocal);

} /* End of ose_unpackAndCheck_B9_frame_538_538 */


/**
 * Do unpacking and E2E validation of frame frame_1384.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B9_frame_1384_1384(const uint8_t frameContent[7])
{
    /* Unpack the data locally. */
    cap_B9_frame_1384_1384_t frameStructLocal;
    cap_unpack_B9_frame_1384_1384(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B9_frame_1384_1384(&frameStructLocal);

} /* End of ose_unpackAndCheck_B9_frame_1384_1384 */


/**
 * Do unpacking and E2E validation of frame frame_21.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B9_frame_21_21(const uint8_t frameContent[6])
{
    /* Unpack the data locally. */
    cap_B9_frame_21_21_t frameStructLocal;
    cap_unpack_B9_frame_21_21(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B9_frame_21_21(&frameStructLocal);

} /* End of ose_unpackAndCheck_B9_frame_21_21 */


/**
 * Do unpacking and E2E validation of frame frame_409.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B9_frame_409_409(const uint8_t frameContent[7])
{
    /* Unpack the data locally. */
    cap_B9_frame_409_409_t frameStructLocal;
    cap_unpack_B9_frame_409_409(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B9_frame_409_409(&frameStructLocal);

} /* End of ose_unpackAndCheck_B9_frame_409_409 */


/**
 * Do unpacking and E2E validation of frame frame_1148.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B9_frame_1148_1148(const uint8_t frameContent[7])
{
    /* Unpack the data locally. */
    cap_B9_frame_1148_1148_t frameStructLocal;
    cap_unpack_B9_frame_1148_1148(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B9_frame_1148_1148(&frameStructLocal);

} /* End of ose_unpackAndCheck_B9_frame_1148_1148 */


/**
 * Do unpacking and E2E validation of frame frame_1934.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B9_frame_1934_1934(const uint8_t frameContent[6])
{
    /* Unpack the data locally. */
    cap_B9_frame_1934_1934_t frameStructLocal;
    cap_unpack_B9_frame_1934_1934(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B9_frame_1934_1934(&frameStructLocal);

} /* End of ose_unpackAndCheck_B9_frame_1934_1934 */


/**
 * Do unpacking and E2E validation of frame frame_1538.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B9_frame_1538_1538(const uint8_t frameContent[8])
{
    /* Unpack the data locally. */
    cap_B9_frame_1538_1538_t frameStructLocal;
    cap_unpack_B9_frame_1538_1538(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B9_frame_1538_1538(&frameStructLocal);

} /* End of ose_unpackAndCheck_B9_frame_1538_1538 */


/**
 * Do unpacking and E2E validation of frame frame_1146.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B9_frame_1146_1146(const uint8_t frameContent[4])
{
    /* Unpack the data locally. */
    cap_B9_frame_1146_1146_t frameStructLocal;
    cap_unpack_B9_frame_1146_1146(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B9_frame_1146_1146(&frameStructLocal);

} /* End of ose_unpackAndCheck_B9_frame_1146_1146 */


/**
 * Do unpacking and E2E validation of frame frame_1025.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B9_frame_1025_1025(const uint8_t frameContent[5])
{
    /* Unpack the data locally. */
    cap_B9_frame_1025_1025_t frameStructLocal;
    cap_unpack_B9_frame_1025_1025(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B9_frame_1025_1025(&frameStructLocal);

} /* End of ose_unpackAndCheck_B9_frame_1025_1025 */


/**
 * Do unpacking and E2E validation of frame frame_1610.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B9_frame_1610_1610(const uint8_t frameContent[4])
{
    /* Unpack the data locally. */
    cap_B9_frame_1610_1610_t frameStructLocal;
    cap_unpack_B9_frame_1610_1610(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B9_frame_1610_1610(&frameStructLocal);

} /* End of ose_unpackAndCheck_B9_frame_1610_1610 */


/**
 * Do unpacking and E2E validation of frame frame_1315.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B9_frame_1315_1315(const uint8_t frameContent[7])
{
    /* Unpack the data locally. */
    cap_B9_frame_1315_1315_t frameStructLocal;
    cap_unpack_B9_frame_1315_1315(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B9_frame_1315_1315(&frameStructLocal);

} /* End of ose_unpackAndCheck_B9_frame_1315_1315 */


/**
 * Do unpacking and E2E validation of frame frame_900.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B9_frame_900_900(const uint8_t frameContent[7])
{
    /* Unpack the data locally. */
    cap_B9_frame_900_900_t frameStructLocal;
    cap_unpack_B9_frame_900_900(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B9_frame_900_900(&frameStructLocal);

} /* End of ose_unpackAndCheck_B9_frame_900_900 */


/**
 * Do unpacking and E2E validation of frame frame_171.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B9_frame_171_171(const uint8_t frameContent[5])
{
    /* Unpack the data locally. */
    cap_B9_frame_171_171_t frameStructLocal;
    cap_unpack_B9_frame_171_171(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B9_frame_171_171(&frameStructLocal);

} /* End of ose_unpackAndCheck_B9_frame_171_171 */


/**
 * Do unpacking and E2E validation of frame frame_240.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B9_frame_240_240(const uint8_t frameContent[5])
{
    /* Unpack the data locally. */
    cap_B9_frame_240_240_t frameStructLocal;
    cap_unpack_B9_frame_240_240(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B9_frame_240_240(&frameStructLocal);

} /* End of ose_unpackAndCheck_B9_frame_240_240 */


/**
 * Do unpacking and E2E validation of frame frame_178.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B9_frame_178_178(const uint8_t frameContent[6])
{
    /* Unpack the data locally. */
    cap_B9_frame_178_178_t frameStructLocal;
    cap_unpack_B9_frame_178_178(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B9_frame_178_178(&frameStructLocal);

} /* End of ose_unpackAndCheck_B9_frame_178_178 */


/**
 * Do unpacking and E2E validation of frame frame_2031.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B9_frame_2031_2031(const uint8_t frameContent[7])
{
    /* Unpack the data locally. */
    cap_B9_frame_2031_2031_t frameStructLocal;
    cap_unpack_B9_frame_2031_2031(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B9_frame_2031_2031(&frameStructLocal);

} /* End of ose_unpackAndCheck_B9_frame_2031_2031 */


/**
 * Do unpacking and E2E validation of frame frame_1935.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B9_frame_1935_1935(const uint8_t frameContent[8])
{
    /* Unpack the data locally. */
    cap_B9_frame_1935_1935_t frameStructLocal;
    cap_unpack_B9_frame_1935_1935(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B9_frame_1935_1935(&frameStructLocal);

} /* End of ose_unpackAndCheck_B9_frame_1935_1935 */


/**
 * Do unpacking and E2E validation of frame frame_1416.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B9_frame_1416_1416(const uint8_t frameContent[8])
{
    /* Unpack the data locally. */
    cap_B9_frame_1416_1416_t frameStructLocal;
    cap_unpack_B9_frame_1416_1416(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B9_frame_1416_1416(&frameStructLocal);

} /* End of ose_unpackAndCheck_B9_frame_1416_1416 */


/**
 * Do unpacking and E2E validation of frame frame_950.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B9_frame_950_950(const uint8_t frameContent[8])
{
    /* Unpack the data locally. */
    cap_B9_frame_950_950_t frameStructLocal;
    cap_unpack_B9_frame_950_950(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B9_frame_950_950(&frameStructLocal);

} /* End of ose_unpackAndCheck_B9_frame_950_950 */


/**
 * Do unpacking and E2E validation of frame frame_734.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B9_frame_734_734(const uint8_t frameContent[8])
{
    /* Unpack the data locally. */
    cap_B9_frame_734_734_t frameStructLocal;
    cap_unpack_B9_frame_734_734(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B9_frame_734_734(&frameStructLocal);

} /* End of ose_unpackAndCheck_B9_frame_734_734 */


/**
 * Do unpacking and E2E validation of frame frame_1565.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B9_frame_1565_1565(const uint8_t frameContent[8])
{
    /* Unpack the data locally. */
    cap_B9_frame_1565_1565_t frameStructLocal;
    cap_unpack_B9_frame_1565_1565(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B9_frame_1565_1565(&frameStructLocal);

} /* End of ose_unpackAndCheck_B9_frame_1565_1565 */


/**
 * Do unpacking and E2E validation of frame frame_1699.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B9_frame_1699_1699(const uint8_t frameContent[6])
{
    /* Unpack the data locally. */
    cap_B9_frame_1699_1699_t frameStructLocal;
    cap_unpack_B9_frame_1699_1699(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B9_frame_1699_1699(&frameStructLocal);

} /* End of ose_unpackAndCheck_B9_frame_1699_1699 */


/**
 * Do unpacking and E2E validation of frame frame_1698.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B9_frame_1698_1698(const uint8_t frameContent[7])
{
    /* Unpack the data locally. */
    cap_B9_frame_1698_1698_t frameStructLocal;
    cap_unpack_B9_frame_1698_1698(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B9_frame_1698_1698(&frameStructLocal);

} /* End of ose_unpackAndCheck_B9_frame_1698_1698 */


/**
 * Do unpacking and E2E validation of frame frame_1854.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B9_frame_1854_1854(const uint8_t frameContent[8])
{
    /* Unpack the data locally. */
    cap_B9_frame_1854_1854_t frameStructLocal;
    cap_unpack_B9_frame_1854_1854(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B9_frame_1854_1854(&frameStructLocal);

} /* End of ose_unpackAndCheck_B9_frame_1854_1854 */


/**
 * Do unpacking and E2E validation of frame frame_1142.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B9_frame_1142_1142(const uint8_t frameContent[6])
{
    /* Unpack the data locally. */
    cap_B9_frame_1142_1142_t frameStructLocal;
    cap_unpack_B9_frame_1142_1142(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B9_frame_1142_1142(&frameStructLocal);

} /* End of ose_unpackAndCheck_B9_frame_1142_1142 */


/**
 * Do unpacking and E2E validation of frame frame_1007.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B9_frame_1007_1007(const uint8_t frameContent[8])
{
    /* Unpack the data locally. */
    cap_B9_frame_1007_1007_t frameStructLocal;
    cap_unpack_B9_frame_1007_1007(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B9_frame_1007_1007(&frameStructLocal);

} /* End of ose_unpackAndCheck_B9_frame_1007_1007 */


/**
 * Do unpacking and E2E validation of frame frame_1613.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B9_frame_1613_1613(const uint8_t frameContent[6])
{
    /* Unpack the data locally. */
    cap_B9_frame_1613_1613_t frameStructLocal;
    cap_unpack_B9_frame_1613_1613(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B9_frame_1613_1613(&frameStructLocal);

} /* End of ose_unpackAndCheck_B9_frame_1613_1613 */


/**
 * Do unpacking and E2E validation of frame frame_627.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B9_frame_627_627(const uint8_t frameContent[8])
{
    /* Unpack the data locally. */
    cap_B9_frame_627_627_t frameStructLocal;
    cap_unpack_B9_frame_627_627(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B9_frame_627_627(&frameStructLocal);

} /* End of ose_unpackAndCheck_B9_frame_627_627 */


/**
 * Do unpacking and E2E validation of frame frame_973.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B9_frame_973_973(const uint8_t frameContent[8])
{
    /* Unpack the data locally. */
    cap_B9_frame_973_973_t frameStructLocal;
    cap_unpack_B9_frame_973_973(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B9_frame_973_973(&frameStructLocal);

} /* End of ose_unpackAndCheck_B9_frame_973_973 */


/**
 * Do unpacking and E2E validation of frame frame_1362.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B9_frame_1362_1362(const uint8_t frameContent[7])
{
    /* Unpack the data locally. */
    cap_B9_frame_1362_1362_t frameStructLocal;
    cap_unpack_B9_frame_1362_1362(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B9_frame_1362_1362(&frameStructLocal);

} /* End of ose_unpackAndCheck_B9_frame_1362_1362 */


/**
 * Do unpacking and E2E validation of frame frame_612.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B10_frame_612_612(const uint8_t frameContent[5])
{
    /* Unpack the data locally. */
    cap_B10_frame_612_612_t frameStructLocal;
    cap_unpack_B10_frame_612_612(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B10_frame_612_612(&frameStructLocal);

} /* End of ose_unpackAndCheck_B10_frame_612_612 */


/**
 * Do unpacking and E2E validation of frame frame_5.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B10_frame_5_5(const uint8_t frameContent[4])
{
    /* Unpack the data locally. */
    cap_B10_frame_5_5_t frameStructLocal;
    cap_unpack_B10_frame_5_5(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B10_frame_5_5(&frameStructLocal);

} /* End of ose_unpackAndCheck_B10_frame_5_5 */


/**
 * Do unpacking and E2E validation of frame frame_1477.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B10_frame_1477_1477(const uint8_t frameContent[6])
{
    /* Unpack the data locally. */
    cap_B10_frame_1477_1477_t frameStructLocal;
    cap_unpack_B10_frame_1477_1477(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B10_frame_1477_1477(&frameStructLocal);

} /* End of ose_unpackAndCheck_B10_frame_1477_1477 */


/**
 * Do unpacking and E2E validation of frame frame_1604.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B10_frame_1604_1604(const uint8_t frameContent[7])
{
    /* Unpack the data locally. */
    cap_B10_frame_1604_1604_t frameStructLocal;
    cap_unpack_B10_frame_1604_1604(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B10_frame_1604_1604(&frameStructLocal);

} /* End of ose_unpackAndCheck_B10_frame_1604_1604 */


/**
 * Do unpacking and E2E validation of frame frame_36.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B10_frame_36_36(const uint8_t frameContent[7])
{
    /* Unpack the data locally. */
    cap_B10_frame_36_36_t frameStructLocal;
    cap_unpack_B10_frame_36_36(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B10_frame_36_36(&frameStructLocal);

} /* End of ose_unpackAndCheck_B10_frame_36_36 */


/**
 * Do unpacking and E2E validation of frame frame_2001.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B10_frame_2001_2001(const uint8_t frameContent[6])
{
    /* Unpack the data locally. */
    cap_B10_frame_2001_2001_t frameStructLocal;
    cap_unpack_B10_frame_2001_2001(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B10_frame_2001_2001(&frameStructLocal);

} /* End of ose_unpackAndCheck_B10_frame_2001_2001 */


/**
 * Do unpacking and E2E validation of frame frame_80.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B10_frame_80_80(const uint8_t frameContent[6])
{
    /* Unpack the data locally. */
    cap_B10_frame_80_80_t frameStructLocal;
    cap_unpack_B10_frame_80_80(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B10_frame_80_80(&frameStructLocal);

} /* End of ose_unpackAndCheck_B10_frame_80_80 */


/**
 * Do unpacking and E2E validation of frame frame_0.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B10_frame_0_0(const uint8_t frameContent[5])
{
    /* Unpack the data locally. */
    cap_B10_frame_0_0_t frameStructLocal;
    cap_unpack_B10_frame_0_0(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B10_frame_0_0(&frameStructLocal);

} /* End of ose_unpackAndCheck_B10_frame_0_0 */


/**
 * Do unpacking and E2E validation of frame frame_1494.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B10_frame_1494_1494(const uint8_t frameContent[4])
{
    /* Unpack the data locally. */
    cap_B10_frame_1494_1494_t frameStructLocal;
    cap_unpack_B10_frame_1494_1494(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B10_frame_1494_1494(&frameStructLocal);

} /* End of ose_unpackAndCheck_B10_frame_1494_1494 */


/**
 * Do unpacking and E2E validation of frame frame_537.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B10_frame_537_537(const uint8_t frameContent[7])
{
    /* Unpack the data locally. */
    cap_B10_frame_537_537_t frameStructLocal;
    cap_unpack_B10_frame_537_537(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B10_frame_537_537(&frameStructLocal);

} /* End of ose_unpackAndCheck_B10_frame_537_537 */


/**
 * Do unpacking and E2E validation of frame frame_741.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B10_frame_741_741(const uint8_t frameContent[6])
{
    /* Unpack the data locally. */
    cap_B10_frame_741_741_t frameStructLocal;
    cap_unpack_B10_frame_741_741(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B10_frame_741_741(&frameStructLocal);

} /* End of ose_unpackAndCheck_B10_frame_741_741 */


/**
 * Do unpacking and E2E validation of frame frame_1396.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B10_frame_1396_1396(const uint8_t frameContent[2])
{
    /* Unpack the data locally. */
    cap_B10_frame_1396_1396_t frameStructLocal;
    cap_unpack_B10_frame_1396_1396(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B10_frame_1396_1396(&frameStructLocal);

} /* End of ose_unpackAndCheck_B10_frame_1396_1396 */


/**
 * Do unpacking and E2E validation of frame frame_207.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B10_frame_207_207(const uint8_t frameContent[7])
{
    /* Unpack the data locally. */
    cap_B10_frame_207_207_t frameStructLocal;
    cap_unpack_B10_frame_207_207(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B10_frame_207_207(&frameStructLocal);

} /* End of ose_unpackAndCheck_B10_frame_207_207 */


/**
 * Do unpacking and E2E validation of frame frame_1996.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B10_frame_1996_1996(const uint8_t frameContent[7])
{
    /* Unpack the data locally. */
    cap_B10_frame_1996_1996_t frameStructLocal;
    cap_unpack_B10_frame_1996_1996(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B10_frame_1996_1996(&frameStructLocal);

} /* End of ose_unpackAndCheck_B10_frame_1996_1996 */


/**
 * Do unpacking and E2E validation of frame frame_1505.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B10_frame_1505_1505(const uint8_t frameContent[6])
{
    /* Unpack the data locally. */
    cap_B10_frame_1505_1505_t frameStructLocal;
    cap_unpack_B10_frame_1505_1505(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B10_frame_1505_1505(&frameStructLocal);

} /* End of ose_unpackAndCheck_B10_frame_1505_1505 */


/**
 * Do unpacking and E2E validation of frame frame_26.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B10_frame_26_26(const uint8_t frameContent[7])
{
    /* Unpack the data locally. */
    cap_B10_frame_26_26_t frameStructLocal;
    cap_unpack_B10_frame_26_26(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B10_frame_26_26(&frameStructLocal);

} /* End of ose_unpackAndCheck_B10_frame_26_26 */


/**
 * Do unpacking and E2E validation of frame frame_515.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B10_frame_515_515(const uint8_t frameContent[4])
{
    /* Unpack the data locally. */
    cap_B10_frame_515_515_t frameStructLocal;
    cap_unpack_B10_frame_515_515(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B10_frame_515_515(&frameStructLocal);

} /* End of ose_unpackAndCheck_B10_frame_515_515 */


/**
 * Do unpacking and E2E validation of frame frame_677.\n
 *   The frame contents are locally unpacked. All signals of the frame, ending with the CRC
 * checksum, are read from this buffer and serialized into a temporary buffer. The CRC of
 * this buffer is computed and compared to the unpacked check value.
 *   @return
 * The function returns \a true if and only if the expected check value of the CRC is seen.
 * If so, E2E protection approves the correct data contents of the frame.
 */
boolean_t ose_unpackAndCheck_B10_frame_677_677(const uint8_t frameContent[4])
{
    /* Unpack the data locally. */
    cap_B10_frame_677_677_t frameStructLocal;
    cap_unpack_B10_frame_677_677(&frameStructLocal, &frameContent[0]);

    /* Run the E2E validation on the unpacked frame and return the result. */
    return e2e_check_B10_frame_677_677(&frameStructLocal);

} /* End of ose_unpackAndCheck_B10_frame_677_677 */


