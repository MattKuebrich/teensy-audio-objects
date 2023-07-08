/* Ring Modulator example

Two sine waves being ring modulated.

POT01 = Carrier frequency
POT02 = Modulator frequency

*/

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

#include "effect_ringmodulator.h"

// GUItool: begin automatically generated code
AudioSynthWaveformModulated carrier;            //xy=128.42859649658203,283.4285891056061
AudioSynthWaveformModulated modulator;           //xy=598.428596496582,297.4285891056061
AudioEffectRingModulator ringModulator;         //xy=421.57152557373047,549.8571300506592
AudioOutputI2S           i2s1;           //xy=968.4286117553711,308.42860221862793
AudioConnection          patchCord7(modulator, 0, ringModulator, 0);
AudioConnection          patchCord8(carrier, 0, ringModulator, 1);
AudioConnection          patchCord9(ringModulator, 0, i2s1, 0);
AudioConnection          patchCord10(ringModulator, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=981.7143249511719,255.00000858306885
// GUItool: end automatically generated code

#define POT01 14
#define POT02 15

void setup() {
  AudioMemory(12);

  sgtl5000_1.enable();
  sgtl5000_1.volume(.5);

  carrier.begin(1.0, 100, WAVEFORM_SINE);
  modulator.begin(1.0, 100, WAVEFORM_SINE);
}

void loop() {

  carrier.frequency(mapf(analogRead(POT01), 0, 1023, 0.0, 1000));
  modulator.frequency(mapf(analogRead(POT02), 0, 1023, 0.0, 1000));

}


// floating point map function taken from https://forum.arduino.cc/index.php?topic=361046.0
double mapf(double x, double in_min, double in_max, double out_min, double out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
