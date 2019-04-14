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

#include "sfTheora/AudioInterface.h"



///////////////////////////////////////////////////////////
// AudioInterface class                                  //
///////////////////////////////////////////////////////////
sftheora::AudioInterface::AudioInterface
  (TheoraVideoClip* owner, int nChannels, int freq) :
	  TheoraAudioInterface(owner, nChannels, freq), TheoraTimer()
{
  owner->setTimer(this);

  nChannels_ = nChannels;
  freq_      = freq;

  read_ = 0;

  initialize(nChannels_, freq_);
}

sftheora::AudioInterface::~AudioInterface()
{
  stop();
}


void sftheora::AudioInterface::insertData(float* data, int nSamples)
{
  sf::Lock lock(dataMutex_);

  for (int i = 0; i < nSamples; ++i) {
    float fSample = data[i];

    if (fSample > 1.0f)
      fSample = 1.0f;
    else if (fSample < -1.0f)
      fSample = -1.0f;

    sf::Int16 iSample = static_cast<sf::Int16>(fSample * 32767);

    data_.push_back(iSample);
  }

  if (getStatus() != sf::SoundStream::Playing)
    sf::SoundStream::play();
}

void sftheora::AudioInterface::destroy()
{
  data_.clear();
  read_ = 0;
}

void sftheora::AudioInterface::play()
{
  sf::SoundStream::play();
  TheoraTimer::play();
}

void sftheora::AudioInterface::pause()
{
  sf::SoundStream::pause();
  TheoraTimer::pause();
}

void sftheora::AudioInterface::stop()
{
  sf::SoundStream::stop();
  TheoraTimer::stop();
}

void sftheora::AudioInterface::seek(float time)
{
  sf::Lock lock(dataMutex_);

  sf::SoundStream::stop();

  data_.clear();
  read_ = 0;
  
  mTime = time;
}


bool sftheora::AudioInterface::onGetData(sf::SoundStream::Chunk& data)
{
  sf::Lock lock(dataMutex_);

  if (data_.empty())
    return false;

  if (read_ > 0) {
    if (read_ >= data_.size())
      data_.clear();
    else
      data_.erase(data_.begin(), data_.begin() + read_);
  }

  read_ = data_.size();
  if (read_ == 0)
    return false;

  if (read_ > SFTHEORA_AI_MAXSAMPLES)
    read_ = SFTHEORA_AI_MAXSAMPLES;
  else
    read_ = (read_ / 2) * 2;

  data.samples     = &data_[0];
  data.sampleCount = read_;

  return true;
}

void sftheora::AudioInterface::onSeek(sf::Time timeOffset)
{
}


///////////////////////////////////////////////////////////
// AudioInterfaceFactory class                           //
///////////////////////////////////////////////////////////
sftheora::AudioInterfaceFactory::AudioInterfaceFactory()
{
  audioInterface_ = NULL;
}


sftheora::AudioInterfaceFactory::~AudioInterfaceFactory()
{
  if (audioInterface_ != NULL) {
    delete audioInterface_;
    audioInterface_ = NULL;
  }
}


sftheora::AudioInterface*
  sftheora::AudioInterfaceFactory::createInstance(TheoraVideoClip* owner,
                                                  int nChannels, int freq)
{
  if (audioInterface_ != NULL) {
    delete audioInterface_;
    audioInterface_ = NULL;
  }

  audioInterface_ = new sftheora::AudioInterface(owner, nChannels, freq);

  return audioInterface_;
}
