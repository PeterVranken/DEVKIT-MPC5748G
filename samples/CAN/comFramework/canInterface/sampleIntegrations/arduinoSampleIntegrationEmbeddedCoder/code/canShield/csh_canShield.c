/**
 * @file csh_canShield.c
 * Implementation of interface of hypothetic Arduino CAN Shield. See readMe.txt in the
 * same directory for design details.
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
 *   csh_initModule
 *   csh_registerStdCanFrame
 *   csh_registerExtCanFrame
 *   csh_sendStdCanFrame
 *   csh_sendExtCanFrame
 *   csh_restartCanBus
 *   csh_getHasCanStdId
 *   csh_getCanStdId
 *   csh_getCanExtId
 *   csh_getCanDLC
 *   csh_getFrameData
 *   csh_hwBusStateChange
 *   csh_hwFrameReceived
 * Local functions
 *   registerCanFrame
 */

/*
 * Include files
 */

#include <stdlib.h>
#include <stdio.h>

#include "rtos_assert.h"
#include "csh_canShield.h"


/*
 * Defines
 */
 
#if CSH_NBR_OF_AVAILABLE_MESSAGE_TRANSFER_OBJECTS > 255
# error Too many message transfer objects. Implementation uses uint8_t as index type
#endif

 
/*
 * Local type definitions
 */
 
 
/*
 * Local prototypes
 */
 
/** The description of the message transfer object. */
typedef struct MTO_t
{
    /** The (extended) CAN ID of the frames, which can be procesed by this MTO. */
    uint32_t idFilter;
    
    /** The mask for ID matching. */
    uint32_t idMask;
    
    /** Boolean if we have a standard or extended ID. */
    unsigned int isInbound:1;
    
    /** For outbound frames only: Buffer is either free or pending, i.e. not yet (entirely)
        serialized on the physical bus. */
    unsigned int isPending:1;
    
    /** The actual CAN ID of the frame, which is currently processed by this MTO. */
    uint32_t id;
    
    /** The frame content bytes. */
    uint8_t dataAry[8];

    /** The DLC of the transmitted frame, i.e. the number of bytes in \a dataAry. */
    unsigned int DLC:4;
    
} MTO_t;
 

/*
 * Data definitions
 */
 
/** The array of MTOs. In a real system this would be implemented in hardware. Here, we
    simulate it in RAM. */
static MTO_t _mtoAry[CSH_NBR_OF_AVAILABLE_MESSAGE_TRANSFER_OBJECTS];

/** Simple simulation of bus management; current bus state. */
csh_stateCanBus_t _stateCanBus = csh_stsBusShutdown;

/** Simple simulation of bus management; a flag to signal the APSW's attempt to restart a
    bus in state bus-off. */
boolean _tryToRestartCanBus = false;


/*
 * Function implementation
 */

/**
 * Frame registering: A message transfer object is prepared for CAN transmission. Send
 * direction and filter for CAN IDs are set.
 *   @param idxMto
 * The operation relates to a specific MTO. The range of \a idxMto is
 * 0..#CSH_NBR_OF_AVAILABLE_MESSAGE_TRANSFER_OBJECTS-1.
 *   @param isInbound
 * The direction of transmission.
 *   @param isStdId
 * Boolean flag to indicate, whether the CAN IDs are 11 Bit standard IDs.
 *   @param canIdFilter
 * The 11 or 29 Bit CAN ID filter. The MTO will handle all frames which have a CAN ID that
 * matches \a canIdFilter at the bit positions, where the corresponding bit in \a canIdMask is
 * set. (If several MTOs fulfill this condition then the one with lower index will win.)
 *   @param canIdMask
 * The 11 or 29 Bit mask for CAN IDs.
 */

static void registerCanFrame( uint8_t idxMto
                            , boolean isInbound
                            , boolean isStdId
                            , uint32_t canIdFilter
                            , uint32_t canIdMask
                            )
{
    ASSERT((((canIdFilter | canIdMask) & ~0x1fffffff) == 0)
           &&  idxMto < CSH_NBR_OF_AVAILABLE_MESSAGE_TRANSFER_OBJECTS
          );

    MTO_t *pMto = &_mtoAry[idxMto];
    pMto->idFilter = canIdFilter;
    
    if(isStdId)
    {
        /* To make 11 Bit IDs compatible with the implementation we force all more
           significant bits to fit to the (null) bits of the 11 Bit IDs. */
        pMto->idMask = canIdMask | 0x1ffff800;
    }
    else
        pMto->idMask = canIdMask;
        
    pMto->isInbound = isInbound? 1: 0;
    pMto->isPending = 0;
    pMto->DLC = 0;
    
} /* End of registerCanFrame */




/**
 * Initialization of this compilation unit. Needs to be called prior to the use of any
 * function or data object.
 */

void csh_initModule()
{
    MTO_t *pMto = &_mtoAry[0];
    uint8_t idxMto;
    for(idxMto=0; idxMto<CSH_NBR_OF_AVAILABLE_MESSAGE_TRANSFER_OBJECTS; ++idxMto)
    {
        /* An MTO with CAN ID filter 0 means an inactive MTO. */
        pMto->idFilter = 0;
        pMto->idMask = 0x1fffffff;
        pMto->isInbound = 0;
        pMto->isPending = 0;
        pMto->id = 0;
        pMto->DLC = 0;
        
        unsigned int u;
        for(u=0; u<sizeof(pMto->dataAry)/sizeof(pMto->dataAry[0]); ++u)
            pMto->dataAry[u] = 0;
            
        ++ pMto;
    }
    
    _stateCanBus = csh_stsBusActive;
    
} /* End of csh_initModule */




/**
 * Frame registering: A message transfer object is prepared for CAN transmission. Send
 * direction and filter for CAN IDs are set.
 *   @param idxMto
 * The operation relates to a specific MTO. The range of \a idxMto is
 * 0..#CSH_NBR_OF_AVAILABLE_MESSAGE_TRANSFER_OBJECTS-1.
 *   @param isInbound
 * The direction of transmission.
 *   @param canStdIdFilter
 * The 11 Bit CAN ID filter. The MTO will handle all frames which have a standard CAN ID
 * that matches \a canStdIdFilter at the bit positions, where the corresponding bit in \a
 * canIdMask is set. (If several MTOs fulfill this condition then the one with lower index
 * will win.)\n
 *   This function can solely be used for CAN frames with a standard CAN ID.
 *   @param canIdMask
 * The 11 Bit mask for CAN IDs.
 */

void csh_registerStdCanFrame( uint8_t idxMto
                            , boolean isInbound
                            , uint16_t canStdIdFilter
                            , uint16_t canIdMask
                            )
{
    /* This is demonstration software only, not a real implementation and our main
       intention is not to save RAM here. So we can effort to simple use a single
       implementation for both API functions. */
    ASSERT(((canStdIdFilter | canIdMask) & ~0x7ff) == 0);
    registerCanFrame( idxMto
                    , isInbound
                    , /* isStdId */ true
                    , (uint32_t)canStdIdFilter
                    , (uint32_t)canIdMask
                    );
} /* End of csh_registerStdCanFrame */




/**
 * Frame registering: A message transfer object is prepared for CAN transmission. Send
 * direction and filter for CAN IDs are set.
 *   @param idxMto
 * The operation relates to a specific MTO. The range of \a idxMto is
 * 0..#CSH_NBR_OF_AVAILABLE_MESSAGE_TRANSFER_OBJECTS-1.
 *   @param isInbound
 * The direction of transmission.
 *   @param canExtIdFilter
 * The 29 Bit CAN ID filter. The MTO will handle all frames which have a CAN ID that
 * matches \a canExtIdFilter at the bit positions, where the corresponding bit in \a
 * canIdMask is set. (If several MTOs fulfill this condition then the one with lower index
 * will win.)
 *   @param canIdMask
 * The 29 Bit mask for CAN IDs.
 */

void csh_registerExtCanFrame( uint8_t idxMto
                            , boolean isInbound
                            , uint32_t canExtIdFilter
                            , uint32_t canIdMask
                            )
{
    registerCanFrame(idxMto, isInbound, /* isStdId */ false, canExtIdFilter, canIdMask);
    
} /* End of csh_registerExtCanFrame */



/**
 * Send a CAN frame with standard ID.
 *   @return
 * \a true, if frame could be written into an available MTO, else \a false.
 *   @param canStdId
 * The 11 Bit CAN ID. Passing an extended ID is reported by assertion.
 *   @param pData
 * The frame contents by read-only reference.
 *   @param DLC
 * The number of bytes \a pData points to.
 *   @remark
 * In the simulation this is a functionless stub. We put the data into the right MTO but
 * there's nobody is ever asking for its new contents.
 */

boolean_t csh_sendStdCanFrame(uint16_t canStdId, const uint8_t *pData, uint8_t DLC)
{
    ASSERT((canStdId & ~0x7ff) == 0  &&  (pData != NULL  ||  DLC == 0) && DLC < 8);
    return csh_sendExtCanFrame((uint32_t)canStdId, pData, DLC);
    
} /* End of csh_sendStdCanFrame */



/**
 * Send a CAN frame with extended ID.
 *   @return
 * \a true, if frame could be written into an available MTO, else \a false.
 *   @param canStdId
 * The 29 Bit CAN ID. Passing a standard ID is naturally possible.
 *   @param pData
 * The frame contents by read-only reference.
 *   @param DLC
 * The number of bytes \a pData points to.
 *   @remark
 * In the simulation this is a functionless stub. We put the data into the right MTO but
 * there's nobody is ever asking for its new contents.
 */

boolean_t csh_sendExtCanFrame(uint32_t canExtId, const uint8_t *pData, uint8_t DLC)
{
    ASSERT((canExtId & ~0x1fffffff) == 0  &&  (pData != NULL  ||  DLC == 0) && DLC < 8);

    /* Sending is only possible if bus is active. */
    if(_stateCanBus == csh_stsBusActive)
    {
        /* In this HW simulation a linear search looks for the matching MTO. A real HW
           system would have parallel structures to immediately detect the appropriate
           MTO. */
        MTO_t *pMto = &_mtoAry[0];
        uint8_t idxMto;
        for(idxMto=0; idxMto<CSH_NBR_OF_AVAILABLE_MESSAGE_TRANSFER_OBJECTS; ++idxMto, ++pMto)
            if(!pMto->isInbound &&  ((pMto->idFilter ^ canExtId) & pMto->idMask) == 0)
                break;

        /* If idxMto<CSH_NBR_OF_AVAILABLE_MESSAGE_TRANSFER_OBJECTS then this index and pMto
           reference the first matching MTO. */

        if(idxMto < CSH_NBR_OF_AVAILABLE_MESSAGE_TRANSFER_OBJECTS)
        {    
            /* For now, the implementation doesn't have an access synchronization to the
               data registers. The reason simply is that we don't have a consumer of the
               information yet. When such a consumer is implemented in a refinement of the
               simulation behvior the it must be synchronized. The true HW would set the
               pending bit on write to the registers and clear it in the instance of having
               the data completely processed - this may be copying into a shadow register
               at start of serialization on the physical bus or at the end of serilization
               on the physical bus. In any case it'll last till the bus is free to send the
               frame held the MTO. The needed task synchronization can use the pending bit
               similarly for atomic access to the entire MTO from both sides.
                 If there is a client for the data then it would be a good idea to foresee
               a second callback into the APSW, which is called, when the data has been
               taken out of the MTO; such a notification interrupt is available in most CAN
               environments. */
            pMto->id = canExtId;
            pMto->DLC = DLC;
            ASSERT(!pMto->isInbound &&  pMto->isPending == 0);
            memcpy(&pMto->dataAry[0], pData, DLC);

            return true;
        }
        else
            return false;
    }
    else
        return false;

} /* End of csh_sendExtCanFrame */



/**
 * Get the data contents of a CAN frame with standard ID.
 *   @return
 * \a true, if frame could be written into an available MTO, else \a false.
 *   @param canStdId
 * The 11 Bit CAN ID. Passing an extended ID is reported by assertion. In systems, where
 * both kinds of IDs are in use one will either not use this method at all or precede the
 * call by 
 * only fit into the 16 Bit value.
 *   @param pData
 * The frame contents by read-only reference.
 *   @param DLC
 * The number of bytes \a pData points to.
 *   @remark
 * In the simulation this is a functionless stub. We could look for the right MTO and fill
 * it but nobody is ever asking for the contents of the outbound MTOs. Therefore the
 * function implementation is left empty.
 */



/**
 * The APSW can use this function to try to recover from a bus-off. If the situatio, which
 * let to the bus-off has disappear than the bus will propbably return to the active
 * state.\n
 *   The behavior is asynchrounous; immediate operationability of the bus after return must
 * not be assumed by the APSW. It'll have to await a later state change notification in
 * case of success.
 */

void csh_restartCanBus()
{
    _tryToRestartCanBus = true;    

} /* End of csh_restartCanBus */




/**
 * Query whether a received frame has a standard ID.
 *   @return
 * \a true, if the frame in the geiven MTO has a standard ID, \a false for an extended ID.
 *   @param idxMto
 * The operation relates to a specific MTO. The range of \a idxMto is
 * 0..#CSH_NBR_OF_AVAILABLE_MESSAGE_TRANSFER_OBJECTS-1. This may be an in- or outbound MTO.
 */

boolean_t csh_getHasCanStdId(uint8_t idxMto)
{
    ASSERT(idxMto < CSH_NBR_OF_AVAILABLE_MESSAGE_TRANSFER_OBJECTS);
    return (_mtoAry[idxMto].id & 0xfffff800) == 0;
    
} /* End of csh_getHasCanStdId */




/**
 * Get the standard CAN ID of a given MTO.
 *   @return
 * Get the ID. An assertion fires if the frame has an extended ID.
 *   @param idxMto
 * The operation relates to a specific MTO. The range of \a idxMto is
 * 0..#CSH_NBR_OF_AVAILABLE_MESSAGE_TRANSFER_OBJECTS-1. This may be an in- or outbound MTO.
 */

uint16_t csh_getCanStdId(uint8_t idxMto)
{
    ASSERT(idxMto < CSH_NBR_OF_AVAILABLE_MESSAGE_TRANSFER_OBJECTS
           &&  (_mtoAry[idxMto].id & 0xfffff800) == 0
          );
    return (uint16_t)_mtoAry[idxMto].id;
    
} /* End of csh_getCanStdId */




/**
 * Get the extended CAN ID of a given MTO.
 *   @return
 * Get the ID, which may naturally be in the 11 Bit range of a standard ID, too.
 *   @param idxMto
 * The operation relates to a specific MTO. The range of \a idxMto is
 * 0..#CSH_NBR_OF_AVAILABLE_MESSAGE_TRANSFER_OBJECTS-1. This may be an in- or outbound MTO.
 */

uint32_t csh_getCanExtId(uint8_t idxMto)
{
    ASSERT(idxMto < CSH_NBR_OF_AVAILABLE_MESSAGE_TRANSFER_OBJECTS
           &&  (_mtoAry[idxMto].id & 0xe0000000) == 0
          );
    return _mtoAry[idxMto].id;
    
} /* End of csh_getCanExtId */




/**
 * Get the DLC of the frame in a given MTO.
 *   @return
 * Get the number of bytes of the frame contents stored in the MTO.
 *   @param idxMto
 * The operation relates to a specific MTO. The range of \a idxMto is
 * 0..#CSH_NBR_OF_AVAILABLE_MESSAGE_TRANSFER_OBJECTS-1. This may be an in- or outbound MTO.
 */

uint8_t csh_getCanDLC(uint8_t idxMto)
{
    ASSERT(idxMto < CSH_NBR_OF_AVAILABLE_MESSAGE_TRANSFER_OBJECTS);
    return (uint8_t)_mtoAry[idxMto].DLC;
    
} /* End of csh_getCanDLC */




/**
 * Get the contents of a frame stored in the given MTO.
 *   @param idxMto
 * The operation relates to a specific MTO. The range of \a idxMto is
 * 0..#CSH_NBR_OF_AVAILABLE_MESSAGE_TRANSFER_OBJECTS-1. This may be an in- or outbound MTO.
 *   @param sizeOfBuffer
 * The maximum number of bytes to copied from the MTO to the destination. The operation is
 * not save even in case of proper applying this API: Even if the client first asks for the
 * DLC and then provided a buffer of that size it may go wrong: The MTO can have been
 * refilled by a new frame between the two operations. To avoid hurt buffer boundaries, the
 * client will tell how large the destination memory area is.
 *   @remark buffer
 * Pointer to the client provided memory area, where to place the frame contents bytes.
 *   @see boolean otherFunction(int)
 */

void csh_getFrameData(uint8_t idxMto, uint8_t sizeOfBuffer, uint8_t *buffer)
{
    ASSERT(idxMto < CSH_NBR_OF_AVAILABLE_MESSAGE_TRANSFER_OBJECTS);
    uint8_t noBytes = _mtoAry[idxMto].DLC;
    if(sizeOfBuffer < noBytes)
        noBytes = sizeOfBuffer;
    memcpy(buffer, &_mtoAry[idxMto].dataAry[0], noBytes);
    
} /* End of csh_getFrameData */




/**
 * Simulation API: A status change of the bus is simulated by invoking this function from
 * the simulation control. The function mainly notifies the APSW about the state change
 * similar to as a true CAN API would do.\n
 *   The behavior is similar to true HW behavior if this function is invoked rarely from a
 * task of higher priority and which is logically unsynchronized with the APSW tasks, that
 * consume the CAN data.\n
 *   The call of this function by APSW code is not intended.
 *   @param canId
 * The standard CAN ID. (The simulation doesn't make use of 29 Bit identifiers.)
 *   @param DLC
 * The number of received frame content bytes.
 *   @param pData
 * The received data by read-only reference.
 */

void csh_hwBusStateChange(csh_stateCanBus_t newState)
{
    ASSERT(newState != csh_stsBusInvalid);
    _stateCanBus = newState;
    
    /* Pending requests to recover from bus-off are cleared as they obviously didn't relate
       to the current bus-off event. */
    if(newState == csh_stsBusOff)
        _tryToRestartCanBus = false;

    /* If the simulation is refined we should consider the proper handling of pending
       MTOs. */
       
    /* Notify the APSW about the state change. */
    csh_callbackOnBusStateChange(newState);

} /* End of csh_hwBusStateChange */




/**
 * Simulation API: The simulation code layer can query if the APSW has meanwhile requested
 * the restart of the CAN bus after a bus-off. It may use this information to simulate the
 * bus recovery.\n
 *   The behavior is similar to true HW behavior if this function is invoked occasionally
 * or regularly during bus-off from a task of higher priority than the APSW tasks, that
 * might request a bus recovery.\n
 *   The call of this function by APSW code is not intended.
 *   @return
 * The function returns \a true if the APSW had requested a bus recovery since the last
 * recent call of this function or the last recent transition to bus-off, whatever came
 * later.
 */

boolean csh_hwGetRestartBus()
{
    /* The flag is reset as side effect of the function. This makes it necessary to have a
       calling task of higher priority than the flag-setting APSW task (using
       csh_restartCanBus). */
    boolean tryToRestartCanBus = _tryToRestartCanBus;
    _tryToRestartCanBus = false;
    return tryToRestartCanBus;
    
} /* End of csh_hwBusStateChange */




/**
 * Simulation API: A frame is received. This function is used to simulate the HW behavior.
 * New CAN data is received, ID and data, and the data is copied into the first matching
 * MTO (if any). Existing data is overwritten just like that and the APSW callback \a
 * csh_callbackOnReceiveCanFrame is invoked to notify the reception to the upper SW layers.
 * The behavior is similar to true HW behavior if this function is invoked occasionally
 * from a task of higher priority and which is logically unsynchronized with the APSW
 * tasks, that consume the CAN data.\n
 *   The call of this function by APSW code is not intended.
 *   @param canId
 * The standard CAN ID. (The simulation doesn't make use of 29 Bit identifiers.)
 *   @param DLC
 * The number of received frame content bytes.
 *   @param pData
 * The received data by read-only reference.
 */

void csh_hwFrameReceived(uint16_t canId, uint8_t DLC, const uint8_t *pData)
{
    /* An MTO with CAN ID 0 means an inactive MTO. No CAN frame with ID can be supported. */
    ASSERT(canId != 0);

    /* Reception of frames isn't posisble in all bus states. */
    if(_stateCanBus == csh_stsBusListening  ||  _stateCanBus == csh_stsBusActive)
    {
        /* In this HW simulation a linear search looks for the matching MTO. A real HW system
           would have parallel structures to immediately detect the appropriate MTO. */
        MTO_t *pMto = &_mtoAry[0];
        uint8_t idxMto;
        for(idxMto=0; idxMto<CSH_NBR_OF_AVAILABLE_MESSAGE_TRANSFER_OBJECTS; ++idxMto, ++pMto)
            if(pMto->isInbound &&  ((pMto->idFilter ^ (uint32_t)canId) & pMto->idMask) == 0)
                break;

        /* If idxMto<CSH_NBR_OF_AVAILABLE_MESSAGE_TRANSFER_OBJECTS then this index and pMto
           reference the first matching MTO. */

        if(idxMto < CSH_NBR_OF_AVAILABLE_MESSAGE_TRANSFER_OBJECTS)
        {
            /* The implementation purposely doesn't consider any synchronization code with the
               APSW tasks. The current contents of the matching MTO are simply overwritten.
               Proper synchronization for unviolated data can solely be done by fast data
               fetching and is fully in the responsibility of the connected APSW. */
            pMto->id = canId;
            pMto->DLC = DLC;
            ASSERT(pMto->isInbound &&  pMto->isPending == 0);
            memcpy(&pMto->dataAry[0], pData, DLC);

            /* Notify dependent code. As in a real HW driven platform this callback is executed
               in the interrupt context (which is equivalent to our task of highest
               priority). */
            csh_callbackOnReceiveCanFrame(idxMto);
        }
    } /* if(Bus in receiving state?) */
} /* End of hwFrameReceived */





