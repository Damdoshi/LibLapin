// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2017
//
// Lapin library

#include			"lapin_private.h"

t_bunny_font			*bunny_load_front(unsigned int			width,
						  unsigned int			height,
						  const char			*file,
						  const t_bunny_position	*size)
{
  t_bunny_font			*final;

  if (strstr(file, ".ttf"))
    {
      struct bunny_ttf_font	*ttf;

      if ((final = (t_bunny_font*)ttf = new (std::nothrow) struct bunny_ttf_font) == NULL)
	return (NULL);
      if (ttf->font.loadFromFile(file) == false)
	{
	  delete ttf;
	  return (NULL);
	}

      if ((ttf->texture = new (std::nothrow) sf::RenderTexture) == NULL)
	{
	  delete ttf;
	  return (NULL);
	}
      if (ttf->texture->create(width, height) == false)
	{
	  delete ttf;
	  return (NULL);
	}
      if ((ttf->sprite = new (std::nothrow) sf::Sprite) == NULL)
	{
	  delete ttf->texture;
	  delete ttf;
	  return (NULL);
	}
      ttf->text.setFont(ttf->font);
      ttf->text.setCharacterSize(size->y);
      ttf->texture->clear(sf::Color(0, 0, 0, 0));
      ttf->texture->display();
      ttf->tex = ttf->texture->getTexture();
      ttf->sprite->setTexture(*ttf->tex);
      ttf->type = TTF_TEXT;
    }
  else
    {
      struct bunny_gfx_font	*gfx;

      if ((final = (t_bunny_font*)gfx = new (std::nothrow) struct bunny_gfx_font) == NULL)
	return (NULL);
      if ((gfx->gfx = bunny_load_picture(file)) == NULL)
	{
	  delete gfx;
	  return (NULL);
	}

      if ((gfx->texture = new (std::nothrow) sf::RenderTexture) == NULL)
	{
	  bunny_delete_clipable(gfx->gfx);
	  delete gfx;
	  return (NULL);
	}
      if (gfx->texture->create(width, height) == false)
	{
	  delete ttf;
	  return (NULL);
	}
      if ((gfx->sprite = new (std::nothrow) sf::Sprite) == NULL)
	{
	  bunny_delete_clipable(gfx->gfx);
	  delete gfx->texture;
	  delete gfx;
	  return (NULL);
	}
      gfx->texture->clear(sf::Color(0, 0, 0, 0));
      gfx->texture->display();
      gfx->tex = gfx->texture->getTexture();
      gfx->sprite->setTexture(*gfx->tex);
      gfx->type = GRAPHIC_TEXT;
    }
  
  // Clipable properties
  final->width = width;
  final->height = height;
  final->rect.x = 0;
  final->rect.y = 0;
  final->rect.w = final->width;
  final->rect.h = final->height;
  final->position.x = 0;
  final->position.y = 0;
  final->origin.x = 0;
  final->origin.y = 0;
  final->scale.x = 1;
  final->scale.y = 1;
  final->rotation = 0;
  final->color_mask.full = WHITE;

  // Text properties
  final->string = NULL;
  final->hcrop = false;
  final->vcrop = true;
  final->hjustify = true;
  final->vjustify = false;
  final->halign = BA_LEFT;
  final->outline = 0;
  final->offset.x = 0;
  final->offset.y = 0;
  final->glyph_size.x = size->x;
  final->glyph_size.y = size->y;

  return (final);
}

