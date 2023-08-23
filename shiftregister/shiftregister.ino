/* Shift register example

   This sketch similar to Rob Hordijk's Benjolin, without the filter. There are two triangle oscillators which go into a comparator and are sent to the output. 
   The square outputs from the same oscillators go into the shift register's data and clock inputs. The DAC (or rungler) output from the shift register then
   frequency modulates the original oscillators. From all this, noisey chaotic / melodic sequences can arise.
   
   POT01 = Osc A Frequency
   POT02 = Osc B Frequency
   POT03 = Rungler to Osc A
   POT04 = Rungler to Osc B
   POT05 = Enable / Disable XOR feedback
   POT05 = Enable / Disable Looping

*/


#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <ResponsiveAnalogRead.h>

#include "effect_shiftregister.h"
#include "effect_comparator.h"

// GUItool: begin automatically generated code
AudioMixer4              osc_a_cv;       //xy=755.0000495910645,1481.3332633972168
AudioMixer4              osc_b_cv;       //xy=774.6666984558105,1614.666690826416
AudioSynthWaveformModulated osc_a_tri;      //xy=922,1468
AudioSynthWaveformModulated osc_a_sq;       //xy=924,1509
AudioSynthWaveformModulated osc_b_tri;      //xy=940,1598
AudioSynthWaveformModulated osc_b_sq;       //xy=944,1642
AudioEffectShiftRegister       rungler_a;      //xy=1204.6667137145996,1628.666648864746
AudioEffectComparator    compare1;       //xy=1219.6667098999023,1466.666639328003
AudioOutputI2S           i2s1;           //xy=1455.0000190734863,1465.0000133514404
AudioControlSGTL5000     sgtl5000_1;     //xy=1284,1411
AudioConnection          patchCord1(osc_a_cv, 0, osc_a_tri, 0);
AudioConnection          patchCord2(osc_a_cv, 0, osc_a_sq, 0);
AudioConnection          patchCord3(osc_b_cv, 0, osc_b_tri, 0);
AudioConnection          patchCord4(osc_b_cv, 0, osc_b_sq, 0);
AudioConnection          patchCord5(osc_a_tri, 0, compare1, 0);
AudioConnection          patchCord6(osc_a_sq, 0, rungler_a, 0);
AudioConnection          patchCord7(osc_b_tri, 0, compare1, 1);
AudioConnection          patchCord8(osc_b_sq, 0, rungler_a, 1);
AudioConnection          patchCord9(rungler_a, 8, osc_a_cv, 0);
AudioConnection          patchCord10(rungler_a, 8, osc_b_cv, 0);
AudioConnection          patchCord11(compare1, 0, i2s1, 0);
AudioConnection          patchCord12(compare1, 0, i2s1, 1);
// GUItool: end automatically generated code

#define POT01 14
#define POT02 15
#define POT03 16
#define POT04 17
#define POT05 22
#define POT06 24

ResponsiveAnalogRead pot01(POT01, true);
ResponsiveAnalogRead pot02(POT02, true);
ResponsiveAnalogRead pot03(POT03, true);
ResponsiveAnalogRead pot04(POT04, true);
ResponsiveAnalogRead pot05(POT05, true);
ResponsiveAnalogRead pot06(POT06, true);

void setup() {
  AudioNoInterrupts();
  AudioMemory(12);

  sgtl5000_1.enable();
  sgtl5000_1.volume(.3);

  //oscA
  osc_a_tri.begin(1.0, 200, WAVEFORM_TRIANGLE);
  osc_a_sq.begin(1.0, 200, WAVEFORM_PULSE);
  //osc_a_sq.offset(-1.0);

  //oscB
  osc_b_tri.begin(1.0, 200, WAVEFORM_TRIANGLE);
  osc_b_sq.begin(1.0, 200, WAVEFORM_PULSE);
  //osc_b_sq.offset(-1.0);

  osc_a_tri.frequencyModulation(10);
  osc_a_sq.frequencyModulation(10);
  osc_b_tri.frequencyModulation(10);
  osc_b_sq.frequencyModulation(10);

  AudioInterrupts();
}

void loop() {

  //If you open the serial monitor, you can view the bits going through the register
  Serial.print(rungler_a.readBit0());
  Serial.print(rungler_a.readBit1());
  Serial.print(rungler_a.readBit2());
  Serial.print(rungler_a.readBit3());
  Serial.print(rungler_a.readBit4());
  Serial.print(rungler_a.readBit5());
  Serial.print(rungler_a.readBit6());
  Serial.println(rungler_a.readBit7());

  pot01.update();
  pot02.update();
  pot03.update();
  pot04.update();
  pot05.update();
  pot06.update();

  float oscAfreq = fscale( 0, 1023.0, 0.094, 4702.563, pot01.getValue(), -6.5); 
  float oscBfreq = fscale( 0, 1023.0, 0.094, 4702.563, pot02.getValue(), -6.5); 
  float rungler_to_osc_a = mapf(pot03.getValue(), 0, 1023, 0.0, 0.5);
  float rungler_to_osc_b = mapf(pot04.getValue(), 0, 1023, 0.0, 0.5);

  osc_a_tri.frequency(oscAfreq); //tri
  osc_a_sq.frequency(oscAfreq); //square

  osc_b_tri.frequency(oscBfreq); //tri
  osc_b_sq.frequency(oscBfreq); //square

  //rungler going into OscAfreq
  osc_a_cv.gain(0, rungler_to_osc_a);

  //rungler going into OscBfreq
  osc_b_cv.gain(0, rungler_to_osc_b);

  //enable looping
  if (pot05.getValue() < 512) {
    rungler_a.xorEnable(0);
  } else {
    rungler_a.xorEnable(1);
  }

  // enable xor feedback
  if (pot06.getValue() < 512) {
    rungler_a.loopEnable(0);
  } else {
    rungler_a.loopEnable(1);
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
