/* Audio Library for Teensy, Shift Register
 * Copyright (c) 2023, Matt Kuebrich
 *  
 *  Sloppily based on Bastl's rungler code here: 
 *  https://github.com/bastl-instruments/one-chip-modules/blob/e3cfc6c9cfab16f935b851e349dfa706e0ca5aec/RUNGLER/RUNGLER.ino
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

#ifndef effect_shiftregister_h
#define effect_shiftregister_h
 
#include <Arduino.h>
#include "AudioStream.h"

class AudioEffectShiftRegister : public AudioStream
{
  public:

    AudioEffectShiftRegister() : AudioStream(2, inputQueueArray) { }

    virtual void update(void);

    void loopEnable(short loopOn) { this->loopOn = loopOn; }
    void xorEnable(short xorOn) { this->xorOn = xorOn; }

    int readBit0(void) {
      return bitRead(srByte, 0);
    }

    int readBit1(void) {
      return bitRead(srByte, 1);
    }

    int readBit2(void) {
      return bitRead(srByte, 2);
    }

    int readBit3(void) {
      return bitRead(srByte, 3);
    }

    int readBit4(void) {
      return bitRead(srByte, 4);
    }

    int readBit5(void) {
      return bitRead(srByte, 5);
    }

    int readBit6(void) {
      return bitRead(srByte, 6);
    }

    int readBit7(void) {
      return bitRead(srByte, 7);
    }

  private:
    audio_block_t *inputQueueArray[2];
    uint8_t srByte = 0; //byte used for 8 shift register bits
    short loopOn = 0;
    short xorOn = 0;
    int16_t audioIn, prevTrig, trig, xorResult;
    int16_t dacOut = 0;
};

#endif
