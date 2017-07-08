// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		<fcntl.h>
#include		<unistd.h>
#include		"lapin_private.h"

#define			PATTERN		"%s file, %p target for data, %p target for data size -> %zd"

ssize_t			bunny_load_file(const char		*file,
					char			**data,
					size_t			*size)
{
  char			*buf;
  int			fd;
  int			sk, sz;

  if ((fd = open(file, O_RDONLY)) == -1)
    scream_error_if(return (-1), bunny_errno, PATTERN, file, data, size, (ssize_t)-1);
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
  scream_log_if(PATTERN, file, data, size, (ssize_t)sk);
  return (sk);

 free_close_and_quit:
  sk = bunny_errno;
  bunny_free(data);
  bunny_errno = sk;
 close_and_quit:
  close(fd);
  scream_error_if(return (-1), bunny_errno, PATTERN, file, data, size, (ssize_t)-1);
  return (-1);
}

