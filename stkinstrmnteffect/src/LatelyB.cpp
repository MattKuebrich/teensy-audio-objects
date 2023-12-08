//-----------------------------------------------------------------------------
// 1.4.1.0 ***** REPAIRATHON2021 BRAND NEW FM ALGORITHMS!!! *****
//-----------------------------------------------------------------------------

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

#include "LatelyB.h"

namespace stk {

LatelyB :: LatelyB( void )
  : FM()
{
  #ifdef __RAW_ARRAYS__
        // Concatenate the STK rawwave path to the rawwave files
        waves_[0] = new MemoryLoop( Stk::rawwavePath() + "sinewave.raw", sinewave_raw,sinewave_raw_len);
        waves_[1] = new MemoryLoop( Stk::rawwavePath() + "sinewave.raw", sinewave_raw,sinewave_raw_len);
        waves_[2] = new MemoryLoop( Stk::rawwavePath() + "sineblnk.raw", sineblnk_raw,sineblnk_raw_len);
        waves_[3] = new MemoryLoop( Stk::rawwavePath() + "sinewave.raw", sinewave_raw,sinewave_raw_len);
  #else
      // Concatenate the STK rawwave path to the rawwave files
    for( int i=0; i<4; i++ )
        waves_[i] = new FileLoop( Stk::rawwavePath() + "sinewave.raw", true );
        
  #endif

    this->setRatio(0, 0.5);
    this->setRatio(1, 0.5);
    this->setRatio(2, 1.0);
    this->setRatio(3, 1.0);

    //adjusted to try and sound closer
    gains_[0] = fmGains_[99];
    gains_[1] = fmGains_[84]; //74
    gains_[2] = fmGains_[81]; //71
    gains_[3] = fmGains_[79]; //79 

    baseGains[0] = gains_[0];
    baseGains[1] = gains_[1];
    baseGains[2] = gains_[2];
    baseGains[3] = gains_[3];

    adsr_[0]->setAllTimes( fmAttTimes_[31], fmAttTimes_[9], fmSusLevels_[0], fmAttTimes_[8]);  //8
    adsr_[1]->setAllTimes( fmAttTimes_[31], fmAttTimes_[9], fmSusLevels_[0], fmAttTimes_[8]); 
    adsr_[2]->setAllTimes( fmAttTimes_[31], fmAttTimes_[17], fmSusLevels_[0], fmAttTimes_[8]);
    adsr_[3]->setAllTimes( fmAttTimes_[31],  fmAttTimes_[16], fmSusLevels_[3], fmAttTimes_[8]);

    twozero_.setGain( 1.0 ); //   2.0 );
    op4Feedback = 0.7;
    vibrato_.setFrequency( 6.0 );
    modDepth_ = 0.0;
    control1_ = 1.0;
    control2_ = 1.0;
    // control1_ = 1.3;
    // control2_ = 1.3;

}  

LatelyB :: ~LatelyB( void )
{
}

void LatelyB :: noteOn( StkFloat frequency, StkFloat amplitude )
{
    gains_[0] = amplitude * baseGains[0]; 
    gains_[1] = amplitude * baseGains[1];
    gains_[2] = amplitude * baseGains[2];
    gains_[3] = amplitude * baseGains[3];

    this->setFrequency(frequency);
    this->keyOn();
}

} // stk namespace
