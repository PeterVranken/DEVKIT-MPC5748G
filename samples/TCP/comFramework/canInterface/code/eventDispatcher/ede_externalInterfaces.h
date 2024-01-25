#ifndef EDE_EXTERNAL_INTERFACES_INCLUDED
#define EDE_EXTERNAL_INTERFACES_INCLUDED
/**
 * @file ede_externalInterfaces.h
 * Definition of common global interface of component EDE, Event Dispatcher Engine. This
 * file specifies required interfaces but there's no directly related implementation file,
 * which would implement them. Some of the interfaces are intended for implementation in
 * the external code; the integration of the component into a given, real environment will
 * require a suitable, appropriate and specific implementation.
 *
 * Copyright (C) 2021-2024 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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

#include <stdlib.h>
#include "ede_basicDefinitions.h"
#include "ede_eventDispatcherEngine.config.h"

/*
 * Defines
 */

/** Standard call of an interface function, which has one or more arguments. Can be applied
    to make such a call look like a normal function call. */
#define EDE_CALL_INTERFACE_VA_ARGS(iObj, method, ...) \
            ((iObj).method((iObj).hInstance, __VA_ARGS__))

/** Standard call of an interface function, which is optional and which has one or more
    arguments. Can be applied to make such a call look like a normal function call. */
#define EDE_CALL_OPTIONAL_INTERFACE_VA_ARGS(iObj, method, defVal, ...) \
            ((method) != NULL? EDE_CALL_INTERFACE_VA_ARGS(iObj, method, __VA_ARGS__): (defVal))

/** Standard call of an interface function, which has no arguments. Can be applied to make
    such a call look like a normal function call. */
#define EDE_CALL_INTERFACE_NO_ARGS(iObj, method) ((iObj).method((iObj).hInstance))

/** Standard call of an interface function, which is optional and which has no arguments.
    Can be applied to make such a call look like a normal function call. */
#define EDE_CALL_OPTIONAL_INTERFACE_NO_ARGS(iObj, method, defVal) \
            ((method) != NULL? EDE_CALL_INTERFACE_NO_ARGS(iObj, method): (defVal))

/** An initializer expression for a still uninitialized object of type \a
    ede_memoryPool_t. */
#define EDE_INVALID_MEMORY_POOL { .malloc = NULL,                   \
                                  .getNbrOfAvailableBytes = NULL,   \
                                  .getNbrOfAllocatedBytes = NULL,   \
                                  .hInstance = 0u,                  \
                                }

/** An initializer expression for a still uninitialized object of type \a
    ede_mapSenderEvHandleToIdx_t. */
#define EDE_INVALID_EVENT_HANDLE_MAP { .addKeyValuePair = NULL, \
                                       .getValue = NULL,        \
                                       .hInstance = 0u,         \
                                     }

/** An initializer expression for a still uninitialized object of type \a
    ede_eventSenderPort_t. */
#define EDE_INVALID_EVENT_SENDER_PORT { .allocBuffer = NULL,                \
                                        .submitBuffer = NULL,               \
                                        .hInstance = 0u,                    \
                                        .requiresDataByReference = false,   \
                                      }

/** An initializer expression for a still uninitialized object of type \a
    ede_eventReceiverPort_t. */
#define EDE_INVALID_EVENT_RECEIVER_PORT { .readBuffer = NULL,               \
                                          .freeBuffer = NULL,               \
                                          .hInstance = 0u,                  \
                                          .providesDataByReference = false, \
                                        }

/*
 * Global type definitions
 */

/** The interface of a memory pool. The instance of an implementation of such a pool allows
    to allocate chunks of memory with specific properties. It depends only on the
    implementation, what these properties can be, e.g. specific linker memory sections,
    managed access restrictions for different processes, alignment or restrictions in
    concurrent access to the pool. */
typedef struct ede_memoryPool_t
{
    /**
     * A chunk of memory is allocated in a given memory pool.
     *   @return
     * Get the pointer to the reserved chunk of memory of requested size. The address will
     * surely be aligned according to the common machine alignment, see configuration setting
     * #EDE_COMMON_MACHINE_ALIGNMENT.\n
     *   The function returns NULL if the complete available memory is exhausted.
     *   @param hInstance
     * The handle of the memory pool instance, which should deliver the requested memory.
     * The value of field \a hInstance from the same interface object will be passed in.
     *   @param sizeOfChunk
     * The number of requested bytes.
     *   @remark
     * The memory interface definition doesn't contain a counterpart for malloc(), e.g.,
     * free(). Even if a given implementation knows a free operation it would matter to the
     * event dispatcher environment. All of its code follows the concept of one-time memory
     * allocation and pooling in case of object reuse. There's no need for ever returning
     * some memory. (Which is a typical embedded requirement.)
     */
    void * (*malloc)(uintptr_t hInstance, unsigned int sizeOfChunk);

    /**
     * Get the number of memory bytes left in the given pool for allocation. A chunk
     * successfully requested with malloc() cannot exceed this size.
     *   @return
     * Get the number of bytes.
     *   @param hInstance
     * The handle of the memory pool, which the request relates to. The value of field \a
     * hInstance from the same interface object will be passed in.
     *   @remark
     * This method is optional. It is meant mainly for diagnosis purposes. May be set to
     * NULL if not supported by an implementation.
     */
    unsigned int (*getNbrOfAvailableBytes)(uintptr_t hInstance);

    /**
     * Diagnostic interface: Get the number of memory bytes allocated so far. Due to alignment
     * operations this can be more than the sum of all requested chunk sizes.
     *   @return
     * Get the number of bytes.
     *   @param hInstance
     * The handle of the memory pool, which the request relates to. The value of field \a
     * hInstance from the same interface object will be passed in.
     *   @remark
     * This method is optional. It is meant mainly for diagnosis purposes. May be set to
     * NULL if not supported by an implementation.
     */
    unsigned int (*getNbrOfAllocatedBytes)(uintptr_t hInstance);

    /** An actual implementation of the memory pool will require some specific data.
        This field provides access to this data.\n
          This value is passed as first argument to the methods specified in this
        interface.\n
          The meaning of \a hInstance is transparent to the interface definition but it'll
        likely by either an index into an array of instances or a pointer to an instance.
        The chosen type allows both and the implementation will do the appropriate type
        cast. */
    uintptr_t hInstance;

} ede_memoryPool_t;


/** The interface of a map, which associates the sender's identification of an event with
    the internally used zero based index. The implementation of the map is done externally
    as part of the integration, here we just specify the interface of the required map.\n
      The map is used for lookup of two kinds of indexes:\n
      1. Use case mapping external events to registered event sources:\n
      The map's function addKeyValuePair() is internally called by the dispatcher engine
    on each registration of an event source, i.e., ede_registerEventSource(). This way, the
    map is built up.\n
      The map's function getValue() is internally called by the dispatcher engine on
    reception of an external event in order to associate the received event data with the
    causing, registered event source.\n
      2. Use case mapping external events to a sender's port:\n
    The map associates an abstract event handle with a sender's port (addressed by index),
    which the event is posted to. Using an externally defined map to decide the port to
    use, allows the external code to control/define the communication structure. (The
    generic implementation of the event dispatcher does not make any assumption about the
    communication paths.) In this use case, only the map lookup operation is used, in the
    operation to post an event, i.e., ede_postEvent(). The implementation of sender and
    dispatcher don't take care of building up the map. */
typedef struct ede_mapSenderEvHandleToIdx_t
{
    /**
     * This function helps to prepare the map.\n
     *   1. Use case mapping external events to registered event sources:\n
     *   A single association as appears in each event registration is added to the map.
     * This function is called once per registered event source as sub-routine of
     * ede_registerEventSource().\n
     *   May be NULL. In many environments, the required map is trivial (e.g. the identity)
     * or known (and generated as ROM table) and no code is required to built-up the map.\n
     *   2. Use case mapping external events to a sender's port:\n
     *   The function is currently not called by the dispatcher engine or sender
     * implementation. The integration code is in charge of providing the map contents and
     * it may or may not make use of this function to buildup the map.\n
     *   May be NULL to indicate that operation is not required.\n
     *   @return
     * The function will return \a true, if the new key, value pair could be considered.
     * The implementation of the map may be limited by size or otherwise. If the map entry
     * could not be made the external function may return \a false and, later at run-time,
     * the sender or dispatcher engine will ignore all events, which origin from the
     * related event source.
     *   @param hInstance
     * This is the identification of the map instance to use. The data type uintptr_t is
     * such that the implementation of the map can hide an index into an array of objects
     * or a pointer to an object behind this value. See field \a hInstance, too.\n
     *   1. Use case mapping external events to registered event sources:\n
     *   Each dispatcher system has its own index space for event sources and will apply a
     * dedicated map.\n
     *   2. Use case mapping external events to a sender's port:\n
     *   Each sender has its own index space for its individual ports and it'll use a
     * dedicated, related map instance.
     *   @param kindOfEvent
     * An event is characterized by its kind and by the sender's handle. The meaning of
     * both values is transparent to sender and dispatcher engine. They will be defined by
     * the integrating environment. A common use case would for example be: Kind is "CAN Rx
     * event" and sender handle is CAN message ID.
     *   @param senderHandleEvent
     * See \a kindOfEvent.
     *   @param mapValue
     * The value of the pair to add to the map. This value needs to be returned by
     * getValue() if the same event characterization is provided.\n
     *   Use cases: It's either the zero based index of a registered event source or the
     * zero based index of a sender's port.
     *   @remark
     * This function is called in the system initialization phase, i.e., in a single
     * threaded, still race condition free context.
     */
    bool (*addKeyValuePair)( uintptr_t hInstance
                           , ede_kindOfEvent_t kindOfEvent
                           , ede_senderHandleEvent_t senderHandleEvent
                           , unsigned int mapValue
                           );

    /**
     * The map lookup operation. The index associated with an external event is queried.\n
     *   1. Use case mapping external events to registered event sources:\n
     *   The requested index is that of an event source as internally used in the
     * dispatcher system. The map query function is called as sub-routine of the
     * dispatching operation, ede_dispatcherMain().\n
     *   2. Use case mapping external events to a sender's port:\n
     *   The requested index is that of a port of the querying sender. The map query
     * function is called as sub-routine of sending an event, ede_postEvent().\n
     *   Must not be NULL.
     *   @return
     * Normally, the requested index is returned by reference (see below) and the function
     * result is \a true. If the function doesn't find a suitable association it will
     * return \a false and the related event is lost.
     *   @param hInstance
     * This is the identification of the map instance to use. The data type uintptr_t is
     * such that the implementation of the map can hide an index into an array of objects
     * or a pointer to an object behind this value. See field \a hInstance, too.\n
     *   1. Use case mapping external events to registered event sources:\n
     *   Each dispatcher has its own index space for event sources and will apply a
     * dedicated map.\n
     *   2. Use case mapping external events to a sender's port:\n
     *   Each sender has its own index space for its individual ports and it'll use a
     * dedicated, related map instance.
     *   @param pValue
     * The result of the lookup operation is returned by reference. If the function returns
     * \a false then it may ignore this parameter.
     *   @param kindOfEvent
     * First element of characterizing the event source under progress. See argument of
     * same name of addKeyValuePair() for more details.
     *   @param senderHandleEvent
     * Second element of characterizing the event source under progress. See argument of
     * same name of addKeyValuePair() for more details.
     *   @remark
     * The external implementation of the map function needs to be reentrant only with
     * respect to different map instances. There won't be concurrent calls for one and the
     * same instance.
     */
    bool (*getValue)( uintptr_t hInstance
                    , unsigned int * pValue
                    , ede_kindOfEvent_t kindOfEvent
                    , ede_senderHandleEvent_t senderHandleEvent
                    );

    /** An actual implementation of the map will require some specific data. This field
        provides access to this data.\n
          This value is passed as first argument to the functions specified in this
        interface.\n
          The meaning of \a hInstance is transparent to the interface definition but it'll
        likely by either an index into an array of map instances or a pointer to a map
        instance. The chosen type allows both and the implementation will do the
        appropriate type cast. */
    uintptr_t hInstance;

} ede_mapSenderEvHandleToIdx_t;


/** An event, which can be sent via the below specified port objects \ref
    ede_eventSenderPort_t and \ref ede_eventReceiverPort_t. */
typedef struct ede_externalEvent_t
{
    /** The kind of event. This value is set by the producer of the data element.\n
          In case of external events the producer is the integration code. Now
        "kindOfEvent" is out of scope of the dispatcher engine. The integration code will
        decide, which kinds of event exist. Only a few values are reserved to the
        dispatcher engine implementation, see #EDE_EV_KIND_LAST for details. */
    ede_kindOfEvent_t kindOfEvent;

    /** The event's handle as used (and issued) by the sender. The handle is meaningless to
        the event sender and event receiver mechanisms besides the fact that a mapping can
        be specified, which maps this handle to the handle internally used by the event
        dispatcher engine at the receiver side. */
    ede_senderHandleEvent_t senderHandleEvent;

    /** The data contents of the event. Although it formally holds values of type uintptr_t
        it effectively is a memory chunk of fixed, user-specified length, that can vary
        between 0 and any number of bytes.\n
          This field is a flexible array member. The alignment of the memory chunk is the
        alignment suitable for both, a (void) pointer and an (un)signed int. This should be
        fine on all existing platforms to avoid misalignments of event data. Even a double
        or long long will normally be alright; these data types would likely cause problems
        only on a system with 32 Bit address bus and 64 data bus width, which can be
        considered a rather extraordinary architecture.\n
          For C11 targets the alignment is as explicitly configured by setting
        #EDE_COMMON_MACHINE_ALIGNMENT.\n
          The flexible array member must not be touched if the user specified a length of
        zero. */
#if defined(_STDC_VERSION_C17_C11)
    _Alignas(EDE_COMMON_MACHINE_ALIGNMENT) uint8_t dataAry[];
#elif defined(__GNUC__) ||  defined(__arm__)
    uint8_t dataAry[] __attribute__((aligned(EDE_COMMON_MACHINE_ALIGNMENT)));
#elif defined(_STDC_VERSION_C99)
    uintptr_t dataAry[];
#else
# error Flexible array members are not supported by your compiler
#endif
} ede_externalEvent_t;

_Static_assert( offsetof(ede_externalEvent_t, dataAry) == sizeof(ede_externalEvent_t)
                &&  sizeof(ede_externalEvent_t) % EDE_COMMON_MACHINE_ALIGNMENT == 0u
              , "Bad definition of properly aligned event type"
              );


/** The sender side interface of a connection element, which connects a sender's output
    port with a dispatcher's input port. This interface allows a sender to post an event.
    The natural implementation of the connection element is a queue and this interface
    would provide access to the end of the queue.\n
      The characteristics of the connection element has a principal impact on the behavior
    of the event dispatching mechanism and will determine much of the realizable use cases.
    The intended use case of a CAN interface will typically require that sender and
    dispatcher can reside in different execution contexts and that they can use their
    respective interfaces without fearing race conditions. */
typedef struct ede_eventSenderPort_t
{
    /**
     * Allocate buffer space for the event to post. The process of sending an event means
     * to first allocate a buffer, then fill it and finally submit it. Sending several
     * events leads to an alternating use of this method and submitBuffer(). The
     * implementation is not obliged to support more complex use cases, in particular, it
     * doesn't need to implement the allocation of several buffers before submission of the
     * first one. It may assume strictly alternating use of both methods and therefore
     * reuse one and the same buffer space for all cycles.
     *   @return
     * The returned pointer points to some memory space, capable of holding an event with
     * \a sizeOfPayload Bytes of payload, i.e., at least (sizeof(ede_externalEvent_t) + \a
     * sizeOfPayload) Byte of space.\n
     *   The buffer is reserved to the caller until the subsequent use of the other method
     * submitBuffer().
     *   @param hInstance
     * Each sender port has its own, dedicated connection element instance. This handle is
     * the identification of the port instance to use.
     *   @param sizeOfPayload
     * The minimum capacity in Byte of the event's payload area the returned event needs to
     * have, i.e., the capacity of field \a dataAry[] in Byte.
     */
    ede_externalEvent_t * (*allocBuffer)(uintptr_t hInstance, unsigned int sizeOfPayload);

    /**
     * Submit the eldest buffer, which had been reserved with allocBuffer() and which had
     * not been submitted yet.
     *   @param hInstance
     * Each sender port has its own, dedicated connection element instance. This handle is
     * the identification of the port instance to use.
     */
    void (*submitBuffer)(uintptr_t hInstance);

    /** An actual implementation of the connection element will require some specific data.
        This field provides access to this data or at least to that portion of the data,
        which is required for submitting events.\n
          This value is passed as first argument to the methods specified in this
        interface.\n
          The meaning of \a hInstance is transparent to the interface definition but it'll
        likely by either an index into an array of instances or a pointer to an instance.
        The chosen type allows both and the implementation will do the appropriate type
        cast. */
    uintptr_t hInstance;

    /**
     * Static property of a port object: It may expect its payload data either as
     * sequence of bytes in field \a dataAry of the allocated event or by reference, in
     * which case, and on exit from allocBuffer(), the first \a n bytes of field \a dataAry
     * contain a pointer to where the payload is expected. \a n is sizeof(void*),
     * which may vary platform dependent.\n
     *   The property is static, i.e., decided at port creation time and thus not dependent
     * on the events it may process; either all sent events are by value or all sent events
     * are by reference.\n
     *   The value is \a true if the port expects its event data by reference and \a false
     * if the delivered data is expected in \a dataAry[],
     */
    bool requiresDataByReference;

} ede_eventSenderPort_t;



/** The dispatcher side interface of a connection element, which connects a sender's output
    port with a dispatcher's input port. This interface allows a dispatcher to fetch a
    previously sent event.\n
      The natural implementation of the connection element is a queue and this interface
    would provide access to the head of the queue.\n
      The characteristics of the connection element has a principal impact on the behavior
    of the event dispatching mechanism and will determine much of the realizable use cases.
    The intended use case of a CAN interface will typically require that sender and
    dispatcher can reside in different execution contexts and that they can use their
    respective interfaces without fearing race conditions. */
typedef struct ede_eventReceiverPort_t
{
    /**
     * Try to read an event from the connection element.
     *   @return
     * The function returns a pointer to a previously sent event. Normally, this will be
     * the eldest not yet fetched event but this is not a technical must. It is basically
     * allowed to reorder elements but this will have a significant impact on the behavior
     * of the event dispatching mechanism and depent on the intended use cases.\n
     *   The data, the returned pointer points to shall be valid for reading until the
     * other method freeBuffer() is invoked. The implementation may assume, that readBuffer()
     * and freeBuffer() are called strictly alternatingly; it doesn't need to allow fetching
     * several buffers before freeing the first of them.\n
     *   The method returns NULL if there is currently no event to deliver. In this case
     * freeBuffer() must not be used later.
     *   @param hInstance
     * Each receiver port has its own, dedicated connection element instance. This handle is
     * the identification of the port instance to use.
     *   @param pSizeOfPayload
     * The method will put the size of the payload of the returned event into * \a
     * pSizeOfPayload. The size is the number of bytes, which can be accessed through the
     * event's field \a dataAry[].\n
     *   If providesDataByReference is \a false then * \a pSizeOfPayload is the
     * number of payload bytes in \a dataAry[] otherwise it is the number of data bytes the
     * pointer points to, which is found in the first bytes of \a dataAry[].
     *   @note
     * If the event data is delivered by reference then no statement can be made about the
     * alignment of the data; this fully depends on the given port implementation. \a
     * dataAry is guaranteed to have the alignment #EDE_COMMON_MACHINE_ALIGNMENT and,
     * consequently, the reference itself can be safely read but no promise can be made for
     * the address it points to.
     */
    const ede_externalEvent_t * (*readBuffer)( uintptr_t hInstance
                                             , unsigned int *pSizeOfPayload
                                             );

    /**
     * Return the eldest buffer, which had been fetched with readBuffer() and which had
     * not been returned yet.
     *   @param hInstance
     * Each receiver port has its own, dedicated connection element instance. This handle is
     * the identification of the port instance to use.
     */
    void (*freeBuffer)(uintptr_t hInstance);

    /** An actual implementation of the connection element will require some specific data.
        This field provides access to this data or at least to that portion of the data,
        which is required for fetching events.\n
          This value is passed as first argument to the methods specified in this
        interface.\n
          The meaning of \a hInstance is transparent to the interface definition but it'll
        likely by either an index into an array of instances or a pointer to an instance.
        The chosen type allows both and the implementation will do the appropriate type
        cast. */
    uintptr_t hInstance;

    /**
     * Static property of a port object: It may deliver the payload data either as sequence
     * of bytes in field \a dataAry of the delivered event or by reference, in which case
     * the first \a n bytes of dataAry contain a pointer to the actual payload. \a n is
     * sizeof(const void*), which may vary platform dependent.\n
     *   The property is static, i.e., decided at port creation time and thus not dependent
     * on the events it delivers; either all events are by value or all delivered events
     * are by reference.
     *   The value is \a true if the port delivers its event data by reference and \a false
     * if the delivered data is found in \a dataAry[],
     */
    bool providesDataByReference;

} ede_eventReceiverPort_t;



/*
 * Global data declarations
 */


/*
 * Global prototypes
 */



/*
 * Global inline functions
 */


#endif  /* EDE_EXTERNAL_INTERFACES_INCLUDED */

