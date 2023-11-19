/* STK Effect example

  This allows you to try all 8 STK effects, but you must select which one to use in setup().
  For this example, it's set to ECHO by default.

  The effects are : CHORUS, ECHO, FREEVERB, JCREV, LENPITSHIFT, NREV, PRCREV and PITSHIFT.

  POT01 = Effects Mix
  POT02 - POT04 = Different functions based on which effect is selected.
  BUTTON01 = Used only for the FreeVerb's "freeze" function.

*/

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <Bounce.h>
#include <ResponsiveAnalogRead.h>

#include "src/effect_stkeffect.h"

const int EFFECT_CHORUS = 1;
const int EFFECT_ECHO = 2;
const int EFFECT_FREEVERB = 3;
const int EFFECT_JCREV = 4;
const int EFFECT_LENTPITSHIFT = 5;
const int EFFECT_NREV = 6;
const int EFFECT_PRCREV = 7;
const int EFFECT_PITSHIFT = 8;

int selectedEffect;
bool showStats;

#define POT01 14
#define POT02 15
#define POT03 16
#define POT04 17

ResponsiveAnalogRead pot01(POT01, true);
ResponsiveAnalogRead pot02(POT02, true);
ResponsiveAnalogRead pot03(POT03, true);
ResponsiveAnalogRead pot04(POT04, true);

float pot01Read;
float pot02Read;
float pot03Read;
float pot04Read;

Bounce button1 = Bounce(33, 50); // 8 = 8 ms debounce time
Bounce button2 = Bounce(34, 50); // 8 = 8 ms debounce time

// GUItool: begin automatically generated code
AudioControlSGTL5000     sgtl5000_1;     //xy=1284,1411
AudioEffectStkEffect stkeffect;            //xy=156.2222023010254,382.88888359069824
AudioInputI2S            i2s_input;           //xy=521.333366394043,456.3333921432495
AudioOutputI2S           i2s1;           //xy=792.8889045715332,396.22222328186035
AudioConnection          patchCord12(i2s_input, 0, stkeffect, 0); //jcverb sounds good with only this enabled
AudioConnection          patchCord17(i2s_input, 1, stkeffect, 1);
AudioConnection          patchCord13(stkeffect, 0, i2s1, 0);
AudioConnection          patchCord14(stkeffect, 1, i2s1, 1);

//USB for testing
//AudioInputUSB            usb_in;           //xy=786.2381210327148,602.0951766967773
//AudioOutputUSB           usb_out;           //xy=792.8889045715332,396.22222328186035
//AudioConnection          patchCord15(stkeffect, 0, usb_out, 0);
//AudioConnection          patchCord16(stkeffect, 1, usb_out, 1);

// GUItool: end automatically generated code


void setup() {

  AudioNoInterrupts();
  AudioMemory(10);

  showStats = 0; // enable to show CPU usage stats

  // Select which effect to use here:
  selectedEffect = EFFECT_ECHO;
  // I'm doing it this way so it sets the effect AND the corresponding controls in loop() in one go.


  if (selectedEffect == EFFECT_CHORUS) {
    stkeffect.begin(CHORUS); //stereo or mono in, stereo out
  }

  if (selectedEffect == EFFECT_ECHO) {
    stkeffect.begin(ECHO); //
  }

  if (selectedEffect == EFFECT_FREEVERB) {
    stkeffect.begin(FREEVERB); //stereo or mono in, stereo out
  }

  if (selectedEffect == EFFECT_JCREV) {
    stkeffect.begin(JCREV); //mono in, stereo out
  }

  if (selectedEffect == EFFECT_LENTPITSHIFT) {
    stkeffect.begin(LENTPITSHIFT); // mono in, mono (mirrored) out, doesnt work with mix() and doesn't work well in general.
  }

  if (selectedEffect == EFFECT_NREV) {
    stkeffect.begin(NREV);  //mono in, stereo out
  }

  if (selectedEffect == EFFECT_PRCREV) {
    stkeffect.begin(PRCREV);  //mono in, stereo out
  }

  if (selectedEffect == EFFECT_PITSHIFT) {
    stkeffect.begin(PITSHIFT); // mono in, mono (mirrored) out
  }

  if (!selectedEffect) {
    selectedEffect = ECHO; // default if not selected
  }

  // Configure the pushbutton pins
  pinMode(33, INPUT_PULLUP);

  sgtl5000_1.enable();
  sgtl5000_1.volume(0.4);

  AudioInterrupts();
}

void loop() {

  if (showStats) {
    stats();
  }


  pot01.update();
  pot02.update();
  pot03.update();
  pot04.update();

  button1.update();

  pot01Read = mapf(pot01.getValue(), 0, 1023, 0.0, 1.0);
  pot02Read = mapf(pot02.getValue(), 0, 1023, 0.0, 1.0);
  pot03Read = mapf(pot03.getValue(), 0, 1023, 0.0, 1.0);
  pot04Read = mapf(pot04.getValue(), 0, 1023, 0.0, 1.0);


  // Most of the default ranges are taken from the Effects STK demo project here:
  // https://github.com/thestk/stk/blob/master/projects/effects/effects.cpp

  // Effects Mix
  stkeffect.mix(pot01Read);

  // Chorus
  if (selectedEffect == EFFECT_CHORUS) {
    stkeffect.modFrequency(pot02Read * 4.0); // 0.0 to 4.0 hz
    stkeffect.modDepth(pot03Read * 0.2);
  }

  // Echo
  if (selectedEffect == EFFECT_ECHO) {
    stkeffect.maxDelay(1.0); //default
    stkeffect.delay(pot02Read * 0.95);
  }

  // JCRev, NRev, PRCRev
  if (selectedEffect == EFFECT_JCREV || selectedEffect == EFFECT_NREV || selectedEffect == EFFECT_PRCREV) {
    stkeffect.decay(pot02Read * 10.0); // 0.0 to 10.0 seconds
  }

  // PitShift, LentPitShift
  if (selectedEffect == EFFECT_PITSHIFT || selectedEffect == EFFECT_LENTPITSHIFT) {
    stkeffect.shift(1.4 * pot02Read + 0.3);
  }

  // FreeVerb
  if (selectedEffect == EFFECT_FREEVERB) {
    stkeffect.damping(pot02Read);
    stkeffect.roomSize(pot03Read);
    stkeffect.width(pot04Read);

    if (button1.fallingEdge()) {
      Serial.println("button1!");
      stkeffect.mode(1); //freeze on button press
    }

    if (button1.risingEdge()) {
      stkeffect.mode(0); //unfreeze when released
    }
  }

}

// floating point map function taken from https://forum.arduino.cc/index.php?topic=361046.0
double mapf(double x, double in_min, double in_max, double out_min, double out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void stats() {
  // Returns an estimate of the total CPU time used during the most recent audio library update.
  // The number is a number from 0 to 100, representing an estimate of the percentage of the total CPU time consumed.

  Serial.print("TOTAL CPU = ");
  Serial.print(AudioProcessorUsage());
  Serial.println("%");

  Serial.print("TOTAL CPU MAX = ");
  Serial.print(AudioProcessorUsageMax());
  Serial.println("%");

  Serial.print("STKEFFECT CPU = ");
  Serial.print(stkeffect.processorUsage());
  Serial.println("%");

  Serial.print("AUDIOMEMORY = ");
  Serial.println(AudioMemoryUsage());

  Serial.print("AUDIOMEMORY MAX = ");
  Serial.println(AudioMemoryUsageMax());
  Serial.println("");
}
