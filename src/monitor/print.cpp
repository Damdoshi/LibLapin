// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin Library

#include		<unistd.h>
#include		"lapin_private.h"

ssize_t			bunny_print_monitored_value(int			fd,
						    const char		*n)
{
  size_t		l;

  l = _bunny_monitor_prepare_buffer(&bunny_big_buffer[0], sizeof(bunny_big_buffer), n);
  return (write(fd, bunny_big_buffer, l));
}

