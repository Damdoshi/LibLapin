/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2019
**
** Bibliotheque Lapin
*/

#ifndef			__LAPIN_RETROCOMPATIBILITY_H__
# define		__LAPIN_RETROCOMPATIBILITY_H__
# if			!defined(__LAPIN_H__)
#  error		You cannot include this file directly.
# endif
# ifdef			__cplusplus
#  include		"cpp_guard.hpp"
# endif

#define			bunny_music_get_cursor(music)	bunny_sound_get_cursor(&(music)->sound)

void			*bunny_pool_getv(t_bunny_pool	*pol,
					 size_t		*id) _BDEPREC();
# define		bunny_pool_get(pol, id, type)	(type*)bunny_pool_getv(pol, id)
# define		bunny_pool_release(pol, id)	bunny_pool_free(pol, (pol)->data[id])
# define		bunny_pool_free_elem(pool)	((pool)->nmemb - (pool)->nbr_occupied)
# define		bunny_pool_occupied_elem(pool)	(pool)->nbr_occupied

# define		ALPHA_GREY(a, g)		ALPHA_GRAY(a, g)
# define		GREY(g)				GRAY(g)

extern int		memory_check _BDEPREC();

typedef t_bunny_color	t_color _BDEPREC();
typedef t_bunny_rgb	t_rgb _BDEPREC();
typedef t_bunny_mouse_button t_bunny_mousebutton _BDEPREC();

extern const char	*default_scope _BDEPREC();
extern const char	*erase_scope _BDEPREC();
extern const unsigned int erase_field _BDEPREC();
extern const char	*erase_index _BDEPREC();
extern const void	*last_scope _BDEPREC();

void			set_max_heap_size(size_t	s) _BDEPREC();

# ifdef			__cplusplus
#  include		"cpp_guard_end.hpp"
# endif
#endif	/*		__LAPIN_RETROCOMPATIBILITY_H__	*/
