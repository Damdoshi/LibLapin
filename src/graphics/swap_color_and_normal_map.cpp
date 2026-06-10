// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2026
//
// Bibliothèque Lapin

#include		"lapin_private.h"

static void		swap(void						**a,
			     void						**b)
{
  void			*c;

  c = *a;
  *a = *b;
  *b = c;
}

/**
 * @doc-symbol bunny_swap_color_and_normal_map
 * @doc-module graphics
 * @doc-kind function
 * @doc-order 540
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Swaps the color texture and the normal-map texture of a picture-like clipable.
 * @description This helper is useful when debugging or when a picture has to expose its normal map through the usual color texture path.
 * @param s The picture-like clipable whose textures must be swapped.
 * @return-success true if the swap was performed.
 * @return-failure false if the clipable has no normal-map storage.
 * @see bunny_enable_normal_map, bunny_display_normal_map
 *
 * @doc-lang fr
 * @brief Échange la texture couleur et la texture de normal map d’un clipable de type picture.
 * @description Cet outil est utile pour le debug ou lorsqu’une picture doit exposer sa normal map par le chemin habituel de texture couleur.
 * @param s Le clipable de type picture dont les textures doivent être échangées.
 * @return-success true si l’échange a été effectué.
 * @return-failure false si le clipable ne possède pas de stockage de normal map.
 * @see bunny_enable_normal_map, bunny_display_normal_map
 */
bool			bunny_swap_color_and_normal_map(t_bunny_clipable	*s)
{
  struct bunny_picture	*pic = (struct bunny_picture*)s;

  if (pic->ntexture == NULL)
    return (false);
  swap((void**)&pic->ntexture, (void**)&pic->texture);
  swap((void**)&pic->ntex, (void**)&pic->tex);
  pic->sprite->setTexture(*pic->tex);
  return (true);
}

