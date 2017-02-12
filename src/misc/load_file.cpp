// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		<fcntl.h>
#include		<unistd.h>
#include		"lapin_private.h"

ssize_t			bunny_load_file(const char		*file,
					char			**data,
					size_t			*size)
{
  char			*buf;
  int			fd;
  int			sk, sz;

  if ((fd = open(file, O_RDONLY)) == -1)
    return (-1);
  if ((sk = lseek(fd, 0, SEEK_END)) == -1)
    goto close_and_quit;
  lseek(fd, 0, SEEK_SET);
  if (size == NULL)
    sz = sk + 1;
  else
    sz = sk;
  if ((buf = (char*)bunny_malloc(sz * sizeof(*buf))) == NULL)
    goto close_and_quit;
  if (read(fd, buf, sk) != sk)
    goto free_close_and_quit;
  buf[sk] = '\0';
  if (size)
    *size = sk;
  *data = buf;
  return (sk);

 free_close_and_quit:
  bunny_free(data);
 close_and_quit:
  close(fd);
  return (-1);
}

