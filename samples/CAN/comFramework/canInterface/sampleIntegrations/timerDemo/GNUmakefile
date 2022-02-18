#
# Generic Makefile for GNU Make 3.81
#
# Compilation and linkage of C(++) code.
#
# Help on the syntax of this makefile is got at
# http://www.gnu.org/software/make/manual/make.pdf.
#
# Copyright (C) 2012-2022 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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
# Preconditions
# =============
#
# The makefile is intended to be executed by the GNU make utility 3.81.
#   The name of the project needs to be assigned to the makefile macro projectName, see
# heading part of the code section of this makefile.
#   The Windows path needs to contain the location of the GNU compiler/linker etc. This is
# the folder containing e.g. gcc or gcc.exe.
#   For your convenience, the Windows path should contain the location of the GNU make
# processor. If you name this file either makefile or GNUmakefile you will just have to
# type "make" in order to get your make process running.
#   This makefile does not handle blanks in any paths or file names. Please rename your
# paths and files accordingly prior to using this makefile.
#
# Targets
# =======
#
# The makefile provides several targets, which can be combined on the command line. Get
# some help on the available targets by invoking the makefile using
#   make help
#
# Options
# =======
#
# Options may be passed on the command line.
#   The follow options may be used:
#   CONFIGURATION: The compile configuration is one out of DEBUG (default) or PRODUCTION. By
# means of defining or undefining macros for the C compiler, different code configurations
# can be produced. Please refer to the comments below to get an explanation of the meaning
# of the supported configurations and which according #defines have to be used in the C
# source code files.
#
# Input Files
# ===========
#
# The makefile compiles and links all source files which are located in a given list of
# source directories. The list of directories is hard coded in the makefile, please look
# for the setting of srcDirList below.
#   A second list of files is found as cFileListExcl. These C/C++ files are excluded from
# build.

# The name of the project is used for several build products.
project := timerDemo

# The directory, from where to run the compiled target when yielding target run. Defaults
# to the directory, where the compiled target is located.
#targetRunDir :=

# A list of arguments passed to the compiled target when yielding target run.
targetRunArgs := -v INFO -f short $(ARG)

# Specify a blank separated list of directories holding source files.
srcDirList := ../../code/eventDispatcher/ ../../code/memoryPool/ ../../code/connectors/	\
              code/

# Exclusion list: Edit the list of excluded files. A blank separated list of source files
# (with extension but without path) is expected, which are excluded from the compilation of
# all *.c and *.cpp
cFileListExcl :=

# Additional include directories (besides the source directories and common, project
# independent paths).
incDirList :=

# Now go into the project independent implementation of the compile and link rules using
# the project specific settings made above.
sharedMakefilePath = makefile/
include $(sharedMakefilePath)parallelJobs.mk
