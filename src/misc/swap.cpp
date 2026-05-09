// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"


/**
 * @doc
 * @doc-symbol bunny_swap
 * @doc-kind function
 * @doc-module misc
 * @doc-order 260
 * @doc-since 0
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Swaps two pointer values.
 * @param a Address of the first pointer.
 * @param b Address of the second pointer.
 * @log "misc"
 * @see bunny_memswap
 *
 * @doc-lang fr
 * @brief Échange deux valeurs de pointeur.
 * @param a Adresse du premier pointeur.
 * @param b Adresse du second pointeur.
 * @log "misc"
 * @see bunny_memswap
 */
void			bunny_swap(void			**a,
				   void			**b)
{
  void			*c = *a;

  *a = *b;
  *b = c;
  scream_log_if("%p first_elem, %p second_elem", "misc", a, b);
}

