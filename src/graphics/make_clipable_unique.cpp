// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include		"lapin_private.h"

#define			PATTERN		"%p -> %s"

bool			bunny_make_clipable_unique(t_bunny_clipable	*clip)
{
  size_t		*type = (size_t*)clip;

  switch (*type)
    {
    case GRAPHIC_RAM:
      {
	struct bunny_picture *pic = (struct bunny_picture*)clip;
	sf::RenderTexture *rtex;

	if (!pic->res_id)
	  return (true);
	if (RessourceManager.IsAlone(ResManager::SF_RENDERTEXTURE, pic->res_id, pic))
	  {
	    RessourceManager.Extract(ResManager::SF_RENDERTEXTURE, pic->res_id, pic);
	    scream_log_if(PATTERN, "graphics", clip, "true");
	    return (true);
	  }
	if ((rtex = new (std::nothrow) sf::RenderTexture) == NULL)
	  scream_error_if(return (false), ENOMEM, PATTERN, "graphics", clip, "false");
	if (rtex->create(pic->texture->getSize().x, pic->texture->getSize().y) == false)
	  {
	    delete rtex;
	    scream_error_if(return (false), ENOMEM, PATTERN, "graphics", clip, "false");
	  }

	RessourceManager.TryRemove(ResManager::SF_RENDERTEXTURE, pic->res_id, pic);

	sf::RenderStates state = sf::RenderStates::Default;

	state.blendMode = sf::BlendNone;
	pic->tex = &rtex->getTexture();
	pic->sprite->setTexture(*pic->tex);
	rtex->draw(*pic->sprite, state);
	rtex->display();
	pic->texture = rtex;
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

	if ((img = new (std::nothrow) sf::Image) == NULL)
	  scream_error_if(return (false), ENOMEM, PATTERN, "graphics", clip, "false");
	img->create(pic->width, pic->height);
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
	pic->sprite->setTexture(*pic->tex);
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

