/* Chaos Maps example

  This sketch demonstates a logistic map and its chaotic behavior. As you turn up the rate past 3.6, chaos will emerge. 
  The LFOs can be used to modulate the rate and sample rate reduction.
  
  POT01 = Seed
  POT02 = Rate
  POT03 = Sample rate
  POT04 = LFO 1 Amount
  POT05 = LFO 1 Frequency
  POT06 = LFO 1 Amount
  POT07 = LFO 1 Frequency

*/

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <ResponsiveAnalogRead.h>

#include "synth_chaosmaps.h"

#define POT01 14
#define POT02 15
#define POT03 16
#define POT04 17
#define POT05 22
#define POT06 24
#define POT07 25

ResponsiveAnalogRead pot01(POT01, true);
ResponsiveAnalogRead pot02(POT02, true);
ResponsiveAnalogRead pot03(POT03, true);
ResponsiveAnalogRead pot04(POT04, true);
ResponsiveAnalogRead pot05(POT05, true);
ResponsiveAnalogRead pot06(POT06, true);
ResponsiveAnalogRead pot07(POT07, true);

bool showMemStats = false;
float seedValue;
float prevSeedValue;


// GUItool: begin automatically generated code
AudioSynthChaosMaps chaosmaps;            //xy=156.2222023010254,382.88888359069824
AudioOutputI2S           i2s1;           //xy=792.8889045715332,396.22222328186035
AudioSynthWaveformModulated lfo1;      //xy=484.00001525878906,1270.0000491142273
AudioSynthWaveformModulated lfo2;      //xy=484.00001525878906,1270.0000491142273
AudioMixer4              mixer;         //xy=303,213
AudioMixer4              mixer2;         //xy=303,213
AudioMixer4              mixer3;         //xy=303,213

AudioConnection          patchCord0(lfo1, 0, mixer, 0); // lfo
AudioConnection          patchCord16(lfo2, 0, mixer2, 0);

AudioConnection          patchCord1(mixer, 0, chaosmaps, 0); // modulate rate
AudioConnection          patchCord11(mixer2, 0, chaosmaps, 1); // modulate samplerate

AudioConnection          patchCord32(chaosmaps, 0, i2s1, 0);
AudioConnection          patchCord34(chaosmaps, 0, i2s1, 1);

//usb for testing
AudioOutputUSB           usb_out;           //xy=792.8889045715332,396.22222328186035
AudioConnection          patchCord5(chaosmaps, 0, usb_out, 0);
AudioConnection          patchCord6(chaosmaps, 0, usb_out, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=1284,1411
// GUItool: end automatically generated code

void setup() {
  AudioNoInterrupts();
  AudioMemory(12);
  Serial.begin(9600);

  lfo1.begin(1.0, 2, WAVEFORM_TRIANGLE);
  lfo2.begin(1.0, 2, WAVEFORM_SAWTOOTH);

  //chaosmaps.sampleRate(16744);
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.3);

  //chaosmaps.rate(3.7);
  chaosmaps.mode(AudioSynthChaosMaps::LOGISTIC);  //LOGISTIC or NFOLD
  chaosmaps.rate(2.0); 
  // when set to a "doubling" map of 2, the cycle repeats creating looping patterns. 
  // when sampling rate is low this can be used for drum triggers
  // dont use rate modulation when doing this
  
  chaosmaps.seed(0.9323343);
  showMemStats = false; // set to true to show CPU usage stats

  AudioInterrupts();
}

void loop() {

  if (showMemStats) {
    memStats();
  }
  
  pot01.update();
  pot02.update();
  pot03.update();
  pot04.update();
  pot05.update();
  pot06.update();
  pot07.update();

  // seed
  seedValue = mapf(pot01.getValue(), 0, 1023, 0.0, 1.0);
  if (seedValue != prevSeedValue){
    chaosmaps.seed(seedValue); // seed amount, dont set repeatidly
  }
  prevSeedValue = seedValue;


  // rate
  //chaosmaps.rate(mapf(pot02.getValue(), 0, 1023, 3.6, 4.0)); // rate amount, chaos is between 3.6 and 4.0
  chaosmaps.rate(mapf(pot02.getValue(), 0, 1023, 1.0, 4.0)); // "doubling amount", should be more than 1

  // sample rate
  chaosmaps.sampleRate(mapf(pot03.getValue(), 0, 1023, 0.0, AUDIO_SAMPLE_RATE_EXACT)); 
  //chaosmaps.sampleRate(fscale( 0.094, 1023.0, 0.0, 8000, pot03.getValue(), -6.5));

  // LFO 1, controls rate modulation
  mixer.gain(0, mapf(pot04.getValue(), 0, 1023, 0.0, 1.0)); // LFO amp
  lfo1.frequency(mapf(pot05.getValue(), 0, 1023, 0, 10.0)); // LFO freq

  // LFO 2, controls samplerate modulation
  mixer2.gain(0, mapf(pot06.getValue(), 0, 1023, 0.0, 1.0)); // LFO amp
  lfo2.frequency(mapf(pot07.getValue(), 0, 1023, 0, 10.0)); // LFO freq
}


// floating point map function taken from https://forum.arduino.cc/index.php?topic=361046.0
double mapf(double x, double in_min, double in_max, double out_min, double out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void memStats() {
  // Returns an estimate of the total CPU time used during the most recent audio library update.
  // The number is a number from 0 to 100, representing an estimate of the percentage of the total CPU time consumed.

  Serial.print("TOTAL CPU = ");
  Serial.print(AudioProcessorUsage());
  Serial.println("%");

  Serial.print("TOTAL CPU MAX = ");
  Serial.print(AudioProcessorUsageMax());
  Serial.println("%");

  Serial.print("logistic map CPU = ");
  Serial.print(chaosmaps.processorUsage());
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
