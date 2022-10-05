[TOC]

# comFramework 2.0 (r476, 04.10.2022) #

## About this project ##

[This project](https://sourceforge.net/p/comframe) presents a flexible, widely customizable CAN communication
interface for embedded applications. It binds signal based application
code to the frame based hardware layer. It covers the CAN stack from the
application layer down to the hardware driver layer (not including).

The interface implementation is code generator supported; the dedicated
API with the application software and the unpack/pack functions for
message (de)composition can be generated from information in the network
databases. A sample integration demonstrates, how to generate much more:
Setting initial signal values, DLC check, checksum generation/validation,
sequence counter generation/validation and the implementation of different
timing patterns is generated in a fully automated fashion. Attributes
defined in the DBC file(s) support the automation.

We call this project a framework since the interface should be considered
a suggestion only; the high flexibility of the code generation process
makes it easy to design different interface architectures, which can reach
a similar degree of automation with respect to changes of the network
database(s).

### The CAN interface ###

The operational core of the [CAN interface](https://sourceforge.net/p/comframe/wiki/The%20CAN%20Interface/) is a dispatcher engine that
decouples the one or more interrupts, which are typically used by the CAN
hardware driver for notification of send or receive events, from the
application task(s); this makes the complete data processing at the
application side safe, straightforward, race condition free programming.

The dispatcher implements a generic concept of events and notifications by
callbacks. Among more, events can be interrupts from the hardware layer or
timer events. The callback functions use the timer and other events to
model the transmission timing patterns of the frames and to generate
timeout information.

The callbacks are external to the dispatcher engine. They are either
auto-coded from the DBC files (this is what the samples demonstrate) or
they can be hand-coded and would then operate on data tables, which are
auto-coded from the DBC files.

Any number of dispatcher objects can be instantiated in order to support
multi-threading architectures in a transparent and convenient way.

### The DBC code generator ###

The code generator consists of an open source parser for CAN network
database files (*_.dbc_ or DBC files) with connected general purpose code
generator. The idea is most simple and most flexible:

The parser transforms the DBC files into an internal data representation,
which holds all information about the network. This data structure is a
special form of the parse tree. The structure has been chosen such that it
is compatible with the template engine StringTemplate V4 by Terence Parr,
see <http://www.stringtemplate.org/>. This template engine is capable to
render deeply nested data structures and it can therefore transform the
parse tree in nearly any kind of textual representation. This explains the
high flexibility/customizability of the whole system.

Just by configuring the templates, the code generator can produce
different useful representations of the information in the network files,
like:

- An HTML report with all frames, signals, attributes and all the
  properties of these
- An Excel file with all the same (however, only as *_.csv_)
- C source code and related header files, which implement a CAN interface.
  The interface will contain the needed data structures, timing related
  frame processing, validation code and pack and unpack operations to
  transform signal sets to frames and vice versa. The implementation can
  be made specific to a particular platform's requirements
- LaTeX source code for documentation of the interface
- Interface definition files: If code from a model based code generation
  environment is linked to the CAN interface (e.g. MathWorks MATLAB
  with either their Embedded Coder or with dSPACE TargetLink) then a
  descripition of the signal interface is essential as these code
  generators need to be aware of the signal sets and their properties,
  data types and scaling in the first place. Our code generator can
  generate the required M scripts or XML files
- ASAM MCD-2 MC interface description files (*_.a2l_) if the target
  platform shall be connected to a measurement and calibration tool like
  ETAS INCA or Vector Informatik CANape
- AUTOSAR specification code (*_.arxml_). The DBC file contents can be
  rendered as an AUTOSAR software component, which connects to the
  ISignals of the COM stack, including all required application data types
  with scaling and more information

### DBC parser ###

In most automation environments our code generator can be used as raw DBC
parser for whatever purpose, too. Typically, interpreted languages like
Perl, Python or Octave's M script are applied in software automation
environments. If you use any interpreted language then you can configure
the code generator to render the information in the syntax of your
scripting language. Run the code generator, run the generated script and
have the information in the context of your automation environment. The
configuration of the code generation can be tailored; you will just render
those parts of the information you really need. No need to develop the
most complex all embracing data structure. A simple [example for GNU Octave](https://sourceforge.net/p/comframe/wiki/Reusage%20and%20standalone%20usage%20of%20DBC%20parser/#example-the-code-generator-as-dbc-parser-for-gnu-octave-m)
is provided.

### excelExporter as auxiliary code generator ###

A second, auxiliary code generator is part of the framework. This is the
Java application excelExporter. The idea is nearly the same as for the
main code generator but the input is a set of Excel workbooks instead of
DBC files. The parse tree can be as simple as a linear list of rows from a
flat table or a as complex as a deeply nested tree of interrelated data
items. The concrete data structure depends on the definition of the input.
The parse tree is rendered by the StringTemplate V4 template engine,
identical to what has been said for the DBC code generator. The intented
use case of the auxiliary code generator excelExporter is to support the
handling of interfaces. Excel files serve as data dictionary of signals,
variables, diagnostic interface items, etc. and can be translated into
C/C++ interface implementations, documentation, ASAM MCD-2 MC or
AUTOSAR interface specifications, etc.

## Status of the project ##

The project is ready for productive use.

- The CAN interface with its dispatcher engine is distributed as source
  code; concept and how-to-use are documented in this [Wiki page](https://sourceforge.net/p/comframe/wiki/The%20CAN%20Interface/)
- Several compilable and runnable sample integrations of the CAN interface
  are distributed with source code and makefiles together with the
  dispatcher engine. There are integrations for Windows, there's an
  Arduino ATmega 2560 real time integration and an integration with the
  MathWorks Embedded Coder. A complete runnable real-time application for
  MPC5748G with CAN driver and integrated CAN interface can be found at
  [GitHub](https://github.com/PeterVranken/DEVKIT-MPC5748G/tree/master/samples/CAN)
- The code generators are distributed as Java application. A number of
  samples for the [DBC code generator](https://sourceforge.net/p/comframe/code/HEAD/tree/codeGenerator/trunk/samples/) and for [excelExporter](https://sourceforge.net/p/comframe/code/HEAD/tree/excelExporter/trunk/samples/) demonstrate
  how templates can look like, which do the transformations mentioned above
- The [download page](https://sourceforge.net/p/comframe/files) at SourceForge provides a ZIP archive for download,
  which bundles all needed tools, files and samples in a ready-to-use
  folder structure. The archive contains the files of revision r476
  (04.10.2022 11:54:21) of the SourceForge [SVN repository](https://sourceforge.net/p/comframe/code/HEAD/tree)
- More recent revisions of the software are distributed as source code in
  this repository and, as far as the code generation tools are concerned,
  as compiled Java \*_.jar_ files. Get for example the last recent DBC code
  generator by replacing the files _dist/_\*_.jar_ and _dist/_\*_.cmd_ in your
  installation by the jar files and command files from
  <https://sourceforge.net/p/comframe/code/HEAD/tree/codeGenerator/trunk/dist/>.
  excelExporter files would be found [here](https://sourceforge.net/p/comframe/code/HEAD/tree/excelExporter/trunk/dist/), respectively

Support of the project is appreciated to support more kinds of network
databases. For now, we are restricted to the DBC format. However, this
format looses importance. New formats like arxml or FIBEX will probably
supersede DBC in the future. Furthermore, different physical bus systems
have different network database files, like *_.ldf_ for LIN communication.
Parsers for these input formats are required and - what's more difficult -
a common data model for all of these buses and network files needs to be
developed so that the parser becomes a configurable choice but the
templates can be kept widely independent of the input format.

## Installation ##

comFramework is mainly distributed as a ZIP archive. Some external tools
like a C compiler are useful. Please find the installation guide as
[Installation of distributed ZIP archive](https://sourceforge.net/p/comframe/wiki/Installation/).

## Documentation ##

### What's new ###

Latest news about the progress of the project can be found as discussion
thread [What's new](https://sourceforge.net/p/comframe/discussion/news/).

The CAN interface is mainly documented in this [Wiki page](https://sourceforge.net/p/comframe/wiki/The%20CAN%20Interface/). An overview of
all available documentation and of the latest changes is given in the
related [readMe](https://svn.code.sf.net/p/comframe/code/canInterface/trunk/readMe.html) file.

An overview of the documentation and the latest changes of the DBC code
generator is given in the related [readMe](https://svn.code.sf.net/p/comframe/code/codeGenerator/trunk/readMe.html) file.

An overview of the documentation and the latest changes of the auxiliary
code generator excelExporter is given in the related [readMe](https://svn.code.sf.net/p/comframe/code/excelExporter/trunk/readMe.html) file.

### Wiki pages ###

A growing source of documentation are the Wiki pages of the project,
please refer to <https://sourceforge.net/p/comframe/wiki/browse_pages/>.
The Wiki pages shade a light at some most relevant, selected issues; a
comprehensive, self-contained (printable) manual is not planned.

As of today, October 2022, we have the following discussions in the Wiki
pages:

- [Installation of distributed ZIP archive](https://sourceforge.net/p/comframe/wiki/Installation/)
- [The CAN interface - concept and usage](https://sourceforge.net/p/comframe/wiki/The%20CAN%20Interface/)
- [The CAN interface - Doxygen pages](https://svn.code.sf.net/p/comframe/code/canInterface/trunk/doc/doxygen/html/index.html)
- [The command line of the DBC code generator](https://sourceforge.net/p/comframe/wiki/Command%20Line%20DBC%20Code%20Generator/)
- [Compatibility of the DBC parser with real *_.dbc_ files](https://sourceforge.net/p/comframe/wiki/Reusage%20and%20standalone%20usage%20of%20DBC%20parser/#compatibility)
- [Prerequisites, limitations and pitfalls](https://sourceforge.net/p/comframe/wiki/Prerequisites%2C%20Limitations%20and%20Pitfalls/)
- [Reusability of the DBC file parser in other contexts/applications](https://sourceforge.net/p/comframe/wiki/Reusage%20and%20standalone%20usage%20of%20DBC%20parser/)
- [Options for conditional code generation](https://sourceforge.net/p/comframe/wiki/Conditional%20code/) 
- [The use of attributes](https://sourceforge.net/p/comframe/wiki/Attributes%20in%20the%20network%20database/)
- [A common pattern how to combine handwritten code with auto-generated
  code in a beneficial way](https://sourceforge.net/p/comframe/wiki/Attributes%20in%20the%20network%20database/#typical-code-architecture)
- [Sugar on top of inheritance or how to change the copyright notice](https://sourceforge.net/p/comframe/wiki/Sugar%20on%20top%20of%20Inheritance%20or%20how%20to%20change%20the%20copyright%20notice/)
- [Concept of excelExporter](https://sourceforge.net/p/excelexporter/wiki/Home/)
- [Comparison of this project with the other SourceForge project *cantools*](https://sourceforge.net/p/comframe/wiki/cantools%20versus%20comFramework's%20Code%20Generator/)
