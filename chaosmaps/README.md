# Chaos Maps

This object implements two classic chaotic maps, a logistic map and an n-fold map.

The logistic map  is expressed like this:

$x_{n+1} = r \cdot x_n \cdot (1 - x_n)$


The n-fold map, more commonly referred to as a "doubling map", is expressed like this:

$f(x) = N \cdot x$

As the ``n`` suggests, you can use a multiplier other than 2.

## Audio Connections

| Port  | Purpose |
| ----- | ------- |
| In 0  | Rate Modulation  |
| In 1  | Sampling Rate Modulation  |
| Out 0  | Map Output  |


## Functions

### **seed**(amount);
Set the seed amount, from 0.0 to 1.0. This should usually be set in setup() or intermittently.
This is also commonly referred to as *population size* or ``x``.

### **rate**(amount);
Set the rate amount, from 1.0 to 4.0. This is also commonly referred to as *growth rate* or ``r``.

### **samplingRate**(freq);
Set the sampling rate. At high sampling rates, the output resembles white noise, while at lower sampling rates, the output can be used as trigger or modulation source. By default, this is set to the Teensy's sampling rate using ``AUDIO_SAMPLE_RATE_EXACT``.

### **mode**(mode);

Supported modes:
* AudioSynthChaosMaps::LOGISTIC
* AudioSynthChaosMaps::NFOLD

