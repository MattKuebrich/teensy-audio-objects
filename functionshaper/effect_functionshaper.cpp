/* Audio Library for Teensy, Function Shaper
 * Copyright (c) 2023, Matt Kuebrich
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
#include "effect_functionshaper.h"

void AudioEffectFunctionShaper::update(void)
{
  audio_block_t *block;

  block = receiveWritable();
  // if (!block) return;

  if (nullptr == block) // null block received, treat as silence:
  {
    block = allocate();                           // get block to write to
    if (nullptr != block)                         // allocated OK...
      memset(block->data, 0, sizeof block->data); // ...fill with silence
  }

  if (nullptr != block)
  {
    if (nullptr != shaper) // guard against unset shaper function
    {
      for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++)
      {
        float x, adjustedGain, out;
        x = (float)block->data[i] / 32768.0f; // scale to -1.0 to 1.0
        r = shaper(x * inGain, r, a, b, c) + dcOffset;
        out = r * muGain; // makeup gain not included in r

        if (limiterEnabled)
        {
          if (abs(r) > limit)
          {
            // Enough gain to bring it below the limit
            adjustedGain = limit / abs(r);
          }
          else
          {
            // Otherwise, leave it alone (gain of 1)
            adjustedGain = 1;
          }
        }
        else
        {
          adjustedGain = 1;
        }

        float mixed = x + (out * adjustedGain - x) * wetdrymix; // crossfade based on mix
        int16_t mixedOutput = (int16_t)(mixed * 32768.0f);      // scale back to -32768 to 32767

        block->data[i] = mixedOutput;
      }
    }
    transmit(block);
    release(block);
  }
  else
  {
    if (nullptr != shaper) // guard against unset shaper function
    {
      for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++) // ensure shaper keeps up-to-date state
        r = shaper(0.0f, r, a, b, c);
    }
    // nothing to transmit, we don't have a block
  }
}
