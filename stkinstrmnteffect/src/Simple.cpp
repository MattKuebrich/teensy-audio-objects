/***************************************************/
/*! \class Simple
    \brief STK wavetable/noise instrument.

    This class combines a looped wave, a
    noise source, a biquad resonance filter,
    a one-pole filter, and an ADSR envelope
    to create some interesting sounds.

    Control Change Numbers: 
       - Filter Pole Position = 2
       - Noise/Pitched Cross-Fade = 4
       - Envelope Rate = 11
       - Gain = 128

    by Perry R. Cook and Gary P. Scavone, 1995--2019.
*/
/***************************************************/

#include "Simple.h"
#include "SKINImsg.h"

namespace stk {

Simple :: Simple( void )
{
  #ifdef __RAW_ARRAYS__
    loop_ = new MemoryLoop( Stk::rawwavePath() + "impuls10.raw", impuls10_raw, impuls10_raw_len );
  #else
    // Concatenate the STK rawwave path to the rawwave file
    loop_ = new FileLoop( Stk::rawwavePath() + "impuls10.raw", true );
  #endif

  filter_.setPole( 0.5 );
  baseFrequency_ = 440.0;
  setFrequency( baseFrequency_ );
  loopGain_ = 0.5;
}  

Simple :: ~Simple( void )
{
  delete loop_;
}

void Simple :: keyOn( void )
{
  adsr_.keyOn();
}

void Simple :: keyOff( void )
{
  adsr_.keyOff();
}

void Simple :: noteOn( StkFloat frequency, StkFloat amplitude )
{
  this->keyOn();
  this->setFrequency( frequency );
  filter_.setGain( amplitude ); 
}
void Simple :: noteOff( StkFloat amplitude )
{
  this->keyOff();
}

void Simple :: setFrequency( StkFloat frequency )
{
#if defined(_STK_DEBUG_)
  if ( frequency <= 0.0 ) {
    oStream_ << "Simple::setFrequency: argument is less than or equal to zero!";
    handleError( StkError::WARNING ); return;
  }
#endif

  biquad_.setResonance( frequency, 0.98, true );
  loop_->setFrequency( frequency );
}

void Simple :: controlChange( int number, StkFloat value )
{
#if defined(_STK_DEBUG_)
  if ( Stk::inRange( value, 0.0, 128.0 ) == false ) {
    oStream_ << "Simple::controlChange: value (" << value << ") is out of range!";
    handleError( StkError::WARNING ); return;
  }
#endif

  StkFloat normalizedValue = value * ONE_OVER_128;
  if (number == __SK_Breath_) // 2
    filter_.setPole( 0.99f * (1.0f - (normalizedValue * 2.0f)) );
  else if (number == __SK_NoiseLevel_) // 4
    loopGain_ = normalizedValue;
  else if (number == __SK_ModFrequency_) { // 11
    normalizedValue /= 0.2f * Stk::sampleRate();
    adsr_.setAttackRate( normalizedValue );
    adsr_.setDecayRate( normalizedValue );
    adsr_.setReleaseRate( normalizedValue );
  }
  else if (number == __SK_AfterTouch_Cont_) // 128
    adsr_.setTarget( normalizedValue );
#if defined(_STK_DEBUG_)
  else {
    oStream_ << "Simple::controlChange: undefined control number (" << number << ")!";
    handleError( StkError::WARNING );
  }
#endif
}

} // stk namespace
