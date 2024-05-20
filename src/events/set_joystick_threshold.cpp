// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include	"lapin_private.h"

void		bunny_set_joystick_threshold(t_bunny_window	*_win,
					     float		offset)
{
  struct bunny_window	*win = (struct bunny_window*)_win;

  win->window->setJoystickThreshold(offset);
}
