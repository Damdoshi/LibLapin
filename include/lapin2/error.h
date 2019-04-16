/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2019
**
** Bibliotheque Lapin
*/

#ifndef			__LAPIN_ERROR_H__
# define		__LAPIN_ERROR_H__
# if			!defined(__LAPIN_H__)
#  error		You cannot include this file directly.
# endif
# ifdef			__cplusplus
#  include		"cpp_guard.hpp"
# endif
# include		<errno.h>
# define		bunny_errno				errno

typedef enum		e_bunny_error
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
    BE_CONFIGURED_FUNCTION_NOT_FOUND,
    BE_TOO_MANY_PARAMETERS,
    BE_MISSING_CONTEXT,
    LAST_ERROR
  }			t_bunny_error;

const char		*bunny_strerror(int			error_code);
void			bunny_perror(const char			*message);

typedef enum		e_bunny_log_type
  {
    BLT_LOG,		// Simple information
    BLT_FAILED,		// The function did not achieved its purpose
    BLT_CRITICAL	// The function encounter a failure that needs a reaction
  }			t_bunny_log_type;

void			bunny_flush(void);
void			_bunny_log(const char			*prototype,
				   const char			*funcname,
				   t_bunny_log_type		logtype,
				   const char			*labels,
				   const char			*messages,
				   const char			*file,
				   int				line);

# define		bunny_log(ltype, labels, messages)	\
  _bunny_log(__PRETTY_FUNCTION__, __func__, ltype, labels, messages, __FILE__, __LINE__)

void			bunny_filter_label(const char		*labels);

int			bunny_get_log_descriptor(void);
int			bunny_get_fail_descriptor(void);
int			bunny_get_critical_descriptor(void);

int			bunny_set_log_descriptor(int		fd);
int			bunny_set_fail_descriptor(int		fd);
int			bunny_set_critical_descriptor(int	fd);

# define		bunny_set_message_descriptors(l, f, c)	\
  { bunny_set_log_descriptor(l); bunny_set_fail_descriptor(f); bunny_set_critical_descriptor(c); }

typedef enum		e_bunny_log_length
  {
    BLL_SHORT_LOG,
    BLL_LABELED_LOG,
    BLL_FULL_LOG
  }		t_bunny_log_length;

t_bunny_log_length	bunny_set_log_length(t_bunny_log_length length);
t_bunny_log_length	bunny_get_log_length(void);

typedef enum		e_bunny_log_verbosity
  {
    BLV_DISPLAY_CRITICAL = 1 << 0,
    BLV_DISPLAY_FAILURE = 1 << 1,
    BLV_DISPLAY_POSTLOG = 1 << 2,
    BLV_DISPLAY_PRELOG = 1 << 3,
  }			t_bunny_log_verbosity;

t_bunny_log_verbosity	bunny_set_log_verbosity(t_bunny_log_verbosity verbosity);
t_bunny_log_verbosity	bunny_get_log_verbosity(void);

# ifdef			__cplusplus
#  include		"cpp_guard_end.hpp"
# endif
#endif	/*		__LAPIN_ERROR_H__			*/

