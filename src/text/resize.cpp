// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

bool			bunny_font_resize(t_bunny_font		*fnt,
					  unsigned int		width,
					  unsigned int		height)
{
  struct bunny_picture	*pic = (struct bunny_picture*)fnt;

  if (pic->texture->create(width, height) == false)
    return (false);
  pic->texture->clear(sf::Color(0, 0, 0, 0));
  pic->texture->display();
  pic->tex = &pic->texture->getTexture();
  pic->sprite->setTexture(*pic->tex);
  if (pic->rect.w == pic->width && pic->rect.h == pic->height)
    {
      pic->rect.w = width;
      pic->rect.h = height;
    }
  pic->width = width;
  pic->height = height;
  return (true);
}

