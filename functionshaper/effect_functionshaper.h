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

#ifndef AudioEffectFunctionShaper_h
#define AudioEffectFunctionShaper_h

#include <Arduino.h>
#include "AudioStream.h"

class AudioEffectFunctionShaper : public AudioStream
{
  public:

    AudioEffectFunctionShaper() : AudioStream(1, inputQueueArray) { }
    virtual void update(void);
    void functionShaper(float (*shaper)(float, float, float, float, float)) { this->shaper = shaper; }
    void inputGain(float inGain) { this->inGain = inGain; }
    void makeupGain(float muGain) { this->muGain = muGain; }
    void parameterA(float a) { this->a = a; }
    void parameterB(float b) { this->b = b; }
    void parameterC(float c) { this->c = c; }
    void mix(float wetdrymix) { this->wetdrymix = wetdrymix; }
    void offset(float dcOffset) { this->dcOffset = dcOffset; }
    void enableLimiter(bool limiterEnabled) { this->limiterEnabled = limiterEnabled; }
    void limiterThreshold(float limit) { this->limit = limit; }

  private:
    audio_block_t *inputQueueArray[1];
    float inGain = 1.0;
    float muGain = 1.0;
    float a = 0.0;
    float b = 0.0;
    float c = 0.0;
    float wetdrymix = 1.0;
    float r = 0.0;
    float limit = 1.0;
    float dcOffset = 0.0;
    bool limiterEnabled = false;
    float (*shaper)(float, float, float, float, float);
};

#endif
