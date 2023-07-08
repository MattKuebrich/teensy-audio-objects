/* Audio Library for Teensy, Sample and Hold
 * Copyright (c) 2023, Matt Kuebrich / John-Michael Reed
 *  
 * Based on code from John-Michael Reed (bleeplabs.com) from:
 * https://forum.pjrc.com/threads/29227-Rate-Reduction-effect-for-audio-h-code-and-questions?p=78290&viewfull=1#post78290
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice, development funding notice, and this permission
 * notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include <Arduino.h>
#include "effect_samplehold.h"

void AudioEffectSampleAndHold::update(void)
{

  audio_block_t *blocka, *blockb;
  int16_t *pa, *pb, *end;
  static short change;

  blocka = receiveWritable(0); // input
  blockb = receiveReadOnly(1); // trigger

  if (!blocka) {
    if (blockb) release(blockb);
    return;
  }
  if (!blockb) {
    release(blocka);
    return;
  }

  pa = (int16_t *)(blocka->data);
  pb = (int16_t *)(blockb->data);

  end = (pa + AUDIO_BLOCK_SAMPLES);

  while (pa < end) {

    audioInPrev = audioIn;
    trigPrev = trig;
    trig = *pb++;

    if (trigPrev >= 0 && trig < 0) {
      change = 1;
    }
    
    else {
      change = 0;
    }

    if (change == 1) {
      audioIn = *pa;
    }

    if (change == 0) {
      audioIn = audioInPrev;
    }
    *pa++ = audioIn;
  }

  transmit(blocka);
  release(blocka);
  release(blockb);

}
