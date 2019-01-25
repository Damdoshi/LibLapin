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

#include "sfTheora/Video.h"



///////////////////////////////////////////////////////////
// Video class                                           //
///////////////////////////////////////////////////////////
sftheora::Video::Video() : Error()
{
  if (!init())
    setError("Failed to initialize video.");
}

sftheora::Video::Video(const std::string& filename) : Error()
{
  if (!init()) {
    setError("Failed to initialize video.");
    return;
  }
  
  load(filename);
}

sftheora::Video::Video(TheoraDataSource* dataSource) : Error()
{
  if (!init()) {
    setError("Failed to initialize video.");
    return;
  }

  load(dataSource);
}

sftheora::Video::Video(const std::string& repr, const void* data,
                       unsigned long size) : Error()
{
  if (!init()) {
    setError("Failed to initialize video.");
    return;
  }

  load(repr, data, size);
}


sftheora::Video::~Video()
{
  unload();
  
  memoryLoader_.release();

  if (ifaceFactory_ != NULL) {
    delete ifaceFactory_;
    ifaceFactory_ = NULL;
  }

  if (vidManager_ != NULL) {
    delete vidManager_;
    vidManager_ = NULL;
  }
}


void sftheora::Video::update(sf::Time deltaTime)
{
  if (vidClip_ == NULL || vidManager_ == NULL)
    return;

  if (started_) {
    if (vidClip_->getNumReadyFrames() <
        vidClip_->getNumPrecachedFrames() * 0.5f)
      return;

    started_ = false;
  }

  vidManager_->update(deltaTime.asSeconds());

  TheoraVideoFrame* frame = vidClip_->getNextFrame();

  if (frame != NULL) {
    sf::Image frameImg;
	  frameImg.create(frame->getWidth(), frame->getHeight(),
                    frame->getBuffer());

	  currentFrame_.loadFromImage(frameImg);

    currentFrame_.setSmooth(true);

    setTexture(currentFrame_);

    vidClip_->popFrame();
  }
}

bool sftheora::Video::load(const std::string& filename)
{
  if (vidManager_ == NULL || ifaceFactory_ == NULL) {
    setError("Video not initialized.");
    return false;
  }
  
  unload();
  
  vidClip_ = vidManager_->createVideoClip(filename, TH_RGBA);
  if (vidClip_ == NULL) {
    setError("Failed to load video.");
    return false;
  }
  
  vidClip_->setAutoRestart(false);
  
  return true;
}

bool sftheora::Video::load(TheoraDataSource* dataSource)
{
  if (vidManager_ == NULL || ifaceFactory_ == NULL) {
    setError("Video not initialized.");
    return false;
  }

  unload();

  vidClip_ = vidManager_->createVideoClip(dataSource, TH_RGBA);
  if (vidClip_ == NULL) {
    setError("Failed to load video.");
    return false;
  }

  vidClip_->setAutoRestart(false);

  return true;
}

bool sftheora::Video::load
  (const std::string& repr, const void* data, unsigned long size)
{
  if (vidManager_ == NULL || ifaceFactory_ == NULL) {
    setError("Video not initialized.");
    return false;
  }
  
  unload();
  
  memoryLoader_.release();
  
  memoryLoader_.set(repr, data, size);

  vidClip_ = vidManager_->createVideoClip(&memoryLoader_, TH_RGBA);
  if (vidClip_ == NULL) {
    setError("Failed to load video.");
    return false;
  }

  vidClip_->setAutoRestart(false);

  return true;
}

void sftheora::Video::unload()
{
  if (vidClip_ != NULL && vidManager_ != NULL) {
    vidManager_->destroyVideoClip(vidClip_);
    vidClip_ = NULL;
  }
}


void sftheora::Video::setLoop(bool loop)
{
  if (vidClip_ == NULL)
    return;

  vidClip_->setAutoRestart(loop);
}


TheoraVideoClip* sftheora::Video::getVideoClip() const
{
  return vidClip_;
}

sf::Time sftheora::Video::getDuration() const
{
  if (vidClip_ == NULL)
    return sf::Time::Zero;

  return sf::seconds(vidClip_->getDuration());
}

sf::Time sftheora::Video::getTime() const
{
  if (vidClip_ == NULL)
    return sf::Time::Zero;

  return sf::seconds(vidClip_->getTimePosition());
}

bool sftheora::Video::isLoop() const
{
  if (vidClip_ == NULL)
    return false;

  return vidClip_->getAutoRestart();
}

bool sftheora::Video::isPaused() const
{
  if (vidClip_ == NULL)
    return false;

  return vidClip_->isPaused();
}

bool sftheora::Video::isDone() const
{
  if (vidClip_ == NULL)
    return false;

  return vidClip_->isDone();
}

void sftheora::Video::togglePause() const
{
  if (vidClip_ == NULL)
    return;

  if (vidClip_->isPaused())
    vidClip_->play();
  else
    vidClip_->pause();
}

void sftheora::Video::play()
{
  if (vidClip_ == NULL)
    return;

  vidClip_->play();
}

void sftheora::Video::pause()
{
  if (vidClip_ == NULL)
    return;

  vidClip_->pause();
}

void sftheora::Video::restart()
{
  if (vidClip_ == NULL)
    return;

  vidClip_->restart();
}

void sftheora::Video::stop()
{
  if (vidClip_ == NULL)
    return;
  
  vidClip_->stop();
}

void sftheora::Video::seek(sf::Time time)
{
  if (vidClip_ == NULL)
    return;
  
  float seconds = time.asSeconds();

  if (seconds < 0.0f)
    seconds = 0.0f;
  else {
    float duration = vidClip_->getDuration();
    if (seconds > duration)
      seconds = duration;
  }
  
  vidClip_->seek(seconds);
}


bool sftheora::Video::init()
{
  vidClip_ = NULL;

  started_ = true;

  vidManager_ = new TheoraVideoManager();
  if (vidManager_ == NULL) {
    setError("Failed to initialize video.");
    return false;
  }

  ifaceFactory_ = new sftheora::AudioInterfaceFactory();
  if (ifaceFactory_ == NULL) {
    setError("Failed to initialize video.");
    return false;
  }

  vidManager_->setAudioInterfaceFactory(ifaceFactory_);

  return true;
}
