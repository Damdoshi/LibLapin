// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2026
//
// Bibliothèque Lapin

#include		"lapin_private.h"

extern bool		gl_display_normal_map;

/**
 * @doc-symbol bunny_display_normal_map
 * @doc-module graphics
 * @doc-kind function
 * @doc-order 530
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Selects whether normal-map rendering displays the normal map instead of the color map.
 * @description This is a global debug/display switch used by the normal-map shader path.
 * @param enable true to display the normal map, false to display the color map.
 * @see bunny_enable_normal_map, bunny_swap_color_and_normal_map
 *
 * @doc-lang fr
 * @brief Choisit si le rendu normal-map affiche la normal map au lieu de la color map.
 * @description C’est un interrupteur global de debug/affichage utilisé par le chemin de shader normal-map.
 * @param enable true pour afficher la normal map, false pour afficher la color map.
 * @see bunny_enable_normal_map, bunny_swap_color_and_normal_map
 */
void			bunny_display_normal_map(bool			blend)
{
  gl_display_normal_map = blend;
}

