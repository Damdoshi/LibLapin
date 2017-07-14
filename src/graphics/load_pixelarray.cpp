// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2015
//
// Lapin Library

#include		"lapin_private.h"

#define			PATTERN		"%s -> %p"

t_bunny_pixelarray	*bunny_load_pixelarray(const char		*file)
{
  struct bunny_pixelarray	*pa;
  uint64_t			hash;

  hash = bunny_hash(BH_FNV, file, strlen(file));
  if ((pa = new (std::nothrow) struct bunny_pixelarray) == NULL)
    goto ReturnNull;
  if ((pa->sprite = new (std::nothrow) sf::Sprite) == NULL)
    goto DeleteStructure;
  if ((pa->tex = (sf::Texture*)RessourceManager.TryGet(ResManager::SF_TEXTURE, hash)) == NULL)
    {
      if ((pa->tex = new (std::nothrow) sf::Texture) == NULL)
	goto DeleteSprite;
      if (pa->tex->loadFromFile(file) == false)
	goto DeleteTexture;
      if ((pa->rawpixels =
	   (unsigned int*)bunny_malloc(pa->tex->getSize().x * pa->tex->getSize().y * sizeof(*pa->rawpixels))) == NULL)
	goto DeleteTexture;
      if ((pa->image = new (std::nothrow) sf::Image) == NULL)
	goto DeleteRawPixels;
      try
	{
	  *pa->image = pa->tex->copyToImage();
	}
      catch (...)
	{}
      if (pa->image->getSize() != pa->tex->getSize())
	goto DeleteImage;
    }
  else
    {
      pa->image = (sf::Image*)RessourceManager.TryGet(ResManager::SF_IMAGE, hash);
      pa->tex = (sf::Texture*)RessourceManager.TryGet(ResManager::SF_TEXTURE, hash);
      pa->rawpixels = (unsigned int*)RessourceManager.TryGet(ResManager::BUNNY_PIXELS, hash);
    }

  RessourceManager.AddToPool(ResManager::SF_IMAGE, hash, pa, pa->image);
  RessourceManager.AddToPool(ResManager::SF_TEXTURE, hash, pa, pa->tex);
  RessourceManager.AddToPool(ResManager::BUNNY_PIXELS, hash, pa, pa->rawpixels);

  pa->res_id = hash;
  pa->sprite->setTexture(*pa->tex);

  pa->type = SYSTEM_RAM;
  pa->width = pa->tex->getSize().x;
  pa->height = pa->tex->getSize().y;

  pa->rect.x = 0;
  pa->rect.y = 0;
  pa->rect.w = pa->width;
  pa->rect.h = pa->height;
  pa->position.x = 0;
  pa->position.y = 0;
  pa->origin.x = 0;
  pa->origin.y = 0;
  pa->scale.x = 1;
  pa->scale.y = 1;
  pa->rotation = 0;
  pa->color_mask.full = WHITE;

  scream_log_if(PATTERN, file, pa);
  return ((t_bunny_pixelarray*)pa);

 DeleteImage:
  delete pa->image;
 DeleteRawPixels:
  bunny_free(pa->rawpixels);
 DeleteTexture:
  delete pa->tex;
 DeleteSprite:
  delete pa->sprite;
 DeleteStructure:
  delete pa;
 ReturnNull:
  scream_error_if(return (NULL), ENOMEM, PATTERN, file, pa);
  return (NULL);
}

