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

#ifndef SFTHEORA_VIDEO_H
#define SFTHEORA_VIDEO_H

#include <string>
#include <SFML/Graphics.hpp>

#include "theoraplayer/TheoraPlayer.h"
#include "theoraplayer/TheoraDataSource.h"
#include "AudioInterface.h"
#include "sfTheora/Error.h"
#include "sfTheora/MemoryLoader.h"



namespace sftheora
{
  class Video;
}


///////////////////////////////////////////////////////////
// Video class                                           //
///////////////////////////////////////////////////////////
class sftheora::Video : public sf::Sprite, public sftheora::Error
{
public:
  Video();
  explicit Video(const std::string& filename);
  explicit Video(TheoraDataSource* dataSource);
  Video(const std::string& repr, const void* data, unsigned long size);

  virtual ~Video();

  void update(sf::Time deltaTime);

  bool load  (const std::string& filename);
  bool load  (TheoraDataSource* dataSource);
  // data can be deleted after function ends
  bool load  (const std::string& repr, const void* data, unsigned long size);
  void unload();

  void setLoop(bool loop);

  TheoraVideoClip*  getVideoClip() const;
  sf::Time          getDuration () const;
  sf::Time          getTime     () const;
  bool              isLoop      () const;
  bool              isPaused    () const;
  bool              isDone      () const;

  void togglePause() const;

  void play   ();
  void pause  ();
  void restart();
  void stop   ();
  void seek   (sf::Time time);

private:
  bool init();


  TheoraVideoManager*              vidManager_;
  sftheora::AudioInterfaceFactory* ifaceFactory_;
  TheoraVideoClip*                 vidClip_;

  sftheora::MemoryLoader memoryLoader_;

  sf::Texture currentFrame_;

  bool started_;
};



#endif // SFTHEORA_VIDEO_H
