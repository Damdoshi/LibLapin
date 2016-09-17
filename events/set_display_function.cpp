// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		"lapin_private.h"

void			bunny_set_display_function(t_bunny_display	display)
{
  gl_callback.display = display;
}

