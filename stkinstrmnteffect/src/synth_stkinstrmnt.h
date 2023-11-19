/* Audio Library for Teensy, STK Instrmnt

   The Synthesis ToolKit in C++ (STK) by Perry R. Cook & Gary P. Scavone
   The Synthesis ToolKit in C++ (STK) Library for Arduino by Phil Schatzmann
   STK Instrmnt audio object for Teensy by Matt Kuebrich

   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files (the "Software"), to deal
   in the Software without restriction, including without limitation the rights
   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
   copies of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:

   The above copyright notice, development funding notice, and this permission
   notice shall be included in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
   THE SOFTWARE.
*/

#ifndef synth_stkinstrmnt_h_
#define synth_stkinstrmnt_h_

#include <Arduino.h>
#include "AudioStream.h"
#include "StkAll.h"

enum Instruments {
  BANDEDWG,
  BEETHREE,
  BLOWBOTL,
  BLOWHOLE,
  BOWED,
  BRASS,
  CLARINET,
  DRUMMER,
  FLUTE,
  FMVOICES,
  HEVYMETL,
  MANDOLIN,
  MESH2D,
  MODALBAR,
  MOOG,
  PERCFLUT,
  PLUCKED,
  RECORDER,
  RESONATE,
  RHODEY,
  SAXOFONY,
  SHAKERS,
  SIMPLE,
  SITAR,
  STIFKARP,
  TUBEBELL,
  VOICFORM,
  WHISTLE,
  WURLEY,
  KRSTLCHR,
  FRENCHRN,
  HNKYTONK,
  LATELYB,
  GUITAR
};

class AudioSynthStkInstrmnt : public AudioStream {

  public:

    // can make notes ring out with higher decay time in voicer
    AudioSynthStkInstrmnt() : AudioStream(1, inputQueueArray), voicer(0.2), voicerGuitar(0.2) {
    }

    void begin(Instruments type, int voices, float decayTime = 0.2) {
      voicer = Voicer(decayTime); //optional decay value for letting notes ring out for a number of seconds
      numVoices = voices;
      Instrmnt *instrument[numVoices];
      Guitar *instrumentGuitar[numVoices];

      voicer.volume(0.5); // set default voicer volume

      // This makes sure the instrument is only set once
      if (!instrumentSet) {

        for (int i = 0; i < numVoices; i++) {
          if (type == BANDEDWG) {
            instrument[i] = new BandedWG();
            hasPresets = true;
          } else if (type == BEETHREE) {
            instrument[i] = new BeeThree();
          } else if (type == BLOWBOTL) {
            instrument[i] = new BlowBotl();
          } else if (type == BLOWHOLE) {
            instrument[i] = new BlowHole(10.0);
          } else if (type == BOWED) {
            instrument[i] = new Bowed(10.0);
          } else if (type == BRASS) {
            instrument[i] = new Brass(10.0);
          } else if (type == CLARINET) {
            instrument[i] = new Clarinet(10.0);
          } else if (type == DRUMMER) {
            instrument[i] = new Drummer();
          } else if (type == FLUTE) {
            instrument[i] = new Flute(10.0);
          } else if (type == FMVOICES) {
            instrument[i] = new FMVoices();
          } else if (type == HEVYMETL) {
            instrument[i] = new HevyMetl();
          } else if (type == MANDOLIN) {
            //instrument[i] = new Mandolin(5.0); //this was from the STK file demo.cpp, but causes limited polyphony
            instrument[i] = new Mandolin(20.0);
          } else if (type == MESH2D) {
            instrument[i] = new Mesh2D(10, 10);
          } else if (type == MODALBAR) {
            instrument[i] = new ModalBar();
            hasPresets = true;
          } else if (type == MOOG) {
            instrument[i] = new Moog();
          } else if (type == PERCFLUT) {
            instrument[i] = new PercFlut();
          } else if (type == PLUCKED) {
            instrument[i] = new Plucked(5.0);
          } else if (type == RECORDER) {
            instrument[i] = new Recorder();
          } else if (type == RESONATE) {
            instrument[i] = new Resonate();
          } else if (type == RHODEY) {
            instrument[i] = new Rhodey();
          } else if (type == SAXOFONY) {
            instrument[i] = new Saxofony(10.0);
          } else if (type == SHAKERS) {
            instrument[i] = new Shakers();
            hasPresets = true;
          } else if (type == SIMPLE) {
            instrument[i] = new Simple();
          } else if (type == SITAR) {
            instrument[i] = new Sitar(5.0);
          } else if (type == STIFKARP) {
            instrument[i] = new StifKarp(5.0);
          } else if (type == TUBEBELL) {
            instrument[i] = new TubeBell();
          } else if (type == VOICFORM) {
            instrument[i] = new VoicForm();
          } else if (type == WHISTLE) {
            instrument[i] = new Whistle();
          } else if (type == WURLEY) {
            instrument[i] = new Wurley();
          } else if (type == KRSTLCHR) {
            instrument[i] = new KrstlChr();
          } else if (type == FRENCHRN) {
            instrument[i] = new FrencHrn();
          } else if (type == HNKYTONK) {
            instrument[i] = new HnkyTonk();
          } else if (type == LATELYB) {
            instrument[i] = new LatelyB();
          } else if (type == GUITAR) {
            instrumentGuitar[i] = new Guitar(1);
            guitarSelected = true;
          }

          if  (guitarSelected) {
            voicerGuitar.addInstrument(instrumentGuitar[i]); //add selected instrument the voicer
          } else {
            voicer.addInstrument(instrument[i]); //add selected instrument the voicer
          }
        }
        instrumentSet = true;
      }
    }

    float frequencyToMidiNote(float frequency) {
      return 12.0f * (log2f(frequency) - log2f(220.0f)) + 57.0f;
    }

    void noteOn(float frequency, float amplitude) {

      if (!instrumentSet && !guitarSelected) {
        Serial.println("Please set an instrument using begin()!");
        return;
      }

      if (guitarSelected) {
        voicerGuitar.noteOn(frequencyToMidiNote(frequency), amplitude * 128.0);
      } else {
        voicer.noteOn(frequencyToMidiNote(frequency), amplitude * 128.0);
      }
    }

    void noteOff(float frequency, float amplitude) {
      if (guitarSelected) {
        voicerGuitar.noteOff(frequencyToMidiNote(frequency), amplitude * 128.0);
        //voicerGuitar.noteOff(frequencyToMidiNote(frequency), (amplitude * 128.0/6.67) *-1.0);  //hacky code to get a value of -0.0 to -0.15. This helped the decay work, but idk why.
      } else {
        voicer.noteOff(frequencyToMidiNote(frequency), amplitude * 128.0);
      }
    }

    void frequency(float frequency) {
      if (guitarSelected) {
        voicerGuitar.setFrequency(frequencyToMidiNote(frequency));
      } else {
        voicer.setFrequency(frequencyToMidiNote(frequency));
      }
    }

    void volume(float volume) {
      voicer.volume(volume);
    }

    void pitchBend(float pitchbend) {
      // convert to -1.0 to 1.0 (octaves), rather than the 0 to 16383 MIDI pitch bend values.
      if (guitarSelected) {
        voicerGuitar.pitchBend(8191.5f * (pitchbend + 1.0f));
      } else {
        voicer.pitchBend(8191.5f * (pitchbend + 1.0f));
      }
    }

    void silence() {
      // send a noteOff message to all existing voices.
      if (guitarSelected) {
        voicerGuitar.silence();
      } else {
        voicer.silence();

      }
    }

    void controlChange(int number, float value) {
      if (guitarSelected) {
        voicerGuitar.controlChange(number, value * 128.0); // 128 (not 127) is correct for this.
      } else {
        if (hasPresets && (number == 16 || number == 1071)){
        //if ((hasPresets) && (number == 16)){
        voicer.controlChange(number, int(value)); // MODALBAR, BANDEDWG and SHAKERS use int presets which need to be set directly
        }else {
        voicer.controlChange(number, value * 128.0); // 128 (not 127) is correct for this.
        }
      }
    }

    int activeVoices() {
      if (guitarSelected) {
        return voicerGuitar.getNumActiveVoices();
      } else {
        return voicer.getNumActiveVoices();
      }
    }

    virtual void update(void);

  private:
    audio_block_t *inputQueueArray[1];
    Voicer voicer;
    VoicerGuitar voicerGuitar;
    int i;
    int numVoices = 3; // default voices
    bool instrumentSet = false; // initialize a flag to track if begin() has run
    bool guitarSelected = false;
    bool hasPresets = false;

    float instrumentVol = 0.5;
    int16_t _clk;
    int16_t _prev_clk;
    int16_t clkin;
    int16_t trig = 0;
    int16_t noteOnTrig;
    int16_t prevnoteOnTrig;
    int16_t triggerThreshold = 0.2 * 32767.0f; ; //a typical 2 "volts" threshold, if we consider the whole range a 10v p2p signal
};

#endif
