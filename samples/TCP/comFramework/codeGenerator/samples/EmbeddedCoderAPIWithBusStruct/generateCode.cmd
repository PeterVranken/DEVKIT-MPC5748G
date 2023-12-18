@echo off
goto LStart
:LUsage
echo usage: generateCode [-h] [--help]
echo Run codeGenerator sample EmbeddedCoderAPIWithBusStruct. The CAN interface
echo specification is generated, which is compatible with The MathWorks' Embedded Coder.
echo The Interface is modelled as a bus. In C the according set of nested structs is
echo generated and in MATLAB code is the it describing bus struct generated. The bus struct
echo can be attached to an Embedded Coder model and the Embedded Coder will generate C code
echo from the model, which directly addresses to the right fields in the nested structs.
echo   All command line arguments but -h are passed to the Java application codeGenerator.
echo Use --help to get the usage message of the Java application.
echo   Most arguments of the Java application are defined by this launch script but you may
echo still pass -v log-level to control the application feedback. Use --help to get more
echo details.
echo   Normally this script needs to be started from the original location in the
echo distribution of codeGenerator. However, you may set the environment variable
echo COMFRAMEWORK_CODEGENERATOR_HOME to make it independent of its location. Refer to the
echo documentation of codeGenerator to get more details.
goto :eof

::
:: Copyright (c) 2016, Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
::

:LStart
if /i "%1" == "-h" goto LUsage

setlocal

if "%COMFRAMEWORK_CODEGENERATOR_HOME%" == "" (
    set COMFRAMEWORK_CODEGENERATOR_HOME=..\..
)

:: The Java classpath is used to localize the StringTemplate V4 template files. Here, it's
:: sufficient to assign those paths, which hold the templates. The launcher script
:: excelExporter.cmd takes care that the actual Java search path is set, too.
set CLASSPATH=templates;..\raceTechnology\templates

:: Find the launcher script.
set PATH=%PATH%;%COMFRAMEWORK_CODEGENERATOR_HOME%\dist

call codeGenerator.cmd ^
  --cluster-name ecSample ^
  --node-name PowerDisplay ^
  -op suppressUnaffectedSignals -ov true ^
  -op setUnusedPayloadBitsToOne -ov false ^
  -op useStorageClassImportedExternPointer ^
  -s checksum -re "(?i)^checksum.*" ^
  -s SQC -re "(?i).*sequence.*" ^
  --bus-name PT ^
    -dbc ../dbcFiles/sampleCanBus.dbc ^
  --output-file-name output/cst_canStatistics.h ^
    --template-file-name cst_canStatistics.h.stg ^
    --template-name canStatistics_h ^
  --output-file-name output/cap_canApi.h ^
    --template-file-name templates/cap_canApi.c.stg ^
    --template-name canApiDecl ^
  --output-file-name output/cap_canApi.a2l ^
    --template-file-name cap_canApi.a2l.stg ^
    --template-name canApiA2lDecl ^
  --output-file-name output/cap_canApi.c ^
    --template-file-name templates/cap_canApi.c.stg ^
    --template-name canApiDef ^
  --output-file-name output/cap_precoCheck.h ^
    --template-file-name templates/cap_precoCheck.h.stg ^
    --template-name precoCheck ^
  --output-file-name output/initEcBusObjects.m ^
    --template-file-name templates/initEcBusObjects.m.stg ^
    --template-name simulinkBusObjects ^
  %*

