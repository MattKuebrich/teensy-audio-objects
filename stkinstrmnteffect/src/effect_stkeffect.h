/* Audio Library for Teensy, STK Effect

   The Synthesis ToolKit in C++ (STK) by Perry R. Cook & Gary P. Scavone
   The Synthesis ToolKit in C++ (STK) Library for Arduino by Phil Schatzmann
   STK Effect audio object for Teensy by Matt Kuebrich
   
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

#ifndef effect_stkeffect_h_
#define effect_stkeffect_h_

#include <Arduino.h>
#include "AudioStream.h"
#include "StkAll.h"

enum Effects {
  CHORUS,
  ECHO,
  FREEVERB,
  JCREV,
  LENTPITSHIFT,
  NREV,
  PRCREV,
  PITSHIFT
};

class AudioEffectStkEffect : public AudioStream {
        Effect* effect;


  public:


    AudioEffectStkEffect() : AudioStream(2, inputQueueArray) {
    }

    void begin(Effects type) {
      
      // This makes sure the instrument is only set once
      if (!effectSet) {
          selectedEffect = type; // Store the effect type

          if (type == CHORUS) {
            effect = new Chorus();
          } else if (type == ECHO) {
            effect = new Echo();
          } else if (type == FREEVERB) {
            effect = new FreeVerb();
          } else if (type == JCREV) {
            effect = new JCRev();          
          } else if (type == LENTPITSHIFT) {
            effect = new LentPitShift();
          } else if (type == NREV) {
            effect = new NRev();
          } else if (type == PRCREV) {
            effect = new PRCRev();          
          } else if (type == PITSHIFT) {
            effect = new PitShift();                    
          }
        effectSet = true;
      }
    }

    // CHORUS
    void modDepth(float moddepth){
    if (selectedEffect == CHORUS){
    static_cast<Chorus*>(effect)->setModDepth(moddepth); //between 0.0 and 1.0
    }
    }

    void modFrequency(float modfreq){
    if (selectedEffect == CHORUS){
    static_cast<Chorus*>(effect)->setModFrequency(modfreq); // freq
    }
    }

    // ECHO
    void delay(float delay){
    if (selectedEffect == ECHO){
    static_cast<Echo*>(effect)->setDelay(delay * AUDIO_SAMPLE_RATE); // in seconds
    }
    }

    void maxDelay(float maxdelay){
    if (selectedEffect == ECHO){
    static_cast<Echo*>(effect)->setMaximumDelay(maxdelay * AUDIO_SAMPLE_RATE); // in seconds
    }
    }

    // REVERBS
    void decay(float decay){
    
    if (selectedEffect == JCREV){
    static_cast<JCRev*>(effect)->setT60(decay); //in seconds
    }

    if (selectedEffect == NREV){
    static_cast<NRev*>(effect)->setT60(decay); //in seconds
    }

    if (selectedEffect == PRCREV){
    static_cast<PRCRev*>(effect)->setT60(decay); //in seconds
    }

  }

    // FREEVERB

    void damping(float damping){
    if (selectedEffect == FREEVERB){
    static_cast<FreeVerb*>(effect)->setDamping(damping); // 0.0 to 1.0
    }
    }

    void roomSize(float roomsize){
    if (selectedEffect == FREEVERB){
    static_cast<FreeVerb*>(effect)->setRoomSize(roomsize); // 0.0 to 1.0
    }
    }

    void width(float width){
    if (selectedEffect == FREEVERB){
    static_cast<FreeVerb*>(effect)->setWidth(width); // 0.0 to 1.0
    }
    }

    void mode(float mode){
    if (selectedEffect == FREEVERB){
    static_cast<FreeVerb*>(effect)->setMode(mode); //frozen = 1, unfrozen = 0
    }
    }

    // PITSHIFT
  
    void shift(float shift){
    if (selectedEffect == PITSHIFT){
    static_cast<PitShift*>(effect)->setShift(shift); //Set the pitch shift factor (1.0 produces no shift).
    }

    // LENTPITSHIFT

    if (selectedEffect == LENTPITSHIFT){
    //if(shift > 2.0) shift = 2.0;
    //else if(shift < 0.5) shift = 0.5;
    static_cast<LentPitShift*>(effect)->setShift(shift); //Set the pitch shift factor (1.0 produces no shift).
    }
    }

      void mix(float mix){
      //this is a function of the effect class
      effect->setEffectMix(mix); // 0.0 to 1.0
    }

      void clear(){
      //this is a function of the effect class
      effect->clear(); // Reset and clear all internal state.
    }

    virtual void update(void);

  private:
    audio_block_t *inputQueueArray[2];
    bool effectSet = false; // Initialize a flag to track if begin() has run
    Effects selectedEffect; 
};

#endif
