/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2016
**
** Bibliotheque Lapin
*/

/*!
** \file compat.h
** This header contains old symbols and or definitions that was used
** in previous version of the bunny library. So it is useful to make
** old programs written in older versions of the bunny library still compiling.
**
**
** So, consider things that are here as obsolete things.
** There is no removal planned, but no one knows in what the future is made,
** do not use anything that is here in your code.
**
** It also contains a few abstraction to port the bunny library on Windows.
*/

#ifndef				__LAPIN_COMPAT_H__
# define			__LAPIN_COMPAT_H__
# if				!defined(__LAPIN_H__)
#  error			You cannot include this file directly.
# endif

# define			bunny_get_screen_size()		\
  *bunny_get_screen_resolution()

# define			ERASE_SCOPE					NULL
# define			ERASE_FIELD					((unsigned int)-1)
# define			ERASE_INDEX					NULL

# define			bunny_ini_first(ini)		\
  bunny_ini_first_scope(ini)
# define			bunny_ini_next(ini, scope)	\
  bunny_ini_next_scope(ini, scope)

# ifdef				__WIN32
#  define			kill(a, b)			exit(1)
# endif

size_t				bunny_strnlen(const char	*str,
					      size_t		max);

extern int			memory_check;
void				set_max_heap_size(size_t	s);
typedef t_bunny_color		t_color;
typedef t_bunny_rgb		t_rgb;
typedef t_bunny_mouse_button	t_bunny_mousebutton;
extern const char		*default_scope;
extern const char		*erase_scope;
extern const unsigned int	erase_field;
extern const char		*erase_index;
extern const void		*last_scope;

#endif	/*			__LAPIN_COMPAT_H__		*/
