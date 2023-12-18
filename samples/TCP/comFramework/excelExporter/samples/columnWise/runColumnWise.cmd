@echo off
goto LStart
:LUsage
echo usage: runColumnWise [-v log-level] [-h] [--help]
echo   Run excelExporter sample columnWise. An Excel workbook holds a simple flat table.
echo The columns collect data items but - different to most of our other samples - the
echo entries found on a row are not necessarily related and they do not form an integral
echo object; considering all cells of a row the set of properties of an object is the basic
echo assumption of the internal data model of excelExporter and this assumption doesn't
echo match here. We can also say in this example do the column elements form each an
echo independent set of echo data items. The sample demonstrates how to handle this
echo structure even if the application's basic assumption about the data organization
echo doesn't match.
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

:: Run the Java application excelExporter.
call excelExporter.cmd ^
  --cluster-name "columnSets" ^
  --input-file-name "columnWise.xlsm" ^
  --output-file-name output/nameGenerator.java ^
    --template-file-name names.stg ^
    --template-name names ^
    --template-wrap-column 72 ^
  %*
