// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include		"lapin_private.h"

/**
 * @doc-symbol bunny_get_maximum_picture_width
 * @doc-module graphics
 * @doc-kind function
 * @doc-order 550
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Returns the maximum texture width supported by the graphic backend.
 * @description This value comes from the backend and is useful before allocating very large pictures.
 * @return-success The maximum supported picture width.
 * @see bunny_new_picture
 *
 * @doc-lang fr
 * @brief Renvoie la largeur maximale de texture prise en charge par le backend graphique.
 * @description Cette valeur vient du backend et est utile avant d’allouer de très grandes pictures.
 * @return-success La largeur maximale de picture prise en charge.
 * @see bunny_new_picture
 */
size_t			bunny_get_maximum_picture_width(void)
{
  return (sf::Texture::getMaximumSize());
}

