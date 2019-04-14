/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2019
**
** Bibliotheque Lapin
*/

#ifndef		__LAPIN_RETROCOMPATIBILITY_H__
# define	__LAPIN_RETROCOMPATIBILITY_H__
# if		!defined(__LAPIN_H__)
#  error	You cannot include this file directly.
# endif

#define		bunny_music_get_cursor(music)	bunny_sound_get_cursor(&(music)->sound)
void		*bunny_pool_getv(t_bunny_pool	*pol,
				 size_t		*id);
# define	bunny_pool_get(pol, id, type)	(type*)bunny_pool_getv(pol, id)
# define	bunny_pool_release(pol, id)	bunny_pool_free(pol, (pol)->data[id])
# define	bunny_pool_free_elem(pool)	((pool)->nmemb - (pool)->nbr_occupied)
# define	bunny_pool_occupied_elem(pool)	(pool)->nbr_occupied

# define	ALPHA_GREY(a, g)		ALPHA_GRAY(a, g)
# define	GREY(g)				GRAY(g)

extern int	memory_check;

typedef t_bunny_color t_color;
typedef t_bunny_rgb t_rgb;
typedef t_bunny_mouse_button t_bunny_mousebutton;

extern const char *default_scope;
extern const char *erase_scope;
extern const unsigned int erase_field;
extern const char *erase_index;
extern const void *last_scope;

void		set_max_heap_size(size_t	s);

#endif	/*	__LAPIN_RETROCOMPATIBILITY_H__	*/
