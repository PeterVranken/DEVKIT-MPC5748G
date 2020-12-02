@echo off
setlocal
set CLASSPATH=./templates
set COMFRAMEWORK_CODEGENERATOR_HOME=..\..\..\comFramework\codeGenerator
set PATH=%PATH%;%COMFRAMEWORK_CODEGENERATOR_HOME%\dist
call codeGenerator ^
  --cluster-name DEVKIT-MPC5775G ^
  --node-name ECU ^
  -op suppressUnaffectedSignals -ov true ^
  -op setUnusedPayloadBitsToOne -ov true ^
  -s checksum -re "(?i)^(checksum|.*(chk|crc)).*" ^
  -s SQC -re "(?i).*(aliv|sequence).*" ^
  --template-wrap-column 70 ^
  --bus-name PT ^
    -dbc dbcFiles/CAN_RT_attributed.dbc ^
    --include-frame-id 0:8520228 ^
    --include-frame-id 9175074:9306402 ^
    --include-frame-id 9438500:9503013 ^
    --include-frame-id 9569060:9699876 ^
    --include-frame-id 9767716:9962789 ^
    --include-frame-id 9963045 ^
    --include-frame-id 9962533 ^
    --include-frame-id 9510437 ^
    --include-frame-id 9509413 ^
    --include-frame-id 9241634 ^
    --include-frame-id 9241122 ^
  --output-file-name cde_canStatistics.h ^
    --template-file-name cde_canStatistics.h.stg ^
    --template-name canStatistics_h ^
  --output-file-name cde_canDataTables.c ^
    --template-file-name cde_canDataTables.c.stg ^
    --template-name dataTables_c ^
  --output-file-name cde_canDataTables.h ^
    --template-file-name cde_canDataTables.c.stg ^
    --template-name dataTables_h ^
  --output-file-name cap_precoCheck.h ^
    --template-file-name cap_precoCheck.h.stg ^
    --template-name precoCheck ^
  --output-file-name cap_canApi.h ^
    --template-file-name cap_canApi.c.stg ^
    --template-name canApiDecl ^
  --output-file-name cap_canApi.c ^
    --template-file-name cap_canApi.c.stg ^
    --template-name canApiDef ^
  --output-file-name codeGenerationReport.adoc ^
    --template-file-name templates/codeGenerationReport.adoc.stg ^
    --template-name asciidocReport ^
  --output-file-name overview.csv ^
    --template-file-name templates/overview.csv.stg ^
    --template-name overview ^
  %*

REM   --node-name PowerDisplay ^
REM    -dbc dbcFiles/sampleCanBus.dbc ^

REM   --node-name ECU ^
REM    -dbc dbcFiles/CAN_RT_attributed.dbc ^
