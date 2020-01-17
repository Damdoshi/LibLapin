// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		<stdlib.h>
#include		"lapin_private.h"

int			bunny_dprintf(int		fd,
				      const char	*format,
				      ...)
{
  char			buffer[1024 * 4];
  va_list		lst;
  int			cnt;
  int			i;

  va_start(lst, format);
  cnt = vsnprintf(&buffer[0], sizeof(buffer), format, lst);
  for (i = 0; i < cnt; ++i)
    if (buffer[i] == '\n' || buffer[i] == '\r')
      buffer[i] = ' ';
  if (write(fd, &buffer[0], cnt) == -1)
    return (-1);
  write(fd, "\n", 1);
  va_end(lst);
  return (cnt);
}

