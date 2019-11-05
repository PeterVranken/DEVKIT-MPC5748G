set mem inaccessible-by-default off
set tcp auto-retry on
set tcp connect-timeout 240
set remotetimeout 60
#monitor preserve1 0 # 'monitor' is possible only after sucessful target remote
#monitor preserve2 0
#set $elf-file = bin/ppc/DEBUG/DEVKIT-MPC5748G-startup.elf
symbol-file bin/ppc/DEBUG/DEVKIT-MPC5748G-startup.elf
!echo Type either core0, core1 or core2 to connect to the Z4A, Z4B or Z2,
!echo respectively. (The GDB server need to run and need to have successfully
!echo connected to the DEVKIT-MPC5748G.)
!echo   Before switching from the selected core to another one use: detach. Or
!echo open one or two other shell windows and run the gdb client, there
!echo connecting to the other cores.
pwd

define core0
  !echo Connect to core 0, Z4A
  target remote localhost:7224 # core 0, Z4A
end
document core0
Make target connection such that core 0 (Z4A) is being debugged from now on.
Use detach prior to attempting to connect to another core.
end

define core1
  !echo Connect to core 1, Z4B
  target remote localhost:7226 # core 1, Z4B
end
document core1
Make target connection such that core 1 (Z4B) is being debugged from now on.
Use detach prior to attempting to connect to another core.
end

define core2
  !echo Connect to core 2, Z2
  target remote localhost:7228 # core 2, Z2
end
document core2
Make target connection such that core 2 (Z2) is being debugged from now on.
Use detach prior to attempting to connect to another core.
end

define flash
  symbol-file bin/ppc/DEBUG/DEVKIT-MPC5748G-startup.elf
  load bin/ppc/DEBUG/DEVKIT-MPC5748G-startup.elf
end
document flash
Flash (load) the binary file of the current project in DEBUG compilation. This
command should be preceded by a successful connection to core 0, see user defined
command core0
end

define flashPRODUCTION
  symbol-file bin/ppc/PRODUCTION/DEVKIT-MPC5748G-startup.elf
  load bin/ppc/PRODUCTION/DEVKIT-MPC5748G-startup.elf
end
document flashPRODUCTION
Flash (load) the binary file of the current project in PRODUCTION compilation. This
command should be preceded by a successful connection to core 0, see user defined
command core0
end

define runAll
  core0
  detach
  core1
  detach
  core2
  detach
end
document runAll
Unvalidated command to run the code on all three cores. Success will depend on
state of the debugging session. None of the cores should currently be connected.
Main intention is to run the code after re-flash and without ending the GDB server.
Or after starting the GDB server.
end
  
