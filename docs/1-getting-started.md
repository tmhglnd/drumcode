# Getting Started

- Attaching contact microphone to the drums
- Setting up the soundcard connections
- Setting up the computer software
- Receiving contact microphone input input
- Listening for triggers
- Triggering an electronic sound

## Attaching the contact microphone to the drums

1. Get a contact microphone (trigger)

We use a contact microphone to get the direct sound (vibrations) from a drumhead or cymbal. There are various forms of contact microphones that can be used. Some can be bought specifically for drums or other instruments like guitar, but it is also possible to make one by hand. Below a list of common contact microphones and a DIY guide:

- [ddrum trigger](https://www.thomannmusic.com/ddrum_acoustic_pro_pack.htm) (for kick, snare, toms)
- [roland trigger](https://www.thomannmusic.com/roland_rt_30hr_dual_trigger.htm) (for kick, snare, toms)
- [k&k hot spot](https://www.thomannmusic.com/kk_hot_spot.htm) (for kick, snare, toms and for other percussion & cymbals)
- [DIY trigger build guide (coming soon...)]() (for kick, snare, toms and for other percussion & cymbals)

Many of these triggers rely on a so called piezo element. This is a small metal plate with a ceramic top layer. When connecting this to a surface (like a drumhead) it can measure the variations in vibrations and convert those to a small alternating voltage.

2. Attach the contact microphone.

Depending on the trigger you have, follow the instructions of the manufacturer to attach it to the drumhead. If you build the trigger yourself, you can use some stage-tape (or gaffer-tape, gaffa-tape) to attach the contact microphone to the drumhead. **Don't use duct-tape**, since this will leave a lot of glue residue after removing.

## Setting up the soundcard connections

1. Get an external soundcard with instrument input

In order to receive the signal from the contact microphone in the computer we need an external USB soundcard with at least one 1/4" Jack input (sometimes called Hi-Z or Instrument input). Soundcards come in many shapes and price ranges. Depending on the amount of triggers you have you may need a bigger soundcard. Below is a list of some decent soundcards to get started with in the range of €50 - 150:

- [M-audio M-track Duo](https://www.thomann.de/nl/m_audio_m_track_duo.htm)
- [Presonus Studio 24c](https://www.thomann.de/nl/presonus_studio_24c.htm)
- [Behringer UMC404](https://www.thomann.de/nl/social_70th-anniversary.html)

2. Connect the trigger

Connect the trigger with the proper cable to the soundcard. For this you'll need to pay attention to the types of connections. There is XLR (microphone cable) or Jack (instrument cable), and both come in socket & plug variants. For example the ddrum trigger has an XLR output (plug), and the presonus studio interface has an XLR/Jack combo input. So you'll need an XLR socket to XLR plug cable, or XLR socket to Jack plug.

3. Connect the soundcard

Connect the soundcard to the computer via the USB port. You might need a USB dongle depending on the type of cable.

## Setting up the computer software

1. Install soundcard driver

You might need to install some driver based on the soundcard that you bought. Check the website of the manufacturer to make sure and download and install the software.

2. Install PlugData

This project uses the programming environment PlugData. Install it via [https://plugdata.org/download.html](https://plugdata.org/download.html)

3. Setting up PlugData

After downloading, start PlugData. You can open a New Patch via the menu icon or with `cmd/ctrl + n`. Go to the PlugData preferences via the menu (top-left) or with `cmd/ctrl + ,`. In the `Audio Settings` adjust the following settings:

- Samplerate: 44100
- Buffersize: 64
- Output Device: Choose your soundcard here
	- Outputs: Make sure they are `Enabled`
	- You can click `Test` to hear a short beep
- Input Device: Choose your soundcard here
	- Inputs: Make sure they are `Enabled`

## Receiving contact microphone input

