/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2019
**
** Bibliotheque Lapin
*/

#ifndef		__LAPIN_PORTABILITY_H__
# define	__LAPIN_PORTABILITY_H__
# if		!defined(__LAPIN_H__)
#  error	You cannot include this file directly.
# endif
# include	<stdint.h>
# include	<sys/types.h>

# ifdef		__APPLE__
#  include	<sys/_types/_ssize_t.h>
# endif

# ifdef		__SIZEOF_INT128__
typedef		__int128			t_bunny_ptrdiff;
# else
typedef		int64_t				t_bunny_ptrdiff;
# endif

# if		defined(__ANSI__) || !defined(__GNUC__)
#  define	__ZERO_LENGTH__			1
# else
#  define	__ZERO_LENGTH__			0
# endif

# ifndef	O_BINARY
#  define	O_BINARY			0
# endif

# ifndef	M_PI
#  define	M_PI				3.14159265358979323846
# endif

# include	<unistd.h>
# ifndef	EWOULDBLOCK
#  define	EWOULDBLOCK			EAGAIN
# endif

# if		defined(__linux__)

#  include	<alloca.h>
#  define	bunny_alloca(a)			alloca(a)
#  define	bunny_freea(a)

# elif		_WIN32 || __WIN32__		// /!\ This include MINGW64 from MSYS2

#  include	<malloc.h>
#  define	bunny_alloca(a)			_alloca(a)
#  define	bunny_freea(a)
#  define	dprintf(fd, format, ...)	bunny_dprintf(fd, format, ##__VA_ARGS__)

# else

#  warning "bunny_alloca will use bunny_malloc"
#  define	bunny_alloca(a)			bunny_malloc(a)
#  define	bunny_freea(a)			bunny_free(a)

# endif

size_t		bunny_strnlen(const char	*str,
			      size_t		max);
char		*bunny_strndup(const char	*str,
			       size_t		max);

char		*bunny_strdup(const char	*str);
int		bunny_strcasecmp(const char	*a,
				 const char	*b);
int		bunny_strncasecmp(const char	*a,
				  const char	*b,
				  size_t	l);
void		*bunny_memdup(const void	*ptr,
			      size_t		len);
int		bunny_dprintf(int		fd,
			      const char	*format,
			      ...);

#endif	/*	__LAPIN_PORTABILITY_H__		*/
