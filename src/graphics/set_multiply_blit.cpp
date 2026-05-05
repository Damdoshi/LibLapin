// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include		"lapin_private.h"

/**
 * @doc-symbol bunny_set_multiply_blit
 * @doc-module graphics
 * @doc-kind function
 * @doc-order 463
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Enables or disables multiplicative blending for the special blit path.
 * @description This changes the global blit mode used by the graphics backend.
 * @param blend true to enable multiplicative blending, false to disable it.
 * @see bunny_blit, bunny_set_alpha_blit, bunny_set_additional_blit
 *
 * @doc-lang fr
 * @brief Active ou désactive le mélange multiplicatif pour le chemin spécial de blit.
 * @description Cela modifie le mode global de blit utilisé par le backend graphique.
 * @param blend true pour activer le mélange multiplicatif, false pour le désactiver.
 * @see bunny_blit, bunny_set_alpha_blit, bunny_set_additional_blit
 */
void			bunny_set_multiply_blit(bool			blend)
{
  gl_set_multiply_blit = blend;
}

