
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
- (number) : the wait time untill hit counts are reported, (default = 250ms, 8th note at 120bpm)

attributes:
- threshold : minimum hits necessary for reporting the output, (default = 1)

### `dc.speed`

### `dc.tempo`

### `dc.direction`

## Utilites

### `dc.calibrate`

### `dc.slide`

### `dc.gate`

### `dc.inrange`

Output the incoming value if it is in the range of the low and high given value. A thin wrapper around the split object. Users that know Max/Pd well can just as good use split or moses.

inlets:
1. (number) is in range?
2. (number) lower limit for range
3. (number) upper limit for range

arguments:
- (number) lower limit for range
- (number) upper limit for range

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