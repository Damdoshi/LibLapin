/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2016
**
**
** Bibliotheque Lapin
*/

#ifndef				__LAPIN_PRIVATE_MISC_H__
# define			__LAPIN_PRIVATE_MISC_H__
# include			<SFML/Window.hpp>

extern t_bunny_context		gl_callback;
extern bool			gl_keyboard[BKS_LAST_KEY];
extern t_bunny_position		gl_mouse;
extern bool			gl_button[LAST_BUNNY_MOUSEBUTTON];
extern bool			gl_joy_button[LAST_BUNNY_JOYSTICK][LAST_BUNNY_BUTTON];
extern float			gl_joy_axis[LAST_BUNNY_JOYSTICK][LAST_BUNNY_AXIS];
extern t_bunny_joystick		gl_joystick[LAST_BUNNY_JOYSTICK];
extern t_bunny_window		*gl_window;
extern bool			gl_full_blit;

t_bunny_response		network_event(unsigned int		v,
					      void			*dat);

#endif	/*			__LAPIN_PRIVATE_MISC_H__		*/

