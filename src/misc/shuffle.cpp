// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"


/**
 * @doc
 * @doc-symbol bunny_shuffle
 * @doc-kind function
 * @doc-module misc
 * @doc-order 256
 * @doc-since 12
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Shuffles an array in place.
 * @param data Array storage.
 * @param datalen Size of one element in bytes.
 * @param nmemb Number of elements in the array.
 * @see bunny_memswap, bunny_randomize
 *
 * @doc-lang fr
 * @brief Mélange un tableau sur place.
 * @param data Stockage du tableau.
 * @param datalen Taille d'un élément en octets.
 * @param nmemb Nombre d'éléments dans le tableau.
 * @see bunny_memswap, bunny_randomize
 */
void			bunny_shuffle(void		*data,
				      size_t		datalen,
				      size_t		nmemb)
{
  char			*d = (char*)data;
  size_t		i;
  int			row;
  int			rnd;

  for (row = 0; row < 10; ++row)
    for (i = 0; i < nmemb; ++i)
      {
	rnd = (rand() + i) % nmemb;
	bunny_memswap(&d[i * datalen], &d[rnd * datalen], datalen);
      }
}
