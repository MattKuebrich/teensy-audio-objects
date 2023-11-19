_STK Instrmnt and STK Effect are separate Teensy audio objects, they share files so it makes sense to package them together._

Jump to [STK Instrmnt](#stk-instrmnt)
Jump to [STK Effect](#stk-effect)


# [STK Instrmnt]

This is a wrapper of all 29 [STK Instruments](https://ccrma.stanford.edu/software/stk/classstk_1_1Instrmnt.html#details) from [The Synthesis ToolKit in C++ (STK)](https://ccrma.stanford.edu/software/stk/) by Perry R. Cook & Gary P. Scavone. It includes a variety of polyphonic physically modeled and FM instruments. Instead of the original STK files, I used Phil Schatzmann's [The Synthesis ToolKit in C++ (STK) Library for Arduino](https://github.com/pschatzmann/arduino-stk) (with minimal edits) as the basis for this.

I'm going to be a bit **verbose** below, mostly so I can remember how things work and choices that were made. This object isn't too hard to use and can be figured out by trying the example sketch. 

###  Consistency with Teensy
To be more consistent other Teensy Audio Objects, I decided to only focuses on the STK instruments. I haven't adapted the entire library (like Phil did), which require more setup and a working knowledge of the STK system. I did adapt the [STK Effects](https://github.com/MattKuebrich/teensy-audio-objects/tree/main/stkeffect) as a separate audio object.

### Value ranges
The original STK code work mostly with MIDI value ranges (0 - 127). To adhere to the [conventions](https://www.pjrc.com/teensy/td_libs_AudioNamingConvention.html) for Teensy Audio Objects, I've converted these ranges. For example, noteOn() expects a frequency in Hz and an amplitude from 0.0 to 1.0. If you're using usbMIDI or something that is sending MIDI, you'll need to convert back to MIDI note numbers / values. An example of this is in the .ino sketch included with this. 

###  Polyphony / Performance
In order to enable polyphony by default, I've used STK's [Voicer](https://ccrma.stanford.edu/software/stk/classstk_1_1Voicer.html) class within the audio object. Make sure to adjust the instrument level with volume() so clipping doesn't occur. These instruments can use hefty amounts of CPU, especially when using many polyphonic voices. 

### Extra Instruments
I've also included 5 instruments not originally part of the Instrmnt class in STK. KrstlChr, FrencHrn, and HnkyTonk are Yamaha TX81Z patches that were ported to ChucK by Perry Cook in "STK-style", so I've adapted those to work here as well. I also took a stab myself at porting the the classic "Lately Bass" patch from the TX81Z, but it needs some work. :/

Additionally, I included the [Guitar instrument from STK](https://ccrma.stanford.edu/software/stk/classstk_1_1Guitar.html), which according to the STK documentation "does not inherit from stk::Instrmnt because of API inconsistencies". To make polyphony work for Guitar, I created a modified version of Voicer, so this should work similar to the other instruments. The original Guitar STK class has the ability to specify a particular string number when calling its functions, but I didn't included that.

###  Trigger Input
As an alternative to calling noteOn() in your sketch, the instrument can be triggered from another object, such as an oscillator. When a signal goes from low to high on the trigger input, a noteOn() will be generated. When going from high to low, a noteOff() will be generated. The pitchBend() or frequency() functions can be used to change the pitch of the triggered notes.

###  Random Technical Notes 
* I tried using [STKFrames](https://ccrma.stanford.edu/software/stk/classstk_1_1StkFrames.html), which processes the audio in "frames" rather than per sample, but abandoned it as it didn't seem to improve performance. I DID use STKFrames for the STK Effect object, as it helped a great deal.

* The FM instruments were sounding "fizzy". I fixed this by turning off interpolation in FileLoop.cpp. 

## Possible TODO
* Adapt the Dymo UGen from ChucK in order to automatically prevent possible distortion when using multiple voices, as suggested by Perry Cook [on the Stk mailing list](https://cm-mail.stanford.edu/pipermail/stk/2015-August/001256.html). I used a hard limiter in the object to prevent nasty digital distortion, but this would be better. Another option is to use another Teensy audio object after the STK instrument, such as [MarkP's Dynamics Processor](https://github.com/MarkzP/AudioEffectDynamics).

* Create a general FM synth with all parameters adjustable via the sketch. Could possibly load TX81Z presets? Although the adapted presets present in STK seem to all require a certain amount of tweaking to sound similar to their TX81Z counterparts, at least in my experiments with comparing them via FM8. In ChucK, you can pass in FM parameters directly, so can (for example), [turn the HeavyMetl instrument into an FM trumpet](https://chuck.stanford.edu/doc/examples/stk/hevymetl-trumpet-algo3.ck) since they both use the same FM algorithm.

## Audio Connections

| Port  | Purpose |
| ----- | ------- |
| In 0  | Trigger Input  |
| Out 0  | Output  |

## Functions

### **begin(instrument, voices, decayTime (optional));
Select which instrument to use by name (see below) and the number of polyphonic voices, like so:
``StkInstrmnt.begin(FLUTE,3);``

Since we don't want to take up memory loading ALL the instruments, this setting can't be dynamically changed within the sketch and is recommended to be put in setup(). 

If you'd like to use multiple STK instruments in a sketch, you can use create more than one instance of the STK Instrmnt audio object.

The decayTime (in seconds) is optional and for some instruments (like Mandolin) it will let the instrument ring out for the decayTime. It abruptly cuts the note off after the decay, which isn't ideal, but seems to be how it works in STK. I'm not sure why some instruments work with this and others don't. For bell-type instruments you can just remove the noteOff() in your sketch and get them to ring out without setting this. 

Available instruments:

[BANDEDWG](https://ccrma.stanford.edu/software/stk/classstk_1_1BandedWG.html)<br>
[BEETHREE](https://ccrma.stanford.edu/software/stk/classstk_1_1BeeThree.html)<br>
[BLOWBOTL](https://ccrma.stanford.edu/software/stk/classstk_1_1BlowBotl.html)<br>
[BLOWHOLE](https://ccrma.stanford.edu/software/stk/classstk_1_1BlowHole.html)<br>
[BOWED](https://ccrma.stanford.edu/software/stk/classstk_1_1Bowed.html)<br>
[BRASS](https://ccrma.stanford.edu/software/stk/classstk_1_1Brass.html)<br>
[CLARINET](https://ccrma.stanford.edu/software/stk/classstk_1_1Clarinet.html)<br>
[DRUMMER](https://ccrma.stanford.edu/software/stk/classstk_1_1Drummer.html)<br>
[FLUTE](https://ccrma.stanford.edu/software/stk/classstk_1_1Flute.html) <br>
[FMVOICES](https://ccrma.stanford.edu/software/stk/classstk_1_1FMVoices.html)<br>
[HEVYMETL](https://ccrma.stanford.edu/software/stk/classstk_1_1HevyMetl.html)<br>
[MANDOLIN](https://ccrma.stanford.edu/software/stk/classstk_1_1Mandolin.html)<br>
[MESH2D](https://ccrma.stanford.edu/software/stk/classstk_1_1Mesh2D.html)<br>
[MODALBAR](https://ccrma.stanford.edu/software/stk/classstk_1_1ModalBar.html)<br>
[MOOG](https://ccrma.stanford.edu/software/stk/classstk_1_1Moog.html)<br>
[PERCFLUT](https://ccrma.stanford.edu/software/stk/classstk_1_1PercFlut.html)<br>
[PLUCKED](https://ccrma.stanford.edu/software/stk/classstk_1_1Plucked.html)<br>
[RECORDER](https://ccrma.stanford.edu/software/stk/classstk_1_1Recorder.html)<br>
[RESONATE](https://ccrma.stanford.edu/software/stk/classstk_1_1Resonate.html)<br>
[RHODEY](https://ccrma.stanford.edu/software/stk/classstk_1_1Rhodey.html)<br>
[SAXOFONY](https://ccrma.stanford.edu/software/stk/classstk_1_1Saxofony.html)<br>
[SHAKERS](https://ccrma.stanford.edu/software/stk/classstk_1_1Shakers.html)<br>
[SIMPLE](https://ccrma.stanford.edu/software/stk/classstk_1_1Simple.html)<br>
[SITAR](https://ccrma.stanford.edu/software/stk/classstk_1_1Sitar.html)<br>
[STIFKARP](https://ccrma.stanford.edu/software/stk/classstk_1_1StifKarp.html)<br>
[TUBEBELL](https://ccrma.stanford.edu/software/stk/classstk_1_1TubeBell.html)<br>
[VOICFORM](https://ccrma.stanford.edu/software/stk/classstk_1_1VoicForm.html)<br>
[WHISTLE](https://ccrma.stanford.edu/software/stk/classstk_1_1Whistle.html)<br>
[WURLEY](https://ccrma.stanford.edu/software/stk/classstk_1_1Wurley.html)<br>
[KRSTLCHR](https://chuck.stanford.edu/doc/reference/ugens-stk.html#KrstlChr)<br>
[FRENCHRN](https://chuck.stanford.edu/doc/reference/ugens-stk.html#FrencHrn)<br>
[HNKYTONK](https://chuck.stanford.edu/doc/reference/ugens-stk.html#HnkyTonk)<br>
LATELYB (Lately Bass patch from the Yamaha TX81Z)<br>
[GUITAR](https://ccrma.stanford.edu/software/stk/classstk_1_1Guitar.html)<br>

### **noteOn**(freq, amplitude);
Trigger the instrument with a frequency in Hz and an amplitude from 0.0 - 1.0.

### **noteOff**(freq, decay);
Stop playing the instrument with a frequency in Hz and the speed of decay from 0.0 - 1.0. (I've had limited success getting the decay to work).

### **frequency**(freq);
Set the frequency in hz. When this is set, it overrides the frequency value from noteOn().

### **pitchBend**(amount);
Set the amount of pitchbend from -1.0 to 1.0.

### **silence**();
Send a noteOff message to all existing voices. 

### **volume**(level);
Adjust the overall instrument volume from 0.0 to 1.0.

### **activeVoices**();
This will return the number of active polyphonic voices sounding.

### **controlChange**(num, val);
Each instrument has a unique set of parameters which can be set using a MIDI CC number and a 0.0 - 1.0 value. Refer to the STK documentation for each instrument above to find which CC numbers to use for which parameters. 

Note: The BandedWG and ModalBar instruments have internal presets which expect an integer (for example, 0 - 8), so you'd need to 


For example, the "Pluck Position" of the [Mandolin](https://ccrma.stanford.edu/software/stk/classstk_1_1Mandolin.html) corresponds to CC number 4, so would be set like so:
``
StkInstrmnt.controlChange(4, 0.5)
``

# [STK Effect]

This is a wrapper of all 8 [STK Effects](https://ccrma.stanford.edu/software/stk/classstk_1_1Effect.html) from [The Synthesis ToolKit in C++ (STK)](https://ccrma.stanford.edu/software/stk/) by Perry R. Cook & Gary P. Scavone. It includes chorus, echo, reverb and pitch shifting effects.

Instead of the original STK files, I'm using Phil Schatzmann's [The Synthesis ToolKit in C++ (STK) Library for Arduino](https://github.com/pschatzmann/arduino-stk) as the basis for this.

## FreeVerb again?
I know, a version of FreeVerb is already part of the Teensy Audio Library, although the STK version here differs in a few ways. It supports stereo input (and stereo output) and has the extra "width" and "freeze" functions. That said, unlike the Teensy version, it's unoptimized. On my Teensy 4.1, it uses 8.6% CPU vs 5.4% while using the stock (AudioEffectFreeverbStereo) effect.

## LentPitShift issue
LentPitShift doesn't work well and spikes the CPU near 100%. That said, it also doesn't run well using STK on my computer either. I'm keeping it here for completeness and in case anyone want to make it better. 

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
[CHORUS](https://ccrma.stanford.edu/software/stk/classstk_1_1Chorus.html)<br>
[ECHO](https://ccrma.stanford.edu/software/stk/classstk_1_1Echo.html)<br>
[FREEVERB](https://ccrma.stanford.edu/software/stk/classstk_1_1FreeVerb.html)<br>
[JCREV](https://ccrma.stanford.edu/software/stk/classstk_1_1JCRev.html)<br>
[LENPITSHIFT](https://ccrma.stanford.edu/software/stk/classstk_1_1LentPitShift.html)<br>
[NREV](https://ccrma.stanford.edu/software/stk/classstk_1_1NRev.html)<br>
[PRCREV](https://ccrma.stanford.edu/software/stk/classstk_1_1PRCRev.html)<br>
[PITSHIFT](https://ccrma.stanford.edu/software/stk/classstk_1_1PitShift.html)<br>

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











