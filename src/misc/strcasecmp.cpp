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
  return (tolower(*a) - tolower(*b));
}

int			bunny_strncasecmp(const char		*a,
					  const char		*b,
					  size_t		i)
{
  size_t		x;

  if (!i)
    return (0);
  for (x = 0; x < i && *a && *b && tolower(*a) == tolower(*b); ++x)
    {
      ++a;
      ++b;
    }
  if (x == i)
    return (0);
  return (tolower(*a) - tolower(*b));
}

