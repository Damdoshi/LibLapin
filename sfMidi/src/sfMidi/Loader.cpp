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

#include <fluidsynth.h>

#include "sfMidi/Loader.h"



///////////////////////////////////////////////////////////
// Loader class                                          //
///////////////////////////////////////////////////////////
sfmidi::Loader::Loader() : sfmidi::Error()
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
}

sfmidi::Loader::Loader(const std::string& soundFont) : sfmidi::Error()
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

  loadSoundFontFromFile(soundFont);
}


sfmidi::Loader::~Loader()
{
  if (synth_ != NULL) {
    delete_fluid_synth(synth_);
    synth_ = NULL;
  }

  if (settings_ != NULL) {
    delete_fluid_settings(settings_);
    settings_ = NULL;
  }
}


void sfmidi::Loader::setGain(double gain)
{
  fluid_settings_setnum(settings_, "synth.gain", gain);
}

double sfmidi::Loader::getGain() const
{
  double gain = 0.2;
  fluid_settings_getnum(settings_, "synth.gain", &gain);
  return gain;
}


bool sfmidi::Loader::loadSoundFontFromFile(const std::string& filename)
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


bool sfmidi::Loader::loadMidiFromFile(const std::string& filename,
                                      sfmidi::AudioData& output) const
{
  static const unsigned int loaderBufferSize = SFMIDI_LOADERFRAMES * 2;

  fluid_player_t* player = new_fluid_player(synth_);
  if (player == NULL)
    return false;

  if (fluid_player_add(player, filename.c_str()) != FLUID_OK)
    return false;

  fluid_player_play(player);

  unsigned int outputSize = SFMIDI_LOADERBLOCKSIZE;

  output.resize(outputSize);

  unsigned int dataSize = 0;

  int read = FLUID_FAILED;

  while (true) {
    read = fluid_synth_write_s16(synth_, SFMIDI_LOADERFRAMES,
                                 &output[dataSize], 0, 2,
                                 &output[dataSize], 1, 2);

    if (read == FLUID_FAILED ||
        fluid_player_get_status(player) != FLUID_PLAYER_PLAYING)
      break;

    dataSize += loaderBufferSize;

    if (outputSize - dataSize < loaderBufferSize) {
      outputSize += SFMIDI_LOADERBLOCKSIZE;
      output.resize(outputSize);
    }
  }

  output.resize(dataSize);

  delete_fluid_player(player);

  return true;
}

bool sfmidi::Loader::loadMidiFromMemory(const std::string& data,
                                        sfmidi::AudioData& output) const
{
  static const unsigned int loaderBufferSize = SFMIDI_LOADERFRAMES * 2;

  fluid_player_t* player = new_fluid_player(synth_);
  if (player == NULL)
    return false;

  if (fluid_player_add_mem(player, data.c_str(), data.size()) != FLUID_OK)
    return false;

  fluid_player_play(player);

  unsigned int outputSize = SFMIDI_LOADERBLOCKSIZE;

  output.resize(outputSize);

  unsigned int dataSize = 0;

  int read = FLUID_FAILED;

  while (true) {
    read = fluid_synth_write_s16(synth_, SFMIDI_LOADERFRAMES,
                                 &output[dataSize], 0, 2,
                                 &output[dataSize], 1, 2);

    if (read == FLUID_FAILED ||
        fluid_player_get_status(player) != FLUID_PLAYER_PLAYING)
      break;

    dataSize += loaderBufferSize;

    if (outputSize - dataSize < loaderBufferSize) {
      outputSize += SFMIDI_LOADERBLOCKSIZE;
      output.resize(outputSize);
    }
  }

  output.resize(dataSize);

  delete_fluid_player(player);

  return true;
}

bool sfmidi::Loader::loadMidiFromMemory(const void* data, unsigned int size,
                                        sfmidi::AudioData& output) const
{
  static const unsigned int loaderBufferSize = SFMIDI_LOADERFRAMES * 2;

  fluid_player_t* player = new_fluid_player(synth_);
  if (player == NULL)
    return false;

  if (fluid_player_add_mem(player, data, size) != FLUID_OK)
    return false;

  fluid_player_play(player);

  unsigned int outputSize = SFMIDI_LOADERBLOCKSIZE;

  output.resize(outputSize);

  unsigned int dataSize = 0;

  int read = FLUID_FAILED;

  while (true) {
    read = fluid_synth_write_s16(synth_, SFMIDI_LOADERFRAMES,
                                 &output[dataSize], 0, 2,
                                 &output[dataSize], 1, 2);

    if (read == FLUID_FAILED ||
        fluid_player_get_status(player) != FLUID_PLAYER_PLAYING)
      break;

    dataSize += loaderBufferSize;

    if (outputSize - dataSize < loaderBufferSize) {
      outputSize += SFMIDI_LOADERBLOCKSIZE;
      output.resize(outputSize);
    }
  }

  output.resize(dataSize);

  delete_fluid_player(player);

  return true;
}
