// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"


/**
 * @doc
 * @doc-symbol bunny_memswap
 * @doc-kind function
 * @doc-module misc
 * @doc-order 257
 * @doc-since 12
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Swaps two memory blocks of the same size.
 * @param a First memory block.
 * @param b Second memory block.
 * @param datalen Number of bytes to exchange.
 * @see bunny_swap, bunny_shuffle
 *
 * @doc-lang fr
 * @brief Échange deux blocs mémoire de même taille.
 * @param a Premier bloc mémoire.
 * @param b Deuxième bloc mémoire.
 * @param datalen Nombre d'octets à échanger.
 * @see bunny_swap, bunny_shuffle
 */
void			bunny_memswap(void		*a,
				      void		*b,
				      size_t		s)
{
  void			*c = bunny_alloca(s);

  memcpy(c, a, s);
  memcpy(a, b, s);
  memcpy(b, c, s);
  bunny_freea(c);
}
