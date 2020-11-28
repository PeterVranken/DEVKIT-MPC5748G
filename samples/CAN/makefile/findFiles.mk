#
# Generic Makefile for GNU Make 3.82 (MinGW port only)
#
# Wildcard search for all source files in all specified source file trees.
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
ifndef FIND_FILES_INCLUDED
FIND_FILES_INCLUDED := 1

# Some core variables have already been set prior to reading this common part of the
# makefile. These variables are:
#   srcDirList: a blank separated list of directories holding source files
#   cFileListExcl: a blank separated list of source files excluded from the compilation of
# all *.S, *.c and *.cpp
#   incDirList: a blank separated list of directories holding header files. The directory
# names should end with a slash. The list must not comprise common, project independent
# directories and nor should the directories from srcDirList be included
#   APP: An optional, additional source root directory

# Unification of writing of include directories: Trailing slash, right path separator.
incDirList := $(call w2u,$(call trailingSlash,$(incDirList)))
#$(info incDirList := $(incDirList))

# Do a clean-up of the list of source folders. At the same time, add the source code tree
# of the selected application to compile together with the common code base.
srcDirList := $(call trailingSlash,$(APP) $(srcDirList))

# Determine the list of files to be compiled.
cFileList := $(call rwildcard,$(srcDirList),*.c *.cpp *.S)

# Subtract each excluded file from the list.
cFileList := $(filter-out $(cFileListExcl), $(cFileList))
#$(info $$(cFileList): $(cFileList))

# Determine the list of actually used source file directories. The list is required for the
# inlude commands for assembler and compiler. "sort" is used to remove the frequent
# duplicates.
srcDirInUseList := $(sort $(dir $(cFileList)))

# Determine the list of object files. We need to replace the file name extensions and
# change the path anchor.
ifneq ($(useFlatObjectFileStructure),)
    # Strip source file path designation.
    objFileList := $(notdir $(cFileList))
else
    # Use source file path designation for objcte files, too.
    objFileList := $(cFileList)
endif
objFileList := $(objFileList:.cpp=.o)
objFileList := $(objFileList:.c=.o)
objFileList := $(objFileList:.S=.o)
objFileList := $(addprefix $(targetDir)obj/,$(objFileList))
#$(info $$(objFileList): $(objFileList))

# Determine the list of actually used object file directories. The list is required to make
# the according directories (which the compiler doesn't silently do). "sort" is used to
# remove the frequent duplicates.
objDirList = $(sort $(dir $(objFileList)))

ifneq ($(useFlatObjectFileStructure),)
# Blank separated search path for source files and their prerequisites are required if
# don't copy the source folder tree for the object files. In this case, we can't directly
# relate object file paths to the source files paths in the pattern rules and we need to
# rely on searching the files.
VPATH := $(srcDirInUseList)
$(info VPATH: $(VPATH))
endif

# Export computed or modified variables.
export srcDirInUseList cFileList incDirList objFileList objDirList VPATH

else
$(error This makefile shouldn't be called twice. There's a problem in your makefile structure)
endif # FIND_FILES_INCLUDED
