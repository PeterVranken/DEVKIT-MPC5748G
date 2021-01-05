Scenario
========

This sample application implements a power display device for an
automotive vehicle. It reads the current values of engine rotational speed
and engine torque from the CAN bus and computes the current power of the
engine. The power is broadcasted on the CAN bus (to whom it may concern,
no specific receiver is specified). This message transfer is regular, in-
and output are repeated every 10 ms.

The power display sends a second frame. It counts all recognized error
events (timeout, DLC, checksum and transmission sequence). Some of these
are regularly reported by a dedicated CAN frame. However, this frame is
not only sent regularly but also in the instance of a changing counter
value. This is called the mixed mode.

To make the sample more instructive some less realistic CAN messages have
been invented. For whatever reasons our application can compare the
computed power and the rotational speed against some user-defined limits.
If a range is exceeded (or when we get into range again) then and only
then an according CAN frame is broadcasted. This "functionality" has been
specified for the only reason to have some purely event based frames in
the system. Two frames are involved: The vehicle sends the limits and our
power display sends the in-range or range violation frame.


Involved frames
---------------

StateEcu01, StateEcu02: Inbound frames to our power display. Origin is the
engine control unit. These frames contain current values of rotational
speed and torque. They are sent periodically every 10 ms.

UserLimits: Inbound frame for our power display application. There may be
a human machine interface in the vehicle, where the user can enter the
current ranges for the observation of rotational speed and power. The
frame is only sent when one of the settings is changed. This will happen
rarely and occasionally only.

InfoPowerDisplay: This frame is sent regularly by our power display. It
contains the computed power plus a status signal. This status will
indicate if the compute power is invalid or unavailable, e.g. due to
recognized errors on the input frames.

StatusPowerDisplay: The number of recognized checksum, DLC and
transmission sequence errors so far. Sent by the power display, when one
of the counter values alters. But no more often then every 50 ms. If no
counter value has altered during the last 1000 ms then the frame is
re-sent with same contents (except for the sequence counter of course). If
the counter values never change than this frame becomes a regular 1000 ms
frame.

LimitsPowerDisplay: Sent by the power display in logical (not immediate)
response to frame UserLimits. When the range for speed of rotation or
power as defined by the last recently received frame UserLimits is
violated the first time or when violation the range is over then the power
display sends this frame to indicate the current in- or out-of-range
status. As long as this status doesn't change this frame won't be sent.


Specification of DBC file
-------------------------

### Attributes ###

The DBC file uses some application specific attributes to specify the
different behavior of the frames and signals.

The following frame related attributes have been defined:

- frameSendMode: An enumeration, which specifies the transmission/timing
  pattern of the frame. Known values are "regular", "event" and "mixed".
  Default value is regular
    - regular: Purely time controlled frames. Inbound frames are expected
      regularly and a timeout error is raised if they stay away. Outbound
      frames are sent strictly regular
    - event: Frames are excepted to be sent when and only when their
      contents change. For inbound frames it means that a timeout can't be
      defined. Outbound frames are sent on data change. A minimum distance
      in time is defined, which limits the frequency of send events even in
      case of permanent content changes
    - mixed: Outbound frames are send on data change but no more often as
      defined by the minimum distance in time. If no data change has been
      seen for a second specified time parameter then the frame is sent,
      too. Inbound frames are handled like regular frames with the only
      exception that the timeout is related to the specified minimum send
      frequency

- sendPeriod: A numeric integer value specifying the period time of
  regular frames in Milliseconds. Range is [5, 10000] ms. Default value is
  10 ms.

    For mixed mode frames this value specifies the maximum time span in
  between two transmission events.

    For event mode frames this attribute is irrelevant

- eventMinDistance: A numeric integer value specifying the minimum
  distance in time between two transmission events in Milliseconds. Range
  is [5, 10000] ms. Default value is 20 ms.

    For regular frames this attribute is ignored

- checksumStartValue: To avoid confounding frames of different CAN IDs the
  checksum validation uses different checksum definitions for different
  frames. An individual start value of the computation is applied. The
  start value is specified with this attribute. It is an integer number in
  the range [0, 255] and the default value is 0

The following signal related attributes have been defined:

- initialValue: A floating point number in the range [-1e99, 1e99], which
  specifies the inital world value of the signal. Default value is 0.

    For inbound frames, the API will show this value for the signal as
  long as the containing frame has never been received.

    For outbound frames, this value will be sent as long as the APSW has
  not updated the API value yet

### Special signals ###

The sample implements a production level validation of the communication.
It defines a checksum and a sequence counter signal for most frames. (Not
for all however, to get more inhomogeneity and better test coverage into
the code.) The code generation process is supported by specifying naming
schemes for these signals:

- checksum: If a signal has this name then it is considered an 8 Bit
  checksum. The checksum needs to allocate a complete byte of the frame;
  it must not go across a byte location. The checksum is defined to be the
  binary inverted arithmetic sum of all other frame content bytes and the
  frame individual start value

- sequenceCounter: If a signal has this name then it is considered a
  cyclic sequence counter. The counter may have up to eight bit and it may
  go across a byte location in the frame. The counting range is defined by
  the min and max property of the signal. min > max is permitted; this
  means inverse counting direction. A counting cycle always begins with
  min and always ends with max

### Allocation of bits ###

The positioning of signals in the frames has purposely been done in an
inefficient way. This must not be considered a design error of the sample.
Useless crossing of byte boundaries, useless gaps between signals and
mixed byte ordering have been defined just to make the required pack and
unpack code more difficult and to improve the test coverage.
