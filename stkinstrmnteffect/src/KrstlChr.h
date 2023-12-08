#ifndef STK_KRSTLCHR_H
#define STK_KRSTLCHR_H

#include "FM.h"

namespace stk {

/***************************************************/
/*! \class KrstlChr
 \brief New STK-style Crystal Choir FM synthesis instrument.

 This class implements 3 parallel operators with
 one modulated, by one with feedback modulation,
 also referred to as algorithm 7 of the TX81Z.

Algorithm 7 is :
    
    1 -\
    2 - +-> Out 
    4-->3 -/ 
    

 Control Change Numbers:
 - Total Modulator Index = 2
 - Modulator Crossfade = 4
 - LFO Speed = 11
 - LFO Depth = 1
 - adsr_ 2 & 4 Target = 128

 The basic Chowning/Stanford FM patent expired
 in 1995, but there exist follow-on patents,
 mostly assigned to Yamaha.  If you are of the
 type who should worry about this (making
 money) worry away.

 by Perry R. Cook, 2021.
 */
/***************************************************/

class KrstlChr : public FM
{
 public:
  //! Class constructor.
  /*!
    An StkError will be thrown if the rawwave path is incorrectly set.
  */
  KrstlChr( void );

  //! Class destructor.
  ~KrstlChr( void );

  //! Start a note with the given frequency and amplitude.
  void noteOn( StkFloat frequency, StkFloat amplitude );

  //! Compute and return one output sample.
  StkFloat tick( unsigned int channel = 0 );

  //! Fill a channel of the StkFrames object with computed outputs.
  /*!
    The \c channel argument must be less than the number of
    channels in the StkFrames argument (the first channel is specified
    by 0).  However, range checking is only performed if _STK_DEBUG_
    is defined during compilation, in which case an out-of-range value
    will trigger an StkError exception.
  */
  StkFrames& tick( StkFrames& frames, unsigned int channel = 0 );

 protected:

};

inline StkFloat KrstlChr :: tick( unsigned int )
{
    /* register */ StkFloat temp, temp2;

    temp2 = vibrato_.tick() * modDepth_ * 0.2; // Save for AM

    temp = vibrato_.tick() * modDepth_ * 0.2;
  
  
    for (int i = 0; i < 4; i++)  {
        if (ratios_[i] > 0.0) {
            waves_[i]->setFrequency(baseFrequency_ * (1.0 + temp) * ratios_[i]);
        }
    }

    waves_[3]->addPhaseOffset(twozero_.lastOut());
    
    twozero_.tick(temp);
    temp = (1.0 + opAMs[3]*temp2) * gains_[3] * adsr_[3]->tick() * waves_[3]->tick(); // Add AM

    waves_[2]->addPhaseOffset(temp);

    temp = (1.0 + opAMs[2]*temp2 - (control2_ * 0.5)) * gains_[2] * adsr_[2]->tick() * waves_[2]->tick(); // Add AM
    temp += (1.0 + opAMs[1]*temp2) * control2_ * (StkFloat) 0.5 * gains_[1] * adsr_[1]->tick() * waves_[1]->tick(); // Add AM
    temp = temp * control1_;
    temp += (1.0 + opAMs[0]*temp2) * gains_[0] * adsr_[0]->tick() * waves_[0]->tick();  // Add AM

    lastFrame_[0] = temp * 0.5;
    return lastFrame_[0];
}

inline StkFrames& KrstlChr :: tick( StkFrames& frames, unsigned int channel )
{
  unsigned int nChannels = lastFrame_.channels();
#if defined(_STK_DEBUG_)
  if ( channel > frames.channels() - nChannels ) {
    oStream_ << "KrstlChr::tick(): channel and StkFrames arguments are incompatible!";
    handleError( StkError::FUNCTION_ARGUMENT );
  }
#endif

  StkFloat *samples = &frames[channel];
  unsigned int j, hop = frames.channels() - nChannels;
  if ( nChannels == 1 ) {
    for ( unsigned int i=0; i<frames.frames(); i++, samples += hop )
      *samples++ = tick();
  }
  else {
    for ( unsigned int i=0; i<frames.frames(); i++, samples += hop ) {
      *samples++ = tick();
      for ( j=1; j<nChannels; j++ )
        *samples++ = lastFrame_[j];
    }
  }

  return frames;
}

} // stk namespace

#endif
