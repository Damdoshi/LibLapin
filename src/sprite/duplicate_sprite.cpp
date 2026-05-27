// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

static void		copy_all(t_bunny_map		*node,
				 void			*param)
{
  bunny_map_set_data((t_bunny_map*)param, node->key, node->data, void*);
}


/**
 * @doc
 * @doc-symbol bunny_duplicate_sprite
 * @doc-kind function
 * @doc-module sprite
 * @doc-order 185
 * @doc-since 0
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Duplicates a sprite object.
 * @param duplicate Sprite to duplicate.
 * @return-success Returns a newly allocated duplicate sprite.
 * @return-failure Returns NULL on allocation failure.
 * @see bunny_load_sprite, bunny_delete_clipable
 *
 * @doc-lang fr
 * @brief Duplique un objet sprite.
 * @param duplicate Sprite à dupliquer.
 * @return-success Renvoie un sprite dupliqué nouvellement alloué.
 * @return-failure Renvoie NULL en cas d'échec d'allocation.
 * @see bunny_load_sprite, bunny_delete_clipable
 */
t_bunny_sprite		*bunny_duplicate_sprite(t_bunny_sprite	*s)
{
  struct bunny_sprite	*spr = (struct bunny_sprite*)s;
  sf::Sprite		sprite(*spr->tex);
  struct bunny_sprite	*nw;
  int			i, j;

  if ((nw = new (std::nothrow) bunny_sprite) == NULL)
    return (NULL);
  memcpy(nw, spr, sizeof(*nw));
  nw->type = SPRITE; // Because it may be a sprite derivated (like a dressed sprite)
  nw->res_id = 0;

  if ((nw->texture = new (std::nothrow) sf::RenderTexture({spr->width, spr->height})) == NULL)
    goto DeleteSprite;
  nw->tex = &nw->texture->getTexture();
  if ((nw->sprite = new (std::nothrow) sf::Sprite(*nw->tex)) == NULL)
    goto DeleteInnerTexture;

  // Deep copy of animations
  if ((nw->animation = (t_bunny_animation*)bunny_calloc
       (s->nbr_animation, sizeof(t_bunny_animation))) == NULL)
    goto DeleteSfSprite;
  for (i = 0; i < (int)s->nbr_animation; ++i)
    {
      t_bunny_animation &anim = nw->animation[i];
      t_bunny_animation &old = s->animation[i];

      memcpy(&anim, &old, sizeof(t_bunny_animation));
      if (old.frame_repetition)
	{
	  if ((anim.frame_repetition = (int*)bunny_calloc
	       (old.nbr_frame, sizeof(int))) == NULL)
	    goto DeleteAnimation;
	  for (j = 0; j < (int)anim.nbr_frame; ++j)
	    anim.frame_repetition[j] = old.frame_repetition[j];
	}
    }

  // Deep copy of hashids
  if ((nw->hashname_id = bunny_new_map(NULL, NULL, NULL, NULL)) == NULL)
    goto DeleteAnimation;
  bunny_map_foreach(s->hashname_id, copy_all, nw->hashname_id);

  // Draw the previous picture on the new one

  nw->texture->clear(sf::Color(0, 0, 0, 0));
  nw->texture->draw(sprite);
  nw->texture->display();

  return ((t_bunny_sprite*)nw);

 DeleteAnimation:
  while (i >= 0)
    {
      t_bunny_animation &anim = nw->animation[i];

      if (anim.frame_repetition)
	bunny_free(anim.frame_repetition);
      i -= 1;
    }
  bunny_free(nw->animation);
 DeleteSfSprite:
  delete nw->sprite;
 DeleteInnerTexture:
  delete nw->texture;
 DeleteSprite:
  delete nw;
  return (NULL);
}
