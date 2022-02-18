@echo off
setlocal
set CLASSPATH="templates"
if "%COMFRAMEWORK_CODEGENERATOR_HOME%" == "" (
    set COMFRAMEWORK_CODEGENERATOR_HOME=..\..\..\..\..\..\codeGenerator\trunk
)
set PATH=%COMFRAMEWORK_CODEGENERATOR_HOME%\dist;%PATH%
call codeGenerator ^
  -v WARN ^
  --cluster-name canInterfaceMTTest ^
  --node-name ECU ^
  -op suppressUnaffectedSignals -ov true ^
  -s checksum -re "(?i)^checksum.*" ^
  -s SQC -re "(?i).*sequence.*" ^
  --template-wrap-column 70 ^
  --bus-name B1 ^
    -dbc dbcFiles/canBus_01.dbc ^
  --bus-name B2 ^
    -dbc dbcFiles/canBus_02.dbc ^
  --bus-name B3 ^
    -dbc dbcFiles/canBus_03.dbc ^
  --bus-name B4 ^
    -dbc dbcFiles/canBus_04.dbc ^
  --bus-name B5 ^
    -dbc dbcFiles/canBus_05.dbc ^
  --bus-name B6 ^
    -dbc dbcFiles/canBus_06.dbc ^
  --bus-name B7 ^
    -dbc dbcFiles/canBus_07.dbc ^
  --bus-name B8 ^
    -dbc dbcFiles/canBus_08.dbc ^
  --bus-name B9 ^
    -dbc dbcFiles/canBus_09.dbc ^
  --bus-name B10 ^
    -dbc dbcFiles/canBus_10.dbc ^
  --output-file-name ../APSW/e2e_frameProtection.c ^
    --template-file-name e2e_frameProtection.c.stg ^
    --template-name e2eProtection_c ^
  --output-file-name ../APSW/e2e_frameProtection.h ^
    --template-file-name e2e_frameProtection.c.stg ^
    --template-name e2eProtection_h ^
  --output-file-name ../osEmulation/ose_dataTables.c ^
    --template-file-name ose_dataTables.c.stg ^
    --template-name dataTables_c ^
  --output-file-name ../osEmulation/ose_dataTables.h ^
    --template-file-name ose_dataTables.c.stg ^
    --template-name dataTables_h ^
  --output-file-name ../osEmulation/ose_unpackAndCheckFrame.c ^
    --template-file-name ose_unpackAndCheckFrame.c.stg ^
    --template-name ose_e2eValidation_c ^
  --output-file-name ../osEmulation/ose_unpackAndCheckFrame.h ^
    --template-file-name ose_unpackAndCheckFrame.c.stg ^
    --template-name ose_e2eValidation_h ^
  --output-file-name cdt_canDataTables.c ^
    --template-file-name cdt_canDataTables.c.stg ^
    --template-name dataTables_c ^
  --output-file-name cdt_canDataTables.h ^
    --template-file-name cdt_canDataTables.c.stg ^
    --template-name dataTables_h ^
  --output-file-name cst_canStatistics.h ^
    --template-file-name cst_canStatistics.h.stg ^
    --template-name canStatistics_h ^
  --output-file-name cap_canApi.h ^
    --template-file-name cap_canApi.c.stg ^
    --template-name canApiDecl ^
  --output-file-name cap_canApi.c ^
    --template-file-name cap_canApi.c.stg ^
    --template-name canApiDef ^
  --output-file-name cap_precoCheck.h ^
    --template-file-name cap_precoCheck.h.stg ^
    --template-name precoCheck ^
  %*
