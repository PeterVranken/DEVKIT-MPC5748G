@echo off
goto LStart
:LUsage
echo usage: runTreeView [-v log-level] [-h] [--help]
echo Run excelExporter sample treeView. An Excel workbook is rendered as a recursive HTML
echo tree. The applied StringTemplate V4 template is held generic and can be reused for
echo other Excel workbooks, which are designed to be processed with excelExporter.
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

:: The Java classpath is used to localize the StringTemplate V4 template files. Here, it's
:: sufficient to assign those paths, which hold the templates. The launcher script
:: excelExporter.cmd takes care that the actual Java search path is set, too.
set CLASSPATH=templates

:: Find the launcher script.
set PATH=%PATH%;%EXCELEXPORTER_HOME%\dist

:: The user options are entirely useless and just serve as sample code.
excelExporter ^
  --log-file treeView.log ^
  --cluster-name "Tree View" ^
  -op op1 -ov val1 ^
  -op op2 -ov val2 ^
  -op opInt -ov 2 ^
  -op opDbl -ov 2.71 ^
  -op opBool ^
  -op opBoolExpl1 -ov true ^
  -op opBoolExpl2 -ov false ^
  --default-worksheet-group defaultWorksheetGroup ^
  --sort-order-of-workbooks lexical ^
  --sort-order-of-worksheets numerical ^
  --input-file-name "simpleTable.xls" ^
  --input-file-name "canComSpec.xlsx" ^
    --workbook-name comSpec ^
    --open-worksheet-selection ^
        --worksheet-by-tab "Sample DBC" ^
        --worksheet-name wsFrame ^
        --applied-worksheet-template tmplFrames ^
    --open-worksheet-selection ^
        --worksheet-by-tab "Signal values" ^
        --worksheet-name wsSigVal ^
        --applied-worksheet-template tmplSigVals ^
  --open-worksheet-template ^
    --worksheet-template-name tmplFrames ^
    -ca -ct Frame --is-grouping-column -soc lexical ^
    --group frames ^
  --open-worksheet-template ^
    --worksheet-template-name tmplSigVals ^
    -ca -ci 1 --is-grouping-column -soc lexical ^
    -ca -ci 2 --is-grouping-column -soc lexical ^
    --group "Signal Values" ^
  --output-file-name HTML/treeView.html ^
    --template-file-name treeView.stg ^
    --template-name treeView ^
  %*
