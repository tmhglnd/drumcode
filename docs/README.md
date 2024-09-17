
# `./drum.code` documentation

*DISCLAIMER: This project is current in development. Please be aware that things may change rapidly and there might be bugs in the software or errors in the documentation. You are welcome to file an issue if you encounter any errors.*

At the moment drumcode is being developed in Max/MSP, although I am thinking of porting to Pure Data for more accessibility.

## Table of Content

A rough outline of the different type of objects in this library

- Signal analysis
- Time, Tempo, Density
- Pitch, Timbre, Descriptors
- Number Generators & Sequences
- MIDI & OSC Output
- Sound Output

## Signal Analysis

### `dc.trigger~`

Perform onset detection on the incoming audio signal. The object is fine-tuned for percussive sounds but can also work for other signals. The higher the sensitivity the more triggers are detected in the signal. The range allows to adjust the lower threshold when the trigger is released and can detect another trigger. Gate, filter and wait allow to further fine-tune the onset detection. Connect this object to dc.display~ to have a visualisation.

inlets:
1. (signal) : detect incoming triggers
2. (number) : sensitivity 0 - 1 (default = 0.5)
3. (number) : sensitivity range 0 - 1 (default = 0.3)
4. (number) : gate below which no triggers are detected -60 - 0 (default = -60dB)

arguments:
- (number) : sensitivity 0 - 1 (default = 0.5)
- (number) : sensitivity range 0 - 1 (default = 0.3)

attributes:
- gate : gate below which no triggers are detected -60 - 0 (default = -60dB)
- wait : how much time to wait till another trigger can occur in ms (default = 62 ms)
- filter : a highpass filter to filter out low frequency content (default = 1700 Hz)
- attack : the attack time for the envelope follower (default = 0.45 ms)
- release : the release time for the envelope follower (default = 15 ms)
- slowramp : the attack and release time for the slow envelope follower (default = 27 ms)

## Time, Tempo, Density

### `dc.timer`

Report the time between two consecutive triggers in milliseconds

inlets:
1. (trigger) : Trigger the timer and report the interval

### `dc.count`

Count the number of received triggers, report when the waiting time is over. As long as triggers are received before the time is the count keeps incrementing and resetting the timer. If the waiting time is over the total is reported. An optional threshold only outputs the count when the amount is high enough.

inlets:
1. (trigger) : count the triggers
2. (number) : the wait time untill hit counts are reported, (default = 250ms, 8th note at 120bpm)

arguments:
- (number) : the wait time untill hit counts are reported, (default = 250ms, 8th note at 120bpm)

attributes:
- threshold : minimum hits necessary for reporting the output, (default = 1)

### `dc.speed`



### `dc.`

## Pitch, Timbre, Descriptors

## Number Generators & Sequences

## MIDI & OSC Output

### `dc.osc.send`

Create a client connected to a specified ip-address and port number. Allowing to send osc messages from the `dc.osc.message` object to that ip and port.

inlets:
1. (message) : the osc-message to send, not needed when using `dc.osc.message`
2. (message) : the ip-address to send to (default = 127.0.0.1 / localhost)
3. (number) : the port to send to (default = 4880)

arguments:
- (message) : the ip-address to send to (default = 127.0.0.1 / localhost)
- (number) : the port to send to (default = 4880)

attributes:
- name - unique name within patcher to bind other dc.osc.message objects to (optional)

### `dc.osc.message`

Format an osc message and send the incoming value out via the `dc.osc.send` object. This object only works in combination with a dc.osc.send in the patch. Specify the osc-address pattern as an argument.

inlets:
1. (number) - send the incoming number as osc message

arguments:
- osc-address - set the osc message address (default = /unnamed)

attributes:
- name - bind to a named dc.osc.send (optional)

## Sound Output