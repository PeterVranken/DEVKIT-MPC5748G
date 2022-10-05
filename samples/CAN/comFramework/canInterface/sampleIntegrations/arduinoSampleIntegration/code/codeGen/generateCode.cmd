@echo off
setlocal
set CLASSPATH="templates;templates/cbk_callbacks"
if "%COMFRAMEWORK_CODEGENERATOR_HOME%" == "" (
    set COMFRAMEWORK_CODEGENERATOR_HOME=..\..\..\..\..\codeGenerator
)
echo Running code generator at %COMFRAMEWORK_CODEGENERATOR_HOME%
set PATH=%COMFRAMEWORK_CODEGENERATOR_HOME%\dist;%PATH%
call codeGenerator ^
  --cluster-name arduinoSampleIntegration ^
  --node-name PowerDisplay ^
  -op suppressUnaffectedSignals -ov true ^
  -op generateLoggingCode -ov false ^
  -s checksum -re "(?i)^checksum.*" ^
  -s SQC -re "(?i).*sequence.*" ^
  --bus-name PT ^
    -dbc dbcFiles/sampleCanBus.dbc ^
  --output-file-name codeGenerationReport.adoc ^
    --template-file-name codeGenerationReport.adoc.stg ^
    --template-name asciidocReport ^
  --output-file-name cbk_callbacks.c ^
    --template-file-name cbk_callbacks.c.stg ^
    --template-name callbacksDef ^
  --output-file-name cbk_precoCheck.h ^
    --template-file-name cbk_precoCheck.h.stg ^
    --template-name precoCheck ^
  --output-file-name cbk_callbacks.h ^
    --template-file-name cbk_callbacks.c.stg ^
    --template-name callbacksDecl ^
  --output-file-name pck_packCanFrame.c ^
    --template-file-name pck_packCanFrame.c.stg ^
    --template-name packFctsDef ^
  --output-file-name pck_packCanFrame.h ^
    --template-file-name pck_packCanFrame.c.stg ^
    --template-name packFctsDecl ^
  --output-file-name cst_canStatistics.h ^
    --template-file-name cst_canStatistics.h.stg ^
    --template-name canStatistics_h ^
  %*
