/**
 * @file ede_eventSender.c
 * Implementation of the event sender. Any number of senders can be created and they can be
 * flexibly connected to an unrelated set of dispatchers. n:m connectivity is supported.
 *
 * Copyright (C) 2021-2022 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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
 *   ede_createSender
 *   ede_postEvent
 *   ede_postEventToPort
 *   ede_getNoSenderPortBlockedEvents
 * Local functions
 */

/** @todo The API of a sender port splits sending a data packet into buffer allocation and
    submission. There are a lot of use cases, where this two-step paradigm saves us payload
    copying. (Data can instead be directly produced inside the allocated buffer.) This
    advantage is lost when using the sender object, which offers just the one-step "post".
    The two-step approach should become an optionally applied additional sender API. */
    
/*
 * Include files
 */

#include "ede_eventSender.h"

#include <string.h>
#include <assert.h>

#include "ede_externalInterfaces.h"
#include "ede_eventDispatcherEngine.h"
#include "ede_externalInterfaces.h"


/*
 * Defines
 */
 

/*
 * Local type definitions
 */
 
/** An event sender object. */
typedef struct ede_eventSender_t
{
    /** The (externally implemented) map, which associates the abstract handle of an
        external event with the port number to use for sending. */
    ede_mapSenderEvHandleToIdx_t mapSdrEvHdlToEdePortIdx;

    /** The number of event output ports in \a portAry. */
    unsigned int noPorts;

    /** The list of event ports, which the events can be posted to. The list is implemented
        as flexible array member; therefore, it needs to be the very last field. */
    struct
    {
        ede_eventSenderPort_t port;

        /** Counter of attempts to write to a blocked port (typically due to a full queue).
            The counter wraps around at its implementation maximum.\n
              This member is updated by the sender and read-only to all other contexts.
            Therefore, it is essential that this member can be read or written in a single
            atomic operation; this explains the type, which has to be configured platform
            dependent. */
        volatile ede_atomicUnsignedInt_t noErrorsPortBlocked;

    } portAry[];
    
} ede_eventSender_t;


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
 * Create a sender.\n
 *   A sender has n output ports and it can be connected to n dispatchers. Main API of a
 * sender is ede_postEvent(), which sends an event to the connetced dispatcher input. The
 * exact behavior depends on the element, which is applied to make the connection between
 * the sender's output port and the dispatcher's input port. This will normally be a queue
 * but can be any other connecting operation, which implements the given interface.
 *   @return
 * Get \a true if the new sender could be created and \a false otherwise.\n
 *   The function will fail only in case of lack of memory. Since all memory allocation is
 * static and deterministic an appropriate and recommended failure handling concept is to
 * check the return value by assertion only. If the assertion doesn't fire throughout the
 * development and test phase then it won't in the production code. Anyhow, the sender
 * must never be used if this function returns \a false.
 *   @param pHandleSender
 * Get the handle of the newly created sender object by reference. This handle is later
 * needed to use the sender. If the function fails then it'll return the special handle
 * #EDE_INVALID_SENDER_HANDLE in * \a pHandleSender.\n
 *   @param portAry
 * All ports of the sender as an array of objects, which implement the given interface.
 * Each port may use the same or another implementation of the interface. Normally, the
 * implementation of the interface will be the tail of the thread-safe queue, see
 * vsq_threadSafeQueueVariableSize.h, which belongs to this package.\n
 *   The array elements are copied and portAry needs to be valid only during the run time
 * of the constructor.
 *   @param noPorts
 * The number of supported ports and the number of elements in portAry at the same time.
 *   @param pMapSenderEvHandleToPortIndex
 * The (externally implemented) map by reference, which associates the abstract handle of
 * an external event with the output port to use for th given event(by index).\n
 *   If the sender has just one port then no mapping is required and NULL can be passed.
 * All events will go into the only port. Note, a map still matters for a sender with a
 * single port: A map now becomes a Boolean filter, whether or not an event may or can be
 * posted.\n
 *   If only method ede_postEventToPort() is going to be used to send an event, i.e., method
 * ede_postEvent() won't be used, then NULL can be passed even for a sender with more than
 * one port.
 *   @param pMemPoolSender
 * A memory pool by reference, which provides the memory needed for construction of the
 * sender object.\n
 *   The memory dealt out by this pool needs to grant write-access to the context that runs
 * the event posting process, i.e., the process, which is going to regularly call
 * ede_sendEvent() for the here created sender object. All other contexts (e.g. dispatchers
 * or other senders) don't need access to the memory.
 *   @remark
 * The call of this function has to be done in a race condition free environment, prior to
 * entering the multi-tasking phase of the application. Most platforms will offer an
 * initialization task for this purpose.
 */
bool ede_createSender( ede_handleSender_t * const pHandleSender
                     , const ede_eventSenderPort_t portAry[]
                     , unsigned int noPorts
                     , const ede_mapSenderEvHandleToIdx_t *pMapSenderEvHandleToPortIndex
                     , ede_memoryPool_t * const pMemPoolSender
                     )
{
    *pHandleSender = EDE_INVALID_SENDER_HANDLE;
    if(noPorts < 1u)
    {
        /* Invalid configuration of sender. */
        return false;
    }

    /* Flexible array member: The size of the sender object depends on the number of ports. */
    const unsigned int sizeOfSenderObj = sizeof(ede_eventSender_t) 
                                         + noPorts * sizeof((*pHandleSender)->portAry[0]);

    /* The sender object is created in the specified memory pool. */
    ede_eventSender_t * const pSender = pMemPoolSender->malloc( pMemPoolSender->hInstance
                                                              , sizeOfSenderObj
                                                              );
    if(pSender == NULL)
        return false;

    if(pMapSenderEvHandleToPortIndex != NULL)
    {
        EDE_ASSERT(pMapSenderEvHandleToPortIndex->getValue != NULL);
        pSender->mapSdrEvHdlToEdePortIdx = *pMapSenderEvHandleToPortIndex;
    }
    else
    {
        pSender->mapSdrEvHdlToEdePortIdx = (ede_mapSenderEvHandleToIdx_t)
                                           {
                                               .addKeyValuePair = NULL,
                                               .getValue = NULL,
                                               .hInstance = 0u,
                                           };
    }

    pSender->noPorts = noPorts;
    for(unsigned int idxPort=0u; idxPort<noPorts; ++idxPort)
    {
        pSender->portAry[idxPort].port = portAry[idxPort];
        pSender->portAry[idxPort].noErrorsPortBlocked = 0u;
    }

    *pHandleSender = pSender;
    return true;

} /* ede_createSender */





/**
 * An event is posted. It is sent via the associated sender's port.\n
 *   This function is invoked by the integration code. In the case of CAN communication,
 * the call is typically used from within a CAN interrupt handler. The posted event
 * normally is a frame reception event or a frame send acknowledge event. Generally, the
 * kind of postable events depends on the platform and the integration.\n
 *   The event is posted to the port, which is named by the map that had been agreed on
 * during construction of the sender. This indirect port selection has been defined in
 * order to allow the external intergration code to specify the connectivity still at run
 * time. As an example, and for CAN communication, the external code could decide for each
 * particular CAN message, whether it is processed by the QM code or by the safety code. If
 * this flexibility is not required then the other API ede_postEventToPort() can be used.\n
 *   The meaning of an event is widely transparent to sender and dispatcher. The event is
 * identified by two values of basic integral data type. The first value is the "kind of
 * event" and this will be an enumeration. The only constraint sender and dispatcher put on
 * this value are a few numeric values, which are reserved for internal purpose; see
 * #EDE_EV_KIND_LAST for details. The second value is a handle or ID of the event. Use and
 * meaning of this value are unconstrained and fully transparant to sender and dispatcher.
 * Having two value to identify an event means that each kind of event has its own handle
 * space; this has been decide to support heterogenous events.
 *   @return
 * \a true, if function succeeded, else \a false. For most imaginable implementations of
 * the port interface, it'll be possible that the port is currently not able to process a
 * new event, e.g., because of a queue full state. In this case, the event is entirely
 * ignored (besides reporting the port-blocked event).
 *   @param hSender
 * The sender object to use. Has been created before by ede_createSender().
 *   @param kindOfEvent
 * The kind of event. It is an enumeration, which is meaningless to the sender or
 * dispatcher object. Which values are passed is entirely in the scope of the integration
 * code, which defines both, the event reporting interrupts and the client code, which
 * eventually evaluates the transmitted events. In the case of CAN communication, this will
 * e.g. be the CAN message reception event.
 *   @param senderHandleEvent
 * The event's handle as used (and issued) by the external integration code. In the case of
 * CAN communication, this will e.g. be the operating system's handle of a registered CAN
 * message.
 *   @param pData
 * A pointer to some event data, which is meaningless to the sender and dispatcher object.
 * Typically used to convey CAN message content bytes in case of a reception event, but can
 * be anything else. May be NULL if \a sizeOfData is zero, too.
 *   @param sizeOfData
 * The number of data bytes, i.e., the number of bytes, \a pData points to.
 *   @remark
 * Posting an event to a particular port of the sender is not reentrant. If event sources
 * running in different CPU contexts are posting to one and the same sender port then the
 * integration code needs to implement mutual exclusion. All of these event sources
 * need to be serialized with respect to event posting.\n
 *   In practice, concurrent event sources that require mutual exclusion will likely occur
 * if the events are reported by different interrupts; different interrupts have different
 * priorities on most existing systems and interrupts of higher priority are normally
 * allowed to preempt those of lower priority. In this situation, a reasonable alternative
 * to explicit mutual exclusion code is an architecture using another interconnected pair
 * of sender and and dispatcher port for each interrupt.
 */
bool ede_postEvent( ede_eventSender_t * const hSender
                  , ede_kindOfEvent_t kindOfEvent
                  , ede_senderHandleEvent_t senderHandleEvent
                  , const void *pData
                  , unsigned int sizeOfData
                  )
{
    /* Apply the (external) mapping in order to find the frame the event is related to. */
    unsigned int idxPort;
    if(hSender->mapSdrEvHdlToEdePortIdx.getValue != NULL)
    {
        if(!hSender->mapSdrEvHdlToEdePortIdx.getValue
                                                ( hSender->mapSdrEvHdlToEdePortIdx.hInstance
                                                , &idxPort
                                                , kindOfEvent
                                                , senderHandleEvent
                                                )
          )
        {
            /* The external map doesn't know the event. This is normally an implementation
               error in the external code and we could even have an assertion here.
               However, the mapping has been specified tolerant, only the event is lost. */
            /// @todo Should this be counted like a lost event due to buffer full?
            //EDE_ASSERT(false);
            return false;
        }
    }
    else
    {
        /* Default mapping means unconditionally using the only port of a sender. */
        idxPort = 0u;
                                          
        if(hSender->noPorts > 1u)
        {
            /* Here, we have a configuration error as the sender has more than one port but
               no map is specified. This points to an implementation error in the external
               code. */
            EDE_ASSERT(false);
            return false;
        }
    }

    return ede_postEventToPort( hSender
                              , idxPort
                              , kindOfEvent
                              , senderHandleEvent
                              , pData
                              , sizeOfData
                              );
} /* ede_postEvent */




/**
 * An event is posted. It is sent via the explicitly stated sender's port.\n
 *   See other API ede_postEvent() for more details. The only difference between both
 * functions is the way, the port to use is selected.
 *   @return
 * \a true, if function succeeded, else \a false. The event has been sent and will be
 * delivered to the dispatcher only if the function returns \a true.
 *   @param hSender
 * The sender object to use. Has been created before by ede_createSender().
 *   @param idxPort
 * The port to be applied for the event by zero based index. The specified number must not
 * be greater or equal to argument \a noPorts of the constructor call, which yielded \a
 * hSender.
 *   @param kindOfEvent
 * The kind of event. It is an enumeration, which is meaningless to connector element and
 * dispatcher engine.
 *   @param senderHandleEvent
 * The event's handle as used (and issued) by the external integration code system. In the
 * case of CAN communication, this will e.g. be the operating system's handle of a
 * registered CAN message.
 *   @param pData
 * A pointer to some event data. It is delivered to the dispatcher as part of the event.
 *   @param sizeOfData
 * The number of data bytes, i.e., the number of bytes, \a pData points to.
 *   @remark
 * All remarks made for ede_postEvent() hold for this function, too.
 */
bool ede_postEventToPort( ede_eventSender_t * const hSender
                        , unsigned int idxPort
                        , ede_kindOfEvent_t kindOfEvent
                        , ede_senderHandleEvent_t senderHandleEvent
                        , const void *pData
                        , unsigned int sizeOfData
                        )
{
    if(idxPort >= hSender->noPorts)
    {
        EDE_ASSERT(false);
        return false;
    }

    ede_eventSenderPort_t const *pPort = &hSender->portAry[idxPort].port;
    
    /* Check if there's still room in the connector element. */
    ede_externalEvent_t * const pEvent = pPort->allocBuffer(pPort->hInstance, sizeOfData);
    if(pEvent != NULL)
    {
        /* Create the event by coying the data. */
        pEvent->kindOfEvent = kindOfEvent;
        pEvent->senderHandleEvent = senderHandleEvent;
        
        void *pDest = &pEvent->dataAry[0];
        if(pPort->requiresDataByReference)
        {
            /* The port tells us by a pointer returned in field dataAry in the event, where
               to put the payload data. */
            memcpy(&pDest, pDest, sizeof(pDest));
        }
        memcpy(pDest, pData, sizeOfData);

        /* Signal the new event to the receiver. pEvent is invalid from now on. */
        pPort->submitBuffer(pPort->hInstance);
        return true;
    }
    else
    {
        /* Connector element is blocked this time. Count this error event. The counter is
           specified to wrap around in order to facilitate the evaluation (e.g. error rates
           by regular delta calculation). */
        ++ hSender->portAry[idxPort].noErrorsPortBlocked;
        return false;
    }
} /* ede_postEventToPort */




/**
 * Get the number of recorded port-blocked events, i.e. the number of lost events due to an
 * currently unavailable port, e.g. because of an overfull queue.
 *   @return
 * Get the number, which should should rise very slowly or not at all in case of a well
 * designed implementation of the port interface. The counter for port-blocked events wraps
 * at its implementation range. Therefore, the client code can easliy check for an allowed
 * maximum loss rate by regularly evaluating the delta/increment of the returned function
 * value.
 *   @param hSender
 * The sender object, which the query is made for.
 *   @param idxPort
 * The port, which the query is made for, by zero based index. The specified number must
 * not be greater or equal to argument \a noPorts of the constructor call, which yielded \a
 * hSender.
 *   @remark
 * The function can be called at any time from any context, which has read access to the
 * memory, which had been used for construction of the sender object; see argument \a
 * pMemPoolSender of ede_createSender() for details.
 */
ede_atomicUnsignedInt_t ede_getNoSenderPortBlockedEvents( ede_handleSender_t hSender
                                                        , unsigned int idxPort
                                                        )
{
    EDE_ASSERT(idxPort < hSender->noPorts);
    return hSender->portAry[idxPort].noErrorsPortBlocked;

} /* End of ede_getNoSenderPortBlockedEvents */
