/**
 * @file apt_applicationTask.c
 * This file links the APSW to the operating system. It contains the
 * entry points into all the application task functions. A set of (regular) tasks is
 * created by the operating system and may or may not be implemented by the APSW. (If
 * not, an empty default implementation is used.)\n
 *   The init task is for example used to initialize all data structures of the CAN
 * interface.\n
 *   The regularly executed run-time tasks run the CAN interface engine and call the APSW.
 * The CAN interface engine updates all signal values and status in the global CAN API and
 * sends due messages, filled with information read from this API.
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
/* Module interface
 *   bsw_taskUserInit
 *   bsw_taskUser1ms
 *   bsw_taskUser10ms
 *   bsw_taskUser100ms
 *   bsw_taskUser1000ms
 * Local functions
 *   tokenizeCmdLine
 *   version
 *   showW
 *   showC
 *   greeting
 *   help
 */


/*
 * Include files
 */

#include "apt_applicationTask.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

#include "cap_canApi.h"
#include "lbd_ledAndButtonDriver.h"
#include "bsw_basicSoftware.h"
#include "cdr_canDriverAPI.h"
#include "ede_eventDispatcherEngine.h"
#include "cst_canStatistics.h"
#include "cdt_canDataTables.h"
#include "f2d_float2Double.h"
#include "can_canRuntime.h"
#include "sio_serialIO.h"
#include "cmd_canCommand.h"
#include "pwm_pwmIODriver.h"
#include "c2p_canToPWM.h"

/*
 * Defines
 */

/** Software version */
#define VERSION "0.7.0"

/** Floating point random number with more than 15 Bit resolution; taken fron
    http://www.azillionmonkeys.com/qed/random.html on Jan 23, 2017.
      @remark Caution, the definition make use of a GNU extension and is not portable. */
#define DRAND() ({                                                                  \
    double d;                                                                       \
    do {                                                                            \
       d = (((rand() * RS_SCALE) + rand()) * RS_SCALE + rand()) * RS_SCALE;         \
    } while(d >= 1); /* Round off */                                                \
    d;                                                                              \
})

/** Helper for #DRAND. */
#define RS_SCALE (1.0 / (1.0 + RAND_MAX))

/** A scaled floating point random number in the range [a, b). */
#define RAND(a,b) ((double)((b)-(a))*DRAND()+(double)(a))

/** A Boolean random number with given probability p of getting a true. */
#define BOOL_RAND(p) ((DRAND()<(p))? true: false)


/*
 * Local type definitions
 */


/*
 * Local prototypes
 */


/*
 * Data definitions
 */

/** Simple counter of 1ms application task invokations. Used for timing operations. */
volatile static unsigned int DATA_P1(_cntTask1ms) = 0;

/** Simple counter of 10ms application task invokations. Used for timing operations. */
volatile static unsigned int DATA_P1(_cntTask10ms) = 0;

/** Switch to enable/disable the continuous display of PWM measurement results. */
volatile static bool SBSS_P1(_enableDisplayPWM) = false;

/*
 * Function implementation
 */


/**
 * Simple command line parsing. Replace white space in the command line by string
 * termination characters and record the beginnings of the non white space regions.
 *   @param pArgC
 * Prior to call: * \a pArgC is set by the caller to the number of entries available in
 * argV.\n
 *   After return: The number of found arguments, i.e., the number of non white space
 * regions in the command line.
 *   @param argV
 * The vector of arguments, i.e., pointers to the non white space regions in the command
 * line.
 *   @param cmdLine
 * Prior to call: The original command line.\n
 *   After return: White space in the command line is replaced by zero bytes. Note, not
 * necessarily all white space due to the restriction superimposed by \a pArgC.
 */
static void tokenizeCmdLine( unsigned int * const pArgC
                           , const char *argV[]
                           , char * const cmdLine
                           )
{
    char *pC = cmdLine;
    unsigned int noArgsFound = 0;
    while(noArgsFound < *pArgC)
    {
        /* Look for beginning of next argument. */
        while(isspace((int)*pC))
            ++ pC;

        /* Decide if we found a new argument of if we reached the end of the command line. */
        if(*pC != '\0')
        {
            /* New argument found. Record the beginning. */
            argV[noArgsFound++] = pC;

            /* Look for its end. */
            do
            {
                ++ pC;
            }
            while(*pC != '\0'  && !isspace((int)*pC));

            if(*pC != '\0')
            {
                /* There are characters left in the command line. Terminate the found
                   argument and continue with the outer loop. */
                * pC++ = '\0';
            }
            else
            {
                /* Command line has been parsed completely, leave outer loop and return. */
                break;
            }
        }
        else
        {
            /* Command line has been parsed completely, leave outer loop and return. */
            break;

        } /* End if(Further non white space region found?) */

    } /* End while(Still room left in ArgV) */

    *pArgC = noArgsFound;

} /* End of tokenizeCmdLine */



/**
 * Print version designation.
 */
static void version()
{
    static const char RODATA(version)[] =
    "DEVKIT-MPC5748G - CAN Demo, demonstration of safe-RTOS' CAN driver\r\n"
    "Copyright (C) 2017-2023  Peter Vranken\r\n"
    "Version " VERSION
    #ifdef DEBUG
    " (Configuration: DEBUG"
    #else
    " (Configuration: PRODUCTION"
    #endif
    #ifdef LINK_IN_RAM
    " in RAM)"
    #else
    " in flash ROM)"
    #endif
    "\r\n";

    fputs(version, stdout);
    
} /* End of version */


/**
 * GPL proposes 'show w', see http://www.gnu.org/licenses/gpl-3.0.html (downloaded
 * Oct 27, 2017)
 */
static void showW()
{
    version();
    
    static const char RODATA(gplShowW)[] =
    "GNU LESSER GENERAL PUBLIC LICENSE\r\n"
    "\r\n"
    "Version 3, 29 June 2007\r\n"
    "\r\n"
    "(...)\r\n"
    "\r\n"
    "15. Disclaimer of Warranty.\r\n"
    "\r\n"
    "THERE IS NO WARRANTY FOR THE PROGRAM, TO THE EXTENT PERMITTED BY\r\n"
    "APPLICABLE LAW. EXCEPT WHEN OTHERWISE STATED IN WRITING THE COPYRIGHT\r\n"
    "HOLDERS AND/OR OTHER PARTIES PROVIDE THE PROGRAM \"AS IS\" WITHOUT\r\n"
    "WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING, BUT NOT\r\n"
    "LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A\r\n"
    "PARTICULAR PURPOSE. THE ENTIRE RISK AS TO THE QUALITY AND PERFORMANCE OF\r\n"
    "THE PROGRAM IS WITH YOU. SHOULD THE PROGRAM PROVE DEFECTIVE, YOU ASSUME\r\n"
    "THE COST OF ALL NECESSARY SERVICING, REPAIR OR CORRECTION.\r\n";

    fputs(gplShowW, stdout);

} /* End of showW */



/**
 * GPL proposes 'show c', see http://www.gnu.org/licenses/gpl-3.0.html (downloaded
 * Oct 27, 2017)
 */
static void showC()
{
    version();
    
    static const char RODATA(gplShowC)[] =
    "This program is free software: you can redistribute it and/or modify\r\n"
    "it under the terms of the GNU Lesser General Public License as published\r\n"
    "by the Free Software Foundation, either version 3 of the License, or\r\n"
    "(at your option) any later version.\r\n"
    "\r\n"
    "This program is distributed in the hope that it will be useful,\r\n"
    "but WITHOUT ANY WARRANTY; without even the implied warranty of\r\n"
    "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\r\n"
    "GNU Lesser General Public License for more details.\r\n"
    "\r\n"
    "You should have received a copy of the GNU Lesser General Public License\r\n"
    "along with this program.  If not, see <https://www.gnu.org/licenses/>.\r\n";

    fputs(gplShowC, stdout);

} /* End of showC */



/**
 * Print program greeting.
 */
static void greeting()
{
    version();

    static const char RODATA(greeting)[] =
    "This program comes with ABSOLUTELY NO WARRANTY; for details type `show w'.\r\n"
    "This is free software, and you are welcome to redistribute it under certain\r\n"
    "conditions; type `show c' for details.\r\n";

    fputs(greeting, stdout);
    
} /* End of greeting */


/**
 * Print usage text.
 */
static void help()
{
    version();

    static const char RODATA(help)[] =
    "Type:\r\n"
    "help: Get this help text\r\n"
    "show c, show w: Show details of software license\r\n"
    "show PWM [on|off]: Enable/disable display of PWM input measurement on PA2 and PA6\r\n"
    "version: Print software version designation\r\n"
    "listen [ID] signal: Report changes of Rx signal. ID is a decimal CAN ID, for"
    " disambiguation of signal name. Maybe preceeded by `x' to specify an extended CAN ID\r\n"
    "unlisten [ID] signal: No longer report changes of Rx signal\r\n"
    "clearlisten: No longer report any Rx signal change\r\n"
    "set [ID] signal value: Specify new value of Tx signal for transmission\r\n"
    "tx [ID] {byte}: Send an arbitrary message with up to eight \"byte\" with queued"
    " sending\r\n"
    "PWM n f [dc]: PWM output. n: 1 means PA1 at J3, pin 1; 2/4/5 means USR_LED2/4/5 at"
    " PA0/4/7\r\n"
    "time: Print current time\r\n"
    "time hour min [sec]: Set current time\r\n";

    fputs(help, stdout);

} /* End of help */



/**
 * The initialization task of process bsw_pidUser, the QM aaplication code process. The task is
 * called at a time when no parallel thread execution is done yet, so no race conditions
 * exist with other parts of the code and safe build-up of all required data structure can
 * be done prior to the start of the real task scheduling.\n
 *   The initialization function of QM process bsw_pidUser is invoked prior to the
 * according initialization function of the safety process.\n
 *   We use this function to initialize the CAN interface.
 *   @return
 * The function may return a negative value to indicate a severe problem. The system won't
 * start up in this case. Normally, we will return zero.
 *   @param PID
 * The process ID of the initialized process, always bsw_pidUser in our case.
 */
int32_t bsw_taskUserInit(uint32_t PID ATTRIB_DBG_ONLY)
{
    assert(PID == bsw_pidUser);

    bool success = true;
    
    /* Print initial hello. */
    greeting();
    
    /* Run the initialization of the CAN stack. */
    if(!can_initCanStack())
        success = false;

    return success? 0: -1;

} /* End of bsw_taskUserInit */




/**
 * Demo code of the regularly executed 1ms task of the APSW.
 *   @return
 * Normally, the function will return zero. However, it may return a negative value to
 * indicate a severe problem. The system would count a process error and a safety
 * supervisor task could take an action.
 *   @param PID
 * The process ID of the process, the task belongs to; always bsw_pidUser in our case.
 *   @param taskParam
 * A task receives an argument. It is always zero in our case.
 */
int32_t bsw_taskUser1ms(uint32_t PID ATTRIB_DBG_ONLY, uint32_t taskParam ATTRIB_UNUSED)
{
    assert(PID == bsw_pidUser);

    ++ _cntTask1ms;
    
    /* Call the 1ms step function of the APSW. */
    //asw_taskApsw_1ms();

    return 0;

} /* End of bsw_taskUser1ms */




/**
 * Demo code of the regularly executed 10ms task of the APSW. The engine of the CAN
 * interface is clocked and the decoded and pre-processed CAN information can be consumed
 * by the APSW. Vice versa, the APSW provided functional results are encoded and timely
 * sent by the engine. All data access can be done easy and directly since no race
 * conditions occur.
 *   @return
 * Normally, the function will return zero. However, it may return a negative value to
 * indicate a severe problem. The system would count a process error and a safety
 * supervisor task could take an action.
 *   @param PID
 * The process ID of the process, the task belongs to; always bsw_pidUser in our case.
 *   @param taskParam
 * A task receives an argument. It is always zero in our case.
 */
int32_t bsw_taskUser10ms(uint32_t PID ATTRIB_DBG_ONLY, uint32_t taskParam ATTRIB_UNUSED)
{
    assert(PID == bsw_pidUser);

    ++ _cntTask10ms;
    
    /* Call the step function of the CAN interface engine for this task. */
    assert(can_hDispatcherSystem != EDE_INVALID_DISPATCHER_SYSTEM_HANDLE);
    ede_dispatcherMain(can_hDispatcherSystem, CAN_IDX_DISPATCHER_10MS);

    /* Look for possible user input through serial interface. */
    static unsigned int DATA_P1(cntIdleLoops_) = 2800;
    char inputMsg[80+1];
    if(sio_getLine(inputMsg, sizeOfAry(inputMsg)) != NULL)
    {
        const char *argV[11];
        unsigned int argC = sizeOfAry(argV);
        tokenizeCmdLine(&argC, argV, inputMsg);
        bool didNotUnderstand = false;
        if(argC >= 1)
        {
            /* Try interpret the input as supported CAN command. */
            if(cmd_parseCanCommand(argC, argV))
            {
                /* The parse function has taken all required actions, nothing to do here. */
            }
            else if(strcmp(argV[0], "show") == 0  &&  argC >= 2)
            {
                if(strcmp(argV[1], "c") == 0)
                    showC();
                else if(strcmp(argV[1], "w") == 0)
                    showW();
                else if(strcmp(argV[1], "PWM") == 0)
                    _enableDisplayPWM = argC == 2u  || strcmp(argV[2], "off") != 0u;
            }
            else if(strcmp(argV[0], "help") == 0)
                help();
            else if(strcmp(argV[0], "version") == 0)
                version();
            else if(strcmp(argV[0], "time") == 0)
            {
                static unsigned int DATA_P1(_offsetInS) = 0;
                if(argC >= 3)
                {
                    signed int i = atoi(argV[1]);
                    if(i < 0)
                        i = 0;
                    else if(i >= 24)
                        i = 23;
                    _offsetInS = (unsigned)i * 3600u;
                    
                    i = atoi(argV[2]);
                    if(i < 0)
                        i = 0;
                    else if(i >= 60)
                        i = 59;
                    _offsetInS += (unsigned)i * 60u;
                    
                    /* Designation of seconds is an option only. */
                    if(argC >= 4)
                    {
                        i = atoi(argV[3]);
                        if(i < 0)
                            i = 0;
                        else if(i >= 60)
                            i = 59;
                        _offsetInS += (unsigned)i;
                    }
                    assert(_offsetInS < 86400);
                    
                    /* Consider current system, which we don't want to reset. */
                    _offsetInS -= _cntTask1ms / 1000;
                }
                
                /* Print current time. */
                const unsigned int noMillis = _cntTask1ms;
                unsigned int noSec = noMillis / 1000 + _offsetInS;

                /* Avoid expensive modulo. */
                if(noSec >= 86400)
                {
                    noSec -= 86400;
                    _offsetInS -= 86400;
                }
                assert(noSec < 86400);

                unsigned int h, m, s;
                h = noSec / 3600;
                m = s = noSec - h*3600;
                m /= 60;
                s -= m*60;

                iprintf( "Current time is %02u:%02u:%02u\r\n"
                       , h, m, s
                       );
            }
            else if(strcmp(argV[0], "PWM") == 0)
            {
                if(argC == 3  ||  argC == 4)
                {
                    const signed int chnN = atoi(argV[1]);
                    pwm_pwmOutChannel_t chn;
                    switch(chnN)
                    {
                        case 1:  chn = pwm_pwmOChn_PA1_J3_pin1; break;
                        case 2:  chn = pwm_pwmOChn_LED_2_DS10;  break;
                        case 4:  chn = pwm_pwmOChn_LED_4_DS11;  break;
                        case 5:  chn = pwm_pwmOChn_LED_5_DS5;   break;
                        default: chn = pwm_pwmOChn_noPwmOutputs;
                    }
                    if(chn != pwm_pwmOChn_noPwmOutputs)
                    {
                        float f = atoff(argV[2]);
                        float dc = 50.0f;
                        if(argC == 4)
                            dc = atoff(argV[3]);
                        pwm_setChnFrequencyAndDutyCycle(chn, f, dc/100.0f);
                    }
                    else
                        iprintf("Invalid PWM channel chosen. Type `help'\r\n");
                }
                else
                    iprintf("Bad number of arguments for command PWM. Type `help'\r\n");
            }
            else
            {
                didNotUnderstand = true;

            } /* End if/else if(Command) */

            /* Reset the timer for output of help if user has entered something. */
            cntIdleLoops_ = 0;
        }
        else
        {
            didNotUnderstand = true;
            
        } /* End if(User input contains possible command) */
        
        if(didNotUnderstand)
        {
            /* Echo bad user input, which could not be consumed. */
            fputs("I couldn't understand you. You typed:", stdout);
            fflush(stdout);

            unsigned int u;
            for(u=0; u<argC; ++u)
            {
                fputs(" ", stdout);
                fputs(argV[u], stdout);
            }
            fputs("\r\nTry `help'\r\n", stdout);
        }
    }
    else
    {
        /* Offer help after 30s of no input. */
        if(++cntIdleLoops_ >= 3000)
        {
            fputs("Type `help' to get software usage information\r\n", stdout);
            cntIdleLoops_ = 0;
        }

    } /* if(Got user input?) */

    return 0;

} /* End of bsw_taskUser10ms */




/**
 * Demo code of the regularly executed 100ms task of the APSW.
 *   @return
 * Normally, the function will return zero. However, it may return a negative value to
 * indicate a severe problem. The system would count a process error and a safety
 * supervisor task could take an action.
 *   @param PID
 * The process ID of the process, the task belongs to; always bsw_pidUser in our case.
 *   @param taskParam
 * A task receives an argument. It is always zero in our case.
 */
int32_t bsw_taskUser100ms(uint32_t PID ATTRIB_DBG_ONLY, uint32_t taskParam ATTRIB_UNUSED)
{
    assert(PID == bsw_pidUser);

    /* Call the 100ms step functions of the APSW. */
    c2p_mainFunction100ms();

#if 1
    static unsigned int SBSS_P1(cntTx_) = 0u;
    static unsigned int SDATA_P1(canId_) = 0x800u;
    uint8_t payload[8] = { cntTx_ & 0xFF00u, cntTx_ & 0x00FFu
                         , 0x22, 0x33 , 0x44, 0x55, 0x66, 0x77
                         };
    for(unsigned int u=0; u<16u; ++u)
    {
        const cdr_errorAPI_t errCode = cdr_sendMessageQueued
                                                        ( BSW_CAN_BUS_0
                                                        , /* isExtId */ true
                                                        , canId_
                                                        , /* DLC */ (canId_ & 7u) + 1u
                                                        , payload
                                                        );
        if(errCode == cdr_errApi_noError)
        {
//            iprintf("apt: Message %u, ID=0x%X successfully submitted for sending\r\n", cntTx_, canId_);
            canId_ = (canId_ + 1u) & 0x080Fu;
            ++ cntTx_;
            payload[0] = cntTx_ & 0xFF00u;
            payload[1] = cntTx_ & 0x00FFu;
        }
        else    
        {
            if(errCode == cdr_errApi_txMailboxBusy)
            {
                iprintf( "apt: Can't send message %u, ID=0x%X, mailbox still busy\r\n"
                       , cntTx_
                       , canId_
                       );
            }
            else
            {
                iprintf( "apt: Can't send message %u, ID=0x%X, error %i\r\n"
                       , cntTx_
                       , canId_
                       , (int)errCode
                       );
            }
            break;
        }
    }
#endif

    return 0;

} /* End of bsw_taskUser100ms */




/**
 * Demo code of the regularly executed 1s task of the APSW.
 *   @return
 * Normally, the function will return zero. However, it may return a negative value to
 * indicate a severe problem. The system would count a process error and a safety
 * supervisor task could take an action.
 *   @param PID
 * The process ID of the process, the task belongs to; always bsw_pidUser in our case.
 *   @param taskParam
 * A task receives an argument. It is always zero in our case.
 */
int32_t bsw_taskUser1000ms(uint32_t PID ATTRIB_DBG_ONLY, uint32_t taskParam ATTRIB_UNUSED)
{
    assert(PID == bsw_pidUser);

    /* Call the 1s step function of the APSW. */
    //asw_taskApsw_1000ms();
    static bool SDATA_P1(isOn_) = false;
    lbd_setLED(lbd_led_7_DS4, isOn_=!isOn_);

    /* Some test code of the uniform floating point signal API shaped for this sample. */
    
//    /* CAN ID 1024, Rx signal "speedOfRotation": Print current value. */
//    const cdt_canSignal_t *pSpeedOfRotation = &cdt_canSignalAry[1];
//    assert(pSpeedOfRotation->isReceived
//           &&  pSpeedOfRotation->idxMsg < sizeOfAry(cdt_canRxMsgAry)
//          );
//    printf( "Message %d, signal %s: %f %s\r\n"
//          , cdt_canRxMsgAry[pSpeedOfRotation->idxMsg].canId
//          , pSpeedOfRotation->name
//          , f2d(pSpeedOfRotation->getter())
//          , pSpeedOfRotation->unit
//          );
//
//    /* CAN ID 1536, Tx signal "power": Change value visibly. */
//    const cdt_canSignal_t *pPower = &cdt_canSignalAry[14];
//    assert(!pPower->isReceived
//           &&  pPower->idxMsg < sizeOfAry(cdt_canTxMsgAry)
//          );
//    const float range = pPower->max - pPower->min
//              , delta = range/15.0f;
//    float newValue;
//    newValue = pPower->getter() + delta;
//    if(newValue > pPower->max)
//        newValue -= range;
//    assert(newValue >= pPower->min  &&  newValue <= pPower->max);
//    pPower->setter(newValue);

    if(_enableDisplayPWM)
    {
        bool isNewResultPA2;
        const float tiPeriod = pwm_getChnInputPeriodTime( &isNewResultPA2
                                                        , pwm_pwmIChn_PA2_J3_pin3_periodTime
                                                        )
                  , f = 1.0f / tiPeriod;

        bool isNewResultPA6;
        const float tiDuty = pwm_getChnInputDutyTime( &isNewResultPA6
                                                    , pwm_pwmIChn_PA6_J2_pin1_dutyTime
                                                    )
                  , dutyCycle = tiDuty * f;

        printf( "PWM at input PA2/PA6: %.3f Hz/%.3f ms (%s/%s result), DC: %.1f%%\r\n"
              , f2d(f)
              , f2d(1000.0f*tiDuty)
              , isNewResultPA2? "new": "old"
              , isNewResultPA6? "new": "old"
              , f2d(dutyCycle <= 1.0f? 100.0f*dutyCycle: -1.0f)
              );
    }
    
    return 0;

} /* End of bsw_taskUser1000ms */




