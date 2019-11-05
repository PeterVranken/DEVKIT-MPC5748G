# Start the GDB client
#   See .gdbinit file in project root directory to understand how to connect to the target
# from the new session, how to select a core or how to switch to another core and how to
# flash a binary.
#   This script may be run simultaneously from up to three shell windows to debug all
# cores at the same time.

# Set paths and Windows search PATH.
..\setEnv.ps1

# Run the client executable, which should now be found.
."$env:S32DS_HOME\Cross_Tools\powerpc-eabivle-4_9\bin\powerpc-eabivle-gdb.exe"