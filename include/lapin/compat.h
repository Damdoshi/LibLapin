/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2016
**
** Bibliotheque Lapin
*/

#ifndef				__LAPIN_COMPAT_H__
# define			__LAPIN_COMPAT_H__
# if				!defined(__LAPIN_ADVANCED_H__) && !defined(__LAPIN_BASIC_H__)
#  error This file must not be included alone.
# endif

# define			bunny_ini_first(ini)		\
  bunny_ini_first_scope(ini)
# define			bunny_ini_next(ini, scope)	\
  bunny_ini_next_scope(ini, scope)

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
