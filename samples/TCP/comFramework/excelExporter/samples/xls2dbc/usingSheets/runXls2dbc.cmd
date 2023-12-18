@echo off
goto LStart
:LUsage
echo usage: runXls2Dbc [-v log-level] [-h] [--help]
echo   Run excelExporter sample xls2dbc. An Excel workbook is applied to model the
echo communication on a fictive CAN bus. excelExporter renders the information as CAN
echo communication database file (*.dbc File).
echo   All command line arguments except for -h are passed to the Java application
echo excelExporter. Use --help to get the usage message of the application.
echo   Most arguments of the Java application are defined by this launch script but you may
echo still pass -v log-level to control the application feedback. Use --help to get more
echo details.
echo   Normally this script needs to be started from the original location in the
echo distribution of excelExporter. However, you may set the environment variable
echo EXCELEXPORTER_HOME to make it independent of its location. Refer to the documentation
echo of excelExporter to get more details.
goto :eof

::
:: Copyright (c) 2015-2016, Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
::

:LStart
if /i "%1" == "-h" goto LUsage

setlocal

if "%EXCELEXPORTER_HOME%" == "" (
    set EXCELEXPORTER_HOME=..\..\..
)

:: The Java classpath is used to localize the StringTemplate V4 template file. Here, it's
:: sufficient to assign those paths, which hold the templates. The launcher script
:: excelExporter.cmd takes care that the actual Java search path is set, too.
set CLASSPATH=templates

:: Find the launcher script.
set PATH=%PATH%;%EXCELEXPORTER_HOME%\dist

:: Launch the Java application excelExporter.
excelExporter ^
  --log-file xls2dbc.log ^
  --cluster-name myECU ^
  --input-file-name "canComSpec.xlsx" -b bkCom ^
    --worksheet-names-are-identifiers ^
    --user-option-name ECU --user-option-value ECU ^
  --open-worksheet-template ^
    --association-by-tab Frames ^
    -ca -ct Name -soc lexical ^
  --open-worksheet-template ^
    --association-by-tab Signals ^
    -ca -ct Frame --is-grouping-column ^
    -ca -ct Name -soc lexical ^
  --open-worksheet-template ^
    --association-by-tab "Signal_Values" ^
    -ca -ct Frame --is-grouping-column ^
    -ca -ct Signal --is-grouping-column ^
  --output-file-name output\canComSpec.dbc ^
    --template-file-name xls2dbc.stg ^
    --template-name dbc ^
  %*
