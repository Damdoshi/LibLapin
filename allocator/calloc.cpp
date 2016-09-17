// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		<string.h>
#include		"lapin_private.h"

void			*bunny_calloc(size_t		nmemb,
				      size_t		data)
{
  void			*ptr;
  int			i;

  if ((ptr = bunny_malloc(i = nmemb * data)) == NULL)
    return (NULL);
  return (memset(ptr, 0, i));
}

