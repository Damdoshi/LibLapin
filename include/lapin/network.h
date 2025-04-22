/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2016
**
** Bibliotheque Lapin
*/

/*!
** \file network.h
** The network module contains facilities to create an asynchronous TCP
** server and a TCP client.
*/

#ifndef				__LAPIN_NETWORK_H__
# define			__LAPIN_NETWORK_H__
# if				!defined(__LAPIN_H__)
#  error			You cannot include this file directly.
# endif
# include			<sys/types.h>
# include			<sys/socket.h>
# include			<netinet/in.h>

typedef void			t_bunny_network;

typedef struct			s_bunny_network_info
{
  struct sockaddr_in		sockaddr;
  socklen_t			socklen;
}				t_bunny_network_info;

int				bunny_infocmp(const t_bunny_network_info	*a,
					      const t_bunny_network_info	*b);
t_bunny_network_info		bunny_new_network_info(const char		*ip,
						       uint16_t			port);

/*!
** Five types of answers are possible when you poll a network element:
** - An error happened
** - Nothing happened
** - A new connection has been opened
** - A connection was closed
** - A message was received
** There is currently no "Packet sent" notification.
** This enumeration is the incarnation of this mechanism.
*/
typedef enum			e_bunny_comtype
  {
    BCT_NETCONNECTED		= 0,
    BCT_NETDISCONNECTED		= 1,
    BCT_MESSAGE			= 2,
    BCT_ERROR			= 3,
  }				t_bunny_comtype;

/*!
** Errors that can occur when the polling is made.
*/
typedef enum			e_bunny_comerror
  {
    BCE_SYSTEM_FAIL		= 0,
    BCE_SELECT_FAIL		= 1,
    BCE_ACCEPT_FAIL		= 2,
    BCE_WRITE_FAIL		= 3,
    BCE_READ_FAIL		= 4,
    BCE_ALLOC_FAIL		= 5,
    BCE_GETTIME_FAIL		= 6,
    LAST_NETWORK_ERROR
  }				t_bunny_comerror;

typedef struct			s_bunny_communication
{
  t_bunny_comtype		comtype;
  t_bunny_network_info		info;
  double			time;
  char				*data;
  size_t			size;
  int				errno_code;
}				t_bunny_communication;

typedef enum			e_bunny_protocol
  {
    BP_IMMEDIATE_RETRIEVE,	// UDP
    BP_FIXED_SIZE_PACKET,	// TCP - If all your packets have the same size
    BP_SIZE_PLUS_DATA_PACKET,	// TCP - uint32_t + data
    BP_TERMINATED_PACKET	// TCP - data + uint8_t
  }				t_bunny_protocol;

// Functions that are supposed to be used by programmers
const t_bunny_network_info	*bunny_network_open(t_bunny_protocol	pcol,
						    size_t		size,
						    char		terminator,
						    uint16_t		port,
						    const char		*ip);
bool				bunny_network_doom(const t_bunny_network_info *a);
bool				bunny_network_close(const t_bunny_network_info *a);

typedef void			(*t_bunny_written)(const t_bunny_network_info *a,
						   void			*wtdata);

bool				bunny_network_writec(const t_bunny_network_info *a,
						     const void		*data,
						     size_t		len,
						     t_bunny_written	wt,
						     void		*wtdata);
# define			bunny_network_write(a, d, l)	\
  bunny_network_writec(a, d, l, NULL, NULL)

#endif	/*			__LAPIN_NETWORK_H__			*/
