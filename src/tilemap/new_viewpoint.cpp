// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include		"lapin_private.h"

t_bunny_tilemap		*bunny_tilemap_new_viewpoint(t_bunny_tilemap	*tm,
						     unsigned int	width,
						     unsigned int	height)
{
  struct bunny_tilemap	*old = (struct bunny_tilemap*)tm;
  struct bunny_tilemap	*nw;
  int			length;

  // Make a copy
  if ((nw = (struct bunny_tilemap*)bunny_memdup(old, sizeof(*old))) == NULL)
    return (NULL);
  // Annotate that is a shallow copy
  nw->duplicated_tilemap = true;
  nw->res_id = 0;

  // Create a new clipable inside the tilemap
  if ((nw->texture = new (std::nothrow) sf::RenderTexture) == NULL)
    goto DeleteTilemap;
  if (nw->texture->create(width, height) == false)
    goto DeleteTexture;
  if ((nw->sprite = new (std::nothrow) sf::Sprite) == NULL)
    goto DeleteTexture;
  length = sqrt(width * width + height * height) * 1.05;
  if ((nw->working = bunny_new_picture(length, length)) == NULL)
    goto DeleteSprite;

  // Set basic values
  nw->width = width;
  nw->height = height;
  nw->rect.x = 0;
  nw->rect.y = 0;
  nw->rect.w = width;
  nw->rect.h = height;

  // Set texture status
  nw->texture->clear(sf::Color(0, 0, 0, 0));
  nw->texture->display();
  nw->texture->setSmooth(false);
  nw->tex = &nw->texture->getTexture();
  nw->sprite->setTexture(*nw->tex);

  // Set working picture status
  nw->working->origin.x = nw->working->buffer.width / 2.0;
  nw->working->origin.y = nw->working->buffer.height / 2.0;
  nw->working->position.x = nw->width / 2.0;
  nw->working->position.y = nw->height / 2.0;
  nw->working_target_diff.x = (nw->working->buffer.width - nw->width) / 2;
  nw->working_target_diff.y = (nw->working->buffer.height - nw->height) / 2;

  return ((t_bunny_tilemap*)nw);

 DeleteSprite:
  delete nw->sprite;
 DeleteTexture:
  delete nw->texture;
 DeleteTilemap:
  bunny_free(nw);
  return (NULL);
}

