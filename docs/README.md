
# `./drum.code` documentation

*DISCLAIMER: This project is currently in development. Please be aware that things may change rapidly and there might be bugs in the software or errors in the documentation. You are welcome to file an issue if you encounter any errors.*

At the moment drumcode is being developed in Max/MSP, although I am thinking of porting to Pure Data for more accessibility.

## Table of Content

A rough outline of the different type of objects in this library:

- [Audio Analysis](#audio-analysis)
- [Time, Tempo, Density](#time-tempo-density)
- [Pitch, Timbre, Descriptors](#pitch-timbre-descriptors)
- [Utilities](#utilites)
- [Number Generators & Sequences](#number-generators--sequences)
- [MIDI & OSC Output](#midi--osc-output)
- [Sound Output](#sound-output)

## Audio Analysis

### `dc.trigger~`

Perform onset detection on the incoming audio signal. The object is fine-tuned for percussive sounds but can also work for other signals. The higher the sensitivity the more triggers are detected in the signal. The range allows to adjust the lower threshold when the trigger is released and can detect another trigger. Gate, filter and wait allow to further fine-tune the onset detection. Connect this object to dc.display~ to have a visualisation.

inlets:
1. (signal) detect incoming triggers
2. (number) sensitivity 0 - 1 (default = 0.5)
3. (number) sensitivity range 0 - 1 (default = 0.3)
4. (number) gate below which no triggers are detected -60 - 0 (default = -60dB)

arguments:
- (number) sensitivity 0 - 1 (default = 0.5)
- (number) sensitivity range 0 - 1 (default = 0.3)

attributes:
- gate : gate below which no triggers are detected -60 - 0 (default = -60dB)
- wait : how much time to wait till another trigger can occur in ms (default = 62 ms)
- filter : a highpass filter to filter out low frequency content (default = 1700 Hz)
- attack : the attack time for the envelope follower (default = 0.45 ms)
- release : the release time for the envelope follower (default = 15 ms)
- slowramp : the attack and release time for the slow envelope follower (default = 27 ms)

### `dc.triggerwindow~`

### `dc.display~`

## Time, Tempo, Density

### `dc.timer`

Report the time in milliseconds elapsed between two triggers received at the input.

inlets:
1. (trigger) Trigger the timer and report the interval

### `dc.count`

Count the number of received triggers, report when the waiting time is over. As long as triggers are received before the time is the count keeps incrementing and resetting the timer. If the waiting time is over the total is reported. An optional threshold only outputs the count when the amount is high enough.

inlets:
1. (trigger) count the triggers
2. (number) the wait time untill hit counts are reported, (default = 250ms, 8th note at 120bpm)

arguments:
- (number) the wait time untill hit counts are reported, (default = 250ms, 8th note at 120bpm)

attributes:
- threshold : minimum hits necessary for reporting the output, (default = 1)

### `dc.speed`

Get the speed "amount" as a floating point number between 0 and 1 from a simple average over a history of time millisecond values. The range is calculated from the default range 40 to 1000 milliseconds.

inlets:
1. (trigger)
2. (number) - the fastest speed in milliseconds (default = 40), maps to 1
3. (number) - the slowest speed in milliseconds (default = 1000), maps to 0

arguments:
- (number) - the fastest speed in milliseconds (default = 40), maps to 1
- (number) - the slowest speed in milliseconds (default = 1000), maps to 0

attributes:
- history : the amount of numbers in the averaging, (default = 4, minimum = 2, maximum = 256)

### `dc.tempo`

### `dc.direction`

## Utilites

### `dc.calibrate`

### `dc.slide`

Create a slide (ramp down), of values that slide back to a ground value (usually 0) over time, but immediately shoots up when an incoming value is received greater than that ground value. Slides back logarithmically.

inlets:
1. (number) input a number to create a slide for
2. (number) slide length 0-1

arguments:
- (number) slide length 0-1

attributes:
- interval : set the time interval in milliseconds for reporting the output (default = 10)

### `dc.average`

Compute a rolling average from the incoming number over a history of numbers. The size of the history can be adjusted, but the default is 4.

inlets:
1. (number) average this number
2. (number) history size (default = 4, min = 2, max = 256)

messages:
- clear - clear the history to reset the average

### `dc.thresh`

Output the incoming value to the left when it is greater or equal to the set threshold (minimum value), else output it to the right.

inlets:
1. (number) input to gate
2. (number) gate threshold

arguments:
- (number) gate threshold (default = 0)

### `dc.inrange`

Output the incoming value if it is in the range of the low and high given value. A thin wrapper around the split object. Users that know Max/Pd well can just as good use split or moses.

inlets:
1. (number) is in range?
2. (number) lower limit for range (default = 0)
3. (number) upper limit for range (default = 127)

arguments:
- (number) lower limit for range (default = 0)
- (number) upper limit for range (default = 127)

### `dc.cpu`

### `dc.latency`

## Pitch, Timbre, Descriptors

## Number Generators & Sequences

### `dc.random`

### `dc.sometimes`

### `dc.every`

### `dc.list.spread`

### `dc.step`

### `dc.scale`

## MIDI & OSC Output

### `dc.midi.info`

### `dc.midi.note`

### `dc.midi.control`

### `dc.osc.send`

Create a client connected to a specified ip-address and port number. Allowing you to send OSC-messages from the `dc.osc.message` object to the specified ip-address and port. Only one of this object is needed in your patch per ip-address and port you want to send to. If you need more, please use the unique naming attribute to make sure the objects send to the correct location.

inlets:
1. (message) the osc-message to send, not needed when using `dc.osc.message`
2. (message) the ip-address to send to (default = 127.0.0.1 / localhost)
3. (number) the port to send to (default = 4880)

arguments:
- (message) the ip-address to send to (default = 127.0.0.1 / localhost)
- (number) the port to send to (default = 4880)

attributes:
- name - unique name within patcher to bind other dc.osc.message objects to (optional)

### `dc.osc.message`

Format an OSC-message and send the incoming value out via the `dc.osc.send` object. This object only works in combination with the dc.osc.send in the patch. Specify the osc-address pattern as an argument.

inlets:
1. (number) - send the incoming number as OSC-message

arguments:
- osc-address - set the OSC-message address (default = /unnamed)

attributes:
- name - bind to a named dc.osc.send (optional)

## Sound Output

### `dc.bleep~`

### `dc.synth~`