/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2016
**
** Bibliotheque Lapin
*/

#ifndef				__LAPIN_MISC_H__
# define			__LAPIN_MISC_H__
# if				!defined(__LAPIN_ADVANCED_H__) && !defined(__LAPIN_BASIC_H__)
#  error			This file must not be included alone.
# endif
# include			<unistd.h>
# define			LITTERAL(fd, str)		write((fd), str "\n", sizeof(str "\n"))
# define			printl(str)			LITTERAL(1,  str)
# define			printlerr(str)			LITTERAL(2,  str)
#endif	/*			__LAPIN_MISC_H__		*/


