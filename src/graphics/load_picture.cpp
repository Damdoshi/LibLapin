// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		"lapin_private.h"

t_bunny_picture		*bunny_load_picture(const char	*file)
{
  struct bunny_picture	*pic;
  sf::Texture		txt;
  sf::Sprite		spr;

  // This work with sf::Texture txt and pic->texture is made because
  // bunny_picture needs to be able to be modified but cannot load
  // file...
  if (txt.loadFromFile(file) == false)
    goto Fail;
  spr.setTexture(txt);
  if ((pic = new (std::nothrow) struct bunny_picture) == NULL)
    goto Fail;
  if ((pic->texture = new (std::nothrow) sf::RenderTexture) == NULL)
    goto FailStruct;
  if ((pic->sprite = new (std::nothrow) sf::Sprite) == NULL)
    goto FailSprite;
  if (pic->texture->create(txt.getSize().x, txt.getSize().y) == false)
    goto FailSprite;

  pic->texture->clear(sf::Color(0, 0, 0, 0));
  pic->texture->draw(spr);
  pic->texture->display();
  pic->tex = &pic->texture->getTexture();
  pic->sprite->setTexture(*pic->tex);

  pic->type = GRAPHIC_RAM;
  pic->width = txt.getSize().x;
  pic->height = txt.getSize().y;

  pic->rect.x = 0;
  pic->rect.y = 0;
  pic->rect.w = pic->width;
  pic->rect.h = pic->height;

  pic->position.x = 0;
  pic->position.y = 0;
  pic->origin.x = 0;
  pic->origin.y = 0;
  pic->scale.x = 1;
  pic->scale.y = 1;
  pic->rotation = 0;
  pic->color_mask.full = WHITE;

  BUNNY_LOG(fprintf(stderr, "%s: Returning %p.\n", __PRETTY_FUNCTION__, pic));

  return ((t_bunny_picture*)pic);

 FailSprite:
  delete pic->texture;
 FailStruct:
  delete pic;
 Fail:
  return (NULL);
}
