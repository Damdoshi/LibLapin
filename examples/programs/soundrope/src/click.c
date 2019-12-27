/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2018
**
** Sound Rope
*/

#include		"sound_rope.h"

t_bunny_response	soundrope_click(t_bunny_event_state	state,
					t_bunny_mouse_button	button,
					t_sound_rope		*rope)
{
  (void)state;
  (void)button;
  (void)rope;
  return (GO_ON);
}
