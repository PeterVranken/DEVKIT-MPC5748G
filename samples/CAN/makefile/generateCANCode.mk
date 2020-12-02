#
# Makefile for GNU Make 3.81
#
# Generation of C sources (and related files) from CAN network database files.
#
# Help on the syntax of this makefile is got at
# http://www.gnu.org/software/make/manual/make.pdf.
#
# Copyright (C) 2015-2020 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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

# Add a line of help to the general makefile help. This text prepends the general help and
# relates to this additional makefile fragment only.
.PHONY: help_generateCANCode
help_generateCANCode:
	$(info Note, as an additional target you may state generateCANCode on the $(EOL)\
           command line. The CAN stack is reproduced from the DBC Files)
h help targets usage: help_generateCANCode

# Generate the C code from the DBC file(s) with help of StringTemplate V4 templates. In
# practice, we mainly modify the templates so this is the major dependency.
.PHONY: generateCANCode
genDir := code/application/canStack/
templateList := $(call rwildcard,$(genDir)templates/,*.stg)
databaseList := $(wildcard $(genDir)dbcFiles/*.dbc)
#$(info List of StringTemplate V4 templates: $(templateList), DBC files: $(databaseList))
generateCANCode: $(genDir)makeTag_generateCode

# Caution, the recipe of this rule highly depends on the makefile configuration setting
# .ONESHELL (see globalVariables.mk). It needs to be given. This allows to first change
# directory then define subsequent steps relative to that directory.
#   Unfortunately, the Windows shell cmd concatenates the lines cd and next one so that
# both lines result in one invalid command. It's unclear if this is a problem in make or in
# the shell itself. The explicit $(EOL) is a workaround to separate the lines.
$(genDir)makeTag_generateCode: $(templateList) $(databaseList) $(genDir)generateCode.cmd
	cd $(call u2w,$(dir $@)) $(EOL)
#	pwd
	call generateCode.cmd -v WARN
	echo Make tag for rule generateCANCode. Do not delete this file > $(notdir $@)
    
souceFileList := $(call rwildcard,$(genDir),*.c *.h)
#$(info List of generated CAN source files: $(souceFileList))
$(souceFileList): $(genDir)makeTag_generateCode

# clean: We can't delete all produced file as they are output of the external shell script
# and not known to this makefile. However, deleting the tag file forces at least the
# re-generation of the files, which is mostly the intention of a clean.
.PHONY: clean_generateCANCode
clean_generateCANCode:
	-$(rm) -f $(genDir)makeTag_generateCode

# Make the local clean a dependency of the user known and demanded clean.
clean: clean_generateCANCode