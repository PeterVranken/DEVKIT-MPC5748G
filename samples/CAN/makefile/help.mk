#
# Generic Makefile for GNU Make 3.82 (MinGW port only)
#
# This file provides help on the targets and configuration item offered by the complete set
# of makefiles.
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
ifndef HELP_INCLUDED
HELP_INCLUDED := 1

# Access help as default target or by several names. This target needs to be the first one
# in this file.
.PHONY: h help targets usage
.DEFAULT_GOAL := help
h help targets usage:
	$(info Usage: make [-sO] [-k] [CONFIG=<configuration>] [SAVE_TMP=1] {<target>})
#	$(info APP: safe-RTOS-VLE is a library rather than a self-contained application. It $(EOL)\
#           can be linked with some sample client code. <sourceCodeFolder> is a folder, $(EOL)\
#           which contains the source files of the selected sample. Default is $(EOL)\
#           code/application/default/ $(EOL)\
#           CAUTION: The change of the application requires a rebuild)
	$(info CONFIG: <configuration> is one out of DEBUG (default) or PRODUCTION.)
	$(info SAVE_TMP: Set to one will make the preprocessed C(++) sources and the assembler \
           files appear in the target directory bin/ppc/<configuration>/obj/)
	$(info $(EOL) Available targets are:)
	$(info - build: Build the executable)
	$(info - compile: Compile all C(++) and assembler source files, but no linkage etc.)
	$(info - clean: Delete all application files generated by the build process)
	$(info - cleanDep: Delete all dependency files, which is useful after changes of $(EOL)\
             #include statements or file renaming to avoid make errors like "No rule $(EOL)\
             to make ...")
	$(info - rebuild: Target clean before build)
	$(info - bin/ppc/<configuration>[-RAM]/obj/<path>/<cFileName>.o: Compile a single $(EOL)\
             C(++) or assembler module, e.g. $(targetDir)obj/mai_main.o)
	$(info - <path>/<cFileName>.i: Preprocess a single C(++) or assembler module. Build $(EOL)\
             product is sibling of source file)
	$(info - <path>/<cFileName>.asm: Generate an assembler listing for a single C(++) $(EOL)\
             or assembler module. Build product is sibling of source file)
	$(info - versionGCC: Print information about which compiler is used)
	$(info - helpGCC: Print usage text of compiler)
	$(info - builtinMacrosGCC: Print built-in #define's of compiler for given configuration)
	$(info - help: Print this help)
	$(error)

endif # HELP_INCLUDED