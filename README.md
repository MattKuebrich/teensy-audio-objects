# teensy-audio-objects

These are simple audio objects I've written for the [Teensy Audio Library](https://www.pjrc.com/teensy/td_libs_Audio.html). I should mention I don't _really_ know what I'm doing, but these have been useful in my own synth DIY projects and a fun challenge.

The example .ino sketches assume you're using a Teensy 3.x or 4.x with the [Teensy Audio Adapter](https://www.pjrc.com/store/teensy3_audio.html) and have a few potentiometers connected. The audio objects are included locally, so there is no need to make modifications to your existing Teensy Audio Library. I'm using [Teensyduino](https://www.pjrc.com/teensy/td_download.html) on a Mac to write and test these.

**Completed Audio Objects:**

* [Bernoulli Gate](https://github.com/MattKuebrich/teensy-audio-objects/tree/main/bernoulligate)
* [Bytebeat](https://github.com/MattKuebrich/teensy-audio-objects/tree/main/bytebeat)
* [Chaos Noise](https://github.com/MattKuebrich/teensy-audio-objects/tree/main/chaosnoise)
* [Comparator](https://github.com/MattKuebrich/teensy-audio-objects/tree/main/comparator)
* [DC Block](https://github.com/MattKuebrich/teensy-audio-objects/tree/main/dcblock)
* [Dust](https://github.com/MattKuebrich/teensy-audio-objects/tree/main/dust)
* [FM Drum](https://github.com/MattKuebrich/teensy-audio-objects/tree/main/fmdrum)
* [Function Shaper](https://github.com/MattKuebrich/teensy-audio-objects/tree/main/functionshaper)
* [Gate to Trigger](https://github.com/MattKuebrich/teensy-audio-objects/tree/main/gatetotrigger)
* [Readout](https://github.com/MattKuebrich/teensy-audio-objects/tree/main/readout)
* [Quantizer](https://github.com/MattKuebrich/teensy-audio-objects/tree/main/quantizer)
* [Ring Modulator](https://github.com/MattKuebrich/teensy-audio-objects/tree/main/ringmodulator)
* [Sample and Hold](https://github.com/MattKuebrich/teensy-audio-objects/tree/main/samplehold)
* [Shift Register / Rungler](https://github.com/MattKuebrich/teensy-audio-objects/tree/main/shiftregister)
* [Slew Limiter](https://github.com/MattKuebrich/teensy-audio-objects/tree/main/slewlimiter)
* [STK Effect](https://github.com/MattKuebrich/teensy-audio-objects/tree/main/stkeffect)

**In Development:**
* Bitbeat?
* Envelope Follower
* Limiter
* [AudioSynthWaveformModulated](https://www.pjrc.com/teensy/gui/?info=AudioSynthWaveformModulated) with sync input
* A version of the Audio System Design Tool for Teensy Audio Library with all of these objects included
