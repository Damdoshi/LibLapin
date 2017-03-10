// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin Library

#include		"lapin_private.h"

char			*bunny_strndup(const char	*str,
				       size_t		max)
{
  char			*s;
  size_t		i;

  s = (char*)bunny_malloc(sizeof(*s) + (max + 1));
  for (i = 0; str[i] && i < max; ++i)
    s[i] = str[i];
  s[i] = '\0';
  return (s);
}

