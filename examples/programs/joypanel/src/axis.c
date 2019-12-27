/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2019
**
** Joystick panel
*/

#include			"joypanel.h"

t_bunny_response		joypanel_joy_axis(int		id,
						  t_bunny_axis	axis,
						  float		value,
						  t_program	*prog)
{
  (void)id;
  (void)axis;
  (void)value;
  (void)prog;
  return (GO_ON);
}

