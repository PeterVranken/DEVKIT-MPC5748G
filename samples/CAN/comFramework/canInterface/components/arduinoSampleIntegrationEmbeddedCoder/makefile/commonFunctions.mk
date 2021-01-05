# 
# Makefile for GNU Make 3.81
#
# Collection of definitions of general purpose helper functions.
#
# Help on the syntax of this makefile is got at
# http://www.gnu.org/software/make/manual/make.pdf.
#


# Return a end of line character. No parameters, can be called without $(call).
define EOL


endef
# Example:
# $(info first line$(EOL)second line)


# Function binFolder
#   Determine the name of the root folder of all build products. The name should
# distinguish between all supported target systems. Furthermore, under Windows it should if
# possible distinguish between 32 or 64 Bit systems.
binFolder = bin/$(if $(findstring Windows,$(OS)),$(if $(findstring 64,$(MINGW_HOME)),win64,win32)/,$(OS)/)
# Example:
# $(info Target folder for produced binaries is $(call binFolder))


# Function pathSearch
#   Look for a single file in a search path, i.e. a list of directories.
# $(1): Blank separated path list (not ending on shlashes) to search through
# $(2): File name without path to be searched in the path
pathSearch = $(firstword $(wildcard $(addsuffix /$(2),$(1))))
# Example:
#$(info make is $(call pathSearch,$(subst ;, ,$(PATH)),make.exe))


# Function noTrailingSlash
#   Remove a possibly existing terminating slash from a list of path or file designations.
# Designations not ending with a slash are returned unchanged.
#   $(1): Blank separated paths list ending or not ending on shlashes.
noTrailingSlash = $(patsubst %/,%,$(1))
# Example:
#$(info Cleaned path designations: $(call noTrailingSlash,/ c:/ c:/tmp/ c:/tmp/file c:/tmp/file.c c:/tmp.x/file.h c: c:/tmp))


# Helper functions: Path separator conversion in either direction. Principally, we use the
# native path convention of the make tool (UNIX style, forward shlash). When calling
# external tools it might be required to convert this style to Windows' backslash notation.
#   Only parameter is the path to convert.
u2w = $(subst /,\,$(1))
w2u = $(subst \,/,$(1))
#   Example:
# $(info mkdir $(call u2w,c:/00_HybridMaster/Components))


# A list of file names is written linewise into a text file. The file can be used as input
# to other tools, like a linker or archiver.
# Return value: undefined. The caller should invalidate the return value by putting the
# call of the macro into a string eating expression, e.g. $(and $(call ...),)
# $(1): Name of generated file
# $(2): List of file names
# Usage:
#   The macro can be called inside the recipe of a rule or unconditionally in the global
# part of a makefile. To do so assign the undefined return value to a dummy variable.
# Implementation hints:
#   Using the stupid Windows shell we can write to a file only by appending line by line to
# an existing file. In order to get a defined starting point we need to delete any exiting
# file of given name in the first line.
#   The next lines write the lines of the file as a kind of side effect of the text
# macro expansions.
define createFileList
    $(shell $(echo) $(firstword $(2)) > $(1))
    $(foreach srcFile,$(wordlist 2,$(words $(2)),$(2)),$(shell $(echo) $(srcFile) >> $(1)))
endef # createFileList
#   Example:
#$(info Create file tmp.lst$(and $(call createFileList,tmp.lst,file1.c file2.c file3.c),))

