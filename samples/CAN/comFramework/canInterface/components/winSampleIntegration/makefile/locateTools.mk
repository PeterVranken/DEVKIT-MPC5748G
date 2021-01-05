# 
# Makefile for GNU Make 3.81
#
# Locate all the external tools used by the other makefile fragments.
#
# This makefile fragment depends on functions.mk.
#
# Help on the syntax of this makefile is got at
# http://www.gnu.org/software/make/manual/make.pdf.
#

# Only uncomment the next line when running this fragment independently for maintenance
# purpose.
#include commonFunctions.mk


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
ifeq ($(OS),Windows_NT)
toolsSearchPath := $(subst ;, ,$(call w2u,$(PATH)))
else
toolsSearchPath := $(subst :, ,$(call w2u,$(PATH)))
endif
toolsSearchPath := $(minGwSearchPath) $(toolsSearchPath)
#$(info Search path for external tools: $(toolsSearchPath))

# Under Windows we have to look for gcc.exe rather than for gcc.
ifeq ($(OS),Windows_NT)
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
ifeq ($(OS),Windows_NT)
    windres := $(call pathSearch,$(toolsSearchPath),windres$(dotExe))
endif

# The make tool is different: We need to use the same one as has been invoked by the user
# and as is executing this makefile fragment.
make := $(MAKE)

# A plausibility check that tools could be loacted.
#$(info Make: $(make), gcc: $(gcc), windres: $(windres))
ifeq ($(and $(make),$(gcc)),)
    $(error Required GNU tools can't be located. Most probable reasons are: You \
            didn't install the MinGW package or you didn't add the path to the MinGW \
            installation to the environment variable PATH and you didn't let environment \
            variable MINGW_HOME point to that directory)
endif
