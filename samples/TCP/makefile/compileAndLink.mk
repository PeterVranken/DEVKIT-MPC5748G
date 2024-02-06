#
# Generic Makefile for GNU Make 3.82 (MinGW port only)
#
# Core of build: Compilation and run of assembler. Linkage of C(++) code.
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
ifndef COMPILE_AND_LINK_INCLUDED
COMPILE_AND_LINK_INCLUDED := 1

# General settings for the makefile.
#$(info Makeprocessor in use is $(MAKE) $(MAKECMDGOALS))

# Include some required makefile functionality.
#   Note, this makefile is either included by parallelJobs.mk or it is directly invoked in
# a recursive call of make. For the latter case we need to inclusion of some sub-ordinated
# makefiles with shared data and functions. This leads to double inclusion of these files
# in the former case. The sub-ordinated makefiles need to cope with this.
include $(sharedMakefilePath)globalVariables.mk
include $(sharedMakefilePath)commonFunctions.mk
include $(sharedMakefilePath)locateTools.mk
include $(sharedMakefilePath)generateCANCode.mk

# The name stem of the final build artifacts.
target := $(project)

# Concept of compilation configurations:
#
# Configuration PRODCUTION:
# - no self-test code
# - no debug output
# - no assertions
#
# Configuration DEBUG:
# + all self-test code
# + debug output possible
# + all assertions active
#
ifeq ($(CONFIG),PRODUCTION)
    ifeq ($(MAKELEVEL),0)
        $(info Making $(target)$(if $(call isDefined,LINK_IN_RAM), in RAM, for flashing) for production)
    endif
    cDefines := -DPRODUCTION -DNDEBUG
else ifeq ($(CONFIG),DEBUG)
    ifeq ($(MAKELEVEL),0)
        $(info Making $(target) for debugging$(if $(call isDefined,LINK_IN_RAM), in RAM, for flashing))
    endif
    cDefines := -DDEBUG
else
    $(error Please set CONFIG to either PRODUCTION or DEBUG)
endif
#$(info $(CONFIG) $(cDefines))

# The lists of files to be processed have been elaborated before by findFiles.mk. They can
# be printed for reference and for debugging purpose.
#$(info incDirList := $(incDirList))
#$(info srcFileList := $(srcFileList))
#$(info objFileList := $(objFileList))
#$(info objDirList := $(objFileList))

# The name of the executable file. This is the ultimate build product in the tree of
# dependcies. It is requested from outside this makefile fragment through this name.
projectExe := $(target).s19

# Function isTargetArchitectureZ4
#   Decide whether a source file has to be compiled for the Z4 or the Z2 architecture. The
# decision is name based, the function is a kind of text filter for file/path names. The
# concept is to use naming conventions in the project to make the distinction.
#   Return: Get the non empty string Z4 if this is the target or the empty string
# otherwise. The return value of this function can thus be used as condition of the $(if)
# make function.
#   $(1): The path to the compiled C/C++ source file
isTargetArchitectureZ4 = $(findstring Z4,$(1))
# Example:
#$(info File code/Z4/myFile.c: $$isTargetArchitectureZ4 returns $(call isTargetArchitectureZ4,code/Z4/myFile.c))

# Function targetArchitecture
#   Decide whether a source file has to be compiled for the Z4 or the Z2 architecture. The
# decision is name based, the function is a kind of text filter for file/path names. The
# concept is to use naming conventions in the project to make the distinction.
#   $(1): The path to the compiled C/C++ source file
targetArchitecture = $(if $(call isTargetArchitectureZ4,$(1)),Z4,Z2)
# Example:
#$(info File code/Z4/myFile.c is compiled for $(call targetArchitecture,code/Z4/myFile.c))

# Include the dependency files. Do this with a failure tolerant include operation - the
# files are not available after a clean.
-include $(patsubst %.o,%.d,$(objFileList))

# Selection of the target. These configuration settings determine the set of machine
# instructions to be used. To ensure consistency, they are passed to the assembler, the
# compiler and the linker, even if not all of the settings affect all of the tools. (The
# linker is affected as it may have an impact on the selection of appropriate libraries.)
#   Floating point support:
#   The target selection impacts how floating point operations are implemented.
# The optimal configuration is: Only use single float operations and use the hardware
# floating point unit.
#   Use of software emulation for floating point operations is supported, too.
#   Use different data addressing modes:
#   Standard setting is the use of short addressing modes for "small" data objects in RAM
# and ROM. The memory space for the short addressing mode is limited it should therefore
# not be flooded with large objects. We limit the data size to 8 Byte (-G8). The short data
# addressing mode is enabled by -meabi -msdata=default.
#   The code compiles with long addressing for all data objects with -meabi -msdata=none.
# Code size and CPU load grow a bit. This may become an issue if the small data areas of
# 64k each (RAM and ROM) become too small to hold all "small" data objects. Prior to
# disabling the mode you should first try to reduce the size limit to 4 or 2 Byte.
targetFlagsZ2 := -mcpu=e200z2
targetFlagsZ4 := -mcpu=e200z4
targetFlags := -mbig-endian -mvle -misel=yes -meabi -msdata=default -G8                     \
               -fshort-double -fsingle-precision-constant
ifeq ($(call isDefined,USE_FP_EMULATION_CLIB),true)
    targetFlags += -msoft-float
else
    targetFlagsZ2 += -msoft-float
    targetFlagsZ4 += -mhard-float
endif

# Choose C library.
ifeq ($(call isDefined,USE_EWL2),true)
    cClibSpec := -specs=ewl_c9x_noio.specs                                                  \
                 --sysroot=$(call w2u,$(S32DS_HOME))/S32DS/build_tools/e200_ewl2
    ifeq ($(MAKELEVEL),0)
        incDirList += $(call w2u,$(S32DS_HOME)/S32DS/build_tools/e200_ewl2/EWL_C/include)   \
                      $(call w2u,$(S32DS_HOME)/S32DS/build_tools/e200_ewl2/EWL_C/include/pa)
    endif
else ifeq ($(call isDefined,USE_NEWLIB),true)
    # The switch -specs=nosys.specs links the generically implemented C library against a
    # stub library that satisfies the low level I/O routines without providing true
    # functionality. We must not use this switch if we want to have the printf
    # functionality with true I/O. If we remove this switch we need however to provide our
    # own I/O stub to satisfy the low level I/O of the clib. See file nwl_ioSysNewLib.c.
    cClibSpec := --sysroot=$(call w2u,$(GCC_POWERPC_HOME))/powerpc-eabivle/newlib
    #cClibSpec += -specs=nosys.specs
else
    $(error Please choose either Embedded Warrior Lib 2 (USE_EWL2) or Newlib (USE_NEWLIB) \
            as C runtime. See configuration variable defineList in file GNUmakefile for more)
endif

# Ensure existence of target directory.
.PHONY: makeDir
makeDir: | $(objDirList)
$(objDirList):
	-$(mkdir) -pv $@

# Pattern rules for assembler language source files.
asmFlags = $(targetFlags) -mregnames                                                        \
           $(if $(call isTargetArchitectureZ4,$<),$(targetFlagsZ4),$(targetFlagsZ2))        \
           -Wall -MMD                                                                       \
           $(foreach path,$(call noTrailingSlash,$(APP) $(incDirList) $(srcDirInUseList)),-I$(path))\
           $(cDefines) $(foreach def,$(defineList),-D$(def))                                \
           -Wa,-g -Wa,-gdwarf-2
ifeq ($(SAVE_TMP),1)
    asmFlags += -Wa,-a=$(patsubst %.o,%.lst,$@)
endif
ifneq ($(CONFIG),DEBUG)
    asmFlags += $(productionCodeOptimization)
endif
#$(info asmFlags := $(asmFlags))

$(targetDir)obj/%.o: %.S
	$(info Assembling source file $<)
	$(gcc) -c $(asmFlags) -o $@ $<


# Pattern rules for compilation of, C and C++ source files.

# TODO Consider adding -fno-asynchronous-unwind-tables to compile switches
cFlags = $(targetFlags)                                                                     \
         $(if $(call isTargetArchitectureZ4,$<),$(targetFlagsZ4),$(targetFlagsZ2))          \
         -mno-string                                                                        \
         -fno-common -fno-exceptions -ffunction-sections -fdata-sections                    \
         -fshort-enums -fdiagnostics-show-option -finline-functions -fmessage-length=0      \
         -fzero-initialized-in-bss -fno-tree-loop-optimize                                  \
         -Wall -Wno-main -Wno-old-style-declaration -Wextra                                 \
         -Wmissing-declarations -Wno-parentheses -Wdiv-by-zero -Wcast-align -Wformat        \
         -Wformat-security -Wignored-qualifiers -Wsign-compare                              \
         -Werror=missing-declarations -Werror=implicit-function-declaration                 \
         -Wno-nested-externs -Werror=int-to-pointer-cast -Werror=pointer-sign               \
         -Werror=pointer-to-int-cast -Werror=return-local-addr -Werror=missing-prototypes   \
         -Werror=missing-field-initializers -Werror=overflow                                \
         $(cClibSpec) -MMD -std=gnu11                                                       \
         $(foreach path,$(call noTrailingSlash,$(APP) $(incDirList) $(srcDirInUseList)),-I$(path))\
         $(cDefines) $(foreach def,$(defineList),-D$(def))

# lwIP is inaccurate in using signed and unsigned integers. We need to enable the warning
# on improper use only for files not belonging to the lwIP package.
cFlags += $(if $(findstring lwip-STABLE-,$@),,-Wsign-conversion -Wstrict-overflow=4)

ifeq ($(SAVE_TMP),1)
    # Debugging the build: Put preprocessed C file and assembler listing in the output
    # directory
    cFlags += -save-temps=obj -fverbose-asm -Wa,-a=$(patsubst %.o,%.lst,$@)
endif
# Debug settings see https://gcc.gnu.org/onlinedocs/gcc/Debugging-Options.html#Debugging-Options
ifeq ($(CONFIG),DEBUG)
    cFlags += -g3 -gdwarf-2 -Og -Winline
else
    cFlags += -g1 -gdwarf-2 $(productionCodeOptimization)
    ifneq ($(productionCodeOptimization),-Os)
        cflags += -Winline
    endif
endif
#$(info cFlags := $(cFlags))

$(targetDir)obj/%.o: %.c
	$(info Compiling C file $< for $(call targetArchitecture,$<))
	$(gcc) -c $(cFlags) -o $@ $<

$(targetDir)obj/%.o: %.cpp
	$(info Compiling C++ file $<)
	$(gcc) -c $(cFlags) -o $@ $<

# Create a preprocessed source file, which is convenient to debug complex nested macro
# expansion, or an assembler listing, which is convenient to understand the
# close-to-hardware parts of the code.
#   Note, different to the compilers does the assembler not take argument -o. It writes the
# output to stdout and we need redirection.
%.i %.asm: %.S
	$(info Preprocessing assembler file $(notdir $<) to text file $(patsubst %.S,%$(suffix $@),$<))
	$(gcc) $(if $(call eq,$(suffix $@),.i),-E,-S) $(filter-out -MMD,$(cFlags)) $< $(if $(call eq,$(suffix $@),.i),-o, >) $(patsubst %.S,%$(suffix $@),$<)

%.i %.asm: %.c
	$(info Preprocessing C file $(notdir $<) to text file $(patsubst %.c,%$(suffix $@),$<))
	$(gcc) $(if $(call eq,$(suffix $@),.i),-E,-S) $(filter-out -MMD,$(cFlags)) -o $(patsubst %.c,%$(suffix $@),$<) $<

%.i %.asm: %.cpp
	$(info Preprocessing C++ file $(notdir $<) to text file $(patsubst %.cpp,%$(suffix $@),$<))
	$(gcc) $(if $(call eq,$(suffix $@),.i),-E,-S) $(filter-out -MMD,$(cFlags)) -o $(patsubst %.cpp,%$(suffix $@),$<) $<

# A general rule enforces rebuild if one of the configuration files changes
$(objFileList): GNUmakefile makefile/compileAndLink.mk

# Note, it looks as if we finally wouldn't need this any longer with Windows 10! Set
# variable to empty value if patch should not be applied.
patchWindowsBug := #true
ifneq ($(patchWindowsBug),)
# More than 30 Years of DOS & Windows but the system still fails to handle long command
# lines. We write the names of all object files line by line into a simple text file and
# will only pass the name of this file to the linker.
$(targetDir)obj/listOfObjFiles.txt: $(objFileList)
	$(info Create linker input file $@)
	$(file >$@,$(sort $^))
endif

# Let the linker create the flashable binary file.
#   CAUTION: An unsolved problem with GCC 4.9.4 is the switch -fshort-double, which is
# highly desired in software emulation mode and unavoidable in hardware mode. There seems
# to be no set of libraries, which has been compiled in this mode. If we call a library
# function using the type double for in- or output then the code doesn't crash but produces
# bad results. A statement like x=exp(y); will produce the wrong result for x. We need to
# do, what is anyway strongly recommended - using the float variants of these library
# functions. Our example would become x=expf(y);, which works as expected. This problem can
# only be solved by rebuilding the C library with our settings.
#   Note, there's no such function for printf & co, e.g. printff. See sample "printf" for
# a proposed, particular work-around.
#   Another issue is the choice Z4 vs. Z2. We need to choose for one library, which is then
# used by both cores. The major difference is the availability of the floating point
# instructions only for Z4. The choice is made by putting either $(targetFlagsZ2) or
# $(targetFlagsZ4) on the linker command line. A safe choice only is Z2 but if the Z2
# source files doesn't make any use of math routines then the chance is high that the Z4
# library will work on the Z2, too. The choice of Z2 is bad for the Z4 if it makes
# intensive use of the math library (or other functions using floating point, e.g. printf).
# Now, the library calls will execute floating point emulation code instead of Z4 floating
# point instructions.
#   -nostartfiles: The compiler generates the call of a function __eabi(stackPointer) at
# the entry into main. __eabi is a function in the clib, which does the initialization of
# the clib, in particular, the C++ constructors seem to be called. If -nostartfiles is
# given then the linker won't link the related files from the clib but the compiler still
# calls __eabi() so that we need to offer a stub then. The clib is not initialized and it
# can be that elements from it won't work.
lFlags = -Wl,--gc-sections $(targetFlags)                                                   \
         -Wl,-Tmakefile/$(if $(call isDefined,LINK_IN_RAM),memoryMapRAM.ld,memoryMapROM.ld) \
         -Wl,-Tmakefile/linkerControlFile.ld                                                \
         -Wl,-sort-common -Wl,-Map="$(targetDir)$(target).map" -Wl,--cref                   \
         -Wl,--warn-common,--warn-once,--orphan-handling=warn -Wl,-g                        \
         $(if $(call isDefined,USE_Z2_CLIB),$(targetFlagsZ2),$(targetFlagsZ4))              \
         -Wl,--defsym=ld_linkInRAM=$(if $(call isDefined,LINK_IN_RAM),1,0)                  \
         $(cClibSpec)

$(targetDir)$(target).elf: $(if $(patchWindowsBug),$(targetDir)obj/listOfObjFiles.txt,$(objFileList)) \
                           makefile/linkerControlFile.ld
	$(info Linking project. Mapfile is $(targetDir)$(target).map)
	$(gcc) $(lFlags) -o $@ $(if $(patchWindowsBug),@$<,$(objFileList)) -lm
    
# Create hex file from linker output.
$(targetDir)$(target).s19: $(targetDir)$(target).elf
	$(objcopy) -O ihex $< $(patsubst %.elf,%.hex,$<)
	$(objcopy) -O symbolsrec $< $(patsubst %.elf,%.s19,$<)

# Delete all dependency files ignoring (-) the return code from Windows because of non
# existing files.
.PHONY: cleanDep
cleanDep:
	-$(rm) -rf $(targetDir)obj/*.d

# Delete all application products ignoring (-) the return code from Windows because of non
# existing files.
.PHONY: clean
clean:
	-$(rm) -rf $(targetDir)obj
	-$(rm) -f $(targetDir)$(target).*

else
$(error This makefile shouldn't be called twice. There's a problem in your makefile structure)
endif # COMPILE_AND_LINK_INCLUDED
