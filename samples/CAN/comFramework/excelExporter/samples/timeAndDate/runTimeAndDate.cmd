@echo off
goto LStart
:LUsage
echo usage: runTimeAndDate [-v log-level] [-h] [--help]
echo   Run excelExporter sample timeAndDate. Two Excel workbooks hold data tables with
echo calendar dates as main information. The sample demonstrates how the dates can be
echo rendered in different ways.
echo   All command line arguments but -h are passed to the Java application excelExporter.
echo   Most arguments of the Java application are defined by this launch script but you may
echo still pass -v log-level to control the application feedback. Use --help to get the
echo usage message of the application.
echo   Normally this script needs to be started from the original location in the
echo distribution of excelExporter. However, you may set the environment variable
echo EXCELEXPORTER_HOME to make it independent of its location. Refer to the documentation
echo of excelExporter to get more details.
goto :eof

::
:: Copyright (c) 2016-2017, Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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
set CLASSPATH=

:: Find the launcher script.
set PATH=%PATH%;%EXCELEXPORTER_HOME%\dist

:: Lauch the Java application excelExporter.
call excelExporter.cmd ^
  --default-worksheet-group timeAndDate ^
  --input-file-name "phasesOfTheMoon.xlsx" ^
    --workbook-name moon ^
  --open-worksheet-selection ^
    --worksheet-name fullMoon ^
    --worksheet-by-tab Vollmond ^
    --applied-worksheet-template moon ^
  --open-worksheet-template ^
    --worksheet-template-name moon ^
    --index-title-row 2 ^
    --column-titles-are-identifiers ^
    --include-range-of-rows 3:1000 ^
    --include-range-of-columns 2 ^
    --open-column-attributes ^
      --column-name dateOfFullMoon ^
      --column-index 2 ^
      --sort-order-of-column numerical ^
  --input-file-name "usPresidents.xlsx" ^
    --workbook-name US ^
  --open-worksheet-selection ^
    --worksheet-name presidents ^
    --worksheet-by-tab "US Presidents" ^
    --applied-worksheet-template presidents ^
  --open-worksheet-template ^
    --worksheet-template-name presidents ^
    --index-title-row 3 ^
    --column-titles-are-identifiers ^
    --exclude-range-of-rows 1:3 ^
  --output-file-name output.txt ^
    --template-file-name timeAndDate.stg ^
    --template-name renderTable ^
  %*
