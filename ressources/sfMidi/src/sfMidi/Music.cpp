////////////////////////////////
// sfMidi 1.1.0               //
// Copyright © Kerli Low 2012 //
////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// License:                                                                 //
// sfMidi                                                                   //
// Copyright (c) 2012 Kerli Low                                             //
// kerlilow@gmail.com                                                       //
//                                                                          //
// This software is provided 'as-is', without any express or implied        //
// warranty. In no event will the authors be held liable for any damages    //
// arising from the use of this software.                                   //
//                                                                          //
// Permission is granted to anyone to use this software for any purpose,    //
// including commercial applications, and to alter it and redistribute it   //
// freely, subject to the following restrictions:                           //
//                                                                          //
//    1. The origin of this software must not be misrepresented; you must   //
//    not claim that you wrote the original software. If you use this       //
//    software in a product, an acknowledgment in the product documentation //
//    would be appreciated but is not required.                             //
//                                                                          //
//    2. Altered source versions must be plainly marked as such, and must   //
//    notbe misrepresented as being the original software.                  //
//                                                                          //
//    3. This notice may not be removed or altered from any source          //
//    distribution.                                                         //
//////////////////////////////////////////////////////////////////////////////

#include "sfMidi/Music.h"



///////////////////////////////////////////////////////////
// Midi class                                            //
///////////////////////////////////////////////////////////
sfmidi::Music::Music() : SoundStream()
{
  initialize(2, 44100);
}


sfmidi::Music::Music(const sfmidi::Loader& loader, const std::string& midi)
  : SoundStream()
{
  initialize(2, 44100);

  if (!loader.loadMidiFromFile(midi, data_))
    setError("Failed to load MIDI.");
}


sfmidi::Music::Music
  (const sfmidi::Loader& loader, const void* midiData, unsigned int midiSize)
  : SoundStream()
{
  initialize(2, 44100);

  if (!loader.loadMidiFromMemory(midiData, midiSize, data_))
    setError("Failed to load MIDI.");
}


sfmidi::Music::~Music()
{
  if (getStatus() != sf::SoundStream::Stopped)
    stop();

  data_.clear();
}


bool sfmidi::Music::loadMidiFromFile
  (const sfmidi::Loader& loader, const std::string& filename)
{
  if (!loader.loadMidiFromFile(filename, data_)) {
    setError("Failed to load MIDI.");
    return false;
  }

  size_ = data_.size();

  return true;
}

bool sfmidi::Music::loadMidiFromMemory
  (const sfmidi::Loader& loader, const std::string& data)
{
  if (!loader.loadMidiFromMemory(data, data_)) {
    setError("Failed to load MIDI.");
    return false;
  }

  size_ = data_.size();

  return true;
}

bool sfmidi::Music::loadMidiFromMemory
  (const sfmidi::Loader& loader, const void* data, unsigned int size)
{
  if (!loader.loadMidiFromMemory(data, size, data_)) {
    setError("Failed to load MIDI.");
    return false;
  }

  size_ = data_.size();

  return true;
}


bool sfmidi::Music::onGetData(sf::SoundStream::Chunk& data)
{
  if (position_ >= size_)
    return false;

  unsigned int size = SFMIDI_MUSICBUFFERSIZE;
  if (size_ - position_ < SFMIDI_MUSICBUFFERSIZE)
    size = size_ - position_;

  data.sampleCount = SFMIDI_MUSICBUFFERSIZE;
  data.samples     = &data_[position_];

  position_ += SFMIDI_MUSICBUFFERSIZE;

  return true;
}

void sfmidi::Music::onSeek(sf::Time timeOffset)
{
  position_ = static_cast<unsigned int>
    (static_cast<double>(timeOffset.asMilliseconds()) / 1000 * 44100);
}
