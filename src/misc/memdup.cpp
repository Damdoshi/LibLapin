// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		"lapin_private.h"

void			*bunny_memdup(const void		*dat,
				      size_t			len)
{
  void			*ptr;

  if ((ptr = bunny_malloc(len)) == NULL)
    return (NULL);
  return (memcpy(ptr, dat, len));
}

