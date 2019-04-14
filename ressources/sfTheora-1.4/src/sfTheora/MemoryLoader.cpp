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

#include <cstring>

#include "sfTheora/MemoryLoader.h"



///////////////////////////////////////////////////////////
// Memory Loader class                                   //
///////////////////////////////////////////////////////////
sftheora::MemoryLoader::MemoryLoader()
{
  data_ = NULL;

  size_ = offset_ = 0;
}

sftheora::MemoryLoader::MemoryLoader
  (const std::string& repr, const void* data, unsigned long size)
{
  repr_ = repr;
  size_ = size;
  
  data_ = new char[size];
  memset(data_, 0, size);
  memcpy(data_, data, size);

  offset_ = 0;
}


sftheora::MemoryLoader::~MemoryLoader()
{
  release();
}


void sftheora::MemoryLoader::release()
{
  if (data_ != NULL) {
    delete[] reinterpret_cast<char*>(data_);
    data_ = NULL;
  }

  size_ = offset_ = 0;
}


void sftheora::MemoryLoader::set
  (const std::string& repr, const void* data, unsigned long size)
{
  release();

  repr_ = repr;
  size_ = size;
  
  data_ = new char[size];
  memset(data_, 0, size);
  memcpy(data_, data, size);

  offset_ = 0;
}


int sftheora::MemoryLoader::read(void* output, int nBytes)
{
  int rem = static_cast<int>(size_ - offset_);
  int size = nBytes < rem ? nBytes : rem;

  memcpy(output, static_cast<char*>(data_) + offset_, size);

  offset_ += size;

  return size;
}

std::string sftheora::MemoryLoader::repr()
{
  return repr_;
}

void sftheora::MemoryLoader::seek(unsigned long byte_index)
{
  offset_ = byte_index;
}

unsigned long sftheora::MemoryLoader::size()
{
  return size_;
}

unsigned long sftheora::MemoryLoader::tell()
{
  return offset_;
}
