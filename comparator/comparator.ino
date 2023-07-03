/* Comparator example  

"The two triangle waves from the oscillators are 'compared' to create one single PWM wave. 
If one osc is tuned into the LFO range and the other is in audio range you wil hear the classic PWM effect. 
When both are tuned into the audio range it sounds like a ringmodulator effect."

- Rob Hordjk, describing the Benjolin's input signal into the filter

*/

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

#include "effect_comparator.h"

// GUItool: begin automatically generated code
AudioSynthWaveformModulated osc_a_tri;      //xy=484.00001525878906,1270.0000491142273
AudioSynthWaveformModulated osc_b_tri;      //xy=484.0000305175781,1320.0000305175781
AudioEffectComparator    comparator1;    //xy=640.0000305175781,1300.000036239624
AudioOutputI2S           i2s1;           //xy=819.333366394043,1303.9999704360962
AudioConnection          patchCord1(osc_a_tri, 0, comparator1, 0);
AudioConnection          patchCord2(osc_b_tri, 0, comparator1, 1);
AudioConnection          patchCord3(comparator1, 0, i2s1, 0);
AudioConnection          patchCord4(comparator1, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=650.3333358764648,1218.3333797454834
// GUItool: end automatically generated code

#define POT01 14
#define POT02 15

float oscAfreq, oscBfreq;

void setup() {
  AudioMemory(12);
  
  sgtl5000_1.enable();
  sgtl5000_1.volume(.5);
  
  osc_a_tri.begin(1.0, 200, WAVEFORM_TRIANGLE);
  osc_b_tri.begin(1.0, 200, WAVEFORM_TRIANGLE);

  comparator1.mode(LESS); // LESS, GREATER, EQUAL, NOT_EQUAL
}

void loop() {
  // set frequency ranges for oscs
  oscAfreq = mapf(analogRead(POT01), 0, 1023, 0.094, 2000.0);
  oscBfreq = mapf(analogRead(POT02), 0, 1023, 0.094, 2000.0);
  
  osc_a_tri.frequency(oscAfreq);
  osc_b_tri.frequency(oscBfreq);
}

// floating point map function taken from https://forum.arduino.cc/index.php?topic=361046.0
double mapf(double x, double in_min, double in_max, double out_min, double out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
