#
# Generic Makefile for GNU Make 3.82 (MinGW port only)
#
# Some global variable settings shared between all makefiles.
#
# Help on the syntax of this makefile is got at
# http://www.gnu.org/software/make/manual/make.pdf.
#
# Copyright (C) 2012-2020 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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
#
ifndef GLOBAL_VARIABLES_INCLUDED
GLOBAL_VARIABLES_INCLUDED := 1

# The name of the project is used for several build products. Should have been set in the
# calling makefile otherwise we have a reasonable default.
project ?= appName

# The build configuration. It is not set anywhere but controlled from the command line of
# make. Here, we just define the default value DEBUG.
CONFIG ?= DEBUG

# Choose optimization level for production compilation.
#   O0: 100%
#   Og: 72%
#   O3: 41%
#   O2: 41%
#   O1: 52%
#   Os: 50%
#   Ofast: 41%, likely same as -O3
productionCodeOptimization := -Ofast

# Searching for files and other operations differ a bit depending on the underlying
# operating system. We check, which one we are running on. This code has been adopted from
# https://stackoverflow.com/questions/714100/os-detecting-makefile (Nov 27, 2020).
ifneq ($(OS),Windows_NT)
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Linux)
        OS := LINUX
    endif
    ifeq ($(UNAME_S),Darwin)
        OS := MAC
    endif
endif
#$(info Operating system: $(OS))

# General settings for the makefile.
ifeq ($(OS),Windows_NT)
    SHELL := cmd
    .SHELLFLAGS := /c
endif

# If .ONESHELL is mentioned as a target, then when a target is built all lines of the
# recipe will be given to a single invocation of the shell rather than each line being
# invoked separately.
.ONESHELL:

# Where to place all generated products?
#   Determine the name of the root folder of all build products. The name should
# distinguish between all supported target systems. Furthermore, under Windows it should if
# possible distinguish between 32 or 64 Bit systems.
targetDir := bin/ppc/$(CONFIG)$(if $(filter LINK_IN_RAM,$(defineList)),-RAM,)/

endif # GLOBAL_VARIABLES_INCLUDED