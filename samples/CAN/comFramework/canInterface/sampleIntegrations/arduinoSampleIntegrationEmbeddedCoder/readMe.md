Arduino Engine Power Display with MathWorks Embedded Coder
==========================================================

Scope
-----

This sample application implements a power display device for an
automotive vehicle. It reads the current values of engine rotational speed
and engine torque from the CAN bus and computes the current power of the
engine. The power is displayed on Arduino's LCD (2*16 characters) and
broadcasted on the CAN bus.

The difference to the other Arduino sample integration is that the
functional software -- the APSW, all the computation of torques and powers
-- is not hand coded but model based. A MathWorks Simulink model specifies
the functionality and it can use the code generator Embedded Coder to
translate this specification into ready-to-use C code. This technique
requires proper interfacing between the Simulink model and our CAN
interface. The sample demonstrates how our code generator can produce an
Embedded Coder script (*_.m_) so that it generates C code, which
directly connects to the CAN interface.

The sample code comes along with all source files and build scripts
(makefile based). It can be compiled for the Mega2560 board; other boards
will need migration work and tiny boards won't work at all because of the
RAM consumption.

Those who don't have the LyquidCristal shield for their Arduino Mega can
still upload and run the sample: The computed power and some relevant
status information (like CPU load and task overrun counters) are printed
regularly to the console window of the Arduino IDE. (Serial connection
must be opened at the IDE.) Please note, status information is printed
only in DEBUG compilation.

The build requires an Arduino 1.0.6 installation and additionally the
environment variable ARDUINO_HOME needs to point to this installation. The
reason is that the GNU avr-gcc tools and the Arduino libraries are located
by the makefile via this variable. GNU make 3.81 should be in the system
search path, then the build command would be (Windows, other systems
accordingly):

~~~~~~~~~~~~~~~~~~~
cd <...>\comFramework\canInterface\components\arduinoSampleIntegrationEmbeddedCoder
make build
~~~~~~~~~~~~~~~~~~~

to build the flashable hex file or 

~~~~~~~~~~~~~~~~~~~
cd <...>\comFramework\canInterface\components\arduinoSampleIntegrationEmbeddedCoder
make -s COM_PORT=COM10 upload
~~~~~~~~~~~~~~~~~~~

to build and upload the application to a Arduino Mega board, which is
connected to the specified COM port.

Note, on Windows systems you will need the MinGW port of make, not the
Cygwin port. Many GCC distributions contain both variants, so it depends
on your system search path, which one is run. Or consider typing
`mingw32-make build`; in a Windows GCC distribution this should be a safe
reference to the right implementation of make. The Cygwin variant uses
another interface to the underlying shell and this interface is not
compatible with our makefiles.

Arduino 1.6 won't work out of the box; the Arduino people decided to no
longer package the Arduino IDE with the GNU avr-gcc tools and the makefile
will fail to locate these tools. You will have to modify the makefile or
use your system search path settings to overcome this.

Caution, we've never tried this code with Arduino 1.6 so far!


Application design
------------------

This is a sample integration of comFramework's CAN interface but not an
Arduino sample. Arduino is just an easily available, commonly known, easy
to use platform. We designed this application to demonstrate how an
integration of the CAN interface into a real platform can look like. The
actual capabilities of the application are secondary. Our CAN interface
builds on the hardware driver layer. This means a CAN shield for Arduino.

### Folder canShield ###

So far the integration doesn't go down to real CAN hardware. Instead a
simulation frame has been shaped, which exposes a typical CAN hardware
driver interface to the rest of the software. This interface looks like
and behaves as a real hardware driver. The interrupt characteristics of
the real hardware driver is simulated by using a random controlled,
asynchronously running task of highest priority.

The simulation computes triangular curves of different frequencies for
speed of rotation and engine torque. This leads to a dynamic but not
exciting behavior of the application. The implementation uses floating
point operations, which is acceptable as it is a simulation anyway and we
still have lots of CPU power reserve. The drawback of using floating point
operations is that we completely loose the feeling of how much CPU load is
produced by the CAN interface and the related pack/unpack functions; much
of the load will result from simulation and APSW.

The simulation code can inject the following kinds of CAN communication
errors: Timeout, wrong data length code, bad checksum, bad sequence
counter value, bus-off error (and recovery). The occurrence of the errors is
random controlled; the probabilities can be adjusted by #define macros at
compile time.

The fictive but realistic CAN shield API and the it feeding simulation
code have been placed in folder code\\canShield. If this application would
be made a real CAN device then this folder would become obsolete and
replaced by some adaptation of the remaining code to the actual CAN API.

### Folder APSW ###

The functional code, the application software or APSW, reads the current
speed of rotation and engine torque values, computes the current engine
power and updates the LCDisplay. It displays speed of rotation and power
and the recognized CAN communication errors.

The APSW is made by model based design. A MathWorks Simulink model
implements the APSW functionality and the MathWorks Embedded Coder
generates C code from this model. The generated code is part of the sample
and the code generation can be reproduced with MATLAB 2019b. To do so,
delete the folder pwr\_computeEnginePower\_ert\_rtw. Open MATLAB and run
script initEcBusObjects.m. Open the model pwr\_computeEnginePower.slx and
type Ctrl-B. The C source code is (re-)generated in folder
pwr\_computeEnginePower\_ert\_rtw. Folder slprj is generated, too, but the
files in this folder are not required for our purpose.

Note, MATLAB is a non open source tool and the code generation requires a
licence. If you don't have MATLAB then you will find the generated C code
in the folder pwr\_computeEnginePower\_ert\_rtw.

The CAN interface is specified to the Embedded Coder through file
code\\APSW\\initEcBusObjects.m. This file is generated by the comFramework
code generator from the DBC file. When executed by MATLAB it creates a set
of Simulink Bus and Signal objects, which are attached to the in- and
outports and in- and output signals of the Simulink model. This way, the
Embedded Coder can generate C source code, which seamlessly links to the
CAN interface we have generated. No additional hand-code is needed.

Note, the Embedded Coder has the full interface information. This includes
the scaling of in- and output signals. The Embedded Coder is capable to do
all operations on the signals just like that in fixed point operations. No
floating point operations are involved.

The APSW is nearly identical to the code generator sample
[EmbeddedCoderAPIWithBusStruct](<https://svn.code.sf.net/p/comframe/code/codeGenerator/trunk/samples/EmbeddedCoderAPIWithBusStruct>
"SVN Repo codeGenerator"). Refer to this sample and read file *readMe.txt*
to get more details about the configuration of the Simulink/Embedded Coder
model with help of MATLAB script files that are auto-coded from the DBC
files.

The APSW code is located in folder code\\APSW.

### Folder integration ###

The folder code\\integration contains those hand-coded parts of the
application, which are needed to integrate the CAN interface with any real
platform (or operating system). The tasks are defined that do the
initialization of the CAN interface (frame and bus registration) and the
regular clocking of the interface engine instances. Moreover, the handle
mapping and the checksum and sequence counter update/validation, which are
external to but required by the CAN interface engine are implemented here.

Please note: Handle mapping is always required by the CAN interface,
(it'll be a trivial identity in many environments like in our Arduino
integration) but checksum and sequence counter update/validation are a
matter of application specific configuration only.

The integration code contains the handling of bus errors, too. Although it
strongly resembles the auto-generated code for frame handling (see below)
and although it could be auto-generated, too, we decided for hand-coding.
The reason simply is that the number of CAN buses is very low in
comparison to the number of frames and that the CAN bus configuration
typically doesn't undergo frequent changes in the course of a software
project. Maintaining this code through template programming as it would be
required for auto-generated coding, won't ever pay off.

### Folder codeGen ###

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

### Folder RTOS ###

Last but not least we have folder RTOS. A popular open source real time
operating system for Arduino has been placed here. Nothing special about
this, maybe with the exception of file
comFramework\\canInterface\\components\\arduinoSampleIntegrationEmbeddedCoder\\code\\RTOS\\rtosConfig\\rtos.config.h,
which configures the RTOS at compile time (number of tasks, required task
communication objects, etc.).
