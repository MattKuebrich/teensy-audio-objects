/* Bytebeat example, simple

  This sketch simply plays back the classic "crowd" bytebeat at a default sample rate of 8000.
 
*/

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

#include "synth_bytebeat.h"

// this suppresses warning that appear while using certain bytebeat formulas
#pragma GCC diagnostic ignored "-Wparentheses"

uint32_t formula1(uint32_t t, uint8_t w, uint32_t p1, uint32_t p2, uint32_t p3) {
  //classic "crowd" formula from http://canonical.org/~kragen/bytebeat/
  return ((t << 1) ^ ((t << 1) + (t >> 7)&t >> 12)) | t >> (4 - (1 ^ 7 & (t >> 19))) | t >> 7;
 }

// GUItool: begin automatically generated code
AudioSynthBytebeat bytebeat;            //xy=156.2222023010254,382.88888359069824
AudioOutputI2S           i2s1;           //xy=792.8889045715332,396.22222328186035
AudioConnection          patchCord2(bytebeat, 0, i2s1, 0);
AudioConnection          patchCord3(bytebeat, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=1284,1411
// GUItool: end automatically generated code

void setup() {
  AudioNoInterrupts();
  AudioMemory(12);

  sgtl5000_1.enable();
  sgtl5000_1.volume(.2);

  bytebeat.sampleRate(8000); //8000 is the default
  bytebeat.formula(formula1);
  
  AudioInterrupts();
}

void loop() {
//nothing to do here  
}
