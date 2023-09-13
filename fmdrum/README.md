# FM Drum

This is a modified version of [mxmxmx's Teensy port](https://github.com/mxmxmx/minitrash/blob/master/soft/libraries/Audio/synth_fm_drum.cpp) of the FM Drum mode from the Mutable Instruments Peaks Eurorack module.

### Updates:
* The drum can be triggered with ``noteOn()`` or with a trigger at the first input. 
* The functions have been updated to take more typical value ranges for the Teensy Audio Library.
* On the Peaks module, noise and overdrive were combined in one knob. I've separated them so they can be set independently.

Note: This is pretty similar to the [SimpleDrum](https://www.pjrc.com/teensy/gui/?info=AudioSynthSimpleDrum) object that exists in the Teensy Audio Library already, although FM Drum has some different options and can get gnarlier, in a good way. :)

## Audio Connections

| Port  | Purpose |
| ----- | ------- |
| In 0  | Trigger Input  |
| Out 0  | FM Drum Output  |

## Functions

### **noteOn()**;
Trigger the drum.

### **frequency**(freq);
Set the base frequency in Hz. Default is 50 Hz.

### **fm**(amount);
Set the fm intensity, from 0 to 1.0. Default is 0.

### **decay**(amount);
Set the FM and AM envelope decay time, from 0 to 1.0.  Default is 0.75.

### **noise**(amount);
Set the noise amount, from 0 to 1.0. Default is 0.

### **overdrive**(amount);
Set the noise amount, from 0 to 1.0. Default is 0.
