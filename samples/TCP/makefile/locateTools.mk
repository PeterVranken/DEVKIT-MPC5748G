#
# Generic Makefile for GNU Make 3.82 (MinGW port only)
#
# Inspect environment variables and system search path to find out, where the executables,
# compiler, linker, etc., are located.
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
ifndef LOCATE_TOOLS_INCLUDED
LOCATE_TOOLS_INCLUDED := 1

# Find the tools preferably in the folder specified by environment variable GCC_POWERPC_HOME
# but look secondary in the system search path also. The system search path is expected as
# either colon or semicolon separated list of path designations in the environment variable
# PATH.
#   CAUTION: Blanks in path designations found in the environment variable PATH can't be
# processed. A search will not take place in those directories.
ifeq ($(call isWin),true)
    toolsSearchPath := $(subst ;, ,$(call w2u,$(PATH)))
else
    toolsSearchPath := $(subst :, ,$(PATH))
endif
toolsSearchPath := $(call trailingSlash,$(GCC_POWERPC_HOME))bin $(toolsSearchPath)
toolsSearchPath := $(call w2u,$(toolsSearchPath))
#$(info Search path for external tools: $(toolsSearchPath))

# Under Windows we have to look for gcc.exe rather than for gcc.
ifeq ($(call isWin),true)
    dotExe := .exe
else
    dotExe :=
endif

# Different releases of GCC use different executable names.
gcc-prefix := powerpc-eabivle-

# Now use the path search to get all absolute tool paths for later use.
cat := $(call pathSearch,$(toolsSearchPath),cat$(dotExe))
cp := $(call pathSearch,$(toolsSearchPath),cp$(dotExe))
echo := $(call pathSearch,$(toolsSearchPath),echo$(dotExe))
gawk := $(call pathSearch,$(toolsSearchPath),gawk$(dotExe))
awk := $(gawk)
gcc := $(call pathSearch,$(toolsSearchPath),$(gcc-prefix)gcc$(dotExe))
g++ := $(call pathSearch,$(toolsSearchPath),$(gcc-prefix)g++$(dotExe))
ar := $(call pathSearch,$(toolsSearchPath),$(gcc-prefix)ar$(dotExe))
objcopy := $(call pathSearch,$(toolsSearchPath),$(gcc-prefix)objcopy$(dotExe))
mkdir := $(call pathSearch,$(toolsSearchPath),mkdir$(dotExe))
mv := $(call pathSearch,$(toolsSearchPath),mv$(dotExe))
now := $(call pathSearch,$(toolsSearchPath),now$(dotExe))
pwd := $(call pathSearch,$(toolsSearchPath),pwd$(dotExe))
rm := $(call pathSearch,$(toolsSearchPath),rm$(dotExe))
rmdir := $(call pathSearch,$(toolsSearchPath),rmdir$(dotExe))
touch := $(call pathSearch,$(toolsSearchPath),touch$(dotExe))

# TODO The resource compiler is system specific. We've added the Windows variant only.
# Extend code for other systems if applicable.
ifeq ($(OS),Windows_NT)
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
	$(gcc) -v --help
builtinMacrosGCC:
	$(gcc) -dM -E - < nul

# A plausibility check that tools could be loacted.
ifeq ($(and $(make),$(gcc),$(cp),$(echo)),)
    $(info make: $(make), gcc: $(gcc), cp: $(cp), echo: $(echo))
    $(info Current working directory: $(shell cd))
    $(info $$(GCC_POWERPC_HOME): $(GCC_POWERPC_HOME))
    $(info $$(PATH): $(toolsSearchPath))
    $(error Required GNU tools can't be located. Most probable reasons are: You \
            didn't install the Cycwin Unix tools, you didn't install GCC for PowerPC \
            or you didn't add the paths to the executables to the environment variable \
            PATH and you didn't set environment variable GCC_POWERPC_HOME to point to \
            the installation of GCC)
else
    #$(info make: $(make), gcc: $(gcc), cp: $(cp), echo: $(echo))
endif

else
$(error This makefile shouldn't be called twice. There's a problem in your makefile structure)
endif # LOCATE_TOOLS_INCLUDED
