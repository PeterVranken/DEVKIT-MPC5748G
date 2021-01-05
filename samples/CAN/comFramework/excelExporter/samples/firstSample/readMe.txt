This sample denotes the most simple introductory example of how to render
Excel formatted information with the Java application excelExporter.

The Excel file EuropeanCapitals.xlsx is a linear list of identically
structured items, where each item is one row in the Excel worksheet and
where each column has the meaning of a property of the data item (a
country and its capital). The Excel input has the form of a simple table.

This table is parsed and fed into the StringTemplate V4 template engine.
The applied template is found in file firstSample.stg. A few lines of
template code suffice to access the table data elements and to reasonably
embed them into literal text. The generated text output is found as file
output.txt.

The only additional complexity is the data sorting. By intention the
generated output uses another sort order then the data input. The command
to sort the input data is part of the launch script runSimpleTable.cmd.

The code generation can be repeated by running the Windows script
runSimpleTable.cmd from this working directory. Repeating the code
generation should be tried as kind of installation test of the application
excelExporter.

If you want to run the application from another working folder then you
need to ensure that the environment variable EXCELEXPORTER_HOME is
properly set. Please refer to the installation notes of excelExporter for
details.

All Windows scripts are trivial; porting them to Linux or Mac OS is
straightforward.
