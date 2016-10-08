// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2015
//
// Bibliothèque Lapin

#include		"lapin_private.h"

void			bunny_set_joy_axis_response(t_bunny_joy_axis	j)
{
  gl_callback.axis = j;
}

