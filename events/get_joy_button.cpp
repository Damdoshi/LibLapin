// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2015
//
// Bibliothèque Lapin

#include		"lapin_private.h"

const bool		(*bunny_get_joy_button(void))[LAST_BUNNY_BUTTON]
{
  return (gl_joy_button);
}

