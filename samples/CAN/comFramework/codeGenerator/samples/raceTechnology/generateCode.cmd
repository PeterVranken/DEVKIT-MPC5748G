@echo off
setlocal
set CLASSPATH=..\raceTechnology\templates
set COMFRAMEWORK_CODEGENERATOR_HOME=..\..
set PATH=%PATH%;%COMFRAMEWORK_CODEGENERATOR_HOME%\dist
call codeGenerator ^
  --cluster-name raceCar ^
  --node-name ECU ^
  -op suppressUnaffectedSignals -ov true ^
  -op setUnusedPayloadBitsToOne -ov true ^
  -s checksum -re "(?i).*(chk|crc).*" ^
  -s alivCtr -re "(?i).*(sqc|aliv).*" ^
  --bus-name PT ^
    -dbc ../dbcFiles/CAN_RT_attributed.dbc ^
  --output-file-name output/codeGenerationReport.adoc ^
    --template-file-name templates/codeGenerationReport.adoc.stg ^
    --template-name asciidocReport ^
  --output-file-name output/overview.csv ^
    --template-file-name templates/overview.csv.stg ^
    --template-name overview ^
  --output-file-name output/canIf/crt_canRT.c ^
    --template-file-name templates/cif.c.stg ^
    --template-name canIfDef ^
    --template-arg-name-cluster cluster ^
  --output-file-name output/canIf/crt_canRT.h ^
    --template-file-name templates/cif.c.stg ^
    --template-name canIfDecl ^
  --output-file-name output/canIf/cst_canStatistics.h ^
    --template-file-name templates/cst_canStatistics.h.stg ^
    --template-name canStatistics_h ^
  --output-file-name output/canIf/crt_canRT.xml ^
    --template-file-name templates/TargetLinkDDImport.xml.stg ^
    --template-name tlDDImport ^
  --output-file-name output/canIf/crt_canRT.m ^
    --template-file-name templates/EmbeddedCoderInterface.m.stg ^
    --template-name ecInterface ^
  --output-file-name output/canIf/crt_canRT.a2l ^
    --template-file-name templates/ASAM-MCD-2MC.a2l.stg ^
    --template-name ASAM_MCD_2MC ^
  %*
