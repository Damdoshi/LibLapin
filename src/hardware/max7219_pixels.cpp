// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2022
//
// Bibliotheque Lapin

#include		"lapin_private.h"

bool			bunny_max7219_pixels(t_bunny_max7219		*m)
{
  int			w = m->width * 8;
  int			h = m->height * 8;

  for (size_t j = 0; j < m->height; ++j)
    {
      _bunny_max7219_start_word(m);
      for (size_t i = 0; i < m->width; ++i)
	{
	  uint8_t	buf = 0;
	  int		x = (i * 8) % w;
	  int		y = (i * 8) % h;

	  for (int l = 0; l < 8; ++l)
	    {
	      for (int k = 0; k < 8; ++k)
		buf = m->pixels[y * w + x] ? 1 << k : 0;

	      _bunny_max7219_write_data(m, BMC_SET_DIGIT0 + l);
	      _bunny_max7219_write_data(m, buf);
	    }
	}
      _bunny_max7219_end_word(m);
    }
  return (true);
}
