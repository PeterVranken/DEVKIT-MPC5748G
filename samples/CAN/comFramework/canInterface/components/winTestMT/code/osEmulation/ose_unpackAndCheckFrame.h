#ifndef OSE_UNPACKANDCHECKFRAME_DEFINED
#define OSE_UNPACKANDCHECKFRAME_DEFINED
/**
 * @file ose_unpackAndCheckFrame.h
 * 
 * This module contains the set of functions for the end-to-end validation of the CAN
 * frames. A CRC checking function is generated for each CAN frame.
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

#include "types.h"
#include "cap_canApi.h"


/*
 * Defines
 */

 

/*
 * Type definitions
 */

 

/*
 * Data declarations
 */

 

/*
 * Function declarations
 */

/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B1_frame_2044(const uint8_t frameContent[4]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B1_frame_1049(const uint8_t frameContent[7]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B1_frame_1834(const uint8_t frameContent[6]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B1_frame_1053(const uint8_t frameContent[7]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B1_frame_693(const uint8_t frameContent[8]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B1_frame_1143(const uint8_t frameContent[5]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B1_frame_453(const uint8_t frameContent[6]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B1_frame_403(const uint8_t frameContent[8]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B1_frame_766(const uint8_t frameContent[7]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B1_frame_1271(const uint8_t frameContent[6]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B1_frame_332(const uint8_t frameContent[5]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B1_frame_602(const uint8_t frameContent[7]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B1_frame_1605(const uint8_t frameContent[7]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B1_frame_1731(const uint8_t frameContent[8]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B1_frame_1529(const uint8_t frameContent[7]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B1_frame_808(const uint8_t frameContent[6]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B1_frame_1181(const uint8_t frameContent[6]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B1_frame_1725(const uint8_t frameContent[6]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B1_frame_208(const uint8_t frameContent[6]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B1_frame_2018(const uint8_t frameContent[8]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B1_frame_590(const uint8_t frameContent[7]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B1_frame_1419(const uint8_t frameContent[6]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B1_frame_1937(const uint8_t frameContent[7]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B1_frame_1630(const uint8_t frameContent[7]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B1_frame_1033(const uint8_t frameContent[5]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B1_frame_803(const uint8_t frameContent[4]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B1_frame_106(const uint8_t frameContent[5]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B1_frame_905(const uint8_t frameContent[8]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B1_frame_1998(const uint8_t frameContent[7]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B1_frame_1885(const uint8_t frameContent[4]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B1_frame_1415(const uint8_t frameContent[5]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B1_frame_915(const uint8_t frameContent[6]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B1_frame_349(const uint8_t frameContent[6]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B2_frame_25(const uint8_t frameContent[5]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B2_frame_1641(const uint8_t frameContent[5]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B2_frame_669(const uint8_t frameContent[6]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B2_frame_1401(const uint8_t frameContent[6]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B2_frame_1340(const uint8_t frameContent[6]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B2_frame_1151(const uint8_t frameContent[7]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B2_frame_1730(const uint8_t frameContent[8]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B2_frame_46(const uint8_t frameContent[6]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B2_frame_1939(const uint8_t frameContent[8]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B2_frame_659(const uint8_t frameContent[6]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B2_frame_981(const uint8_t frameContent[6]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B2_frame_708(const uint8_t frameContent[8]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B2_frame_1618(const uint8_t frameContent[4]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B2_frame_1956(const uint8_t frameContent[5]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B2_frame_463(const uint8_t frameContent[4]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B2_frame_954(const uint8_t frameContent[8]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B2_frame_1126(const uint8_t frameContent[7]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B2_frame_729(const uint8_t frameContent[6]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B2_frame_2045(const uint8_t frameContent[5]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B2_frame_1901(const uint8_t frameContent[7]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B2_frame_381(const uint8_t frameContent[8]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B2_frame_796(const uint8_t frameContent[6]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B2_frame_1652(const uint8_t frameContent[7]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B2_frame_1442(const uint8_t frameContent[2]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B3_frame_661(const uint8_t frameContent[4]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B3_frame_1084(const uint8_t frameContent[4]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B3_frame_1170(const uint8_t frameContent[8]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B3_frame_1696(const uint8_t frameContent[7]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B3_frame_1398(const uint8_t frameContent[8]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B3_frame_1425(const uint8_t frameContent[5]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B3_frame_1154(const uint8_t frameContent[5]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B3_frame_1404(const uint8_t frameContent[8]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B3_frame_1374(const uint8_t frameContent[7]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B3_frame_820(const uint8_t frameContent[4]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B3_frame_1713(const uint8_t frameContent[7]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B3_frame_1485(const uint8_t frameContent[7]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B3_frame_1385(const uint8_t frameContent[6]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B3_frame_2017(const uint8_t frameContent[8]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B3_frame_523(const uint8_t frameContent[7]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B3_frame_807(const uint8_t frameContent[8]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B3_frame_1637(const uint8_t frameContent[5]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B3_frame_1784(const uint8_t frameContent[4]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B3_frame_649(const uint8_t frameContent[7]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B4_frame_1801(const uint8_t frameContent[8]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B4_frame_1926(const uint8_t frameContent[8]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B4_frame_986(const uint8_t frameContent[8]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B4_frame_998(const uint8_t frameContent[8]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B4_frame_743(const uint8_t frameContent[5]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B4_frame_655(const uint8_t frameContent[5]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B4_frame_1332(const uint8_t frameContent[8]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B4_frame_86(const uint8_t frameContent[5]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B4_frame_1002(const uint8_t frameContent[6]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B4_frame_1957(const uint8_t frameContent[6]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B4_frame_969(const uint8_t frameContent[8]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B4_frame_739(const uint8_t frameContent[6]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B4_frame_484(const uint8_t frameContent[3]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B4_frame_1970(const uint8_t frameContent[6]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B4_frame_163(const uint8_t frameContent[6]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B4_frame_948(const uint8_t frameContent[8]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B4_frame_853(const uint8_t frameContent[8]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B4_frame_1444(const uint8_t frameContent[8]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B5_frame_570(const uint8_t frameContent[7]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B5_frame_1406(const uint8_t frameContent[6]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B5_frame_201(const uint8_t frameContent[6]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B5_frame_1951(const uint8_t frameContent[8]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B5_frame_154(const uint8_t frameContent[4]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B5_frame_1043(const uint8_t frameContent[8]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B5_frame_306(const uint8_t frameContent[6]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B5_frame_37(const uint8_t frameContent[7]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B5_frame_1351(const uint8_t frameContent[5]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B5_frame_1458(const uint8_t frameContent[7]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B5_frame_809(const uint8_t frameContent[6]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B5_frame_1752(const uint8_t frameContent[8]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B5_frame_170(const uint8_t frameContent[8]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B5_frame_1732(const uint8_t frameContent[5]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B6_frame_550(const uint8_t frameContent[6]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B6_frame_168(const uint8_t frameContent[7]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B6_frame_66(const uint8_t frameContent[8]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B6_frame_1387(const uint8_t frameContent[6]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B6_frame_441(const uint8_t frameContent[5]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B6_frame_1716(const uint8_t frameContent[8]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B6_frame_941(const uint8_t frameContent[7]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B6_frame_1640(const uint8_t frameContent[7]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B6_frame_1575(const uint8_t frameContent[8]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B6_frame_1272(const uint8_t frameContent[6]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B6_frame_913(const uint8_t frameContent[7]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B6_frame_1165(const uint8_t frameContent[4]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B6_frame_895(const uint8_t frameContent[3]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B6_frame_666(const uint8_t frameContent[3]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B6_frame_1495(const uint8_t frameContent[8]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B6_frame_1175(const uint8_t frameContent[5]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B6_frame_1277(const uint8_t frameContent[2]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B6_frame_1593(const uint8_t frameContent[5]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B6_frame_1980(const uint8_t frameContent[7]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B6_frame_1287(const uint8_t frameContent[8]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B6_frame_189(const uint8_t frameContent[2]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B6_frame_494(const uint8_t frameContent[5]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B6_frame_1045(const uint8_t frameContent[4]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B6_frame_1469(const uint8_t frameContent[8]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B6_frame_1684(const uint8_t frameContent[8]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B6_frame_1614(const uint8_t frameContent[8]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B6_frame_747(const uint8_t frameContent[6]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B6_frame_1013(const uint8_t frameContent[2]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B6_frame_582(const uint8_t frameContent[4]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B6_frame_291(const uint8_t frameContent[7]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B6_frame_137(const uint8_t frameContent[6]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B7_frame_782(const uint8_t frameContent[6]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B7_frame_1867(const uint8_t frameContent[4]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B7_frame_61(const uint8_t frameContent[7]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B7_frame_1403(const uint8_t frameContent[8]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B7_frame_158(const uint8_t frameContent[8]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B7_frame_1052(const uint8_t frameContent[3]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B7_frame_1297(const uint8_t frameContent[7]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B7_frame_1829(const uint8_t frameContent[8]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B7_frame_1281(const uint8_t frameContent[6]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B7_frame_678(const uint8_t frameContent[2]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B7_frame_1157(const uint8_t frameContent[3]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B7_frame_111(const uint8_t frameContent[8]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B7_frame_509(const uint8_t frameContent[6]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B7_frame_199(const uint8_t frameContent[4]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B7_frame_1931(const uint8_t frameContent[5]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B7_frame_1524(const uint8_t frameContent[6]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B7_frame_924(const uint8_t frameContent[8]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B7_frame_1022(const uint8_t frameContent[7]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B7_frame_793(const uint8_t frameContent[7]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B7_frame_465(const uint8_t frameContent[3]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B7_frame_294(const uint8_t frameContent[8]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B7_frame_593(const uint8_t frameContent[5]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B7_frame_1475(const uint8_t frameContent[8]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B7_frame_192(const uint8_t frameContent[6]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B7_frame_1954(const uint8_t frameContent[6]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B7_frame_1993(const uint8_t frameContent[8]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B8_frame_392(const uint8_t frameContent[8]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B8_frame_33(const uint8_t frameContent[4]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B8_frame_1076(const uint8_t frameContent[4]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B8_frame_24(const uint8_t frameContent[6]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B8_frame_880(const uint8_t frameContent[8]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B8_frame_646(const uint8_t frameContent[5]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B8_frame_85(const uint8_t frameContent[8]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B8_frame_696(const uint8_t frameContent[3]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B8_frame_991(const uint8_t frameContent[5]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B8_frame_632(const uint8_t frameContent[8]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B8_frame_1388(const uint8_t frameContent[7]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B8_frame_755(const uint8_t frameContent[5]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B8_frame_966(const uint8_t frameContent[8]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B8_frame_1961(const uint8_t frameContent[8]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B8_frame_1687(const uint8_t frameContent[8]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B8_frame_1663(const uint8_t frameContent[4]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B8_frame_1510(const uint8_t frameContent[8]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B8_frame_1460(const uint8_t frameContent[4]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B8_frame_653(const uint8_t frameContent[7]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B8_frame_699(const uint8_t frameContent[4]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B8_frame_970(const uint8_t frameContent[3]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B8_frame_305(const uint8_t frameContent[5]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B8_frame_309(const uint8_t frameContent[6]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B8_frame_231(const uint8_t frameContent[1]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B8_frame_1530(const uint8_t frameContent[7]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B9_frame_1676(const uint8_t frameContent[7]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B9_frame_1491(const uint8_t frameContent[6]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B9_frame_1536(const uint8_t frameContent[4]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B9_frame_621(const uint8_t frameContent[4]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B9_frame_538(const uint8_t frameContent[8]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B9_frame_1384(const uint8_t frameContent[7]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B9_frame_21(const uint8_t frameContent[6]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B9_frame_409(const uint8_t frameContent[7]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B9_frame_1148(const uint8_t frameContent[7]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B9_frame_1934(const uint8_t frameContent[6]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B9_frame_1538(const uint8_t frameContent[8]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B9_frame_1146(const uint8_t frameContent[4]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B9_frame_1025(const uint8_t frameContent[5]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B9_frame_1610(const uint8_t frameContent[4]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B9_frame_1315(const uint8_t frameContent[7]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B9_frame_900(const uint8_t frameContent[7]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B9_frame_171(const uint8_t frameContent[5]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B9_frame_240(const uint8_t frameContent[5]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B9_frame_178(const uint8_t frameContent[6]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B9_frame_2031(const uint8_t frameContent[7]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B9_frame_1935(const uint8_t frameContent[8]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B9_frame_1416(const uint8_t frameContent[8]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B9_frame_950(const uint8_t frameContent[8]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B9_frame_734(const uint8_t frameContent[8]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B9_frame_1565(const uint8_t frameContent[8]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B9_frame_1699(const uint8_t frameContent[6]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B9_frame_1698(const uint8_t frameContent[7]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B9_frame_1854(const uint8_t frameContent[8]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B9_frame_1142(const uint8_t frameContent[6]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B9_frame_1007(const uint8_t frameContent[8]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B9_frame_1613(const uint8_t frameContent[6]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B9_frame_627(const uint8_t frameContent[8]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B9_frame_973(const uint8_t frameContent[8]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B9_frame_1362(const uint8_t frameContent[7]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B10_frame_612(const uint8_t frameContent[5]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B10_frame_5(const uint8_t frameContent[4]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B10_frame_1477(const uint8_t frameContent[6]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B10_frame_1604(const uint8_t frameContent[7]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B10_frame_36(const uint8_t frameContent[7]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B10_frame_2001(const uint8_t frameContent[6]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B10_frame_80(const uint8_t frameContent[6]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B10_frame_0(const uint8_t frameContent[5]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B10_frame_1494(const uint8_t frameContent[4]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B10_frame_537(const uint8_t frameContent[7]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B10_frame_741(const uint8_t frameContent[6]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B10_frame_1396(const uint8_t frameContent[2]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B10_frame_207(const uint8_t frameContent[7]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B10_frame_1996(const uint8_t frameContent[7]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B10_frame_1505(const uint8_t frameContent[6]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B10_frame_26(const uint8_t frameContent[7]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B10_frame_515(const uint8_t frameContent[4]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B10_frame_677(const uint8_t frameContent[4]);

#endif // !defined(OSE_UNPACKANDCHECKFRAME_DEFINED)