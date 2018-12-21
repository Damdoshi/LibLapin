/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2016
**
** Bibliotheque Lapin
*/

#ifndef				__LAPIN_PORTA_H__
# define			__LAPIN_PORTA_H__
# if				!defined(__LAPIN_H__)
#  error			You cannot include this file directly.
# endif
# include			<sys/types.h>
# ifdef				__APPLE__
#  include			<sys/_types/_ssize_t.h>
# endif
# if				defined(__ANSI__) || !defined(__GNUC__)
#  define			__ZERO_LENGTH__			1
# else
#  define			__ZERO_LENGTH__			0
# endif
# ifndef			O_BINARY
#  define			O_BINARY			0
# endif
#endif	/*			__LAPIN_PORTA_H__		*/

