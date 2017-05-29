// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2015
//
// Lapin Library

#include		"lapin_private.h"

void			bunny_set_connect_response(t_bunny_connect_response func)
{
  gl_callback.netconnect = func;
}

