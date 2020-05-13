# See usage message for help.
$usage = `
'usage: .\processes_ld.ps1
  Run excelExporter to generate the process related fragments of the linker script'

# Copyright (C) 2020 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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

function endWithError
{
    write-host $usage;
    exit;
}

# Support help
if($args[0] -match '^(-h|/h|/\?|--help)$') {endWithError}

# Limit the allowed number of parameters.
if($args[0] -match '.') {endWithError}

# The Java classpath is used to localize the StringTemplate V4 template file. Here, it's
# sufficient to assign those paths, which hold the templates. The launcher script
# excelExporter.cmd takes care that the actual Java search path is set, too.
$env:CLASSPATH = "."

if("$env:EXCELEXPORTER_HOME" -eq "")
{
    # TODO The installation path of tool excelExporter needs to be configured.
    write-host "Please, specifiy the path to your installation of excelExporter. The path `
to the folder is needed that contains folder 'dist'."
    write-host "  You can either persistently set environment variable EXCELEXPORTER_HOME `
or you can write the path into this script. Look for TODO tags."
    write-host "  If you didn't install excelExporter yet then have a look here:"
    write-host "https://sourceforge.net/p/excelexporter/wiki/Home/"

    # TODO Remove the next line if you decide to write the path into this script.
    exit

    $env:EXCELEXPORTER_HOME = "c:\ProgramFiles\excelExporter"
    write-host "For now, we assume $env:EXCELEXPORTER_HOME"
}



# Lauch the Java application excelExporter.
$spreadsheet = "processes_ld.xlsx"
$output      = "processRAM.ld"
$template    = "processRAM_ld"
."$env:EXCELEXPORTER_HOME\dist\excelExporter.cmd" `
  --input-file-name "$spreadsheet" `
    --workbook-name processes `
  --open-worksheet-template `
    --association-by-index 1 `
    --column-titles-are-identifiers `
  --output-file-name "$output" `
    --template-file-name "processes_ld.stg" `
    --template-name $template

$output      = "processRAMInitAry.ld"
$template    = "processRAMInitAry_ld"
."$env:EXCELEXPORTER_HOME\dist\excelExporter.cmd" `
  --input-file-name "$spreadsheet" `
    --workbook-name processes `
  --open-worksheet-template `
    --association-by-index 1 `
    --column-titles-are-identifiers `
  --output-file-name "$output" `
    --template-file-name "processes_ld.stg" `
    --template-name $template
