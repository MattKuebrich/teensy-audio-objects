/* Gate to Trigger example

  In this sketch a square wave LFO (our gate) is converted to a trigger, which plays a drum (through a hacky use of the Peak object).
  If you change the edge parameter to BOTH, you'll hear the drum going twice as fast, as it is being triggered on the
  rising and falling edges.

  POT01 = LFO freq

*/

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

#include "effect_gatetotrigger.h"

// GUItool: begin automatically generated code
AudioEffectGateToTrigger gatetrigger;            //xy=156.2222023010254,382.88888359069824
AudioOutputI2S           i2s1;           //xy=792.8889045715332,396.22222328186035
AudioSynthSimpleDrum drum1;           //xy=598.428596496582,297.4285891056061
AudioSynthWaveformModulated osc;
AudioAnalyzePeak peak1;
AudioConnection          patchCord1(osc, 0, gatetrigger, 0);
AudioConnection          patchCord2(gatetrigger, 0, peak1, 0);
AudioConnection          patchCord3(drum1, 0, i2s1, 0);
AudioConnection          patchCord4(drum1, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=1284,1411

//USB for testing
//AudioOutputUSB           usb1;           //xy=786.2381210327148,602.0951766967773
//AudioConnection          patchCord5(osc, 0, usb1, 0);
//AudioConnection          patchCord6(gatetrigger, 0, usb1, 1);


// GUItool: end automatically generated code

#define POT01 14
#define POT02 15
#define POT03 16
#define POT04 17

float peakRead1 = 0.0;
float peakRead1Prev = 0.0;

void setup() {
  AudioNoInterrupts();
  AudioMemory(12);

  drum1.frequency(60);
  drum1.length(100);
  drum1.secondMix(0.0);
  drum1.pitchMod(2.0);

  sgtl5000_1.enable();
  sgtl5000_1.volume(.5);

  osc.begin(1.0, 10, WAVEFORM_SQUARE);
  gatetrigger.duration(1); //1ms
  gatetrigger.edge(AudioEffectGateToTrigger::BOTH); //START, END, BOTH

  AudioInterrupts();
}

void loop() {
  
  osc.frequency(mapf(analogRead(POT01), 0, 1023, 0.0, 20.0));

  //trigger drum1
  if (peak1.available()) {
    peakRead1 = peak1.read();
  }

  if ((peakRead1 >= 1) && (peakRead1 != peakRead1Prev)) {
    drum1.noteOn();
  }

  peakRead1Prev = peakRead1;
}


// floating point map function taken from https://forum.arduino.cc/index.php?topic=361046.0
double mapf(double x, double in_min, double in_max, double out_min, double out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
