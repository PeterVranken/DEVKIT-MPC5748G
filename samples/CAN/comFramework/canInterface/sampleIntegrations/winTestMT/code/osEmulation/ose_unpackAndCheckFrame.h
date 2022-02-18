#ifndef OSE_UNPACKANDCHECKFRAME_DEFINED
#define OSE_UNPACKANDCHECKFRAME_DEFINED
/**
 * @file ose_unpackAndCheckFrame.h
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
extern boolean_t ose_unpackAndCheck_B1_frame_x2044_x2044(const uint8_t frameContent[4]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B1_frame_1049_1049(const uint8_t frameContent[7]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B1_frame_1834_1834(const uint8_t frameContent[6]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B1_frame_1053_1053(const uint8_t frameContent[7]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B1_frame_693_693(const uint8_t frameContent[8]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B1_frame_1143_1143(const uint8_t frameContent[5]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B1_frame_453_453(const uint8_t frameContent[6]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B1_frame_403_403(const uint8_t frameContent[8]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B1_frame_766_766(const uint8_t frameContent[7]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B1_frame_1271_1271(const uint8_t frameContent[6]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B1_frame_332_332(const uint8_t frameContent[5]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B1_frame_602_602(const uint8_t frameContent[7]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B1_frame_1605_1605(const uint8_t frameContent[7]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B1_frame_1731_1731(const uint8_t frameContent[8]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B1_frame_1529_1529(const uint8_t frameContent[7]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B1_frame_808_808(const uint8_t frameContent[6]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B1_frame_1181_1181(const uint8_t frameContent[6]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B1_frame_1725_1725(const uint8_t frameContent[6]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B1_frame_208_208(const uint8_t frameContent[6]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B1_frame_2047_2047(const uint8_t frameContent[8]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B1_frame_590_590(const uint8_t frameContent[7]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B1_frame_1419_1419(const uint8_t frameContent[6]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B1_frame_x0_x0(const uint8_t frameContent[7]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B1_frame_1630_1630(const uint8_t frameContent[7]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B1_frame_1033_1033(const uint8_t frameContent[5]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B1_frame_803_803(const uint8_t frameContent[4]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B1_frame_106_106(const uint8_t frameContent[5]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B1_frame_905_905(const uint8_t frameContent[8]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B1_frame_0_0(const uint8_t frameContent[7]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B1_frame_1885_1885(const uint8_t frameContent[4]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B1_frame_1415_1415(const uint8_t frameContent[5]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B1_frame_915_915(const uint8_t frameContent[6]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B1_frame_349_349(const uint8_t frameContent[6]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B2_frame_25_25(const uint8_t frameContent[5]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B2_frame_1641_1641(const uint8_t frameContent[5]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B2_frame_669_669(const uint8_t frameContent[6]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B2_frame_1401_1401(const uint8_t frameContent[6]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B2_frame_1340_1340(const uint8_t frameContent[6]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B2_frame_1151_1151(const uint8_t frameContent[7]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B2_frame_1730_1730(const uint8_t frameContent[8]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B2_frame_46_46(const uint8_t frameContent[6]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B2_frame_1939_1939(const uint8_t frameContent[8]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B2_frame_659_659(const uint8_t frameContent[6]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B2_frame_981_981(const uint8_t frameContent[6]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B2_frame_708_708(const uint8_t frameContent[8]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B2_frame_1618_1618(const uint8_t frameContent[4]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B2_frame_1956_1956(const uint8_t frameContent[5]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B2_frame_463_463(const uint8_t frameContent[4]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B2_frame_954_954(const uint8_t frameContent[8]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B2_frame_1126_1126(const uint8_t frameContent[7]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B2_frame_729_729(const uint8_t frameContent[6]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B2_frame_2045_2045(const uint8_t frameContent[5]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B2_frame_1901_1901(const uint8_t frameContent[7]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B2_frame_381_381(const uint8_t frameContent[8]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B2_frame_796_796(const uint8_t frameContent[6]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B2_frame_1652_1652(const uint8_t frameContent[7]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B2_frame_1442_1442(const uint8_t frameContent[2]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B3_frame_661_661(const uint8_t frameContent[4]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B3_frame_1084_1084(const uint8_t frameContent[4]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B3_frame_1170_1170(const uint8_t frameContent[8]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B3_frame_1696_1696(const uint8_t frameContent[7]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B3_frame_1398_1398(const uint8_t frameContent[8]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B3_frame_1425_1425(const uint8_t frameContent[5]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B3_frame_1154_1154(const uint8_t frameContent[5]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B3_frame_1404_1404(const uint8_t frameContent[8]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B3_frame_1374_1374(const uint8_t frameContent[7]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B3_frame_820_820(const uint8_t frameContent[4]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B3_frame_1713_1713(const uint8_t frameContent[7]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B3_frame_1485_1485(const uint8_t frameContent[7]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B3_frame_1385_1385(const uint8_t frameContent[6]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B3_frame_2017_2017(const uint8_t frameContent[8]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B3_frame_523_523(const uint8_t frameContent[7]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B3_frame_807_807(const uint8_t frameContent[8]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B3_frame_1637_1637(const uint8_t frameContent[5]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B3_frame_1784_1784(const uint8_t frameContent[4]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B3_frame_649_649(const uint8_t frameContent[7]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B4_frame_1801_1801(const uint8_t frameContent[8]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B4_frame_1926_1926(const uint8_t frameContent[8]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B4_frame_986_986(const uint8_t frameContent[8]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B4_frame_998_998(const uint8_t frameContent[8]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B4_frame_743_743(const uint8_t frameContent[5]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B4_frame_655_655(const uint8_t frameContent[5]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B4_frame_1332_1332(const uint8_t frameContent[8]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B4_frame_86_86(const uint8_t frameContent[5]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B4_frame_1002_1002(const uint8_t frameContent[6]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B4_frame_1957_1957(const uint8_t frameContent[6]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B4_frame_969_969(const uint8_t frameContent[8]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B4_frame_739_739(const uint8_t frameContent[6]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B4_frame_484_484(const uint8_t frameContent[3]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B4_frame_1970_1970(const uint8_t frameContent[6]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B4_frame_163_163(const uint8_t frameContent[6]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B4_frame_948_948(const uint8_t frameContent[8]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B4_frame_853_853(const uint8_t frameContent[8]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B4_frame_1444_1444(const uint8_t frameContent[8]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B5_frame_570_570(const uint8_t frameContent[7]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B5_frame_1406_1406(const uint8_t frameContent[6]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B5_frame_201_201(const uint8_t frameContent[6]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B5_frame_1951_1951(const uint8_t frameContent[8]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B5_frame_154_154(const uint8_t frameContent[4]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B5_frame_1043_1043(const uint8_t frameContent[8]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B5_frame_306_306(const uint8_t frameContent[6]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B5_frame_37_37(const uint8_t frameContent[7]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B5_frame_1351_1351(const uint8_t frameContent[5]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B5_frame_1458_1458(const uint8_t frameContent[7]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B5_frame_809_809(const uint8_t frameContent[6]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B5_frame_1752_1752(const uint8_t frameContent[8]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B5_frame_170_170(const uint8_t frameContent[8]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B5_frame_1732_1732(const uint8_t frameContent[5]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B6_frame_550_550(const uint8_t frameContent[6]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B6_frame_168_168(const uint8_t frameContent[7]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B6_frame_66_66(const uint8_t frameContent[8]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B6_frame_1387_1387(const uint8_t frameContent[6]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B6_frame_441_441(const uint8_t frameContent[5]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B6_frame_1716_1716(const uint8_t frameContent[8]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B6_frame_941_941(const uint8_t frameContent[7]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B6_frame_1640_1640(const uint8_t frameContent[7]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B6_frame_1575_1575(const uint8_t frameContent[8]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B6_frame_1272_1272(const uint8_t frameContent[6]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B6_frame_913_913(const uint8_t frameContent[7]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B6_frame_1165_1165(const uint8_t frameContent[4]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B6_frame_895_895(const uint8_t frameContent[3]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B6_frame_666_666(const uint8_t frameContent[3]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B6_frame_1495_1495(const uint8_t frameContent[8]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B6_frame_1175_1175(const uint8_t frameContent[5]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B6_frame_1277_1277(const uint8_t frameContent[2]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B6_frame_1593_1593(const uint8_t frameContent[5]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B6_frame_1980_1980(const uint8_t frameContent[7]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B6_frame_1287_1287(const uint8_t frameContent[8]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B6_frame_189_189(const uint8_t frameContent[2]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B6_frame_494_494(const uint8_t frameContent[5]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B6_frame_1045_1045(const uint8_t frameContent[4]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B6_frame_1469_1469(const uint8_t frameContent[8]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B6_frame_1684_1684(const uint8_t frameContent[8]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B6_frame_1614_1614(const uint8_t frameContent[8]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B6_frame_747_747(const uint8_t frameContent[6]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B6_frame_1013_1013(const uint8_t frameContent[2]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B6_frame_582_582(const uint8_t frameContent[4]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B6_frame_291_291(const uint8_t frameContent[7]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B6_frame_137_137(const uint8_t frameContent[6]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B7_frame_782_782(const uint8_t frameContent[6]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B7_frame_1867_1867(const uint8_t frameContent[4]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B7_frame_61_61(const uint8_t frameContent[7]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B7_frame_1403_1403(const uint8_t frameContent[8]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B7_frame_158_158(const uint8_t frameContent[8]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B7_frame_1052_1052(const uint8_t frameContent[3]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B7_frame_1297_1297(const uint8_t frameContent[7]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B7_frame_1829_1829(const uint8_t frameContent[8]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B7_frame_1281_1281(const uint8_t frameContent[6]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B7_frame_678_678(const uint8_t frameContent[2]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B7_frame_1157_1157(const uint8_t frameContent[3]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B7_frame_111_111(const uint8_t frameContent[8]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B7_frame_509_509(const uint8_t frameContent[6]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B7_frame_199_199(const uint8_t frameContent[4]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B7_frame_1931_1931(const uint8_t frameContent[5]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B7_frame_1524_1524(const uint8_t frameContent[6]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B7_frame_924_924(const uint8_t frameContent[8]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B7_frame_1022_1022(const uint8_t frameContent[7]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B7_frame_793_793(const uint8_t frameContent[7]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B7_frame_465_465(const uint8_t frameContent[3]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B7_frame_294_294(const uint8_t frameContent[8]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B7_frame_593_593(const uint8_t frameContent[5]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B7_frame_1475_1475(const uint8_t frameContent[8]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B7_frame_192_192(const uint8_t frameContent[6]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B7_frame_1954_1954(const uint8_t frameContent[6]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B7_frame_1993_1993(const uint8_t frameContent[8]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B8_frame_392_392(const uint8_t frameContent[8]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B8_frame_33_33(const uint8_t frameContent[4]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B8_frame_1076_1076(const uint8_t frameContent[4]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B8_frame_24_24(const uint8_t frameContent[6]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B8_frame_880_880(const uint8_t frameContent[8]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B8_frame_646_646(const uint8_t frameContent[5]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B8_frame_85_85(const uint8_t frameContent[8]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B8_frame_696_696(const uint8_t frameContent[3]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B8_frame_991_991(const uint8_t frameContent[5]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B8_frame_632_632(const uint8_t frameContent[8]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B8_frame_1388_1388(const uint8_t frameContent[7]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B8_frame_755_755(const uint8_t frameContent[5]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B8_frame_966_966(const uint8_t frameContent[8]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B8_frame_1961_1961(const uint8_t frameContent[8]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B8_frame_1687_1687(const uint8_t frameContent[8]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B8_frame_1663_1663(const uint8_t frameContent[4]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B8_frame_1510_1510(const uint8_t frameContent[8]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B8_frame_1460_1460(const uint8_t frameContent[4]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B8_frame_653_653(const uint8_t frameContent[7]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B8_frame_699_699(const uint8_t frameContent[4]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B8_frame_970_970(const uint8_t frameContent[3]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B8_frame_305_305(const uint8_t frameContent[5]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B8_frame_309_309(const uint8_t frameContent[6]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B8_frame_231_231(const uint8_t frameContent[1]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B8_frame_1530_1530(const uint8_t frameContent[7]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B9_frame_1676_1676(const uint8_t frameContent[7]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B9_frame_1491_1491(const uint8_t frameContent[6]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B9_frame_1536_1536(const uint8_t frameContent[4]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B9_frame_621_621(const uint8_t frameContent[4]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B9_frame_538_538(const uint8_t frameContent[8]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B9_frame_1384_1384(const uint8_t frameContent[7]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B9_frame_21_21(const uint8_t frameContent[6]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B9_frame_409_409(const uint8_t frameContent[7]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B9_frame_1148_1148(const uint8_t frameContent[7]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B9_frame_1934_1934(const uint8_t frameContent[6]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B9_frame_1538_1538(const uint8_t frameContent[8]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B9_frame_1146_1146(const uint8_t frameContent[4]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B9_frame_1025_1025(const uint8_t frameContent[5]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B9_frame_1610_1610(const uint8_t frameContent[4]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B9_frame_1315_1315(const uint8_t frameContent[7]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B9_frame_900_900(const uint8_t frameContent[7]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B9_frame_171_171(const uint8_t frameContent[5]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B9_frame_240_240(const uint8_t frameContent[5]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B9_frame_178_178(const uint8_t frameContent[6]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B9_frame_2031_2031(const uint8_t frameContent[7]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B9_frame_1935_1935(const uint8_t frameContent[8]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B9_frame_1416_1416(const uint8_t frameContent[8]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B9_frame_950_950(const uint8_t frameContent[8]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B9_frame_734_734(const uint8_t frameContent[8]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B9_frame_1565_1565(const uint8_t frameContent[8]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B9_frame_1699_1699(const uint8_t frameContent[6]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B9_frame_1698_1698(const uint8_t frameContent[7]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B9_frame_1854_1854(const uint8_t frameContent[8]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B9_frame_1142_1142(const uint8_t frameContent[6]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B9_frame_1007_1007(const uint8_t frameContent[8]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B9_frame_1613_1613(const uint8_t frameContent[6]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B9_frame_627_627(const uint8_t frameContent[8]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B9_frame_973_973(const uint8_t frameContent[8]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B9_frame_1362_1362(const uint8_t frameContent[7]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B10_frame_612_612(const uint8_t frameContent[5]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B10_frame_5_5(const uint8_t frameContent[4]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B10_frame_1477_1477(const uint8_t frameContent[6]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B10_frame_1604_1604(const uint8_t frameContent[7]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B10_frame_36_36(const uint8_t frameContent[7]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B10_frame_2001_2001(const uint8_t frameContent[6]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B10_frame_80_80(const uint8_t frameContent[6]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B10_frame_0_0(const uint8_t frameContent[5]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B10_frame_1494_1494(const uint8_t frameContent[4]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B10_frame_537_537(const uint8_t frameContent[7]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B10_frame_741_741(const uint8_t frameContent[6]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B10_frame_1396_1396(const uint8_t frameContent[2]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B10_frame_207_207(const uint8_t frameContent[7]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B10_frame_1996_1996(const uint8_t frameContent[7]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B10_frame_1505_1505(const uint8_t frameContent[6]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B10_frame_26_26(const uint8_t frameContent[7]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B10_frame_515_515(const uint8_t frameContent[4]);
/** Unpack a frame and run E2E validation. */
extern boolean_t ose_unpackAndCheck_B10_frame_677_677(const uint8_t frameContent[4]);

#endif // !defined(OSE_UNPACKANDCHECKFRAME_DEFINED)