// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

uint64_t		bunny_sprite_get_animation(const t_bunny_sprite	*_sprite)
{
  t_bunny_sprite	*sprite = (t_bunny_sprite*)_sprite;

  return (bunny_vector_data
	  (sprite->animation, sprite->current_animation, t_bunny_animation).hash);
}

