// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2019
//
// Lapin library

#include		<stdio.h>
#define			__LAPIN_H__
#include		"lapin2/error.h"

void			bunny_perror(const char		*str)
{
  if (str && *str)
    fprintf(stderr, "%s: ", str);
  fprintf(stderr, "%s\n", bunny_strerror(bunny_errno));
}

