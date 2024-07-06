# Readout

This object simply reads an input and outputs the same signal back to the sketch as a -1.0 to 1.0 float. You check if data is available using available() and retreive the value using read(). It's very similar (and modified from) the [Peak](Peakhttps://www.pjrc.com/teensy/gui/?info=AudioAnalyzePeak) audio object, but outputs the values directly without finding the peak. 

This is useful for modulating values that you can only set from within the sketch, like the attack of the envelope object or, in the case of the example sketch, the frequency and noteOn() for the simpledrum object. 

In order to do the opposite of this and send a value from the sketch INTO the audio library, you'd want to use the existing [dc object](https://www.pjrc.com/teensy/gui/index.html?info=AudioSynthWaveformDc).
  
## Audio Connections

| Port  | Purpose |
| ----- | ------- |
| In 0  | Signal to readout |

## Functions

### **available**();
Returns true each time new data is available.

### **read**();
Returns the input back to the sketch as a -1.0 to 1.0 float.



