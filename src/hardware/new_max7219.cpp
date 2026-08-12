// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2022
//
// Bibliotheque Lapin

#include		"lapin_private.h"


/**
 * @doc
 * @doc-symbol bunny_new_max7219
 * @doc-kind function
 * @doc-module hardware
 * @doc-order 440
 * @doc-since 0
 * @doc-until latest
 * @doc-level 50
 *
 * @doc-lang en
 * @brief Allocates a MAX7219 matrix chain descriptor.
 * @param w Width in 8x8 matrices.
 * @param h Height in 8x8 matrices.
 * @param clockpin Clock pin number.
 * @param loadpin Load pin number.
 * @param datapin Data pin number.
 * @return-success Returns a new MAX7219 descriptor.
 * @return-failure Returns NULL on allocation failure.
 * @see bunny_delete_max7219
 *
 * @doc-lang fr
 * @brief Alloue un descripteur de chaîne de matrices MAX7219.
 * @param w Largeur en matrices 8x8.
 * @param h Hauteur en matrices 8x8.
 * @param clockpin Numéro de broche clock.
 * @param loadpin Numéro de broche load.
 * @param datapin Numéro de broche data.
 * @return-success Renvoie un nouveau descripteur MAX7219.
 * @return-failure Renvoie NULL en cas d’échec d’allocation.
 * @see bunny_delete_max7219
 */
t_bunny_max7219		*bunny_new_max7219(size_t			w,
					   size_t			h,
					   int				clockpin,
					   int				loadpin,
					   int				datapin)
{
  t_bunny_max7219	*max;

  if ((max = (t_bunny_max7219*)bunny_calloc(1, sizeof(*max))) == NULL)
    return (NULL);
  if (((*(bool**)&max->pixels) = (bool*)bunny_calloc(w * h * 8 * 8, sizeof(*max->pixels))) == NULL)
    goto DeleteMax;
  if (((*(char**)max->luminosity) = (char*)bunny_calloc(w * h, sizeof(*max->luminosity))) == NULL)
    goto DeletePixels;
  if ((max->clock_pin = bunny_new_bitstream(clockpin, w * h * 8 * 8 * 2)) == NULL)
    goto DeleteLuminosity;
  if ((max->load_pin = bunny_new_bitstream(loadpin, w * h * 8 * 8 * 2)) == NULL)
    goto DeleteClock;
  if ((max->data_pin = bunny_new_bitstream(datapin, w * h * 8 * 8 * 2)) == NULL)
    goto DeleteLoad;

  max->width = w;
  max->height = h;
  max->stream_progression = 0;
  return (max);

 DeleteLoad:
  bunny_delete_bitstream(max->load_pin);
 DeleteClock:
  bunny_delete_bitstream(max->clock_pin);
 DeleteLuminosity:
  bunny_free(max->luminosity);
 DeletePixels:
  bunny_free(max->pixels);
 DeleteMax:
  bunny_free(max);
  return (NULL);
}

