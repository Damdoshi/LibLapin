// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2024
// EFRITS SAS 2022-2024
//
// Lapin Library

#include		"lapin_private.h"

#define			PATTERN		"%u width, %u height, %p shift, %zu bpp, %d bitplane -> %p"

const uint8_t		default_shift[4] = {
  [RED_CMP] = RED_CMP,
  [GREEN_CMP] = GREEN_CMP,
  [BLUE_CMP] = BLUE_CMP,
  [ALPHA_CMP] = ALPHA_CMP
};

t_bunny_pixelarray	*bunny_forge_pixelarray(unsigned int	w,
						unsigned int	h,
						const uint8_t	*shifts,
						t_bunny_bitwidth bitw,
						bool		bitplane,
						t_bunny_color	*palette,
						size_t		palette_size)
{
  struct bunny_pixelarray *pa;
  size_t		siz;
  size_t		i;
  static const size_t	bitwm[] = {1, 2, 4, 8, 16, 32, 128};
  size_t		bpp = bitwm[bitw];

  // Vérification de la validité du bitage de l'image
  if (bitplane && bitw > BBW_256_COLORS)
    return (NULL);
  siz = ceil((double)bpp * w * h / 8);

  if ((pa = new (std::nothrow) struct bunny_pixelarray) == NULL)
    goto ReturnNull;
  if ((pa->rawpixels =
       (unsigned int*)bunny_malloc(siz)) == NULL)
    goto DeleteStructure;

  // Si on est en cours de correction, on ne fait pas de véritable création
  // de pont vers SFML.
  if (getenv("TECHNOCORE") == NULL)
    {
      if ((pa->image = new (std::nothrow) sf::Image) == NULL)
	goto DeleteRawPixels;
      pa->image->create(w, h, sf::Color(255, 105, 180, 255));
      if (pa->image->getSize() != sf::Vector2u(w, h))
	goto DeleteImage;
      if ((pa->tex = new (std::nothrow) sf::Texture) == NULL)
	goto DeleteImage;
      if ((pa->sprite = new (std::nothrow) sf::Sprite) == NULL)
	goto DeleteTexture;
      pa->sprite->setTexture(*pa->tex);
    }
  else
    {
      pa->image = NULL;
      pa->tex = NULL;
      pa->sprite = NULL;
    }
  
  if (bpp == 32 && bitplane == false && shifts && memcmp(shifts, default_shift, sizeof(default_shift)))
    for (i = 0; i < w * h; ++i)
      ((unsigned int*)pa->rawpixels)[i] = PINK2;
  else
    for (i = 0; i < siz; ++i)
      ((unsigned char*)pa->rawpixels)[i] = rand();

  pa->type = SYSTEM_RAM;
  pa->unused = 0;
  pa->width = w;
  pa->height = h;

  pa->rect.x = 0;
  pa->rect.y = 0;
  pa->rect.w = w;
  pa->rect.h = h;
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

  pa->bits_per_pixels = bitw;
  pa->bitplane = bitplane;
  if (palette)
    {
      if (!(pa->palette = (t_bunny_color*)bunny_memdup(palette, palette_size * sizeof(*pa->palette))))
	goto DeleteSprite;
      pa->palette_size = palette_size;
    }
  else
    {
      pa->palette = NULL;
      pa->palette_size = 0;
    }

  if (shifts)
    memcpy(pa->color_shifts, shifts, sizeof(pa->color_shifts));
  else
    memcpy(pa->color_shifts, default_shift, sizeof(pa->color_shifts));
  pa->res_id = 0;

  scream_log_if(PATTERN, "ressource,graphics", w, h, pa);
  return ((t_bunny_pixelarray*)pa);

 DeleteSprite:
  if (pa->sprite)
    delete pa->sprite;
 DeleteTexture:
  if (pa->tex)
    delete pa->tex;
 DeleteImage:
  if (pa->image)
    delete pa->image;
 DeleteRawPixels:
  bunny_free(pa->rawpixels);
 DeleteStructure:
  delete pa;
 ReturnNull:
  scream_error_if(return (NULL), ENOMEM, PATTERN, "ressource,graphics", w, h, (void*)NULL);
  return (NULL);

}
