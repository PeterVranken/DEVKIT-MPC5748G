$usage = `
'usage: .\setEnv.ps1
  Set environment variables appropriately to run Eclipse and makefile based builds from PowerShell'

function endWithError { write-host $usage; exit; }

# Support help
#if($args[0] -match '^$|^(-h|/h|/\?|--help)$') {endWithError}

# Limit the allowed number of parameters.
#if($args[0] -match '.') {endWithError}

# The path to the installation of the IDE, the NXP S32 Design Studio. Note, this
# environment may already be persistently set by the installation procedure.
if ("$env:S32DS_HOME" -eq "")
{
    # TODO Adjust the path to the installation of the NXP S32 Design Studio and remove
    # this comment and the next three commands. The installation folder is the very one,
    # which contains e.g. folders S32DS, Drivers and eclipse.
    write-host ('setEnv.ps1: You need to configure this script prior to first use:' `
                + ' Specify location of NXP S32 Design Studio')
    write-host 'Press any key to continue ...';
    $null = $host.UI.RawUI.ReadKey('NoEcho,IncludeKeyDown')

    $env:S32DS_HOME = 'C:\ProgramFiles\NXP\S32DS_Power_v2.1'
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
    $env:GCC_POWERPC_HOME = "$env:S32DS_HOME\S32DS\build_tools\powerpc-eabivle-4_9"
    write-host ("Environment variable GCC_POWERPC_HOME is set to $env:GCC_POWERPC_HOME")
}
else
{
    write-host ("Environment variable GCC_POWERPC_HOME is already persistently set to " `
                + $env:GCC_POWERPC_HOME)
}

# The path to Java binaries. Java is used for some code generation tools in sample CAN. The
# Open Source JDK is alright; see e.g. https://jdk.java.net/18/ (visited in May 2022).
if ("$env:JAVA_BIN" -eq "")
{
    $env:JAVA_BIN = "C:\ProgramFiles\Java\jdk-18.0.1.1\bin"
    write-host ("Environment variable JAVA_BIN is set to $env:JAVA_BIN")
}
else
{
    write-host ("Environment variable JAVA_BIN is already persistently set to " `
                + $env:JAVA_BIN)
}

# Create a convenience shortcut to the right instance of the make processor.
set-alias -Name "make" `
          -Value ("$PSScriptRoot\bin\mingw32-make.exe") `
          -Description ('Run the GNU make processor, which is appropriate to build the' `
                        + ' software for the DEVKIT-MPC5748G board')

# Prepare the Windows search path for the run of the compilation tools.
$env:PATH = "$PSScriptRoot\bin" `
            + ";$env:GCC_POWERPC_HOME\bin" `
            + ";$env:S32DS_HOME\S32DS\build_tools\msys32\usr\bin" `
            + ";$env:S32DS_HOME\eclipse\plugins\com.pemicro.debug.gdbjtag.ppc_2.0.5.202210261806\win32" `
            + ";$env:JAVA_BIN" `
            + ";$env:PATH"

write-host ("Environment prepared for GCC toolchain powerpc-eabivle-4.9.4.
  To start, cd into a sample's root folder (where GNUmakefile resides) and type 'make help'.")
