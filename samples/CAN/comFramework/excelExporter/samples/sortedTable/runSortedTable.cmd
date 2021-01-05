@echo off
goto LStart
:LUsage
echo usage: runSortedTable [-v log-level] [-h] [--help]
echo   Run excelExporter sample sortedTable. An Excel workbook holds a most simple flat
echo table. The rows form a linear list of data objects in the rendering process. The
echo sample demonstrates how sorting of the data in the output can be controlled. The
echo actual Java application excelExporter is launched repeatedly, each time with different
echo sort settings. The produced out files can be compared to the see effects.
echo   All command line arguments but -h are passed to the Java application excelExporter.
echo Use --help to get the usage message of the application.
echo   Most arguments of the Java application are defined by this launch script but you may
echo still pass -v log-level to control the application feedback. Use --help to get more
echo details.
echo   Normally this script needs to be started from the original location in the
echo distribution of excelExporter. However, you may set the environment variable
echo EXCELEXPORTER_HOME to make it independent of its location. Refer to the documentation
echo of excelExporter to get more details.
goto :eof

:: 
:: Copyright (c) 2016, Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
:: 

:LStart
if /i "%1" == "-h" goto LUsage

setlocal

if "%EXCELEXPORTER_HOME%" == "" (
    set EXCELEXPORTER_HOME=..\..
)

:: The Java classpath is used to localize the StringTemplate V4 template file. Here, it's
:: sufficient to assign those paths, which hold the templates. The launcher script
:: excelExporter.cmd takes care that the actual Java search path is set, too.
set CLASSPATH=templates

:: Find the launcher script.
set PATH=%PATH%;%EXCELEXPORTER_HOME%\dist

:: The first run of the tool does not configure any sorting.
call excelExporter.cmd ^
  --cluster-name "No Sorting" ^
  --input-file-name "simpleTable.xls" ^
  --output-file-name output/noSorting.txt ^
    --template-file-name sortedTable.stg ^
    --template-name table ^
  %*

:: The second run of the tool sorts the data only according to the title.
if ERRORLEVEL 1 (
    echo Abort of launch script due to errors in previous run of excelExporter
) else (
    call excelExporter.cmd ^
      --cluster-name "Titles in lexical order" ^
      --input-file-name "simpleTable.xls" ^
      --open-worksheet-template ^
        --open-column-attributes ^
          --column-title Title ^
          --sort-order-of-column lexical ^
      --output-file-name output/titlesLexical.txt ^
        --template-file-name sortedTable.stg ^
        --template-name table ^
      %*
)


:: The next run of the tool sorts the data only according to the title. The difference is
:: the choice for case sensitive ASCII sorting.
if ERRORLEVEL 1 (
    echo Abort of launch script due to errors in previous run of excelExporter
) else (
    call excelExporter.cmd ^
      --cluster-name "Titles in lexical order" ^
      --input-file-name "simpleTable.xls" ^
      --open-worksheet-template ^
        --open-column-attributes ^
          --column-title Title ^
          --sort-order-of-column ASCII ^
      --output-file-name output/titlesASCII.txt ^
        --template-file-name sortedTable.stg ^
        --template-name table ^
      %*
)


:: The next run of the tool sorts the data only according to the title, descending order.
if ERRORLEVEL 1 (
    echo Abort of launch script due to errors in previous run of excelExporter
) else (
    call excelExporter.cmd ^
      --cluster-name "Titles in lexical order" ^
      --input-file-name "simpleTable.xls" ^
      --open-worksheet-template ^
        --open-column-attributes ^
          --column-title Title ^
          --sort-order-of-column inverseLexical ^
      --output-file-name output/titlesInverseLexical.txt ^
        --template-file-name sortedTable.stg ^
        --template-name table ^
      %*
)


:: The next run of the tool sorts the data only according to the title. The difference is
:: the choice for case sensitive, descending sorting.
if ERRORLEVEL 1 (
    echo Abort of launch script due to errors in previous run of excelExporter
) else (
    call excelExporter.cmd ^
      --cluster-name "Titles in lexical order" ^
      --input-file-name "simpleTable.xls" ^
      --open-worksheet-template ^
        --open-column-attributes ^
          --column-title Title ^
          --sort-order-of-column inverseASCII ^
      --output-file-name output/titlesInverseASCII.txt ^
        --template-file-name sortedTable.stg ^
        --template-name table ^
      %*
)


:: The next run of the tool sorts the data principally according to the author and
:: subordinated in order of number of pages.
if ERRORLEVEL 1 (
    echo Abort of launch script due to errors in previous run of excelExporter
) else (
    call excelExporter.cmd ^
      --cluster-name "Authors in lexical order then number of pages" ^
      --input-file-name "simpleTable.xls" ^
      --open-worksheet-template ^
        --open-column-attributes ^
          --column-title Author ^
          --sort-order-of-column lexical ^
        --open-column-attributes ^
          --column-title "Number of Pages" ^
          --sort-order-of-column numerical ^
      --output-file-name output/authorsLexical_pagesNumerical.txt ^
        --template-file-name sortedTable.stg ^
        --template-name table ^
      %*
)


:: The next run of the tool sorts the data principally according to the author and
:: subordinated in decreasing order of number of pages.
::   Please note, in this example the priority of the sorting is given explicitly, not
:: implicitly by the order of the sort commands on the command line as before.
if ERRORLEVEL 1 (
    echo Abort of launch script due to errors in previous run of excelExporter
) else (
    call excelExporter.cmd ^
      --cluster-name "Authors in lexical order then number of pages" ^
      --input-file-name "simpleTable.xls" ^
      --open-worksheet-template ^
        --open-column-attributes ^
          --column-title "Number of Pages" ^
          --sort-order-of-column inverseNumerical ^
          --sort-priority-of-column 2 ^
        --open-column-attributes ^
          --column-title Author ^
          --sort-order-of-column lexical ^
          --sort-priority-of-column 1 ^
      --output-file-name output/authorsLexical_pagesInverseNumerical.txt ^
        --template-file-name sortedTable.stg ^
        --template-name table ^
      %*
)