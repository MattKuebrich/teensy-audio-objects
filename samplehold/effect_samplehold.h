/* Audio Library for Teensy, Sample and Hold
   Copyright (c) 2023, Matt Kuebrich / John-Michael Reed
   Based on code from John-Michael Reed (bleeplabs.com) from:
   https://forum.pjrc.com/threads/29227-Rate-Reduction-effect-for-audio-h-code-and-questions?p=78290&viewfull=1#post78290

   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files (the "Software"), to deal
   in the Software without restriction, including without limitation the rights
   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
   copies of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:

   The above copyright notice, development funding notice, and this permission
   notice shall be included in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
   THE SOFTWARE.
*/

#ifndef effect_samplehold_h_
#define effect_samplehold_h_

#include <Arduino.h>
#include "AudioStream.h"

class AudioEffectSampleAndHold : public AudioStream
{
  public:
    AudioEffectSampleAndHold() : AudioStream(2, inputQueueArray) { }
    virtual void update(void);

  private:
    audio_block_t *inputQueueArray[2];
    int16_t prev_audio_in, audio_in, prev_trig, trig;

};

#endif
