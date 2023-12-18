#
# Generic Makefile for GNU Make 3.81
#
# Parallel invocation of targets for compilation and linkage of C(++) code.
#
# Help on the syntax of this makefile is got at
# http://www.gnu.org/software/make/manual/make.pdf.
#

# A normal makefile cannot safely be run with the make command line switch -j if it
# combines targets to sequences of such. A common example is a derived target rebuild,
# which depends on clean and build in this order. The order of prerequisites is however
# regarded only in the standard sequential mode of make. If -j N is given, the
# prerequisites are made in parallel; in our example clean was not be guaranteed to be
# completed before the build begins.
#   make considers all prerequisites as long as independent and will make them in parallel
# as long as they are not explicitly coupled by inter-dependencies. Such inter-dependencies
# can however not always be expressed with the term "target: prerequisite". The result of
# clean is to have no any file left, so which file to state as prerequisite of a rule
# actually depending on clean? Moreover: Such a dependency is typically only optional, we
# do not want to do a clean always; a regular, always-present prerequisite "clean" of
# target build would obviously be counterproductive.
#   The only found way out of this is to use the makefile recursively. Now the build steps
# are properly serialized as steps of a recipe. Each step may benefit from parallelism but
# the execution of steps remain sequential. Each step is a single rule with fully expressed
# dependency hierarchy. The prerequisite(s) of the phony rules get the character of a .BEGIN
# rule, like some make derivates offer. Caution, they are again not serialized in a defined
# order if make is invoked with -j.

# Some core variables have already been set prior to reading this common part of the
# makefile. These variables are:
#   project: Name of the sub-project; used e.g. as name of the executable
#   srcDirList: a blank separated list of directories holding source files
#   cFileListExcl: a blank separated list of source files (with extension but without path)
# excluded from the compilation of all *.c and *.cpp
#   incDirList: a blank separated list of directories holding header files. The directory
# names should end with a slash. The list must not comprise common, project independent
# directories and nor must the directories listed in srcDirList be included
#   defineList: a blank separated list of defines, with or without value
#   sharedMakefilePath: The path to the common makefile fragments like this one
#   targetRunArgs: A list of arguments passed to the compiled target when yielding target
# run
export project srcDirList cFileListExcl incDirList defineList sharedMakefilePath targetRunArgs

# Load the makefile, the targets of which are run in a safe parallel way.
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
	$(MAKE) $(mFlags) generateCode
	$(MAKE) $(mFlags) $(targetDir)$(projectExe)

# Rebuild all.
#   clean and makeDir do not interfere and maybe listed without explicit serialization.
.PHONY: rebuild
rebuild: makeDir clean
	$(MAKE) $(mFlags) generateCode
	$(MAKE) $(mFlags) $(targetDir)$(projectExe)
            
# Compile all C source files.
.PHONY: compile
compile: $(objListWithPath)

# Execute the compiled software under Windows if it could be built.
.PHONY: run
targetRunDir ?= $(targetDir)
run: makeDir
	$(info Running $(call u2w,$(abspath $(targetDir)$(projectExe))) $(targetRunArgs) in directory $(targetRunDir))
	$(MAKE) $(mFlags) generateCode
	$(MAKE) $(mFlags) $(targetDir)$(projectExe)
	cd $(targetRunDir) & pwd & $(call u2w,$(abspath $(targetDir)$(projectExe))) $(targetRunArgs)

