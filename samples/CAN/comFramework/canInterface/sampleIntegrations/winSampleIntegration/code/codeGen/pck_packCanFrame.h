#ifndef PCK_PACKCANFRAME_DEFINED
#define PCK_PACKCANFRAME_DEFINED
/**
 * @file pck_packCanFrame.h
 * Declaration of pack/unpack functions for the CAN frames of cluster winSampleIntegration.
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

#include "types.h"
#include "cbk_callbacks.h"


/*
 * Defines
 */

#ifndef PCK_UNCONDITIONALLY_GENERATE_PACK_FCTS
/** Normally, a pack function is generated for sent frames only. If this define is set to a
    value other than 0 then a pack function is generated for received Frames, too. */
# define PCK_UNCONDITIONALLY_GENERATE_PACK_FCTS 0
#endif

#ifndef PCK_UNCONDITIONALLY_GENERATE_UNPACK_FCTS
/** Normally, an unpack function is generated for received Frames only. If this define is set
    to a value other than 0 then an unpack function is generated for sent Frames, too. */
# define PCK_UNCONDITIONALLY_GENERATE_UNPACK_FCTS 0
#endif


/** The minimum of the world value of signal checksum of frame
    StateEcu01 (1024, 0x400) on bus PT. */
#define PCK_PT_1024_CHECKSUM_MIN	(0)

/** The maximum of the world value of signal checksum of frame
    StateEcu01 (1024, 0x400) on bus PT. */
#define PCK_PT_1024_CHECKSUM_MAX	(255)


/** Convert the binary value of signal speedOfRotation of frame
    StateEcu01 (1024, 0x400) as received via the CAN interface
    into the world value. */
#define PCK_PT_1024_SPEEDOFROTATION_BIN_TO_DBL(bin) \
            ((double)(bin)*PCK_PT_1024_SPEEDOFROTATION_FACTOR+PCK_PT_1024_SPEEDOFROTATION_OFFSET)

/** Convert the world value of signal speedOfRotation of frame
    StateEcu01 (1024, 0x400) into the binary value as transmitted
    via the CAN interface. */
#define PCK_PT_1024_SPEEDOFROTATION_DBL_TO_BIN(dbl) \
            ((uint16_t)(((dbl)-PCK_PT_1024_SPEEDOFROTATION_OFFSET)/PCK_PT_1024_SPEEDOFROTATION_FACTOR))

/** The gain factor of the scaling of signal speedOfRotation of frame
    StateEcu01 (1024, 0x400). */
#define PCK_PT_1024_SPEEDOFROTATION_FACTOR	(0.1)

/** The offset of the scaling of signal speedOfRotation of frame
    StateEcu01 (1024, 0x400). */
#define PCK_PT_1024_SPEEDOFROTATION_OFFSET	(0.0)

/** The minimum of the world value of signal speedOfRotation of frame
    StateEcu01 (1024, 0x400) on bus PT. */
#define PCK_PT_1024_SPEEDOFROTATION_MIN	(0.0)

/** The maximum of the world value of signal speedOfRotation of frame
    StateEcu01 (1024, 0x400) on bus PT. */
#define PCK_PT_1024_SPEEDOFROTATION_MAX	(6500.0)

/** The minimum of the world value of signal sequenceCounter of frame
    StateEcu01 (1024, 0x400) on bus PT. */
#define PCK_PT_1024_SEQUENCECOUNTER_MIN	(0)

/** The maximum of the world value of signal sequenceCounter of frame
    StateEcu01 (1024, 0x400) on bus PT. */
#define PCK_PT_1024_SEQUENCECOUNTER_MAX	(14)

/** The minimum of the world value of signal checksum of frame
    StateEcu02 (1040, 0x410) on bus PT. */
#define PCK_PT_1040_CHECKSUM_MIN	(0)

/** The maximum of the world value of signal checksum of frame
    StateEcu02 (1040, 0x410) on bus PT. */
#define PCK_PT_1040_CHECKSUM_MAX	(255)

/** The minimum of the world value of signal sequenceCounter of frame
    StateEcu02 (1040, 0x410) on bus PT. */
#define PCK_PT_1040_SEQUENCECOUNTER_MIN	(15)

/** The maximum of the world value of signal sequenceCounter of frame
    StateEcu02 (1040, 0x410) on bus PT. */
#define PCK_PT_1040_SEQUENCECOUNTER_MAX	(1)


/** Convert the binary value of signal torque of frame
    StateEcu02 (1040, 0x410) as received via the CAN interface
    into the world value. */
#define PCK_PT_1040_TORQUE_BIN_TO_DBL(bin) \
            ((double)(bin)*PCK_PT_1040_TORQUE_FACTOR+PCK_PT_1040_TORQUE_OFFSET)

/** Convert the world value of signal torque of frame
    StateEcu02 (1040, 0x410) into the binary value as transmitted
    via the CAN interface. */
#define PCK_PT_1040_TORQUE_DBL_TO_BIN(dbl) \
            ((int16_t)(((dbl)-PCK_PT_1040_TORQUE_OFFSET)/PCK_PT_1040_TORQUE_FACTOR))

/** The gain factor of the scaling of signal torque of frame
    StateEcu02 (1040, 0x410). */
#define PCK_PT_1040_TORQUE_FACTOR	(0.5)

/** The offset of the scaling of signal torque of frame
    StateEcu02 (1040, 0x410). */
#define PCK_PT_1040_TORQUE_OFFSET	(0.0)

/** The minimum of the world value of signal torque of frame
    StateEcu02 (1040, 0x410) on bus PT. */
#define PCK_PT_1040_TORQUE_MIN	(-500.0)

/** The maximum of the world value of signal torque of frame
    StateEcu02 (1040, 0x410) on bus PT. */
#define PCK_PT_1040_TORQUE_MAX	(500.0)

/** The minimum of the world value of signal sequenceCounter of frame
    UserLimits (2032, 0x7f0) on bus PT. */
#define PCK_PT_2032_SEQUENCECOUNTER_MIN	(1)

/** The maximum of the world value of signal sequenceCounter of frame
    UserLimits (2032, 0x7f0) on bus PT. */
#define PCK_PT_2032_SEQUENCECOUNTER_MAX	(14)


/** Convert the binary value of signal minSpeedOfRotation of frame
    UserLimits (2032, 0x7f0) as received via the CAN interface
    into the world value. */
#define PCK_PT_2032_MINSPEEDOFROTATION_BIN_TO_DBL(bin) \
            ((double)(bin)*PCK_PT_2032_MINSPEEDOFROTATION_FACTOR+PCK_PT_2032_MINSPEEDOFROTATION_OFFSET)

/** Convert the world value of signal minSpeedOfRotation of frame
    UserLimits (2032, 0x7f0) into the binary value as transmitted
    via the CAN interface. */
#define PCK_PT_2032_MINSPEEDOFROTATION_DBL_TO_BIN(dbl) \
            ((uint16_t)(((dbl)-PCK_PT_2032_MINSPEEDOFROTATION_OFFSET)/PCK_PT_2032_MINSPEEDOFROTATION_FACTOR))

/** The gain factor of the scaling of signal minSpeedOfRotation of frame
    UserLimits (2032, 0x7f0). */
#define PCK_PT_2032_MINSPEEDOFROTATION_FACTOR	(1.6)

/** The offset of the scaling of signal minSpeedOfRotation of frame
    UserLimits (2032, 0x7f0). */
#define PCK_PT_2032_MINSPEEDOFROTATION_OFFSET	(0.0)

/** The minimum of the world value of signal minSpeedOfRotation of frame
    UserLimits (2032, 0x7f0) on bus PT. */
#define PCK_PT_2032_MINSPEEDOFROTATION_MIN	(0.0)

/** The maximum of the world value of signal minSpeedOfRotation of frame
    UserLimits (2032, 0x7f0) on bus PT. */
#define PCK_PT_2032_MINSPEEDOFROTATION_MAX	(6500.0)


/** Convert the binary value of signal maxSpeedOfRotation of frame
    UserLimits (2032, 0x7f0) as received via the CAN interface
    into the world value. */
#define PCK_PT_2032_MAXSPEEDOFROTATION_BIN_TO_DBL(bin) \
            ((double)(bin)*PCK_PT_2032_MAXSPEEDOFROTATION_FACTOR+PCK_PT_2032_MAXSPEEDOFROTATION_OFFSET)

/** Convert the world value of signal maxSpeedOfRotation of frame
    UserLimits (2032, 0x7f0) into the binary value as transmitted
    via the CAN interface. */
#define PCK_PT_2032_MAXSPEEDOFROTATION_DBL_TO_BIN(dbl) \
            ((uint16_t)(((dbl)-PCK_PT_2032_MAXSPEEDOFROTATION_OFFSET)/PCK_PT_2032_MAXSPEEDOFROTATION_FACTOR))

/** The gain factor of the scaling of signal maxSpeedOfRotation of frame
    UserLimits (2032, 0x7f0). */
#define PCK_PT_2032_MAXSPEEDOFROTATION_FACTOR	(1.6)

/** The offset of the scaling of signal maxSpeedOfRotation of frame
    UserLimits (2032, 0x7f0). */
#define PCK_PT_2032_MAXSPEEDOFROTATION_OFFSET	(0.0)

/** The minimum of the world value of signal maxSpeedOfRotation of frame
    UserLimits (2032, 0x7f0) on bus PT. */
#define PCK_PT_2032_MAXSPEEDOFROTATION_MIN	(0.0)

/** The maximum of the world value of signal maxSpeedOfRotation of frame
    UserLimits (2032, 0x7f0) on bus PT. */
#define PCK_PT_2032_MAXSPEEDOFROTATION_MAX	(6500.0)

/** The minimum of the world value of signal checksum of frame
    UserLimits (2032, 0x7f0) on bus PT. */
#define PCK_PT_2032_CHECKSUM_MIN	(0)

/** The maximum of the world value of signal checksum of frame
    UserLimits (2032, 0x7f0) on bus PT. */
#define PCK_PT_2032_CHECKSUM_MAX	(255)


/** Convert the binary value of signal minPower of frame
    UserLimits (2032, 0x7f0) as received via the CAN interface
    into the world value. */
#define PCK_PT_2032_MINPOWER_BIN_TO_DBL(bin) \
            ((double)(bin)*PCK_PT_2032_MINPOWER_FACTOR+PCK_PT_2032_MINPOWER_OFFSET)

/** Convert the world value of signal minPower of frame
    UserLimits (2032, 0x7f0) into the binary value as transmitted
    via the CAN interface. */
#define PCK_PT_2032_MINPOWER_DBL_TO_BIN(dbl) \
            ((uint16_t)(((dbl)-PCK_PT_2032_MINPOWER_OFFSET)/PCK_PT_2032_MINPOWER_FACTOR))

/** The gain factor of the scaling of signal minPower of frame
    UserLimits (2032, 0x7f0). */
#define PCK_PT_2032_MINPOWER_FACTOR	(0.5)

/** The offset of the scaling of signal minPower of frame
    UserLimits (2032, 0x7f0). */
#define PCK_PT_2032_MINPOWER_OFFSET	(-10.0)

/** The minimum of the world value of signal minPower of frame
    UserLimits (2032, 0x7f0) on bus PT. */
#define PCK_PT_2032_MINPOWER_MIN	(-10.0)

/** The maximum of the world value of signal minPower of frame
    UserLimits (2032, 0x7f0) on bus PT. */
#define PCK_PT_2032_MINPOWER_MAX	(240.0)


/** Convert the binary value of signal maxPower of frame
    UserLimits (2032, 0x7f0) as received via the CAN interface
    into the world value. */
#define PCK_PT_2032_MAXPOWER_BIN_TO_DBL(bin) \
            ((double)(bin)*PCK_PT_2032_MAXPOWER_FACTOR+PCK_PT_2032_MAXPOWER_OFFSET)

/** Convert the world value of signal maxPower of frame
    UserLimits (2032, 0x7f0) into the binary value as transmitted
    via the CAN interface. */
#define PCK_PT_2032_MAXPOWER_DBL_TO_BIN(dbl) \
            ((uint16_t)(((dbl)-PCK_PT_2032_MAXPOWER_OFFSET)/PCK_PT_2032_MAXPOWER_FACTOR))

/** The gain factor of the scaling of signal maxPower of frame
    UserLimits (2032, 0x7f0). */
#define PCK_PT_2032_MAXPOWER_FACTOR	(0.5)

/** The offset of the scaling of signal maxPower of frame
    UserLimits (2032, 0x7f0). */
#define PCK_PT_2032_MAXPOWER_OFFSET	(-10.0)

/** The minimum of the world value of signal maxPower of frame
    UserLimits (2032, 0x7f0) on bus PT. */
#define PCK_PT_2032_MAXPOWER_MIN	(-10.0)

/** The maximum of the world value of signal maxPower of frame
    UserLimits (2032, 0x7f0) on bus PT. */
#define PCK_PT_2032_MAXPOWER_MAX	(240.0)

/** The minimum of the world value of signal checksum of frame
    InfoPowerDisplay (1536, 0x600) on bus PT. */
#define PCK_PT_1536_CHECKSUM_MIN	(0)

/** The maximum of the world value of signal checksum of frame
    InfoPowerDisplay (1536, 0x600) on bus PT. */
#define PCK_PT_1536_CHECKSUM_MAX	(255)

/** The minimum of the world value of signal sequenceCounter of frame
    InfoPowerDisplay (1536, 0x600) on bus PT. */
#define PCK_PT_1536_SEQUENCECOUNTER_MIN	(0)

/** The maximum of the world value of signal sequenceCounter of frame
    InfoPowerDisplay (1536, 0x600) on bus PT. */
#define PCK_PT_1536_SEQUENCECOUNTER_MAX	(14)


/** Convert the binary value of signal power of frame
    InfoPowerDisplay (1536, 0x600) as received via the CAN interface
    into the world value. */
#define PCK_PT_1536_POWER_BIN_TO_DBL(bin) \
            ((double)(bin)*PCK_PT_1536_POWER_FACTOR+PCK_PT_1536_POWER_OFFSET)

/** Convert the world value of signal power of frame
    InfoPowerDisplay (1536, 0x600) into the binary value as transmitted
    via the CAN interface. */
#define PCK_PT_1536_POWER_DBL_TO_BIN(dbl) \
            ((uint16_t)(((dbl)-PCK_PT_1536_POWER_OFFSET)/PCK_PT_1536_POWER_FACTOR))

/** The gain factor of the scaling of signal power of frame
    InfoPowerDisplay (1536, 0x600). */
#define PCK_PT_1536_POWER_FACTOR	(32.0)

/** The offset of the scaling of signal power of frame
    InfoPowerDisplay (1536, 0x600). */
#define PCK_PT_1536_POWER_OFFSET	(-500000.0)

/** The minimum of the world value of signal power of frame
    InfoPowerDisplay (1536, 0x600) on bus PT. */
#define PCK_PT_1536_POWER_MIN	(-500000.0)

/** The maximum of the world value of signal power of frame
    InfoPowerDisplay (1536, 0x600) on bus PT. */
#define PCK_PT_1536_POWER_MAX	(500000.0)

/** The minimum of the world value of signal state of frame
    InfoPowerDisplay (1536, 0x600) on bus PT. */
#define PCK_PT_1536_STATE_MIN	(0)

/** The maximum of the world value of signal state of frame
    InfoPowerDisplay (1536, 0x600) on bus PT. */
#define PCK_PT_1536_STATE_MAX	(2)

/** The minimum of the world value of signal noDlcErrors of frame
    StatusPowerDisplay (1537, 0x601) on bus PT. */
#define PCK_PT_1537_NODLCERRORS_MIN	(0)

/** The maximum of the world value of signal noDlcErrors of frame
    StatusPowerDisplay (1537, 0x601) on bus PT. */
#define PCK_PT_1537_NODLCERRORS_MAX	(2047)

/** The minimum of the world value of signal noCheckSumErrors of frame
    StatusPowerDisplay (1537, 0x601) on bus PT. */
#define PCK_PT_1537_NOCHECKSUMERRORS_MIN	(0)

/** The maximum of the world value of signal noCheckSumErrors of frame
    StatusPowerDisplay (1537, 0x601) on bus PT. */
#define PCK_PT_1537_NOCHECKSUMERRORS_MAX	(2047)

/** The minimum of the world value of signal noSqcErrors of frame
    StatusPowerDisplay (1537, 0x601) on bus PT. */
#define PCK_PT_1537_NOSQCERRORS_MIN	(0)

/** The maximum of the world value of signal noSqcErrors of frame
    StatusPowerDisplay (1537, 0x601) on bus PT. */
#define PCK_PT_1537_NOSQCERRORS_MAX	(2047)

/** The minimum of the world value of signal sequenceCounter of frame
    StatusPowerDisplay (1537, 0x601) on bus PT. */
#define PCK_PT_1537_SEQUENCECOUNTER_MIN	(1)

/** The maximum of the world value of signal sequenceCounter of frame
    StatusPowerDisplay (1537, 0x601) on bus PT. */
#define PCK_PT_1537_SEQUENCECOUNTER_MAX	(126)

/** The minimum of the world value of signal checksum of frame
    StatusPowerDisplay (1537, 0x601) on bus PT. */
#define PCK_PT_1537_CHECKSUM_MIN	(0)

/** The maximum of the world value of signal checksum of frame
    StatusPowerDisplay (1537, 0x601) on bus PT. */
#define PCK_PT_1537_CHECKSUM_MAX	(255)

/** The minimum of the world value of signal sequenceCounter of frame
    LimitsPowerDisplay (1538, 0x602) on bus PT. */
#define PCK_PT_1538_SEQUENCECOUNTER_MIN	(6)

/** The maximum of the world value of signal sequenceCounter of frame
    LimitsPowerDisplay (1538, 0x602) on bus PT. */
#define PCK_PT_1538_SEQUENCECOUNTER_MAX	(1)

/** The minimum of the world value of signal belowMinSpeedOfRotation of frame
    LimitsPowerDisplay (1538, 0x602) on bus PT. */
#define PCK_PT_1538_BELOWMINSPEEDOFROTATION_MIN	(0)

/** The maximum of the world value of signal belowMinSpeedOfRotation of frame
    LimitsPowerDisplay (1538, 0x602) on bus PT. */
#define PCK_PT_1538_BELOWMINSPEEDOFROTATION_MAX	(1)

/** The minimum of the world value of signal aboveMaxSpeedOfRotation of frame
    LimitsPowerDisplay (1538, 0x602) on bus PT. */
#define PCK_PT_1538_ABOVEMAXSPEEDOFROTATION_MIN	(0)

/** The maximum of the world value of signal aboveMaxSpeedOfRotation of frame
    LimitsPowerDisplay (1538, 0x602) on bus PT. */
#define PCK_PT_1538_ABOVEMAXSPEEDOFROTATION_MAX	(1)

/** The minimum of the world value of signal belowMinPower of frame
    LimitsPowerDisplay (1538, 0x602) on bus PT. */
#define PCK_PT_1538_BELOWMINPOWER_MIN	(0)

/** The maximum of the world value of signal belowMinPower of frame
    LimitsPowerDisplay (1538, 0x602) on bus PT. */
#define PCK_PT_1538_BELOWMINPOWER_MAX	(1)

/** The minimum of the world value of signal aboveMaxPower of frame
    LimitsPowerDisplay (1538, 0x602) on bus PT. */
#define PCK_PT_1538_ABOVEMAXPOWER_MIN	(0)

/** The maximum of the world value of signal aboveMaxPower of frame
    LimitsPowerDisplay (1538, 0x602) on bus PT. */
#define PCK_PT_1538_ABOVEMAXPOWER_MAX	(1)

 

/*
 * Type definitions
 */

/** The signals of CAN frame StateEcu01 (1024, 0x400) on bus PT. */
typedef struct pck_PT_StateEcu01_1024_t
{
    /** Signal checksum. */
    uint8_t checksum;

    /** Signal speedOfRotation. */
    uint16_t speedOfRotation;

    /** Signal sequenceCounter. */
    uint8_t sequenceCounter;

} pck_PT_StateEcu01_1024_t;


/** The signals of CAN frame StateEcu02 (1040, 0x410) on bus PT. */
typedef struct pck_PT_StateEcu02_1040_t
{
    /** Signal checksum. */
    uint8_t checksum;

    /** Signal sequenceCounter. */
    uint8_t sequenceCounter;

    /** Signal torque. */
    int16_t torque;

} pck_PT_StateEcu02_1040_t;


/** The signals of CAN frame UserLimits (2032, 0x7f0) on bus PT. */
typedef struct pck_PT_UserLimits_2032_t
{
    /** Signal sequenceCounter. */
    uint8_t sequenceCounter;

    /** Signal minSpeedOfRotation. */
    uint16_t minSpeedOfRotation;

    /** Signal maxSpeedOfRotation. */
    uint16_t maxSpeedOfRotation;

    /** Signal checksum. */
    uint8_t checksum;

    /** Signal minPower. */
    uint16_t minPower;

    /** Signal maxPower. */
    uint16_t maxPower;

} pck_PT_UserLimits_2032_t;


/** The signals of CAN frame InfoPowerDisplay (1536, 0x600) on bus PT. */
typedef struct pck_PT_InfoPowerDisplay_1536_t
{
    /** Signal checksum. */
    uint8_t checksum;

    /** Signal sequenceCounter. */
    uint8_t sequenceCounter;

    /** Signal power. */
    uint16_t power;

    /** Signal state. */
    uint8_t state;

} pck_PT_InfoPowerDisplay_1536_t;


/** The signals of CAN frame StatusPowerDisplay (1537, 0x601) on bus PT. */
typedef struct pck_PT_StatusPowerDisplay_1537_t
{
    /** Signal noDlcErrors. */
    uint16_t noDlcErrors;

    /** Signal noCheckSumErrors. */
    uint16_t noCheckSumErrors;

    /** Signal noSqcErrors. */
    uint16_t noSqcErrors;

    /** Signal sequenceCounter. */
    uint8_t sequenceCounter;

    /** Signal checksum. */
    uint8_t checksum;

} pck_PT_StatusPowerDisplay_1537_t;


/** The signals of CAN frame LimitsPowerDisplay (1538, 0x602) on bus PT. */
typedef struct pck_PT_LimitsPowerDisplay_1538_t
{
    /** Signal sequenceCounter. */
    uint8_t sequenceCounter;

    /** Signal belowMinSpeedOfRotation. */
    bool belowMinSpeedOfRotation;

    /** Signal aboveMaxSpeedOfRotation. */
    bool aboveMaxSpeedOfRotation;

    /** Signal belowMinPower. */
    bool belowMinPower;

    /** Signal aboveMaxPower. */
    bool aboveMaxPower;

} pck_PT_LimitsPowerDisplay_1538_t;


/** Signals and transmission status of CAN frame StateEcu01 (1024, 0x400) on bus PT.
    A global variable of this type is used as API between CAN interface and APSW. */
typedef struct pck_API_PT_StateEcu01_1024_t
{
    /** The collection of signals of the frame. */
    pck_PT_StateEcu01_1024_t signals;

    /** The transmission status. */
    cbk_stsTransmission_t stsTransmission;

} pck_API_PT_StateEcu01_1024_t;


/** Signals and transmission status of CAN frame StateEcu02 (1040, 0x410) on bus PT.
    A global variable of this type is used as API between CAN interface and APSW. */
typedef struct pck_API_PT_StateEcu02_1040_t
{
    /** The collection of signals of the frame. */
    pck_PT_StateEcu02_1040_t signals;

    /** The transmission status. */
    cbk_stsTransmission_t stsTransmission;

} pck_API_PT_StateEcu02_1040_t;


/** Signals and transmission status of CAN frame UserLimits (2032, 0x7f0) on bus PT.
    A global variable of this type is used as API between CAN interface and APSW. */
typedef struct pck_API_PT_UserLimits_2032_t
{
    /** The collection of signals of the frame. */
    pck_PT_UserLimits_2032_t signals;

    /** The transmission status. */
    cbk_stsTransmission_t stsTransmission;

} pck_API_PT_UserLimits_2032_t;


/** Signals and transmission status of CAN frame InfoPowerDisplay (1536, 0x600) on bus PT.
    A global variable of this type is used as API between CAN interface and APSW. */
typedef struct pck_API_PT_InfoPowerDisplay_1536_t
{
    /** The collection of signals of the frame. */
    pck_PT_InfoPowerDisplay_1536_t signals;

    /** The transmission status. */
    cbk_stsTransmission_t stsTransmission;

} pck_API_PT_InfoPowerDisplay_1536_t;


/** Signals and transmission status of CAN frame StatusPowerDisplay (1537, 0x601) on bus PT.
    A global variable of this type is used as API between CAN interface and APSW. */
typedef struct pck_API_PT_StatusPowerDisplay_1537_t
{
    /** The collection of signals of the frame. */
    pck_PT_StatusPowerDisplay_1537_t signals;

    /** The transmission status. */
    cbk_stsTransmission_t stsTransmission;

} pck_API_PT_StatusPowerDisplay_1537_t;


/** Signals and transmission status of CAN frame LimitsPowerDisplay (1538, 0x602) on bus PT.
    A global variable of this type is used as API between CAN interface and APSW. */
typedef struct pck_API_PT_LimitsPowerDisplay_1538_t
{
    /** The collection of signals of the frame. */
    pck_PT_LimitsPowerDisplay_1538_t signals;

    /** The transmission status. */
    cbk_stsTransmission_t stsTransmission;

} pck_API_PT_LimitsPowerDisplay_1538_t;


 

/*
 * Data declarations
 */

/** Signals and transmission status of CAN frame StateEcu01 (1024, 0x400) on bus PT.
    This global variable is used as API between CAN interface and APSW. */
extern pck_API_PT_StateEcu01_1024_t pck_API_PT_StateEcu01_1024;

/** Signals and transmission status of CAN frame StateEcu02 (1040, 0x410) on bus PT.
    This global variable is used as API between CAN interface and APSW. */
extern pck_API_PT_StateEcu02_1040_t pck_API_PT_StateEcu02_1040;

/** Signals and transmission status of CAN frame UserLimits (2032, 0x7f0) on bus PT.
    This global variable is used as API between CAN interface and APSW. */
extern pck_API_PT_UserLimits_2032_t pck_API_PT_UserLimits_2032;

/** Signals and transmission status of CAN frame InfoPowerDisplay (1536, 0x600) on bus PT.
    This global variable is used as API between CAN interface and APSW. */
extern pck_API_PT_InfoPowerDisplay_1536_t pck_API_PT_InfoPowerDisplay_1536;

/** Signals and transmission status of CAN frame StatusPowerDisplay (1537, 0x601) on bus PT.
    This global variable is used as API between CAN interface and APSW. */
extern pck_API_PT_StatusPowerDisplay_1537_t pck_API_PT_StatusPowerDisplay_1537;

/** Signals and transmission status of CAN frame LimitsPowerDisplay (1538, 0x602) on bus PT.
    This global variable is used as API between CAN interface and APSW. */
extern pck_API_PT_LimitsPowerDisplay_1538_t pck_API_PT_LimitsPowerDisplay_1538;

 

/*
 * Function declarations
 */

#if PCK_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/** Pack the signal values of inbound PDU StateEcu01 (1024, 0x400)
    into a byte array of 4 Byte. The signal values are read from the global interface
    struct pck_API_PT_StateEcu01_1024. */
void pck_pack_PT_StateEcu01_1024(uint8_t m[]);
#endif

/** Unpack the signals of inbound PDU StateEcu01 (1024, 0x400) from
    a byte array of 4 Byte. The signal values are written into the global interface struct
    pck_API_PT_StateEcu01_1024. */
void pck_unpack_PT_StateEcu01_1024(const uint8_t m[]);


#if PCK_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/** Pack the signal values of inbound PDU StateEcu02 (1040, 0x410)
    into a byte array of 4 Byte. The signal values are read from the global interface
    struct pck_API_PT_StateEcu02_1040. */
void pck_pack_PT_StateEcu02_1040(uint8_t m[]);
#endif

/** Unpack the signals of inbound PDU StateEcu02 (1040, 0x410) from
    a byte array of 4 Byte. The signal values are written into the global interface struct
    pck_API_PT_StateEcu02_1040. */
void pck_unpack_PT_StateEcu02_1040(const uint8_t m[]);


#if PCK_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/** Pack the signal values of inbound PDU UserLimits (2032, 0x7f0)
    into a byte array of 8 Byte. The signal values are read from the global interface
    struct pck_API_PT_UserLimits_2032. */
void pck_pack_PT_UserLimits_2032(uint8_t m[]);
#endif

/** Unpack the signals of inbound PDU UserLimits (2032, 0x7f0) from
    a byte array of 8 Byte. The signal values are written into the global interface struct
    pck_API_PT_UserLimits_2032. */
void pck_unpack_PT_UserLimits_2032(const uint8_t m[]);

/** Pack the signal values of outbound PDU InfoPowerDisplay (1536, 0x600)
    into a byte array of 6 Byte. The signal values are read from the global interface
    struct pck_API_PT_InfoPowerDisplay_1536. */
void pck_pack_PT_InfoPowerDisplay_1536(uint8_t m[]);

#if PCK_UNCONDITIONALLY_GENERATE_UNPACK_FCTS != 0
/** Unpack the signals of outbound PDU InfoPowerDisplay (1536, 0x600) from
    a byte array of 6 Byte. The signal values are written into the global interface struct
    pck_API_PT_InfoPowerDisplay_1536. */
void pck_unpack_PT_InfoPowerDisplay_1536(const uint8_t m[]);
#endif

/** Pack the signal values of outbound PDU StatusPowerDisplay (1537, 0x601)
    into a byte array of 6 Byte. The signal values are read from the global interface
    struct pck_API_PT_StatusPowerDisplay_1537. */
void pck_pack_PT_StatusPowerDisplay_1537(uint8_t m[]);

#if PCK_UNCONDITIONALLY_GENERATE_UNPACK_FCTS != 0
/** Unpack the signals of outbound PDU StatusPowerDisplay (1537, 0x601) from
    a byte array of 6 Byte. The signal values are written into the global interface struct
    pck_API_PT_StatusPowerDisplay_1537. */
void pck_unpack_PT_StatusPowerDisplay_1537(const uint8_t m[]);
#endif

/** Pack the signal values of outbound PDU LimitsPowerDisplay (1538, 0x602)
    into a byte array of 1 Byte. The signal values are read from the global interface
    struct pck_API_PT_LimitsPowerDisplay_1538. */
void pck_pack_PT_LimitsPowerDisplay_1538(uint8_t m[]);

#if PCK_UNCONDITIONALLY_GENERATE_UNPACK_FCTS != 0
/** Unpack the signals of outbound PDU LimitsPowerDisplay (1538, 0x602) from
    a byte array of 1 Byte. The signal values are written into the global interface struct
    pck_API_PT_LimitsPowerDisplay_1538. */
void pck_unpack_PT_LimitsPowerDisplay_1538(const uint8_t m[]);
#endif


#endif // !defined(PCK_PACKCANFRAME_DEFINED)