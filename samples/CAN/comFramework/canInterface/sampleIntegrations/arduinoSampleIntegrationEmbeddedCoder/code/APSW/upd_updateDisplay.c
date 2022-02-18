/**
 * @file upd_computeEnginePower.c
 * Use the display to show the results of the APSW, which is implemented as
 * Simulink/Embedded Coder model. This module implements a 100ms step funtion, which
 * updates the display contents.
 *
 * Copyright (C) 2015-2016 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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
 *   upd_updateDisplay
 * Local functions
 */

/*
 * Include files
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "rtos_assert.h"
#include "cap_canApi.h"
#include "dpy_display.h"
#include "apt_applicationTask.h"
#include "sim_simulateCanReception.h"
#include "pwr_computeEnginePower.h"
#include "upd_updateDisplay.h"


/*
 * Defines
 */

#ifndef M_PI
# define M_PI   3.14159265358979323846
#endif

/* The positions of the different error indicator characters in the status string. */
#define IDX_CHAR_TO     0
#define IDX_CHAR_DLC    1
#define IDX_CHAR_CHKSUM 2
#define IDX_CHAR_SQC    3
#define IDX_CHAR_BUSOFF 4
#define IDX_CHAR_LAST   4


/*
 * Local type definitions
 */


/*
 * Local prototypes
 */


/*
 * Data definitions
 */
 
/**
 * Update the information shown in the LCDisplay. This function is to called regularly from
 * the 100ms APSW task.
 */

void upd_updateDisplay()
{
    cli();
    uint16_t power = cap_canBus_PT.PT_InfoPowerDisplay_1536_sts.signals.power;
    sei();
    
    /* Prepare the transmission status as string. */
    char strSts[IDX_CHAR_LAST+1+1];
    
    /* The errors timeout, DLC, checksum and squence counter have been prepared for display
       by the Simulink model. One of its outputs is an error of four Boolean, which
       indicate one of the transmission problems each. The model implements a hold
       function, which ensures that a single occurance of the error is displayed for a
       duration, which makes it perceptible. The only thing to do here is to translate the
       Booleans into the displayed string. */
    strSts[IDX_CHAR_TO] = pwr_transmissionErrAry[0]? 'T': ' ';
    strSts[IDX_CHAR_DLC] = pwr_transmissionErrAry[3]? 'D': ' ';
    strSts[IDX_CHAR_CHKSUM] = pwr_transmissionErrAry[1]? 'C': ' ';
    strSts[IDX_CHAR_SQC] = pwr_transmissionErrAry[2]? 'S': ' ';
    
    /* Bus off is an error status, which is provided by the CAN stack. It is set as long as
       the bus is not available. For this error we don't implement a hold mechanism; the
       duration of the events is long enough to justify this. */
    strSts[IDX_CHAR_BUSOFF] = apt_canBusOff? 'B': ' ';
    
    /* Terminate string and display it. */
    strSts[IDX_CHAR_LAST+1] = '\0';
    dpy_printStatus(strSts);

    /* Print current power values on the LCDisplay. Do this at two rates: high update rate
       for the pseudo-analog display, low update rate for numeric display.
         The status is ignored; if it is not "valid" then the numeric value is still the
       best possible choice to display. */
            
    /* The display expects power as an integer value in kW. */
    int16_t powerInKw_I16 = 4ul*power/125 - 500;
    /* The pseudo-analog display doesn't know negative values. They have to be truncated
       here. */
    uint8_t powerInKw_U8 = powerInKw_I16 >= 255
                           ? 255
                           : (powerInKw_I16 <= 0? 0: (uint8_t)powerInKw_I16)
                           ;
    dpy_printValueAsBar(/* value */ powerInKw_U8, /* fullScale */ 250);

    static uint8_t cntDispPwrNum_ = 1;
    if(cntDispPwrNum_ == 5)
    {
        cli();
        int16_t torque = cap_canBus_PT.PT_StateEcu02_1040_sts.signals.torque;
        sei();
        dpy_printTqAndPwr(torque/2, powerInKw_I16);
        cntDispPwrNum_ = 0;
    }
    ++ cntDispPwrNum_;

} /* End of upd_updateDisplay */
