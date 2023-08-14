/* Readout example, added available

   This object simply reads an input and outputs the same signal back to the sketch as a (-1.0 to 1.0) float.
   You check if data is available using available() and retreive the value using read(). It's very similar 
   (and modified from) the Peak audio object. This is useful for modulating values that you can only set from 
   within the sketch, like the attack of the envelope object or, in the case of this sketch, the frequency 
   and noteOn() for the simpledrum object. 

   POT01 = This controls a sawtooth oscillator that "modulates" the frequency of the simpledrum. 
   POT02 = This controls a square oscillator that triggers the simpledrum.

*/

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include "analyze_readout.h"

// GUItool: begin automatically generated code
AudioOutputI2S           i2s1;           //xy=792.8889045715332,396.22222328186035
AudioSynthSimpleDrum drum1;           //xy=598.428596496582,297.4285891056061
AudioSynthWaveformModulated osc1;
AudioSynthWaveformModulated osc2;
AudioAnalyzeReadout readoutTrig;
AudioAnalyzeReadout readoutDrumFreq;
AudioConnection          patchCord1(osc1, 0, readoutDrumFreq, 0);
AudioConnection          patchCord2(osc2, 0, readoutTrig, 0);
AudioConnection          patchCord3(drum1, 0, i2s1, 0);
AudioConnection          patchCord4(drum1, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=1284,1411
// GUItool: end automatically generated code

#define POT01 14
#define POT02 15

float readout1 = 0.0;
float readout2 = 0.0;
float readout2Prev = 0.0;

void setup() {
  AudioNoInterrupts();
  AudioMemory(12);

  drum1.frequency(60);
  drum1.length(100);
  drum1.secondMix(0.0);
  drum1.pitchMod(2.0);

  sgtl5000_1.enable();
  sgtl5000_1.volume(.5);

  osc1.begin(1.0, 10, WAVEFORM_SAWTOOTH);
  osc2.begin(1.0, 10, WAVEFORM_SQUARE);

  AudioInterrupts();
}

void loop() {

  // Modulate drum freq by osc1
  osc1.frequency(mapf(analogRead(POT01), 0, 1023, 0.0, 20.0));

    if (readoutDrumFreq.available()) {
  readout1 = readoutDrumFreq.read();
    Serial.println(readout1);
  }
  
  // Trigger drum based on osc2
  osc2.frequency(mapf(analogRead(POT02), 0, 1023, 0.0, 20.0));
    if (readoutTrig.available()) {
  readout2 = readoutTrig.read();
    }

  if ((readout2 >= 1) && (readout2 != readout2Prev)) {
    drum1.frequency(200 * (readout1 + 1.0)); // modulates centered around 200hz, from 0 and 400hz
    drum1.noteOn();
  }
  readout2Prev = readout2;
}


// floating point map function taken from https://forum.arduino.cc/index.php?topic=361046.0
double mapf(double x, double in_min, double in_max, double out_min, double out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
