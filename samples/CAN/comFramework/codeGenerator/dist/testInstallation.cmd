@echo off

:: A dedicated installation of the Java binaries may be used. The variable doesn't need to
:: be set; if not then the Java installation from the Windows search path would be used.
if not "%COMFRAMEWORK_JAVA_HOME%" == "" set PATH=%COMFRAMEWORK_JAVA_HOME%\bin;%PATH%

java -cp ".;comFrameworkCodeGenerator-1.11.jar;antlr-4.10.1-complete.jar;log4j-1.2.11.jar" -ea codeGenerator.main.CodeGenerator --help
