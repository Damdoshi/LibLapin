// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

/**
 * @doc-symbol bunny_new_pixelarray
 * @doc-module graphics
 * @doc-kind function
 * @doc-order 30
 * @doc-since 0
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Creates a new pixelarray filled with PINK2.
 * @description The returned object is stored in LibLapin allocated memory and must be destroyed with bunny_delete_clipable.
 * @param wid The width in pixels.
 * @param hei The height in pixels.
 * @return-success A valid t_bunny_pixelarray.
 * @return-failure NULL if allocation fails.
 * @error ENOMEM Out of memory.
 * @log Logs are written with the "ressource" and "graphics" labels.
 * @see t_bunny_pixelarray, bunny_forge_pixelarray, bunny_load_pixelarray, bunny_delete_clipable
 *
 * @doc-lang fr
 * @brief Crée un nouveau pixelarray rempli avec PINK2.
 * @description L’objet renvoyé est stocké dans la mémoire allouée par la LibLapin et doit être détruit avec bunny_delete_clipable.
 * @param wid La largeur en pixels.
 * @param hei La hauteur en pixels.
 * @return-success Un t_bunny_pixelarray valide.
 * @return-failure NULL si l’allocation échoue.
 * @error ENOMEM Mémoire insuffisante.
 * @log Les logs sont écrits avec les labels "ressource" et "graphics".
 * @see t_bunny_pixelarray, bunny_forge_pixelarray, bunny_load_pixelarray, bunny_delete_clipable
 */
t_bunny_pixelarray	*bunny_new_pixelarray(unsigned int	width,
					      unsigned int	height)
{
  return (bunny_forge_pixelarray(width, height, NULL, BBW_ARGB_COLORS, false, NULL, 0));
}
