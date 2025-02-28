// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin Library

#include		"lapin_private.h"

#define			PATTERN		"%p memory, %zu length, %s file -> %p"

t_bunny_pixelarray	*bunny_read_pixelarray_id(const void		*buf,
						  size_t		len,
						  const char		*file)
{
  struct bunny_pixelarray	*pa;
  uint64_t			hash;

  hash = bunny_hash(BH_FNV, file, strlen(file));
  if ((pa = new (std::nothrow) struct bunny_pixelarray) == NULL)
    goto ReturnNull;
  if ((pa->sprite = new (std::nothrow) sf::Sprite) == NULL)
    goto DeleteStructure;
  if (RessourceManager.disable_manager ||
      file == NULL ||
      (pa->tex = (sf::Texture*)RessourceManager.TryGet(ResManager::SF_TEXTURE, hash)) == NULL)
    {
      if ((pa->tex = new (std::nothrow) sf::Texture) == NULL)
	goto DeleteSprite;
      if (pa->tex->loadFromMemory(buf, len) == false)
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

  if (RessourceManager.disable_manager == false)
    {
      RessourceManager.AddToPool(ResManager::SF_IMAGE, file, hash, pa, pa->image);
      RessourceManager.AddToPool(ResManager::SF_TEXTURE, file, hash, pa, pa->tex);
      RessourceManager.AddToPool(ResManager::BUNNY_PIXELS, file, hash, pa, pa->rawpixels);
    }

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
  pa->smooth = false;
  pa->mosaic = false;
  pa->glactive = false;

  scream_log_if(PATTERN, "ressource,graphics", buf, len, file, pa);
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
  scream_error_if(return (NULL), ENOMEM, PATTERN, "ressource,graphics", buf, len, file, (void*)NULL);
  return (NULL);
}

