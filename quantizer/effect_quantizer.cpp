/* Audio Library for Teensy, Quantizer
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

#include "effect_quantizer.h"

void AudioEffectQuantizer::update() {
audio_block_t *block;
block = receiveWritable();

if (!block) return;
if (!inputScale) return;

for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++) {
float input = (float)block->data[i] / 3276.7f; // Convert to 0 to 10 range

    // Quantizer code below based on Jeremy Wentworth's VCV Rack Quantizer
    // https://github.com/jeremywen/JW-Modules/blob/master/src/QuantizeUtils.cpp
    // BSD 3-Clause License
    // Copyright (c) 2017, Jeremy Wentworth 
    // All rights reserved.

    float closestVal = 10.0;
    float closestDist = 10.0;
    float scaleNoteInVolts = 0;
    float distAway = 0;
    int rootNote = 0;
    int octaveInVolts = int(floorf(input));
    float voltMinusOct = input - octaveInVolts;

    for (int i = 0; i < noteCount; i++) {
      scaleNoteInVolts = inputScale[i] / 12.0;
      distAway = fabs(voltMinusOct - scaleNoteInVolts);
      if (distAway < closestDist) {
        closestVal = scaleNoteInVolts;
        closestDist = distAway;
      }
    };

    float quantizedOutput = octaveInVolts + octaveShift + rootNote / 12.0 + closestVal;

    block->data[i] = (int16_t)(quantizedOutput * 3276.7f); // Convert back to int16_t range
  }

  transmit(block);
  release(block);
}
