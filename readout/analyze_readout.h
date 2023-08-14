 /* Audio Library for Teensy, Readout
 * Copyright (c) 2023, Matt Kuebrich
 * This is a modified version of the Peak audio object by Paul Stoffregen, paul@pjrc.com
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

#ifndef analyze_readout_h
#define analyze_readout_h

#include "Arduino.h"
#include "AudioStream.h"

class AudioAnalyzeReadout : public AudioStream
{
public:
	AudioAnalyzeReadout(void) : AudioStream(1, inputQueueArray) {}

  bool available(void) {
    __disable_irq();
    bool flag = new_output;
    if (flag) new_output = false;
    __enable_irq();
    return flag;
  }
  
  float read(void) {
    return (float)sample / 32767.0f;
  }
 
	virtual void update(void);
  
private:
	audio_block_t *inputQueueArray[1];
  volatile bool new_output;
  int16_t sample;
};

#endif
