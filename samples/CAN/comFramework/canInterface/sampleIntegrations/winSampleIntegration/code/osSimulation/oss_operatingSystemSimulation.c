/**
 * @file oss_operatingSystemSimulation.c
 * Simulation of those parts of an operating system, which are required in the context of
 * the CAN interface. The simulation is most simple; it's single-threaded and won't
 * show any real-time effects of a preemptive task based system. However, it's
 * sufficient to connect to all API functions and to run through all the code and to
 * demonstrate the way the CAN interface works and how it has to be integrated in a real
 * system.
 *
 * Copyright (C) 2015-2022 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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
 *   oss_kernel
 *   oss_installTask
 *   oss_installIrqHandlerCanRx
 *   oss_installIrqHandlerCanBusOff
 *   oss_registerFrameForReception
 *   oss_registerFrameForSending
 *   oss_restartCanBus
 *   oss_sendCanFrame
 * Local functions
 *   logCanFrame
 *   clockMsgSpeed
 *   clockMsgTorque
 *   clockMsgUserLimits
 *   task100us
 */

/*
 * Include files
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <assert.h>

#include "smalloc.h"
#include "log_logger.h"
#include "opt_getOpt.h"
#include "fil_file.h"
#include "main.h"
#include "oss_operatingSystemSimulation.h"


/*
 * Defines
 */

/** Global switch to enable error simulation for all frames. Set it to either 1 or 0. */
#define DO_ERROR_SIMULATION         1

/** Global switch to enable error simulation for frame 1024. Set it to either 1 or 0. */
#define DO_ERROR_SIMULATION_1024    1

/** Global switch to enable error simulation for frame 1040. Set it to either 1 or 0. */
#define DO_ERROR_SIMULATION_1040    1

/** Global switch to enable error simulation for frame 2032. Set it to either 1 or 0. */
#define DO_ERROR_SIMULATION_2032    0

/** The probability of a bus-off error. Only change the number literal in the definition! */
#define P_BUS_OFF                   (1e-5 * (DO_ERROR_SIMULATION))

/** The probability of a bus recovery attempt to succeed. Only change the first definition! */
#if DO_ERROR_SIMULATION == 1
# define P_BUS_RECOVERY             (0.95)
#else
# define P_BUS_RECOVERY             (1.0)
#endif

/** The probability of simulating a timeout for frame 1024. Only change the number literal
    in the definition! */
#define P_TIMEOUT_1024              (0.01 * (DO_ERROR_SIMULATION)*(DO_ERROR_SIMULATION_1024))

/** The probability of simulating a DLC error for frame 1024. Only change the number
    literal in the definition! */
#define P_DLC_ERR_1024              (0.01 * (DO_ERROR_SIMULATION)*(DO_ERROR_SIMULATION_1024))

/** The probability of simulating a checksum error for frame 1024. Only change the number
    literal in the definition! */
#define P_CHKSUM_ERR_1024           (0.01 * (DO_ERROR_SIMULATION)*(DO_ERROR_SIMULATION_1024))

/** The probability of simulating a sequence counter error for frame 1024. Only change the
    number literal in the definition! */
#define P_SQC_ERR_1024              (0.01 * (DO_ERROR_SIMULATION)*(DO_ERROR_SIMULATION_1024))

/** The probability of simulating a timeout for frame 1040. Only change the number literal
    in the definition! */
#define P_TIMEOUT_1040              (0.01 * (DO_ERROR_SIMULATION)*(DO_ERROR_SIMULATION_1040))

/** The probability of simulating a DLC error for frame 1040. Only change the number
    literal in the definition! */
#define P_DLC_ERR_1040              (0.01 * (DO_ERROR_SIMULATION)*(DO_ERROR_SIMULATION_1040))

/** The probability of simulating a checksum error for frame 1040. Only change the number
    literal in the definition! */
#define P_CHKSUM_ERR_1040           (0.01 * (DO_ERROR_SIMULATION)*(DO_ERROR_SIMULATION_1040))

/** The probability of simulating a sequence counter error for frame 1040. Only change the
    number literal in the definition! */
#define P_SQC_ERR_1040              (0.01 * (DO_ERROR_SIMULATION)*(DO_ERROR_SIMULATION_1040))

/** The probability of simulating a DLC error for frame 2032. Only change the number
    literal in the definition! */
#define P_DLC_ERR_2032              (0.1 * (DO_ERROR_SIMULATION)*(DO_ERROR_SIMULATION_2032))

/** The probability of simulating a checksum error for frame 2032. Only change the number
    literal in the definition! */
#define P_CHKSUM_ERR_2032           (0.1 * (DO_ERROR_SIMULATION)*(DO_ERROR_SIMULATION_2032))

/** The probability of simulating a sequence counter error for frame 2032. Only change the
    number literal in the definition! */
#define P_SQC_ERR_2032              (0.1 * (DO_ERROR_SIMULATION)*(DO_ERROR_SIMULATION_2032))



/** A scaled floating point random number in the range [a, b). */
#define RAND(a,b) ((double)((b)-(a))*RND()+(double)(a))

/** A Boolean random number with given probability p of getting a true. */
#define BOOL_RAND(p) (RND()<(p)? true: false)

/** A floating point random number in the range [0;1). */
#define RND() ((double)rand()/(double)RAND_MAX)


/*
 * Local type definitions
 */


/*
 * Local prototypes
 */


/*
 * Data definitions
 */

/** The time unit of the simulated OS kernel in micro seconds. */
unsigned int oss_tiTick = 1;

/** The simulation time in us. */
unsigned long long oss_tiSim = 0;

/** The CAN reception IRQ handler. */
static oss_irqHandlerCanRx_t _irqHandlerCanRx = NULL;

/** The CAN bus state change IRQ handler. */
static oss_irqHandlerCanBusOff_t _irqHandlerCanBusOff = NULL;

/** Array of task function pointers or NULL if task is not installed. */
static oss_task_t _taskAry[oss_noTaskTypes] = {[oss_noTaskTypes-1] = NULL};

/** The type of the unique handle of a processed CAN frame. */
static oss_handleCanFrame_t _nextHandleCanFrame = 0;

/* The handles of the received CAN frames, which are known to the system and supported by
   this simulation. */
static oss_handleCanFrame_t _hFrame1024 = OSS_INVALID_CAN_FRAME_HANDLE
                          , _hFrame1040 = OSS_INVALID_CAN_FRAME_HANDLE
                          , _hFrame2032 = OSS_INVALID_CAN_FRAME_HANDLE;

/** The CAN log file. */
static FILE *_logCanData = NULL;

/** The status of the only simulated CAN bus: Normally active but can have a bus-off. */
static bool _isBusOff = false;


/*
 * Function implementation
 */


/**
 * Log a transmitted CAN frame.
 *   @param isReceived
 * The transmission direction.
 *   @param osHandleFrame
 * The operating system handle of the frame as got from \a oss_registerFrameForSending.
 *   @param pData
 * The frame contents, already byte encoded.
 *   @param DLC
 * The number of bytes to send out.
 */

static void logCanFrame( bool isReceived
                       , oss_handleCanFrame_t osHandleFrame
                       , const uint8_t *pData
                       , unsigned int DLC
                       )
{
    if(_logCanData == NULL)
        _logCanData = fopen(MAIN_APP_NAME ".CAN.log", "wt");
    if(_logCanData != NULL)
    {
        fprintf( _logCanData
               , "%10.1f ms - %cx - ID %4u - DLC %u -"
               , (double)oss_tiSim/1000.0
               , isReceived? 'R': 'T'
               , (unsigned)osHandleFrame
               , DLC
               );
        unsigned int idxByte;
        for(idxByte=0; idxByte<DLC; ++idxByte)
            fprintf(_logCanData, " %02X", (unsigned)pData[idxByte]);
        fprintf(_logCanData, "\n");
    }
    /* For simplicity: File is closed by end of application run. */

} /* End of logCanFrame. */



/**
 * Tick the function, which controls the simulation of the generation of the inbound CAN
 * message that mainly contains the speed of rotation of the engine.\n
 *   The function controlls the update timing and the data content generation.
 *   @return
 * \a true, if new data reception is simulated, \a false otherwise.
 *   @param msg
 * The caller provided buffer for up to eight message contents bytes.
 *   @param pDLC
 * The function returns the actual number of written bytes as * \a pDLC.
 */

static bool clockMsgSpeed(unsigned char msg[8], unsigned int *pDLC)
{
#define TI_MSG_US           10000   /* us */
#define REL_DRIFT           1e-4
#define REL_JITTER          0.05
#define SOR_MIN             800.0   /* rpm */
#define SOR_MAX             4500.0  /* rpm */
#define SOR_SLOPE           100.0   /* rpm/s */
#define CHKSUM_START_VAL    17

    static unsigned long long tiReceive_ = TI_MSG_US
                            , tiLastReceive_ = 0;
    static double speedOfRotationSlope_ = SOR_SLOPE
                , speedOfRotation_ = SOR_MIN;
    static unsigned int SQC_ = 0;
    if(oss_tiSim > tiReceive_)
    {
        /* New reception event, produce new data. */
        speedOfRotation_ += (double)(oss_tiSim - tiLastReceive_) *1e-6 *speedOfRotationSlope_;
        if(speedOfRotation_ > SOR_MAX)
        {
            speedOfRotation_ = 2*SOR_MAX - speedOfRotation_;
            speedOfRotationSlope_ = -SOR_SLOPE;
        }
        else if(speedOfRotation_ < SOR_MIN)
        {
            speedOfRotation_ = 2*SOR_MIN - speedOfRotation_;
            speedOfRotationSlope_ = SOR_SLOPE;
        }

        /* Compute new reception time. Consider drift, jitter and ... */
        tiLastReceive_ = tiReceive_;
        tiReceive_ += (unsigned long long)(RAND(1-REL_JITTER,1+REL_JITTER)
                                           *(TI_MSG_US*(1+REL_DRIFT))
                                          );

        /* In state bus-off we are not going to send a frame and the next steps are skipped
           in order to avoid confusing console messages about an anyway suppressed frame. */
        if(_isBusOff)
        {
            *pDLC = 0;
            return false;
        }

        /* ... and consider a timeout. */
        if(BOOL_RAND(P_TIMEOUT_1024))
        {
            double tiTimeout = RAND(2,10)*TI_MSG_US;
            LOG_DEBUG( main_hGlobalLogger
                     , "%.1f ms: "
                       "oss::clockMsgSpeed: "
                       "Simulate a timeout of message speed. The next message will be"
                       " delayed by additional %.1 f ms"
                     , oss_tiSim / 1000.0
                     , tiTimeout / 1000.0
                     );
            tiReceive_ += (unsigned long long)tiTimeout;
        }

        /* Pack new data into the message. The affected message bytes are written entirely,
           therefore this must be the first store statement. */
        unsigned long sorBin = ((unsigned long)((speedOfRotation_ - 0.0) / 0.1 + 0.5) << 4)
                               & 0x000ffff0ul;
        msg[1] = sorBin >> 16;
        msg[2] = (sorBin >> 8) & 0xff;
        msg[3] = sorBin & 0xf0;

        /* Update and store sequence counter. */
        if(BOOL_RAND(P_SQC_ERR_1024))
        {
            LOG_DEBUG( main_hGlobalLogger
                     , "%.1f ms: "
                       "oss::clockMsgSpeed: "
                       "Simulate a sequence error for message speed"
                     , oss_tiSim / 1000.0
                     );
            ++ SQC_;
        }
        assert((msg[1] & 0xf0) == 0);
        msg[1] |= (SQC_ & 0x0f) << 4;
        if(SQC_ >= 14)
            SQC_ = 0;
        else
            ++ SQC_;

        /* Compute and add the checksum. */
        msg[0] = ~(CHKSUM_START_VAL + msg[1] + msg[2] + msg[3]);
        if(BOOL_RAND(P_CHKSUM_ERR_1024))
        {
            LOG_DEBUG( main_hGlobalLogger
                     , "%.1f ms: "
                       "oss::clockMsgSpeed: "
                       "Simulate a checksum error for message speed"
                     , oss_tiSim / 1000.0
                     );
            ++ msg[0];
        }

        /* Return the DLC with a possible, simulated error. */
        *pDLC = 4;
        if(BOOL_RAND(P_DLC_ERR_1024))
        {
            LOG_DEBUG( main_hGlobalLogger
                     , "%.1f ms: "
                       "oss::clockMsgSpeed: "
                       "Simulate a DLC error for message speed"
                     , oss_tiSim / 1000.0
                     );
            -- *pDLC;
        }

        return true;
    }
    else
    {
        *pDLC = 0;
        return false;
    }

#undef TI_MSG_US
#undef REL_DRIFT
#undef REL_JITTER
#undef SOR_MIN
#undef SOR_MAX
#undef SOR_SLOPE
#undef CHKSUM_START_VAL
} /* End of clockMsgSpeed */




/**
 * Tick the function, which controls the simulation of the generation of the inbound CAN
 * message that mainly contains the current torque of the engine.\n
 *   The function controlls the update timing and the data content generation. Failure
 * injection is supported by fixed rates of random errors.
 *   @return
 * \a true, if new data reception is simulated, \a false otherwise.
 *   @param msg
 * The caller provided buffer for up to eight message contents bytes.
 *   @param pDLC
 * The function returns the actual number of written bytes as * \a pDLC.
 */

static bool clockMsgTorque(unsigned char msg[8], unsigned int *pDLC)
{
#define TI_MSG_US           25000   /* us */
#define REL_DRIFT           (-1e-4)
#define REL_JITTER          0.05
#define TRQ_MIN             -10.0   /* Nm */
#define TRQ_MAX             450.0   /* Nm */
#define TRQ_SLOPE           230.0   /* Nm/s */
#define CHKSUM_START_VAL    218

    static unsigned long long tiReceive_ = TI_MSG_US
                            , tiLastReceive_ = 0;
    static double torqueSlope_ = TRQ_SLOPE
                , torque_ = TRQ_MIN;
    static unsigned int SQC_ = 15;
    if(oss_tiSim > tiReceive_)
    {
        /* New reception event, produce new data. */
        torque_ += (double)(oss_tiSim - tiLastReceive_) * 1e-6 * torqueSlope_;
        if(torque_ > TRQ_MAX)
        {
            torque_ = 2*TRQ_MAX - torque_;
            torqueSlope_ = -TRQ_SLOPE;
        }
        else if(torque_ < TRQ_MIN)
        {
            torque_ = 2*TRQ_MIN - torque_;
            torqueSlope_ = TRQ_SLOPE;
        }

        /* Compute new reception time. Consider drift, jitter and ... */
        tiLastReceive_ = tiReceive_;
        tiReceive_ += (unsigned long long)(RAND(1-REL_JITTER,1+REL_JITTER)
                                           *(TI_MSG_US*(1+REL_DRIFT))
                                          );

        /* In state bus-off we are not going to send a frame and the next steps are skipped
           in order to avoid confusing console messages about an anyway suppressed frame. */
        if(_isBusOff)
        {
            *pDLC = 0;
            return false;
        }

        /* ... and consider a timeout. */
        if(BOOL_RAND(P_TIMEOUT_1040))
        {
            double tiTimeout = RAND(2,10)*TI_MSG_US;
            LOG_DEBUG( main_hGlobalLogger
                     , "%.1f ms: "
                       "oss::clockMsgTorque: "
                       "Simulate a timeout of message torque. The next message will be"
                       " delayed by additional %.1 f ms"
                     , oss_tiSim / 1000.0
                     , tiTimeout / 1000.0
                     );
            tiReceive_ += (unsigned long long)tiTimeout;
        }

        /* Pack new data into the message. All bits of the affected two message bytes are
           written, therefore this must be the first store statement. */
        signed short tqBin = (signed short)((torque_ - 0.0) / 0.5 + 0.5);
        unsigned short tqBinShftMask = ((unsigned short)tqBin << 4) & 0x7ff0;
        msg[2] = tqBinShftMask >> 8;
        msg[3] = tqBinShftMask & 0xff;

        /* Update and store sequence counter. */
        if(BOOL_RAND(P_SQC_ERR_1040))
        {
            LOG_DEBUG( main_hGlobalLogger
                     , "%.1f ms: "
                       "oss::clockMsgTorque: "
                       "Simulate a sequence error for message torque"
                     , oss_tiSim / 1000.0
                     );
            ++ SQC_;
        }
        msg[1] = SQC_ & 0x0f;
        if(SQC_ >= 2)
            -- SQC_;
        else
            SQC_ = 15;

        /* Compute and add the checksum. */
        msg[0] = ~(CHKSUM_START_VAL + msg[1] + msg[2] + msg[3]);
        if(BOOL_RAND(P_CHKSUM_ERR_1040))
        {
            LOG_DEBUG( main_hGlobalLogger
                     , "%.1f ms: "
                       "oss::clockMsgTorque: "
                       "Simulate a checksum error for message torque"
                     , oss_tiSim / 1000.0
                     );
            ++ msg[0];
        }

        /* Return the DLC with a possible, simulated error. */
        *pDLC = 4;
        if(BOOL_RAND(P_DLC_ERR_1040))
        {
            LOG_DEBUG( main_hGlobalLogger
                     , "%.1f ms: "
                       "oss::clockMsgTorque: "
                       "Simulate a DLC error for message torque\n"
                     , oss_tiSim / 1000.0
                     );
            -- *pDLC;
        }

        return true;
    }
    else
    {
        *pDLC = 0;
        return false;
    }

#undef TI_MSG_US
#undef REL_DRIFT
#undef REL_JITTER
#undef TRQ_MIN
#undef TRQ_MAX
#undef TRQ_SLOPE
#undef CHKSUM_START_VAL
} /* End of clockMsgTorque */



/**
 * Tick the function, which controls the simulation of the generation of the inbound CAN
 * message that contains new user set limits for the supervision of speed of rotation and
 * engine torque.\n
 *   The function controlls the update timing and the data content generation. Failure
 * injection is supported by fixed rates of random errors. This message is a purely
 * data-change triggered one, which a timeout must never be generated for.
 *   @return
 * \a true, if new data reception is simulated, \a false otherwise.
 *   @param msg
 * The caller provided buffer for up to eight message contents bytes.
 *   @param pDLC
 * The function returns the actual number of written bytes as * \a pDLC.
 */

static bool clockMsgUserLimits(unsigned char msg[8], unsigned int *pDLC)
{
#define TI_MEAN_MSG_US      5200000   /* us */
#define TI_MIN_MSG_US       1000000   /* us */
#define CHKSUM_START_VAL    119

    static unsigned long long tiReceive_ = 175000; /* us, first reception */
    static unsigned int SQC_ = 1;
    if(oss_tiSim > tiReceive_)
    {
        /* New reception event, produce new data. Extract from the network database:
             SG_ minSpeedOfRotation : 6|12@1+ (1.6,0) [0|6500] "rpm"
             SG_ maxSpeedOfRotation : 18|12@1+ (1.6,0) [0|6500] "rpm"
             SG_ minPower : 47|9@0+ (0.5,-10) [-10|240] "KW"
             SG_ maxPower : 53|9@0+ (0.5,-10) [-10|240] "KW"
             Our data change is most simple: We toggle all variables bewteen two values. */
        static unsigned int minSpeedOfRotation = 800 /* rpm */
                                                 * 10 / 16
                          , maxSpeedOfRotation = 5000 /* rpm */
                                                 * 10 / 16
                          , minPower = ( -1 /* KW */
                                         - (-10)
                                       ) * 2
                          , maxPower = ( 70 /* KW */
                                         - (-10)
                                       ) * 2
                          , deltaSOR = 100 /* rpm */ * 10 / 16
                          , deltaPwr = 12 /* KW */ * 2;
        minSpeedOfRotation -= deltaSOR;
        maxSpeedOfRotation += deltaSOR;
        minPower += deltaPwr;
        maxPower += deltaPwr;
        deltaSOR = -deltaSOR;
        deltaPwr = -deltaPwr;

        /* Compute new reception time. This is a pure (rare) random value for the purely
           data change triggered message. */
        tiReceive_ += (unsigned long long)RAND( TI_MIN_MSG_US
                                              , 2*TI_MEAN_MSG_US - TI_MIN_MSG_US
                                              );

        /* In state bus-off we are not going to send a frame and the next steps are skipped
           in order to avoid confusing console messages about an anyway suppressed frame. */
        if(_isBusOff)
        {
            *pDLC = 0;
            return false;
        }

        /* Pack new data into the message. */
        memset(msg, /* value */ 0, /* count */ 8);
        
        uint32_t tmp32 = minSpeedOfRotation << 6;
        msg[0] |= tmp32 & 0xC0;
        tmp32 >>= 8;
        msg[1] = tmp32;
        tmp32 >>= 8;
        msg[2] |= tmp32;
        
        uint16_t tmp16 = maxSpeedOfRotation << 2;
        msg[2] |= tmp16 & 0xFC;
        tmp16 >>= 8;
        msg[3] |= tmp16;
        
        tmp16 = minPower << 7;
        msg[6] |= tmp16 & 0x80;
        tmp16 >>= 8;
        msg[5] |= tmp16;
        
        tmp16 = maxPower << 5;
        msg[7] |= tmp16 & 0xE0;
        tmp16 >>= 8;
        msg[6] |= tmp16;
        
        /* Update and store sequence counter. */
        if(BOOL_RAND(P_SQC_ERR_2032))
        {
            LOG_DEBUG( main_hGlobalLogger
                     , "%.1f ms: "
                       "oss::clockMsgLimits: "
                       "Simulate a sequence error for message user limits"
                     , oss_tiSim / 1000.0
                     );
            ++ SQC_;
        }
        msg[0] |= (SQC_ & 0x0f) << 2;
        if(SQC_ < 14)
            ++ SQC_;
        else
            SQC_ = 1;

        /* Compute and add the checksum. */
        msg[4] = ~(CHKSUM_START_VAL
                   + msg[0] + msg[1] + msg[2] + msg[3] + msg[5] + msg[6] + msg[7]
                  );
        if(BOOL_RAND(P_CHKSUM_ERR_2032))
        {
            LOG_DEBUG( main_hGlobalLogger
                     , "%.1f ms: "
                       "oss::clockMsgLimits: "
                       "Simulate a checksum error for message user limits"
                     , oss_tiSim / 1000.0
                     );
            /* We inject a data error in signal minSpeedOfRotation, which should be
               recognized as checksum error. */
            ++ msg[1];
        }

        /* Return the DLC with a possible, simulated error. */
        *pDLC = 8;
        if(BOOL_RAND(P_DLC_ERR_2032))
        {
            LOG_DEBUG( main_hGlobalLogger
                     , "%.1f ms: "
                       "oss::clockMsgLimits: "
                       "Simulate a DLC error for message user limits\n"
                     , oss_tiSim / 1000.0
                     );
            -- *pDLC;
        }

        return true;
    }
    else
    {
        *pDLC = 0;
        return false;
    }

#undef TI_MEAN_MSG_US
#undef TI_MIN_MSG_US
#undef CHKSUM_START_VAL
} /* End of clockMsgUserLimits */



/**
 * Simulation of the 100 us task. This task is much faster than the true application tasks
 * and can be used to simulate the CAN receive interrupt's behavior of appearing at any
 * time. The simulation considers this by some pseudo-random timing.
 */

static void task100us()
{
    /* The simulation knows 3 CAN messages: A regular message at 10 ms, a regular message at
       25 ms rate and a data change triggered message. The regular messages are simulated
       with a time-jitter and a frequency-offset and the data change message has a random
       behavior plus regular 5s fallback repetition.
         All messages have a random controlled timeout failure. */
    unsigned char msg[8];
    unsigned int DLC = 0;
    if(clockMsgSpeed(msg, &DLC))
    {
        /* A reception event is simulated. Invoke the CAN reception callback, which would
           be the CAN interrupt in a true system. The integration code has installed its
           own handler code. Here we just see the function pointer. */
        if(_irqHandlerCanRx != NULL)
        {
            logCanFrame(/* isReceived */ true, _hFrame1024, msg, DLC);
            _irqHandlerCanRx(_hFrame1024, msg, DLC);
        }
        else
        {
            /* The application is useless otherwise, assertion as warning. */
            assert(false);
        }
    }
    if(clockMsgTorque(msg, &DLC))
    {
        /* A reception event is simulated. Invoke the CAN reception callback, which would
           be the CAN interrupt in a true system. The integration code has installed its
           own handler code. Here we just see the function pointer. */
        if(_irqHandlerCanRx != NULL)
        {
            logCanFrame(/* isReceived */ true, _hFrame1040, msg, DLC);
            _irqHandlerCanRx(_hFrame1040, msg, DLC);
        }
    }
    if(clockMsgUserLimits(msg, &DLC))
    {
        /* A reception event is simulated. Invoke the CAN reception callback, which would
           be the CAN interrupt in a true system. The integration code has installed its
           own handler code. Here we just see the function pointer. */
        if(_irqHandlerCanRx != NULL)
        {
            logCanFrame(/* isReceived */ true, _hFrame2032, msg, DLC);
            _irqHandlerCanRx(_hFrame2032, msg, DLC);
        }
    }

    /* A bus-off event is simulated occasionally by a low probability. */
    if(!_isBusOff && BOOL_RAND(P_BUS_OFF))
    {
        _isBusOff = true;
        LOG_DEBUG( main_hGlobalLogger
                 , "%.1f ms: "
                   "oss::task100us: "
                   "Simulate a bus-off"
                 , oss_tiSim / 1000.0
                 );
        if(_irqHandlerCanBusOff != NULL)
            _irqHandlerCanBusOff(/* isOff */ true);
    }

    /* A spontaneous recovery is also occasionally possible. */
    if(_isBusOff && BOOL_RAND(0.2*P_BUS_OFF))
    {
        _isBusOff = false;
        LOG_DEBUG( main_hGlobalLogger
                 , "%.1f ms: "
                   "oss::task100us: "
                   "Simulate a spontaneous recovery from bus-off"
                 , oss_tiSim / 1000.0
                 );
        if(_irqHandlerCanBusOff != NULL)
            _irqHandlerCanBusOff(/* isOff */ false);
    }
} /* End of task100us */




/**
 * The simulation of the operating system kernel. Since we have a single threaded
 * simulation this is barely more than a simple loop with some function calls at regularly
 * reached multiples of the task base periods.
 *   @return
 * \a true, if function succeeded, else \a false.
 *   @param tickInUs
 * The tick time (i.e. the time reslution) of the simulated operation system kernel. Unit is
 * micro second. Must not be more than 100us, which is the internaly required fastest rate
 * of operations.
 *   @param tiSimEndInUs
 * The duration of the simualted time. Unit is micro second. Simulation always starts at
 * time null.
 */

void oss_kernel(unsigned int tickInUs, unsigned long long tiSimEndInUs)
{
    assert(tickInUs > 0  &&  tickInUs <= 100);

    LOG_INFO( main_hGlobalLogger
            , "oss_kernel: Simulate %.3f ms, which are %llu ticks"
            , tiSimEndInUs / 1000.0
            , (tiSimEndInUs / tickInUs) + 1
            );

    /// @todo Make this a user-option
    //srand((unsigned)time(0));

    if(_taskAry[oss_taskType_init] != NULL)
        _taskAry[oss_taskType_init]();

    oss_tiSim = 0;
    oss_tiTick = tickInUs;
    unsigned long long tiAlarmTask100us = 0
                     , tiAlarmTask1ms = 0
                     , tiAlarmTask10ms = 0
                     , tiAlarmTask100ms = 0
                     , tiAlarmTask1s = 0;
    while(oss_tiSim <= tiSimEndInUs)
    {
        if(oss_tiSim >= tiAlarmTask100us)
        {
            task100us();
            tiAlarmTask100us += 100;
        }

        if(_taskAry[oss_taskType_regular1ms] != NULL
           &&  oss_tiSim >= tiAlarmTask1ms
          )
        {
            _taskAry[oss_taskType_regular1ms]();
            tiAlarmTask1ms += 1000;
        }

        if(_taskAry[oss_taskType_regular10ms] != NULL
           &&  oss_tiSim >= tiAlarmTask10ms
          )
        {
            _taskAry[oss_taskType_regular10ms]();
            tiAlarmTask10ms += 10000;
        }

        if(_taskAry[oss_taskType_regular100ms] != NULL
           &&  oss_tiSim >= tiAlarmTask100ms
          )
        {
            _taskAry[oss_taskType_regular100ms]();
            tiAlarmTask100ms += 100000;
        }

        if(_taskAry[oss_taskType_regular1s] != NULL
           &&  oss_tiSim >= tiAlarmTask1s
          )
        {
            _taskAry[oss_taskType_regular1s]();
            tiAlarmTask1s += 1000000;
        }

        if(oss_tiSim == tiSimEndInUs)
        {
            if(_taskAry[oss_taskType_shutdown] != NULL)
                _taskAry[oss_taskType_shutdown]();
        }

        /* Next kernel tick. */
        oss_tiSim += tickInUs;
    }
} /* End of oss_kernel */




/**
 * Install a function as task function in the operating system.\n
 *   @return
 * The task function so far is returned; this will normally be NULL.
 *   @param kindOfTask
 * Different tasks, mostly regularly triggered ones, can be installed.
 *   @param function
 * The function, which is from now on called as a task.
 */

oss_task_t oss_installTask(oss_taskType_t type, oss_task_t function)
{
    oss_task_t oldTask = NULL;
    if((unsigned)type < oss_noTaskTypes)
    {
        oldTask = _taskAry[(unsigned)type];
        _taskAry[(unsigned)type] = function;
    }
    else
        assert(false);

    return oldTask;

} /* End of oss_installTask */




/**
 * Install the IRQ handler for CAN bus off and recovers in the operating system.\n
 *   @return
 * The IRQ handler so far is returned; this will normally be NULL.
 *   @param irqHandler
 * The handler, which is from now on called on every CAN bus state change.
 */

oss_irqHandlerCanBusOff_t oss_installIrqHandlerCanBusOff(oss_irqHandlerCanBusOff_t irqHandler)
{
    oss_irqHandlerCanBusOff_t oldHandler = _irqHandlerCanBusOff;
    _irqHandlerCanBusOff = irqHandler;
    return oldHandler;

} /* End of oss_installIrqHandlerCanBusOff */




/**
 * Install the IRQ handler for CAN reception in the operating system.\n
 *   @return
 * The IRQ handler so far is returned; this will normally be NULL.
 *   @param irqHandler
 * The handler, which is from now on called on every CAN frame reception.
 */

oss_irqHandlerCanRx_t oss_installIrqHandlerCanRx(oss_irqHandlerCanRx_t irqHandler)
{
    oss_irqHandlerCanRx_t oldHandler = _irqHandlerCanRx;
    _irqHandlerCanRx = irqHandler;
    return oldHandler;

} /* End of oss_installIrqHandlerCanRx */




/**
 * All platforms require a kind of agreement on the set of CAN frames to be received and
 * processed. This may be done by static configuration with a configurator tool, by a
 * global, statically initialized data table or by an API call. This platform simulation
 * assumes an API.
 *   @return
 * Particularly if a platform has an API to register a frame for reception then it might
 * assign a unique handle to the registered frame for later processing (e.g. the
 * on-reception-interrupt might reported the received frame by this handle rather than by
 * CAN ID). Our simulation assumes such a handle although is uses the CAN ID as handle.\n
 *   A platform may have a limitation for receiving frames (e.g. a fixed maximum number of
 * supported frames). Therefore the registration may fail. The simulation defines the
 * return value #OSS_INVALID_CAN_FRAME_HANDLE as error indication.
 *   @param osHandleBus
 * Transmission of a CAN frame is always related to a CAN bus and most platforms support
 * more than one bus. There will be a kind of bus handle to say on which bus to receive the
 * frame.
 *   @param canId
 * The frame to be received is identified by its CAN ID, which is unique in the context of
 * a given CAN bus.
 *   @param isExtId
 * \a true, if \a canId is a 29 Bit CAN ID or \a flase for a standard 11 Bit ID.
 *   @remark
 * The simulation has no effect. The set of received (i.e. simulated) frames is hard coded
 * and won't depend on the correct call of this API function. Only the function return
 * value is supported as expected: If a none supported frame is registered then the
 * function returns #OSS_INVALID_CAN_FRAME_HANDLE.
 */

oss_handleCanFrame_t oss_registerFrameForReception( oss_handleCanBus_t osHandleBus
                                                  , unsigned long canId
                                                  , bool isExtId
                                                  )
{
    assert(_nextHandleCanFrame < (oss_handleCanFrame_t)-1);
    if(osHandleBus != OSS_CAN_BUS_PT  ||  isExtId)
        return OSS_INVALID_CAN_FRAME_HANDLE;
    switch(canId)
    {
    case 1024:
        _hFrame1024 = _nextHandleCanFrame++;
        return _hFrame1024;

    case 1040:
        _hFrame1040 = _nextHandleCanFrame++;
        return _hFrame1040;

    case 2032:
        _hFrame2032 = _nextHandleCanFrame++;
        return _hFrame2032;

    default:
        return OSS_INVALID_CAN_FRAME_HANDLE;
    }
} /* End of oss_registerFrameForReception */




/**
 * A platform might require a kind of agreement on the set of sent CAN frames. This may be
 * done by static configuration with a configurator tool, by a global, statically
 * initialized data table or by an API call. This platform simulation assumes an API.
 *   @return
 * Particularly if a platform has an API to register a frame for sending then it might
 * assign a unique handle to the registered frame for later processing (e.g. the actual
 * send API or the on-send-complete-interrupt might identify the sent frame by this handle
 * rather than by CAN ID). Our simulation assumes such a handle.\n
 *   A platform may have a limitation for sending frames (e.g. a fixed maximum number of
 * supported frames). Therefore the registration may fail. The simulation defines the
 * return value #OSS_INVALID_CAN_FRAME_HANDLE as error indication.
 *   @param osHandleBus
 * Transmission of a CAN frame is always related to a CAN bus and most platforms support
 * more than one bus. There will be a kind of bus handle to say on which bus to send the
 * frame.
 *   @param canId
 * The frame to be sent is identified by its CAN ID, which is unique in the context of
 * a given CAN bus.
 *   @param isExtId
 * \a true, if \a canId is a 29 Bit CAN ID or \a flase for a standard 11 Bit ID.
 *   @remark
 * The simulation has no effect. The set of sendable frames is basically unlimited
 * and won't depend on the correct call of this API function. Only the function return
 * value is supported as expected: If a not anticipated frame is registered then the
 * function returns #OSS_INVALID_CAN_FRAME_HANDLE.
 */

oss_handleCanFrame_t oss_registerFrameForSending( oss_handleCanBus_t osHandleBus
                                                , unsigned long canId
                                                , bool isExtId
                                                )
{
    assert(_nextHandleCanFrame < (oss_handleCanFrame_t)-1);
    return osHandleBus == OSS_CAN_BUS_PT
           && !isExtId
           && (canId == 1536  ||  canId == 1537 ||  canId == 1538)
           ? _nextHandleCanFrame++
           : OSS_INVALID_CAN_FRAME_HANDLE;

} /* End of oss_registerFrameForSending */




/**
 * A platform may notify by interrupt if it goes into bus-off state. If so it might offer a
 * function to make (after a while) an attempt to restart the bus. This function simulates
 * this behavior. The restart of the bus will succeed with a random probablity.
 *   @param osHandleBus
 * The handle of the CAN bus.
 */

void oss_restartCanBus(oss_handleCanBus_t osHandleBus ATTRIB_DBG_ONLY)
{
    /* So far, we simulate only a single bus. */
    assert(osHandleBus == OSS_CAN_BUS_PT);

    /* Recovery might have been tried regardless of the current bus status. */
    if(!_isBusOff)
    {
        LOG_DEBUG( main_hGlobalLogger
                 , "%.1f ms: "
                   "oss_restartCanBus: "
                   "Attempt to recover from bus-off although bus is not in state bus-off"
                 , oss_tiSim / 1000.0
                 );
    }
    else if(BOOL_RAND(P_BUS_RECOVERY))
    {
        /* A successful recovery from bus-off is simulated by a high probability. */
        _isBusOff = false;
        LOG_DEBUG( main_hGlobalLogger
                 , "%.1f ms: "
                   "oss_restartCanBus: "
                   "Simulate successful recovery from bus-off"
                 , oss_tiSim / 1000.0
                 );
        if(_irqHandlerCanBusOff != NULL)
            _irqHandlerCanBusOff(/* isOff */ false);
    }
    else
    {
        LOG_DEBUG( main_hGlobalLogger
                 , "%.1f ms: "
                   "oss_restartCanBus: "
                   "Simulate failing attempt to recover from bus-off"
                 , oss_tiSim / 1000.0
                 );
    }
} /* End of oss_restartCanBus */



/**
 * The platform's simulated CAN send function. The frame is identified by the OS handle,
 * which had been obtain with an initial call of \a oss_registerFrameForSending.
 *   @return
 * The function returns a success message. A \a false will typically appear if the message
 * transfer object had not been flushed meanwhile. Mostly, a transfer object is related to
 * a CAN handle and hence the error appears if two frames of same ID are sent to soon after
 * one another. We don't measure the time but simulate an error by a random process.\n
 *   In our simulation the function also returns \a false if we are in bus-off state.
 *   @param osHandleFrame
 * The operating system handle of the frame as got from \a oss_registerFrameForSending.
 *   @param pData
 * The frame contents, already byte encoded.
 *   @param DLC
 * The number of bytes to send out.
 */

bool oss_sendCanFrame( oss_handleCanFrame_t osHandleFrame
                     , uint8_t *pData
                     , unsigned int DLC
                     )
{
#define P_SEND_ERR 0.01

    bool success = osHandleFrame != OSS_INVALID_CAN_FRAME_HANDLE;
    assert(success);

    if(_isBusOff)
        success = false;

    if(success)
    {
        if(BOOL_RAND(P_SEND_ERR))
        {
            LOG_DEBUG( main_hGlobalLogger
                     , "%.1f ms: "
                       "oss_sendCanFrame: "
                       "Simulate a send error for message with OS handle %u\n"
                     , oss_tiSim / 1000.0
                     , (unsigned)osHandleFrame
                     );
            success = false;
        }
        else
        {
            logCanFrame(/* isReceived */ false, osHandleFrame, pData, DLC);
            LOG_DEBUG( main_hGlobalLogger
                     , "%.1f ms: "
                       "oss_sendCanFrame: "
                       "Successfully send message with OS handle %u\n"
                     , oss_tiSim / 1000.0
                     , (unsigned)osHandleFrame
                     );
        }
    }

    return success;

#undef P_SEND_ERR
} /* End of oss_sendCanFrame */