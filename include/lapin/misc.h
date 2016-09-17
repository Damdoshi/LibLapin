/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2016
**
** Bibliotheque Lapin
*/

/*!
** \file misc.h
** Utilities
*/

#ifndef				__LAPIN_MISC_H__
# define			__LAPIN_MISC_H__
# if				!defined(__LAPIN_H__)
#  error			You cannot include this file directly.
# endif
# include			<unistd.h>

# define			LITTERAL(fd, str)		write((fd), str "\n", sizeof(str "\n"))

/*!
** Write a litteral string (defined in code, with two double quotes) on stdout.
** \param str The string litteral to write
*/
# define			bunny_printl(str)		LITTERAL(1,  str)

/*!
** Write a litteral string (defined in code, with two double quotes) on stderr.
** \param str The string litteral to write
*/
# define			bunny_printlerr(str)		LITTERAL(2,  str)

#endif	/*			__LAPIN_MISC_H__		*/

