#ifndef CAP_CANAPI_DEFINED
#define CAP_CANAPI_DEFINED
/**
 * @file cap_canApi.h
 * Declaration of API and pack/unpack functions for the CAN frames of cluster ecSample.
 *
 * This file has been created with comFramework - codeGenerator version 1.10.6,
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

#include "types.h"


/*
 * Defines
 */

#ifndef CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS
/** Normally, a pack function is generated for sent frames only. If this define is set to a
    value other than 0 then a pack function is generated for received Frames, too. */
# define CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS 0
#endif

#ifndef CAP_UNCONDITIONALLY_GENERATE_UNPACK_FCTS
/** Normally, an unpack function is generated for received Frames only. If this define is set
    to a value other than 0 then an unpack function is generated for sent Frames, too. */
# define CAP_UNCONDITIONALLY_GENERATE_UNPACK_FCTS 0
#endif


/** The minimum of the world value of signal checksum of frame
    StateEcu01 (1024, 0x400) on bus PT. */
#define CAP_PT_1024_CHECKSUM_MIN	(0)

/** The maximum of the world value of signal checksum of frame
    StateEcu01 (1024, 0x400) on bus PT. */
#define CAP_PT_1024_CHECKSUM_MAX	(255)



/** Convert the binary value of signal speedOfRotation of frame
    StateEcu01 (1024, 0x400) on bus PT into the world value. */
#define CAP_PT_1024_SPEEDOFROTATION_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PT_1024_SPEEDOFROTATION_FACTOR)

/** Convert the world value of signal speedOfRotation of frame
    StateEcu01 (1024, 0x400) on bus PT into the binary value as
    transmitted via the CAN interface. */
#define CAP_PT_1024_SPEEDOFROTATION_DBL_TO_BIN(dbl) \
            ((uint16_T)((dbl)/CAP_PT_1024_SPEEDOFROTATION_FACTOR))

/** The gain factor of the scaling of signal speedOfRotation of frame
    StateEcu01 (1024, 0x400) on bus PT. */
#define CAP_PT_1024_SPEEDOFROTATION_FACTOR	(0.1)

/** The offset of the scaling of signal speedOfRotation of frame
    StateEcu01 (1024, 0x400) on bus PT. */
#define CAP_PT_1024_SPEEDOFROTATION_OFFSET	(0.0)

/** The minimum of the world value of signal speedOfRotation of frame
    StateEcu01 (1024, 0x400) on bus PT. */
#define CAP_PT_1024_SPEEDOFROTATION_MIN	(0.0)

/** The maximum of the world value of signal speedOfRotation of frame
    StateEcu01 (1024, 0x400) on bus PT. */
#define CAP_PT_1024_SPEEDOFROTATION_MAX	(6500.0)


/** The minimum of the world value of signal sequenceCounter of frame
    StateEcu01 (1024, 0x400) on bus PT. */
#define CAP_PT_1024_SEQUENCECOUNTER_MIN	(0)

/** The maximum of the world value of signal sequenceCounter of frame
    StateEcu01 (1024, 0x400) on bus PT. */
#define CAP_PT_1024_SEQUENCECOUNTER_MAX	(14)


/** The minimum of the world value of signal checksum of frame
    StateEcu02 (1040, 0x410) on bus PT. */
#define CAP_PT_1040_CHECKSUM_MIN	(0)

/** The maximum of the world value of signal checksum of frame
    StateEcu02 (1040, 0x410) on bus PT. */
#define CAP_PT_1040_CHECKSUM_MAX	(255)


/** The minimum of the world value of signal sequenceCounter of frame
    StateEcu02 (1040, 0x410) on bus PT. */
#define CAP_PT_1040_SEQUENCECOUNTER_MIN	(15)

/** The maximum of the world value of signal sequenceCounter of frame
    StateEcu02 (1040, 0x410) on bus PT. */
#define CAP_PT_1040_SEQUENCECOUNTER_MAX	(1)



/** Convert the binary value of signal torque of frame
    StateEcu02 (1040, 0x410) on bus PT into the world value. */
#define CAP_PT_1040_TORQUE_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PT_1040_TORQUE_FACTOR)

/** Convert the world value of signal torque of frame
    StateEcu02 (1040, 0x410) on bus PT into the binary value as
    transmitted via the CAN interface. */
#define CAP_PT_1040_TORQUE_DBL_TO_BIN(dbl) \
            ((int16_T)((dbl)/CAP_PT_1040_TORQUE_FACTOR))

/** The gain factor of the scaling of signal torque of frame
    StateEcu02 (1040, 0x410) on bus PT. */
#define CAP_PT_1040_TORQUE_FACTOR	(0.5)

/** The offset of the scaling of signal torque of frame
    StateEcu02 (1040, 0x410) on bus PT. */
#define CAP_PT_1040_TORQUE_OFFSET	(0.0)

/** The minimum of the world value of signal torque of frame
    StateEcu02 (1040, 0x410) on bus PT. */
#define CAP_PT_1040_TORQUE_MIN	(-500.0)

/** The maximum of the world value of signal torque of frame
    StateEcu02 (1040, 0x410) on bus PT. */
#define CAP_PT_1040_TORQUE_MAX	(500.0)


/** The minimum of the world value of signal sequenceCounter of frame
    UserLimits (2032, 0x7f0) on bus PT. */
#define CAP_PT_2032_SEQUENCECOUNTER_MIN	(1)

/** The maximum of the world value of signal sequenceCounter of frame
    UserLimits (2032, 0x7f0) on bus PT. */
#define CAP_PT_2032_SEQUENCECOUNTER_MAX	(14)



/** Convert the binary value of signal minSpeedOfRotation of frame
    UserLimits (2032, 0x7f0) on bus PT into the world value. */
#define CAP_PT_2032_MINSPEEDOFROTATION_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PT_2032_MINSPEEDOFROTATION_FACTOR)

/** Convert the world value of signal minSpeedOfRotation of frame
    UserLimits (2032, 0x7f0) on bus PT into the binary value as
    transmitted via the CAN interface. */
#define CAP_PT_2032_MINSPEEDOFROTATION_DBL_TO_BIN(dbl) \
            ((uint16_T)((dbl)/CAP_PT_2032_MINSPEEDOFROTATION_FACTOR))

/** The gain factor of the scaling of signal minSpeedOfRotation of frame
    UserLimits (2032, 0x7f0) on bus PT. */
#define CAP_PT_2032_MINSPEEDOFROTATION_FACTOR	(1.6)

/** The offset of the scaling of signal minSpeedOfRotation of frame
    UserLimits (2032, 0x7f0) on bus PT. */
#define CAP_PT_2032_MINSPEEDOFROTATION_OFFSET	(0.0)

/** The minimum of the world value of signal minSpeedOfRotation of frame
    UserLimits (2032, 0x7f0) on bus PT. */
#define CAP_PT_2032_MINSPEEDOFROTATION_MIN	(0.0)

/** The maximum of the world value of signal minSpeedOfRotation of frame
    UserLimits (2032, 0x7f0) on bus PT. */
#define CAP_PT_2032_MINSPEEDOFROTATION_MAX	(6500.0)



/** Convert the binary value of signal maxSpeedOfRotation of frame
    UserLimits (2032, 0x7f0) on bus PT into the world value. */
#define CAP_PT_2032_MAXSPEEDOFROTATION_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PT_2032_MAXSPEEDOFROTATION_FACTOR)

/** Convert the world value of signal maxSpeedOfRotation of frame
    UserLimits (2032, 0x7f0) on bus PT into the binary value as
    transmitted via the CAN interface. */
#define CAP_PT_2032_MAXSPEEDOFROTATION_DBL_TO_BIN(dbl) \
            ((uint16_T)((dbl)/CAP_PT_2032_MAXSPEEDOFROTATION_FACTOR))

/** The gain factor of the scaling of signal maxSpeedOfRotation of frame
    UserLimits (2032, 0x7f0) on bus PT. */
#define CAP_PT_2032_MAXSPEEDOFROTATION_FACTOR	(1.6)

/** The offset of the scaling of signal maxSpeedOfRotation of frame
    UserLimits (2032, 0x7f0) on bus PT. */
#define CAP_PT_2032_MAXSPEEDOFROTATION_OFFSET	(0.0)

/** The minimum of the world value of signal maxSpeedOfRotation of frame
    UserLimits (2032, 0x7f0) on bus PT. */
#define CAP_PT_2032_MAXSPEEDOFROTATION_MIN	(0.0)

/** The maximum of the world value of signal maxSpeedOfRotation of frame
    UserLimits (2032, 0x7f0) on bus PT. */
#define CAP_PT_2032_MAXSPEEDOFROTATION_MAX	(6500.0)


/** The minimum of the world value of signal checksum of frame
    UserLimits (2032, 0x7f0) on bus PT. */
#define CAP_PT_2032_CHECKSUM_MIN	(0)

/** The maximum of the world value of signal checksum of frame
    UserLimits (2032, 0x7f0) on bus PT. */
#define CAP_PT_2032_CHECKSUM_MAX	(255)



/** Convert the binary value of signal minPower of frame
    UserLimits (2032, 0x7f0) on bus PT into the world value. */
#define CAP_PT_2032_MINPOWER_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PT_2032_MINPOWER_FACTOR+CAP_PT_2032_MINPOWER_OFFSET)

/** Convert the world value of signal minPower of frame
    UserLimits (2032, 0x7f0) on bus PT into the binary value as
    transmitted via the CAN interface. */
#define CAP_PT_2032_MINPOWER_DBL_TO_BIN(dbl) \
            ((uint16_T)(((dbl)-CAP_PT_2032_MINPOWER_OFFSET)/CAP_PT_2032_MINPOWER_FACTOR))

/** The gain factor of the scaling of signal minPower of frame
    UserLimits (2032, 0x7f0) on bus PT. */
#define CAP_PT_2032_MINPOWER_FACTOR	(0.5)

/** The offset of the scaling of signal minPower of frame
    UserLimits (2032, 0x7f0) on bus PT. */
#define CAP_PT_2032_MINPOWER_OFFSET	(-10.0)

/** The minimum of the world value of signal minPower of frame
    UserLimits (2032, 0x7f0) on bus PT. */
#define CAP_PT_2032_MINPOWER_MIN	(-10.0)

/** The maximum of the world value of signal minPower of frame
    UserLimits (2032, 0x7f0) on bus PT. */
#define CAP_PT_2032_MINPOWER_MAX	(240.0)



/** Convert the binary value of signal maxPower of frame
    UserLimits (2032, 0x7f0) on bus PT into the world value. */
#define CAP_PT_2032_MAXPOWER_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PT_2032_MAXPOWER_FACTOR+CAP_PT_2032_MAXPOWER_OFFSET)

/** Convert the world value of signal maxPower of frame
    UserLimits (2032, 0x7f0) on bus PT into the binary value as
    transmitted via the CAN interface. */
#define CAP_PT_2032_MAXPOWER_DBL_TO_BIN(dbl) \
            ((uint16_T)(((dbl)-CAP_PT_2032_MAXPOWER_OFFSET)/CAP_PT_2032_MAXPOWER_FACTOR))

/** The gain factor of the scaling of signal maxPower of frame
    UserLimits (2032, 0x7f0) on bus PT. */
#define CAP_PT_2032_MAXPOWER_FACTOR	(0.5)

/** The offset of the scaling of signal maxPower of frame
    UserLimits (2032, 0x7f0) on bus PT. */
#define CAP_PT_2032_MAXPOWER_OFFSET	(-10.0)

/** The minimum of the world value of signal maxPower of frame
    UserLimits (2032, 0x7f0) on bus PT. */
#define CAP_PT_2032_MAXPOWER_MIN	(-10.0)

/** The maximum of the world value of signal maxPower of frame
    UserLimits (2032, 0x7f0) on bus PT. */
#define CAP_PT_2032_MAXPOWER_MAX	(240.0)


/** The minimum of the world value of signal checksum of frame
    InfoPowerDisplay (1536, 0x600) on bus PT. */
#define CAP_PT_1536_CHECKSUM_MIN	(0)

/** The maximum of the world value of signal checksum of frame
    InfoPowerDisplay (1536, 0x600) on bus PT. */
#define CAP_PT_1536_CHECKSUM_MAX	(255)


/** The minimum of the world value of signal sequenceCounter of frame
    InfoPowerDisplay (1536, 0x600) on bus PT. */
#define CAP_PT_1536_SEQUENCECOUNTER_MIN	(0)

/** The maximum of the world value of signal sequenceCounter of frame
    InfoPowerDisplay (1536, 0x600) on bus PT. */
#define CAP_PT_1536_SEQUENCECOUNTER_MAX	(14)



/** Convert the binary value of signal power of frame
    InfoPowerDisplay (1536, 0x600) on bus PT into the world value. */
#define CAP_PT_1536_POWER_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PT_1536_POWER_FACTOR+CAP_PT_1536_POWER_OFFSET)

/** Convert the world value of signal power of frame
    InfoPowerDisplay (1536, 0x600) on bus PT into the binary value as
    transmitted via the CAN interface. */
#define CAP_PT_1536_POWER_DBL_TO_BIN(dbl) \
            ((uint16_T)(((dbl)-CAP_PT_1536_POWER_OFFSET)/CAP_PT_1536_POWER_FACTOR))

/** The gain factor of the scaling of signal power of frame
    InfoPowerDisplay (1536, 0x600) on bus PT. */
#define CAP_PT_1536_POWER_FACTOR	(32.0)

/** The offset of the scaling of signal power of frame
    InfoPowerDisplay (1536, 0x600) on bus PT. */
#define CAP_PT_1536_POWER_OFFSET	(-500000.0)

/** The minimum of the world value of signal power of frame
    InfoPowerDisplay (1536, 0x600) on bus PT. */
#define CAP_PT_1536_POWER_MIN	(-500000.0)

/** The maximum of the world value of signal power of frame
    InfoPowerDisplay (1536, 0x600) on bus PT. */
#define CAP_PT_1536_POWER_MAX	(500000.0)


/** The minimum of the world value of signal state of frame
    InfoPowerDisplay (1536, 0x600) on bus PT. */
#define CAP_PT_1536_STATE_MIN	(0)

/** The maximum of the world value of signal state of frame
    InfoPowerDisplay (1536, 0x600) on bus PT. */
#define CAP_PT_1536_STATE_MAX	(2)


/** The minimum of the world value of signal noDlcErrors of frame
    StatusPowerDisplay (1537, 0x601) on bus PT. */
#define CAP_PT_1537_NODLCERRORS_MIN	(0)

/** The maximum of the world value of signal noDlcErrors of frame
    StatusPowerDisplay (1537, 0x601) on bus PT. */
#define CAP_PT_1537_NODLCERRORS_MAX	(2047)


/** The minimum of the world value of signal noCheckSumErrors of frame
    StatusPowerDisplay (1537, 0x601) on bus PT. */
#define CAP_PT_1537_NOCHECKSUMERRORS_MIN	(0)

/** The maximum of the world value of signal noCheckSumErrors of frame
    StatusPowerDisplay (1537, 0x601) on bus PT. */
#define CAP_PT_1537_NOCHECKSUMERRORS_MAX	(2047)


/** The minimum of the world value of signal noSqcErrors of frame
    StatusPowerDisplay (1537, 0x601) on bus PT. */
#define CAP_PT_1537_NOSQCERRORS_MIN	(0)

/** The maximum of the world value of signal noSqcErrors of frame
    StatusPowerDisplay (1537, 0x601) on bus PT. */
#define CAP_PT_1537_NOSQCERRORS_MAX	(2047)


/** The minimum of the world value of signal sequenceCounter of frame
    StatusPowerDisplay (1537, 0x601) on bus PT. */
#define CAP_PT_1537_SEQUENCECOUNTER_MIN	(1)

/** The maximum of the world value of signal sequenceCounter of frame
    StatusPowerDisplay (1537, 0x601) on bus PT. */
#define CAP_PT_1537_SEQUENCECOUNTER_MAX	(126)


/** The minimum of the world value of signal checksum of frame
    StatusPowerDisplay (1537, 0x601) on bus PT. */
#define CAP_PT_1537_CHECKSUM_MIN	(0)

/** The maximum of the world value of signal checksum of frame
    StatusPowerDisplay (1537, 0x601) on bus PT. */
#define CAP_PT_1537_CHECKSUM_MAX	(255)


/** The minimum of the world value of signal sequenceCounter of frame
    LimitsPowerDisplay (1538, 0x602) on bus PT. */
#define CAP_PT_1538_SEQUENCECOUNTER_MIN	(6)

/** The maximum of the world value of signal sequenceCounter of frame
    LimitsPowerDisplay (1538, 0x602) on bus PT. */
#define CAP_PT_1538_SEQUENCECOUNTER_MAX	(1)


/** The minimum of the world value of signal belowMinSpeedOfRotation of frame
    LimitsPowerDisplay (1538, 0x602) on bus PT. */
#define CAP_PT_1538_BELOWMINSPEEDOFROTATION_MIN	(0)

/** The maximum of the world value of signal belowMinSpeedOfRotation of frame
    LimitsPowerDisplay (1538, 0x602) on bus PT. */
#define CAP_PT_1538_BELOWMINSPEEDOFROTATION_MAX	(1)


/** The minimum of the world value of signal aboveMaxSpeedOfRotation of frame
    LimitsPowerDisplay (1538, 0x602) on bus PT. */
#define CAP_PT_1538_ABOVEMAXSPEEDOFROTATION_MIN	(0)

/** The maximum of the world value of signal aboveMaxSpeedOfRotation of frame
    LimitsPowerDisplay (1538, 0x602) on bus PT. */
#define CAP_PT_1538_ABOVEMAXSPEEDOFROTATION_MAX	(1)


/** The minimum of the world value of signal belowMinPower of frame
    LimitsPowerDisplay (1538, 0x602) on bus PT. */
#define CAP_PT_1538_BELOWMINPOWER_MIN	(0)

/** The maximum of the world value of signal belowMinPower of frame
    LimitsPowerDisplay (1538, 0x602) on bus PT. */
#define CAP_PT_1538_BELOWMINPOWER_MAX	(1)


/** The minimum of the world value of signal aboveMaxPower of frame
    LimitsPowerDisplay (1538, 0x602) on bus PT. */
#define CAP_PT_1538_ABOVEMAXPOWER_MIN	(0)

/** The maximum of the world value of signal aboveMaxPower of frame
    LimitsPowerDisplay (1538, 0x602) on bus PT. */
#define CAP_PT_1538_ABOVEMAXPOWER_MAX	(1)



/** The size in Byte of frame StateEcu01 (1024, 0x400) on bus PT. */
#define CAP_PT_STATEECU01_1024_DLC	4

/** The size in Bit of checksum signal of frame StateEcu01 (1024, 0x400)
    on bus PT. */
#define CAP_PT_STATEECU01_1024_CHECKSUM_LENGTH	8

/** The start bit of checksum signal of frame StateEcu01 (1024, 0x400)
    on bus PT. */
#define CAP_PT_STATEECU01_1024_CHECKSUM_STARTBIT	7

/** The endianness of checksum signal of frame StateEcu01 (1024, 0x400)
    on bus PT. */
#define CAP_PT_STATEECU01_1024_CHECKSUM_IS_BIG_ENDIAN	true

/** The data ID of checksum signal of frame StateEcu01 (1024, 0x400)
    on bus PT. */
#define CAP_PT_STATEECU01_1024_CHECKSUM_START_VALUE	17

/** The size in Bit of the sequence counter of frame StateEcu01 (1024, 0x400)
    on bus PT. */
#define CAP_PT_STATEECU01_1024_SQC_LENGTH	4

/** The minmum value of the sequence counter of frame StateEcu01 (1024, 0x400)
    on bus PT. */
#define CAP_PT_STATEECU01_1024_SQC_FROM	0

/** The maximum value of the sequence counter of frame StateEcu01 (1024, 0x400)
    on bus PT. */
#define CAP_PT_STATEECU01_1024_SQC_TO	14

/** The size in Byte of frame StateEcu02 (1040, 0x410) on bus PT. */
#define CAP_PT_STATEECU02_1040_DLC	4

/** The size in Bit of checksum signal of frame StateEcu02 (1040, 0x410)
    on bus PT. */
#define CAP_PT_STATEECU02_1040_CHECKSUM_LENGTH	8

/** The start bit of checksum signal of frame StateEcu02 (1040, 0x410)
    on bus PT. */
#define CAP_PT_STATEECU02_1040_CHECKSUM_STARTBIT	0

/** The endianness of checksum signal of frame StateEcu02 (1040, 0x410)
    on bus PT. */
#define CAP_PT_STATEECU02_1040_CHECKSUM_IS_BIG_ENDIAN	false

/** The data ID of checksum signal of frame StateEcu02 (1040, 0x410)
    on bus PT. */
#define CAP_PT_STATEECU02_1040_CHECKSUM_START_VALUE	218

/** The size in Bit of the sequence counter of frame StateEcu02 (1040, 0x410)
    on bus PT. */
#define CAP_PT_STATEECU02_1040_SQC_LENGTH	4

/** The minmum value of the sequence counter of frame StateEcu02 (1040, 0x410)
    on bus PT. */
#define CAP_PT_STATEECU02_1040_SQC_FROM	15

/** The maximum value of the sequence counter of frame StateEcu02 (1040, 0x410)
    on bus PT. */
#define CAP_PT_STATEECU02_1040_SQC_TO	1

/** The size in Byte of frame UserLimits (2032, 0x7f0) on bus PT. */
#define CAP_PT_USERLIMITS_2032_DLC	8

/** The size in Bit of checksum signal of frame UserLimits (2032, 0x7f0)
    on bus PT. */
#define CAP_PT_USERLIMITS_2032_CHECKSUM_LENGTH	8

/** The start bit of checksum signal of frame UserLimits (2032, 0x7f0)
    on bus PT. */
#define CAP_PT_USERLIMITS_2032_CHECKSUM_STARTBIT	39

/** The endianness of checksum signal of frame UserLimits (2032, 0x7f0)
    on bus PT. */
#define CAP_PT_USERLIMITS_2032_CHECKSUM_IS_BIG_ENDIAN	true

/** The data ID of checksum signal of frame UserLimits (2032, 0x7f0)
    on bus PT. */
#define CAP_PT_USERLIMITS_2032_CHECKSUM_START_VALUE	119

/** The size in Bit of the sequence counter of frame UserLimits (2032, 0x7f0)
    on bus PT. */
#define CAP_PT_USERLIMITS_2032_SQC_LENGTH	4

/** The minmum value of the sequence counter of frame UserLimits (2032, 0x7f0)
    on bus PT. */
#define CAP_PT_USERLIMITS_2032_SQC_FROM	1

/** The maximum value of the sequence counter of frame UserLimits (2032, 0x7f0)
    on bus PT. */
#define CAP_PT_USERLIMITS_2032_SQC_TO	14

/** The size in Byte of frame InfoPowerDisplay (1536, 0x600) on bus PT. */
#define CAP_PT_INFOPOWERDISPLAY_1536_DLC	6

/** The size in Bit of checksum signal of frame InfoPowerDisplay (1536, 0x600)
    on bus PT. */
#define CAP_PT_INFOPOWERDISPLAY_1536_CHECKSUM_LENGTH	8

/** The start bit of checksum signal of frame InfoPowerDisplay (1536, 0x600)
    on bus PT. */
#define CAP_PT_INFOPOWERDISPLAY_1536_CHECKSUM_STARTBIT	0

/** The endianness of checksum signal of frame InfoPowerDisplay (1536, 0x600)
    on bus PT. */
#define CAP_PT_INFOPOWERDISPLAY_1536_CHECKSUM_IS_BIG_ENDIAN	false

/** The data ID of checksum signal of frame InfoPowerDisplay (1536, 0x600)
    on bus PT. */
#define CAP_PT_INFOPOWERDISPLAY_1536_CHECKSUM_START_VALUE	112

/** The size in Bit of the sequence counter of frame InfoPowerDisplay (1536, 0x600)
    on bus PT. */
#define CAP_PT_INFOPOWERDISPLAY_1536_SQC_LENGTH	4

/** The minmum value of the sequence counter of frame InfoPowerDisplay (1536, 0x600)
    on bus PT. */
#define CAP_PT_INFOPOWERDISPLAY_1536_SQC_FROM	0

/** The maximum value of the sequence counter of frame InfoPowerDisplay (1536, 0x600)
    on bus PT. */
#define CAP_PT_INFOPOWERDISPLAY_1536_SQC_TO	14

/** The size in Byte of frame StatusPowerDisplay (1537, 0x601) on bus PT. */
#define CAP_PT_STATUSPOWERDISPLAY_1537_DLC	6

/** The size in Bit of checksum signal of frame StatusPowerDisplay (1537, 0x601)
    on bus PT. */
#define CAP_PT_STATUSPOWERDISPLAY_1537_CHECKSUM_LENGTH	8

/** The start bit of checksum signal of frame StatusPowerDisplay (1537, 0x601)
    on bus PT. */
#define CAP_PT_STATUSPOWERDISPLAY_1537_CHECKSUM_STARTBIT	47

/** The endianness of checksum signal of frame StatusPowerDisplay (1537, 0x601)
    on bus PT. */
#define CAP_PT_STATUSPOWERDISPLAY_1537_CHECKSUM_IS_BIG_ENDIAN	true

/** The data ID of checksum signal of frame StatusPowerDisplay (1537, 0x601)
    on bus PT. */
#define CAP_PT_STATUSPOWERDISPLAY_1537_CHECKSUM_START_VALUE	113

/** The size in Bit of the sequence counter of frame StatusPowerDisplay (1537, 0x601)
    on bus PT. */
#define CAP_PT_STATUSPOWERDISPLAY_1537_SQC_LENGTH	7

/** The minmum value of the sequence counter of frame StatusPowerDisplay (1537, 0x601)
    on bus PT. */
#define CAP_PT_STATUSPOWERDISPLAY_1537_SQC_FROM	1

/** The maximum value of the sequence counter of frame StatusPowerDisplay (1537, 0x601)
    on bus PT. */
#define CAP_PT_STATUSPOWERDISPLAY_1537_SQC_TO	126

/** The size in Byte of frame LimitsPowerDisplay (1538, 0x602) on bus PT. */
#define CAP_PT_LIMITSPOWERDISPLAY_1538_DLC	1

/** The size in Bit of the sequence counter of frame LimitsPowerDisplay (1538, 0x602)
    on bus PT. */
#define CAP_PT_LIMITSPOWERDISPLAY_1538_SQC_LENGTH	3

/** The minmum value of the sequence counter of frame LimitsPowerDisplay (1538, 0x602)
    on bus PT. */
#define CAP_PT_LIMITSPOWERDISPLAY_1538_SQC_FROM	6

/** The maximum value of the sequence counter of frame LimitsPowerDisplay (1538, 0x602)
    on bus PT. */
#define CAP_PT_LIMITSPOWERDISPLAY_1538_SQC_TO	1


 

/*
 * Type definitions
 */

/** The different status bits of the CAN transmission status word. */
typedef enum cap_enumStsTransmission_t
{
    /** No bit is set, no error or problem or else is reported. */
    cap_stsTransm_okay = 0,

    /** The frame has never been received since startup of the interface. Only for inbound
        frames. */
    cap_stsTransm_neverReceived = 1,

    /** The frame could not be sent, send buffer full. Only for outbound frames. */
    cap_stsTransm_errSendBufferFull = 1,

    /** The frame has not been received timely. */
    cap_stsTransm_errTimeout = 2,

    /** The received frame has a data error; the checksum doesn't match. No signals will be
        extracted. */ 
    cap_stsTransm_errChecksum = 4,

    /** The sequence counter of the received frame indicates a lost frame. */
    cap_stsTransm_errSequence = 8,

    /** The received frame doesn't have the expected size. No signals can be extracted. */
    cap_stsTransm_errDLC = 16

} cap_enumStsTransmission_t;


/** The type of the transmission status. The encoding of the information is done bit-wise,
    see enumeration \a cap_enumStsTransmission_t. The status variable is neither defined as an
    enumeration nor as a bit field in order to permit the use of binary operations to
    filter and combine status bits. Furthermore, having a defined word width means safer
    interfacing with the Embedded Coder. */
typedef uint8_T cap_stsTransmission_t;


/** The signals of inbound CAN frame StateEcu01 (1024, 0x400) on
    bus PT. */
typedef struct cap_PT_StateEcu01_1024_t
{
    /** Signal checksum. */
    uint8_T checksum;

    /** Signal speedOfRotation. */
    uint16_T speedOfRotation;

    /** Signal sequenceCounter. */
    uint8_T sequenceCounter;

} cap_PT_StateEcu01_1024_t;


/** The signals of inbound CAN frame StateEcu02 (1040, 0x410) on
    bus PT. */
typedef struct cap_PT_StateEcu02_1040_t
{
    /** Signal checksum. */
    uint8_T checksum;

    /** Signal sequenceCounter. */
    uint8_T sequenceCounter;

    /** Signal torque. */
    int16_T torque;

} cap_PT_StateEcu02_1040_t;


/** The signals of inbound CAN frame UserLimits (2032, 0x7f0) on
    bus PT. */
typedef struct cap_PT_UserLimits_2032_t
{
    /** Signal sequenceCounter. */
    uint8_T sequenceCounter;

    /** Signal minSpeedOfRotation. */
    uint16_T minSpeedOfRotation;

    /** Signal maxSpeedOfRotation. */
    uint16_T maxSpeedOfRotation;

    /** Signal checksum. */
    uint8_T checksum;

    /** Signal minPower. */
    uint16_T minPower;

    /** Signal maxPower. */
    uint16_T maxPower;

} cap_PT_UserLimits_2032_t;


/** The signals of outbound CAN frame InfoPowerDisplay (1536, 0x600) on
    bus PT. */
typedef struct cap_PT_InfoPowerDisplay_1536_t
{
    /** Signal checksum. */
    uint8_T checksum;

    /** Signal sequenceCounter. */
    uint8_T sequenceCounter;

    /** Signal power. */
    uint16_T power;

    /** Signal state. */
    uint8_T state;

} cap_PT_InfoPowerDisplay_1536_t;


/** The signals of outbound CAN frame StatusPowerDisplay (1537, 0x601) on
    bus PT. */
typedef struct cap_PT_StatusPowerDisplay_1537_t
{
    /** Signal noDlcErrors. */
    uint16_T noDlcErrors;

    /** Signal noCheckSumErrors. */
    uint16_T noCheckSumErrors;

    /** Signal noSqcErrors. */
    uint16_T noSqcErrors;

    /** Signal sequenceCounter. */
    uint8_T sequenceCounter;

    /** Signal checksum. */
    uint8_T checksum;

} cap_PT_StatusPowerDisplay_1537_t;


/** The signals of outbound CAN frame LimitsPowerDisplay (1538, 0x602) on
    bus PT. */
typedef struct cap_PT_LimitsPowerDisplay_1538_t
{
    /** Signal sequenceCounter. */
    uint8_T sequenceCounter;

    /** Signal belowMinSpeedOfRotation. */
    boolean_T belowMinSpeedOfRotation;

    /** Signal aboveMaxSpeedOfRotation. */
    boolean_T aboveMaxSpeedOfRotation;

    /** Signal belowMinPower. */
    boolean_T belowMinPower;

    /** Signal aboveMaxPower. */
    boolean_T aboveMaxPower;

} cap_PT_LimitsPowerDisplay_1538_t;


/** Signals and transmission status of inbound CAN frame StateEcu01
    (1024, 0x400) on bus PT. */
typedef struct cap_PT_StateEcu01_1024_sts_t
{
    /** The collection of signals of the frame. */
    cap_PT_StateEcu01_1024_t signals;

    /** The transmission status. */
    cap_stsTransmission_t stsTransmission;

} cap_PT_StateEcu01_1024_sts_t;


/** Signals and transmission status of inbound CAN frame StateEcu02
    (1040, 0x410) on bus PT. */
typedef struct cap_PT_StateEcu02_1040_sts_t
{
    /** The collection of signals of the frame. */
    cap_PT_StateEcu02_1040_t signals;

    /** The transmission status. */
    cap_stsTransmission_t stsTransmission;

} cap_PT_StateEcu02_1040_sts_t;


/** Signals and transmission status of inbound CAN frame UserLimits
    (2032, 0x7f0) on bus PT. */
typedef struct cap_PT_UserLimits_2032_sts_t
{
    /** The collection of signals of the frame. */
    cap_PT_UserLimits_2032_t signals;

    /** The transmission status. */
    cap_stsTransmission_t stsTransmission;

} cap_PT_UserLimits_2032_sts_t;


/** Signals and transmission status of outbound CAN frame InfoPowerDisplay
    (1536, 0x600) on bus PT. */
typedef struct cap_PT_InfoPowerDisplay_1536_sts_t
{
    /** The collection of signals of the frame. */
    cap_PT_InfoPowerDisplay_1536_t signals;

    /** The transmission status. */
    cap_stsTransmission_t stsTransmission;

} cap_PT_InfoPowerDisplay_1536_sts_t;


/** Signals and transmission status of outbound CAN frame StatusPowerDisplay
    (1537, 0x601) on bus PT. */
typedef struct cap_PT_StatusPowerDisplay_1537_sts_t
{
    /** The collection of signals of the frame. */
    cap_PT_StatusPowerDisplay_1537_t signals;

    /** The transmission status. */
    cap_stsTransmission_t stsTransmission;

} cap_PT_StatusPowerDisplay_1537_sts_t;


/** Signals and transmission status of outbound CAN frame LimitsPowerDisplay
    (1538, 0x602) on bus PT. */
typedef struct cap_PT_LimitsPowerDisplay_1538_sts_t
{
    /** The collection of signals of the frame. */
    cap_PT_LimitsPowerDisplay_1538_t signals;

    /** The transmission status. */
    cap_stsTransmission_t stsTransmission;

} cap_PT_LimitsPowerDisplay_1538_sts_t;



/** The frames and signals of CAN bus PT. A global variable of this type is used
    as API between the lower layers of the CAN stack and the APSW. */
typedef struct cap_canBus_PT_t
{
    /** Signals and transmission status of inbound CAN frame StateEcu01
        (1024, 0x400) */
    cap_PT_StateEcu01_1024_sts_t PT_StateEcu01_1024_sts;

    /** Signals and transmission status of inbound CAN frame StateEcu02
        (1040, 0x410) */
    cap_PT_StateEcu02_1040_sts_t PT_StateEcu02_1040_sts;

    /** Signals and transmission status of inbound CAN frame UserLimits
        (2032, 0x7f0) */
    cap_PT_UserLimits_2032_sts_t PT_UserLimits_2032_sts;

    /** Signals and transmission status of outbound CAN frame InfoPowerDisplay
        (1536, 0x600) */
    cap_PT_InfoPowerDisplay_1536_sts_t PT_InfoPowerDisplay_1536_sts;

    /** Signals and transmission status of outbound CAN frame StatusPowerDisplay
        (1537, 0x601) */
    cap_PT_StatusPowerDisplay_1537_sts_t PT_StatusPowerDisplay_1537_sts;

    /** Signals and transmission status of outbound CAN frame LimitsPowerDisplay
        (1538, 0x602) */
    cap_PT_LimitsPowerDisplay_1538_sts_t PT_LimitsPowerDisplay_1538_sts;


} cap_canBus_PT_t;


 

/*
 * Data declarations
 */

/** Provide direct read/write access to the external struct, which bundles the signals of
    frame StateEcu01 (1024, 0x400) on bus PT. This struct is a nested
    sub-element of the large the CAN bus describing struct cap_canBus_PT.\n
      This pointer can be used with Embedded Coder's access method "ImportedExternPointer".
      @remark This pointer should be a const data object. However, this is impossible for
    the same reason, why the default custom storage can't be used: The Embedded Coder
    generates an extern declaration, which doesn't consider the const attribute. Having it
    here would lead to conflicting types. */
extern cap_PT_StateEcu01_1024_t *cap_pPT_StateEcu01_1024;

/** Provide direct read/write access to the external struct, which bundles the signals of
    frame StateEcu02 (1040, 0x410) on bus PT. This struct is a nested
    sub-element of the large the CAN bus describing struct cap_canBus_PT.\n
      This pointer can be used with Embedded Coder's access method "ImportedExternPointer".
      @remark This pointer should be a const data object. However, this is impossible for
    the same reason, why the default custom storage can't be used: The Embedded Coder
    generates an extern declaration, which doesn't consider the const attribute. Having it
    here would lead to conflicting types. */
extern cap_PT_StateEcu02_1040_t *cap_pPT_StateEcu02_1040;

/** Provide direct read/write access to the external struct, which bundles the signals of
    frame UserLimits (2032, 0x7f0) on bus PT. This struct is a nested
    sub-element of the large the CAN bus describing struct cap_canBus_PT.\n
      This pointer can be used with Embedded Coder's access method "ImportedExternPointer".
      @remark This pointer should be a const data object. However, this is impossible for
    the same reason, why the default custom storage can't be used: The Embedded Coder
    generates an extern declaration, which doesn't consider the const attribute. Having it
    here would lead to conflicting types. */
extern cap_PT_UserLimits_2032_t *cap_pPT_UserLimits_2032;

/** Provide direct read/write access to the external struct, which bundles the signals of
    frame InfoPowerDisplay (1536, 0x600) on bus PT. This struct is a nested
    sub-element of the large the CAN bus describing struct cap_canBus_PT.\n
      This pointer can be used with Embedded Coder's access method "ImportedExternPointer".
      @remark This pointer should be a const data object. However, this is impossible for
    the same reason, why the default custom storage can't be used: The Embedded Coder
    generates an extern declaration, which doesn't consider the const attribute. Having it
    here would lead to conflicting types. */
extern cap_PT_InfoPowerDisplay_1536_t *cap_pPT_InfoPowerDisplay_1536;

/** Provide direct read/write access to the external struct, which bundles the signals of
    frame StatusPowerDisplay (1537, 0x601) on bus PT. This struct is a nested
    sub-element of the large the CAN bus describing struct cap_canBus_PT.\n
      This pointer can be used with Embedded Coder's access method "ImportedExternPointer".
      @remark This pointer should be a const data object. However, this is impossible for
    the same reason, why the default custom storage can't be used: The Embedded Coder
    generates an extern declaration, which doesn't consider the const attribute. Having it
    here would lead to conflicting types. */
extern cap_PT_StatusPowerDisplay_1537_t *cap_pPT_StatusPowerDisplay_1537;

/** Provide direct read/write access to the external struct, which bundles the signals of
    frame LimitsPowerDisplay (1538, 0x602) on bus PT. This struct is a nested
    sub-element of the large the CAN bus describing struct cap_canBus_PT.\n
      This pointer can be used with Embedded Coder's access method "ImportedExternPointer".
      @remark This pointer should be a const data object. However, this is impossible for
    the same reason, why the default custom storage can't be used: The Embedded Coder
    generates an extern declaration, which doesn't consider the const attribute. Having it
    here would lead to conflicting types. */
extern cap_PT_LimitsPowerDisplay_1538_t *cap_pPT_LimitsPowerDisplay_1538;

/** Signals and transmission status of CAN frames on bus PT. This global variable
    is used as API between the lower layers of the CAN stack and the APSW. */
extern cap_canBus_PT_t cap_canBus_PT;

 

/*
 * Function declarations
 */

#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/** Pack the signal values of inbound PDU StateEcu01 (1024, 0x400)
    into a byte array of 4 Byte. The signal values are read from the global interface
    struct cap_canBus_PT.PT_StateEcu01_1024_sts. */
void cap_pack_PT_StateEcu01_1024(uint8_T m[]);
#endif

/** Unpack the signals of inbound PDU StateEcu01 (1024, 0x400) from
    a byte array of 4 Byte. The signal values are written into the global interface struct
    PT_StateEcu01_1024_sts. */
void cap_unpack_PT_StateEcu01_1024(const uint8_T m[]);


#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/** Pack the signal values of inbound PDU StateEcu02 (1040, 0x410)
    into a byte array of 4 Byte. The signal values are read from the global interface
    struct cap_canBus_PT.PT_StateEcu02_1040_sts. */
void cap_pack_PT_StateEcu02_1040(uint8_T m[]);
#endif

/** Unpack the signals of inbound PDU StateEcu02 (1040, 0x410) from
    a byte array of 4 Byte. The signal values are written into the global interface struct
    PT_StateEcu02_1040_sts. */
void cap_unpack_PT_StateEcu02_1040(const uint8_T m[]);


#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/** Pack the signal values of inbound PDU UserLimits (2032, 0x7f0)
    into a byte array of 8 Byte. The signal values are read from the global interface
    struct cap_canBus_PT.PT_UserLimits_2032_sts. */
void cap_pack_PT_UserLimits_2032(uint8_T m[]);
#endif

/** Unpack the signals of inbound PDU UserLimits (2032, 0x7f0) from
    a byte array of 8 Byte. The signal values are written into the global interface struct
    PT_UserLimits_2032_sts. */
void cap_unpack_PT_UserLimits_2032(const uint8_T m[]);

/** Pack the signal values of outbound PDU InfoPowerDisplay (1536, 0x600)
    into a byte array of 6 Byte. The signal values are read from the global interface
    struct cap_canBus_PT.PT_InfoPowerDisplay_1536_sts. */
void cap_pack_PT_InfoPowerDisplay_1536(uint8_T m[]);

#if CAP_UNCONDITIONALLY_GENERATE_UNPACK_FCTS != 0
/** Unpack the signals of outbound PDU InfoPowerDisplay (1536, 0x600) from
    a byte array of 6 Byte. The signal values are written into the global interface struct
    PT_InfoPowerDisplay_1536_sts. */
void cap_unpack_PT_InfoPowerDisplay_1536(const uint8_T m[]);
#endif

/** Pack the signal values of outbound PDU StatusPowerDisplay (1537, 0x601)
    into a byte array of 6 Byte. The signal values are read from the global interface
    struct cap_canBus_PT.PT_StatusPowerDisplay_1537_sts. */
void cap_pack_PT_StatusPowerDisplay_1537(uint8_T m[]);

#if CAP_UNCONDITIONALLY_GENERATE_UNPACK_FCTS != 0
/** Unpack the signals of outbound PDU StatusPowerDisplay (1537, 0x601) from
    a byte array of 6 Byte. The signal values are written into the global interface struct
    PT_StatusPowerDisplay_1537_sts. */
void cap_unpack_PT_StatusPowerDisplay_1537(const uint8_T m[]);
#endif

/** Pack the signal values of outbound PDU LimitsPowerDisplay (1538, 0x602)
    into a byte array of 1 Byte. The signal values are read from the global interface
    struct cap_canBus_PT.PT_LimitsPowerDisplay_1538_sts. */
void cap_pack_PT_LimitsPowerDisplay_1538(uint8_T m[]);

#if CAP_UNCONDITIONALLY_GENERATE_UNPACK_FCTS != 0
/** Unpack the signals of outbound PDU LimitsPowerDisplay (1538, 0x602) from
    a byte array of 1 Byte. The signal values are written into the global interface struct
    PT_LimitsPowerDisplay_1538_sts. */
void cap_unpack_PT_LimitsPowerDisplay_1538(const uint8_T m[]);
#endif



/*
 * Inline function definitions
 */

#endif // !defined(CAP_CANAPI_DEFINED)