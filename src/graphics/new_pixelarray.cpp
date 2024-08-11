// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

t_bunny_pixelarray	*bunny_new_pixelarray(unsigned int	width,
					      unsigned int	height)
{
  return (bunny_forge_pixelarray(width, height, NULL, BBW_ARGB_COLORS, false, NULL, 0));
}
