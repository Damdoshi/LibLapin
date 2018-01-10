// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include	"lapin_private.h"

void		bunny_set_joy_axis_minimum_offset(t_bunny_axis		_axis,
						  float			off)
{
  int		axis = _axis;
  int		i;

  for (i = 0; i < LAST_BUNNY_AXIS && axis & 0x1 == 0; ++i)
    axis >>= 1;
  if (i == LAST_BUNNY_AXIS)
    return ;
  gl_axis_offset[i] = off;
}

