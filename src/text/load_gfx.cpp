// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2017
//
// Lapin library

#include			"lapin_private.h"

#define				PATTERN				\
  "%u width, %u height, %s file, %p (%d, %d) size -> %p"

t_bunny_font			*__bunny_load_gfx(unsigned int		width,
						  unsigned int		height,
						  const char		*file,
						  const t_bunny_position *size)
{
  struct bunny_gfx_font		*gfx;
  uint64_t			hash;

  bunny_errno = ENOMEM;
  if ((gfx = new (std::nothrow) struct bunny_gfx_font) == NULL)
    goto ReturnNull;
  if ((gfx->sprite = new (std::nothrow) sf::Sprite) == NULL)
    goto DeleteStructure;
  if ((gfx->texture = new (std::nothrow) sf::RenderTexture) == NULL)
    goto DeleteSprite;
  gfx->tex = &gfx->texture->getTexture();
  if (gfx->texture->create(width, height) == false)
    goto DeleteTexture;

  hash = bunny_hash(BH_FNV, file, strlen(file));
  if ((gfx->gfx = (t_bunny_picture*)RessourceManager.TryGet(ResManager::BUNNY_PICTURE, hash)) == NULL)
    {
      if ((gfx->gfx = bunny_load_picture(file)) == NULL)
	{
	  bunny_errno = EINVAL;
	  goto DeleteTexture;
	}
    }
  bunny_errno = 0;
  gfx->res_id = hash;

  gfx->gfx->clip_width = size->x;
  gfx->gfx->clip_height = size->y;
  gfx->texture->clear(sf::Color(0, 0, 0, 0));
  gfx->texture->display();
  gfx->tex = &gfx->texture->getTexture();
  gfx->sprite->setTexture(*gfx->tex);
  gfx->type = GRAPHIC_TEXT;
  gfx->glyph_size.x = size->x;
  gfx->glyph_size.y = size->y;

  scream_log_if(PATTERN, width, height, file, size, size->x, size->y, gfx);
  return ((t_bunny_font*)gfx);

 DeleteTexture:
  delete gfx->texture;
 DeleteSprite:
  delete gfx->sprite;
 DeleteStructure:
  delete gfx;
 ReturnNull:
  scream_error_if
    (return (NULL), bunny_errno, PATTERN, width, height, file, size, size->x, size->y, (void*)NULL);
  return (NULL);
}

