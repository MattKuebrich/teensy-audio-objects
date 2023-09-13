/* DC Block example

  This is simply a saw oscillator going into the DC blocker. 
  You can apply an offset to the oscillator with POT03 and 
  see how the waveform reacts on a scope.
 
  POT01 = Oscillator frequency
  POT02 = Oscillator amplitude
  POT03 = Oscillator offset

  This was adapted from "Tim's Quicker DC Blocker" by Tim Wescott
  https://www.dsprelated.com/showthread/comp.dsp/172787-1.php
  https://www.dsprelated.com/showthread/comp.dsp/316993-2.php
  
*/

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

#include "filter_dcblock.h"

#define POT01 14
#define POT02 15
#define POT03 16

// GUItool: begin automatically generated code
AudioControlSGTL5000     sgtl5000_1;     //xy=1284,1411
AudioFilterDCBlock dcblock;            //xy=156.2222023010254,382.88888359069824
AudioOutputI2S           i2s1;           //xy=792.8889045715332,396.22222328186035
AudioSynthWaveformModulated osc;      //xy=484.00001525878906,1270.
AudioConnection          patchCord1(osc, 0, dcblock, 0);
AudioConnection          patchCord2(dcblock, 0, i2s1, 0);
AudioConnection          patchCord3(dcblock, 0, i2s1, 1);

//USB for testing
//AudioOutputUSB           usb_out;           //xy=792.8889045715332,396.22222328186035
//AudioConnection          patchCord5(dcblock, 0, usb_out, 0);
//AudioConnection          patchCord6(osc, 0, usb_out, 1);
// GUItool: end automatically generated code

void setup() {
  AudioNoInterrupts();
  AudioMemory(20);
  Serial.begin(9600);
  osc.begin(0.5, 100, WAVEFORM_SAWTOOTH); 
  dcblock.frequency(30); // default, works well
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.4);
  AudioInterrupts();
}

void loop() {
  osc.frequency(mapf(analogRead(POT01), 0, 1023, 0.0, 100));
  osc.amplitude(mapf(analogRead(POT02), 0, 1023, 0.0, 1.0));
  osc.offset(mapf(analogRead(POT03), 0, 1023, -1.0, 1.0)); // add some dc offset in
}

// floating point map function taken from https://forum.arduino.cc/index.php?topic=361046.0
double mapf(double x, double in_min, double in_max, double out_min, double out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
