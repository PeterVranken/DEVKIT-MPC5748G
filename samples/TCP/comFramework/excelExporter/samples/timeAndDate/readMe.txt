ExcelExporter 0.18 introduced the new field "date" in the data model of
the Excel worksheet cell. This field is of Java class Calendar and enables
the use of StringTemplate V4's date renderer. Date and time designations
in Excel spreadsheet can be rendered in virtually any format, using a
format string mechanism similar to the Java class
java.text.SimpleDateFormat (e.g.
https://docs.oracle.com/javase/tutorial/i18n/format/simpleDateFormat.html).
        
This sample demonstrates some of the various ways to render dates and
times.

The code generation can be repeated by running the Windows script
runTimeAndDate.cmd from this working directory. Repeating the code
generation should be tried as kind of installation test of the application
excelExporter.

If you want to run the application from another working folder then you
need to ensure that the environment variable EXCELEXPORTER_HOME is
properly set. Please refer to the installation notes of excelExporter for
details.

All Windows scripts are trivial; porting them to Linux or Mac OS is
straightforward.
