// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include			"lapin_private.h"

static t_bunny_pixelarray	*bunny_fake_pixelarray(unsigned int		width,
						       unsigned int		height)
{
  t_bunny_pixelarray		*pa;
  unsigned int			**ptr;
  unsigned int			i;
  size_t			*type;
  
  if ((pa = (t_bunny_pixelarray*)malloc(sizeof(*pa))) == NULL)
    goto Fail;
  ptr = (unsigned int**)&pa->pixels;
  if ((*ptr = (unsigned int*)malloc(width * height * sizeof(**ptr))) == NULL)
    goto FailStruct;
  for (i = 0; i < width * height; ++i)
    ((int*)pa->pixels)[i] = PINK2;

  type = (size_t*)pa;
  *type = 2;
  pa->clipable.clip_x_position = 0;
  pa->clipable.clip_y_position = 0;
  pa->clipable.clip_width = pa->clipable.buffer.width = width;
  pa->clipable.clip_height = pa->clipable.buffer.height = height;
  pa->clipable.origin.x = 0;
  pa->clipable.origin.y = 0;
  pa->clipable.scale.x = 1;
  pa->clipable.scale.y = 1;
  pa->clipable.rotation = 0;
  pa->clipable.color_mask.full = WHITE;

  return (pa);

 FailStruct:
  free(ptr);
 Fail:
  return (NULL);
}

t_bunny_pixelarray		*bunny_new_pixelarray(unsigned int		width,
						      unsigned int		height)
{
  struct bunny_pixelarray	*pa;
  unsigned int			i;

  if (getenv("TECHNOCORE") != NULL)
    return (bunny_fake_pixelarray(width, height));
  if ((pa = new (std::nothrow) struct bunny_pixelarray) == NULL)
    goto Fail;
  if ((pa->rawpixels = (unsigned int*)bunny_malloc(width * height * sizeof(*pa->rawpixels))) == NULL)
    goto FailStruct;
  for (i = 0; i < width * height; ++i)
    pa->rawpixels[i] = PINK2;
  pa->image.create(width, height, sf::Color(255, 105, 180, 255));

  pa->type = SYSTEM_RAM;
  pa->rect.left = 0;
  pa->rect.top = 0;
  pa->rect.width = pa->width = width;
  pa->rect.height = pa->height = height;
  pa->sprite.setTexture(pa->tex);
  pa->x_origin = 0;
  pa->y_origin = 0;
  pa->x_scale = 1;
  pa->y_scale = 1;
  pa->rotation = 0;
  pa->color_mask.full = WHITE;

  return ((t_bunny_pixelarray*)pa);

 FailStruct:
  delete pa;
 Fail:
  return (NULL);
}
