#
# Makefile for GNU Make 3.81
#
# Generation of C sources (and related files) from CAN network database files.
#
# Help on the syntax of this makefile is got at
# http://www.gnu.org/software/make/manual/make.pdf.
#
# Copyright (C) 2015-2022 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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

# Generate the C code from the DBC file with help of StringTemplate V4 templates. In
# practice, we mainly modify the templates so this is the major dependency.
.PHONY: generateCode
genDir := code/canApi/
templateList := $(call rwildcard, $(genDir)templates/, *.stg)
databaseList := $(call rwildcard, $(genDir)dbcFiles/, *.dbc)
#$(info List of StringTemplate V4 templates: $(templateList), DBC files: $(databaseList))
generateCode: $(genDir)makeTag_generateCode

$(genDir)makeTag_generateCode: $(templateList) $(databaseList)
	cd $(call u2w,$(genDir)) & generateCode.cmd
	@echo Make tag for rule generateCode. Do not delete this file > $@
    
# Make the standard targets dependent on this application specific target.
run build compile: $(genDir)makeTag_generateCode

# clean: We can't delete all produced file as they are output of the external shell script
# and not known to this makefile. However, deleting the tag file forces at least the
# re-generation of the files, which is mostly the intention of a clean.
.PHONY: clean_generateCode
clean_generateCode:
	-$(rm) -f $(genDir)makeTag_generateCode

# Make the local clean a dependency of the user known and demanded clean.
clean: clean_generateCode