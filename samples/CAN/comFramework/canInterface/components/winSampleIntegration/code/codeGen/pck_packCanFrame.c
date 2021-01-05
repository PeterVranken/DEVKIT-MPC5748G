/**
 * @file pck_packCanFrame.c
 * Implementation of pack/unpack functions for the CAN frames of cluster winSampleIntegration.
 *
 * This file has been created with comFramework - codeGenerator version 1.10.0,
 * see http://sourceforge.net/projects/comframe/
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

#include <string.h>
#include <assert.h>

#include "types.h"
#include "pck_packCanFrame.h"


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

/** Signals and transmission status of CAN frame StateEcu01 (1024, 0x400) on bus PT.
    This global variable is used as API between CAN interface and APSW. */
pck_API_PT_StateEcu01_1024_t pck_API_PT_StateEcu01_1024 =
{
    .signals =
    {
        .checksum = 0,
        .speedOfRotation = (uint16_t)((0.0 /* rpm */ - 0.0) / 0.1),
        .sequenceCounter = 0,
    },

    .stsTransmission = cbk_stsTransm_neverReceived
};


/** Signals and transmission status of CAN frame StateEcu02 (1040, 0x410) on bus PT.
    This global variable is used as API between CAN interface and APSW. */
pck_API_PT_StateEcu02_1040_t pck_API_PT_StateEcu02_1040 =
{
    .signals =
    {
        .checksum = 0,
        .sequenceCounter = 0,
        .torque = (int16_t)((0.0 /* Nm */ - 0.0) / 0.5),
    },

    .stsTransmission = cbk_stsTransm_neverReceived
};


/** Signals and transmission status of CAN frame UserLimits (2032, 0x7f0) on bus PT.
    This global variable is used as API between CAN interface and APSW. */
pck_API_PT_UserLimits_2032_t pck_API_PT_UserLimits_2032 =
{
    .signals =
    {
        .sequenceCounter = 1,
        .minSpeedOfRotation = (uint16_t)((800.0 /* rpm */ - 0.0) / 1.6),
        .maxSpeedOfRotation = (uint16_t)((6000.0 /* rpm */ - 0.0) / 1.6),
        .checksum = 0,
        .minPower = (uint16_t)((-1.0 /* KW */ - -10.0) / 0.5),
        .maxPower = (uint16_t)((100.0 /* KW */ - -10.0) / 0.5),
    },

    .stsTransmission = cbk_stsTransm_neverReceived
};


/** Signals and transmission status of CAN frame InfoPowerDisplay (1536, 0x600) on bus PT.
    This global variable is used as API between CAN interface and APSW. */
pck_API_PT_InfoPowerDisplay_1536_t pck_API_PT_InfoPowerDisplay_1536 =
{
    .signals =
    {
        .checksum = 0,
        .sequenceCounter = 0,
        .power = (uint16_t)((0.0 /* W */ - -500000.0) / 32.0),
        .state = 0,
    },

    .stsTransmission = cbk_stsTransm_okay
};


/** Signals and transmission status of CAN frame StatusPowerDisplay (1537, 0x601) on bus PT.
    This global variable is used as API between CAN interface and APSW. */
pck_API_PT_StatusPowerDisplay_1537_t pck_API_PT_StatusPowerDisplay_1537 =
{
    .signals =
    {
        .noDlcErrors = 0,
        .noCheckSumErrors = 0,
        .noSqcErrors = 0,
        .sequenceCounter = 1,
        .checksum = 0,
    },

    .stsTransmission = cbk_stsTransm_okay
};


/** Signals and transmission status of CAN frame LimitsPowerDisplay (1538, 0x602) on bus PT.
    This global variable is used as API between CAN interface and APSW. */
pck_API_PT_LimitsPowerDisplay_1538_t pck_API_PT_LimitsPowerDisplay_1538 =
{
    .signals =
    {
        .sequenceCounter = 6,
        .belowMinSpeedOfRotation = 0,
        .aboveMaxSpeedOfRotation = 0,
        .belowMinPower = 0,
        .aboveMaxPower = 0,
    },

    .stsTransmission = cbk_stsTransm_okay
};


 

/*
 * Function implementation
 */

#if PCK_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU StateEcu01 (1024, 0x400) on bus PT into a byte
 * array of 4 Byte.\n
 *   The signal values are read from the global interface struct pck_API_PT_StateEcu01_1024.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void pck_pack_PT_StateEcu01_1024(uint8_t m[])
{
    /* The further commands will partly use bitwise OR commands to write the signal values.
       Those bytes, which are not entirely occupied by the signals need to be cleared at
       the beginning. */
    m[1] = 0x00;
    m[3] = 0x00;

    /* Pack signal checksum. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pck_API_PT_StateEcu01_1024.signals.checksum;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (uint8_t)s;
    }

    /* Pack signal speedOfRotation. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint32_t s = (uint32_t)pck_API_PT_StateEcu01_1024.signals.speedOfRotation << 4;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[3] |= (uint8_t)(s & 0xf0);
        s >>= 8;
        m[2] = (uint8_t)s;
        s >>= 8;
        m[1] |= (uint8_t)(s & 0x0f);
    }

    /* Pack signal sequenceCounter. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pck_API_PT_StateEcu01_1024.signals.sequenceCounter << 4;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] |= (uint8_t)(s & 0xf0);
    }
} /* End of pck_pack_PT_StateEcu01_1024 */
#endif



/**
 * Unpack the signals of inbound PDU StateEcu01 (1024, 0x400) on bus PT from a byte
 * array of 4 Byte.\n
 *   The signal values are written into the global interface struct pck_API_PT_StateEcu01_1024.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void pck_unpack_PT_StateEcu01_1024(const uint8_t m[])
{
    /* Decode all normal, not multiplexed signals. */
    pck_API_PT_StateEcu01_1024.signals.checksum = (uint8_t)((uint8_t)m[0]);
    pck_API_PT_StateEcu01_1024.signals.speedOfRotation = (uint16_t)(((((((uint32_t)(m[1] & 0x0f)) << 8) | m[2]) << 8) | m[3]) >> 4);
    pck_API_PT_StateEcu01_1024.signals.sequenceCounter = (uint8_t)(((uint8_t)(m[1] & 0xf0)) >> 4);

} /* End of pck_unpack_PT_StateEcu01_1024 */



#if PCK_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU StateEcu02 (1040, 0x410) on bus PT into a byte
 * array of 4 Byte.\n
 *   The signal values are read from the global interface struct pck_API_PT_StateEcu02_1040.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void pck_pack_PT_StateEcu02_1040(uint8_t m[])
{
    /* The further commands will partly use bitwise OR commands to write the signal values.
       Those bytes, which are not entirely occupied by the signals need to be cleared at
       the beginning. */
    m[1] = 0x00;
    m[2] = 0x00;
    m[3] = 0x00;

    /* Pack signal checksum. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pck_API_PT_StateEcu02_1040.signals.checksum;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (uint8_t)s;
    }

    /* Pack signal sequenceCounter. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pck_API_PT_StateEcu02_1040.signals.sequenceCounter;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] |= (uint8_t)(s & 0x0f);
    }

    /* Pack signal torque. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint16_t s = (uint16_t)pck_API_PT_StateEcu02_1040.signals.torque << (5-1);

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[3] |= (uint8_t)(s & 0xf0);
        s >>= 8;
        m[2] |= (uint8_t)(s & 0x7f);
    }
} /* End of pck_pack_PT_StateEcu02_1040 */
#endif



/**
 * Unpack the signals of inbound PDU StateEcu02 (1040, 0x410) on bus PT from a byte
 * array of 4 Byte.\n
 *   The signal values are written into the global interface struct pck_API_PT_StateEcu02_1040.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void pck_unpack_PT_StateEcu02_1040(const uint8_t m[])
{
    /* Decode all normal, not multiplexed signals. */
    pck_API_PT_StateEcu02_1040.signals.checksum = (uint8_t)((uint8_t)m[0]);
    pck_API_PT_StateEcu02_1040.signals.sequenceCounter = (uint8_t)((uint8_t)(m[1] & 0x0f));
    pck_API_PT_StateEcu02_1040.signals.torque = (int16_t)((int16_t)(((((uint16_t)m[2]) << 8) | m[3]) << 1) >> 5);

} /* End of pck_unpack_PT_StateEcu02_1040 */



#if PCK_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU UserLimits (2032, 0x7f0) on bus PT into a byte
 * array of 8 Byte.\n
 *   The signal values are read from the global interface struct pck_API_PT_UserLimits_2032.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void pck_pack_PT_UserLimits_2032(uint8_t m[])
{
    /* The further commands will partly use bitwise OR commands to write the signal values.
       Those bytes, which are not entirely occupied by the signals need to be cleared at
       the beginning. */
    memset(m, /* value */ 0, /* noBytes */ 8);

    /* Pack signal sequenceCounter. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pck_API_PT_UserLimits_2032.signals.sequenceCounter << 2;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] |= (uint8_t)(s & 0x3c);
    }

    /* Pack signal minSpeedOfRotation. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint32_t s = (uint32_t)pck_API_PT_UserLimits_2032.signals.minSpeedOfRotation << 6;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] |= (uint8_t)(s & 0xc0);
        s >>= 8;
        m[1] = (uint8_t)s;
        s >>= 8;
        m[2] |= (uint8_t)(s & 0x03);
    }

    /* Pack signal maxSpeedOfRotation. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint16_t s = (uint16_t)pck_API_PT_UserLimits_2032.signals.maxSpeedOfRotation << 2;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[2] |= (uint8_t)(s & 0xfc);
        s >>= 8;
        m[3] |= (uint8_t)(s & 0x3f);
    }

    /* Pack signal checksum. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pck_API_PT_UserLimits_2032.signals.checksum;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[4] = (uint8_t)s;
    }

    /* Pack signal minPower. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint16_t s = (uint16_t)pck_API_PT_UserLimits_2032.signals.minPower << 7;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[6] |= (uint8_t)(s & 0x80);
        s >>= 8;
        m[5] = (uint8_t)s;
    }

    /* Pack signal maxPower. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint16_t s = (uint16_t)pck_API_PT_UserLimits_2032.signals.maxPower << 5;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[7] |= (uint8_t)(s & 0xe0);
        s >>= 8;
        m[6] |= (uint8_t)(s & 0x3f);
    }
} /* End of pck_pack_PT_UserLimits_2032 */
#endif



/**
 * Unpack the signals of inbound PDU UserLimits (2032, 0x7f0) on bus PT from a byte
 * array of 8 Byte.\n
 *   The signal values are written into the global interface struct pck_API_PT_UserLimits_2032.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void pck_unpack_PT_UserLimits_2032(const uint8_t m[])
{
    /* Decode all normal, not multiplexed signals. */
    pck_API_PT_UserLimits_2032.signals.sequenceCounter = (uint8_t)(((uint8_t)(m[0] & 0x3c)) >> 2);
    pck_API_PT_UserLimits_2032.signals.minSpeedOfRotation = (uint16_t)(((((((uint32_t)(m[2] & 0x03)) << 8) | m[1]) << 8) | m[0]) >> 6);
    pck_API_PT_UserLimits_2032.signals.maxSpeedOfRotation = (uint16_t)(((((uint16_t)(m[3] & 0x3f)) << 8) | m[2]) >> 2);
    pck_API_PT_UserLimits_2032.signals.checksum = (uint8_t)((uint8_t)m[4]);
    pck_API_PT_UserLimits_2032.signals.minPower = (uint16_t)(((((uint16_t)m[5]) << 8) | m[6]) >> 7);
    pck_API_PT_UserLimits_2032.signals.maxPower = (uint16_t)(((((uint16_t)(m[6] & 0x3f)) << 8) | m[7]) >> 5);

} /* End of pck_unpack_PT_UserLimits_2032 */


/**
 * Pack the signals of outbound PDU InfoPowerDisplay (1536, 0x600) on bus PT into a byte
 * array of 6 Byte.\n
 *   The signal values are read from the global interface struct pck_API_PT_InfoPowerDisplay_1536.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void pck_pack_PT_InfoPowerDisplay_1536(uint8_t m[])
{
    /* The further commands will partly use bitwise OR commands to write the signal values.
       Those bytes, which are not entirely occupied by the signals need to be cleared at
       the beginning. */
    memset(m, /* value */ 0, /* noBytes */ 6);

    /* Pack signal checksum. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pck_API_PT_InfoPowerDisplay_1536.signals.checksum;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (uint8_t)s;
    }

    /* Pack signal sequenceCounter. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pck_API_PT_InfoPowerDisplay_1536.signals.sequenceCounter;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] |= (uint8_t)(s & 0x0f);
    }

    /* Pack signal power. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint32_t s = (uint32_t)pck_API_PT_InfoPowerDisplay_1536.signals.power << 5;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] |= (uint8_t)(s & 0xe0);
        s >>= 8;
        m[2] = (uint8_t)s;
        s >>= 8;
        m[3] |= (uint8_t)(s & 0x0f);
    }

    /* Pack signal state. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint16_t s = (uint16_t)pck_API_PT_InfoPowerDisplay_1536.signals.state << 7;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[5] |= (uint8_t)(s & 0x80);
        s >>= 8;
        m[4] |= (uint8_t)(s & 0x03);
    }
} /* End of pck_pack_PT_InfoPowerDisplay_1536 */


#if PCK_UNCONDITIONALLY_GENERATE_UNPACK_FCTS != 0
/**
 * Unpack the signals of outbound PDU InfoPowerDisplay (1536, 0x600) on bus PT from a byte
 * array of 6 Byte.\n
 *   The signal values are written into the global interface struct pck_API_PT_InfoPowerDisplay_1536.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void pck_unpack_PT_InfoPowerDisplay_1536(const uint8_t m[])
{
    /* Decode all normal, not multiplexed signals. */
    pck_API_PT_InfoPowerDisplay_1536.signals.checksum = (uint8_t)((uint8_t)m[0]);
    pck_API_PT_InfoPowerDisplay_1536.signals.sequenceCounter = (uint8_t)((uint8_t)(m[1] & 0x0f));
    pck_API_PT_InfoPowerDisplay_1536.signals.power = (uint16_t)(((((((uint32_t)(m[3] & 0x0f)) << 8) | m[2]) << 8) | m[1]) >> 5);
    pck_API_PT_InfoPowerDisplay_1536.signals.state = (uint8_t)(((((uint16_t)(m[4] & 0x03)) << 8) | m[5]) >> 7);

} /* End of pck_unpack_PT_InfoPowerDisplay_1536 */
#endif



/**
 * Pack the signals of outbound PDU StatusPowerDisplay (1537, 0x601) on bus PT into a byte
 * array of 6 Byte.\n
 *   The signal values are read from the global interface struct pck_API_PT_StatusPowerDisplay_1537.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void pck_pack_PT_StatusPowerDisplay_1537(uint8_t m[])
{
    /* The further commands will partly use bitwise OR commands to write the signal values.
       Those bytes, which are not entirely occupied by the signals need to be cleared at
       the beginning. */
    m[1] = 0x00;
    m[2] = 0x00;
    m[4] = 0x00;

    /* Pack signal noDlcErrors. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint16_t s = (uint16_t)pck_API_PT_StatusPowerDisplay_1537.signals.noDlcErrors;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (uint8_t)s;
        s >>= 8;
        m[1] |= (uint8_t)(s & 0x07);
    }

    /* Pack signal noCheckSumErrors. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint16_t s = (uint16_t)pck_API_PT_StatusPowerDisplay_1537.signals.noCheckSumErrors << 3;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] |= (uint8_t)(s & 0xf8);
        s >>= 8;
        m[2] |= (uint8_t)(s & 0x3f);
    }

    /* Pack signal noSqcErrors. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint32_t s = (uint32_t)pck_API_PT_StatusPowerDisplay_1537.signals.noSqcErrors << 6;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[2] |= (uint8_t)(s & 0xc0);
        s >>= 8;
        m[3] = (uint8_t)s;
        s >>= 8;
        m[4] |= (uint8_t)(s & 0x01);
    }

    /* Pack signal sequenceCounter. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pck_API_PT_StatusPowerDisplay_1537.signals.sequenceCounter << 1;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[4] |= (uint8_t)(s & 0xfe);
    }

    /* Pack signal checksum. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pck_API_PT_StatusPowerDisplay_1537.signals.checksum;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[5] = (uint8_t)s;
    }
} /* End of pck_pack_PT_StatusPowerDisplay_1537 */


#if PCK_UNCONDITIONALLY_GENERATE_UNPACK_FCTS != 0
/**
 * Unpack the signals of outbound PDU StatusPowerDisplay (1537, 0x601) on bus PT from a byte
 * array of 6 Byte.\n
 *   The signal values are written into the global interface struct pck_API_PT_StatusPowerDisplay_1537.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void pck_unpack_PT_StatusPowerDisplay_1537(const uint8_t m[])
{
    /* Decode all normal, not multiplexed signals. */
    pck_API_PT_StatusPowerDisplay_1537.signals.noDlcErrors = (uint16_t)((((uint16_t)(m[1] & 0x07)) << 8) | m[0]);
    pck_API_PT_StatusPowerDisplay_1537.signals.noCheckSumErrors = (uint16_t)(((((uint16_t)(m[2] & 0x3f)) << 8) | m[1]) >> 3);
    pck_API_PT_StatusPowerDisplay_1537.signals.noSqcErrors = (uint16_t)(((((((uint32_t)(m[4] & 0x01)) << 8) | m[3]) << 8) | m[2]) >> 6);
    pck_API_PT_StatusPowerDisplay_1537.signals.sequenceCounter = (uint8_t)(((uint8_t)(m[4] & 0xfe)) >> 1);
    pck_API_PT_StatusPowerDisplay_1537.signals.checksum = (uint8_t)((uint8_t)m[5]);

} /* End of pck_unpack_PT_StatusPowerDisplay_1537 */
#endif



/**
 * Pack the signals of outbound PDU LimitsPowerDisplay (1538, 0x602) on bus PT into a byte
 * array of 1 Byte.\n
 *   The signal values are read from the global interface struct pck_API_PT_LimitsPowerDisplay_1538.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void pck_pack_PT_LimitsPowerDisplay_1538(uint8_t m[])
{
    /* The further commands will partly use bitwise OR commands to write the signal values.
       Those bytes, which are not entirely occupied by the signals need to be cleared at
       the beginning. */
    m[0] = 0x00;

    /* Pack signal sequenceCounter. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pck_API_PT_LimitsPowerDisplay_1538.signals.sequenceCounter;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] |= (uint8_t)(s & 0x07);
    }

    /* Pack signal belowMinSpeedOfRotation. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pck_API_PT_LimitsPowerDisplay_1538.signals.belowMinSpeedOfRotation << 3;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] |= (uint8_t)(s & 0x08);
    }

    /* Pack signal aboveMaxSpeedOfRotation. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pck_API_PT_LimitsPowerDisplay_1538.signals.aboveMaxSpeedOfRotation << 4;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] |= (uint8_t)(s & 0x10);
    }

    /* Pack signal belowMinPower. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pck_API_PT_LimitsPowerDisplay_1538.signals.belowMinPower << 5;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] |= (uint8_t)(s & 0x20);
    }

    /* Pack signal aboveMaxPower. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pck_API_PT_LimitsPowerDisplay_1538.signals.aboveMaxPower << 6;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] |= (uint8_t)(s & 0x40);
    }
} /* End of pck_pack_PT_LimitsPowerDisplay_1538 */


#if PCK_UNCONDITIONALLY_GENERATE_UNPACK_FCTS != 0
/**
 * Unpack the signals of outbound PDU LimitsPowerDisplay (1538, 0x602) on bus PT from a byte
 * array of 1 Byte.\n
 *   The signal values are written into the global interface struct pck_API_PT_LimitsPowerDisplay_1538.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void pck_unpack_PT_LimitsPowerDisplay_1538(const uint8_t m[])
{
    /* Decode all normal, not multiplexed signals. */
    pck_API_PT_LimitsPowerDisplay_1538.signals.sequenceCounter = (uint8_t)((uint8_t)(m[0] & 0x07));
    pck_API_PT_LimitsPowerDisplay_1538.signals.belowMinSpeedOfRotation = (boolean_t)(((uint8_t)(m[0] & 0x08)) >> 3);
    pck_API_PT_LimitsPowerDisplay_1538.signals.aboveMaxSpeedOfRotation = (boolean_t)(((uint8_t)(m[0] & 0x10)) >> 4);
    pck_API_PT_LimitsPowerDisplay_1538.signals.belowMinPower = (boolean_t)(((uint8_t)(m[0] & 0x20)) >> 5);
    pck_API_PT_LimitsPowerDisplay_1538.signals.aboveMaxPower = (boolean_t)(((uint8_t)(m[0] & 0x40)) >> 6);

} /* End of pck_unpack_PT_LimitsPowerDisplay_1538 */
#endif



