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

# ifdef				BUNNY_DEBUG
#  undef			BUNNY_DEBUG
#  define			BUNNY_DEBUG(code)			code
# else
#  define			BUNNY_DEBUG(code)
# endif
# ifdef				BUNNY_LOG
#  undef			BUNNY_LOG
#  define			BUNNY_LOG(code)				code
# else
#  define			BUNNY_LOG(code)
# endif

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
**
** /!\ This function is not implemented yet
**
** \param An error number
*/
const char			*bunny_strerror(int			errorcode);

/*!
** Print the sent string followed by ": " if the string is not NULL and if the
** first byte is not '\0', followed by the last error description.
** Works the same way as perror(3)
**
** /!\ This function is not implemented yet
**
** \param A prefix to write before the error description. __FUNC__ or
** __PRETTY_FUNCTION__ may be a good idea, or the concatenation of __FILE__ and
** __LINE__... Or the name of the function that provokes the error.
*/
void				bunny_perror(const char			*str);

/*!
** Load an entire file.
** \param file The file name
** \param data A pointer to the content of the file (this param is an output)
** \param size A pointer to the size of the file (this param is an output)
** If size is NULL, then an additionnal '\0' is set at the end of the data.
** \return The size of the file if everything went well, else -1
**
** Note that data and size are only changed if everything went well.
*/
ssize_t				bunny_load_file(const char		*file,
						char			**data,
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
** +, -, *, /, %, >, <, >=, <=, !=, ==, ?: and () (not the function call but
** the priority modifier.
** Support doubles and integers and variables. You can use '.' to go inside a
** variable.
** \param operation The operation to compute
** \param env The variable environment
** \return The result or nan("") on error.
*/
double				bunny_evaluate(const char		*operation,
					       t_bunny_configuration	*env);

/*
** Self evaluation.
*/
void				bunny_consistancy(void);

#endif	/*			__LAPIN_MISC_H__			*/

