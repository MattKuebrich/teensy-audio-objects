/* Bytebeat example, Equation Composer

  This sketch includes all four bytebeat equation banks from the Equation Composer Eurorack module by Microbe Modular. 
  
  Adapted with Bret Truchan's permission.
  https://github.com/clone45/EquationComposer
  
  This uses the ResponsiveAnalogRead and Bounce libraries, so make sure they are installed.

  POT01 = Select equation bank
  POT02 = Select equation
  POT03 = Sample rate
  POT04 = Parameter 1
  POT05 = Parameter 2
  POT06 = Parameter 3
  BUTTON01 = Reset
  BUTTON02 = Reverse

*/

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

#include <ResponsiveAnalogRead.h>
#include <Bounce.h>

#include "synth_bytebeat.h"

//banks
#include "bank_khepri.h"
#include "bank_sobek.h"
#include "bank_ptah.h"
#include "bank_drum.h"

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
#define POT06 24

const int KHEPRI_NUM_FORMULAS = 20;
const int PTAH_NUM_FORMULAS = 20;
const int SOBEK_NUM_FORMULAS = 16;
const int DRUM_NUM_FORMULAS = 14;

typedef uint32_t (*FormulaFunction)(uint32_t, uint8_t, uint32_t, uint32_t, uint32_t);

FormulaFunction khepriFormulas[KHEPRI_NUM_FORMULAS] = {
  khepri1, khepri2, khepri3, khepri4, khepri5,
  khepri6, khepri7, khepri8, khepri9, khepri10,
  khepri11, khepri12, khepri13, khepri14, khepri15,
  khepri16, khepri17, khepri18, khepri19, khepri20
};

FormulaFunction ptahFormulas[PTAH_NUM_FORMULAS] = {
  ptah1, ptah2, ptah3, ptah4, ptah5,
  ptah6, ptah7, ptah8, ptah9, ptah10,
  ptah11, ptah12, ptah13, ptah14, ptah15,
  ptah16, ptah17, ptah18, ptah19, ptah20
};

FormulaFunction sobekFormulas[SOBEK_NUM_FORMULAS] = {
  sobek1, sobek2, sobek3, sobek4, sobek5,
  sobek6, sobek7, sobek8, sobek9, sobek10,
  sobek11, sobek12, sobek13, sobek14, sobek15,
  sobek16
};

FormulaFunction drumFormulas[DRUM_NUM_FORMULAS] = {
  drum1, drum2, drum3, drum4, drum5,
  drum6, drum7, drum8, drum9, drum10,
  drum11, drum12, drum13, drum14
};


ResponsiveAnalogRead pot01(POT01, true, 0.001);
ResponsiveAnalogRead pot02(POT02, true, 0.001);
ResponsiveAnalogRead pot03(POT03, true, 0.001);
ResponsiveAnalogRead pot04(POT04, true, 0.001);
ResponsiveAnalogRead pot05(POT05, true, 0.001);
ResponsiveAnalogRead pot06(POT06, true, 0.001);

Bounce button1 = Bounce(33, 8);
Bounce button2 = Bounce(34, 8);

bool rev = 0;

void setup() {
  AudioNoInterrupts();
  AudioMemory(12);

  // configure the pushbutton pins
  pinMode(33, INPUT_PULLUP);
  pinMode(34, INPUT_PULLUP);

  sgtl5000_1.enable();
  
  // bytebeats are LOUD so volume is turned down
  sgtl5000_1.volume(.2); 

  // defaults
  bytebeat.sampleRate(8000);
  bytebeat.formula(khepri1);

  AudioInterrupts();
}

void loop() {

  pot01.update();
  pot02.update();
  pot03.update();
  pot04.update();
  pot05.update();
  pot06.update();

  button1.update();
  button2.update();

  // set samplerate
  bytebeat.sampleRate(map(pot03.getValue(), 0, 1023, 2000, 8000)); // seems to be a sensible range

  // set bank
  int bankIndex = map(pot01.getValue(), 0, 1023, 1, 4);

  // set formula
  int formulaIndex = map(pot02.getValue(), 0, 1023, 1, 20);

  // assign bank and formula
  if (bankIndex == 1) {
    if (formulaIndex >= 1 && formulaIndex <= KHEPRI_NUM_FORMULAS) {
      bytebeat.formula(khepriFormulas[formulaIndex - 1]);
      Serial.println("khepri" + String(formulaIndex));
    } else {
      //if we're above the number of formulas, stay on the last one
      bytebeat.formula(khepriFormulas[KHEPRI_NUM_FORMULAS - 1]);
      Serial.println("khepri" + String(KHEPRI_NUM_FORMULAS));
    }
  }

  if (bankIndex == 2) {
    if (formulaIndex >= 1 && formulaIndex <= PTAH_NUM_FORMULAS) {
      bytebeat.formula(ptahFormulas[formulaIndex - 1]);
      Serial.println("ptah" + String(formulaIndex));
    } else {
      //if we're above the number of formulas, stay on the last one
      bytebeat.formula(ptahFormulas[PTAH_NUM_FORMULAS - 1]);
      Serial.println("ptah" + String(PTAH_NUM_FORMULAS));
    }
  }

  if (bankIndex == 3) {
    if (formulaIndex >= 1 && formulaIndex <= SOBEK_NUM_FORMULAS) {
      bytebeat.formula(sobekFormulas[formulaIndex - 1]);
      Serial.println("sobek" + String(formulaIndex));
    } else {
      //if we're above the number of formulas, stay on the last one
      bytebeat.formula(sobekFormulas[SOBEK_NUM_FORMULAS - 1]);
      Serial.println("sobek" + String(SOBEK_NUM_FORMULAS));
    }
  }

  if (bankIndex == 4) {
    if (formulaIndex >= 1 && formulaIndex <= DRUM_NUM_FORMULAS) {
      bytebeat.formula(drumFormulas[formulaIndex - 1]);
      Serial.println("drum" + String(formulaIndex));
    } else {
      //if we're above the number of formulas, stay on the last one
      bytebeat.formula(drumFormulas[DRUM_NUM_FORMULAS - 1]);
      Serial.println("drum" + String(DRUM_NUM_FORMULAS));
    }
  }

  // set parameters
  bytebeat.parameter1(map(pot04.getValue(), 0, 1023, 1, 255)); 
  bytebeat.parameter2(map(pot05.getValue(), 0, 1023, 1, 255));
  bytebeat.parameter3(map(pot06.getValue(), 0, 1023, 1, 255));

  // reset
  if (button1.fallingEdge()) {
    bytebeat.reset();
    Serial.println("bytebeat reset");
  }

  // reverse
  if (button2.fallingEdge()) {
    rev = !rev;
    Serial.println("bytebeat reverse");
    bytebeat.reverse(rev);
  }
  
}

// floating point map function taken from https://forum.arduino.cc/index.php?topic=361046.0
double mapf(double x, double in_min, double in_max, double out_min, double out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
