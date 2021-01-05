# excelExporter - Rendering Excel Spreadsheets as Text #

## Introduction ##

This archive contains the binary distribution of excelExporter, an
application that can translate the information found in one or more Excel
workbooks into manifold textual representations. excelExporter is a
general purpose text rendering application for Excel spreadsheets.

excelExporter is the auxiliary code generator from the [comFramework](https://sourceforge.net/p/comframe/wiki/Home/)
project. However, the use of excelExporter is in no way restricted to the
context of CAN interface generation in embedded, automotive software
development. Because of its generality we decided to publish it as
independent SourceForge project. This relates to the binaries and the
documentation. The source code and the build scripts remain part of
project comFramework; some of the links down here will thus point to that
other project.

The principal aim of the tool is supporting automation tasks in software
development environments. In the context of the comFramework project this
targets the handling of data dictionaries and interfaces but excelExporter
is by design independent from this intended purpose and will be useful for
various other automation tasks.

You can render the information in the Excel input for example as:

- HTML or LaTeX for reporting and documentation
- Various XML formats for interfacing with other applications
- C/C++ or any other textual programming languages

In- and output description are decoupled in the parametrization of the
tool. First you will specify a set of Excel input files. All of these are
parsed and merged to one large data structure, ofter referred to as _data
model_. Input files of same or of different format are supported.
("Format" refers to the structure of the Excel files with respect to
contained sheets and columns.)

Secondary, you will define a list of output files. The specification of
each output file is associated with the specification of a StringTemplate
V4 template file. The template controls the output generation and this is
how the same information is rendered once as HTML code and once as - for
example - C program fragment.


## Documentation ##

### Command line interface of excelExporter ###

The usage of the tool is explained in the application's command line usage
text: Begin with running excelExporter with command line option --help.

The command line interface of the application has the following concept:

The arguments form groups. A group of successive arguments can specify an
input file, another group can specify another input file or an output file
and so on. The beginning of a group of arguments is recognized by a
specific argument, the principal argument of the group. The usage text
typically says "this argument opens the context of ...". Naturally, the
same command line switches can be repeatedly used, once in each group of
same kind.

Such a group of command line arguments or a "context" actually is the
representation of an object in the parameter tree of the application. This
is the model behind the parameter tree:

- Root elements are either Excel input file specifications, specifications
  of generated output files or worksheet templates
- The input file specification contains the Excel file name and it has any
  number of worksheet selection objects as children
    - A worksheet selection specifies one or more worksheets for parsing.
      All sheets or any sub-set of sheets of a workbook can be parsed.
      Selection can be made by name or by index
- An output file specification contains the file name and information
  about the StringTemplate V4 template to be applied
- A worksheet template is a set of rules how to interpret one or more
  worksheets. It can be applied to a particular worksheet or to several of
  those, from either one or from several input files. It describes how the
  data of a worksheet is organized in terms of groups and sub-groups. It
  has any number of column attributes objects as children
    - A column attributes object specifies properties of a column, like
      name and sort order

Besides the command line arguments from a group or context there are
"traditional" command line arguments, which relate to the run of the
application as a whole, like logging and verbosity settings. The
application usage text says they belong to the global context.

Please note, different to the common GNU command line interface this
application demands a blank between the switch and its value. For example
-oMyOutputFile.c would be rejected, whereas -o MyOutputFile.c would be the
correct specification of a generated output file.

The application's command line arguments relate to the definition of in-
and output files and how to parse the input. This should be understood
after reading the application usage text. To successfully use the
application one still needs to understand the internal representation of
the read input data (i.e. the data model) and the way it is rendered in
the output files. The next sections explain the available, related
documentation.


### The data model ###

The internal representation of the parsed input information is explained
in detail in Wiki page [excelExporter's Data Model](https://sourceforge.net/p/excelexporter/wiki/The%20Data%20Model/) and it is documented 
as a [Javadoc of the complete data structure](https://svn.code.sf.net/p/comframe/code/excelExporter/trunk/doc/dataModel/index.html?overview-summary.html).

In the Javadoc you find the documentation of all public elements of the
data structure that are accessible from the StringTemplate V4 templates.
The data structure is deeply nested, and actually, it are even two data
structures, which are passed to the rendering process:

- The parsed information forms an object of class *Cluster*
- The information about output files plus some environmental information
  is put into an object of class *Info*

You will study the Javadoc pages to see, which pieces of information to be
used from within a template.

Please note, the Javadoc describes the different elements (classes) of the
data model. Their nesting is not fully transparent from the Javadoc since
recursive structures are involved. The actual structure of the data
model will depend on (and reflect) the structure the input data is
organized in. Only in the most simple case it's a linear list of so called
[RowObjects](https://svn.code.sf.net/p/comframe/code/excelExporter/trunk/doc/dataModel/excelExporter/excelParser/dataModel/RowObject.html), which represent a single row from the Excel input
file and which consist of so called [CellObjects](https://svn.code.sf.net/p/comframe/code/excelExporter/trunk/doc/dataModel/excelExporter/excelParser/dataModel/CellObject.html). In all other cases the actual data structure
depends on your input data, on the format of your Excel file and on your
application configuration (which all needs to be consistent with one
another).

The explanation of the data model and how its structure depends on Excel
input and application configuration is given in the Wiki page mentioned
before.

Another source of knowledge about the data model and how to access its
elements is the investigation of the sample templates:
[excelExporter/samples/.../*.stg](https://svn.code.sf.net/p/comframe/code/excelExporter/trunk/samples/).

### The StringTemplate V4 templates ###

The technique of rendering the information held in a *Cluster* and an *Info*
object is well documented. The two objects are passed to the
StringTemplate V4 template engine and this engine is fully documented.
Please refer to <http://www.stringtemplate.org/> or find a printable version
of the documentation as <https://svn.code.sf.net/p/comframe/code/excelExporter/trunk/doc/ST4-270115-0836-52.pdf>.

Please note, as a matter of experience, you will have to read the
StringTemplate V4 documentation entirely before you can start to
successfully develop your first useful template. StringTemplate V4 is
powerful and convenient but not self-explaining.

Studying the samples [excelExporter/samples/.../*.stg](https://svn.code.sf.net/p/comframe/code/excelExporter/trunk/samples/)
is another important source of information.

### The Wiki pages ###

An additional source of documentation are the Wiki pages of the project,
please refer to <https://sourceforge.net/p/excelexporter/wiki/browse_pages/>.
The Wiki pages shade a light at some most relevant, selected issues; a
comprehensive, self-contained (printable) manual is not planned. As of
today, September 2018, we have the following discussions in the Wiki pages:

- [excelExporter's Data Model](https://sourceforge.net/p/excelexporter/wiki/The%20Data%20Model/)
- [Grouping and sorting](https://sourceforge.net/p/excelexporter/wiki/Grouping%20and%20sorting/)
- [Overview on the comFramework project](https://sourceforge.net/p/comframe/wiki/Home/)


## Installation ##

excelExporter is a Java 7 application. The installation is as simple as
unpacking an archive and optionally setting an environment variable. It is
described in detail in the file
[installation.txt](https://svn.code.sf.net/p/comframe/code/excelExporter/trunk/doc/installation.txt).


## What's new ##

### Release 1.0 ###

After more than a year of hassle-free productive use of the tool we
decided to make it a release and change the major field of the revision
designation to one - even if there's only little new functionality.

New sample renderTable: This folder contains pre-configured files for the
most common use case of excelExporter. Copy these files to have a fully
operational starting point for your excelExporter application - out of the
box and without struggling with the complex and cumbersome command line of
the tool.

Error handling improved. Internal errors of StringTemplate V4 during
rendering are now streamlined with the application logging. Before, they
were printed in the log (together with the bulky but in the given context
meaningless Java stack frame) but were not recognized or counted by the
application.

Minor improvements of documentation.

Fix: The field "isBlank" of a CellObject in the data model was not
operational. Blank cells are not put into the data model at all; so any
access to this field would evaluate to either false (for normal, non blank
cells) or null (for blank cells). Now the data model offers the logically
inverse as isNotBlank: This evaluates to true for normal, non blank cells
or null (interpreted as false) for blank cells. This change is the only
reason for the increase of the version number of the data model.

There should be no functional change for existing templates, which make
use of the no longer existing field CellObject.isBlank: The behavior
should be as wrong as it used to be. However, using the new field
CellObject.isNotBlank, they can now be repaired.

### Release 0.18 ###

New cell type "date" introduced for spreadsheet cell objects. Time and
date designations read from an Excel spreadsheet can now be rendered with
the StringTemplate V4 DateRenderer and using format strings, which are
similar to the Java class SimpleDateFormat.

A new sample has been added, timeAndDate, which demonstrates the new
capabilities.
  
### Release 0.17 ###

Documentation extended and many corrections made on documentation.

The row object container got the new field prop to support the common use
case of groups with a single row object.

### Release 0.16 ###

The initial release. Full functionality of the application but preliminary
state of samples and documentation.
