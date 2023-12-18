@echo off
goto LStart
:LUsage
echo usage: runFirstSample [-v log-level] [-h] [--help]
echo   Run excelExporter sample firstSample. An Excel workbook holds a most simple flat
echo table. The rows form a linear list of data objects in the rendering process. The
echo sample demonstrates how the data can be rendered using most simple template
echo constructs.
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
set CLASSPATH=

:: Find the launcher script.
set PATH=%PATH%;%EXCELEXPORTER_HOME%\dist

:: Lauch the Java application excelExporter.
call excelExporter.cmd ^
  --input-file-name "EuropeanCapitals.xlsx" ^
  --output-file-name output.txt ^
    --template-file-name firstSample.stg ^
    --template-name renderTable ^
  --open-worksheet-template ^
    --open-column-attributes ^
      --column-title Country ^
      --sort-order-of-column lexical ^
  %*
