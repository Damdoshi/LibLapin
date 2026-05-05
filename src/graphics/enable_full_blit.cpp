// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include		"lapin_private.h"

/**
 * @doc-symbol bunny_enable_full_blit
 * @doc-module graphics
 * @doc-kind function
 * @doc-order 460
 * @doc-since 9
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Enables or disables complete pixelarray source handling in bunny_blit.
 * @description When enabled, blits from pixelarrays support clipping, transformations and alpha handling more completely. The default is disabled.
 * @param enable true to enable full blit support, false to disable it.
 * @see bunny_blit, t_bunny_my_blit, gl_bunny_my_blit
 *
 * @doc-lang fr
 * @brief Active ou désactive la gestion complète des sources pixelarray dans bunny_blit.
 * @description Lorsque c’est activé, les blits depuis des pixelarrays prennent en charge plus complètement la découpe, les transformations et l’alpha. Par défaut, c’est désactivé.
 * @param enable true pour activer le support complet du blit, false pour le désactiver.
 * @see bunny_blit, t_bunny_my_blit, gl_bunny_my_blit
 */
void			bunny_enable_full_blit(bool			blend)
{
  gl_full_blit = blend;
}

