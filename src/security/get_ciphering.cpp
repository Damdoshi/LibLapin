// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		<string.h>
#include		"lapin_private.h"

t_bunny_ciphering	bunny_get_ciphering(const char		*name)
{
  size_t		i;

  for (i = 0; i < BS_CUSTOM; ++i)
    if (strcmp(name, gl_bunny_ciphering_table[i]) == 0)
      {
	scream_log_if("%s -> %zu", "security", name, i);
	return ((t_bunny_ciphering)i);
      }
  scream_log_if("%s -> %d", "security", name, BS_CUSTOM);
  return (BS_CUSTOM);
}

