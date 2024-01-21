/* Audio Library for Teensy, Chaos Maps
 * Copyright (c) 2024, Matt Kuebrich
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

#include "synth_chaosmaps.h"

void AudioSynthChaosMaps::update(void) {
  audio_block_t *block, *moddata, *moddata2;

  block = allocate();
  if (!block) return;

  moddata = receiveReadOnly(0);
  moddata2 = receiveReadOnly(1);

  for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++) {


    if (moddata) {
      rateMod = ((moddata->data[i] + 32768) / 65536.0f) + 0.5f;
      release(moddata);
      moddata = NULL; //this fixes AudioMemory going crazy high
    }

    if (moddata2) {
      //srateMod = (float)moddata2->data[i] / 32768.0f; //scale to -1.0 to 1.0, causes downsample rate to go negative, sounds cool :)
      srateMod = (moddata2->data[i] + 32768) / 65536.0f; //scale to 0.0 to 1.0
      release(moddata2);
      moddata2 = NULL;
    }

    srateIn2 = srateIn * srateMod;

    if (downsample_index % int(AUDIO_SAMPLE_RATE_EXACT / (srateIn2)) == 0) {

      rateIn2 = rateIn * rateMod; // modulate growth rate
      //rateIn2 = constrain(rateIn2, 0.001, 4.0); // ?
      rateIn2 = constrain(rateIn2, 1.0, 3.99); // limit range, don't go to zero or it'll die off

      if (seedIn <= 0.0) {
        //Serial.print("repeat");
        seedIn = seedInit; //if stabalized, repeat using initial seed value, only seems to happen using 2.0 as rate (a proper doubling map)
      }

      seedIn = constrain(seedIn, 0.0, 1.0);

      if (modeIn == LOGISTIC) {
        // logistic map
        seedIn = (constrain(rateIn2, 3.0, 4.0) * seedIn) * (1 - seedIn);
      } else if (modeIn == NFOLD) {
        // n-fold map
        seedIn = fmod(seedIn * rateIn2, 1.0);
      }

      out = int(seedIn * 65536) - 32768; //scale
    }

    block->data[i] = out;

    downsample_index++;

    if (downsample_index >= AUDIO_SAMPLE_RATE) {
      downsample_index = 0;
    }
  }

  transmit(block);
  release(block);
  if (moddata) release(moddata);
  if (moddata2) release(moddata2);

}
