/* Audio Library for Teensy, Gate to Trigger
   Copyright (c) 2023, Matt Kuebrich

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

#ifndef effect_gatetotrigger_h_
#define effect_gatetotrigger_h_

#include <Audio.h>

#define START        0
#define END          1
#define BOTH         2

class AudioEffectGateToTrigger : public AudioStream {
  public:
    AudioEffectGateToTrigger() : AudioStream(1, inputQueueArray)
    {
      duration(1); // a typical 1ms trigger length
      threshold(0.2); // a typical 2 "volts" threshold, if we consider the whole range a 10v p2p signal
      edge(START); // trigger on the start of the gate (rising edge)
    }

    virtual void update(void);

    void duration(float d) {
      triggerDurationSamples = d * (AUDIO_SAMPLE_RATE_EXACT / 1000.0f);
    }

    void threshold(float t) {
      if (t < 0.0f) t = 0;
      else if (t > 1.0f) t = 1.0f;
      triggerThreshold = t * 32767.0f;
    }

    void edge(float edgeMode) {
      this->edgeMode = edgeMode;
    }

  private:
    audio_block_t *inputQueueArray[1];
    int32_t triggerValue = 32767; //full "10v" trigger, use half this for a "5V" trigger
    int32_t triggerThreshold;
    int triggerDurationSamples;
    bool gateState;
    int triggerCounter;
    bool prevGateState;
    short edgeMode = 0;
};

#endif
