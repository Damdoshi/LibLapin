// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"


/**
 * @doc
 * @doc-symbol bunny_read_until_it_is_full
 * @doc-kind function
 * @doc-module parsing
 * @doc-order 390
 * @doc-since 12
 * @doc-until latest
 * @doc-level 40
 *
 * @doc-lang en
 * @brief Reads repeatedly until a buffer is full or the file descriptor stops producing data.
 * @param fd The file descriptor to read.
 * @param rd The destination buffer.
 * @param len The number of bytes to read.
 * @return-case success The number of bytes actually read.
 * @see t_bunny_binary_box
 *
 * @doc-lang fr
 * @brief Lit en boucle jusqu'à remplir un buffer ou jusqu'à ce que le descripteur cesse de produire des données.
 * @param fd Le descripteur de fichier à lire.
 * @param rd Le buffer de destination.
 * @param len Le nombre d'octets à lire.
 * @return-case success Le nombre d'octets effectivement lus.
 * @see t_bunny_binary_box
 */

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

