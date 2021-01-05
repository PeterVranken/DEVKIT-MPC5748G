This folder contains three different implementations of the same sample.
An Excel workbook is applied to model the contents of a CAN communication
database. CAN communication consists of buses, frames, signals and their
attributes. These elements are nested; a bus has frames and a frame has
signals, a signal may have named values and all of them have attributes.
The standard database file (*.dbc) describes only a single bus and so does
the Excel in our example. It supports frames, signals, attributes and
named signal values. The code generator writes a valid *.dbc file.

excelExporter offers grouping and lookup techniques to model data
dependencies between different data items. The three sub-folders present
different variants of Excel file and related StringTemplate V4 templates,
which make use of the different techniques. Although the result is
identical in all three cases is there a significant impact of the data
design on readability and maintainability of both, Excel input and
StringTemplate V4 templates.

In folder usingGroups we tried what seemed to be most natural; the
structure of the problem is a tree of related data items and by using
excelExporters grouping facilities we build our data model exactly as this
tree. Frames have signals as children and named signal values as grant
children. However, it turned out that this may be natural for the internal
data represention but it definitly isn't from the perspective of common
Excel usage. It's hard to understand and adopt the structure of the Excel
file. Maintenance becomes inconvenient.

Moreover, the StringTemplate V4 templates, which render the information as
*.dbc are more sophisticated and cumbersome. This may be less important as
templates need to be developed only once per application of excelExporter
but it's not negligible.

In folder usingSheets you find the data model defined in a way, which is
much closer to what's common in Excel. Maintenance of the Excel input
should not be an issue in this case. The different data items are held in
different worksheets with different, appropriate column definitions.
excelExporter's grouping is still needed to bundle the signals of a frame
and to bundle the named values of a signal. Regardless, the iterations in
the related StringTemplate V4 templates are easier to understand and the
templates thus easier to maintain.

Folder usingReferences actually is a mixture of both other variants.

The prefered solution in folder usingSheets has another advantage, which
is not apparent in the sample. The sorting of elements is much more
flexible. Using the tree structure of groups as done in folder usingGroups
suffers from the fact that groups can only be sorted either in appearance
in the input or in lexical order of their names. When using dedicated
sheets for the different kinds of data item as done in folder usingSheets
then all items form lists of row objects and these lists can be sorted
according to all the row objects' properties (i.e. the columns of the
Excel input). Only by adding some sort arguments to the command line we
could order the frames in the generated *.dbc file by size, by CAN ID, by
transmission characteristics, etc. Multi-priority sorting would enable to
have all inbound frames prior to all outbound ones and still sort both
groups by name, size, ID or else. The same considerations hold for the
signals of a frame and for the named values of a signal.