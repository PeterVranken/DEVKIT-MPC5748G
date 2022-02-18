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
binFolder = bin/$(if $(findstring Windows,$(OS)),win,$(OS))/
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
