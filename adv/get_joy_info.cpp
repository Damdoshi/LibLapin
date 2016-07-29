// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2015
//
// Bibliothèque Lapin

#include		"lapin_private.h"

const t_bunny_joystick	*bunny_get_joy_info(int		id)
{
  if (id >= LAST_BUNNY_JOYSTICK || id < 0)
    return (NULL);
  return (&gl_joystick[id]);
}

