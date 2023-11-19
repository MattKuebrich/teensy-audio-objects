//-----------------------------------------------------------------------------
// 1.4.1.0 ***** REPAIRATHON2021 BRAND NEW FM ALGORITHMS!!! *****
//-----------------------------------------------------------------------------
/***** REPAIRATHON2021 BRAND NEW FM ALGORITHMS!!! *****/
/***************************************************/
/*! \class HnkyTonk
    \brief New STK-style Honkey Tonk Piano FM synthesis instrument.

   This class implements 4 cascade operators with
   feedback modulation on the master modulator,
   also referred to as algorithm 1 of the TX81Z.

   Algorithm 1 is :
       4-->3-->2-->1-->Out

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

#include "HnkyTonk.h"

namespace stk {

HnkyTonk :: HnkyTonk( void )
  : FM()
{
  #ifdef __RAW_ARRAYS__
        // Concatenate the STK rawwave path to the rawwave files
    for( int i=0; i<4; i++ ) //changed to 4 by mk
        waves_[i] = new MemoryLoop( Stk::rawwavePath() + "sinewave.raw", sinewave_raw,sinewave_raw_len);
  #else
      // Concatenate the STK rawwave path to the rawwave files
    for( int i=0; i<4; i++ )
        waves_[i] = new FileLoop( Stk::rawwavePath() + "sinewave.raw", true );
        
  #endif

    this->setRatio(0, 1.51);
    this->setRatio(1, 1.49);
    this->setRatio(2, 10.49);
    this->setRatio(3, 7.22);

    gains_[0] = fmGains_[99]; 
    gains_[1] = fmGains_[78]; 
    gains_[2] = fmGains_[61];
    gains_[3] = fmGains_[48]; 

    baseGains[0] = gains_[0];
    baseGains[1] = gains_[1];
    baseGains[2] = gains_[2];
    baseGains[3] = gains_[3];

    adsr_[0]->setAllTimes( fmAttTimes_[20], fmAttTimes_[8], fmSusLevels_[12], fmAttTimes_[5]); // 6
    adsr_[1]->setAllTimes( fmAttTimes_[22], fmAttTimes_[3], fmSusLevels_[12], fmAttTimes_[4]);
    adsr_[2]->setAllTimes( fmAttTimes_[24], fmAttTimes_[27], fmSusLevels_[13], fmAttTimes_[3]);
    adsr_[3]->setAllTimes( fmAttTimes_[24],  fmAttTimes_[1],  fmSusLevels_[0], fmAttTimes_[3]);

    twozero_.setGain( 0.8 );
    op4Feedback = 0.8;
    vibrato_.setFrequency( 6.0 );
    modDepth_ = 0.05;
}  

HnkyTonk :: ~HnkyTonk( void )
{
}

void HnkyTonk :: noteOn( StkFloat frequency, StkFloat amplitude )
{
    gains_[0] = amplitude * baseGains[0]; 
    gains_[1] = amplitude * baseGains[1];
    gains_[2] = amplitude * baseGains[2];
    gains_[3] = amplitude * baseGains[3];

    this->setFrequency(frequency);
    this->keyOn();
}

} // stk namespace
