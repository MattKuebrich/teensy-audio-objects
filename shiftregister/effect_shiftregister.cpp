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

#include <Arduino.h>
#include "effect_shiftregister.h"

void AudioEffectShiftRegister::update(void)
{

  audio_block_t *blocka, *blockb, *block0, *block1, *block2, *block3, *block4, *block5, *block6, *block7;
  int16_t *pa, *pb, *p0, *p1, *p2, *p3, *p4, *p5, *p6, *p7, *end;
  static short change;
  uint16_t dacOut, bit0, bit1, bit2, bit3, bit4, bit5, bit6, bit7;
  uint16_t selectedOut;

  blocka = receiveWritable(0);
  blockb = receiveReadOnly(1);

  if (!blocka) {
    if (blockb) release(blockb);
    return;
  }
  if (!blockb) {
    release(blocka);
    return;
  }

  block0 = allocate();
  if (!block0) return;
  block1 = allocate();
  if (!block1) return;
  block2 = allocate();
  if (!block2) return;
  block3 = allocate();
  if (!block3) return;
  block4 = allocate();
  if (!block4) return;
  block5 = allocate();
  if (!block5) return;
  block6 = allocate();
  if (!block6) return;
  block7 = allocate();
  if (!block7) return;

  pa = (int16_t *)(blocka->data);
  pb = (int16_t *)(blockb->data);
  p0 = (int16_t *)(block0->data);
  p1 = (int16_t *)(block1->data);
  p2 = (int16_t *)(block2->data);
  p3 = (int16_t *)(block3->data);
  p4 = (int16_t *)(block4->data);
  p5 = (int16_t *)(block5->data);
  p6 = (int16_t *)(block6->data);
  p7 = (int16_t *)(block7->data);
  audioIn = *pa;

  end = (pa + AUDIO_BLOCK_SAMPLES);

  while (pa < end) {

    prevTrig = trig;
    trig = *pb++;

    if (prevTrig >= 0 && trig < 0) {
      change = 1;
    }

    else {
      change = 0;
    }

    if (change == 1 && audioIn >= 0) { // if clock and audio are both high...
      srByte = srByte << 1; //we shift bit...

      // Trying to have the input be XOR'd with the last stage of the shift register, as in the rungler. 
      // I'm not sure if this is working correctly, but you can sometimes hear a difference.
      
      if (xorOn) {
        xorResult = bitRead(srByte, 7) ^ (audioIn >= 0);
      } else {
        xorResult = audioIn;
      }

      if (loopOn) {
        bitWrite(srByte, 0, bitRead(srByte, 7)); //loop enable, take last bit and connect it to first
      } else {
        bitWrite(srByte, 0, xorResult); //then write new 1 bit to srByte
      }
    }

    if (change == 1 && audioIn < 0) { //if clock if high, but audio is not
      srByte = srByte << 1; //shift bit..

      if (loopOn) {
        bitWrite(srByte, 0, bitRead(srByte, 7)); //loop enable, take last bit and connect it to first
      } else {
        bitWrite(srByte, 0, 0); //then write new 0 bit to srByte
      }

    }

    // this prints out every bit from srByte, for debugging.
    //for ( int8_t i = 7; i >= 0; i-- )
    //  Serial.print( bitRead( srByte, i ) );

/*
    //4bit dac ala double knot
    bitWrite(dacOut, 0, bitRead(srByte, 0));
    bitWrite(dacOut, 1, bitRead(srByte, 1));
    bitWrite(dacOut, 2, bitRead(srByte, 2));
    bitWrite(dacOut, 3, bitRead(srByte, 3));
*/

    //3bit dac ala rungler
    bitWrite(dacOut, 0, bitRead(srByte, 5));
    bitWrite(dacOut, 1, bitRead(srByte, 6));
    bitWrite(dacOut, 2, bitRead(srByte, 7));

    selectedOut = map(dacOut, 0, 7, 0, 32767); 

    bit0 = map(bitRead(srByte, 0), 0, 1, 0, 32767);
    bit1 = map(bitRead(srByte, 1), 0, 1, 0, 32767);
    bit2 = map(bitRead(srByte, 2), 0, 1, 0, 32767);
    bit3 = map(bitRead(srByte, 3), 0, 1, 0, 32767);
    bit4 = map(bitRead(srByte, 4), 0, 1, 0, 32767);
    bit5 = map(bitRead(srByte, 5), 0, 1, 0, 32767);
    bit6 = map(bitRead(srByte, 6), 0, 1, 0, 32767);
    bit7 = map(bitRead(srByte, 7), 0, 1, 0, 32767);

    *pa++ = selectedOut;
    *p0++ = bit0;
    *p1++ = bit1;
    *p2++ = bit2;
    *p3++ = bit3;
    *p4++ = bit4;
    *p5++ = bit5;
    *p6++ = bit6;
    *p7++ = bit7;
  }

  transmit(blocka, 8);
  transmit(block0, 0);
  transmit(block1, 1);
  transmit(block2, 2);
  transmit(block3, 3);
  transmit(block4, 4);
  transmit(block5, 5);
  transmit(block6, 6);
  transmit(block7, 7);


  release(blocka);
  release(blockb);
  release(block0);
  release(block1);
  release(block2);
  release(block3);
  release(block4);
  release(block5);
  release(block6);
  release(block7);
}
