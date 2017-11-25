// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin Library

#include		<string.h>
#include		"lapin_private.h"

int			bunny_strcasecmp(const char		*a,
					 const char		*b)
{
  while (*a && *b && tolower(*a) == tolower(*b))
    {
      ++a;
      ++b;
    }
  return (*a - *b);
}

int			bunny_strncasecmp(const char		*a,
					  const char		*b,
					  size_t		i)
{
  if (!i)
    return (0);
  while (*a && *b && tolower(*a) == tolower(*b))
    {
      if (i-- == 0)
	break ;
      ++a;
      ++b;
    }
  return (*a - *b);
}

