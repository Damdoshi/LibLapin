// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2021
//
// LibLapin

#include	<stdio.h>
#include	"lapin_private.h"

/**
 * @doc-symbol bunny_default_record_device
 * @doc-module sound
 * @doc-kind function
 * @doc-order 650
 * @doc-since 13
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Returns the default recording device name.
 * @return-success Name of the default recording device.
 * @see bunny_record_devices, bunny_record_available, bunny_new_recorder
 *
 * @doc-lang fr
 * @brief Renvoie le nom du périphérique d'enregistrement par défaut.
 * @return-success Nom du périphérique d'enregistrement par défaut.
 * @see bunny_record_devices, bunny_record_available, bunny_new_recorder
 */
const char	*bunny_default_record_device(void)
{
  static char	buf[512];

  if (buf[0] != '\0')
    return (&buf[0]);
  snprintf(buf, sizeof(buf), "%s", sf::SoundBufferRecorder::getDefaultDevice().c_str());
  return (&buf[0]);
}

