## Chaos Noise

This is a chaotic noise generator which creates vinyl-like hiss, static and pops.

It is adapted from Paul Batchelor's [chaosNoise algorithm from his sndkit audio toolkit](https://pbat.ch/sndkit/chaosnoise/).

The even noisier "broken" mode was adapted from Michael Hetrick's [Crackle VCV Rack module](https://github.com/mhetrick/hetrickcv/blob/master/src/Crackle.cpp).

Both of those projects are originally based on the [Crackle UGen in Supercollider](https://doc.sccode.org/Classes/Crackle.html).

### Functions
``chaos(amount);``

``rate(freq);``

``mode(mode);``

Supported modes:
* CLASSIC
* BROKEN


