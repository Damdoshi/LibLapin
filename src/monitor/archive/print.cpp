// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin Library

#include		<unistd.h>
#include		"lapin_private.h"

ssize_t			bunny_print_monitored_value(int			fd,
						    const char		*n)
{
  size_t		l;

  l = _bunny_monitor_prepare_buffer(&gl_monitor_buffer[0], sizeof(gl_monitor_buffer), n);
  return (write(fd, gl_monitor_buffer, l));
}

