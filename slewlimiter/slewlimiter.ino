/* Slew limiter example

This uses the slew limiter as a way to add portamento. As the rise and fall times are turned up, the notes begin to glide between each other.

POT01 = Triangle oscillator frequency
POT02 = Sample and hold oscillator frequency
POT03 = Slew limiter rise time
POT04 = Slew limiter fall time

*/

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

#include "effect_slewlimiter.h"

#define POT01 14
#define POT02 15
#define POT03 16
#define POT04 17

float oscFreq, shFreq, riseTime, fallTime;

// GUItool: begin automatically generated code
AudioSynthWaveformModulated osc;   //xy=319.6666488647461,560.3333024978638
AudioSynthWaveformModulated sh;   //xy=319.6666488647461,560.3333024978638
AudioEffectSlewLimiter slewLimiter;            //xy=156.2222023010254,382.88888359069824
AudioOutputI2S           i2s1;           //xy=792.8889045715332,396.22222328186035
AudioConnection          patchCord1(sh, 0, slewLimiter, 0);
AudioConnection          patchCord2(slewLimiter, 0, osc, 0);
AudioConnection          patchCord3(osc, 0, i2s1, 0);
AudioConnection          patchCord4(osc, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=1284,1411
// GUItool: end automatically generated code

void setup() {
  AudioMemory(12);

  sgtl5000_1.enable();
  sgtl5000_1.volume(0.5);

  osc.begin(1.0, 100, WAVEFORM_TRIANGLE);
  sh.begin(0.2, 100, WAVEFORM_SAMPLE_HOLD);
}

void loop() {
  oscFreq  = mapf(analogRead(POT01), 0, 1023, 0.0, 512.0);
  shFreq   = mapf(analogRead(POT02), 0, 1023, 0.0, 20.0);
  riseTime = mapf(analogRead(POT03), 0, 1023, 0.0, 1.0);
  fallTime = mapf(analogRead(POT04), 0, 1023, 0.0, 1.0);

  osc.frequency(oscFreq);
  sh.frequency(shFreq);
  slewLimiter.rise(riseTime);
  slewLimiter.fall(fallTime);
}


// floating point map function taken from https://forum.arduino.cc/index.php?topic=361046.0
double mapf(double x, double in_min, double in_max, double out_min, double out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
