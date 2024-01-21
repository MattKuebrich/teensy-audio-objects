/* Audio Library for Teensy, Chaos Maps
 * Copyright (c) 2024, Matt Kuebrich
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

#ifndef synth_chaosmaps_h_
#define synth_chaosmaps_h_

#include <Arduino.h>
#include "AudioStream.h"

class AudioSynthChaosMaps : public AudioStream
{
  public:

    enum mapMode {
    LOGISTIC = 0,
    NFOLD  = 1,
    };
  
    AudioSynthChaosMaps() : AudioStream(2, inputQueueArray) {}

    virtual void update(void);
    void seed(float seedIn) {this->seedIn = seedIn; this->seedInit = seedIn;} // population size or "x"
    void rate(float rateIn) {this->rateIn = rateIn;} // growth rate or "r"
    void sampleRate(float srateIn) {this->srateIn = srateIn;}
    void mode(short modeIn) {this->modeIn = modeIn;}

  private:
    audio_block_t *inputQueueArray[2];
    float seedIn = 0.5122325;
    float seedInit;
    float rateIn = 3.6;
    float rateIn2;
    float srateIn = AUDIO_SAMPLE_RATE_EXACT;
    float srateIn2;
    float rateMod = 1.0; 
    float srateMod = 1.0;
    int downsample_index = 0;
    short modeIn = LOGISTIC;
    int out = 0;
};

#endif
