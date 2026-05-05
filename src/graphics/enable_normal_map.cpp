// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2026
//
// Bibliothèque Lapin

#include		"lapin_private.h"

extern bool		gl_normal_map;

/**
 * @doc-symbol bunny_enable_normal_map
 * @doc-module graphics
 * @doc-kind function
 * @doc-order 520
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Enables or disables automatic normal-map storage for newly created pictures.
 * @description When enabled, bunny_new_picture prepares the normal-map side resource used by normal-map rendering paths.
 * @param enable true to enable normal-map support, false to disable it.
 * @see bunny_new_picture, bunny_display_normal_map, bunny_swap_color_and_normal_map
 *
 * @doc-lang fr
 * @brief Active ou désactive le stockage automatique de normal map pour les nouvelles pictures.
 * @description Lorsque c’est activé, bunny_new_picture prépare la ressource latérale de normal map utilisée par les chemins de rendu en normal map.
 * @param enable true pour activer le support des normal maps, false pour le désactiver.
 * @see bunny_new_picture, bunny_display_normal_map, bunny_swap_color_and_normal_map
 */
void			bunny_enable_normal_map(bool			blend)
{
  gl_normal_map = blend;
}

