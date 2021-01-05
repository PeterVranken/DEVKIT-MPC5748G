This sample demonstrates how to model structured data, i.e. having a
structure, which is more complicated than a flat list of homogeneous data
items. The Excel file models a CAN communication matrix and excelExporter
can render the information as a CAN network database (*.dbc) file.

The data model in the Excel input has several nested levels. The CAN bus
has frames, each frame has some signals and each signal can have named
values. All objects are held in a single worksheet. Objects of different
kinds use different sets of columns to hold their individual properties.

excelExporter's grouping facilities are applied to model the objects'
relationship. We build a tree of groups, where each group represents a
single object (i.e. either a frame, a signal or a named signal value) and
where the object's children are represented by the group's sub-groups.
Each group has a single row-object, which represents the set of properties
of the object, which is represented by the group.

The worksheet represents the bus, its groups represent the frames. Each
sub-groups of a frame represents a signal of that frame and each sub-group
of a signal represents a named value of that signal. The groups, which
represent named signal values don't have any sub-groups.

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
