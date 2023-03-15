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

# Only uncomment the next line when running this fragment independently for maintenance
# purpose.
#include commonFunctions.mk

# Use the Windows standard shell to execute commands.
ifeq ($(osName),win)
    #$(info Use Command Prompt as shell for Windows)
    SHELL = cmd
    .SHELLFLAGS = /c
endif


# The MinGW package comes along with a lot of application installers and so there may be
# more than one installation on the system and in the system's search path. A dedicated
# environment variable may be used to select a particular MinGW installation.
ifneq ($(MINGW_HOME),)
    # Caution: External paths (like here in the environment variable) do not comply with
    # the makefile style rule that paths end with the slash.
    minGwSearchPath := $(call w2u,$(MINGW_HOME))
    minGwSearchPath := $(call noTrailingSlash,$(minGwSearchPath))
    minGwSearchPath := $(addprefix $(minGwSearchPath)/,bin msys/1.0/bin)
else
    minGwSearchPath :=
endif


# Find the tools preferably in the folder specified by environment variable MINGW_HOME but
# look secondary in the system search path also. The system search path is expected as
# either colon or semicolon separated list of path designations in the environment variable
# PATH.
#   CAUTION: Blanks in path designations found in the environment variable PATH can't be
# processed. A search will not take place in those directories.
ifeq ($(osName),win)
toolsSearchPath := $(subst ;, ,$(call w2u,$(PATH)))
else
toolsSearchPath := $(subst :, ,$(call w2u,$(PATH)))
endif
toolsSearchPath := $(minGwSearchPath) $(toolsSearchPath)
#$(info Search path for external tools: $(toolsSearchPath))

# Under Windows we have to look for gcc.exe rather than for gcc.
ifeq ($(osName),win)
    dotExe := .exe
else
    dotExe :=
endif

# Now use the path search to get all absolute tool paths for later use.
cat := $(call pathSearch,$(toolsSearchPath),cat$(dotExe))
cp := $(call pathSearch,$(toolsSearchPath),cp$(dotExe))
echo := $(call pathSearch,$(toolsSearchPath),echo$(dotExe))
gawk := $(call pathSearch,$(toolsSearchPath),gawk$(dotExe))
awk := $(gawk)
gcc := $(call pathSearch,$(toolsSearchPath),gcc$(dotExe))
g++ := $(call pathSearch,$(toolsSearchPath),g++$(dotExe))
mkdir := $(call pathSearch,$(toolsSearchPath),mkdir$(dotExe))
mv := $(call pathSearch,$(toolsSearchPath),mv$(dotExe))
now := $(call pathSearch,$(toolsSearchPath),now$(dotExe))
pwd := $(call pathSearch,$(toolsSearchPath),pwd$(dotExe))
rm := $(call pathSearch,$(toolsSearchPath),rm$(dotExe))
rmdir := $(call pathSearch,$(toolsSearchPath),rmdir$(dotExe))
touch := $(call pathSearch,$(toolsSearchPath),touch$(dotExe))

# TODO The resource compiler is system specific. We've added the Windows variant only.
# Extend code for other systems if applicable.
ifeq ($(osName),win)
    windres := $(call pathSearch,$(toolsSearchPath),windres$(dotExe))
endif

# The make tool is different: We need to use the same one as has been invoked by the user
# and as is executing this makefile fragment.
make := $(MAKE)

.PHONY: versionGCC helpGCC builtinMacrosGCC
versionGCC:
	$(info GCC: $(call u2w,$(gcc)))
	$(gcc) --version
helpGCC:
	$(info GCC: $(call u2w,$(gcc)))
	$(gcc) -v --help
builtinMacrosGCC:
	$(gcc) -dM -E - < nul

# A plausibility check that tools could be loacted.
ifeq ($(and $(make),$(gcc),$(echo),$(rm),$(touch)),)
    $(info Make: $(make), gcc: $(gcc), echo: $(echo), rm: $(rm), touch: $(touch), windres: $(windres))
    $(error Required GNU tools can't be located. Most probable reasons are: You \
            didn't install the MinGW package or you didn't add the path to the MinGW \
            installation to the environment variable PATH and you didn't let environment \
            variable MINGW_HOME point to that directory or no appropriate distribution of \
            POSIX executables like rm or mkdir is in the search path)
endif

else
$(error This makefile shouldn't be called twice. There's a problem in your makefile structure)
endif # LOCATE_TOOLS_INCLUDED
