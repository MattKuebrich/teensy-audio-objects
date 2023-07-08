/* Bernoulli Gate example

Based on a random process and the probability set, the clock triggers either drum1 (left channel) or drum2 (right channel). 
The peak object is used as a hacky way to trigger the drums.

POT01 = Clock frequency
POT02 = Bernoulli gate probability

*/

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

#include "effect_bernoulligate.h"

// GUItool: begin automatically generated code
AudioSynthWaveformModulated lfo;            //xy=128.42859649658203,283.4285891056061
AudioSynthSimpleDrum drum1;           //xy=598.428596496582,297.4285891056061
AudioSynthSimpleDrum drum2;           //xy=598.428596496582,297.4285891056061
AudioAnalyzePeak peak1;
AudioAnalyzePeak peak2;
AudioEffectBernoulliGate         bgate;         //xy=421.57152557373047,549.8571300506592
AudioOutputUSB           usb1;           //xy=786.2381210327148,602.0951766967773
AudioOutputI2S           i2s1;           //xy=968.4286117553711,308.42860221862793
AudioConnection          patchCord1(lfo, bgate);
AudioConnection          patchCord2(bgate, 0, peak1, 0);
AudioConnection          patchCord3(bgate, 1, peak2, 0);
AudioConnection          patchCord4(drum1, 0, i2s1, 0);
AudioConnection          patchCord5(drum2, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=981.7143249511719,255.00000858306885
// GUItool: end automatically generated code

#define POT01 14
#define POT02 15

float peakRead1 = 0.0;
float peakRead2 = 0.0;

float peakRead1Prev = 0.0;
float peakRead2Prev = 0.0;

void setup() {
  AudioNoInterrupts();
  AudioMemory(12);

  drum1.frequency(400);
  drum1.length(150);
  drum1.secondMix(0.5);
  drum1.pitchMod(1.0);

  drum2.frequency(60);
  drum2.length(100);
  drum2.secondMix(0.0);
  drum2.pitchMod(2.0);

  lfo.begin(1.0, 10, WAVEFORM_PULSE);
  bgate.probability(0.5);

  sgtl5000_1.enable();
  sgtl5000_1.volume(0.5);
  AudioInterrupts();
}

void loop() {

  //set clock into bernoulli gate
  lfo.frequency(mapf(analogRead(POT01), 0, 1023, 0.0, 10.0));

  //set probability of bernoulli gate
  bgate.probability(mapf(analogRead(POT02), 0, 1023, 0.0, 1.0));


  //trigger drum1 on a high pulse
  if (peak1.available()) {
    peakRead1 = peak1.read();
  }

  if ((peakRead1 >= 1) && (peakRead1 != peakRead1Prev)) {
    drum1.noteOn();
  }

  peakRead1Prev = peakRead1;


  //trigger drum2 on a high pulse
  if (peak2.available()) {
    peakRead2 = peak2.read();
  }

  if ((peakRead2 >= 1) && (peakRead2 != peakRead2Prev)) {
    drum2.noteOn();
  }

  peakRead2Prev = peakRead2;

}


// floating point map function taken from https://forum.arduino.cc/index.php?topic=361046.0
double mapf(double x, double in_min, double in_max, double out_min, double out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
