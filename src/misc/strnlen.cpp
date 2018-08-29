// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin Library

#include		"lapin_private.h"

size_t			bunny_strnlen(const char	*str,
				      size_t		max)
{
  size_t		i;

  for (i = 0; str[i] && i < max; ++i);
  scream_log_if("%s string, %zu max_size -> %zu", "misc", str, max, i);
  return (i);
}

