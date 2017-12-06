/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2016
**
** Bibliotheque Lapin
*/

/*!
** \file error.h
** Bunny error handling and error handling
*/

#ifndef				__LAPIN_ERROR_H__
# define			__LAPIN_ERROR_H__
# if				!defined(__LAPIN_H__)
#  error			You cannot include this file directly.
# endif
# include			<errno.h>

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

typedef enum			e_bunny_error
  {
    BE_CANT_GENERATE_RESSOURCE	= 10000,
    BE_SYNTAX_ERROR,
    BE_BAD_ADDRESS,
    BE_TYPE_ERROR,
    BE_CONTAINER_IS_EMPTY,
    BE_CANNOT_DUPLICATE,
    BE_CANNOT_FIND_ELEMENT,
    BE_CANNOT_FIND_EMBEDDED_KEY,
    BE_UNKNOWN_DISPLAY_DEVICE,
    LAST_ERROR
  }				t_bunny_error;

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
** Works the same way as perror(3), it writes on stderr.
**
** /!\ This function is not implemented yet
**
** \param A prefix to write before the error description. __FUNC__ or
** __PRETTY_FUNCTION__ may be a good idea, or the concatenation of __FILE__ and
** __LINE__... Or the name of the function that provokes the error.
*/
void				bunny_perror(const char			*str);

/*!
** Set the file descriptor used for error logging.
** This file descriptor can be negative to disable error logging.
** By default, is is STDERR_FILENO.
** \param fd The file descriptor for error logging
*/
void				bunny_set_error_descriptor(int		fd);

/*!
** Get the file descriptor used to log errors.
** This file descriptor can be negative: no logs are printed.
** By default, is is STDERR_FILENO.
** \return The file descriptor used for error logs.
*/
int				bunny_get_error_descriptor(void);

/*!
** Set the file descriptor used for normal logging.
** This file descriptor can be negative to disable logging.
** By default, is is STDOUT_FILENO.
** \param fd The file descriptor for logging
*/
void				bunny_set_log_descriptor(int		fd);

/*!
** Get the file descriptor used to log normal messages.
** This file descriptor can be negative: no logs are printed.
** By default, is is STDOUT_FILENO.
** \return The file descriptor used for logs.
*/
int				bunny_get_log_descriptor(void);

/*!
** Only print logs that contains label precised by parameter.
** Labels must be separated by ',' comma without any whitespace.
** LibLapin labels are:
**
**   system, ressource, graphics, sound, configuration, security,
**   unix, syntax, network, hardware
**
** \param label A string containing comma separated labels.
*/
void				bunny_set_log_filter(const char		*label);

#endif	/*			__LAPIN_ERROR_H__	*/
