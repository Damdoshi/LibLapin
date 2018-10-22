// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

static void		copy_all(t_bunny_map		*node,
				 void			*param)
{
  bunny_map_set_data((t_bunny_map*)param, node->key, node->data, int);
}

t_bunny_sprite		*bunny_duplicate_sprite(t_bunny_sprite	*s)
{
  sf::Sprite		sprite;
  struct bunny_sprite	*spr = (struct bunny_sprite*)s;
  struct bunny_sprite	*nw;
  int			i, j;

  if ((nw = new (std::nothrow) bunny_sprite) == NULL)
    return (NULL);
  memcpy(nw, spr, sizeof(*nw));
  nw->type = SPRITE; // Because it may be a sprite derivated (like a dressed sprite)
  nw->res_id = 0;

  if ((nw->texture = new (std::nothrow) sf::RenderTexture) == NULL)
    goto DeleteSprite;
  if (nw->texture->create(spr->width, spr->height) == false)
    goto DeleteInnerTexture;
  nw->tex = &nw->texture->getTexture();
  if ((nw->sprite = new (std::nothrow) sf::Sprite) == NULL)
    goto DeleteInnerTexture;
  nw->sprite->setTexture(*nw->tex);

  // Deep copy of animations
  if ((nw->animation = bunny_new_vector
       (bunny_vector_size(s->animation), t_bunny_animation)) == NULL)
    goto DeleteSfSprite;
  for (i = 0; i < (int)bunny_vector_size(nw->animation); ++i)
    {
      t_bunny_animation &anim = bunny_vector_data(nw->animation, i, t_bunny_animation);
      t_bunny_animation &old = bunny_vector_data(s->animation, i, t_bunny_animation);

      memcpy(&anim, &old, sizeof(t_bunny_animation));
      if (old.frame_repetition)
	{
	  if ((anim.frame_repetition = bunny_new_vector
	       (bunny_vector_size(old.frame_repetition), int)) == NULL)
	    goto DeleteAnimation;
	  for (j = 0; j < (int)bunny_vector_size(anim.frame_repetition); ++j)
	    bunny_vector_data(anim.frame_repetition, j, int)
	      = bunny_vector_data(old.frame_repetition, j, int);
	}
    }

  // Deep copy of hashids
  if ((nw->hashname_id = bunny_new_map(NULL, NULL, NULL, NULL)) == NULL)
    goto DeleteAnimation;
  bunny_map_foreach(s->hashname_id, copy_all, nw->hashname_id);

  // Draw the previous picture on the new one
  sprite.setTexture(*spr->tex);
  nw->texture->clear(sf::Color(0, 0, 0, 0));
  nw->texture->draw(sprite);
  nw->texture->display();

  return ((t_bunny_sprite*)nw);

 DeleteAnimation:
  while (i >= 0)
    {
      t_bunny_animation &anim = bunny_vector_data(nw->animation, i, t_bunny_animation);

      if (anim.frame_repetition)
	bunny_delete_vector(anim.frame_repetition);
      i -= 1;
    }
  bunny_delete_vector(nw->animation);
 DeleteSfSprite:
  delete nw->sprite;
 DeleteInnerTexture:
  delete nw->texture;
 DeleteSprite:
  delete nw;
  return (NULL);
}
