@echo off
setlocal
set CLASSPATH=..\raceTechnology\templates
set COMFRAMEWORK_CODEGENERATOR_HOME=..\..
set PATH=%PATH%;%COMFRAMEWORK_CODEGENERATOR_HOME%\dist
codeGenerator ^
  --verbosity WARN ^
  --cluster-name demo ^
  --node-name ECU ^
  --bus-name RT_simplified ^
    -dbc ../dbcFiles/CAN_RT_simplified.dbc ^
  --bus-name DUP ^
    -dbc ../dbcFiles/duplicatedCanIDs.dbc ^
  --bus-name CAN_RT_attributed ^
    -dbc ../dbcFiles/CAN_RT_attributed.dbc ^
    -id 9240610:9384482 ^
  --bus-name CAN_RT ^
    -dbc ../dbcFiles/CAN_RT_repaired.dbc ^
    -id 9240866:9371938 ^
  --output-file-name output/testIterations.txt ^
    --template-file-name templates/testIterations.stg ^
    --template-name testFrameRefIterations ^
  %*

