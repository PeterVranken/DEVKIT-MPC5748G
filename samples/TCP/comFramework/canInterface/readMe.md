# The CAN interface #

This is the implementation of the comFramework CAN interface engine. 

Folder `code` contains the source code of the engine. There are no other
files, particularly no build scripts as the interface engine is intended
for integration into a real project as source code. The files from this
folder are typically added to an existing build project for the aimed
target platform.

Folder `sampleIntegrations` contains source code and build scripts for
several demo applications of the CAN interface. The reproduction of the
build requires a particular build tool chain; out of the box we use
Arduino 1.8 and MinGW GCC for Windows.

Please refer to the project Wiki with the documentation of the CAN interface
and the readMe files of the available sample integrations for details:

Most relevant Wiki pages:

-   [SourceForge project home](https://sourceforge.net/p/comframe/wiki/Home/)
-   [SourceForge, installation](https://sourceforge.net/p/comframe/wiki/Installation/)
-   [SourceForge, CAN interface - concept and usage](https://sourceforge.net/p/comframe/wiki/The%20CAN%20Interface/)
-   [SourceForge, CAN interface - Doxygen pages](https://svn.code.sf.net/p/comframe/code/canInterface/trunk/doc/doxygen/html/index.html)

Sample integrations:

-   [Sample integration for Windows](https://svn.code.sf.net/p/comframe/code/canInterface/trunk/sampleIntegrations/winSampleIntegration/readMe.html)
-   [Sample integration on Arduino](https://svn.code.sf.net/p/comframe/code/canInterface/trunk/sampleIntegrations/arduinoSampleIntegration/readMe.html)
-   [Sample integration with MathWorks Embedded Coder on Arduino](https://svn.code.sf.net/p/comframe/code/canInterface/trunk/sampleIntegrations/arduinoSampleIntegrationEmbeddedCoder/readMe.html)
-   [Sample integration with POSIX multi-threading platform](https://svn.code.sf.net/p/comframe/code/canInterface/trunk/sampleIntegrations/winTestMT/readMe.html)
-   [Sample integration on DEVKIT-MPC5748G](https://github.com/PeterVranken/DEVKIT-MPC5748G/tree/master/samples/CAN)

# What's new #

## Release 2.0 ##

An redesign of the software's class model has been made. It targets at
enlarging the number of supported integration use cases. It's now straight
forward to integrate into fully memory protected or managed systems or to
operated closer to the CAN hardware, with leaner software buffering
strategies.

Let's first have a look at revision 1.x. There is a single global (and
implicit) instance of the whole. It has any number of event dispatchers
and each dispatcher has one event queue and one handle map, which
associates the external events got via the queue with the internally
registered event sources.

In revision 2.0, the "whole" thing of 1.x becomes the new dispatcher
system. Any number of such systems can be created. A system has any number
of dispatchers.

Revision 2.0 introduces interfaces and implementations of those. A
dispatcher no longer has an event queue. Instead, it now has any number of
event receiver ports and these ports can connect to an arbitrary
implementation of the event receiver interface.

The additional definition of an event sender interface allows the
implementation of "connectors", which have both types of ports: Events can
be submitted via the connector's sender port and the dispatcher can
consume the submitted events if one of its ports is connected to the
connector's receiver port. The event queue implementation known from
revision 1.x is now available as such a connector object.

The new sender object has a sender port and provides an API, which
strongly resembles the event posting API of the 1.x dispatcher: Creating a
sender, a connector-queue and a dispatcher and connecting them in chain
yields a configuration, which is compatible with the monolithic construct
of revision 1.x.

The malloc API of 1.x has been substituted by a memory pool interface. The
different objects can be created from the same or from different memory
pool instances - which is the concept to support memory protected or
managed systems.

Of course, to facilitate the code migration, the malloc API implementation
known from 1.x is now available as an implementation of the memory pool
interface.

Handle mapping has always been a major issue in integrating the CAN
interface. Already 1.x had used an interface to connect to a map instance
in order to allow arbitrary mapping strategies. This has been even more
generalized and a number of map implementations is provided, which should
cover all existing use cases.

## Release 1.5 ##

A new, abstract event source has been offered for the dispatcher
mechanism. It can be applied for posting events, which are not directly
related to a particular CAN bus or frame. Use case are events from some
application code, which relate somehow to the CAN communication, but which
are not as prototypical as e.g. a frame Rx/Tx or bus-off event.

Note, this extension means an incompatible change of the existing API
cde_initModule(). Existing code won't compile.

Better support of CAN FD by a new queue implementation. The new
implementation can save a significant amount of RAM if events of varying
size are processed. The elder implementation allocated a fixed amount of
memory for each event, which means a waste of memory particularly for CAN
FD, where the majority of frames still have up to eight Byte but a few of
64 Byte need to be handled, too.

Major bug fix: The CAN interface used to represent CAN IDs as an ordinary
integer number, disregarding whether it were a standard 11 Bit or an
extended 29 Bit ID. Now it uses a struct with two fields to store numeric
value and kind of ID independently.

Note, this repair means an incompatible API change of the CAN interface
engine. Existing code won't compile. Moreover, the templates of typical
comFramework client projects will require adaptation to serve the new data
type for CAN IDs.

The sample code for Windows has been migrated to a recent revision of
MinGW GCC (8.1.0, 32 Bit and 64 Bit).

There are some minor bug fixes of the sample code and the makefiles.

## Release 1.4 ##

New commonly usable templates have been added to the project-independent
library template file codeGenC.stg: bitMask and bitMaskCalc to provide bit
masks for typical signal operations.

The documentation has been improved and there are some minor bug
fixes of the sample code and the makefiles.

## Release 1.3 ##

The implementation of the CAN interface engine (also referred to as
dispatcher engine) makes use of a new implementation of the thread-safe
dispatcher queue. The API is unchanged and existing code building on 1.2.1
will be compilable without modifications and it'll show unchanged
behavior.

The new queue no longer makes any restrictions on thread priorities.
It is a lock-free implementation that can run in any multi-threaded or
multi-core environment. The elder implementation required that the a CAN
event notifying execution context (a CAN interrupt usually) had a higher
priority than and could never be preempted by the execution context of the
CAN consuming APSW code. This is the normal situation on any single-core
RTOS platform but not beyond. Now, the sources of CAN events and the
receiving APSW tasks can run on different cores or in different threads of
arbitrary priority and with arbitrary scheduling scheme.

A new test application runs the CAN interface in a POSIX multi-threading
environment. Dispatcher queues connect several tasks, which can all
preempt one another and which are not restricted to run on a single core.

The new test application is at the same time a new sample integration,
which demonstrates how to design a different, more conventional
architecture of the CAN interface and how to let the code generator
generate CRC based end-to-end protection functions for CAN frames.

## Release 1.2.1 ##

The thread safe implementation of the event queue has been supported by a
memory barrier between data manipulation and acknowledge. This might be
necessary on particular platforms. A platform dependent #define becomes
element of the configuration.

Bug fix: All sample integrations' templates had generated the conversion
macros binary-value-to-world-value and vice versa only for signals, which
are either sent or received by the node. This was inconsistent with the
generation of signal initialization code, which had been generated for all
the signals of a frame. The initialization code may depend on the
conversion macros. Now, the templates generate the conversion macros for
all signals, even those, which are not transmitted by the node.

The interface descriptions for Embedded Coder and TargetLink generated by
the samples will now list all signals of a transmitted frame. So far, only
sent and received signals had been listed. Although this is basically
correct was it found to be hindering because many real network databases
don't specify senders and receivers properly for all frames and signals.

Bug fix: A misplaced \<endif> was found in the sample integrations'
templates. The #define's that make minimum and maximum of a signal public
were only generated for scaled signals. This was not by intention, minimum
and maximum are as useful for unscaled integers. Now, the minimum and
maximum values are available as #define for all signals.

Bug fix: The same misplaced \<endif> let to unwanted suppression of parts
of the Embedded Coder interface. For unscaled integers was the chosen
storage class mechanism not generated. This affects only the Arduino
Embedded Coder sample.
