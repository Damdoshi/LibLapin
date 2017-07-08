// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		"lapin_private.h"

#define			PATTERN		"%p memory, %zu length -> %p"

t_bunny_picture		*bunny_read_picture(const void		*_pic,
					    size_t		len)
{
  struct bunny_picture	*pic;
  sf::Texture		txt;
  sf::Sprite		spr;

  if (txt.loadFromMemory(_pic, len) == false)
    scream_error_if(return (NULL), errno, PATTERN, _pic, len, (void*)NULL);
  spr.setTexture(txt);
  if ((pic = new (std::nothrow) struct bunny_picture) == NULL)
    goto Fail;
  if ((pic->texture = new (std::nothrow) sf::RenderTexture) == NULL)
    goto FailStruct;
  if ((pic->sprite = new (std::nothrow) sf::Sprite) == NULL)
    goto FailSprite;

  pic->texture->create(txt.getSize().x, txt.getSize().y);
  pic->texture->clear(sf::Color(0, 0, 0, 0));
  pic->texture->draw(spr);
  pic->texture->display();
  pic->tex = &pic->texture->getTexture();
  pic->sprite->setTexture(*pic->tex);

  pic->type = GRAPHIC_RAM;
  pic->width = pic->texture->getSize().x;
  pic->height = pic->texture->getSize().y;

  pic->rect.x = 0;
  pic->rect.y = 0;
  pic->rect.w = txt.getSize().x;
  pic->rect.h = txt.getSize().y;
  pic->position.x = 0;
  pic->position.y = 0;
  pic->origin.x = 0;
  pic->origin.y = 0;
  pic->scale.x = 1;
  pic->scale.y = 1;
  pic->rotation = 0;
  pic->color_mask.full = WHITE;

  scream_log_if(PATTERN, _pic, len, pic);
  return ((t_bunny_picture*)pic);

 FailSprite:
  delete pic->texture;
 FailStruct:
  delete pic;
 Fail:
  scream_error_if(return (NULL), ENOMEM, PATTERN, _pic, len, (void*)NULL);
  return (NULL);
}
