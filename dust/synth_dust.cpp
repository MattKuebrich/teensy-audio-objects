/* Audio Library for Teensy, Dust
 * Copyright (c) 2023, Matt Kuebrich
 *
 * This was adapted from Michael Hetrick's Dust VCV Rack module 
 * (https://github.com/mhetrick/hetrickcv/blob/master/src/Dust.cpp), 
 * which was based on the Dust UGen in Supercollider 
 * (https://doc.sccode.org/Classes/Dust.html).
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

#include "synth_dust.h"

void AudioSynthDust::update(void) {
  audio_block_t *block, *moddata;

  block = allocate();
  moddata = receiveReadOnly();

  if (!block) return;

  for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++) {
    if (moddata) {
      destinyMod = (float)moddata->data[i] / 32768.0f; //scale to -1.0 to 1.0
      release(moddata);
    }

    float densityInput = desnsityIn + destinyMod;

    if (lastDensity != densityInput)
    {
      //changed this so the density input values can be 0.0 to 1.0, rather than 0.0 to 4.0
      densityScaled = fastPow(densityInput, 3.0f) * AUDIO_SAMPLE_RATE; //using fastPow to speed things up
      lastDensity = densityInput;
      threshold = 1.0 / AUDIO_SAMPLE_RATE * densityScaled;
    }

    float noiseValue = rand() / (float) RAND_MAX;

    if (noiseValue < threshold) {
      if (unipolar) {
        float scale = threshold > 0.0 ? 1.0 / threshold : 0.0;
        block->data[i] = clamp(noiseValue * scale * MAX_AMPLITUDE, MIN_AMPLITUDE, MAX_AMPLITUDE);

      } else {
        float scale = threshold > 0.0 ? 2.0 / threshold : 0.0;
        block->data[i] = clamp((noiseValue * scale - 1.0) * MAX_AMPLITUDE, MIN_AMPLITUDE, MAX_AMPLITUDE);
      }
    } else {
      block->data[i] = 0;
    }
  }

  transmit(block);
  release(block);
  if (moddata) release(moddata);
}
