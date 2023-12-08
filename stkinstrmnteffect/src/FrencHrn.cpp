//-----------------------------------------------------------------------------
// 1.4.1.0 ***** REPAIRATHON2021 BRAND NEW FM ALGORITHMS!!! *****
//-----------------------------------------------------------------------------

/***************************************************/
/*! \class FrencHrn
    \brief NEW STK-style French Horn FM synthesis instrument.

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

#include "FrencHrn.h"

namespace stk {

FrencHrn :: FrencHrn( void )
  : FM()
{
  #ifdef __RAW_ARRAYS__
        // Concatenate the STK rawwave path to the rawwave files
    //for( int i=0; i<4; i++ )
    for( int i=0; i<4; i++ )
        waves_[i] = new MemoryLoop( Stk::rawwavePath() + "sinewave.raw", sinewave_raw,sinewave_raw_len);
  #else
      // Concatenate the STK rawwave path to the rawwave files
    for( int i=0; i<4; i++ )
        waves_[i] = new FileLoop( Stk::rawwavePath() + "sinewave.raw", true );
        
  #endif

    this->setRatio(0, 1.0);
    this->setRatio(1, 0.99);
    this->setRatio(2, 3.14);
    this->setRatio(3, 0.99);

    gains_[0] = fmGains_[97]; /***** REPAIRATHON2021: French Horn!!! *****/
    gains_[1] = fmGains_[77]; // Factory Bank 1759 says 67, adjust for controls
    gains_[2] = fmGains_[59];
    gains_[3] = fmGains_[71]; 

    baseGains[0] = gains_[0];
    baseGains[1] = gains_[1];
    baseGains[2] = gains_[2];
    baseGains[3] = gains_[3];

    adsr_[0]->setAllTimes( fmAttTimes_[12], fmAttTimes_[31], fmSusLevels_[15], fmAttTimes_[16]); // 6
    adsr_[1]->setAllTimes( fmAttTimes_[14], fmAttTimes_[31], fmSusLevels_[15], fmAttTimes_[16]);
    adsr_[2]->setAllTimes( fmAttTimes_[31], fmAttTimes_[14], fmSusLevels_[0], fmAttTimes_[16]);
    adsr_[3]->setAllTimes( fmAttTimes_[8],  fmAttTimes_[5],  fmSusLevels_[0], fmAttTimes_[16]);

     //setting this to longer times to see if it sounds diff
    //adsr_[0]->setAllTimes( 0.5, fmAttTimes_[31], fmSusLevels_[15], fmAttTimes_[16]); // 6
    //adsr_[1]->setAllTimes( 0.5, fmAttTimes_[31], fmSusLevels_[15], fmAttTimes_[16]);
    //adsr_[2]->setAllTimes( 0.5, fmAttTimes_[14], fmSusLevels_[0], fmAttTimes_[16]);
    //adsr_[3]->setAllTimes( 0.5,  fmAttTimes_[5],  fmSusLevels_[0], fmAttTimes_[16]);

    twozero_.setGain( 1.0 ); //   2.0 );
    op4Feedback = 1.0;
    vibrato_.setFrequency( 6.0 );
    modDepth_ = 0.0;
    control1_ = 1.0;
    control2_ = 1.0;
    // control1_ = 1.3;
    // control2_ = 1.3;

}  

FrencHrn :: ~FrencHrn( void )
{
}

void FrencHrn :: noteOn( StkFloat frequency, StkFloat amplitude )
{
    gains_[0] = amplitude * baseGains[0]; 
    gains_[1] = amplitude * baseGains[1];
    gains_[2] = amplitude * baseGains[2];
    gains_[3] = amplitude * baseGains[3];

    this->setFrequency(frequency);
    this->keyOn();
}

} // stk namespace
