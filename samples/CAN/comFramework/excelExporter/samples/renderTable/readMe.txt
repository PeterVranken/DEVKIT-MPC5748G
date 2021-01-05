As a matter of experience, excelExporter is hard to use. The command line
is quite complex. excelExporter supports rendering several workbooks and
sheets in a single run, where different sheets can contain differenly
structured data. All of this requires a quite complex command line. It
needs to enable you to select the books and sheets and to specify the
structure of your data in all the worksheets.

Furthermore, prior to successfully using excelExporter, you need to
understand StringTemplate V4 and syntax and meaning of its template
expressions and you need to know how the data from your Excel input is
organized in the internal data model of excelExporter and how it can be
retrieved from there in a template.

On the other hand, far the most of all use cases of excelExporter are
quite simple. It's nearly always about a single worksheet in simple table
structure: The first row (the header row) contains the column titles and
each other row describes a single data item. The properties of the data
item are found in the cells of the row and the name of each property is
the title of the according column. excelExporter is applied to render this
list. The output is exected to be a list, too; it's the repetition of the
basic pattern defined (by StringTemplate V4 template) for a single data
item. This list may be embedded into some frameing portions of text.

This folder contains all preconfigured files, which are required
to support this use case on a Windows machine.

The rendering process is started by command line. Excel input file and
desired output file are stated as arguments:

    renderTable.cmd <outputFile> <excelWorkbook>

For example:

    renderTable.cmd stdout mySimpleTable.xlsx

The command line for excelExporter is stated such that a single worksheet
- the first one - from the specified workbook is rendered.

The StringTemplate V4 template group file is organized such that the
framing text blocks and the template for the basic pattern for a single
data item (i.e. Excel row) can be easily identified and customized to your
particular needs.

Before you start your work, you may consider to type:

    renderTable.cmd --help
    
which will open all the documents you normally require to develop an
excelExporter application:

- Explanation of concepts of excelExporter
- The manual of StringTemplate V4
- The Javadoc documentation of the internal data model of excelExporter
- It prints the command line documentation ("usage") of excelExporter

An valid installation of excelExporter is prerequiste, in particular, 
environment variable EXCELEXPORTER_HOME needs to be set and point to the
installation of the tool.

To start your work, copy this entire folder, then:

- Open the Excel file, alter the column titles and add more columns
  according to your needs
- Open the StringTemplate V4 template group file and alter the templates,
  which define the basic pattern for a single data item and the framing
  portions of text
- Run renderTable.cmd as described above
