// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		"lapin_private.h"

static int		log_descriptor = STDOUT_FILENO;

void			bunny_set_log_descriptor(int	fd)
{
  log_descriptor = fd;
}

int			bunny_get_log_descriptor(void)
{
  return (log_descriptor);
}


