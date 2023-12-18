= _renderTable_: Simplified use of _excelExporter_
:toc:

== Introduction

As a matter of experience, _excelExporter_ is hard to use. The command line
is quite complex. _excelExporter_ supports rendering several workbooks and
sheets in a single run, where different sheets can contain differently
structured data. All of this requires a quite complex command line. It
needs to enable you to select the books and sheets and to specify the
structure of your data in all the worksheets.

Furthermore, prior to successfully using _excelExporter_, you need to
understand StringTemplate V4 and syntax and meaning of its template
expressions and you need to know how the data from your Excel input is
organized in the internal data model of _excelExporter_ and how it can be
retrieved from there in a template.

On the other hand, far the most of all use cases of _excelExporter_ are
quite simple. It's almost always about a single worksheet in simple table
structure: The first row (the header row) contains the column titles and
each other row describes a single data item. The properties of the data
item are found in the cells of the row and the name of each property is
the title of the according column. _excelExporter_ is applied to render this
list. The output is expected to be a list, too; it's the repetition of the
basic pattern defined (by StringTemplate V4 template) for a single data
item. This list may be embedded into some framing portions of text.

This folder contains some preconfigured files, which support this use case
on a Windows machine.

Script `renderTable.cmd` is typically used in two steps:

- The first run generates a default StringTemplate V4 template file, which
  serves as a starting point for your desired templates. Moreover, this
  run of the script generates a simple Windows wrapper script with an
  appropriate command line for _excelExporter_
- Subsequent runs are done indirectly via the wrapper script generated in
  the first step. These runs require the specification of wanted output
  file and Excel workbook. They will render the workbook according to the
  template file generated in the first step (and maybe meanwhile modified)

The generated StringTemplate V4 template group file is organized such that the
framing text blocks and the template for the basic pattern for a single
data item (i.e., Excel row) can be easily identified and customized to your
particular needs. It contains TODO tags, how to elaborate if for your needs.

Before you start your work, you should type:

    renderTable.cmd -h
    renderTable.cmd --help
    
The first command prints the usage message, which explains in detail how
to run the two steps and the second one will open all the documents you
normally require to develop an _excelExporter_ application:

- Explanation of concepts of _excelExporter_
- The manual of StringTemplate V4
- The Javadoc documentation of the internal data model of _excelExporter_
- It prints the command line documentation ("usage") of _excelExporter_

A valid installation of _excelExporter_ is prerequisite; in particular, 
environment variable EXCELEXPORTER_HOME needs to be set and point to the
installation of the tool.

To start your work, copy this entire folder, ensure that the script
`renderTable.cmd` is in the Windows search path and run `renderTable.cmd`
as described above.

== Tutorial

=== Install _renderTable_

. Copy the folder `renderTable` to an installation location of your
  choice. The chosen path must not contain any blanks
  - The sub-folder `example` is part of this tutorial only and is not
    required in the installation. You may delete it from your copy
. Add the installation directory to environment variable PATH. In a newly 
  opened shell window, type: "where.exe renderTable.cmd" The response
  should point to your installation directory
  
=== Generate wrapper script

. Copy folder `example` to a location of your choice. This is your working
  environment, not an installation directory. The chosen path must not
  contain any blanks
. In a newly opened PowerShell window, `cd` to your copy of folder `example`
. Type: "renderTable -h" and carefully read the response
. Type: "renderTable --help" and inspect the opening documents
. Type: "renderTable renderMySimpleTable.stg": Two new files appear in
  your working folder:
  - renderMySimpleTable.stg, a StringTemplate V4 template group file
  - renderMySimpleTable.ps1, a PowerShell script, which wraps the call of
    _excelExporter_ for your particular use case
. Type: ".\renderMySimpleTable.ps1", which should respond with the correct
  usage of the new wrapper script

=== Elaborate templates

. Type: ".\renderMySimpleTable.ps1 stdout mySimpleTable.xlsx", which would
  be the correct usage of the wrapper script. The generated text is written
  to the console. The generated text indicates, what has still to be done
  in the preliminary template group file
. Open `renderMySimpleTable.stg` in a text editor
. Replace
+
    This is how row <row.iRow> looks like. TODO: Edit template renderRow(row) in <\\>
    StringTemplate template group file <info.templateFile> to design the appearance of the row<\n>
+
with, for example:
+
    <info.calc.noRows_sadd_1><\\>
    <row.ID>) <row.Title>, written by <row.Author>, <row.Number_of_Pages> pages<\n>

. Back in PowerShell, type again: ".\renderMySimpleTable.ps1 stdout mySimpleTable.xlsx". The
  output should be much more to the point
. Return to the text editor and extend
+
    This is sheet <sheet.name_> of workbook <sheet.parentBook.name_> (<sheet.excelFile>):
    <sheet.rowAry:renderRow()><\\>
    
+
into, for example:
+
    This is sheet <sheet.name_> of workbook <sheet.parentBook.name_> (<sheet.excelFile>):
    <sheet.rowAry:renderRow()><\\>
    We rendered <info.calc.noRows> data items.

. Repeat the previous PowerShell command and double-check the new output

=== Generate your output file

. When you have elaborated your template to the extend needed, type this
  command in the PowerShell window to generate your output file, e.g. `myOutput.txt`:
+
    .\renderMySimpleTable.ps1 myOutput.txt mySimpleTable.xlsx

. Open `myOutput.txt` in a text editor and check the result! From now on,
  the expected work flow is that you maintain your Excel table and re-run
  the wrapper script to update the generated text file accordingly