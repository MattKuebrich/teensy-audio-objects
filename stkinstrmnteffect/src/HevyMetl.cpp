/***************************************************/
/*! \class HevyMetl
    \brief STK heavy metal FM synthesis instrument.

    This class implements 3 cascade operators with
    feedback modulation, also referred to as
    algorithm 3 of the TX81Z.

    Algorithm 3 is :     4--\
                    3-->2-- + -->1-->Out

    Control Change Numbers: 
       - Total Modulator Index = 2
       - Modulator Crossfade = 4
       - LFO Speed = 11
       - LFO Depth = 1
       - ADSR 2 & 4 Target = 128

    The basic Chowning/Stanford FM patent expired
    in 1995, but there exist follow-on patents,
    mostly assigned to Yamaha.  If you are of the
    type who should worry about this (making
    money) worry away.

    by Perry R. Cook and Gary P. Scavone, 1995--2019.
*/
/***************************************************/

#include "HevyMetl.h"

// #ifdef __RAW_ARRAYS__
//   extern const unsigned char *fwavblnk_raw, *sinewave_raw;
//   extern unsigned int fwavblnk_raw_len,sinewave_raw_len;
// #endif

namespace stk {

HevyMetl :: HevyMetl( void )
  : FM()
{
  #ifdef __RAW_ARRAYS__
    for ( unsigned int i=0; i<3; i++ )
    waves_[i] = new MemoryLoop( Stk::rawwavePath() + "sinewave.raw", sinewave_raw,sinewave_raw_len );
  waves_[3] = new MemoryLoop( Stk::rawwavePath() + "fwavblnk.raw", fwavblnk_raw,fwavblnk_raw_len);
  #else
  // Concatenate the STK rawwave path to the rawwave files
  for ( unsigned int i=0; i<3; i++ )
    waves_[i] = new FileLoop( Stk::rawwavePath() + "sinewave.raw", true );
  waves_[3] = new FileLoop( Stk::rawwavePath() + "fwavblnk.raw", true );
  #endif

  this->setRatio(0, 1.0 * 1.000);
  this->setRatio(1, 4.0 * 0.999);
  this->setRatio(2, 3.0 * 1.001);
  this->setRatio(3, 0.5 * 1.002);

  gains_[0] = fmGains_[92];
  gains_[1] = fmGains_[76];
  gains_[2] = fmGains_[91];
  gains_[3] = fmGains_[68];

// MK this doesn't seem to make sense that these are all set to gains_[0] ??
  baseGains[0] = gains_[0];  // 1.4.1.0 ***** REPAIRATHON2021 ADDITIONS *****
  baseGains[1] = gains_[0];
  baseGains[2] = gains_[0];
  baseGains[3] = gains_[0];

  adsr_[0]->setAllTimes( 0.001, 0.001, 1.0, 0.01);
  adsr_[1]->setAllTimes( 0.001, 0.010, 1.0, 0.50);
  adsr_[2]->setAllTimes( 0.010, 0.005, 1.0, 0.20);
  adsr_[3]->setAllTimes( 0.030, 0.010, 0.2, 0.20);

  twozero_.setGain( 2.0 );
  op4Feedback = 2.0; // 1.4.1.0
  vibrato_.setFrequency( 5.5 );
  modDepth_ = 0.0;
}  

HevyMetl :: ~HevyMetl( void )
{
}

void HevyMetl :: noteOn( StkFloat frequency, StkFloat amplitude )
{
  // 1.4.1.0 ***** REPAIRATHON2021 CHANGESS *****
  gains_[0] = amplitude * baseGains[0];
  gains_[1] = amplitude * baseGains[1];
  gains_[2] = amplitude * baseGains[2];
  gains_[3] = amplitude * baseGains[3];

  this->setFrequency( frequency );
  this->keyOn();
}

} // stk namespace
