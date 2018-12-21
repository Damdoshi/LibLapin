// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

#define			PATTERN		"%p data, %zu data length -> %p"

void			*bunny_memdup(const void		*dat,
				      size_t			len)
{
  void			*ptr;

  if ((ptr = bunny_malloc(len)) == NULL)
    scream_error_if(return (NULL), bunny_errno, PATTERN, "misc", dat, len, (void*)NULL);
  scream_log_if(PATTERN, "misc", dat, len, ptr);
  return (memcpy(ptr, dat, len));
}

