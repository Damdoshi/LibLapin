// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		"lapin_private.h"

void			bunny_perror(const char		*str)
{
  if (!str || *str)
    fprintf(stderr, "%s\n", bunny_strerror(bunny_errno));
  else
    fprintf(stderr, "%s: %s\n", str, bunny_strerror(bunny_errno));
}

