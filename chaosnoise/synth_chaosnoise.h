/* Audio Library for Teensy, Chaos Noise
 * Copyright (c) 2023, Matt Kuebrich
 *  
 * This is adapted on Paul Batchelor's chaosNoise algorithm from his sndkit audio toolkit
 * (https://pbat.ch/sndkit/chaosnoise/) as well as Michael Hetrick's Crackle VCV Rack module.
 * (https://github.com/mhetrick/hetrickcv/blob/master/src/Crackle.cpp).
 *  
 * Both of which are originally based on the Crackle UGen in Supercollider
 * (https://doc.sccode.org/Classes/Crackle.html).
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

#ifndef synth_chaosnoise_h_
#define synth_chaosnoise_h_

#include <Arduino.h>
#include "AudioStream.h"

#define PHSMAX 0x1000000L
#define PHSMSK 0x0FFFFFFL

#define CLASSIC         0
#define BROKEN          1

class AudioSynthChaosNoise : public AudioStream {
public:
    AudioSynthChaosNoise() : AudioStream(0, NULL) { }

  void chaos(float chaosAmt) { this->chaosAmt = chaosAmt + 1.0;} //shift to the expected 1.0 to 2.0 range
  void rate(float sampleRate) { this->sampleRate = sampleRate; }
  void mode(float chaosMode) {this->chaosMode = chaosMode;}

  virtual void update(void);

private:
  float chaosAmt = 1.5; // default value
  float sampleRate = AUDIO_SAMPLE_RATE; // default value
  float y0 = 0.5; //init
  float y1, y2;
  uint32_t phs = 0;
  float lasty1 = 0.2643f;
  float maxlens = PHSMAX / AUDIO_SAMPLE_RATE;
  short chaosMode = 0;
};

#endif
