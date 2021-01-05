This sample demonstrates two things. First, it shows the simplest but
probably also most common use case of Excel and excelExporter: The data is
a linear list of identically structured items, where each item is a row in
the Excel worksheet and where each column has the meaning of a property of
the data item. The Excel input has the form of a simple table.

Secondary, the sorting facilities of excelExporter are demonstrated. The
Excel table can be rendered in the order of rows but the contained data
items can be sorted prior to rendering, too. Sorting can be done according
to selectable properties of the data items, i.e. according to selectable
columns of the Excel input.

The code generation can be repeated by running the Windows script
runSortedTable.cmd from this working directory. Repeating the code
generation should be tried as kind of installation test of the application
excelExporter. The script will launch excelExporter repeatedly, using
different sorting settings each time. Please find the generated files as
output\*.txt.

If you want to run the application from another working folder then you
need to ensure that the environment variable EXCELEXPORTER_HOME is
properly set. Please refer to the installation notes of excelExporter for
details.

All Windows scripts are trivial; porting them to Linux or Mac OS is
straightforward.
