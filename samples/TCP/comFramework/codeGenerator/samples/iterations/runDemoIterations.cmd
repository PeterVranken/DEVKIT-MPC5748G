@echo off
setlocal
set CLASSPATH=..\raceTechnology\templates
set COMFRAMEWORK_CODEGENERATOR_HOME=..\..
set PATH=%PATH%;%COMFRAMEWORK_CODEGENERATOR_HOME%\dist
call codeGenerator ^
  --cluster-name demoIterations ^
  --node-name ECU ^
  --bus-name RT_simplified ^
    -dbc ../dbcFiles/CAN_RT_simplified.dbc ^
  --bus-name DUP ^
    -dbc ../dbcFiles/duplicatedCanIDs.dbc ^
  --output-file-name output/demoIterations.txt ^
    --template-file-name templates/demoIterations.stg ^
    --template-name demoIterations ^
  %*
