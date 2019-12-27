/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2019
**
** Joystick panel
*/

#include			"joypanel.h"

t_bunny_response		joypanel_joy_connect(t_bunny_event_state state,
						     int	id,
						     const t_bunny_joystick *info,
						     t_program	*prog)
{
  if (state == CONNECTED)
    {
      prog->joystick[id] = info;
      if (id >= prog->nbr_joystick)
	prog->nbr_joystick += (id - prog->nbr_joystick) + 1;
    }
  else if (state == DISCONNECTED)
    {
      prog->joystick[id] = NULL;
      while (prog->nbr_joystick > 0 && prog->joystick[prog->nbr_joystick - 1] == NULL)
	--prog->nbr_joystick;
    }
  if (joypanel_start(prog) == false)
    {
      bunny_printlerr("Cannot resize the window.");
      return (EXIT_ON_ERROR);
    }
  return (GO_ON);
}

