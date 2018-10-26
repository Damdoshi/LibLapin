// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include		"lapin_private.h"

t_bunny_response	bunny_box_click(t_bunny_event_state	state,
					t_bunny_mouse_button	button,
					void			*_box)
{
  t_bunny_box_system	*box = (t_bunny_box_system*)_box;

  (void)state;
  (void)button;
  (void)box;
  return (GO_ON);
}

