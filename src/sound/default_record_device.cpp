// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2021
//
// LibLapin

#include			"lapin_private.h"

const char			*bunny_default_device(void)
{
  static char			buf[512];

  if (buf[0] != '\0')
    return (&buf[0]);
  strncpy(&buf[0], sf::SoundBufferRecorder::getDefaultDevice().c_str(), sizeof(buf));
  return (&buf[0]);
}

