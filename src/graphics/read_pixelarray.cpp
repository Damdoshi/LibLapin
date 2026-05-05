// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin Library

#include		"lapin_private.h"

#define			PATTERN		"%p memory, %zu length, %s file -> %p"

/**
 * @doc-symbol bunny_read_pixelarray_id
 * @doc-module graphics
 * @doc-kind function
 * @doc-order 50
 * @doc-since 12
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Reads an encoded image from memory into a pixelarray and optionally associates it with a resource identifier.
 * @description When from_file is not NULL, it is used by the resource manager as the origin identifier for the loaded data.
 * @param buf The memory buffer containing the encoded image.
 * @param len The size of buf in bytes.
 * @param from_file The optional resource identifier.
 * @return-success A loaded t_bunny_pixelarray.
 * @return-failure NULL on failure.
 * @error ENOMEM Out of memory.
 * @log Logs are written with the "ressource" and "graphics" labels.
 * @see bunny_read_pixelarray, bunny_load_pixelarray
 *
 * @doc-lang fr
 * @brief Lit une image encodée en mémoire vers un pixelarray et peut l’associer à un identifiant de ressource.
 * @description Lorsque from_file n’est pas NULL, il est utilisé par le gestionnaire de ressources comme identifiant d’origine des données chargées.
 * @param buf Le buffer mémoire contenant l’image encodée.
 * @param len La taille de buf en octets.
 * @param from_file L’identifiant de ressource optionnel.
 * @return-success Un t_bunny_pixelarray chargé.
 * @return-failure NULL en cas d’échec.
 * @error ENOMEM Mémoire insuffisante.
 * @log Les logs sont écrits avec les labels "ressource" et "graphics".
 * @see bunny_read_pixelarray, bunny_load_pixelarray
 */
t_bunny_pixelarray	*bunny_read_pixelarray_id(const void		*buf,
						  size_t		len,
						  const char		*file)
{
  struct bunny_pixelarray	*pa;
  uint64_t			hash;

  hash = file ? bunny_hash(BH_FNV, file, strlen(file)) : 0;
  if (_bunny_is_psd_buffer(buf, len))
    return (_bunny_load_psd_pixelarray_from_memory(buf, len, file));

  if ((pa = new (std::nothrow) struct bunny_pixelarray) == NULL)
    goto ReturnNull;
  pa->ntexture = NULL;
  pa->ntex = NULL;
  if (RessourceManager.disable_manager ||
      file == NULL ||
      (pa->tex = (sf::Texture*)RessourceManager.TryGet(ResManager::SF_TEXTURE, hash)) == NULL)
    {
      if ((pa->tex = new (std::nothrow) sf::Texture) == NULL)
	goto DeleteStructure;
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
  if ((pa->sprite = new (std::nothrow) sf::Sprite(*pa->tex)) == NULL)
    goto DeleteImage;

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
 DeleteStructure:
  delete pa;
 ReturnNull:
  scream_error_if(return (NULL), ENOMEM, PATTERN, "ressource,graphics", buf, len, file, (void*)NULL);
  return (NULL);
}

