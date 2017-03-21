// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2015
//
// Lapin Library

#include		"lapin_private.h"

void			bunny_set_message_response(t_bunny_message_response func)
{
  gl_callback.netmessage = func;
}

