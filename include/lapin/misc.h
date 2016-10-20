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

# define			LITTERAL(fd, str)			write((fd), str "\n", sizeof(str "\n"))

/*!
** Write a litteral string (defined in code, with two double quotes) on stdout.
** \param str The string litteral to write
*/
# define			bunny_printl(str)			LITTERAL(1,  str)

/*!
** Write a litteral string (defined in code, with two double quotes) on stderr.
** \param str The string litteral to write
*/
# define			bunny_printlerr(str)			LITTERAL(2,  str)

/*!
** The last error that occurs.
*/
# define			bunny_errno				errno

/*!
** Return a string that contains the description of the sent error number in
** an human readable fashion. Works the same way as strerror(3).
** \param An error number
*/
const char			*bunny_strerror(int			errorcode);

/*!
** Print the sent string followed by ": " if the string is not NULL and if the
** first byte is not '\0', followed by the last error description.
** Works the same way as perror(3)
** \param A prefix to write before the error description. __FUNC__ or
** __PRETTY_FUNCTION__ may be a good idea, or the concatenation of __FILE__ and
** __LINE__... Or the name of the function that provokes the error.
*/
void				bunny_perror(const char			*str);

/*!
** Load a file into the space managed by bunny_malloc. The content of
** the file is returned, the size is written at the sent address.
** \param file The file to load
** \param size The address where to save the file size
** \return The content of the file, NULL on error.
*/
char				*bunny_load_file(const char		*file,
						 size_t			*size);

/*!
** Save the sent data into a file.
** \param file The destination file
** \param data The data to save
** \param len The length of the data
** \return True if everything went well, false instead.
*/
bool				bunny_save_file(const char		*file,
						const char		*data,
						size_t			len);

/*!
** Compute the operation sent as first parameter. Supported operators are:
** ',', '=', '||=', '^^=', '&&=' '|=', '^=', '&=', '<<=', '>>=', '+=', '-=',
** '*=', '/=', '%=', '##=', '? :', '||', '^^', '&&', '==', '!=', '~=', '<=',
** '>=', '<', '>', '|', '^', '&' '<<>', '<>>', '<<', '>>', '+', '-', '*', '/'
** '%', '.*', '##' and '(' ')'.
** Integers, floats, string and variables can be used. Variables availability
** fully depend on the given env parameter.
** \param operation The operation to compute
** \param env The variable environment
** \return Return the result as a string that must be freed by bunny_free. It
** may return NULL on error.
*/
char				*bunny_evaluate(const char		*operation,
						t_bunny_configuration	*env);

#endif	/*			__LAPIN_MISC_H__			*/

