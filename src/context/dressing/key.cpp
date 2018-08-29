// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include		"lapin_private.h"

t_bunny_response	dressing_key(t_bunny_event_state state,
				     t_bunny_keysym	sym,
				     void		*data)
{
  (void)state;
  (void)sym;
  (void)data;
  return (GO_ON);
}

