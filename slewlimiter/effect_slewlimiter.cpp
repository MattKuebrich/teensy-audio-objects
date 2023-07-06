/* Audio Library for Teensy, Slew Limiter
 * Copyright (c) 2023, Matt Kuebrich
 * Based on Ivan Cohen's simplified version of the Befaco Slew Limiter VCV Rack module.
 * https://forum.juce.com/t/adc17-fifty-shades-of-distortion-homework-part-2/25174
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

#include "effect_slewlimiter.h"

void AudioEffectSlewLimiter::update(void) {
  audio_block_t *block;

  block = receiveReadOnly(0);
  if (block == NULL) return;

  float slewMin = 0.1f;  // Minimum slope in volts per second
  float slewMax = 10000.f; // Maximum slope in volts per second

  float Ts = 1.0f / AUDIO_SAMPLE_RATE_EXACT;
  int16_t slewRise = (int16_t)(slewMax * Ts * powf(slewMin / slewMax, rise_time) * 32768.0f);
  int16_t slewFall = (int16_t)(slewMax * Ts * powf(slewMin / slewMax, fall_time) * 32768.0f);

  for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++) {
    int16_t input = block->data[i];

    if (input > last) {
      out = min(input, out + slewRise);
    }
    else {
      out = max(input, out - slewFall);
    }

    last = out;
    block->data[i] = out;
  }

  transmit(block);
  release(block);
}
