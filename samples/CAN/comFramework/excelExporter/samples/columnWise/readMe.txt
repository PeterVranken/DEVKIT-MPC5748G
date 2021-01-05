This sample demonstrates the iteration along Excel columns.

The usual paradigm is to consider the rows of an Excel worksheet data
items, where the complete row forms one object and the cells in the
different columns hold the values of the according properties of the
object. The usual iteration visits all the row objects and renders them
using the individual property values.

Sometimes we see Excel worksheets, where the cells of a row are not
directly related. Instead, the columns are self-contained and will likely
have differing lengths. In this example we see two columns. Each
represents a set of given names, female and male. The sample template code
shows how to evaluate both sets independently despite of application
excelExporter still building the data model in its usual row by row
paradigm - a built-in behavior, which can't be changed at all.

The code generation can be repeated by running the Windows script
runColumnWise.cmd from this working directory. Repeating the code
generation should be tried as kind of installation test of the application
excelExporter. 

If you want to run the application from another working folder then you
need to ensure that the environment variable EXCELEXPORTER_HOME is
properly set. Please refer to the installation notes of excelExporter for
details.

excelExporter generates the Java source code output\nameGenerator.java.
The Java source code can be compiled with the script output\javac.cmd and
the compiled code can be launched with the other script
output\nameGenerator.cmd. (These two scripts are fixed part of the sample
and aren't generated.)

All Windows scripts are trivial; porting them to Linux or Mac OS is
straightforward.
