# STK Effect

This is a wrapper of all 8 [STK Effects](https://ccrma.stanford.edu/software/stk/classstk_1_1Effect.html) from [The Synthesis ToolKit in C++ (STK)](https://ccrma.stanford.edu/software/stk/) by Perry R. Cook & Gary P. Scavone. It includes:

* [Chorus](https://ccrma.stanford.edu/software/stk/classstk_1_1Chorus.html)
* [Echo](https://ccrma.stanford.edu/software/stk/classstk_1_1Echo.html)
* [JCRev](https://ccrma.stanford.edu/software/stk/classstk_1_1FreeVerb.html) - reverb developed by developed by John Chowning
* [NRev](https://ccrma.stanford.edu/software/stk/classstk_1_1NRev.html) - reverb by CCRMA
* [PRCRev](https://ccrma.stanford.edu/software/stk/classstk_1_1PRCRev.html) - reverb by Perry Cook
* [FreeVerb](https://ccrma.stanford.edu/software/stk/classstk_1_1FreeVerb.html) reverb by Jezar at Dreampoint
* [PitShift](https://ccrma.stanford.edu/software/stk/classstk_1_1PitShift.html) - simple pitch shifter
* [LentPitShift](https://ccrma.stanford.edu/software/stk/classstk_1_1LentPitShift.html) - pitch shifter based on the Lent algorith by Francois Germain

Instead of the original STK files, I'm using Phil Schatzmann's [The Synthesis ToolKit in C++ (STK) Library for Arduino](https://github.com/pschatzmann/arduino-stk) as the basis for this.

## FreeVerb again?
I know, a version of FreeVerb is already part of the Teensy Audio Library, although the STK version here differs in a few ways. It supports stereo input (and stereo output) and has the extra "width" and "freeze" functions. That said, unlike the Teensy version, it's unoptimized. On my Teensy 4.1, it uses 8.6% CPU vs 5.4% while using the stock (AudioEffectFreeverbStereo) effect.

## LentPitShift issue
LentPitShift doesn't work well and spikes the CPU near 100% on a Teensy 4.1. That said, it also doesn't run well using STK on my computer either. I'm keeping it here for completeness and in case anyone want to make it better. 

## Audio Connections

| Port  | Purpose |
| ----- | ------- |
| In 0  | Left / Mono Input  |
| In 1  | Right Input  |
| Out 0  | Left Output  |
| Out 1  | Right Output  |

Note: All the effects don't follow the same I/O scheme.

CHORUS = Stereo or mono in, stereo out.<br>
ECHO, PITSHIFT, LENTPITSHIFT = Mono in, mono (mirrored) out.<br>
JCREV, NREV, PRCREV = Mono in, stereo out.<br>
FREEVERB = Stereo or mono in, stereo out.

## Functions

Unlike most normal audio objects, this has specific functions to use based on which effect is chosen. For example, roomSize() won't do anything if you've got the PITSHIFT selected as the effect.

### **begin(effect)**;
Select which effect to use by name (see below). Since we don't want to take up memory loading ALL the effects, this setting can't be dynamically changed within the sketch and is recommended to be put in setup(). 

If you'd like to use multiple STK effects in a sketch, you can create more than one instance of the STK Effect audio object.

Effects: <br>
CHORUS<br>
ECHO<br>
JCREV<br>
NREV<br>
PRCREV<br>
FREEVERB<br>
PITSHIFT<br>
LENPITSHIFT<br>

### **mix**(level);
Set the mixture of input and "effected" levels in the output from 0.0 to 1.0. This applies to all effects.

### **clear**();
Reset and clear all internal states. This applies to all effects.

## Chorus 

### **modDepth**(amount);
Set modulation depth from 0.0 to 1.0.

### **modFrequency**(frequency);
Set modulation frequency in Hz.

## Echo 
Echo 

### **delay**(seconds);
Set the delay line length in seconds.

### **maxDelay**(seconds);
Set the maximum delay line length in seconds. This defaults to 1 second. When set to higher delays (2s) it gets crackly and above 3s doesn't seem to work.

## JCRev / NRev / PRCRev

### **decay**(seconds);
Set the reverberation decay time in seconds.


## FreeVerb

### **damping**(amount);
Set the damping parameter from 0.0 to 1.0.

### **roomSize**(amount);
Set the room size (comb filter feedback gain) parameter from 0.0 to 1.0.

### **width**(amount);
Set the width (left-right mixing) parameter from 0.0 to 1.0.

### **mode**(bool);
Set the mode, frozen = 1, unfrozen = 0.


## PitShift / LentPitShift

### **shift**(amount);
Set the pitch shift factor. Below 1.0 lowers the pitch, 1.0 produces no shift and above 1.0 increases the pitch.
If you have mix() enabled, this obviously works best at 100% wet.




