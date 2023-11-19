/* STK Instrmnt / STK Effect example
  
  This sketch enables the ModalBar (struck bar) instrument with 5 voice polyphony and control over its parameters. 
  The ModalBar instrument (along with WGBanded and Shakers) are unique to STK as they have internal presets.
  The output is passed through a reverb, the STK Effect JCRev.

  When uploading, use Arduino IDE / Teensyduino. Under Tools -> USB Type, it should be set to "Serial + MIDI + Audio".
  Adjust the potentiometer pins to match your setup. The ResponsiveAnalogRead and Bounce libraries are also used. 
  This was tested using a Teensy 4.1.

  You can play the instruments via usbMIDI, use the pushbutton to trigger a note or use the trigger input.

  As these are struck instruments, I've disabled noteOff() so they ring out. Other instruments (like Clarinet) 
  require a noteOff() so they don't keep sounding indefinitely.
  
  Further information about ModalBar is here:
  https://ccrma.stanford.edu/software/stk/classstk_1_1ModalBar.html

  All the other instruments are commented out in setup(). Keep in mind you'll need to adjust the controlChange 
  assignments when trying out other instruments.
  
  POT01 = Cycles through presets, Marimba = 0, Vibraphone = 1, Agogo = 2, Wood1 = 3, Reso = 4, Wood2 = 5, Beats = 6, Two Fixed = 7, Clump = 8
  POT02 - Pitch Bend
  POT03 - Stick Hardness
  POT04 - Stick Position
  POT05 - Direct Stick mix
  
  BUTTON01 = Trigger noteOn()

*/

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <Bounce.h>
#include <ResponsiveAnalogRead.h>

#include "src/synth_stkinstrmnt.h"
#include "src/effect_stkeffect.h"

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

Bounce button1 = Bounce(33, 50); // 8 = 8 ms debounce time

float pot01Read;
float pot01Read_prev;
float pot02Read;
float pot03Read;
float pot04Read;
float pot05Read;

bool showMemStats = false;

AudioControlSGTL5000     sgtl5000_1;     //xy=1284,1411
AudioOutputI2S           i2s1;           //xy=792.8889045715332,396.22222328186035
AudioSynthStkInstrmnt StkInstrmnt;
AudioEffectStkEffect StkEffect;

AudioSynthWaveformModulated osc;      //xy=484.00001525878906,1270.

//Enable this to test the trigger input
//AudioConnection          patchCord17(osc, 0, StkInstrmnt, 0);

AudioConnection          patchCord18(StkInstrmnt, 0, StkEffect, 0);

AudioConnection          patchCord13(StkEffect, 0, i2s1, 0);
AudioConnection          patchCord14(StkEffect, 1, i2s1, 1);

AudioOutputUSB           usb_out;           //xy=792.8889045715332,396.22222328186035
AudioConnection          patchCord15(StkEffect, 0, usb_out, 0);
AudioConnection          patchCord16(StkEffect, 1, usb_out, 1);

// MIDI input, since StkInstrmnt takes freq as noteOn, these need to be converted from midi to freq and since amplitude comes in as 0 to 127, they need to divided down to 0 -m1.

float midiNoteToFrequency(float incoming_note) {
  return 220.0f * pow(2.0f, (incoming_note - 57.0f) / 12.0f);
}

void OnNoteOn(byte channel, byte note, byte velocity) {
  StkInstrmnt.noteOn(midiNoteToFrequency(note), velocity / 127.0); //trigger sk note, with (instrument, amplitude)
}

void OnNoteOff(byte channel, byte note, byte velocity) {
  // Disabled for ModalBar
  //StkInstrmnt.noteOff(midiNoteToFrequency(note), velocity / 127.0); //trigger sk note, with (instrument, amplitude)
}

void OnControlChange(byte channel, byte control, byte value) {
  StkInstrmnt.controlChange(control, value / 127.0); //trigger sk note, with (instrument, amplitude)
}

void setup() {

  AudioMemory(20);

  showMemStats = true; // set to true to show CPU usage stats
  
  // Configure the pushbutton pins
  pinMode(33, INPUT_PULLUP);
  
  usbMIDI.setHandleNoteOff(OnNoteOff);
  usbMIDI.setHandleNoteOn(OnNoteOn) ;
  usbMIDI.setHandleControlChange(OnControlChange);

  AudioNoInterrupts();

  sgtl5000_1.enable();
  sgtl5000_1.volume(1.0);

  osc.begin(1.0,3, WAVEFORM_SQUARE);
  StkEffect.begin(JCREV); //mono in, stereo out
  StkEffect.mix(0.1); //mono in, stereo out


  // Set instrument name and number of voices, optional decay in sec
  
  //StkInstrmnt.begin(BANDEDWG,2); //this doesn't work with pitchBend
  //StkInstrmnt.begin(BEETHREE,7);
  //StkInstrmnt.begin(BLOWBOTL,3);
  //StkInstrmnt.begin(BLOWHOLE,3);
  //StkInstrmnt.begin(BOWED,3);
  //StkInstrmnt.begin(BRASS,3);
  //StkInstrmnt.begin(CLARINET,3);
  //StkInstrmnt.begin(DRUMMER,3);
  //StkInstrmnt.begin(FLUTE,3);
  //StkInstrmnt.begin(FMVOICES,3);
  //StkInstrmnt.begin(HEVYMETL,3);
  //StkInstrmnt.begin(MANDOLIN,5,8); 
  //StkInstrmnt.begin(MESH2D,3);
  StkInstrmnt.begin(MODALBAR,5);
  //StkInstrmnt.begin(MOOG,3);
  //StkInstrmnt.begin(PERCFLUT,3);
  //StkInstrmnt.begin(PLUCKED,3); 
  //StkInstrmnt.begin(RECORDER,3);
  //StkInstrmnt.begin(RESONATE,3);
  //StkInstrmnt.begin(RHODEY,3);
  //StkInstrmnt.begin(SAXOFONY,3);
  //StkInstrmnt.begin(SHAKERS,3);
  //StkInstrmnt.begin(SIMPLE,3);
  //StkInstrmnt.begin(SITAR,2);
  //StkInstrmnt.begin(STIFKARP,3); 
  //StkInstrmnt.begin(TUBEBELL,3); 
  //StkInstrmnt.begin(VOICFORM,3);
  //StkInstrmnt.begin(WHISTLE,3);
  //StkInstrmnt.begin(WURLEY,3,3);
  //StkInstrmnt.begin(KRSTLCHR,4);
  //StkInstrmnt.begin(FRENCHRN,4,3);
  //StkInstrmnt.begin(HNKYTONK,3,3);
  //StkInstrmnt.begin(LATELYB,5,5);
  //StkInstrmnt.begin(GUITAR,3);

  StkInstrmnt.volume(0.8); //adjust so it's not clipping

  AudioInterrupts();
}

void loop() {

  if (showMemStats) {
    memStats();
  }

  usbMIDI.read();

  pot01.update();
  pot02.update();
  pot03.update();
  pot04.update();
  pot05.update();

  button1.update();

  pot01Read = map(pot01.getValue(), 0, 1023, 0, 8); // preset
  pot02Read = mapf(pot02.getValue(), 0, 1023, -1.0, 1.0); // pitchbend
  pot03Read = mapf(pot03.getValue(), 0, 1023, 0.0, 1.0); // stick hardness
  pot04Read = mapf(pot04.getValue(), 0, 1023, 0.0, 1.0); // stick position
  pot05Read = mapf(pot05.getValue(), 0, 1023, 0.0, 1.0); // stick direct mix

  if (pot01Read != pot01Read_prev){
  // setting the preset resets all other parameters, so we only want to set this after a new preset is selected
  StkInstrmnt.controlChange(16, pot01Read); // set preset
}

  pot01Read_prev = pot01Read;

  StkInstrmnt.pitchBend(pot02Read); // pitchbend
  StkInstrmnt.controlChange(2, pot03Read); // stick hardness
  StkInstrmnt.controlChange(4, pot04Read); // stick position  
  StkInstrmnt.controlChange(1, pot05Read); // stick direct mix (STK documentation says this should be 8, but that doesn't work)


  if (button1.fallingEdge()) {
    Serial.println("Note triggered!");
    StkInstrmnt.noteOn(220.0, 0.78); // start a note with frequency in Hz and amplitude from 0 to 1.0.

  }

  if (button1.risingEdge()) { 
    //StkInstrmnt.noteOff(220.0, 0.5); // stop a note with the given amplitude (speed of decay) from 0 to 1.0. The speed of decay doesn't seem to do much FYI.
  }
  

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

  Serial.print("STKINSTRMNT CPU = ");
  Serial.print(StkInstrmnt.processorUsage());
  Serial.println("%");

  Serial.print("AUDIOMEMORY = ");
  Serial.println(AudioMemoryUsage());

  Serial.print("AUDIOMEMORY MAX = ");
  Serial.println(AudioMemoryUsageMax());
  Serial.println("");
}
