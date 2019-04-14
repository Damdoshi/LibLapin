////////////////////////////////
// sfTheora 1.4.0             //
// Copyright � Kerli Low 2011 //
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

#ifndef SFTHEORA_ERROR_H
#define SFTHEORA_ERROR_H

#include <string>



namespace sftheora
{
  class Error;
}


///////////////////////////////////////////////////////////
// Error class                                           //
///////////////////////////////////////////////////////////
class sftheora::Error
{
public:
  Error() { error_ = ""; }

  const std::string& getError  () const;
  bool               hasError  () const;
  void               clearError();


protected:
  void setError(const std::string& error);


private:
  std::string error_;
};


///////////////////////////////////////////////////////////
// Error class                                           //
///////////////////////////////////////////////////////////
inline const std::string& sftheora::Error::getError() const
{
  return error_;
}

inline bool sftheora::Error::hasError() const
{
  return !error_.empty();
}

inline void sftheora::Error::clearError()
{
  error_.clear();
}


inline void sftheora::Error::setError(const std::string& error)
{
  error_ = error;
}



#endif // SFTHEORA_ERROR_H
