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
//    not be misrepresented as being the original software.                 //
//                                                                          //
//    3. This notice may not be removed or altered from any source          //
//    distribution.                                                         //
//////////////////////////////////////////////////////////////////////////////

#ifndef SFMIDI_LOADER_H
#define SFMIDI_LOADER_H

#include <string>
#include <vector>
#include <SFML/Audio.hpp>

#include "sfMidi/Error.h"



const unsigned int SFMIDI_LOADERFRAMES    = 2048;
const unsigned int SFMIDI_LOADERBLOCKSIZE = SFMIDI_LOADERFRAMES * 1000;


// Forward declarations //
struct _fluid_hashtable_t;
typedef struct _fluid_hashtable_t fluid_settings_t;
struct _fluid_synth_t;
typedef struct _fluid_synth_t fluid_synth_t;
// //


namespace sfmidi
{
  typedef std::vector<sf::Int16> AudioData;


  class Loader;
}


///////////////////////////////////////////////////////////
// Loader class                                          //
///////////////////////////////////////////////////////////
class sfmidi::Loader : public sfmidi::Error
{
public:
  Loader();
  Loader(const std::string& soundFont);

  ~Loader();

  void   setGain(double gain); // 0.0 - 10.0; Default: 0.2
  double getGain() const;

  bool loadSoundFontFromFile(const std::string& filename);

  bool loadMidiFromFile  (const std::string& filename,
                          sfmidi::AudioData& output) const;
  bool loadMidiFromMemory(const std::string& data,
                          sfmidi::AudioData& output) const;
  bool loadMidiFromMemory(const void* data, unsigned int size,
                          sfmidi::AudioData& output) const;


private:
  fluid_settings_t* settings_;
  fluid_synth_t*    synth_;
};



#endif // SFMIDI_LOADER_H
