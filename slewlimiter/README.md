# Slew Limiter

A slew limiter smoothes out an incoming signal, limiting the rate at which it can change over time. 

This object is based on [Ivan Cohen's simplified version of the Befaco Slew Limiter VCV Rack module](https://forum.juce.com/t/adc17-fifty-shades-of-distortion-homework-part-2/25174). 

## Audio Connections

| Port  | Purpose |
| ----- | ------- |
| In 0  | Signal Input  |
| Out 0  | Slewed Output  |

## Functions
### **rise**(amount);
Set the rise time, from 0.0 to 1.0.

### **fall**(amount);
Set the fall time, from 0.0 to 1.0.

