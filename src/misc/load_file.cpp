// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include			"lapin_private.h"

char				*bunny_load_file(const char		*file,
						 size_t			*size)
{
  char				*n;
  int				fd;

  if ((fd = open(file, O_RDONLY)) == -1)
    return (NULL);
  if ((*size = lseek(fd, 0, SEEK_END)) == -1)
    {
      close(fd);
      return (NULL);
    }
  lseek(fd, 0, SEEK_SET);
  if ((n = bunny_malloc(*size)) == NULL)
    {
      close(fd);
      return (NULL);
    }
  if (read(fd, n, *size) != *size)
    {
      bunny_free(n);
      close(fd);
      return (NULL);
    }
  return (n);
}

