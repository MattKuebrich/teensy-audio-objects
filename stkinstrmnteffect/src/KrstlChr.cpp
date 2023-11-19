//-----------------------------------------------------------------------------
// 1.4.1.0 ***** REPAIRATHON2021 BRAND NEW FM ALGORITHMS!!! *****
//-----------------------------------------------------------------------------

/***************************************************/
/*! \class KrstlChr
    \brief New STK-style "Crystal Choir" FM synthesis instrument.

    This class implements 3 parallel operators with
    one modulated, by one with feedback modulation,
    also referred to as algorithm 7 of the TX81Z.

    Algorithm 3 is: 4-->3-->\
                        2--> + -->Out
                        1-->/

    Control Change Numbers:
       - Total Modulator Index = 2
       - Modulator Crossfade = 4
       - LFO Speed = 11
       - LFO Depth = 1
       - adsr_ 2 & 4 Target = 128

    The basic Chowning/Stanford FM patent expired
    in 1995, but there exist follow-on patents,
    mostly assigned to Yamaha. If you are of the
    type who should worry about this (making
    money) worry away.

    by Perry R. Cook, 2021.
 */
/***************************************************/

#include "KrstlChr.h"

namespace stk {

KrstlChr :: KrstlChr( void )
  : FM()
{
  #ifdef __RAW_ARRAYS__
  waves_[0] = new MemoryLoop( Stk::rawwavePath() + "sineblnk.raw", sineblnk_raw,sineblnk_raw_len);
  waves_[1] = new MemoryLoop( Stk::rawwavePath() + "snglpeak.raw", snglpeak_raw,snglpeak_raw_len);
  waves_[2] = new MemoryLoop( Stk::rawwavePath() + "sinewave.raw", sinewave_raw,sinewave_raw_len);
  waves_[3] = new MemoryLoop( Stk::rawwavePath() + "snglpeak.raw", snglpeak_raw,snglpeak_raw_len);
  #else
  // Concatenate the STK rawwave path to the rawwave files
  waves_[0] = new FileLoop( Stk::rawwavePath() + "sineblnk.raw", true );
  waves_[1] = new FileLoop( Stk::rawwavePath() + "snglpeak.raw", true );
  waves_[2] = new FileLoop( Stk::rawwavePath() + "sinewave.raw", true );
  waves_[3] = new FileLoop( Stk::rawwavePath() + "snglpeak.raw", true );
  #endif


    //  this->setRatio(0, 1.50); // This is what PatchBase editor says
    //  this->setRatio(1, 1.51); // Factory bank 1761 is
    //  this->setRatio(2, 1.49); // but I think that's shit
    //  this->setRatio(3, 8.63);

    this->setRatio(0, 1.00);
    this->setRatio(1, 0.99);
    this->setRatio(2, 1.01);
    this->setRatio(3, 8.63);

    gains_[0] = fmGains_[99];
    gains_[1] = fmGains_[99];
    gains_[2] = fmGains_[89];
    gains_[3] = fmGains_[77]; // Factory Bank 1761 says 67

    baseGains[0] = gains_[0];
    baseGains[1] = gains_[1];
    baseGains[2] = gains_[2];
    baseGains[3] = gains_[3];

    adsr_[0]->setAllTimes( fmAttTimes_[14], fmAttTimes_[8], 1.0, fmAttTimes_[5]);
    adsr_[1]->setAllTimes( fmAttTimes_[11], fmAttTimes_[8], 1.0, fmAttTimes_[7]);
    adsr_[2]->setAllTimes( fmAttTimes_[15], fmAttTimes_[7], 1.0, fmAttTimes_[7]);
    adsr_[3]->setAllTimes( fmAttTimes_[31], fmAttTimes_[0], 1.0, fmAttTimes_[4]);

    twozero_.setGain( 2.0 ); // Op4 Feedback
    op4Feedback = 2.0;
    vibrato_.setFrequency( 3.5 );
    modDepth_ = 0.02;

}  

KrstlChr :: ~KrstlChr( void )
{
}

void KrstlChr :: noteOn( StkFloat frequency, StkFloat amplitude )
{
    gains_[0] = amplitude * baseGains[0]; /***** REPAIRATHON2021 *****/
    gains_[1] = amplitude * baseGains[1];
    gains_[2] = amplitude * baseGains[2];
    gains_[3] = amplitude * baseGains[3];

    this->setFrequency(frequency);
    this->keyOn();
}

} // stk namespace
