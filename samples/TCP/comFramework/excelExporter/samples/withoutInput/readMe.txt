Primarily, this sample demonstrates that template expansion with
excelExporter can be a powerful and cheap automation tool even when not
having much Excel organized data behind. Secondary, the sample is a
demonstration of the capabilities of the numeric scratch pad; how to use
it for simple arithmetics and conditional template expansion.

The applied StringTemplate V4 templates are widely self-contained, i.e.
their expansion barely depends on external data. Actually, we only pass a
single (numeric) data item into the rendering process. The sample
generates a multiplication table and the data item is its length (number
of rows). The table length is passed in on the command line as a user
option; no Excel file is involved in the expansion process. excelExporter
in this configuration mutates to a command line controlled multiplication
table generator.

The code generation can be repeated by running the Windows script
runWithoutInput.cmd from this working directory. Repeating the code
generation should be tried as kind of installation test of the application
excelExporter. The generated output is placed in file output\mulTab.txt
and it is written to the console.

If you want to run the application from another working folder then you
need to ensure that the environment variable EXCELEXPORTER_HOME is
properly set. Please refer to the installation notes of excelExporter for
details.

All Windows scripts are trivial; porting them to Linux or Mac OS is
straightforward.
