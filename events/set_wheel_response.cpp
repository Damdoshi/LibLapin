// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2015
//
// Bibliothèque Lapin

#include		"lapin_private.h"

void			bunny_set_wheel_response(t_bunny_wheel	w)
{
  gl_callback.wheel = w;
}
