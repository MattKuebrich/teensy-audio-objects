# Function Shaper

This object modifies the waveshape of an input signal to generate distortion, clipping, bitcrushing, fuzz, and other gnarly effects. You pass it a waveshaping function directly, unlike existing [waveshaper](https://www.pjrc.com/teensy/gui/?info=AudioEffectWaveshaper) Teensy object, which uses lookup tables. Many formulas can be found on the web (on sites such as [musicdsp.org](https://www.musicdsp.org/)) and easily implemented. The example sketch contains 20 of them. 

When writing the shaper function, the variable ``x `` represents the input. 

Parameters (or coefficients) ``a``, ``b`` and ``c`` can be used in the shaper function and set inside your sketch. For example, you could set up potentiometers to adjust these parameters. 

The variable ``r`` can also be used within the function and represents the previous shaped output. This can be used to create recursive functions. This output is taken before the makeup gain is applied.

A few extra notes: The existing Teensy [waveshaper](https://www.pjrc.com/teensy/gui/?info=AudioEffectWaveshaper) will use less CPU than this object, as using lookup tables with interpolation is more efficient. On the Teensy 4.1, Function Shaper formulas use around 0.5% - 2% CPU, while the waveshaper object seems to use around 0.3%. 

There is no oversampling with this object. I experimented with a few ways of implementing it and couldn't really hear a difference, although I could have been doing it wrong. :shrug:

## Audio Connections

| Port  | Purpose |
| ----- | ------- |
| In 0  | Signal Input |
| Out 0  | Shaped Output  |


## Functions
### **functionShaper**(function);
This should be a function in your sketch which returns the waveshaper, er function.

```
float tanhClipping(float x, float r, float a, float b, float c) {
  //hyperbolic tangent soft clipping
  return fastTanh(x);
} 
```

Then set it like this: 
``shaper.functionShaper(tanhClipping);``

### **inputGain**(level);
Set the input gain going into the function shaper. It's important to have a good amount of gain added to the signal before being waveshaped. In the example sketch I have this set from a range of 1.0 (unity gain) to 20.0. 

### **makeupGain**(level);
Makeup gain is used to adjust the overall signal level after the waveshaping as taken place, since often the distorted signal is too quiet or too loud. In the example sketch I have this set to a range of 0.0 to 1.0.

### **parameterA**(amount);
Set the ``a`` parameter in the shaper.

### **parameterB**(amount);
Set the ``b`` parameter in the shaper.

### **parameterC**(amount);
Set the ``c`` parameters in the shaper.

### **mix**(level);
Sets the mix between the input signal (dry) and the waveshaped signal (wet). 0.0 is 100% dry and 1.0 is 100% wet. Default is 1.0. 

### **offset**(level);
This applies a DC offset from -1.0 to 1.0 to the signal, after the input gain as been applied. It can change the character of waveshaper. Default is 0.0.

### **enableLimiter**(bool);
When true, this enables the internal limiter which helps avoid nasty digital distortion. This defaults to enabled, with a threshold of 1.0. 

### **limiterThreshold**(float);
Set the limiter threshold. The default is 1.0.




