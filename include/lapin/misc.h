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

/*!
** The last error that occurs.
*/
# define			bunny_errno			errno

/*!
** Return a string that contains the description of the sent error number in
** an human readable fashion. Works the same way as strerror(3).
** \param An error number
*/
const char			bunny_strerror(int		errorcode);

/*!
** Print the sent string followed by ": " if the string is not NULL and if the
** first byte is not '\0', followed by the last error description.
** Works the same way as perror(3)
** \param A prefix to write before the error description. __FUNC__ or
** __PRETTY_FUNCTION__ may be a good idea, or the concatenation of __FILE__ and
** __LINE__... Or the name of the function that provokes the error.
*/
void				bunny_perror(const char		*str);

#endif	/*			__LAPIN_MISC_H__		*/

