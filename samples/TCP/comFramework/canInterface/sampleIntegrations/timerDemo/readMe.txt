The files in the folder and below contain a Windows test application for
the timer API of the CAN interface. If GCC and GNU make 3.81 are available
it can be compiled using the command:

make -s build

Build and execution of the test application can done using the command:

make -s run

Note, on Windows systems you will need the MinGW port of make, not the
Cygwin port. Many GCC distributions contain both variants, so it depends
on your system search path, which one is run. Or consider typing
mingw32-make build; in a Windows GCC distribution this should be a safe
reference to the right implementation of make. The Cygwin variant uses
another interface to the underlying shell and this interface is not
compatible with our makefiles.

