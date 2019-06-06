// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		"lapin_private.h"

t_bunny_string_couple	*bunny_search_string_couple(t_bunny_string_couple	*couple,
						    size_t			len,
						    const char			*a,
						    const char			*b)
{
  size_t		i;

  for (i = 0; i < len; ++i)
    if (strcmp(couple[i].first, a) == 0 && strcmp(couple[i].second, b) == 0)
      return (&couple[i]);
  return (NULL);
}

