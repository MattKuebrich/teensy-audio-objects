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


#ifndef effect_slewlimiter_h
#define effect_slewlimiter_h

#include <Arduino.h>
#include "AudioStream.h"

class AudioEffectSlewLimiter : public AudioStream
{
  public:
    AudioEffectSlewLimiter() : AudioStream(1, inputQueueArray) { }
    virtual void update(void);
    void rise(float rise_time) { this->rise_time = rise_time; }
    void fall(float fall_time) { this->fall_time = fall_time; }
   
  private:
    audio_block_t *inputQueueArray[1];
    float rise_time = 0.0f;
    float fall_time = 0.0f;
    float out;
    float last = 0.0f; 
};

#endif
