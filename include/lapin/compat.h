/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2016
**
** Bibliotheque Lapin
*/

/*!
** \file compat.h
** This header contains or include old symbols and or definitions that was used
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
# include			"compat/ini.h"

# define			bunny_get_screen_size()		\
  *bunny_get_screen_resolution()

# ifdef				__WIN32
#  define			freexit(a, b)			exit(1)
# else
#  define			freexit(a, b)			kill(a, b)
# endif

# ifndef			M_PI
#  define			M_PI				3.14159265358979323846
# endif

size_t				bunny_strnlen(const char	*str,
					      size_t		max);

char				*bunny_strndup(const char	*str,
					       size_t		max);

char				*bunny_strdup(const char	*str);

int				bunny_strcasecmp(const char	*a,
						 const char	*b);
int				bunny_strncasecmp(const char	*a,
						  const char	*b,
						  size_t	l);

int				bunny_dprintf(int		fd,
					      const char	*format,
					      ...);


/*!
** Get the position in seconds of the sent music.
** \param music The music to know where the cursor is
** \return The position in seconds between the beginning and the current cursor.
*/
#define				bunny_music_get_cursor(music)	\
  bunny_sound_get_cursor(&(music)->sound)

/*!
** Get a free element inside the pool.
** \param pol The pool to browse.
** \param id A pointer to store the id of the element in the storage array. May be NULL.
** \return NULL if there is no free element inside the pool, or a pointer to a free element
**
*/
void				*bunny_pool_getv(t_bunny_pool		*pol,
						 size_t			*id);

/*!
** Get a free element inside the pool.
** \param pol The pool to browse.
** \param id A pointer to store the id of the element. May be NULL.
** \param type The type of datas inside the pool
** \return NULL if there is no free element inside the pool, or a pointer to a free element
*/
# define			bunny_pool_get(pol, id, type)		\
  (type*)bunny_pool_getv(pol, id)

/*!
** Signal that the sent element is free again.
** Pay attention: its fast free mechanism have a cost: it changes the id
** of the last reserved allocation! Its id is now the id of the freed element.
** \param pol The pool to browse.
** \param id The element to release
*/
# define			buxnny_pool_release(pol, id)		\
  bunny_pool_free(pol, (pol)->data[id])

/*!
** Get how many free elements there is in the pool.
** \param pool The pool to get the number of free element
** \return The pool amount of free elements as size_t
*/
# define			bunny_pool_free_elem(pool)		((pool)->nmemb - (pool)->nbr_occupied)

# define			bunny_pool_occupied_elem(pool)		(pool)->nbr_occupied

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

# define			ALPHA_GREY(a, g)		\
  COLOR(a, g, g, g)

# define			GREY(g)				\
  COLOR(255, g, g, g)

# ifdef				__linux__
#  include			<alloca.h>
#  define			bunny_alloca(a)			alloca(a)
#  define			bunny_freea(a)

# elif				_WIN32 || __WIN32__
#  include			<malloc.h>
#  define			bunny_alloca(a)			_alloca(a)
#  define			bunny_freea(a)
#  define			dprintf(fd, format, ...)	\
  bunny_dprintf(fd, format, __VA_ARGS__)

# else
#  define			bunny_alloca(a)			bunny_malloc(a)
#  define			bunny_freea(a)			bunny_free(a)
# endif

#endif	/*			__LAPIN_COMPAT_H__		*/
