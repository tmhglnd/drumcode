# `./drum.code`

**A library of tools for hybrid drums (or instruments), with onset detection, timbre analysis, midi and osc trigger outputs, and more**

<!-- [**🙏 Support me by buying me a coffee on ko-fi**](https://ko-fi.com/tmhglnd) -->

- [Install](#-install)
- [Getting Started](./docs/getting-started.md)
- [Documentation](./docs/README.md)

⭐️ **watch and star this repo to keep up-to-date with the latest results of my research**

## 📟 About

Drumcode (stylized as `./drum.code`) is a live coding performance for human and computer. During the performance the computer acts as a co-performer playing itself by making changes in the code while listening and reacting to patterns played on the drums. On the other side the human will react to the sounds made by the computer resulting in a dialogue between the analog and digital worlds of both performers. The code is generated in real-time, based on previous programmed live coding performances and pre-coded snippets. Decisions are made via machine learning techniques trained on rhythmical patterns and tuned probabilities.

This library consists of tools, utilities, practices and research that I am currently working on in order to create the live performance. The project has recently been granted funding by the Creative Industries Fund in the Netherlands. Within the scope of this fund it is my goal to not only create these tools for myself, but also give workshops to drummers (and other musicians) to learn about creative coding and creating a hybrid instrument from their acoustic drums. This project is a continuation of my research in algorithmic and electronic music composition and connects in various ways with my other projects such as the [Mercury live coding environment](https://github.com/tmhglnd/mercury), the [Mercury Playground](https://github.com/tmhglnd/mercury-playground) and the [Total Serialism](https://github.com/tmhglnd/total-serialism) library.

![`./drum.code` live performance. Photo by Paulus ](/media/drumcode.jpg)

## 🚀 Install

This library runs in PureData (0.55.0+) or PlugData (v0.9.2+). If you're a first time user I recommend you install [**PlugData**](https://plugdata.org/download.html) first, after that do:

- [**Download `drumcode`**](https://github.com/tmhglnd/drumcode/archive/refs/heads/main.zip), Unzip folder and move to `/Documents/plugdata/externals`, rename the folder to `drumcode`.

OR (*for advanced git users:*)

- `$ cd ~/Documents/plugdata/externals`, `$ git clone https://github.com/tmhglnd/drumcode.git`

### Dependencies

The drumcode library uses the following dependencies, which you will have to download and install separately before starting to use drumcode.

- [Fluid Corpus Manipulation](https://www.flucoma.org/download/)
	- Download the *Pure Data Binaries*
	- Unpack the `.dmg` `.zip` or `.tar.gz` (depending on your OS)
	- Place the `FluidCorpusManipulation` folder in `/Documents/plugdata/externals`
- [Cyclone](https://github.com/porres/pd-cyclone/) (PureData only! included in PlugData by default)
	- When using PureData, install via `Help > Find Externals`
- [ELSE](https://github.com/porres/pd-else/) (PureData only! included in PlugData by default)
	- When using PureData, install via `Help > Find Externals`

### Usage

1. Open PlugData and start a `new patch`
2. Place the following object in the patch: `[declare -path drumcode/pd]`
3. Create an object to check if it is working. Objects are typed as `[dc.objectNameHere]`

- Open the `drumcode-objects-list.pd` to get a quick list of all available objects.
- Open the `drumcode-objects-overview.pd` to get an overview of available objects with small examples and explanation.
- Open some of the patches in the `/templates` folder to get some quick ways to start
- Open the [getting started guide](./docs/getting-started.md) for a tutorial

## 🥁 Performances & Publications

- [./drum.code at The Overkill Festival in Enschede, NL](https://youtu.be/AoOR0NR0smk?si=ljSXh_uKKaQGIodq&t=112)
- [./drum.code in Proceedings of the AIMC 2023](https://aimc2023.pubpub.org/pub/micjpv5j)
- [./drum.code at the AI Music Creativity conference in Brighton, UK](https://www.youtube.com/live/d0RMUqcbhmQ?si=aTXUo32V00xjPMpJ&t=3739)
- [Morph with Rafaele Andrade at Gaudeamus Muziekweek 2023](https://www.youtube.com/watch?v=nHwbq-yrC2A)
- [Morph with Lina Bautista at NIME/Gaudeamus Muziekweek 2024](https://www.youtube.com/watch?v=SXl8asBUsng)

### 📝 Cite this work

Hoogland, T. (2023). './drum.code'. *AIMC 2023*. Retrieved from https://aimc2023.pubpub.org/pub/micjpv5j

```bibtex
@article{Hoogland2023drum,
	author = {Hoogland, Timo},
	journal = {AIMC 2023},
	year = {2023},
	month = {aug 29},
	note = {https://aimc2023.pubpub.org/pub/micjpv5j},
	publisher = {},
	title = {./drum.code},
}
```

## 🔭 Goals

- An accessible, documented, entry-level toolkit/library for working with acoustic instruments and electronic music
- Research into real-time onset-detection, timbre-analysis and other sound descriptors for acoustic instruments and creating a documented open-source toolkit/library
- Research into pattern detection, tempo detection and other temporal based descriptors through machine learning classification techniques and other techniques such as auto-correlation
- Research in working with contact microphones on drums and other acoustic instruments and documentation with good practices and findings
- Creating ways to connect the toolkit with other platforms via protocols such as MIDI, OSC and DMX
- Combining the library with open-source live coding languages such as the Mercury Playground
- Using live coding techniques and languages to create electronic music with self-build triggers
- Research into training neural networks on small live coded datasets to generate, suggest or adjust code in real-time based on external input from for example matched descriptors of the acoustic instrument.
- Using the library to give workshops to drummers (and potentially other musicians) in which live interaction between the acoustic drums and digital electronic music is created through creative coding. 

## 🔋 Powered By

- This project has been granted funding from [**Creative Industries Fund NL**](https://stimuleringsfonds.nl/en/)

![](/media/sci-logo.jpg)

## 🙏 Thanks

- [Fluid Corpus Manipulation Library](https://www.flucoma.org/) by Tremblay, P.A., Green, O., Roma, G., Bradbury, J., Moore, T., Hart, J., & Harker, A.
- [ELSE Library](https://github.com/porres/pd-else/) by Alexandre Torres Porres
- [Cyclone Library](https://github.com/porres/pd-cyclone) by Alexander Torres Porres
- [PlugData](https://github.com/plugdata-team/plugdata) by Tim Schoen

## ✨ Inspiration & Reading

For this project I've found inspiration in many different places, such as from different artists, coders, musicians, papers, and more. Thanks to all the great people working in this field for inspiring me.

- [The Fluid Corpus Manipulation Project](https://www.flucoma.org/) 
	- Machine Learning/Listening, Software Library
- [Jojo Mayer - Nerve](https://www.youtube.com/watch?v=SIahbUYxdfE) 
	- Drums, Electronics, Live Band
- [Jojo Mayer - Me/Machine](https://www.youtube.com/watch?v=WJVPCKzUKF0)
	- Drums, Electronics
- [Yaxu & Rephlex - Canute](https://www.youtube.com/watch?v=uAq4BAbvRS4) 
	- Electronic Drums, Live Coding
- [Graham Dunning - Mechanical Techno](https://www.youtube.com/watch?v=HG8qR75R-as) 
	- Triggers, DIY Instrument
- [Dan Mayo - Black Ash](https://www.youtube.com/watch?v=UVaoFt6rFGQ)
	- Drums, Live Electronics
- [Gerri Jäger - Solo Lux](https://www.youtube.com/watch?v=onmv5ZEj1fY)
	- Drums, Triggers, Live Electronics
- [Ian Chang - Guzheng](https://www.youtube.com/watch?v=HCdocdYcenk)
	- Drums, Mesh heads, Software Library Sensory Percussion
- [Owen Green & Rodrigo Constanza - Talk Play Talk](https://youtu.be/aslEJBB9iT4?si=ahGDTmu7IG6gE6Mf)
	- Live electronics, Hybrid Instrument, Machine Listening
- [SP-Tools by Rodrigo Constanza](https://rodrigoconstanzo.com/2022/07/sp-tools-machine-learning-tools-for-drums-and-percussion-alpha/)
	- Machine Learning, Software Library

## 📝 License

[The GNU GPL v.3 License](https://choosealicense.com/licenses/gpl-3.0/)

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
