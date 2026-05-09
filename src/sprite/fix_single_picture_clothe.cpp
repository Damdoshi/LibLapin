// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2019
//
// Lapin library

#include		"lapin_private.h"

// This function turn into a copy of the sent sprite all defaulty filled closet sprites
// EXCEPT for the underlying picture.
// It is used by dressed sprite to avoid having to repeat big chunks of configuration


/**
 * @doc
 * @doc-symbol bunny_fix_single_picture_clothe
 * @doc-kind function
 * @doc-module sprite
 * @doc-order 570
 * @doc-since 0
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Optimizes a single-picture clothe for a dressed sprite.
 * @param sprite Dressed sprite used as reference.
 * @param closet Closet to inspect and possibly fix.
 * @return-success Returns true if the fix was applied or was unnecessary.
 * @return-failure Returns false on allocation or duplication failure.
 * @see bunny_dressed_sprite_wear
 *
 * @doc-lang fr
 * @brief Optimise un vêtement à image unique pour un sprite habillé.
 * @param sprite Sprite habillé utilisé comme référence.
 * @param closet Placard à inspecter et éventuellement corriger.
 * @return-success Renvoie true si le correctif a été appliqué ou était inutile.
 * @return-failure Renvoie false en cas d'échec d'allocation ou de duplication.
 * @see bunny_dressed_sprite_wear
 */
bool			bunny_fix_single_picture_clothe(t_bunny_dressed_sprite	*sprite,
							t_bunny_closet		*closet)
{
  t_bunny_map		**nod;

  for (bunny_map_all(closet->clothes, nod))
    {
      t_bunny_clothe	*clt = bunny_map_data(*nod, t_bunny_clothe*);
      t_bunny_sprite	*spr = clt->sprite;

      if (bunny_map_size(spr->hashname_id) != 1)
	continue ;
      if (!bunny_map_get_subtree(spr->hashname_id, (void*)(size_t)bunny_sprite_animation_name("Idle"), false))
	continue ;
      clt->sprite = bunny_duplicate_sprite(&sprite->sprite);
      if (bunny_make_clipable_unique(&clt->sprite->clipable) == false)
	{
	  bunny_delete_clipable(&clt->sprite->clipable);
	  clt->sprite = spr;
	  return (false);
	}
      struct bunny_sprite *oldsprite = (struct bunny_sprite*)spr;
      struct bunny_sprite *newsprite = (struct bunny_sprite*)clt->sprite;

      delete newsprite->texture;
      delete newsprite->sprite;
      newsprite->texture = oldsprite->texture;
      newsprite->tex = oldsprite->tex;
      newsprite->sprite = oldsprite->sprite;
      newsprite->res_id = oldsprite->res_id;
      oldsprite->texture = NULL;
      oldsprite->tex = NULL;
      oldsprite->sprite = NULL;
      oldsprite->res_id = 0;
      bunny_delete_clipable(&spr->clipable);
    }
  return (true);
}

