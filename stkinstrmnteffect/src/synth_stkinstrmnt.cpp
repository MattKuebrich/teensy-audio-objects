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

// taken from ArdConfig.cpp, dummy functions so it will compile
extern "C" int _open() {return -1;}
extern "C" int _stat() {return -1;}
extern "C" int _gettimeofday() {return -1;}

#include "synth_stkinstrmnt.h"

void AudioSynthStkInstrmnt::update(void) {
  audio_block_t *block, *trigInput;
  trigInput = receiveReadOnly();
  block = allocate();

  // Release the block if allocation failed
  if (!block) {
    if (trigInput) {
      release(trigInput);
    }
    return;
  }

  for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++) {

    // I just set the note for external trigger to be 60 (C3).
    // This is complicated because CV to MIDI can mean note, gate, or velocity.

    if (noteOnTrig) {
      voicer.noteOn(60.0, 100.0);
    }

    if (trigInput) {
      clkin = trigInput->data[i];
      release(trigInput);
    } else {
      clkin = 0;
      // if no trigInput, the trigger equals, the noteOn();
      trig = noteOnTrig;
      noteOnTrig = 0;
    }

    if (clkin > triggerThreshold) {
      trig = 1;
    } else {
      trig = 0;
    }

    // this ensures the note is triggered from the trigInput or noteOn()
    if ((!trig && _prev_clk) || (noteOnTrig != prevnoteOnTrig)) {
      voicer.noteOn(60.0, 100.0);
    }

    else if (trig && _prev_clk) { 
      voicer.noteOff(60.0, 64.0, 0);
}

    _prev_clk = trig;
    prevnoteOnTrig = noteOnTrig;

    if (guitarSelected) {
      float guitarSample = voicerGuitar.tick();
      //clip peaks to avoid nasty digital distortion
      if (guitarSample > 0.99f) {
        guitarSample = 0.99f;
      } else if (guitarSample < -0.99f) {
        guitarSample = -0.99f;
      }
      block->data[i] = static_cast<int16_t>((guitarSample * instrumentVol) * 32767.0);
    } else {
      float sample = voicer.tick();
      //clip peaks to avoid nasty digital distortion
      if (sample > 0.99f) {
        sample = 0.99f;
      } else if (sample < -0.99f) {
        sample = -0.99f;
      }
      
      // this works but isn't a great way to avoid clipping
      //block->data[i] = static_cast<int16_t>((sample * instrumentVol) * 32767.0)/ activeVoices();
      block->data[i] = static_cast<int16_t>((sample * instrumentVol) * 32767.0);
    }

  }

  noteOnTrig = 0; // reset trig for noteOn to work
  transmit(block);
  release(block);
}