# `./drum.code`

**A library of tools for hybrid drums (or instruments), with onset detection, timbre analysis, midi and osc trigger outputs, and more**

<!-- [**🙏 Support me by buying me a coffee on ko-fi**](https://ko-fi.com/tmhglnd) -->

- [Documentation](./docs/README.md)

⭐️ **watch and star this repo to keep up-to-date with the latest results of my research**

## 📟 About

Drumcode (stylized as `./drum.code`) is a live coding performance for human and computer. During the performance the computer acts as a co-performer playing itself by making changes in the code while listening and reacting to patterns played on the drums. On the other side the human will react to the sounds made by the computer resulting in a dialogue between the analog and digital worlds of both performers. The code is generated in real-time, based on previous programmed live coding performances and pre-coded snippets. Decisions are made via machine learning techniques trained on rhythmical patterns and tuned probabilities.

This library consists of tools, utilities, practices and research that I am currently working on in order to create the live performance. The project has recently been granted funding by the Creative Industries Fund in the Netherlands. Within the scope of this fund it is my goal to not only create these tools for myself, but also give workshops to drummers (and other musicians) to learn about creative coding and creating a hybrid instrument from their acoustic drums. This project is a continuation of my research in algorithmic and electronic music composition and connects in various ways with my other projects such as the [Mercury live coding environment](https://github.com/tmhglnd/mercury), the [Mercury Playground](https://github.com/tmhglnd/mercury-playground) and the [Total Serialism](https://github.com/tmhglnd/total-serialism) library.

![`./drum.code` live performance. Photo by Paulus ](/media/drumcode.jpg)

## 🚀 Install

This library runs in PureData (0.55.0+) or PlugData (v0.9.2+). If you're a first time use I recommend you install [PlugData](https://plugdata.org/download.html)

1. `Click Code > Download ZIP`

2. `Unzip folder in /Documents/plugdata/externals`

3. Rename the folder to `drumcode` if necessary (sometimes when downloading it is called `drumcode-main`).

4. Open PlugData and start a `new patch`. Place the following object in the patch:

5. `[declare -path drumcode]`

6. Create an object to check if it is working, for example `[dc.timer]`

7. Open the `drumcode-objects-overview.pd` to get an overview of available objects.

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

## 📝 License

[The GNU GPL v.3 License](https://choosealicense.com/licenses/gpl-3.0/)

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
