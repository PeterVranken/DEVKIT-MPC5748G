#
# Generic Makefile for GNU Make 3.82 (MinGW port only)
#
# Build of project.
#
# Help on the syntax of this makefile is got at
# http://www.gnu.org/software/make/manual/make.pdf.
#
# Copyright (C) 2012-2024 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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
# The makefile is intended to be executed by the GNU make utility 3.82. The MinGW is
# required, the Cygwin/msys port handles paths under Windows differently and will fail. The
# easiest way to ensure the right port is an executable named mingw32-make.exe. In case of
# doubts, run "make --version" to see.
#   This makefile does not handle blanks in any paths or file names. Please rename your
# paths and files accordingly prior to using this makefile.
#
# Targets and Options
# ===================
#
# The makefile provides several targets, which can be combined on the command line.
#   Some options can be set on either command line or down below in this main makefile. For
# example, the build confiuration, DEBUG or PRODUCTION, can be set.
#   Get some help on the available targets and options by invoking the makefile using:
#
#   make help
#
# Input Files
# ===========
#
# The makefile compiles and links all source files which are located in a given list of
# source directories. The list of directories is configured in this main makefile, please
# look for the setting of srcDirList below.
#   A second list of files is found as cFileListExcl. These C/C++ files are excluded from
# build.

# The name of the project is used for several build products.
project := DEVKIT-MPC5748G-safe-RTOS

# safe-RTOS is a kind of library (although distributed as source code). It requires
# some application code. A few samples are part of this repository. The sample to compile
# can be selected through the makefile command line. Specify a source code folder, which
# contains the application code. This folder shall be added to the list srcDirList.
#   Note, this variable shall be usually set on the command line of make.
APP ?= code/application/default/

# Specify a blank separated list of directories holding source files. The directories are
# searched recursively for C/C++ and assembler source files.
srcDirList := code/system/

# Exclusion list: Edit the list of excluded files. A blank separated list of source files
# (with extension but without path) is expected, which are excluded from the compilation of
# all *.c, *.cpp and *.S.
cFileListExcl :=

# Additional include directories (besides the source directories and common, project
# independent paths).
incDirList := code/system/

# A blank separated list of C defines for compilation, with or without value.
#   There are some macros with predefined meaning for the build process. They impact the
# build process and they are forwarded to the compiler:
#   USE_EWL2: Link against the NXP Embedded Warrior Lib 2. Note, this option has never been
# tested as the licensing of the EWL is untransparent.
#   USE_NEWLIB: Link against the Open Source C library Newlib. One out of USE_EWL2 or
# USE_NEWLIB needs to be defined.
#   USE_FP_EMULATION_CLIB: If given, then all code on all cores won't use the floating
# point instructions. All cores can do floating point operations regardless of USE_Z2_CLIB,
# however it's slow. This option has been barely tested.
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
defineList := USE_NEWLIB \
#              LINK_IN_RAM

# Now go into the project independent implementation of the compile and link rules using
# the project specific settings made above.
sharedMakefilePath = makefile/
include $(sharedMakefilePath)parallelJobs.mk
