@echo off
setlocal
set CLASSPATH=..\raceTechnology\templates
set COMFRAMEWORK_CODEGENERATOR_HOME=..\..
set PATH=%PATH%;%COMFRAMEWORK_CODEGENERATOR_HOME%\dist
call codeGenerator ^
  --cluster-name AUTOSAR_sample ^
  --node-name ECU ^
  -op suppressUnaffectedSignals -ov true ^
  --bus-name CAN_RT ^
      -dbc ../dbcFiles/CAN_RT_attributed.dbc ^
  --output-file-name output/cif_swcCanInterface.arxml ^
    --template-file-name templates/swcCanInterface.arxml.stg ^
    --template-name swcCanInterface ^
  %*
