// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
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
  if (RessourceManager.disable_manager ||
      (gfx->gfx = (t_bunny_picture*)RessourceManager.TryGet(ResManager::BUNNY_PICTURE, hash)) == NULL)
    {
      if ((gfx->gfx = bunny_load_picture(file)) == NULL)
	{
	  bunny_errno = EINVAL;
	  goto DeleteTexture;
	}
    }

  if (RessourceManager.disable_manager == false)
    RessourceManager.AddToPool(ResManager::BUNNY_PICTURE, file, hash, gfx, gfx->gfx);

  gfx->res_id = hash;
  gfx->texture->clear(sf::Color(0, 0, 0, 0));
  gfx->texture->display();
  gfx->tex = &gfx->texture->getTexture();
  gfx->sprite->setTexture(*gfx->tex);
  gfx->type = GRAPHIC_TEXT;

  /*
  if (bunny_which_format(file) != BC_CUSTOM)
    {
      if (bunny_set_text_attribute(file, gfx, NULL, false) == false)
	goto DeletePicture;
      return (true);
    }
  */
  bunny_errno = 0;

  gfx->gfx->clip_width = size->x;
  gfx->gfx->clip_height = size->y;
  gfx->glyph_size.x = size->x;
  gfx->glyph_size.y = size->y;
  gfx->conf_string = NULL;
  gfx->smooth = false;
  gfx->mosaic = false;

  scream_log_if(PATTERN, "ressource,graphics", width, height, file, size, size->x, size->y, gfx);
  return ((t_bunny_font*)gfx);

  /*
    DeletePicture:
    bunny_delete_clipable(gfx->gfx);
  */
 DeleteTexture:
  delete gfx->texture;
 DeleteSprite:
  delete gfx->sprite;
 DeleteStructure:
  delete gfx;
 ReturnNull:
  scream_error_if
    (return (NULL), bunny_errno, PATTERN, "ressource,graphics", width, height, file, size, size->x, size->y, (void*)NULL);
  return (NULL);
}

