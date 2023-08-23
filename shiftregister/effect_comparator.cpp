/* Audio Library for Teensy, Comparator
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
#include "effect_comparator.h"

void AudioEffectComparator::update(void)
{
  audio_block_t *blocka, *blockb;

  blocka = receiveWritable(0);
  blockb = receiveReadOnly(1);

  if (!blocka) {
    if (blockb) release(blockb);
    return;
  }
  if (!blockb) {
    release(blocka);
    return;
  }

  for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++) {
    
    int16_t a = blocka->data[i];
    int16_t b = blockb->data[i];

    //LESS
    if (compareMode == 0){
    if(a < b){a = 32767;}
    else {a = 0;}
    }

    //GREATER
    if (compareMode == 1){
    if(a > b){a = 32767;}
    else {a = 0;}
    }

    //EQUAL
    if (compareMode == 2){
    if(a == b){a = 32767;}
    else {a = 0;}
    }

    //NOT_EQUAL
    if (compareMode == 3){
    if(a != b){a = 32767;}
    else {a = 0;}
    }

    blocka->data[i] = a;
  
  }
  transmit(blocka);
  release(blocka);
  release(blockb);
}
