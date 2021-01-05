@echo off
goto LStart
:LUsage
echo usage: renderTable [-h] [--help] ^<desiredOutputTextFile^> ^<excelInputFile^> [-v log-level]
echo   Run excelExporter to render a simple list of data elements described in Excel workbook
echo ^<excelInputFile^>. The Excel workbook holds a simple table. Its rows form a linear list
echo of data objects for the rendering process.
echo   All command line arguments behind the designation of the Excel workbook are passed to
echo the Java application excelExporter. Most arguments of the Java application are defined
echo by this launch script but you may still pass -v log-level to control the application
echo feedback.
echo   Use --help to open all the documentation typically required to develop an excelExporter
echo application.
echo   Use -h to print this text.
echo   This script needs to locate the installation of excelExporter. The environment variable
echo EXCELEXPORTER_HOME needs to be set for that. Refer to the documentation of excelExporter
echo to get more details about its installation.
echo    ^<desiredOutputTextFile^>: The name of the generated output file (may include path).
echo    ^<excelInputFile^>: The name of the Excel workbook file (may include path).
goto :eof

REM
REM Copyright (c) 2016-2018, Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
REM

setlocal

:LStart
if /i "%1" == "" goto LUsage
if /i "%1" == "-h" goto LUsage

REM Find the launcher script of Java application excelExcorter.
if "%EXCELEXPORTER_HOME%" == "" (

    REM TODO Remove this code block if you decide to write the path into this script.
    echo Please, specifiy the path to your installation of excelExporter. The path to the
    echo folder is needed that contains folder "dist".
    echo   You can either persistently set environment variable EXCELEXPORTER_HOME or you can
    echo write the path into this script. Look for TODO tags.
    echo   If you didn't install excelExporter yet then have a look here:
    echo https://sourceforge.net/p/excelexporter/wiki/Home/
    goto :eof

    REM The installation path of tool excelExporter
    set EXCELEXPORTER_HOME=c:\ProgramFiles\excelExporter
)
set PATH=%PATH%;%EXCELEXPORTER_HOME%\dist

if /i "%1" == "--help" (

    REM Open the documents typically required for working with excelExporter

    REM Open the explanation of the concept of the data model
    start "excelExporter's Data Model - Concept" /MIN https://sourceforge.net/p/excelexporter/wiki/The%%20Data%%20Model/

    REM Open the explanation of the concept of data organization with excelExporter
    start "excelExporter's Data Model - Concept" /MIN https://sourceforge.net/p/excelexporter/wiki/Grouping%%20and%%20sorting/

    REM Open the Javadoc documentation of the data model
    start "excelExporter's Data Model - Javadoc" /MIN "%EXCELEXPORTER_HOME%\doc\dataModel\index.html"

    REM Open the manual of StringTemplate V4
    start "Manual ST4" /MIN "%EXCELEXPORTER_HOME%\doc\ST4-270115-0836-52.pdf"

    REM Run excelExporter with request for command line help
    call excelExporter.cmd --help

    REM Do nothing else
    goto :eof
)

if /i "%2" == "" goto LUsage

REM The Java classpath is used to localize the StringTemplate V4 template file(s). Here, it's
REM sufficient to assign those paths, which hold the templates. The launcher script
REM excelExporter.cmd takes care that the actual Java search path is set, too.
REM set CLASSPATH=.;%~dp0;%~dp0templates
echo Template search path: %CLASSPATH%

REM Retrieve the file names from the command line.
set outputFile=%1
set workbook=%2

REM The template file is taken from the same directory where this script resides in.
set st4GroupFile=myTemplate.stg

REM A kind of title for the project
set clusterName=%~n2

shift /1
shift /1

REM Run excelExporter to render the table
call excelExporter.cmd ^
  --cluster-name "%clusterName%" ^
  --input-file-name "%workbook%" ^
    --workbook-name workbook1 ^
    --open-worksheet-selection ^
      --worksheet-by-index 1 ^
      --worksheet-name worksheet1 ^
  --open-worksheet-template ^
    --association-by-index 1 ^
    --column-titles-are-identifiers ^
  --output-file-name "%outputFile%" ^
    --template-file-name "%st4GroupFile%" ^
    --template-name renderTable ^
  %1 %2 %3 %4 %5 %6
