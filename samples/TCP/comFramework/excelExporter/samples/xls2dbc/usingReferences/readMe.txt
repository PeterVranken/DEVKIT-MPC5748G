This sample demonstrates how to model structured data, i.e. having a
structure, which is more complicated than a flat list of homogeneous data
items. The Excel file models a CAN communication matrix and excelExporter
can render the information as a CAN network database (*.dbc) file.

The data model in the Excel input has several nested levels. The CAN bus
has frames, each frame has some signals and each signal can have named
values.

Two techniques are applied in the Excel workbook to shape the relationship
between the data elements: In one worksheet the grouping characteristics
of columns is applied to specify the relationship between bus, frames and
signals and the data elements of the second worksheet are related to the
elements of first one by name references. Actually, this implementation of
the sample is a mixture of the other two implementations, usingGroups and
usingSheets.

Successful interpretation of the Excel file requires according command
line arguments of the application; excelExporter can't figure this out
itself! Please inspect the launch script to find out how worksheet
templates and column attribute objects are applied to teach excelExporter
to read the Excel input successfully.

The code generation can be repeated by running the Windows script
runXls2Dbc.cmd from this working directory. Repeating the code generation
should be tried as kind of installation test of the application
excelExporter. Please find the generated file as output\canComSpec.dbc.

If you want to run the application from another working folder then you
need to ensure that the environment variable EXCELEXPORTER_HOME is
properly set. Please refer to the installation notes of excelExporter for
details.

All Windows scripts are trivial; porting them to Linux or Mac OS is
straightforward.
