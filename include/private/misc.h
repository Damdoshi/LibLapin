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
# include			<queue>

typedef struct			s_async_order
{
  t_bunny_function		func;
  void				*data_to_compute;
  void				*add_ptr;
}				t_async_order;

void				async_wrap(void			*data,
					   void			*add);

extern std::queue<void*>	gl_completed_tasks;
extern void			*gl_self_plugin;
extern t_bunny_context		gl_callback;
extern bool			gl_keyboard[BKS_LAST_KEY];
extern t_bunny_position		gl_mouse;
extern bool			gl_button[LAST_BUNNY_MOUSEBUTTON];
extern bool			gl_joy_button[sf::Joystick::Count][LAST_BUNNY_BUTTON];
extern float			gl_joy_axis[sf::Joystick::Count][LAST_BUNNY_AXIS];
extern float			gl_axis_offset[LAST_BUNNY_AXIS];
extern t_bunny_joystick		gl_joystick[sf::Joystick::Count];
extern t_bunny_window		*gl_window;
extern bool			gl_full_blit;
extern bool			gl_set_alpha_blit;
extern bool			gl_set_additional_blit;
extern bool			gl_set_multiply_blit;
extern size_t			gl_bunny_frequency;
extern bool			gl_complete_log;
extern t_bunny_list		*gl_backtasks_queue;
extern void			*gl_loop_data;

extern t_bunny_threadpool	*gl_bunny_loop_threadpool;

t_bunny_response		network_event(unsigned int		v,
					      void			*dat);

void				_real_call(const t_bunny_prototype	*function,
					   t_bunny_value		*return_value,
					   size_t			nbr,
					   t_bunny_value		*params);

t_bunny_configuration		*_get_good_conf(const char		*file,
						t_bunny_configuration	**conf);
bool				bunny_filter_label(const char		*labels);

# ifdef				NO_BUNNY_ERROR_LOG
#  define			scream_error_if(out, err, patt, lab, ...) \
  do									\
    {									\
      bunny_errno = err;						\
      out;								\
    }									\
  while (0)
# else
#  define			scream_error_if(out, err, patt, lab, ...) \
  do									\
    {									\
      if (bunny_get_error_descriptor() >= 0 &&				\
	  bunny_filter_label(lab))					\
	{								\
	  if (gl_complete_log)						\
	    bunny_dprintf(bunny_get_error_descriptor(),			\
		    "FAILURE [%s][%016lu][%16s:%d][%s][" patt "]\n",	\
		    lab,						\
		    (long unsigned int)time(NULL),			\
		    __FILE__, __LINE__,					\
		    bunny_strerror(err),				\
		    ##__VA_ARGS__);					\
	  else								\
	    bunny_dprintf(bunny_get_error_descriptor(),			\
		    "%s - " patt ".\n",					\
		    bunny_strerror(err),				\
		    ##__VA_ARGS__);					\
	}								\
      bunny_errno = err;						\
      out;								\
    }									\
  while (0)
# endif

# ifdef				NO_BUNNY_LOG
#  define			scream_log_if(pattern, lab, ...)	\
  //  bunny_errno = 0;
# else
#  define			scream_log_if(pattern, lab, ...)	\
  do									\
    {									\
      if (bunny_get_log_descriptor() >= 0 &&				\
	  bunny_filter_label(lab))					\
	{								\
	  if (gl_complete_log)						\
	    bunny_dprintf(bunny_get_log_descriptor(),			\
		    "LOG     [%s][%016lu][%16s:%d][" pattern "].\n",	\
		    lab,						\
		    (long unsigned int)time(NULL),			\
		    __FILE__, __LINE__,					\
		    ##__VA_ARGS__);					\
	  else								\
	    bunny_dprintf(bunny_get_log_descriptor(),			\
		    pattern ".\n",					\
		    ##__VA_ARGS__);					\
	}								\
      /* bunny_errno = 0; */						\
    }									\
  while (0)
# endif
# define			usleep(a)				bunny_usleep(a)
#endif	/*			__LAPIN_PRIVATE_MISC_H__		*/

