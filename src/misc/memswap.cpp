// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

void			bunny_memswap(void		*a,
				      void		*b,
				      size_t		s)
{
  void			*c = bunny_alloca(s);

  memcpy(c, a, s);
  memcpy(a, b, s);
  memcpy(b, c, s);
  bunny_freea(c);
}
