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
 
#ifndef effect_bernoulligate_h_
#define effect_bernoulligate_h_

#include <Arduino.h>
#include "AudioStream.h"

class AudioEffectBernoulliGate : public AudioStream
{
  public:

    AudioEffectBernoulliGate() : AudioStream(1, inputQueueArray) { }
    virtual void update(void);

    void probability(float p) {
      if (p < 0.0) {
        p = 0.0;
      } else if (p > 1.0) {
        p = 1.0;
      }
      prob = p;
    }

  private:
    audio_block_t *inputQueueArray[1];
    float prob = 0.5;
    int choice;
};

#endif