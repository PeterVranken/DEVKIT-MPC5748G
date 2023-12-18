@echo off
setlocal
set CLASSPATH="templates"
if "%COMFRAMEWORK_CODEGENERATOR_HOME%" == "" (
    set COMFRAMEWORK_CODEGENERATOR_HOME=..\..\..\..\..\codeGenerator
)
echo Running code generator at %COMFRAMEWORK_CODEGENERATOR_HOME%
set PATH=%COMFRAMEWORK_CODEGENERATOR_HOME%\dist;%PATH%
call codeGenerator ^
  --cluster-name arduinoSampleIntegrationEC ^
  --node-name PowerDisplay ^
  -op suppressUnaffectedSignals -ov true ^
  -op generateLoggingCode -ov false ^
  -op useStorageClassImportedExternPointer ^
  -s checksum -re "(?i)^checksum.*" ^
  -s SQC -re "(?i).*sequence.*" ^
  --bus-name PT ^
    -dbc dbcFiles/sampleCanBus.dbc ^
  --output-file-name cst_canStatistics.h ^
    --template-file-name cst_canStatistics.h.stg ^
    --template-name canStatistics_h ^
  --output-file-name cap_canApi.h ^
    --template-file-name templates/cap_canApi.c.stg ^
    --template-name canApiDecl ^
  --output-file-name cap_canApi.c ^
    --template-file-name templates/cap_canApi.c.stg ^
    --template-name canApiDef ^
  --output-file-name cap_precoCheck.h ^
    --template-file-name templates/cap_precoCheck.h.stg ^
    --template-name precoCheck ^
  --output-file-name ../APSW/initEcBusObjects.m ^
    --template-file-name templates/initEcBusObjects.m.stg ^
    --template-name simulinkBusObjects ^
  --output-file-name cbk_callbacks.c ^
    --template-file-name cbk_callbacks.c.stg ^
    --template-name callbacksDef ^
  --output-file-name cbk_callbacks.h ^
    --template-file-name cbk_callbacks.c.stg ^
    --template-name callbacksDecl ^
  --output-file-name cap_canApi.targetLinkDDExtImport.xml ^
    --template-file-name templates/TargetLinkDDImport.xml.stg ^
    --template-name tlDDImport ^
  %*

:: The last file, cap_canApi.targetLinkDDExtImport.xml, has been generated only as a
:: demonstration of how to integrate the CAN interface with TargetLink designed application
:: software. This file is not used in this project.