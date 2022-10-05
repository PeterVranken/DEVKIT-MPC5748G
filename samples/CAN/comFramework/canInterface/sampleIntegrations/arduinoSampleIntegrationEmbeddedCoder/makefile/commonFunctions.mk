#
# Generic Makefile for GNU Make 3.82 (MinGW port only)
#
# Some common purpose makefile functions, which are accessible from all makefiles.
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
ifndef COMMON_FUNCTIONS_INCLUDED
COMMON_FUNCTIONS_INCLUDED := 1

# Return a string indicating the operating system, the makefile executes on. Get "win" for
# a Windows system or "linux" otherwise.
osName = $(if (or $(call eq,$(OS),WINDOWS),$(call eq,$(OS),Windows_NT)),win,linux)
# Example:
#ifeq ($(osName),win)
#    $(info We are executing on Windows)
#else
#    $(warning Is this well-prepared for Linux?)
#endif

# Return a end of line character. No parameters, can be called without $(call).
define EOL


endef
# Example:
# $(info first line$(EOL)second line)


# Function isInDefineList
#   The main makefile offers a variable "defineList", with user configurable settings for
# the build. This function supports the use of the list in conditional parts of the
# makfile, i.e. using ifeq/ifneq/ifdef/ifndef.
#   The call of this function returns the word true if $(1) is element of $(defineList) and
# the word false otherwise. Note, "true" and "false" are symbols but no Boolean constants.
# The use of these particular result values has no technical significance but supports
# having readable conditional makefile code. See example.
#   $(1): The name of a define to be checked for presence in $(defineList).
isInDefineList = $(if $(filter $(1),$(defineList)),true,false)
# Example:
#ifeq ($(call isInDefineList,DEFINE_OF_INTEREST),true)
#$(info DEFINE_OF_INTEREST is element of $(defineList))
#else
#$(info DEFINE_OF_INTEREST isn't element of $(defineList))
#endif


# Function pathSearch
#   Look for a single file in a search path, i.e. a list of directories.
#   $(1): Blank separated path list to search through
#   $(2): File name without path to be searched in the path
pathSearch = $(firstword $(wildcard $(addsuffix $(2),$(call trailingSlash,$(1)))))
# Example:
#$(info make is $(call pathSearch,$(subst ;, ,$(PATH)),make.exe))


# Function noTrailingSlash
#   Remove a possibly existing terminating slash from a list of path or file designations.
# Designations not ending with a slash are returned unchanged.
#   $(1): Blank separated paths list ending or not ending on shlashes.
noTrailingSlash = $(patsubst %/,%,$(1))
# Example:
#$(info Cleaned path designations: $(call noTrailingSlash,/ c:/ c:/tmp/ c:/tmp/file c:/tmp/file.c c:/tmp.x/file.h c: c:/tmp))


# Function trailingSlash
#   Ensure a possibly not yet present terminating slash for a list of path designations.
# Designations already ending with a slash are returned unchanged.
#   $(1): Blank separated paths list ending or not ending on shlashes.
trailingSlash = $(addsuffix /,$(call noTrailingSlash,$(1)))
# Example:
#$(info Proper path designations: $(call trailingSlash,/ c:/ c: c:/tmp/ c:/tmp c:/tmp/file c:/tmp/file.c c:/tmp.x/file.h c: c:/tmp))


# Recursive search for files. Use cases are similar to those of built-in function wildcard.
# This basis of this code has been gratefully taken from
# http://blog.jgc.org/2011/07/gnu-make-recursive-wildcard-function.html (1.4.2017). A small
# change supports the search of a list of directories all at once.
#   $(1): A blank separated list of directories, ending with slash. The empty field means the
# current working directory and yields the same file as ./ All of these directories are
# searched for all files matching against any of the wildcards given in $(2).
#   $(2): A blank separated list of wildcards in the form *.<extension>
rwildcard = $(strip $(foreach d,$(wildcard $(addsuffix *,$(1))),$(call rwildcard,$(d)/,$(2)) $(filter $(subst *,%,$(2)),$(d))))
# Usage is as follows. First, all C files in the current directory (or below).
#$(info $(call rwildcard,,*.c))
#$(info $(call rwildcard,./,*.c))
# Then all C files in c:/tmp:
#$(info $(call rwildcard,c:/tmp/,*.c))
# Multiple patterns can be used. Here are all C and H files:
# Multiple directories and patterns can be used. Here are all C and H files in two directories:
#$(info $(call rwildcard,test/helloWorld/ code/,*.c *.h))


# Helper functions: Path separator conversion in either direction. Principally, we use the
# native path convention of the make tool (UNIX style, forward shlash). When calling
# external tools it might be required to convert this style to Windows' backslash notation.
#   Only parameter is the path to convert.
u2w = $(subst /,\,$(1))
w2u = $(subst \,/,$(1))
#   Example:
# $(info mkdir $(call u2w,c:/00_HybridMaster/Components))



# Test for equality: A wrapper around the required ugly string comparison operations.
#   The macro returns either the empty string (condition is false) or the string "true".
#   $(1) and $(2) are the two compared strings.
eq = $(if $(1)$(2),$(and $(findstring $(1),$(2)),$(findstring $(2),$(1)),true),true)
#$(info 2==3: $(call eq,2,3), 2==2: $(call eq,2,2), ""=="": $(call eq,,), 1=="": $(call eq,1,),""==1: $(call eq,,1))


# Test if a file is in a list of such. Can be used in conditional expressions to handle
# such a file specifically.
#   The file is addressed by $(notdir $(1)), i.e. it is addressed to by only its raw file
# name with extension.
#   $(1): The file (can also be a list of such). The macro expands to non-empty if the file
# (or one or more of the files in the list) matches one of the elements of the list $(2).
# Otherwise it expands to nothing. The macro can thus be used as condition c of
# $(if c, ... , ...)
#   $(2): The list of file names to test. Only provide raw file names with extension.
isFileInList = $(if $(filter $(2), $(notdir $(1))),1,)
#$(info "$(call isFileInList, a/x/test.c path/c, a b xtest.c)")

endif # COMMON_FUNCTIONS_INCLUDED
