#ifndef CBK_PRECOCHECK_DEFINED
#define CBK_PRECOCHECK_DEFINED
/**
 * @file cbk_precoCheck.h
 * 
 * This header file contains a number of compile time checks of static elements of the
 * network database, which need to be fulfilled for successful compilation and execution of
 * the generated code.\n
 *   The file is included by the generated file cbk_callbacks.c after setting a number of
 * #define's that are related to frames and signals. These defines are checked for valid
 * values. The checks are completed by some tests of the attributes, which the code
 * generation depends on. It's highly probable that these tests will emit a compile time
 * error if the code generation is done with an arbitrary other network file.
 *   @remark
 * All checks relate to static properties of the network database. If these tests can be
 * done by code generation template expressions (mainly the test of Boolean object
 * properties and test of existence of objects) then this way is preferred. Code generation
 * templates can't do numeric comparisons. If those are required than the code generation
 * process generates according C preprocessor conditions with #error directives. Since the
 * former kind of tests is frequently used you will not see anything in this file about
 * most of the tests! Error code will show up only if the error has been detected in the
 * network file.
 *
 * This file has been created with comFramework - codeGenerator version 1.7.0,
 * see http://sourceforge.net/projects/comframe/
 *
 * Copyright (C) 2016 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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


/*
 * Defines
 */

/** This is not a common, global header file. It must only be included by \a 
    cbk_callbacks.c. Check. */
#ifdef CBK_INCLUDES_PRECO_CHECKS
# undef CBK_INCLUDES_PRECO_CHECKS
#else
# error This header must be included only by cbk_callbacks.c
#endif


/** Check the definition of the checksum of frame StateEcu01 (1024, 0x400).\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if PT_STATEECU01_1024_CHECKSUM_LENGTH != 8               \
    || (!PT_STATEECU01_1024_CHECKSUM_IS_BIG_ENDIAN        \
        && PT_STATEECU01_1024_CHECKSUM_STARTBIT%8 != 0    \
        || PT_STATEECU01_1024_CHECKSUM_IS_BIG_ENDIAN      \
           && PT_STATEECU01_1024_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Frame StateEcu01 (1024, 0x400): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame StateEcu02 (1040, 0x410).\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if PT_STATEECU02_1040_CHECKSUM_LENGTH != 8               \
    || (!PT_STATEECU02_1040_CHECKSUM_IS_BIG_ENDIAN        \
        && PT_STATEECU02_1040_CHECKSUM_STARTBIT%8 != 0    \
        || PT_STATEECU02_1040_CHECKSUM_IS_BIG_ENDIAN      \
           && PT_STATEECU02_1040_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Frame StateEcu02 (1040, 0x410): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame UserLimits (2032, 0x7f0).\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if PT_USERLIMITS_2032_CHECKSUM_LENGTH != 8               \
    || (!PT_USERLIMITS_2032_CHECKSUM_IS_BIG_ENDIAN        \
        && PT_USERLIMITS_2032_CHECKSUM_STARTBIT%8 != 0    \
        || PT_USERLIMITS_2032_CHECKSUM_IS_BIG_ENDIAN      \
           && PT_USERLIMITS_2032_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Frame UserLimits (2032, 0x7f0): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame InfoPowerDisplay (1536, 0x600).\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if PT_INFOPOWERDISPLAY_1536_CHECKSUM_LENGTH != 8               \
    || (!PT_INFOPOWERDISPLAY_1536_CHECKSUM_IS_BIG_ENDIAN        \
        && PT_INFOPOWERDISPLAY_1536_CHECKSUM_STARTBIT%8 != 0    \
        || PT_INFOPOWERDISPLAY_1536_CHECKSUM_IS_BIG_ENDIAN      \
           && PT_INFOPOWERDISPLAY_1536_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Frame InfoPowerDisplay (1536, 0x600): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the checksum of frame StatusPowerDisplay (1537, 0x601).\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if PT_STATUSPOWERDISPLAY_1537_CHECKSUM_LENGTH != 8               \
    || (!PT_STATUSPOWERDISPLAY_1537_CHECKSUM_IS_BIG_ENDIAN        \
        && PT_STATUSPOWERDISPLAY_1537_CHECKSUM_STARTBIT%8 != 0    \
        || PT_STATUSPOWERDISPLAY_1537_CHECKSUM_IS_BIG_ENDIAN      \
           && PT_STATUSPOWERDISPLAY_1537_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Frame StatusPowerDisplay (1537, 0x601): Checksums are supported only as an eight Bit integer on byte boundary
#endif

/** Check the definition of the sequence counter of frame StateEcu01 (1024, 0x400).\n
      A precondition for sequence counters is that they have only up to eight Bit. */
#if PT_STATEECU01_1024_SQC_LENGTH > 8
# error Frame StateEcu01 (1024, 0x400): Sequence counters must be no longer than eight Bit, found 4 Bit
#endif

/** Check the definition of the sequence counter of frame StateEcu02 (1040, 0x410).\n
      A precondition for sequence counters is that they have only up to eight Bit. */
#if PT_STATEECU02_1040_SQC_LENGTH > 8
# error Frame StateEcu02 (1040, 0x410): Sequence counters must be no longer than eight Bit, found 4 Bit
#endif

/** Check the definition of the sequence counter of frame UserLimits (2032, 0x7f0).\n
      A precondition for sequence counters is that they have only up to eight Bit. */
#if PT_USERLIMITS_2032_SQC_LENGTH > 8
# error Frame UserLimits (2032, 0x7f0): Sequence counters must be no longer than eight Bit, found 4 Bit
#endif

/** Check the definition of the sequence counter of frame InfoPowerDisplay (1536, 0x600).\n
      A precondition for sequence counters is that they have only up to eight Bit. */
#if PT_INFOPOWERDISPLAY_1536_SQC_LENGTH > 8
# error Frame InfoPowerDisplay (1536, 0x600): Sequence counters must be no longer than eight Bit, found 4 Bit
#endif

/** Check the definition of the sequence counter of frame StatusPowerDisplay (1537, 0x601).\n
      A precondition for sequence counters is that they have only up to eight Bit. */
#if PT_STATUSPOWERDISPLAY_1537_SQC_LENGTH > 8
# error Frame StatusPowerDisplay (1537, 0x601): Sequence counters must be no longer than eight Bit, found 7 Bit
#endif

/** Check the definition of the sequence counter of frame LimitsPowerDisplay (1538, 0x602).\n
      A precondition for sequence counters is that they have only up to eight Bit. */
#if PT_LIMITSPOWERDISPLAY_1538_SQC_LENGTH > 8
# error Frame LimitsPowerDisplay (1538, 0x602): Sequence counters must be no longer than eight Bit, found 3 Bit
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

#endif // !defined(CBK_PRECOCHECK_DEFINED)
