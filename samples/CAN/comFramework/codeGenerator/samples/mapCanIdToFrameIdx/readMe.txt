This sample generates a lookup table, which yields the index at which a
frame had been registered in the CAN interface engine if the CAN bus (by
index) and the CAN ID are given.

Each integration of the CAN interface needs to solve the following mapping
problem: The hardware driver layer, which our CAN interface builds on,
usually notifies hardware events (reception, send acknowledge, errors) by
callbacks (which can also be the raw interrupt handlers). These callbacks
get the information about what happened (which bus, which CAN frame, which
event) in a platform specific way, which can't generally be anticipated by
the CAN interface. The CAN interface expects to see the index of a frame
as assigned during the registration process. The platform specific way to
identify a frame needs to be mapped onto the CAN interface's index. The
CAN interface engine invokes external code to do the mapping; providing
this code is part of the integration of the interface into a real
platform.

On principle, it's the same for buses but in practice, this is irrelevant.
The number of buses is no greater than four in all real existing platforms
and nearly anywhere the platform uses a null based linear index for
addressing to a bus just as the CAN interface does. The mapping reduces to
the identity. And if it wouldn't in pathologic situations then a simple on
the fly switch/case statement would be appropriate to do the mapping.

In real platforms a common style to identify a frame is by the pair of bus
index and CAN ID. For these systems, the mapping tables can be built in
ROM by the code generator. This sample demonstrates how. The templates and
the accompanying source code could be used in a real integration.

The core files mci_mapCanIdToFrameIdx.h/c in folder output are generated
by the Java application codeGenerator. These files implement the required
data tables, which depend on the network database files, but they contain
no functional code. Suitable, hand-coded functional code has been added as
mci_getIdxFrameByCanId.h/c in the same folder.

To make the C sources compilable and testable we've added the hand-coded
main.c and the Windows build and debug commands compileWithGcc.cmd and
gdb.cmd.

The code generation can be repeated by running the Windows script
generateCode.cmd from this working directory. Repeating the code
generation should be tried as kind of installation test of the
application.

If you want to run the application from another working folder then you
will have to modify the script: The Windows script references the required
resources by relative paths from here. Please, refer to
codeGenerator\doc\installation.txt, too.

All Windows scripts are trivial; porting them to Linux or Mac OS is
straightforward.
