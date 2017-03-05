// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2017
//
// Lapin library

#include		"lapin_private.h"

t_bunny_font		*bunny_load_gfx_font(const char			*file,
					     const t_bunny_position	*pos)
{
  struct bunny_gfx_font	*fnt;
  sf::Texture		txt;
  sf::Sprite		spr;

  if (txt.loadFromFile(file) == false)
    goto Fail;
  spr.setTexture(txt);
  if ((fnt = new (std::nothrow) struct bunny_gfx_font) == NULL)
    goto Fail;
  if ((fnt->texture = new (std::nothrow) sf::RenderTexture) == NULL)
    goto FailStruct;
  if ((fnt->sprite = new (std::nothrow) sf::Sprite) == NULL)
    goto FailSprite;

  fnt->texture->create(txt.getSize().x, txt.getSize().y);
  fnt->texture->clear(sf::Color(0, 0, 0, 0));
  fnt->texture->draw(spr);
  fnt->texture->display();
  fnt->tex = &fnt->texture->getTexture();
  fnt->sprite->setTexture(*fnt->tex);

  fnt->type = GRAPHIC_TEXT;
  fnt->width = txt.getSize().x;
  fnt->height = txt.getSize().y;

  fnt->rect.x = 0;
  fnt->rect.y = 0;
  fnt->rect.w = pos->x;
  fnt->rect.h = pos->y;

  fnt->position.x = 0;
  fnt->position.y = 0;
  fnt->origin.x = 0;
  fnt->origin.y = 0;
  fnt->scale.x = 1;
  fnt->scale.y = 1;
  fnt->rotation = 0;
  fnt->color_mask.full = WHITE;

  fnt->string = NULL;
  fnt->hcrop = false;
  fnt->vcrop = true;
  fnt->justify = false;
  fnt->halign = BAL_LEFT;
  fnt->valign = BAL_TOP;
  fnt->outline = 0;

  BUNNY_LOG(fprintf(stderr, "%s: Returning %p.\n", __PRETTY_FUNCTION__, fnt));

  return ((t_bunny_font*)fnt);

 FailSprite:
  delete fnt->texture;
 FailStruct:
  delete fnt;
 Fail:
  return (NULL);
}

