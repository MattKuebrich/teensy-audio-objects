/* Audio Library for Teensy, Chaos Noise
 * Copyright (c) 2023, Matt Kuebrich
 *  
 * This is adapted on Paul Batchelor's chaosNoise algorithm from his sndkit audio toolkit
 * (https://pbat.ch/sndkit/chaosnoise/) as well as Michael Hetrick's Crackle VCV Rack module.
 * (https://github.com/mhetrick/hetrickcv/blob/master/src/Crackle.cpp).
 *  
 * Both of which are originally based on the Crackle UGen in Supercollider
 * (https://doc.sccode.org/Classes/Crackle.html).
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

#include "synth_chaosnoise.h"

void AudioSynthChaosNoise::update(void) {
  audio_block_t *block;

  block = allocate();
  if (block == NULL) return;

  switch (chaosSel) {
    case CLASSIC:
      for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++) {
        phs += floor(sampleRate * maxlens);
        if (phs >= PHSMAX) {
          phs &= PHSMSK;

          float y_new;
          y_new = fabs(chaosAmt * y0 - y1 - 0.05);
          y1 = y0;
          y0 = y_new;
        }
        block->data[i] = y0 * 32767;
      }
      break;

    case BROKEN:
      for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++) {
        phs += floor(sampleRate * maxlens);
        float y0 = fabs(y1 * chaosAmt - y2 - 0.05f);

        if (phs >= PHSMAX) {
          phs &= PHSMSK;
          y2 = y1;
        }
        y1 = lasty1;
        lasty1 = constrain(y0, -1.0f, 1.0f);
        block->data[i] = y0 * 32767;
      }
      break;
  }

  transmit(block);
  release(block);
}
