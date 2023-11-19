/***************************************************/
/*! \class VoicerGuitar
    \brief STK voice manager class.

    This class can be used to manage a group of STK instrument
    classes.  Individual voices can be controlled via unique note
    tags.  Instrument groups can be controlled by group number.

    A previously constructed STK instrument class is linked with a
    voice manager using the addInstrument() function.  An optional
    group number argument can be specified to the addInstrument()
    function as well (default group = 0).  The voice manager does not
    delete any instrument instances ... it is the responsibility of
    the user to allocate and deallocate all instruments.

    The tick() function returns the mix of all sounding voices.  Each
    noteOn returns a unique tag (credits to the NeXT MusicKit), so you
    can send control changes to specific voices within an ensemble.
    Alternately, control changes can be sent to all voices in a given
    group.

    by Perry R. Cook and Gary P. Scavone, 1995--2019.
*/
/***************************************************/

#include "VoicerGuitar.h"
#include <cmath>

namespace stk {

VoicerGuitar :: VoicerGuitar( StkFloat decayTime )
{
  if ( decayTime < 0.0f ) {
    oStream_ << "VoicerGuitar::VoicerGuitar: argument (" << decayTime << ") must be positive!";
    handleError( StkError::FUNCTION_ARGUMENT );
  }

  tags_ = 23456;
  muteTime_ = (int) ( decayTime * Stk::sampleRate() );
  lastFrame_.resize( 1, 1, 0.0 );
}

void VoicerGuitar :: addInstrument( Guitar *instrument, int group )
{
  VoicerGuitar::Voice voice;
  voice.instrument = instrument;
  voice.group = group;
  voice.noteNumber = -1;
  voices_.push_back( voice );


  // Check output channels and resize lastFrame_ if necessary.
  if ( instrument->channelsOut() > lastFrame_.channels() ) {
    unsigned int startChannel = lastFrame_.channels();
    lastFrame_.resize( 1, instrument->channelsOut() );
    for ( unsigned int i=startChannel; i<lastFrame_.size(); i++ )
      lastFrame_[i] = 0.0;
  }


}

void VoicerGuitar :: removeInstrument( Guitar *instrument )
{
  bool found = false;
  std::vector< VoicerGuitar::Voice >::iterator i;
  for ( i=voices_.begin(); i!=voices_.end(); ++i ) {
    if ( (*i).instrument != instrument ) continue;
    voices_.erase( i );
    found = true;
    break;
  }

  if ( found ) {
    // Check output channels and resize lastFrame_ if necessary.
    unsigned int maxChannels = 1;
    
  
    for ( i=voices_.begin(); i!=voices_.end(); ++i ) {
      if ( (*i).instrument->channelsOut() > maxChannels ) maxChannels = (*i).instrument->channelsOut();
    }
  

    if ( maxChannels < lastFrame_.channels() )
      lastFrame_.resize( 1, maxChannels );
  }
  else {
    oStream_ << "VoicerGuitar::removeInstrument: instrument pointer not found in current voices!";
    handleError( StkError::WARNING );
  }
}

long VoicerGuitar :: noteOn(StkFloat noteNumber, StkFloat amplitude, int group )
{
  unsigned int i;
  StkFloat frequency = (StkFloat) 220.0f * std::pow( 2.0f, (noteNumber - 57.0f) / 12.0f );
  for ( i=0; i<voices_.size(); i++ ) {
    if (voices_[i].noteNumber < 0 && voices_[i].group == group) {
      voices_[i].tag = tags_++;
      voices_[i].group = group;
      voices_[i].noteNumber = noteNumber;
      voices_[i].frequency = frequency;
      voices_[i].instrument->noteOn( frequency, amplitude * ONE_OVER_128, 0); //change this?
      voices_[i].sounding = 1;
      return voices_[i].tag;
    }
  }

  // All voices are sounding, so interrupt the oldest voice.
  int voice = -1;
  for ( i=0; i<voices_.size(); i++ ) {
    if ( voices_[i].group == group ) {
      if ( voice == -1 ) voice = i;
      else if ( voices_[i].tag < voices_[voice].tag ) voice = (int) i;
    }
  }

  if ( voice >= 0 ) {
    voices_[voice].tag = tags_++;
    voices_[voice].group = group;
    voices_[voice].noteNumber = noteNumber;
    voices_[voice].frequency = frequency;
    voices_[voice].instrument->noteOn( frequency, amplitude * ONE_OVER_128, 0);
    voices_[voice].sounding = 1;
    return voices_[voice].tag;
  }

  return -1;
}

void VoicerGuitar :: noteOff( StkFloat noteNumber, StkFloat amplitude, int group )
{
  for ( unsigned int i=0; i<voices_.size(); i++ ) {
    if ( voices_[i].noteNumber == noteNumber && voices_[i].group == group ) {
      voices_[i].instrument->noteOff( amplitude * ONE_OVER_128, 0);
      voices_[i].sounding = -muteTime_; 
    }
  }
}

/*
void VoicerGuitar :: noteOff( long tag, StkFloat amplitude)
{
  for ( unsigned int i=0; i<voices_.size(); i++ ) {
    if ( voices_[i].tag == tag ) {
      voices_[i].instrument->noteOff( amplitude * ONE_OVER_128, 0); //mk test
      voices_[i].sounding = -muteTime_;
      break;
    }
  }
}
*/

void VoicerGuitar :: setFrequency( StkFloat noteNumber, int group )
{
  StkFloat frequency = (StkFloat) 220.0f * std::pow( 2.0f, (noteNumber - 57.0f) / 12.0f );
  for ( unsigned int i=0; i<voices_.size(); i++ ) {
    if ( voices_[i].group == group ) {
      voices_[i].noteNumber = noteNumber;
      voices_[i].frequency = frequency;
      voices_[i].instrument->setFrequency( frequency );
    }
  }
}

void VoicerGuitar :: setFrequency( long tag, StkFloat noteNumber )
{
  StkFloat frequency = (StkFloat) 220.0f * std::pow( 2.0f, (noteNumber - 57.0f) / 12.0f );
  for ( unsigned int i=0; i<voices_.size(); i++ ) {
    if ( voices_[i].tag == tag ) {
      voices_[i].noteNumber = noteNumber;
      voices_[i].frequency = frequency;
      voices_[i].instrument->setFrequency( frequency );
      break;
    }
  }
}

void VoicerGuitar :: pitchBend( StkFloat value, int group )
{
  StkFloat pitchScaler;
  if ( value < 8192.0f )
    pitchScaler = std::pow( 0.5f, (8192.0f-value) / 8192.0f );
  else
    pitchScaler = std::pow( 2.0f, (value-8192.0f) / 8192.0f );
  for ( unsigned int i=0; i<voices_.size(); i++ ) {
    if ( voices_[i].group == group )
      voices_[i].instrument->setFrequency( (StkFloat) (voices_[i].frequency * pitchScaler) );
  }
}

void VoicerGuitar :: pitchBend( long tag, StkFloat value )
{
  StkFloat pitchScaler;
  if ( value < 8192.0f )
    pitchScaler = std::pow( 0.5f, (8192.0f-value) / 8192.0f );
  else
    pitchScaler = std::pow( 2.0f, (value-8192.0f) / 8192.0f );
  for ( unsigned int i=0; i<voices_.size(); i++ ) {
    if ( voices_[i].tag == tag ) {
      voices_[i].instrument->setFrequency( (StkFloat) (voices_[i].frequency * pitchScaler) );
      break;
    }
  }
}

void VoicerGuitar :: controlChange( int number, StkFloat value, int group )
{
  for ( unsigned int i=0; i<voices_.size(); i++ ) {
    if ( voices_[i].group == group )
      voices_[i].instrument->controlChange( number, value );
  }
}

void VoicerGuitar :: controlChange( long tag, int number, StkFloat value )
{
  for ( unsigned int i=0; i<voices_.size(); i++ ) {
    if ( voices_[i].tag == tag ) {
      voices_[i].instrument->controlChange( number, value );
      break;
    }
  }
}

void VoicerGuitar :: silence( void )
{
  for ( unsigned int i=0; i<voices_.size(); i++ ) {
    if ( voices_[i].sounding > 0 )
      voices_[i].instrument->noteOff( 0.5 );
  }
}

//added by mk
int VoicerGuitar :: getNumActiveVoices() {
  int numActive = 0;
  for (unsigned int i=0; i<voices_.size(); i++) {
    if (voices_[i].sounding > 0) {
      numActive++;
    }
  }
  return numActive;
}

} // stk namespace
