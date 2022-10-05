# Windows Multi-threading test

## Scope

This sample integration of the CAN interface demonstrates some new
aspects - new with respect to the other, elder sample integrations:

-   The architecture of the CAN interface is different and much more
    conventional in comparison to the elder samples. The code generator no
    longer produces all the individual message related callbacks to define
    the different message timing patterns. Instead, it shapes large data
    tables, an entry for each processed message, with all information about
    the messages. There's a hand-coded callback for each of the supported
    timing patterns and the same callback is applied to all messages that
    expose the given timing pattern. Of course, the implementation of the
    callbacks makes use of the information in the data tables to respect the
    message individual settings and parameters. This concept had already been
    outlined in the project's [Wiki pages](https://sourceforge.net/p/comframe/wiki/The%20CAN%20Interface/#a-more-common-architecture) (or [see here](https://sourceforge.net/p/comframe/wiki/Attributes%20in%20the%20network%20database/#typical-code-architecture))
-   The application implements end-to-end protection. This is a variant of
    the message checksum protection demonstrated in the other sample
    integrations. The previously shown CRC protection operates directly on
    the bytes of the packed messages and is necessarily part of the CAN
    interface - the APSW doesn't have access to message bytes. _End-to-end_
    stresses that the protection goes till the interface with the APSW and
    includes failures of the CAN interface engine itself, e.g. because of
    race conditions or wrong pack or unpack code. This can be achieved by
    computing the checksum across the bytes of the unpacked signal values
    directly taken from the CAN API with the APSW. Our code generator
    produces a set of functions to do so. For inbound messages the data is
    validated and outbound messages get their appropriate CRC checksum prior
    to transmission

## Build and run the test application

The sample code comes along with all source files and build scripts
(makefile based). GNU GCC and GNU make 3.81 should be in the system
search path, then the build command would be (Windows, other systems
accordingly):

    cd <...>\comFramework\canInterface\sampleIntegrations\winTestMT
    make -s build

To start the sample application you may type:

    make run

Please try also: `make help` and `make run ARG=-h`

Note, on Windows systems you will need the MinGW port of make, not the
Cygwin port. Many GCC distributions contain both variants, so it depends
on your system search path, which one is run. Or consider typing
`mingw32-make build`; in a Windows GCC distribution this should be a safe
reference to the right implementation of make. The Cygwin variant uses
another interface to the underlying shell and this interface is not
compatible with our makefiles.

Note, by default the compilation is done in debug mode, which is really
essential for this test application. Since most of the test results are
checked by assertion it would be quite useless to run it in production
code compilation.

### Pthreads and C11 atomic support required

The multi-threading of the application builds on the pthreads library and
on C11's `stdatomic`. Not all of the GCC distributions support these
packages but both are a prerequisite of a successful build.

### Non standard DLLs

To run the built application the pthreads and the C atomic library need to
be on the system search path. Under Windows, and if it isn't, you won't
even get an error message. The application just returns immediately with a
non zero return code. This may affect those, who don't want to install
GCC and build the sample but just want to run the precompiled executable.

On an Windows 7 system and using MinGW32 GCC 5.3 the following DLLs are
required and need to be on the search path (the standard Windows DLLs are
not mentioned here):

    <...>\MinGW-5.3.0\bin\pthreadGC-3.dll
    <...>\MinGW-5.3.0\bin\libgcc_s_dw2-1.dll
    <...>\MinGW-5.3.0\bin\libatomic-1.dll

On an Windows 10 system and using mingw64 GCC 8.1.0, no additional DLLs
were needed; the generated executable ran out of the box. Maybe all
required DLLs belong to the Windows standard set.

## Design of the test application

There is a folder named `APSW` but you won't find much of application
functionality. The whole application is aimed a test of the CAN interface
in the first place and all it visibly does is printing some test results.
By default, the application is running infinitely and will regularly print
some statistics about completed cycles and recognized errors.

Even if there's barely application software code dealing with the CAN
payload, the architecture of the test application follows the conventional
structure. It would be straight forward to integrate some real functional
code at the intended code locations. This has been achieved by strictly
separating the test application in two parts.

One part is an emulation of a real platform. The interface of the platform
emulation is designed much like a real embedded Basic Software looks like.
The APSW links to the operating system by registering some task functions,
which are then regularly invoked by the operating system's scheduler.
Similarly, CAN reception events are asynchronously reported through a
callback, that has to be registered by the APSW, too.

The other part is the integration of the CAN interface and the APSW on
top. The CAN interface consists of the few given source files of the
interface engine, the in this case hand-coded callbacks demanded by the
engine and the CAN data tables that are auto-coded from the information in
the network databases.

### Basic Software emulation

The operating system emulation builds on an implementation of the POSIX
multi-threading standard. (Tests have been run only under Windows but
compilation and execution should be possible under Linux, too.) This
threading interface is not like a typical embedded RTOS. Threads will
mutually preempt each other and they can run coincidental on different
cores. All of this is permitted when using the CAN interface in
revision 1.3 or newer. Elder revision made some restrictions on task
priority relations.

The operating system has a number of regular, cyclic tasks, which are
spinning once a Millisecond, every 10 ms, every 100 ms and once a second.
The according, registered APSW task function is invoked in every cycle.
Another asynchronous, cyclically executed task is used internally by the OS
emulation. It is spinning in a 1 ms cycle.

The internal 1 ms task implements a state machine that figures out for
each time tick, which inbound CAN messages would arrive. (The transmission
timing patterns of all messages are known by configuration.) The reception
of all of these messages is simulated. The message contents are randomly
chosen and reported in the application CAN log file. The
on-CAN-reception-callback, which had been registered by the APSW, is
invoked with the message information. This is an asynchronous, preempting
call to the APSW, much like the CAN interrupt in a real embedded
environment.

The OS emulation offers an API to the APSW to send a CAN message (see
`ose_operatingSystemEmulation.c`, `ose_sendCanFrame`). The simulation of
CAN sending double-checks the message contents (it checks for the correct
CRC checksum) and reports the message send event in the application CAN log.
These actions are intentionally not done directly in the API function.
This function is called by one of the APSW tasks and it is executed in the
APSW task's context. The described actions are however done in the OS'
internal 1 ms task. The principal reason is that we want to test the CAN
interface implementation as much as possible and communication between the
invoking APSW tasks and the OS internal task is implemented by a number of
dispatcher objects. Their queues cross the task boundaries between APSW
and OS and become part of the test. The secondary reason for this
architecture is that it permits using one and the same log file for CAN Rx
and CAN Tx events in the OS emulation.

The configuration of the OS is designed as data tables,
which are declared by the OS code as `extern const` and have to be defined
in the APSW. We let our code generation auto-code these tables. See
`ose_operatingSystemEmulation.h`, `ose_receivedCanFrameAry` and
`ose_sentCanFrameAry`.

The analogy with a real embedded Basic Software has its limits. Our test
application needs to do the E2E encoding for simulated Rx messages and the
E2E validation for Tx messages, where a real OS wouldn't do any processing of
the message contents. This is implemented by some test specific
configuration items; Rx messages need for example a function pointer to the
message specific function to randomly fill the message and E2E protect it.

An APSW will always use our dispatcher objects to connect the
asynchronous CAN Rx callback with its functional tasks and so does the
APSW code in this sample. This leads to an architecture of the test
application where each APSW task is connected to the internal OS task
through a pair of dispatcher queues, one for each direction. Rx messages go
through these queues from OS to APSW and Tx messages go through these queues
from APSW to OS. E2E protection and E2E validation are always done at the
other end of a dispatcher queue and the entire data handling of the CAN
interface engine is in between and thus checked by the E2E code. This is
the core of the testing concept. No errors are randomly, purposely
injected and there must never occur an E2E validation error.

#### Folder code/osEmulation

This folder and its sub-folder contain the files that implement the
operating system emulation. When looking at the test application with the
view of a sample integration of the CAN interface then this folder is out
of scope -- with one exception:

The auto-coded files, which contain the generated configuration data
tables, are placed in this folder, too, and such configuration tables are
not uncommon in a real embedded environment. See module
`ose_dataTables.c`.

### APSW and CAN Interface integration ###

As said, the APSW barely has real functionality. The intention is to just
exchange a lot of random messages under E2E protection in order to test the
CAN interface. Large and complex but meaningless CAN network databases
support this idea. Message and signal definitions in these files are
randomly generated by a
[GNU Octave script](https://svn.code.sf.net/p/comframe/code/canInterface/branches/generateRandomDbc).
The complexity of the random message specification is rather higher than for
most real existing network databases, which tend to avoid signals across
byte boundaries as much as possible. This is beneficial for testing.

The transmission timing patterns of the messages and the way these patterns
are specified by attributes in the network databases is identical to the
other sample integrations, see e.g.
<https://svn.code.sf.net/p/comframe/code/canInterface/trunk/sampleIntegrations/winSampleIntegration/doc/specificationNetworkDatabase.html#attributes>.

#### Folder code/APSW

This folder contains the files of the APSW. The structure is close to what
a real embedded application could look like and it can be considered
sample integration code.

Module `apt_applicationTask.c` registers the APSW tasks at the operating
system and initializes the CAN interface. All messages are registered at the
engine and the timer logic is initialized (e.g. for Rx timeout recognition
and Tx send time control). The callbacks required by the CAN interface
engine are implemented in this module, too.

The E2E protection and validation of messages -- a dedicated set of functions
for each message -- is implemented in module `e2e_frameProtection.c`. This
file is auto-coded by our code generator. It makes use of the hand-coded
checksum computation in file `crc_checksum.c`.

#### Folder code/canApi

When looking at the test application with the
view of a sample integration of the CAN interface then this folder is most
important. It contains the auto-coded files, which belong to the CAN
interface. The CAN interface engine is hand-coded and project independent
but the interface integration adds all the specific knowledge about the
CAN communication in the given project. This knowledge is mainly collected
in module `cdt_canDataTables.c`, which implements the large constant data
table about all affected messages, which the hand-coded callbacks of the
interface engine operate on.

Moreover, the folder contains the auto-coded, global CAN API together with
the set of pack and unpack functions, see module `cap_canApi.c`. This is
more or less the same as for the elder sample integrations. A significant
difference is the way event messages have been supported. The elder
integrations use a data comparison mechanism in the auto-coded part of the
CAN interface in order to detect signal changes. They consider a signal
change the trigger to send the parent message. In contrast, sample
`winTestMT` offers an explicit event interface, which has to be used by
the APSW to trigger sending an event message. In the test application, this
interface is served by a random process.

Last but not least there is the auto-coded file `cst_canStatistics.h`,
which contains a number of #define's, that make counts of messages available
to the software -- total counts, per bus and per kind of message. The macros
are useful for precise memory allocation of message related data objects.

All C sources and related header files in this folder are generated by the
code generator but not all generated files are located here; in this
application the auto-coded files have not been collected in one folder but
they are generated where they logically belong. You may refer to the
script file `generateCode.cmd` in this folder to see, which files are
generated for the application.

The templates for the code generator are located in the sub-folder
`templates`.

The CAN network databases are located in the sub-folder `dbcFiles`.