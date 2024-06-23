/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2019
**
** Joystick panel
*/

#include			"joypanel.h"

t_bunny_response		joypanel_key(t_bunny_event_state	state,
					     t_bunny_keysym		sym,
					     t_program			*program)
{
  (void)state;
  (void)program;
  if (sym == BKS_ESCAPE)
    return (EXIT_ON_SUCCESS);
  return (GO_ON);
}
