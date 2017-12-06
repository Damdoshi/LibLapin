// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Bibliotheque Lapin

#include		"lapin_private.h"

size_t			bunny_ini_count_field(const t_bunny_ini		*ini,
					      const char		*scope,
					      const char		*field)
{
  size_t		i;

  for (i = 0; bunny_ini_get_field(ini, scope, field, i); ++i);
  scream_log_if
    ("%p ini, %s scope, %s field -> %zu",
     "configuration",
     ini, scope, field, i);
  return (i);
}

