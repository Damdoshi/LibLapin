// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include		"lapin_private.h"

/**
 * @doc-symbol bunny_set_alpha_blit
 * @doc-module graphics
 * @doc-kind function
 * @doc-order 461
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Enables or disables alpha blending for the special blit path.
 * @description This changes the global blit mode used by the graphics backend.
 * @param enable true to enable alpha blending, false to disable it.
 * @see bunny_blit, bunny_set_additional_blit, bunny_set_multiply_blit
 *
 * @doc-lang fr
 * @brief Active ou désactive le mélange alpha pour le chemin spécial de blit.
 * @description Cela modifie le mode global de blit utilisé par le backend graphique.
 * @param enable true pour activer le mélange alpha, false pour le désactiver.
 * @see bunny_blit, bunny_set_additional_blit, bunny_set_multiply_blit
 */
void			bunny_set_alpha_blit(bool			blend)
{
  gl_set_alpha_blit = blend;
}

