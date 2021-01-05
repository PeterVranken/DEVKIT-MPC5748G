/**
 * @file mai_main.c
 * A simple main function for demonstration how to use and integrate the generated parts of
 * the C code.
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
/* Module interface
 *   main
 * Local functions
 *   printAndValidate
 */

/*
 * Include files
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>

#include "pwr_computeEnginePower.h"
#include "cap_canApi.h"
#include "mai_main.h"


/*
 * Defines
 */

#ifndef M_PI
/** PI for C99 compilation. */
# define M_PI 3.14159265358979
#endif


/*
 * Local type definitions
 */


/*
 * Local prototypes
 */


/*
 * Data definitions
 */


/*
 * Function implementation
 */



/**
 * Print current output of the Embedded Coder model and validate it by assertion.
 */

static void printAndValidate()
{
    double sor = CAP_PT_1024_SPEEDOFROTATION_BIN_TO_DBL
                                (cap_canBus_PT.PT_StateEcu01_1024_sts.signals.speedOfRotation)
         , tq = CAP_PT_1040_TORQUE_BIN_TO_DBL
                                (cap_canBus_PT.PT_StateEcu02_1040_sts.signals.torque)
         , pwr = CAP_PT_1536_POWER_BIN_TO_DBL(cap_pPT_InfoPowerDisplay_1536->power);
    unsigned noDlcErrs = cap_canBus_PT.PT_StatusPowerDisplay_1537_sts.signals.noDlcErrors
           , noChksumErrs = cap_canBus_PT.PT_StatusPowerDisplay_1537_sts.signals.noCheckSumErrors
           , noSqcErrs = cap_canBus_PT.PT_StatusPowerDisplay_1537_sts.signals.noSqcErrors;

    double pwrOk = 2.0*M_PI/60.0 * sor * tq
         , relErr = pwrOk == 0.0? (pwr == 0.0? 0.0: 1.0)
                                : (pwr - pwrOk)/pwrOk;

    printf( "SOR: %6.1f rpm, torque: %5.1f Nm, power: %5.1f kW, relErr: %3.1f%%, status: %1u,"
            " noDlcErrs: %3u, noChksumErrs: %3u, noSqcErrs: %3u\n"
          , sor
          , tq
          , pwr / 1000.0
          , 100.0 * relErr
          , (unsigned)cap_canBus_PT.PT_InfoPowerDisplay_1536_sts.signals.state
          , noDlcErrs
          , noChksumErrs
          , noSqcErrs
          );

    assert(cap_canBus_PT.PT_InfoPowerDisplay_1536_sts.signals.state != 0
           || (pwr <= pwrOk + 2500.0  &&  pwr >= pwrOk - 2500.0  &&  fabs(relErr) <= 0.02)
          );

} /* End of printAndValidate */




/**
 * Run the Embedded Coder generate step function an number of times and print and validate
 * the output.
 *   @return
 * 1, if function succeeded, else 0.
 *   @param noArgs
 * Number of command line arguments.
 *   @param argAry
 * Array of command line arguments.
 */

int main(int noArgs, const char *argAry[])
{
    const char * const greeting =
       "----------------------------------------------------------------------------------------\n"
       " EmbeddedCoderAPIWithBusStruct - A demo of comFramework's support of the Embedded Coder\n"
       " Copyright (C) 2016 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)\n"
       " This is free software; see the source for copying conditions. There is NO\n"
       " warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.\n"
       "----------------------------------------------------------------------------------------";

    /* Print the greeting. */
    printf("%s\n", greeting);

    /* Initialize the Embedded Coder software module(s). */
    pwr_computeEnginePower_initialize();

    assert(cap_canBus_PT.PT_StateEcu01_1024_sts.stsTransmission == cap_stsTransm_neverReceived
           &&  cap_canBus_PT.PT_StateEcu02_1040_sts.stsTransmission
               == cap_stsTransm_neverReceived
          );
    assert(cap_canBus_PT.PT_StatusPowerDisplay_1537_sts.signals.noDlcErrors == 0
           &&  cap_canBus_PT.PT_StatusPowerDisplay_1537_sts.signals.noCheckSumErrors == 0
           &&  cap_canBus_PT.PT_StatusPowerDisplay_1537_sts.signals.noSqcErrors == 0
          );
    assert(cap_canBus_PT.PT_InfoPowerDisplay_1536_sts.signals.state == 0);

    /* Run the step function without writing input values into the CAN API - the generated
       initialization code should guarantee a defined status. */
    pwr_computeEnginePower_step();
    assert(cap_canBus_PT.PT_InfoPowerDisplay_1536_sts.signals.state == 1);
    printAndValidate();

    /* Set ECU values and repeat. */
    cap_canBus_PT.PT_StateEcu01_1024_sts.signals.speedOfRotation =
                                                CAP_PT_1024_SPEEDOFROTATION_DBL_TO_BIN(800.0);
    cap_canBus_PT.PT_StateEcu02_1040_sts.signals.torque =
                                                CAP_PT_1040_TORQUE_DBL_TO_BIN(5.0);
    cap_canBus_PT.PT_StateEcu01_1024_sts.stsTransmission = cap_stsTransm_okay;
    cap_canBus_PT.PT_StateEcu02_1040_sts.stsTransmission = cap_stsTransm_okay;
    pwr_computeEnginePower_step();
    assert(cap_canBus_PT.PT_InfoPowerDisplay_1536_sts.signals.state == 0);
    printAndValidate();

    /* Set ECU values and repeat. */
    cap_canBus_PT.PT_StateEcu01_1024_sts.signals.speedOfRotation =
                                                CAP_PT_1024_SPEEDOFROTATION_DBL_TO_BIN(2500.0);
    cap_canBus_PT.PT_StateEcu02_1040_sts.signals.torque =
                                                CAP_PT_1040_TORQUE_DBL_TO_BIN(125.0);
    cap_canBus_PT.PT_StateEcu01_1024_sts.stsTransmission = cap_stsTransm_okay;
    cap_canBus_PT.PT_StateEcu02_1040_sts.stsTransmission = cap_stsTransm_okay;
    pwr_computeEnginePower_step();
    assert(cap_canBus_PT.PT_InfoPowerDisplay_1536_sts.signals.state == 0);
    printAndValidate();

    /* Set ECU values and repeat. */
    cap_canBus_PT.PT_StateEcu01_1024_sts.signals.speedOfRotation =
                                             CAP_PT_1024_SPEEDOFROTATION_DBL_TO_BIN(1000.0);
    cap_canBus_PT.PT_StateEcu02_1040_sts.signals.torque =
                                             CAP_PT_1040_TORQUE_DBL_TO_BIN(-7.0);
    cap_canBus_PT.PT_StateEcu01_1024_sts.stsTransmission = cap_stsTransm_okay;
    cap_canBus_PT.PT_StateEcu02_1040_sts.stsTransmission = cap_stsTransm_okay;
    pwr_computeEnginePower_step();
    assert(cap_canBus_PT.PT_InfoPowerDisplay_1536_sts.signals.state == 0);
    printAndValidate();

    /* Set specified maximum ECU values and repeat. */
    cap_canBus_PT.PT_StateEcu01_1024_sts.signals.speedOfRotation =
                    CAP_PT_1024_SPEEDOFROTATION_DBL_TO_BIN(CAP_PT_1024_SPEEDOFROTATION_MAX);
    cap_canBus_PT.PT_StateEcu02_1040_sts.signals.torque =
                    CAP_PT_1040_TORQUE_DBL_TO_BIN(CAP_PT_1040_TORQUE_MAX);
    cap_canBus_PT.PT_StateEcu01_1024_sts.stsTransmission = cap_stsTransm_okay;
    cap_canBus_PT.PT_StateEcu02_1040_sts.stsTransmission = cap_stsTransm_okay;
    pwr_computeEnginePower_step();
    assert(cap_canBus_PT.PT_InfoPowerDisplay_1536_sts.signals.state == 0);
    printAndValidate();

    /* Set valus above specified maximum ECU values and repeat. */
    cap_canBus_PT.PT_StateEcu01_1024_sts.signals.speedOfRotation =
                    CAP_PT_1024_SPEEDOFROTATION_DBL_TO_BIN(CAP_PT_1024_SPEEDOFROTATION_MAX);
    cap_canBus_PT.PT_StateEcu02_1040_sts.signals.torque =
                    CAP_PT_1040_TORQUE_DBL_TO_BIN(2.0*CAP_PT_1040_TORQUE_MAX);
    cap_canBus_PT.PT_StateEcu01_1024_sts.stsTransmission = cap_stsTransm_okay;
    cap_canBus_PT.PT_StateEcu02_1040_sts.stsTransmission = cap_stsTransm_okay;
    pwr_computeEnginePower_step();
    assert(cap_canBus_PT.PT_InfoPowerDisplay_1536_sts.signals.state == 2);
    printAndValidate();

    /* Set valus above specified maximum ECU values and repeat. */
    cap_canBus_PT.PT_StateEcu01_1024_sts.signals.speedOfRotation =
                    CAP_PT_1024_SPEEDOFROTATION_DBL_TO_BIN(CAP_PT_1024_SPEEDOFROTATION_MAX);
    cap_canBus_PT.PT_StateEcu02_1040_sts.signals.torque =
                    CAP_PT_1040_TORQUE_DBL_TO_BIN(-2.0*CAP_PT_1040_TORQUE_MAX);
    cap_canBus_PT.PT_StateEcu01_1024_sts.stsTransmission = cap_stsTransm_okay;
    cap_canBus_PT.PT_StateEcu02_1040_sts.stsTransmission = cap_stsTransm_okay;
    pwr_computeEnginePower_step();
    assert(cap_canBus_PT.PT_InfoPowerDisplay_1536_sts.signals.state == 2);
    printAndValidate();

    /* Set valid values but indicate a transmission problem. */
    cap_canBus_PT.PT_StateEcu01_1024_sts.signals.speedOfRotation =
                                                CAP_PT_1024_SPEEDOFROTATION_DBL_TO_BIN(4500.0);
    cap_canBus_PT.PT_StateEcu02_1040_sts.signals.torque =
                                                CAP_PT_1040_TORQUE_DBL_TO_BIN(251.0);
    cap_canBus_PT.PT_StateEcu01_1024_sts.stsTransmission = cap_stsTransm_errChecksum;
    cap_canBus_PT.PT_StateEcu02_1040_sts.stsTransmission = cap_stsTransm_okay;
    pwr_computeEnginePower_step();
    assert(cap_canBus_PT.PT_InfoPowerDisplay_1536_sts.signals.state == 1);
    assert(cap_canBus_PT.PT_StatusPowerDisplay_1537_sts.signals.noDlcErrors == 0
           &&  cap_canBus_PT.PT_StatusPowerDisplay_1537_sts.signals.noCheckSumErrors == 1
           &&  cap_canBus_PT.PT_StatusPowerDisplay_1537_sts.signals.noSqcErrors == 0
          );
    printAndValidate();

    /* Set valid values but indicate another transmission problem. */
    cap_canBus_PT.PT_StateEcu01_1024_sts.signals.speedOfRotation =
                                                CAP_PT_1024_SPEEDOFROTATION_DBL_TO_BIN(4500.0);
    cap_canBus_PT.PT_StateEcu02_1040_sts.signals.torque =
                                                CAP_PT_1040_TORQUE_DBL_TO_BIN(251.0);
    cap_canBus_PT.PT_StateEcu01_1024_sts.stsTransmission = cap_stsTransm_okay;
    cap_canBus_PT.PT_StateEcu02_1040_sts.stsTransmission = cap_stsTransm_errSequence;
    pwr_computeEnginePower_step();
    assert(cap_canBus_PT.PT_InfoPowerDisplay_1536_sts.signals.state == 1);
    assert(cap_canBus_PT.PT_StatusPowerDisplay_1537_sts.signals.noDlcErrors == 0
           &&  cap_canBus_PT.PT_StatusPowerDisplay_1537_sts.signals.noCheckSumErrors == 1
           &&  cap_canBus_PT.PT_StatusPowerDisplay_1537_sts.signals.noSqcErrors == 1
          );
    printAndValidate();

    /* Set valid values but indicate another transmission problem. */
    cap_canBus_PT.PT_StateEcu01_1024_sts.signals.speedOfRotation =
                                                CAP_PT_1024_SPEEDOFROTATION_DBL_TO_BIN(4500.0);
    cap_canBus_PT.PT_StateEcu02_1040_sts.signals.torque =
                                                CAP_PT_1040_TORQUE_DBL_TO_BIN(251.0);
    cap_canBus_PT.PT_StateEcu01_1024_sts.stsTransmission = cap_stsTransm_errDLC;
    cap_canBus_PT.PT_StateEcu02_1040_sts.stsTransmission = cap_stsTransm_errDLC;
    pwr_computeEnginePower_step();
    assert(cap_canBus_PT.PT_InfoPowerDisplay_1536_sts.signals.state == 1);
    assert(cap_canBus_PT.PT_StatusPowerDisplay_1537_sts.signals.noDlcErrors == 1
           &&  cap_canBus_PT.PT_StatusPowerDisplay_1537_sts.signals.noCheckSumErrors == 1
           &&  cap_canBus_PT.PT_StatusPowerDisplay_1537_sts.signals.noSqcErrors == 1
          );
    printAndValidate();

    /* Check initial values of user limits. */
    assert(cap_canBus_PT.PT_UserLimits_2032_sts.signals.minSpeedOfRotation
           == CAP_PT_2032_MINSPEEDOFROTATION_DBL_TO_BIN(800.0)
           &&  cap_canBus_PT.PT_UserLimits_2032_sts.signals.maxSpeedOfRotation
               == CAP_PT_2032_MAXSPEEDOFROTATION_DBL_TO_BIN(6000.0)
           &&  cap_canBus_PT.PT_UserLimits_2032_sts.signals.minPower
               == CAP_PT_2032_MINPOWER_DBL_TO_BIN(-1.0)
           &&  cap_canBus_PT.PT_UserLimits_2032_sts.signals.maxPower
               == CAP_PT_2032_MAXPOWER_DBL_TO_BIN(100.0)
          );
          
    /* Validate that the user limits are used. The last update should have happened when
       the last valid set of values was passed in. These were out of the user specified
       limits. */
    assert(!cap_canBus_PT.PT_LimitsPowerDisplay_1538_sts.signals.belowMinSpeedOfRotation
           &&  cap_canBus_PT.PT_LimitsPowerDisplay_1538_sts.signals.aboveMaxSpeedOfRotation
           &&  !cap_canBus_PT.PT_LimitsPowerDisplay_1538_sts.signals.belowMinPower
           &&  cap_canBus_PT.PT_LimitsPowerDisplay_1538_sts.signals.aboveMaxPower
          );
    
    /* Send new valid input values and validate that they are correctly compared with the
       user limits. */
    cap_canBus_PT.PT_StateEcu01_1024_sts.signals.speedOfRotation =
                                                CAP_PT_1024_SPEEDOFROTATION_DBL_TO_BIN(4000.0);
    cap_canBus_PT.PT_StateEcu02_1040_sts.signals.torque =
                                                CAP_PT_1040_TORQUE_DBL_TO_BIN(157.0);
    cap_canBus_PT.PT_StateEcu01_1024_sts.stsTransmission = cap_stsTransm_okay;
    cap_canBus_PT.PT_StateEcu02_1040_sts.stsTransmission = cap_stsTransm_okay;
    pwr_computeEnginePower_step();
    printAndValidate();
    assert(cap_canBus_PT.PT_InfoPowerDisplay_1536_sts.signals.state == 0);
    assert(cap_canBus_PT.PT_StatusPowerDisplay_1537_sts.signals.noDlcErrors == 1
           &&  cap_canBus_PT.PT_StatusPowerDisplay_1537_sts.signals.noCheckSumErrors == 1
           &&  cap_canBus_PT.PT_StatusPowerDisplay_1537_sts.signals.noSqcErrors == 1
          );
    assert(!cap_canBus_PT.PT_LimitsPowerDisplay_1538_sts.signals.belowMinSpeedOfRotation
           &&  !cap_canBus_PT.PT_LimitsPowerDisplay_1538_sts.signals.aboveMaxSpeedOfRotation
           &&  !cap_canBus_PT.PT_LimitsPowerDisplay_1538_sts.signals.belowMinPower
           &&  !cap_canBus_PT.PT_LimitsPowerDisplay_1538_sts.signals.aboveMaxPower
          );
          
    /* Set user limits to new values and validate that they are still used correct. */
    cap_canBus_PT.PT_UserLimits_2032_sts.signals.minSpeedOfRotation = 
                                        CAP_PT_2032_MINSPEEDOFROTATION_DBL_TO_BIN(4002.0);
    cap_canBus_PT.PT_UserLimits_2032_sts.signals.minPower = 
                                        CAP_PT_2032_MINPOWER_DBL_TO_BIN(70.0); /* kW */
    cap_canBus_PT.PT_StateEcu01_1024_sts.signals.speedOfRotation =
                                                CAP_PT_1024_SPEEDOFROTATION_DBL_TO_BIN(4000.0);
    cap_canBus_PT.PT_StateEcu02_1040_sts.signals.torque =
                                                CAP_PT_1040_TORQUE_DBL_TO_BIN(165.0);
    cap_canBus_PT.PT_StateEcu01_1024_sts.stsTransmission = cap_stsTransm_okay;
    cap_canBus_PT.PT_StateEcu02_1040_sts.stsTransmission = cap_stsTransm_okay;
    pwr_computeEnginePower_step();
    printAndValidate();
    assert(cap_canBus_PT.PT_InfoPowerDisplay_1536_sts.signals.state == 0);
    assert(cap_canBus_PT.PT_StatusPowerDisplay_1537_sts.signals.noDlcErrors == 1
           &&  cap_canBus_PT.PT_StatusPowerDisplay_1537_sts.signals.noCheckSumErrors == 1
           &&  cap_canBus_PT.PT_StatusPowerDisplay_1537_sts.signals.noSqcErrors == 1
          );
    assert(cap_canBus_PT.PT_LimitsPowerDisplay_1538_sts.signals.belowMinSpeedOfRotation
           &&  !cap_canBus_PT.PT_LimitsPowerDisplay_1538_sts.signals.aboveMaxSpeedOfRotation
           &&  cap_canBus_PT.PT_LimitsPowerDisplay_1538_sts.signals.belowMinPower
           &&  !cap_canBus_PT.PT_LimitsPowerDisplay_1538_sts.signals.aboveMaxPower
          );

} /* End of main */




