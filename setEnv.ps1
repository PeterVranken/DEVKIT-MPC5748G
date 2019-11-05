$usage = `
'usage: .\setEnv.ps1
  Set environment variables appropriately to run Eclipse and makefile based builds from PowerShell'

function endWithError { write-host $usage; exit; }

# Support help
#if($args[0] -match '^$|^(-h|/h|/\?|--help)$') {endWithError}

# Limit the allowed number of parameters.
#if($args[0] -match '.') {endWithError}

# The path to the GCC C cross compiler installation. Note, this environment may
# already be persistently set by the installation procedure. Otherwise we look for GCC
# inside the Design Studio installation.
if ("$env:S32DS_HOME" -eq "")
{
    # TODO Adjust the path to the installation of the NXP S32 Design Studion and remove
    # this comment and the next three commands. The installation folder is the very one,
    # which contains e.g. folders Cross_Tools, Drivers and eclipse.
    write-host ('setEnv.ps1: You need to configure this script prior to first use:' `
                + ' Specify location of NXP S32 Design Studio')
    write-host 'Press any key to continue ...';
    $null = $host.UI.RawUI.ReadKey('NoEcho,IncludeKeyDown')

    $env:S32DS_HOME = 'C:\ProgramFiles\NXP\S32DS_Power_v2017.R1'
    write-host ("Environment variable S32DS_HOME is set to $env:S32DS_HOME")
}
else
{
    write-host ('Environment variable S32DS_HOME is already persistently set to ' `
                + $env:S32DS_HOME)
}

# The path to the GCC C cross compiler installation. Note, this environment may
# already be persistently set by the installation procedure. Otherwise we look for GCC
# inside the Design Studio installation.
if ("$env:GCC_POWERPC_HOME" -eq "")
{
    $env:GCC_POWERPC_HOME = "$env:S32DS_HOME\Cross_Tools\powerpc-eabivle-4_9"
    write-host ("Environment variable GCC_POWERPC_HOME is set to $env:GCC_POWERPC_HOME")
}
else
{
    write-host ("Environment variable GCC_POWERPC_HOME is already persistently set to " `
                + $env:GCC_POWERPC_HOME)
}

# Create a convenience shortcut to the right instance of the make processor.
set-alias -Name "make" `
          -Value ("$PSScriptRoot\bin\mingw32-make.exe") `
          -Description ('Run the GNU make processor, which is appropriate to build the' `
                        + ' software for the DEVKIT-MPC5748G board')

# Prepare the Windows search path for the run of the compilation tools.
$env:PATH = "bin" `
            + ";$env:GCC_POWERPC_HOME\bin" `
            + ";$env:S32DS_HOME\utils\msys32\usr\bin" `
            + ";$env:S32DS_HOME\eclipse\plugins\com.pemicro.debug.gdbjtag.ppc_1.7.2.201709281658\win32" `
            + ";$env:PATH"
