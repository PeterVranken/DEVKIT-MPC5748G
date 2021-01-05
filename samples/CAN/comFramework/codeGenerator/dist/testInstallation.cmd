@echo off
java -cp ".;comFrameworkCodeGenerator-1.10.jar;ST-4.0.8.jar;antlr-4.5-complete.jar;log4j-1.2.11.jar" -ea codeGenerator.main.CodeGenerator --help
