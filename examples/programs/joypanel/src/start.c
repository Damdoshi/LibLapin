/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2019
**
** Joystick panel
*/

#include		"joypanel.h"

static int		joystickcnt(t_program		*prog)
{
  int			i;
  int			cnt;

  for (i = 0, cnt = 0; i < prog->nbr_joystick; ++i)
    if (prog->joystick[i])
      cnt += 1;
  return (cnt);
}

bool			joypanel_start(t_program	*prog)
{
  t_bunny_size		siz;

  siz.x = prog->nbr_joystick > 6 ? 1600 : 800;
  siz.y = 100 + (joystickcnt(prog) <= 6 ? joystickcnt(prog) : 6) * single_panel_height;
  if (prog->window == NULL)
    return (prog->window = bunny_start(siz.x, siz.y, false, "JoyPanel"));
  bunny_resize_window(prog->window, siz);
  return (true);
}

