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
extern size_t			gl_bunny_frequency;

t_bunny_response		network_event(unsigned int		v,
					      void			*dat);

void				_real_call(const t_bunny_prototype	*function,
					   t_bunny_value		*return_value,
					   size_t			nbr,
					   t_bunny_value		*params);

t_bunny_configuration		*_get_good_conf(const char		*file,
						t_bunny_configuration	**conf);

# ifdef				NO_BUNNY_ERROR_LOG
#  define			scream_error_if(out, err, patt, ...)	\
  do									\
    {									\
      bunny_errno = err;						\
      out;								\
    }									\
  while (0)
# else
#  define			scream_error_if(out, err, patt, ...)	\
  do									\
    {									\
      if (bunny_get_error_descriptor() >= 0)				\
	dprintf(bunny_get_error_descriptor(),				\
		"FAILURE [%016lu]\t[%16s]\t[%s]\t[" patt "].\n",	\
		(long unsigned int)time(NULL),				\
		__FUNCTION__,						\
		strerror(err),						\
		__VA_ARGS__);						\
      bunny_errno = err;						\
      out;								\
    }									\
  while (0)
# endif

# ifdef				NO_BUNNY_LOG
#  define			scream_log_if(pattern, ...)		\
  //  bunny_errno = 0;
# else
#  define			scream_log_if(pattern, ...)		\
  do									\
    {									\
      if (bunny_get_log_descriptor() >= 0)				\
	dprintf(bunny_get_log_descriptor(),				\
		"LOG     [%016lu]\t[%16s]\t[" pattern "].\n",		\
		(long unsigned int)time(NULL),				\
		__FUNCTION__,						\
		__VA_ARGS__);						\
      bunny_errno = 0;							\
    }									\
  while (0)
# endif

#endif	/*			__LAPIN_PRIVATE_MISC_H__		*/

