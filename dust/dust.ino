/* Dust example

  This routes the dust to the output, with an LFO modulating the density amount.
  
  POT01 = Density amount
  POT02 = LFO frequency, density modulation
  POT03 = LFO amplitude, controls the amount of density modulation 

*/

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include "synth_dust.h"

#define POT01 14
#define POT02 15
#define POT03 16

// GUItool: begin automatically generated code
AudioSynthDust dust;            //xy=156.2222023010254,382.88888359069824
AudioOutputI2S           i2s1;           //xy=792.8889045715332,396.22222328186035
AudioSynthWaveformModulated lfo;      //xy=484.00001525878906,1270.0000491142273
AudioMixer4              mixer;         //xy=303,213
AudioConnection          patchCord0(lfo, 0, mixer, 0);
AudioConnection          patchCord1(mixer, 0, dust, 0);
AudioConnection          patchCord2(dust, 0, i2s1, 0);
AudioConnection          patchCord3(dust, 0, i2s1, 1);

//usb for testing
//AudioOutputUSB           usb_out;           //xy=792.8889045715332,396.22222328186035
//AudioConnection          patchCord4(dust, 0, usb_out, 0);
//AudioConnection          patchCord5(dust, 0, usb_out, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=1284,1411
// GUItool: end automatically generated code

void setup() {
  AudioNoInterrupts();
  AudioMemory(12);
  Serial.begin(9600);

  lfo.begin(0.5, 200, WAVEFORM_SINE);
  
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.3);

  dust.enableUnipolar(0); //default

  AudioInterrupts();
}

void loop() {
  dust.density(mapf(analogRead(POT01), 0, 1023, 0.0, 1.0)); // density amount
  lfo.frequency(mapf(analogRead(POT02), 0, 1023, 0, 10.0)); // LFO freq
  mixer.gain(0, mapf(analogRead(POT03), 0, 1023, 0.0, 1.0)); // LFO amp
}


// floating point map function taken from https://forum.arduino.cc/index.php?topic=361046.0
double mapf(double x, double in_min, double in_max, double out_min, double out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
