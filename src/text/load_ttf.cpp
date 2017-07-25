// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2017
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

  bunny_errno = ENOMEM;
  if ((ttf = new (std::nothrow) struct bunny_ttf_font) == NULL)
    goto ReturnNull;
  if ((ttf->text = new (std::nothrow) sf::Text) == NULL)
    goto DeleteStructure;
  if ((ttf->sprite = new (std::nothrow) sf::Sprite) == NULL)
    goto DeleteText;
  if ((ttf->texture = new (std::nothrow) sf::RenderTexture) == NULL)
    goto DeleteSprite;
  if (ttf->texture->create(width, height) == false)
    goto DeleteTexture;

  hash = bunny_hash(BH_FNV, file, strlen(file));
  if ((ttf->font = (sf::Font*)RessourceManager.TryGet(ResManager::SF_FONT, hash)) == NULL)
    {
      if ((ttf->font = new (std::nothrow) sf::Font) == NULL)
	goto DeleteTexture;
      if (ttf->font->loadFromFile(file) == false)
	{
	  bunny_errno = EINVAL;
	  goto DeleteFont;
	}
    }

  ttf->res_id = hash;
  bunny_errno = 0;

  ttf->text->setFont(*ttf->font);
  ttf->text->setCharacterSize(size->y);
  ttf->texture->clear(sf::Color(0, 0, 0, 0));
  ttf->texture->display();
  ttf->tex = &ttf->texture->getTexture();
  ttf->sprite->setTexture(*ttf->tex);
  ttf->type = TTF_TEXT;
  ttf->glyph_size.x = size->x;
  ttf->glyph_size.y = size->y;

  scream_log_if(PATTERN, width, height, file, size, size->x, size->y, ttf);
  return ((t_bunny_font*)ttf);

 DeleteTexture:
  delete ttf->texture;
 DeleteFont:
  delete ttf->font;
 DeleteSprite:
  delete ttf->sprite;
 DeleteText:
  delete ttf->text;
 DeleteStructure:
  delete ttf;
 ReturnNull:
  scream_error_if
    (return (NULL), bunny_errno, PATTERN, width, height, file, size, size->x, size->y, (void*)NULL);
  return (NULL);
}