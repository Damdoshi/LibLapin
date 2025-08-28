// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
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
  size_t		i;
  void			*ptr;

  // To ensure a precise behaviour everywhere
  if (!nmemb || !data)
    return (NULL);
# if			defined (__STDC_VERSION__) && __STDC_VERSION__ >= 202311L
  if (!ckd_mul(&i, nmemb, data))
    return (NULL);
#else
  i = nmemb * data;
#endif

#ifdef			LAPIN_ALLOCATOR_DEACTIVATED
  if ((ptr = calloc(nmemb, data)) == NULL)
    scream_error_if(return (NULL), errno, PATTERN, "allocator", nmemb, data, ptr);
  scream_log_if(PATTERN, "allocator", nmemb, data, ptr);
  return (ptr);
#endif
  if ((ptr = bunny_malloc(i)) == NULL)
    scream_error_if(return (NULL), errno, PATTERN, "allocator", nmemb, data, ptr);
  scream_log_if(PATTERN, "allocator", nmemb, data, ptr);
  return (memset(ptr, 0, i));
}

