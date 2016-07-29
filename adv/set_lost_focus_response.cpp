// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2015
//
// Bibliothèque Lapin

#include		"lapin_private.h"

void			bunny_set_lost_focus_response(t_bunny_lost_focus	j)
{
  gl_callback.lost_focus = j;
}

