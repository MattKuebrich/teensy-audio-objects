# Chaos Maps

This object implements two classic chaotic maps, a logistic map and an n-fold map. It can be used to create noisy / chaotic sounds or modulation sources.

I first read about these in James Gleick's book *Chaos: Making a New Science* and was interested to see how they could be used in an audio context. 

The logistic map is mathematically expressed like this:

$x_{n+1} = r \cdot x_n \cdot (1 - x_n)$

This GIF shows the logistic map on an oscilloscope as the ``rate`` increases from about 1.0 to 4.0. It begins with stablity. As the rate increases, bifurcations begin - the output oscillating between two values, then four, then eight, and so on. As the rate reaches around 3.6, it transitions into chaos. Plotted differently, the map would look something like [this](https://en.wikipedia.org/wiki/Bifurcation_diagram#/media/File:Logistic_Map_Bifurcation_Diagram,_Matplotlib.svg). 

<img src="https://github.com/MattKuebrich/teensy-audio-objects/blob/main/chaosmaps/logisticmap.gif" alt="logistic map on a scope" width="350"/>

The n-fold map, more commonly referred to as a "doubling map", is expressed like this:

$f(x) = (n \cdot x) \bmod 1$

As the ``n`` suggests, you can use a multiplier other than 2. 






## Audio Connections

| Port  | Purpose |
| ----- | ------- |
| In 0  | Rate Modulation  |
| In 1  | Sampling Rate Modulation  |
| Out 0  | Map Output  |

## Functions

### **seed**(amount);
Set the seed amount, from 0.0 to 1.0. This should usually be set in setup() or intermittently. This is also commonly referred to as *population size* or ``x``.

### **rate**(amount);
Set the rate amount, from 1.0 to 4.0. For the logistic map, this is also commonly referred to as *growth rate* or ``r``.  

In the case of the n-fold map, this can be thought of as the *multiplier rate* or ``n``. For a classic "doubling map", use a rate of 2.0. 
Since an exact doubling map [will die off after a certain amount of iterations](https://trinket.io/python3/0d5bf1c579) (around 50?), I've set them to repeat again once they've reached 0.0 (died off). 

This can useful for create repeating sequences of values. Depending on how you have the samplingRate set, this can sound like an oscillator or be used a modulation source or a chaotic "sequencer", not unlike [Rob Hordijk's rungler in "loop mode"](https://web.archive.org/web/20150311234517/http://casperelectronics.com/rungle-mods/). For a new set of values, change the seed value. 

While using a doubling map, the initial (seed) value should be an irrational number (let's say 0.453) in order for the map to exhibit chaotic behavior. Using a rational number (say 0.2), will give periodic results.

### **samplingRate**(freq);
Set the sampling rate. This downsamples the output so it's usable in different contexts. At high sampling rates, the output resembles white noise, while at lower sampling rates, the output can be used as trigger or modulation source. By default, this is set to the Teensy's sampling rate using ``AUDIO_SAMPLE_RATE_EXACT``, usually 44100 Hz.

### **mode**(mode);

Supported modes:
* AudioSynthChaosMaps::LOGISTIC
* AudioSynthChaosMaps::NFOLD

## References

* [Geoff Boeing's very readable intro to logistic maps](https://geoffboeing.com/2015/03/chaos-theory-logistic-map/)

* [chaos theory and practice thread on the lines forum](https://llllllll.co/t/chaos-theory-and-practice/63010/6)

* [Very cool audiovisual demonstration of a logistic map on YouTube](https://www.youtube.com/watch?v=lK5oqf8ROCo)

* [logistic map](https://editor.p5js.org/mattkuebrich/sketches/X0YJukvoU) and [doubling map](https://editor.p5js.org/mattkuebrich/sketches/ZQL43UFdk) visualized in p5js

