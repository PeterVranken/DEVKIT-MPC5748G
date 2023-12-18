@echo off
setlocal
set CLASSPATH=templates;..\raceTechnology\templates
set COMFRAMEWORK_CODEGENERATOR_HOME=..\..
set PATH=%PATH%;%COMFRAMEWORK_CODEGENERATOR_HOME%\dist
call codeGenerator ^
  --cluster-name demoScratchPad ^
  --node-name ECU ^
  --bus-name RT_simplified ^
    -dbc ../dbcFiles/CAN_RT_simplified.dbc ^
  --output-file-name output/demoScratchPad.txt ^
    --template-file-name demoScratchPad.stg ^
    --template-name demoScratchPad ^
  %*
