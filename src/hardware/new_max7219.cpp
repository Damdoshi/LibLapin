// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2022
//
// Bibliotheque Lapin

#include		"lapin_private.h"

t_bunny_max7219		*bunny_new_max7219(size_t			w,
					   size_t			h,
					   int				clockpin,
					   int				loadpin,
					   int				datapin)
{
  t_bunny_max7219	*max;

  if ((max = (t_bunny_max7219*)bunny_calloc(sizeof(*max), 1)) == NULL)
    return (NULL);
  if (((*(bool**)&max->pixels) = (bool*)bunny_calloc(sizeof(*max->pixels), w * h * 8 * 8)) == NULL)
    goto DeleteMax;
  if (((*(char**)max->luminosity) = (char*)bunny_calloc(sizeof(*max->luminosity), w * h)) == NULL)
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
  bunny_free(max->luminosity);
 DeleteMax:
  bunny_free(max);
  return (NULL);
}

