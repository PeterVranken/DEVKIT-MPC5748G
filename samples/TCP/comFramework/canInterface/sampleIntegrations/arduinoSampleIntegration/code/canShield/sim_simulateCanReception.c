/**
 * @file sim_simulateCanReception.c
 * Simulation of CAN frame reception.
 *
 * Copyright (C) 2015 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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
 *   sim_simulateCanReception
 * Local functions
 *   clockMsgSpeed
 *   clockMsgTorque
 *   clockMsgUserLimits
 */

/*
 * Include files
 */

#include <stdlib.h>
#include <stdio.h>

#include "rtos_assert.h"
#include "csh_canShield.h"
#include "sim_simulateCanReception.h"


/*
 * Defines
 */
 
/** Global switch to enable error simulation for frame 1024. Set it to either 1 or 0. */
#define DO_ERROR_SIMULATION_1024    1

/** Global switch to enable error simulation for frame 1040. Set it to either 1 or 0. */
#define DO_ERROR_SIMULATION_1040    1

/** Global switch to enable error simulation for frame 2032. Set it to either 1 or 0. */
#define DO_ERROR_SIMULATION_2032    1

/** The probability of a bus-off error. Only change the number literal in the definition! */
#define P_BUS_OFF               (0.0005 * (SIM_DO_ERROR_SIMULATION))

/** The probability of a bus recovery attempt to succeed. Only change the first definition! */
#if SIM_DO_ERROR_SIMULATION == 1
# define P_BUS_RECOVERY         (0.5)
#else
# define P_BUS_RECOVERY         (1.0)
#endif

/** The probability of simulating a timeout for frame 1024. Only change the number literal
    in the definition! */
#define P_TIMEOUT_1024          (0.0003 * (SIM_DO_ERROR_SIMULATION)*(DO_ERROR_SIMULATION_1024))

/** The probability of simulating a DLC error for frame 1024. Only change the number
    literal in the definition! */
#define P_DLC_ERR_1024          (0.0002 * (SIM_DO_ERROR_SIMULATION)*(DO_ERROR_SIMULATION_1024))

/** The probability of simulating a checksum error for frame 1024. Only change the number
    literal in the definition! */
#define P_CHKSUM_ERR_1024       (0.001 * (SIM_DO_ERROR_SIMULATION)*(DO_ERROR_SIMULATION_1024))

/** The probability of simulating a sequence counter error for frame 1024. Only change the
    number literal in the definition! */
#define P_SQC_ERR_1024          (0.0005 * (SIM_DO_ERROR_SIMULATION)*(DO_ERROR_SIMULATION_1024))

/** The probability of simulating a timeout for frame 1040. Only change the number literal
    in the definition! */
#define P_TIMEOUT_1040          (0.0001 * (SIM_DO_ERROR_SIMULATION)*(DO_ERROR_SIMULATION_1040))

/** The probability of simulating a DLC error for frame 1040. Only change the number
    literal in the definition! */
#define P_DLC_ERR_1040          (0.0001 * (SIM_DO_ERROR_SIMULATION)*(DO_ERROR_SIMULATION_1040))

/** The probability of simulating a checksum error for frame 1040. Only change the number
    literal in the definition! */
#define P_CHKSUM_ERR_1040       (0.0001 * (SIM_DO_ERROR_SIMULATION)*(DO_ERROR_SIMULATION_1040))

/** The probability of simulating a sequence counter error for frame 1040. Only change the
    number literal in the definition! */
#define P_SQC_ERR_1040          (0.0001 * (SIM_DO_ERROR_SIMULATION)*(DO_ERROR_SIMULATION_1040))

/** The probability of simulating a DLC error for frame 2032. Only change the number
    literal in the definition! */
#define P_DLC_ERR_2032          (0.001 * (SIM_DO_ERROR_SIMULATION)*(DO_ERROR_SIMULATION_2032))

/** The probability of simulating a checksum error for frame 2032. Only change the number
    literal in the definition! */
#define P_CHKSUM_ERR_2032       (0.001 * (SIM_DO_ERROR_SIMULATION)*(DO_ERROR_SIMULATION_2032))

/** The probability of simulating a sequence counter error for frame 2032. Only change the
    number literal in the definition! */
#define P_SQC_ERR_2032          (0.001 * (SIM_DO_ERROR_SIMULATION)*(DO_ERROR_SIMULATION_2032))



/** A scaled floating point random number in the range [a, b). */
#define RAND(a,b) ((float)((b)-(a))*RND()+(float)(a))

/** A Boolean random number with given probability p of getting a true. */
#define BOOL_RAND(p) (RND()<(p)? true: false)

/** A floating point random number in the range [0;1). */
#define RND() ((float)rand()/(float)RAND_MAX)


 
/*
 * Local type definitions
 */
 
 
/*
 * Local prototypes
 */
 
 
/*
 * Data definitions
 */
 
/** The simulation time. */
static uint32_t _tiSim = 0;

/** The status of the only simulated CAN bus: Normally active but can have a bus-off. */
static boolean_t _isBusOff = false;
 
/*
 * Function implementation
 */


/**
 * Tick the function, which controls the simulation of the generation of the inbound CAN
 * message that mainly contains the speed of rotation of the engine.\n
 *   The function controlls the update timing and the data content generation. It needs to
 * be called every 10 ms in mean.
 *   @return
 * \a true, if new data reception is simulated, \a false otherwise.
 *   @param msg
 * The caller provided buffer for up to eight message contents bytes.
 *   @param pDLC
 * The function returns the actual number of written bytes as * \a pDLC.
 */

static boolean_t clockMsgSpeed(uint8_t msg[8], uint8_t *pDLC)
{
#define TI_MSG_MS           10      /* ms */
#define SOR_MIN             800.0   /* rpm */
#define SOR_MAX             6500.0  /* rpm */
#define SOR_SLOPE           100.0   /* rpm/s */
#define CHKSUM_START_VAL    17

    /* This is just a simulation and demonstration. We ignore the counter overrun. After
       about 50 days the application will get stuck. */
    static uint32_t tiReceive_ = TI_MSG_MS
                  , tiLastReceive_ = 0;
    static float speedOfRotationSlope_ = SOR_SLOPE
               , speedOfRotation_ = SOR_MIN;
    static uint8_t SQC_ = 0;
    if(_tiSim > tiReceive_)
    {
        /* New reception event, produce new data. */
        /// @todo Here we have a logical error. The frames should jitter but only to simulate the timing inaccuracy of the bus. The logical data source is regular and the delta time of the "physical" simulation should thus not jitter. However, consider varying delta times in case of bus-off or simulated timeouts
        speedOfRotation_ += (float)(_tiSim - tiLastReceive_) * 1e-3 *speedOfRotationSlope_;
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

        /* Compute new reception time. (Jitter and drift are not implemented here but by
           intentional inaccuracy of the time base _tiSim.) */
        tiLastReceive_ = tiReceive_;
        tiReceive_ += TI_MSG_MS;

        /* In state bus-off we are not going to send a frame and the next steps are skipped. */
        if(_isBusOff)
        {
            *pDLC = 0;
            return false;
        }

        /* Consider a timeout. */
        if(BOOL_RAND(P_TIMEOUT_1024))
        {
            float tiTimeout = RAND(2,10)*TI_MSG_MS;
            tiReceive_ += (uint32_t)tiTimeout;
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
            ++ SQC_;
        ASSERT((msg[1] & 0xf0) == 0);
        msg[1] |= (SQC_ & 0x0f) << 4;
        if(SQC_ >= 14)
            SQC_ = 0;
        else
            ++ SQC_;

        /* Compute and add the checksum. */
        msg[0] = ~(CHKSUM_START_VAL + msg[1] + msg[2] + msg[3]);
        if(BOOL_RAND(P_CHKSUM_ERR_1024))
            ++ msg[0];

        /* Return the DLC with a possible, simulated error. */
        *pDLC = 4;
        if(BOOL_RAND(P_DLC_ERR_1024))
            -- *pDLC;

        return true;
    }
    else
    {
        *pDLC = 0;
        return false;
    }

#undef TI_MSG_MS
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

static boolean_t clockMsgTorque(uint8_t msg[8], uint8_t *pDLC)
{
#define TI_MSG_MS           25      /* ms */
#define TRQ_MIN             -10.0   /* Nm */
#define TRQ_MAX             450.0   /* Nm */
#define TRQ_SLOPE           110.0   /* Nm/s */
#define CHKSUM_START_VAL    218

    /* This is just a simulation and demonstration. We ignore the counter overrun. After
       about 50 days the application will get stuck. */
    static uint32_t tiReceive_ = TI_MSG_MS
                  , tiLastReceive_ = 0;
    static float torqueSlope_ = TRQ_SLOPE
               , torque_ = TRQ_MIN;
    static unsigned int SQC_ = 15;
    if(_tiSim > tiReceive_)
    {
        /* New reception event, produce new data. */
        /// @todo Here we have a logical error. The frames should jitter but only to simulate the timing inaccuracy of the bus. The logical data source is regular and the delta time of the "physical" simulation should thus not jitter. However, consider varying delta times in case of bus-off or simulated timeouts
        torque_ += (float)(_tiSim - tiLastReceive_) * 1e-3 * torqueSlope_;
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

        /* Compute new reception time. (Jitter and drift are not implemented here but by
           intentional inaccuracy of the time base _tiSim.) */
        tiLastReceive_ = tiReceive_;
        tiReceive_ += TI_MSG_MS;

        /* In state bus-off we are not going to send a frame and the next steps are skipped
           in order to avoid confusing console messages about an anyway suppressed frame. */
        if(_isBusOff)
        {
            *pDLC = 0;
            return false;
        }

        /* Consider a timeout. */
        if(BOOL_RAND(P_TIMEOUT_1040))
        {
            float tiTimeout = RAND(2,10)*TI_MSG_MS;
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
            ++ SQC_;
        msg[1] = SQC_ & 0x0f;
        if(SQC_ >= 2)
            -- SQC_;
        else
            SQC_ = 15;

        /* Compute and add the checksum. */
        msg[0] = ~(CHKSUM_START_VAL + msg[1] + msg[2] + msg[3]);
        if(BOOL_RAND(P_CHKSUM_ERR_1040))
            ++ msg[0];

        /* Return the DLC with a possible, simulated error. */
        *pDLC = 4;
        if(BOOL_RAND(P_DLC_ERR_1040))
            -- *pDLC;

        return true;
    }
    else
    {
        *pDLC = 0;
        return false;
    }

#undef TI_MSG_MS
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

static boolean_t clockMsgUserLimits(uint8_t msg[8], uint8_t *pDLC)
{
#define TI_MEAN_MSG_MS      9213   /* ms */
#define TI_MIN_MSG_MS       1234   /* ms */
#define CHKSUM_START_VAL    119

    /* This is just a simulation and demonstration. We ignore the counter overrun. After
       about 50 days the application will get stuck. */
    static uint32_t tiReceive_ = 17534 /* ms, first reception */
                  , tiLastReceive_ = 0;
    static unsigned int SQC_ = 1;
    if(_tiSim > tiReceive_)
    {
        /* New reception event, produce new data. Extract from the network database:
             SG_ minSpeedOfRotation : 6|12@1+ (1.6,0) [0|6500] "rpm"
             SG_ maxSpeedOfRotation : 18|12@1+ (1.6,0) [0|6500] "rpm"
             SG_ minPower : 47|9@0+ (0.5,-10) [-10|240] "KW"
             SG_ maxPower : 53|9@0+ (0.5,-10) [-10|240] "KW"
             Our data change is most simple: We toggle all variables bewteen two values. */
        static unsigned int minSpeedOfRotation = 800 /* rpm */
                                                 * 10 / 16
                          , maxSpeedOfRotation = 5000u /* rpm */
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
        tiLastReceive_ = tiReceive_;
        tiReceive_ += (uint32_t)RAND(TI_MIN_MSG_MS, 2*TI_MEAN_MSG_MS - TI_MIN_MSG_MS);

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
            ++ SQC_;
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
            /* We inject a data error in signal minSpeedOfRotation, which should be
               recognized as checksum error. */
            ++ msg[1];
        }

        /* Return the DLC with a possible, simulated error. */
        *pDLC = 8;
        if(BOOL_RAND(P_DLC_ERR_2032))
            -- *pDLC;

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
 * Simulation of CAN reception.\n
 *   This function should be called every 10 ms. Irregular calling with an average of 10 ms
 * is alright, this way the timing irregularities of the true CAN bus can eb simulated at
 * the same time.
 */

void sim_simulateCanReception()
{
    /* This function is called every 10 ms in mean. */
    _tiSim += 10;
    
    /* The simulation knows 3 CAN messages: A regular message at 10 ms, a regular message at
       25 ms rate and a data change triggered message. The regular messages are simulated
       with time-jitter and the data change message has a random behavior plus regular 5s
       fallback repetition.
         All messages have a random controlled timeout failure. */
    uint8_t msg[8];
    uint8_t DLC = 0;
    if(clockMsgSpeed(msg, &DLC))
    {
        /* A reception event is simulated. Invoke the function from the API of the CAN
           shield, which simulates the reception of a CAN frame. */
        csh_hwFrameReceived(/* canId */ 1024, DLC, msg);
    }
    if(clockMsgTorque(msg, &DLC))
    {
        /* A reception event is simulated. Invoke the function from the API of the CAN
           shield, which simulates the reception of a CAN frame. */
        csh_hwFrameReceived(/* canId */ 1040, DLC, msg);
    }
    if(clockMsgUserLimits(msg, &DLC))
    {
        /* A reception event is simulated. Invoke the function from the API of the CAN
           shield, which simulates the reception of a CAN frame. */
        csh_hwFrameReceived(/* canId */ 2032, DLC, msg);
    }

    /* A bus-off event is simulated occasionally by a low probability. */
    if(!_isBusOff && BOOL_RAND(P_BUS_OFF))
    {
        _isBusOff = true;
        csh_hwBusStateChange(/* newState */ csh_stsBusOff);
    }

    if(_isBusOff)
    {
        /* The APSW can request the bus recovery but this will only succeed with a given
           probability. And a spontaneous recovery is also occasionally possible. */
        if((csh_hwGetRestartBus() && BOOL_RAND(P_BUS_RECOVERY))  ||  BOOL_RAND(P_BUS_OFF))
        {
            _isBusOff = false;
            csh_hwBusStateChange(/* newState */ csh_stsBusActive);
        }
    }
} /* End of sim_simulateCanReception */





