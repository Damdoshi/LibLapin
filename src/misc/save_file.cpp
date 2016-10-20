// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include			<fcntl.h>
#include			"lapin_private.h"

bool				bunny_save_file(const char		*file,
						const char		*data,
						size_t			len)
{
  int				fd;

  if ((fd = open(file, O_CREAT | O_TRUNC | O_WRONLY, 0644)) == -1)
    return (false);
  if (write(fd, data, len) != (ssize_t)len)
    {
      close(fd);
      return (false);
    }
  close(fd);
  return (true);
}

