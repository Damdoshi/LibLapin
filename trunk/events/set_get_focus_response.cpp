// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2015
//
// Bibliothèque Lapin

#include		"lapin_private.h"

void			bunny_set_get_focus_response(t_bunny_get_focus	j)
{
  gl_callback.get_focus = j;
}

