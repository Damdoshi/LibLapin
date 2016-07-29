/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2016
**
** Bibliotheque Lapin
*/

#ifndef			__LAPIN_EXTRA_TYPE_H__
# define		__LAPIN_EXTRA_TYPE_H__
# ifdef			__cplusplus
#  include		"lapin/cpp_guard.hpp"
# endif

typedef enum		e_bunny_comtype
  {
    ERROR		= 0,
    EXPIRED		= 1,
    NETCONNECTED	= 2,
    NETDISCONNECTED	= 3,
    MESSAGE		= 4
  }			t_bunny_comtype;
typedef enum		e_bunny_comerror
  {
    SYSTEM_FAIL		= 0,
    SELECT_FAIL		= 1,
    ACCEPT_FAIL		= 2,
    WRITE_FAIL		= 3,
    READ_FAIL		= 4,
    ALLOC_FAIL		= 5,
    GETTIME_FAIL	= 6,
    LAST_ERROR
  }			t_bunny_comerror;

typedef struct		s_bunny_error
{
  t_bunny_comtype	comtype;
  unsigned int		time;
  t_bunny_comerror	errortype;
}			t_bunny_error;

typedef struct		s_bunny_expired
{
  t_bunny_comtype	comtype;
  unsigned int		time;
}			t_bunny_expired;

typedef struct		s_bunny_connected
{
  t_bunny_comtype	comtype;
  unsigned int		time;
  int			fd;
}			t_bunny_connected;

typedef struct		s_bunny_disconnected
{
  t_bunny_comtype	comtype;
  unsigned int		time;
  int			fd;
}			t_bunny_disconnected;

typedef struct		s_bunny_message
{
  t_bunny_comtype	comtype;
  unsigned int		time;
  int			fd;
  unsigned int		size;
  const char 		*buffer;
}			t_bunny_message;

typedef union		u_bunny_communication
{
  t_bunny_comtype	comtype;
  t_bunny_error		error;
  t_bunny_expired	expired;
  t_bunny_connected	connected;
  t_bunny_disconnected	disconnected;
  t_bunny_message	message;
}			t_bunny_communication;


# ifdef			__cplusplus
#  include		"lapin/cpp_guard_end.hpp"
# endif
#endif	/*		__LAPIN_EXTRA_TYPE_H__				*/
