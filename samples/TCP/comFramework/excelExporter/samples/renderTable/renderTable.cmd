@echo off
goto LStart
:LUsage
echo usage:
echo   renderTable ^<generatedFile^> ^<excelWorkbook^> ^<templateGroupFile^> [-v log-level]
echo or:
echo   renderTable ^<newDefaultTemplateFile.stg^>
echo or:
echo   renderTable [-h]
echo or:
echo   renderTable [--help]
echo
echo   This is a wrapper script to run excelExporter with a minimalistic configuration.
echo The supported model is as such: An Excel workbook holds a most simple flat table in a
echo single worksheet. The rows form a linear list of data objects in the rendering
echo process. The first row holds column titles and these titles are the template
echo variables, through which the cells of a row can be accessed in the templates in
echo ^<templateGroupFile^>.
echo   ^<generatedFile^>: The name of the generated file, i.e. the file which holds the
echo rendered contents of the Excel table.
echo   If this is the only argument (and if this argument is not -h) the generated file is
echo not the rendered content of an Excel workbook but an initial StringTemplate V4
echo template group file, which is compatible with the simple model of this script. (The
echo file name extension should now be chosen as stg). You can use this template group file
echo as starting point for your actually required rendering process. Everything essential
echo is in place and you can focus on your actual task.
echo   Moreover, a Windows shell script is generated, which contains a suitable command line
echo to call excelExporter.
echo   ^<excelWorkbook^>: The name of the Excel workbook to be rendered. It needs to have a
echo single worksheet. Note, more than one worksheet can still be used but the structure of
echo the starting point template group file needs then to be extended. See help of
echo excelExporter for details.
echo   ^<templateGroupFile^>: The name of the template group file, which describes how to
echo render the contents of the Excel workbook. Note, the code generator application
echo locates this file through the JAVA class path. This wrapper adds the current working
echo directory and the root directory of the current drive to the class path. The file
echo designation you pass in needs to be relative to one of these. Most natural will be a
echo file in your current working directory and a file designation without path.
echo   -h: Print this help, i.e. the usage text of the wrapper script.
echo   Note, argument -h needs to be the first one on the command line. Otherwise it is
echo not recognized by the wrapper script and passed on to the code generator application.
echo   --help: Print the help of the code generator application excelExporter, which is
echo invoked by this wrapper script. The manual of StringTemplate V4 (how to write templates
echo in general) and the HTML documentation of the code generator application excelExporter
echo (how can the data be accessed that is read from the Excel file) are opened in separate
echo windows, too. You will likely need these documents to successfuly write your templates.
echo   -v: Verbosity level. Use --help to get more information
goto :eof

REM
REM Copyright (c) 2016-2019, Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
REM

:LStart
setlocal

REM Find the launcher script of Java application excelExcorter.
if "%EXCELEXPORTER_HOME%" == "" (
    REM TODO The installation path of tool excelExporter needs to be configured.
    echo Please, specifiy the path to your installation of excelExporter. The path to the
    echo folder is needed that contains folder "dist".
    echo   You can either persistently set environment variable EXCELEXPORTER_HOME or you can
    echo write the path into this script. Look for TODO tags.
    echo   If you didn't install excelExporter yet then have a look here:
    echo https://sourceforge.net/p/excelexporter/wiki/Home/

    REM TODO Remove the next line if you decide to write the path into this script.
    goto :eof

    set EXCELEXPORTER_HOME=c:\ProgramFiles\excelExporter
)
set PATH=%PATH%;%EXCELEXPORTER_HOME%\dist

if "%1" == "" goto LHelpWrapper
if /i "%1" == "-h" goto LHelpWrapper
if /i "%1" == "--help" goto LHelpExcelExporter
goto LNoHelpWrapper

:LHelpWrapper

REM Print usage and quit
goto LUsage

:LHelpExcelExporter

REM Open the manual of StringTemplate V4
start "Manual ST4" /MIN %~dp0ST4-270115-0836-52.pdf

REM Open the documentation of the data model
start "Data Model" /MIN %~dp0dataModelForStringTemplateV4.html

REM Run excelExporter with request for command line help
call excelExporter.cmd --help
goto :eof

:LNoHelpWrapper

REM Call of wrapper's wizard to generated a default template group file?
if "%2" == "" goto LCreateNewTemplate

REM Else: Normal run of application

if "%1" == "" goto LUsage
if "%2" == "" goto LUsage
if "%3" == "" goto LUsage

set outputFile=%1
set workbook=%2
set st4GroupFile=%3
shift /1
shift /1
shift /1

REM The Java classpath is used to localize the StringTemplate V4 template file. Here, it's
REM sufficient to assign those paths, which hold the templates. The launcher script
REM excelExporter.cmd takes care that the actual Java search path is set, too.
set CLASSPATH=.;/

REM Lauch the Java application excelExporter.
call excelExporter.cmd ^
  --input-file-name "%workbook%" ^
  --open-worksheet-template ^
    --association-by-index 1 ^
    --column-titles-are-identifiers ^
  --output-file-name "%outputFile%" ^
    --template-file-name "%st4GroupFile%" ^
    --template-name renderTable ^
  %1 %2 %3 %4 %5 %6
goto :eof


:LCreateNewTemplate
REM Create a new StringTemplate V4 template group file. This is a convenience function of
REM the wrapper script. The template group file will be a valuable starting point for the
REM user's actually required template file.
set CLASSPATH=%~dp0.
if not "%~x1" == ".stg" (
    set templateGroupFile=%1.stg
) else (
    set templateGroupFile=%1
)
call excelExporter.cmd ^
  --log-level warn ^
  --cluster-name "GenerateTemplate" ^
  -op templateGroupFile -ov "%templateGroupFile%" ^
  --output-file-name "%~dpn1.stg" ^
    --template-file-name defaultTemplate.stg ^
    --template-name defaultTemplate ^
  --output-file-name "%~dpn1.ps1" ^
    --template-file-name shellScript.stg ^
    --template-name shellScriptToRunExcelExporter

goto :eof