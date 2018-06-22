// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		"lapin_private.h"

void			bunny_shuffle(void		*data,
				      size_t		datalen,
				      size_t		nmemb)
{
  char			*d = (char*)data;
  size_t		i;
  int			row;
  int			rnd;

  for (row = 0; row < 10; ++row)
    for (i = 0; i < nmemb; ++i)
      {
	rnd = (rand() + i) % nmemb;
	bunny_memswap(&d[i * datalen], &d[rnd * datalen], datalen);
      }
}
