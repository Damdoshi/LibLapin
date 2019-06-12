// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		"lapin_private.h"

int			bunny_sprite_collide(const t_bunny_sprite	*a,
					     const t_bunny_sprite	*b,
					     t_bunny_string_couple	*couple,
					     size_t			len)
{
  const t_bunny_collision_shapes *as;
  const t_bunny_collision_shapes *bs;

  as = bunny_sprite_get_collision(a);
  bs = bunny_sprite_get_collision(b);
  if (!as || !bs)
    return (-1);
  return
    (bunny_collision_nbr
     (as->collisions, as->nbr_collision, NULL, 0,
      bs->collisions, bs->nbr_collision, NULL, 0,
      couple, len
      ));
}

