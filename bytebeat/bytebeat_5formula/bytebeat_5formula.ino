/* Bytebeat example, 5formula

  This sketch generates bytebeats with 5 selectable formulas, sample rate, parameters, reset and reverse functions.
  It uses the ResponsiveAnalogRead and Bounce libraries, so make sure they are installed.

  POT01 = Select bytebeat equation
  POT02 = Sample rate
  POT03 = Parameter 1
  POT04 = Parameter 2
  POT05 = Parameter 3

*/

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <ResponsiveAnalogRead.h>
#include <Bounce.h>

#include "synth_bytebeat.h"

// this suppresses warning that appear while using certain bytebeat formulas
#pragma GCC diagnostic ignored "-Wparentheses"

uint32_t formula1(uint32_t t, uint8_t w, uint32_t p1, uint32_t p2, uint32_t p3) {
  //classic "crowd" formula from http://canonical.org/~kragen/bytebeat/
  return ((t << 1) ^ ((t << 1) + (t >> 7)&t >> 12)) | t >> (4 - (1 ^ 7 & (t >> 19))) | t >> 7;
}

uint32_t formula2(uint32_t t, uint8_t w, uint32_t p1, uint32_t p2, uint32_t p3) {
  //ststututterter
  //return ((t * (-(t >> p1 / 12 | t | t >> p2 / 12 | t >> p3 / 13)))^t);
  
  //techno
  p1 = map(p1, 0, 1023, 0, 3000);
  p2 = map(p2, 0, 1023, 5, 10);
  p3 = map(p3, 0, 1023, 0, 10);
  return t&(592)?t>>p1:t>>p2&t>>p2&(t*29)<<t|t/p3>>p2;  
}

uint32_t formula3(uint32_t t, uint8_t w, uint32_t p1, uint32_t p2, uint32_t p3) {
  //remappiung ranges 
  p1 = map(p1, 0, 1023, 0, 128);
  p2 = map(p2, 0, 1023, 0, 10);
  p3 = map(p3, 0, 1023, 0, 10);
  return (t >> 8 & p1 ? (t << 1 & t * 3 & -t >> p2 & t >> p3) - 1 | t >> 2 : (t << 1 & t * 3 & -t >> p2 & t >> p3 + 1) - 1 | -t >> p2 + 1);
}

uint32_t formula4(uint32_t t, uint8_t w, uint32_t p1, uint32_t p2, uint32_t p3) {
  //example of a recursive formula, w is the previous bytebeat output
  return w ^ (t >> (p3 >> 4)) >> (t / 6988 * t % (p1 + 1)) + (t << t / (p2 * 4));
}

uint32_t formula5(uint32_t t, uint8_t w, uint32_t p1, uint32_t p2, uint32_t p3) {
  // melodic (from equation composer)
  return ( t * (( t >> 9 | t >> p1 ) & p2)) & (p3 + 5);
}


// GUItool: begin automatically generated code
AudioSynthBytebeat bytebeat;            //xy=156.2222023010254,382.88888359069824
AudioOutputI2S           i2s1;           //xy=792.8889045715332,396.22222328186035
AudioConnection          patchCord2(bytebeat, 0, i2s1, 0);
AudioConnection          patchCord3(bytebeat, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=1284,1411
// GUItool: end automatically generated code

#define POT01 14
#define POT02 15
#define POT03 16
#define POT04 17
#define POT05 22

ResponsiveAnalogRead pot01(POT01, true);
ResponsiveAnalogRead pot02(POT02, true);
ResponsiveAnalogRead pot03(POT03, true);
ResponsiveAnalogRead pot04(POT04, true);
ResponsiveAnalogRead pot05(POT05, true);

Bounce button1 = Bounce(33, 8);
Bounce button2 = Bounce(34, 8);

bool rev = 0;

void setup() {
  AudioNoInterrupts();
  AudioMemory(12);

  // Configure the pushbutton pins
  pinMode(33, INPUT_PULLUP);
  pinMode(34, INPUT_PULLUP);

  sgtl5000_1.enable();
  sgtl5000_1.volume(.2);

  bytebeat.sampleRate(44100);
  bytebeat.formula(formula1);

  AudioInterrupts();
}

void loop() {

  pot01.update();
  pot02.update();
  pot03.update();
  pot04.update();
  pot05.update();

  button1.update();
  button2.update();

  // set samplerate, expander lower range with fscale
  //bytebeat.sampleRate(fscale( 0.094, 1023.0, 10, 48000, pot02.getValue(), -6.5));
  bytebeat.sampleRate(8000);

  // set formula
  int formulaIndex = map(pot01.getValue(), 0, 1023, 1, 5);

  switch (formulaIndex) {
    case 1:
      bytebeat.formula(formula1);
      Serial.println("formula1");
      break;
    case 2:
      bytebeat.formula(formula2);
      Serial.println("formula2");
      bytebeat.sampleRate(8000); //sample rate explicitly set here so it won't use the value set by the pot above
      break;
    case 3:
      bytebeat.formula(formula3);
      Serial.println("formula3");
      bytebeat.sampleRate(8000); //sample rate explicitly set here so it won't use the value set by the pot above
      break;
    case 4:
      bytebeat.formula(formula4);
      Serial.println("formula4");
      break;
    case 5:
      bytebeat.formula(formula5);
      Serial.println("formula5");
      break;
  }

  // set parameters
  bytebeat.parameter1(map(pot03.getValue(), 0, 1023, 0, 1023));
  bytebeat.parameter2(map(pot04.getValue(), 0, 1023, 0, 1023));
  bytebeat.parameter3(map(pot05.getValue(), 0, 1023, 0, 1023));

  //reset
  if (button1.fallingEdge()) {
    bytebeat.reset();
    Serial.println("bytebeat reset");
  }

  //reverse
  if (button2.fallingEdge()) {
    rev = !rev;
    bytebeat.reverse(rev);
    Serial.println("bytebeat reverse");
  }

}



// floating point map function taken from https://forum.arduino.cc/index.php?topic=361046.0
double mapf(double x, double in_min, double in_max, double out_min, double out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
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
