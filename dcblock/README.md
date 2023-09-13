# DC Block

A DC blocker is a recursive one-pole highpass filter that removes DC offset often introduced by digital audio processes. By using a sub-audio cutoff frequency, it centers the waveform while preserving audible content.

This code was adapted from "Tim's Quicker DC Blocker" by Tim Wescott. I can't find where the code originated but it's been reposted [here](https://www.dsprelated.com/showthread/comp.dsp/172787-1.php) by Robert Bristow-Johnson, about halfway down the page. 

## Audio Connections

| Port  | Purpose |
| ----- | ------- |
| In 0  | Signal Input   |
| Out 0  | Filtered Output  |

## Functions
### **frequency**(freq);
Set the cutoff frequency for the DC filter in Hz. The default is 30Hz. 

When reading about DC blockers, you might see this setting expressed this as a "pole" or "scale" number. A pole of 0.995 corresponds to the 30Hz default. Another commonly used value is 0.999 (or 7Hz).
