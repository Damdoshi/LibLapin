// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2015
//
// Bibliothèque Lapin

#include		"lapin_private.h"

void			bunny_set_close_response(t_bunny_close	j)
{
  gl_callback.close = j;
}

