/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2019
**
** Joystick panel
*/

#include			"joypanel.h"

t_bunny_response		joypanel_joy_button(t_bunny_event_state	state,
						    int		id,
						    int		button,
						    t_program	*prog)
{
  (void)state;
  (void)id;
  (void)button;
  (void)prog;
  return (GO_ON);
}

