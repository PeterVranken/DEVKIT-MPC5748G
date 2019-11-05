# Start the GDB server
#   Use Ctrl-C to stop it again after use.

# Set paths and Windows search PATH.
..\setEnv.ps1

# Run the server executable, which is part of the installation of the NXP S32 Design Studio.
#   Note, the proposed command lines below are pretty volatile and need a regular
# migration; every update of the Design Studio potentially changes the installation folder
# name of the P&E Micro tooling.

# TODO Use this command if you have a P&E Multilink device connected to the JTAG connector
# of the DEVKIT board.
#$env:S32DS_HOME\eclipse\plugins\com.pemicro.debug.gdbjtag.ppc_1.7.5.201807182113\win32\pegdbserver_power_console.exe -device=MPC5748g -startserver -serverport=7224 -gdbmport=6224 -interface=USBMULTILINK -speed=5000 -port=USB1 -verbose

# TODO Use this command if you use the DEVKIT board's native debugger through the USB
# connection.
."$env:S32DS_HOME\eclipse\plugins\com.pemicro.debug.gdbjtag.ppc_1.7.5.201807182113\win32\pegdbserver_power_console.exe" -device=MPC5748g -startserver -serverport=7224 -gdbmport=6224 -interface=OPENSDA -speed=5000 -port=USB1 -verbose