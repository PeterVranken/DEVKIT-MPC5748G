:: Upload the compiled Arduino sample (RTuinOS_arduinoSampleIntegrationEC.hex) to a connected
:: ATmega 2560 board. Run this script solely from the directory where the hex file is
:: located in.

setlocal

:: TODO Adjust the path and port setting below, remove this and the next two lines and re-run the script.
@echo TODO Edit script upload.cmd and specify the path to your Arduino installation and the appropriate COM port prior to first use
goto :eof

:: Required configuration: The installation path of the Arduino system 1.8.x
set ARDUINO_HOME=C:\ProgramFiles\arduino-1.8.19

:: Required configuration: Assign your COM port for upload. Open Desktop/Computer
:: Icon/Manage/Device Manager/Ports (COM & LPT) to find out, which COM port your Arduino
:: Mega board is connected to.
set COM_PORT=COM7
"%ARDUINO_HOME%\hardware\tools\avr\bin\avrdude.exe"         ^
    -C"%ARDUINO_HOME%\hardware\tools\avr\etc\avrdude.conf"  ^
    -v -patmega2560 -cWiring                                ^
    -P%COM_PORT% -b115200                                   ^
    -D -Uflash:w:RTuinOS_arduinoSampleIntegrationEC.hex:i
