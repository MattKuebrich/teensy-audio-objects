/* wav2int16 example

  This is a simple example that shows how to use an arbitrary waveforms in the 
  Teensy Audio Library's AudioSynthWaveformModulated object. The data here was generated using the wav2int python script.

  POT01 = Oscillator frequency
  
*/

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

#define POT01 14
#define MAX_FREQ 1200    // max frequency for arbitraryWaveform(array, maxFreq); 

const int16_t analogsine[257] = {
-73, 410, 894, 1377, 1862, 2349, 2841, 3338, 3838, 4339, 4837, 5327, 5804, 6263, 6706, 7139, 7574, 8027, 8519, 9066, 9682, 10373, 11141, 11980, 12883, 13843, 14849, 15894, 16969, 18065, 19173, 20282, 21383, 22466, 23520, 24536, 25507, 26427, 27289, 28089, 28825, 29494, 30098, 30634, 31106, 31513, 31859, 32145, 32374, 32548, 32669, 32741, 32766, 32747, 32684, 32579, 32432, 32243, 32011, 31739, 31429, 31087, 30723, 30343, 29957, 29568, 29181, 28795, 28409, 28023, 27637, 27252, 26874, 26508, 26156, 25821, 25501, 25191, 24887, 24585, 24284, 23983, 23683, 23388, 23097, 22809, 22520, 22222, 21908, 21571, 21202, 20800, 20361, 19886, 19374, 18827, 18244, 17626, 16970, 16275, 15542, 14768, 13952, 13094, 12192, 11246, 10254, 9218, 8138, 7014, 5850, 4648, 3413, 2150, 866, -431, -1734, -3033, -4318, -5581, -6811, -8003, -9148, -10239, -11268, -12225, -13099, -13882, -14569, -15162, -15669, -16106, -16490, -16841, -17173, -17498, -17821, -18145, -18470, -18792, -19108, -19415, -19712, -19997, -20272, -20538, -20793, -21038, -21271, -21490, -21696, -21888, -22068, -22237, -22396, -22544, -22680, -22803, -22912, -23006, -23088, -23157, -23215, -23264, -23303, -23332, -23349, -23354, -23346, -23325, -23292, -23247, -23192, -23128, -23055, -22974, -22884, -22784, -22675, -22557, -22429, -22291, -22144, -21987, -21821, -21647, -21464, -21271, -21069, -20858, -20637, -20407, -20170, -19928, -19684, -19438, -19193, -18950, -18708, -18468, -18232, -17999, -17772, -17549, -17331, -17117, -16906, -16698, -16493, -16290, -16088, -15887, -15684, -15477, -15264, -15044, -14816, -14579, -14334, -14082, -13821, -13553, -13277, -12994, -12702, -12403, -12096, -11782, -11461, -11134, -10801, -10463, -10120, -9772, -9418, -9057, -8689, -8312, -7927, -7534, -7136, -6732, -6324, -5912, -5496, -5074, -4645, -4209, -3767, -3319, -2866, -2407, -1943, -1474, -1004, -535, -73
};

// GUItool: begin automatically generated code
AudioControlSGTL5000     sgtl5000_1;     //xy=1284,1411
AudioOutputI2S           i2s1;           //xy=792.8889045715332,396.22222328186035
AudioSynthWaveformModulated osc;      //xy=484.00001525878906,1270.
AudioConnection          patchCord1(osc, 0, i2s1, 0);
AudioConnection          patchCord2(osc, 0, i2s1, 1);

//USB for testing
//AudioOutputUSB           usb_out;           //xy=792.8889045715332,396.22222328186035
//AudioConnection          patchCord3(osc, 0, usb_out, 0);
//AudioConnection          patchCord4(osc, 0, usb_out, 1);

// GUItool: end automatically generated code

void setup() {
  AudioNoInterrupts();
  AudioMemory(20);
  Serial.begin(9600);
  osc.begin(0.5, 150, WAVEFORM_ARBITRARY); 
  osc.arbitraryWaveform(analogsine, MAX_FREQ); // MAX_FREQ is currently ignored in the AudioSynthWaveformModulated object
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.4);
  AudioInterrupts();
}

void loop() {
  osc.frequency(mapf(analogRead(POT01), 0, 1023, 0.0, 300));
}

// floating point map function taken from https://forum.arduino.cc/index.php?topic=361046.0
double mapf(double x, double in_min, double in_max, double out_min, double out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
