#ifndef CAP_PRECOCHECK_DEFINED
#define CAP_PRECOCHECK_DEFINED
/**
 * @file cap_precoCheck.h
 * 
 * This header file contains a number of compile time checks of static elements of the
 * network database, which need to be fulfilled for successful compilation and execution of
 * the generated code.\n
 *   The file is included by the generated file cap_canApi.c after setting a number of
 * #define's that are related to frames and signals. These defines are checked for valid
 * values. The checks are completed by some tests of the attributes, which the code
 * generation depends on. It's highly probable that these tests will emit a compile time
 * error if the code generation is done with an arbitrary other network file.
 *   @remark
 * All checks relate to static properties of the network database. If these tests can be
 * done by code generation template expressions (mainly the test of Boolean object
 * properties and test of existence of objects) then this way is preferred. A failing test
 * will generate an error directive, a successful test will not emit anything.\n
 *   Code generation templates are limited and cumbersome in doing numeric comparisons. If
 * those are required than the code generation process tends to generate according C
 * preprocessor conditions with #error directives inside.\n
 *   Since the former kind of tests is frequently used you will not see anything in this
 * file about most of the tests! Error code will show up only if the error has been
 * detected in the network file.
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

#include "cap_canApi.h"

/*
 * Defines
 */

/** This is not a common, global header file. It must only be included by \a 
    cap_canApi.c. Check. */
#ifdef CAP_INCLUDES_PRECO_CHECKS
# undef CAP_INCLUDES_PRECO_CHECKS
#else
# error This header must be included only by cap_canApi.c
#endif

/** Double-check that the code generation templates are configured to use the right suffix
    for global objects. Go to file symbols.stg, dictionary file, if you get an error here. */
#define CAP_TMP_DEF_STRCMP_cap_
#ifndef CAP_TMP_DEF_STRCMP_cap_
# error Bad template configuration: Mismatch of module suffix, see cap_ but require cap_
#endif
#undef CAP_TMP_DEF_STRCMP_cap_











/** Check the definition of the checksum of frame frame_1706 (1706, 0x6aa)
    on bus B1.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B1_FRAME_1706_1706_CHECKSUM_LENGTH != 8               \
    || (!CAP_B1_FRAME_1706_1706_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B1_FRAME_1706_1706_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B1_FRAME_1706_1706_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B1_FRAME_1706_1706_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_01.dbc, frame frame_1706 (1706, 0x6aa): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1242 (1242, 0x4da)
    on bus B1.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B1_FRAME_1242_1242_CHECKSUM_LENGTH != 8               \
    || (!CAP_B1_FRAME_1242_1242_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B1_FRAME_1242_1242_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B1_FRAME_1242_1242_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B1_FRAME_1242_1242_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_01.dbc, frame frame_1242 (1242, 0x4da): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_774 (774, 0x306)
    on bus B1.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B1_FRAME_774_774_CHECKSUM_LENGTH != 8               \
    || (!CAP_B1_FRAME_774_774_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B1_FRAME_774_774_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B1_FRAME_774_774_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B1_FRAME_774_774_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_01.dbc, frame frame_774 (774, 0x306): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_2044 (2044, 0x7fc)
    on bus B1.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B1_FRAME_2044_2044_CHECKSUM_LENGTH != 8               \
    || (!CAP_B1_FRAME_2044_2044_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B1_FRAME_2044_2044_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B1_FRAME_2044_2044_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B1_FRAME_2044_2044_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_01.dbc, frame frame_2044 (2044, 0x7fc): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1907 (1907, 0x773)
    on bus B1.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B1_FRAME_1907_1907_CHECKSUM_LENGTH != 8               \
    || (!CAP_B1_FRAME_1907_1907_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B1_FRAME_1907_1907_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B1_FRAME_1907_1907_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B1_FRAME_1907_1907_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_01.dbc, frame frame_1907 (1907, 0x773): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_594 (594, 0x252)
    on bus B1.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B1_FRAME_594_594_CHECKSUM_LENGTH != 8               \
    || (!CAP_B1_FRAME_594_594_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B1_FRAME_594_594_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B1_FRAME_594_594_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B1_FRAME_594_594_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_01.dbc, frame frame_594 (594, 0x252): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1049 (1049, 0x419)
    on bus B1.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B1_FRAME_1049_1049_CHECKSUM_LENGTH != 8               \
    || (!CAP_B1_FRAME_1049_1049_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B1_FRAME_1049_1049_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B1_FRAME_1049_1049_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B1_FRAME_1049_1049_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_01.dbc, frame frame_1049 (1049, 0x419): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1207 (1207, 0x4b7)
    on bus B1.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B1_FRAME_1207_1207_CHECKSUM_LENGTH != 8               \
    || (!CAP_B1_FRAME_1207_1207_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B1_FRAME_1207_1207_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B1_FRAME_1207_1207_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B1_FRAME_1207_1207_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_01.dbc, frame frame_1207 (1207, 0x4b7): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_902 (902, 0x386)
    on bus B1.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B1_FRAME_902_902_CHECKSUM_LENGTH != 8               \
    || (!CAP_B1_FRAME_902_902_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B1_FRAME_902_902_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B1_FRAME_902_902_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B1_FRAME_902_902_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_01.dbc, frame frame_902 (902, 0x386): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1834 (1834, 0x72a)
    on bus B1.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B1_FRAME_1834_1834_CHECKSUM_LENGTH != 8               \
    || (!CAP_B1_FRAME_1834_1834_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B1_FRAME_1834_1834_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B1_FRAME_1834_1834_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B1_FRAME_1834_1834_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_01.dbc, frame frame_1834 (1834, 0x72a): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_609 (609, 0x261)
    on bus B1.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B1_FRAME_609_609_CHECKSUM_LENGTH != 8               \
    || (!CAP_B1_FRAME_609_609_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B1_FRAME_609_609_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B1_FRAME_609_609_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B1_FRAME_609_609_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_01.dbc, frame frame_609 (609, 0x261): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1367 (1367, 0x557)
    on bus B1.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B1_FRAME_1367_1367_CHECKSUM_LENGTH != 8               \
    || (!CAP_B1_FRAME_1367_1367_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B1_FRAME_1367_1367_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B1_FRAME_1367_1367_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B1_FRAME_1367_1367_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_01.dbc, frame frame_1367 (1367, 0x557): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1053 (1053, 0x41d)
    on bus B1.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B1_FRAME_1053_1053_CHECKSUM_LENGTH != 8               \
    || (!CAP_B1_FRAME_1053_1053_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B1_FRAME_1053_1053_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B1_FRAME_1053_1053_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B1_FRAME_1053_1053_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_01.dbc, frame frame_1053 (1053, 0x41d): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1114 (1114, 0x45a)
    on bus B1.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B1_FRAME_1114_1114_CHECKSUM_LENGTH != 8               \
    || (!CAP_B1_FRAME_1114_1114_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B1_FRAME_1114_1114_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B1_FRAME_1114_1114_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B1_FRAME_1114_1114_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_01.dbc, frame frame_1114 (1114, 0x45a): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_693 (693, 0x2b5)
    on bus B1.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B1_FRAME_693_693_CHECKSUM_LENGTH != 8               \
    || (!CAP_B1_FRAME_693_693_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B1_FRAME_693_693_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B1_FRAME_693_693_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B1_FRAME_693_693_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_01.dbc, frame frame_693 (693, 0x2b5): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1143 (1143, 0x477)
    on bus B1.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B1_FRAME_1143_1143_CHECKSUM_LENGTH != 8               \
    || (!CAP_B1_FRAME_1143_1143_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B1_FRAME_1143_1143_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B1_FRAME_1143_1143_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B1_FRAME_1143_1143_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_01.dbc, frame frame_1143 (1143, 0x477): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_667 (667, 0x29b)
    on bus B1.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B1_FRAME_667_667_CHECKSUM_LENGTH != 8               \
    || (!CAP_B1_FRAME_667_667_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B1_FRAME_667_667_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B1_FRAME_667_667_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B1_FRAME_667_667_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_01.dbc, frame frame_667 (667, 0x29b): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_453 (453, 0x1c5)
    on bus B1.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B1_FRAME_453_453_CHECKSUM_LENGTH != 8               \
    || (!CAP_B1_FRAME_453_453_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B1_FRAME_453_453_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B1_FRAME_453_453_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B1_FRAME_453_453_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_01.dbc, frame frame_453 (453, 0x1c5): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1294 (1294, 0x50e)
    on bus B1.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B1_FRAME_1294_1294_CHECKSUM_LENGTH != 8               \
    || (!CAP_B1_FRAME_1294_1294_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B1_FRAME_1294_1294_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B1_FRAME_1294_1294_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B1_FRAME_1294_1294_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_01.dbc, frame frame_1294 (1294, 0x50e): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_403 (403, 0x193)
    on bus B1.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B1_FRAME_403_403_CHECKSUM_LENGTH != 8               \
    || (!CAP_B1_FRAME_403_403_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B1_FRAME_403_403_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B1_FRAME_403_403_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B1_FRAME_403_403_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_01.dbc, frame frame_403 (403, 0x193): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1051 (1051, 0x41b)
    on bus B1.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B1_FRAME_1051_1051_CHECKSUM_LENGTH != 8               \
    || (!CAP_B1_FRAME_1051_1051_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B1_FRAME_1051_1051_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B1_FRAME_1051_1051_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B1_FRAME_1051_1051_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_01.dbc, frame frame_1051 (1051, 0x41b): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1352 (1352, 0x548)
    on bus B1.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B1_FRAME_1352_1352_CHECKSUM_LENGTH != 8               \
    || (!CAP_B1_FRAME_1352_1352_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B1_FRAME_1352_1352_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B1_FRAME_1352_1352_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B1_FRAME_1352_1352_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_01.dbc, frame frame_1352 (1352, 0x548): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1140 (1140, 0x474)
    on bus B1.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B1_FRAME_1140_1140_CHECKSUM_LENGTH != 8               \
    || (!CAP_B1_FRAME_1140_1140_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B1_FRAME_1140_1140_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B1_FRAME_1140_1140_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B1_FRAME_1140_1140_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_01.dbc, frame frame_1140 (1140, 0x474): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_652 (652, 0x28c)
    on bus B1.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B1_FRAME_652_652_CHECKSUM_LENGTH != 8               \
    || (!CAP_B1_FRAME_652_652_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B1_FRAME_652_652_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B1_FRAME_652_652_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B1_FRAME_652_652_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_01.dbc, frame frame_652 (652, 0x28c): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1091 (1091, 0x443)
    on bus B1.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B1_FRAME_1091_1091_CHECKSUM_LENGTH != 8               \
    || (!CAP_B1_FRAME_1091_1091_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B1_FRAME_1091_1091_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B1_FRAME_1091_1091_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B1_FRAME_1091_1091_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_01.dbc, frame frame_1091 (1091, 0x443): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1715 (1715, 0x6b3)
    on bus B1.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B1_FRAME_1715_1715_CHECKSUM_LENGTH != 8               \
    || (!CAP_B1_FRAME_1715_1715_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B1_FRAME_1715_1715_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B1_FRAME_1715_1715_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B1_FRAME_1715_1715_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_01.dbc, frame frame_1715 (1715, 0x6b3): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_766 (766, 0x2fe)
    on bus B1.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B1_FRAME_766_766_CHECKSUM_LENGTH != 8               \
    || (!CAP_B1_FRAME_766_766_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B1_FRAME_766_766_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B1_FRAME_766_766_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B1_FRAME_766_766_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_01.dbc, frame frame_766 (766, 0x2fe): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_131 (131, 0x083)
    on bus B1.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B1_FRAME_131_131_CHECKSUM_LENGTH != 8               \
    || (!CAP_B1_FRAME_131_131_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B1_FRAME_131_131_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B1_FRAME_131_131_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B1_FRAME_131_131_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_01.dbc, frame frame_131 (131, 0x083): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1271 (1271, 0x4f7)
    on bus B1.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B1_FRAME_1271_1271_CHECKSUM_LENGTH != 8               \
    || (!CAP_B1_FRAME_1271_1271_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B1_FRAME_1271_1271_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B1_FRAME_1271_1271_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B1_FRAME_1271_1271_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_01.dbc, frame frame_1271 (1271, 0x4f7): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_332 (332, 0x14c)
    on bus B1.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B1_FRAME_332_332_CHECKSUM_LENGTH != 8               \
    || (!CAP_B1_FRAME_332_332_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B1_FRAME_332_332_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B1_FRAME_332_332_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B1_FRAME_332_332_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_01.dbc, frame frame_332 (332, 0x14c): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_602 (602, 0x25a)
    on bus B1.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B1_FRAME_602_602_CHECKSUM_LENGTH != 8               \
    || (!CAP_B1_FRAME_602_602_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B1_FRAME_602_602_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B1_FRAME_602_602_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B1_FRAME_602_602_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_01.dbc, frame frame_602 (602, 0x25a): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_833 (833, 0x341)
    on bus B1.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B1_FRAME_833_833_CHECKSUM_LENGTH != 8               \
    || (!CAP_B1_FRAME_833_833_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B1_FRAME_833_833_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B1_FRAME_833_833_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B1_FRAME_833_833_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_01.dbc, frame frame_833 (833, 0x341): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1605 (1605, 0x645)
    on bus B1.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B1_FRAME_1605_1605_CHECKSUM_LENGTH != 8               \
    || (!CAP_B1_FRAME_1605_1605_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B1_FRAME_1605_1605_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B1_FRAME_1605_1605_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B1_FRAME_1605_1605_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_01.dbc, frame frame_1605 (1605, 0x645): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_514 (514, 0x202)
    on bus B1.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B1_FRAME_514_514_CHECKSUM_LENGTH != 8               \
    || (!CAP_B1_FRAME_514_514_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B1_FRAME_514_514_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B1_FRAME_514_514_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B1_FRAME_514_514_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_01.dbc, frame frame_514 (514, 0x202): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1731 (1731, 0x6c3)
    on bus B1.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B1_FRAME_1731_1731_CHECKSUM_LENGTH != 8               \
    || (!CAP_B1_FRAME_1731_1731_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B1_FRAME_1731_1731_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B1_FRAME_1731_1731_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B1_FRAME_1731_1731_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_01.dbc, frame frame_1731 (1731, 0x6c3): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1529 (1529, 0x5f9)
    on bus B1.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B1_FRAME_1529_1529_CHECKSUM_LENGTH != 8               \
    || (!CAP_B1_FRAME_1529_1529_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B1_FRAME_1529_1529_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B1_FRAME_1529_1529_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B1_FRAME_1529_1529_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_01.dbc, frame frame_1529 (1529, 0x5f9): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_417 (417, 0x1a1)
    on bus B1.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B1_FRAME_417_417_CHECKSUM_LENGTH != 8               \
    || (!CAP_B1_FRAME_417_417_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B1_FRAME_417_417_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B1_FRAME_417_417_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B1_FRAME_417_417_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_01.dbc, frame frame_417 (417, 0x1a1): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_808 (808, 0x328)
    on bus B1.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B1_FRAME_808_808_CHECKSUM_LENGTH != 8               \
    || (!CAP_B1_FRAME_808_808_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B1_FRAME_808_808_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B1_FRAME_808_808_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B1_FRAME_808_808_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_01.dbc, frame frame_808 (808, 0x328): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1181 (1181, 0x49d)
    on bus B1.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B1_FRAME_1181_1181_CHECKSUM_LENGTH != 8               \
    || (!CAP_B1_FRAME_1181_1181_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B1_FRAME_1181_1181_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B1_FRAME_1181_1181_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B1_FRAME_1181_1181_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_01.dbc, frame frame_1181 (1181, 0x49d): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1725 (1725, 0x6bd)
    on bus B1.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B1_FRAME_1725_1725_CHECKSUM_LENGTH != 8               \
    || (!CAP_B1_FRAME_1725_1725_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B1_FRAME_1725_1725_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B1_FRAME_1725_1725_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B1_FRAME_1725_1725_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_01.dbc, frame frame_1725 (1725, 0x6bd): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_208 (208, 0x0d0)
    on bus B1.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B1_FRAME_208_208_CHECKSUM_LENGTH != 8               \
    || (!CAP_B1_FRAME_208_208_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B1_FRAME_208_208_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B1_FRAME_208_208_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B1_FRAME_208_208_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_01.dbc, frame frame_208 (208, 0x0d0): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1246 (1246, 0x4de)
    on bus B1.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B1_FRAME_1246_1246_CHECKSUM_LENGTH != 8               \
    || (!CAP_B1_FRAME_1246_1246_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B1_FRAME_1246_1246_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B1_FRAME_1246_1246_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B1_FRAME_1246_1246_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_01.dbc, frame frame_1246 (1246, 0x4de): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1423 (1423, 0x58f)
    on bus B1.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B1_FRAME_1423_1423_CHECKSUM_LENGTH != 8               \
    || (!CAP_B1_FRAME_1423_1423_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B1_FRAME_1423_1423_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B1_FRAME_1423_1423_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B1_FRAME_1423_1423_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_01.dbc, frame frame_1423 (1423, 0x58f): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_2018 (2018, 0x7e2)
    on bus B1.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B1_FRAME_2018_2018_CHECKSUM_LENGTH != 8               \
    || (!CAP_B1_FRAME_2018_2018_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B1_FRAME_2018_2018_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B1_FRAME_2018_2018_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B1_FRAME_2018_2018_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_01.dbc, frame frame_2018 (2018, 0x7e2): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_846 (846, 0x34e)
    on bus B1.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B1_FRAME_846_846_CHECKSUM_LENGTH != 8               \
    || (!CAP_B1_FRAME_846_846_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B1_FRAME_846_846_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B1_FRAME_846_846_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B1_FRAME_846_846_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_01.dbc, frame frame_846 (846, 0x34e): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1764 (1764, 0x6e4)
    on bus B1.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B1_FRAME_1764_1764_CHECKSUM_LENGTH != 8               \
    || (!CAP_B1_FRAME_1764_1764_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B1_FRAME_1764_1764_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B1_FRAME_1764_1764_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B1_FRAME_1764_1764_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_01.dbc, frame frame_1764 (1764, 0x6e4): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1412 (1412, 0x584)
    on bus B1.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B1_FRAME_1412_1412_CHECKSUM_LENGTH != 8               \
    || (!CAP_B1_FRAME_1412_1412_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B1_FRAME_1412_1412_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B1_FRAME_1412_1412_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B1_FRAME_1412_1412_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_01.dbc, frame frame_1412 (1412, 0x584): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1445 (1445, 0x5a5)
    on bus B1.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B1_FRAME_1445_1445_CHECKSUM_LENGTH != 8               \
    || (!CAP_B1_FRAME_1445_1445_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B1_FRAME_1445_1445_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B1_FRAME_1445_1445_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B1_FRAME_1445_1445_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_01.dbc, frame frame_1445 (1445, 0x5a5): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_590 (590, 0x24e)
    on bus B1.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B1_FRAME_590_590_CHECKSUM_LENGTH != 8               \
    || (!CAP_B1_FRAME_590_590_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B1_FRAME_590_590_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B1_FRAME_590_590_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B1_FRAME_590_590_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_01.dbc, frame frame_590 (590, 0x24e): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_442 (442, 0x1ba)
    on bus B1.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B1_FRAME_442_442_CHECKSUM_LENGTH != 8               \
    || (!CAP_B1_FRAME_442_442_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B1_FRAME_442_442_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B1_FRAME_442_442_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B1_FRAME_442_442_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_01.dbc, frame frame_442 (442, 0x1ba): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_672 (672, 0x2a0)
    on bus B1.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B1_FRAME_672_672_CHECKSUM_LENGTH != 8               \
    || (!CAP_B1_FRAME_672_672_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B1_FRAME_672_672_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B1_FRAME_672_672_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B1_FRAME_672_672_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_01.dbc, frame frame_672 (672, 0x2a0): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1419 (1419, 0x58b)
    on bus B1.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B1_FRAME_1419_1419_CHECKSUM_LENGTH != 8               \
    || (!CAP_B1_FRAME_1419_1419_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B1_FRAME_1419_1419_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B1_FRAME_1419_1419_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B1_FRAME_1419_1419_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_01.dbc, frame frame_1419 (1419, 0x58b): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1937 (1937, 0x791)
    on bus B1.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B1_FRAME_1937_1937_CHECKSUM_LENGTH != 8               \
    || (!CAP_B1_FRAME_1937_1937_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B1_FRAME_1937_1937_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B1_FRAME_1937_1937_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B1_FRAME_1937_1937_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_01.dbc, frame frame_1937 (1937, 0x791): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1630 (1630, 0x65e)
    on bus B1.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B1_FRAME_1630_1630_CHECKSUM_LENGTH != 8               \
    || (!CAP_B1_FRAME_1630_1630_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B1_FRAME_1630_1630_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B1_FRAME_1630_1630_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B1_FRAME_1630_1630_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_01.dbc, frame frame_1630 (1630, 0x65e): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_718 (718, 0x2ce)
    on bus B1.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B1_FRAME_718_718_CHECKSUM_LENGTH != 8               \
    || (!CAP_B1_FRAME_718_718_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B1_FRAME_718_718_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B1_FRAME_718_718_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B1_FRAME_718_718_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_01.dbc, frame frame_718 (718, 0x2ce): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1042 (1042, 0x412)
    on bus B1.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B1_FRAME_1042_1042_CHECKSUM_LENGTH != 8               \
    || (!CAP_B1_FRAME_1042_1042_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B1_FRAME_1042_1042_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B1_FRAME_1042_1042_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B1_FRAME_1042_1042_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_01.dbc, frame frame_1042 (1042, 0x412): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_2013 (2013, 0x7dd)
    on bus B1.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B1_FRAME_2013_2013_CHECKSUM_LENGTH != 8               \
    || (!CAP_B1_FRAME_2013_2013_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B1_FRAME_2013_2013_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B1_FRAME_2013_2013_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B1_FRAME_2013_2013_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_01.dbc, frame frame_2013 (2013, 0x7dd): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1473 (1473, 0x5c1)
    on bus B1.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B1_FRAME_1473_1473_CHECKSUM_LENGTH != 8               \
    || (!CAP_B1_FRAME_1473_1473_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B1_FRAME_1473_1473_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B1_FRAME_1473_1473_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B1_FRAME_1473_1473_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_01.dbc, frame frame_1473 (1473, 0x5c1): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1033 (1033, 0x409)
    on bus B1.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B1_FRAME_1033_1033_CHECKSUM_LENGTH != 8               \
    || (!CAP_B1_FRAME_1033_1033_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B1_FRAME_1033_1033_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B1_FRAME_1033_1033_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B1_FRAME_1033_1033_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_01.dbc, frame frame_1033 (1033, 0x409): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_803 (803, 0x323)
    on bus B1.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B1_FRAME_803_803_CHECKSUM_LENGTH != 8               \
    || (!CAP_B1_FRAME_803_803_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B1_FRAME_803_803_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B1_FRAME_803_803_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B1_FRAME_803_803_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_01.dbc, frame frame_803 (803, 0x323): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_779 (779, 0x30b)
    on bus B1.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B1_FRAME_779_779_CHECKSUM_LENGTH != 8               \
    || (!CAP_B1_FRAME_779_779_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B1_FRAME_779_779_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B1_FRAME_779_779_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B1_FRAME_779_779_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_01.dbc, frame frame_779 (779, 0x30b): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_106 (106, 0x06a)
    on bus B1.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B1_FRAME_106_106_CHECKSUM_LENGTH != 8               \
    || (!CAP_B1_FRAME_106_106_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B1_FRAME_106_106_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B1_FRAME_106_106_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B1_FRAME_106_106_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_01.dbc, frame frame_106 (106, 0x06a): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_905 (905, 0x389)
    on bus B1.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B1_FRAME_905_905_CHECKSUM_LENGTH != 8               \
    || (!CAP_B1_FRAME_905_905_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B1_FRAME_905_905_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B1_FRAME_905_905_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B1_FRAME_905_905_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_01.dbc, frame frame_905 (905, 0x389): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_877 (877, 0x36d)
    on bus B1.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B1_FRAME_877_877_CHECKSUM_LENGTH != 8               \
    || (!CAP_B1_FRAME_877_877_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B1_FRAME_877_877_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B1_FRAME_877_877_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B1_FRAME_877_877_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_01.dbc, frame frame_877 (877, 0x36d): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_489 (489, 0x1e9)
    on bus B1.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B1_FRAME_489_489_CHECKSUM_LENGTH != 8               \
    || (!CAP_B1_FRAME_489_489_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B1_FRAME_489_489_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B1_FRAME_489_489_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B1_FRAME_489_489_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_01.dbc, frame frame_489 (489, 0x1e9): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1758 (1758, 0x6de)
    on bus B1.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B1_FRAME_1758_1758_CHECKSUM_LENGTH != 8               \
    || (!CAP_B1_FRAME_1758_1758_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B1_FRAME_1758_1758_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B1_FRAME_1758_1758_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B1_FRAME_1758_1758_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_01.dbc, frame frame_1758 (1758, 0x6de): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1998 (1998, 0x7ce)
    on bus B1.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B1_FRAME_1998_1998_CHECKSUM_LENGTH != 8               \
    || (!CAP_B1_FRAME_1998_1998_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B1_FRAME_1998_1998_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B1_FRAME_1998_1998_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B1_FRAME_1998_1998_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_01.dbc, frame frame_1998 (1998, 0x7ce): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1324 (1324, 0x52c)
    on bus B1.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B1_FRAME_1324_1324_CHECKSUM_LENGTH != 8               \
    || (!CAP_B1_FRAME_1324_1324_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B1_FRAME_1324_1324_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B1_FRAME_1324_1324_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B1_FRAME_1324_1324_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_01.dbc, frame frame_1324 (1324, 0x52c): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1885 (1885, 0x75d)
    on bus B1.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B1_FRAME_1885_1885_CHECKSUM_LENGTH != 8               \
    || (!CAP_B1_FRAME_1885_1885_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B1_FRAME_1885_1885_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B1_FRAME_1885_1885_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B1_FRAME_1885_1885_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_01.dbc, frame frame_1885 (1885, 0x75d): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1415 (1415, 0x587)
    on bus B1.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B1_FRAME_1415_1415_CHECKSUM_LENGTH != 8               \
    || (!CAP_B1_FRAME_1415_1415_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B1_FRAME_1415_1415_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B1_FRAME_1415_1415_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B1_FRAME_1415_1415_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_01.dbc, frame frame_1415 (1415, 0x587): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1252 (1252, 0x4e4)
    on bus B1.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B1_FRAME_1252_1252_CHECKSUM_LENGTH != 8               \
    || (!CAP_B1_FRAME_1252_1252_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B1_FRAME_1252_1252_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B1_FRAME_1252_1252_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B1_FRAME_1252_1252_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_01.dbc, frame frame_1252 (1252, 0x4e4): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_947 (947, 0x3b3)
    on bus B1.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B1_FRAME_947_947_CHECKSUM_LENGTH != 8               \
    || (!CAP_B1_FRAME_947_947_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B1_FRAME_947_947_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B1_FRAME_947_947_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B1_FRAME_947_947_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_01.dbc, frame frame_947 (947, 0x3b3): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1334 (1334, 0x536)
    on bus B1.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B1_FRAME_1334_1334_CHECKSUM_LENGTH != 8               \
    || (!CAP_B1_FRAME_1334_1334_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B1_FRAME_1334_1334_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B1_FRAME_1334_1334_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B1_FRAME_1334_1334_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_01.dbc, frame frame_1334 (1334, 0x536): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_458 (458, 0x1ca)
    on bus B1.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B1_FRAME_458_458_CHECKSUM_LENGTH != 8               \
    || (!CAP_B1_FRAME_458_458_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B1_FRAME_458_458_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B1_FRAME_458_458_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B1_FRAME_458_458_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_01.dbc, frame frame_458 (458, 0x1ca): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_915 (915, 0x393)
    on bus B1.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B1_FRAME_915_915_CHECKSUM_LENGTH != 8               \
    || (!CAP_B1_FRAME_915_915_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B1_FRAME_915_915_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B1_FRAME_915_915_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B1_FRAME_915_915_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_01.dbc, frame frame_915 (915, 0x393): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_349 (349, 0x15d)
    on bus B1.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B1_FRAME_349_349_CHECKSUM_LENGTH != 8               \
    || (!CAP_B1_FRAME_349_349_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B1_FRAME_349_349_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B1_FRAME_349_349_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B1_FRAME_349_349_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_01.dbc, frame frame_349 (349, 0x15d): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1 (1, 0x001)
    on bus B1.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B1_FRAME_1_1_CHECKSUM_LENGTH != 8               \
    || (!CAP_B1_FRAME_1_1_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B1_FRAME_1_1_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B1_FRAME_1_1_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B1_FRAME_1_1_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_01.dbc, frame frame_1 (1, 0x001): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_435 (435, 0x1b3)
    on bus B1.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B1_FRAME_435_435_CHECKSUM_LENGTH != 8               \
    || (!CAP_B1_FRAME_435_435_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B1_FRAME_435_435_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B1_FRAME_435_435_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B1_FRAME_435_435_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_01.dbc, frame frame_435 (435, 0x1b3): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_982 (982, 0x3d6)
    on bus B1.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B1_FRAME_982_982_CHECKSUM_LENGTH != 8               \
    || (!CAP_B1_FRAME_982_982_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B1_FRAME_982_982_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B1_FRAME_982_982_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B1_FRAME_982_982_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_01.dbc, frame frame_982 (982, 0x3d6): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_263 (263, 0x107)
    on bus B1.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B1_FRAME_263_263_CHECKSUM_LENGTH != 8               \
    || (!CAP_B1_FRAME_263_263_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B1_FRAME_263_263_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B1_FRAME_263_263_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B1_FRAME_263_263_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_01.dbc, frame frame_263 (263, 0x107): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_90 (90, 0x05a)
    on bus B2.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B2_FRAME_90_90_CHECKSUM_LENGTH != 8               \
    || (!CAP_B2_FRAME_90_90_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B2_FRAME_90_90_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B2_FRAME_90_90_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B2_FRAME_90_90_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_02.dbc, frame frame_90 (90, 0x05a): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1675 (1675, 0x68b)
    on bus B2.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B2_FRAME_1675_1675_CHECKSUM_LENGTH != 8               \
    || (!CAP_B2_FRAME_1675_1675_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B2_FRAME_1675_1675_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B2_FRAME_1675_1675_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B2_FRAME_1675_1675_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_02.dbc, frame frame_1675 (1675, 0x68b): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_261 (261, 0x105)
    on bus B2.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B2_FRAME_261_261_CHECKSUM_LENGTH != 8               \
    || (!CAP_B2_FRAME_261_261_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B2_FRAME_261_261_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B2_FRAME_261_261_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B2_FRAME_261_261_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_02.dbc, frame frame_261 (261, 0x105): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_660 (660, 0x294)
    on bus B2.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B2_FRAME_660_660_CHECKSUM_LENGTH != 8               \
    || (!CAP_B2_FRAME_660_660_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B2_FRAME_660_660_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B2_FRAME_660_660_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B2_FRAME_660_660_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_02.dbc, frame frame_660 (660, 0x294): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1074 (1074, 0x432)
    on bus B2.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B2_FRAME_1074_1074_CHECKSUM_LENGTH != 8               \
    || (!CAP_B2_FRAME_1074_1074_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B2_FRAME_1074_1074_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B2_FRAME_1074_1074_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B2_FRAME_1074_1074_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_02.dbc, frame frame_1074 (1074, 0x432): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_25 (25, 0x019)
    on bus B2.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B2_FRAME_25_25_CHECKSUM_LENGTH != 8               \
    || (!CAP_B2_FRAME_25_25_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B2_FRAME_25_25_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B2_FRAME_25_25_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B2_FRAME_25_25_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_02.dbc, frame frame_25 (25, 0x019): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1747 (1747, 0x6d3)
    on bus B2.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B2_FRAME_1747_1747_CHECKSUM_LENGTH != 8               \
    || (!CAP_B2_FRAME_1747_1747_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B2_FRAME_1747_1747_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B2_FRAME_1747_1747_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B2_FRAME_1747_1747_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_02.dbc, frame frame_1747 (1747, 0x6d3): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1641 (1641, 0x669)
    on bus B2.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B2_FRAME_1641_1641_CHECKSUM_LENGTH != 8               \
    || (!CAP_B2_FRAME_1641_1641_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B2_FRAME_1641_1641_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B2_FRAME_1641_1641_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B2_FRAME_1641_1641_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_02.dbc, frame frame_1641 (1641, 0x669): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_786 (786, 0x312)
    on bus B2.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B2_FRAME_786_786_CHECKSUM_LENGTH != 8               \
    || (!CAP_B2_FRAME_786_786_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B2_FRAME_786_786_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B2_FRAME_786_786_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B2_FRAME_786_786_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_02.dbc, frame frame_786 (786, 0x312): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_341 (341, 0x155)
    on bus B2.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B2_FRAME_341_341_CHECKSUM_LENGTH != 8               \
    || (!CAP_B2_FRAME_341_341_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B2_FRAME_341_341_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B2_FRAME_341_341_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B2_FRAME_341_341_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_02.dbc, frame frame_341 (341, 0x155): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1400 (1400, 0x578)
    on bus B2.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B2_FRAME_1400_1400_CHECKSUM_LENGTH != 8               \
    || (!CAP_B2_FRAME_1400_1400_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B2_FRAME_1400_1400_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B2_FRAME_1400_1400_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B2_FRAME_1400_1400_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_02.dbc, frame frame_1400 (1400, 0x578): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1545 (1545, 0x609)
    on bus B2.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B2_FRAME_1545_1545_CHECKSUM_LENGTH != 8               \
    || (!CAP_B2_FRAME_1545_1545_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B2_FRAME_1545_1545_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B2_FRAME_1545_1545_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B2_FRAME_1545_1545_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_02.dbc, frame frame_1545 (1545, 0x609): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_669 (669, 0x29d)
    on bus B2.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B2_FRAME_669_669_CHECKSUM_LENGTH != 8               \
    || (!CAP_B2_FRAME_669_669_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B2_FRAME_669_669_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B2_FRAME_669_669_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B2_FRAME_669_669_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_02.dbc, frame frame_669 (669, 0x29d): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_328 (328, 0x148)
    on bus B2.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B2_FRAME_328_328_CHECKSUM_LENGTH != 8               \
    || (!CAP_B2_FRAME_328_328_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B2_FRAME_328_328_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B2_FRAME_328_328_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B2_FRAME_328_328_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_02.dbc, frame frame_328 (328, 0x148): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_844 (844, 0x34c)
    on bus B2.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B2_FRAME_844_844_CHECKSUM_LENGTH != 8               \
    || (!CAP_B2_FRAME_844_844_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B2_FRAME_844_844_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B2_FRAME_844_844_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B2_FRAME_844_844_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_02.dbc, frame frame_844 (844, 0x34c): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_196 (196, 0x0c4)
    on bus B2.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B2_FRAME_196_196_CHECKSUM_LENGTH != 8               \
    || (!CAP_B2_FRAME_196_196_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B2_FRAME_196_196_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B2_FRAME_196_196_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B2_FRAME_196_196_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_02.dbc, frame frame_196 (196, 0x0c4): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_870 (870, 0x366)
    on bus B2.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B2_FRAME_870_870_CHECKSUM_LENGTH != 8               \
    || (!CAP_B2_FRAME_870_870_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B2_FRAME_870_870_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B2_FRAME_870_870_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B2_FRAME_870_870_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_02.dbc, frame frame_870 (870, 0x366): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1492 (1492, 0x5d4)
    on bus B2.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B2_FRAME_1492_1492_CHECKSUM_LENGTH != 8               \
    || (!CAP_B2_FRAME_1492_1492_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B2_FRAME_1492_1492_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B2_FRAME_1492_1492_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B2_FRAME_1492_1492_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_02.dbc, frame frame_1492 (1492, 0x5d4): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1401 (1401, 0x579)
    on bus B2.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B2_FRAME_1401_1401_CHECKSUM_LENGTH != 8               \
    || (!CAP_B2_FRAME_1401_1401_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B2_FRAME_1401_1401_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B2_FRAME_1401_1401_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B2_FRAME_1401_1401_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_02.dbc, frame frame_1401 (1401, 0x579): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1413 (1413, 0x585)
    on bus B2.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B2_FRAME_1413_1413_CHECKSUM_LENGTH != 8               \
    || (!CAP_B2_FRAME_1413_1413_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B2_FRAME_1413_1413_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B2_FRAME_1413_1413_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B2_FRAME_1413_1413_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_02.dbc, frame frame_1413 (1413, 0x585): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1185 (1185, 0x4a1)
    on bus B2.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B2_FRAME_1185_1185_CHECKSUM_LENGTH != 8               \
    || (!CAP_B2_FRAME_1185_1185_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B2_FRAME_1185_1185_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B2_FRAME_1185_1185_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B2_FRAME_1185_1185_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_02.dbc, frame frame_1185 (1185, 0x4a1): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_322 (322, 0x142)
    on bus B2.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B2_FRAME_322_322_CHECKSUM_LENGTH != 8               \
    || (!CAP_B2_FRAME_322_322_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B2_FRAME_322_322_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B2_FRAME_322_322_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B2_FRAME_322_322_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_02.dbc, frame frame_322 (322, 0x142): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1188 (1188, 0x4a4)
    on bus B2.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B2_FRAME_1188_1188_CHECKSUM_LENGTH != 8               \
    || (!CAP_B2_FRAME_1188_1188_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B2_FRAME_1188_1188_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B2_FRAME_1188_1188_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B2_FRAME_1188_1188_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_02.dbc, frame frame_1188 (1188, 0x4a4): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1340 (1340, 0x53c)
    on bus B2.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B2_FRAME_1340_1340_CHECKSUM_LENGTH != 8               \
    || (!CAP_B2_FRAME_1340_1340_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B2_FRAME_1340_1340_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B2_FRAME_1340_1340_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B2_FRAME_1340_1340_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_02.dbc, frame frame_1340 (1340, 0x53c): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1151 (1151, 0x47f)
    on bus B2.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B2_FRAME_1151_1151_CHECKSUM_LENGTH != 8               \
    || (!CAP_B2_FRAME_1151_1151_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B2_FRAME_1151_1151_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B2_FRAME_1151_1151_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B2_FRAME_1151_1151_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_02.dbc, frame frame_1151 (1151, 0x47f): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_2012 (2012, 0x7dc)
    on bus B2.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B2_FRAME_2012_2012_CHECKSUM_LENGTH != 8               \
    || (!CAP_B2_FRAME_2012_2012_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B2_FRAME_2012_2012_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B2_FRAME_2012_2012_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B2_FRAME_2012_2012_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_02.dbc, frame frame_2012 (2012, 0x7dc): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1041 (1041, 0x411)
    on bus B2.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B2_FRAME_1041_1041_CHECKSUM_LENGTH != 8               \
    || (!CAP_B2_FRAME_1041_1041_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B2_FRAME_1041_1041_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B2_FRAME_1041_1041_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B2_FRAME_1041_1041_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_02.dbc, frame frame_1041 (1041, 0x411): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_287 (287, 0x11f)
    on bus B2.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B2_FRAME_287_287_CHECKSUM_LENGTH != 8               \
    || (!CAP_B2_FRAME_287_287_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B2_FRAME_287_287_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B2_FRAME_287_287_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B2_FRAME_287_287_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_02.dbc, frame frame_287 (287, 0x11f): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_138 (138, 0x08a)
    on bus B2.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B2_FRAME_138_138_CHECKSUM_LENGTH != 8               \
    || (!CAP_B2_FRAME_138_138_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B2_FRAME_138_138_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B2_FRAME_138_138_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B2_FRAME_138_138_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_02.dbc, frame frame_138 (138, 0x08a): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1730 (1730, 0x6c2)
    on bus B2.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B2_FRAME_1730_1730_CHECKSUM_LENGTH != 8               \
    || (!CAP_B2_FRAME_1730_1730_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B2_FRAME_1730_1730_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B2_FRAME_1730_1730_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B2_FRAME_1730_1730_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_02.dbc, frame frame_1730 (1730, 0x6c2): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_937 (937, 0x3a9)
    on bus B2.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B2_FRAME_937_937_CHECKSUM_LENGTH != 8               \
    || (!CAP_B2_FRAME_937_937_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B2_FRAME_937_937_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B2_FRAME_937_937_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B2_FRAME_937_937_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_02.dbc, frame frame_937 (937, 0x3a9): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_490 (490, 0x1ea)
    on bus B2.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B2_FRAME_490_490_CHECKSUM_LENGTH != 8               \
    || (!CAP_B2_FRAME_490_490_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B2_FRAME_490_490_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B2_FRAME_490_490_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B2_FRAME_490_490_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_02.dbc, frame frame_490 (490, 0x1ea): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1827 (1827, 0x723)
    on bus B2.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B2_FRAME_1827_1827_CHECKSUM_LENGTH != 8               \
    || (!CAP_B2_FRAME_1827_1827_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B2_FRAME_1827_1827_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B2_FRAME_1827_1827_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B2_FRAME_1827_1827_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_02.dbc, frame frame_1827 (1827, 0x723): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1819 (1819, 0x71b)
    on bus B2.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B2_FRAME_1819_1819_CHECKSUM_LENGTH != 8               \
    || (!CAP_B2_FRAME_1819_1819_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B2_FRAME_1819_1819_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B2_FRAME_1819_1819_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B2_FRAME_1819_1819_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_02.dbc, frame frame_1819 (1819, 0x71b): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_46 (46, 0x02e)
    on bus B2.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B2_FRAME_46_46_CHECKSUM_LENGTH != 8               \
    || (!CAP_B2_FRAME_46_46_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B2_FRAME_46_46_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B2_FRAME_46_46_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B2_FRAME_46_46_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_02.dbc, frame frame_46 (46, 0x02e): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1255 (1255, 0x4e7)
    on bus B2.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B2_FRAME_1255_1255_CHECKSUM_LENGTH != 8               \
    || (!CAP_B2_FRAME_1255_1255_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B2_FRAME_1255_1255_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B2_FRAME_1255_1255_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B2_FRAME_1255_1255_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_02.dbc, frame frame_1255 (1255, 0x4e7): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1036 (1036, 0x40c)
    on bus B2.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B2_FRAME_1036_1036_CHECKSUM_LENGTH != 8               \
    || (!CAP_B2_FRAME_1036_1036_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B2_FRAME_1036_1036_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B2_FRAME_1036_1036_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B2_FRAME_1036_1036_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_02.dbc, frame frame_1036 (1036, 0x40c): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1939 (1939, 0x793)
    on bus B2.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B2_FRAME_1939_1939_CHECKSUM_LENGTH != 8               \
    || (!CAP_B2_FRAME_1939_1939_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B2_FRAME_1939_1939_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B2_FRAME_1939_1939_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B2_FRAME_1939_1939_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_02.dbc, frame frame_1939 (1939, 0x793): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_922 (922, 0x39a)
    on bus B2.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B2_FRAME_922_922_CHECKSUM_LENGTH != 8               \
    || (!CAP_B2_FRAME_922_922_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B2_FRAME_922_922_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B2_FRAME_922_922_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B2_FRAME_922_922_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_02.dbc, frame frame_922 (922, 0x39a): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_759 (759, 0x2f7)
    on bus B2.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B2_FRAME_759_759_CHECKSUM_LENGTH != 8               \
    || (!CAP_B2_FRAME_759_759_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B2_FRAME_759_759_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B2_FRAME_759_759_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B2_FRAME_759_759_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_02.dbc, frame frame_759 (759, 0x2f7): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_88 (88, 0x058)
    on bus B2.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B2_FRAME_88_88_CHECKSUM_LENGTH != 8               \
    || (!CAP_B2_FRAME_88_88_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B2_FRAME_88_88_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B2_FRAME_88_88_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B2_FRAME_88_88_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_02.dbc, frame frame_88 (88, 0x058): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_162 (162, 0x0a2)
    on bus B2.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B2_FRAME_162_162_CHECKSUM_LENGTH != 8               \
    || (!CAP_B2_FRAME_162_162_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B2_FRAME_162_162_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B2_FRAME_162_162_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B2_FRAME_162_162_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_02.dbc, frame frame_162 (162, 0x0a2): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_659 (659, 0x293)
    on bus B2.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B2_FRAME_659_659_CHECKSUM_LENGTH != 8               \
    || (!CAP_B2_FRAME_659_659_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B2_FRAME_659_659_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B2_FRAME_659_659_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B2_FRAME_659_659_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_02.dbc, frame frame_659 (659, 0x293): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_495 (495, 0x1ef)
    on bus B2.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B2_FRAME_495_495_CHECKSUM_LENGTH != 8               \
    || (!CAP_B2_FRAME_495_495_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B2_FRAME_495_495_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B2_FRAME_495_495_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B2_FRAME_495_495_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_02.dbc, frame frame_495 (495, 0x1ef): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_563 (563, 0x233)
    on bus B2.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B2_FRAME_563_563_CHECKSUM_LENGTH != 8               \
    || (!CAP_B2_FRAME_563_563_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B2_FRAME_563_563_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B2_FRAME_563_563_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B2_FRAME_563_563_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_02.dbc, frame frame_563 (563, 0x233): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1888 (1888, 0x760)
    on bus B2.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B2_FRAME_1888_1888_CHECKSUM_LENGTH != 8               \
    || (!CAP_B2_FRAME_1888_1888_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B2_FRAME_1888_1888_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B2_FRAME_1888_1888_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B2_FRAME_1888_1888_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_02.dbc, frame frame_1888 (1888, 0x760): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_981 (981, 0x3d5)
    on bus B2.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B2_FRAME_981_981_CHECKSUM_LENGTH != 8               \
    || (!CAP_B2_FRAME_981_981_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B2_FRAME_981_981_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B2_FRAME_981_981_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B2_FRAME_981_981_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_02.dbc, frame frame_981 (981, 0x3d5): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_708 (708, 0x2c4)
    on bus B2.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B2_FRAME_708_708_CHECKSUM_LENGTH != 8               \
    || (!CAP_B2_FRAME_708_708_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B2_FRAME_708_708_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B2_FRAME_708_708_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B2_FRAME_708_708_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_02.dbc, frame frame_708 (708, 0x2c4): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1382 (1382, 0x566)
    on bus B2.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B2_FRAME_1382_1382_CHECKSUM_LENGTH != 8               \
    || (!CAP_B2_FRAME_1382_1382_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B2_FRAME_1382_1382_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B2_FRAME_1382_1382_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B2_FRAME_1382_1382_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_02.dbc, frame frame_1382 (1382, 0x566): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1345 (1345, 0x541)
    on bus B2.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B2_FRAME_1345_1345_CHECKSUM_LENGTH != 8               \
    || (!CAP_B2_FRAME_1345_1345_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B2_FRAME_1345_1345_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B2_FRAME_1345_1345_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B2_FRAME_1345_1345_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_02.dbc, frame frame_1345 (1345, 0x541): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1618 (1618, 0x652)
    on bus B2.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B2_FRAME_1618_1618_CHECKSUM_LENGTH != 8               \
    || (!CAP_B2_FRAME_1618_1618_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B2_FRAME_1618_1618_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B2_FRAME_1618_1618_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B2_FRAME_1618_1618_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_02.dbc, frame frame_1618 (1618, 0x652): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1956 (1956, 0x7a4)
    on bus B2.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B2_FRAME_1956_1956_CHECKSUM_LENGTH != 8               \
    || (!CAP_B2_FRAME_1956_1956_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B2_FRAME_1956_1956_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B2_FRAME_1956_1956_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B2_FRAME_1956_1956_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_02.dbc, frame frame_1956 (1956, 0x7a4): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_497 (497, 0x1f1)
    on bus B2.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B2_FRAME_497_497_CHECKSUM_LENGTH != 8               \
    || (!CAP_B2_FRAME_497_497_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B2_FRAME_497_497_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B2_FRAME_497_497_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B2_FRAME_497_497_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_02.dbc, frame frame_497 (497, 0x1f1): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_463 (463, 0x1cf)
    on bus B2.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B2_FRAME_463_463_CHECKSUM_LENGTH != 8               \
    || (!CAP_B2_FRAME_463_463_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B2_FRAME_463_463_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B2_FRAME_463_463_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B2_FRAME_463_463_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_02.dbc, frame frame_463 (463, 0x1cf): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_954 (954, 0x3ba)
    on bus B2.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B2_FRAME_954_954_CHECKSUM_LENGTH != 8               \
    || (!CAP_B2_FRAME_954_954_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B2_FRAME_954_954_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B2_FRAME_954_954_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B2_FRAME_954_954_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_02.dbc, frame frame_954 (954, 0x3ba): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1514 (1514, 0x5ea)
    on bus B2.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B2_FRAME_1514_1514_CHECKSUM_LENGTH != 8               \
    || (!CAP_B2_FRAME_1514_1514_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B2_FRAME_1514_1514_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B2_FRAME_1514_1514_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B2_FRAME_1514_1514_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_02.dbc, frame frame_1514 (1514, 0x5ea): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_92 (92, 0x05c)
    on bus B2.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B2_FRAME_92_92_CHECKSUM_LENGTH != 8               \
    || (!CAP_B2_FRAME_92_92_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B2_FRAME_92_92_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B2_FRAME_92_92_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B2_FRAME_92_92_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_02.dbc, frame frame_92 (92, 0x05c): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1350 (1350, 0x546)
    on bus B2.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B2_FRAME_1350_1350_CHECKSUM_LENGTH != 8               \
    || (!CAP_B2_FRAME_1350_1350_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B2_FRAME_1350_1350_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B2_FRAME_1350_1350_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B2_FRAME_1350_1350_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_02.dbc, frame frame_1350 (1350, 0x546): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1126 (1126, 0x466)
    on bus B2.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B2_FRAME_1126_1126_CHECKSUM_LENGTH != 8               \
    || (!CAP_B2_FRAME_1126_1126_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B2_FRAME_1126_1126_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B2_FRAME_1126_1126_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B2_FRAME_1126_1126_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_02.dbc, frame frame_1126 (1126, 0x466): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1347 (1347, 0x543)
    on bus B2.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B2_FRAME_1347_1347_CHECKSUM_LENGTH != 8               \
    || (!CAP_B2_FRAME_1347_1347_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B2_FRAME_1347_1347_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B2_FRAME_1347_1347_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B2_FRAME_1347_1347_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_02.dbc, frame frame_1347 (1347, 0x543): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_31 (31, 0x01f)
    on bus B2.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B2_FRAME_31_31_CHECKSUM_LENGTH != 8               \
    || (!CAP_B2_FRAME_31_31_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B2_FRAME_31_31_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B2_FRAME_31_31_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B2_FRAME_31_31_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_02.dbc, frame frame_31 (31, 0x01f): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1694 (1694, 0x69e)
    on bus B2.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B2_FRAME_1694_1694_CHECKSUM_LENGTH != 8               \
    || (!CAP_B2_FRAME_1694_1694_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B2_FRAME_1694_1694_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B2_FRAME_1694_1694_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B2_FRAME_1694_1694_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_02.dbc, frame frame_1694 (1694, 0x69e): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_725 (725, 0x2d5)
    on bus B2.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B2_FRAME_725_725_CHECKSUM_LENGTH != 8               \
    || (!CAP_B2_FRAME_725_725_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B2_FRAME_725_725_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B2_FRAME_725_725_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B2_FRAME_725_725_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_02.dbc, frame frame_725 (725, 0x2d5): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_729 (729, 0x2d9)
    on bus B2.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B2_FRAME_729_729_CHECKSUM_LENGTH != 8               \
    || (!CAP_B2_FRAME_729_729_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B2_FRAME_729_729_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B2_FRAME_729_729_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B2_FRAME_729_729_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_02.dbc, frame frame_729 (729, 0x2d9): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_429 (429, 0x1ad)
    on bus B2.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B2_FRAME_429_429_CHECKSUM_LENGTH != 8               \
    || (!CAP_B2_FRAME_429_429_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B2_FRAME_429_429_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B2_FRAME_429_429_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B2_FRAME_429_429_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_02.dbc, frame frame_429 (429, 0x1ad): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_633 (633, 0x279)
    on bus B2.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B2_FRAME_633_633_CHECKSUM_LENGTH != 8               \
    || (!CAP_B2_FRAME_633_633_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B2_FRAME_633_633_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B2_FRAME_633_633_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B2_FRAME_633_633_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_02.dbc, frame frame_633 (633, 0x279): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_2045 (2045, 0x7fd)
    on bus B2.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B2_FRAME_2045_2045_CHECKSUM_LENGTH != 8               \
    || (!CAP_B2_FRAME_2045_2045_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B2_FRAME_2045_2045_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B2_FRAME_2045_2045_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B2_FRAME_2045_2045_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_02.dbc, frame frame_2045 (2045, 0x7fd): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1005 (1005, 0x3ed)
    on bus B2.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B2_FRAME_1005_1005_CHECKSUM_LENGTH != 8               \
    || (!CAP_B2_FRAME_1005_1005_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B2_FRAME_1005_1005_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B2_FRAME_1005_1005_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B2_FRAME_1005_1005_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_02.dbc, frame frame_1005 (1005, 0x3ed): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1794 (1794, 0x702)
    on bus B2.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B2_FRAME_1794_1794_CHECKSUM_LENGTH != 8               \
    || (!CAP_B2_FRAME_1794_1794_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B2_FRAME_1794_1794_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B2_FRAME_1794_1794_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B2_FRAME_1794_1794_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_02.dbc, frame frame_1794 (1794, 0x702): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1901 (1901, 0x76d)
    on bus B2.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B2_FRAME_1901_1901_CHECKSUM_LENGTH != 8               \
    || (!CAP_B2_FRAME_1901_1901_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B2_FRAME_1901_1901_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B2_FRAME_1901_1901_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B2_FRAME_1901_1901_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_02.dbc, frame frame_1901 (1901, 0x76d): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1010 (1010, 0x3f2)
    on bus B2.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B2_FRAME_1010_1010_CHECKSUM_LENGTH != 8               \
    || (!CAP_B2_FRAME_1010_1010_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B2_FRAME_1010_1010_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B2_FRAME_1010_1010_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B2_FRAME_1010_1010_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_02.dbc, frame frame_1010 (1010, 0x3f2): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_381 (381, 0x17d)
    on bus B2.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B2_FRAME_381_381_CHECKSUM_LENGTH != 8               \
    || (!CAP_B2_FRAME_381_381_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B2_FRAME_381_381_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B2_FRAME_381_381_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B2_FRAME_381_381_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_02.dbc, frame frame_381 (381, 0x17d): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_796 (796, 0x31c)
    on bus B2.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B2_FRAME_796_796_CHECKSUM_LENGTH != 8               \
    || (!CAP_B2_FRAME_796_796_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B2_FRAME_796_796_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B2_FRAME_796_796_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B2_FRAME_796_796_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_02.dbc, frame frame_796 (796, 0x31c): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_260 (260, 0x104)
    on bus B2.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B2_FRAME_260_260_CHECKSUM_LENGTH != 8               \
    || (!CAP_B2_FRAME_260_260_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B2_FRAME_260_260_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B2_FRAME_260_260_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B2_FRAME_260_260_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_02.dbc, frame frame_260 (260, 0x104): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1337 (1337, 0x539)
    on bus B2.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B2_FRAME_1337_1337_CHECKSUM_LENGTH != 8               \
    || (!CAP_B2_FRAME_1337_1337_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B2_FRAME_1337_1337_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B2_FRAME_1337_1337_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B2_FRAME_1337_1337_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_02.dbc, frame frame_1337 (1337, 0x539): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1652 (1652, 0x674)
    on bus B2.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B2_FRAME_1652_1652_CHECKSUM_LENGTH != 8               \
    || (!CAP_B2_FRAME_1652_1652_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B2_FRAME_1652_1652_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B2_FRAME_1652_1652_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B2_FRAME_1652_1652_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_02.dbc, frame frame_1652 (1652, 0x674): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1442 (1442, 0x5a2)
    on bus B2.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B2_FRAME_1442_1442_CHECKSUM_LENGTH != 8               \
    || (!CAP_B2_FRAME_1442_1442_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B2_FRAME_1442_1442_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B2_FRAME_1442_1442_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B2_FRAME_1442_1442_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_02.dbc, frame frame_1442 (1442, 0x5a2): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1519 (1519, 0x5ef)
    on bus B3.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B3_FRAME_1519_1519_CHECKSUM_LENGTH != 8               \
    || (!CAP_B3_FRAME_1519_1519_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B3_FRAME_1519_1519_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B3_FRAME_1519_1519_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B3_FRAME_1519_1519_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_03.dbc, frame frame_1519 (1519, 0x5ef): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_661 (661, 0x295)
    on bus B3.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B3_FRAME_661_661_CHECKSUM_LENGTH != 8               \
    || (!CAP_B3_FRAME_661_661_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B3_FRAME_661_661_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B3_FRAME_661_661_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B3_FRAME_661_661_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_03.dbc, frame frame_661 (661, 0x295): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1084 (1084, 0x43c)
    on bus B3.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B3_FRAME_1084_1084_CHECKSUM_LENGTH != 8               \
    || (!CAP_B3_FRAME_1084_1084_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B3_FRAME_1084_1084_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B3_FRAME_1084_1084_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B3_FRAME_1084_1084_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_03.dbc, frame frame_1084 (1084, 0x43c): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_888 (888, 0x378)
    on bus B3.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B3_FRAME_888_888_CHECKSUM_LENGTH != 8               \
    || (!CAP_B3_FRAME_888_888_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B3_FRAME_888_888_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B3_FRAME_888_888_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B3_FRAME_888_888_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_03.dbc, frame frame_888 (888, 0x378): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1170 (1170, 0x492)
    on bus B3.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B3_FRAME_1170_1170_CHECKSUM_LENGTH != 8               \
    || (!CAP_B3_FRAME_1170_1170_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B3_FRAME_1170_1170_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B3_FRAME_1170_1170_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B3_FRAME_1170_1170_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_03.dbc, frame frame_1170 (1170, 0x492): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1320 (1320, 0x528)
    on bus B3.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B3_FRAME_1320_1320_CHECKSUM_LENGTH != 8               \
    || (!CAP_B3_FRAME_1320_1320_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B3_FRAME_1320_1320_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B3_FRAME_1320_1320_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B3_FRAME_1320_1320_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_03.dbc, frame frame_1320 (1320, 0x528): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1696 (1696, 0x6a0)
    on bus B3.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B3_FRAME_1696_1696_CHECKSUM_LENGTH != 8               \
    || (!CAP_B3_FRAME_1696_1696_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B3_FRAME_1696_1696_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B3_FRAME_1696_1696_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B3_FRAME_1696_1696_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_03.dbc, frame frame_1696 (1696, 0x6a0): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1162 (1162, 0x48a)
    on bus B3.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B3_FRAME_1162_1162_CHECKSUM_LENGTH != 8               \
    || (!CAP_B3_FRAME_1162_1162_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B3_FRAME_1162_1162_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B3_FRAME_1162_1162_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B3_FRAME_1162_1162_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_03.dbc, frame frame_1162 (1162, 0x48a): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1398 (1398, 0x576)
    on bus B3.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B3_FRAME_1398_1398_CHECKSUM_LENGTH != 8               \
    || (!CAP_B3_FRAME_1398_1398_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B3_FRAME_1398_1398_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B3_FRAME_1398_1398_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B3_FRAME_1398_1398_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_03.dbc, frame frame_1398 (1398, 0x576): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_187 (187, 0x0bb)
    on bus B3.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B3_FRAME_187_187_CHECKSUM_LENGTH != 8               \
    || (!CAP_B3_FRAME_187_187_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B3_FRAME_187_187_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B3_FRAME_187_187_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B3_FRAME_187_187_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_03.dbc, frame frame_187 (187, 0x0bb): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_428 (428, 0x1ac)
    on bus B3.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B3_FRAME_428_428_CHECKSUM_LENGTH != 8               \
    || (!CAP_B3_FRAME_428_428_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B3_FRAME_428_428_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B3_FRAME_428_428_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B3_FRAME_428_428_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_03.dbc, frame frame_428 (428, 0x1ac): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1425 (1425, 0x591)
    on bus B3.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B3_FRAME_1425_1425_CHECKSUM_LENGTH != 8               \
    || (!CAP_B3_FRAME_1425_1425_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B3_FRAME_1425_1425_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B3_FRAME_1425_1425_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B3_FRAME_1425_1425_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_03.dbc, frame frame_1425 (1425, 0x591): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1217 (1217, 0x4c1)
    on bus B3.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B3_FRAME_1217_1217_CHECKSUM_LENGTH != 8               \
    || (!CAP_B3_FRAME_1217_1217_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B3_FRAME_1217_1217_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B3_FRAME_1217_1217_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B3_FRAME_1217_1217_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_03.dbc, frame frame_1217 (1217, 0x4c1): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_456 (456, 0x1c8)
    on bus B3.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B3_FRAME_456_456_CHECKSUM_LENGTH != 8               \
    || (!CAP_B3_FRAME_456_456_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B3_FRAME_456_456_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B3_FRAME_456_456_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B3_FRAME_456_456_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_03.dbc, frame frame_456 (456, 0x1c8): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1627 (1627, 0x65b)
    on bus B3.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B3_FRAME_1627_1627_CHECKSUM_LENGTH != 8               \
    || (!CAP_B3_FRAME_1627_1627_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B3_FRAME_1627_1627_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B3_FRAME_1627_1627_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B3_FRAME_1627_1627_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_03.dbc, frame frame_1627 (1627, 0x65b): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_804 (804, 0x324)
    on bus B3.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B3_FRAME_804_804_CHECKSUM_LENGTH != 8               \
    || (!CAP_B3_FRAME_804_804_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B3_FRAME_804_804_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B3_FRAME_804_804_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B3_FRAME_804_804_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_03.dbc, frame frame_804 (804, 0x324): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1154 (1154, 0x482)
    on bus B3.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B3_FRAME_1154_1154_CHECKSUM_LENGTH != 8               \
    || (!CAP_B3_FRAME_1154_1154_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B3_FRAME_1154_1154_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B3_FRAME_1154_1154_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B3_FRAME_1154_1154_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_03.dbc, frame frame_1154 (1154, 0x482): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1404 (1404, 0x57c)
    on bus B3.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B3_FRAME_1404_1404_CHECKSUM_LENGTH != 8               \
    || (!CAP_B3_FRAME_1404_1404_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B3_FRAME_1404_1404_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B3_FRAME_1404_1404_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B3_FRAME_1404_1404_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_03.dbc, frame frame_1404 (1404, 0x57c): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_259 (259, 0x103)
    on bus B3.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B3_FRAME_259_259_CHECKSUM_LENGTH != 8               \
    || (!CAP_B3_FRAME_259_259_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B3_FRAME_259_259_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B3_FRAME_259_259_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B3_FRAME_259_259_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_03.dbc, frame frame_259 (259, 0x103): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1374 (1374, 0x55e)
    on bus B3.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B3_FRAME_1374_1374_CHECKSUM_LENGTH != 8               \
    || (!CAP_B3_FRAME_1374_1374_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B3_FRAME_1374_1374_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B3_FRAME_1374_1374_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B3_FRAME_1374_1374_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_03.dbc, frame frame_1374 (1374, 0x55e): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_820 (820, 0x334)
    on bus B3.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B3_FRAME_820_820_CHECKSUM_LENGTH != 8               \
    || (!CAP_B3_FRAME_820_820_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B3_FRAME_820_820_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B3_FRAME_820_820_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B3_FRAME_820_820_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_03.dbc, frame frame_820 (820, 0x334): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1433 (1433, 0x599)
    on bus B3.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B3_FRAME_1433_1433_CHECKSUM_LENGTH != 8               \
    || (!CAP_B3_FRAME_1433_1433_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B3_FRAME_1433_1433_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B3_FRAME_1433_1433_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B3_FRAME_1433_1433_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_03.dbc, frame frame_1433 (1433, 0x599): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1820 (1820, 0x71c)
    on bus B3.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B3_FRAME_1820_1820_CHECKSUM_LENGTH != 8               \
    || (!CAP_B3_FRAME_1820_1820_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B3_FRAME_1820_1820_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B3_FRAME_1820_1820_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B3_FRAME_1820_1820_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_03.dbc, frame frame_1820 (1820, 0x71c): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1909 (1909, 0x775)
    on bus B3.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B3_FRAME_1909_1909_CHECKSUM_LENGTH != 8               \
    || (!CAP_B3_FRAME_1909_1909_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B3_FRAME_1909_1909_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B3_FRAME_1909_1909_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B3_FRAME_1909_1909_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_03.dbc, frame frame_1909 (1909, 0x775): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1713 (1713, 0x6b1)
    on bus B3.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B3_FRAME_1713_1713_CHECKSUM_LENGTH != 8               \
    || (!CAP_B3_FRAME_1713_1713_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B3_FRAME_1713_1713_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B3_FRAME_1713_1713_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B3_FRAME_1713_1713_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_03.dbc, frame frame_1713 (1713, 0x6b1): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1318 (1318, 0x526)
    on bus B3.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B3_FRAME_1318_1318_CHECKSUM_LENGTH != 8               \
    || (!CAP_B3_FRAME_1318_1318_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B3_FRAME_1318_1318_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B3_FRAME_1318_1318_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B3_FRAME_1318_1318_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_03.dbc, frame frame_1318 (1318, 0x526): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1068 (1068, 0x42c)
    on bus B3.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B3_FRAME_1068_1068_CHECKSUM_LENGTH != 8               \
    || (!CAP_B3_FRAME_1068_1068_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B3_FRAME_1068_1068_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B3_FRAME_1068_1068_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B3_FRAME_1068_1068_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_03.dbc, frame frame_1068 (1068, 0x42c): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1670 (1670, 0x686)
    on bus B3.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B3_FRAME_1670_1670_CHECKSUM_LENGTH != 8               \
    || (!CAP_B3_FRAME_1670_1670_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B3_FRAME_1670_1670_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B3_FRAME_1670_1670_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B3_FRAME_1670_1670_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_03.dbc, frame frame_1670 (1670, 0x686): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1300 (1300, 0x514)
    on bus B3.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B3_FRAME_1300_1300_CHECKSUM_LENGTH != 8               \
    || (!CAP_B3_FRAME_1300_1300_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B3_FRAME_1300_1300_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B3_FRAME_1300_1300_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B3_FRAME_1300_1300_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_03.dbc, frame frame_1300 (1300, 0x514): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1446 (1446, 0x5a6)
    on bus B3.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B3_FRAME_1446_1446_CHECKSUM_LENGTH != 8               \
    || (!CAP_B3_FRAME_1446_1446_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B3_FRAME_1446_1446_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B3_FRAME_1446_1446_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B3_FRAME_1446_1446_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_03.dbc, frame frame_1446 (1446, 0x5a6): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_144 (144, 0x090)
    on bus B3.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B3_FRAME_144_144_CHECKSUM_LENGTH != 8               \
    || (!CAP_B3_FRAME_144_144_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B3_FRAME_144_144_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B3_FRAME_144_144_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B3_FRAME_144_144_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_03.dbc, frame frame_144 (144, 0x090): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1029 (1029, 0x405)
    on bus B3.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B3_FRAME_1029_1029_CHECKSUM_LENGTH != 8               \
    || (!CAP_B3_FRAME_1029_1029_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B3_FRAME_1029_1029_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B3_FRAME_1029_1029_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B3_FRAME_1029_1029_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_03.dbc, frame frame_1029 (1029, 0x405): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_23 (23, 0x017)
    on bus B3.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B3_FRAME_23_23_CHECKSUM_LENGTH != 8               \
    || (!CAP_B3_FRAME_23_23_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B3_FRAME_23_23_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B3_FRAME_23_23_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B3_FRAME_23_23_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_03.dbc, frame frame_23 (23, 0x017): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1485 (1485, 0x5cd)
    on bus B3.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B3_FRAME_1485_1485_CHECKSUM_LENGTH != 8               \
    || (!CAP_B3_FRAME_1485_1485_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B3_FRAME_1485_1485_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B3_FRAME_1485_1485_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B3_FRAME_1485_1485_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_03.dbc, frame frame_1485 (1485, 0x5cd): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1262 (1262, 0x4ee)
    on bus B3.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B3_FRAME_1262_1262_CHECKSUM_LENGTH != 8               \
    || (!CAP_B3_FRAME_1262_1262_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B3_FRAME_1262_1262_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B3_FRAME_1262_1262_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B3_FRAME_1262_1262_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_03.dbc, frame frame_1262 (1262, 0x4ee): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1512 (1512, 0x5e8)
    on bus B3.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B3_FRAME_1512_1512_CHECKSUM_LENGTH != 8               \
    || (!CAP_B3_FRAME_1512_1512_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B3_FRAME_1512_1512_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B3_FRAME_1512_1512_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B3_FRAME_1512_1512_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_03.dbc, frame frame_1512 (1512, 0x5e8): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_912 (912, 0x390)
    on bus B3.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B3_FRAME_912_912_CHECKSUM_LENGTH != 8               \
    || (!CAP_B3_FRAME_912_912_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B3_FRAME_912_912_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B3_FRAME_912_912_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B3_FRAME_912_912_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_03.dbc, frame frame_912 (912, 0x390): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1979 (1979, 0x7bb)
    on bus B3.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B3_FRAME_1979_1979_CHECKSUM_LENGTH != 8               \
    || (!CAP_B3_FRAME_1979_1979_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B3_FRAME_1979_1979_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B3_FRAME_1979_1979_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B3_FRAME_1979_1979_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_03.dbc, frame frame_1979 (1979, 0x7bb): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1856 (1856, 0x740)
    on bus B3.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B3_FRAME_1856_1856_CHECKSUM_LENGTH != 8               \
    || (!CAP_B3_FRAME_1856_1856_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B3_FRAME_1856_1856_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B3_FRAME_1856_1856_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B3_FRAME_1856_1856_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_03.dbc, frame frame_1856 (1856, 0x740): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_74 (74, 0x04a)
    on bus B3.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B3_FRAME_74_74_CHECKSUM_LENGTH != 8               \
    || (!CAP_B3_FRAME_74_74_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B3_FRAME_74_74_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B3_FRAME_74_74_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B3_FRAME_74_74_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_03.dbc, frame frame_74 (74, 0x04a): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1779 (1779, 0x6f3)
    on bus B3.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B3_FRAME_1779_1779_CHECKSUM_LENGTH != 8               \
    || (!CAP_B3_FRAME_1779_1779_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B3_FRAME_1779_1779_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B3_FRAME_1779_1779_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B3_FRAME_1779_1779_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_03.dbc, frame frame_1779 (1779, 0x6f3): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1385 (1385, 0x569)
    on bus B3.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B3_FRAME_1385_1385_CHECKSUM_LENGTH != 8               \
    || (!CAP_B3_FRAME_1385_1385_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B3_FRAME_1385_1385_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B3_FRAME_1385_1385_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B3_FRAME_1385_1385_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_03.dbc, frame frame_1385 (1385, 0x569): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_425 (425, 0x1a9)
    on bus B3.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B3_FRAME_425_425_CHECKSUM_LENGTH != 8               \
    || (!CAP_B3_FRAME_425_425_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B3_FRAME_425_425_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B3_FRAME_425_425_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B3_FRAME_425_425_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_03.dbc, frame frame_425 (425, 0x1a9): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1697 (1697, 0x6a1)
    on bus B3.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B3_FRAME_1697_1697_CHECKSUM_LENGTH != 8               \
    || (!CAP_B3_FRAME_1697_1697_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B3_FRAME_1697_1697_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B3_FRAME_1697_1697_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B3_FRAME_1697_1697_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_03.dbc, frame frame_1697 (1697, 0x6a1): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_2017 (2017, 0x7e1)
    on bus B3.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B3_FRAME_2017_2017_CHECKSUM_LENGTH != 8               \
    || (!CAP_B3_FRAME_2017_2017_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B3_FRAME_2017_2017_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B3_FRAME_2017_2017_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B3_FRAME_2017_2017_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_03.dbc, frame frame_2017 (2017, 0x7e1): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_378 (378, 0x17a)
    on bus B3.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B3_FRAME_378_378_CHECKSUM_LENGTH != 8               \
    || (!CAP_B3_FRAME_378_378_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B3_FRAME_378_378_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B3_FRAME_378_378_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B3_FRAME_378_378_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_03.dbc, frame frame_378 (378, 0x17a): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_814 (814, 0x32e)
    on bus B3.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B3_FRAME_814_814_CHECKSUM_LENGTH != 8               \
    || (!CAP_B3_FRAME_814_814_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B3_FRAME_814_814_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B3_FRAME_814_814_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B3_FRAME_814_814_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_03.dbc, frame frame_814 (814, 0x32e): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_929 (929, 0x3a1)
    on bus B3.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B3_FRAME_929_929_CHECKSUM_LENGTH != 8               \
    || (!CAP_B3_FRAME_929_929_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B3_FRAME_929_929_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B3_FRAME_929_929_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B3_FRAME_929_929_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_03.dbc, frame frame_929 (929, 0x3a1): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1661 (1661, 0x67d)
    on bus B3.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B3_FRAME_1661_1661_CHECKSUM_LENGTH != 8               \
    || (!CAP_B3_FRAME_1661_1661_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B3_FRAME_1661_1661_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B3_FRAME_1661_1661_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B3_FRAME_1661_1661_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_03.dbc, frame frame_1661 (1661, 0x67d): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1115 (1115, 0x45b)
    on bus B3.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B3_FRAME_1115_1115_CHECKSUM_LENGTH != 8               \
    || (!CAP_B3_FRAME_1115_1115_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B3_FRAME_1115_1115_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B3_FRAME_1115_1115_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B3_FRAME_1115_1115_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_03.dbc, frame frame_1115 (1115, 0x45b): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1540 (1540, 0x604)
    on bus B3.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B3_FRAME_1540_1540_CHECKSUM_LENGTH != 8               \
    || (!CAP_B3_FRAME_1540_1540_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B3_FRAME_1540_1540_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B3_FRAME_1540_1540_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B3_FRAME_1540_1540_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_03.dbc, frame frame_1540 (1540, 0x604): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1831 (1831, 0x727)
    on bus B3.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B3_FRAME_1831_1831_CHECKSUM_LENGTH != 8               \
    || (!CAP_B3_FRAME_1831_1831_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B3_FRAME_1831_1831_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B3_FRAME_1831_1831_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B3_FRAME_1831_1831_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_03.dbc, frame frame_1831 (1831, 0x727): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1978 (1978, 0x7ba)
    on bus B3.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B3_FRAME_1978_1978_CHECKSUM_LENGTH != 8               \
    || (!CAP_B3_FRAME_1978_1978_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B3_FRAME_1978_1978_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B3_FRAME_1978_1978_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B3_FRAME_1978_1978_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_03.dbc, frame frame_1978 (1978, 0x7ba): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1968 (1968, 0x7b0)
    on bus B3.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B3_FRAME_1968_1968_CHECKSUM_LENGTH != 8               \
    || (!CAP_B3_FRAME_1968_1968_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B3_FRAME_1968_1968_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B3_FRAME_1968_1968_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B3_FRAME_1968_1968_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_03.dbc, frame frame_1968 (1968, 0x7b0): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1795 (1795, 0x703)
    on bus B3.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B3_FRAME_1795_1795_CHECKSUM_LENGTH != 8               \
    || (!CAP_B3_FRAME_1795_1795_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B3_FRAME_1795_1795_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B3_FRAME_1795_1795_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B3_FRAME_1795_1795_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_03.dbc, frame frame_1795 (1795, 0x703): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_545 (545, 0x221)
    on bus B3.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B3_FRAME_545_545_CHECKSUM_LENGTH != 8               \
    || (!CAP_B3_FRAME_545_545_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B3_FRAME_545_545_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B3_FRAME_545_545_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B3_FRAME_545_545_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_03.dbc, frame frame_545 (545, 0x221): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_523 (523, 0x20b)
    on bus B3.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B3_FRAME_523_523_CHECKSUM_LENGTH != 8               \
    || (!CAP_B3_FRAME_523_523_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B3_FRAME_523_523_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B3_FRAME_523_523_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B3_FRAME_523_523_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_03.dbc, frame frame_523 (523, 0x20b): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1873 (1873, 0x751)
    on bus B3.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B3_FRAME_1873_1873_CHECKSUM_LENGTH != 8               \
    || (!CAP_B3_FRAME_1873_1873_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B3_FRAME_1873_1873_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B3_FRAME_1873_1873_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B3_FRAME_1873_1873_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_03.dbc, frame frame_1873 (1873, 0x751): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_807 (807, 0x327)
    on bus B3.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B3_FRAME_807_807_CHECKSUM_LENGTH != 8               \
    || (!CAP_B3_FRAME_807_807_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B3_FRAME_807_807_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B3_FRAME_807_807_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B3_FRAME_807_807_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_03.dbc, frame frame_807 (807, 0x327): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1637 (1637, 0x665)
    on bus B3.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B3_FRAME_1637_1637_CHECKSUM_LENGTH != 8               \
    || (!CAP_B3_FRAME_1637_1637_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B3_FRAME_1637_1637_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B3_FRAME_1637_1637_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B3_FRAME_1637_1637_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_03.dbc, frame frame_1637 (1637, 0x665): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1612 (1612, 0x64c)
    on bus B3.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B3_FRAME_1612_1612_CHECKSUM_LENGTH != 8               \
    || (!CAP_B3_FRAME_1612_1612_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B3_FRAME_1612_1612_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B3_FRAME_1612_1612_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B3_FRAME_1612_1612_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_03.dbc, frame frame_1612 (1612, 0x64c): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_214 (214, 0x0d6)
    on bus B3.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B3_FRAME_214_214_CHECKSUM_LENGTH != 8               \
    || (!CAP_B3_FRAME_214_214_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B3_FRAME_214_214_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B3_FRAME_214_214_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B3_FRAME_214_214_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_03.dbc, frame frame_214 (214, 0x0d6): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1784 (1784, 0x6f8)
    on bus B3.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B3_FRAME_1784_1784_CHECKSUM_LENGTH != 8               \
    || (!CAP_B3_FRAME_1784_1784_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B3_FRAME_1784_1784_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B3_FRAME_1784_1784_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B3_FRAME_1784_1784_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_03.dbc, frame frame_1784 (1784, 0x6f8): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_649 (649, 0x289)
    on bus B3.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B3_FRAME_649_649_CHECKSUM_LENGTH != 8               \
    || (!CAP_B3_FRAME_649_649_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B3_FRAME_649_649_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B3_FRAME_649_649_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B3_FRAME_649_649_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_03.dbc, frame frame_649 (649, 0x289): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_577 (577, 0x241)
    on bus B4.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B4_FRAME_577_577_CHECKSUM_LENGTH != 8               \
    || (!CAP_B4_FRAME_577_577_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B4_FRAME_577_577_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B4_FRAME_577_577_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B4_FRAME_577_577_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_04.dbc, frame frame_577 (577, 0x241): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_517 (517, 0x205)
    on bus B4.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B4_FRAME_517_517_CHECKSUM_LENGTH != 8               \
    || (!CAP_B4_FRAME_517_517_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B4_FRAME_517_517_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B4_FRAME_517_517_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B4_FRAME_517_517_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_04.dbc, frame frame_517 (517, 0x205): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1470 (1470, 0x5be)
    on bus B4.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B4_FRAME_1470_1470_CHECKSUM_LENGTH != 8               \
    || (!CAP_B4_FRAME_1470_1470_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B4_FRAME_1470_1470_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B4_FRAME_1470_1470_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B4_FRAME_1470_1470_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_04.dbc, frame frame_1470 (1470, 0x5be): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1189 (1189, 0x4a5)
    on bus B4.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B4_FRAME_1189_1189_CHECKSUM_LENGTH != 8               \
    || (!CAP_B4_FRAME_1189_1189_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B4_FRAME_1189_1189_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B4_FRAME_1189_1189_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B4_FRAME_1189_1189_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_04.dbc, frame frame_1189 (1189, 0x4a5): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1801 (1801, 0x709)
    on bus B4.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B4_FRAME_1801_1801_CHECKSUM_LENGTH != 8               \
    || (!CAP_B4_FRAME_1801_1801_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B4_FRAME_1801_1801_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B4_FRAME_1801_1801_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B4_FRAME_1801_1801_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_04.dbc, frame frame_1801 (1801, 0x709): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1926 (1926, 0x786)
    on bus B4.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B4_FRAME_1926_1926_CHECKSUM_LENGTH != 8               \
    || (!CAP_B4_FRAME_1926_1926_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B4_FRAME_1926_1926_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B4_FRAME_1926_1926_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B4_FRAME_1926_1926_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_04.dbc, frame frame_1926 (1926, 0x786): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_986 (986, 0x3da)
    on bus B4.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B4_FRAME_986_986_CHECKSUM_LENGTH != 8               \
    || (!CAP_B4_FRAME_986_986_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B4_FRAME_986_986_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B4_FRAME_986_986_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B4_FRAME_986_986_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_04.dbc, frame frame_986 (986, 0x3da): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_998 (998, 0x3e6)
    on bus B4.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B4_FRAME_998_998_CHECKSUM_LENGTH != 8               \
    || (!CAP_B4_FRAME_998_998_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B4_FRAME_998_998_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B4_FRAME_998_998_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B4_FRAME_998_998_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_04.dbc, frame frame_998 (998, 0x3e6): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_480 (480, 0x1e0)
    on bus B4.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B4_FRAME_480_480_CHECKSUM_LENGTH != 8               \
    || (!CAP_B4_FRAME_480_480_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B4_FRAME_480_480_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B4_FRAME_480_480_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B4_FRAME_480_480_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_04.dbc, frame frame_480 (480, 0x1e0): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_865 (865, 0x361)
    on bus B4.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B4_FRAME_865_865_CHECKSUM_LENGTH != 8               \
    || (!CAP_B4_FRAME_865_865_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B4_FRAME_865_865_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B4_FRAME_865_865_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B4_FRAME_865_865_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_04.dbc, frame frame_865 (865, 0x361): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_743 (743, 0x2e7)
    on bus B4.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B4_FRAME_743_743_CHECKSUM_LENGTH != 8               \
    || (!CAP_B4_FRAME_743_743_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B4_FRAME_743_743_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B4_FRAME_743_743_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B4_FRAME_743_743_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_04.dbc, frame frame_743 (743, 0x2e7): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1940 (1940, 0x794)
    on bus B4.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B4_FRAME_1940_1940_CHECKSUM_LENGTH != 8               \
    || (!CAP_B4_FRAME_1940_1940_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B4_FRAME_1940_1940_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B4_FRAME_1940_1940_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B4_FRAME_1940_1940_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_04.dbc, frame frame_1940 (1940, 0x794): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_764 (764, 0x2fc)
    on bus B4.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B4_FRAME_764_764_CHECKSUM_LENGTH != 8               \
    || (!CAP_B4_FRAME_764_764_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B4_FRAME_764_764_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B4_FRAME_764_764_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B4_FRAME_764_764_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_04.dbc, frame frame_764 (764, 0x2fc): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_907 (907, 0x38b)
    on bus B4.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B4_FRAME_907_907_CHECKSUM_LENGTH != 8               \
    || (!CAP_B4_FRAME_907_907_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B4_FRAME_907_907_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B4_FRAME_907_907_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B4_FRAME_907_907_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_04.dbc, frame frame_907 (907, 0x38b): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_366 (366, 0x16e)
    on bus B4.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B4_FRAME_366_366_CHECKSUM_LENGTH != 8               \
    || (!CAP_B4_FRAME_366_366_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B4_FRAME_366_366_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B4_FRAME_366_366_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B4_FRAME_366_366_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_04.dbc, frame frame_366 (366, 0x16e): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_2039 (2039, 0x7f7)
    on bus B4.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B4_FRAME_2039_2039_CHECKSUM_LENGTH != 8               \
    || (!CAP_B4_FRAME_2039_2039_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B4_FRAME_2039_2039_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B4_FRAME_2039_2039_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B4_FRAME_2039_2039_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_04.dbc, frame frame_2039 (2039, 0x7f7): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_411 (411, 0x19b)
    on bus B4.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B4_FRAME_411_411_CHECKSUM_LENGTH != 8               \
    || (!CAP_B4_FRAME_411_411_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B4_FRAME_411_411_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B4_FRAME_411_411_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B4_FRAME_411_411_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_04.dbc, frame frame_411 (411, 0x19b): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_376 (376, 0x178)
    on bus B4.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B4_FRAME_376_376_CHECKSUM_LENGTH != 8               \
    || (!CAP_B4_FRAME_376_376_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B4_FRAME_376_376_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B4_FRAME_376_376_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B4_FRAME_376_376_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_04.dbc, frame frame_376 (376, 0x178): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_655 (655, 0x28f)
    on bus B4.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B4_FRAME_655_655_CHECKSUM_LENGTH != 8               \
    || (!CAP_B4_FRAME_655_655_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B4_FRAME_655_655_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B4_FRAME_655_655_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B4_FRAME_655_655_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_04.dbc, frame frame_655 (655, 0x28f): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1985 (1985, 0x7c1)
    on bus B4.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B4_FRAME_1985_1985_CHECKSUM_LENGTH != 8               \
    || (!CAP_B4_FRAME_1985_1985_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B4_FRAME_1985_1985_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B4_FRAME_1985_1985_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B4_FRAME_1985_1985_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_04.dbc, frame frame_1985 (1985, 0x7c1): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1572 (1572, 0x624)
    on bus B4.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B4_FRAME_1572_1572_CHECKSUM_LENGTH != 8               \
    || (!CAP_B4_FRAME_1572_1572_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B4_FRAME_1572_1572_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B4_FRAME_1572_1572_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B4_FRAME_1572_1572_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_04.dbc, frame frame_1572 (1572, 0x624): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_253 (253, 0x0fd)
    on bus B4.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B4_FRAME_253_253_CHECKSUM_LENGTH != 8               \
    || (!CAP_B4_FRAME_253_253_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B4_FRAME_253_253_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B4_FRAME_253_253_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B4_FRAME_253_253_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_04.dbc, frame frame_253 (253, 0x0fd): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_866 (866, 0x362)
    on bus B4.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B4_FRAME_866_866_CHECKSUM_LENGTH != 8               \
    || (!CAP_B4_FRAME_866_866_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B4_FRAME_866_866_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B4_FRAME_866_866_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B4_FRAME_866_866_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_04.dbc, frame frame_866 (866, 0x362): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1332 (1332, 0x534)
    on bus B4.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B4_FRAME_1332_1332_CHECKSUM_LENGTH != 8               \
    || (!CAP_B4_FRAME_1332_1332_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B4_FRAME_1332_1332_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B4_FRAME_1332_1332_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B4_FRAME_1332_1332_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_04.dbc, frame frame_1332 (1332, 0x534): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_86 (86, 0x056)
    on bus B4.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B4_FRAME_86_86_CHECKSUM_LENGTH != 8               \
    || (!CAP_B4_FRAME_86_86_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B4_FRAME_86_86_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B4_FRAME_86_86_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B4_FRAME_86_86_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_04.dbc, frame frame_86 (86, 0x056): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1270 (1270, 0x4f6)
    on bus B4.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B4_FRAME_1270_1270_CHECKSUM_LENGTH != 8               \
    || (!CAP_B4_FRAME_1270_1270_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B4_FRAME_1270_1270_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B4_FRAME_1270_1270_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B4_FRAME_1270_1270_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_04.dbc, frame frame_1270 (1270, 0x4f6): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1002 (1002, 0x3ea)
    on bus B4.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B4_FRAME_1002_1002_CHECKSUM_LENGTH != 8               \
    || (!CAP_B4_FRAME_1002_1002_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B4_FRAME_1002_1002_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B4_FRAME_1002_1002_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B4_FRAME_1002_1002_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_04.dbc, frame frame_1002 (1002, 0x3ea): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1957 (1957, 0x7a5)
    on bus B4.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B4_FRAME_1957_1957_CHECKSUM_LENGTH != 8               \
    || (!CAP_B4_FRAME_1957_1957_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B4_FRAME_1957_1957_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B4_FRAME_1957_1957_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B4_FRAME_1957_1957_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_04.dbc, frame frame_1957 (1957, 0x7a5): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_969 (969, 0x3c9)
    on bus B4.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B4_FRAME_969_969_CHECKSUM_LENGTH != 8               \
    || (!CAP_B4_FRAME_969_969_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B4_FRAME_969_969_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B4_FRAME_969_969_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B4_FRAME_969_969_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_04.dbc, frame frame_969 (969, 0x3c9): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1631 (1631, 0x65f)
    on bus B4.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B4_FRAME_1631_1631_CHECKSUM_LENGTH != 8               \
    || (!CAP_B4_FRAME_1631_1631_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B4_FRAME_1631_1631_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B4_FRAME_1631_1631_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B4_FRAME_1631_1631_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_04.dbc, frame frame_1631 (1631, 0x65f): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_823 (823, 0x337)
    on bus B4.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B4_FRAME_823_823_CHECKSUM_LENGTH != 8               \
    || (!CAP_B4_FRAME_823_823_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B4_FRAME_823_823_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B4_FRAME_823_823_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B4_FRAME_823_823_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_04.dbc, frame frame_823 (823, 0x337): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_83 (83, 0x053)
    on bus B4.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B4_FRAME_83_83_CHECKSUM_LENGTH != 8               \
    || (!CAP_B4_FRAME_83_83_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B4_FRAME_83_83_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B4_FRAME_83_83_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B4_FRAME_83_83_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_04.dbc, frame frame_83 (83, 0x053): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_481 (481, 0x1e1)
    on bus B4.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B4_FRAME_481_481_CHECKSUM_LENGTH != 8               \
    || (!CAP_B4_FRAME_481_481_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B4_FRAME_481_481_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B4_FRAME_481_481_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B4_FRAME_481_481_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_04.dbc, frame frame_481 (481, 0x1e1): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_739 (739, 0x2e3)
    on bus B4.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B4_FRAME_739_739_CHECKSUM_LENGTH != 8               \
    || (!CAP_B4_FRAME_739_739_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B4_FRAME_739_739_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B4_FRAME_739_739_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B4_FRAME_739_739_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_04.dbc, frame frame_739 (739, 0x2e3): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_65 (65, 0x041)
    on bus B4.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B4_FRAME_65_65_CHECKSUM_LENGTH != 8               \
    || (!CAP_B4_FRAME_65_65_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B4_FRAME_65_65_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B4_FRAME_65_65_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B4_FRAME_65_65_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_04.dbc, frame frame_65 (65, 0x041): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1776 (1776, 0x6f0)
    on bus B4.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B4_FRAME_1776_1776_CHECKSUM_LENGTH != 8               \
    || (!CAP_B4_FRAME_1776_1776_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B4_FRAME_1776_1776_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B4_FRAME_1776_1776_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B4_FRAME_1776_1776_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_04.dbc, frame frame_1776 (1776, 0x6f0): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_11 (11, 0x00b)
    on bus B4.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B4_FRAME_11_11_CHECKSUM_LENGTH != 8               \
    || (!CAP_B4_FRAME_11_11_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B4_FRAME_11_11_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B4_FRAME_11_11_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B4_FRAME_11_11_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_04.dbc, frame frame_11 (11, 0x00b): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_484 (484, 0x1e4)
    on bus B4.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B4_FRAME_484_484_CHECKSUM_LENGTH != 8               \
    || (!CAP_B4_FRAME_484_484_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B4_FRAME_484_484_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B4_FRAME_484_484_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B4_FRAME_484_484_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_04.dbc, frame frame_484 (484, 0x1e4): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1970 (1970, 0x7b2)
    on bus B4.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B4_FRAME_1970_1970_CHECKSUM_LENGTH != 8               \
    || (!CAP_B4_FRAME_1970_1970_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B4_FRAME_1970_1970_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B4_FRAME_1970_1970_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B4_FRAME_1970_1970_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_04.dbc, frame frame_1970 (1970, 0x7b2): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_732 (732, 0x2dc)
    on bus B4.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B4_FRAME_732_732_CHECKSUM_LENGTH != 8               \
    || (!CAP_B4_FRAME_732_732_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B4_FRAME_732_732_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B4_FRAME_732_732_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B4_FRAME_732_732_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_04.dbc, frame frame_732 (732, 0x2dc): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_682 (682, 0x2aa)
    on bus B4.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B4_FRAME_682_682_CHECKSUM_LENGTH != 8               \
    || (!CAP_B4_FRAME_682_682_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B4_FRAME_682_682_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B4_FRAME_682_682_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B4_FRAME_682_682_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_04.dbc, frame frame_682 (682, 0x2aa): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1840 (1840, 0x730)
    on bus B4.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B4_FRAME_1840_1840_CHECKSUM_LENGTH != 8               \
    || (!CAP_B4_FRAME_1840_1840_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B4_FRAME_1840_1840_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B4_FRAME_1840_1840_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B4_FRAME_1840_1840_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_04.dbc, frame frame_1840 (1840, 0x730): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_2036 (2036, 0x7f4)
    on bus B4.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B4_FRAME_2036_2036_CHECKSUM_LENGTH != 8               \
    || (!CAP_B4_FRAME_2036_2036_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B4_FRAME_2036_2036_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B4_FRAME_2036_2036_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B4_FRAME_2036_2036_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_04.dbc, frame frame_2036 (2036, 0x7f4): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_163 (163, 0x0a3)
    on bus B4.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B4_FRAME_163_163_CHECKSUM_LENGTH != 8               \
    || (!CAP_B4_FRAME_163_163_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B4_FRAME_163_163_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B4_FRAME_163_163_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B4_FRAME_163_163_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_04.dbc, frame frame_163 (163, 0x0a3): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_963 (963, 0x3c3)
    on bus B4.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B4_FRAME_963_963_CHECKSUM_LENGTH != 8               \
    || (!CAP_B4_FRAME_963_963_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B4_FRAME_963_963_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B4_FRAME_963_963_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B4_FRAME_963_963_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_04.dbc, frame frame_963 (963, 0x3c3): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_510 (510, 0x1fe)
    on bus B4.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B4_FRAME_510_510_CHECKSUM_LENGTH != 8               \
    || (!CAP_B4_FRAME_510_510_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B4_FRAME_510_510_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B4_FRAME_510_510_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B4_FRAME_510_510_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_04.dbc, frame frame_510 (510, 0x1fe): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_948 (948, 0x3b4)
    on bus B4.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B4_FRAME_948_948_CHECKSUM_LENGTH != 8               \
    || (!CAP_B4_FRAME_948_948_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B4_FRAME_948_948_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B4_FRAME_948_948_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B4_FRAME_948_948_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_04.dbc, frame frame_948 (948, 0x3b4): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_105 (105, 0x069)
    on bus B4.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B4_FRAME_105_105_CHECKSUM_LENGTH != 8               \
    || (!CAP_B4_FRAME_105_105_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B4_FRAME_105_105_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B4_FRAME_105_105_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B4_FRAME_105_105_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_04.dbc, frame frame_105 (105, 0x069): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1756 (1756, 0x6dc)
    on bus B4.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B4_FRAME_1756_1756_CHECKSUM_LENGTH != 8               \
    || (!CAP_B4_FRAME_1756_1756_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B4_FRAME_1756_1756_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B4_FRAME_1756_1756_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B4_FRAME_1756_1756_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_04.dbc, frame frame_1756 (1756, 0x6dc): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_853 (853, 0x355)
    on bus B4.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B4_FRAME_853_853_CHECKSUM_LENGTH != 8               \
    || (!CAP_B4_FRAME_853_853_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B4_FRAME_853_853_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B4_FRAME_853_853_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B4_FRAME_853_853_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_04.dbc, frame frame_853 (853, 0x355): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_988 (988, 0x3dc)
    on bus B4.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B4_FRAME_988_988_CHECKSUM_LENGTH != 8               \
    || (!CAP_B4_FRAME_988_988_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B4_FRAME_988_988_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B4_FRAME_988_988_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B4_FRAME_988_988_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_04.dbc, frame frame_988 (988, 0x3dc): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_200 (200, 0x0c8)
    on bus B4.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B4_FRAME_200_200_CHECKSUM_LENGTH != 8               \
    || (!CAP_B4_FRAME_200_200_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B4_FRAME_200_200_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B4_FRAME_200_200_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B4_FRAME_200_200_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_04.dbc, frame frame_200 (200, 0x0c8): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_2 (2, 0x002)
    on bus B4.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B4_FRAME_2_2_CHECKSUM_LENGTH != 8               \
    || (!CAP_B4_FRAME_2_2_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B4_FRAME_2_2_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B4_FRAME_2_2_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B4_FRAME_2_2_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_04.dbc, frame frame_2 (2, 0x002): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1660 (1660, 0x67c)
    on bus B4.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B4_FRAME_1660_1660_CHECKSUM_LENGTH != 8               \
    || (!CAP_B4_FRAME_1660_1660_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B4_FRAME_1660_1660_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B4_FRAME_1660_1660_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B4_FRAME_1660_1660_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_04.dbc, frame frame_1660 (1660, 0x67c): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1875 (1875, 0x753)
    on bus B4.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B4_FRAME_1875_1875_CHECKSUM_LENGTH != 8               \
    || (!CAP_B4_FRAME_1875_1875_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B4_FRAME_1875_1875_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B4_FRAME_1875_1875_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B4_FRAME_1875_1875_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_04.dbc, frame frame_1875 (1875, 0x753): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1444 (1444, 0x5a4)
    on bus B4.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B4_FRAME_1444_1444_CHECKSUM_LENGTH != 8               \
    || (!CAP_B4_FRAME_1444_1444_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B4_FRAME_1444_1444_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B4_FRAME_1444_1444_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B4_FRAME_1444_1444_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_04.dbc, frame frame_1444 (1444, 0x5a4): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1932 (1932, 0x78c)
    on bus B5.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B5_FRAME_1932_1932_CHECKSUM_LENGTH != 8               \
    || (!CAP_B5_FRAME_1932_1932_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B5_FRAME_1932_1932_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B5_FRAME_1932_1932_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B5_FRAME_1932_1932_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_05.dbc, frame frame_1932 (1932, 0x78c): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_639 (639, 0x27f)
    on bus B5.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B5_FRAME_639_639_CHECKSUM_LENGTH != 8               \
    || (!CAP_B5_FRAME_639_639_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B5_FRAME_639_639_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B5_FRAME_639_639_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B5_FRAME_639_639_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_05.dbc, frame frame_639 (639, 0x27f): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_570 (570, 0x23a)
    on bus B5.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B5_FRAME_570_570_CHECKSUM_LENGTH != 8               \
    || (!CAP_B5_FRAME_570_570_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B5_FRAME_570_570_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B5_FRAME_570_570_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B5_FRAME_570_570_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_05.dbc, frame frame_570 (570, 0x23a): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1406 (1406, 0x57e)
    on bus B5.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B5_FRAME_1406_1406_CHECKSUM_LENGTH != 8               \
    || (!CAP_B5_FRAME_1406_1406_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B5_FRAME_1406_1406_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B5_FRAME_1406_1406_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B5_FRAME_1406_1406_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_05.dbc, frame frame_1406 (1406, 0x57e): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_201 (201, 0x0c9)
    on bus B5.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B5_FRAME_201_201_CHECKSUM_LENGTH != 8               \
    || (!CAP_B5_FRAME_201_201_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B5_FRAME_201_201_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B5_FRAME_201_201_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B5_FRAME_201_201_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_05.dbc, frame frame_201 (201, 0x0c9): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_541 (541, 0x21d)
    on bus B5.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B5_FRAME_541_541_CHECKSUM_LENGTH != 8               \
    || (!CAP_B5_FRAME_541_541_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B5_FRAME_541_541_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B5_FRAME_541_541_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B5_FRAME_541_541_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_05.dbc, frame frame_541 (541, 0x21d): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1911 (1911, 0x777)
    on bus B5.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B5_FRAME_1911_1911_CHECKSUM_LENGTH != 8               \
    || (!CAP_B5_FRAME_1911_1911_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B5_FRAME_1911_1911_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B5_FRAME_1911_1911_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B5_FRAME_1911_1911_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_05.dbc, frame frame_1911 (1911, 0x777): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1951 (1951, 0x79f)
    on bus B5.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B5_FRAME_1951_1951_CHECKSUM_LENGTH != 8               \
    || (!CAP_B5_FRAME_1951_1951_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B5_FRAME_1951_1951_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B5_FRAME_1951_1951_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B5_FRAME_1951_1951_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_05.dbc, frame frame_1951 (1951, 0x79f): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_2032 (2032, 0x7f0)
    on bus B5.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B5_FRAME_2032_2032_CHECKSUM_LENGTH != 8               \
    || (!CAP_B5_FRAME_2032_2032_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B5_FRAME_2032_2032_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B5_FRAME_2032_2032_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B5_FRAME_2032_2032_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_05.dbc, frame frame_2032 (2032, 0x7f0): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1837 (1837, 0x72d)
    on bus B5.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B5_FRAME_1837_1837_CHECKSUM_LENGTH != 8               \
    || (!CAP_B5_FRAME_1837_1837_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B5_FRAME_1837_1837_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B5_FRAME_1837_1837_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B5_FRAME_1837_1837_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_05.dbc, frame frame_1837 (1837, 0x72d): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_2011 (2011, 0x7db)
    on bus B5.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B5_FRAME_2011_2011_CHECKSUM_LENGTH != 8               \
    || (!CAP_B5_FRAME_2011_2011_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B5_FRAME_2011_2011_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B5_FRAME_2011_2011_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B5_FRAME_2011_2011_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_05.dbc, frame frame_2011 (2011, 0x7db): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1672 (1672, 0x688)
    on bus B5.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B5_FRAME_1672_1672_CHECKSUM_LENGTH != 8               \
    || (!CAP_B5_FRAME_1672_1672_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B5_FRAME_1672_1672_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B5_FRAME_1672_1672_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B5_FRAME_1672_1672_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_05.dbc, frame frame_1672 (1672, 0x688): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_154 (154, 0x09a)
    on bus B5.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B5_FRAME_154_154_CHECKSUM_LENGTH != 8               \
    || (!CAP_B5_FRAME_154_154_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B5_FRAME_154_154_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B5_FRAME_154_154_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B5_FRAME_154_154_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_05.dbc, frame frame_154 (154, 0x09a): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_126 (126, 0x07e)
    on bus B5.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B5_FRAME_126_126_CHECKSUM_LENGTH != 8               \
    || (!CAP_B5_FRAME_126_126_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B5_FRAME_126_126_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B5_FRAME_126_126_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B5_FRAME_126_126_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_05.dbc, frame frame_126 (126, 0x07e): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1848 (1848, 0x738)
    on bus B5.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B5_FRAME_1848_1848_CHECKSUM_LENGTH != 8               \
    || (!CAP_B5_FRAME_1848_1848_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B5_FRAME_1848_1848_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B5_FRAME_1848_1848_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B5_FRAME_1848_1848_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_05.dbc, frame frame_1848 (1848, 0x738): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1989 (1989, 0x7c5)
    on bus B5.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B5_FRAME_1989_1989_CHECKSUM_LENGTH != 8               \
    || (!CAP_B5_FRAME_1989_1989_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B5_FRAME_1989_1989_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B5_FRAME_1989_1989_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B5_FRAME_1989_1989_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_05.dbc, frame frame_1989 (1989, 0x7c5): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_248 (248, 0x0f8)
    on bus B5.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B5_FRAME_248_248_CHECKSUM_LENGTH != 8               \
    || (!CAP_B5_FRAME_248_248_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B5_FRAME_248_248_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B5_FRAME_248_248_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B5_FRAME_248_248_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_05.dbc, frame frame_248 (248, 0x0f8): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_424 (424, 0x1a8)
    on bus B5.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B5_FRAME_424_424_CHECKSUM_LENGTH != 8               \
    || (!CAP_B5_FRAME_424_424_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B5_FRAME_424_424_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B5_FRAME_424_424_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B5_FRAME_424_424_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_05.dbc, frame frame_424 (424, 0x1a8): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_325 (325, 0x145)
    on bus B5.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B5_FRAME_325_325_CHECKSUM_LENGTH != 8               \
    || (!CAP_B5_FRAME_325_325_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B5_FRAME_325_325_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B5_FRAME_325_325_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B5_FRAME_325_325_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_05.dbc, frame frame_325 (325, 0x145): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_506 (506, 0x1fa)
    on bus B5.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B5_FRAME_506_506_CHECKSUM_LENGTH != 8               \
    || (!CAP_B5_FRAME_506_506_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B5_FRAME_506_506_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B5_FRAME_506_506_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B5_FRAME_506_506_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_05.dbc, frame frame_506 (506, 0x1fa): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1244 (1244, 0x4dc)
    on bus B5.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B5_FRAME_1244_1244_CHECKSUM_LENGTH != 8               \
    || (!CAP_B5_FRAME_1244_1244_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B5_FRAME_1244_1244_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B5_FRAME_1244_1244_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B5_FRAME_1244_1244_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_05.dbc, frame frame_1244 (1244, 0x4dc): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1218 (1218, 0x4c2)
    on bus B5.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B5_FRAME_1218_1218_CHECKSUM_LENGTH != 8               \
    || (!CAP_B5_FRAME_1218_1218_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B5_FRAME_1218_1218_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B5_FRAME_1218_1218_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B5_FRAME_1218_1218_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_05.dbc, frame frame_1218 (1218, 0x4c2): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_329 (329, 0x149)
    on bus B5.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B5_FRAME_329_329_CHECKSUM_LENGTH != 8               \
    || (!CAP_B5_FRAME_329_329_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B5_FRAME_329_329_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B5_FRAME_329_329_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B5_FRAME_329_329_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_05.dbc, frame frame_329 (329, 0x149): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1030 (1030, 0x406)
    on bus B5.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B5_FRAME_1030_1030_CHECKSUM_LENGTH != 8               \
    || (!CAP_B5_FRAME_1030_1030_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B5_FRAME_1030_1030_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B5_FRAME_1030_1030_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B5_FRAME_1030_1030_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_05.dbc, frame frame_1030 (1030, 0x406): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_70 (70, 0x046)
    on bus B5.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B5_FRAME_70_70_CHECKSUM_LENGTH != 8               \
    || (!CAP_B5_FRAME_70_70_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B5_FRAME_70_70_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B5_FRAME_70_70_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B5_FRAME_70_70_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_05.dbc, frame frame_70 (70, 0x046): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_906 (906, 0x38a)
    on bus B5.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B5_FRAME_906_906_CHECKSUM_LENGTH != 8               \
    || (!CAP_B5_FRAME_906_906_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B5_FRAME_906_906_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B5_FRAME_906_906_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B5_FRAME_906_906_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_05.dbc, frame frame_906 (906, 0x38a): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1507 (1507, 0x5e3)
    on bus B5.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B5_FRAME_1507_1507_CHECKSUM_LENGTH != 8               \
    || (!CAP_B5_FRAME_1507_1507_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B5_FRAME_1507_1507_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B5_FRAME_1507_1507_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B5_FRAME_1507_1507_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_05.dbc, frame frame_1507 (1507, 0x5e3): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1253 (1253, 0x4e5)
    on bus B5.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B5_FRAME_1253_1253_CHECKSUM_LENGTH != 8               \
    || (!CAP_B5_FRAME_1253_1253_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B5_FRAME_1253_1253_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B5_FRAME_1253_1253_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B5_FRAME_1253_1253_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_05.dbc, frame frame_1253 (1253, 0x4e5): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_362 (362, 0x16a)
    on bus B5.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B5_FRAME_362_362_CHECKSUM_LENGTH != 8               \
    || (!CAP_B5_FRAME_362_362_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B5_FRAME_362_362_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B5_FRAME_362_362_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B5_FRAME_362_362_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_05.dbc, frame frame_362 (362, 0x16a): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1043 (1043, 0x413)
    on bus B5.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B5_FRAME_1043_1043_CHECKSUM_LENGTH != 8               \
    || (!CAP_B5_FRAME_1043_1043_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B5_FRAME_1043_1043_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B5_FRAME_1043_1043_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B5_FRAME_1043_1043_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_05.dbc, frame frame_1043 (1043, 0x413): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_800 (800, 0x320)
    on bus B5.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B5_FRAME_800_800_CHECKSUM_LENGTH != 8               \
    || (!CAP_B5_FRAME_800_800_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B5_FRAME_800_800_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B5_FRAME_800_800_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B5_FRAME_800_800_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_05.dbc, frame frame_800 (800, 0x320): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_306 (306, 0x132)
    on bus B5.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B5_FRAME_306_306_CHECKSUM_LENGTH != 8               \
    || (!CAP_B5_FRAME_306_306_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B5_FRAME_306_306_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B5_FRAME_306_306_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B5_FRAME_306_306_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_05.dbc, frame frame_306 (306, 0x132): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_283 (283, 0x11b)
    on bus B5.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B5_FRAME_283_283_CHECKSUM_LENGTH != 8               \
    || (!CAP_B5_FRAME_283_283_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B5_FRAME_283_283_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B5_FRAME_283_283_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B5_FRAME_283_283_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_05.dbc, frame frame_283 (283, 0x11b): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1562 (1562, 0x61a)
    on bus B5.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B5_FRAME_1562_1562_CHECKSUM_LENGTH != 8               \
    || (!CAP_B5_FRAME_1562_1562_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B5_FRAME_1562_1562_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B5_FRAME_1562_1562_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B5_FRAME_1562_1562_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_05.dbc, frame frame_1562 (1562, 0x61a): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_37 (37, 0x025)
    on bus B5.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B5_FRAME_37_37_CHECKSUM_LENGTH != 8               \
    || (!CAP_B5_FRAME_37_37_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B5_FRAME_37_37_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B5_FRAME_37_37_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B5_FRAME_37_37_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_05.dbc, frame frame_37 (37, 0x025): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_464 (464, 0x1d0)
    on bus B5.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B5_FRAME_464_464_CHECKSUM_LENGTH != 8               \
    || (!CAP_B5_FRAME_464_464_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B5_FRAME_464_464_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B5_FRAME_464_464_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B5_FRAME_464_464_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_05.dbc, frame frame_464 (464, 0x1d0): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1853 (1853, 0x73d)
    on bus B5.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B5_FRAME_1853_1853_CHECKSUM_LENGTH != 8               \
    || (!CAP_B5_FRAME_1853_1853_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B5_FRAME_1853_1853_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B5_FRAME_1853_1853_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B5_FRAME_1853_1853_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_05.dbc, frame frame_1853 (1853, 0x73d): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1319 (1319, 0x527)
    on bus B5.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B5_FRAME_1319_1319_CHECKSUM_LENGTH != 8               \
    || (!CAP_B5_FRAME_1319_1319_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B5_FRAME_1319_1319_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B5_FRAME_1319_1319_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B5_FRAME_1319_1319_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_05.dbc, frame frame_1319 (1319, 0x527): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_564 (564, 0x234)
    on bus B5.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B5_FRAME_564_564_CHECKSUM_LENGTH != 8               \
    || (!CAP_B5_FRAME_564_564_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B5_FRAME_564_564_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B5_FRAME_564_564_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B5_FRAME_564_564_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_05.dbc, frame frame_564 (564, 0x234): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1642 (1642, 0x66a)
    on bus B5.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B5_FRAME_1642_1642_CHECKSUM_LENGTH != 8               \
    || (!CAP_B5_FRAME_1642_1642_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B5_FRAME_1642_1642_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B5_FRAME_1642_1642_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B5_FRAME_1642_1642_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_05.dbc, frame frame_1642 (1642, 0x66a): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1024 (1024, 0x400)
    on bus B5.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B5_FRAME_1024_1024_CHECKSUM_LENGTH != 8               \
    || (!CAP_B5_FRAME_1024_1024_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B5_FRAME_1024_1024_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B5_FRAME_1024_1024_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B5_FRAME_1024_1024_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_05.dbc, frame frame_1024 (1024, 0x400): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1351 (1351, 0x547)
    on bus B5.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B5_FRAME_1351_1351_CHECKSUM_LENGTH != 8               \
    || (!CAP_B5_FRAME_1351_1351_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B5_FRAME_1351_1351_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B5_FRAME_1351_1351_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B5_FRAME_1351_1351_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_05.dbc, frame frame_1351 (1351, 0x547): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_2004 (2004, 0x7d4)
    on bus B5.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B5_FRAME_2004_2004_CHECKSUM_LENGTH != 8               \
    || (!CAP_B5_FRAME_2004_2004_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B5_FRAME_2004_2004_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B5_FRAME_2004_2004_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B5_FRAME_2004_2004_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_05.dbc, frame frame_2004 (2004, 0x7d4): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_14 (14, 0x00e)
    on bus B5.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B5_FRAME_14_14_CHECKSUM_LENGTH != 8               \
    || (!CAP_B5_FRAME_14_14_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B5_FRAME_14_14_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B5_FRAME_14_14_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B5_FRAME_14_14_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_05.dbc, frame frame_14 (14, 0x00e): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_477 (477, 0x1dd)
    on bus B5.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B5_FRAME_477_477_CHECKSUM_LENGTH != 8               \
    || (!CAP_B5_FRAME_477_477_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B5_FRAME_477_477_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B5_FRAME_477_477_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B5_FRAME_477_477_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_05.dbc, frame frame_477 (477, 0x1dd): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1781 (1781, 0x6f5)
    on bus B5.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B5_FRAME_1781_1781_CHECKSUM_LENGTH != 8               \
    || (!CAP_B5_FRAME_1781_1781_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B5_FRAME_1781_1781_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B5_FRAME_1781_1781_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B5_FRAME_1781_1781_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_05.dbc, frame frame_1781 (1781, 0x6f5): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_572 (572, 0x23c)
    on bus B5.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B5_FRAME_572_572_CHECKSUM_LENGTH != 8               \
    || (!CAP_B5_FRAME_572_572_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B5_FRAME_572_572_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B5_FRAME_572_572_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B5_FRAME_572_572_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_05.dbc, frame frame_572 (572, 0x23c): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1458 (1458, 0x5b2)
    on bus B5.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B5_FRAME_1458_1458_CHECKSUM_LENGTH != 8               \
    || (!CAP_B5_FRAME_1458_1458_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B5_FRAME_1458_1458_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B5_FRAME_1458_1458_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B5_FRAME_1458_1458_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_05.dbc, frame frame_1458 (1458, 0x5b2): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1990 (1990, 0x7c6)
    on bus B5.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B5_FRAME_1990_1990_CHECKSUM_LENGTH != 8               \
    || (!CAP_B5_FRAME_1990_1990_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B5_FRAME_1990_1990_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B5_FRAME_1990_1990_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B5_FRAME_1990_1990_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_05.dbc, frame frame_1990 (1990, 0x7c6): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1811 (1811, 0x713)
    on bus B5.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B5_FRAME_1811_1811_CHECKSUM_LENGTH != 8               \
    || (!CAP_B5_FRAME_1811_1811_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B5_FRAME_1811_1811_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B5_FRAME_1811_1811_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B5_FRAME_1811_1811_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_05.dbc, frame frame_1811 (1811, 0x713): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_27 (27, 0x01b)
    on bus B5.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B5_FRAME_27_27_CHECKSUM_LENGTH != 8               \
    || (!CAP_B5_FRAME_27_27_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B5_FRAME_27_27_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B5_FRAME_27_27_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B5_FRAME_27_27_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_05.dbc, frame frame_27 (27, 0x01b): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1576 (1576, 0x628)
    on bus B5.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B5_FRAME_1576_1576_CHECKSUM_LENGTH != 8               \
    || (!CAP_B5_FRAME_1576_1576_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B5_FRAME_1576_1576_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B5_FRAME_1576_1576_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B5_FRAME_1576_1576_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_05.dbc, frame frame_1576 (1576, 0x628): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_809 (809, 0x329)
    on bus B5.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B5_FRAME_809_809_CHECKSUM_LENGTH != 8               \
    || (!CAP_B5_FRAME_809_809_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B5_FRAME_809_809_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B5_FRAME_809_809_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B5_FRAME_809_809_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_05.dbc, frame frame_809 (809, 0x329): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1752 (1752, 0x6d8)
    on bus B5.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B5_FRAME_1752_1752_CHECKSUM_LENGTH != 8               \
    || (!CAP_B5_FRAME_1752_1752_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B5_FRAME_1752_1752_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B5_FRAME_1752_1752_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B5_FRAME_1752_1752_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_05.dbc, frame frame_1752 (1752, 0x6d8): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1454 (1454, 0x5ae)
    on bus B5.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B5_FRAME_1454_1454_CHECKSUM_LENGTH != 8               \
    || (!CAP_B5_FRAME_1454_1454_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B5_FRAME_1454_1454_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B5_FRAME_1454_1454_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B5_FRAME_1454_1454_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_05.dbc, frame frame_1454 (1454, 0x5ae): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_170 (170, 0x0aa)
    on bus B5.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B5_FRAME_170_170_CHECKSUM_LENGTH != 8               \
    || (!CAP_B5_FRAME_170_170_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B5_FRAME_170_170_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B5_FRAME_170_170_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B5_FRAME_170_170_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_05.dbc, frame frame_170 (170, 0x0aa): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1732 (1732, 0x6c4)
    on bus B5.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B5_FRAME_1732_1732_CHECKSUM_LENGTH != 8               \
    || (!CAP_B5_FRAME_1732_1732_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B5_FRAME_1732_1732_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B5_FRAME_1732_1732_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B5_FRAME_1732_1732_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_05.dbc, frame frame_1732 (1732, 0x6c4): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_550 (550, 0x226)
    on bus B6.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B6_FRAME_550_550_CHECKSUM_LENGTH != 8               \
    || (!CAP_B6_FRAME_550_550_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B6_FRAME_550_550_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B6_FRAME_550_550_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B6_FRAME_550_550_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_06.dbc, frame frame_550 (550, 0x226): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_794 (794, 0x31a)
    on bus B6.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B6_FRAME_794_794_CHECKSUM_LENGTH != 8               \
    || (!CAP_B6_FRAME_794_794_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B6_FRAME_794_794_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B6_FRAME_794_794_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B6_FRAME_794_794_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_06.dbc, frame frame_794 (794, 0x31a): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_168 (168, 0x0a8)
    on bus B6.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B6_FRAME_168_168_CHECKSUM_LENGTH != 8               \
    || (!CAP_B6_FRAME_168_168_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B6_FRAME_168_168_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B6_FRAME_168_168_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B6_FRAME_168_168_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_06.dbc, frame frame_168 (168, 0x0a8): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_66 (66, 0x042)
    on bus B6.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B6_FRAME_66_66_CHECKSUM_LENGTH != 8               \
    || (!CAP_B6_FRAME_66_66_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B6_FRAME_66_66_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B6_FRAME_66_66_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B6_FRAME_66_66_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_06.dbc, frame frame_66 (66, 0x042): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1387 (1387, 0x56b)
    on bus B6.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B6_FRAME_1387_1387_CHECKSUM_LENGTH != 8               \
    || (!CAP_B6_FRAME_1387_1387_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B6_FRAME_1387_1387_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B6_FRAME_1387_1387_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B6_FRAME_1387_1387_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_06.dbc, frame frame_1387 (1387, 0x56b): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1714 (1714, 0x6b2)
    on bus B6.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B6_FRAME_1714_1714_CHECKSUM_LENGTH != 8               \
    || (!CAP_B6_FRAME_1714_1714_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B6_FRAME_1714_1714_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B6_FRAME_1714_1714_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B6_FRAME_1714_1714_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_06.dbc, frame frame_1714 (1714, 0x6b2): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_2010 (2010, 0x7da)
    on bus B6.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B6_FRAME_2010_2010_CHECKSUM_LENGTH != 8               \
    || (!CAP_B6_FRAME_2010_2010_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B6_FRAME_2010_2010_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B6_FRAME_2010_2010_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B6_FRAME_2010_2010_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_06.dbc, frame frame_2010 (2010, 0x7da): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_300 (300, 0x12c)
    on bus B6.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B6_FRAME_300_300_CHECKSUM_LENGTH != 8               \
    || (!CAP_B6_FRAME_300_300_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B6_FRAME_300_300_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B6_FRAME_300_300_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B6_FRAME_300_300_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_06.dbc, frame frame_300 (300, 0x12c): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1561 (1561, 0x619)
    on bus B6.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B6_FRAME_1561_1561_CHECKSUM_LENGTH != 8               \
    || (!CAP_B6_FRAME_1561_1561_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B6_FRAME_1561_1561_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B6_FRAME_1561_1561_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B6_FRAME_1561_1561_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_06.dbc, frame frame_1561 (1561, 0x619): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_992 (992, 0x3e0)
    on bus B6.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B6_FRAME_992_992_CHECKSUM_LENGTH != 8               \
    || (!CAP_B6_FRAME_992_992_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B6_FRAME_992_992_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B6_FRAME_992_992_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B6_FRAME_992_992_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_06.dbc, frame frame_992 (992, 0x3e0): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_441 (441, 0x1b9)
    on bus B6.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B6_FRAME_441_441_CHECKSUM_LENGTH != 8               \
    || (!CAP_B6_FRAME_441_441_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B6_FRAME_441_441_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B6_FRAME_441_441_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B6_FRAME_441_441_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_06.dbc, frame frame_441 (441, 0x1b9): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1716 (1716, 0x6b4)
    on bus B6.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B6_FRAME_1716_1716_CHECKSUM_LENGTH != 8               \
    || (!CAP_B6_FRAME_1716_1716_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B6_FRAME_1716_1716_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B6_FRAME_1716_1716_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B6_FRAME_1716_1716_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_06.dbc, frame frame_1716 (1716, 0x6b4): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_941 (941, 0x3ad)
    on bus B6.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B6_FRAME_941_941_CHECKSUM_LENGTH != 8               \
    || (!CAP_B6_FRAME_941_941_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B6_FRAME_941_941_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B6_FRAME_941_941_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B6_FRAME_941_941_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_06.dbc, frame frame_941 (941, 0x3ad): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_157 (157, 0x09d)
    on bus B6.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B6_FRAME_157_157_CHECKSUM_LENGTH != 8               \
    || (!CAP_B6_FRAME_157_157_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B6_FRAME_157_157_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B6_FRAME_157_157_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B6_FRAME_157_157_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_06.dbc, frame frame_157 (157, 0x09d): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1981 (1981, 0x7bd)
    on bus B6.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B6_FRAME_1981_1981_CHECKSUM_LENGTH != 8               \
    || (!CAP_B6_FRAME_1981_1981_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B6_FRAME_1981_1981_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B6_FRAME_1981_1981_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B6_FRAME_1981_1981_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_06.dbc, frame frame_1981 (1981, 0x7bd): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1640 (1640, 0x668)
    on bus B6.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B6_FRAME_1640_1640_CHECKSUM_LENGTH != 8               \
    || (!CAP_B6_FRAME_1640_1640_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B6_FRAME_1640_1640_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B6_FRAME_1640_1640_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B6_FRAME_1640_1640_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_06.dbc, frame frame_1640 (1640, 0x668): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1575 (1575, 0x627)
    on bus B6.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B6_FRAME_1575_1575_CHECKSUM_LENGTH != 8               \
    || (!CAP_B6_FRAME_1575_1575_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B6_FRAME_1575_1575_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B6_FRAME_1575_1575_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B6_FRAME_1575_1575_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_06.dbc, frame frame_1575 (1575, 0x627): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1169 (1169, 0x491)
    on bus B6.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B6_FRAME_1169_1169_CHECKSUM_LENGTH != 8               \
    || (!CAP_B6_FRAME_1169_1169_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B6_FRAME_1169_1169_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B6_FRAME_1169_1169_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B6_FRAME_1169_1169_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_06.dbc, frame frame_1169 (1169, 0x491): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1941 (1941, 0x795)
    on bus B6.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B6_FRAME_1941_1941_CHECKSUM_LENGTH != 8               \
    || (!CAP_B6_FRAME_1941_1941_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B6_FRAME_1941_1941_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B6_FRAME_1941_1941_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B6_FRAME_1941_1941_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_06.dbc, frame frame_1941 (1941, 0x795): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_978 (978, 0x3d2)
    on bus B6.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B6_FRAME_978_978_CHECKSUM_LENGTH != 8               \
    || (!CAP_B6_FRAME_978_978_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B6_FRAME_978_978_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B6_FRAME_978_978_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B6_FRAME_978_978_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_06.dbc, frame frame_978 (978, 0x3d2): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1155 (1155, 0x483)
    on bus B6.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B6_FRAME_1155_1155_CHECKSUM_LENGTH != 8               \
    || (!CAP_B6_FRAME_1155_1155_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B6_FRAME_1155_1155_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B6_FRAME_1155_1155_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B6_FRAME_1155_1155_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_06.dbc, frame frame_1155 (1155, 0x483): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1971 (1971, 0x7b3)
    on bus B6.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B6_FRAME_1971_1971_CHECKSUM_LENGTH != 8               \
    || (!CAP_B6_FRAME_1971_1971_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B6_FRAME_1971_1971_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B6_FRAME_1971_1971_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B6_FRAME_1971_1971_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_06.dbc, frame frame_1971 (1971, 0x7b3): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1838 (1838, 0x72e)
    on bus B6.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B6_FRAME_1838_1838_CHECKSUM_LENGTH != 8               \
    || (!CAP_B6_FRAME_1838_1838_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B6_FRAME_1838_1838_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B6_FRAME_1838_1838_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B6_FRAME_1838_1838_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_06.dbc, frame frame_1838 (1838, 0x72e): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1770 (1770, 0x6ea)
    on bus B6.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B6_FRAME_1770_1770_CHECKSUM_LENGTH != 8               \
    || (!CAP_B6_FRAME_1770_1770_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B6_FRAME_1770_1770_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B6_FRAME_1770_1770_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B6_FRAME_1770_1770_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_06.dbc, frame frame_1770 (1770, 0x6ea): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1701 (1701, 0x6a5)
    on bus B6.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B6_FRAME_1701_1701_CHECKSUM_LENGTH != 8               \
    || (!CAP_B6_FRAME_1701_1701_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B6_FRAME_1701_1701_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B6_FRAME_1701_1701_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B6_FRAME_1701_1701_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_06.dbc, frame frame_1701 (1701, 0x6a5): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1727 (1727, 0x6bf)
    on bus B6.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B6_FRAME_1727_1727_CHECKSUM_LENGTH != 8               \
    || (!CAP_B6_FRAME_1727_1727_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B6_FRAME_1727_1727_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B6_FRAME_1727_1727_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B6_FRAME_1727_1727_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_06.dbc, frame frame_1727 (1727, 0x6bf): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1329 (1329, 0x531)
    on bus B6.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B6_FRAME_1329_1329_CHECKSUM_LENGTH != 8               \
    || (!CAP_B6_FRAME_1329_1329_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B6_FRAME_1329_1329_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B6_FRAME_1329_1329_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B6_FRAME_1329_1329_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_06.dbc, frame frame_1329 (1329, 0x531): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1272 (1272, 0x4f8)
    on bus B6.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B6_FRAME_1272_1272_CHECKSUM_LENGTH != 8               \
    || (!CAP_B6_FRAME_1272_1272_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B6_FRAME_1272_1272_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B6_FRAME_1272_1272_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B6_FRAME_1272_1272_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_06.dbc, frame frame_1272 (1272, 0x4f8): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_913 (913, 0x391)
    on bus B6.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B6_FRAME_913_913_CHECKSUM_LENGTH != 8               \
    || (!CAP_B6_FRAME_913_913_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B6_FRAME_913_913_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B6_FRAME_913_913_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B6_FRAME_913_913_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_06.dbc, frame frame_913 (913, 0x391): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1493 (1493, 0x5d5)
    on bus B6.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B6_FRAME_1493_1493_CHECKSUM_LENGTH != 8               \
    || (!CAP_B6_FRAME_1493_1493_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B6_FRAME_1493_1493_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B6_FRAME_1493_1493_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B6_FRAME_1493_1493_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_06.dbc, frame frame_1493 (1493, 0x5d5): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1165 (1165, 0x48d)
    on bus B6.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B6_FRAME_1165_1165_CHECKSUM_LENGTH != 8               \
    || (!CAP_B6_FRAME_1165_1165_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B6_FRAME_1165_1165_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B6_FRAME_1165_1165_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B6_FRAME_1165_1165_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_06.dbc, frame frame_1165 (1165, 0x48d): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_997 (997, 0x3e5)
    on bus B6.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B6_FRAME_997_997_CHECKSUM_LENGTH != 8               \
    || (!CAP_B6_FRAME_997_997_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B6_FRAME_997_997_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B6_FRAME_997_997_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B6_FRAME_997_997_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_06.dbc, frame frame_997 (997, 0x3e5): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1269 (1269, 0x4f5)
    on bus B6.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B6_FRAME_1269_1269_CHECKSUM_LENGTH != 8               \
    || (!CAP_B6_FRAME_1269_1269_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B6_FRAME_1269_1269_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B6_FRAME_1269_1269_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B6_FRAME_1269_1269_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_06.dbc, frame frame_1269 (1269, 0x4f5): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1962 (1962, 0x7aa)
    on bus B6.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B6_FRAME_1962_1962_CHECKSUM_LENGTH != 8               \
    || (!CAP_B6_FRAME_1962_1962_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B6_FRAME_1962_1962_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B6_FRAME_1962_1962_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B6_FRAME_1962_1962_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_06.dbc, frame frame_1962 (1962, 0x7aa): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1116 (1116, 0x45c)
    on bus B6.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B6_FRAME_1116_1116_CHECKSUM_LENGTH != 8               \
    || (!CAP_B6_FRAME_1116_1116_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B6_FRAME_1116_1116_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B6_FRAME_1116_1116_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B6_FRAME_1116_1116_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_06.dbc, frame frame_1116 (1116, 0x45c): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_32 (32, 0x020)
    on bus B6.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B6_FRAME_32_32_CHECKSUM_LENGTH != 8               \
    || (!CAP_B6_FRAME_32_32_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B6_FRAME_32_32_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B6_FRAME_32_32_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B6_FRAME_32_32_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_06.dbc, frame frame_32 (32, 0x020): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_895 (895, 0x37f)
    on bus B6.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B6_FRAME_895_895_CHECKSUM_LENGTH != 8               \
    || (!CAP_B6_FRAME_895_895_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B6_FRAME_895_895_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B6_FRAME_895_895_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B6_FRAME_895_895_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_06.dbc, frame frame_895 (895, 0x37f): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1479 (1479, 0x5c7)
    on bus B6.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B6_FRAME_1479_1479_CHECKSUM_LENGTH != 8               \
    || (!CAP_B6_FRAME_1479_1479_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B6_FRAME_1479_1479_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B6_FRAME_1479_1479_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B6_FRAME_1479_1479_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_06.dbc, frame frame_1479 (1479, 0x5c7): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_666 (666, 0x29a)
    on bus B6.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B6_FRAME_666_666_CHECKSUM_LENGTH != 8               \
    || (!CAP_B6_FRAME_666_666_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B6_FRAME_666_666_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B6_FRAME_666_666_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B6_FRAME_666_666_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_06.dbc, frame frame_666 (666, 0x29a): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_557 (557, 0x22d)
    on bus B6.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B6_FRAME_557_557_CHECKSUM_LENGTH != 8               \
    || (!CAP_B6_FRAME_557_557_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B6_FRAME_557_557_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B6_FRAME_557_557_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B6_FRAME_557_557_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_06.dbc, frame frame_557 (557, 0x22d): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1857 (1857, 0x741)
    on bus B6.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B6_FRAME_1857_1857_CHECKSUM_LENGTH != 8               \
    || (!CAP_B6_FRAME_1857_1857_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B6_FRAME_1857_1857_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B6_FRAME_1857_1857_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B6_FRAME_1857_1857_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_06.dbc, frame frame_1857 (1857, 0x741): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1395 (1395, 0x573)
    on bus B6.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B6_FRAME_1395_1395_CHECKSUM_LENGTH != 8               \
    || (!CAP_B6_FRAME_1395_1395_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B6_FRAME_1395_1395_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B6_FRAME_1395_1395_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B6_FRAME_1395_1395_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_06.dbc, frame frame_1395 (1395, 0x573): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1495 (1495, 0x5d7)
    on bus B6.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B6_FRAME_1495_1495_CHECKSUM_LENGTH != 8               \
    || (!CAP_B6_FRAME_1495_1495_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B6_FRAME_1495_1495_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B6_FRAME_1495_1495_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B6_FRAME_1495_1495_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_06.dbc, frame frame_1495 (1495, 0x5d7): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_457 (457, 0x1c9)
    on bus B6.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B6_FRAME_457_457_CHECKSUM_LENGTH != 8               \
    || (!CAP_B6_FRAME_457_457_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B6_FRAME_457_457_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B6_FRAME_457_457_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B6_FRAME_457_457_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_06.dbc, frame frame_457 (457, 0x1c9): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1175 (1175, 0x497)
    on bus B6.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B6_FRAME_1175_1175_CHECKSUM_LENGTH != 8               \
    || (!CAP_B6_FRAME_1175_1175_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B6_FRAME_1175_1175_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B6_FRAME_1175_1175_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B6_FRAME_1175_1175_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_06.dbc, frame frame_1175 (1175, 0x497): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1424 (1424, 0x590)
    on bus B6.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B6_FRAME_1424_1424_CHECKSUM_LENGTH != 8               \
    || (!CAP_B6_FRAME_1424_1424_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B6_FRAME_1424_1424_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B6_FRAME_1424_1424_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B6_FRAME_1424_1424_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_06.dbc, frame frame_1424 (1424, 0x590): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1859 (1859, 0x743)
    on bus B6.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B6_FRAME_1859_1859_CHECKSUM_LENGTH != 8               \
    || (!CAP_B6_FRAME_1859_1859_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B6_FRAME_1859_1859_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B6_FRAME_1859_1859_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B6_FRAME_1859_1859_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_06.dbc, frame frame_1859 (1859, 0x743): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_985 (985, 0x3d9)
    on bus B6.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B6_FRAME_985_985_CHECKSUM_LENGTH != 8               \
    || (!CAP_B6_FRAME_985_985_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B6_FRAME_985_985_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B6_FRAME_985_985_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B6_FRAME_985_985_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_06.dbc, frame frame_985 (985, 0x3d9): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_454 (454, 0x1c6)
    on bus B6.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B6_FRAME_454_454_CHECKSUM_LENGTH != 8               \
    || (!CAP_B6_FRAME_454_454_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B6_FRAME_454_454_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B6_FRAME_454_454_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B6_FRAME_454_454_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_06.dbc, frame frame_454 (454, 0x1c6): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_753 (753, 0x2f1)
    on bus B6.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B6_FRAME_753_753_CHECKSUM_LENGTH != 8               \
    || (!CAP_B6_FRAME_753_753_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B6_FRAME_753_753_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B6_FRAME_753_753_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B6_FRAME_753_753_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_06.dbc, frame frame_753 (753, 0x2f1): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_13 (13, 0x00d)
    on bus B6.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B6_FRAME_13_13_CHECKSUM_LENGTH != 8               \
    || (!CAP_B6_FRAME_13_13_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B6_FRAME_13_13_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B6_FRAME_13_13_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B6_FRAME_13_13_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_06.dbc, frame frame_13 (13, 0x00d): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1277 (1277, 0x4fd)
    on bus B6.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B6_FRAME_1277_1277_CHECKSUM_LENGTH != 8               \
    || (!CAP_B6_FRAME_1277_1277_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B6_FRAME_1277_1277_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B6_FRAME_1277_1277_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B6_FRAME_1277_1277_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_06.dbc, frame frame_1277 (1277, 0x4fd): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1593 (1593, 0x639)
    on bus B6.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B6_FRAME_1593_1593_CHECKSUM_LENGTH != 8               \
    || (!CAP_B6_FRAME_1593_1593_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B6_FRAME_1593_1593_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B6_FRAME_1593_1593_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B6_FRAME_1593_1593_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_06.dbc, frame frame_1593 (1593, 0x639): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1408 (1408, 0x580)
    on bus B6.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B6_FRAME_1408_1408_CHECKSUM_LENGTH != 8               \
    || (!CAP_B6_FRAME_1408_1408_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B6_FRAME_1408_1408_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B6_FRAME_1408_1408_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B6_FRAME_1408_1408_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_06.dbc, frame frame_1408 (1408, 0x580): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_999 (999, 0x3e7)
    on bus B6.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B6_FRAME_999_999_CHECKSUM_LENGTH != 8               \
    || (!CAP_B6_FRAME_999_999_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B6_FRAME_999_999_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B6_FRAME_999_999_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B6_FRAME_999_999_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_06.dbc, frame frame_999 (999, 0x3e7): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_132 (132, 0x084)
    on bus B6.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B6_FRAME_132_132_CHECKSUM_LENGTH != 8               \
    || (!CAP_B6_FRAME_132_132_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B6_FRAME_132_132_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B6_FRAME_132_132_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B6_FRAME_132_132_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_06.dbc, frame frame_132 (132, 0x084): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1980 (1980, 0x7bc)
    on bus B6.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B6_FRAME_1980_1980_CHECKSUM_LENGTH != 8               \
    || (!CAP_B6_FRAME_1980_1980_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B6_FRAME_1980_1980_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B6_FRAME_1980_1980_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B6_FRAME_1980_1980_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_06.dbc, frame frame_1980 (1980, 0x7bc): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_553 (553, 0x229)
    on bus B6.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B6_FRAME_553_553_CHECKSUM_LENGTH != 8               \
    || (!CAP_B6_FRAME_553_553_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B6_FRAME_553_553_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B6_FRAME_553_553_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B6_FRAME_553_553_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_06.dbc, frame frame_553 (553, 0x229): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_321 (321, 0x141)
    on bus B6.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B6_FRAME_321_321_CHECKSUM_LENGTH != 8               \
    || (!CAP_B6_FRAME_321_321_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B6_FRAME_321_321_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B6_FRAME_321_321_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B6_FRAME_321_321_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_06.dbc, frame frame_321 (321, 0x141): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1552 (1552, 0x610)
    on bus B6.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B6_FRAME_1552_1552_CHECKSUM_LENGTH != 8               \
    || (!CAP_B6_FRAME_1552_1552_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B6_FRAME_1552_1552_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B6_FRAME_1552_1552_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B6_FRAME_1552_1552_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_06.dbc, frame frame_1552 (1552, 0x610): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1287 (1287, 0x507)
    on bus B6.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B6_FRAME_1287_1287_CHECKSUM_LENGTH != 8               \
    || (!CAP_B6_FRAME_1287_1287_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B6_FRAME_1287_1287_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B6_FRAME_1287_1287_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B6_FRAME_1287_1287_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_06.dbc, frame frame_1287 (1287, 0x507): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1487 (1487, 0x5cf)
    on bus B6.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B6_FRAME_1487_1487_CHECKSUM_LENGTH != 8               \
    || (!CAP_B6_FRAME_1487_1487_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B6_FRAME_1487_1487_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B6_FRAME_1487_1487_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B6_FRAME_1487_1487_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_06.dbc, frame frame_1487 (1487, 0x5cf): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1225 (1225, 0x4c9)
    on bus B6.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B6_FRAME_1225_1225_CHECKSUM_LENGTH != 8               \
    || (!CAP_B6_FRAME_1225_1225_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B6_FRAME_1225_1225_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B6_FRAME_1225_1225_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B6_FRAME_1225_1225_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_06.dbc, frame frame_1225 (1225, 0x4c9): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1183 (1183, 0x49f)
    on bus B6.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B6_FRAME_1183_1183_CHECKSUM_LENGTH != 8               \
    || (!CAP_B6_FRAME_1183_1183_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B6_FRAME_1183_1183_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B6_FRAME_1183_1183_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B6_FRAME_1183_1183_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_06.dbc, frame frame_1183 (1183, 0x49f): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_679 (679, 0x2a7)
    on bus B6.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B6_FRAME_679_679_CHECKSUM_LENGTH != 8               \
    || (!CAP_B6_FRAME_679_679_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B6_FRAME_679_679_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B6_FRAME_679_679_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B6_FRAME_679_679_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_06.dbc, frame frame_679 (679, 0x2a7): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_257 (257, 0x101)
    on bus B6.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B6_FRAME_257_257_CHECKSUM_LENGTH != 8               \
    || (!CAP_B6_FRAME_257_257_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B6_FRAME_257_257_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B6_FRAME_257_257_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B6_FRAME_257_257_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_06.dbc, frame frame_257 (257, 0x101): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_189 (189, 0x0bd)
    on bus B6.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B6_FRAME_189_189_CHECKSUM_LENGTH != 8               \
    || (!CAP_B6_FRAME_189_189_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B6_FRAME_189_189_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B6_FRAME_189_189_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B6_FRAME_189_189_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_06.dbc, frame frame_189 (189, 0x0bd): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_494 (494, 0x1ee)
    on bus B6.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B6_FRAME_494_494_CHECKSUM_LENGTH != 8               \
    || (!CAP_B6_FRAME_494_494_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B6_FRAME_494_494_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B6_FRAME_494_494_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B6_FRAME_494_494_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_06.dbc, frame frame_494 (494, 0x1ee): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1045 (1045, 0x415)
    on bus B6.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B6_FRAME_1045_1045_CHECKSUM_LENGTH != 8               \
    || (!CAP_B6_FRAME_1045_1045_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B6_FRAME_1045_1045_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B6_FRAME_1045_1045_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B6_FRAME_1045_1045_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_06.dbc, frame frame_1045 (1045, 0x415): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1032 (1032, 0x408)
    on bus B6.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B6_FRAME_1032_1032_CHECKSUM_LENGTH != 8               \
    || (!CAP_B6_FRAME_1032_1032_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B6_FRAME_1032_1032_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B6_FRAME_1032_1032_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B6_FRAME_1032_1032_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_06.dbc, frame frame_1032 (1032, 0x408): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_58 (58, 0x03a)
    on bus B6.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B6_FRAME_58_58_CHECKSUM_LENGTH != 8               \
    || (!CAP_B6_FRAME_58_58_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B6_FRAME_58_58_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B6_FRAME_58_58_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B6_FRAME_58_58_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_06.dbc, frame frame_58 (58, 0x03a): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_313 (313, 0x139)
    on bus B6.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B6_FRAME_313_313_CHECKSUM_LENGTH != 8               \
    || (!CAP_B6_FRAME_313_313_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B6_FRAME_313_313_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B6_FRAME_313_313_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B6_FRAME_313_313_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_06.dbc, frame frame_313 (313, 0x139): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_115 (115, 0x073)
    on bus B6.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B6_FRAME_115_115_CHECKSUM_LENGTH != 8               \
    || (!CAP_B6_FRAME_115_115_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B6_FRAME_115_115_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B6_FRAME_115_115_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B6_FRAME_115_115_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_06.dbc, frame frame_115 (115, 0x073): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1574 (1574, 0x626)
    on bus B6.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B6_FRAME_1574_1574_CHECKSUM_LENGTH != 8               \
    || (!CAP_B6_FRAME_1574_1574_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B6_FRAME_1574_1574_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B6_FRAME_1574_1574_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B6_FRAME_1574_1574_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_06.dbc, frame frame_1574 (1574, 0x626): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1757 (1757, 0x6dd)
    on bus B6.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B6_FRAME_1757_1757_CHECKSUM_LENGTH != 8               \
    || (!CAP_B6_FRAME_1757_1757_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B6_FRAME_1757_1757_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B6_FRAME_1757_1757_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B6_FRAME_1757_1757_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_06.dbc, frame frame_1757 (1757, 0x6dd): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1469 (1469, 0x5bd)
    on bus B6.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B6_FRAME_1469_1469_CHECKSUM_LENGTH != 8               \
    || (!CAP_B6_FRAME_1469_1469_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B6_FRAME_1469_1469_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B6_FRAME_1469_1469_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B6_FRAME_1469_1469_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_06.dbc, frame frame_1469 (1469, 0x5bd): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1684 (1684, 0x694)
    on bus B6.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B6_FRAME_1684_1684_CHECKSUM_LENGTH != 8               \
    || (!CAP_B6_FRAME_1684_1684_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B6_FRAME_1684_1684_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B6_FRAME_1684_1684_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B6_FRAME_1684_1684_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_06.dbc, frame frame_1684 (1684, 0x694): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_505 (505, 0x1f9)
    on bus B6.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B6_FRAME_505_505_CHECKSUM_LENGTH != 8               \
    || (!CAP_B6_FRAME_505_505_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B6_FRAME_505_505_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B6_FRAME_505_505_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B6_FRAME_505_505_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_06.dbc, frame frame_505 (505, 0x1f9): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1310 (1310, 0x51e)
    on bus B6.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B6_FRAME_1310_1310_CHECKSUM_LENGTH != 8               \
    || (!CAP_B6_FRAME_1310_1310_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B6_FRAME_1310_1310_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B6_FRAME_1310_1310_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B6_FRAME_1310_1310_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_06.dbc, frame frame_1310 (1310, 0x51e): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_567 (567, 0x237)
    on bus B6.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B6_FRAME_567_567_CHECKSUM_LENGTH != 8               \
    || (!CAP_B6_FRAME_567_567_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B6_FRAME_567_567_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B6_FRAME_567_567_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B6_FRAME_567_567_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_06.dbc, frame frame_567 (567, 0x237): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1632 (1632, 0x660)
    on bus B6.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B6_FRAME_1632_1632_CHECKSUM_LENGTH != 8               \
    || (!CAP_B6_FRAME_1632_1632_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B6_FRAME_1632_1632_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B6_FRAME_1632_1632_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B6_FRAME_1632_1632_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_06.dbc, frame frame_1632 (1632, 0x660): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_345 (345, 0x159)
    on bus B6.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B6_FRAME_345_345_CHECKSUM_LENGTH != 8               \
    || (!CAP_B6_FRAME_345_345_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B6_FRAME_345_345_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B6_FRAME_345_345_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B6_FRAME_345_345_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_06.dbc, frame frame_345 (345, 0x159): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1918 (1918, 0x77e)
    on bus B6.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B6_FRAME_1918_1918_CHECKSUM_LENGTH != 8               \
    || (!CAP_B6_FRAME_1918_1918_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B6_FRAME_1918_1918_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B6_FRAME_1918_1918_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B6_FRAME_1918_1918_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_06.dbc, frame frame_1918 (1918, 0x77e): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1614 (1614, 0x64e)
    on bus B6.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B6_FRAME_1614_1614_CHECKSUM_LENGTH != 8               \
    || (!CAP_B6_FRAME_1614_1614_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B6_FRAME_1614_1614_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B6_FRAME_1614_1614_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B6_FRAME_1614_1614_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_06.dbc, frame frame_1614 (1614, 0x64e): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_858 (858, 0x35a)
    on bus B6.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B6_FRAME_858_858_CHECKSUM_LENGTH != 8               \
    || (!CAP_B6_FRAME_858_858_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B6_FRAME_858_858_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B6_FRAME_858_858_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B6_FRAME_858_858_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_06.dbc, frame frame_858 (858, 0x35a): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_467 (467, 0x1d3)
    on bus B6.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B6_FRAME_467_467_CHECKSUM_LENGTH != 8               \
    || (!CAP_B6_FRAME_467_467_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B6_FRAME_467_467_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B6_FRAME_467_467_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B6_FRAME_467_467_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_06.dbc, frame frame_467 (467, 0x1d3): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1754 (1754, 0x6da)
    on bus B6.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B6_FRAME_1754_1754_CHECKSUM_LENGTH != 8               \
    || (!CAP_B6_FRAME_1754_1754_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B6_FRAME_1754_1754_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B6_FRAME_1754_1754_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B6_FRAME_1754_1754_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_06.dbc, frame frame_1754 (1754, 0x6da): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_923 (923, 0x39b)
    on bus B6.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B6_FRAME_923_923_CHECKSUM_LENGTH != 8               \
    || (!CAP_B6_FRAME_923_923_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B6_FRAME_923_923_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B6_FRAME_923_923_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B6_FRAME_923_923_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_06.dbc, frame frame_923 (923, 0x39b): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_747 (747, 0x2eb)
    on bus B6.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B6_FRAME_747_747_CHECKSUM_LENGTH != 8               \
    || (!CAP_B6_FRAME_747_747_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B6_FRAME_747_747_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B6_FRAME_747_747_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B6_FRAME_747_747_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_06.dbc, frame frame_747 (747, 0x2eb): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_44 (44, 0x02c)
    on bus B6.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B6_FRAME_44_44_CHECKSUM_LENGTH != 8               \
    || (!CAP_B6_FRAME_44_44_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B6_FRAME_44_44_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B6_FRAME_44_44_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B6_FRAME_44_44_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_06.dbc, frame frame_44 (44, 0x02c): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_315 (315, 0x13b)
    on bus B6.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B6_FRAME_315_315_CHECKSUM_LENGTH != 8               \
    || (!CAP_B6_FRAME_315_315_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B6_FRAME_315_315_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B6_FRAME_315_315_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B6_FRAME_315_315_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_06.dbc, frame frame_315 (315, 0x13b): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1013 (1013, 0x3f5)
    on bus B6.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B6_FRAME_1013_1013_CHECKSUM_LENGTH != 8               \
    || (!CAP_B6_FRAME_1013_1013_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B6_FRAME_1013_1013_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B6_FRAME_1013_1013_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B6_FRAME_1013_1013_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_06.dbc, frame frame_1013 (1013, 0x3f5): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_582 (582, 0x246)
    on bus B6.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B6_FRAME_582_582_CHECKSUM_LENGTH != 8               \
    || (!CAP_B6_FRAME_582_582_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B6_FRAME_582_582_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B6_FRAME_582_582_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B6_FRAME_582_582_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_06.dbc, frame frame_582 (582, 0x246): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_291 (291, 0x123)
    on bus B6.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B6_FRAME_291_291_CHECKSUM_LENGTH != 8               \
    || (!CAP_B6_FRAME_291_291_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B6_FRAME_291_291_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B6_FRAME_291_291_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B6_FRAME_291_291_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_06.dbc, frame frame_291 (291, 0x123): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_137 (137, 0x089)
    on bus B6.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B6_FRAME_137_137_CHECKSUM_LENGTH != 8               \
    || (!CAP_B6_FRAME_137_137_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B6_FRAME_137_137_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B6_FRAME_137_137_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B6_FRAME_137_137_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_06.dbc, frame frame_137 (137, 0x089): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_782 (782, 0x30e)
    on bus B7.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B7_FRAME_782_782_CHECKSUM_LENGTH != 8               \
    || (!CAP_B7_FRAME_782_782_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B7_FRAME_782_782_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B7_FRAME_782_782_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B7_FRAME_782_782_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_07.dbc, frame frame_782 (782, 0x30e): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1125 (1125, 0x465)
    on bus B7.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B7_FRAME_1125_1125_CHECKSUM_LENGTH != 8               \
    || (!CAP_B7_FRAME_1125_1125_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B7_FRAME_1125_1125_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B7_FRAME_1125_1125_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B7_FRAME_1125_1125_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_07.dbc, frame frame_1125 (1125, 0x465): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1842 (1842, 0x732)
    on bus B7.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B7_FRAME_1842_1842_CHECKSUM_LENGTH != 8               \
    || (!CAP_B7_FRAME_1842_1842_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B7_FRAME_1842_1842_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B7_FRAME_1842_1842_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B7_FRAME_1842_1842_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_07.dbc, frame frame_1842 (1842, 0x732): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1429 (1429, 0x595)
    on bus B7.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B7_FRAME_1429_1429_CHECKSUM_LENGTH != 8               \
    || (!CAP_B7_FRAME_1429_1429_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B7_FRAME_1429_1429_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B7_FRAME_1429_1429_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B7_FRAME_1429_1429_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_07.dbc, frame frame_1429 (1429, 0x595): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_191 (191, 0x0bf)
    on bus B7.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B7_FRAME_191_191_CHECKSUM_LENGTH != 8               \
    || (!CAP_B7_FRAME_191_191_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B7_FRAME_191_191_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B7_FRAME_191_191_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B7_FRAME_191_191_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_07.dbc, frame frame_191 (191, 0x0bf): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1867 (1867, 0x74b)
    on bus B7.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B7_FRAME_1867_1867_CHECKSUM_LENGTH != 8               \
    || (!CAP_B7_FRAME_1867_1867_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B7_FRAME_1867_1867_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B7_FRAME_1867_1867_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B7_FRAME_1867_1867_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_07.dbc, frame frame_1867 (1867, 0x74b): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_967 (967, 0x3c7)
    on bus B7.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B7_FRAME_967_967_CHECKSUM_LENGTH != 8               \
    || (!CAP_B7_FRAME_967_967_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B7_FRAME_967_967_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B7_FRAME_967_967_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B7_FRAME_967_967_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_07.dbc, frame frame_967 (967, 0x3c7): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_61 (61, 0x03d)
    on bus B7.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B7_FRAME_61_61_CHECKSUM_LENGTH != 8               \
    || (!CAP_B7_FRAME_61_61_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B7_FRAME_61_61_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B7_FRAME_61_61_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B7_FRAME_61_61_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_07.dbc, frame frame_61 (61, 0x03d): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1403 (1403, 0x57b)
    on bus B7.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B7_FRAME_1403_1403_CHECKSUM_LENGTH != 8               \
    || (!CAP_B7_FRAME_1403_1403_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B7_FRAME_1403_1403_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B7_FRAME_1403_1403_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B7_FRAME_1403_1403_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_07.dbc, frame frame_1403 (1403, 0x57b): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1948 (1948, 0x79c)
    on bus B7.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B7_FRAME_1948_1948_CHECKSUM_LENGTH != 8               \
    || (!CAP_B7_FRAME_1948_1948_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B7_FRAME_1948_1948_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B7_FRAME_1948_1948_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B7_FRAME_1948_1948_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_07.dbc, frame frame_1948 (1948, 0x79c): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_462 (462, 0x1ce)
    on bus B7.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B7_FRAME_462_462_CHECKSUM_LENGTH != 8               \
    || (!CAP_B7_FRAME_462_462_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B7_FRAME_462_462_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B7_FRAME_462_462_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B7_FRAME_462_462_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_07.dbc, frame frame_462 (462, 0x1ce): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_158 (158, 0x09e)
    on bus B7.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B7_FRAME_158_158_CHECKSUM_LENGTH != 8               \
    || (!CAP_B7_FRAME_158_158_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B7_FRAME_158_158_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B7_FRAME_158_158_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B7_FRAME_158_158_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_07.dbc, frame frame_158 (158, 0x09e): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_673 (673, 0x2a1)
    on bus B7.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B7_FRAME_673_673_CHECKSUM_LENGTH != 8               \
    || (!CAP_B7_FRAME_673_673_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B7_FRAME_673_673_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B7_FRAME_673_673_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B7_FRAME_673_673_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_07.dbc, frame frame_673 (673, 0x2a1): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_422 (422, 0x1a6)
    on bus B7.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B7_FRAME_422_422_CHECKSUM_LENGTH != 8               \
    || (!CAP_B7_FRAME_422_422_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B7_FRAME_422_422_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B7_FRAME_422_422_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B7_FRAME_422_422_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_07.dbc, frame frame_422 (422, 0x1a6): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1821 (1821, 0x71d)
    on bus B7.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B7_FRAME_1821_1821_CHECKSUM_LENGTH != 8               \
    || (!CAP_B7_FRAME_1821_1821_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B7_FRAME_1821_1821_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B7_FRAME_1821_1821_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B7_FRAME_1821_1821_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_07.dbc, frame frame_1821 (1821, 0x71d): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1052 (1052, 0x41c)
    on bus B7.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B7_FRAME_1052_1052_CHECKSUM_LENGTH != 8               \
    || (!CAP_B7_FRAME_1052_1052_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B7_FRAME_1052_1052_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B7_FRAME_1052_1052_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B7_FRAME_1052_1052_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_07.dbc, frame frame_1052 (1052, 0x41c): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1380 (1380, 0x564)
    on bus B7.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B7_FRAME_1380_1380_CHECKSUM_LENGTH != 8               \
    || (!CAP_B7_FRAME_1380_1380_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B7_FRAME_1380_1380_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B7_FRAME_1380_1380_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B7_FRAME_1380_1380_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_07.dbc, frame frame_1380 (1380, 0x564): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1788 (1788, 0x6fc)
    on bus B7.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B7_FRAME_1788_1788_CHECKSUM_LENGTH != 8               \
    || (!CAP_B7_FRAME_1788_1788_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B7_FRAME_1788_1788_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B7_FRAME_1788_1788_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B7_FRAME_1788_1788_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_07.dbc, frame frame_1788 (1788, 0x6fc): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_255 (255, 0x0ff)
    on bus B7.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B7_FRAME_255_255_CHECKSUM_LENGTH != 8               \
    || (!CAP_B7_FRAME_255_255_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B7_FRAME_255_255_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B7_FRAME_255_255_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B7_FRAME_255_255_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_07.dbc, frame frame_255 (255, 0x0ff): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_586 (586, 0x24a)
    on bus B7.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B7_FRAME_586_586_CHECKSUM_LENGTH != 8               \
    || (!CAP_B7_FRAME_586_586_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B7_FRAME_586_586_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B7_FRAME_586_586_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B7_FRAME_586_586_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_07.dbc, frame frame_586 (586, 0x24a): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_914 (914, 0x392)
    on bus B7.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B7_FRAME_914_914_CHECKSUM_LENGTH != 8               \
    || (!CAP_B7_FRAME_914_914_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B7_FRAME_914_914_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B7_FRAME_914_914_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B7_FRAME_914_914_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_07.dbc, frame frame_914 (914, 0x392): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_565 (565, 0x235)
    on bus B7.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B7_FRAME_565_565_CHECKSUM_LENGTH != 8               \
    || (!CAP_B7_FRAME_565_565_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B7_FRAME_565_565_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B7_FRAME_565_565_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B7_FRAME_565_565_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_07.dbc, frame frame_565 (565, 0x235): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_53 (53, 0x035)
    on bus B7.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B7_FRAME_53_53_CHECKSUM_LENGTH != 8               \
    || (!CAP_B7_FRAME_53_53_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B7_FRAME_53_53_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B7_FRAME_53_53_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B7_FRAME_53_53_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_07.dbc, frame frame_53 (53, 0x035): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_752 (752, 0x2f0)
    on bus B7.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B7_FRAME_752_752_CHECKSUM_LENGTH != 8               \
    || (!CAP_B7_FRAME_752_752_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B7_FRAME_752_752_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B7_FRAME_752_752_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B7_FRAME_752_752_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_07.dbc, frame frame_752 (752, 0x2f0): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1312 (1312, 0x520)
    on bus B7.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B7_FRAME_1312_1312_CHECKSUM_LENGTH != 8               \
    || (!CAP_B7_FRAME_1312_1312_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B7_FRAME_1312_1312_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B7_FRAME_1312_1312_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B7_FRAME_1312_1312_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_07.dbc, frame frame_1312 (1312, 0x520): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_863 (863, 0x35f)
    on bus B7.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B7_FRAME_863_863_CHECKSUM_LENGTH != 8               \
    || (!CAP_B7_FRAME_863_863_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B7_FRAME_863_863_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B7_FRAME_863_863_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B7_FRAME_863_863_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_07.dbc, frame frame_863 (863, 0x35f): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1297 (1297, 0x511)
    on bus B7.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B7_FRAME_1297_1297_CHECKSUM_LENGTH != 8               \
    || (!CAP_B7_FRAME_1297_1297_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B7_FRAME_1297_1297_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B7_FRAME_1297_1297_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B7_FRAME_1297_1297_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_07.dbc, frame frame_1297 (1297, 0x511): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1535 (1535, 0x5ff)
    on bus B7.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B7_FRAME_1535_1535_CHECKSUM_LENGTH != 8               \
    || (!CAP_B7_FRAME_1535_1535_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B7_FRAME_1535_1535_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B7_FRAME_1535_1535_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B7_FRAME_1535_1535_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_07.dbc, frame frame_1535 (1535, 0x5ff): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1829 (1829, 0x725)
    on bus B7.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B7_FRAME_1829_1829_CHECKSUM_LENGTH != 8               \
    || (!CAP_B7_FRAME_1829_1829_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B7_FRAME_1829_1829_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B7_FRAME_1829_1829_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B7_FRAME_1829_1829_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_07.dbc, frame frame_1829 (1829, 0x725): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_262 (262, 0x106)
    on bus B7.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B7_FRAME_262_262_CHECKSUM_LENGTH != 8               \
    || (!CAP_B7_FRAME_262_262_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B7_FRAME_262_262_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B7_FRAME_262_262_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B7_FRAME_262_262_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_07.dbc, frame frame_262 (262, 0x106): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1208 (1208, 0x4b8)
    on bus B7.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B7_FRAME_1208_1208_CHECKSUM_LENGTH != 8               \
    || (!CAP_B7_FRAME_1208_1208_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B7_FRAME_1208_1208_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B7_FRAME_1208_1208_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B7_FRAME_1208_1208_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_07.dbc, frame frame_1208 (1208, 0x4b8): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1542 (1542, 0x606)
    on bus B7.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B7_FRAME_1542_1542_CHECKSUM_LENGTH != 8               \
    || (!CAP_B7_FRAME_1542_1542_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B7_FRAME_1542_1542_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B7_FRAME_1542_1542_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B7_FRAME_1542_1542_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_07.dbc, frame frame_1542 (1542, 0x606): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1341 (1341, 0x53d)
    on bus B7.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B7_FRAME_1341_1341_CHECKSUM_LENGTH != 8               \
    || (!CAP_B7_FRAME_1341_1341_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B7_FRAME_1341_1341_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B7_FRAME_1341_1341_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B7_FRAME_1341_1341_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_07.dbc, frame frame_1341 (1341, 0x53d): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1281 (1281, 0x501)
    on bus B7.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B7_FRAME_1281_1281_CHECKSUM_LENGTH != 8               \
    || (!CAP_B7_FRAME_1281_1281_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B7_FRAME_1281_1281_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B7_FRAME_1281_1281_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B7_FRAME_1281_1281_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_07.dbc, frame frame_1281 (1281, 0x501): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1119 (1119, 0x45f)
    on bus B7.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B7_FRAME_1119_1119_CHECKSUM_LENGTH != 8               \
    || (!CAP_B7_FRAME_1119_1119_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B7_FRAME_1119_1119_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B7_FRAME_1119_1119_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B7_FRAME_1119_1119_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_07.dbc, frame frame_1119 (1119, 0x45f): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_869 (869, 0x365)
    on bus B7.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B7_FRAME_869_869_CHECKSUM_LENGTH != 8               \
    || (!CAP_B7_FRAME_869_869_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B7_FRAME_869_869_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B7_FRAME_869_869_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B7_FRAME_869_869_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_07.dbc, frame frame_869 (869, 0x365): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1381 (1381, 0x565)
    on bus B7.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B7_FRAME_1381_1381_CHECKSUM_LENGTH != 8               \
    || (!CAP_B7_FRAME_1381_1381_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B7_FRAME_1381_1381_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B7_FRAME_1381_1381_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B7_FRAME_1381_1381_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_07.dbc, frame frame_1381 (1381, 0x565): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_678 (678, 0x2a6)
    on bus B7.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B7_FRAME_678_678_CHECKSUM_LENGTH != 8               \
    || (!CAP_B7_FRAME_678_678_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B7_FRAME_678_678_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B7_FRAME_678_678_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B7_FRAME_678_678_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_07.dbc, frame frame_678 (678, 0x2a6): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1157 (1157, 0x485)
    on bus B7.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B7_FRAME_1157_1157_CHECKSUM_LENGTH != 8               \
    || (!CAP_B7_FRAME_1157_1157_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B7_FRAME_1157_1157_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B7_FRAME_1157_1157_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B7_FRAME_1157_1157_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_07.dbc, frame frame_1157 (1157, 0x485): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_152 (152, 0x098)
    on bus B7.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B7_FRAME_152_152_CHECKSUM_LENGTH != 8               \
    || (!CAP_B7_FRAME_152_152_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B7_FRAME_152_152_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B7_FRAME_152_152_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B7_FRAME_152_152_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_07.dbc, frame frame_152 (152, 0x098): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1496 (1496, 0x5d8)
    on bus B7.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B7_FRAME_1496_1496_CHECKSUM_LENGTH != 8               \
    || (!CAP_B7_FRAME_1496_1496_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B7_FRAME_1496_1496_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B7_FRAME_1496_1496_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B7_FRAME_1496_1496_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_07.dbc, frame frame_1496 (1496, 0x5d8): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_111 (111, 0x06f)
    on bus B7.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B7_FRAME_111_111_CHECKSUM_LENGTH != 8               \
    || (!CAP_B7_FRAME_111_111_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B7_FRAME_111_111_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B7_FRAME_111_111_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B7_FRAME_111_111_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_07.dbc, frame frame_111 (111, 0x06f): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1237 (1237, 0x4d5)
    on bus B7.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B7_FRAME_1237_1237_CHECKSUM_LENGTH != 8               \
    || (!CAP_B7_FRAME_1237_1237_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B7_FRAME_1237_1237_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B7_FRAME_1237_1237_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B7_FRAME_1237_1237_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_07.dbc, frame frame_1237 (1237, 0x4d5): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_509 (509, 0x1fd)
    on bus B7.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B7_FRAME_509_509_CHECKSUM_LENGTH != 8               \
    || (!CAP_B7_FRAME_509_509_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B7_FRAME_509_509_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B7_FRAME_509_509_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B7_FRAME_509_509_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_07.dbc, frame frame_509 (509, 0x1fd): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_927 (927, 0x39f)
    on bus B7.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B7_FRAME_927_927_CHECKSUM_LENGTH != 8               \
    || (!CAP_B7_FRAME_927_927_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B7_FRAME_927_927_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B7_FRAME_927_927_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B7_FRAME_927_927_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_07.dbc, frame frame_927 (927, 0x39f): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_199 (199, 0x0c7)
    on bus B7.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B7_FRAME_199_199_CHECKSUM_LENGTH != 8               \
    || (!CAP_B7_FRAME_199_199_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B7_FRAME_199_199_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B7_FRAME_199_199_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B7_FRAME_199_199_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_07.dbc, frame frame_199 (199, 0x0c7): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1601 (1601, 0x641)
    on bus B7.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B7_FRAME_1601_1601_CHECKSUM_LENGTH != 8               \
    || (!CAP_B7_FRAME_1601_1601_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B7_FRAME_1601_1601_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B7_FRAME_1601_1601_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B7_FRAME_1601_1601_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_07.dbc, frame frame_1601 (1601, 0x641): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1931 (1931, 0x78b)
    on bus B7.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B7_FRAME_1931_1931_CHECKSUM_LENGTH != 8               \
    || (!CAP_B7_FRAME_1931_1931_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B7_FRAME_1931_1931_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B7_FRAME_1931_1931_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B7_FRAME_1931_1931_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_07.dbc, frame frame_1931 (1931, 0x78b): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_405 (405, 0x195)
    on bus B7.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B7_FRAME_405_405_CHECKSUM_LENGTH != 8               \
    || (!CAP_B7_FRAME_405_405_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B7_FRAME_405_405_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B7_FRAME_405_405_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B7_FRAME_405_405_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_07.dbc, frame frame_405 (405, 0x195): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1219 (1219, 0x4c3)
    on bus B7.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B7_FRAME_1219_1219_CHECKSUM_LENGTH != 8               \
    || (!CAP_B7_FRAME_1219_1219_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B7_FRAME_1219_1219_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B7_FRAME_1219_1219_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B7_FRAME_1219_1219_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_07.dbc, frame frame_1219 (1219, 0x4c3): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_788 (788, 0x314)
    on bus B7.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B7_FRAME_788_788_CHECKSUM_LENGTH != 8               \
    || (!CAP_B7_FRAME_788_788_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B7_FRAME_788_788_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B7_FRAME_788_788_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B7_FRAME_788_788_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_07.dbc, frame frame_788 (788, 0x314): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1689 (1689, 0x699)
    on bus B7.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B7_FRAME_1689_1689_CHECKSUM_LENGTH != 8               \
    || (!CAP_B7_FRAME_1689_1689_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B7_FRAME_1689_1689_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B7_FRAME_1689_1689_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B7_FRAME_1689_1689_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_07.dbc, frame frame_1689 (1689, 0x699): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_42 (42, 0x02a)
    on bus B7.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B7_FRAME_42_42_CHECKSUM_LENGTH != 8               \
    || (!CAP_B7_FRAME_42_42_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B7_FRAME_42_42_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B7_FRAME_42_42_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B7_FRAME_42_42_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_07.dbc, frame frame_42 (42, 0x02a): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1671 (1671, 0x687)
    on bus B7.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B7_FRAME_1671_1671_CHECKSUM_LENGTH != 8               \
    || (!CAP_B7_FRAME_1671_1671_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B7_FRAME_1671_1671_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B7_FRAME_1671_1671_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B7_FRAME_1671_1671_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_07.dbc, frame frame_1671 (1671, 0x687): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1890 (1890, 0x762)
    on bus B7.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B7_FRAME_1890_1890_CHECKSUM_LENGTH != 8               \
    || (!CAP_B7_FRAME_1890_1890_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B7_FRAME_1890_1890_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B7_FRAME_1890_1890_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B7_FRAME_1890_1890_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_07.dbc, frame frame_1890 (1890, 0x762): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_434 (434, 0x1b2)
    on bus B7.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B7_FRAME_434_434_CHECKSUM_LENGTH != 8               \
    || (!CAP_B7_FRAME_434_434_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B7_FRAME_434_434_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B7_FRAME_434_434_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B7_FRAME_434_434_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_07.dbc, frame frame_434 (434, 0x1b2): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1389 (1389, 0x56d)
    on bus B7.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B7_FRAME_1389_1389_CHECKSUM_LENGTH != 8               \
    || (!CAP_B7_FRAME_1389_1389_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B7_FRAME_1389_1389_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B7_FRAME_1389_1389_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B7_FRAME_1389_1389_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_07.dbc, frame frame_1389 (1389, 0x56d): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_141 (141, 0x08d)
    on bus B7.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B7_FRAME_141_141_CHECKSUM_LENGTH != 8               \
    || (!CAP_B7_FRAME_141_141_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B7_FRAME_141_141_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B7_FRAME_141_141_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B7_FRAME_141_141_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_07.dbc, frame frame_141 (141, 0x08d): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1524 (1524, 0x5f4)
    on bus B7.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B7_FRAME_1524_1524_CHECKSUM_LENGTH != 8               \
    || (!CAP_B7_FRAME_1524_1524_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B7_FRAME_1524_1524_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B7_FRAME_1524_1524_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B7_FRAME_1524_1524_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_07.dbc, frame frame_1524 (1524, 0x5f4): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_924 (924, 0x39c)
    on bus B7.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B7_FRAME_924_924_CHECKSUM_LENGTH != 8               \
    || (!CAP_B7_FRAME_924_924_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B7_FRAME_924_924_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B7_FRAME_924_924_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B7_FRAME_924_924_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_07.dbc, frame frame_924 (924, 0x39c): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1022 (1022, 0x3fe)
    on bus B7.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B7_FRAME_1022_1022_CHECKSUM_LENGTH != 8               \
    || (!CAP_B7_FRAME_1022_1022_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B7_FRAME_1022_1022_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B7_FRAME_1022_1022_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B7_FRAME_1022_1022_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_07.dbc, frame frame_1022 (1022, 0x3fe): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_412 (412, 0x19c)
    on bus B7.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B7_FRAME_412_412_CHECKSUM_LENGTH != 8               \
    || (!CAP_B7_FRAME_412_412_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B7_FRAME_412_412_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B7_FRAME_412_412_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B7_FRAME_412_412_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_07.dbc, frame frame_412 (412, 0x19c): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_592 (592, 0x250)
    on bus B7.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B7_FRAME_592_592_CHECKSUM_LENGTH != 8               \
    || (!CAP_B7_FRAME_592_592_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B7_FRAME_592_592_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B7_FRAME_592_592_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B7_FRAME_592_592_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_07.dbc, frame frame_592 (592, 0x250): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1813 (1813, 0x715)
    on bus B7.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B7_FRAME_1813_1813_CHECKSUM_LENGTH != 8               \
    || (!CAP_B7_FRAME_1813_1813_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B7_FRAME_1813_1813_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B7_FRAME_1813_1813_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B7_FRAME_1813_1813_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_07.dbc, frame frame_1813 (1813, 0x715): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1323 (1323, 0x52b)
    on bus B7.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B7_FRAME_1323_1323_CHECKSUM_LENGTH != 8               \
    || (!CAP_B7_FRAME_1323_1323_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B7_FRAME_1323_1323_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B7_FRAME_1323_1323_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B7_FRAME_1323_1323_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_07.dbc, frame frame_1323 (1323, 0x52b): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_334 (334, 0x14e)
    on bus B7.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B7_FRAME_334_334_CHECKSUM_LENGTH != 8               \
    || (!CAP_B7_FRAME_334_334_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B7_FRAME_334_334_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B7_FRAME_334_334_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B7_FRAME_334_334_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_07.dbc, frame frame_334 (334, 0x14e): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_18 (18, 0x012)
    on bus B7.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B7_FRAME_18_18_CHECKSUM_LENGTH != 8               \
    || (!CAP_B7_FRAME_18_18_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B7_FRAME_18_18_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B7_FRAME_18_18_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B7_FRAME_18_18_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_07.dbc, frame frame_18 (18, 0x012): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_793 (793, 0x319)
    on bus B7.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B7_FRAME_793_793_CHECKSUM_LENGTH != 8               \
    || (!CAP_B7_FRAME_793_793_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B7_FRAME_793_793_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B7_FRAME_793_793_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B7_FRAME_793_793_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_07.dbc, frame frame_793 (793, 0x319): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1302 (1302, 0x516)
    on bus B7.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B7_FRAME_1302_1302_CHECKSUM_LENGTH != 8               \
    || (!CAP_B7_FRAME_1302_1302_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B7_FRAME_1302_1302_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B7_FRAME_1302_1302_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B7_FRAME_1302_1302_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_07.dbc, frame frame_1302 (1302, 0x516): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1622 (1622, 0x656)
    on bus B7.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B7_FRAME_1622_1622_CHECKSUM_LENGTH != 8               \
    || (!CAP_B7_FRAME_1622_1622_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B7_FRAME_1622_1622_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B7_FRAME_1622_1622_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B7_FRAME_1622_1622_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_07.dbc, frame frame_1622 (1622, 0x656): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_465 (465, 0x1d1)
    on bus B7.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B7_FRAME_465_465_CHECKSUM_LENGTH != 8               \
    || (!CAP_B7_FRAME_465_465_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B7_FRAME_465_465_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B7_FRAME_465_465_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B7_FRAME_465_465_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_07.dbc, frame frame_465 (465, 0x1d1): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1997 (1997, 0x7cd)
    on bus B7.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B7_FRAME_1997_1997_CHECKSUM_LENGTH != 8               \
    || (!CAP_B7_FRAME_1997_1997_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B7_FRAME_1997_1997_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B7_FRAME_1997_1997_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B7_FRAME_1997_1997_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_07.dbc, frame frame_1997 (1997, 0x7cd): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_294 (294, 0x126)
    on bus B7.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B7_FRAME_294_294_CHECKSUM_LENGTH != 8               \
    || (!CAP_B7_FRAME_294_294_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B7_FRAME_294_294_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B7_FRAME_294_294_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B7_FRAME_294_294_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_07.dbc, frame frame_294 (294, 0x126): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_82 (82, 0x052)
    on bus B7.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B7_FRAME_82_82_CHECKSUM_LENGTH != 8               \
    || (!CAP_B7_FRAME_82_82_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B7_FRAME_82_82_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B7_FRAME_82_82_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B7_FRAME_82_82_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_07.dbc, frame frame_82 (82, 0x052): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1816 (1816, 0x718)
    on bus B7.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B7_FRAME_1816_1816_CHECKSUM_LENGTH != 8               \
    || (!CAP_B7_FRAME_1816_1816_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B7_FRAME_1816_1816_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B7_FRAME_1816_1816_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B7_FRAME_1816_1816_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_07.dbc, frame frame_1816 (1816, 0x718): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_159 (159, 0x09f)
    on bus B7.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B7_FRAME_159_159_CHECKSUM_LENGTH != 8               \
    || (!CAP_B7_FRAME_159_159_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B7_FRAME_159_159_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B7_FRAME_159_159_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B7_FRAME_159_159_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_07.dbc, frame frame_159 (159, 0x09f): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1449 (1449, 0x5a9)
    on bus B7.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B7_FRAME_1449_1449_CHECKSUM_LENGTH != 8               \
    || (!CAP_B7_FRAME_1449_1449_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B7_FRAME_1449_1449_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B7_FRAME_1449_1449_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B7_FRAME_1449_1449_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_07.dbc, frame frame_1449 (1449, 0x5a9): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1177 (1177, 0x499)
    on bus B7.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B7_FRAME_1177_1177_CHECKSUM_LENGTH != 8               \
    || (!CAP_B7_FRAME_1177_1177_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B7_FRAME_1177_1177_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B7_FRAME_1177_1177_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B7_FRAME_1177_1177_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_07.dbc, frame frame_1177 (1177, 0x499): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1356 (1356, 0x54c)
    on bus B7.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B7_FRAME_1356_1356_CHECKSUM_LENGTH != 8               \
    || (!CAP_B7_FRAME_1356_1356_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B7_FRAME_1356_1356_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B7_FRAME_1356_1356_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B7_FRAME_1356_1356_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_07.dbc, frame frame_1356 (1356, 0x54c): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_875 (875, 0x36b)
    on bus B7.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B7_FRAME_875_875_CHECKSUM_LENGTH != 8               \
    || (!CAP_B7_FRAME_875_875_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B7_FRAME_875_875_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B7_FRAME_875_875_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B7_FRAME_875_875_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_07.dbc, frame frame_875 (875, 0x36b): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_593 (593, 0x251)
    on bus B7.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B7_FRAME_593_593_CHECKSUM_LENGTH != 8               \
    || (!CAP_B7_FRAME_593_593_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B7_FRAME_593_593_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B7_FRAME_593_593_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B7_FRAME_593_593_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_07.dbc, frame frame_593 (593, 0x251): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1592 (1592, 0x638)
    on bus B7.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B7_FRAME_1592_1592_CHECKSUM_LENGTH != 8               \
    || (!CAP_B7_FRAME_1592_1592_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B7_FRAME_1592_1592_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B7_FRAME_1592_1592_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B7_FRAME_1592_1592_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_07.dbc, frame frame_1592 (1592, 0x638): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1870 (1870, 0x74e)
    on bus B7.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B7_FRAME_1870_1870_CHECKSUM_LENGTH != 8               \
    || (!CAP_B7_FRAME_1870_1870_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B7_FRAME_1870_1870_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B7_FRAME_1870_1870_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B7_FRAME_1870_1870_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_07.dbc, frame frame_1870 (1870, 0x74e): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1475 (1475, 0x5c3)
    on bus B7.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B7_FRAME_1475_1475_CHECKSUM_LENGTH != 8               \
    || (!CAP_B7_FRAME_1475_1475_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B7_FRAME_1475_1475_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B7_FRAME_1475_1475_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B7_FRAME_1475_1475_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_07.dbc, frame frame_1475 (1475, 0x5c3): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_440 (440, 0x1b8)
    on bus B7.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B7_FRAME_440_440_CHECKSUM_LENGTH != 8               \
    || (!CAP_B7_FRAME_440_440_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B7_FRAME_440_440_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B7_FRAME_440_440_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B7_FRAME_440_440_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_07.dbc, frame frame_440 (440, 0x1b8): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1080 (1080, 0x438)
    on bus B7.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B7_FRAME_1080_1080_CHECKSUM_LENGTH != 8               \
    || (!CAP_B7_FRAME_1080_1080_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B7_FRAME_1080_1080_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B7_FRAME_1080_1080_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B7_FRAME_1080_1080_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_07.dbc, frame frame_1080 (1080, 0x438): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_2000 (2000, 0x7d0)
    on bus B7.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B7_FRAME_2000_2000_CHECKSUM_LENGTH != 8               \
    || (!CAP_B7_FRAME_2000_2000_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B7_FRAME_2000_2000_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B7_FRAME_2000_2000_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B7_FRAME_2000_2000_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_07.dbc, frame frame_2000 (2000, 0x7d0): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_192 (192, 0x0c0)
    on bus B7.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B7_FRAME_192_192_CHECKSUM_LENGTH != 8               \
    || (!CAP_B7_FRAME_192_192_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B7_FRAME_192_192_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B7_FRAME_192_192_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B7_FRAME_192_192_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_07.dbc, frame frame_192 (192, 0x0c0): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1954 (1954, 0x7a2)
    on bus B7.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B7_FRAME_1954_1954_CHECKSUM_LENGTH != 8               \
    || (!CAP_B7_FRAME_1954_1954_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B7_FRAME_1954_1954_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B7_FRAME_1954_1954_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B7_FRAME_1954_1954_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_07.dbc, frame frame_1954 (1954, 0x7a2): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1055 (1055, 0x41f)
    on bus B7.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B7_FRAME_1055_1055_CHECKSUM_LENGTH != 8               \
    || (!CAP_B7_FRAME_1055_1055_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B7_FRAME_1055_1055_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B7_FRAME_1055_1055_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B7_FRAME_1055_1055_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_07.dbc, frame frame_1055 (1055, 0x41f): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1993 (1993, 0x7c9)
    on bus B7.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B7_FRAME_1993_1993_CHECKSUM_LENGTH != 8               \
    || (!CAP_B7_FRAME_1993_1993_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B7_FRAME_1993_1993_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B7_FRAME_1993_1993_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B7_FRAME_1993_1993_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_07.dbc, frame frame_1993 (1993, 0x7c9): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_234 (234, 0x0ea)
    on bus B7.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B7_FRAME_234_234_CHECKSUM_LENGTH != 8               \
    || (!CAP_B7_FRAME_234_234_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B7_FRAME_234_234_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B7_FRAME_234_234_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B7_FRAME_234_234_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_07.dbc, frame frame_234 (234, 0x0ea): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1075 (1075, 0x433)
    on bus B7.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B7_FRAME_1075_1075_CHECKSUM_LENGTH != 8               \
    || (!CAP_B7_FRAME_1075_1075_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B7_FRAME_1075_1075_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B7_FRAME_1075_1075_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B7_FRAME_1075_1075_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_07.dbc, frame frame_1075 (1075, 0x433): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_845 (845, 0x34d)
    on bus B7.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B7_FRAME_845_845_CHECKSUM_LENGTH != 8               \
    || (!CAP_B7_FRAME_845_845_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B7_FRAME_845_845_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B7_FRAME_845_845_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B7_FRAME_845_845_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_07.dbc, frame frame_845 (845, 0x34d): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_605 (605, 0x25d)
    on bus B7.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B7_FRAME_605_605_CHECKSUM_LENGTH != 8               \
    || (!CAP_B7_FRAME_605_605_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B7_FRAME_605_605_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B7_FRAME_605_605_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B7_FRAME_605_605_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_07.dbc, frame frame_605 (605, 0x25d): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1330 (1330, 0x532)
    on bus B7.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B7_FRAME_1330_1330_CHECKSUM_LENGTH != 8               \
    || (!CAP_B7_FRAME_1330_1330_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B7_FRAME_1330_1330_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B7_FRAME_1330_1330_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B7_FRAME_1330_1330_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_07.dbc, frame frame_1330 (1330, 0x532): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1249 (1249, 0x4e1)
    on bus B8.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B8_FRAME_1249_1249_CHECKSUM_LENGTH != 8               \
    || (!CAP_B8_FRAME_1249_1249_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B8_FRAME_1249_1249_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B8_FRAME_1249_1249_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B8_FRAME_1249_1249_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_08.dbc, frame frame_1249 (1249, 0x4e1): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_579 (579, 0x243)
    on bus B8.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B8_FRAME_579_579_CHECKSUM_LENGTH != 8               \
    || (!CAP_B8_FRAME_579_579_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B8_FRAME_579_579_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B8_FRAME_579_579_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B8_FRAME_579_579_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_08.dbc, frame frame_579 (579, 0x243): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_392 (392, 0x188)
    on bus B8.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B8_FRAME_392_392_CHECKSUM_LENGTH != 8               \
    || (!CAP_B8_FRAME_392_392_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B8_FRAME_392_392_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B8_FRAME_392_392_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B8_FRAME_392_392_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_08.dbc, frame frame_392 (392, 0x188): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_891 (891, 0x37b)
    on bus B8.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B8_FRAME_891_891_CHECKSUM_LENGTH != 8               \
    || (!CAP_B8_FRAME_891_891_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B8_FRAME_891_891_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B8_FRAME_891_891_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B8_FRAME_891_891_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_08.dbc, frame frame_891 (891, 0x37b): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1082 (1082, 0x43a)
    on bus B8.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B8_FRAME_1082_1082_CHECKSUM_LENGTH != 8               \
    || (!CAP_B8_FRAME_1082_1082_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B8_FRAME_1082_1082_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B8_FRAME_1082_1082_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B8_FRAME_1082_1082_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_08.dbc, frame frame_1082 (1082, 0x43a): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_878 (878, 0x36e)
    on bus B8.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B8_FRAME_878_878_CHECKSUM_LENGTH != 8               \
    || (!CAP_B8_FRAME_878_878_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B8_FRAME_878_878_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B8_FRAME_878_878_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B8_FRAME_878_878_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_08.dbc, frame frame_878 (878, 0x36e): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_299 (299, 0x12b)
    on bus B8.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B8_FRAME_299_299_CHECKSUM_LENGTH != 8               \
    || (!CAP_B8_FRAME_299_299_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B8_FRAME_299_299_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B8_FRAME_299_299_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B8_FRAME_299_299_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_08.dbc, frame frame_299 (299, 0x12b): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1921 (1921, 0x781)
    on bus B8.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B8_FRAME_1921_1921_CHECKSUM_LENGTH != 8               \
    || (!CAP_B8_FRAME_1921_1921_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B8_FRAME_1921_1921_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B8_FRAME_1921_1921_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B8_FRAME_1921_1921_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_08.dbc, frame frame_1921 (1921, 0x781): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_754 (754, 0x2f2)
    on bus B8.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B8_FRAME_754_754_CHECKSUM_LENGTH != 8               \
    || (!CAP_B8_FRAME_754_754_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B8_FRAME_754_754_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B8_FRAME_754_754_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B8_FRAME_754_754_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_08.dbc, frame frame_754 (754, 0x2f2): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_838 (838, 0x346)
    on bus B8.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B8_FRAME_838_838_CHECKSUM_LENGTH != 8               \
    || (!CAP_B8_FRAME_838_838_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B8_FRAME_838_838_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B8_FRAME_838_838_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B8_FRAME_838_838_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_08.dbc, frame frame_838 (838, 0x346): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_33 (33, 0x021)
    on bus B8.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B8_FRAME_33_33_CHECKSUM_LENGTH != 8               \
    || (!CAP_B8_FRAME_33_33_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B8_FRAME_33_33_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B8_FRAME_33_33_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B8_FRAME_33_33_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_08.dbc, frame frame_33 (33, 0x021): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1076 (1076, 0x434)
    on bus B8.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B8_FRAME_1076_1076_CHECKSUM_LENGTH != 8               \
    || (!CAP_B8_FRAME_1076_1076_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B8_FRAME_1076_1076_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B8_FRAME_1076_1076_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B8_FRAME_1076_1076_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_08.dbc, frame frame_1076 (1076, 0x434): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_16 (16, 0x010)
    on bus B8.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B8_FRAME_16_16_CHECKSUM_LENGTH != 8               \
    || (!CAP_B8_FRAME_16_16_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B8_FRAME_16_16_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B8_FRAME_16_16_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B8_FRAME_16_16_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_08.dbc, frame frame_16 (16, 0x010): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1578 (1578, 0x62a)
    on bus B8.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B8_FRAME_1578_1578_CHECKSUM_LENGTH != 8               \
    || (!CAP_B8_FRAME_1578_1578_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B8_FRAME_1578_1578_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B8_FRAME_1578_1578_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B8_FRAME_1578_1578_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_08.dbc, frame frame_1578 (1578, 0x62a): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1550 (1550, 0x60e)
    on bus B8.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B8_FRAME_1550_1550_CHECKSUM_LENGTH != 8               \
    || (!CAP_B8_FRAME_1550_1550_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B8_FRAME_1550_1550_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B8_FRAME_1550_1550_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B8_FRAME_1550_1550_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_08.dbc, frame frame_1550 (1550, 0x60e): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1636 (1636, 0x664)
    on bus B8.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B8_FRAME_1636_1636_CHECKSUM_LENGTH != 8               \
    || (!CAP_B8_FRAME_1636_1636_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B8_FRAME_1636_1636_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B8_FRAME_1636_1636_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B8_FRAME_1636_1636_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_08.dbc, frame frame_1636 (1636, 0x664): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_24 (24, 0x018)
    on bus B8.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B8_FRAME_24_24_CHECKSUM_LENGTH != 8               \
    || (!CAP_B8_FRAME_24_24_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B8_FRAME_24_24_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B8_FRAME_24_24_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B8_FRAME_24_24_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_08.dbc, frame frame_24 (24, 0x018): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_880 (880, 0x370)
    on bus B8.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B8_FRAME_880_880_CHECKSUM_LENGTH != 8               \
    || (!CAP_B8_FRAME_880_880_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B8_FRAME_880_880_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B8_FRAME_880_880_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B8_FRAME_880_880_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_08.dbc, frame frame_880 (880, 0x370): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_575 (575, 0x23f)
    on bus B8.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B8_FRAME_575_575_CHECKSUM_LENGTH != 8               \
    || (!CAP_B8_FRAME_575_575_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B8_FRAME_575_575_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B8_FRAME_575_575_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B8_FRAME_575_575_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_08.dbc, frame frame_575 (575, 0x23f): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_931 (931, 0x3a3)
    on bus B8.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B8_FRAME_931_931_CHECKSUM_LENGTH != 8               \
    || (!CAP_B8_FRAME_931_931_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B8_FRAME_931_931_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B8_FRAME_931_931_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B8_FRAME_931_931_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_08.dbc, frame frame_931 (931, 0x3a3): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_525 (525, 0x20d)
    on bus B8.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B8_FRAME_525_525_CHECKSUM_LENGTH != 8               \
    || (!CAP_B8_FRAME_525_525_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B8_FRAME_525_525_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B8_FRAME_525_525_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B8_FRAME_525_525_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_08.dbc, frame frame_525 (525, 0x20d): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1645 (1645, 0x66d)
    on bus B8.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B8_FRAME_1645_1645_CHECKSUM_LENGTH != 8               \
    || (!CAP_B8_FRAME_1645_1645_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B8_FRAME_1645_1645_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B8_FRAME_1645_1645_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B8_FRAME_1645_1645_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_08.dbc, frame frame_1645 (1645, 0x66d): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_646 (646, 0x286)
    on bus B8.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B8_FRAME_646_646_CHECKSUM_LENGTH != 8               \
    || (!CAP_B8_FRAME_646_646_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B8_FRAME_646_646_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B8_FRAME_646_646_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B8_FRAME_646_646_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_08.dbc, frame frame_646 (646, 0x286): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_85 (85, 0x055)
    on bus B8.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B8_FRAME_85_85_CHECKSUM_LENGTH != 8               \
    || (!CAP_B8_FRAME_85_85_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B8_FRAME_85_85_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B8_FRAME_85_85_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B8_FRAME_85_85_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_08.dbc, frame frame_85 (85, 0x055): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1832 (1832, 0x728)
    on bus B8.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B8_FRAME_1832_1832_CHECKSUM_LENGTH != 8               \
    || (!CAP_B8_FRAME_1832_1832_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B8_FRAME_1832_1832_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B8_FRAME_1832_1832_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B8_FRAME_1832_1832_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_08.dbc, frame frame_1832 (1832, 0x728): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1598 (1598, 0x63e)
    on bus B8.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B8_FRAME_1598_1598_CHECKSUM_LENGTH != 8               \
    || (!CAP_B8_FRAME_1598_1598_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B8_FRAME_1598_1598_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B8_FRAME_1598_1598_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B8_FRAME_1598_1598_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_08.dbc, frame frame_1598 (1598, 0x63e): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_696 (696, 0x2b8)
    on bus B8.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B8_FRAME_696_696_CHECKSUM_LENGTH != 8               \
    || (!CAP_B8_FRAME_696_696_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B8_FRAME_696_696_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B8_FRAME_696_696_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B8_FRAME_696_696_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_08.dbc, frame frame_696 (696, 0x2b8): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1933 (1933, 0x78d)
    on bus B8.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B8_FRAME_1933_1933_CHECKSUM_LENGTH != 8               \
    || (!CAP_B8_FRAME_1933_1933_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B8_FRAME_1933_1933_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B8_FRAME_1933_1933_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B8_FRAME_1933_1933_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_08.dbc, frame frame_1933 (1933, 0x78d): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_991 (991, 0x3df)
    on bus B8.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B8_FRAME_991_991_CHECKSUM_LENGTH != 8               \
    || (!CAP_B8_FRAME_991_991_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B8_FRAME_991_991_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B8_FRAME_991_991_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B8_FRAME_991_991_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_08.dbc, frame frame_991 (991, 0x3df): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1959 (1959, 0x7a7)
    on bus B8.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B8_FRAME_1959_1959_CHECKSUM_LENGTH != 8               \
    || (!CAP_B8_FRAME_1959_1959_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B8_FRAME_1959_1959_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B8_FRAME_1959_1959_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B8_FRAME_1959_1959_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_08.dbc, frame frame_1959 (1959, 0x7a7): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_748 (748, 0x2ec)
    on bus B8.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B8_FRAME_748_748_CHECKSUM_LENGTH != 8               \
    || (!CAP_B8_FRAME_748_748_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B8_FRAME_748_748_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B8_FRAME_748_748_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B8_FRAME_748_748_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_08.dbc, frame frame_748 (748, 0x2ec): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1566 (1566, 0x61e)
    on bus B8.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B8_FRAME_1566_1566_CHECKSUM_LENGTH != 8               \
    || (!CAP_B8_FRAME_1566_1566_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B8_FRAME_1566_1566_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B8_FRAME_1566_1566_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B8_FRAME_1566_1566_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_08.dbc, frame frame_1566 (1566, 0x61e): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_722 (722, 0x2d2)
    on bus B8.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B8_FRAME_722_722_CHECKSUM_LENGTH != 8               \
    || (!CAP_B8_FRAME_722_722_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B8_FRAME_722_722_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B8_FRAME_722_722_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B8_FRAME_722_722_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_08.dbc, frame frame_722 (722, 0x2d2): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_632 (632, 0x278)
    on bus B8.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B8_FRAME_632_632_CHECKSUM_LENGTH != 8               \
    || (!CAP_B8_FRAME_632_632_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B8_FRAME_632_632_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B8_FRAME_632_632_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B8_FRAME_632_632_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_08.dbc, frame frame_632 (632, 0x278): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1388 (1388, 0x56c)
    on bus B8.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B8_FRAME_1388_1388_CHECKSUM_LENGTH != 8               \
    || (!CAP_B8_FRAME_1388_1388_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B8_FRAME_1388_1388_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B8_FRAME_1388_1388_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B8_FRAME_1388_1388_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_08.dbc, frame frame_1388 (1388, 0x56c): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1817 (1817, 0x719)
    on bus B8.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B8_FRAME_1817_1817_CHECKSUM_LENGTH != 8               \
    || (!CAP_B8_FRAME_1817_1817_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B8_FRAME_1817_1817_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B8_FRAME_1817_1817_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B8_FRAME_1817_1817_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_08.dbc, frame frame_1817 (1817, 0x719): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_755 (755, 0x2f3)
    on bus B8.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B8_FRAME_755_755_CHECKSUM_LENGTH != 8               \
    || (!CAP_B8_FRAME_755_755_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B8_FRAME_755_755_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B8_FRAME_755_755_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B8_FRAME_755_755_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_08.dbc, frame frame_755 (755, 0x2f3): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1910 (1910, 0x776)
    on bus B8.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B8_FRAME_1910_1910_CHECKSUM_LENGTH != 8               \
    || (!CAP_B8_FRAME_1910_1910_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B8_FRAME_1910_1910_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B8_FRAME_1910_1910_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B8_FRAME_1910_1910_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_08.dbc, frame frame_1910 (1910, 0x776): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_966 (966, 0x3c6)
    on bus B8.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B8_FRAME_966_966_CHECKSUM_LENGTH != 8               \
    || (!CAP_B8_FRAME_966_966_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B8_FRAME_966_966_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B8_FRAME_966_966_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B8_FRAME_966_966_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_08.dbc, frame frame_966 (966, 0x3c6): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_75 (75, 0x04b)
    on bus B8.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B8_FRAME_75_75_CHECKSUM_LENGTH != 8               \
    || (!CAP_B8_FRAME_75_75_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B8_FRAME_75_75_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B8_FRAME_75_75_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B8_FRAME_75_75_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_08.dbc, frame frame_75 (75, 0x04b): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1961 (1961, 0x7a9)
    on bus B8.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B8_FRAME_1961_1961_CHECKSUM_LENGTH != 8               \
    || (!CAP_B8_FRAME_1961_1961_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B8_FRAME_1961_1961_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B8_FRAME_1961_1961_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B8_FRAME_1961_1961_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_08.dbc, frame frame_1961 (1961, 0x7a9): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1687 (1687, 0x697)
    on bus B8.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B8_FRAME_1687_1687_CHECKSUM_LENGTH != 8               \
    || (!CAP_B8_FRAME_1687_1687_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B8_FRAME_1687_1687_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B8_FRAME_1687_1687_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B8_FRAME_1687_1687_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_08.dbc, frame frame_1687 (1687, 0x697): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1946 (1946, 0x79a)
    on bus B8.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B8_FRAME_1946_1946_CHECKSUM_LENGTH != 8               \
    || (!CAP_B8_FRAME_1946_1946_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B8_FRAME_1946_1946_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B8_FRAME_1946_1946_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B8_FRAME_1946_1946_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_08.dbc, frame frame_1946 (1946, 0x79a): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1663 (1663, 0x67f)
    on bus B8.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B8_FRAME_1663_1663_CHECKSUM_LENGTH != 8               \
    || (!CAP_B8_FRAME_1663_1663_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B8_FRAME_1663_1663_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B8_FRAME_1663_1663_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B8_FRAME_1663_1663_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_08.dbc, frame frame_1663 (1663, 0x67f): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1193 (1193, 0x4a9)
    on bus B8.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B8_FRAME_1193_1193_CHECKSUM_LENGTH != 8               \
    || (!CAP_B8_FRAME_1193_1193_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B8_FRAME_1193_1193_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B8_FRAME_1193_1193_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B8_FRAME_1193_1193_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_08.dbc, frame frame_1193 (1193, 0x4a9): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_95 (95, 0x05f)
    on bus B8.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B8_FRAME_95_95_CHECKSUM_LENGTH != 8               \
    || (!CAP_B8_FRAME_95_95_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B8_FRAME_95_95_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B8_FRAME_95_95_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B8_FRAME_95_95_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_08.dbc, frame frame_95 (95, 0x05f): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1510 (1510, 0x5e6)
    on bus B8.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B8_FRAME_1510_1510_CHECKSUM_LENGTH != 8               \
    || (!CAP_B8_FRAME_1510_1510_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B8_FRAME_1510_1510_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B8_FRAME_1510_1510_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B8_FRAME_1510_1510_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_08.dbc, frame frame_1510 (1510, 0x5e6): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1678 (1678, 0x68e)
    on bus B8.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B8_FRAME_1678_1678_CHECKSUM_LENGTH != 8               \
    || (!CAP_B8_FRAME_1678_1678_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B8_FRAME_1678_1678_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B8_FRAME_1678_1678_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B8_FRAME_1678_1678_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_08.dbc, frame frame_1678 (1678, 0x68e): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1812 (1812, 0x714)
    on bus B8.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B8_FRAME_1812_1812_CHECKSUM_LENGTH != 8               \
    || (!CAP_B8_FRAME_1812_1812_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B8_FRAME_1812_1812_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B8_FRAME_1812_1812_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B8_FRAME_1812_1812_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_08.dbc, frame frame_1812 (1812, 0x714): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1131 (1131, 0x46b)
    on bus B8.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B8_FRAME_1131_1131_CHECKSUM_LENGTH != 8               \
    || (!CAP_B8_FRAME_1131_1131_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B8_FRAME_1131_1131_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B8_FRAME_1131_1131_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B8_FRAME_1131_1131_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_08.dbc, frame frame_1131 (1131, 0x46b): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_625 (625, 0x271)
    on bus B8.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B8_FRAME_625_625_CHECKSUM_LENGTH != 8               \
    || (!CAP_B8_FRAME_625_625_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B8_FRAME_625_625_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B8_FRAME_625_625_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B8_FRAME_625_625_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_08.dbc, frame frame_625 (625, 0x271): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_204 (204, 0x0cc)
    on bus B8.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B8_FRAME_204_204_CHECKSUM_LENGTH != 8               \
    || (!CAP_B8_FRAME_204_204_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B8_FRAME_204_204_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B8_FRAME_204_204_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B8_FRAME_204_204_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_08.dbc, frame frame_204 (204, 0x0cc): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1700 (1700, 0x6a4)
    on bus B8.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B8_FRAME_1700_1700_CHECKSUM_LENGTH != 8               \
    || (!CAP_B8_FRAME_1700_1700_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B8_FRAME_1700_1700_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B8_FRAME_1700_1700_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B8_FRAME_1700_1700_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_08.dbc, frame frame_1700 (1700, 0x6a4): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1460 (1460, 0x5b4)
    on bus B8.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B8_FRAME_1460_1460_CHECKSUM_LENGTH != 8               \
    || (!CAP_B8_FRAME_1460_1460_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B8_FRAME_1460_1460_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B8_FRAME_1460_1460_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B8_FRAME_1460_1460_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_08.dbc, frame frame_1460 (1460, 0x5b4): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1600 (1600, 0x640)
    on bus B8.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B8_FRAME_1600_1600_CHECKSUM_LENGTH != 8               \
    || (!CAP_B8_FRAME_1600_1600_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B8_FRAME_1600_1600_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B8_FRAME_1600_1600_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B8_FRAME_1600_1600_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_08.dbc, frame frame_1600 (1600, 0x640): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_653 (653, 0x28d)
    on bus B8.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B8_FRAME_653_653_CHECKSUM_LENGTH != 8               \
    || (!CAP_B8_FRAME_653_653_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B8_FRAME_653_653_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B8_FRAME_653_653_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B8_FRAME_653_653_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_08.dbc, frame frame_653 (653, 0x28d): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_699 (699, 0x2bb)
    on bus B8.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B8_FRAME_699_699_CHECKSUM_LENGTH != 8               \
    || (!CAP_B8_FRAME_699_699_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B8_FRAME_699_699_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B8_FRAME_699_699_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B8_FRAME_699_699_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_08.dbc, frame frame_699 (699, 0x2bb): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1307 (1307, 0x51b)
    on bus B8.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B8_FRAME_1307_1307_CHECKSUM_LENGTH != 8               \
    || (!CAP_B8_FRAME_1307_1307_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B8_FRAME_1307_1307_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B8_FRAME_1307_1307_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B8_FRAME_1307_1307_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_08.dbc, frame frame_1307 (1307, 0x51b): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1414 (1414, 0x586)
    on bus B8.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B8_FRAME_1414_1414_CHECKSUM_LENGTH != 8               \
    || (!CAP_B8_FRAME_1414_1414_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B8_FRAME_1414_1414_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B8_FRAME_1414_1414_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B8_FRAME_1414_1414_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_08.dbc, frame frame_1414 (1414, 0x586): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1085 (1085, 0x43d)
    on bus B8.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B8_FRAME_1085_1085_CHECKSUM_LENGTH != 8               \
    || (!CAP_B8_FRAME_1085_1085_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B8_FRAME_1085_1085_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B8_FRAME_1085_1085_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B8_FRAME_1085_1085_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_08.dbc, frame frame_1085 (1085, 0x43d): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_39 (39, 0x027)
    on bus B8.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B8_FRAME_39_39_CHECKSUM_LENGTH != 8               \
    || (!CAP_B8_FRAME_39_39_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B8_FRAME_39_39_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B8_FRAME_39_39_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B8_FRAME_39_39_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_08.dbc, frame frame_39 (39, 0x027): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1453 (1453, 0x5ad)
    on bus B8.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B8_FRAME_1453_1453_CHECKSUM_LENGTH != 8               \
    || (!CAP_B8_FRAME_1453_1453_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B8_FRAME_1453_1453_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B8_FRAME_1453_1453_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B8_FRAME_1453_1453_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_08.dbc, frame frame_1453 (1453, 0x5ad): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1039 (1039, 0x40f)
    on bus B8.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B8_FRAME_1039_1039_CHECKSUM_LENGTH != 8               \
    || (!CAP_B8_FRAME_1039_1039_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B8_FRAME_1039_1039_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B8_FRAME_1039_1039_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B8_FRAME_1039_1039_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_08.dbc, frame frame_1039 (1039, 0x40f): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_970 (970, 0x3ca)
    on bus B8.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B8_FRAME_970_970_CHECKSUM_LENGTH != 8               \
    || (!CAP_B8_FRAME_970_970_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B8_FRAME_970_970_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B8_FRAME_970_970_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B8_FRAME_970_970_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_08.dbc, frame frame_970 (970, 0x3ca): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1668 (1668, 0x684)
    on bus B8.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B8_FRAME_1668_1668_CHECKSUM_LENGTH != 8               \
    || (!CAP_B8_FRAME_1668_1668_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B8_FRAME_1668_1668_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B8_FRAME_1668_1668_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B8_FRAME_1668_1668_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_08.dbc, frame frame_1668 (1668, 0x684): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_305 (305, 0x131)
    on bus B8.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B8_FRAME_305_305_CHECKSUM_LENGTH != 8               \
    || (!CAP_B8_FRAME_305_305_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B8_FRAME_305_305_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B8_FRAME_305_305_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B8_FRAME_305_305_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_08.dbc, frame frame_305 (305, 0x131): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_309 (309, 0x135)
    on bus B8.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B8_FRAME_309_309_CHECKSUM_LENGTH != 8               \
    || (!CAP_B8_FRAME_309_309_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B8_FRAME_309_309_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B8_FRAME_309_309_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B8_FRAME_309_309_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_08.dbc, frame frame_309 (309, 0x135): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1724 (1724, 0x6bc)
    on bus B8.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B8_FRAME_1724_1724_CHECKSUM_LENGTH != 8               \
    || (!CAP_B8_FRAME_1724_1724_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B8_FRAME_1724_1724_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B8_FRAME_1724_1724_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B8_FRAME_1724_1724_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_08.dbc, frame frame_1724 (1724, 0x6bc): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1296 (1296, 0x510)
    on bus B8.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B8_FRAME_1296_1296_CHECKSUM_LENGTH != 8               \
    || (!CAP_B8_FRAME_1296_1296_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B8_FRAME_1296_1296_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B8_FRAME_1296_1296_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B8_FRAME_1296_1296_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_08.dbc, frame frame_1296 (1296, 0x510): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_461 (461, 0x1cd)
    on bus B8.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B8_FRAME_461_461_CHECKSUM_LENGTH != 8               \
    || (!CAP_B8_FRAME_461_461_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B8_FRAME_461_461_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B8_FRAME_461_461_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B8_FRAME_461_461_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_08.dbc, frame frame_461 (461, 0x1cd): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_231 (231, 0x0e7)
    on bus B8.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B8_FRAME_231_231_CHECKSUM_LENGTH != 8               \
    || (!CAP_B8_FRAME_231_231_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B8_FRAME_231_231_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B8_FRAME_231_231_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B8_FRAME_231_231_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_08.dbc, frame frame_231 (231, 0x0e7): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1804 (1804, 0x70c)
    on bus B8.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B8_FRAME_1804_1804_CHECKSUM_LENGTH != 8               \
    || (!CAP_B8_FRAME_1804_1804_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B8_FRAME_1804_1804_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B8_FRAME_1804_1804_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B8_FRAME_1804_1804_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_08.dbc, frame frame_1804 (1804, 0x70c): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1530 (1530, 0x5fa)
    on bus B8.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B8_FRAME_1530_1530_CHECKSUM_LENGTH != 8               \
    || (!CAP_B8_FRAME_1530_1530_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B8_FRAME_1530_1530_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B8_FRAME_1530_1530_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B8_FRAME_1530_1530_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_08.dbc, frame frame_1530 (1530, 0x5fa): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_496 (496, 0x1f0)
    on bus B8.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B8_FRAME_496_496_CHECKSUM_LENGTH != 8               \
    || (!CAP_B8_FRAME_496_496_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B8_FRAME_496_496_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B8_FRAME_496_496_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B8_FRAME_496_496_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_08.dbc, frame frame_496 (496, 0x1f0): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_777 (777, 0x309)
    on bus B8.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B8_FRAME_777_777_CHECKSUM_LENGTH != 8               \
    || (!CAP_B8_FRAME_777_777_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B8_FRAME_777_777_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B8_FRAME_777_777_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B8_FRAME_777_777_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_08.dbc, frame frame_777 (777, 0x309): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1844 (1844, 0x734)
    on bus B8.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B8_FRAME_1844_1844_CHECKSUM_LENGTH != 8               \
    || (!CAP_B8_FRAME_1844_1844_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B8_FRAME_1844_1844_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B8_FRAME_1844_1844_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B8_FRAME_1844_1844_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_08.dbc, frame frame_1844 (1844, 0x734): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_511 (511, 0x1ff)
    on bus B8.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B8_FRAME_511_511_CHECKSUM_LENGTH != 8               \
    || (!CAP_B8_FRAME_511_511_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B8_FRAME_511_511_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B8_FRAME_511_511_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B8_FRAME_511_511_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_08.dbc, frame frame_511 (511, 0x1ff): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_616 (616, 0x268)
    on bus B8.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B8_FRAME_616_616_CHECKSUM_LENGTH != 8               \
    || (!CAP_B8_FRAME_616_616_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B8_FRAME_616_616_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B8_FRAME_616_616_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B8_FRAME_616_616_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_08.dbc, frame frame_616 (616, 0x268): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_934 (934, 0x3a6)
    on bus B8.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B8_FRAME_934_934_CHECKSUM_LENGTH != 8               \
    || (!CAP_B8_FRAME_934_934_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B8_FRAME_934_934_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B8_FRAME_934_934_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B8_FRAME_934_934_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_08.dbc, frame frame_934 (934, 0x3a6): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1676 (1676, 0x68c)
    on bus B9.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B9_FRAME_1676_1676_CHECKSUM_LENGTH != 8               \
    || (!CAP_B9_FRAME_1676_1676_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B9_FRAME_1676_1676_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B9_FRAME_1676_1676_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B9_FRAME_1676_1676_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_09.dbc, frame frame_1676 (1676, 0x68c): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1012 (1012, 0x3f4)
    on bus B9.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B9_FRAME_1012_1012_CHECKSUM_LENGTH != 8               \
    || (!CAP_B9_FRAME_1012_1012_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B9_FRAME_1012_1012_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B9_FRAME_1012_1012_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B9_FRAME_1012_1012_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_09.dbc, frame frame_1012 (1012, 0x3f4): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1491 (1491, 0x5d3)
    on bus B9.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B9_FRAME_1491_1491_CHECKSUM_LENGTH != 8               \
    || (!CAP_B9_FRAME_1491_1491_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B9_FRAME_1491_1491_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B9_FRAME_1491_1491_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B9_FRAME_1491_1491_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_09.dbc, frame frame_1491 (1491, 0x5d3): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1536 (1536, 0x600)
    on bus B9.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B9_FRAME_1536_1536_CHECKSUM_LENGTH != 8               \
    || (!CAP_B9_FRAME_1536_1536_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B9_FRAME_1536_1536_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B9_FRAME_1536_1536_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B9_FRAME_1536_1536_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_09.dbc, frame frame_1536 (1536, 0x600): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_499 (499, 0x1f3)
    on bus B9.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B9_FRAME_499_499_CHECKSUM_LENGTH != 8               \
    || (!CAP_B9_FRAME_499_499_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B9_FRAME_499_499_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B9_FRAME_499_499_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B9_FRAME_499_499_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_09.dbc, frame frame_499 (499, 0x1f3): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_621 (621, 0x26d)
    on bus B9.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B9_FRAME_621_621_CHECKSUM_LENGTH != 8               \
    || (!CAP_B9_FRAME_621_621_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B9_FRAME_621_621_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B9_FRAME_621_621_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B9_FRAME_621_621_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_09.dbc, frame frame_621 (621, 0x26d): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_538 (538, 0x21a)
    on bus B9.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B9_FRAME_538_538_CHECKSUM_LENGTH != 8               \
    || (!CAP_B9_FRAME_538_538_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B9_FRAME_538_538_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B9_FRAME_538_538_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B9_FRAME_538_538_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_09.dbc, frame frame_538 (538, 0x21a): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1384 (1384, 0x568)
    on bus B9.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B9_FRAME_1384_1384_CHECKSUM_LENGTH != 8               \
    || (!CAP_B9_FRAME_1384_1384_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B9_FRAME_1384_1384_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B9_FRAME_1384_1384_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B9_FRAME_1384_1384_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_09.dbc, frame frame_1384 (1384, 0x568): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_993 (993, 0x3e1)
    on bus B9.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B9_FRAME_993_993_CHECKSUM_LENGTH != 8               \
    || (!CAP_B9_FRAME_993_993_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B9_FRAME_993_993_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B9_FRAME_993_993_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B9_FRAME_993_993_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_09.dbc, frame frame_993 (993, 0x3e1): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_21 (21, 0x015)
    on bus B9.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B9_FRAME_21_21_CHECKSUM_LENGTH != 8               \
    || (!CAP_B9_FRAME_21_21_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B9_FRAME_21_21_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B9_FRAME_21_21_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B9_FRAME_21_21_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_09.dbc, frame frame_21 (21, 0x015): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1210 (1210, 0x4ba)
    on bus B9.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B9_FRAME_1210_1210_CHECKSUM_LENGTH != 8               \
    || (!CAP_B9_FRAME_1210_1210_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B9_FRAME_1210_1210_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B9_FRAME_1210_1210_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B9_FRAME_1210_1210_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_09.dbc, frame frame_1210 (1210, 0x4ba): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_566 (566, 0x236)
    on bus B9.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B9_FRAME_566_566_CHECKSUM_LENGTH != 8               \
    || (!CAP_B9_FRAME_566_566_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B9_FRAME_566_566_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B9_FRAME_566_566_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B9_FRAME_566_566_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_09.dbc, frame frame_566 (566, 0x236): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_409 (409, 0x199)
    on bus B9.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B9_FRAME_409_409_CHECKSUM_LENGTH != 8               \
    || (!CAP_B9_FRAME_409_409_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B9_FRAME_409_409_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B9_FRAME_409_409_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B9_FRAME_409_409_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_09.dbc, frame frame_409 (409, 0x199): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_810 (810, 0x32a)
    on bus B9.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B9_FRAME_810_810_CHECKSUM_LENGTH != 8               \
    || (!CAP_B9_FRAME_810_810_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B9_FRAME_810_810_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B9_FRAME_810_810_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B9_FRAME_810_810_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_09.dbc, frame frame_810 (810, 0x32a): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1001 (1001, 0x3e9)
    on bus B9.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B9_FRAME_1001_1001_CHECKSUM_LENGTH != 8               \
    || (!CAP_B9_FRAME_1001_1001_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B9_FRAME_1001_1001_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B9_FRAME_1001_1001_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B9_FRAME_1001_1001_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_09.dbc, frame frame_1001 (1001, 0x3e9): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1148 (1148, 0x47c)
    on bus B9.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B9_FRAME_1148_1148_CHECKSUM_LENGTH != 8               \
    || (!CAP_B9_FRAME_1148_1148_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B9_FRAME_1148_1148_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B9_FRAME_1148_1148_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B9_FRAME_1148_1148_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_09.dbc, frame frame_1148 (1148, 0x47c): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1934 (1934, 0x78e)
    on bus B9.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B9_FRAME_1934_1934_CHECKSUM_LENGTH != 8               \
    || (!CAP_B9_FRAME_1934_1934_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B9_FRAME_1934_1934_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B9_FRAME_1934_1934_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B9_FRAME_1934_1934_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_09.dbc, frame frame_1934 (1934, 0x78e): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1238 (1238, 0x4d6)
    on bus B9.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B9_FRAME_1238_1238_CHECKSUM_LENGTH != 8               \
    || (!CAP_B9_FRAME_1238_1238_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B9_FRAME_1238_1238_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B9_FRAME_1238_1238_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B9_FRAME_1238_1238_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_09.dbc, frame frame_1238 (1238, 0x4d6): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1602 (1602, 0x642)
    on bus B9.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B9_FRAME_1602_1602_CHECKSUM_LENGTH != 8               \
    || (!CAP_B9_FRAME_1602_1602_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B9_FRAME_1602_1602_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B9_FRAME_1602_1602_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B9_FRAME_1602_1602_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_09.dbc, frame frame_1602 (1602, 0x642): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_113 (113, 0x071)
    on bus B9.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B9_FRAME_113_113_CHECKSUM_LENGTH != 8               \
    || (!CAP_B9_FRAME_113_113_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B9_FRAME_113_113_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B9_FRAME_113_113_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B9_FRAME_113_113_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_09.dbc, frame frame_113 (113, 0x071): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1629 (1629, 0x65d)
    on bus B9.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B9_FRAME_1629_1629_CHECKSUM_LENGTH != 8               \
    || (!CAP_B9_FRAME_1629_1629_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B9_FRAME_1629_1629_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B9_FRAME_1629_1629_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B9_FRAME_1629_1629_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_09.dbc, frame frame_1629 (1629, 0x65d): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1928 (1928, 0x788)
    on bus B9.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B9_FRAME_1928_1928_CHECKSUM_LENGTH != 8               \
    || (!CAP_B9_FRAME_1928_1928_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B9_FRAME_1928_1928_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B9_FRAME_1928_1928_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B9_FRAME_1928_1928_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_09.dbc, frame frame_1928 (1928, 0x788): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1256 (1256, 0x4e8)
    on bus B9.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B9_FRAME_1256_1256_CHECKSUM_LENGTH != 8               \
    || (!CAP_B9_FRAME_1256_1256_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B9_FRAME_1256_1256_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B9_FRAME_1256_1256_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B9_FRAME_1256_1256_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_09.dbc, frame frame_1256 (1256, 0x4e8): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1538 (1538, 0x602)
    on bus B9.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B9_FRAME_1538_1538_CHECKSUM_LENGTH != 8               \
    || (!CAP_B9_FRAME_1538_1538_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B9_FRAME_1538_1538_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B9_FRAME_1538_1538_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B9_FRAME_1538_1538_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_09.dbc, frame frame_1538 (1538, 0x602): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1852 (1852, 0x73c)
    on bus B9.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B9_FRAME_1852_1852_CHECKSUM_LENGTH != 8               \
    || (!CAP_B9_FRAME_1852_1852_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B9_FRAME_1852_1852_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B9_FRAME_1852_1852_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B9_FRAME_1852_1852_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_09.dbc, frame frame_1852 (1852, 0x73c): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1146 (1146, 0x47a)
    on bus B9.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B9_FRAME_1146_1146_CHECKSUM_LENGTH != 8               \
    || (!CAP_B9_FRAME_1146_1146_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B9_FRAME_1146_1146_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B9_FRAME_1146_1146_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B9_FRAME_1146_1146_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_09.dbc, frame frame_1146 (1146, 0x47a): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1025 (1025, 0x401)
    on bus B9.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B9_FRAME_1025_1025_CHECKSUM_LENGTH != 8               \
    || (!CAP_B9_FRAME_1025_1025_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B9_FRAME_1025_1025_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B9_FRAME_1025_1025_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B9_FRAME_1025_1025_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_09.dbc, frame frame_1025 (1025, 0x401): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1610 (1610, 0x64a)
    on bus B9.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B9_FRAME_1610_1610_CHECKSUM_LENGTH != 8               \
    || (!CAP_B9_FRAME_1610_1610_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B9_FRAME_1610_1610_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B9_FRAME_1610_1610_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B9_FRAME_1610_1610_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_09.dbc, frame frame_1610 (1610, 0x64a): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1315 (1315, 0x523)
    on bus B9.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B9_FRAME_1315_1315_CHECKSUM_LENGTH != 8               \
    || (!CAP_B9_FRAME_1315_1315_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B9_FRAME_1315_1315_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B9_FRAME_1315_1315_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B9_FRAME_1315_1315_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_09.dbc, frame frame_1315 (1315, 0x523): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_900 (900, 0x384)
    on bus B9.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B9_FRAME_900_900_CHECKSUM_LENGTH != 8               \
    || (!CAP_B9_FRAME_900_900_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B9_FRAME_900_900_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B9_FRAME_900_900_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B9_FRAME_900_900_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_09.dbc, frame frame_900 (900, 0x384): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_29 (29, 0x01d)
    on bus B9.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B9_FRAME_29_29_CHECKSUM_LENGTH != 8               \
    || (!CAP_B9_FRAME_29_29_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B9_FRAME_29_29_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B9_FRAME_29_29_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B9_FRAME_29_29_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_09.dbc, frame frame_29 (29, 0x01d): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_171 (171, 0x0ab)
    on bus B9.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B9_FRAME_171_171_CHECKSUM_LENGTH != 8               \
    || (!CAP_B9_FRAME_171_171_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B9_FRAME_171_171_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B9_FRAME_171_171_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B9_FRAME_171_171_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_09.dbc, frame frame_171 (171, 0x0ab): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_240 (240, 0x0f0)
    on bus B9.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B9_FRAME_240_240_CHECKSUM_LENGTH != 8               \
    || (!CAP_B9_FRAME_240_240_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B9_FRAME_240_240_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B9_FRAME_240_240_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B9_FRAME_240_240_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_09.dbc, frame frame_240 (240, 0x0f0): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_726 (726, 0x2d6)
    on bus B9.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B9_FRAME_726_726_CHECKSUM_LENGTH != 8               \
    || (!CAP_B9_FRAME_726_726_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B9_FRAME_726_726_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B9_FRAME_726_726_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B9_FRAME_726_726_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_09.dbc, frame frame_726 (726, 0x2d6): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_245 (245, 0x0f5)
    on bus B9.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B9_FRAME_245_245_CHECKSUM_LENGTH != 8               \
    || (!CAP_B9_FRAME_245_245_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B9_FRAME_245_245_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B9_FRAME_245_245_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B9_FRAME_245_245_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_09.dbc, frame frame_245 (245, 0x0f5): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1965 (1965, 0x7ad)
    on bus B9.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B9_FRAME_1965_1965_CHECKSUM_LENGTH != 8               \
    || (!CAP_B9_FRAME_1965_1965_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B9_FRAME_1965_1965_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B9_FRAME_1965_1965_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B9_FRAME_1965_1965_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_09.dbc, frame frame_1965 (1965, 0x7ad): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_178 (178, 0x0b2)
    on bus B9.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B9_FRAME_178_178_CHECKSUM_LENGTH != 8               \
    || (!CAP_B9_FRAME_178_178_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B9_FRAME_178_178_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B9_FRAME_178_178_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B9_FRAME_178_178_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_09.dbc, frame frame_178 (178, 0x0b2): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_2031 (2031, 0x7ef)
    on bus B9.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B9_FRAME_2031_2031_CHECKSUM_LENGTH != 8               \
    || (!CAP_B9_FRAME_2031_2031_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B9_FRAME_2031_2031_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B9_FRAME_2031_2031_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B9_FRAME_2031_2031_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_09.dbc, frame frame_2031 (2031, 0x7ef): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1393 (1393, 0x571)
    on bus B9.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B9_FRAME_1393_1393_CHECKSUM_LENGTH != 8               \
    || (!CAP_B9_FRAME_1393_1393_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B9_FRAME_1393_1393_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B9_FRAME_1393_1393_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B9_FRAME_1393_1393_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_09.dbc, frame frame_1393 (1393, 0x571): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1338 (1338, 0x53a)
    on bus B9.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B9_FRAME_1338_1338_CHECKSUM_LENGTH != 8               \
    || (!CAP_B9_FRAME_1338_1338_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B9_FRAME_1338_1338_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B9_FRAME_1338_1338_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B9_FRAME_1338_1338_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_09.dbc, frame frame_1338 (1338, 0x53a): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1935 (1935, 0x78f)
    on bus B9.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B9_FRAME_1935_1935_CHECKSUM_LENGTH != 8               \
    || (!CAP_B9_FRAME_1935_1935_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B9_FRAME_1935_1935_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B9_FRAME_1935_1935_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B9_FRAME_1935_1935_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_09.dbc, frame frame_1935 (1935, 0x78f): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1478 (1478, 0x5c6)
    on bus B9.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B9_FRAME_1478_1478_CHECKSUM_LENGTH != 8               \
    || (!CAP_B9_FRAME_1478_1478_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B9_FRAME_1478_1478_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B9_FRAME_1478_1478_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B9_FRAME_1478_1478_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_09.dbc, frame frame_1478 (1478, 0x5c6): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1500 (1500, 0x5dc)
    on bus B9.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B9_FRAME_1500_1500_CHECKSUM_LENGTH != 8               \
    || (!CAP_B9_FRAME_1500_1500_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B9_FRAME_1500_1500_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B9_FRAME_1500_1500_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B9_FRAME_1500_1500_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_09.dbc, frame frame_1500 (1500, 0x5dc): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1416 (1416, 0x588)
    on bus B9.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B9_FRAME_1416_1416_CHECKSUM_LENGTH != 8               \
    || (!CAP_B9_FRAME_1416_1416_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B9_FRAME_1416_1416_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B9_FRAME_1416_1416_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B9_FRAME_1416_1416_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_09.dbc, frame frame_1416 (1416, 0x588): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_2033 (2033, 0x7f1)
    on bus B9.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B9_FRAME_2033_2033_CHECKSUM_LENGTH != 8               \
    || (!CAP_B9_FRAME_2033_2033_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B9_FRAME_2033_2033_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B9_FRAME_2033_2033_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B9_FRAME_2033_2033_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_09.dbc, frame frame_2033 (2033, 0x7f1): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1058 (1058, 0x422)
    on bus B9.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B9_FRAME_1058_1058_CHECKSUM_LENGTH != 8               \
    || (!CAP_B9_FRAME_1058_1058_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B9_FRAME_1058_1058_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B9_FRAME_1058_1058_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B9_FRAME_1058_1058_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_09.dbc, frame frame_1058 (1058, 0x422): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_223 (223, 0x0df)
    on bus B9.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B9_FRAME_223_223_CHECKSUM_LENGTH != 8               \
    || (!CAP_B9_FRAME_223_223_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B9_FRAME_223_223_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B9_FRAME_223_223_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B9_FRAME_223_223_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_09.dbc, frame frame_223 (223, 0x0df): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_950 (950, 0x3b6)
    on bus B9.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B9_FRAME_950_950_CHECKSUM_LENGTH != 8               \
    || (!CAP_B9_FRAME_950_950_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B9_FRAME_950_950_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B9_FRAME_950_950_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B9_FRAME_950_950_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_09.dbc, frame frame_950 (950, 0x3b6): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_734 (734, 0x2de)
    on bus B9.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B9_FRAME_734_734_CHECKSUM_LENGTH != 8               \
    || (!CAP_B9_FRAME_734_734_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B9_FRAME_734_734_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B9_FRAME_734_734_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B9_FRAME_734_734_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_09.dbc, frame frame_734 (734, 0x2de): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_971 (971, 0x3cb)
    on bus B9.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B9_FRAME_971_971_CHECKSUM_LENGTH != 8               \
    || (!CAP_B9_FRAME_971_971_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B9_FRAME_971_971_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B9_FRAME_971_971_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B9_FRAME_971_971_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_09.dbc, frame frame_971 (971, 0x3cb): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1565 (1565, 0x61d)
    on bus B9.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B9_FRAME_1565_1565_CHECKSUM_LENGTH != 8               \
    || (!CAP_B9_FRAME_1565_1565_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B9_FRAME_1565_1565_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B9_FRAME_1565_1565_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B9_FRAME_1565_1565_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_09.dbc, frame frame_1565 (1565, 0x61d): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1815 (1815, 0x717)
    on bus B9.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B9_FRAME_1815_1815_CHECKSUM_LENGTH != 8               \
    || (!CAP_B9_FRAME_1815_1815_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B9_FRAME_1815_1815_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B9_FRAME_1815_1815_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B9_FRAME_1815_1815_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_09.dbc, frame frame_1815 (1815, 0x717): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_824 (824, 0x338)
    on bus B9.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B9_FRAME_824_824_CHECKSUM_LENGTH != 8               \
    || (!CAP_B9_FRAME_824_824_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B9_FRAME_824_824_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B9_FRAME_824_824_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B9_FRAME_824_824_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_09.dbc, frame frame_824 (824, 0x338): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_445 (445, 0x1bd)
    on bus B9.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B9_FRAME_445_445_CHECKSUM_LENGTH != 8               \
    || (!CAP_B9_FRAME_445_445_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B9_FRAME_445_445_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B9_FRAME_445_445_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B9_FRAME_445_445_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_09.dbc, frame frame_445 (445, 0x1bd): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_583 (583, 0x247)
    on bus B9.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B9_FRAME_583_583_CHECKSUM_LENGTH != 8               \
    || (!CAP_B9_FRAME_583_583_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B9_FRAME_583_583_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B9_FRAME_583_583_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B9_FRAME_583_583_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_09.dbc, frame frame_583 (583, 0x247): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1699 (1699, 0x6a3)
    on bus B9.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B9_FRAME_1699_1699_CHECKSUM_LENGTH != 8               \
    || (!CAP_B9_FRAME_1699_1699_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B9_FRAME_1699_1699_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B9_FRAME_1699_1699_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B9_FRAME_1699_1699_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_09.dbc, frame frame_1699 (1699, 0x6a3): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_551 (551, 0x227)
    on bus B9.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B9_FRAME_551_551_CHECKSUM_LENGTH != 8               \
    || (!CAP_B9_FRAME_551_551_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B9_FRAME_551_551_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B9_FRAME_551_551_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B9_FRAME_551_551_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_09.dbc, frame frame_551 (551, 0x227): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_8 (8, 0x008)
    on bus B9.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B9_FRAME_8_8_CHECKSUM_LENGTH != 8               \
    || (!CAP_B9_FRAME_8_8_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B9_FRAME_8_8_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B9_FRAME_8_8_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B9_FRAME_8_8_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_09.dbc, frame frame_8 (8, 0x008): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1698 (1698, 0x6a2)
    on bus B9.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B9_FRAME_1698_1698_CHECKSUM_LENGTH != 8               \
    || (!CAP_B9_FRAME_1698_1698_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B9_FRAME_1698_1698_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B9_FRAME_1698_1698_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B9_FRAME_1698_1698_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_09.dbc, frame frame_1698 (1698, 0x6a2): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_840 (840, 0x348)
    on bus B9.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B9_FRAME_840_840_CHECKSUM_LENGTH != 8               \
    || (!CAP_B9_FRAME_840_840_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B9_FRAME_840_840_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B9_FRAME_840_840_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B9_FRAME_840_840_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_09.dbc, frame frame_840 (840, 0x348): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_899 (899, 0x383)
    on bus B9.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B9_FRAME_899_899_CHECKSUM_LENGTH != 8               \
    || (!CAP_B9_FRAME_899_899_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B9_FRAME_899_899_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B9_FRAME_899_899_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B9_FRAME_899_899_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_09.dbc, frame frame_899 (899, 0x383): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_148 (148, 0x094)
    on bus B9.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B9_FRAME_148_148_CHECKSUM_LENGTH != 8               \
    || (!CAP_B9_FRAME_148_148_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B9_FRAME_148_148_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B9_FRAME_148_148_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B9_FRAME_148_148_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_09.dbc, frame frame_148 (148, 0x094): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1854 (1854, 0x73e)
    on bus B9.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B9_FRAME_1854_1854_CHECKSUM_LENGTH != 8               \
    || (!CAP_B9_FRAME_1854_1854_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B9_FRAME_1854_1854_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B9_FRAME_1854_1854_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B9_FRAME_1854_1854_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_09.dbc, frame frame_1854 (1854, 0x73e): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1142 (1142, 0x476)
    on bus B9.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B9_FRAME_1142_1142_CHECKSUM_LENGTH != 8               \
    || (!CAP_B9_FRAME_1142_1142_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B9_FRAME_1142_1142_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B9_FRAME_1142_1142_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B9_FRAME_1142_1142_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_09.dbc, frame frame_1142 (1142, 0x476): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1007 (1007, 0x3ef)
    on bus B9.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B9_FRAME_1007_1007_CHECKSUM_LENGTH != 8               \
    || (!CAP_B9_FRAME_1007_1007_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B9_FRAME_1007_1007_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B9_FRAME_1007_1007_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B9_FRAME_1007_1007_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_09.dbc, frame frame_1007 (1007, 0x3ef): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1613 (1613, 0x64d)
    on bus B9.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B9_FRAME_1613_1613_CHECKSUM_LENGTH != 8               \
    || (!CAP_B9_FRAME_1613_1613_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B9_FRAME_1613_1613_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B9_FRAME_1613_1613_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B9_FRAME_1613_1613_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_09.dbc, frame frame_1613 (1613, 0x64d): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1474 (1474, 0x5c2)
    on bus B9.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B9_FRAME_1474_1474_CHECKSUM_LENGTH != 8               \
    || (!CAP_B9_FRAME_1474_1474_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B9_FRAME_1474_1474_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B9_FRAME_1474_1474_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B9_FRAME_1474_1474_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_09.dbc, frame frame_1474 (1474, 0x5c2): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1762 (1762, 0x6e2)
    on bus B9.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B9_FRAME_1762_1762_CHECKSUM_LENGTH != 8               \
    || (!CAP_B9_FRAME_1762_1762_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B9_FRAME_1762_1762_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B9_FRAME_1762_1762_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B9_FRAME_1762_1762_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_09.dbc, frame frame_1762 (1762, 0x6e2): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1121 (1121, 0x461)
    on bus B9.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B9_FRAME_1121_1121_CHECKSUM_LENGTH != 8               \
    || (!CAP_B9_FRAME_1121_1121_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B9_FRAME_1121_1121_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B9_FRAME_1121_1121_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B9_FRAME_1121_1121_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_09.dbc, frame frame_1121 (1121, 0x461): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1648 (1648, 0x670)
    on bus B9.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B9_FRAME_1648_1648_CHECKSUM_LENGTH != 8               \
    || (!CAP_B9_FRAME_1648_1648_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B9_FRAME_1648_1648_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B9_FRAME_1648_1648_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B9_FRAME_1648_1648_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_09.dbc, frame frame_1648 (1648, 0x670): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_627 (627, 0x273)
    on bus B9.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B9_FRAME_627_627_CHECKSUM_LENGTH != 8               \
    || (!CAP_B9_FRAME_627_627_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B9_FRAME_627_627_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B9_FRAME_627_627_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B9_FRAME_627_627_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_09.dbc, frame frame_627 (627, 0x273): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1120 (1120, 0x460)
    on bus B9.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B9_FRAME_1120_1120_CHECKSUM_LENGTH != 8               \
    || (!CAP_B9_FRAME_1120_1120_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B9_FRAME_1120_1120_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B9_FRAME_1120_1120_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B9_FRAME_1120_1120_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_09.dbc, frame frame_1120 (1120, 0x460): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_973 (973, 0x3cd)
    on bus B9.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B9_FRAME_973_973_CHECKSUM_LENGTH != 8               \
    || (!CAP_B9_FRAME_973_973_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B9_FRAME_973_973_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B9_FRAME_973_973_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B9_FRAME_973_973_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_09.dbc, frame frame_973 (973, 0x3cd): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1362 (1362, 0x552)
    on bus B9.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B9_FRAME_1362_1362_CHECKSUM_LENGTH != 8               \
    || (!CAP_B9_FRAME_1362_1362_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B9_FRAME_1362_1362_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B9_FRAME_1362_1362_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B9_FRAME_1362_1362_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_09.dbc, frame frame_1362 (1362, 0x552): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_897 (897, 0x381)
    on bus B9.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B9_FRAME_897_897_CHECKSUM_LENGTH != 8               \
    || (!CAP_B9_FRAME_897_897_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B9_FRAME_897_897_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B9_FRAME_897_897_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B9_FRAME_897_897_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_09.dbc, frame frame_897 (897, 0x381): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_324 (324, 0x144)
    on bus B10.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B10_FRAME_324_324_CHECKSUM_LENGTH != 8               \
    || (!CAP_B10_FRAME_324_324_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B10_FRAME_324_324_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B10_FRAME_324_324_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B10_FRAME_324_324_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_10.dbc, frame frame_324 (324, 0x144): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1232 (1232, 0x4d0)
    on bus B10.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B10_FRAME_1232_1232_CHECKSUM_LENGTH != 8               \
    || (!CAP_B10_FRAME_1232_1232_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B10_FRAME_1232_1232_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B10_FRAME_1232_1232_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B10_FRAME_1232_1232_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_10.dbc, frame frame_1232 (1232, 0x4d0): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_161 (161, 0x0a1)
    on bus B10.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B10_FRAME_161_161_CHECKSUM_LENGTH != 8               \
    || (!CAP_B10_FRAME_161_161_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B10_FRAME_161_161_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B10_FRAME_161_161_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B10_FRAME_161_161_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_10.dbc, frame frame_161 (161, 0x0a1): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1037 (1037, 0x40d)
    on bus B10.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B10_FRAME_1037_1037_CHECKSUM_LENGTH != 8               \
    || (!CAP_B10_FRAME_1037_1037_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B10_FRAME_1037_1037_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B10_FRAME_1037_1037_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B10_FRAME_1037_1037_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_10.dbc, frame frame_1037 (1037, 0x40d): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1129 (1129, 0x469)
    on bus B10.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B10_FRAME_1129_1129_CHECKSUM_LENGTH != 8               \
    || (!CAP_B10_FRAME_1129_1129_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B10_FRAME_1129_1129_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B10_FRAME_1129_1129_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B10_FRAME_1129_1129_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_10.dbc, frame frame_1129 (1129, 0x469): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1231 (1231, 0x4cf)
    on bus B10.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B10_FRAME_1231_1231_CHECKSUM_LENGTH != 8               \
    || (!CAP_B10_FRAME_1231_1231_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B10_FRAME_1231_1231_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B10_FRAME_1231_1231_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B10_FRAME_1231_1231_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_10.dbc, frame frame_1231 (1231, 0x4cf): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_892 (892, 0x37c)
    on bus B10.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B10_FRAME_892_892_CHECKSUM_LENGTH != 8               \
    || (!CAP_B10_FRAME_892_892_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B10_FRAME_892_892_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B10_FRAME_892_892_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B10_FRAME_892_892_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_10.dbc, frame frame_892 (892, 0x37c): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_612 (612, 0x264)
    on bus B10.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B10_FRAME_612_612_CHECKSUM_LENGTH != 8               \
    || (!CAP_B10_FRAME_612_612_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B10_FRAME_612_612_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B10_FRAME_612_612_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B10_FRAME_612_612_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_10.dbc, frame frame_612 (612, 0x264): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1982 (1982, 0x7be)
    on bus B10.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B10_FRAME_1982_1982_CHECKSUM_LENGTH != 8               \
    || (!CAP_B10_FRAME_1982_1982_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B10_FRAME_1982_1982_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B10_FRAME_1982_1982_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B10_FRAME_1982_1982_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_10.dbc, frame frame_1982 (1982, 0x7be): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_225 (225, 0x0e1)
    on bus B10.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B10_FRAME_225_225_CHECKSUM_LENGTH != 8               \
    || (!CAP_B10_FRAME_225_225_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B10_FRAME_225_225_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B10_FRAME_225_225_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B10_FRAME_225_225_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_10.dbc, frame frame_225 (225, 0x0e1): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_5 (5, 0x005)
    on bus B10.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B10_FRAME_5_5_CHECKSUM_LENGTH != 8               \
    || (!CAP_B10_FRAME_5_5_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B10_FRAME_5_5_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B10_FRAME_5_5_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B10_FRAME_5_5_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_10.dbc, frame frame_5 (5, 0x005): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_232 (232, 0x0e8)
    on bus B10.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B10_FRAME_232_232_CHECKSUM_LENGTH != 8               \
    || (!CAP_B10_FRAME_232_232_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B10_FRAME_232_232_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B10_FRAME_232_232_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B10_FRAME_232_232_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_10.dbc, frame frame_232 (232, 0x0e8): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_591 (591, 0x24f)
    on bus B10.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B10_FRAME_591_591_CHECKSUM_LENGTH != 8               \
    || (!CAP_B10_FRAME_591_591_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B10_FRAME_591_591_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B10_FRAME_591_591_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B10_FRAME_591_591_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_10.dbc, frame frame_591 (591, 0x24f): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_91 (91, 0x05b)
    on bus B10.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B10_FRAME_91_91_CHECKSUM_LENGTH != 8               \
    || (!CAP_B10_FRAME_91_91_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B10_FRAME_91_91_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B10_FRAME_91_91_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B10_FRAME_91_91_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_10.dbc, frame frame_91 (91, 0x05b): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_316 (316, 0x13c)
    on bus B10.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B10_FRAME_316_316_CHECKSUM_LENGTH != 8               \
    || (!CAP_B10_FRAME_316_316_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B10_FRAME_316_316_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B10_FRAME_316_316_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B10_FRAME_316_316_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_10.dbc, frame frame_316 (316, 0x13c): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1841 (1841, 0x731)
    on bus B10.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B10_FRAME_1841_1841_CHECKSUM_LENGTH != 8               \
    || (!CAP_B10_FRAME_1841_1841_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B10_FRAME_1841_1841_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B10_FRAME_1841_1841_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B10_FRAME_1841_1841_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_10.dbc, frame frame_1841 (1841, 0x731): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1103 (1103, 0x44f)
    on bus B10.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B10_FRAME_1103_1103_CHECKSUM_LENGTH != 8               \
    || (!CAP_B10_FRAME_1103_1103_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B10_FRAME_1103_1103_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B10_FRAME_1103_1103_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B10_FRAME_1103_1103_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_10.dbc, frame frame_1103 (1103, 0x44f): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_109 (109, 0x06d)
    on bus B10.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B10_FRAME_109_109_CHECKSUM_LENGTH != 8               \
    || (!CAP_B10_FRAME_109_109_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B10_FRAME_109_109_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B10_FRAME_109_109_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B10_FRAME_109_109_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_10.dbc, frame frame_109 (109, 0x06d): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1999 (1999, 0x7cf)
    on bus B10.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B10_FRAME_1999_1999_CHECKSUM_LENGTH != 8               \
    || (!CAP_B10_FRAME_1999_1999_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B10_FRAME_1999_1999_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B10_FRAME_1999_1999_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B10_FRAME_1999_1999_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_10.dbc, frame frame_1999 (1999, 0x7cf): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1477 (1477, 0x5c5)
    on bus B10.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B10_FRAME_1477_1477_CHECKSUM_LENGTH != 8               \
    || (!CAP_B10_FRAME_1477_1477_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B10_FRAME_1477_1477_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B10_FRAME_1477_1477_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B10_FRAME_1477_1477_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_10.dbc, frame frame_1477 (1477, 0x5c5): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_956 (956, 0x3bc)
    on bus B10.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B10_FRAME_956_956_CHECKSUM_LENGTH != 8               \
    || (!CAP_B10_FRAME_956_956_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B10_FRAME_956_956_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B10_FRAME_956_956_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B10_FRAME_956_956_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_10.dbc, frame frame_956 (956, 0x3bc): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1604 (1604, 0x644)
    on bus B10.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B10_FRAME_1604_1604_CHECKSUM_LENGTH != 8               \
    || (!CAP_B10_FRAME_1604_1604_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B10_FRAME_1604_1604_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B10_FRAME_1604_1604_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B10_FRAME_1604_1604_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_10.dbc, frame frame_1604 (1604, 0x644): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_36 (36, 0x024)
    on bus B10.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B10_FRAME_36_36_CHECKSUM_LENGTH != 8               \
    || (!CAP_B10_FRAME_36_36_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B10_FRAME_36_36_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B10_FRAME_36_36_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B10_FRAME_36_36_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_10.dbc, frame frame_36 (36, 0x024): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1847 (1847, 0x737)
    on bus B10.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B10_FRAME_1847_1847_CHECKSUM_LENGTH != 8               \
    || (!CAP_B10_FRAME_1847_1847_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B10_FRAME_1847_1847_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B10_FRAME_1847_1847_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B10_FRAME_1847_1847_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_10.dbc, frame frame_1847 (1847, 0x737): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_267 (267, 0x10b)
    on bus B10.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B10_FRAME_267_267_CHECKSUM_LENGTH != 8               \
    || (!CAP_B10_FRAME_267_267_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B10_FRAME_267_267_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B10_FRAME_267_267_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B10_FRAME_267_267_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_10.dbc, frame frame_267 (267, 0x10b): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1407 (1407, 0x57f)
    on bus B10.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B10_FRAME_1407_1407_CHECKSUM_LENGTH != 8               \
    || (!CAP_B10_FRAME_1407_1407_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B10_FRAME_1407_1407_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B10_FRAME_1407_1407_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B10_FRAME_1407_1407_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_10.dbc, frame frame_1407 (1407, 0x57f): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1915 (1915, 0x77b)
    on bus B10.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B10_FRAME_1915_1915_CHECKSUM_LENGTH != 8               \
    || (!CAP_B10_FRAME_1915_1915_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B10_FRAME_1915_1915_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B10_FRAME_1915_1915_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B10_FRAME_1915_1915_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_10.dbc, frame frame_1915 (1915, 0x77b): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_2007 (2007, 0x7d7)
    on bus B10.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B10_FRAME_2007_2007_CHECKSUM_LENGTH != 8               \
    || (!CAP_B10_FRAME_2007_2007_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B10_FRAME_2007_2007_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B10_FRAME_2007_2007_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B10_FRAME_2007_2007_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_10.dbc, frame frame_2007 (2007, 0x7d7): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1194 (1194, 0x4aa)
    on bus B10.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B10_FRAME_1194_1194_CHECKSUM_LENGTH != 8               \
    || (!CAP_B10_FRAME_1194_1194_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B10_FRAME_1194_1194_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B10_FRAME_1194_1194_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B10_FRAME_1194_1194_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_10.dbc, frame frame_1194 (1194, 0x4aa): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_446 (446, 0x1be)
    on bus B10.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B10_FRAME_446_446_CHECKSUM_LENGTH != 8               \
    || (!CAP_B10_FRAME_446_446_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B10_FRAME_446_446_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B10_FRAME_446_446_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B10_FRAME_446_446_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_10.dbc, frame frame_446 (446, 0x1be): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1060 (1060, 0x424)
    on bus B10.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B10_FRAME_1060_1060_CHECKSUM_LENGTH != 8               \
    || (!CAP_B10_FRAME_1060_1060_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B10_FRAME_1060_1060_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B10_FRAME_1060_1060_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B10_FRAME_1060_1060_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_10.dbc, frame frame_1060 (1060, 0x424): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_2001 (2001, 0x7d1)
    on bus B10.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B10_FRAME_2001_2001_CHECKSUM_LENGTH != 8               \
    || (!CAP_B10_FRAME_2001_2001_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B10_FRAME_2001_2001_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B10_FRAME_2001_2001_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B10_FRAME_2001_2001_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_10.dbc, frame frame_2001 (2001, 0x7d1): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_80 (80, 0x050)
    on bus B10.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B10_FRAME_80_80_CHECKSUM_LENGTH != 8               \
    || (!CAP_B10_FRAME_80_80_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B10_FRAME_80_80_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B10_FRAME_80_80_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B10_FRAME_80_80_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_10.dbc, frame frame_80 (80, 0x050): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_0 (0, 0x000)
    on bus B10.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B10_FRAME_0_0_CHECKSUM_LENGTH != 8               \
    || (!CAP_B10_FRAME_0_0_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B10_FRAME_0_0_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B10_FRAME_0_0_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B10_FRAME_0_0_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_10.dbc, frame frame_0 (0, 0x000): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1702 (1702, 0x6a6)
    on bus B10.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B10_FRAME_1702_1702_CHECKSUM_LENGTH != 8               \
    || (!CAP_B10_FRAME_1702_1702_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B10_FRAME_1702_1702_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B10_FRAME_1702_1702_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B10_FRAME_1702_1702_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_10.dbc, frame frame_1702 (1702, 0x6a6): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1494 (1494, 0x5d6)
    on bus B10.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B10_FRAME_1494_1494_CHECKSUM_LENGTH != 8               \
    || (!CAP_B10_FRAME_1494_1494_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B10_FRAME_1494_1494_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B10_FRAME_1494_1494_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B10_FRAME_1494_1494_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_10.dbc, frame frame_1494 (1494, 0x5d6): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_964 (964, 0x3c4)
    on bus B10.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B10_FRAME_964_964_CHECKSUM_LENGTH != 8               \
    || (!CAP_B10_FRAME_964_964_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B10_FRAME_964_964_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B10_FRAME_964_964_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B10_FRAME_964_964_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_10.dbc, frame frame_964 (964, 0x3c4): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_400 (400, 0x190)
    on bus B10.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B10_FRAME_400_400_CHECKSUM_LENGTH != 8               \
    || (!CAP_B10_FRAME_400_400_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B10_FRAME_400_400_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B10_FRAME_400_400_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B10_FRAME_400_400_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_10.dbc, frame frame_400 (400, 0x190): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_264 (264, 0x108)
    on bus B10.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B10_FRAME_264_264_CHECKSUM_LENGTH != 8               \
    || (!CAP_B10_FRAME_264_264_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B10_FRAME_264_264_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B10_FRAME_264_264_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B10_FRAME_264_264_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_10.dbc, frame frame_264 (264, 0x108): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_479 (479, 0x1df)
    on bus B10.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B10_FRAME_479_479_CHECKSUM_LENGTH != 8               \
    || (!CAP_B10_FRAME_479_479_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B10_FRAME_479_479_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B10_FRAME_479_479_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B10_FRAME_479_479_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_10.dbc, frame frame_479 (479, 0x1df): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_502 (502, 0x1f6)
    on bus B10.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B10_FRAME_502_502_CHECKSUM_LENGTH != 8               \
    || (!CAP_B10_FRAME_502_502_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B10_FRAME_502_502_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B10_FRAME_502_502_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B10_FRAME_502_502_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_10.dbc, frame frame_502 (502, 0x1f6): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_537 (537, 0x219)
    on bus B10.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B10_FRAME_537_537_CHECKSUM_LENGTH != 8               \
    || (!CAP_B10_FRAME_537_537_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B10_FRAME_537_537_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B10_FRAME_537_537_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B10_FRAME_537_537_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_10.dbc, frame frame_537 (537, 0x219): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_741 (741, 0x2e5)
    on bus B10.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B10_FRAME_741_741_CHECKSUM_LENGTH != 8               \
    || (!CAP_B10_FRAME_741_741_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B10_FRAME_741_741_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B10_FRAME_741_741_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B10_FRAME_741_741_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_10.dbc, frame frame_741 (741, 0x2e5): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1396 (1396, 0x574)
    on bus B10.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B10_FRAME_1396_1396_CHECKSUM_LENGTH != 8               \
    || (!CAP_B10_FRAME_1396_1396_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B10_FRAME_1396_1396_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B10_FRAME_1396_1396_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B10_FRAME_1396_1396_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_10.dbc, frame frame_1396 (1396, 0x574): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_207 (207, 0x0cf)
    on bus B10.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B10_FRAME_207_207_CHECKSUM_LENGTH != 8               \
    || (!CAP_B10_FRAME_207_207_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B10_FRAME_207_207_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B10_FRAME_207_207_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B10_FRAME_207_207_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_10.dbc, frame frame_207 (207, 0x0cf): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_419 (419, 0x1a3)
    on bus B10.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B10_FRAME_419_419_CHECKSUM_LENGTH != 8               \
    || (!CAP_B10_FRAME_419_419_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B10_FRAME_419_419_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B10_FRAME_419_419_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B10_FRAME_419_419_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_10.dbc, frame frame_419 (419, 0x1a3): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1325 (1325, 0x52d)
    on bus B10.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B10_FRAME_1325_1325_CHECKSUM_LENGTH != 8               \
    || (!CAP_B10_FRAME_1325_1325_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B10_FRAME_1325_1325_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B10_FRAME_1325_1325_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B10_FRAME_1325_1325_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_10.dbc, frame frame_1325 (1325, 0x52d): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1996 (1996, 0x7cc)
    on bus B10.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B10_FRAME_1996_1996_CHECKSUM_LENGTH != 8               \
    || (!CAP_B10_FRAME_1996_1996_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B10_FRAME_1996_1996_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B10_FRAME_1996_1996_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B10_FRAME_1996_1996_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_10.dbc, frame frame_1996 (1996, 0x7cc): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1505 (1505, 0x5e1)
    on bus B10.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B10_FRAME_1505_1505_CHECKSUM_LENGTH != 8               \
    || (!CAP_B10_FRAME_1505_1505_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B10_FRAME_1505_1505_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B10_FRAME_1505_1505_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B10_FRAME_1505_1505_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_10.dbc, frame frame_1505 (1505, 0x5e1): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_393 (393, 0x189)
    on bus B10.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B10_FRAME_393_393_CHECKSUM_LENGTH != 8               \
    || (!CAP_B10_FRAME_393_393_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B10_FRAME_393_393_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B10_FRAME_393_393_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B10_FRAME_393_393_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_10.dbc, frame frame_393 (393, 0x189): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_703 (703, 0x2bf)
    on bus B10.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B10_FRAME_703_703_CHECKSUM_LENGTH != 8               \
    || (!CAP_B10_FRAME_703_703_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B10_FRAME_703_703_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B10_FRAME_703_703_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B10_FRAME_703_703_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_10.dbc, frame frame_703 (703, 0x2bf): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_48 (48, 0x030)
    on bus B10.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B10_FRAME_48_48_CHECKSUM_LENGTH != 8               \
    || (!CAP_B10_FRAME_48_48_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B10_FRAME_48_48_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B10_FRAME_48_48_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B10_FRAME_48_48_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_10.dbc, frame frame_48 (48, 0x030): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_26 (26, 0x01a)
    on bus B10.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B10_FRAME_26_26_CHECKSUM_LENGTH != 8               \
    || (!CAP_B10_FRAME_26_26_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B10_FRAME_26_26_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B10_FRAME_26_26_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B10_FRAME_26_26_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_10.dbc, frame frame_26 (26, 0x01a): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_515 (515, 0x203)
    on bus B10.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B10_FRAME_515_515_CHECKSUM_LENGTH != 8               \
    || (!CAP_B10_FRAME_515_515_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B10_FRAME_515_515_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B10_FRAME_515_515_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B10_FRAME_515_515_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_10.dbc, frame frame_515 (515, 0x203): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1570 (1570, 0x622)
    on bus B10.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B10_FRAME_1570_1570_CHECKSUM_LENGTH != 8               \
    || (!CAP_B10_FRAME_1570_1570_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B10_FRAME_1570_1570_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B10_FRAME_1570_1570_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B10_FRAME_1570_1570_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_10.dbc, frame frame_1570 (1570, 0x622): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1791 (1791, 0x6ff)
    on bus B10.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B10_FRAME_1791_1791_CHECKSUM_LENGTH != 8               \
    || (!CAP_B10_FRAME_1791_1791_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B10_FRAME_1791_1791_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B10_FRAME_1791_1791_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B10_FRAME_1791_1791_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_10.dbc, frame frame_1791 (1791, 0x6ff): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_1364 (1364, 0x554)
    on bus B10.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B10_FRAME_1364_1364_CHECKSUM_LENGTH != 8               \
    || (!CAP_B10_FRAME_1364_1364_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B10_FRAME_1364_1364_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B10_FRAME_1364_1364_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B10_FRAME_1364_1364_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_10.dbc, frame frame_1364 (1364, 0x554): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame frame_677 (677, 0x2a5)
    on bus B10.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_B10_FRAME_677_677_CHECKSUM_LENGTH != 8               \
    || (!CAP_B10_FRAME_677_677_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_B10_FRAME_677_677_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_B10_FRAME_677_677_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_B10_FRAME_677_677_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file canBus_10.dbc, frame frame_677 (677, 0x2a5): Checksums are supported only as an eight Bit integer on byte boundary
#endif
 

/*
 * Type definitions
 */

 

/*
 * Data declarations
 */

 

/*
 * Function declarations
 */

#endif // !defined(CAP_PRECOCHECK_DEFINED)
