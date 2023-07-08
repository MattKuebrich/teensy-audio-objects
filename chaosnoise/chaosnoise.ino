/* Chaosnoise example

This simply routes the chaos noise to the output.

POT01 = Chaos amount 
POT02 = Sample rate

*/

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

#include "synth_chaosnoise.h"

#define POT01 14
#define POT02 15
#define POT03 16

// GUItool: begin automatically generated code
AudioSynthChaosNoise chaosnoise;            //xy=156.2222023010254,382.88888359069824
AudioOutputI2S           i2s1;           //xy=792.8889045715332,396.22222328186035
AudioConnection          patchCord1(chaosnoise, 0, i2s1, 0);
AudioConnection          patchCord2(chaosnoise, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=1284,1411
// GUItool: end automatically generated code

void setup() {
  AudioNoInterrupts();
  AudioMemory(12);
  Serial.begin(9600);

  sgtl5000_1.enable();
  sgtl5000_1.volume(0.3); // this gets pretty loud, so lowered the volume

  AudioInterrupts();
}

void loop() {
  chaosnoise.chaos(mapf(analogRead(POT01), 0, 1023, 0.0, 1.0)); // 0.0 to 1.0
  chaosnoise.rate(mapf(analogRead(POT02), 0, 1023, 0.0, 44100.0)); // in Hz
  chaosnoise.mode(BROKEN); //CLASSIC, BROKEN
}


// floating point map function taken from https://forum.arduino.cc/index.php?topic=361046.0
double mapf(double x, double in_min, double in_max, double out_min, double out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
