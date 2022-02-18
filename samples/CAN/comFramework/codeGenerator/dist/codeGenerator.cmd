@echo off
goto begin
:usage
echo codeGenerator [...]
echo   Run the code generator, a Java application. Pass an arbitrary list of arguments to
echo the code generator. Consider to begin with --help.
echo   The script sets the Java class path as appropriate to start the code generator
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

setlocal

:: Check for the most typical errors
if "%COMFRAMEWORK_CODEGENERATOR_HOME%" == "" (
    echo Bad installation of comFramework-codeGenerator detected. You need to set the
    echo environment variable COMFRAMEWORK_CODEGENERATOR_HOME first. It should point to the
    echo application installation folder, which contains the folders dist, doc and samples
    goto :eof
)

:: A dedicated installation of the Java binaries may be used. The variable doesn't need to
:: be set; if not then the Java installation from the Windows search path would be used.
if not "%COMFRAMEWORK_JAVA_HOME%" == "" set PATH=%COMFRAMEWORK_JAVA_HOME%\bin;%PATH%

:: Launch the Java application. Pass all script arguments to the application.
::   The folders with the required templates can by added by setting the variable
:: CLASSPATH.
::   Note, the ANTLR jar contains a copy of ST V4, but not the last recent one. We place
:: the ST V4 jar before the ANTLR jar in order to make the maintenance release of ST V4
:: take effect. Unfortunately, the library versions printed at startup by the application
:: do not designate the actually loaded jars but those, which were used at application build
:: time. The printed versions are correct only if the classpath defined here is identical
:: to the one used for building.
java -cp "%COMFRAMEWORK_CODEGENERATOR_HOME%\dist\ST-4.3.1.jar;%COMFRAMEWORK_CODEGENERATOR_HOME%\dist\antlr-4.8-complete.jar;%COMFRAMEWORK_CODEGENERATOR_HOME%\dist\log4j-1.2.11.jar;%COMFRAMEWORK_CODEGENERATOR_HOME%\dist\comFrameworkCodeGenerator-1.10.jar;%CLASSPATH%" ^
     -ea ^
     codeGenerator.main.CodeGenerator %*