/* Audio Library for Teensy, Gate to Trigger
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

#include "effect_gatetotrigger.h"

void AudioEffectGateToTrigger::update(void) {
  audio_block_t *block;
  block = receiveWritable(0);

  if (nullptr == block) // null block received, treat as silence:
  {
    block = allocate(); // get block to write to
    if (nullptr != block) // allocated OK...
      memset(block->data, 0, sizeof block->data); // ...fill with silence
  }

  if (nullptr != block)
  {
    switch (edgeSel) {
case START:
        for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++) {
          //trigger on gate START (rising edge)
          if (block->data[i] > triggerThreshold) {
            if (!gateState) {
              gateState = true;
              triggerCounter = triggerDurationSamples;
            }
            if (triggerCounter > 0) {
              block->data[i] = triggerValue;
              triggerCounter--;
            } else {
              block->data[i] = 0;
            }
          } else {
            gateState = false;
            block->data[i] = 0;
          }
        }
        break;

case END:
        for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++) {
          //trigger on gate END (falling edge)
          if (block->data[i] < -triggerThreshold) {
            if (gateState) {
              gateState = false;
              triggerCounter = triggerDurationSamples;
            }
            if (triggerCounter > 0) {
              block->data[i] = triggerValue;
              triggerCounter--;
            } else {
              block->data[i] = 0;
            }
          } else {
            gateState = true;
            block->data[i] = 0;
          }
        }
break;

case BOTH:

        for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++) {
          //trigger on BOTH (rising and falling edges)
          if (block->data[i] > triggerThreshold) {
            if (!gateState) {
              gateState = true;
              triggerCounter = triggerDurationSamples;
            }
            if (triggerCounter > 0) {
              block->data[i] = triggerValue;
              triggerCounter--;
            } else {
              block->data[i] = 0;
            }
          } else if (block->data[i] < triggerThreshold) {
            if (gateState) {
              gateState = false;
              triggerCounter = triggerDurationSamples;
            }
            if (triggerCounter > 0) {
              block->data[i] = triggerValue;
              triggerCounter--;
            } else {
              block->data[i] = 0;
            }
          } else {
            gateState = false;
            block->data[i] = 0;
          }
        }
        break;

    }

    transmit(block);
    release(block);
  }
}
