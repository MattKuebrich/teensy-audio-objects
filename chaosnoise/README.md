# Chaos Noise

This is a chaotic noise generator which creates vinyl-like hiss, static and pops. 

It is adapted from Paul Batchelor's [chaosNoise algorithm from his sndkit audio toolkit](https://pbat.ch/sndkit/chaosnoise/). The even noisier "broken" mode was adapted from Michael Hetrick's [Crackle VCV Rack module](https://github.com/mhetrick/hetrickcv/blob/master/src/Crackle.cpp). Both of those projects are originally based on the [Crackle UGen in Supercollider](https://doc.sccode.org/Classes/Crackle.html).

## Audio Connections

| Port  | Purpose |
| ----- | ------- |
| Out 0  | Chaos Noise  |


## Functions
### **chaos**(amount);
Set the chaos amount, from 0.0 to 1.0.

### **rate**(freq);
Set the rate of the noise is processed, which changes the tone quality / pitch of the noise.

### **mode**(mode);
Set the chaos noise mode.

Supported modes:
* CLASSIC
* BROKEN
