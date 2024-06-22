// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2022
//
// Bibliotheque Lapin

#include		"lapin_private.h"

bool			bunny_max7219_luminosity(t_bunny_max7219		*m)
{
  _bunny_max7219_start_word(m);
  for (size_t i = 0; i < m->width * m->height; ++i)
    {
      _bunny_max7219_write_data(m, BMC_SET_INTENSITY);
      _bunny_max7219_write_data(m, m->luminosity[i]);
    }
  _bunny_max7219_end_word(m);
  return (true);
}
