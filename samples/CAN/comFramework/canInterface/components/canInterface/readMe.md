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

## Release 1.4 ##

New commonly usable templates have been added to the project-independent
library template file codeGenC.stg: bitMask and bitMaskCalc to provide bit
masks for typical signal operations.

The documentation has been improved and there are some minor bug
fixes of the sample code and the makefiles

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