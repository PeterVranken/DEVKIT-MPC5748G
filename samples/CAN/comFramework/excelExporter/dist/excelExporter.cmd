@echo off
goto begin
:usage
echo excelExporter [...]
echo   Run the Excel exporter, a Java application. Pass an arbitrary list of arguments to
echo the code generator. Consider to begin with --help.
echo   The script sets the Java class path as appropriate to start the Excel exporter
echo application. However, the application itself uses the Java class path to find the
echo project dependent StringTemplate V4 template files. The location of these is not
echo anticipated by this script. Instead an extension of the Java class path may be given
echo via the CLASSPATH environment variable. The value of CLASSPATH is a semicolon
echo separated list of paths holding your project templates. (The local working directory
echo already is part of the class path.) Please note, setting the environment variable
echo should be done only locally as it'll contain project specific paths!
rem
rem  Copyright (C) 2015-2021 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
rem
rem  This program is free software: you can redistribute it and/or modify it
rem  under the terms of the GNU Lesser General Public License as published by the
rem  Free Software Foundation, either version 3 of the License, or any later
rem  version.
rem
rem  This program is distributed in the hope that it will be useful, but WITHOUT
rem  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
rem  FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License
rem  for more details.
rem
rem  You should have received a copy of the GNU Lesser General Public License
rem  along with this program. If not, see <http://www.gnu.org/licenses/>.
rem
goto :eof
:begin

if "%1" == "" goto usage

:: Check for the most typical errors
if "%EXCELEXPORTER_HOME%" == "" (
    echo Bad installation of excelExporter detected. You need to set the environment
    echo variable EXCELEXPORTER_HOME first. It should point to the application installation
    echo folder, which contains the folders dist, doc and samples
    goto :eof
)

:: A dedicated installation of the Java binaries may be used. The variable doesn't need to
:: be set; if not then the Java installation from the Windows search path would be used.
if not "%COMFRAMEWORK_JAVA_HOME%" == "" set PATH=%COMFRAMEWORK_JAVA_HOME%\bin;%PATH%

:: Launch the Java application. Pass all script arguments to the application.
::   The folders with the required templates can by added by setting the variable
:: CLASSPATH.
java -cp "%EXCELEXPORTER_HOME%\dist\ST-4.3.1.jar;%EXCELEXPORTER_HOME%\dist\antlr-4.8-complete.jar;%EXCELEXPORTER_HOME%\dist\log4j-api-2.4.jar;%EXCELEXPORTER_HOME%\dist\log4j-core-2.4.jar;%EXCELEXPORTER_HOME%\dist\excelExporter-1.0.jar;%EXCELEXPORTER_HOME%\dist\poi-3.13-20150929.jar;%EXCELEXPORTER_HOME%\dist\poi-ooxml-3.13-20150929.jar;%EXCELEXPORTER_HOME%\dist\poi-ooxml-schemas-3.13-20150929.jar;%EXCELEXPORTER_HOME%\dist\xmlbeans-2.6.0.jar;.;%CLASSPATH%" ^
     -ea ^
     excelExporter.main.ExcelExporter %*