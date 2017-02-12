// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Bibliotheque Lapin

#include		"lapin_private.h"

void			bunny_set_loop_main_function(t_bunny_loop	loop)
{
  gl_callback.loop = loop;
}

