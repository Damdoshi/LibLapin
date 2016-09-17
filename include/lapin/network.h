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
    ERROR			= 0,
    EXPIRED			= 1,
    NETCONNECTED		= 2,
    NETDISCONNECTED		= 3,
    MESSAGE			= 4
  }				t_bunny_comtype;

/*!
** Errors that can occur when the polling is made.
*/
typedef enum			e_bunny_comerror
  {
    SYSTEM_FAIL			= 0,
    SELECT_FAIL			= 1,
    ACCEPT_FAIL			= 2,
    WRITE_FAIL			= 3,
    READ_FAIL			= 4,
    ALLOC_FAIL			= 5,
    GETTIME_FAIL		= 6,
    LAST_ERROR
  }				t_bunny_comerror;

/*!
** This structure resumes all informations about the error that occured while polling.
** The time attribute is the remaining time before the polling was suppose to end.
*/
typedef struct			s_bunny_error
{
  t_bunny_comtype		comtype;
  unsigned int			time;
  t_bunny_comerror		errortype;
}				t_bunny_error;

/*!
** This structure resumes all informations about the nothingness that happened while polling.
** The time attribute is the remaining time before the polling was suppose to end. In this case, it is 0.
*/
typedef struct			s_bunny_expired
{
  t_bunny_comtype		comtype;
  unsigned int			time;
}				t_bunny_expired;

/*!
** This structure resumes all informations about the new connection that was opened.
** The time attribute is the remaining time before the polling was suppose to end.
** The fd attribute is the file descriptor of the connection. Do not try to read or write on it,
** use functions instead.
*/
typedef struct			s_bunny_connected
{
  t_bunny_comtype		comtype;
  unsigned int			time;
  int				fd;
}				t_bunny_connected;

/*!
** This structure resumes all informations about the connection that was lost.
** The time attribute is the remaining time before the polling was suppose to end.
** The fd attribute is the file descriptor of the connection that was closed. Do not use it,
** it is closed.
*/
typedef struct			s_bunny_disconnected
{
  t_bunny_comtype		comtype;
  unsigned int			time;
  int				fd;
}				t_bunny_disconnected;

/*!
** This structure resumes all informations about a received packet.
** The time attribute is the remaining time before the polling was suppose to end.
** The fd attribute if the file descriptor from where the message is coming.
** The size attribute is the size of the data.
** The buffer attribute is the received data. Its length is size. Duplicate it
** if you want to keep it. It will be freed by the system on the next polling.
*/
typedef struct			s_bunny_message
{
  t_bunny_comtype		comtype;
  unsigned int			time;
  int				fd;
  unsigned int			size;
  const char			*buffer;
}				t_bunny_message;

/*!
** The t_bunny_communication union contains every previous structure.
** In order to know which one is really in the union, you need to read comtype.
** The t_bunny_communication union is returned by polling functions.
*/
typedef union			u_bunny_communication
{
  t_bunny_comtype		comtype;
  t_bunny_error			error;
  t_bunny_expired		expired;
  t_bunny_connected		connected;
  t_bunny_disconnected		disconnected;
  t_bunny_message		message;
}				t_bunny_communication;

/*!
** The t_bunny_server contains data about the TCP server. It starts with private
** fields you cannot access.
** The fd attribute is the file descriptor of the server: the listening socket.
** The port attribute is the port where the server is listening.
*/
typedef struct			s_bunny_server
{
  const void * const		_private;
  const int			fd;
  const uint16_t		port;
}				t_bunny_server;

/*!
** The bunny_new_server function creates a TCP server that listen on a specific port.
** \param port The port where to listen
** \return A pointer on a t_bunny_server, NULL on error.
*/
t_bunny_server			*bunny_new_server(uint16_t			port);

/*!
** The bunny_delete_server function destroy a TCP server. All connections dies
** when the listening socket is closed.
** \param srv The server to close.
*/
void				bunny_delete_server(t_bunny_server		*srv);

/*!
** Try to read and write on every connection and look if there is new or closed connection
** on the sent server. Return a t_bunny_communication that resume what happened.
** If a full packet is ready to be returned, timout is ignored and it returns immediatly.
** \param srv The TCP server.
** \param timout The maximum time to wait before returning an "expired packet".
** \return A t_bunny_communication. It cannot be NULL.
*/
const t_bunny_communication	*bunny_server_poll(t_bunny_server		*srv,
						   uint32_t			timout);

/*!
** Ask to the server to write a data at the next call to bunny_server_poll.
** \param srv The server from where is the fd
** \param dat The data to send
** \param len The length of data
** \param fd The connection where to write
** \return True if everything went well, false on error: not enough memory
** or the connection was doomed or fd was not found.
*/
bool				bunny_server_write(t_bunny_server		*srv,
						   const void			*dat,
						   size_t			len,
						   int				fd);

/*!
** Return true if there is a ready packet inside the TCP server. In this case, calling
** bunny_server_poll returns immediatly.
** \param srv The server to look at
** \return True if there is completed packets.
*/
bool				bunny_server_packet_ready(const t_bunny_server	*srv);

/*!
** Close the given connection after it have sent every datas he was requested to send.
** \param srv The TCP server that created fd.
** \param fd The connection to close
** \return True if everything went well, false on error: fd was not found.
*/
bool				bunny_server_doom_client(t_bunny_server		*srv,
							 int			fd);

/*!
** The t_bunny_client contains data abouth the TCP client. It starts with private
** fields you cannot access.
** The fd attribute is the file descriptor of the client.
** The host attribute is the IP of the server.
** The port attribute is the port we are talking with on the server.
*/
typedef struct			s_bunny_client
{
  const void * const		_private;
  const int			fd;
  const char * const		host;
  uint16_t			port;
}				t_bunny_client;

/*!
** The bunny_new_client function creates a TCP client that will talk with a distant server.
** \param host The IP address of the server.
** \param port The port on the server
** \return A t_bunny_client or NULL on error.
*/
t_bunny_client			*bunny_new_client(const char			*host,
						  uint16_t			port);

/*!
** The bunny_delete_client function destroy a TCP client.
** \param clt The client to close.
*/
void				bunny_delete_client(t_bunny_client		*clt);

/*!
** Try to read and write on the socket.
** \param clt The TCP client
** \param timout The maximum time to wait before returning an "expired packet".
** \return A t_bunny_communication. It cannot be NULL.
*/
const t_bunny_communication	*bunny_client_poll(t_bunny_client		*clt,
						   uint32_t			timout);

/*!
** Ask to the client to write data at the next call to bunny_client_write.
** \param clt The TCP client
** \param data The data to write
** \param len The length of the data
** \return True if everything went well, false on error: not enough memory
** or the connection is dead.
*/
bool				bunny_client_write(t_bunny_client		*clt,
						   const void			*data,
						   size_t			len);

#endif	/*			__LAPIN_NETWORK_H__				*/
