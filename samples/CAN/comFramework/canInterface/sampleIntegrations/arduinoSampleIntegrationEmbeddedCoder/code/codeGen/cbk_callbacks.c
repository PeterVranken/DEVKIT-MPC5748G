/**
 * @file cbk_callbacks.c
 * 
 * This file contains the set of callbacks for the CAN interface engine, which implement
 * the network database specific parts of the interface.\n
 *   This sample integration supports in- and outbound frames and these may have three
 * transmission modes:\n
 *
 * - Regular. Normal frames, which are transmitted regularly. For inbound frames this means
 *   a timeout timer, which has an elapse time relative to the nominal period of the
 *   frame. On reception this timer is re-triggered. If it elapses a timeout error is
 *   reported at the API to the APSW.\n
 *     For outbound frames it means a periodic timer, which unconditionally sends the
 *   frame\n
 * - Event based. This actually means data change triggered. An outbound frame is checked
 *   in every tick, whether at least one of the signal values has changed. If so and only if
 *   so, it is sent out. A local, static buffer is applied to implement the change
 *   recognition. A timing condition is specified, too. A minimum distance of two sent
 *   frames is regarded; this defines a maximum send frequency even in case of permanent
 *   data changes. A timer object with dependent elapse time is use to control this
 *   behavior: After sending a frame the next data-change test is scheduled only after the
 *   minimum delay time, but normally, if no data-change has been found, the same timer
 *   will elapse again in the next computation time tick. Now the data-change test is
 *   repeated soon in order to avoid long latency times after data changes.\n
 *     For inbound frames event based means that we don't use any timer and can't generate
 *   a timeout event. The API to the APSW is updated if the frame comes in and never else\n
 * - Mixed mode. Basically a data change triggered frame but with a fallback: It is
 *   transmitted after a (typically long) while of no data changes. It behaves like a
 *   regular frame of low period time if no data changes appear at all.\n
 *     For inbound frames this means the same behavior as for regular frames with the only
 *   exception of applying another timeout value. Now the timeout is determined by the
 *   maximum distance in time due to the fallback rule.\n
 *     For outbound frames it means a combination of two timers. The solution for event
 *   based frames is extended by a second timer, the timeout timer. It elapses after the
 *   maximum distance in time due to the fallback rule and is re-triggered on every actual
 *   send event (regardless whether due to data-change or due to fallback). If it elapses
 *   it sends the frame\n
 *
 * The transmission mode and the related timings are specified in the network database by
 * frame attributes:\n
 *
 * - frameSendMode: The transmission mode as an enumeration. Permitted values are: regular,
 *   event and mixed
 * - sendPeriod: The constant period time of regular frames in Milli seconds. Irrelevant
 *   for event mode frames. For mixed mode frames it is the maximum distance in time
 *   between two transmissions in ms (i.e. if no data change appears)
 * - eventMinDistance: Irrelevant for regular frames. For all others this is the minimum
 *   distance in time between two transmissions in ms (i.e. if permanent data changes
 *   appears)
 *
 * All timing is done in the grid or granularity of the clock tick of the dispatcher. CAN
 * network databases strongly tend to use Milli seconds as time unit for their attributes
 * (as we do in our sample integration). If the dispatcher is clocked every Milli second
 * then all timing will be most accurate. If it is clocked slower (for sake of less
 * overhead) then all events are postponed till the next dispatcher clock tick. This is
 * often an acceptable optimization of the code. Regular frames, which found on periodic
 * counters will still be accurate on average: If the dispatcher is clocked every ten Milli
 * seconds and a frame had a period of 25 ms then it would be sent every alternatingly two or
 * three clock ticks. The other transmission mode found on single shot timers and here the
 * time spans would be rounded up; a minimum distance of 25 ms would actually become
 * 30 ms.
 *
 * All frames may have a single checksum and a single sequence counter. Both are normal
 * signals of the frame but they could unambiguously be identified as checksum or sequence
 * counter by name (regular expression matching at code generation time).\n
 *   The checksum signal can be supported only if it is an eight Bit signal, which is
 * located on byte position. This is because checksums are understood byte oriented not
 * signal value oriented. If the signal doesn't meet this demand then the generated code
 * will fail to compile.\n
 *   The checksum is assumed to apply to all the content bytes of the frame; checksums
 * defined for sub-sets of signals or signal groups can't be supported. The kind of
 * checksum (sum, CRC, etc.) is out of scope. An external function implements the checksum
 * computation and validation and defines the kind of checksum. Different kinds of
 * checksums for different frames are not supported but this would be an easy and
 * straightforward extension; another database attribute could be introduced and just be
 * passed to the external function.\n
 *   The checksum computation is supported by a frame attribute in the network database:
 *
 * - checksumStartValue: A one Byte number, which is used as start value for the checksum
 *   computation. It should be chosen differently for all frames so that taking the
 *   contents of frame A for those of frame B would lead to a checksum error
 *
 * The sequence counter is supported only if it is a signal of up to eight Bit.
 * Supporting longer signals is as easy as changing the type of some data elements from
 * uint8 to uint16 but even sequence counters of more than 4 Bit are barely used.\n
 *   The sequence counter operates cyclically and can have different boundaries and both
 * counting directories. These properties are controlled by the signal's min and max value
 * in the network database. Min always has the meaning of the first value in the cycle and
 * max always is the last value in the cycle (both including). Consequently, if min > max
 * then the counter acts as a down counter. (It's not clear if setting min > max will lead
 * to error messages or warnings in other, unrelated tools, which operate on the network
 * database.)
 *
 * The API with the APSW is data based. A static struct exists for each frame. It contains
 * the signal values and the status word, a bit vector. For received frames the following
 * status or errors are known (see \a cap_stsTransmission_t):
 *
 * - Never received: An initially set status bit, which is never set but reset on the first
 *   reception of the frame
 * - Wrong DLC: The frame can't be decoded. No further check or data evaluation is done.
 *   The signal values in the API won't be updated on reception
 * - Wrong checksum: The frame contents are invalid and consequently, the signal values are
 *   not decoded and will not overwrite those in the API
 * - Wrong sequence counter: The received frame is not the direct successor of the last
 *   recently received frame of same ID. However, the frame as such is alright and it is
 *   unpacked and the signal values are written into the API
 *
 * Sent frames only know a single error in our sample environment: The operating system's
 * CAN send function just returns a \a false to indicate an undetermined error, like
 * message buffer full or bus-off. This bit is written into the status word in the API to
 * the APSW.
 *
 * This file has been created with comFramework - codeGenerator version 1.11.2,
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"
#include "rtos_assert.h"
#include "csh_canShield.h"
#include "ede_eventDispatcherEngine.h"
#include "cde_stubs.h"
#include "chk_checksum.h"
#include "cap_canApi.h"
#include "apt_applicationTask.h"
#include "cbk_callbacks.h"


/*
 * Defines
 */

/** The common setting for timeout errors of inbound frames, used only until the very first
    reception: The timeout condition is defined relative to the nominal repetition time for
    regular frames or to the maximum distance of frames for event frames. */
#define RELATIVE_TIMEOUT_INITIAL_FRAME_RECEPTION 10

/** The common setting for timeout errors of inbound frames: The timeout condition is
    defined relative to the nominal repetition time for regular frames or to the maximum
    distance of frames for event frames. */
#define RELATIVE_TIMEOUT_FRAME_RECEPTION 3

/** Timer objects, which need the shortest possible elapse time, can use this define as
    period. The value ensures that the timer will elapse already in the next clock tick of
    the dispatcher. */
#define TI_NEXT_TICK 1

/** Double-check that the code generation templates are configured to use the right suffix
    for global objects. Go to file symbols.stg, dictionary file, if you get an error here. */
#define TMP_DEF_STRCMP_cbk_
#ifndef TMP_DEF_STRCMP_cbk_
# error Bad template configuration: Mismatch of module suffix, see cbk_ but require cbk_
#endif
#undef TMP_DEF_STRCMP_cbk_ 

/*
 * Local type definitions
 */

 

/*
 * Local prototypes
 */

 

/*
 * Data definitions
 */

/* The list of timer handles for the implementation of message processing. They are shared
   between the different frame related callbacks. */
static ede_handleTimer_t _hTimerTimeout_PT_1024 = EDE_INVALID_TIMER_HANDLE;
static ede_handleTimer_t _hTimerTimeout_PT_1040 = EDE_INVALID_TIMER_HANDLE;
static ede_handleTimer_t _hTimerTimeout_PT_1537 = EDE_INVALID_TIMER_HANDLE;
static ede_handleTimer_t _hTimerDueCheck_PT_1537 = EDE_INVALID_TIMER_HANDLE;
static ede_handleTimer_t _hTimerDueCheck_PT_1538 = EDE_INVALID_TIMER_HANDLE;


/* Event based outbound frames are implemented by saving the sent data contents in the
   instance of sending and comparing the current API data with the saved data. A difference
   will trigger next sending. These are the static buffers, where the frame contents are
   saved. */
static cap_PT_StatusPowerDisplay_1537_t _lastSentFrContents_PT_StatusPowerDisplay_1537 =
    {
        .noDlcErrors = 0,
        .noCheckSumErrors = 0,
        .noSqcErrors = 0,
        .sequenceCounter = 1,
        .checksum = 0,
    };

static cap_PT_LimitsPowerDisplay_1538_t _lastSentFrContents_PT_LimitsPowerDisplay_1538 =
    {
        .sequenceCounter = 6,
        .belowMinSpeedOfRotation = 0,
        .aboveMaxSpeedOfRotation = 0,
        .belowMinPower = 0,
        .aboveMaxPower = 0,
    };

 

/*
 * Function implementation
 */

/**
 * Frame related callback for frame StateEcu01 (1024, 0x400),
 * which is invoked by the interface engine on reception of that frame.\n
 *   The data is extracted, validated if applicable (checksum, sequence counter), the
 * signals are unpacked and written into the global APSW interface and the timer for
 * timeout recognition is handled.
 *   @param pContext
 * The dispatcher context this callback is invoked from.
 */
static void onReceiveFrame_PT_1024(const ede_callbackContext_t *pContext)
{
    ASSERT(ede_getKindOfEvent(pContext) == APT_EV_RX_CAN_MSG);

    /* Unwanted sequence error artefacts will always be seen after another error, which
       inibited the decoding of the predecessors's sequence counter value. If we have these
       errors, we need to reinitialize the sequence error validation. */
    boolean_t reinitSQCValidation = (cap_canBus_PT.PT_StateEcu01_1024_sts.stsTransmission & ~cap_stsTransm_errSequence) != 0;

    /* Frame received: Reset a possible never received and timeout error bit and let the
       timeout condition count from null. */
    cap_canBus_PT.PT_StateEcu01_1024_sts.stsTransmission &=
                            ~(cap_stsTransm_neverReceived
                              | cap_stsTransm_errTimeout
                             );
    ede_retriggerSingleShotTimer( pContext
                                , _hTimerTimeout_PT_1024
                                , RELATIVE_TIMEOUT_FRAME_RECEPTION * 10 /* ms */
                                );

    /* Get access to the data bytes. */
    unsigned int sizeOfFrameContents;
    const uint8_t * const frameContents = ede_getEventData(pContext, &sizeOfFrameContents);

    /* Do the DLC check: If the number of received bytes doesn't match the expected fixed
       size then we can't do any other evaluation. */
    if(sizeOfFrameContents == CAP_PT_STATEECU01_1024_DLC)
    {
        /* Reset a possible DLC error bit. */
        cap_canBus_PT.PT_StateEcu01_1024_sts.stsTransmission &= ~cap_stsTransm_errDLC;

        /* Validate the checksum. */
        if(chk_validateChecksum( frameContents
                               , CAP_PT_STATEECU01_1024_DLC
                               , /* idxChecksumByte */ CAP_PT_STATEECU01_1024_CHECKSUM_STARTBIT / 8
                               , CAP_PT_STATEECU01_1024_CHECKSUM_START_VALUE
                               )
          )
        {
            /* Reset a possible checksum error bit. */
            cap_canBus_PT.PT_StateEcu01_1024_sts.stsTransmission &= ~cap_stsTransm_errChecksum;

            /* Unpack the signals. The result is directly written into the global struct
               cap_canBus_PT.PT_StateEcu01_1024_sts.signals, which serves as interface with
               the APSW. */
            cap_unpack_PT_StateEcu01_1024(frameContents);

            /* Check the sequence counter. */
            static uint8_t lastSqc_ = 0;
            if(chk_validateSequenceCounter( cap_canBus_PT.PT_StateEcu01_1024_sts.signals.sequenceCounter
                                          , &lastSqc_
                                          , CAP_PT_STATEECU01_1024_SQC_FROM
                                          , CAP_PT_STATEECU01_1024_SQC_TO
                                          , reinitSQCValidation
                                          )
              )
            {
                /* No sequence error. Reset possible error bit. */
                cap_canBus_PT.PT_StateEcu01_1024_sts.stsTransmission &= ~cap_stsTransm_errSequence;
            }
            else
            {
                /* Sequence error. Set error bit in API to the APSW. */
                cap_canBus_PT.PT_StateEcu01_1024_sts.stsTransmission |= cap_stsTransm_errSequence;
            }
        }
        else
        {
            /* Set the checksum error bit. */
            cap_canBus_PT.PT_StateEcu01_1024_sts.stsTransmission |= cap_stsTransm_errChecksum;
        }
    }
    else
    {
        /* The DLC error is set but the data content related errors are reset: we can't
           evaluate the data and can't therefore make a statement. */
        cap_canBus_PT.PT_StateEcu01_1024_sts.stsTransmission &= ~(cap_stsTransm_errChecksum | cap_stsTransm_errSequence);
        cap_canBus_PT.PT_StateEcu01_1024_sts.stsTransmission |= cap_stsTransm_errDLC;
    }
} /* End of onReceiveFrame_PT_1024 */



/**
 * Frame related callback for frame StateEcu02 (1040, 0x410),
 * which is invoked by the interface engine on reception of that frame.\n
 *   The data is extracted, validated if applicable (checksum, sequence counter), the
 * signals are unpacked and written into the global APSW interface and the timer for
 * timeout recognition is handled.
 *   @param pContext
 * The dispatcher context this callback is invoked from.
 */
static void onReceiveFrame_PT_1040(const ede_callbackContext_t *pContext)
{
    ASSERT(ede_getKindOfEvent(pContext) == APT_EV_RX_CAN_MSG);

    /* Unwanted sequence error artefacts will always be seen after another error, which
       inibited the decoding of the predecessors's sequence counter value. If we have these
       errors, we need to reinitialize the sequence error validation. */
    boolean_t reinitSQCValidation = (cap_canBus_PT.PT_StateEcu02_1040_sts.stsTransmission & ~cap_stsTransm_errSequence) != 0;

    /* Frame received: Reset a possible never received and timeout error bit and let the
       timeout condition count from null. */
    cap_canBus_PT.PT_StateEcu02_1040_sts.stsTransmission &=
                            ~(cap_stsTransm_neverReceived
                              | cap_stsTransm_errTimeout
                             );
    ede_retriggerSingleShotTimer( pContext
                                , _hTimerTimeout_PT_1040
                                , RELATIVE_TIMEOUT_FRAME_RECEPTION * 25 /* ms */
                                );

    /* Get access to the data bytes. */
    unsigned int sizeOfFrameContents;
    const uint8_t * const frameContents = ede_getEventData(pContext, &sizeOfFrameContents);

    /* Do the DLC check: If the number of received bytes doesn't match the expected fixed
       size then we can't do any other evaluation. */
    if(sizeOfFrameContents == CAP_PT_STATEECU02_1040_DLC)
    {
        /* Reset a possible DLC error bit. */
        cap_canBus_PT.PT_StateEcu02_1040_sts.stsTransmission &= ~cap_stsTransm_errDLC;

        /* Validate the checksum. */
        if(chk_validateChecksum( frameContents
                               , CAP_PT_STATEECU02_1040_DLC
                               , /* idxChecksumByte */ CAP_PT_STATEECU02_1040_CHECKSUM_STARTBIT / 8
                               , CAP_PT_STATEECU02_1040_CHECKSUM_START_VALUE
                               )
          )
        {
            /* Reset a possible checksum error bit. */
            cap_canBus_PT.PT_StateEcu02_1040_sts.stsTransmission &= ~cap_stsTransm_errChecksum;

            /* Unpack the signals. The result is directly written into the global struct
               cap_canBus_PT.PT_StateEcu02_1040_sts.signals, which serves as interface with
               the APSW. */
            cap_unpack_PT_StateEcu02_1040(frameContents);

            /* Check the sequence counter. */
            static uint8_t lastSqc_ = 0;
            if(chk_validateSequenceCounter( cap_canBus_PT.PT_StateEcu02_1040_sts.signals.sequenceCounter
                                          , &lastSqc_
                                          , CAP_PT_STATEECU02_1040_SQC_FROM
                                          , CAP_PT_STATEECU02_1040_SQC_TO
                                          , reinitSQCValidation
                                          )
              )
            {
                /* No sequence error. Reset possible error bit. */
                cap_canBus_PT.PT_StateEcu02_1040_sts.stsTransmission &= ~cap_stsTransm_errSequence;
            }
            else
            {
                /* Sequence error. Set error bit in API to the APSW. */
                cap_canBus_PT.PT_StateEcu02_1040_sts.stsTransmission |= cap_stsTransm_errSequence;
            }
        }
        else
        {
            /* Set the checksum error bit. */
            cap_canBus_PT.PT_StateEcu02_1040_sts.stsTransmission |= cap_stsTransm_errChecksum;
        }
    }
    else
    {
        /* The DLC error is set but the data content related errors are reset: we can't
           evaluate the data and can't therefore make a statement. */
        cap_canBus_PT.PT_StateEcu02_1040_sts.stsTransmission &= ~(cap_stsTransm_errChecksum | cap_stsTransm_errSequence);
        cap_canBus_PT.PT_StateEcu02_1040_sts.stsTransmission |= cap_stsTransm_errDLC;
    }
} /* End of onReceiveFrame_PT_1040 */



/**
 * Frame related callback for frame UserLimits (2032, 0x7f0),
 * which is invoked by the interface engine on reception of that frame.\n
 *   The data is extracted, validated if applicable (checksum, sequence counter), the
 * signals are unpacked and written into the global APSW interface and the timer for
 * timeout recognition is handled.
 *   @param pContext
 * The dispatcher context this callback is invoked from.
 */
static void onReceiveFrame_PT_2032(const ede_callbackContext_t *pContext)
{
    ASSERT(ede_getKindOfEvent(pContext) == APT_EV_RX_CAN_MSG);

    /* Unwanted sequence error artefacts will always be seen after another error, which
       inibited the decoding of the predecessors's sequence counter value. If we have these
       errors, we need to reinitialize the sequence error validation. */
    boolean_t reinitSQCValidation = (cap_canBus_PT.PT_UserLimits_2032_sts.stsTransmission & ~cap_stsTransm_errSequence) != 0;

    /* Frame received: Reset a possible never received bit. */
    cap_canBus_PT.PT_UserLimits_2032_sts.stsTransmission &= ~cap_stsTransm_neverReceived;

    /* Get access to the data bytes. */
    unsigned int sizeOfFrameContents;
    const uint8_t * const frameContents = ede_getEventData(pContext, &sizeOfFrameContents);

    /* Do the DLC check: If the number of received bytes doesn't match the expected fixed
       size then we can't do any other evaluation. */
    if(sizeOfFrameContents == CAP_PT_USERLIMITS_2032_DLC)
    {
        /* Reset a possible DLC error bit. */
        cap_canBus_PT.PT_UserLimits_2032_sts.stsTransmission &= ~cap_stsTransm_errDLC;

        /* Validate the checksum. */
        if(chk_validateChecksum( frameContents
                               , CAP_PT_USERLIMITS_2032_DLC
                               , /* idxChecksumByte */ CAP_PT_USERLIMITS_2032_CHECKSUM_STARTBIT / 8
                               , CAP_PT_USERLIMITS_2032_CHECKSUM_START_VALUE
                               )
          )
        {
            /* Reset a possible checksum error bit. */
            cap_canBus_PT.PT_UserLimits_2032_sts.stsTransmission &= ~cap_stsTransm_errChecksum;

            /* Unpack the signals. The result is directly written into the global struct
               cap_canBus_PT.PT_UserLimits_2032_sts.signals, which serves as interface with
               the APSW. */
            cap_unpack_PT_UserLimits_2032(frameContents);

            /* Check the sequence counter. */
            static uint8_t lastSqc_ = 0;
            if(chk_validateSequenceCounter( cap_canBus_PT.PT_UserLimits_2032_sts.signals.sequenceCounter
                                          , &lastSqc_
                                          , CAP_PT_USERLIMITS_2032_SQC_FROM
                                          , CAP_PT_USERLIMITS_2032_SQC_TO
                                          , reinitSQCValidation
                                          )
              )
            {
                /* No sequence error. Reset possible error bit. */
                cap_canBus_PT.PT_UserLimits_2032_sts.stsTransmission &= ~cap_stsTransm_errSequence;
            }
            else
            {
                /* Sequence error. Set error bit in API to the APSW. */
                cap_canBus_PT.PT_UserLimits_2032_sts.stsTransmission |= cap_stsTransm_errSequence;
            }
        }
        else
        {
            /* Set the checksum error bit. */
            cap_canBus_PT.PT_UserLimits_2032_sts.stsTransmission |= cap_stsTransm_errChecksum;
        }
    }
    else
    {
        /* The DLC error is set but the data content related errors are reset: we can't
           evaluate the data and can't therefore make a statement. */
        cap_canBus_PT.PT_UserLimits_2032_sts.stsTransmission &= ~(cap_stsTransm_errChecksum | cap_stsTransm_errSequence);
        cap_canBus_PT.PT_UserLimits_2032_sts.stsTransmission |= cap_stsTransm_errDLC;
    }
} /* End of onReceiveFrame_PT_2032 */




/**
 * Frame related timer callback for frame StateEcu01 (1024, 0x400),
 * which is invoked by the interface engine on timeout of that frame.\n
 *   The timeout error is set.
 *   @param pContext
 * The dispatcher context this callback is invoked from.
 */
static void onTimeoutFrame_PT_1024(const ede_callbackContext_t *pContext)
{
    ASSERT(ede_getKindOfEvent(pContext) == EDE_EV_TIMER_ELAPSED);

    /* Timeout event for frame received. Set the timeout error bit. */
    cap_canBus_PT.PT_StateEcu01_1024_sts.stsTransmission |= cap_stsTransm_errTimeout;
} /* End of onTimeoutFrame_PT_1024 */




/**
 * Frame related timer callback for frame StateEcu02 (1040, 0x410),
 * which is invoked by the interface engine on timeout of that frame.\n
 *   The timeout error is set.
 *   @param pContext
 * The dispatcher context this callback is invoked from.
 */
static void onTimeoutFrame_PT_1040(const ede_callbackContext_t *pContext)
{
    ASSERT(ede_getKindOfEvent(pContext) == EDE_EV_TIMER_ELAPSED);

    /* Timeout event for frame received. Set the timeout error bit. */
    cap_canBus_PT.PT_StateEcu02_1040_sts.stsTransmission |= cap_stsTransm_errTimeout;
} /* End of onTimeoutFrame_PT_1040 */





/**
 * Send frame InfoPowerDisplay (1536, 0x600).\n
 *   This is a regularly invoked timer callback from the interface engine.\n
 *   The frame contents are completed by checksum and sequence counter (if appropriate) and
 * sent.
 *   @param pContext
 * The dispatcher context this callback is invoked from.
 */
static void onSendFrame_PT_1536(const ede_callbackContext_t *pContext)
{
    ASSERT(ede_getKindOfEvent(pContext) == EDE_EV_TIMER_ELAPSED);

    /* Update the sequence counter. */
    chk_updateSequenceCounter( &cap_canBus_PT.PT_InfoPowerDisplay_1536_sts.signals.sequenceCounter
                             , CAP_PT_INFOPOWERDISPLAY_1536_SQC_FROM
                             , CAP_PT_INFOPOWERDISPLAY_1536_SQC_TO
                             );

    /* Pack the signals. The signal values are read from the global struct
       cap_canBus_PT.PT_InfoPowerDisplay_1536_sts.signals, which serves as interface with the APSW. */
    uint8_t frameContents[6];
    cap_pack_PT_InfoPowerDisplay_1536(frameContents);

    /* Update the checksum in the packed data. */
    chk_computeChecksum( &frameContents[0]
                       , CAP_PT_INFOPOWERDISPLAY_1536_DLC
                       , /* idxChecksumByte */ CAP_PT_INFOPOWERDISPLAY_1536_CHECKSUM_STARTBIT / 8
                       , CAP_PT_INFOPOWERDISPLAY_1536_CHECKSUM_START_VALUE
                       );

    /* Send the frame. */
    if(csh_sendStdCanFrame((uint16_t)cde_getCanId(pContext).id, frameContents, /* DLC */ 6))
    {
        /* Bit operation not required here, there's only one error bit for outbound frames. */
        cap_canBus_PT.PT_InfoPowerDisplay_1536_sts.stsTransmission = cap_stsTransm_okay;
    }
    else
        cap_canBus_PT.PT_InfoPowerDisplay_1536_sts.stsTransmission = cap_stsTransm_errSendBufferFull;
} /* End of onSendFrame_PT_1536 */



/**
 * Send frame StatusPowerDisplay (1537, 0x601).\n
 *   The function is either directly invoked from the interface engine as the callback of
 * the fallback timer or called from the due check callback in case of a recognized data
 * change.\n
 *   The frame contents are completed by checksum and sequence counter (if appropriate) and
 * sent.
 *   @param pContext
 * The dispatcher context this callback is invoked from.
 */
static void onSendFrame_PT_1537(const ede_callbackContext_t *pContext)
{
    ASSERT(ede_getKindOfEvent(pContext) == EDE_EV_TIMER_ELAPSED);

    /* Update the sequence counter. */
    chk_updateSequenceCounter( &cap_canBus_PT.PT_StatusPowerDisplay_1537_sts.signals.sequenceCounter
                             , CAP_PT_STATUSPOWERDISPLAY_1537_SQC_FROM
                             , CAP_PT_STATUSPOWERDISPLAY_1537_SQC_TO
                             );

    /* Save the contents of the event frame in order to recognize future data changes. */
    memcpy( &_lastSentFrContents_PT_StatusPowerDisplay_1537
          , &cap_canBus_PT.PT_StatusPowerDisplay_1537_sts.signals
          , sizeof(_lastSentFrContents_PT_StatusPowerDisplay_1537)
          );

    /* Pack the signals. The signal values are read from the global struct
       cap_canBus_PT.PT_StatusPowerDisplay_1537_sts.signals, which serves as interface with the APSW. */
    uint8_t frameContents[6];
    cap_pack_PT_StatusPowerDisplay_1537(frameContents);

    /* Update the checksum in the packed data. */
    chk_computeChecksum( &frameContents[0]
                       , CAP_PT_STATUSPOWERDISPLAY_1537_DLC
                       , /* idxChecksumByte */ CAP_PT_STATUSPOWERDISPLAY_1537_CHECKSUM_STARTBIT / 8
                       , CAP_PT_STATUSPOWERDISPLAY_1537_CHECKSUM_START_VALUE
                       );

    /* Send the frame. */
    if(csh_sendStdCanFrame((uint16_t)cde_getCanId(pContext).id, frameContents, /* DLC */ 6))
    {
        /* Bit operation not required here, there's only one error bit for outbound frames. */
        cap_canBus_PT.PT_StatusPowerDisplay_1537_sts.stsTransmission = cap_stsTransm_okay;
    }
    else
        cap_canBus_PT.PT_StatusPowerDisplay_1537_sts.stsTransmission = cap_stsTransm_errSendBufferFull;

    /* The frame was sent. The next time we repeat the due check is determined by the
       minimum time distance, which is a property of the frame taken from the network
       database. */
    ede_retriggerSingleShotTimer( pContext
                                , _hTimerDueCheck_PT_1537
                                , /* tiNewFromNow */ 50 /* ms */
                                );

    /* Retrigger the fallback timer for the next timeout of the mixed mode frame. Caution:
       Don't use NULL for hTimer here, since the function is called not only from the
       timeout counter's on-elapse callback but from the due check counter's callback as
       well. NULL would unintendedly reference the due check counter in the latter case. */
    ede_retriggerSingleShotTimer( pContext
                                , _hTimerTimeout_PT_1537
                                , /* tiNewFromNow */ 1000 /* ms */
                                );
} /* End of onSendFrame_PT_1537 */



/**
 * Send frame LimitsPowerDisplay (1538, 0x602).\n
 *   The function is called from the due check callback in case of a recognized data
 * change.\n
 *   The frame contents are completed by checksum and sequence counter (if appropriate) and
 * sent.
 *   @param pContext
 * The dispatcher context this callback is invoked from.
 */
static void onSendFrame_PT_1538(const ede_callbackContext_t *pContext)
{
    ASSERT(ede_getKindOfEvent(pContext) == EDE_EV_TIMER_ELAPSED);

    /* Update the sequence counter. */
    chk_updateSequenceCounter( &cap_canBus_PT.PT_LimitsPowerDisplay_1538_sts.signals.sequenceCounter
                             , CAP_PT_LIMITSPOWERDISPLAY_1538_SQC_FROM
                             , CAP_PT_LIMITSPOWERDISPLAY_1538_SQC_TO
                             );

    /* Save the contents of the event frame in order to recognize future data changes. */
    memcpy( &_lastSentFrContents_PT_LimitsPowerDisplay_1538
          , &cap_canBus_PT.PT_LimitsPowerDisplay_1538_sts.signals
          , sizeof(_lastSentFrContents_PT_LimitsPowerDisplay_1538)
          );

    /* Pack the signals. The signal values are read from the global struct
       cap_canBus_PT.PT_LimitsPowerDisplay_1538_sts.signals, which serves as interface with the APSW. */
    uint8_t frameContents[1];
    cap_pack_PT_LimitsPowerDisplay_1538(frameContents);

    /* Send the frame. */
    if(csh_sendStdCanFrame((uint16_t)cde_getCanId(pContext).id, frameContents, /* DLC */ 1))
    {
        /* Bit operation not required here, there's only one error bit for outbound frames. */
        cap_canBus_PT.PT_LimitsPowerDisplay_1538_sts.stsTransmission = cap_stsTransm_okay;
    }
    else
        cap_canBus_PT.PT_LimitsPowerDisplay_1538_sts.stsTransmission = cap_stsTransm_errSendBufferFull;

    /* The frame was sent. The next time we repeat the due check is determined by the
       minimum time distance, which is a property of the frame taken from the network
       database. */
    ede_retriggerSingleShotTimer( pContext
                                , _hTimerDueCheck_PT_1538
                                , /* tiNewFromNow */ 20 /* ms */
                                );
} /* End of onSendFrame_PT_1538 */




/**
 * Frame related timer callback for frame StatusPowerDisplay (1537, 0x601),
 * which is regularly invoked by the interface engine.\n
 *   The frame contents are checked for intermediate changes and the frame is sent in case.
 *   @param pContext
 * The dispatcher context this callback is invoked from.
 */
static void onDueCheckEventFrame_PT_1537(const ede_callbackContext_t *pContext)
{
    ASSERT(ede_getKindOfEvent(pContext) == EDE_EV_TIMER_ELAPSED);

    /* Compare frame contents as sent last recently with current API data: A change means a
       send event. */
    boolean_t isDue =
                memcmp( &_lastSentFrContents_PT_StatusPowerDisplay_1537
                      , &cap_canBus_PT.PT_StatusPowerDisplay_1537_sts.signals
                      , sizeof(_lastSentFrContents_PT_StatusPowerDisplay_1537)
                      )
                != 0;

    if(isDue)
    {
        /* Unconditionally send the frame. The due check timer is retriggered in
           function onSendFrame_PT_1537. */
        onSendFrame_PT_1537(pContext);
    }
    else
    {
        /* The frame wasn't sent this time. Repeat the data-change check as early as
           possible, this is the meaning of an event frame. */
        ede_retriggerSingleShotTimer( pContext
                                    , /* hTimer */ NULL
                                    , /* tiNewFromNow */ TI_NEXT_TICK
                                    );
    }
} /* End of onDueCheckEventFrame_PT_1537 */




/**
 * Frame related timer callback for frame LimitsPowerDisplay (1538, 0x602),
 * which is regularly invoked by the interface engine.\n
 *   The frame contents are checked for intermediate changes and the frame is sent in case.
 *   @param pContext
 * The dispatcher context this callback is invoked from.
 */
static void onDueCheckEventFrame_PT_1538(const ede_callbackContext_t *pContext)
{
    ASSERT(ede_getKindOfEvent(pContext) == EDE_EV_TIMER_ELAPSED);

    /* Compare frame contents as sent last recently with current API data: A change means a
       send event. */
    boolean_t isDue =
                memcmp( &_lastSentFrContents_PT_LimitsPowerDisplay_1538
                      , &cap_canBus_PT.PT_LimitsPowerDisplay_1538_sts.signals
                      , sizeof(_lastSentFrContents_PT_LimitsPowerDisplay_1538)
                      )
                != 0;

    if(isDue)
    {
        /* Unconditionally send the frame. The due check timer is retriggered in
           function onSendFrame_PT_1538. */
        onSendFrame_PT_1538(pContext);
    }
    else
    {
        /* The frame wasn't sent this time. Repeat the data-change check as early as
           possible, this is the meaning of an event frame. */
        ede_retriggerSingleShotTimer( pContext
                                    , /* hTimer */ NULL
                                    , /* tiNewFromNow */ TI_NEXT_TICK
                                    );
    }
} /* End of onDueCheckEventFrame_PT_1538 */





/**
 * Frame related callback for frame StateEcu01 (1024, 0x400),
 * which is invoked by the interface engine at initialization time.\n
 *   The callback for processing of external events is installed and the required timers
 * are configured.
 *   @param pContext
 * The dispatcher context this callback is invoked from.
 */
static void onInitFrame_PT_1024(const ede_callbackContext_t *pContext)
{
    ASSERT(ede_getKindOfEvent(pContext) == EDE_EV_EVENT_SOURCE_EXT_INIT);

    /* Install the event handler for processing of external frame reception events. */
    ede_installCallback(pContext, onReceiveFrame_PT_1024);

    /* Start the timeout timer. A longer timeout value is used for the first reception. */
    _hTimerTimeout_PT_1024 = ede_createSingleShotTimer
                                    ( pContext
                                    , RELATIVE_TIMEOUT_INITIAL_FRAME_RECEPTION * 10 /* ms */
                                    , onTimeoutFrame_PT_1024
                                    , /* killAtDueTime */ false
                                    );
    ASSERT(_hTimerTimeout_PT_1024 != EDE_INVALID_TIMER_HANDLE);

} /* End of onInitFrame_PT_1024 */



/**
 * Frame related callback for frame StateEcu02 (1040, 0x410),
 * which is invoked by the interface engine at initialization time.\n
 *   The callback for processing of external events is installed and the required timers
 * are configured.
 *   @param pContext
 * The dispatcher context this callback is invoked from.
 */
static void onInitFrame_PT_1040(const ede_callbackContext_t *pContext)
{
    ASSERT(ede_getKindOfEvent(pContext) == EDE_EV_EVENT_SOURCE_EXT_INIT);

    /* Install the event handler for processing of external frame reception events. */
    ede_installCallback(pContext, onReceiveFrame_PT_1040);

    /* Start the timeout timer. A longer timeout value is used for the first reception. */
    _hTimerTimeout_PT_1040 = ede_createSingleShotTimer
                                    ( pContext
                                    , RELATIVE_TIMEOUT_INITIAL_FRAME_RECEPTION * 25 /* ms */
                                    , onTimeoutFrame_PT_1040
                                    , /* killAtDueTime */ false
                                    );
    ASSERT(_hTimerTimeout_PT_1040 != EDE_INVALID_TIMER_HANDLE);

} /* End of onInitFrame_PT_1040 */



/**
 * Frame related callback for frame UserLimits (2032, 0x7f0),
 * which is invoked by the interface engine at initialization time.\n
 *   The callback for processing of external events is installed and the required timers
 * are configured.
 *   @param pContext
 * The dispatcher context this callback is invoked from.
 */
static void onInitFrame_PT_2032(const ede_callbackContext_t *pContext)
{
    ASSERT(ede_getKindOfEvent(pContext) == EDE_EV_EVENT_SOURCE_EXT_INIT);

    /* Install the event handler for processing of external frame reception events. */
    ede_installCallback(pContext, onReceiveFrame_PT_2032);

} /* End of onInitFrame_PT_2032 */



/**
 * Frame related callback for frame InfoPowerDisplay (1536, 0x600),
 * which is invoked by the interface engine at initialization time.\n
 *   The callback for processing of external events is installed and the required timers
 * are configured.
 *   @param pContext
 * The dispatcher context this callback is invoked from.
 */
static void onInitFrame_PT_1536(const ede_callbackContext_t *pContext)
{
    ASSERT(ede_getKindOfEvent(pContext) == EDE_EV_EVENT_SOURCE_INT_INIT);

    /* Start the regular send timer. */
#ifdef DEBUG
    ede_handleTimer_t hTimer =
#endif
    ede_createPeriodicTimer( pContext
                           , 30 /* ms */
                           , onSendFrame_PT_1536
                           );
    ASSERT(hTimer != EDE_INVALID_TIMER_HANDLE);

} /* End of onInitFrame_PT_1536 */



/**
 * Frame related callback for frame StatusPowerDisplay (1537, 0x601),
 * which is invoked by the interface engine at initialization time.\n
 *   The callback for processing of external events is installed and the required timers
 * are configured.
 *   @param pContext
 * The dispatcher context this callback is invoked from.
 */
static void onInitFrame_PT_1537(const ede_callbackContext_t *pContext)
{
    ASSERT(ede_getKindOfEvent(pContext) == EDE_EV_EVENT_SOURCE_INT_INIT);

    /* Start the due check timer. This timer needs to be created prior to the timeout
       timer: If both are due in the same dispatcher clock tick then the due check will be
       served first and will have the chance to retrigger the timeout timer before its
       callback is invoked; double sending of the frame is avoided in this case. */
    _hTimerDueCheck_PT_1537 = ede_createSingleShotTimer
                                    ( pContext
                                    , TI_NEXT_TICK
                                    , onDueCheckEventFrame_PT_1537
                                    , /* autoKill */ false
                                    );
    ASSERT(_hTimerDueCheck_PT_1537 != EDE_INVALID_TIMER_HANDLE);

    /* Start a fallback timer to trigger sending if no data change was recognized. */
    _hTimerTimeout_PT_1537 = ede_createSingleShotTimer
                                    ( pContext
                                    , 1000 /* ms */
                                    , onSendFrame_PT_1537
                                    , /* autoKill */ false
                                    );
    ASSERT(_hTimerTimeout_PT_1537 != EDE_INVALID_TIMER_HANDLE);

} /* End of onInitFrame_PT_1537 */



/**
 * Frame related callback for frame LimitsPowerDisplay (1538, 0x602),
 * which is invoked by the interface engine at initialization time.\n
 *   The callback for processing of external events is installed and the required timers
 * are configured.
 *   @param pContext
 * The dispatcher context this callback is invoked from.
 */
static void onInitFrame_PT_1538(const ede_callbackContext_t *pContext)
{
    ASSERT(ede_getKindOfEvent(pContext) == EDE_EV_EVENT_SOURCE_INT_INIT);

    /* Start the due check timer. */
    _hTimerDueCheck_PT_1538 = ede_createSingleShotTimer
                                    ( pContext
                                    , TI_NEXT_TICK
                                    , onDueCheckEventFrame_PT_1538
                                    , /* autoKill */ false
                                    );
    ASSERT(_hTimerDueCheck_PT_1538 != EDE_INVALID_TIMER_HANDLE);

} /* End of onInitFrame_PT_1538 */




/**
 * Register all frames of cluster arduinoSampleIntegrationEC at the interface engine, which are
 * either sent or received by the implemented network node PowerDisplay.
 */
void cbk_initInterface()
{
    unsigned int idxMto = 0;
    unsigned int idxEdeEvSrc ATTRIB_DBG_ONLY;

    /* Declare frame StateEcu01 (1024, 0x400) at the operating system level. */
    csh_registerStdCanFrame( idxMto
                           , /* isReception */ true
                           , /* canStdIdFilter */ 1024
                           , /* canIdMask */ 0x7ff
                           );

    /* Having collected all required information the frame is now registered in the
       interface engine. */
    idxEdeEvSrc = ede_registerExternalEventSource
                                ( apt_hDispatcherSystem
                                , /* idxDispatcher */ APT_IDX_DISPATCHER_FRAME_EVENTS
                                , /* kindOfEvent */ APT_EV_RX_CAN_MSG
                                , /* senderHandleEvent */ idxMto
                                , /* callback */ onInitFrame_PT_1024
                                , /* refEventSourceData */ 1024u /* CAN ID */
                                );
    ASSERT(idxEdeEvSrc == idxMto + APT_EV_RX_CAN_MSG);
    ++ idxMto;

    /* Declare frame StateEcu02 (1040, 0x410) at the operating system level. */
    csh_registerStdCanFrame( idxMto
                           , /* isReception */ true
                           , /* canStdIdFilter */ 1040
                           , /* canIdMask */ 0x7ff
                           );

    /* Having collected all required information the frame is now registered in the
       interface engine. */
    idxEdeEvSrc = ede_registerExternalEventSource
                                ( apt_hDispatcherSystem
                                , /* idxDispatcher */ APT_IDX_DISPATCHER_FRAME_EVENTS
                                , /* kindOfEvent */ APT_EV_RX_CAN_MSG
                                , /* senderHandleEvent */ idxMto
                                , /* callback */ onInitFrame_PT_1040
                                , /* refEventSourceData */ 1040u /* CAN ID */
                                );
    ASSERT(idxEdeEvSrc == idxMto + APT_EV_RX_CAN_MSG);
    ++ idxMto;

    /* Declare frame UserLimits (2032, 0x7f0) at the operating system level. */
    csh_registerStdCanFrame( idxMto
                           , /* isReception */ true
                           , /* canStdIdFilter */ 2032
                           , /* canIdMask */ 0x7ff
                           );

    /* Having collected all required information the frame is now registered in the
       interface engine. */
    idxEdeEvSrc = ede_registerExternalEventSource
                                ( apt_hDispatcherSystem
                                , /* idxDispatcher */ APT_IDX_DISPATCHER_FRAME_EVENTS
                                , /* kindOfEvent */ APT_EV_RX_CAN_MSG
                                , /* senderHandleEvent */ idxMto
                                , /* callback */ onInitFrame_PT_2032
                                , /* refEventSourceData */ 2032u /* CAN ID */
                                );
    ASSERT(idxEdeEvSrc == idxMto + APT_EV_RX_CAN_MSG);
    ++ idxMto;


    const unsigned int noRegisteredRxMsgs ATTRIB_DBG_ONLY = idxMto;

    /* Declare frame InfoPowerDisplay (1536, 0x600) at the operating system level. */
    csh_registerStdCanFrame( idxMto
                           , /* isReception */ false
                           , /* canStdIdFilter */ 1536
                           , /* canIdMask */ 0x7ff
                           );

    /* Having collected all required information the frame is now registered in the
       interface engine. */
    idxEdeEvSrc = ede_registerInternalEventSource
                                ( apt_hDispatcherSystem
                                , /* idxDispatcher */ APT_IDX_DISPATCHER_FRAME_EVENTS
                                , /* callback */ onInitFrame_PT_1536
                                , /* refEventSourceData */ 1536u /* CAN ID */
                                );
    ASSERT(idxEdeEvSrc + noRegisteredRxMsgs == idxMto);
    ++ idxMto;

    /* Declare frame StatusPowerDisplay (1537, 0x601) at the operating system level. */
    csh_registerStdCanFrame( idxMto
                           , /* isReception */ false
                           , /* canStdIdFilter */ 1537
                           , /* canIdMask */ 0x7ff
                           );

    /* Having collected all required information the frame is now registered in the
       interface engine. */
    idxEdeEvSrc = ede_registerInternalEventSource
                                ( apt_hDispatcherSystem
                                , /* idxDispatcher */ APT_IDX_DISPATCHER_FRAME_EVENTS
                                , /* callback */ onInitFrame_PT_1537
                                , /* refEventSourceData */ 1537u /* CAN ID */
                                );
    ASSERT(idxEdeEvSrc + noRegisteredRxMsgs == idxMto);
    ++ idxMto;

    /* Declare frame LimitsPowerDisplay (1538, 0x602) at the operating system level. */
    csh_registerStdCanFrame( idxMto
                           , /* isReception */ false
                           , /* canStdIdFilter */ 1538
                           , /* canIdMask */ 0x7ff
                           );

    /* Having collected all required information the frame is now registered in the
       interface engine. */
    idxEdeEvSrc = ede_registerInternalEventSource
                                ( apt_hDispatcherSystem
                                , /* idxDispatcher */ APT_IDX_DISPATCHER_FRAME_EVENTS
                                , /* callback */ onInitFrame_PT_1538
                                , /* refEventSourceData */ 1538u /* CAN ID */
                                );
    ASSERT(idxEdeEvSrc + noRegisteredRxMsgs == idxMto);
    ++ idxMto;

} /* End of cbk_initInterface */



