// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include			<string.h>
#include			"lapin_private.h"

#define				PATTERN		\
  "%u width, %u height, %s file, %p (%d, %d) size -> %p"

t_bunny_font			*__bunny_load_ttf(unsigned int		width,
						  unsigned int		height,
						  const char		*file,
						  const t_bunny_position *size)
{
  struct bunny_ttf_font		*ttf;
  uint64_t			hash;
  bool				in_pool;

  in_pool = false;
  bunny_errno = ENOMEM;
  if ((ttf = new (std::nothrow) struct bunny_ttf_font) == NULL)
    goto ReturnNull;
  ttf->ntexture = NULL;
  ttf->ntex = NULL;
  if ((ttf->texture = new (std::nothrow) sf::RenderTexture({width, height})) == NULL)
    goto DeleteStructure;

  hash = bunny_hash(BH_FNV, file, strlen(file));
  if (RessourceManager.disable_manager ||
      (ttf->font = (sf::Font*)RessourceManager.TryGet(ResManager::SF_FONT, hash)) == NULL)
    {
      if ((ttf->font = new (std::nothrow) sf::Font) == NULL)
	goto DeleteTexture;
      if (ttf->font->openFromFile(file) == false)
	{
	  bunny_errno = EINVAL;
	  goto DeleteFont;
	}
    }

  if (RessourceManager.disable_manager == false)
    {
      RessourceManager.AddToPool(ResManager::SF_FONT, file, hash, ttf, ttf->font);
      in_pool = true;
    }

  ttf->res_id = hash;
  ttf->texture->clear(sf::Color(0, 0, 0, 0));
  ttf->texture->display();
  ttf->tex = &ttf->texture->getTexture();
  ttf->ntex = ttf->ntexture ? &ttf->ntexture->getTexture() : NULL;
  if ((ttf->sprite = new (std::nothrow) sf::Sprite(*ttf->tex)) == NULL)
    goto DeleteFont;
  ttf->type = TTF_TEXT;
  ttf->conf_string = NULL;
  /*
  if (bunny_which_format(file) != BC_CUSTOM)
    {
      if (bunny_set_text_attribute(file, gfx, NULL, true) == false)
	goto DeleteFont;
      return (true);
    }
  */
  bunny_errno = 0;

  ttf->glyph_size.x = size->x;
  ttf->glyph_size.y = size->y;
  if ((ttf->text = new (std::nothrow) sf::Text(*ttf->font, "", size->y)) == NULL)
    goto DeleteSprite;

  ttf->text->setCharacterSize(size->y);
  scream_log_if(PATTERN, "ressource,text", width, height, file, size, size->x, size->y, ttf);
  return ((t_bunny_font*)ttf);

 DeleteSprite:
  delete ttf->sprite;
 DeleteFont:
  if (in_pool)
    RessourceManager.TryRemove(ResManager::SF_FONT, hash, ttf);
  else
    delete ttf->font;
 DeleteTexture:
  delete ttf->texture;
 DeleteStructure:
  delete ttf;
 ReturnNull:
  scream_error_if
    (return (NULL), bunny_errno, PATTERN, "ressource,text", width, height, file, size, size->x, size->y, (void*)NULL);
  return (NULL);
}
