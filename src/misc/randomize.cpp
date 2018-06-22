// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		"lapin_private.h"

void			bunny_randomize(void		*data,
					size_t		len)
{
  char			*ptr = (char*)data;
  size_t		i;

  for (i = 0; i < len; ++i)
    ptr[i] = rand() % 255;
}

