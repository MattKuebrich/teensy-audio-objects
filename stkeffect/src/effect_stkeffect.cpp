/* Audio Library for Teensy, STK Effect

   The Synthesis ToolKit in C++ (STK) by Perry R. Cook & Gary P. Scavone
   The Synthesis ToolKit in C++ (STK) Library for Arduino by Phil Schatzmann
   STK Effect audio object for Teensy by Matt Kuebrich
   
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
#include "effect_stkeffect.h"

void AudioEffectStkEffect::update(void) {

    audio_block_t *blocka = receiveWritable(0); 
    audio_block_t *blockb = receiveWritable(1); 

    if (!blocka && !blockb) {
        return;
    }

    // if only blocka or blockb is received, allocate a silent block for the missing one.
    if (!blocka) {
        blocka = allocate();
        if (!blocka) return;
        memset(blocka->data, 0, sizeof(blocka->data)); // silent
    } else if (!blockb) {
        blockb = allocate();
        if (!blockb) {
            release(blocka);
            return; 
        }
        memset(blockb->data, 0, sizeof(blockb->data)); // silent
    }

    StkFrames frames(AUDIO_BLOCK_SAMPLES, 2);

    for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++) {
        frames(i, 0) = (float)blocka->data[i] / 32768.0f;  // scale input to -1.0 to 1.0
        frames(i, 1) = (float)blockb->data[i] / 32768.0f;  // scale input to -1.0 to 1.0
    }

    effect->tick(frames,0);

    for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++) {
        
 // mono in / mono out
  if (selectedEffect == ECHO || selectedEffect == PITSHIFT || selectedEffect == LENTPITSHIFT){
        blocka->data[i] = frames(i, 0) * 32767.0; 
        blockb->data[i] = frames(i, 0) * 32767.0; //mirror mono in both channels
 // stereo in / stereo out        
  } else if (selectedEffect == FREEVERB || CHORUS) { 
        blocka->data[i] = frames(i, 0) * 32767.0; 
        blockb->data[i] = frames(i, 1) * 32767.0; 
  } else {
// mono in / stereo out    
        blocka->data[i] = frames(i, 0) * 32767.0; 
        blockb->data[i] = frames(i, 1) * 32767.0; 
  }
    }
  transmit(blocka, 0);
  transmit(blockb, 1);
  release(blocka);
  release(blockb);
}







