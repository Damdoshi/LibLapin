// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2022
//
// Bibliotheque Lapin

#include		"lapin_private.h"


/**
 * @doc
 * @doc-symbol bunny_delete_max7219
 * @doc-kind function
 * @doc-module hardware
 * @doc-order 520
 * @doc-since 0
 * @doc-until latest
 * @doc-level 50
 *
 * @doc-lang en
 * @brief Destroys a MAX7219 descriptor and its working buffers.
 * @param m Descriptor to destroy.
 * @see bunny_new_max7219
 *
 * @doc-lang fr
 * @brief Détruit un descripteur MAX7219 et ses buffers de travail.
 * @param m Descripteur à détruire.
 * @see bunny_new_max7219
 */
void			bunny_delete_max7219(t_bunny_max7219		*m)
{
  bunny_free(m->pixels);
  bunny_free(m->luminosity);
  bunny_free(m);
}

