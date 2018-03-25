// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		<stdlib.h>
#include		"lapin_private.h"

static FILE		*f[1024];

void			close_all_outputs(void)
{
  int			i;

  for (i = 0; i < 1024; ++i)
    if (f[i] != NULL)
      fclose(f[i]);
}

int			bunny_dprintf(int		fd,
				      const char	*format,
				      ...)
{
  va_list		lst;
  int			cnt;

  va_start(lst, format);
#if			_WIN32 || __WIN32__
  static bool		s;

  if (f[fd] == NULL)
    {
      if (s == false)
	{
	  atexit(close_all_outputs);
	  s = true;
	}
      if ((f[fd] = fdopen(fd, "w")) == NULL)
	return (-1);
    }

  cnt = vfprintf(f[fd], format, lst);
#else
  cnt = vdprintf(fd, format, lst);
#endif
  va_end(lst);
  return (cnt);
}

