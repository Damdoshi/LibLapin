// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		<string.h>
#include		"lapin_private.h"

#ifdef			LAPIN_ALLOCATOR_DEACTIVATED
# undef			bunny_malloc
# undef			bunny_calloc
# undef			bunny_realloc
# undef			bunny_free
#endif

void			*bunny_calloc(size_t		nmemb,
				      size_t		data)
{
#ifdef			LAPIN_ALLOCATOR_DEACTIVATED
  return (calloc(nmemb, data));
#endif
  void			*ptr;
  int			i;

  if ((ptr = bunny_malloc(i = nmemb * data)) == NULL)
    return (NULL);
  return (memset(ptr, 0, i));
}

