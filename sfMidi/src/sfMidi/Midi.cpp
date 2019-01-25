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

#include <fstream>
#include <fluidsynth.h>

#include "sfMidi/Midi.h"



///////////////////////////////////////////////////////////
// Midi class                                            //
///////////////////////////////////////////////////////////
sfmidi::Midi::Midi() : sf::SoundStream(), sfmidi::Error()
{
  settings_ = new_fluid_settings();
  if (settings_ == NULL) {
    setError("Failed to initialize.");
    return;
  }
  
  synth_ = new_fluid_synth(settings_);
  if (synth_ == NULL) {
    setError("Failed to initialize.");
    return;
  }

  player_ = new_fluid_player(synth_);
  if (player_ == NULL) {
    setError("Failed to initialize.");
    return;
  }

  buffer_.resize(SFMIDI_AUDIOFRAMES * 2);

  loop_ = false;
  loopClock_ = NULL;

  initialize(2, 44100);
}


sfmidi::Midi::Midi(const std::string& soundFont, const std::string& midi)
  : sf::SoundStream(), sfmidi::Error()
{
  settings_ = new_fluid_settings();
  if (settings_ == NULL) {
    setError("Failed to initialize.");
    return;
  }
  
  synth_ = new_fluid_synth(settings_);
  if (synth_ == NULL) {
    setError("Failed to initialize.");
    return;
  }

  player_ = new_fluid_player(synth_);
  if (player_ == NULL) {
    setError("Failed to initialize.");
    return;
  }

  buffer_.resize(SFMIDI_AUDIOFRAMES * 2);

  loop_ = false;
  loopClock_ = NULL;

  initialize(2, 44100);

  if (loadSoundFontFromFile(soundFont))
    loadMidiFromFile(midi);
}


sfmidi::Midi::Midi
  (const std::string& soundFont, const void* midiData, unsigned int midiSize)
  : sf::SoundStream(), sfmidi::Error()
{ 
  settings_ = new_fluid_settings();
  if (settings_ == NULL) {
    setError("Failed to initialize.");
    return;
  }
  
  synth_ = new_fluid_synth(settings_);
  if (synth_ == NULL) {
    setError("Failed to initialize.");
    return;
  }

  player_ = new_fluid_player(synth_);
  if (player_ == NULL) {
    setError("Failed to initialize.");
    return;
  }

  buffer_.resize(SFMIDI_AUDIOFRAMES * 2);

  loop_ = false;
  loopClock_ = NULL;

  initialize(2, 44100);

  if (loadSoundFontFromFile(soundFont))
    loadMidiFromMemory(midiData, midiSize);
}


sfmidi::Midi::~Midi()
{
  if (getStatus() != sf::SoundStream::Stopped)
    stop();

  if (player_ != NULL) {
    delete_fluid_player(player_);
    player_ = NULL;
  }

  if (synth_ != NULL) {
    delete_fluid_synth(synth_);
    synth_ = NULL;
  }

  if (settings_ != NULL) {
    delete_fluid_settings(settings_);
    settings_ = NULL;
  }
}


void sfmidi::Midi::setLoop(bool loop)
{
  loop_ = loop;
}

void sfmidi::Midi::setGain(double gain)
{
  fluid_settings_setnum(settings_, "synth.gain", gain);
}

bool sfmidi::Midi::getLoop() const
{
  return loop_;
}

double sfmidi::Midi::getGain() const
{
  double gain = 0.2;
  fluid_settings_getnum(settings_, "synth.gain", &gain);
  return gain;
}


bool sfmidi::Midi::loadSoundFontFromFile(const std::string& filename)
{
  if (fluid_synth_sfload(synth_, filename.c_str(), 1) != FLUID_FAILED) {
    for (int i = fluid_synth_sfcount(synth_); i > 1; --i) {
      fluid_sfont_t* sfont = fluid_synth_get_sfont(synth_, 1);
      if (sfont != NULL)
        fluid_synth_sfunload(synth_, sfont->id, 1);
    }

    return true;
  }

  setError("Failed to load SoundFont.");
  return false;
}


bool sfmidi::Midi::loadMidiFromFile(const std::string& filename)
{
  if (player_ != NULL)
    delete_fluid_player(player_);

  player_ = new_fluid_player(synth_);
  if (player_ == NULL) {
    setError("Failed to load MIDI.");
    return false;
  }

  std::ifstream file(filename, std::ios::binary);
  if (!file.is_open()) {
    setError("Failed to load MIDI.");
    return false;
  }

  file.seekg(0, std::ios::end);
  unsigned int size = static_cast<unsigned int>(file.tellg());
  file.seekg(0, std::ios::beg);

  char* data = new char[size];
  if (data == NULL) {
    setError("Failed to load MIDI.");
    return false;
  }

  file.read(data, size);

  midi_ = std::string(data, size);

  delete[] data;

  file.close();

  if (fluid_player_add_mem(player_, midi_.c_str(), midi_.size()) !=
      FLUID_OK) {
    setError("Failed to load MIDI.");
    return false;
  }

  return true;
}

bool sfmidi::Midi::loadMidiFromMemory(const std::string& data)
{
  if (player_ != NULL)
    delete_fluid_player(player_);

  player_ = new_fluid_player(synth_);
  if (player_ == NULL) {
    setError("Failed to load MIDI.");
    return false;
  }

  midi_ = data;

  if (fluid_player_add_mem(player_, midi_.c_str(), midi_.size()) !=
      FLUID_OK) {
    setError("Failed to load MIDI.");
    return false;
  }

  return true;
}

bool sfmidi::Midi::loadMidiFromMemory(const void* data, unsigned int size)
{
  if (player_ != NULL)
    delete_fluid_player(player_);

  player_ = new_fluid_player(synth_);
  if (player_ == NULL) {
    setError("Failed to load MIDI.");
    return false;
  }

  midi_ = std::string(static_cast<const char*>(data), size);

  if (fluid_player_add_mem(player_, midi_.c_str(), midi_.size()) !=
      FLUID_OK) {
    setError("Failed to load MIDI.");
    return false;
  }

  return true;
}


void sfmidi::Midi::play()
{
  int status = fluid_player_get_status(player_);

  if (status == FLUID_PLAYER_READY)
    fluid_player_play(player_);

  if (loop_ && status == FLUID_PLAYER_DONE) {
    stop();
    delete_fluid_player(player_);
    player_ = new_fluid_player(synth_);
    if (player_ == NULL) {
      setError("Failed to play MIDI.");
      return;
    }

    fluid_player_add_mem(player_, midi_.c_str(), midi_.size());
    fluid_player_play(player_);
  }

  if (fluid_player_get_status(player_) != FLUID_PLAYER_DONE)
    SoundStream::play();
}


bool sfmidi::Midi::onGetData(sf::SoundStream::Chunk& data)
{
  static const unsigned int audioBufferSize = SFMIDI_AUDIOFRAMES * 2;

  int read = fluid_synth_write_s16(synth_, SFMIDI_AUDIOFRAMES,
                                   &buffer_[0], 0, 2, &buffer_[0], 1, 2);
  
  if (read == FLUID_FAILED)
    return false;

  data.sampleCount = audioBufferSize;
  data.samples     = &buffer_[0];
  
  if (loop_ && fluid_player_get_status(player_) == FLUID_PLAYER_DONE) {
    if (loopClock_ == NULL)
      loopClock_ = new sf::Clock();
    else if (loopClock_->getElapsedTime().asMilliseconds() > 500) {
      delete loopClock_;
      loopClock_ = NULL;

      pause();
      delete_fluid_player(player_);
      player_ = new_fluid_player(synth_);
      if (player_ == NULL)
        return false;

      fluid_player_add_mem(player_, midi_.c_str(), midi_.size());
      fluid_player_play(player_);
      sf::SoundStream::play();
    }
  }

  return true;
}

void sfmidi::Midi::onSeek(sf::Time timeOffset)
{
  static const unsigned int seekFrameLength = SFMIDI_SEEKBUFFERSIZE / 2;
  static sf::Int16          seekBuffer[SFMIDI_SEEKBUFFERSIZE];

  if (fluid_player_get_status(player_) == FLUID_PLAYER_DONE)
    return;
  
  sf::Int32 msec = timeOffset.asMilliseconds();
  
  sf::Int32 currentOffset = getPlayingOffset().asMilliseconds();

  if (currentOffset == msec)
    return;
  else if (currentOffset < msec) { // Seek forward
    unsigned int count = static_cast<unsigned int>
      (static_cast<double>(msec - currentOffset) / 1000 /
       SFMIDI_SEEKBUFFERSIZE * 44100 * 2);

    unsigned int i = 0;

    for (i = 0; i < count; ++i) {
      if (fluid_synth_write_s16
            (synth_, seekFrameLength,
             seekBuffer, 0, 2, seekBuffer, 1, 2) == FLUID_FAILED)
        break;
    }
  }
  else { // Seek backwards
    // Seeking backwards requires reloading midi file
    // and seek forward until desired offset
    sf::SoundStream::Status status = getStatus();

    if (status != sf::SoundStream::Stopped)
      stop();

    delete_fluid_player(player_);
    player_ = new_fluid_player(synth_);
    if (player_ == NULL)
      return;

    fluid_player_add_mem(player_, midi_.c_str(), midi_.size());
    fluid_player_play(player_);

    unsigned int count = static_cast<unsigned int>
      (static_cast<double>(msec) / 1000 / SFMIDI_SEEKBUFFERSIZE * 44100 * 2);

    for (unsigned int i = 0; i < count; ++i) {
      if (fluid_synth_write_s16
            (synth_, seekFrameLength,
             seekBuffer, 0, 2, seekBuffer, 1, 2) == FLUID_FAILED)
        return;
    }

    if (status == sf::SoundStream::Playing)
      sf::SoundStream::play();
  }
}
