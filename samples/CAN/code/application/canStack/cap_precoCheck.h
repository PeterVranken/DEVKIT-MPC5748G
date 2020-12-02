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
 * This file has been created with comFramework - codeGenerator version 1.10.4,
 * see http://sourceforge.net/projects/comframe/
 *
 * Copyright (C) 2020 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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
#include "cap_canApi.h"
#include "cde_canStatistics.h"


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



/* For each bus, there should be at least one affected message, received or sent. There a
   typical mistakes in configuration of the code generator, which lead to not considering
   any message from the DBC file. These kind of mistakes are address by this check. */
_Static_assert( CDE_NO_CAN_FRAMES_PT
              , "No single message from CAN_RT_attributed.dbc is considered by the"
                " generated code. This is likely due to an error in the configuration"
                " of the code generator. Did you set the node name correctly?"
              );

/** Check the definition of the checksum of frame RT_IRTemp_Temp_1 (9503013, 0x910125)
    on bus PT.\n
      A precondition for checksums is that they have eight Bit and are positioned at a byte
    position. */
#if CAP_PT_RT_IRTEMP_TEMP_1_9503013_CHECKSUM_LENGTH != 8               \
    || (!CAP_PT_RT_IRTEMP_TEMP_1_9503013_CHECKSUM_IS_BIG_ENDIAN        \
        && CAP_PT_RT_IRTEMP_TEMP_1_9503013_CHECKSUM_STARTBIT%8 != 0    \
        || CAP_PT_RT_IRTEMP_TEMP_1_9503013_CHECKSUM_IS_BIG_ENDIAN      \
           && CAP_PT_RT_IRTEMP_TEMP_1_9503013_CHECKSUM_STARTBIT%8 != 7 \
       )
# error Input file CAN_RT_attributed.dbc, frame RT_IRTemp_Temp_1 (9503013, 0x910125): Checksums are supported only as an eight Bit integer on byte boundary
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


/*
 * Inline function definitions
 */

#endif // !defined(CAP_PRECOCHECK_DEFINED)
