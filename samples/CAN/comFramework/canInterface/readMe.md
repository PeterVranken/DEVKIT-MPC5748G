This folder contains the implementation of the comFramework CAN interface and
some sample integrations on true platforms.

Please refer to the project Wiki, the documentation of the CAN interface
and the readMe files of the available sample integrations for details:

General Wiki pages:

-   [SourceForge project home](<https://sourceforge.net/p/comframe/wiki/Home/>)
-   [SourceForge, installation](<https://sourceforge.net/p/comframe/wiki/Installation/>)

Root documentation of the CAN interface:

-   [SourceForge, CAN interface - concept and usage](<https://sourceforge.net/p/comframe/wiki/The%20CAN%20Interface/>)
-   [SourceForge, CAN interface - Doxygen pages](https://svn.code.sf.net/p/comframe/code/canInterface/trunk/components/canInterface/doc/doxygen/html/index.html)
-   [CAN interface, readMe](<https://svn.code.sf.net/p/comframe/code/canInterface/trunk/components/canInterface/readMe.html>)
-   [**CAN interface, what's new**](<https://svn.code.sf.net/p/comframe/code/canInterface/trunk/components/canInterface/readMe.html#whats-new>)

Sample integrations:

-   [Sample integration for Windows](<https://svn.code.sf.net/p/comframe/code/canInterface/trunk/components/winSampleIntegration/readMe.html>)
-   [Sample integration on Arduino](<https://svn.code.sf.net/p/comframe/code/canInterface/trunk/components/arduinoSampleIntegration/readMe.html>)
-   [Sample integration with MathWorks Embedded Coder on Arduino](<https://svn.code.sf.net/p/comframe/code/canInterface/trunk/components/arduinoSampleIntegrationEmbeddedCoder/readMe.html>)
-   [Sample integration with POSIX multi-threading platform](<https://svn.code.sf.net/p/comframe/code/canInterface/trunk/components/winTestMT/readMe.html>)
-   [Sample integration on DEVKIT-MPC5748G](<https://github.com/PeterVranken/DEVKIT-MPC5748G/tree/master/samples/CAN>)

# The CAN interface #

This is the implementation of the comFramework CAN interface engine. There
are no other files, particularly no build scripts as the interface engine
is intended for integration into a real project as source code.

Please refer to the project Wiki with the documentation of the CAN interface
and the readMe files of the available sample integrations for details:

Most relevant Wiki pages:

-   [SourceForge project home](<https://sourceforge.net/p/comframe/wiki/Home/>)
-   [SourceForge, installation](<https://sourceforge.net/p/comframe/wiki/Installation/>)
-   [SourceForge, CAN interface - concept and usage](<https://sourceforge.net/p/comframe/wiki/The%20CAN%20Interface/>)
-   [SourceForge, CAN interface - Doxygen pages](https://svn.code.sf.net/p/comframe/code/canInterface/trunk/components/canInterface/doc/doxygen/html/index.html)

Sample integrations:

-   [Sample integration for Windows](<https://svn.code.sf.net/p/comframe/code/canInterface/trunk/components/winSampleIntegration/readMe.html>)
-   [Sample integration on Arduino](<https://svn.code.sf.net/p/comframe/code/canInterface/trunk/components/arduinoSampleIntegration/readMe.html>)
-   [Sample integration with MathWorks Embedded Coder on Arduino](<https://svn.code.sf.net/p/comframe/code/canInterface/trunk/components/arduinoSampleIntegrationEmbeddedCoder/readMe.html>)
-   [Sample integration with POSIX multi-threading platform](<https://svn.code.sf.net/p/comframe/code/canInterface/trunk/components/winTestMT/readMe.html>)

# What's new #

## Release 1.6 ##

Under development:

- Architectural redesign
  - Concept of allocating objects to specific, well-defined memories
  - Support of memory protected environments
  - Better support of different environments with respect to ISR, task,
    process, multi-core architectures 
- Little functional changes

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
