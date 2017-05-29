// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2015
//
// Lapin Library

#include		"lapin_private.h"

void			bunny_set_client_to_scheduler(t_bunny_client	*clt)
{
  gl_callback.netcom = (t_bunny_network*)clt;
}

void			bunny_set_server_to_scheduler(t_bunny_server	*srv)
{
  gl_callback.netcom = (t_bunny_network*)srv;
}

void			bunny_remove_network_from_scheduler(void)
{
  gl_callback.netcom = NULL;
}
