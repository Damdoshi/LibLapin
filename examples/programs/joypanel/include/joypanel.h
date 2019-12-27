/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2019
**
** Joystick panel
*/

#ifndef				__JOYPANEL_H__
# define			__JOYPANEL_H__
# include			<lapin.h>

typedef struct			s_program
{
  t_bunny_window		*window;
  t_bunny_font			*title;
  t_bunny_font			*text;
  t_bunny_font			*label;
  const t_bunny_joystick	**joystick;
  int				nbr_joystick;
}				t_program;

extern const int		single_panel_height;

bool				joypanel_start(t_program	*prog);

#endif	/*i			__JOYPANEL_H__			*/
