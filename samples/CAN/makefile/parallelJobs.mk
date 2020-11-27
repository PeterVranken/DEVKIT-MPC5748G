#
# Generic Makefile for GNU Make 3.82 (MinGW port only)
#
# Control the serialization of build steps, which must happen sequentially even if make is
# commanded to do parallel processing (i.e. jobs=n is given).
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
ifndef PARALLEL_JOBS_INCLUDED
PARALLEL_JOBS_INCLUDED := 1

# A normal GNU makefile cannot safely be run with the make command line switch -j if it
# combines targets to sequences of such. A common example is a derived target rebuild,
# which depends on clean and build in this order. The order of prerequisites is however
# regarded only in the standard sequential mode of make. If -j N is given, the
# prerequisites are made in parallel; in our example clean was not be guaranteed to be
# completed before the build begins.
#   make considers all prerequisites as long as independent and will make them in parallel
# as long as they are not explicitly coupled by inter-dependencies. Such inter-dependencies
# can however not always be expressed with the term "target: prerequisite". The result of
# clean is to have not any file left, so which file to state as prerequisite of a rule
# actually depending on clean? Moreover: Such a dependency is typically only optional, we
# do not want to do a clean always; a regular, always-present prerequisite "clean" of
# target build would obviously be counterproductive.
#   The only found way out of this is to use the makefile recursively. Now the build steps
# are properly serialized as steps of a recipe. Each step may benefit from parallelism but
# the execution of steps remains sequential. Each step is a single rule with fully expressed
# dependency hierarchy. The prerequisite(s) of the phony rules get the character of a .BEGIN
# rule, like some make derivatives offer. Caution, these are again not serialized in a
# defined order if make is invoked with -j.

# When we get here, some core variables have already been set in the main makefile, which
# is meant the user-configuration file. These variables are:
#   project: Name of the sub-project; used e.g. as name of the executable
#   srcDirList: a blank separated list of directories holding source files
#   cFileListExcl: a blank separated list of source files (with extension but without path)
# excluded from the compilation of all *.c and *.cpp
#   incDirList: a blank separated list of directories holding header files. The directory
# names should end with a slash. The list must not comprise common, project independent
# directories and nor must the directories listed in srcDirList be included
#   defineList: a blank separated list of defines, with or without value
#   sharedMakefilePath: The path to the common makefile fragments like this one. (Normally
# never customized)
#   targetRunArgs: A list of arguments passed to the compiled target when yielding target
# run
export project defineList sharedMakefilePath

# Consider this pseudo target as an alternative of selectively exporting variables.
#.EXPORT_ALL_VARIABLES:

# Load the makefile, the targets of which are run in a safe parallel way.
include $(sharedMakefilePath)help.mk
include $(sharedMakefilePath)globalVariables.mk
include $(sharedMakefilePath)commonFunctions.mk
include $(sharedMakefilePath)findFiles.mk
include $(sharedMakefilePath)compileAndLink.mk

# An unsolved problem: -j <n> is not automatically passed to sub-calls of make. Here, we
# wrote the switch explicitly into the command line. It works well, but it isn't what we
# want to have. The number of processes needs to be user controlled as it is situation
# dependent. Do we really need to have a new self-defined switch to control the argument of
# -j?
jobs ?= 4

# Define those command line options of recursive invocations of make, which are not
# propagated by the built-in automatisms.
mFlags = -f $(sharedMakefilePath)compileAndLink.mk -j $(jobs) --no-print-directory

# Run the complete build process with compilation, linkage and a2l and binary file
# modifications.
.PHONY: build
build: makeDir
	$(MAKE) $(mFlags) $(targetDir)$(projectExe)

# Rebuild all.
#   clean and makeDir do not interfere and maybe listed without explicit serialization.
.PHONY: rebuild
rebuild: clean
	$(MAKE) $(mFlags) makeDir
	$(MAKE) $(mFlags) $(targetDir)$(projectExe)
            
# Compile all C source files and assemble the *.S. Target directory tree needs to exist.
.PHONY: compile
compile: $(objListWithPath)

# Execute the compiled software under Windows if it could be built.
.PHONY: run
targetRunDir ?= $(targetDir)
run: makeDir
	$(info Running $(call u2w,$(abspath $(targetDir)$(projectExe))) $(targetRunArgs) in directory $(targetRunDir))
	$(MAKE) $(mFlags) $(targetDir)$(projectExe)
	cd $(targetRunDir) & pwd & $(call u2w,$(abspath $(targetDir)$(projectExe))) $(targetRunArgs)

else
$(error This makefile shouldn't be called twice. There's a problem in your makefile structure)
endif # PARALLEL_JOBS_INCLUDED
