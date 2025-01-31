# `./drum.code` Reference

*DISCLAIMER: This project is currently in development. Please be aware that things may change rapidly and there might be bugs in the software or errors in the documentation. You are welcome to file an issue if you encounter any errors.*

At the moment drumcode is being developed in Pure Data (Plug Data), but I'm considering creating clones for MaxMSP as well.

## Table of Content

A rough outline of the different type of objects in this library:

- [Audio Analysis](#audio-analysis)
- [Time, Tempo, Density](#time-tempo-density)
- [Pitch, Timbre, Descriptors](#pitch-timbre-descriptors)
- [Metronome, Sequencing & Utilities](#metronome-sequencing--utilities)
- [Generators, Algorithms & Patterns](#generators-algorithms--sequences)
- [MIDI & OSC Output](#midi--osc-output)
- [Sound Output](#sound-output)
- [PlugData Useful Common Objects](#plugdata-useful-common-objects)

## Audio Analysis

Use the following objects to analyse the incoming sound from the contact microphone through the external soundcard. The trigger analysis will give you a trigger or short frame of sound to process further for tempo or pitch related analysis.

### `dc.trigger~`

Perform onset detection on the incoming audio signal. The object is fine-tuned for percussive sounds but can also work for other signals. The higher the sensitivity the more triggers are detected in the signal. The range allows to adjust the lower threshold when the trigger is released and can detect another trigger. Gate, filter and wait allow to further fine-tune the onset detection. Connect this object to dc.display~ to have a visualisation.

inlets:
1. (signal) detect incoming triggers
2. (number) sensitivity 0 - 1 (default = 0.5)
3. (number) sensitivity range 0 - 1 (default = 0.3)
4. (number) gate below which no triggers are detected -60 - 0 (default = -60dB)

arguments order:
- (number) sensitivity 0 - 1 (default = 0.5)
- (number) sensitivity range 0 - 1 (default = 0.3)

attributes:
- gate : gate below which no triggers are detected -60 - 0 (default = -60dB)
- wait : how much time to wait till another trigger can occur in ms (default = 62 ms)
- filter : a highpass filter to filter out low frequency content (default = 1700 Hz)
- attack : the attack time for the envelope follower (default = 0.45 ms)
- release : the release time for the envelope follower (default = 15 ms)
- slowramp : the attack and release time for the slow envelope follower (default = 27 ms)

### `dc.trigger.display`

This is a little display that can be connected to the outlet of the `dc.trigger~`. The display shows the incoming signals amplitude and two lines. The upper line is the on-threshold, determined by the sensitivity. The lower line is the off-threshold, determined by the sensitivity range. If the signal goes above the upper line a trigger is detected. If the signal goes below the lower line a next trigger can be detected again.

### `dc.trigger.velocity~`

Output the measured velocity from a trigger detection. The velocity is output as a value between 1 and 127 Depending on the incoming sound the scaling may need to be adjusted. This can be done by enabling the calibration in the third inlet. The velocity curve can also be set with the message -curve or attribute. The trigger is also passed to the left outlet to make sure things stay syncronized. This is because the amplitude measure takes a little time (~3ms) to gather some sound and measure the peak amplitude.

inlets:
1. (signal) audio input from adc~/meter~
2. (trigger) trigger signal input from dc.trigger~
3. (toggle) enable calibration

attributes:
- curve - adjust the velocity curve between 0 and 1 (default=0.7)
- history - adjust the measure time in milliseconds, this adds latency (default=2.5)

### `dc.trigger.frame~`

Capture a short frame of sound when the trigger is detected. This short frame of sound can be used to analyse for various sound descriptors such as pitch, loudness, spectral centroid, noisiness, timbre (mfcc) and more. Connect the trigger to the right inlet and connect the sound to the left inlet.

inlets:
1. (signal) capture a short piece of incoming signal
2. (trigger) detected trigger from drum.trigger~ triggers the frame output

arguments order:
- (number) framesize in samples (default = 256, min = 8, max = 22050)

<!-- ### `dc.display~` -->

## Time, Tempo, Density

Use the following objects to derive tempo related information from the triggers. For example measure the milliseconds between hits, or track the average speed at which you're playing, or see if you're slowing down or speeding up, or count a certain amount of hits in a specific timeframe.

### `dc.trigger.timecontrols`

A combination object of a couple of the common used time analysis features. This object combines the timer, count, speed and direction. This object is in many cases the best starting point if you are a first time user.

inlets:
1. (trigger) Trigger input from dc.trigger~

outlets:
1. The trigger throughput
2. Report the time in milliseconds elapsed between two triggers received at the input.
3. Get the speed "amount" as a value between 0 and 127
4. Get a speed "ramp", ramping up to the speed value, but slowly ramping back to 0 over a specified time
5. Get the direction of speeding up (127) or slowing down (0)
6. Get the counted number of triggers within a short timeframe

### `dc.timer`

Report the time in milliseconds elapsed between two triggers received at the input.

inlets:
1. (trigger) Trigger the timer and report the interval

### `dc.count`

Count the number of received triggers, report when the waiting time is over. As long as triggers are received before the time is the count keeps incrementing and resetting the timer. If the waiting time is over the total is reported. An optional threshold only outputs the count when the amount is high enough.

inlets:
1. (trigger) count the triggers
2. (number) the wait time untill hit counts are reported, (default = 250ms, 8th note at 120bpm)

arguments order:
- (number) the wait time untill hit counts are reported, (default = 250ms, 8th note at 120bpm)

<!-- attributes:
- threshold : minimum hits necessary for reporting the output, (default = 1) -->

### `dc.speed`

Get the speed "amount" as a floating point number between 0 and 1 from a simple average over a history of time millisecond values. The range is calculated from the default range 40 to 1000 milliseconds.

inlets:
1. (trigger)
2. (number) - the fastest speed in milliseconds (default = 40), maps to 1
3. (number) - the slowest speed in milliseconds (default = 1000), maps to 0

arguments order:
- (number) - the fastest speed in milliseconds (default = 40), maps to 1
- (number) - the slowest speed in milliseconds (default = 1000), maps to 0

attributes:
- history : the amount of numbers in the averaging, (default = 4, minimum = 2, maximum = 256)

### `dc.tempo`

A simple taptempo feature. Input a trigger. If the triggers are received within the range of 40 to 200 BPM the estimated tempo is output. This is done over a rolling average of 6 beats. The rolling average is reset when the first incoming value is too high or too low, allowing you to wait and then retrigger the tempo. The taptempo expects a tempo in quarternotes and outputs BPM in quarternotes.

inlets:
1. (trigger) estimate the tempo

arguments:
- (number) history size to take average from (default = 4)

### `dc.direction`

Measure in which direction the tempo of a trigger is going. Speeding up (1) or slowing down (0). With an optional argument you can set the threshold for which a speeding/slowing tempo is detected, the default is above 20 milliseconds. You can also change the -mode to 1, in mode 1 the measure outputs a 0.5 if the tempo is not changing.

inlets:
1. (number) - time between triggers from `dc.timer`

arguments:
- (number) - threshold for speeding/slowing detection in ms (default = 25)

attributes:
- mode : in mode 0 only a `0` or `1` are output for slowing down or speeding up. In mode 1 a `0.5` is output if the speed doesn't change.

### `dc.rhythm.analyse`

Analyse an incoming rhythmical pattern from triggers. The rhythm is quantised to a fixed interval, for example 16th or 8th notes. The tempo is determined by the BPM set in the dc.transport. Therefore a dc.transport is needed to make this object function properly. The rhythm that is output is a list of 1's and 0's where 1 is a detected onset and 0 is a detected rest (nothing detected). The object can output the "rolling" rhythm, a continues output for every note, or a fixed interval based on the output listlength.

inlets:
1. (trigger) input a trigger from dc.trigger~ or dc.trigger.velocity~
2. (number) subdivision quantization for pattern detection (default = 16)
3. (number) report interval and list output length (default = 16)

arguments:
- (number) subdivision quantization for pattern detection (default = 16)
- (number) report interval and list output length (default = 16)

attributes:
- name - give a unique name linked to a dc.transport (optional)

### `dc.rhythm.match`

Match a list of input rhythm with a set of predefined rhythms. If the rhythm is part of the set it will output the corresponding index of that rhythm. Multiple rhyhtms can be provided as a list of 0's and 1's. If the rhythm to match is shorter than the incoming list, the incoming list is sliced and only the last part it is used. For example if the matched rhythm is [1 0 1 1], and the input list is [1 0 0 1 1 0 1 1] the output will still return true (1) because the final 4 values are the same. If you need an exact match you can instead use `[zl.compare]` from the cyclone library.

inlets:
1. (list) a pattern to match with the provided options
2. (list) insert a list to add to match options

arguments:
- (list) initial list to match rhythm to (default = none)

## Metronome, Sequencing & Utilities

### `dc.calibrate`

Rescale the incoming values to an output range based on the highest and lowest values received. This range auto-adapts when the calibration is turned on in the right inlet. Higher or lower numbers are received and measured. The output range is 0-1 by default but can be adjust with arguments.

inlets:
1. (number) incoming value to automatically rescale
2. (number) start/stop calibration/autoscaling

arguments:
- (number) - lower output range (default = 0)
- (number) - higher output range (default = 1)

### `dc.wait`

Limit the speed of incoming triggers/numbers, holding them of for a specific amount of time. After the first input is recieved, a gate closes temporarily. Until the gate is opened no input will be passed through. The gate opens after the specified waiting time in milliseconds.

inlets:
1. (trigger/number) incoming value to limit in speed
2. (number) set waiting time in milliseconds

arguments order:
- (number) set waiting time in milliseconds

### `dc.slide`

Create a slide (ramp down), of values that slide back to a ground value (usually 0) over time, but immediately shoots up when an incoming value is received greater than that ground value. Slides back logarithmically.

inlets:
1. (number) input a number to create a slide for
2. (number) slide amount 0-127 (default = 64)

arguments order:
- (number) slide length 0-127 (default = 64)

attributes:
- interval : set the time interval in milliseconds for reporting the output (default = 10)

### `dc.average`

Compute a rolling average from the incoming number over a history of numbers. The size of the history can be adjusted, but the default is 4.

inlets:
1. (number) average this number
2. (number) history size (default = 4, min = 2, max = 256)

messages:
- clear - clear the history to reset the average

### `dc.gate`

Output the incoming value to the left when it is greater or equal to the set threshold (minimum value), else output it to the right.

inlets:
1. (number) input to gate
2. (number) gate threshold

arguments order:
- (number) gate threshold (default = 0)

### `dc.inrange`

Output the incoming value if it is in the range of the low and high given value. A thin wrapper around the split object. Users that know Max/Pd well can just as good use split or moses.

inlets:
1. (number) is in range?
2. (number) lower limit for range (default = 0)
3. (number) upper limit for range (default = 127)

arguments order:
- (number) lower limit for range (default = 0)
- (number) upper limit for range (default = 127)

<!-- ### `dc.cpu` -->

<!-- ### `dc.latency`  -->

### `dc.transport`

Create a global transport to set the BPM and Time Signature of the patch. Other objects can interface with the global transport, like the dc.sequencer. These objects are synchronised with the transport and start/stop when the transported is started.

inlets:
1. (toggle) start/stop transport
2. (number) set the tempo in BPM (default = 100)
3. (list) set the time signature (default = 4 4)

arguments:
- (number) set the tempo in BPM (default = 100)

attributes:
- timesig - set the time signature in the object
- name - give a unique name to the transport (optional)

messages:
- reset - reset the transport to beginning, bar 1, beat 1

### `dc.metronome`

The metronome outputs triggers and step-numbers in a specified time interval (2, 4, 8, 12, 16, etc), where this number means 1/n, so 4 is 1/4 is a quarter note, and 12 is 1/12 so 8th-note triplets. The counter of the step by default counts to infinite, but you can make it wrap with n-bars by providing a second argument for the counter reset. This object only works if you already have a `[dc.transport]` in the patch.

inlets:
1. (number) division (2, 4, 8, 12, 16, etc) (default = 4, quarter note)

arguments:
- (number) division (2, 4, 8, 12, 16, etc) (default = 4, quarter note)
- (number) reset counter after n-bars (default = 0, no reset)

attributes:
- name - bind to unique name of the transport (optional)

### `dc.clicktrack~`

A clicktrack~ object that outputs bleeps for quarter and eigth notes with an accent on the first note of the measure. You can set the eight note volume and adjust the beep length. Combine this object with dc.transport for it to work. I recommend sending it to [dac~ 3 4] so you can hear it at a different output from your soundcard and not have it mixed with your music that goes to the main speakers.

inlets:
1. (number) eigth note volume 0-127 (default = 0)
2. (number) tone length 0-127 (default = 80)
3. (list) list of two notes for accent and regular tone (default = A6 D6)

arguments:
- (number) eigth note volume 0-127 (default = 0)
- (number) tone length 0-127 (default = 80)
- (list) list of two notes for accent and regular tone (default = A6 D6)

attributes:
- name - bind to unique name of the transport (optional)

## Pitch, Timbre, Descriptors

(coming soon...)

## Generators, Algorithms & Patterns

Use the following objects to generate sequences of values, for example for MIDI notes, velocities or modulations. You can generate things randomly, create a specific sequence of values, train a simple model to learn from a sequence, and do some things algorithmically with chance over counting.

### `dc.chance`

Let the input pass through to the output on the left outlet with a certain amount of chance between 0-100%. Every other case the input is passed to the right outlet. Default chance is 50%.

inlets:
1. (trigger/number) pass through to output with chance
2. (number) chance percentage 0-100 (default = 50)

arguments:
- (number) chance percentage 0-100 (default = 50)

### `dc.every`

Let the input pass through to the output on the left outlet every n-events. Every other time the input is passed to the right outlet. The default every times is 8.

inlets:
1. (trigger/number) pass through to output every n-events
2. (number) every time (default = 8)

arguments:
- (number) every time (default = 8)

### `dc.random`

Generate random values within a minimum and maximum range. The low and high values are included. You can specify a default range with "amplitude"/"amp", "velocity"/"vel", "note"/"pitch", "duration"/"dur" to quickly get some output in a desired range. Otherwise specify the low, high range, and if the output should be integer (1, default) or float (0)

inlets:
1. (trigger) trigger the output of a random number
2. (number) the lowest possible value (default = 36)
3. (number) the highest possible value (default = 72)

arguments:
- (number) the lowest possible value (default = 36)
	- or: (symbol) a single word to set the range (note, velocity, duration, amplitude)
- (number) the highest possible value (default = 72)
- (on/off) the random numbers are only whole numbers (default = true (1))

<!-- ### `dc.list.spread` -->

### `dc.step`

Step through the values of a list for every time the object receives a trigger. The list can be defined as arguments or via the right inlet. A number can be send to go to a specific step as well. Changing the list resets the counter to the beginning.

inlets:
1. (trigger/number) next step in sequence, or go to number
2. (list) input a list of numbers for the sequence

arguments:
- (number) as many numbers you want to have part of the list

### `dc.choose`

Randomly choose a value from a list of predefined numbers for every time the object receives a trigger. The list can be defined as arguments or via the right inlet.

inlets:
1. (trigger/number) randomly choose the next value
2. (list) input a list of numbers for the sequence

arguments:
- (number) as many numbers you want to have part of the list

### `dc.learn`

This object learns a pattern from an incoming list of values and when send a trigger will play a pattern that is similar to the learned one. This is based on the probability of what is most likely to happen next. The learning is done through a Markov Chain, a probabilistic sequence prediction model. The default order of the chain is 2, but can be adjusted with -order attribute. A list send to the second inlet with clear the model and train on that list. A list send to the third inlet with add the list to the previous training.

inlets:
1. (trigger) predict the next value and output
2. (list) clear and learn from incoming list pattern
3. (number/list) add to the learned pattern, without clearing

arguments:
- (list) learn from list pattern

attributes:
- order - set the markov chain order (default = 2)

<!-- ### `dc.scale` -->

## MIDI & OSC

Use these objects if you prefer to use other software (like a DAW such as Ableton, Logic or other coding language like SuperCollider, Max) and you want to send the output from the analysis to those platforms. You can send messages over MIDI (midi notes and control change) or over OSC (Open Sound Control).

<!-- ### `dc.midi.info` -->

### `dc.note.scale`

Map the incoming MIDI note to a note in a specified scale with a specified root. Scale name and root name can be specified as argument or via the 2nd and 3rd inlets. Available scales: major, minor, minor_harmonic, minor_melodic, dorian, phrygian, lydian, mixolydian, locrian, major_pentatonic, minor_pentatonic, chromatic. Default is major c.

inlets:
1. (number) MIDI pitch to map to scale
2. (message) scale name for mapping
3. (message) root name for transposing

arguments:
- (message) scale name for mapping
- (message) root name for transposing

### `dc.note.out`

Send a MIDI-note to an external platform to trigger sounds. This can be a DAW, an external hardware Synth, or something else. Choose the devices you want to output to via the MIDI Preferences in Pd.

inlets:
1. (number/trigger) trigger the MIDI note (default = 60)
2. (number) set the MIDI velocity 1-127 for note-on (default = 120)
3. (number) set the note duration in milliseconds (default = 250)
4. (number) set the MIDI channel to send to (default = All)

arguments:
- (number) set the MIDI velocity 1-127 for note-on (default = 120)
- (number) set the note duration in milliseconds (default = 250)
- (number) set the MIDI channel to send to (default = All)

<!-- ### `dc.midi.control` -->

### `dc.osc.send`

Create a client connected to a specified ip-address and port number. Allowing you to send OSC-messages from the `dc.osc.message` object to the specified ip-address and port. Only one of this object is needed in your patch per ip-address and port you want to send to. If you need more, please use the unique naming attribute to make sure the objects send to the correct location.

inlets:
1. (message) the osc-message to send, not needed when using `dc.osc.message`
2. (message) the ip-address to send to (default = 127.0.0.1 / localhost)
3. (number) the port to send to (default = 4880)

arguments order:
- (message) the ip-address to send to (default = 127.0.0.1 / localhost)
- (number) the port to send to (default = 4880)

attributes:
- name : unique name within patcher to bind other dc.osc.message objects to (optional)

### `dc.osc.message`

Format an OSC-message from the incoming value and send out via the `[dc.osc.send]` object. This object only works in combination with the dc.osc.send in your patch. Specify the osc-address pattern as an argument. You can use a unique -name if you prefer.

inlets:
1. (number) - send the incoming number as OSC-message

arguments order: order:
- (osc-address) - set the OSC-message address (default = /undefined)

attributes:
- name : bind to a named dc.osc.send (optional)

## Sound Output

Use the following objects if you want to create some sound directly in PureData / PlugData. Depending on the instrument you can trigger them with a note, a bang (trigger) or a number. Below the sound generators (synth, sample and sampler) there are also some effects (fx) that you can use to extend the sound design. For example with a reverb, delay or distortion.

### `dc.synth~`

A simple polyphonic synth beep made from a sinewave with some distortion. Useful to quickly create a sound to test if a patch is working, to create a clicktrack to play along with, or to actually use for musical purposes of course!

inlets:
1. (trigger/number) MIDI note pitch triggers the note 0-127 (default = 60)
2. (number) velocity/volume 1-127 (default = 127)
3. (number) note length amount 0-127 (default = 30)
4. (number) distortion amount (0-127) (default = 0)

arguments:
- (number) velocity/volume 1-127 (default = 127)
- (number) note length amount 0-127 (default = 30)
- (number) distortion amount 0-127 (default = 0)

### `dc.sample~`

Play a sample (soundfile) from the computer when a trigger (bang) is send to the left inlet. The sound can be loaded via the read message send to the left inlet. Alternatively the first argument can be the name of the soundfile if the file is in the searchpath. For example by adding the object [declare -path /path/to/sounds/folder]. Then easily load the sound with for example: [dc.sample~ bell.wav]

inlets:
1. (trigger/number/read) play the sound, play the sound with a different playback speed, load a soundfile
2. (number) velocity of the sound 0-127 (default = 120)

arguments:
- (name) a name or path of a soundfile to load

### `dc.sampler~`

Play multiple samples (soundfiles) from a loaded folder of sounds from the computer when a trigger (bang) or number (number) is send to the left inlet. The sound can be loaded via the "read" message send to the left inlet. The number send ot the inlet is the index of the loaded sample. With the message "stop" you can stop the sound while it is still playing.

inlets:
1. (trigger/number/read/stop) trigger first sample, play the index of the sample, load a folder, stop the sound
2. (number) velocity of the sound 0-127 (default = 120)
3. (number) playback rate 0-127 (default = 64)

arguments:
- (path) a filepath to a folder to load samples from

### `dc.noise~`

A polyphonic filtered whitenoise synth. Used to created more percussive sounds with some simple filtered noise and an attack and decay. Snare-dum-ish or hihat-ish sounds can be created.

inlets:
1. (trigger/number) Velocity triggers the noise (0-127) (default = 120)
2. (number) noise length amount 0-127 (default = 30)
3. (number) filter cutoff 0-127 (default = 70)
4. (number) filter resonance 0-127 (default = 40)

arguments:
- (number) noise length amount 0-127 (default = 30)
- (number) filter cutoff 0-127 (default = 70)
- (number) filter resonance 0-127 (default = 40)

### `dc.gain~`

A stereo gain slider. As an alternative for the gain~ and gain2~ sliders, because those sometimes hang in Plugdata.

inlets:
1. (signal) left signal to gain
2. (signal) right signal to gain

### `dc.fade~`

Fade a (stereo) signal in or out. The fade in/out can be started with a trigger (switching between states) or it can be forced with a toggle or the number 0 or 1 The 4th inlet allows you to set the fade time in milliseconds with a number. The fade has a cubic ramp.

inlets:
1. (signal) left signal to fade
2. (signal) right signal to fade
3. (trigger/number) trigger switches signal on/off, 1 turns on, 0 turns off
4. (number) fade time in milliseconds (default = 25)

arguments:
- (number) fade time in milliseconds (default = 25)

### `dc.fx.delay~`

A delay effect in an "analog tape style" consisting of a delaytime, feedback amount and a damping filter. All the parameters range from 0-127 for ease of use with MIDI values.

inlets:
1. (signal) sound to be delayed
2. (number) delaylength 0 - 127 (default = 40)
3. (number) feedback 0 - 127 (default = 90)
4. (number) damping 0 - 127 (default = 70)

arguments:
- (number) delaylength 0 - 127 (default = 40)
- (number) feedback 0 - 127 (default = 90)
- (number) damping 0 - 127 (default = 70)

### `dc.fx.degrade~`

A degrading filter effect, giving a "8bit style" to the sound. Consisting of a downsampling algorithm. The parameter ranges from 0-127 for ease of use with MIDI values.

inlets:
1. (signal) sound to be degraded
2. (number) degrading amount 0-127 (default = 64)

arguments:
- (number) degrading amount 0-127 (default = 64)

### `dc.fx.distortion~`

A distortion effect in an "analog soft-clipping style". The distortion amount is set in a range from 0-127 for ease of use with MIDI values.

inlets:
1. (signal) sound to distort
2. (number) distortion amount 0 - 127 (default 40)

arguments:
- (number) distortion amount 0 - 127 (default 40)

### `dc.fx.filter~`

A lowpass filter effect in an "analog style" consisting of a cutoff frequency and a resonance. All the parameters range from 0-127 for ease of use with MIDI values.

inlets:
1. (signal) sound to be filtered
2. (number) filter cutoff 0-127 (default = 70)
3. (number) filter resonance 0-127 (default = 40)

arguments:
- (number) filter cutoff 0-127 (default = 70)
- (number) filter resonance 0-127 (default = 40)

### `dc.fx.reverb~`

A reverb effect in an "plate style" consisting of a roomsize and a brightness/damping filter. All the parameters range from 0-127 for ease of use with MIDI values.

inlets:
1. (signal) sound to be reverberated
2. (number) roomsize 0 - 127 (default = 40)
3. (number) brightness 0 - 127 ( default = 40)

arguments:
- (number) roomsize 0 - 127 (default = 40)
- (number) brightness 0 - 127 ( default = 40)

<!-- ### `dc.synth~` -->

## PlugData Useful Common Objects

There are many objects already in PlugData (and PureData) by default. Either by being part of the default application, or via some other libraries such as Cyclone and ELSE. These objects can be very useful as well when patching on projects with drumcode. Some of these objects are already in use throughout the examples and templates. These objects are listed below:

### `adc~` & `dac~`

### `meter~` & `scope~`

### `gain~` & `gain2~`

### button `bng` (b) & toggle `tgl` (t)

### `hslider` & `vslider`

### `+`, `-`, `*`, `/`

### number `floatbox` (f)/(i)

### message `msg` (m)

### `scale`

### `select`

### `counter`

### `gate`

### `switch`
