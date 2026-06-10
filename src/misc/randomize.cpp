// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"


/**
 * @doc
 * @doc-symbol bunny_randomize
 * @doc-kind function
 * @doc-module misc
 * @doc-order 255
 * @doc-since 12
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Fills a memory block with random bytes.
 * @param data Memory block to fill.
 * @param len Number of bytes to write.
 *
 * @doc-lang fr
 * @brief Remplit un bloc mémoire avec des octets aléatoires.
 * @param data Bloc mémoire à remplir.
 * @param len Nombre d'octets à écrire.
 */
void			bunny_randomize(void		*data,
					size_t		len)
{
  char			*ptr = (char*)data;
  size_t		i;

  for (i = 0; i < len; ++i)
    ptr[i] = rand() % 255;
}

