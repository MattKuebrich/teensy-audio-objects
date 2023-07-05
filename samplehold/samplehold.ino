/* Sample and hold example

This is a classic sci-fi sound made by sampling white noise at a steady rate and using that
to modulate another oscillator's frequency. 

POT01 = Amplitude of noise that's being sampled (acts like a range control the random tones).
POT02 = Pulse (clock) frequency that's doing the "holding".
POT03 = Sine wave base frequency (that is being modulated by the S&H)

*/

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

#include "effect_samplehold.h"

// GUItool: begin automatically generated code
AudioSynthWaveformModulated pulse;   //xy=319.6666488647461,560.3333024978638
AudioSynthWaveformModulated osc;   //xy=319.6666488647461,560.3333024978638
AudioSynthNoiseWhite     noise1;
AudioOutputI2S           i2s1;           //xy=968.4286117553711,308.42860221862793
AudioEffectSampleAndHold sh;       //xy=573.6666564941406,523.6666564941406
AudioConnection          patchCord1(noise1, 0, sh, 0); //to sample
AudioConnection          patchCord2(pulse, 0, sh, 1); //pulse
AudioConnection          patchCord3(sh, osc); // s&h modulates another wave
AudioConnection          patchCord4(osc, 0, i2s1, 0);
AudioConnection          patchCord5(osc, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=981.7143249511719,255.00000858306885
// GUItool: end automatically generated code

#define POT01 14
#define POT02 15
#define POT03 16

float pulseFreq;
float oscFreq;
float noiseAmp;

void setup() {
  AudioMemory(12);

  sgtl5000_1.enable();
  sgtl5000_1.volume(.5);
  
  noise1.amplitude(.5);
  pulse.begin(1.0, 100, WAVEFORM_PULSE);
  osc.begin(1.0, 100, WAVEFORM_SINE);
  osc.frequencyModulation(7); 
}

void loop() {
  
  noiseAmp  = mapf(analogRead(POT01), 0, 1023, 0.0, 1.0); 
  pulseFreq  = mapf(analogRead(POT02), 0, 1023, 0.0, 30.0);
  oscFreq  = mapf(analogRead(POT03), 0, 1023, 0.0, 500.0); 

  noise1.amplitude(noiseAmp); // noise to sample
  pulse.frequency(pulseFreq); //pulse as clock
  osc.frequency(oscFreq); //sine to modulate
}

// floating point map function taken from https://forum.arduino.cc/index.php?topic=361046.0
double mapf(double x, double in_min, double in_max, double out_min, double out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
