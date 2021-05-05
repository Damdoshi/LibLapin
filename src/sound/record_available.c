// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2021
//
// LibLapin

#include			"lapin_private.h"

bool				bunny_record_available(void)
{
  return (sf::SoundBufferRecorder::isAvailable());
}

