/**
 * @file cap_canApi.c
 * 
 * This file implements the data oriented CAN API between the Embedded Coder generated APSW
 * code and the upper layers of the CAN stack. The global data structure is initialized
 * with the initial signal values from the CAN network database.\n
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
 * This file has been created with comFramework - codeGenerator version 1.11.2,
 * see http://sourceforge.net/projects/comframe/
 *
 * Copyright (C) 2015-2022 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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

#include "cap_canApi.h"

#include <string.h>
#include <assert.h>

#include "types.h"

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

/** Provide direct read/write access to the external struct, which bundles the signals of
    frame StateEcu01 (1024, 0x400) on bus PT. This struct is a nested
    sub-element of the large the CAN bus describing struct cap_canBus_PT.\n
      This pointer can be used with Embedded Coder's access method "ImportedExternPointer".
      @remark This pointer should be a const data object. However, this is impossible for
    the same reason, why the default custom storage can't be used: The Embedded Coder
    generates an extern declaration, which doesn't consider the const attribute. Having it
    here would lead to conflicting types. */
cap_PT_StateEcu01_1024_t *cap_pPT_StateEcu01_1024 =
        &cap_canBus_PT.PT_StateEcu01_1024_sts.signals;

/** Provide direct read/write access to the external struct, which bundles the signals of
    frame StateEcu02 (1040, 0x410) on bus PT. This struct is a nested
    sub-element of the large the CAN bus describing struct cap_canBus_PT.\n
      This pointer can be used with Embedded Coder's access method "ImportedExternPointer".
      @remark This pointer should be a const data object. However, this is impossible for
    the same reason, why the default custom storage can't be used: The Embedded Coder
    generates an extern declaration, which doesn't consider the const attribute. Having it
    here would lead to conflicting types. */
cap_PT_StateEcu02_1040_t *cap_pPT_StateEcu02_1040 =
        &cap_canBus_PT.PT_StateEcu02_1040_sts.signals;

/** Provide direct read/write access to the external struct, which bundles the signals of
    frame UserLimits (2032, 0x7f0) on bus PT. This struct is a nested
    sub-element of the large the CAN bus describing struct cap_canBus_PT.\n
      This pointer can be used with Embedded Coder's access method "ImportedExternPointer".
      @remark This pointer should be a const data object. However, this is impossible for
    the same reason, why the default custom storage can't be used: The Embedded Coder
    generates an extern declaration, which doesn't consider the const attribute. Having it
    here would lead to conflicting types. */
cap_PT_UserLimits_2032_t *cap_pPT_UserLimits_2032 =
        &cap_canBus_PT.PT_UserLimits_2032_sts.signals;

/** Provide direct read/write access to the external struct, which bundles the signals of
    frame InfoPowerDisplay (1536, 0x600) on bus PT. This struct is a nested
    sub-element of the large the CAN bus describing struct cap_canBus_PT.\n
      This pointer can be used with Embedded Coder's access method "ImportedExternPointer".
      @remark This pointer should be a const data object. However, this is impossible for
    the same reason, why the default custom storage can't be used: The Embedded Coder
    generates an extern declaration, which doesn't consider the const attribute. Having it
    here would lead to conflicting types. */
cap_PT_InfoPowerDisplay_1536_t *cap_pPT_InfoPowerDisplay_1536 =
        &cap_canBus_PT.PT_InfoPowerDisplay_1536_sts.signals;

/** Provide direct read/write access to the external struct, which bundles the signals of
    frame StatusPowerDisplay (1537, 0x601) on bus PT. This struct is a nested
    sub-element of the large the CAN bus describing struct cap_canBus_PT.\n
      This pointer can be used with Embedded Coder's access method "ImportedExternPointer".
      @remark This pointer should be a const data object. However, this is impossible for
    the same reason, why the default custom storage can't be used: The Embedded Coder
    generates an extern declaration, which doesn't consider the const attribute. Having it
    here would lead to conflicting types. */
cap_PT_StatusPowerDisplay_1537_t *cap_pPT_StatusPowerDisplay_1537 =
        &cap_canBus_PT.PT_StatusPowerDisplay_1537_sts.signals;

/** Provide direct read/write access to the external struct, which bundles the signals of
    frame LimitsPowerDisplay (1538, 0x602) on bus PT. This struct is a nested
    sub-element of the large the CAN bus describing struct cap_canBus_PT.\n
      This pointer can be used with Embedded Coder's access method "ImportedExternPointer".
      @remark This pointer should be a const data object. However, this is impossible for
    the same reason, why the default custom storage can't be used: The Embedded Coder
    generates an extern declaration, which doesn't consider the const attribute. Having it
    here would lead to conflicting types. */
cap_PT_LimitsPowerDisplay_1538_t *cap_pPT_LimitsPowerDisplay_1538 =
        &cap_canBus_PT.PT_LimitsPowerDisplay_1538_sts.signals;

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
            .speedOfRotation = CAP_PT_1024_SPEEDOFROTATION_DBL_TO_BIN(0.0),
            .sequenceCounter = 0,
        },

        .stsTransmission = cap_stsTransm_neverReceived
    },

    /** Signals and transmission status of inbound CAN frame StateEcu02
        (1040, 0x410) on bus PT. */
    .PT_StateEcu02_1040_sts =
    {
        .signals =
        {
            .checksum = 0,
            .sequenceCounter = 0,
            .torque = CAP_PT_1040_TORQUE_DBL_TO_BIN(0.0),
        },

        .stsTransmission = cap_stsTransm_neverReceived
    },

    /** Signals and transmission status of inbound CAN frame UserLimits
        (2032, 0x7f0) on bus PT. */
    .PT_UserLimits_2032_sts =
    {
        .signals =
        {
            .sequenceCounter = 1,
            .minSpeedOfRotation = CAP_PT_2032_MINSPEEDOFROTATION_DBL_TO_BIN(800.0),
            .maxSpeedOfRotation = CAP_PT_2032_MAXSPEEDOFROTATION_DBL_TO_BIN(6000.0),
            .checksum = 0,
            .minPower = CAP_PT_2032_MINPOWER_DBL_TO_BIN(-1.0),
            .maxPower = CAP_PT_2032_MAXPOWER_DBL_TO_BIN(100.0),
        },

        .stsTransmission = cap_stsTransm_neverReceived
    },

    /** Signals and transmission status of outbound CAN frame InfoPowerDisplay
        (1536, 0x600) on bus PT. */
    .PT_InfoPowerDisplay_1536_sts =
    {
        .signals =
        {
            .checksum = 0,
            .sequenceCounter = 0,
            .power = CAP_PT_1536_POWER_DBL_TO_BIN(0.0),
            .state = 0,
        },

        .stsTransmission = cap_stsTransm_okay
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

        .stsTransmission = cap_stsTransm_okay
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

        .stsTransmission = cap_stsTransm_okay
    },


}; /* End of cap_canBus_PT_t cap_canBus_PT */


 

/*
 * Function implementation
 */

#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU StateEcu01 (1024, 0x400) on bus PT
 * into a byte array of 4 Byte.\n
 *   The signal values are read from the global interface struct
 * cap_canBus_PT.PT_StateEcu01_1024_sts.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to null.
 */

void cap_pack_PT_StateEcu01_1024(uint8_T m[])
{
    /* The further commands will partly use bitwise OR commands to write the signal values.
       Those bytes, which are not entirely occupied by the signals need to be cleared at
       the beginning. */
    m[1] = 0;
    m[3] = 0;

    /* Pack signal checksum. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_T s = (uint8_T)cap_canBus_PT.PT_StateEcu01_1024_sts.signals.checksum;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (uint8_T)s;
    }

    /* Pack signal speedOfRotation. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint32_T s = (uint32_T)cap_canBus_PT.PT_StateEcu01_1024_sts.signals.speedOfRotation << 4;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[3] |= (uint8_T)(s & 0xf0);
        s >>= 8;
        m[2] = (uint8_T)s;
        s >>= 8;
        m[1] |= (uint8_T)(s & 0x0f);
    }

    /* Pack signal sequenceCounter. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_T s = (uint8_T)cap_canBus_PT.PT_StateEcu01_1024_sts.signals.sequenceCounter << 4;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] |= (uint8_T)(s & 0xf0);
    }
} /* End of cap_pack_PT_StateEcu01_1024 */
#endif



/**
 * Unpack the signals of inbound PDU StateEcu01 (1024, 0x400) on bus PT
 * from a byte array of 4 Byte.\n
 *   The signal values are written into the global interface struct
 * cap_canBus_PT.PT_StateEcu01_1024_sts.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void cap_unpack_PT_StateEcu01_1024(const uint8_T m[])
{
    /* Decode all normal, not multiplexed signals. */
    cap_canBus_PT.PT_StateEcu01_1024_sts.signals.checksum =
        (uint8_T)((uint8_T)m[0]);
    cap_canBus_PT.PT_StateEcu01_1024_sts.signals.speedOfRotation =
        (uint16_T)(((((((uint32_T)(m[1] & 0x0f)) << 8) | m[2]) << 8) | m[3]) >> 4);
    cap_canBus_PT.PT_StateEcu01_1024_sts.signals.sequenceCounter =
        (uint8_T)(((uint8_T)(m[1] & 0xf0)) >> 4);

} /* End of cap_unpack_PT_StateEcu01_1024 */



#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU StateEcu02 (1040, 0x410) on bus PT
 * into a byte array of 4 Byte.\n
 *   The signal values are read from the global interface struct
 * cap_canBus_PT.PT_StateEcu02_1040_sts.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to null.
 */

void cap_pack_PT_StateEcu02_1040(uint8_T m[])
{
    /* The further commands will partly use bitwise OR commands to write the signal values.
       Those bytes, which are not entirely occupied by the signals need to be cleared at
       the beginning. */
    m[1] = 0;
    m[2] = 0;
    m[3] = 0;

    /* Pack signal checksum. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_T s = (uint8_T)cap_canBus_PT.PT_StateEcu02_1040_sts.signals.checksum;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (uint8_T)s;
    }

    /* Pack signal sequenceCounter. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_T s = (uint8_T)cap_canBus_PT.PT_StateEcu02_1040_sts.signals.sequenceCounter;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] |= (uint8_T)(s & 0x0f);
    }

    /* Pack signal torque. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint16_T s = (uint16_T)cap_canBus_PT.PT_StateEcu02_1040_sts.signals.torque << (5-1);

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[3] |= (uint8_T)(s & 0xf0);
        s >>= 8;
        m[2] |= (uint8_T)(s & 0x7f);
    }
} /* End of cap_pack_PT_StateEcu02_1040 */
#endif



/**
 * Unpack the signals of inbound PDU StateEcu02 (1040, 0x410) on bus PT
 * from a byte array of 4 Byte.\n
 *   The signal values are written into the global interface struct
 * cap_canBus_PT.PT_StateEcu02_1040_sts.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void cap_unpack_PT_StateEcu02_1040(const uint8_T m[])
{
    /* Decode all normal, not multiplexed signals. */
    cap_canBus_PT.PT_StateEcu02_1040_sts.signals.checksum =
        (uint8_T)((uint8_T)m[0]);
    cap_canBus_PT.PT_StateEcu02_1040_sts.signals.sequenceCounter =
        (uint8_T)((uint8_T)(m[1] & 0x0f));
    cap_canBus_PT.PT_StateEcu02_1040_sts.signals.torque =
        (int16_T)((int16_T)(((((uint16_T)m[2]) << 8) | m[3]) << 1) >> 5);

} /* End of cap_unpack_PT_StateEcu02_1040 */



#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU UserLimits (2032, 0x7f0) on bus PT
 * into a byte array of 8 Byte.\n
 *   The signal values are read from the global interface struct
 * cap_canBus_PT.PT_UserLimits_2032_sts.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to null.
 */

void cap_pack_PT_UserLimits_2032(uint8_T m[])
{
    /* The further commands will partly use bitwise OR commands to write the signal values.
       Those bytes, which are not entirely occupied by the signals need to be cleared at
       the beginning. */
    memset(m, /* value */ 0, /* noBytes */ 8);

    /* Pack signal sequenceCounter. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_T s = (uint8_T)cap_canBus_PT.PT_UserLimits_2032_sts.signals.sequenceCounter << 2;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] |= (uint8_T)(s & 0x3c);
    }

    /* Pack signal minSpeedOfRotation. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint32_T s = (uint32_T)cap_canBus_PT.PT_UserLimits_2032_sts.signals.minSpeedOfRotation << 6;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] |= (uint8_T)(s & 0xc0);
        s >>= 8;
        m[1] = (uint8_T)s;
        s >>= 8;
        m[2] |= (uint8_T)(s & 0x03);
    }

    /* Pack signal maxSpeedOfRotation. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint16_T s = (uint16_T)cap_canBus_PT.PT_UserLimits_2032_sts.signals.maxSpeedOfRotation << 2;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[2] |= (uint8_T)(s & 0xfc);
        s >>= 8;
        m[3] |= (uint8_T)(s & 0x3f);
    }

    /* Pack signal checksum. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_T s = (uint8_T)cap_canBus_PT.PT_UserLimits_2032_sts.signals.checksum;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[4] = (uint8_T)s;
    }

    /* Pack signal minPower. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint16_T s = (uint16_T)cap_canBus_PT.PT_UserLimits_2032_sts.signals.minPower << 7;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[6] |= (uint8_T)(s & 0x80);
        s >>= 8;
        m[5] = (uint8_T)s;
    }

    /* Pack signal maxPower. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint16_T s = (uint16_T)cap_canBus_PT.PT_UserLimits_2032_sts.signals.maxPower << 5;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[7] |= (uint8_T)(s & 0xe0);
        s >>= 8;
        m[6] |= (uint8_T)(s & 0x3f);
    }
} /* End of cap_pack_PT_UserLimits_2032 */
#endif



/**
 * Unpack the signals of inbound PDU UserLimits (2032, 0x7f0) on bus PT
 * from a byte array of 8 Byte.\n
 *   The signal values are written into the global interface struct
 * cap_canBus_PT.PT_UserLimits_2032_sts.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void cap_unpack_PT_UserLimits_2032(const uint8_T m[])
{
    /* Decode all normal, not multiplexed signals. */
    cap_canBus_PT.PT_UserLimits_2032_sts.signals.sequenceCounter =
        (uint8_T)(((uint8_T)(m[0] & 0x3c)) >> 2);
    cap_canBus_PT.PT_UserLimits_2032_sts.signals.minSpeedOfRotation =
        (uint16_T)(((((((uint32_T)(m[2] & 0x03)) << 8) | m[1]) << 8) | m[0]) >> 6);
    cap_canBus_PT.PT_UserLimits_2032_sts.signals.maxSpeedOfRotation =
        (uint16_T)(((((uint16_T)(m[3] & 0x3f)) << 8) | m[2]) >> 2);
    cap_canBus_PT.PT_UserLimits_2032_sts.signals.checksum =
        (uint8_T)((uint8_T)m[4]);
    cap_canBus_PT.PT_UserLimits_2032_sts.signals.minPower =
        (uint16_T)(((((uint16_T)m[5]) << 8) | m[6]) >> 7);
    cap_canBus_PT.PT_UserLimits_2032_sts.signals.maxPower =
        (uint16_T)(((((uint16_T)(m[6] & 0x3f)) << 8) | m[7]) >> 5);

} /* End of cap_unpack_PT_UserLimits_2032 */


/**
 * Pack the signals of outbound PDU InfoPowerDisplay (1536, 0x600) on bus PT
 * into a byte array of 6 Byte.\n
 *   The signal values are read from the global interface struct
 * cap_canBus_PT.PT_InfoPowerDisplay_1536_sts.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to null.
 */

void cap_pack_PT_InfoPowerDisplay_1536(uint8_T m[])
{
    /* The further commands will partly use bitwise OR commands to write the signal values.
       Those bytes, which are not entirely occupied by the signals need to be cleared at
       the beginning. */
    memset(m, /* value */ 0, /* noBytes */ 6);

    /* Pack signal checksum. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_T s = (uint8_T)cap_canBus_PT.PT_InfoPowerDisplay_1536_sts.signals.checksum;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (uint8_T)s;
    }

    /* Pack signal sequenceCounter. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_T s = (uint8_T)cap_canBus_PT.PT_InfoPowerDisplay_1536_sts.signals.sequenceCounter;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] |= (uint8_T)(s & 0x0f);
    }

    /* Pack signal power. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint32_T s = (uint32_T)cap_canBus_PT.PT_InfoPowerDisplay_1536_sts.signals.power << 5;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] |= (uint8_T)(s & 0xe0);
        s >>= 8;
        m[2] = (uint8_T)s;
        s >>= 8;
        m[3] |= (uint8_T)(s & 0x0f);
    }

    /* Pack signal state. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint16_T s = (uint16_T)cap_canBus_PT.PT_InfoPowerDisplay_1536_sts.signals.state << 7;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[5] |= (uint8_T)(s & 0x80);
        s >>= 8;
        m[4] |= (uint8_T)(s & 0x03);
    }
} /* End of cap_pack_PT_InfoPowerDisplay_1536 */


#if CAP_UNCONDITIONALLY_GENERATE_UNPACK_FCTS != 0
/**
 * Unpack the signals of outbound PDU InfoPowerDisplay (1536, 0x600) on bus PT
 * from a byte array of 6 Byte.\n
 *   The signal values are written into the global interface struct
 * cap_canBus_PT.PT_InfoPowerDisplay_1536_sts.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void cap_unpack_PT_InfoPowerDisplay_1536(const uint8_T m[])
{
    /* Decode all normal, not multiplexed signals. */
    cap_canBus_PT.PT_InfoPowerDisplay_1536_sts.signals.checksum =
        (uint8_T)((uint8_T)m[0]);
    cap_canBus_PT.PT_InfoPowerDisplay_1536_sts.signals.sequenceCounter =
        (uint8_T)((uint8_T)(m[1] & 0x0f));
    cap_canBus_PT.PT_InfoPowerDisplay_1536_sts.signals.power =
        (uint16_T)(((((((uint32_T)(m[3] & 0x0f)) << 8) | m[2]) << 8) | m[1]) >> 5);
    cap_canBus_PT.PT_InfoPowerDisplay_1536_sts.signals.state =
        (uint8_T)(((((uint16_T)(m[4] & 0x03)) << 8) | m[5]) >> 7);

} /* End of cap_unpack_PT_InfoPowerDisplay_1536 */
#endif



/**
 * Pack the signals of outbound PDU StatusPowerDisplay (1537, 0x601) on bus PT
 * into a byte array of 6 Byte.\n
 *   The signal values are read from the global interface struct
 * cap_canBus_PT.PT_StatusPowerDisplay_1537_sts.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to null.
 */

void cap_pack_PT_StatusPowerDisplay_1537(uint8_T m[])
{
    /* The further commands will partly use bitwise OR commands to write the signal values.
       Those bytes, which are not entirely occupied by the signals need to be cleared at
       the beginning. */
    m[1] = 0;
    m[2] = 0;
    m[4] = 0;

    /* Pack signal noDlcErrors. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint16_T s = (uint16_T)cap_canBus_PT.PT_StatusPowerDisplay_1537_sts.signals.noDlcErrors;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (uint8_T)s;
        s >>= 8;
        m[1] |= (uint8_T)(s & 0x07);
    }

    /* Pack signal noCheckSumErrors. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint16_T s = (uint16_T)cap_canBus_PT.PT_StatusPowerDisplay_1537_sts.signals.noCheckSumErrors << 3;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] |= (uint8_T)(s & 0xf8);
        s >>= 8;
        m[2] |= (uint8_T)(s & 0x3f);
    }

    /* Pack signal noSqcErrors. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint32_T s = (uint32_T)cap_canBus_PT.PT_StatusPowerDisplay_1537_sts.signals.noSqcErrors << 6;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[2] |= (uint8_T)(s & 0xc0);
        s >>= 8;
        m[3] = (uint8_T)s;
        s >>= 8;
        m[4] |= (uint8_T)(s & 0x01);
    }

    /* Pack signal sequenceCounter. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_T s = (uint8_T)cap_canBus_PT.PT_StatusPowerDisplay_1537_sts.signals.sequenceCounter << 1;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[4] |= (uint8_T)(s & 0xfe);
    }

    /* Pack signal checksum. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_T s = (uint8_T)cap_canBus_PT.PT_StatusPowerDisplay_1537_sts.signals.checksum;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[5] = (uint8_T)s;
    }
} /* End of cap_pack_PT_StatusPowerDisplay_1537 */


#if CAP_UNCONDITIONALLY_GENERATE_UNPACK_FCTS != 0
/**
 * Unpack the signals of outbound PDU StatusPowerDisplay (1537, 0x601) on bus PT
 * from a byte array of 6 Byte.\n
 *   The signal values are written into the global interface struct
 * cap_canBus_PT.PT_StatusPowerDisplay_1537_sts.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void cap_unpack_PT_StatusPowerDisplay_1537(const uint8_T m[])
{
    /* Decode all normal, not multiplexed signals. */
    cap_canBus_PT.PT_StatusPowerDisplay_1537_sts.signals.noDlcErrors =
        (uint16_T)((((uint16_T)(m[1] & 0x07)) << 8) | m[0]);
    cap_canBus_PT.PT_StatusPowerDisplay_1537_sts.signals.noCheckSumErrors =
        (uint16_T)(((((uint16_T)(m[2] & 0x3f)) << 8) | m[1]) >> 3);
    cap_canBus_PT.PT_StatusPowerDisplay_1537_sts.signals.noSqcErrors =
        (uint16_T)(((((((uint32_T)(m[4] & 0x01)) << 8) | m[3]) << 8) | m[2]) >> 6);
    cap_canBus_PT.PT_StatusPowerDisplay_1537_sts.signals.sequenceCounter =
        (uint8_T)(((uint8_T)(m[4] & 0xfe)) >> 1);
    cap_canBus_PT.PT_StatusPowerDisplay_1537_sts.signals.checksum =
        (uint8_T)((uint8_T)m[5]);

} /* End of cap_unpack_PT_StatusPowerDisplay_1537 */
#endif



/**
 * Pack the signals of outbound PDU LimitsPowerDisplay (1538, 0x602) on bus PT
 * into a byte array of 1 Byte.\n
 *   The signal values are read from the global interface struct
 * cap_canBus_PT.PT_LimitsPowerDisplay_1538_sts.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to null.
 */

void cap_pack_PT_LimitsPowerDisplay_1538(uint8_T m[])
{
    /* The further commands will partly use bitwise OR commands to write the signal values.
       Those bytes, which are not entirely occupied by the signals need to be cleared at
       the beginning. */
    m[0] = 0;

    /* Pack signal sequenceCounter. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_T s = (uint8_T)cap_canBus_PT.PT_LimitsPowerDisplay_1538_sts.signals.sequenceCounter;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] |= (uint8_T)(s & 0x07);
    }

    /* Pack signal belowMinSpeedOfRotation. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_T s = (uint8_T)cap_canBus_PT.PT_LimitsPowerDisplay_1538_sts.signals.belowMinSpeedOfRotation << 3;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] |= (uint8_T)(s & 0x08);
    }

    /* Pack signal aboveMaxSpeedOfRotation. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_T s = (uint8_T)cap_canBus_PT.PT_LimitsPowerDisplay_1538_sts.signals.aboveMaxSpeedOfRotation << 4;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] |= (uint8_T)(s & 0x10);
    }

    /* Pack signal belowMinPower. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_T s = (uint8_T)cap_canBus_PT.PT_LimitsPowerDisplay_1538_sts.signals.belowMinPower << 5;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] |= (uint8_T)(s & 0x20);
    }

    /* Pack signal aboveMaxPower. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_T s = (uint8_T)cap_canBus_PT.PT_LimitsPowerDisplay_1538_sts.signals.aboveMaxPower << 6;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] |= (uint8_T)(s & 0x40);
    }
} /* End of cap_pack_PT_LimitsPowerDisplay_1538 */


#if CAP_UNCONDITIONALLY_GENERATE_UNPACK_FCTS != 0
/**
 * Unpack the signals of outbound PDU LimitsPowerDisplay (1538, 0x602) on bus PT
 * from a byte array of 1 Byte.\n
 *   The signal values are written into the global interface struct
 * cap_canBus_PT.PT_LimitsPowerDisplay_1538_sts.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void cap_unpack_PT_LimitsPowerDisplay_1538(const uint8_T m[])
{
    /* Decode all normal, not multiplexed signals. */
    cap_canBus_PT.PT_LimitsPowerDisplay_1538_sts.signals.sequenceCounter =
        (uint8_T)((uint8_T)(m[0] & 0x07));
    cap_canBus_PT.PT_LimitsPowerDisplay_1538_sts.signals.belowMinSpeedOfRotation =
        (boolean_T)(((uint8_T)(m[0] & 0x08)) >> 3);
    cap_canBus_PT.PT_LimitsPowerDisplay_1538_sts.signals.aboveMaxSpeedOfRotation =
        (boolean_T)(((uint8_T)(m[0] & 0x10)) >> 4);
    cap_canBus_PT.PT_LimitsPowerDisplay_1538_sts.signals.belowMinPower =
        (boolean_T)(((uint8_T)(m[0] & 0x20)) >> 5);
    cap_canBus_PT.PT_LimitsPowerDisplay_1538_sts.signals.aboveMaxPower =
        (boolean_T)(((uint8_T)(m[0] & 0x40)) >> 6);

} /* End of cap_unpack_PT_LimitsPowerDisplay_1538 */
#endif



