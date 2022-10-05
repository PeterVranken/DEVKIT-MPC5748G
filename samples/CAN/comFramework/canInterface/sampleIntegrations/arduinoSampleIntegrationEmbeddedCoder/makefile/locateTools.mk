#
# Makefile for GNU Make 3.81
#
# Locate all the external tools used by the other makefile fragments.
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
ifndef LOCATE_TOOLS_INCLUDED
LOCATE_TOOLS_INCLUDED := 1

# Use the Windows standard shell to execute commands.
ifeq ($(osName),win)
    #$(info Use Command Prompt as shell for Windows)
    SHELL = cmd
    .SHELLFLAGS = /c
endif

# Under Windows we have to look for gcc.exe rather than for gcc.
ifeq ($(osName),win)

    dotExe := .exe
else
    dotExe :=
endif

# Double-check environment.
#   The original Arduino code is referenced in the Arduino installation directory. By
# default the location of this is not known. To run this makefile an environment variable
# needs to point to the right location. This is checked now.
ifeq ($(strip $(ARDUINO_HOME)),)
    $(error Environment variable ARDUINO_HOME is not set. Required AVR tools can't \
            be located. Environment variable ARDUINO_HOME needs to point to an \
            installation of the Arduino IDE 1.8.x, i.e., to the folder, where arduino.exe \
            is located in)
endif
# Ensure a trailing slash at the end of this externally set variable.
ARDUINO_HOME := $(call trailingSlash,$(call w2u,$(ARDUINO_HOME)))
#$(info $$(ARDUINO_HOME): $(ARDUINO_HOME))

# The Arduino 1.8 installation no longer contains the executables, which provide the
# standard UNIX commands to a Windows system. We need them however for execution of this
# makefile. By default the location of such files is not known. To run this makefile an
# environment variable needs to point to the right location. This is checked now.
ifeq ($(strip $(UNIX_TOOLS_HOME)),)
  $(error Environment variable UNIX_TOOLS_HOME is not set. Required UNIX commands like \
          rm or mkdir can't be located. Environment variable UNIX_TOOLS_HOME needs to \
          point to a directory, which contains rm.exe, mkdir.exe, etc, or rm, mkdir on \
          a Linux system, respectively. These executables are distributed in many ways. \
          You may e.g. install Git (https://git-scm.com/downloads) - the installation \
          contains all needed files)
endif
# Ensure a trailing slash at the end of this externally set variable.
UNIX_TOOLS_HOME := $(call trailingSlash,$(call w2u,$(UNIX_TOOLS_HOME)))
#$(info $$(UNIX_TOOLS_HOME): $(UNIX_TOOLS_HOME))

mkdir := $(UNIX_TOOLS_HOME)mkdir$(dotExe)
rmdir := $(UNIX_TOOLS_HOME)rmdir$(dotExe)
cat := $(UNIX_TOOLS_HOME)cat$(dotExe)
echo := $(UNIX_TOOLS_HOME)echo$(dotExe)
cp := $(UNIX_TOOLS_HOME)cp$(dotExe)
rm := $(UNIX_TOOLS_HOME)rm$(dotExe)
gawk := $(UNIX_TOOLS_HOME)gawk$(dotExe)
awk := $(gawk)
touch := $(UNIX_TOOLS_HOME)touch$(dotExe)
mv := $(UNIX_TOOLS_HOME)mv$(dotExe)
avr-gcc := $(ARDUINO_HOME)hardware/tools/avr/bin/avr-gcc$(dotExe)
avr-g++ := $(ARDUINO_HOME)hardware/tools/avr/bin/avr-g++$(dotExe)
avr-ar := $(ARDUINO_HOME)hardware/tools/avr/bin/avr-ar$(dotExe)
avr-objcopy := $(ARDUINO_HOME)hardware/tools/avr/bin/avr-objcopy$(dotExe)
avr-size := $(ARDUINO_HOME)hardware/tools/avr/bin/avr-size$(dotExe)
avrdude := $(ARDUINO_HOME)hardware/tools/avr/bin/avrdude
avrdude_conf := $(ARDUINO_HOME)hardware/tools/avr/etc/avrdude.conf

# The make tool is different: We need to use the same one as has been invoked by the user
# and as is executing this makefile fragment.
make := $(MAKE)

#$(info make: $(make), gcc: $(avr-gcc), cp: $(cp), echo: $(echo))

.PHONY: versionGCC helpGCC builtinMacrosGCC
versionGCC:
	$(info GCC: $(call u2w,$(gcc)))
	$(avr-gcc) --version
helpGCC:
	$(info GCC: $(call u2w,$(gcc)))
	$(avr-gcc) -v --help
builtinMacrosGCC:
	$(avr-gcc) -dM -E - < nul

else
$(error This makefile shouldn't be called twice. There's a problem in your makefile structure)
endif # LOCATE_TOOLS_INCLUDED
