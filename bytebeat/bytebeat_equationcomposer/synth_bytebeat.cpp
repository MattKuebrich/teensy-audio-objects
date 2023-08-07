/* Audio Library for Teensy, Bytebeat
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
 
#include "synth_bytebeat.h"

void AudioSynthBytebeat::update(void) {
  audio_block_t *block;

  block = allocate();
  if (block == NULL) return;

  for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++) {

    if (reversePlayback) {
      w = bytebeatFormula(abs(t) / (AUDIO_SAMPLE_RATE / sr), w, p1, p2, p3);
      t--;
    } else {
      w = bytebeatFormula(abs(t) / (AUDIO_SAMPLE_RATE / sr), w, p1, p2, p3);
      t++; 
    }
        
    block->data[i] = ((w * 65535) / 255) - 32768;

  }

  transmit(block);
  release(block);
}
