/* Quantizer example

   This quantizer is based on Jeremy Wentworth's VCV Rack Quantizer. 
   The user defines scales within the sketch.

   POT01 = Frequency of the triangle LFO to quantize.
   POT02 = Frequency of another triangle osc which the LFO is modulating. Pot all the way down is middle C.
   POT03 = Controls the "range" of pitches
   POT04 = Select the scale
   POT05 = Set the octave shift (currently disabled)

*/


#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <ResponsiveAnalogRead.h>

#include "effect_quantizer.h"

float scales[17][13] = {
   {0, 2, 3, 5, 7, 8, 10, 12},                 // AEOLIAN     
   {0, 3, 5, 6, 7, 10, 12},                    // BLUES             
   {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}, // CHROMATIC
   {0, 2, 3, 5, 7, 8, 10, 12},                 // DIATONIC_MINOR
   {0, 2, 3, 5, 7, 9, 10, 12},                 // DORIAN
   {0, 2, 3, 5, 7, 8, 11, 12},                 // HARMONIC_MINOR
   {0, 1, 1, 4, 5, 8, 10, 12},                 // INDIAN
   {0, 1, 3, 5, 6, 8, 10, 12},                 // LOCRIAN
   {0, 2, 4, 6, 7, 9, 11, 12},                 // LYDIAN
   {0, 2, 4, 5, 7, 9, 11, 12},                 // MAJOR
   {0, 2, 3, 5, 7, 8, 9, 10, 11, 12},          // MELODIC_MINOR
   {0, 2, 3, 5, 7, 8, 10, 12},                 // MINOR
   {0, 2, 4, 5, 7, 9, 10, 12},                 // MIXOLYDIAN
   {0, 2, 3, 5, 7, 8, 10, 12},                 // NATURAL_MINOR
   {0, 2, 4, 7, 9, 12},                        // PENTATONIC
   {0, 1, 3, 5, 7, 8, 10, 12},                 // PHRYGIAN
   {0, 1, 3, 5, 7, 10, 11, 12}                 // TURKISH
};

// GUItool: begin automatically generated code
AudioSynthWaveformDc     dc;             //xy=149.11111450195312,320.2222423553467
AudioSynthWaveformModulated tri;            //xy=156.2222023010254,382.88888359069824
AudioAmplifier           amp1;           //xy=307.8888359069824,381.4444065093994
AudioEffectQuantizer     quantizer;      //xy=464.11106872558594,383.2221555709839
AudioSynthWaveformModulated tri2;           //xy=626.1110610961914,396.99999618530273
AudioOutputI2S           i2s1;           //xy=792.8889045715332,396.22222328186035
AudioEffectDelay         delay1;         //xy=2535.9999999999995,1787.9999999999995
AudioConnection          patchCord1(tri, amp1);
AudioConnection          patchCord2(amp1, quantizer);
AudioConnection          patchCord3(quantizer, 0, tri2, 0);
AudioConnection          patchCord4(tri2, 0, i2s1, 0);
AudioConnection          patchCord5(tri2, 0, i2s1, 1);

AudioControlSGTL5000     sgtl5000_1;     //xy=1284,1411
// GUItool: end automatically generated code


#define POT01 14
#define POT02 15
#define POT03 16
#define POT04 17
#define POT05 22

int scaleIndex = 0;
int noteCount = 0;
String scaleName;
ResponsiveAnalogRead pot01(POT01, true);
ResponsiveAnalogRead pot02(POT02, true);
ResponsiveAnalogRead pot03(POT03, true);
ResponsiveAnalogRead pot04(POT04, true);
ResponsiveAnalogRead pot05(POT05, true);

void setup() {
  AudioNoInterrupts();
  AudioMemory(12);

  //tri.begin(1.0, 10, WAVEFORM_SAMPLE_HOLD);
  tri.begin(1.0, 10, WAVEFORM_TRIANGLE);

  //tri.begin(0.5, 10, WAVEFORM_TRIANGLE);
  //tri.offset(0.5);

  tri2.begin(1.0, 261.63, WAVEFORM_TRIANGLE);
  tri.frequencyModulation(10);
  tri2.frequencyModulation(10);

  quantizer.octave(0);
  quantizer.scale(scales[0],8);

  sgtl5000_1.enable();
  sgtl5000_1.volume(.5);

  AudioInterrupts();
}

void loop() {

  pot01.update();
  pot02.update();
  pot03.update();
  pot04.update();
  pot05.update();

  int scale_sel = map(pot04.getValue(), 0, 1023, 0, 16);

  switch (scale_sel) {
    case 0:
      scaleIndex = 0;
      scaleName = "AEOLIAN";
      noteCount = 8;
      break;
    case 1:
      scaleIndex = 1;
      scaleName = "BLUES";
      noteCount = 7;
      break;
    case 2:
      scaleIndex = 2;
      scaleName = "CHROMATIC";
      noteCount = 13;
      break;
    case 3:
      scaleIndex = 3;
      scaleName = "DIATONIC_MINOR";
      noteCount = 8;
      break;
    case 4:
      scaleIndex = 4;
      scaleName = "DORIAN";
      noteCount = 8;
      break;
    case 5:
      scaleIndex = 5;
      scaleName = "HARMONIC_MINOR";
      noteCount = 8;
      break;
    case 6:
      scaleIndex = 6;
      scaleName = "INDIAN";
      noteCount = 8;
      break;
    case 7:
      scaleIndex = 7;
      scaleName = "LOCRIAN";
      noteCount = 8;
      break;
    case 8:
      scaleIndex = 8;
      scaleName = "LYDIAN";
      noteCount = 8;
      break;
    case 9:
      scaleIndex = 9;
      scaleName = "MAJOR";
      noteCount = 8;
      break;
    case 10:
      scaleIndex = 10;
      scaleName = "MELODIC_MINOR";
      noteCount = 8;
      break;
    case 11:
      scaleIndex = 11;
      scaleName = "MINOR";
      noteCount = 8;
      break;
    case 12:
      scaleIndex = 12;
      scaleName = "MIXOLYDIAN";
      noteCount = 8;
      break;
     case 13:
      scaleIndex = 13;
      scaleName = "NATURAL_MINOR";
      noteCount = 8;
      break;
     case 14:
      scaleIndex = 14;
      scaleName = "PENTATONIC";
      noteCount = 6;
      break;
     case 15:
      scaleIndex = 15;
      scaleName = "PHRYGIAN";
      noteCount = 8;
      break;
     case 16:
      scaleIndex = 16;
      scaleName = "TURKISH";
      noteCount = 8;
      break; 
  }

  // Display scale in serial monitor
  Serial.println(scaleName);

  tri.frequency(mapf(pot01.getValue(), 0, 1023, 0.0, 0.5)); // The frequency of the triangle LFO to quantize.
  tri2.frequency(mapf(pot02.getValue(), 0, 1023, 261.626, 1024)); // The LFO is frequency modulating this triangle osc. Pot all the way down is middle C.

  amp1.gain(mapf(pot03.getValue(), 0, 1023, 0.0, 0.25)); // Controls the "range" of pitches
  // I was having trouble with this being noisy when changing pitches, so I'm using ResponsiveAnalogRead and that fixed it.
  // I believe this thread is addressing the same issue and I tried the AudioSmoothAmplifier.h object there and it also fixed the issue
  // https://forum.pjrc.com/threads/67007-Mixer-and-Amp-gain-really-noisy?highlight=potentiometer+smoothing

  quantizer.scale(scales[scaleIndex], noteCount);
  //quantizer.octave(map(pot05.getValue(), 0, 1023, -2, 2)); // Shift octaves. Can go negative.

}


// floating point map function taken from https://forum.arduino.cc/index.php?topic=361046.0
double mapf(double x, double in_min, double in_max, double out_min, double out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
