#ifndef STK_LATELYB_H
#define STK_LATELYB_H

#include "FM.h"

namespace stk {

/***************************************************/
/*! \class LatelyB
    \brief NEW STK-style Lately Bass FM synthesis instrument.

    This class implements 3 cascade operators with
    feedback modulation, also referred to as
    algorithm 2 of the TX81Z.

    Algorithm 2 is: 
    
    ____4--\
    3--+-->>2-->1-->Out

    Control Change Numbers:
        - Total Modulator Index = 2
        - Modulator Crossfade = 4
        - LFO Speed = 11
        - LFO Depth = 1
        - ADSR 2 & 4 Target = 128

    The basic Chowning/Stanford FM patent expired
    in 1995, but there exist follow-on patents,
    mostly assigned to Yamaha. If you are of the
    type who should worry about this (making
    money) worry away.

    by Perry R. Cook, 2021.
 */
/***************************************************/

class LatelyB : public FM
{
 public:
  //! Class constructor.
  /*!
    An StkError will be thrown if the rawwave path is incorrectly set.
  */
  LatelyB( void );

  //! Class destructor.
  ~LatelyB( void );

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

inline StkFloat LatelyB :: tick( unsigned int )
{

    /* register */ StkFloat temp, temp2;

    temp2 = vibrato_.tick(); // save for AM /***** REPAIRATHON2021 HACK *****/

    temp = temp2 * modDepth_ * 0.2;

    for (int i = 0; i < 4; i++)  {
        if (ratios_[i] > 0.0) {
            waves_[i]->setFrequency(baseFrequency_ * (1.0 + temp) * ratios_[i]);
        }
    }

    waves_[3]->addPhaseOffset(twozero_.lastOut()); // Operator 4
    temp = (1.0 + opAMs[3]*temp2) * control2_ * 0.5 * gains_[3] * adsr_[3]->tick() * waves_[3]->tick(); // ADDED AM
    twozero_.tick(temp);
    temp = temp * control2_;

    temp += (1.0 + opAMs[2]*temp2) * control1_ * 0.5 * gains_[2] * adsr_[2]->tick() * waves_[2]->tick(); // Operator 3 // ADDED AM too

    waves_[1]->addPhaseOffset(temp);                // Operator 2
    temp = (1.0 + opAMs[1]*temp2) * gains_[1] * adsr_[1]->tick() * waves_[1]->tick(); // ADDED AM
    temp = temp * 0.5 * (control1_ + control2_);
    //  temp = temp * control1_;

    waves_[0]->addPhaseOffset(temp);            // Operator 1
    temp = (1.0 + opAMs[0]*temp2) * gains_[0] * adsr_[0]->tick() * waves_[0]->tick(); // ADDED AM

    lastFrame_[0] = temp;
    return lastFrame_[0];
}

inline StkFrames& LatelyB :: tick( StkFrames& frames, unsigned int channel )
{
  unsigned int nChannels = lastFrame_.channels();
#if defined(_STK_DEBUG_)
  if ( channel > frames.channels() - nChannels ) {
    oStream_ << "LatelyB::tick(): channel and StkFrames arguments are incompatible!";
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
