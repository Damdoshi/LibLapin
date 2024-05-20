// Jason Brillante "Damdoshi
// Hanged Bunny Studio 2014-2021
//
// LibLapin

#include			"lapin_private.h"

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
