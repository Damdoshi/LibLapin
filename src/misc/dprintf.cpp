// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		<stdlib.h>
#include		"lapin_private.h"

int			bunny_dprintf(int		fd,
				      const char	*format,
				      ...)
{
  va_list		lst;
  int			cnt;

  va_start(lst, format);
#if			_WIN32 || __WIN32__
  char			buffer[1024 * 4];

  cnt = vsnprintf(&buffer[0], sizeof(buffer), format, lst);
  if (write(fd, &buffer[0], cnt) == -1)
    return (-1);
#else
  cnt = vdprintf(fd, format, lst);
#endif
  va_end(lst);
  return (cnt);
}

