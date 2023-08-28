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

#ifndef synth_dust_h_
#define synth_dust_h_

#include <Arduino.h>
#include "AudioStream.h"

class AudioSynthDust : public AudioStream
{
  public:
    AudioSynthDust() : AudioStream(1, inputQueueArray) {}

    virtual void update(void);
    void density(float desnsityIn) {this->desnsityIn = desnsityIn;}
    void enableUnipolar(float unipolar) {this->unipolar = unipolar;}
    
    float clamp(float x, float a = 0.f, float b = 1.f) {
      return fmax(fmin(x, b), a);
    }

    double fastPow(double a, double b) // martin.ankerl.com
    {
      union {
        double d;
        int x[2];
      } u = { a };
      u.x[1] = (int)(b * (u.x[1] - 1072632447) + 1072632447);
      u.x[0] = 0;
      return u.d;
    }

  private:
    audio_block_t *inputQueueArray[1];
    const int MAX_AMPLITUDE = 32767;
    const int MIN_AMPLITUDE = -32768;
    float desnsityIn = 0.5;
    float destinyMod = 0.0;
    float lastDensity = 0.0;
    float densityScaled = 0.0;
    bool unipolar;


    float threshold = 0.0;
};

#endif
