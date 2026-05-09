// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2019
//
// Lapin library

#include		<string.h>
#include		"lapin_private.h"

#define			PATTERN		"%s file -> %p"

static void		broadcast_shift_animation(t_bunny_map		*nod,
						  void			*p)
{
  t_bunny_clothe	*clothe = bunny_map_data(nod, t_bunny_clothe*);

  if (clothe)
    bunny_sprite_shift_animation_id(clothe->sprite, *(uint64_t*)p);
}


/**
 * @doc
 * @doc-symbol bunny_sprite_shift_animation_id
 * @doc-kind function
 * @doc-module sprite
 * @doc-order 265
 * @doc-since 0
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Requests a transition to another sprite animation by hash.
 * @param sprite Sprite to update.
 * @return-success Returns true if the animation exists and the shift was accepted.
 * @return-failure Returns false if the animation does not exist.
 * @see bunny_sprite_shift_animation_name
 *
 * @doc-lang fr
 * @brief Demande une transition vers une autre animation de sprite par hash.
 * @param sprite Sprite à mettre à jour.
 * @return-success Renvoie true si l'animation existe et que le changement est accepté.
 * @return-failure Renvoie false si l'animation n'existe pas.
 * @see bunny_sprite_shift_animation_name
 */
bool			bunny_sprite_shift_animation_id(t_bunny_sprite	*spr,
							uint64_t	hash)
{
  struct bunny_sprite	&sprite = *(struct bunny_sprite*)spr;
  t_bunny_map		*map;

  if (sprite.type == DRESSED_SPRITE)
    {
      struct bunny_dressed_sprite &dressed = (struct bunny_dressed_sprite&)sprite;

      bunny_map_foreach(dressed.clothes, broadcast_shift_animation, &hash);
    }
  if (spr->animation == NULL)
    return (false);
  int32_t		anim;

  if ((map = bunny_map_get_subtree(sprite.hashname_id, (void*)hash, false)) == NULL)
    return (false);
  // Check animations are compatible
  anim = bunny_map_data(map, int32_t);
  if (sprite.animation[sprite.current_animation].nbr_frame != sprite.animation[anim].nbr_frame)
    return (false);

  sprite.current_animation = anim;
  sprite.current_animation_hash = hash;

  t_bunny_animation	&ani = sprite.animation[anim];

  sprite.position.x = ani.position.x;
  sprite.position.y = ani.position.y;
  return (true);
}


/**
 * @doc
 * @doc-symbol bunny_sprite_shift_animation_name
 * @doc-kind function
 * @doc-module sprite
 * @doc-order 245
 * @doc-since 0
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Requests a transition to another sprite animation by name.
 * @param sprite Sprite to update.
 * @return-success Returns true if the animation exists and the shift was accepted.
 * @return-failure Returns false if the animation does not exist.
 * @see bunny_sprite_shift_animation_id
 *
 * @doc-lang fr
 * @brief Demande une transition vers une autre animation de sprite par nom.
 * @param sprite Sprite à mettre à jour.
 * @return-success Renvoie true si l'animation existe et que le changement est accepté.
 * @return-failure Renvoie false si l'animation n'existe pas.
 * @see bunny_sprite_shift_animation_id
 */
bool			bunny_sprite_shift_animation_name(t_bunny_sprite *spr,
							  const char	*anim)
{
  return (bunny_sprite_shift_animation_id(spr, bunny_hash(BH_DJB2, anim, strlen(anim))));
}

