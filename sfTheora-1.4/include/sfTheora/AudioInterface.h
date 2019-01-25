////////////////////////////////
// sfTheora 1.4.0             //
// Copyright © Kerli Low 2011 //
////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// License:                                                                 //
// sfTheora                                                                 //
// Copyright (c) 2011 Kerli Low                                             //
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

#ifndef SFTHEORA_AUDIOINTERFACE_H
#define SFTHEORA_AUDIOINTERFACE_H

#include <vector>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

#include "theoraplayer/TheoraAudioInterface.h"
#include "theoraplayer/TheoraVideoClip.h"
#include "theoraplayer/TheoraTimer.h"

#define SFTHEORA_AI_MAXSAMPLES 2048



namespace sftheora
{
  class AudioInterface;
  class AudioInterfaceFactory;
  class Video;
}


///////////////////////////////////////////////////////////
// Audio Interface class                                 //
///////////////////////////////////////////////////////////
class sftheora::AudioInterface
  : public TheoraAudioInterface, private TheoraTimer, public sf::SoundStream
{
public:
  AudioInterface(TheoraVideoClip* owner, int nChannels, int freq);

  ~AudioInterface();

  void insertData(float* data, int nSamples);
  void destroy   ();
  void play      ();
  void pause     ();
  void stop      ();
  void seek      (float time);


private:
  friend class sftheora::Video;


  virtual bool onGetData(sf::SoundStream::Chunk& data);
  virtual void onSeek   (sf::Time timeOffset);


  sf::Mutex dataMutex_;

  int nChannels_;
  int freq_;

  unsigned int read_;

  std::vector<sf::Int16> data_;
};


///////////////////////////////////////////////////////////
// Audio Interface Factory class                         //
///////////////////////////////////////////////////////////
class sftheora::AudioInterfaceFactory : public TheoraAudioInterfaceFactory
{
public:
  AudioInterfaceFactory();

  ~AudioInterfaceFactory();

	sftheora::AudioInterface* createInstance(TheoraVideoClip* owner,
                                           int nChannels, int freq);


private:
  friend class sftheora::Video;


  sftheora::AudioInterface* audioInterface_;
};



#endif // SFTHEORA_AUDIOINTERFACE_H
