This folder contains some files, which model the API of a hypothetic CAN
shield for Arduino. The API shaped here is what the integration code has
to connect to.

The hyothetic API has not been designed for simple integration and
customization of the code generation but should resemble real existing
system as much as possible. We consider however, that Arduino is a small
eight Bit platform, which won't have a highly abstracted API, our model is
close to typical hardware designs.

These are our assumptions: The hardware offers a limited number of so
called message transfer objects (MTO). The limit is a hardware limit,
typically a power of two. These are hardware register sets, which can
handle one message each. Each MTO is either used for reception or for
sending. The MTOs are addressed to by a linear, zero based index. Among some
status bits do they each have:
- a 32 Bit CAN ID register
- a 32 Bit CAN ID mask register
- 8 Byte message content buffer
- a 3 Bit DLC register, which contains the number of transmitted bytes

For CAN reception and when a CAN frame is received then the HW iterates
along all MTOs in rising index order. The first one, which
- is configured for reception and
- where (received CAN ID & mask & CAN ID register) == mask
is filled with the frame contents bytes read from the physical bus.
Existing contents of the content buffer are unconditionally overwritten in
an atomic, single clock operation. In the same clock tick are the status
registers updated. An interrupt is raised, which announces the newly
arrived frame. The interrupt checks, which MTO signaled reception and
passes the index to the user callback via the API. From within the user
defined callback other API functions may be called to get DLC, actually
received CAN ID and contents bytes. They take the index of the MTO as
input and they are not synchronized. If the handler is too slow a new
frame could arrive and overwrite the registers and alter the further
return values of these functions. The only way to sort this out is to
guarantee that the handler is faster than the transmission of a single
frame on the physical bus (i.e. about 250 us at 500 kbs).
  For CAN sending the selection of the right MTO is similar only the MTO
has to be configured for sending and the "received CAN ID" in the
explanation above needs to be replaced by "user specified CAN ID".
  However, failure handling differs. If the MTO is still full (i.e. the
former frame contents have not yet been completely serialized on the
physical bus) then the user send command is ignored with error message
"buffer full" rather than overwriting the MTO's registers. The send
function is thus never blocking.

This leads to an API, which is MTO index based for reception and CAN ID
based for sending. Due to the simplicity of the 8 Bit platform the user
handler of the interrupt has a given name and the user has to implement it
in order not to end up with a linker error.

In practice, most CAN frames still use the standard 11 Bit identifiers.
Due to the limitations of an 8 Bit platform, some functions are defined
twice for standard and extended IDs: so most applications can safe 2 Byte
per CAN frame.