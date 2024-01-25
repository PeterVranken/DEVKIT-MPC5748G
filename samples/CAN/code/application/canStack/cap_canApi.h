#ifndef CAP_CANAPI_DEFINED
#define CAP_CANAPI_DEFINED
/**
 * @file cap_canApi.h
 * Declaration of API and pack/unpack functions for the CAN messages of cluster
 * DEVKIT-MPC5775G.
 *
 * This file has been created with comFramework - codeGenerator version 1.11.3,
 * see http://sourceforge.net/projects/comframe/
 *
 * Copyright (C) 2015-2024 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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

#include "typ_types.h"


/*
 * Defines
 */

#ifndef CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS
/** Normally, a pack function is generated for sent messages only. If this define is set to a
    value other than 0 then a pack function is generated for received messages, too. */
# define CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS 0
#endif

#ifndef CAP_UNCONDITIONALLY_GENERATE_UNPACK_FCTS
/** Normally, an unpack function is generated for received messages only. If this define is set
    to a value other than 0 then an unpack function is generated for sent messages, too. */
# define CAP_UNCONDITIONALLY_GENERATE_UNPACK_FCTS 0
#endif


/** This macro can be used to control the compilation of code, which depends on the
    presence of the particular message PWM_in (1000, 0x3e8)
    on bus PWM in the message catalog. */
#define CAP_MSG_PWM_PWM_IN_1000

/** Provide read/write access to the message API struct, which bundles the set of signals of
    message PWM_in (1000, 0x3e8) on bus PWM with the
    transmission status information. The referenced struct is a nested sub-element of the
    large the CAN bus describing struct cap_canBus_PWM. */
#define cap_getMsgSts_PWM_PWM_in_1000() \
            (cap_canBus_PWM.PWM_PWM_in_1000_sts)

/** Provide read/write access to the message API struct, which bundles the signals of message
    PWM_in (1000, 0x3e8) on bus PWM. The referenced struct is
    a nested sub-element of the large the CAN bus describing struct cap_canBus_PWM. */
#define cap_getMsg_PWM_PWM_in_1000() \
            (cap_canBus_PWM.PWM_PWM_in_1000_sts.signals)

/** Provide read/write access to a field of the struct, which bundles the signals of message
    PWM_in (1000, 0x3e8) on bus PWM. This struct is a nested
    sub-element of the large the CAN bus describing struct cap_canBus_PWM. */
#define cap_getSignal_PWM_PWM_in_1000(signalName) \
            (cap_canBus_PWM.PWM_PWM_in_1000_sts.signals.signalName)

/** The size in Byte of message PWM_in (1000, 0x3e8) on bus PWM. */
#define CAP_PWM_PWM_IN_1000_DLC	8

/** This macro can be used to control the compilation of code, which depends on the
    presence of the particular message PWM_out (1001, 0x3e9)
    on bus PWM in the message catalog. */
#define CAP_MSG_PWM_PWM_OUT_1001

/** Provide read/write access to the message API struct, which bundles the set of signals of
    message PWM_out (1001, 0x3e9) on bus PWM with the
    transmission status information. The referenced struct is a nested sub-element of the
    large the CAN bus describing struct cap_canBus_PWM. */
#define cap_getMsgSts_PWM_PWM_out_1001() \
            (cap_canBus_PWM.PWM_PWM_out_1001_sts)

/** Provide read/write access to the message API struct, which bundles the signals of message
    PWM_out (1001, 0x3e9) on bus PWM. The referenced struct is
    a nested sub-element of the large the CAN bus describing struct cap_canBus_PWM. */
#define cap_getMsg_PWM_PWM_out_1001() \
            (cap_canBus_PWM.PWM_PWM_out_1001_sts.signals)

/** Provide read/write access to a field of the struct, which bundles the signals of message
    PWM_out (1001, 0x3e9) on bus PWM. This struct is a nested
    sub-element of the large the CAN bus describing struct cap_canBus_PWM. */
#define cap_getSignal_PWM_PWM_out_1001(signalName) \
            (cap_canBus_PWM.PWM_PWM_out_1001_sts.signals.signalName)

/** The size in Byte of message PWM_out (1001, 0x3e9) on bus PWM. */
#define CAP_PWM_PWM_OUT_1001_DLC	8

/** This macro can be used to control the compilation of code, which depends on the
    presence of the particular message StateEcu01 (1024, 0x400)
    on bus PT in the message catalog. */
#define CAP_MSG_PT_STATEECU01_1024

/** Provide read/write access to the message API struct, which bundles the set of signals of
    message StateEcu01 (1024, 0x400) on bus PT with the
    transmission status information. The referenced struct is a nested sub-element of the
    large the CAN bus describing struct cap_canBus_PT. */
#define cap_getMsgSts_PT_StateEcu01_1024() \
            (cap_canBus_PT.PT_StateEcu01_1024_sts)

/** Provide read/write access to the message API struct, which bundles the signals of message
    StateEcu01 (1024, 0x400) on bus PT. The referenced struct is
    a nested sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getMsg_PT_StateEcu01_1024() \
            (cap_canBus_PT.PT_StateEcu01_1024_sts.signals)

/** Provide read/write access to a field of the struct, which bundles the signals of message
    StateEcu01 (1024, 0x400) on bus PT. This struct is a nested
    sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getSignal_PT_StateEcu01_1024(signalName) \
            (cap_canBus_PT.PT_StateEcu01_1024_sts.signals.signalName)

/** The size in Byte of message StateEcu01 (1024, 0x400) on bus PT. */
#define CAP_PT_STATEECU01_1024_DLC	4

/** The size in Bit of checksum signal of message StateEcu01 (1024, 0x400)
    on bus PT. */
#define CAP_PT_STATEECU01_1024_CHECKSUM_LENGTH	8

/** The start bit of checksum signal of message StateEcu01 (1024, 0x400)
    on bus PT. */
#define CAP_PT_STATEECU01_1024_CHECKSUM_STARTBIT	7

/** The endianness of checksum signal of message StateEcu01 (1024, 0x400)
    on bus PT. */
#define CAP_PT_STATEECU01_1024_CHECKSUM_IS_BIG_ENDIAN	true

/** The data ID of checksum signal of message StateEcu01 (1024, 0x400)
    on bus PT. */
#define CAP_PT_STATEECU01_1024_CHECKSUM_START_VALUE	

/** The size in Bit of the sequence counter of message StateEcu01 (1024, 0x400)
    on bus PT. */
#define CAP_PT_STATEECU01_1024_SQC_LENGTH	4

/** The minmum value of the sequence counter of message StateEcu01 (1024, 0x400)
    on bus PT. */
#define CAP_PT_STATEECU01_1024_SQC_FROM	0

/** The maximum value of the sequence counter of message StateEcu01 (1024, 0x400)
    on bus PT. */
#define CAP_PT_STATEECU01_1024_SQC_TO	14

/** This macro can be used to control the compilation of code, which depends on the
    presence of the particular message StateEcu02 (1040, 0x410)
    on bus PT in the message catalog. */
#define CAP_MSG_PT_STATEECU02_1040

/** Provide read/write access to the message API struct, which bundles the set of signals of
    message StateEcu02 (1040, 0x410) on bus PT with the
    transmission status information. The referenced struct is a nested sub-element of the
    large the CAN bus describing struct cap_canBus_PT. */
#define cap_getMsgSts_PT_StateEcu02_1040() \
            (cap_canBus_PT.PT_StateEcu02_1040_sts)

/** Provide read/write access to the message API struct, which bundles the signals of message
    StateEcu02 (1040, 0x410) on bus PT. The referenced struct is
    a nested sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getMsg_PT_StateEcu02_1040() \
            (cap_canBus_PT.PT_StateEcu02_1040_sts.signals)

/** Provide read/write access to a field of the struct, which bundles the signals of message
    StateEcu02 (1040, 0x410) on bus PT. This struct is a nested
    sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getSignal_PT_StateEcu02_1040(signalName) \
            (cap_canBus_PT.PT_StateEcu02_1040_sts.signals.signalName)

/** The size in Byte of message StateEcu02 (1040, 0x410) on bus PT. */
#define CAP_PT_STATEECU02_1040_DLC	4

/** The size in Bit of checksum signal of message StateEcu02 (1040, 0x410)
    on bus PT. */
#define CAP_PT_STATEECU02_1040_CHECKSUM_LENGTH	8

/** The start bit of checksum signal of message StateEcu02 (1040, 0x410)
    on bus PT. */
#define CAP_PT_STATEECU02_1040_CHECKSUM_STARTBIT	0

/** The endianness of checksum signal of message StateEcu02 (1040, 0x410)
    on bus PT. */
#define CAP_PT_STATEECU02_1040_CHECKSUM_IS_BIG_ENDIAN	false

/** The data ID of checksum signal of message StateEcu02 (1040, 0x410)
    on bus PT. */
#define CAP_PT_STATEECU02_1040_CHECKSUM_START_VALUE	

/** The size in Bit of the sequence counter of message StateEcu02 (1040, 0x410)
    on bus PT. */
#define CAP_PT_STATEECU02_1040_SQC_LENGTH	4

/** The minmum value of the sequence counter of message StateEcu02 (1040, 0x410)
    on bus PT. */
#define CAP_PT_STATEECU02_1040_SQC_FROM	1

/** The maximum value of the sequence counter of message StateEcu02 (1040, 0x410)
    on bus PT. */
#define CAP_PT_STATEECU02_1040_SQC_TO	15

/** This macro can be used to control the compilation of code, which depends on the
    presence of the particular message UserLimits (2032, 0x7f0)
    on bus PT in the message catalog. */
#define CAP_MSG_PT_USERLIMITS_2032

/** Provide read/write access to the message API struct, which bundles the set of signals of
    message UserLimits (2032, 0x7f0) on bus PT with the
    transmission status information. The referenced struct is a nested sub-element of the
    large the CAN bus describing struct cap_canBus_PT. */
#define cap_getMsgSts_PT_UserLimits_2032() \
            (cap_canBus_PT.PT_UserLimits_2032_sts)

/** Provide read/write access to the message API struct, which bundles the signals of message
    UserLimits (2032, 0x7f0) on bus PT. The referenced struct is
    a nested sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getMsg_PT_UserLimits_2032() \
            (cap_canBus_PT.PT_UserLimits_2032_sts.signals)

/** Provide read/write access to a field of the struct, which bundles the signals of message
    UserLimits (2032, 0x7f0) on bus PT. This struct is a nested
    sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getSignal_PT_UserLimits_2032(signalName) \
            (cap_canBus_PT.PT_UserLimits_2032_sts.signals.signalName)

/** The size in Byte of message UserLimits (2032, 0x7f0) on bus PT. */
#define CAP_PT_USERLIMITS_2032_DLC	8

/** The size in Bit of checksum signal of message UserLimits (2032, 0x7f0)
    on bus PT. */
#define CAP_PT_USERLIMITS_2032_CHECKSUM_LENGTH	8

/** The start bit of checksum signal of message UserLimits (2032, 0x7f0)
    on bus PT. */
#define CAP_PT_USERLIMITS_2032_CHECKSUM_STARTBIT	39

/** The endianness of checksum signal of message UserLimits (2032, 0x7f0)
    on bus PT. */
#define CAP_PT_USERLIMITS_2032_CHECKSUM_IS_BIG_ENDIAN	true

/** The data ID of checksum signal of message UserLimits (2032, 0x7f0)
    on bus PT. */
#define CAP_PT_USERLIMITS_2032_CHECKSUM_START_VALUE	

/** The size in Bit of the sequence counter of message UserLimits (2032, 0x7f0)
    on bus PT. */
#define CAP_PT_USERLIMITS_2032_SQC_LENGTH	4

/** The minmum value of the sequence counter of message UserLimits (2032, 0x7f0)
    on bus PT. */
#define CAP_PT_USERLIMITS_2032_SQC_FROM	1

/** The maximum value of the sequence counter of message UserLimits (2032, 0x7f0)
    on bus PT. */
#define CAP_PT_USERLIMITS_2032_SQC_TO	14

/** This macro can be used to control the compilation of code, which depends on the
    presence of the particular message InfoPowerDisplay (1536, 0x600)
    on bus PT in the message catalog. */
#define CAP_MSG_PT_INFOPOWERDISPLAY_1536

/** Provide read/write access to the message API struct, which bundles the set of signals of
    message InfoPowerDisplay (1536, 0x600) on bus PT with the
    transmission status information. The referenced struct is a nested sub-element of the
    large the CAN bus describing struct cap_canBus_PT. */
#define cap_getMsgSts_PT_InfoPowerDisplay_1536() \
            (cap_canBus_PT.PT_InfoPowerDisplay_1536_sts)

/** Provide read/write access to the message API struct, which bundles the signals of message
    InfoPowerDisplay (1536, 0x600) on bus PT. The referenced struct is
    a nested sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getMsg_PT_InfoPowerDisplay_1536() \
            (cap_canBus_PT.PT_InfoPowerDisplay_1536_sts.signals)

/** Provide read/write access to a field of the struct, which bundles the signals of message
    InfoPowerDisplay (1536, 0x600) on bus PT. This struct is a nested
    sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getSignal_PT_InfoPowerDisplay_1536(signalName) \
            (cap_canBus_PT.PT_InfoPowerDisplay_1536_sts.signals.signalName)

/** The size in Byte of message InfoPowerDisplay (1536, 0x600) on bus PT. */
#define CAP_PT_INFOPOWERDISPLAY_1536_DLC	6

/** The size in Bit of checksum signal of message InfoPowerDisplay (1536, 0x600)
    on bus PT. */
#define CAP_PT_INFOPOWERDISPLAY_1536_CHECKSUM_LENGTH	8

/** The start bit of checksum signal of message InfoPowerDisplay (1536, 0x600)
    on bus PT. */
#define CAP_PT_INFOPOWERDISPLAY_1536_CHECKSUM_STARTBIT	0

/** The endianness of checksum signal of message InfoPowerDisplay (1536, 0x600)
    on bus PT. */
#define CAP_PT_INFOPOWERDISPLAY_1536_CHECKSUM_IS_BIG_ENDIAN	false

/** The data ID of checksum signal of message InfoPowerDisplay (1536, 0x600)
    on bus PT. */
#define CAP_PT_INFOPOWERDISPLAY_1536_CHECKSUM_START_VALUE	

/** The size in Bit of the sequence counter of message InfoPowerDisplay (1536, 0x600)
    on bus PT. */
#define CAP_PT_INFOPOWERDISPLAY_1536_SQC_LENGTH	4

/** The minmum value of the sequence counter of message InfoPowerDisplay (1536, 0x600)
    on bus PT. */
#define CAP_PT_INFOPOWERDISPLAY_1536_SQC_FROM	0

/** The maximum value of the sequence counter of message InfoPowerDisplay (1536, 0x600)
    on bus PT. */
#define CAP_PT_INFOPOWERDISPLAY_1536_SQC_TO	14

/** This macro can be used to control the compilation of code, which depends on the
    presence of the particular message StatusPowerDisplay (1537, 0x601)
    on bus PT in the message catalog. */
#define CAP_MSG_PT_STATUSPOWERDISPLAY_1537

/** Provide read/write access to the message API struct, which bundles the set of signals of
    message StatusPowerDisplay (1537, 0x601) on bus PT with the
    transmission status information. The referenced struct is a nested sub-element of the
    large the CAN bus describing struct cap_canBus_PT. */
#define cap_getMsgSts_PT_StatusPowerDisplay_1537() \
            (cap_canBus_PT.PT_StatusPowerDisplay_1537_sts)

/** Provide read/write access to the message API struct, which bundles the signals of message
    StatusPowerDisplay (1537, 0x601) on bus PT. The referenced struct is
    a nested sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getMsg_PT_StatusPowerDisplay_1537() \
            (cap_canBus_PT.PT_StatusPowerDisplay_1537_sts.signals)

/** Provide read/write access to a field of the struct, which bundles the signals of message
    StatusPowerDisplay (1537, 0x601) on bus PT. This struct is a nested
    sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getSignal_PT_StatusPowerDisplay_1537(signalName) \
            (cap_canBus_PT.PT_StatusPowerDisplay_1537_sts.signals.signalName)

/** The size in Byte of message StatusPowerDisplay (1537, 0x601) on bus PT. */
#define CAP_PT_STATUSPOWERDISPLAY_1537_DLC	6

/** The size in Bit of checksum signal of message StatusPowerDisplay (1537, 0x601)
    on bus PT. */
#define CAP_PT_STATUSPOWERDISPLAY_1537_CHECKSUM_LENGTH	8

/** The start bit of checksum signal of message StatusPowerDisplay (1537, 0x601)
    on bus PT. */
#define CAP_PT_STATUSPOWERDISPLAY_1537_CHECKSUM_STARTBIT	47

/** The endianness of checksum signal of message StatusPowerDisplay (1537, 0x601)
    on bus PT. */
#define CAP_PT_STATUSPOWERDISPLAY_1537_CHECKSUM_IS_BIG_ENDIAN	true

/** The data ID of checksum signal of message StatusPowerDisplay (1537, 0x601)
    on bus PT. */
#define CAP_PT_STATUSPOWERDISPLAY_1537_CHECKSUM_START_VALUE	

/** The size in Bit of the sequence counter of message StatusPowerDisplay (1537, 0x601)
    on bus PT. */
#define CAP_PT_STATUSPOWERDISPLAY_1537_SQC_LENGTH	7

/** The minmum value of the sequence counter of message StatusPowerDisplay (1537, 0x601)
    on bus PT. */
#define CAP_PT_STATUSPOWERDISPLAY_1537_SQC_FROM	1

/** The maximum value of the sequence counter of message StatusPowerDisplay (1537, 0x601)
    on bus PT. */
#define CAP_PT_STATUSPOWERDISPLAY_1537_SQC_TO	126

/** This macro can be used to control the compilation of code, which depends on the
    presence of the particular message LimitsPowerDisplay (1538, 0x602)
    on bus PT in the message catalog. */
#define CAP_MSG_PT_LIMITSPOWERDISPLAY_1538

/** Provide read/write access to the message API struct, which bundles the set of signals of
    message LimitsPowerDisplay (1538, 0x602) on bus PT with the
    transmission status information. The referenced struct is a nested sub-element of the
    large the CAN bus describing struct cap_canBus_PT. */
#define cap_getMsgSts_PT_LimitsPowerDisplay_1538() \
            (cap_canBus_PT.PT_LimitsPowerDisplay_1538_sts)

/** Provide read/write access to the message API struct, which bundles the signals of message
    LimitsPowerDisplay (1538, 0x602) on bus PT. The referenced struct is
    a nested sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getMsg_PT_LimitsPowerDisplay_1538() \
            (cap_canBus_PT.PT_LimitsPowerDisplay_1538_sts.signals)

/** Provide read/write access to a field of the struct, which bundles the signals of message
    LimitsPowerDisplay (1538, 0x602) on bus PT. This struct is a nested
    sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getSignal_PT_LimitsPowerDisplay_1538(signalName) \
            (cap_canBus_PT.PT_LimitsPowerDisplay_1538_sts.signals.signalName)

/** The size in Byte of message LimitsPowerDisplay (1538, 0x602) on bus PT. */
#define CAP_PT_LIMITSPOWERDISPLAY_1538_DLC	1

/** The size in Bit of the sequence counter of message LimitsPowerDisplay (1538, 0x602)
    on bus PT. */
#define CAP_PT_LIMITSPOWERDISPLAY_1538_SQC_LENGTH	3

/** The minmum value of the sequence counter of message LimitsPowerDisplay (1538, 0x602)
    on bus PT. */
#define CAP_PT_LIMITSPOWERDISPLAY_1538_SQC_FROM	1

/** The maximum value of the sequence counter of message LimitsPowerDisplay (1538, 0x602)
    on bus PT. */
#define CAP_PT_LIMITSPOWERDISPLAY_1538_SQC_TO	6


/** Convert the binary value of signal PA2_J3_pin3_periodTime of message
    PWM_in (1000, 0x3e8) on bus PWM into the world value. */
#define CAP_PWM_1000_PA2_J3_pin3_periodTime_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PWM_1000_PA2_J3_pin3_periodTime_FACTOR)

/** Convert the world value of signal PA2_J3_pin3_periodTime of message
    PWM_in (1000, 0x3e8) on bus PWM into the binary value as
    transmitted via the CAN interface. */
#define CAP_PWM_1000_PA2_J3_pin3_periodTime_DBL_TO_BIN(dbl) \
            ((uint16_t)((dbl)/CAP_PWM_1000_PA2_J3_pin3_periodTime_FACTOR))

/** The gain factor of the scaling of signal PA2_J3_pin3_periodTime of message
    PWM_in (1000, 0x3e8) on bus PWM. */
#define CAP_PWM_1000_PA2_J3_pin3_periodTime_FACTOR	(0.015625)

/** The offset of the scaling of signal PA2_J3_pin3_periodTime of message
    PWM_in (1000, 0x3e8) on bus PWM. */
#define CAP_PWM_1000_PA2_J3_pin3_periodTime_OFFSET	(0.0)

/** The minimum of the world value of signal PA2_J3_pin3_periodTime of message
    PWM_in (1000, 0x3e8) on bus PWM. */
#define CAP_PWM_1000_PA2_J3_pin3_periodTime_MIN	(0.0)

/** The maximum of the world value of signal PA2_J3_pin3_periodTime of message
    PWM_in (1000, 0x3e8) on bus PWM. */
#define CAP_PWM_1000_PA2_J3_pin3_periodTime_MAX	(511.98437551)

/** The minimum of the world value of signal PA2_J3_pin3_isNew of message
    PWM_in (1000, 0x3e8) on bus PWM. */
#define CAP_PWM_1000_PA2_J3_pin3_isNew_MIN	(0)

/** The maximum of the world value of signal PA2_J3_pin3_isNew of message
    PWM_in (1000, 0x3e8) on bus PWM. */
#define CAP_PWM_1000_PA2_J3_pin3_isNew_MAX	(0)

/** The minimum of the world value of signal PA6_J2_pin1_isNew of message
    PWM_in (1000, 0x3e8) on bus PWM. */
#define CAP_PWM_1000_PA6_J2_pin1_isNew_MIN	(0)

/** The maximum of the world value of signal PA6_J2_pin1_isNew of message
    PWM_in (1000, 0x3e8) on bus PWM. */
#define CAP_PWM_1000_PA6_J2_pin1_isNew_MAX	(0)


/** Convert the binary value of signal PA6_J2_pin1_dutyTime of message
    PWM_in (1000, 0x3e8) on bus PWM into the world value. */
#define CAP_PWM_1000_PA6_J2_pin1_dutyTime_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PWM_1000_PA6_J2_pin1_dutyTime_FACTOR)

/** Convert the world value of signal PA6_J2_pin1_dutyTime of message
    PWM_in (1000, 0x3e8) on bus PWM into the binary value as
    transmitted via the CAN interface. */
#define CAP_PWM_1000_PA6_J2_pin1_dutyTime_DBL_TO_BIN(dbl) \
            ((uint16_t)((dbl)/CAP_PWM_1000_PA6_J2_pin1_dutyTime_FACTOR))

/** The gain factor of the scaling of signal PA6_J2_pin1_dutyTime of message
    PWM_in (1000, 0x3e8) on bus PWM. */
#define CAP_PWM_1000_PA6_J2_pin1_dutyTime_FACTOR	(0.015625)

/** The offset of the scaling of signal PA6_J2_pin1_dutyTime of message
    PWM_in (1000, 0x3e8) on bus PWM. */
#define CAP_PWM_1000_PA6_J2_pin1_dutyTime_OFFSET	(0.0)

/** The minimum of the world value of signal PA6_J2_pin1_dutyTime of message
    PWM_in (1000, 0x3e8) on bus PWM. */
#define CAP_PWM_1000_PA6_J2_pin1_dutyTime_MIN	(0.0)

/** The maximum of the world value of signal PA6_J2_pin1_dutyTime of message
    PWM_in (1000, 0x3e8) on bus PWM. */
#define CAP_PWM_1000_PA6_J2_pin1_dutyTime_MAX	(511.984375)


/** Convert the binary value of signal PA2_PA6_dutyCycle of message
    PWM_in (1000, 0x3e8) on bus PWM into the world value. */
#define CAP_PWM_1000_PA2_PA6_dutyCycle_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PWM_1000_PA2_PA6_dutyCycle_FACTOR)

/** Convert the world value of signal PA2_PA6_dutyCycle of message
    PWM_in (1000, 0x3e8) on bus PWM into the binary value as
    transmitted via the CAN interface. */
#define CAP_PWM_1000_PA2_PA6_dutyCycle_DBL_TO_BIN(dbl) \
            ((uint16_t)((dbl)/CAP_PWM_1000_PA2_PA6_dutyCycle_FACTOR))

/** The gain factor of the scaling of signal PA2_PA6_dutyCycle of message
    PWM_in (1000, 0x3e8) on bus PWM. */
#define CAP_PWM_1000_PA2_PA6_dutyCycle_FACTOR	(0.00390625)

/** The offset of the scaling of signal PA2_PA6_dutyCycle of message
    PWM_in (1000, 0x3e8) on bus PWM. */
#define CAP_PWM_1000_PA2_PA6_dutyCycle_OFFSET	(0.0)

/** The minimum of the world value of signal PA2_PA6_dutyCycle of message
    PWM_in (1000, 0x3e8) on bus PWM. */
#define CAP_PWM_1000_PA2_PA6_dutyCycle_MIN	(0.0)

/** The maximum of the world value of signal PA2_PA6_dutyCycle of message
    PWM_in (1000, 0x3e8) on bus PWM. */
#define CAP_PWM_1000_PA2_PA6_dutyCycle_MAX	(100.0)


/** Convert the binary value of signal PA2_J3_pin3_frequency of message
    PWM_in (1000, 0x3e8) on bus PWM into the world value. */
#define CAP_PWM_1000_PA2_J3_pin3_frequency_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PWM_1000_PA2_J3_pin3_frequency_FACTOR)

/** Convert the world value of signal PA2_J3_pin3_frequency of message
    PWM_in (1000, 0x3e8) on bus PWM into the binary value as
    transmitted via the CAN interface. */
#define CAP_PWM_1000_PA2_J3_pin3_frequency_DBL_TO_BIN(dbl) \
            ((uint16_t)((dbl)/CAP_PWM_1000_PA2_J3_pin3_frequency_FACTOR))

/** The gain factor of the scaling of signal PA2_J3_pin3_frequency of message
    PWM_in (1000, 0x3e8) on bus PWM. */
#define CAP_PWM_1000_PA2_J3_pin3_frequency_FACTOR	(0.25)

/** The offset of the scaling of signal PA2_J3_pin3_frequency of message
    PWM_in (1000, 0x3e8) on bus PWM. */
#define CAP_PWM_1000_PA2_J3_pin3_frequency_OFFSET	(0.0)

/** The minimum of the world value of signal PA2_J3_pin3_frequency of message
    PWM_in (1000, 0x3e8) on bus PWM. */
#define CAP_PWM_1000_PA2_J3_pin3_frequency_MIN	(0.0)

/** The maximum of the world value of signal PA2_J3_pin3_frequency of message
    PWM_in (1000, 0x3e8) on bus PWM. */
#define CAP_PWM_1000_PA2_J3_pin3_frequency_MAX	(8191.75)

/** The minimum of the world value of signal LED_2_DS10_inhibit of message
    PWM_out (1001, 0x3e9) on bus PWM. */
#define CAP_PWM_1001_LED_2_DS10_inhibit_MIN	(0)

/** The maximum of the world value of signal LED_2_DS10_inhibit of message
    PWM_out (1001, 0x3e9) on bus PWM. */
#define CAP_PWM_1001_LED_2_DS10_inhibit_MAX	(1)

/** The minimum of the world value of signal LED_4_DS11_inhibit of message
    PWM_out (1001, 0x3e9) on bus PWM. */
#define CAP_PWM_1001_LED_4_DS11_inhibit_MIN	(0)

/** The maximum of the world value of signal LED_4_DS11_inhibit of message
    PWM_out (1001, 0x3e9) on bus PWM. */
#define CAP_PWM_1001_LED_4_DS11_inhibit_MAX	(1)

/** The minimum of the world value of signal LED_5_DS5_inhibit of message
    PWM_out (1001, 0x3e9) on bus PWM. */
#define CAP_PWM_1001_LED_5_DS5_inhibit_MIN	(0)

/** The maximum of the world value of signal LED_5_DS5_inhibit of message
    PWM_out (1001, 0x3e9) on bus PWM. */
#define CAP_PWM_1001_LED_5_DS5_inhibit_MAX	(1)

/** The minimum of the world value of signal PA1_J3_pin1_inhibit of message
    PWM_out (1001, 0x3e9) on bus PWM. */
#define CAP_PWM_1001_PA1_J3_pin1_inhibit_MIN	(0)

/** The maximum of the world value of signal PA1_J3_pin1_inhibit of message
    PWM_out (1001, 0x3e9) on bus PWM. */
#define CAP_PWM_1001_PA1_J3_pin1_inhibit_MAX	(1)


/** Convert the binary value of signal LED_2_DS10_frequency of message
    PWM_out (1001, 0x3e9) on bus PWM into the world value. */
#define CAP_PWM_1001_LED_2_DS10_frequency_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PWM_1001_LED_2_DS10_frequency_FACTOR)

/** Convert the world value of signal LED_2_DS10_frequency of message
    PWM_out (1001, 0x3e9) on bus PWM into the binary value as
    transmitted via the CAN interface. */
#define CAP_PWM_1001_LED_2_DS10_frequency_DBL_TO_BIN(dbl) \
            ((uint16_t)((dbl)/CAP_PWM_1001_LED_2_DS10_frequency_FACTOR))

/** The gain factor of the scaling of signal LED_2_DS10_frequency of message
    PWM_out (1001, 0x3e9) on bus PWM. */
#define CAP_PWM_1001_LED_2_DS10_frequency_FACTOR	(0.97752)

/** The offset of the scaling of signal LED_2_DS10_frequency of message
    PWM_out (1001, 0x3e9) on bus PWM. */
#define CAP_PWM_1001_LED_2_DS10_frequency_OFFSET	(0.0)

/** The minimum of the world value of signal LED_2_DS10_frequency of message
    PWM_out (1001, 0x3e9) on bus PWM. */
#define CAP_PWM_1001_LED_2_DS10_frequency_MIN	(2.0)

/** The maximum of the world value of signal LED_2_DS10_frequency of message
    PWM_out (1001, 0x3e9) on bus PWM. */
#define CAP_PWM_1001_LED_2_DS10_frequency_MAX	(1000.0)


/** Convert the binary value of signal LED_4_DS11_frequency of message
    PWM_out (1001, 0x3e9) on bus PWM into the world value. */
#define CAP_PWM_1001_LED_4_DS11_frequency_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PWM_1001_LED_4_DS11_frequency_FACTOR)

/** Convert the world value of signal LED_4_DS11_frequency of message
    PWM_out (1001, 0x3e9) on bus PWM into the binary value as
    transmitted via the CAN interface. */
#define CAP_PWM_1001_LED_4_DS11_frequency_DBL_TO_BIN(dbl) \
            ((uint16_t)((dbl)/CAP_PWM_1001_LED_4_DS11_frequency_FACTOR))

/** The gain factor of the scaling of signal LED_4_DS11_frequency of message
    PWM_out (1001, 0x3e9) on bus PWM. */
#define CAP_PWM_1001_LED_4_DS11_frequency_FACTOR	(0.97752)

/** The offset of the scaling of signal LED_4_DS11_frequency of message
    PWM_out (1001, 0x3e9) on bus PWM. */
#define CAP_PWM_1001_LED_4_DS11_frequency_OFFSET	(0.0)

/** The minimum of the world value of signal LED_4_DS11_frequency of message
    PWM_out (1001, 0x3e9) on bus PWM. */
#define CAP_PWM_1001_LED_4_DS11_frequency_MIN	(2.0)

/** The maximum of the world value of signal LED_4_DS11_frequency of message
    PWM_out (1001, 0x3e9) on bus PWM. */
#define CAP_PWM_1001_LED_4_DS11_frequency_MAX	(1000.0)


/** Convert the binary value of signal LED_5_DS5_frequency of message
    PWM_out (1001, 0x3e9) on bus PWM into the world value. */
#define CAP_PWM_1001_LED_5_DS5_frequency_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PWM_1001_LED_5_DS5_frequency_FACTOR)

/** Convert the world value of signal LED_5_DS5_frequency of message
    PWM_out (1001, 0x3e9) on bus PWM into the binary value as
    transmitted via the CAN interface. */
#define CAP_PWM_1001_LED_5_DS5_frequency_DBL_TO_BIN(dbl) \
            ((uint16_t)((dbl)/CAP_PWM_1001_LED_5_DS5_frequency_FACTOR))

/** The gain factor of the scaling of signal LED_5_DS5_frequency of message
    PWM_out (1001, 0x3e9) on bus PWM. */
#define CAP_PWM_1001_LED_5_DS5_frequency_FACTOR	(0.97752)

/** The offset of the scaling of signal LED_5_DS5_frequency of message
    PWM_out (1001, 0x3e9) on bus PWM. */
#define CAP_PWM_1001_LED_5_DS5_frequency_OFFSET	(0.0)

/** The minimum of the world value of signal LED_5_DS5_frequency of message
    PWM_out (1001, 0x3e9) on bus PWM. */
#define CAP_PWM_1001_LED_5_DS5_frequency_MIN	(2.0)

/** The maximum of the world value of signal LED_5_DS5_frequency of message
    PWM_out (1001, 0x3e9) on bus PWM. */
#define CAP_PWM_1001_LED_5_DS5_frequency_MAX	(1000.0)


/** Convert the binary value of signal PA1_J3_pin1_frequency of message
    PWM_out (1001, 0x3e9) on bus PWM into the world value. */
#define CAP_PWM_1001_PA1_J3_pin1_frequency_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PWM_1001_PA1_J3_pin1_frequency_FACTOR)

/** Convert the world value of signal PA1_J3_pin1_frequency of message
    PWM_out (1001, 0x3e9) on bus PWM into the binary value as
    transmitted via the CAN interface. */
#define CAP_PWM_1001_PA1_J3_pin1_frequency_DBL_TO_BIN(dbl) \
            ((uint16_t)((dbl)/CAP_PWM_1001_PA1_J3_pin1_frequency_FACTOR))

/** The gain factor of the scaling of signal PA1_J3_pin1_frequency of message
    PWM_out (1001, 0x3e9) on bus PWM. */
#define CAP_PWM_1001_PA1_J3_pin1_frequency_FACTOR	(9.7752)

/** The offset of the scaling of signal PA1_J3_pin1_frequency of message
    PWM_out (1001, 0x3e9) on bus PWM. */
#define CAP_PWM_1001_PA1_J3_pin1_frequency_OFFSET	(0.0)

/** The minimum of the world value of signal PA1_J3_pin1_frequency of message
    PWM_out (1001, 0x3e9) on bus PWM. */
#define CAP_PWM_1001_PA1_J3_pin1_frequency_MIN	(2.0)

/** The maximum of the world value of signal PA1_J3_pin1_frequency of message
    PWM_out (1001, 0x3e9) on bus PWM. */
#define CAP_PWM_1001_PA1_J3_pin1_frequency_MAX	(10000.0)


/** Convert the binary value of signal LED_2_DS10_dutyCycle of message
    PWM_out (1001, 0x3e9) on bus PWM into the world value. */
#define CAP_PWM_1001_LED_2_DS10_dutyCycle_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PWM_1001_LED_2_DS10_dutyCycle_FACTOR)

/** Convert the world value of signal LED_2_DS10_dutyCycle of message
    PWM_out (1001, 0x3e9) on bus PWM into the binary value as
    transmitted via the CAN interface. */
#define CAP_PWM_1001_LED_2_DS10_dutyCycle_DBL_TO_BIN(dbl) \
            ((uint8_t)((dbl)/CAP_PWM_1001_LED_2_DS10_dutyCycle_FACTOR))

/** The gain factor of the scaling of signal LED_2_DS10_dutyCycle of message
    PWM_out (1001, 0x3e9) on bus PWM. */
#define CAP_PWM_1001_LED_2_DS10_dutyCycle_FACTOR	(3.2259)

/** The offset of the scaling of signal LED_2_DS10_dutyCycle of message
    PWM_out (1001, 0x3e9) on bus PWM. */
#define CAP_PWM_1001_LED_2_DS10_dutyCycle_OFFSET	(0.0)

/** The minimum of the world value of signal LED_2_DS10_dutyCycle of message
    PWM_out (1001, 0x3e9) on bus PWM. */
#define CAP_PWM_1001_LED_2_DS10_dutyCycle_MIN	(0.0)

/** The maximum of the world value of signal LED_2_DS10_dutyCycle of message
    PWM_out (1001, 0x3e9) on bus PWM. */
#define CAP_PWM_1001_LED_2_DS10_dutyCycle_MAX	(0.0)


/** Convert the binary value of signal LED_4_DS11_dutyCycle of message
    PWM_out (1001, 0x3e9) on bus PWM into the world value. */
#define CAP_PWM_1001_LED_4_DS11_dutyCycle_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PWM_1001_LED_4_DS11_dutyCycle_FACTOR)

/** Convert the world value of signal LED_4_DS11_dutyCycle of message
    PWM_out (1001, 0x3e9) on bus PWM into the binary value as
    transmitted via the CAN interface. */
#define CAP_PWM_1001_LED_4_DS11_dutyCycle_DBL_TO_BIN(dbl) \
            ((uint8_t)((dbl)/CAP_PWM_1001_LED_4_DS11_dutyCycle_FACTOR))

/** The gain factor of the scaling of signal LED_4_DS11_dutyCycle of message
    PWM_out (1001, 0x3e9) on bus PWM. */
#define CAP_PWM_1001_LED_4_DS11_dutyCycle_FACTOR	(3.2259)

/** The offset of the scaling of signal LED_4_DS11_dutyCycle of message
    PWM_out (1001, 0x3e9) on bus PWM. */
#define CAP_PWM_1001_LED_4_DS11_dutyCycle_OFFSET	(0.0)

/** The minimum of the world value of signal LED_4_DS11_dutyCycle of message
    PWM_out (1001, 0x3e9) on bus PWM. */
#define CAP_PWM_1001_LED_4_DS11_dutyCycle_MIN	(0.0)

/** The maximum of the world value of signal LED_4_DS11_dutyCycle of message
    PWM_out (1001, 0x3e9) on bus PWM. */
#define CAP_PWM_1001_LED_4_DS11_dutyCycle_MAX	(0.0)


/** Convert the binary value of signal LED_5_DS5_dutyCycle of message
    PWM_out (1001, 0x3e9) on bus PWM into the world value. */
#define CAP_PWM_1001_LED_5_DS5_dutyCycle_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PWM_1001_LED_5_DS5_dutyCycle_FACTOR)

/** Convert the world value of signal LED_5_DS5_dutyCycle of message
    PWM_out (1001, 0x3e9) on bus PWM into the binary value as
    transmitted via the CAN interface. */
#define CAP_PWM_1001_LED_5_DS5_dutyCycle_DBL_TO_BIN(dbl) \
            ((uint8_t)((dbl)/CAP_PWM_1001_LED_5_DS5_dutyCycle_FACTOR))

/** The gain factor of the scaling of signal LED_5_DS5_dutyCycle of message
    PWM_out (1001, 0x3e9) on bus PWM. */
#define CAP_PWM_1001_LED_5_DS5_dutyCycle_FACTOR	(3.2259)

/** The offset of the scaling of signal LED_5_DS5_dutyCycle of message
    PWM_out (1001, 0x3e9) on bus PWM. */
#define CAP_PWM_1001_LED_5_DS5_dutyCycle_OFFSET	(0.0)

/** The minimum of the world value of signal LED_5_DS5_dutyCycle of message
    PWM_out (1001, 0x3e9) on bus PWM. */
#define CAP_PWM_1001_LED_5_DS5_dutyCycle_MIN	(0.0)

/** The maximum of the world value of signal LED_5_DS5_dutyCycle of message
    PWM_out (1001, 0x3e9) on bus PWM. */
#define CAP_PWM_1001_LED_5_DS5_dutyCycle_MAX	(0.0)


/** Convert the binary value of signal PA1_J3_pin1_dutyCycle of message
    PWM_out (1001, 0x3e9) on bus PWM into the world value. */
#define CAP_PWM_1001_PA1_J3_pin1_dutyCycle_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PWM_1001_PA1_J3_pin1_dutyCycle_FACTOR)

/** Convert the world value of signal PA1_J3_pin1_dutyCycle of message
    PWM_out (1001, 0x3e9) on bus PWM into the binary value as
    transmitted via the CAN interface. */
#define CAP_PWM_1001_PA1_J3_pin1_dutyCycle_DBL_TO_BIN(dbl) \
            ((uint8_t)((dbl)/CAP_PWM_1001_PA1_J3_pin1_dutyCycle_FACTOR))

/** The gain factor of the scaling of signal PA1_J3_pin1_dutyCycle of message
    PWM_out (1001, 0x3e9) on bus PWM. */
#define CAP_PWM_1001_PA1_J3_pin1_dutyCycle_FACTOR	(3.2259)

/** The offset of the scaling of signal PA1_J3_pin1_dutyCycle of message
    PWM_out (1001, 0x3e9) on bus PWM. */
#define CAP_PWM_1001_PA1_J3_pin1_dutyCycle_OFFSET	(0.0)

/** The minimum of the world value of signal PA1_J3_pin1_dutyCycle of message
    PWM_out (1001, 0x3e9) on bus PWM. */
#define CAP_PWM_1001_PA1_J3_pin1_dutyCycle_MIN	(0.0)

/** The maximum of the world value of signal PA1_J3_pin1_dutyCycle of message
    PWM_out (1001, 0x3e9) on bus PWM. */
#define CAP_PWM_1001_PA1_J3_pin1_dutyCycle_MAX	(0.0)

/** The minimum of the world value of signal checksum of message
    StateEcu01 (1024, 0x400) on bus PT. */
#define CAP_PT_1024_checksum_MIN	(0)

/** The maximum of the world value of signal checksum of message
    StateEcu01 (1024, 0x400) on bus PT. */
#define CAP_PT_1024_checksum_MAX	(255)


/** Convert the binary value of signal speedOfRotation of message
    StateEcu01 (1024, 0x400) on bus PT into the world value. */
#define CAP_PT_1024_speedOfRotation_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PT_1024_speedOfRotation_FACTOR)

/** Convert the world value of signal speedOfRotation of message
    StateEcu01 (1024, 0x400) on bus PT into the binary value as
    transmitted via the CAN interface. */
#define CAP_PT_1024_speedOfRotation_DBL_TO_BIN(dbl) \
            ((uint16_t)((dbl)/CAP_PT_1024_speedOfRotation_FACTOR))

/** The gain factor of the scaling of signal speedOfRotation of message
    StateEcu01 (1024, 0x400) on bus PT. */
#define CAP_PT_1024_speedOfRotation_FACTOR	(0.1)

/** The offset of the scaling of signal speedOfRotation of message
    StateEcu01 (1024, 0x400) on bus PT. */
#define CAP_PT_1024_speedOfRotation_OFFSET	(0.0)

/** The minimum of the world value of signal speedOfRotation of message
    StateEcu01 (1024, 0x400) on bus PT. */
#define CAP_PT_1024_speedOfRotation_MIN	(0.0)

/** The maximum of the world value of signal speedOfRotation of message
    StateEcu01 (1024, 0x400) on bus PT. */
#define CAP_PT_1024_speedOfRotation_MAX	(6500.0)

/** The minimum of the world value of signal sequenceCounter of message
    StateEcu01 (1024, 0x400) on bus PT. */
#define CAP_PT_1024_sequenceCounter_MIN	(0)

/** The maximum of the world value of signal sequenceCounter of message
    StateEcu01 (1024, 0x400) on bus PT. */
#define CAP_PT_1024_sequenceCounter_MAX	(14)

/** The minimum of the world value of signal checksum of message
    StateEcu02 (1040, 0x410) on bus PT. */
#define CAP_PT_1040_checksum_MIN	(0)

/** The maximum of the world value of signal checksum of message
    StateEcu02 (1040, 0x410) on bus PT. */
#define CAP_PT_1040_checksum_MAX	(255)

/** The minimum of the world value of signal sequenceCounter of message
    StateEcu02 (1040, 0x410) on bus PT. */
#define CAP_PT_1040_sequenceCounter_MIN	(1)

/** The maximum of the world value of signal sequenceCounter of message
    StateEcu02 (1040, 0x410) on bus PT. */
#define CAP_PT_1040_sequenceCounter_MAX	(15)


/** Convert the binary value of signal torque of message
    StateEcu02 (1040, 0x410) on bus PT into the world value. */
#define CAP_PT_1040_torque_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PT_1040_torque_FACTOR)

/** Convert the world value of signal torque of message
    StateEcu02 (1040, 0x410) on bus PT into the binary value as
    transmitted via the CAN interface. */
#define CAP_PT_1040_torque_DBL_TO_BIN(dbl) \
            ((int16_t)((dbl)/CAP_PT_1040_torque_FACTOR))

/** The gain factor of the scaling of signal torque of message
    StateEcu02 (1040, 0x410) on bus PT. */
#define CAP_PT_1040_torque_FACTOR	(0.5)

/** The offset of the scaling of signal torque of message
    StateEcu02 (1040, 0x410) on bus PT. */
#define CAP_PT_1040_torque_OFFSET	(0.0)

/** The minimum of the world value of signal torque of message
    StateEcu02 (1040, 0x410) on bus PT. */
#define CAP_PT_1040_torque_MIN	(-500.0)

/** The maximum of the world value of signal torque of message
    StateEcu02 (1040, 0x410) on bus PT. */
#define CAP_PT_1040_torque_MAX	(500.0)

/** The minimum of the world value of signal sequenceCounter of message
    UserLimits (2032, 0x7f0) on bus PT. */
#define CAP_PT_2032_sequenceCounter_MIN	(1)

/** The maximum of the world value of signal sequenceCounter of message
    UserLimits (2032, 0x7f0) on bus PT. */
#define CAP_PT_2032_sequenceCounter_MAX	(14)


/** Convert the binary value of signal minSpeedOfRotation of message
    UserLimits (2032, 0x7f0) on bus PT into the world value. */
#define CAP_PT_2032_minSpeedOfRotation_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PT_2032_minSpeedOfRotation_FACTOR)

/** Convert the world value of signal minSpeedOfRotation of message
    UserLimits (2032, 0x7f0) on bus PT into the binary value as
    transmitted via the CAN interface. */
#define CAP_PT_2032_minSpeedOfRotation_DBL_TO_BIN(dbl) \
            ((uint16_t)((dbl)/CAP_PT_2032_minSpeedOfRotation_FACTOR))

/** The gain factor of the scaling of signal minSpeedOfRotation of message
    UserLimits (2032, 0x7f0) on bus PT. */
#define CAP_PT_2032_minSpeedOfRotation_FACTOR	(1.6)

/** The offset of the scaling of signal minSpeedOfRotation of message
    UserLimits (2032, 0x7f0) on bus PT. */
#define CAP_PT_2032_minSpeedOfRotation_OFFSET	(0.0)

/** The minimum of the world value of signal minSpeedOfRotation of message
    UserLimits (2032, 0x7f0) on bus PT. */
#define CAP_PT_2032_minSpeedOfRotation_MIN	(0.0)

/** The maximum of the world value of signal minSpeedOfRotation of message
    UserLimits (2032, 0x7f0) on bus PT. */
#define CAP_PT_2032_minSpeedOfRotation_MAX	(6500.0)


/** Convert the binary value of signal maxSpeedOfRotation of message
    UserLimits (2032, 0x7f0) on bus PT into the world value. */
#define CAP_PT_2032_maxSpeedOfRotation_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PT_2032_maxSpeedOfRotation_FACTOR)

/** Convert the world value of signal maxSpeedOfRotation of message
    UserLimits (2032, 0x7f0) on bus PT into the binary value as
    transmitted via the CAN interface. */
#define CAP_PT_2032_maxSpeedOfRotation_DBL_TO_BIN(dbl) \
            ((uint16_t)((dbl)/CAP_PT_2032_maxSpeedOfRotation_FACTOR))

/** The gain factor of the scaling of signal maxSpeedOfRotation of message
    UserLimits (2032, 0x7f0) on bus PT. */
#define CAP_PT_2032_maxSpeedOfRotation_FACTOR	(1.6)

/** The offset of the scaling of signal maxSpeedOfRotation of message
    UserLimits (2032, 0x7f0) on bus PT. */
#define CAP_PT_2032_maxSpeedOfRotation_OFFSET	(0.0)

/** The minimum of the world value of signal maxSpeedOfRotation of message
    UserLimits (2032, 0x7f0) on bus PT. */
#define CAP_PT_2032_maxSpeedOfRotation_MIN	(0.0)

/** The maximum of the world value of signal maxSpeedOfRotation of message
    UserLimits (2032, 0x7f0) on bus PT. */
#define CAP_PT_2032_maxSpeedOfRotation_MAX	(6500.0)

/** The minimum of the world value of signal checksum of message
    UserLimits (2032, 0x7f0) on bus PT. */
#define CAP_PT_2032_checksum_MIN	(0)

/** The maximum of the world value of signal checksum of message
    UserLimits (2032, 0x7f0) on bus PT. */
#define CAP_PT_2032_checksum_MAX	(255)


/** Convert the binary value of signal minPower of message
    UserLimits (2032, 0x7f0) on bus PT into the world value. */
#define CAP_PT_2032_minPower_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PT_2032_minPower_FACTOR+CAP_PT_2032_minPower_OFFSET)

/** Convert the world value of signal minPower of message
    UserLimits (2032, 0x7f0) on bus PT into the binary value as
    transmitted via the CAN interface. */
#define CAP_PT_2032_minPower_DBL_TO_BIN(dbl) \
            ((uint16_t)(((dbl)-CAP_PT_2032_minPower_OFFSET)/CAP_PT_2032_minPower_FACTOR))

/** The gain factor of the scaling of signal minPower of message
    UserLimits (2032, 0x7f0) on bus PT. */
#define CAP_PT_2032_minPower_FACTOR	(0.5)

/** The offset of the scaling of signal minPower of message
    UserLimits (2032, 0x7f0) on bus PT. */
#define CAP_PT_2032_minPower_OFFSET	(-10.0)

/** The minimum of the world value of signal minPower of message
    UserLimits (2032, 0x7f0) on bus PT. */
#define CAP_PT_2032_minPower_MIN	(-10.0)

/** The maximum of the world value of signal minPower of message
    UserLimits (2032, 0x7f0) on bus PT. */
#define CAP_PT_2032_minPower_MAX	(240.0)


/** Convert the binary value of signal maxPower of message
    UserLimits (2032, 0x7f0) on bus PT into the world value. */
#define CAP_PT_2032_maxPower_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PT_2032_maxPower_FACTOR+CAP_PT_2032_maxPower_OFFSET)

/** Convert the world value of signal maxPower of message
    UserLimits (2032, 0x7f0) on bus PT into the binary value as
    transmitted via the CAN interface. */
#define CAP_PT_2032_maxPower_DBL_TO_BIN(dbl) \
            ((uint16_t)(((dbl)-CAP_PT_2032_maxPower_OFFSET)/CAP_PT_2032_maxPower_FACTOR))

/** The gain factor of the scaling of signal maxPower of message
    UserLimits (2032, 0x7f0) on bus PT. */
#define CAP_PT_2032_maxPower_FACTOR	(0.5)

/** The offset of the scaling of signal maxPower of message
    UserLimits (2032, 0x7f0) on bus PT. */
#define CAP_PT_2032_maxPower_OFFSET	(-10.0)

/** The minimum of the world value of signal maxPower of message
    UserLimits (2032, 0x7f0) on bus PT. */
#define CAP_PT_2032_maxPower_MIN	(-10.0)

/** The maximum of the world value of signal maxPower of message
    UserLimits (2032, 0x7f0) on bus PT. */
#define CAP_PT_2032_maxPower_MAX	(240.0)

/** The minimum of the world value of signal checksum of message
    InfoPowerDisplay (1536, 0x600) on bus PT. */
#define CAP_PT_1536_checksum_MIN	(0)

/** The maximum of the world value of signal checksum of message
    InfoPowerDisplay (1536, 0x600) on bus PT. */
#define CAP_PT_1536_checksum_MAX	(255)

/** The minimum of the world value of signal sequenceCounter of message
    InfoPowerDisplay (1536, 0x600) on bus PT. */
#define CAP_PT_1536_sequenceCounter_MIN	(0)

/** The maximum of the world value of signal sequenceCounter of message
    InfoPowerDisplay (1536, 0x600) on bus PT. */
#define CAP_PT_1536_sequenceCounter_MAX	(14)


/** Convert the binary value of signal power of message
    InfoPowerDisplay (1536, 0x600) on bus PT into the world value. */
#define CAP_PT_1536_power_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PT_1536_power_FACTOR+CAP_PT_1536_power_OFFSET)

/** Convert the world value of signal power of message
    InfoPowerDisplay (1536, 0x600) on bus PT into the binary value as
    transmitted via the CAN interface. */
#define CAP_PT_1536_power_DBL_TO_BIN(dbl) \
            ((uint16_t)(((dbl)-CAP_PT_1536_power_OFFSET)/CAP_PT_1536_power_FACTOR))

/** The gain factor of the scaling of signal power of message
    InfoPowerDisplay (1536, 0x600) on bus PT. */
#define CAP_PT_1536_power_FACTOR	(32.0)

/** The offset of the scaling of signal power of message
    InfoPowerDisplay (1536, 0x600) on bus PT. */
#define CAP_PT_1536_power_OFFSET	(-500000.0)

/** The minimum of the world value of signal power of message
    InfoPowerDisplay (1536, 0x600) on bus PT. */
#define CAP_PT_1536_power_MIN	(-500000.0)

/** The maximum of the world value of signal power of message
    InfoPowerDisplay (1536, 0x600) on bus PT. */
#define CAP_PT_1536_power_MAX	(500000.0)

/** The minimum of the world value of signal state of message
    InfoPowerDisplay (1536, 0x600) on bus PT. */
#define CAP_PT_1536_state_MIN	(0)

/** The maximum of the world value of signal state of message
    InfoPowerDisplay (1536, 0x600) on bus PT. */
#define CAP_PT_1536_state_MAX	(2)

/** The minimum of the world value of signal noDlcErrors of message
    StatusPowerDisplay (1537, 0x601) on bus PT. */
#define CAP_PT_1537_noDlcErrors_MIN	(0)

/** The maximum of the world value of signal noDlcErrors of message
    StatusPowerDisplay (1537, 0x601) on bus PT. */
#define CAP_PT_1537_noDlcErrors_MAX	(2047)

/** The minimum of the world value of signal noCheckSumErrors of message
    StatusPowerDisplay (1537, 0x601) on bus PT. */
#define CAP_PT_1537_noCheckSumErrors_MIN	(0)

/** The maximum of the world value of signal noCheckSumErrors of message
    StatusPowerDisplay (1537, 0x601) on bus PT. */
#define CAP_PT_1537_noCheckSumErrors_MAX	(2047)

/** The minimum of the world value of signal noSqcErrors of message
    StatusPowerDisplay (1537, 0x601) on bus PT. */
#define CAP_PT_1537_noSqcErrors_MIN	(0)

/** The maximum of the world value of signal noSqcErrors of message
    StatusPowerDisplay (1537, 0x601) on bus PT. */
#define CAP_PT_1537_noSqcErrors_MAX	(2047)

/** The minimum of the world value of signal sequenceCounter of message
    StatusPowerDisplay (1537, 0x601) on bus PT. */
#define CAP_PT_1537_sequenceCounter_MIN	(1)

/** The maximum of the world value of signal sequenceCounter of message
    StatusPowerDisplay (1537, 0x601) on bus PT. */
#define CAP_PT_1537_sequenceCounter_MAX	(126)

/** The minimum of the world value of signal checksum of message
    StatusPowerDisplay (1537, 0x601) on bus PT. */
#define CAP_PT_1537_checksum_MIN	(0)

/** The maximum of the world value of signal checksum of message
    StatusPowerDisplay (1537, 0x601) on bus PT. */
#define CAP_PT_1537_checksum_MAX	(255)

/** The minimum of the world value of signal sequenceCounter of message
    LimitsPowerDisplay (1538, 0x602) on bus PT. */
#define CAP_PT_1538_sequenceCounter_MIN	(1)

/** The maximum of the world value of signal sequenceCounter of message
    LimitsPowerDisplay (1538, 0x602) on bus PT. */
#define CAP_PT_1538_sequenceCounter_MAX	(6)

/** The minimum of the world value of signal belowMinSpeedOfRotation of message
    LimitsPowerDisplay (1538, 0x602) on bus PT. */
#define CAP_PT_1538_belowMinSpeedOfRotation_MIN	(0)

/** The maximum of the world value of signal belowMinSpeedOfRotation of message
    LimitsPowerDisplay (1538, 0x602) on bus PT. */
#define CAP_PT_1538_belowMinSpeedOfRotation_MAX	(1)

/** The minimum of the world value of signal aboveMaxSpeedOfRotation of message
    LimitsPowerDisplay (1538, 0x602) on bus PT. */
#define CAP_PT_1538_aboveMaxSpeedOfRotation_MIN	(0)

/** The maximum of the world value of signal aboveMaxSpeedOfRotation of message
    LimitsPowerDisplay (1538, 0x602) on bus PT. */
#define CAP_PT_1538_aboveMaxSpeedOfRotation_MAX	(1)

/** The minimum of the world value of signal belowMinPower of message
    LimitsPowerDisplay (1538, 0x602) on bus PT. */
#define CAP_PT_1538_belowMinPower_MIN	(0)

/** The maximum of the world value of signal belowMinPower of message
    LimitsPowerDisplay (1538, 0x602) on bus PT. */
#define CAP_PT_1538_belowMinPower_MAX	(1)

/** The minimum of the world value of signal aboveMaxPower of message
    LimitsPowerDisplay (1538, 0x602) on bus PT. */
#define CAP_PT_1538_aboveMaxPower_MIN	(0)

/** The maximum of the world value of signal aboveMaxPower of message
    LimitsPowerDisplay (1538, 0x602) on bus PT. */
#define CAP_PT_1538_aboveMaxPower_MAX	(1)




/*
 * Type definitions
 */

/** The enumeration of supported message send patterns. */
typedef enum cap_enumSendMode_t
{
    cap_enumSendMode_0_cyclic = 0,
    cap_enumSendMode_1_event = 1,
    cap_enumSendMode_2_cyclicOrEvent = 2,
    cap_enumSendMode_3_unsupported = 3,
    cap_enumSendMode_4_unsupported = 4,
    cap_enumSendMode_5_unsupported = 5,
    cap_enumSendMode_6_unsupported = 6,
    cap_enumSendMode_7_unsupported = 7,
    cap_enumSendMode_8_unsupported = 8,

} cap_enumSendMode_t;

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
typedef uint8_t cap_stsTransmission_t;

/** This struct bundles the transmission related information for a single frame. */
typedef struct cap_infoTransmission_t
{
    /** The transmission status. */
    cap_stsTransmission_t stsTransmission;

    /** The number of receive or sent events of the frame. The APSW, who is regularly
        checking the global CAN API, can look at changes of this variable to find out if
        there were newly received frames or whether the outbound frame became due
        meanwhile. Since the CAN API is race-condition free it may even reset the value to
        zero after each check - and and will then always have a simple and straight forward
        indication of the frames received and sent meanwhile.
          @remark The counter cycles around if it is not regularly reset by the APSW, no
        boundaries are implemented. */
    unsigned int noTransmittedMsgs;

    /** For outbound frames and by setting this flag to \a true, the APSW can signal that
        the frame contents have been updated and that the frame requires sending. The APSW
        should never reset the flag, the frame sending logic will do as soon as it submits
        the frame at the operating system for sending.\n
          For regular, outbound frames it is useless to set the flag. These frames are
        anyway due at each check cycle.\n
          For outbound frames with timing pattern "mixed", it is not required or useful to
        regularly set this flag when there's no real data change event; the sending logic
        implements the regular sending if no APSW send command happens.\n
          For inbound frames this flag is a bit redundant with \a
        noTransmittedMsgs; it is set on reception by the interface engine but not
        reset. If the APSW resets it after check it behaves like a Boolean statement
        whether new information arrived. */
    bool isEvent;

} cap_infoTransmission_t;



/** The signals of outbound CAN frame PWM_in (1000, 0x3e8) on
    bus PWM. */
typedef struct cap_PWM_PWM_in_1000_t
{
    /** Signal PA2_J3_pin3_periodTime. */
    uint16_t PA2_J3_pin3_periodTime;

    /** Signal PA2_J3_pin3_isNew. */
    bool PA2_J3_pin3_isNew;

    /** Signal PA6_J2_pin1_isNew. */
    bool PA6_J2_pin1_isNew;

    /** Signal PA6_J2_pin1_dutyTime. */
    uint16_t PA6_J2_pin1_dutyTime;

    /** Signal PA2_PA6_dutyCycle. */
    uint16_t PA2_PA6_dutyCycle;

    /** Signal PA2_J3_pin3_frequency. */
    uint16_t PA2_J3_pin3_frequency;

} cap_PWM_PWM_in_1000_t;


/** The signals of inbound CAN frame PWM_out (1001, 0x3e9) on
    bus PWM. */
typedef struct cap_PWM_PWM_out_1001_t
{
    /** Signal LED_2_DS10_inhibit. */
    bool LED_2_DS10_inhibit;

    /** Signal LED_4_DS11_inhibit. */
    bool LED_4_DS11_inhibit;

    /** Signal LED_5_DS5_inhibit. */
    bool LED_5_DS5_inhibit;

    /** Signal PA1_J3_pin1_inhibit. */
    bool PA1_J3_pin1_inhibit;

    /** Signal LED_2_DS10_frequency. */
    uint16_t LED_2_DS10_frequency;

    /** Signal LED_4_DS11_frequency. */
    uint16_t LED_4_DS11_frequency;

    /** Signal LED_5_DS5_frequency. */
    uint16_t LED_5_DS5_frequency;

    /** Signal PA1_J3_pin1_frequency. */
    uint16_t PA1_J3_pin1_frequency;

    /** Signal LED_2_DS10_dutyCycle. */
    uint8_t LED_2_DS10_dutyCycle;

    /** Signal LED_4_DS11_dutyCycle. */
    uint8_t LED_4_DS11_dutyCycle;

    /** Signal LED_5_DS5_dutyCycle. */
    uint8_t LED_5_DS5_dutyCycle;

    /** Signal PA1_J3_pin1_dutyCycle. */
    uint8_t PA1_J3_pin1_dutyCycle;

} cap_PWM_PWM_out_1001_t;


/** The signals of inbound CAN frame StateEcu01 (1024, 0x400) on
    bus PT. */
typedef struct cap_PT_StateEcu01_1024_t
{
    /** Signal checksum. */
    uint8_t checksum;

    /** Signal speedOfRotation. */
    uint16_t speedOfRotation;

    /** Signal sequenceCounter. */
    uint8_t sequenceCounter;

} cap_PT_StateEcu01_1024_t;


/** The signals of inbound CAN frame StateEcu02 (1040, 0x410) on
    bus PT. */
typedef struct cap_PT_StateEcu02_1040_t
{
    /** Signal checksum. */
    uint8_t checksum; /* Signal is not used by node PowerDisplay. */

    /** Signal sequenceCounter. */
    uint8_t sequenceCounter;

    /** Signal torque. */
    int16_t torque;

} cap_PT_StateEcu02_1040_t;


/** The signals of inbound CAN frame UserLimits (2032, 0x7f0) on
    bus PT. */
typedef struct cap_PT_UserLimits_2032_t
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

} cap_PT_UserLimits_2032_t;


/** The signals of outbound CAN frame InfoPowerDisplay (1536, 0x600) on
    bus PT. */
typedef struct cap_PT_InfoPowerDisplay_1536_t
{
    /** Signal checksum. */
    uint8_t checksum;

    /** Signal sequenceCounter. */
    uint8_t sequenceCounter;

    /** Signal power. */
    uint16_t power;

    /** Signal state. */
    uint8_t state;

} cap_PT_InfoPowerDisplay_1536_t;


/** The signals of outbound CAN frame StatusPowerDisplay (1537, 0x601) on
    bus PT. */
typedef struct cap_PT_StatusPowerDisplay_1537_t
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

} cap_PT_StatusPowerDisplay_1537_t;


/** The signals of outbound CAN frame LimitsPowerDisplay (1538, 0x602) on
    bus PT. */
typedef struct cap_PT_LimitsPowerDisplay_1538_t
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

} cap_PT_LimitsPowerDisplay_1538_t;


/** Signals and transmission status of outbound CAN frame PWM_in
    (1000, 0x3e8) on bus PWM. */
typedef struct cap_PWM_PWM_in_1000_sts_t
{
    /** The collection of signals of the frame. */
    cap_PWM_PWM_in_1000_t signals;

    /** Some transmission related information for this frame. */
    cap_infoTransmission_t infoTransmission;

} cap_PWM_PWM_in_1000_sts_t;


/** Signals and transmission status of inbound CAN frame PWM_out
    (1001, 0x3e9) on bus PWM. */
typedef struct cap_PWM_PWM_out_1001_sts_t
{
    /** The collection of signals of the frame. */
    cap_PWM_PWM_out_1001_t signals;

    /** Some transmission related information for this frame. */
    cap_infoTransmission_t infoTransmission;

} cap_PWM_PWM_out_1001_sts_t;


/** Signals and transmission status of inbound CAN frame StateEcu01
    (1024, 0x400) on bus PT. */
typedef struct cap_PT_StateEcu01_1024_sts_t
{
    /** The collection of signals of the frame. */
    cap_PT_StateEcu01_1024_t signals;

    /** Some transmission related information for this frame. */
    cap_infoTransmission_t infoTransmission;

} cap_PT_StateEcu01_1024_sts_t;


/** Signals and transmission status of inbound CAN frame StateEcu02
    (1040, 0x410) on bus PT. */
typedef struct cap_PT_StateEcu02_1040_sts_t
{
    /** The collection of signals of the frame. */
    cap_PT_StateEcu02_1040_t signals;

    /** Some transmission related information for this frame. */
    cap_infoTransmission_t infoTransmission;

} cap_PT_StateEcu02_1040_sts_t;


/** Signals and transmission status of inbound CAN frame UserLimits
    (2032, 0x7f0) on bus PT. */
typedef struct cap_PT_UserLimits_2032_sts_t
{
    /** The collection of signals of the frame. */
    cap_PT_UserLimits_2032_t signals;

    /** Some transmission related information for this frame. */
    cap_infoTransmission_t infoTransmission;

} cap_PT_UserLimits_2032_sts_t;


/** Signals and transmission status of outbound CAN frame InfoPowerDisplay
    (1536, 0x600) on bus PT. */
typedef struct cap_PT_InfoPowerDisplay_1536_sts_t
{
    /** The collection of signals of the frame. */
    cap_PT_InfoPowerDisplay_1536_t signals;

    /** Some transmission related information for this frame. */
    cap_infoTransmission_t infoTransmission;

} cap_PT_InfoPowerDisplay_1536_sts_t;


/** Signals and transmission status of outbound CAN frame StatusPowerDisplay
    (1537, 0x601) on bus PT. */
typedef struct cap_PT_StatusPowerDisplay_1537_sts_t
{
    /** The collection of signals of the frame. */
    cap_PT_StatusPowerDisplay_1537_t signals;

    /** Some transmission related information for this frame. */
    cap_infoTransmission_t infoTransmission;

} cap_PT_StatusPowerDisplay_1537_sts_t;


/** Signals and transmission status of outbound CAN frame LimitsPowerDisplay
    (1538, 0x602) on bus PT. */
typedef struct cap_PT_LimitsPowerDisplay_1538_sts_t
{
    /** The collection of signals of the frame. */
    cap_PT_LimitsPowerDisplay_1538_t signals;

    /** Some transmission related information for this frame. */
    cap_infoTransmission_t infoTransmission;

} cap_PT_LimitsPowerDisplay_1538_sts_t;



/** The frames and signals of CAN bus PWM. A global variable of this type is used
    as API between the lower layers of the CAN stack and the APSW. */
typedef struct cap_canBus_PWM_t
{
    /** Signals and transmission status of outbound CAN frame PWM_in
        (1000, 0x3e8) */
    cap_PWM_PWM_in_1000_sts_t PWM_PWM_in_1000_sts;

    /** Signals and transmission status of inbound CAN frame PWM_out
        (1001, 0x3e9) */
    cap_PWM_PWM_out_1001_sts_t PWM_PWM_out_1001_sts;


} cap_canBus_PWM_t;


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

/** Signals and transmission status of CAN frames on bus PWM. This global variable
    is used as API between the lower layers of the CAN stack and the APSW. */
extern cap_canBus_PWM_t cap_canBus_PWM;

/** Signals and transmission status of CAN frames on bus PT. This global variable
    is used as API between the lower layers of the CAN stack and the APSW. */
extern cap_canBus_PT_t cap_canBus_PT;



/*
 * Function declarations
 */

/** Pack the signal values of outbound PDU PWM_in (1000, 0x3e8)
    into a byte array of 8 Byte. The signal values are read from the global interface
    struct cap_canBus_PWM.PWM_PWM_in_1000_sts. */
void cap_packApi_PWM_PWM_in(uint8_t m[]);

/** Pack the signal values of outbound PDU PWM_in (1000, 0x3e8)
    into a byte array of 8 Byte. The signal values are read from a message by reference. */
void cap_pack_PWM_PWM_in
                ( uint8_t m[]
                , const cap_PWM_PWM_in_1000_t *pMsgStruct
                );

#if CAP_UNCONDITIONALLY_GENERATE_UNPACK_FCTS != 0
/** Unpack the signals of outbound PDU PWM_in (1000, 0x3e8) from
    a byte array of 8 Byte. The signal values are written into the global interface struct
    PWM_PWM_in_1000_sts. */
void cap_unpackApi_PWM_PWM_in(const uint8_t m[]);

/** Unpack the signals of outbound PDU PWM_in (1000, 0x3e8) from
    a byte array of 8 Byte. The signal values are written into a message struct by
    reference. */
void cap_unpack_PWM_PWM_in
                ( cap_PWM_PWM_in_1000_t *pMsgStruct
                , const uint8_t m[]
                );
#endif


#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/** Pack the signal values of inbound PDU PWM_out (1001, 0x3e9)
    into a byte array of 8 Byte. The signal values are read from the global interface
    struct cap_canBus_PWM.PWM_PWM_out_1001_sts. */
void cap_packApi_PWM_PWM_out(uint8_t m[]);

/** Pack the signal values of inbound PDU PWM_out (1001, 0x3e9)
    into a byte array of 8 Byte. The signal values are read from a message by reference. */
void cap_pack_PWM_PWM_out
                ( uint8_t m[]
                , const cap_PWM_PWM_out_1001_t *pMsgStruct
                );
#endif

/** Unpack the signals of inbound PDU PWM_out (1001, 0x3e9) from
    a byte array of 8 Byte. The signal values are written into the global interface struct
    PWM_PWM_out_1001_sts. */
void cap_unpackApi_PWM_PWM_out(const uint8_t m[]);

/** Unpack the signals of inbound PDU PWM_out (1001, 0x3e9) from
    a byte array of 8 Byte. The signal values are written into a message struct by
    reference. */
void cap_unpack_PWM_PWM_out
                ( cap_PWM_PWM_out_1001_t *pMsgStruct
                , const uint8_t m[]
                );


#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/** Pack the signal values of inbound PDU StateEcu01 (1024, 0x400)
    into a byte array of 4 Byte. The signal values are read from the global interface
    struct cap_canBus_PT.PT_StateEcu01_1024_sts. */
void cap_packApi_PT_StateEcu01(uint8_t m[]);

/** Pack the signal values of inbound PDU StateEcu01 (1024, 0x400)
    into a byte array of 4 Byte. The signal values are read from a message by reference. */
void cap_pack_PT_StateEcu01
                ( uint8_t m[]
                , const cap_PT_StateEcu01_1024_t *pMsgStruct
                );
#endif

/** Unpack the signals of inbound PDU StateEcu01 (1024, 0x400) from
    a byte array of 4 Byte. The signal values are written into the global interface struct
    PT_StateEcu01_1024_sts. */
void cap_unpackApi_PT_StateEcu01(const uint8_t m[]);

/** Unpack the signals of inbound PDU StateEcu01 (1024, 0x400) from
    a byte array of 4 Byte. The signal values are written into a message struct by
    reference. */
void cap_unpack_PT_StateEcu01
                ( cap_PT_StateEcu01_1024_t *pMsgStruct
                , const uint8_t m[]
                );


#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/** Pack the signal values of inbound PDU StateEcu02 (1040, 0x410)
    into a byte array of 4 Byte. The signal values are read from the global interface
    struct cap_canBus_PT.PT_StateEcu02_1040_sts. */
void cap_packApi_PT_StateEcu02(uint8_t m[]);

/** Pack the signal values of inbound PDU StateEcu02 (1040, 0x410)
    into a byte array of 4 Byte. The signal values are read from a message by reference. */
void cap_pack_PT_StateEcu02
                ( uint8_t m[]
                , const cap_PT_StateEcu02_1040_t *pMsgStruct
                );
#endif

/** Unpack the signals of inbound PDU StateEcu02 (1040, 0x410) from
    a byte array of 4 Byte. The signal values are written into the global interface struct
    PT_StateEcu02_1040_sts. */
void cap_unpackApi_PT_StateEcu02(const uint8_t m[]);

/** Unpack the signals of inbound PDU StateEcu02 (1040, 0x410) from
    a byte array of 4 Byte. The signal values are written into a message struct by
    reference. */
void cap_unpack_PT_StateEcu02
                ( cap_PT_StateEcu02_1040_t *pMsgStruct
                , const uint8_t m[]
                );


#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/** Pack the signal values of inbound PDU UserLimits (2032, 0x7f0)
    into a byte array of 8 Byte. The signal values are read from the global interface
    struct cap_canBus_PT.PT_UserLimits_2032_sts. */
void cap_packApi_PT_UserLimits(uint8_t m[]);

/** Pack the signal values of inbound PDU UserLimits (2032, 0x7f0)
    into a byte array of 8 Byte. The signal values are read from a message by reference. */
void cap_pack_PT_UserLimits
                ( uint8_t m[]
                , const cap_PT_UserLimits_2032_t *pMsgStruct
                );
#endif

/** Unpack the signals of inbound PDU UserLimits (2032, 0x7f0) from
    a byte array of 8 Byte. The signal values are written into the global interface struct
    PT_UserLimits_2032_sts. */
void cap_unpackApi_PT_UserLimits(const uint8_t m[]);

/** Unpack the signals of inbound PDU UserLimits (2032, 0x7f0) from
    a byte array of 8 Byte. The signal values are written into a message struct by
    reference. */
void cap_unpack_PT_UserLimits
                ( cap_PT_UserLimits_2032_t *pMsgStruct
                , const uint8_t m[]
                );

/** Pack the signal values of outbound PDU InfoPowerDisplay (1536, 0x600)
    into a byte array of 6 Byte. The signal values are read from the global interface
    struct cap_canBus_PT.PT_InfoPowerDisplay_1536_sts. */
void cap_packApi_PT_InfoPowerDisplay(uint8_t m[]);

/** Pack the signal values of outbound PDU InfoPowerDisplay (1536, 0x600)
    into a byte array of 6 Byte. The signal values are read from a message by reference. */
void cap_pack_PT_InfoPowerDisplay
                ( uint8_t m[]
                , const cap_PT_InfoPowerDisplay_1536_t *pMsgStruct
                );

#if CAP_UNCONDITIONALLY_GENERATE_UNPACK_FCTS != 0
/** Unpack the signals of outbound PDU InfoPowerDisplay (1536, 0x600) from
    a byte array of 6 Byte. The signal values are written into the global interface struct
    PT_InfoPowerDisplay_1536_sts. */
void cap_unpackApi_PT_InfoPowerDisplay(const uint8_t m[]);

/** Unpack the signals of outbound PDU InfoPowerDisplay (1536, 0x600) from
    a byte array of 6 Byte. The signal values are written into a message struct by
    reference. */
void cap_unpack_PT_InfoPowerDisplay
                ( cap_PT_InfoPowerDisplay_1536_t *pMsgStruct
                , const uint8_t m[]
                );
#endif

/** Pack the signal values of outbound PDU StatusPowerDisplay (1537, 0x601)
    into a byte array of 6 Byte. The signal values are read from the global interface
    struct cap_canBus_PT.PT_StatusPowerDisplay_1537_sts. */
void cap_packApi_PT_StatusPowerDisplay(uint8_t m[]);

/** Pack the signal values of outbound PDU StatusPowerDisplay (1537, 0x601)
    into a byte array of 6 Byte. The signal values are read from a message by reference. */
void cap_pack_PT_StatusPowerDisplay
                ( uint8_t m[]
                , const cap_PT_StatusPowerDisplay_1537_t *pMsgStruct
                );

#if CAP_UNCONDITIONALLY_GENERATE_UNPACK_FCTS != 0
/** Unpack the signals of outbound PDU StatusPowerDisplay (1537, 0x601) from
    a byte array of 6 Byte. The signal values are written into the global interface struct
    PT_StatusPowerDisplay_1537_sts. */
void cap_unpackApi_PT_StatusPowerDisplay(const uint8_t m[]);

/** Unpack the signals of outbound PDU StatusPowerDisplay (1537, 0x601) from
    a byte array of 6 Byte. The signal values are written into a message struct by
    reference. */
void cap_unpack_PT_StatusPowerDisplay
                ( cap_PT_StatusPowerDisplay_1537_t *pMsgStruct
                , const uint8_t m[]
                );
#endif

/** Pack the signal values of outbound PDU LimitsPowerDisplay (1538, 0x602)
    into a byte array of 1 Byte. The signal values are read from the global interface
    struct cap_canBus_PT.PT_LimitsPowerDisplay_1538_sts. */
void cap_packApi_PT_LimitsPowerDisplay(uint8_t m[]);

/** Pack the signal values of outbound PDU LimitsPowerDisplay (1538, 0x602)
    into a byte array of 1 Byte. The signal values are read from a message by reference. */
void cap_pack_PT_LimitsPowerDisplay
                ( uint8_t m[]
                , const cap_PT_LimitsPowerDisplay_1538_t *pMsgStruct
                );

#if CAP_UNCONDITIONALLY_GENERATE_UNPACK_FCTS != 0
/** Unpack the signals of outbound PDU LimitsPowerDisplay (1538, 0x602) from
    a byte array of 1 Byte. The signal values are written into the global interface struct
    PT_LimitsPowerDisplay_1538_sts. */
void cap_unpackApi_PT_LimitsPowerDisplay(const uint8_t m[]);

/** Unpack the signals of outbound PDU LimitsPowerDisplay (1538, 0x602) from
    a byte array of 1 Byte. The signal values are written into a message struct by
    reference. */
void cap_unpack_PT_LimitsPowerDisplay
                ( cap_PT_LimitsPowerDisplay_1538_t *pMsgStruct
                , const uint8_t m[]
                );
#endif


/** Get the current value of message PWM_in (1000), signal PA2_J3_pin3_periodTime
    as float. */
float get_PWM_1000_PA2_J3_pin3_periodTime(void);

/** Set the value of message PWM_in (1000), signal PA2_J3_pin3_periodTime. */
void set_PWM_1000_PA2_J3_pin3_periodTime(float newValue);

/** Get the current value of message PWM_in (1000), signal PA2_J3_pin3_isNew
    as float. */
float get_PWM_1000_PA2_J3_pin3_isNew(void);

/** Set the value of message PWM_in (1000), signal PA2_J3_pin3_isNew. */
void set_PWM_1000_PA2_J3_pin3_isNew(float newValue);

/** Get the current value of message PWM_in (1000), signal PA6_J2_pin1_isNew
    as float. */
float get_PWM_1000_PA6_J2_pin1_isNew(void);

/** Set the value of message PWM_in (1000), signal PA6_J2_pin1_isNew. */
void set_PWM_1000_PA6_J2_pin1_isNew(float newValue);

/** Get the current value of message PWM_in (1000), signal PA6_J2_pin1_dutyTime
    as float. */
float get_PWM_1000_PA6_J2_pin1_dutyTime(void);

/** Set the value of message PWM_in (1000), signal PA6_J2_pin1_dutyTime. */
void set_PWM_1000_PA6_J2_pin1_dutyTime(float newValue);

/** Get the current value of message PWM_in (1000), signal PA2_PA6_dutyCycle
    as float. */
float get_PWM_1000_PA2_PA6_dutyCycle(void);

/** Set the value of message PWM_in (1000), signal PA2_PA6_dutyCycle. */
void set_PWM_1000_PA2_PA6_dutyCycle(float newValue);

/** Get the current value of message PWM_in (1000), signal PA2_J3_pin3_frequency
    as float. */
float get_PWM_1000_PA2_J3_pin3_frequency(void);

/** Set the value of message PWM_in (1000), signal PA2_J3_pin3_frequency. */
void set_PWM_1000_PA2_J3_pin3_frequency(float newValue);

/** Get the current value of message PWM_out (1001), signal LED_2_DS10_inhibit
    as float. */
float get_PWM_1001_LED_2_DS10_inhibit(void);

/** Set the value of message PWM_out (1001), signal LED_2_DS10_inhibit. */
void set_PWM_1001_LED_2_DS10_inhibit(float newValue);

/** Get the current value of message PWM_out (1001), signal LED_4_DS11_inhibit
    as float. */
float get_PWM_1001_LED_4_DS11_inhibit(void);

/** Set the value of message PWM_out (1001), signal LED_4_DS11_inhibit. */
void set_PWM_1001_LED_4_DS11_inhibit(float newValue);

/** Get the current value of message PWM_out (1001), signal LED_5_DS5_inhibit
    as float. */
float get_PWM_1001_LED_5_DS5_inhibit(void);

/** Set the value of message PWM_out (1001), signal LED_5_DS5_inhibit. */
void set_PWM_1001_LED_5_DS5_inhibit(float newValue);

/** Get the current value of message PWM_out (1001), signal PA1_J3_pin1_inhibit
    as float. */
float get_PWM_1001_PA1_J3_pin1_inhibit(void);

/** Set the value of message PWM_out (1001), signal PA1_J3_pin1_inhibit. */
void set_PWM_1001_PA1_J3_pin1_inhibit(float newValue);

/** Get the current value of message PWM_out (1001), signal LED_2_DS10_frequency
    as float. */
float get_PWM_1001_LED_2_DS10_frequency(void);

/** Set the value of message PWM_out (1001), signal LED_2_DS10_frequency. */
void set_PWM_1001_LED_2_DS10_frequency(float newValue);

/** Get the current value of message PWM_out (1001), signal LED_4_DS11_frequency
    as float. */
float get_PWM_1001_LED_4_DS11_frequency(void);

/** Set the value of message PWM_out (1001), signal LED_4_DS11_frequency. */
void set_PWM_1001_LED_4_DS11_frequency(float newValue);

/** Get the current value of message PWM_out (1001), signal LED_5_DS5_frequency
    as float. */
float get_PWM_1001_LED_5_DS5_frequency(void);

/** Set the value of message PWM_out (1001), signal LED_5_DS5_frequency. */
void set_PWM_1001_LED_5_DS5_frequency(float newValue);

/** Get the current value of message PWM_out (1001), signal PA1_J3_pin1_frequency
    as float. */
float get_PWM_1001_PA1_J3_pin1_frequency(void);

/** Set the value of message PWM_out (1001), signal PA1_J3_pin1_frequency. */
void set_PWM_1001_PA1_J3_pin1_frequency(float newValue);

/** Get the current value of message PWM_out (1001), signal LED_2_DS10_dutyCycle
    as float. */
float get_PWM_1001_LED_2_DS10_dutyCycle(void);

/** Set the value of message PWM_out (1001), signal LED_2_DS10_dutyCycle. */
void set_PWM_1001_LED_2_DS10_dutyCycle(float newValue);

/** Get the current value of message PWM_out (1001), signal LED_4_DS11_dutyCycle
    as float. */
float get_PWM_1001_LED_4_DS11_dutyCycle(void);

/** Set the value of message PWM_out (1001), signal LED_4_DS11_dutyCycle. */
void set_PWM_1001_LED_4_DS11_dutyCycle(float newValue);

/** Get the current value of message PWM_out (1001), signal LED_5_DS5_dutyCycle
    as float. */
float get_PWM_1001_LED_5_DS5_dutyCycle(void);

/** Set the value of message PWM_out (1001), signal LED_5_DS5_dutyCycle. */
void set_PWM_1001_LED_5_DS5_dutyCycle(float newValue);

/** Get the current value of message PWM_out (1001), signal PA1_J3_pin1_dutyCycle
    as float. */
float get_PWM_1001_PA1_J3_pin1_dutyCycle(void);

/** Set the value of message PWM_out (1001), signal PA1_J3_pin1_dutyCycle. */
void set_PWM_1001_PA1_J3_pin1_dutyCycle(float newValue);

/** Get the current value of message StateEcu01 (1024), signal checksum
    as float. */
float get_PT_1024_checksum(void);

/** Set the value of message StateEcu01 (1024), signal checksum. */
void set_PT_1024_checksum(float newValue);

/** Get the current value of message StateEcu01 (1024), signal speedOfRotation
    as float. */
float get_PT_1024_speedOfRotation(void);

/** Set the value of message StateEcu01 (1024), signal speedOfRotation. */
void set_PT_1024_speedOfRotation(float newValue);

/** Get the current value of message StateEcu01 (1024), signal sequenceCounter
    as float. */
float get_PT_1024_sequenceCounter(void);

/** Set the value of message StateEcu01 (1024), signal sequenceCounter. */
void set_PT_1024_sequenceCounter(float newValue);

/** Get the current value of message StateEcu02 (1040), signal sequenceCounter
    as float. */
float get_PT_1040_sequenceCounter(void);

/** Set the value of message StateEcu02 (1040), signal sequenceCounter. */
void set_PT_1040_sequenceCounter(float newValue);

/** Get the current value of message StateEcu02 (1040), signal torque
    as float. */
float get_PT_1040_torque(void);

/** Set the value of message StateEcu02 (1040), signal torque. */
void set_PT_1040_torque(float newValue);

/** Get the current value of message UserLimits (2032), signal sequenceCounter
    as float. */
float get_PT_2032_sequenceCounter(void);

/** Set the value of message UserLimits (2032), signal sequenceCounter. */
void set_PT_2032_sequenceCounter(float newValue);

/** Get the current value of message UserLimits (2032), signal minSpeedOfRotation
    as float. */
float get_PT_2032_minSpeedOfRotation(void);

/** Set the value of message UserLimits (2032), signal minSpeedOfRotation. */
void set_PT_2032_minSpeedOfRotation(float newValue);

/** Get the current value of message UserLimits (2032), signal maxSpeedOfRotation
    as float. */
float get_PT_2032_maxSpeedOfRotation(void);

/** Set the value of message UserLimits (2032), signal maxSpeedOfRotation. */
void set_PT_2032_maxSpeedOfRotation(float newValue);

/** Get the current value of message UserLimits (2032), signal checksum
    as float. */
float get_PT_2032_checksum(void);

/** Set the value of message UserLimits (2032), signal checksum. */
void set_PT_2032_checksum(float newValue);

/** Get the current value of message UserLimits (2032), signal minPower
    as float. */
float get_PT_2032_minPower(void);

/** Set the value of message UserLimits (2032), signal minPower. */
void set_PT_2032_minPower(float newValue);

/** Get the current value of message UserLimits (2032), signal maxPower
    as float. */
float get_PT_2032_maxPower(void);

/** Set the value of message UserLimits (2032), signal maxPower. */
void set_PT_2032_maxPower(float newValue);

/** Get the current value of message InfoPowerDisplay (1536), signal checksum
    as float. */
float get_PT_1536_checksum(void);

/** Set the value of message InfoPowerDisplay (1536), signal checksum. */
void set_PT_1536_checksum(float newValue);

/** Get the current value of message InfoPowerDisplay (1536), signal sequenceCounter
    as float. */
float get_PT_1536_sequenceCounter(void);

/** Set the value of message InfoPowerDisplay (1536), signal sequenceCounter. */
void set_PT_1536_sequenceCounter(float newValue);

/** Get the current value of message InfoPowerDisplay (1536), signal power
    as float. */
float get_PT_1536_power(void);

/** Set the value of message InfoPowerDisplay (1536), signal power. */
void set_PT_1536_power(float newValue);

/** Get the current value of message InfoPowerDisplay (1536), signal state
    as float. */
float get_PT_1536_state(void);

/** Set the value of message InfoPowerDisplay (1536), signal state. */
void set_PT_1536_state(float newValue);

/** Get the current value of message StatusPowerDisplay (1537), signal noDlcErrors
    as float. */
float get_PT_1537_noDlcErrors(void);

/** Set the value of message StatusPowerDisplay (1537), signal noDlcErrors. */
void set_PT_1537_noDlcErrors(float newValue);

/** Get the current value of message StatusPowerDisplay (1537), signal noCheckSumErrors
    as float. */
float get_PT_1537_noCheckSumErrors(void);

/** Set the value of message StatusPowerDisplay (1537), signal noCheckSumErrors. */
void set_PT_1537_noCheckSumErrors(float newValue);

/** Get the current value of message StatusPowerDisplay (1537), signal noSqcErrors
    as float. */
float get_PT_1537_noSqcErrors(void);

/** Set the value of message StatusPowerDisplay (1537), signal noSqcErrors. */
void set_PT_1537_noSqcErrors(float newValue);

/** Get the current value of message StatusPowerDisplay (1537), signal sequenceCounter
    as float. */
float get_PT_1537_sequenceCounter(void);

/** Set the value of message StatusPowerDisplay (1537), signal sequenceCounter. */
void set_PT_1537_sequenceCounter(float newValue);

/** Get the current value of message StatusPowerDisplay (1537), signal checksum
    as float. */
float get_PT_1537_checksum(void);

/** Set the value of message StatusPowerDisplay (1537), signal checksum. */
void set_PT_1537_checksum(float newValue);

/** Get the current value of message LimitsPowerDisplay (1538), signal sequenceCounter
    as float. */
float get_PT_1538_sequenceCounter(void);

/** Set the value of message LimitsPowerDisplay (1538), signal sequenceCounter. */
void set_PT_1538_sequenceCounter(float newValue);

/** Get the current value of message LimitsPowerDisplay (1538), signal belowMinSpeedOfRotation
    as float. */
float get_PT_1538_belowMinSpeedOfRotation(void);

/** Set the value of message LimitsPowerDisplay (1538), signal belowMinSpeedOfRotation. */
void set_PT_1538_belowMinSpeedOfRotation(float newValue);

/** Get the current value of message LimitsPowerDisplay (1538), signal aboveMaxSpeedOfRotation
    as float. */
float get_PT_1538_aboveMaxSpeedOfRotation(void);

/** Set the value of message LimitsPowerDisplay (1538), signal aboveMaxSpeedOfRotation. */
void set_PT_1538_aboveMaxSpeedOfRotation(float newValue);

/** Get the current value of message LimitsPowerDisplay (1538), signal belowMinPower
    as float. */
float get_PT_1538_belowMinPower(void);

/** Set the value of message LimitsPowerDisplay (1538), signal belowMinPower. */
void set_PT_1538_belowMinPower(float newValue);

/** Get the current value of message LimitsPowerDisplay (1538), signal aboveMaxPower
    as float. */
float get_PT_1538_aboveMaxPower(void);

/** Set the value of message LimitsPowerDisplay (1538), signal aboveMaxPower. */
void set_PT_1538_aboveMaxPower(float newValue);




/*
 * Inline function definitions
 */

#endif // !defined(CAP_CANAPI_DEFINED)