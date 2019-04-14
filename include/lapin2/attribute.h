/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2019
**
** Bibliotheque Lapin
*/

#ifndef		__LAPIN_ATTRIBUTE_H__
# define	__LAPIN_ATTRIBUTE_H__
# if		!defined(__LAPIN_H__)
#  error	You cannot include this file directly.
# endif

# ifdef		__GNUC__

#  define	_BFMT(a, b)		__attribute__((format (printf, a, b)))
#  define	_BPURE()		__attribute__((pure))
#  define	_BDEPREC()		__attribute__((deprecated))
#  define	_BMALLOC()		__attribute__((malloc))

# else

#  define	_BFMT(a, b)
#  define	_BPURE()
#  define	_BDEPREC()
#  define	_BMALLOC()

# endif

#endif	/*	__LAPIN_ATTRIBUTE_H__	*/
