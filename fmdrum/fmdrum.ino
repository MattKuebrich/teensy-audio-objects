/* FM Drum example

  This is a port of the FM Drum mode from the Mutable Instruments Peaks Eurorack module. In this example, you can trigger the drum with a button or an LFO. 
  
  POT01 = LFO trigger freq
  POT02 = FM Drum, Frequency
  POT03 = FM Drum, FM intensity
  POT04 = FM Drum, FM and AM envelope decay time
  POT05 = FM Drum, Noise
  POT05 = FM Drum, Overdrive

*/

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <Bounce.h>
#include "synth_fm_drum.h"

#define POT01 14
#define POT02 15
#define POT03 16
#define POT04 17
#define POT05 22
#define POT06 24

Bounce button1 = Bounce(33, 8); // 8 = 8 ms debounce time

// GUItool: begin automatically generated code
AudioSynthFMDrum drum;            //xy=156.2222023010254,382.88888359069824
AudioControlSGTL5000     sgtl5000_1;     //xy=1284,1411
AudioOutputI2S           i2s1;           //xy=792.8889045715332,396.22222328186035
AudioSynthWaveformModulated lfo;      //xy=484.00001525878906,1270.0000491142273
AudioMixer4              mixer;         //xy=303,213
AudioConnection          patchCord1(lfo, 0, drum, 0);
AudioConnection          patchCord3(drum, 0, i2s1, 0);
AudioConnection          patchCord4(drum, 0, i2s1, 1);

//USB for testing
//AudioOutputUSB           usb_out;           //xy=792.8889045715332,396.22222328186035
//AudioConnection          patchCord5(drum, 0, usb_out, 0);
//AudioConnection          patchCord6(drum, 0, usb_out, 1);
// GUItool: end automatically generated code

void setup() {
  AudioNoInterrupts();
  AudioMemory(12);
  Serial.begin(9600);

  // Configure the pushbutton pins
  pinMode(33, INPUT_PULLUP);

  //lfo.begin(1.0, 200, WAVEFORM_TRIANGLE);
  lfo.begin(0.5, 0, WAVEFORM_SQUARE);

  sgtl5000_1.enable();
  sgtl5000_1.volume(0.4);

  AudioInterrupts();
}

void loop() {


  // Trigger drum with button
  button1.update();
  if (button1.fallingEdge()) {
    Serial.println("button press");
    drum.noteOn();
  }

  // Trigger drum with LFO
  lfo.frequency(mapf(analogRead(POT01), 0, 1023, 0, 10.0));

  // FM Drum controls
  drum.frequency(fscale(0, 1023.0, 20.0, 2304.0, analogRead(POT02), -5.0));
  drum.fm(fscale(0, 1023.0, 0.0, 1.0, analogRead(POT03), -5.0));
  drum.decay(fscale(0, 1023.0, 0.0, 1.0, analogRead(POT04), -2.0));
  drum.noise(fscale(0, 1023.0, 0.0, 1.0, analogRead(POT05), -5.0));
  drum.overdrive(fscale(0, 1023.0, 0.0, 1.0, analogRead(POT06), -2.0));
  
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
