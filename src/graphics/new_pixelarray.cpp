// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include			"lapin_private.h"

#define				PATTERN		"%u width, %u height -> %p"

t_bunny_pixelarray		*bunny_new_pixelarray(unsigned int		width,
						      unsigned int		height)
{
  struct bunny_pixelarray	*pa;
  unsigned int			i;

  if ((pa = new (std::nothrow) struct bunny_pixelarray) == NULL)
    goto ReturnNull;
  if ((pa->rawpixels =
       (unsigned int*)bunny_malloc(width * height * sizeof(*pa->rawpixels))) == NULL)
    goto DeleteStructure;
  if (getenv("TECHNOCORE") == NULL)
    {
      if ((pa->image = new (std::nothrow) sf::Image) == NULL)
	goto DeleteRawPixels;
      pa->image->create(width, height, sf::Color(255, 105, 180, 255));
      if (pa->image->getSize() != sf::Vector2u(width, height))
	goto DeleteImage;
      if ((pa->tex = new (std::nothrow) sf::Texture) == NULL)
	goto DeleteImage;
      if ((pa->sprite = new (std::nothrow) sf::Sprite) == NULL)
	goto DeleteTexture;
      pa->sprite->setTexture(*pa->tex);
    }

  for (i = 0; i < width * height; ++i)
    pa->rawpixels[i] = PINK2;

  pa->type = SYSTEM_RAM;
  pa->unused = 0;
  pa->width = width;
  pa->height = height;

  pa->rect.x = 0;
  pa->rect.y = 0;
  pa->rect.w = width;
  pa->rect.h = height;
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

  pa->res_id = 0;
  pa->glactive = false;

  scream_log_if(PATTERN, "ressource,graphics", width, height, pa);
  return ((t_bunny_pixelarray*)pa);

 DeleteTexture:
  delete pa->tex;
 DeleteImage:
  delete pa->image;
 DeleteRawPixels:
  bunny_free(pa->rawpixels);
 DeleteStructure:
  delete pa;
 ReturnNull:
  scream_error_if(return (NULL), ENOMEM, PATTERN, "ressource,graphics", width, height, (void*)NULL);
  return (NULL);
}
