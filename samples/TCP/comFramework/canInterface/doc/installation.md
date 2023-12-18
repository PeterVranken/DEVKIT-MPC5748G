[TOC]

# Installation #

## Overview ##

comFramework is distributed as a ZIP archive. The initial installation
step is unzipping the contents to a directory of your choice. The
directory should grant read and write access to all users.

The downloaded comFramework archive contains

-   the source files of the CAN interface engine for integration
    in target projects,
-   the Java applications, that implement the two code generators, which
    support the interface design,
-   and three sample integrations.

The source files of the CAN interface don't need any installation (with
the trivial exception of a text editor to open and read them).

The DBC code generator is always needed. Its installation means to provide
a Java runtime environment, 1.8 or higher, to set an environment variable
and optionally to extend the system's search path.

excelExporter, the auxiliary code generator is not essential but useful.
Its installation means to provide a Java runtime environment, 1.7 or
higher, to set an environment variable and optionally to extend the
system's search path.

The sample integrations come along with the generated C source code. They
are mainly meant as instructive sample code. An installation of tools is
not required if this suffices, if there's no need or intention to alter
the sample code and re-compile it.

The Arduino sample comes along with source code and the compiled
executable; you can immediately upload it to your Arduino Mega 2560 board
and see how it behaves. An installation of Arduino 1.8.19 is required.

If the Windows examples should be needed as running applications for
further investigation or debugging then GCC needs to be installed. 32 and
64 Bit versions are supported but only a few versions of GCC have been
tested; see [whichCCompilerToUse.adoc](https://vranken@svn.code.sf.net/p/comframe/code/canInterface/trunk/sampleIntegrations/winTestMT/whichCCompilerToUse.adoc) for details.

Compilation of the Windows samples has been done under Windows 7 and 10.
The code is free of specific operating system calls and only uses
functions from the GCC libraries. As these are widely operating system
independent the sample should compile and run under other Windows
versions, Linux and Mac OS as well; this has however never been tested and
as a matter of experience most often there are some minor
incompatibilities, which have to be sorted out first - just give it a try.

Using another compiler than GCC will mean code changes in the application
interface, command line evaluation in the first place.

All C compilation and related operations is controlled from makefiles,
which need the MinGW port of GNU make 3.81 or higher. If you type "make
--version" in a shell window this revision of make needs to respond. Other
make derivatives or elder revisions of GNU make won't probably work.

## Java ##

A Java runtime environment of version 18 or higher is required. Nothing
has to be done if such an environment is already in the Windows search
path. (java.exe is found just like that; type "where.exe java" and "java
-version" in a shell window to prove.)

If no Java executables are available in your system yet, then visit
http://www.oracle.com/technetwork/java/javase/downloads/index.html
(visited Oct 4, 2022) to get the Java JRE. Caution, you will likely want
to follow the link to the distribution of "OpenJDK" in order to avoid
license violations.

After installing the Java package, you need to make the executables
accessible. Either:

- extend the Windows search path. Add the path to the folder containing
  java.exe to environment variable PATH
- create a new environment variable COMFRAMEWORK\_JAVA\_HOME and assign
  the Java JRE installation path. The right path is the one, which
  contains bin\\java.exe

Either of the two may be done globally and persistently or locally in the
startup scripting of your project, which makes use of comFramework.

## Code generator ##

The installation of the main code generator is described in detail in file
[installation.html](https://svn.code.sf.net/p/comframe/code/codeGenerator/trunk/doc/installation.html); the file can be found locally as
comFramework/codeGenerator/doc/installation.html.

Please refer to the files readMe.txt in the root directory of any of the
samples, which come along with the code generator for more details on how
to run the code generator.

## excelExporter ##

The installation of the auxiliary code generator excelExporter is
described in detail in file [installation.html](https://svn.code.sf.net/p/comframe/code/excelExporter/trunk/doc/installation.html); the file can be found locally as
comFramework/excelExporter/doc/installation.html.

Please refer to the files readMe.txt in the root directory of any of the
samples, which come along with excelExporter for more details on how to
run excelExporter.

## Arduino sample integrations ##

Arduino 1.8.19 needs to be installed for compilation of the samples and even
for upload of the pre-compiled binaries. (The GCC avr tools are taken from the
Arduino installation.) Please refer to <http://www.arduino.cc/>.

Caution: Do not install the elder revision Arduino 1.6.5: This package did
not contain all required GCC avr tools.

A new environment variable needs to be set. Let ARDUINO_HOME point to
the root directory of the Arduino installation. All tools are located
via this variable.

An installation of MinGW make is required. Modify the system path
variable such that GNU MinGW make 3.81 is found when typing "make".

In a shell window type:

    make --version

The MinGW port of GNU make 3.81 should respond. Now CD to one of the root
directories comFramework/canInterface/sampleIntegrations/arduinoSampleIntegration
or comFramework/canInterface/sampleIntegrations/arduinoSampleIntegrationEmbeddedCoder
of the Arduino samples and type:

    make -s clean
    make -s build

to rebuild the sample (which includes the generation of the network database
dependent C code of the CAN interface). Try "make help", too.

Please refer to file readMe.md in the root of the Arduino samples for
further details.

## Windows sample integrations ##

GNU make 3.81 needs to be installed. Under Windows, only use MinGW
distributions. The Cygwin distributions will probably need some
modifications of the makefiles.

The GNU C compiler GCC (32 or 64 Bit, e.g.,
mingw-i686-8.1.0-release-win32-dwarf-rt_v6-rev0 or
mingw-w64-x86_64-8.1.0-posix-seh-rt_v6-rev0) needs to be installed.

On principle, the makefiles are prepared to support the compilation under
Linux and Mac OS as well. If problems appear you should first have a look
into sub-makefile locateTools.mk, which is responsible to find the paths
to the executables. There are different configuration possibilities to
find the tools either via system search path or via environment variable
settings. Maybe you need to alter this configuration first. The same holds
if you have different GCC revisions installed and want to switch between
them.

If MinGW GNU make 3.81 and GCC are installed then you can CD to the root
directory comFramework/canInterface/sampleIntegrations/winSampleIntegration
or comFramework/canInterface/sampleIntegrations/winTestMT of the Windows
sample integrations and type:

    make -s clean
    make -s build

to rebuild the samples (which includes the generation of the network
database dependent C code of the CAN interface). Try make help, too.

Please refer to files readMe.md in the root of the Windows samples for
further details.
