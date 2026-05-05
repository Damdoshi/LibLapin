// Jason Brillante "Damdoshi
// Hanged Bunny Studio 2014-2021
//
// LibLapin

#include			"lapin_private.h"

/**
 * @doc-symbol bunny_record_devices
 * @doc-module sound
 * @doc-kind function
 * @doc-order 640
 * @doc-since 13
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Returns the list of available recording devices.
 * @return-success A NULL-terminated array of device names.
 * @see bunny_default_record_device, bunny_record_available, bunny_new_recorder
 *
 * @doc-lang fr
 * @brief Renvoie la liste des périphériques d'enregistrement disponibles.
 * @return-success Un tableau de noms de périphériques terminé par NULL.
 * @see bunny_default_record_device, bunny_record_available, bunny_new_recorder
 */
const char			**bunny_record_devices(void)
{
  static char			*tab[512];
  static char			s[512][512];

  for (int i = 0; i < NBRCELL(tab); ++i)
    tab[i] = &s[i][0];
  auto const			&dev = sf::SoundBufferRecorder::getAvailableDevices();
  int				i;

  i = 0;
  for (auto it = dev.begin(); it != dev.end(); ++it)
    {
      strncpy(&s[i][0], it->c_str(), NBRCELL(s[i]));
      i = i + 1;
    }
  tab[i] = NULL;
  return ((const char**)&tab[0]);
}
