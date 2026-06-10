// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include		"lapin_private.h"

/**
 * @doc-symbol bunny_set_additional_blit
 * @doc-module graphics
 * @doc-kind function
 * @doc-order 462
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Enables or disables additive blending for the special blit path.
 * @description This changes the global blit mode used by the graphics backend.
 * @param enable true to enable additive blending, false to disable it.
 * @see bunny_blit, bunny_set_alpha_blit, bunny_set_multiply_blit
 *
 * @doc-lang fr
 * @brief Active ou désactive le mélange additif pour le chemin spécial de blit.
 * @description Cela modifie le mode global de blit utilisé par le backend graphique.
 * @param enable true pour activer le mélange additif, false pour le désactiver.
 * @see bunny_blit, bunny_set_alpha_blit, bunny_set_multiply_blit
 */
void			bunny_set_additional_blit(bool			blend)
{
  gl_set_additional_blit = blend;
}

