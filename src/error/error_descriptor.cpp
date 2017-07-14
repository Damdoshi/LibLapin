// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		"lapin_private.h"

static int		error_descriptor = -1;

void			bunny_set_error_descriptor(int	fd)
{
  error_descriptor = fd;
}

int			bunny_get_error_descriptor(void)
{
  return (error_descriptor);
}


