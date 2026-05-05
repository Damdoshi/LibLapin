// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include		"lapin_private.h"

#define			PATTERN		"%p -> %s"

/**
 * @doc-symbol bunny_make_clipable_unique
 * @doc-module graphics
 * @doc-kind function
 * @doc-order 470
 * @doc-since 12
 * @doc-until latest
 * @doc-level expert
 *
 * @doc-lang en
 * @brief Ensures that a shared clipable owns unique graphic data before modification.
 * @description Resources loaded through the resource manager can share the same underlying data. This function duplicates the data when needed, similarly to copy-on-write. Objects created with bunny_new_* are already unique.
 * @param clipable The clipable to make unique.
 * @return-success true if the clipable is unique or was made unique.
 * @return-failure false if duplication fails.
 * @error ENOMEM Out of memory while duplicating the resource.
 * @log Logs are written with the "graphics" label.
 * @see bunny_load_picture, bunny_load_pixelarray
 *
 * @doc-lang fr
 * @brief Garantit qu’un clipable partagé possède ses propres données graphiques avant modification.
 * @description Les ressources chargées par le gestionnaire de ressources peuvent partager les mêmes données sous-jacentes. Cette fonction duplique les données si nécessaire, à la manière d’un copy-on-write. Les objets créés avec bunny_new_* sont déjà uniques.
 * @param clipable Le clipable à rendre unique.
 * @return-success true si le clipable est unique ou a été rendu unique.
 * @return-failure false si la duplication échoue.
 * @error ENOMEM Mémoire insuffisante lors de la duplication de la ressource.
 * @log Les logs sont écrits avec le label "graphics".
 * @see bunny_load_picture, bunny_load_pixelarray
 */
bool			bunny_make_clipable_unique(t_bunny_clipable	*clip)
{
  size_t		*type = (size_t*)clip;

  switch (*type)
    {
    case DRESSED_SPRITE:
    case SPRITE:
    case GRAPHIC_RAM:
      {
	struct bunny_picture *pic = (struct bunny_picture*)clip;
	sf::RenderTexture *rtex;
	sf::RenderTexture *nrtex = NULL;

	if (!pic->res_id)
	  return (true);
	if (RessourceManager.IsAlone(ResManager::SF_RENDERTEXTURE, pic->res_id, pic))
	  {
	    RessourceManager.Extract(ResManager::SF_RENDERTEXTURE, pic->res_id, pic);
	    scream_log_if(PATTERN, "graphics", clip, "true");
	    return (true);
	  }
	if ((rtex = new (std::nothrow) sf::RenderTexture({pic->texture->getSize().x, pic->texture->getSize().y})) == NULL)
	  scream_error_if(return (false), ENOMEM, PATTERN, "graphics", clip, "false");

	RessourceManager.TryRemove(ResManager::SF_RENDERTEXTURE, pic->res_id, pic);

	sf::RenderStates state = sf::RenderStates::Default;

	state.blendMode = sf::BlendNone;
	pic->tex = &rtex->getTexture();
	rtex->draw(*pic->sprite, state);
	rtex->display();
	if (pic->ntexture)
	  {
	    if ((nrtex = new (std::nothrow) sf::RenderTexture(pic->ntexture->getSize())) == NULL)
	      {
		delete rtex;
		scream_error_if(return (false), ENOMEM, PATTERN, "graphics", clip, "false");
	      }
	    sf::Sprite nspr(pic->ntexture->getTexture());
	    nrtex->draw(nspr, state);
	    nrtex->display();
	  }
	if (pic->sprite == NULL)
	  {
	    if ((pic->sprite = new (std::nothrow) sf::Sprite(*pic->tex)) == NULL)
	      return (false);
	  }
	else
	  pic->sprite->setTexture(*pic->tex); // Safe
	pic->texture = rtex;
	if (pic->ntexture)
	  delete pic->ntexture;
	pic->ntexture = nrtex;
	pic->ntex = nrtex ? &nrtex->getTexture() : pic->ntex;
	scream_log_if(PATTERN, "graphics", clip, "true");
	pic->res_id = 0;
	return (true);
      }
    case SYSTEM_RAM:
      {
	struct bunny_pixelarray *pic = (struct bunny_pixelarray*)clip;
	sf::Texture *tex;
	sf::Image *img;
	unsigned int *pixels;

	if (!pic->res_id)
	  return (true);
	if (RessourceManager.IsAlone(ResManager::SF_IMAGE, pic->res_id, pic))
	  {
	    RessourceManager.Extract(ResManager::SF_IMAGE, pic->res_id, pic);
	    RessourceManager.Extract(ResManager::SF_TEXTURE, pic->res_id, pic);
	    RessourceManager.Extract(ResManager::BUNNY_PIXELS, pic->res_id, pic);
	    scream_log_if(PATTERN, "graphics", clip, "true");
	    return (true);
	  }

	if ((img = new (std::nothrow) sf::Image({pic->width, pic->height})) == NULL)
	  scream_error_if(return (false), ENOMEM, PATTERN, "graphics", clip, "false");
	if (img->getSize() != pic->tex->getSize() || (tex = new (std::nothrow) sf::Texture) == NULL)
	  {
	    delete img;
	    scream_error_if(return (false), ENOMEM, PATTERN, "graphics", clip, "false");
	  }
	if ((pixels = (unsigned int*)bunny_malloc(pic->width * pic->height * sizeof(*pixels))) == NULL)
	  {
	    delete img;
	    delete tex;
	    scream_error_if(return (false), bunny_errno, PATTERN, "graphics", clip, "false");
	  }

	RessourceManager.TryRemove(ResManager::SF_TEXTURE, pic->res_id, pic);
	RessourceManager.TryRemove(ResManager::SF_IMAGE, pic->res_id, pic);
	RessourceManager.TryRemove(ResManager::BUNNY_PIXELS, pic->res_id, pic);

	memcpy(pixels, pic->rawpixels, pic->width * pic->height * sizeof(*pic->rawpixels));

	pic->rawpixels = pixels;
	pic->image = img;
	pic->tex = tex;
	if (pic->sprite == NULL)
	  {
	    if ((pic->sprite = new (std::nothrow) sf::Sprite(*pic->tex)) == NULL)
	      return (false);
	  }
	else
	  pic->sprite->setTexture(*pic->tex); // Safe
	pic->res_id = 0;
	scream_log_if(PATTERN, "graphics", clip, "true");
	return (true);
      }
    default:
      return (false);
    }
  // Never
  return (true);
}

