#
# Generic Makefile for GNU Make 3.81
#
# Compilation and linkage of C(++) code.
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
project := DEVKIT-MPC5748G-CAN

# Specify a blank separated list of directories holding source files. The directories are
# searched recursively for C/C++ and assembler source files.
srcDirList := code/

# Exclusion list: Edit the list of excluded files. A blank separated list of source files
# (with extension but without path) is expected, which are excluded from the compilation of
# all *.c and *.cpp
cFileListExcl :=

# Additional include directories (besides the source directories and common, project
# independent paths).
incDirList := code/application/

# A blank separated list of C defines for compilation, with or without value.
#   There are some macros with predefined meaning for the build process. They impact the
# build process and they are forwarded to the compiler:
#   USE_EWL2: Link against the NXP Embedded Warrior Lib 2. Note, this option has never been
# tested as the licensing of the EWL is untransparent.
#   USE_NEWLIB: Link against the Open Source C library Newlib. One out of USE_EWL2 or
# USE_NEWLIB needs to be defined.
#   USE_FP_EMULATION_CLIB: If given, then all code on all cores won't use the floating
# point instructions. All cores can do floating point operations regardless of USE_Z2_CLIB,
# however it's slow. This option has been barley tested.
#   USE_Z2_CLIB: The code can be compiled against binaries of the c runtime libs, which had
# been compiled either for the Z2 or for the Z4 core. Since the libraries are shared
# between all cores, only the Z2 variant is guaranteed safe if the Z2 core makes clib
# calls. The major difference between the cores is the availability of floating point
# instructions to the Z4 cores. As a matter of experience, if the Z2 doesn't do any
# floating point operations, it's still safe to link against the Z4 libraries to the
# benefit of the floating point performance of the two Z4 cores.
#   LINK_IN_RAM: If given, the linker will place all code and all data in RAM. The program
# under development can be loaded by the debugger without erasing and re-programming the
# flash, which reduces the turnaround time and which saves flash programming cycles.
defineList := USE_NEWLIB LINK_IN_RAM

# Now go into the project independent implementation of the compile and link rules using
# the project specific settings made above.
sharedMakefilePath = makefile/
include $(sharedMakefilePath)parallelJobs.mk
