# 
# Makefile for GNU Make 3.81
#
# Included makefile fragment, which specifies some application dependent settings.
#   The main purpose of this makefile is to specify the source file folders. Furthermore,
# this application requires to link against the floating point library for printf & co.
#
# Help on the syntax of this makefile is got at
# http://www.gnu.org/software/make/manual/make.pdf.
#
# Copyright (C) 2013-2022 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
#
# This program is free software: you can redistribute it and/or modify it
# under the terms of the GNU Lesser General Public License as published by the
# Free Software Foundation, either version 3 of the License, or any later
# version.
#
# This program is distributed in the hope that it will be useful, but WITHOUT
# ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
# FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License
# for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this program. If not, see <http://www.gnu.org/licenses/>.

# The standard list of source code directories is extended by some folders, which have been
# introduced specifically for this sample. Please note the makefile convention to let path
# names end on a slash
srcDirList += ../../code/eventDispatcher/ ../../code/memoryPool/ ../../code/connectors/     \
              ../../code/handleMaps/                                                        \
              code/rtos/rtosConfig/ code/codeGen/ code/integration/ code/APSW/              \
              code/canShield/
#$(info arduinoSampleIntegration.mk: Customized list of source folders for $(APP): $(srcDirList))

# This sample requires the floating point support for the standard I/O library (printf in
# the first place).
IO_FLOAT_LIB = 1
$(info arduinoSampleIntegration.mk: The application makes use of the stdio library with floating point support for printf & co)

# Add the rule for code generation.
include $(sharedMakefilePath)generateCode.mk
help_arduinoSampleIntegration = \
    $(info - generateCode: Run the code generator to generate the DBC dependent parts of the CAN interface)
