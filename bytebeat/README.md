# Bytebeat

Bytebeats are pieces of glitchy lo-fi music created by defining a waveform as a function of time using a single-line formula.[This beginner's guide from Tuesday Night Machines](https://nightmachines.tv/downloads/Bytebeats_Beginners_Guide_TTNM_v1-5.pdf) is a great introduction and [Bytebeat Composer](https://dollchan.net/bytebeat) is an easy way to experiment with bytebeats in your browser. 

The parameters p1, p2 and p3 can be used in the bytebeat formula and set inside your sketch. You could (as in the example sketch) control p1, p2 and p3 with potentiometers. The variable w can also be used within the formula and represented the previous bytebeat output. This can be used to create recursive formulas. This object only uses the classic "C-compatible" flavor of bytebeat equations. Equations written in Javascript won't work.

I've written 3 sketches to demonstrate how to use this by bytebeat audio object.

[bytebeat_simple](https://github.com/MattKuebrich/teensy-audio-objects/tree/main/bytebeat/bytebeat_simple)
Simply plays a single bytebeat.

[bytebeat_5formula](https://github.com/MattKuebrich/teensy-audio-objects/tree/main/bytebeat/bytebeat_5formula)
Generates bytebeats with 5 selectable formulas, sample rate, parameters, reset and reverse functions.

[bytebeat_equationcomposer]([bytebeat_5formula](https://github.com/MattKuebrich/teensy-audio-objects/tree/main/bytebeat/bytebeat_equationcomposer)
Includes all four bytebeat equation banks from the Equation Composer Eurorack module by Microbe Modular (with permission from creator Bret Truchan). 

## Audio Connections

| Port  | Purpose |
| ----- | ------- |
| Out 0  | Bytebeat Output  |


## Functions
### **formula**(function);
Set the bytebeat formula. This should be a function in your sketch that that returns the bytebeat formula. For example:
``uint32_t myformula(uint32_t t, uint8_t w, uint32_t p1, uint32_t p2, uint32_t p3) { return (sin(t) * 1e7 & 255); }``       

### **sampleRate**(freq);
Set the sample rate (pitch) of the bytebeat equation. Some equations you find on the web will require a specific sample rate to sound "correct". The default sample rate is 8000.

### **parameter1**(amount);
Set the ``p1`` variable in the bytebeat.

### **parameter2**(amount);
Set the ``p2`` variable in the bytebeat.

### **parameter3**(amount);
Set the ``p3`` variable in the bytebeat.

### **reverse**(bool);
When true, this plays the bytebeat in reverse.

### **reset**();
Resets the bytebeat (sets the time back to 0).







