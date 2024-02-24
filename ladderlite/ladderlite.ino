/* Ladder Lite example

  This is sketch was written for an Adafruit ItsyBitsy M4 Express board, but obviously could be adapted for Teensy boards.

  It uses four instances of the "lite" ladder filter, each filtering a different fixed-frequency oscillator.

  POT01 = Filter A Cutoff
  POT02 = Filter B Cutoff
  POT03 = Filter C Cutoff
  POT04 = Filter D Cutoff

*/

#include "filter_ladderlite.h"
#include <Audio.h> // uses the "Adafruit Fork" verison of the Teensy Audio Library, https://github.com/adafruit/Audio

#define POT01 2
#define POT02 3
#define POT03 4
#define POT04 5
#define POT05 6

// GUItool: begin automatically generated code

AudioSynthWaveform OscA;      //xy=1177.6665954589844,1918.3332815170288
AudioSynthWaveform OscB;       //xy=1179.6665954589844,1959.3332815170288
AudioSynthWaveform OscC;       //xy=1179.6665954589844,1959.3332815170288
AudioSynthWaveform OscD;       //xy=1179.6665954589844,1959.3332815170288

AudioFilterLadderLite       LadderA;        //xy=1776.6666259765625,1838.0000381469727
AudioFilterLadderLite       LadderB;        //xy=1776.6666259765625,1838.0000381469727
AudioFilterLadderLite       LadderC;        //xy=1776.6666259765625,1838.0000381469727
AudioFilterLadderLite       LadderD;        //xy=1776.6666259765625,1838.0000381469727

AudioOutputAnalogStereo  dac;          //xy=2098.6666259765625,1851.0000381469727
AudioMixer4              mixer;   //xy=1590.6666259765625,1827.0000381469727

AudioConnection          patchCord1(OscA, 0, LadderA, 0);
AudioConnection          patchCord2(OscB, 0, LadderB, 0);
AudioConnection          patchCord3(OscC, 0, LadderC, 0);
AudioConnection          patchCord4(OscD, 0, LadderD, 0);
AudioConnection          patchCord5(LadderA, 0, mixer, 0);
AudioConnection          patchCord6(LadderB, 0, mixer, 1);
AudioConnection          patchCord7(LadderC, 0, mixer, 2);
AudioConnection          patchCord8(LadderD, 0, mixer, 3);
AudioConnection          patchCord9(mixer, 0, dac, 0);
AudioConnection          patchCord10(mixer, 0, dac, 1);

// GUItool: end automatically generated code

float POT01_READ, POT02_READ, POT03_READ, POT04_READ, POT05_READ;

float oscAfreq, oscBfreq, filterCutoffA, filterCutoffB, filterCutoffC, filterCutoffD;

void setup() {

  AudioMemory(30); 
  Serial.begin(9600);

  OscA.begin(0.5, 100, WAVEFORM_SAWTOOTH);
  OscB.begin(0.5, 200, WAVEFORM_SAWTOOTH);
  OscC.begin(0.5, 300, WAVEFORM_SAWTOOTH);
  OscD.begin(0.5, 400, WAVEFORM_SAWTOOTH);

  LadderA.frequency(5000);
  LadderA.resonance(0.74); 
  LadderB.frequency(5000);
  LadderB.resonance(0.74); 
  LadderC.frequency(5000);
  LadderC.resonance(0.74); 
  LadderD.frequency(5000);
  LadderD.resonance(0.74); 

  //default to linear but setting it anyway
  LadderA.interpolationMethod(LADDERLITE_FILTER_INTERPOLATION_LINEAR);
  LadderB.interpolationMethod(LADDERLITE_FILTER_INTERPOLATION_LINEAR);
  LadderC.interpolationMethod(LADDERLITE_FILTER_INTERPOLATION_LINEAR);
  LadderD.interpolationMethod(LADDERLITE_FILTER_INTERPOLATION_LINEAR);

}

void loop() {

//memStats(); // I don't think this is working correctly on the ItsyBitsy ?? 

filterCutoffA = fscale( 0, 1023.0, 20, 8000.0, analogRead(POT01), -3.5); 
filterCutoffB = fscale( 0, 1023.0, 20, 8000.0, analogRead(POT02), -3.5); 
filterCutoffC = fscale( 0, 1023.0, 20, 8000.0, analogRead(POT03), -3.5);
filterCutoffD = fscale( 0, 1023.0, 20, 8000.0, analogRead(POT04), -3.5); 

LadderA.frequency(filterCutoffA);
LadderB.frequency(filterCutoffB);
LadderC.frequency(filterCutoffC);
LadderD.frequency(filterCutoffD);

} //end of loop


void memStats() {
  // Returns an estimate of the total CPU time used during the most recent audio library update.
  // The number is a number from 0 to 100, representing an estimate of the percentage of the total CPU time consumed.

  Serial.print("TOTAL CPU = ");
  Serial.print(AudioProcessorUsage());
  Serial.println("%");

  Serial.print("TOTAL CPU MAX = ");
  Serial.print(AudioProcessorUsageMax());
  Serial.println("%");

  Serial.print("ladder map CPU = ");
  Serial.print(LadderA.processorUsage());
  Serial.println("%");

  Serial.print("AUDIOMEMORY = ");
  Serial.println(AudioMemoryUsage());

  Serial.print("AUDIOMEMORY MAX = ");
  Serial.println(AudioMemoryUsageMax());
  Serial.println("");
}


//fscale for log response on frequency
//https://playground.arduino.cc/Main/Fscale/
float fscale( float originalMin, float originalMax, float newBegin, float
              newEnd, float inputValue, float curve) {

  float OriginalRange = 0;
  float NewRange = 0;
  float zeroRefCurVal = 0;
  float normalizedCurVal = 0;
  float rangedValue = 0;
  boolean invFlag = 0;

  // condition curve parameter
  // limit range

  if (curve > 10) curve = 10;
  if (curve < -10) curve = -10;

  curve = (curve * -.1) ; // - invert and scale - this seems more intuitive - postive numbers give more weight to high end on output
  curve = pow(10, curve); // convert linear scale into lograthimic exponent for other pow function

  // Check for out of range inputValues
  if (inputValue < originalMin) {
    inputValue = originalMin;
  }
  if (inputValue > originalMax) {
    inputValue = originalMax;
  }

  // Zero Refference the values
  OriginalRange = originalMax - originalMin;

  if (newEnd > newBegin) {
    NewRange = newEnd - newBegin;
  }
  else
  {
    NewRange = newBegin - newEnd;
    invFlag = 1;
  }

  zeroRefCurVal = inputValue - originalMin;
  normalizedCurVal  =  zeroRefCurVal / OriginalRange;   // normalize to 0 - 1 float


  // Check for originalMin > originalMax  - the math for all other cases i.e. negative numbers seems to work out fine
  if (originalMin > originalMax ) {
    return 0;
  }

  if (invFlag == 0) {
    rangedValue =  (pow(normalizedCurVal, curve) * NewRange) + newBegin;

  }
  else     // invert the ranges
  {
    rangedValue =  newBegin - (pow(normalizedCurVal, curve) * NewRange);
  }

  return rangedValue;
}
