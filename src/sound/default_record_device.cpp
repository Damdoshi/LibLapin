// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2021
//
// LibLapin

#include	<stdio.h>
#include	"lapin_private.h"

const char	*bunny_default_record_device(void)
{
  static char	buf[512];

  if (buf[0] != '\0')
    return (&buf[0]);
  snprintf(buf, sizeof(buf), "%s", sf::SoundBufferRecorder::getDefaultDevice().c_str());
  return (&buf[0]);
}

