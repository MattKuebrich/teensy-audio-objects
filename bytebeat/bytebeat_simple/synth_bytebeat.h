/* Audio Library for Teensy, Bytebeat
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

#ifndef synth_bytebeat_h_
#define synth_bytebeat_h_

#include <Audio.h>

class AudioSynthBytebeat : public AudioStream {
  public:
    AudioSynthBytebeat() : AudioStream(0, NULL) {
      t = 0;
      sr = 8000;
    }

    void formula(uint32_t (*bytebeatFormula)(uint32_t, uint8_t, uint32_t, uint32_t, uint32_t)) { this->bytebeatFormula = bytebeatFormula; }
    void sampleRate(float sr) { this->sr = sr; }
    void reverse(bool reversePlayback) { this->reversePlayback = reversePlayback; }
    void reset(void) {t = 0;}
    void parameter1(uint32_t p1) { this->p1 = p1; }
    void parameter2(uint32_t p2) { this->p2 = p2; }
    void parameter3(uint32_t p3) { this->p3 = p3; }
    virtual void update(void);

  private:
    uint32_t (*bytebeatFormula)(uint32_t, uint8_t, uint32_t, uint32_t, uint32_t);
    uint32_t t;
    uint32_t p1, p2, p3;
    uint32_t sr;
    uint8_t w;
    bool reversePlayback = false;
};

#endif
