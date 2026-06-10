// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		"lapin_private.h"


/**
 * @doc
 * @doc-symbol bunny_dressed_sprite_wear
 * @doc-kind function
 * @doc-module sprite
 * @doc-order 560
 * @doc-since 0
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Changes the clothe worn in one closet of a dressed sprite.
 * @param sprite Dressed sprite to update.
 * @param closet Closet name.
 * @param clothe Clothe name inside closet.
 * @return-success Returns true if the closet and clothe exist and were selected.
 * @return-failure Returns false otherwise.
 * @see bunny_render_dressed_sprite
 *
 * @doc-lang fr
 * @brief Change le vêtement porté dans un placard d'un sprite habillé.
 * @param sprite Sprite habillé à mettre à jour.
 * @param closet Nom du placard.
 * @param clothe Nom du vêtement dans le placard.
 * @return-success Renvoie true si le placard et le vêtement existent et ont été sélectionnés.
 * @return-failure Renvoie false sinon.
 * @see bunny_render_dressed_sprite
 */
bool			bunny_dressed_sprite_wear(t_bunny_dressed_sprite	*sprite,
						  const char			*closet_name,
						  const char			*clothe_name)
{
  t_bunny_closet	*closet;
  t_bunny_clothe	*clothe;
  t_bunny_hash		hs_closet;
  t_bunny_hash		hs_clothe;

  hs_closet = bunny_hash(BH_DJB2, closet_name, strlen(closet_name));
  if ((closet = bunny_map_get_data(sprite->closets, hs_closet, t_bunny_closet*)) == NULL)
    return (false);
  hs_clothe = bunny_hash(BH_DJB2, clothe_name, strlen(clothe_name));
  if ((clothe = bunny_map_get_data(closet->clothes, hs_clothe, t_bunny_clothe*)) == NULL)
    return (false);
  if (bunny_map_set_data(sprite->clothes, hs_closet, clothe, t_bunny_clothe*) == NULL)
    return (false);
  return (true);
}

