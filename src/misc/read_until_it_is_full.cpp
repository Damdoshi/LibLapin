// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

size_t			bunny_read_until_it_is_full(int		fd,
						    void	*_rd,
						    size_t	total)
{
  char			*rd = (char*)_rd;
  ssize_t		acc;
  ssize_t		rdd;

  acc = 0;
  do
    {
      if ((rdd = read(fd, &rd[acc], total - acc)) <= 0)
	return (acc);
      acc += rdd;
    }
  while ((size_t)acc < total);
  return (acc);
}

