// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2019
//
// Lapin library

#include		<string.h>
#include		"lapin_private.h"

#define			PATTERN		"%s file -> %p"

static void		broadcast_set_animation(t_bunny_map		*nod,
						void			*p)
{
  t_bunny_clothe	*clothe = bunny_map_data(nod, t_bunny_clothe*);

  if (clothe)
    bunny_sprite_set_animation_id(clothe->sprite, *(uint64_t*)p);
}

bool			bunny_sprite_set_animation_id(t_bunny_sprite	*spr,
						      uint64_t		hash)
{
  struct bunny_sprite	&sprite = *(struct bunny_sprite*)spr;
  t_bunny_map		*map;

  if (sprite.current_animation_hash == hash)
    return (true);
  if (sprite.type == DRESSED_SPRITE)
    {
      struct bunny_dressed_sprite &dressed = (struct bunny_dressed_sprite&)sprite;

      bunny_map_foreach(dressed.clothes, broadcast_set_animation, &hash);
    }
  if (spr->animation == NULL)
    return (false);

  if ((map = bunny_map_get_subtree(sprite.hashname_id, (void*)hash, false)) == NULL)
    return (false);
  sprite.current_animation_hash = hash;
  sprite.current_animation = bunny_map_data(map, int32_t);
  sprite.current_repeat = 0;
  sprite.current_frame_repeat = 0;
  sprite.current_frame = 0;
  sprite.current_time = 0;

  t_bunny_animation	&anim = sprite.animation[sprite.current_animation];

  sprite.position.x = anim.position.x;
  sprite.position.y = anim.position.y;
  sprite.stop_repeat = false;
  return (true);
}

bool			bunny_sprite_set_animation_name(t_bunny_sprite	*spr,
							const char	*anim)
{
  return (bunny_sprite_set_animation_id(spr, bunny_hash(BH_DJB2, anim, strlen(anim))));
}
