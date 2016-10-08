// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		"lapin_private.h"

t_bunny_picture		*bunny_new_picture(unsigned int		width,
					   unsigned int		height)
{
  struct bunny_picture	*pic;

  if ((pic = new (std::nothrow) struct bunny_picture) == NULL)
    goto Fail;
  if ((pic->texture = new (std::nothrow) sf::RenderTexture) == NULL)
    goto FailStruct;

  pic->texture->create(width, height);
  pic->texture->clear(sf::Color(0, 0, 0, 0));
  pic->texture->display();
  pic->texture->setSmooth(false);
  pic->tex = &pic->texture->getTexture();
  pic->sprite.setTexture(*pic->tex);
  pic->type = GRAPHIC_RAM;
  pic->width = pic->rect.width = width;
  pic->height = pic->rect.height = height;
  pic->rect.left = 0;
  pic->rect.top = 0;
  pic->x_origin = 0;
  pic->y_origin = 0;
  pic->x_scale = 1;
  pic->y_scale = 1;
  pic->rotation = 0;
  pic->color_mask.full = WHITE;

  return ((t_bunny_picture*)pic);

 FailStruct:
  delete pic;
 Fail:
  return (NULL);
}
