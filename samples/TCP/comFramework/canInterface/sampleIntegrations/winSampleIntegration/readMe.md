# Windows Sample Integration

## Scope

This sample application implements a power display device for an
automotive vehicle as a Windows application. Although the application is
entirely useless as such it contains all elements of the integration of
the comFramework CAN interface into a real embedded platform. All needed
code elements can be inspected and understood and the application can be
run and debugged for detail investigations. Many of the code elements and
particularly most of the code-generation template code will be reusable in
the aimed target environment. This is proven by the second sample
integration, ../arduinoSampleIntegration, which has the same functionality
and shares many code elements with only minor modifications.

The application reads the current values of engine rotational speed
and engine torque from the CAN bus and computes the current power of the
engine. The results are printed to the console and written in a log file.

The sample code comes along with all source files and build scripts
(makefile based). GNU GCC and GNU make 3.81 should be in the system
search path, then the build command would be (Windows, other systems
accordingly):

    cd <...>\comFramework\canInterface\sampleIntegrations\winSampleIntegration
    make -s build

To start the sample application you may type:

    make -s run

Please try also: `make help`

Note, on Windows systems you will need the MinGW port of make, not the
Cygwin port. Many GCC distributions contain both variants, so it depends
on your system search path, which one is run. Or consider typing
`mingw32-make build`; in a Windows GCC distribution this should be a safe
reference to the right implementation of make. The Cygwin variant uses
another interface to the underlying shell and this interface is not
compatible with our makefiles.


## Application design

We designed this application to demonstrate how an integration into a real
platform can look like. The actual capabilities of the application are
secondary.

### Folder osSimulation

The integration doesn't support real CAN hardware and it neither builds on
a real strictly priority controlled RTOS. Instead, a simulation frame has
been shaped, which simulates the task scheduling and the interrupt based
CAN interface of a fictive operating system. The simulation is most simple
and particularly is it single-threaded. The tasks of different priorities
and the interrupt notifications are executed strictly sequential and no
race-conditions occur. All multi-threading related aspects of the CAN
interface can in no way be tested in this environment but the code elements
and structure and thus the instructive intention of the application are
not affected by this fact.

The simulation computes triangular curves of different frequencies for
speed of rotation and engine torque. This leads to a dynamic but not
exciting behavior of the application.

The simulation code can inject the following kinds of CAN communication
errors: Timeout, wrong data length code, bad checksum, bad sequence
counter value, bus-off error (and recovery). The occurrence of the errors is
random controlled; the probabilities can be adjusted by #define macros at
compile time.

### Folder APSW

The functional code, the application software or APSW, reads the current
speed of rotation and engine torque values, computes the current engine
power and prints the results. It can display a lot of program flow
information and in particular the simulated and recognized CAN
communication errors. The verbosity can be controlled via the command
line. (Try `--help` first.)

The APSW is hand-coded but in structure it is designed to resemble the
code of typical model based development environments in that it simply
reads required input signal values from some global variables, performs
the computations and writes the results into other dedicated global
variables. This design pattern was chosen in order to prove the CAN
interface's capabilities for support of data-change triggered frames.
(Hand-coded software tends to be event driven by itself, which makes
data-change recognition mechanisms obsolete.)

The APSW code is located in folder code\\APSW.

### Folder integration

More important is folder code\\integration. It contains those hand-coded
parts of the application, which are needed to integrate the CAN interface
with any real platform (or operating system). The tasks are defined that
do the initialization of the CAN interface (frame and bus registration)
and the regular clocking of the interface engine instances. Moreover, the
handle mapping and the checksum and sequence counter update/validation,
which are external to but required by the CAN interface engine are
implemented here.

Please note: Handle mapping is always required by the CAN interface
(it'll be a trivial identity in many environments like in our Arduino
integration), but checksum and sequence counter update/validation are a
matter of application specific configuration only.

The integration code contains the handling of bus errors, too. Although it
strongly resembles the auto-generated code for frame handling (see below)
and although it could be auto-generated, too, we decided for hand-coding.
The reason simply is that the number of CAN buses is very low in
comparison to the number of frames and that the CAN bus configuration
typically doesn't undergo frequent changes in the course of a software
project. Maintaining this code through template programming as it would be
required for auto-generated coding, won't ever pay off.

### Folder codeGen

Most important is folder code\\codeGen. It contains the configuration of
the CAN interface for this application. This configuration is mainly
determined by the code generation from the network database file(s). The
transmission modes and all program flow for communication validation
(timeouts, checksum and sequence counter support) are implemented here,
controlled by the attributes in the network databases. Moreover, the
global data API with the APSW, which is highly dependent on the network
databases is implemented here, too.

All C sources and related header files in this folder are generated by the
code generator.

### Folder environment

This folder contains a few header and stub files to satisfy the
compilation and to support compilation with both, Windows GCC 32 Bit and
64 Bit, which differ in some respects.
