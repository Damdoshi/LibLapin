// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		"lapin_private.h"

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

