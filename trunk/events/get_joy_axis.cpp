// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2015
//
// Bibliothèque Lapin

#include		"lapin_private.h"

const float		(*bunny_get_joy_axis(void))[LAST_BUNNY_AXIS]
{
  return (gl_joy_axis);
}

