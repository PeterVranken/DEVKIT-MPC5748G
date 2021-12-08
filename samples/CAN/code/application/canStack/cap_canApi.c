/**
 * @file cap_canApi.c
 * 
 * This file implements the data oriented CAN API between the APSW code and the upper
 * layers of the CAN stack. The global data structure is initialized with the initial
 * signal values from the CAN network database.\n
 *   The integration of the API with the CAN stack is supported by a set of pack and unpack
 * functions; one such pair of functions is available for each CAN frame. The pack function
 * composes the binary frame contents from the set of signal values found in the API and
 * the counterpart function (unpack) decomposes received binary frame content data into
 * distinct signal values, which are placed into the API.\n
 *   The functions are globally accessible; their names are composed such that name clashes
 * across different buses won't appear even if frames of same name and ID are
 * transmitted.\n
 *   Note, concurrency is not handled here. Particularly for CAN input, data reception and
 * decomposition of the frame contents into signals might be an asynchronous event. If so,
 * the caller of the unpack function would have to add appropriate code to implement mutual
 * exclusion with the Embedded Coder generated APSW code, which also accesses the API data.
 * Although less likely may the same hold for CAN output.
 *
 * This file has been created with comFramework - codeGenerator version 1.10.4,
 * see http://sourceforge.net/projects/comframe/
 *
 * Copyright (C) 2021 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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

#include "typ_types.h"
#include "cap_canApi.h"


/*
 * Defines
 */

/* Check the values of the frame and special signal related #define's. Compilation errors
   can occur due to incompatibilites between the code generation templates and the actual
   network databases. */
#define CAP_INCLUDES_PRECO_CHECKS
#include "cap_precoCheck.h"


/*
 * Local type definitions
 */


/*
 * Local prototypes
 */


/*
 * Data definitions
 */

/** Signals and transmission status of the CAN frames on bus PWM. This global
    variable is used as API between the platform's CAN interface and the APSW. */
cap_canBus_PWM_t cap_canBus_PWM =
{
    /** Signals and transmission status of outbound CAN frame PWM_in
        (1000, 0x3e8) on bus PWM. */
    .PWM_PWM_in_1000_sts =
    {
        .signals =
        {
            .PA2_J3_pin3_periodTime = CAP_PWM_1000_PA2_J3_pin3_periodTime_DBL_TO_BIN(0.0),
            .PA2_J3_pin3_isNew = 0,
            .PA6_J2_pin1_isNew = 0,
            .PA6_J2_pin1_dutyTime = CAP_PWM_1000_PA6_J2_pin1_dutyTime_DBL_TO_BIN(0.0),
            .PA2_PA6_dutyCycle = CAP_PWM_1000_PA2_PA6_dutyCycle_DBL_TO_BIN(0.0),
            .PA2_J3_pin3_frequency = CAP_PWM_1000_PA2_J3_pin3_frequency_DBL_TO_BIN(0.0),
        },

        .infoTransmission =
        {
            .stsTransmission = cap_stsTransm_okay,
            .noTransmittedFrames = 0,
            .isEvent = false,
        },
    },

    /** Signals and transmission status of inbound CAN frame PWM_out
        (1001, 0x3e9) on bus PWM. */
    .PWM_PWM_out_1001_sts =
    {
        .signals =
        {
            .LED_2_DS10_inhibit = 1,
            .LED_4_DS11_inhibit = 1,
            .LED_5_DS5_inhibit = 1,
            .PA1_J3_pin1_inhibit = 1,
            .LED_2_DS10_frequency = CAP_PWM_1001_LED_2_DS10_frequency_DBL_TO_BIN(1.5),
            .LED_4_DS11_frequency = CAP_PWM_1001_LED_4_DS11_frequency_DBL_TO_BIN(2.5),
            .LED_5_DS5_frequency = CAP_PWM_1001_LED_5_DS5_frequency_DBL_TO_BIN(4.0),
            .PA1_J3_pin1_frequency = CAP_PWM_1001_PA1_J3_pin1_frequency_DBL_TO_BIN(1000.0),
            .LED_2_DS10_dutyCycle = CAP_PWM_1001_LED_2_DS10_dutyCycle_DBL_TO_BIN(30.0),
            .LED_4_DS11_dutyCycle = CAP_PWM_1001_LED_4_DS11_dutyCycle_DBL_TO_BIN(55.0),
            .LED_5_DS5_dutyCycle = CAP_PWM_1001_LED_5_DS5_dutyCycle_DBL_TO_BIN(15.0),
            .PA1_J3_pin1_dutyCycle = CAP_PWM_1001_PA1_J3_pin1_dutyCycle_DBL_TO_BIN(50.0),
        },

        .infoTransmission =
        {
            .stsTransmission = cap_stsTransm_neverReceived,
            .noTransmittedFrames = 0,
            .isEvent = false,
        },
    },


}; /* End of cap_canBus_PWM_t cap_canBus_PWM */


/** Signals and transmission status of the CAN frames on bus PT. This global
    variable is used as API between the platform's CAN interface and the APSW. */
cap_canBus_PT_t cap_canBus_PT =
{
    /** Signals and transmission status of inbound CAN frame StateEcu01
        (1024, 0x400) on bus PT. */
    .PT_StateEcu01_1024_sts =
    {
        .signals =
        {
            .checksum = 0,
            .speedOfRotation = CAP_PT_1024_speedOfRotation_DBL_TO_BIN(0.0),
            .sequenceCounter = 0,
        },

        .infoTransmission =
        {
            .stsTransmission = cap_stsTransm_neverReceived,
            .noTransmittedFrames = 0,
            .isEvent = false,
        },
    },

    /** Signals and transmission status of inbound CAN frame StateEcu02
        (1040, 0x410) on bus PT. */
    .PT_StateEcu02_1040_sts =
    {
        .signals =
        {
            .checksum = 0,
            .sequenceCounter = 0,
            .torque = CAP_PT_1040_torque_DBL_TO_BIN(0.0),
        },

        .infoTransmission =
        {
            .stsTransmission = cap_stsTransm_neverReceived,
            .noTransmittedFrames = 0,
            .isEvent = false,
        },
    },

    /** Signals and transmission status of inbound CAN frame UserLimits
        (2032, 0x7f0) on bus PT. */
    .PT_UserLimits_2032_sts =
    {
        .signals =
        {
            .sequenceCounter = 1,
            .minSpeedOfRotation = CAP_PT_2032_minSpeedOfRotation_DBL_TO_BIN(800.0),
            .maxSpeedOfRotation = CAP_PT_2032_maxSpeedOfRotation_DBL_TO_BIN(6000.0),
            .checksum = 0,
            .minPower = CAP_PT_2032_minPower_DBL_TO_BIN(-1.0),
            .maxPower = CAP_PT_2032_maxPower_DBL_TO_BIN(100.0),
        },

        .infoTransmission =
        {
            .stsTransmission = cap_stsTransm_neverReceived,
            .noTransmittedFrames = 0,
            .isEvent = false,
        },
    },

    /** Signals and transmission status of outbound CAN frame InfoPowerDisplay
        (1536, 0x600) on bus PT. */
    .PT_InfoPowerDisplay_1536_sts =
    {
        .signals =
        {
            .checksum = 0,
            .sequenceCounter = 0,
            .power = CAP_PT_1536_power_DBL_TO_BIN(0.0),
            .state = 0,
        },

        .infoTransmission =
        {
            .stsTransmission = cap_stsTransm_okay,
            .noTransmittedFrames = 0,
            .isEvent = false,
        },
    },

    /** Signals and transmission status of outbound CAN frame StatusPowerDisplay
        (1537, 0x601) on bus PT. */
    .PT_StatusPowerDisplay_1537_sts =
    {
        .signals =
        {
            .noDlcErrors = 0,
            .noCheckSumErrors = 0,
            .noSqcErrors = 0,
            .sequenceCounter = 1,
            .checksum = 0,
        },

        .infoTransmission =
        {
            .stsTransmission = cap_stsTransm_okay,
            .noTransmittedFrames = 0,
            .isEvent = false,
        },
    },

    /** Signals and transmission status of outbound CAN frame LimitsPowerDisplay
        (1538, 0x602) on bus PT. */
    .PT_LimitsPowerDisplay_1538_sts =
    {
        .signals =
        {
            .sequenceCounter = 6,
            .belowMinSpeedOfRotation = 0,
            .aboveMaxSpeedOfRotation = 0,
            .belowMinPower = 0,
            .aboveMaxPower = 0,
        },

        .infoTransmission =
        {
            .stsTransmission = cap_stsTransm_okay,
            .noTransmittedFrames = 0,
            .isEvent = false,
        },
    },


}; /* End of cap_canBus_PT_t cap_canBus_PT */




/*
 * Function implementation
 */

/**
 * Pack the signals of outbound PDU PWM_in (1000, 0x3e8) on bus PWM
 * into a byte array of 8 Byte.\n
 *   The signal values are read from the global interface struct
 * cap_canBus_PWM.PWM_PWM_in_1000_sts.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */
void cap_packApi_PWM_PWM_in(uint8_t m[])
{
    cap_pack_PWM_PWM_in
            ( &m[0]
            , /* pFrameStruct */ &cap_getFrame_PWM_PWM_in_1000()
            );
} /* End of cap_packApi_PWM_PWM_in */




/**
 * Pack the signals of outbound PDU PWM_in (1000, 0x3e8) on bus PWM
 * into a byte array of 8 Byte.\n
 *   The signal values are read from a frame struct by reference.
 *   @param pFrameStruct
 * The signal values to pack are read from the interface struct * \a pFrameStruct, which
 * models frame PWM_in.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */
void cap_pack_PWM_PWM_in
                    ( uint8_t m[]
                    , const cap_PWM_PWM_in_1000_t *pFrameStruct
                    )
{
    /* The further commands will partly use bit clear and set commands to write the signal
       values. Those bytes, which are not entirely occupied by the signals are initialized
       as 0xff in order to finally have ones in all unused payload bit positions. */
    memset(m, /* value */ 0xff, /* noBytes */ 8);

    /* Pack signal PA2_J3_pin3_periodTime. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint16_t s = (uint16_t)pFrameStruct->PA2_J3_pin3_periodTime;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] = (uint8_t)s;
        s >>= 8;
        m[0] &= (uint8_t)~0x7f;
        m[0] |= (uint8_t)(s & 0x7f);
    }

    /* Pack signal PA2_J3_pin3_isNew. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->PA2_J3_pin3_isNew << 7;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (uint8_t)~0x80;
        m[0] |= (uint8_t)(s & 0x80);
    }

    /* Pack signal PA6_J2_pin1_isNew. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->PA6_J2_pin1_isNew;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[2] &= (uint8_t)~0x01;
        m[2] |= (uint8_t)(s & 0x01);
    }

    /* Pack signal PA6_J2_pin1_dutyTime. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint16_t s = (uint16_t)pFrameStruct->PA6_J2_pin1_dutyTime << 1;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[2] &= (uint8_t)~0xfe;
        m[2] |= (uint8_t)(s & 0xfe);
        s >>= 8;
        m[3] = (uint8_t)s;
    }

    /* Pack signal PA2_PA6_dutyCycle. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint16_t s = (uint16_t)pFrameStruct->PA2_PA6_dutyCycle << 1;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[5] &= (uint8_t)~0xfe;
        m[5] |= (uint8_t)(s & 0xfe);
        s >>= 8;
        m[4] = (uint8_t)s;
    }

    /* Pack signal PA2_J3_pin3_frequency. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint32_t s = (uint32_t)pFrameStruct->PA2_J3_pin3_frequency << 2;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[7] &= (uint8_t)~0xfc;
        m[7] |= (uint8_t)(s & 0xfc);
        s >>= 8;
        m[6] = (uint8_t)s;
        s >>= 8;
        m[5] &= (uint8_t)~0x01;
        m[5] |= (uint8_t)(s & 0x01);
    }
} /* End of cap_pack_PWM_PWM_in */


#if CAP_UNCONDITIONALLY_GENERATE_UNPACK_FCTS != 0
/**
 * Unpack the signals of outbound PDU PWM_in (1000, 0x3e8) on bus PWM
 * from a byte array of 8 Byte.\n
 *   The unpacked signal values are written into the global interface struct
 * cap_canBus_PWM.PWM_PWM_in_1000_sts, which models frame PWM_in.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */
void cap_unpackApi_PWM_PWM_in(const uint8_t m[])
{
    cap_unpack_PWM_PWM_in
            ( /* pFrameStruct */ &cap_getFrame_PWM_PWM_in_1000()
            , &m[0]
            );
} /* End of cap_unpackApi_PWM_PWM_in */



/**
 * Unpack the signals of outbound PDU PWM_in (1000, 0x3e8) on bus PWM
 * from a byte array of 8 Byte.\n
 *   @param pFrameStruct
 * The unpacked signal values are written into the interface struct * \a pFrameStruct,
 * which models frame PWM_in.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */
void cap_unpack_PWM_PWM_in
                    ( cap_PWM_PWM_in_1000_t *pFrameStruct
                    , const uint8_t m[]
                    )
{
    /* Decode all normal, not multiplexed signals. */
    pFrameStruct->PA2_J3_pin3_periodTime =
        (uint16_t)((((uint16_t)(m[0] & 0x7f)) << 8) | m[1]);
    pFrameStruct->PA2_J3_pin3_isNew =
        (boolean_t)(((uint8_t)(m[0] & 0x80)) >> 7);
    pFrameStruct->PA6_J2_pin1_isNew =
        (boolean_t)((uint8_t)(m[2] & 0x01));
    pFrameStruct->PA6_J2_pin1_dutyTime =
        (uint16_t)(((((uint16_t)m[3]) << 8) | m[2]) >> 1);
    pFrameStruct->PA2_PA6_dutyCycle =
        (uint16_t)(((((uint16_t)m[4]) << 8) | m[5]) >> 1);
    pFrameStruct->PA2_J3_pin3_frequency =
        (uint16_t)(((((((uint32_t)(m[5] & 0x01)) << 8) | m[6]) << 8) | m[7]) >> 2);

} /* End of cap_unpack_PWM_PWM_in */
#endif




#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU PWM_out (1001, 0x3e9) on bus PWM
 * into a byte array of 8 Byte.\n
 *   The signal values are read from the global interface struct
 * cap_canBus_PWM.PWM_PWM_out_1001_sts.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */
void cap_packApi_PWM_PWM_out(uint8_t m[])
{
    cap_pack_PWM_PWM_out
            ( &m[0]
            , /* pFrameStruct */ &cap_getFrame_PWM_PWM_out_1001()
            );
} /* End of cap_packApi_PWM_PWM_out */




/**
 * Pack the signals of inbound PDU PWM_out (1001, 0x3e9) on bus PWM
 * into a byte array of 8 Byte.\n
 *   The signal values are read from a frame struct by reference.
 *   @param pFrameStruct
 * The signal values to pack are read from the interface struct * \a pFrameStruct, which
 * models frame PWM_out.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */
void cap_pack_PWM_PWM_out
                    ( uint8_t m[]
                    , const cap_PWM_PWM_out_1001_t *pFrameStruct
                    )
{
    /* The further commands will partly use bit clear and set commands to write the signal
       values. Those bytes, which are not entirely occupied by the signals are initialized
       as 0xff in order to finally have ones in all unused payload bit positions. */
    memset(m, /* value */ 0xff, /* noBytes */ 8);

    /* Pack signal LED_2_DS10_inhibit. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->LED_2_DS10_inhibit;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (uint8_t)~0x01;
        m[0] |= (uint8_t)(s & 0x01);
    }

    /* Pack signal LED_4_DS11_inhibit. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->LED_4_DS11_inhibit << 1;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (uint8_t)~0x02;
        m[0] |= (uint8_t)(s & 0x02);
    }

    /* Pack signal LED_5_DS5_inhibit. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->LED_5_DS5_inhibit << 2;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (uint8_t)~0x04;
        m[0] |= (uint8_t)(s & 0x04);
    }

    /* Pack signal PA1_J3_pin1_inhibit. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->PA1_J3_pin1_inhibit << 3;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (uint8_t)~0x08;
        m[0] |= (uint8_t)(s & 0x08);
    }

    /* Pack signal LED_2_DS10_frequency. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint16_t s = (uint16_t)pFrameStruct->LED_2_DS10_frequency << 4;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (uint8_t)~0xf0;
        m[0] |= (uint8_t)(s & 0xf0);
        s >>= 8;
        m[1] &= (uint8_t)~0x3f;
        m[1] |= (uint8_t)(s & 0x3f);
    }

    /* Pack signal LED_4_DS11_frequency. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint16_t s = (uint16_t)pFrameStruct->LED_4_DS11_frequency << 6;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] &= (uint8_t)~0xc0;
        m[1] |= (uint8_t)(s & 0xc0);
        s >>= 8;
        m[2] = (uint8_t)s;
    }

    /* Pack signal LED_5_DS5_frequency. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint16_t s = (uint16_t)pFrameStruct->LED_5_DS5_frequency;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[3] = (uint8_t)s;
        s >>= 8;
        m[4] &= (uint8_t)~0x03;
        m[4] |= (uint8_t)(s & 0x03);
    }

    /* Pack signal PA1_J3_pin1_frequency. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint16_t s = (uint16_t)pFrameStruct->PA1_J3_pin1_frequency << 2;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[4] &= (uint8_t)~0xfc;
        m[4] |= (uint8_t)(s & 0xfc);
        s >>= 8;
        m[5] &= (uint8_t)~0x0f;
        m[5] |= (uint8_t)(s & 0x0f);
    }

    /* Pack signal LED_2_DS10_dutyCycle. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint16_t s = (uint16_t)pFrameStruct->LED_2_DS10_dutyCycle << 4;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[5] &= (uint8_t)~0xf0;
        m[5] |= (uint8_t)(s & 0xf0);
        s >>= 8;
        m[6] &= (uint8_t)~0x01;
        m[6] |= (uint8_t)(s & 0x01);
    }

    /* Pack signal LED_4_DS11_dutyCycle. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->LED_4_DS11_dutyCycle << 1;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[6] &= (uint8_t)~0x3e;
        m[6] |= (uint8_t)(s & 0x3e);
    }

    /* Pack signal LED_5_DS5_dutyCycle. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint16_t s = (uint16_t)pFrameStruct->LED_5_DS5_dutyCycle << 6;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[6] &= (uint8_t)~0xc0;
        m[6] |= (uint8_t)(s & 0xc0);
        s >>= 8;
        m[7] &= (uint8_t)~0x07;
        m[7] |= (uint8_t)(s & 0x07);
    }

    /* Pack signal PA1_J3_pin1_dutyCycle. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->PA1_J3_pin1_dutyCycle << 3;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[7] &= (uint8_t)~0xf8;
        m[7] |= (uint8_t)(s & 0xf8);
    }
} /* End of cap_pack_PWM_PWM_out */
#endif



/**
 * Unpack the signals of inbound PDU PWM_out (1001, 0x3e9) on bus PWM
 * from a byte array of 8 Byte.\n
 *   The unpacked signal values are written into the global interface struct
 * cap_canBus_PWM.PWM_PWM_out_1001_sts, which models frame PWM_out.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */
void cap_unpackApi_PWM_PWM_out(const uint8_t m[])
{
    cap_unpack_PWM_PWM_out
            ( /* pFrameStruct */ &cap_getFrame_PWM_PWM_out_1001()
            , &m[0]
            );
} /* End of cap_unpackApi_PWM_PWM_out */



/**
 * Unpack the signals of inbound PDU PWM_out (1001, 0x3e9) on bus PWM
 * from a byte array of 8 Byte.\n
 *   @param pFrameStruct
 * The unpacked signal values are written into the interface struct * \a pFrameStruct,
 * which models frame PWM_out.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */
void cap_unpack_PWM_PWM_out
                    ( cap_PWM_PWM_out_1001_t *pFrameStruct
                    , const uint8_t m[]
                    )
{
    /* Decode all normal, not multiplexed signals. */
    pFrameStruct->LED_2_DS10_inhibit =
        (boolean_t)((uint8_t)(m[0] & 0x01));
    pFrameStruct->LED_4_DS11_inhibit =
        (boolean_t)(((uint8_t)(m[0] & 0x02)) >> 1);
    pFrameStruct->LED_5_DS5_inhibit =
        (boolean_t)(((uint8_t)(m[0] & 0x04)) >> 2);
    pFrameStruct->PA1_J3_pin1_inhibit =
        (boolean_t)(((uint8_t)(m[0] & 0x08)) >> 3);
    pFrameStruct->LED_2_DS10_frequency =
        (uint16_t)(((((uint16_t)(m[1] & 0x3f)) << 8) | m[0]) >> 4);
    pFrameStruct->LED_4_DS11_frequency =
        (uint16_t)(((((uint16_t)m[2]) << 8) | m[1]) >> 6);
    pFrameStruct->LED_5_DS5_frequency =
        (uint16_t)((((uint16_t)(m[4] & 0x03)) << 8) | m[3]);
    pFrameStruct->PA1_J3_pin1_frequency =
        (uint16_t)(((((uint16_t)(m[5] & 0x0f)) << 8) | m[4]) >> 2);
    pFrameStruct->LED_2_DS10_dutyCycle =
        (uint8_t)(((((uint16_t)(m[6] & 0x01)) << 8) | m[5]) >> 4);
    pFrameStruct->LED_4_DS11_dutyCycle =
        (uint8_t)(((uint8_t)(m[6] & 0x3e)) >> 1);
    pFrameStruct->LED_5_DS5_dutyCycle =
        (uint8_t)(((((uint16_t)(m[7] & 0x07)) << 8) | m[6]) >> 6);
    pFrameStruct->PA1_J3_pin1_dutyCycle =
        (uint8_t)(((uint8_t)(m[7] & 0xf8)) >> 3);

} /* End of cap_unpack_PWM_PWM_out */



#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU StateEcu01 (1024, 0x400) on bus PT
 * into a byte array of 4 Byte.\n
 *   The signal values are read from the global interface struct
 * cap_canBus_PT.PT_StateEcu01_1024_sts.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */
void cap_packApi_PT_StateEcu01(uint8_t m[])
{
    cap_pack_PT_StateEcu01
            ( &m[0]
            , /* pFrameStruct */ &cap_getFrame_PT_StateEcu01_1024()
            );
} /* End of cap_packApi_PT_StateEcu01 */




/**
 * Pack the signals of inbound PDU StateEcu01 (1024, 0x400) on bus PT
 * into a byte array of 4 Byte.\n
 *   The signal values are read from a frame struct by reference.
 *   @param pFrameStruct
 * The signal values to pack are read from the interface struct * \a pFrameStruct, which
 * models frame StateEcu01.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */
void cap_pack_PT_StateEcu01
                    ( uint8_t m[]
                    , const cap_PT_StateEcu01_1024_t *pFrameStruct
                    )
{
    /* The further commands will partly use bit clear and set commands to write the signal
       values. Those bytes, which are not entirely occupied by the signals are initialized
       as 0xff in order to finally have ones in all unused payload bit positions. */
    m[1] = 0xff;
    m[3] = 0xff;

    /* Pack signal checksum. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->checksum;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (uint8_t)s;
    }

    /* Pack signal speedOfRotation. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint32_t s = (uint32_t)pFrameStruct->speedOfRotation << 4;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[3] &= (uint8_t)~0xf0;
        m[3] |= (uint8_t)(s & 0xf0);
        s >>= 8;
        m[2] = (uint8_t)s;
        s >>= 8;
        m[1] &= (uint8_t)~0x0f;
        m[1] |= (uint8_t)(s & 0x0f);
    }

    /* Pack signal sequenceCounter. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->sequenceCounter << 4;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] &= (uint8_t)~0xf0;
        m[1] |= (uint8_t)(s & 0xf0);
    }
} /* End of cap_pack_PT_StateEcu01 */
#endif



/**
 * Unpack the signals of inbound PDU StateEcu01 (1024, 0x400) on bus PT
 * from a byte array of 4 Byte.\n
 *   The unpacked signal values are written into the global interface struct
 * cap_canBus_PT.PT_StateEcu01_1024_sts, which models frame StateEcu01.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */
void cap_unpackApi_PT_StateEcu01(const uint8_t m[])
{
    cap_unpack_PT_StateEcu01
            ( /* pFrameStruct */ &cap_getFrame_PT_StateEcu01_1024()
            , &m[0]
            );
} /* End of cap_unpackApi_PT_StateEcu01 */



/**
 * Unpack the signals of inbound PDU StateEcu01 (1024, 0x400) on bus PT
 * from a byte array of 4 Byte.\n
 *   @param pFrameStruct
 * The unpacked signal values are written into the interface struct * \a pFrameStruct,
 * which models frame StateEcu01.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */
void cap_unpack_PT_StateEcu01
                    ( cap_PT_StateEcu01_1024_t *pFrameStruct
                    , const uint8_t m[]
                    )
{
    /* Decode all normal, not multiplexed signals. */
    pFrameStruct->checksum =
        (uint8_t)((uint8_t)m[0]);
    pFrameStruct->speedOfRotation =
        (uint16_t)(((((((uint32_t)(m[1] & 0x0f)) << 8) | m[2]) << 8) | m[3]) >> 4);
    pFrameStruct->sequenceCounter =
        (uint8_t)(((uint8_t)(m[1] & 0xf0)) >> 4);

} /* End of cap_unpack_PT_StateEcu01 */



#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU StateEcu02 (1040, 0x410) on bus PT
 * into a byte array of 4 Byte.\n
 *   The signal values are read from the global interface struct
 * cap_canBus_PT.PT_StateEcu02_1040_sts.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */
void cap_packApi_PT_StateEcu02(uint8_t m[])
{
    cap_pack_PT_StateEcu02
            ( &m[0]
            , /* pFrameStruct */ &cap_getFrame_PT_StateEcu02_1040()
            );
} /* End of cap_packApi_PT_StateEcu02 */




/**
 * Pack the signals of inbound PDU StateEcu02 (1040, 0x410) on bus PT
 * into a byte array of 4 Byte.\n
 *   The signal values are read from a frame struct by reference.
 *   @param pFrameStruct
 * The signal values to pack are read from the interface struct * \a pFrameStruct, which
 * models frame StateEcu02.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */
void cap_pack_PT_StateEcu02
                    ( uint8_t m[]
                    , const cap_PT_StateEcu02_1040_t *pFrameStruct
                    )
{
    /* The further commands will partly use bit clear and set commands to write the signal
       values. Those bytes, which are not entirely occupied by the signals are initialized
       as 0xff in order to finally have ones in all unused payload bit positions. */
    m[1] = 0xff;
    m[2] = 0xff;
    m[3] = 0xff;

    /* Pack signal checksum. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->checksum;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (uint8_t)s;
    }

    /* Pack signal sequenceCounter. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->sequenceCounter;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] &= (uint8_t)~0x0f;
        m[1] |= (uint8_t)(s & 0x0f);
    }

    /* Pack signal torque. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint16_t s = (uint16_t)pFrameStruct->torque << (5-1);

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[3] &= (uint8_t)~0xf0;
        m[3] |= (uint8_t)(s & 0xf0);
        s >>= 8;
        m[2] &= (uint8_t)~0x7f;
        m[2] |= (uint8_t)(s & 0x7f);
    }
} /* End of cap_pack_PT_StateEcu02 */
#endif



/**
 * Unpack the signals of inbound PDU StateEcu02 (1040, 0x410) on bus PT
 * from a byte array of 4 Byte.\n
 *   The unpacked signal values are written into the global interface struct
 * cap_canBus_PT.PT_StateEcu02_1040_sts, which models frame StateEcu02.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */
void cap_unpackApi_PT_StateEcu02(const uint8_t m[])
{
    cap_unpack_PT_StateEcu02
            ( /* pFrameStruct */ &cap_getFrame_PT_StateEcu02_1040()
            , &m[0]
            );
} /* End of cap_unpackApi_PT_StateEcu02 */



/**
 * Unpack the signals of inbound PDU StateEcu02 (1040, 0x410) on bus PT
 * from a byte array of 4 Byte.\n
 *   @param pFrameStruct
 * The unpacked signal values are written into the interface struct * \a pFrameStruct,
 * which models frame StateEcu02.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */
void cap_unpack_PT_StateEcu02
                    ( cap_PT_StateEcu02_1040_t *pFrameStruct
                    , const uint8_t m[]
                    )
{
    /* Decode all normal, not multiplexed signals. */
    pFrameStruct->sequenceCounter =
        (uint8_t)((uint8_t)(m[1] & 0x0f));
    pFrameStruct->torque =
        (int16_t)((int16_t)(((((uint16_t)m[2]) << 8) | m[3]) << 1) >> 5);

} /* End of cap_unpack_PT_StateEcu02 */



#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU UserLimits (2032, 0x7f0) on bus PT
 * into a byte array of 8 Byte.\n
 *   The signal values are read from the global interface struct
 * cap_canBus_PT.PT_UserLimits_2032_sts.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */
void cap_packApi_PT_UserLimits(uint8_t m[])
{
    cap_pack_PT_UserLimits
            ( &m[0]
            , /* pFrameStruct */ &cap_getFrame_PT_UserLimits_2032()
            );
} /* End of cap_packApi_PT_UserLimits */




/**
 * Pack the signals of inbound PDU UserLimits (2032, 0x7f0) on bus PT
 * into a byte array of 8 Byte.\n
 *   The signal values are read from a frame struct by reference.
 *   @param pFrameStruct
 * The signal values to pack are read from the interface struct * \a pFrameStruct, which
 * models frame UserLimits.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */
void cap_pack_PT_UserLimits
                    ( uint8_t m[]
                    , const cap_PT_UserLimits_2032_t *pFrameStruct
                    )
{
    /* The further commands will partly use bit clear and set commands to write the signal
       values. Those bytes, which are not entirely occupied by the signals are initialized
       as 0xff in order to finally have ones in all unused payload bit positions. */
    memset(m, /* value */ 0xff, /* noBytes */ 8);

    /* Pack signal sequenceCounter. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->sequenceCounter << 2;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (uint8_t)~0x3c;
        m[0] |= (uint8_t)(s & 0x3c);
    }

    /* Pack signal minSpeedOfRotation. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint32_t s = (uint32_t)pFrameStruct->minSpeedOfRotation << 6;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (uint8_t)~0xc0;
        m[0] |= (uint8_t)(s & 0xc0);
        s >>= 8;
        m[1] = (uint8_t)s;
        s >>= 8;
        m[2] &= (uint8_t)~0x03;
        m[2] |= (uint8_t)(s & 0x03);
    }

    /* Pack signal maxSpeedOfRotation. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint16_t s = (uint16_t)pFrameStruct->maxSpeedOfRotation << 2;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[2] &= (uint8_t)~0xfc;
        m[2] |= (uint8_t)(s & 0xfc);
        s >>= 8;
        m[3] &= (uint8_t)~0x3f;
        m[3] |= (uint8_t)(s & 0x3f);
    }

    /* Pack signal checksum. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->checksum;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[4] = (uint8_t)s;
    }

    /* Pack signal minPower. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint16_t s = (uint16_t)pFrameStruct->minPower << 7;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[6] &= (uint8_t)~0x80;
        m[6] |= (uint8_t)(s & 0x80);
        s >>= 8;
        m[5] = (uint8_t)s;
    }

    /* Pack signal maxPower. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint16_t s = (uint16_t)pFrameStruct->maxPower << 5;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[7] &= (uint8_t)~0xe0;
        m[7] |= (uint8_t)(s & 0xe0);
        s >>= 8;
        m[6] &= (uint8_t)~0x3f;
        m[6] |= (uint8_t)(s & 0x3f);
    }
} /* End of cap_pack_PT_UserLimits */
#endif



/**
 * Unpack the signals of inbound PDU UserLimits (2032, 0x7f0) on bus PT
 * from a byte array of 8 Byte.\n
 *   The unpacked signal values are written into the global interface struct
 * cap_canBus_PT.PT_UserLimits_2032_sts, which models frame UserLimits.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */
void cap_unpackApi_PT_UserLimits(const uint8_t m[])
{
    cap_unpack_PT_UserLimits
            ( /* pFrameStruct */ &cap_getFrame_PT_UserLimits_2032()
            , &m[0]
            );
} /* End of cap_unpackApi_PT_UserLimits */



/**
 * Unpack the signals of inbound PDU UserLimits (2032, 0x7f0) on bus PT
 * from a byte array of 8 Byte.\n
 *   @param pFrameStruct
 * The unpacked signal values are written into the interface struct * \a pFrameStruct,
 * which models frame UserLimits.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */
void cap_unpack_PT_UserLimits
                    ( cap_PT_UserLimits_2032_t *pFrameStruct
                    , const uint8_t m[]
                    )
{
    /* Decode all normal, not multiplexed signals. */
    pFrameStruct->sequenceCounter =
        (uint8_t)(((uint8_t)(m[0] & 0x3c)) >> 2);
    pFrameStruct->minSpeedOfRotation =
        (uint16_t)(((((((uint32_t)(m[2] & 0x03)) << 8) | m[1]) << 8) | m[0]) >> 6);
    pFrameStruct->maxSpeedOfRotation =
        (uint16_t)(((((uint16_t)(m[3] & 0x3f)) << 8) | m[2]) >> 2);
    pFrameStruct->checksum =
        (uint8_t)((uint8_t)m[4]);
    pFrameStruct->minPower =
        (uint16_t)(((((uint16_t)m[5]) << 8) | m[6]) >> 7);
    pFrameStruct->maxPower =
        (uint16_t)(((((uint16_t)(m[6] & 0x3f)) << 8) | m[7]) >> 5);

} /* End of cap_unpack_PT_UserLimits */


/**
 * Pack the signals of outbound PDU InfoPowerDisplay (1536, 0x600) on bus PT
 * into a byte array of 6 Byte.\n
 *   The signal values are read from the global interface struct
 * cap_canBus_PT.PT_InfoPowerDisplay_1536_sts.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */
void cap_packApi_PT_InfoPowerDisplay(uint8_t m[])
{
    cap_pack_PT_InfoPowerDisplay
            ( &m[0]
            , /* pFrameStruct */ &cap_getFrame_PT_InfoPowerDisplay_1536()
            );
} /* End of cap_packApi_PT_InfoPowerDisplay */




/**
 * Pack the signals of outbound PDU InfoPowerDisplay (1536, 0x600) on bus PT
 * into a byte array of 6 Byte.\n
 *   The signal values are read from a frame struct by reference.
 *   @param pFrameStruct
 * The signal values to pack are read from the interface struct * \a pFrameStruct, which
 * models frame InfoPowerDisplay.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */
void cap_pack_PT_InfoPowerDisplay
                    ( uint8_t m[]
                    , const cap_PT_InfoPowerDisplay_1536_t *pFrameStruct
                    )
{
    /* The further commands will partly use bit clear and set commands to write the signal
       values. Those bytes, which are not entirely occupied by the signals are initialized
       as 0xff in order to finally have ones in all unused payload bit positions. */
    memset(m, /* value */ 0xff, /* noBytes */ 6);

    /* Pack signal checksum. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->checksum;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (uint8_t)s;
    }

    /* Pack signal sequenceCounter. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->sequenceCounter;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] &= (uint8_t)~0x0f;
        m[1] |= (uint8_t)(s & 0x0f);
    }

    /* Pack signal power. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint32_t s = (uint32_t)pFrameStruct->power << 5;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] &= (uint8_t)~0xe0;
        m[1] |= (uint8_t)(s & 0xe0);
        s >>= 8;
        m[2] = (uint8_t)s;
        s >>= 8;
        m[3] &= (uint8_t)~0x0f;
        m[3] |= (uint8_t)(s & 0x0f);
    }

    /* Pack signal state. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint16_t s = (uint16_t)pFrameStruct->state << 7;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[5] &= (uint8_t)~0x80;
        m[5] |= (uint8_t)(s & 0x80);
        s >>= 8;
        m[4] &= (uint8_t)~0x03;
        m[4] |= (uint8_t)(s & 0x03);
    }
} /* End of cap_pack_PT_InfoPowerDisplay */


#if CAP_UNCONDITIONALLY_GENERATE_UNPACK_FCTS != 0
/**
 * Unpack the signals of outbound PDU InfoPowerDisplay (1536, 0x600) on bus PT
 * from a byte array of 6 Byte.\n
 *   The unpacked signal values are written into the global interface struct
 * cap_canBus_PT.PT_InfoPowerDisplay_1536_sts, which models frame InfoPowerDisplay.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */
void cap_unpackApi_PT_InfoPowerDisplay(const uint8_t m[])
{
    cap_unpack_PT_InfoPowerDisplay
            ( /* pFrameStruct */ &cap_getFrame_PT_InfoPowerDisplay_1536()
            , &m[0]
            );
} /* End of cap_unpackApi_PT_InfoPowerDisplay */



/**
 * Unpack the signals of outbound PDU InfoPowerDisplay (1536, 0x600) on bus PT
 * from a byte array of 6 Byte.\n
 *   @param pFrameStruct
 * The unpacked signal values are written into the interface struct * \a pFrameStruct,
 * which models frame InfoPowerDisplay.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */
void cap_unpack_PT_InfoPowerDisplay
                    ( cap_PT_InfoPowerDisplay_1536_t *pFrameStruct
                    , const uint8_t m[]
                    )
{
    /* Decode all normal, not multiplexed signals. */
    pFrameStruct->checksum =
        (uint8_t)((uint8_t)m[0]);
    pFrameStruct->sequenceCounter =
        (uint8_t)((uint8_t)(m[1] & 0x0f));
    pFrameStruct->power =
        (uint16_t)(((((((uint32_t)(m[3] & 0x0f)) << 8) | m[2]) << 8) | m[1]) >> 5);
    pFrameStruct->state =
        (uint8_t)(((((uint16_t)(m[4] & 0x03)) << 8) | m[5]) >> 7);

} /* End of cap_unpack_PT_InfoPowerDisplay */
#endif



/**
 * Pack the signals of outbound PDU StatusPowerDisplay (1537, 0x601) on bus PT
 * into a byte array of 6 Byte.\n
 *   The signal values are read from the global interface struct
 * cap_canBus_PT.PT_StatusPowerDisplay_1537_sts.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */
void cap_packApi_PT_StatusPowerDisplay(uint8_t m[])
{
    cap_pack_PT_StatusPowerDisplay
            ( &m[0]
            , /* pFrameStruct */ &cap_getFrame_PT_StatusPowerDisplay_1537()
            );
} /* End of cap_packApi_PT_StatusPowerDisplay */




/**
 * Pack the signals of outbound PDU StatusPowerDisplay (1537, 0x601) on bus PT
 * into a byte array of 6 Byte.\n
 *   The signal values are read from a frame struct by reference.
 *   @param pFrameStruct
 * The signal values to pack are read from the interface struct * \a pFrameStruct, which
 * models frame StatusPowerDisplay.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */
void cap_pack_PT_StatusPowerDisplay
                    ( uint8_t m[]
                    , const cap_PT_StatusPowerDisplay_1537_t *pFrameStruct
                    )
{
    /* The further commands will partly use bit clear and set commands to write the signal
       values. Those bytes, which are not entirely occupied by the signals are initialized
       as 0xff in order to finally have ones in all unused payload bit positions. */
    m[1] = 0xff;
    m[2] = 0xff;
    m[4] = 0xff;

    /* Pack signal noDlcErrors. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint16_t s = (uint16_t)pFrameStruct->noDlcErrors;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (uint8_t)s;
        s >>= 8;
        m[1] &= (uint8_t)~0x07;
        m[1] |= (uint8_t)(s & 0x07);
    }

    /* Pack signal noCheckSumErrors. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint16_t s = (uint16_t)pFrameStruct->noCheckSumErrors << 3;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] &= (uint8_t)~0xf8;
        m[1] |= (uint8_t)(s & 0xf8);
        s >>= 8;
        m[2] &= (uint8_t)~0x3f;
        m[2] |= (uint8_t)(s & 0x3f);
    }

    /* Pack signal noSqcErrors. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint32_t s = (uint32_t)pFrameStruct->noSqcErrors << 6;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[2] &= (uint8_t)~0xc0;
        m[2] |= (uint8_t)(s & 0xc0);
        s >>= 8;
        m[3] = (uint8_t)s;
        s >>= 8;
        m[4] &= (uint8_t)~0x01;
        m[4] |= (uint8_t)(s & 0x01);
    }

    /* Pack signal sequenceCounter. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->sequenceCounter << 1;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[4] &= (uint8_t)~0xfe;
        m[4] |= (uint8_t)(s & 0xfe);
    }

    /* Pack signal checksum. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->checksum;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[5] = (uint8_t)s;
    }
} /* End of cap_pack_PT_StatusPowerDisplay */


#if CAP_UNCONDITIONALLY_GENERATE_UNPACK_FCTS != 0
/**
 * Unpack the signals of outbound PDU StatusPowerDisplay (1537, 0x601) on bus PT
 * from a byte array of 6 Byte.\n
 *   The unpacked signal values are written into the global interface struct
 * cap_canBus_PT.PT_StatusPowerDisplay_1537_sts, which models frame StatusPowerDisplay.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */
void cap_unpackApi_PT_StatusPowerDisplay(const uint8_t m[])
{
    cap_unpack_PT_StatusPowerDisplay
            ( /* pFrameStruct */ &cap_getFrame_PT_StatusPowerDisplay_1537()
            , &m[0]
            );
} /* End of cap_unpackApi_PT_StatusPowerDisplay */



/**
 * Unpack the signals of outbound PDU StatusPowerDisplay (1537, 0x601) on bus PT
 * from a byte array of 6 Byte.\n
 *   @param pFrameStruct
 * The unpacked signal values are written into the interface struct * \a pFrameStruct,
 * which models frame StatusPowerDisplay.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */
void cap_unpack_PT_StatusPowerDisplay
                    ( cap_PT_StatusPowerDisplay_1537_t *pFrameStruct
                    , const uint8_t m[]
                    )
{
    /* Decode all normal, not multiplexed signals. */
    pFrameStruct->noDlcErrors =
        (uint16_t)((((uint16_t)(m[1] & 0x07)) << 8) | m[0]);
    pFrameStruct->noCheckSumErrors =
        (uint16_t)(((((uint16_t)(m[2] & 0x3f)) << 8) | m[1]) >> 3);
    pFrameStruct->noSqcErrors =
        (uint16_t)(((((((uint32_t)(m[4] & 0x01)) << 8) | m[3]) << 8) | m[2]) >> 6);
    pFrameStruct->sequenceCounter =
        (uint8_t)(((uint8_t)(m[4] & 0xfe)) >> 1);
    pFrameStruct->checksum =
        (uint8_t)((uint8_t)m[5]);

} /* End of cap_unpack_PT_StatusPowerDisplay */
#endif



/**
 * Pack the signals of outbound PDU LimitsPowerDisplay (1538, 0x602) on bus PT
 * into a byte array of 1 Byte.\n
 *   The signal values are read from the global interface struct
 * cap_canBus_PT.PT_LimitsPowerDisplay_1538_sts.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */
void cap_packApi_PT_LimitsPowerDisplay(uint8_t m[])
{
    cap_pack_PT_LimitsPowerDisplay
            ( &m[0]
            , /* pFrameStruct */ &cap_getFrame_PT_LimitsPowerDisplay_1538()
            );
} /* End of cap_packApi_PT_LimitsPowerDisplay */




/**
 * Pack the signals of outbound PDU LimitsPowerDisplay (1538, 0x602) on bus PT
 * into a byte array of 1 Byte.\n
 *   The signal values are read from a frame struct by reference.
 *   @param pFrameStruct
 * The signal values to pack are read from the interface struct * \a pFrameStruct, which
 * models frame LimitsPowerDisplay.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */
void cap_pack_PT_LimitsPowerDisplay
                    ( uint8_t m[]
                    , const cap_PT_LimitsPowerDisplay_1538_t *pFrameStruct
                    )
{
    /* The further commands will partly use bit clear and set commands to write the signal
       values. Those bytes, which are not entirely occupied by the signals are initialized
       as 0xff in order to finally have ones in all unused payload bit positions. */
    m[0] = 0xff;

    /* Pack signal sequenceCounter. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->sequenceCounter;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (uint8_t)~0x07;
        m[0] |= (uint8_t)(s & 0x07);
    }

    /* Pack signal belowMinSpeedOfRotation. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->belowMinSpeedOfRotation << 3;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (uint8_t)~0x08;
        m[0] |= (uint8_t)(s & 0x08);
    }

    /* Pack signal aboveMaxSpeedOfRotation. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->aboveMaxSpeedOfRotation << 4;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (uint8_t)~0x10;
        m[0] |= (uint8_t)(s & 0x10);
    }

    /* Pack signal belowMinPower. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->belowMinPower << 5;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (uint8_t)~0x20;
        m[0] |= (uint8_t)(s & 0x20);
    }

    /* Pack signal aboveMaxPower. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->aboveMaxPower << 6;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (uint8_t)~0x40;
        m[0] |= (uint8_t)(s & 0x40);
    }
} /* End of cap_pack_PT_LimitsPowerDisplay */


#if CAP_UNCONDITIONALLY_GENERATE_UNPACK_FCTS != 0
/**
 * Unpack the signals of outbound PDU LimitsPowerDisplay (1538, 0x602) on bus PT
 * from a byte array of 1 Byte.\n
 *   The unpacked signal values are written into the global interface struct
 * cap_canBus_PT.PT_LimitsPowerDisplay_1538_sts, which models frame LimitsPowerDisplay.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */
void cap_unpackApi_PT_LimitsPowerDisplay(const uint8_t m[])
{
    cap_unpack_PT_LimitsPowerDisplay
            ( /* pFrameStruct */ &cap_getFrame_PT_LimitsPowerDisplay_1538()
            , &m[0]
            );
} /* End of cap_unpackApi_PT_LimitsPowerDisplay */



/**
 * Unpack the signals of outbound PDU LimitsPowerDisplay (1538, 0x602) on bus PT
 * from a byte array of 1 Byte.\n
 *   @param pFrameStruct
 * The unpacked signal values are written into the interface struct * \a pFrameStruct,
 * which models frame LimitsPowerDisplay.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */
void cap_unpack_PT_LimitsPowerDisplay
                    ( cap_PT_LimitsPowerDisplay_1538_t *pFrameStruct
                    , const uint8_t m[]
                    )
{
    /* Decode all normal, not multiplexed signals. */
    pFrameStruct->sequenceCounter =
        (uint8_t)((uint8_t)(m[0] & 0x07));
    pFrameStruct->belowMinSpeedOfRotation =
        (boolean_t)(((uint8_t)(m[0] & 0x08)) >> 3);
    pFrameStruct->aboveMaxSpeedOfRotation =
        (boolean_t)(((uint8_t)(m[0] & 0x10)) >> 4);
    pFrameStruct->belowMinPower =
        (boolean_t)(((uint8_t)(m[0] & 0x20)) >> 5);
    pFrameStruct->aboveMaxPower =
        (boolean_t)(((uint8_t)(m[0] & 0x40)) >> 6);

} /* End of cap_unpack_PT_LimitsPowerDisplay */
#endif




/**
 * Get the value of signal PA2_J3_pin3_periodTime of outbound PDU PWM_in
 * (1000, 0x3e8) on bus PWM.
 *   @return
 * Get the current value form the global API.
 */
float get_PWM_1000_PA2_J3_pin3_periodTime(void)
    { return CAP_PWM_1000_PA2_J3_pin3_periodTime_BIN_TO_DBL(cap_getSignal_PWM_PWM_in_1000(PA2_J3_pin3_periodTime)); }

/**
 * Set the value of signal PA2_J3_pin3_periodTime of outbound PDU PWM_in
 * (1000, 0x3e8) on bus PWM in the global API.
 *   @param newValue
 * This value is written into the global API.
 */
void set_PWM_1000_PA2_J3_pin3_periodTime(float newValue)
    { cap_getSignal_PWM_PWM_in_1000(PA2_J3_pin3_periodTime) = CAP_PWM_1000_PA2_J3_pin3_periodTime_DBL_TO_BIN(newValue); }

/**
 * Get the value of signal PA2_J3_pin3_isNew of outbound PDU PWM_in
 * (1000, 0x3e8) on bus PWM.
 *   @return
 * Get the current value form the global API.
 */
float get_PWM_1000_PA2_J3_pin3_isNew(void)
    { return (float)cap_getSignal_PWM_PWM_in_1000(PA2_J3_pin3_isNew); }

/**
 * Set the value of signal PA2_J3_pin3_isNew of outbound PDU PWM_in
 * (1000, 0x3e8) on bus PWM in the global API.
 *   @param newValue
 * This value is written into the global API.
 */
void set_PWM_1000_PA2_J3_pin3_isNew(float newValue)
    { cap_getSignal_PWM_PWM_in_1000(PA2_J3_pin3_isNew) = (boolean_t)(int)(newValue + 0.5f); }

/**
 * Get the value of signal PA6_J2_pin1_isNew of outbound PDU PWM_in
 * (1000, 0x3e8) on bus PWM.
 *   @return
 * Get the current value form the global API.
 */
float get_PWM_1000_PA6_J2_pin1_isNew(void)
    { return (float)cap_getSignal_PWM_PWM_in_1000(PA6_J2_pin1_isNew); }

/**
 * Set the value of signal PA6_J2_pin1_isNew of outbound PDU PWM_in
 * (1000, 0x3e8) on bus PWM in the global API.
 *   @param newValue
 * This value is written into the global API.
 */
void set_PWM_1000_PA6_J2_pin1_isNew(float newValue)
    { cap_getSignal_PWM_PWM_in_1000(PA6_J2_pin1_isNew) = (boolean_t)(int)(newValue + 0.5f); }

/**
 * Get the value of signal PA6_J2_pin1_dutyTime of outbound PDU PWM_in
 * (1000, 0x3e8) on bus PWM.
 *   @return
 * Get the current value form the global API.
 */
float get_PWM_1000_PA6_J2_pin1_dutyTime(void)
    { return CAP_PWM_1000_PA6_J2_pin1_dutyTime_BIN_TO_DBL(cap_getSignal_PWM_PWM_in_1000(PA6_J2_pin1_dutyTime)); }

/**
 * Set the value of signal PA6_J2_pin1_dutyTime of outbound PDU PWM_in
 * (1000, 0x3e8) on bus PWM in the global API.
 *   @param newValue
 * This value is written into the global API.
 */
void set_PWM_1000_PA6_J2_pin1_dutyTime(float newValue)
    { cap_getSignal_PWM_PWM_in_1000(PA6_J2_pin1_dutyTime) = CAP_PWM_1000_PA6_J2_pin1_dutyTime_DBL_TO_BIN(newValue); }

/**
 * Get the value of signal PA2_PA6_dutyCycle of outbound PDU PWM_in
 * (1000, 0x3e8) on bus PWM.
 *   @return
 * Get the current value form the global API.
 */
float get_PWM_1000_PA2_PA6_dutyCycle(void)
    { return CAP_PWM_1000_PA2_PA6_dutyCycle_BIN_TO_DBL(cap_getSignal_PWM_PWM_in_1000(PA2_PA6_dutyCycle)); }

/**
 * Set the value of signal PA2_PA6_dutyCycle of outbound PDU PWM_in
 * (1000, 0x3e8) on bus PWM in the global API.
 *   @param newValue
 * This value is written into the global API.
 */
void set_PWM_1000_PA2_PA6_dutyCycle(float newValue)
    { cap_getSignal_PWM_PWM_in_1000(PA2_PA6_dutyCycle) = CAP_PWM_1000_PA2_PA6_dutyCycle_DBL_TO_BIN(newValue); }

/**
 * Get the value of signal PA2_J3_pin3_frequency of outbound PDU PWM_in
 * (1000, 0x3e8) on bus PWM.
 *   @return
 * Get the current value form the global API.
 */
float get_PWM_1000_PA2_J3_pin3_frequency(void)
    { return CAP_PWM_1000_PA2_J3_pin3_frequency_BIN_TO_DBL(cap_getSignal_PWM_PWM_in_1000(PA2_J3_pin3_frequency)); }

/**
 * Set the value of signal PA2_J3_pin3_frequency of outbound PDU PWM_in
 * (1000, 0x3e8) on bus PWM in the global API.
 *   @param newValue
 * This value is written into the global API.
 */
void set_PWM_1000_PA2_J3_pin3_frequency(float newValue)
    { cap_getSignal_PWM_PWM_in_1000(PA2_J3_pin3_frequency) = CAP_PWM_1000_PA2_J3_pin3_frequency_DBL_TO_BIN(newValue); }

/**
 * Get the value of signal LED_2_DS10_inhibit of inbound PDU PWM_out
 * (1001, 0x3e9) on bus PWM.
 *   @return
 * Get the current value form the global API.
 */
float get_PWM_1001_LED_2_DS10_inhibit(void)
    { return (float)cap_getSignal_PWM_PWM_out_1001(LED_2_DS10_inhibit); }

/**
 * Set the value of signal LED_2_DS10_inhibit of inbound PDU PWM_out
 * (1001, 0x3e9) on bus PWM in the global API.
 *   @param newValue
 * This value is written into the global API.
 */
void set_PWM_1001_LED_2_DS10_inhibit(float newValue)
    { cap_getSignal_PWM_PWM_out_1001(LED_2_DS10_inhibit) = (boolean_t)(int)(newValue + 0.5f); }

/**
 * Get the value of signal LED_4_DS11_inhibit of inbound PDU PWM_out
 * (1001, 0x3e9) on bus PWM.
 *   @return
 * Get the current value form the global API.
 */
float get_PWM_1001_LED_4_DS11_inhibit(void)
    { return (float)cap_getSignal_PWM_PWM_out_1001(LED_4_DS11_inhibit); }

/**
 * Set the value of signal LED_4_DS11_inhibit of inbound PDU PWM_out
 * (1001, 0x3e9) on bus PWM in the global API.
 *   @param newValue
 * This value is written into the global API.
 */
void set_PWM_1001_LED_4_DS11_inhibit(float newValue)
    { cap_getSignal_PWM_PWM_out_1001(LED_4_DS11_inhibit) = (boolean_t)(int)(newValue + 0.5f); }

/**
 * Get the value of signal LED_5_DS5_inhibit of inbound PDU PWM_out
 * (1001, 0x3e9) on bus PWM.
 *   @return
 * Get the current value form the global API.
 */
float get_PWM_1001_LED_5_DS5_inhibit(void)
    { return (float)cap_getSignal_PWM_PWM_out_1001(LED_5_DS5_inhibit); }

/**
 * Set the value of signal LED_5_DS5_inhibit of inbound PDU PWM_out
 * (1001, 0x3e9) on bus PWM in the global API.
 *   @param newValue
 * This value is written into the global API.
 */
void set_PWM_1001_LED_5_DS5_inhibit(float newValue)
    { cap_getSignal_PWM_PWM_out_1001(LED_5_DS5_inhibit) = (boolean_t)(int)(newValue + 0.5f); }

/**
 * Get the value of signal PA1_J3_pin1_inhibit of inbound PDU PWM_out
 * (1001, 0x3e9) on bus PWM.
 *   @return
 * Get the current value form the global API.
 */
float get_PWM_1001_PA1_J3_pin1_inhibit(void)
    { return (float)cap_getSignal_PWM_PWM_out_1001(PA1_J3_pin1_inhibit); }

/**
 * Set the value of signal PA1_J3_pin1_inhibit of inbound PDU PWM_out
 * (1001, 0x3e9) on bus PWM in the global API.
 *   @param newValue
 * This value is written into the global API.
 */
void set_PWM_1001_PA1_J3_pin1_inhibit(float newValue)
    { cap_getSignal_PWM_PWM_out_1001(PA1_J3_pin1_inhibit) = (boolean_t)(int)(newValue + 0.5f); }

/**
 * Get the value of signal LED_2_DS10_frequency of inbound PDU PWM_out
 * (1001, 0x3e9) on bus PWM.
 *   @return
 * Get the current value form the global API.
 */
float get_PWM_1001_LED_2_DS10_frequency(void)
    { return CAP_PWM_1001_LED_2_DS10_frequency_BIN_TO_DBL(cap_getSignal_PWM_PWM_out_1001(LED_2_DS10_frequency)); }

/**
 * Set the value of signal LED_2_DS10_frequency of inbound PDU PWM_out
 * (1001, 0x3e9) on bus PWM in the global API.
 *   @param newValue
 * This value is written into the global API.
 */
void set_PWM_1001_LED_2_DS10_frequency(float newValue)
    { cap_getSignal_PWM_PWM_out_1001(LED_2_DS10_frequency) = CAP_PWM_1001_LED_2_DS10_frequency_DBL_TO_BIN(newValue); }

/**
 * Get the value of signal LED_4_DS11_frequency of inbound PDU PWM_out
 * (1001, 0x3e9) on bus PWM.
 *   @return
 * Get the current value form the global API.
 */
float get_PWM_1001_LED_4_DS11_frequency(void)
    { return CAP_PWM_1001_LED_4_DS11_frequency_BIN_TO_DBL(cap_getSignal_PWM_PWM_out_1001(LED_4_DS11_frequency)); }

/**
 * Set the value of signal LED_4_DS11_frequency of inbound PDU PWM_out
 * (1001, 0x3e9) on bus PWM in the global API.
 *   @param newValue
 * This value is written into the global API.
 */
void set_PWM_1001_LED_4_DS11_frequency(float newValue)
    { cap_getSignal_PWM_PWM_out_1001(LED_4_DS11_frequency) = CAP_PWM_1001_LED_4_DS11_frequency_DBL_TO_BIN(newValue); }

/**
 * Get the value of signal LED_5_DS5_frequency of inbound PDU PWM_out
 * (1001, 0x3e9) on bus PWM.
 *   @return
 * Get the current value form the global API.
 */
float get_PWM_1001_LED_5_DS5_frequency(void)
    { return CAP_PWM_1001_LED_5_DS5_frequency_BIN_TO_DBL(cap_getSignal_PWM_PWM_out_1001(LED_5_DS5_frequency)); }

/**
 * Set the value of signal LED_5_DS5_frequency of inbound PDU PWM_out
 * (1001, 0x3e9) on bus PWM in the global API.
 *   @param newValue
 * This value is written into the global API.
 */
void set_PWM_1001_LED_5_DS5_frequency(float newValue)
    { cap_getSignal_PWM_PWM_out_1001(LED_5_DS5_frequency) = CAP_PWM_1001_LED_5_DS5_frequency_DBL_TO_BIN(newValue); }

/**
 * Get the value of signal PA1_J3_pin1_frequency of inbound PDU PWM_out
 * (1001, 0x3e9) on bus PWM.
 *   @return
 * Get the current value form the global API.
 */
float get_PWM_1001_PA1_J3_pin1_frequency(void)
    { return CAP_PWM_1001_PA1_J3_pin1_frequency_BIN_TO_DBL(cap_getSignal_PWM_PWM_out_1001(PA1_J3_pin1_frequency)); }

/**
 * Set the value of signal PA1_J3_pin1_frequency of inbound PDU PWM_out
 * (1001, 0x3e9) on bus PWM in the global API.
 *   @param newValue
 * This value is written into the global API.
 */
void set_PWM_1001_PA1_J3_pin1_frequency(float newValue)
    { cap_getSignal_PWM_PWM_out_1001(PA1_J3_pin1_frequency) = CAP_PWM_1001_PA1_J3_pin1_frequency_DBL_TO_BIN(newValue); }

/**
 * Get the value of signal LED_2_DS10_dutyCycle of inbound PDU PWM_out
 * (1001, 0x3e9) on bus PWM.
 *   @return
 * Get the current value form the global API.
 */
float get_PWM_1001_LED_2_DS10_dutyCycle(void)
    { return CAP_PWM_1001_LED_2_DS10_dutyCycle_BIN_TO_DBL(cap_getSignal_PWM_PWM_out_1001(LED_2_DS10_dutyCycle)); }

/**
 * Set the value of signal LED_2_DS10_dutyCycle of inbound PDU PWM_out
 * (1001, 0x3e9) on bus PWM in the global API.
 *   @param newValue
 * This value is written into the global API.
 */
void set_PWM_1001_LED_2_DS10_dutyCycle(float newValue)
    { cap_getSignal_PWM_PWM_out_1001(LED_2_DS10_dutyCycle) = CAP_PWM_1001_LED_2_DS10_dutyCycle_DBL_TO_BIN(newValue); }

/**
 * Get the value of signal LED_4_DS11_dutyCycle of inbound PDU PWM_out
 * (1001, 0x3e9) on bus PWM.
 *   @return
 * Get the current value form the global API.
 */
float get_PWM_1001_LED_4_DS11_dutyCycle(void)
    { return CAP_PWM_1001_LED_4_DS11_dutyCycle_BIN_TO_DBL(cap_getSignal_PWM_PWM_out_1001(LED_4_DS11_dutyCycle)); }

/**
 * Set the value of signal LED_4_DS11_dutyCycle of inbound PDU PWM_out
 * (1001, 0x3e9) on bus PWM in the global API.
 *   @param newValue
 * This value is written into the global API.
 */
void set_PWM_1001_LED_4_DS11_dutyCycle(float newValue)
    { cap_getSignal_PWM_PWM_out_1001(LED_4_DS11_dutyCycle) = CAP_PWM_1001_LED_4_DS11_dutyCycle_DBL_TO_BIN(newValue); }

/**
 * Get the value of signal LED_5_DS5_dutyCycle of inbound PDU PWM_out
 * (1001, 0x3e9) on bus PWM.
 *   @return
 * Get the current value form the global API.
 */
float get_PWM_1001_LED_5_DS5_dutyCycle(void)
    { return CAP_PWM_1001_LED_5_DS5_dutyCycle_BIN_TO_DBL(cap_getSignal_PWM_PWM_out_1001(LED_5_DS5_dutyCycle)); }

/**
 * Set the value of signal LED_5_DS5_dutyCycle of inbound PDU PWM_out
 * (1001, 0x3e9) on bus PWM in the global API.
 *   @param newValue
 * This value is written into the global API.
 */
void set_PWM_1001_LED_5_DS5_dutyCycle(float newValue)
    { cap_getSignal_PWM_PWM_out_1001(LED_5_DS5_dutyCycle) = CAP_PWM_1001_LED_5_DS5_dutyCycle_DBL_TO_BIN(newValue); }

/**
 * Get the value of signal PA1_J3_pin1_dutyCycle of inbound PDU PWM_out
 * (1001, 0x3e9) on bus PWM.
 *   @return
 * Get the current value form the global API.
 */
float get_PWM_1001_PA1_J3_pin1_dutyCycle(void)
    { return CAP_PWM_1001_PA1_J3_pin1_dutyCycle_BIN_TO_DBL(cap_getSignal_PWM_PWM_out_1001(PA1_J3_pin1_dutyCycle)); }

/**
 * Set the value of signal PA1_J3_pin1_dutyCycle of inbound PDU PWM_out
 * (1001, 0x3e9) on bus PWM in the global API.
 *   @param newValue
 * This value is written into the global API.
 */
void set_PWM_1001_PA1_J3_pin1_dutyCycle(float newValue)
    { cap_getSignal_PWM_PWM_out_1001(PA1_J3_pin1_dutyCycle) = CAP_PWM_1001_PA1_J3_pin1_dutyCycle_DBL_TO_BIN(newValue); }

/**
 * Get the value of signal checksum of inbound PDU StateEcu01
 * (1024, 0x400) on bus PT.
 *   @return
 * Get the current value form the global API.
 */
float get_PT_1024_checksum(void)
    { return (float)cap_getSignal_PT_StateEcu01_1024(checksum); }

/**
 * Set the value of signal checksum of inbound PDU StateEcu01
 * (1024, 0x400) on bus PT in the global API.
 *   @param newValue
 * This value is written into the global API.
 */
void set_PT_1024_checksum(float newValue)
    { cap_getSignal_PT_StateEcu01_1024(checksum) = (uint8_t)(newValue + 0.5f); }

/**
 * Get the value of signal speedOfRotation of inbound PDU StateEcu01
 * (1024, 0x400) on bus PT.
 *   @return
 * Get the current value form the global API.
 */
float get_PT_1024_speedOfRotation(void)
    { return CAP_PT_1024_speedOfRotation_BIN_TO_DBL(cap_getSignal_PT_StateEcu01_1024(speedOfRotation)); }

/**
 * Set the value of signal speedOfRotation of inbound PDU StateEcu01
 * (1024, 0x400) on bus PT in the global API.
 *   @param newValue
 * This value is written into the global API.
 */
void set_PT_1024_speedOfRotation(float newValue)
    { cap_getSignal_PT_StateEcu01_1024(speedOfRotation) = CAP_PT_1024_speedOfRotation_DBL_TO_BIN(newValue); }

/**
 * Get the value of signal sequenceCounter of inbound PDU StateEcu01
 * (1024, 0x400) on bus PT.
 *   @return
 * Get the current value form the global API.
 */
float get_PT_1024_sequenceCounter(void)
    { return (float)cap_getSignal_PT_StateEcu01_1024(sequenceCounter); }

/**
 * Set the value of signal sequenceCounter of inbound PDU StateEcu01
 * (1024, 0x400) on bus PT in the global API.
 *   @param newValue
 * This value is written into the global API.
 */
void set_PT_1024_sequenceCounter(float newValue)
    { cap_getSignal_PT_StateEcu01_1024(sequenceCounter) = (uint8_t)(newValue + 0.5f); }

/**
 * Get the value of signal sequenceCounter of inbound PDU StateEcu02
 * (1040, 0x410) on bus PT.
 *   @return
 * Get the current value form the global API.
 */
float get_PT_1040_sequenceCounter(void)
    { return (float)cap_getSignal_PT_StateEcu02_1040(sequenceCounter); }

/**
 * Set the value of signal sequenceCounter of inbound PDU StateEcu02
 * (1040, 0x410) on bus PT in the global API.
 *   @param newValue
 * This value is written into the global API.
 */
void set_PT_1040_sequenceCounter(float newValue)
    { cap_getSignal_PT_StateEcu02_1040(sequenceCounter) = (uint8_t)(newValue + 0.5f); }

/**
 * Get the value of signal torque of inbound PDU StateEcu02
 * (1040, 0x410) on bus PT.
 *   @return
 * Get the current value form the global API.
 */
float get_PT_1040_torque(void)
    { return CAP_PT_1040_torque_BIN_TO_DBL(cap_getSignal_PT_StateEcu02_1040(torque)); }

/**
 * Set the value of signal torque of inbound PDU StateEcu02
 * (1040, 0x410) on bus PT in the global API.
 *   @param newValue
 * This value is written into the global API.
 */
void set_PT_1040_torque(float newValue)
    { cap_getSignal_PT_StateEcu02_1040(torque) = CAP_PT_1040_torque_DBL_TO_BIN(newValue); }

/**
 * Get the value of signal sequenceCounter of inbound PDU UserLimits
 * (2032, 0x7f0) on bus PT.
 *   @return
 * Get the current value form the global API.
 */
float get_PT_2032_sequenceCounter(void)
    { return (float)cap_getSignal_PT_UserLimits_2032(sequenceCounter); }

/**
 * Set the value of signal sequenceCounter of inbound PDU UserLimits
 * (2032, 0x7f0) on bus PT in the global API.
 *   @param newValue
 * This value is written into the global API.
 */
void set_PT_2032_sequenceCounter(float newValue)
    { cap_getSignal_PT_UserLimits_2032(sequenceCounter) = (uint8_t)(newValue + 0.5f); }

/**
 * Get the value of signal minSpeedOfRotation of inbound PDU UserLimits
 * (2032, 0x7f0) on bus PT.
 *   @return
 * Get the current value form the global API.
 */
float get_PT_2032_minSpeedOfRotation(void)
    { return CAP_PT_2032_minSpeedOfRotation_BIN_TO_DBL(cap_getSignal_PT_UserLimits_2032(minSpeedOfRotation)); }

/**
 * Set the value of signal minSpeedOfRotation of inbound PDU UserLimits
 * (2032, 0x7f0) on bus PT in the global API.
 *   @param newValue
 * This value is written into the global API.
 */
void set_PT_2032_minSpeedOfRotation(float newValue)
    { cap_getSignal_PT_UserLimits_2032(minSpeedOfRotation) = CAP_PT_2032_minSpeedOfRotation_DBL_TO_BIN(newValue); }

/**
 * Get the value of signal maxSpeedOfRotation of inbound PDU UserLimits
 * (2032, 0x7f0) on bus PT.
 *   @return
 * Get the current value form the global API.
 */
float get_PT_2032_maxSpeedOfRotation(void)
    { return CAP_PT_2032_maxSpeedOfRotation_BIN_TO_DBL(cap_getSignal_PT_UserLimits_2032(maxSpeedOfRotation)); }

/**
 * Set the value of signal maxSpeedOfRotation of inbound PDU UserLimits
 * (2032, 0x7f0) on bus PT in the global API.
 *   @param newValue
 * This value is written into the global API.
 */
void set_PT_2032_maxSpeedOfRotation(float newValue)
    { cap_getSignal_PT_UserLimits_2032(maxSpeedOfRotation) = CAP_PT_2032_maxSpeedOfRotation_DBL_TO_BIN(newValue); }

/**
 * Get the value of signal checksum of inbound PDU UserLimits
 * (2032, 0x7f0) on bus PT.
 *   @return
 * Get the current value form the global API.
 */
float get_PT_2032_checksum(void)
    { return (float)cap_getSignal_PT_UserLimits_2032(checksum); }

/**
 * Set the value of signal checksum of inbound PDU UserLimits
 * (2032, 0x7f0) on bus PT in the global API.
 *   @param newValue
 * This value is written into the global API.
 */
void set_PT_2032_checksum(float newValue)
    { cap_getSignal_PT_UserLimits_2032(checksum) = (uint8_t)(newValue + 0.5f); }

/**
 * Get the value of signal minPower of inbound PDU UserLimits
 * (2032, 0x7f0) on bus PT.
 *   @return
 * Get the current value form the global API.
 */
float get_PT_2032_minPower(void)
    { return CAP_PT_2032_minPower_BIN_TO_DBL(cap_getSignal_PT_UserLimits_2032(minPower)); }

/**
 * Set the value of signal minPower of inbound PDU UserLimits
 * (2032, 0x7f0) on bus PT in the global API.
 *   @param newValue
 * This value is written into the global API.
 */
void set_PT_2032_minPower(float newValue)
    { cap_getSignal_PT_UserLimits_2032(minPower) = CAP_PT_2032_minPower_DBL_TO_BIN(newValue); }

/**
 * Get the value of signal maxPower of inbound PDU UserLimits
 * (2032, 0x7f0) on bus PT.
 *   @return
 * Get the current value form the global API.
 */
float get_PT_2032_maxPower(void)
    { return CAP_PT_2032_maxPower_BIN_TO_DBL(cap_getSignal_PT_UserLimits_2032(maxPower)); }

/**
 * Set the value of signal maxPower of inbound PDU UserLimits
 * (2032, 0x7f0) on bus PT in the global API.
 *   @param newValue
 * This value is written into the global API.
 */
void set_PT_2032_maxPower(float newValue)
    { cap_getSignal_PT_UserLimits_2032(maxPower) = CAP_PT_2032_maxPower_DBL_TO_BIN(newValue); }

/**
 * Get the value of signal checksum of outbound PDU InfoPowerDisplay
 * (1536, 0x600) on bus PT.
 *   @return
 * Get the current value form the global API.
 */
float get_PT_1536_checksum(void)
    { return (float)cap_getSignal_PT_InfoPowerDisplay_1536(checksum); }

/**
 * Set the value of signal checksum of outbound PDU InfoPowerDisplay
 * (1536, 0x600) on bus PT in the global API.
 *   @param newValue
 * This value is written into the global API.
 */
void set_PT_1536_checksum(float newValue)
    { cap_getSignal_PT_InfoPowerDisplay_1536(checksum) = (uint8_t)(newValue + 0.5f); }

/**
 * Get the value of signal sequenceCounter of outbound PDU InfoPowerDisplay
 * (1536, 0x600) on bus PT.
 *   @return
 * Get the current value form the global API.
 */
float get_PT_1536_sequenceCounter(void)
    { return (float)cap_getSignal_PT_InfoPowerDisplay_1536(sequenceCounter); }

/**
 * Set the value of signal sequenceCounter of outbound PDU InfoPowerDisplay
 * (1536, 0x600) on bus PT in the global API.
 *   @param newValue
 * This value is written into the global API.
 */
void set_PT_1536_sequenceCounter(float newValue)
    { cap_getSignal_PT_InfoPowerDisplay_1536(sequenceCounter) = (uint8_t)(newValue + 0.5f); }

/**
 * Get the value of signal power of outbound PDU InfoPowerDisplay
 * (1536, 0x600) on bus PT.
 *   @return
 * Get the current value form the global API.
 */
float get_PT_1536_power(void)
    { return CAP_PT_1536_power_BIN_TO_DBL(cap_getSignal_PT_InfoPowerDisplay_1536(power)); }

/**
 * Set the value of signal power of outbound PDU InfoPowerDisplay
 * (1536, 0x600) on bus PT in the global API.
 *   @param newValue
 * This value is written into the global API.
 */
void set_PT_1536_power(float newValue)
    { cap_getSignal_PT_InfoPowerDisplay_1536(power) = CAP_PT_1536_power_DBL_TO_BIN(newValue); }

/**
 * Get the value of signal state of outbound PDU InfoPowerDisplay
 * (1536, 0x600) on bus PT.
 *   @return
 * Get the current value form the global API.
 */
float get_PT_1536_state(void)
    { return (float)cap_getSignal_PT_InfoPowerDisplay_1536(state); }

/**
 * Set the value of signal state of outbound PDU InfoPowerDisplay
 * (1536, 0x600) on bus PT in the global API.
 *   @param newValue
 * This value is written into the global API.
 */
void set_PT_1536_state(float newValue)
    { cap_getSignal_PT_InfoPowerDisplay_1536(state) = (uint8_t)(newValue + 0.5f); }

/**
 * Get the value of signal noDlcErrors of outbound PDU StatusPowerDisplay
 * (1537, 0x601) on bus PT.
 *   @return
 * Get the current value form the global API.
 */
float get_PT_1537_noDlcErrors(void)
    { return (float)cap_getSignal_PT_StatusPowerDisplay_1537(noDlcErrors); }

/**
 * Set the value of signal noDlcErrors of outbound PDU StatusPowerDisplay
 * (1537, 0x601) on bus PT in the global API.
 *   @param newValue
 * This value is written into the global API.
 */
void set_PT_1537_noDlcErrors(float newValue)
    { cap_getSignal_PT_StatusPowerDisplay_1537(noDlcErrors) = (uint16_t)(newValue + 0.5f); }

/**
 * Get the value of signal noCheckSumErrors of outbound PDU StatusPowerDisplay
 * (1537, 0x601) on bus PT.
 *   @return
 * Get the current value form the global API.
 */
float get_PT_1537_noCheckSumErrors(void)
    { return (float)cap_getSignal_PT_StatusPowerDisplay_1537(noCheckSumErrors); }

/**
 * Set the value of signal noCheckSumErrors of outbound PDU StatusPowerDisplay
 * (1537, 0x601) on bus PT in the global API.
 *   @param newValue
 * This value is written into the global API.
 */
void set_PT_1537_noCheckSumErrors(float newValue)
    { cap_getSignal_PT_StatusPowerDisplay_1537(noCheckSumErrors) = (uint16_t)(newValue + 0.5f); }

/**
 * Get the value of signal noSqcErrors of outbound PDU StatusPowerDisplay
 * (1537, 0x601) on bus PT.
 *   @return
 * Get the current value form the global API.
 */
float get_PT_1537_noSqcErrors(void)
    { return (float)cap_getSignal_PT_StatusPowerDisplay_1537(noSqcErrors); }

/**
 * Set the value of signal noSqcErrors of outbound PDU StatusPowerDisplay
 * (1537, 0x601) on bus PT in the global API.
 *   @param newValue
 * This value is written into the global API.
 */
void set_PT_1537_noSqcErrors(float newValue)
    { cap_getSignal_PT_StatusPowerDisplay_1537(noSqcErrors) = (uint16_t)(newValue + 0.5f); }

/**
 * Get the value of signal sequenceCounter of outbound PDU StatusPowerDisplay
 * (1537, 0x601) on bus PT.
 *   @return
 * Get the current value form the global API.
 */
float get_PT_1537_sequenceCounter(void)
    { return (float)cap_getSignal_PT_StatusPowerDisplay_1537(sequenceCounter); }

/**
 * Set the value of signal sequenceCounter of outbound PDU StatusPowerDisplay
 * (1537, 0x601) on bus PT in the global API.
 *   @param newValue
 * This value is written into the global API.
 */
void set_PT_1537_sequenceCounter(float newValue)
    { cap_getSignal_PT_StatusPowerDisplay_1537(sequenceCounter) = (uint8_t)(newValue + 0.5f); }

/**
 * Get the value of signal checksum of outbound PDU StatusPowerDisplay
 * (1537, 0x601) on bus PT.
 *   @return
 * Get the current value form the global API.
 */
float get_PT_1537_checksum(void)
    { return (float)cap_getSignal_PT_StatusPowerDisplay_1537(checksum); }

/**
 * Set the value of signal checksum of outbound PDU StatusPowerDisplay
 * (1537, 0x601) on bus PT in the global API.
 *   @param newValue
 * This value is written into the global API.
 */
void set_PT_1537_checksum(float newValue)
    { cap_getSignal_PT_StatusPowerDisplay_1537(checksum) = (uint8_t)(newValue + 0.5f); }

/**
 * Get the value of signal sequenceCounter of outbound PDU LimitsPowerDisplay
 * (1538, 0x602) on bus PT.
 *   @return
 * Get the current value form the global API.
 */
float get_PT_1538_sequenceCounter(void)
    { return (float)cap_getSignal_PT_LimitsPowerDisplay_1538(sequenceCounter); }

/**
 * Set the value of signal sequenceCounter of outbound PDU LimitsPowerDisplay
 * (1538, 0x602) on bus PT in the global API.
 *   @param newValue
 * This value is written into the global API.
 */
void set_PT_1538_sequenceCounter(float newValue)
    { cap_getSignal_PT_LimitsPowerDisplay_1538(sequenceCounter) = (uint8_t)(newValue + 0.5f); }

/**
 * Get the value of signal belowMinSpeedOfRotation of outbound PDU LimitsPowerDisplay
 * (1538, 0x602) on bus PT.
 *   @return
 * Get the current value form the global API.
 */
float get_PT_1538_belowMinSpeedOfRotation(void)
    { return (float)cap_getSignal_PT_LimitsPowerDisplay_1538(belowMinSpeedOfRotation); }

/**
 * Set the value of signal belowMinSpeedOfRotation of outbound PDU LimitsPowerDisplay
 * (1538, 0x602) on bus PT in the global API.
 *   @param newValue
 * This value is written into the global API.
 */
void set_PT_1538_belowMinSpeedOfRotation(float newValue)
    { cap_getSignal_PT_LimitsPowerDisplay_1538(belowMinSpeedOfRotation) = (boolean_t)(int)(newValue + 0.5f); }

/**
 * Get the value of signal aboveMaxSpeedOfRotation of outbound PDU LimitsPowerDisplay
 * (1538, 0x602) on bus PT.
 *   @return
 * Get the current value form the global API.
 */
float get_PT_1538_aboveMaxSpeedOfRotation(void)
    { return (float)cap_getSignal_PT_LimitsPowerDisplay_1538(aboveMaxSpeedOfRotation); }

/**
 * Set the value of signal aboveMaxSpeedOfRotation of outbound PDU LimitsPowerDisplay
 * (1538, 0x602) on bus PT in the global API.
 *   @param newValue
 * This value is written into the global API.
 */
void set_PT_1538_aboveMaxSpeedOfRotation(float newValue)
    { cap_getSignal_PT_LimitsPowerDisplay_1538(aboveMaxSpeedOfRotation) = (boolean_t)(int)(newValue + 0.5f); }

/**
 * Get the value of signal belowMinPower of outbound PDU LimitsPowerDisplay
 * (1538, 0x602) on bus PT.
 *   @return
 * Get the current value form the global API.
 */
float get_PT_1538_belowMinPower(void)
    { return (float)cap_getSignal_PT_LimitsPowerDisplay_1538(belowMinPower); }

/**
 * Set the value of signal belowMinPower of outbound PDU LimitsPowerDisplay
 * (1538, 0x602) on bus PT in the global API.
 *   @param newValue
 * This value is written into the global API.
 */
void set_PT_1538_belowMinPower(float newValue)
    { cap_getSignal_PT_LimitsPowerDisplay_1538(belowMinPower) = (boolean_t)(int)(newValue + 0.5f); }

/**
 * Get the value of signal aboveMaxPower of outbound PDU LimitsPowerDisplay
 * (1538, 0x602) on bus PT.
 *   @return
 * Get the current value form the global API.
 */
float get_PT_1538_aboveMaxPower(void)
    { return (float)cap_getSignal_PT_LimitsPowerDisplay_1538(aboveMaxPower); }

/**
 * Set the value of signal aboveMaxPower of outbound PDU LimitsPowerDisplay
 * (1538, 0x602) on bus PT in the global API.
 *   @param newValue
 * This value is written into the global API.
 */
void set_PT_1538_aboveMaxPower(float newValue)
    { cap_getSignal_PT_LimitsPowerDisplay_1538(aboveMaxPower) = (boolean_t)(int)(newValue + 0.5f); }

