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

#define			PATTERN				"%zu nmemb, %zu size -> %p"

void			*bunny_calloc(size_t		nmemb,
				      size_t		data)
{
  void			*ptr;

#ifdef			LAPIN_ALLOCATOR_DEACTIVATED
  if ((ptr = calloc(nmemb, data)) == NULL)
    scream_error_if(return (NULL), errno, PATTERN, nmemb, data, ptr);
  scream_log_if(PATTERN, nmemb, data, ptr);
  return (ptr);
#endif

  int			i;

  if ((ptr = bunny_malloc(i = nmemb * data)) == NULL)
    scream_error_if(return (NULL), errno, PATTERN, nmemb, data, ptr);

  scream_log_if(PATTERN, nmemb, data, ptr);
  return (memset(ptr, 0, i));
}

