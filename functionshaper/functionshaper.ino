/* Function Shaper example

  This takes a line-in input and passes it through a waveshaping function to create different distorted effects.
  You can select between 20 different shaper functions (which are defined in the "waveshapers.ino" file).

  POT01 = Select shaper function
  POT02 = Input gain
  POT03 = Makeup gain
  POT04 = Parameter A
  POT05 = Parameter B
  POT06 = Parameter C
  POT07 = Mix
  POT08 = DC offset (disabled)

*/

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include "effect_functionshaper.h"

// Going with Paul's advice and using .ino files instead of .cpp and .h files for functions.
// https://forum.pjrc.com/threads/65343-Do-I-need-to-create-my-own-libraries?p=263773&viewfull=1#post263773

#define POT01 14
#define POT02 15
#define POT03 16
#define POT04 17
#define POT05 22
#define POT06 24
#define POT07 25
#define POT08 26

// GUItool: begin automatically generated code

AudioEffectFunctionShaper shaper;            //xy=156.2222023010254,382.88888359069824
AudioControlSGTL5000     sgtl5000_1;     //xy=1284,1411

AudioInputI2S            i2s_input;           //xy=521.333366394043,456.3333921432495
AudioOutputI2S           i2s1;           //xy=792.8889045715332,396.22222328186035
AudioConnection          patchCord1(i2s_input, 0, shaper, 0);
AudioConnection          patchCord2(shaper, 0, i2s1, 0);
AudioConnection          patchCord3(shaper, 0, i2s1, 1);

//USB for testing
//AudioInputUSB            usb2;           //xy=786.2381210327148,602.0951766967773
//AudioOutputUSB           usb1;           //xy=786.2381210327148,602.0951766967773
//AudioConnection          patchCord11(usb2, 0, shaper, 0);
//AudioConnection          patchCord4(shaper, 0, usb1, 0);
//AudioConnection          patchCord5(shaper, 0, usb1, 1);

// GUItool: end automatically generated code

void setup() {
  AudioNoInterrupts();
  AudioMemory(12);
  analogReadResolution(10);
  analogReadAveraging(32); // average the analog value by averaging 16 readings
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.5);
  sgtl5000_1.inputSelect(AUDIO_INPUT_LINEIN);
  shaper.functionShaper(function1);
  // makes sure that the final distorted audio doesn't go above 1.0 and hurt ears or sound toooo nasty
  shaper.enableLimiter(true);
  shaper.limiterThreshold(0.99);
  AudioInterrupts();
}

void loop() {

  // Returns an estimate of the total CPU time used during the most recent audio library update.
  // The number is a number from 0 to 100, representing an estimate of the percentage of the total CPU time consumed.
  //Serial.print("\t\t CPU= ");
  //Serial.println(AudioProcessorUsage());
  //Serial.print("CPU_M = ");
  //Serial.println(AudioProcessorUsageMax());


  //set function
  int functionIndex = map(analogRead(POT01), 0, 1023, 1, 20);

    switch (functionIndex) {
      case 1:
        shaper.functionShaper(function1);
        Serial.println("function1");
        break;
      case 2:
        Serial.println("function2");
        shaper.functionShaper(function2);
        break;
      case 3:
        Serial.println("function3");
        shaper.functionShaper(function3);
        break;
      case 4:
        Serial.println("function4");
        shaper.functionShaper(function4);
        break;
      case 5:
        shaper.functionShaper(function5);
        Serial.println("function5");
        break;
      case 6:
        Serial.println("function6");
        shaper.functionShaper(function6);
        break;
      case 7:
        Serial.println("function7");
        shaper.functionShaper(function7);
        break;
      case 8:
        Serial.println("function8");
        shaper.functionShaper(function8);
        break;
      case 9:
        Serial.println("function9");
        shaper.functionShaper(function9);
        break;
      case 10:
        Serial.println("function10");
        shaper.functionShaper(function10);
        break;
      case 11:
        Serial.println("function11");
        shaper.functionShaper(function11);
        break;
      case 12:
        Serial.println("function12");
        shaper.functionShaper(function12);
        break;
      case 13:
        Serial.println("function13");
        shaper.functionShaper(function13);
        break;
      case 14:
        Serial.println("function14");
        shaper.functionShaper(function14);
        break;
      case 15:
        Serial.println("function15");
        shaper.functionShaper(function15);
        break;
      case 16:
        Serial.println("function16");
        shaper.functionShaper(function16);
        break;
      case 17:
        Serial.println("function17");
        shaper.functionShaper(function17);
        break;
      case 18:
        Serial.println("function18");
        shaper.functionShaper(function18);
        break;
      case 19:
        Serial.println("function19");
        shaper.functionShaper(function19);
        break;
      case 20:
        Serial.println("function20");
        shaper.functionShaper(function20);
        break;
    }

  shaper.inputGain(mapf(analogRead(POT02), 0, 1023, 1.0, 20.0));
  shaper.makeupGain(fscale(0, 1023.0, 0.0, 1.0, analogRead(POT03), -3.0));
  shaper.parameterA(mapf(analogRead(POT04), 0, 1023, 0.0, 1.0));
  shaper.parameterB(mapf(analogRead(POT05), 0, 1023, 0.0, 1.0));
  shaper.parameterC(mapf(analogRead(POT06), 0, 1023, 0.0, 1.0));
  shaper.mix(mapf(analogRead(POT07), 0, 1023, 0.0, 1.0));
  //shaper.offset(mapf(analogRead(POT08), 0, 1023, -1.0, 1.0));
}
