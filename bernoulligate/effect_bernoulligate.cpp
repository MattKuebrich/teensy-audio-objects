/* Audio Library for Teensy, Bernoulli Gate
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
 
#include "effect_bernoulligate.h"

void AudioEffectBernoulliGate::update(void) {
  audio_block_t *blocka;
  blocka = receiveWritable(0);

  if (!blocka) {
    return;
  }

  audio_block_t *blockb;
  blockb = allocate();
  if (!blockb) {
    release(blocka);
    return;
  }

  int32_t gate = 0;
  int32_t gate_prev = 0;

  for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++) {
    int32_t a = blocka->data[i];
    gate = (a > 0) ? 32767 : -32768;

    if (gate_prev > 0 && gate <= 0) {
      choice = (random(100) <= prob * 100) ? 0 : 1;
    }

    blocka->data[i] = (choice == 1) ? gate : -32768;
    blockb->data[i] = (choice == 1) ? -32768 : gate;

    gate_prev = gate;
  }

  transmit(blocka, 0);
  transmit(blockb, 1);
  release(blocka);
  release(blockb);
}
