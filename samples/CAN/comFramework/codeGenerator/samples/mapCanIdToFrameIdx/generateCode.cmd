@echo off
setlocal
set CLASSPATH=..\raceTechnology\templates
set COMFRAMEWORK_CODEGENERATOR_HOME=..\..
set PATH=%PATH%;%COMFRAMEWORK_CODEGENERATOR_HOME%\dist
call codeGenerator ^
  --verbosity WARN ^
  --cluster-name demo ^
  --node-name ECU ^
  --bus-name RT_simplified ^
    -dbc ../dbcFiles/CAN_RT_simplified.dbc ^
  --bus-name CAN_RT_attributed ^
    -dbc ../dbcFiles/CAN_RT_attributed.dbc ^
    -id 0:2047 ^
    -id 9240610:9384482 ^
    -id 536870911 ^
  --bus-name CAN_RT ^
    -dbc ../dbcFiles/CAN_RT_repaired.dbc ^
    -id 0:2047 ^
    -id 9240866:9371938 ^
    -id 536870911 ^
  --output-file-name output/mci_mapCanIdToFrameIdx.c ^
    --template-file-name templates/mapCanIdToFrameIdx.c.stg ^
    --template-name fileContentsC ^
  --output-file-name output/mci_mapCanIdToFrameIdx.h ^
    --template-file-name templates/mapCanIdToFrameIdx.c.stg ^
    --template-name fileContentsH ^
  %*

