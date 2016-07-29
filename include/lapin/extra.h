/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2016
**
** Bibliotheque Lapin
*/

#ifndef				__LAPIN_EXTRA_H__
# define			__LAPIN_EXTRA_H__
# include			<stdint.h>
# ifdef				__cplusplus
#  include			"lapin/cpp_guard.hpp"
# endif
# include			"lapin/extra_type.h"

/*
** *****
** ****
** *** A:\> EXTRA\NETWORK
** **
** *|
** || The function bunny_new_server creates a TCP server which listen on the
** || given port. It returns NULL on error.
** ||
** || The function bunny_delete_server close the server and destroy the object.
** ||
** || bunny_server_poll watch if anything happened. It will sleep until something
** || happen or until the given timeout was consumed. It returns a pointer on
** || t_bunny_communication which cannot be NULL.
** || The union t_bunny_communication is detailed inside extra_type.h and
** || is useful to know if a connection, a disconnection, a message, an error
** || or nothing happened.
** ||
** || bunny_server_write post a write request. It does not write immediatly!
** || You need to  call bunny_server_poll in order to make write request sent.
** || Of course, you must precise the fd to write.
** ||
** || bunny_server_packet_ready return true if there is an available packet
** || in the t_bunny_server structure. You should call bunny_server_poll to get
** || it. It will return instantly withouth caring about the timeout.
** ||
** || bunny_server_doom_client ask to delete a client after all its write
** || requests were done. So it does not kill instantly the client: you need
** || to call bunny_server_poll after and that there is no more write requests
** || on it before.
** ||                                                                            |
** |\                                                                           /|
** | > - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - < |
** |/                                                                           \|
** ||                                                                            |
** || The function bunny_new_client creates a TCP client connected to an IP
** || and a port. host must be an IP.
** ||
** || The function bunny_delete_client close the client and destroy the object.
** ||
** || bunny_client_poll works the same way as bunny_server_poll but on client
** || side.
** ||
** || bunny_client_write works the same was as bunny_server_write, but on client
** || side. So it does not need a fd as parameter.
** ||
** |*
** *
*/

typedef struct			s_bunny_server
{
  const void * const		_private;
  const int			fd;
  const uint16_t		port;
}				t_bunny_server;

t_bunny_server			*bunny_new_server(uint16_t			port);
void				bunny_delete_server(t_bunny_server		*srv);

const t_bunny_communication	*bunny_server_poll(t_bunny_server		*srv,
						   uint32_t			timout);
bool				bunny_server_write(t_bunny_server		*srv,
						   const void			*dat,
						   size_t			len,
						   int				fd);
bool				bunny_server_packet_ready(const t_bunny_server	*srv);
bool				bunny_server_doom_client(t_bunny_server		*srv,
							 int			fd);

typedef struct			s_bunny_client
{
  const void * const		_private;
  const int			fd;
  const char * const		host;
  uint16_t			port;
}				t_bunny_client;

t_bunny_client			*bunny_new_client(const char			*host,
						  uint16_t			port);
void				bunny_delete_client(t_bunny_client		*clt);

const t_bunny_communication	*bunny_client_poll(t_bunny_client		*clt,
						   uint32_t			timout);
bool				bunny_client_write(t_bunny_client		*clt,
						   const void			*data,
						   size_t			len);

/*
** *****
** ****
** *** A:\> EXTRA\THREAD_POOL
** **
** *|
** || This is a very simple thread API. It only serve ONE purpose: to dispatch
** || the same treatment on every element of a data set faster.
** || /!\ You should NEVER attempt to modify the same data in two threads, becase
** || this API does not contains any thread lock facility.
** ||
** || What this API purpose?
** || You have a set of elements: void *data[1024].
** || You want to call a function on every elements and you only need write acces
** || on the element itself. You can of course read anything you want aside.
** ||
** || bunny_new_threadpool create a thread pool with a specific amount of threads.
** || You should avoid using to many threads. Give a reasonable amount accordingly
** || to your system.
** ||
** || bunny_delete_threadpool delete the threadpool. You should have wait that
** || every work was done before.
** ||
** || bunny_thread_foreach call func with data[n] and add_ptr as parameter.
** || n may be any value in [0; len[. The add_ptr data is constant and must
** || not be write in order to avoid race condition. The only value that can
** || be changed is data.
** ||
** || bunny_thread_wait_completion does not return until all tasks given
** || by bunny_thread_foreach were done.
** ||
** |*
** *
*/

typedef struct			s_bunny_threadpool
{
  const void * const		_private;
  size_t			nbr_threads;
}				t_bunny_threadpool;

t_bunny_threadpool		*bunny_new_threadpool(size_t			nbr);
void				bunny_delete_threadpool(t_bunny_threadpool	*pol);

typedef void			(*t_bunny_function)(void			*data,
						    const void			*add_ptr);
bool				bunny_thread_foreach(t_bunny_threadpool		*pol,
						     t_bunny_function		func,
						     void			**data,
						     size_t			len,
						     const void			*add_ptr);
void				bunny_thread_wait_completion(t_bunny_threadpool	*pol);

/*
** *****
** ****
** *** A:\> EXTRA\HARDWARE_INTERFACE
** **
** *|
** || bunny_new_hardware create open a communication between a Velleman 110N board
** || and the current computer. It takes the ID of the board (which match the jumper
** || on the board itself) as parameter. id can only takes values in [0;3]
** ||
** || bunny_delete_hardware close the communication with the device and destroy the
** || object.
** ||
** || bunny_hardware_read read what's on the device and assign read values inside
** || the field digital_inputs and analog_inputs of the t_bunny_hardware structure.
** ||
** || bunny_hardware_write write what is in digital_outputs and analog_outputs
** || fields on the device.
** ||
** |*
** *
*/

typedef struct			s_bunny_hardware
{
  const void * const		_private;
  const int			id;
  const bool			digital_inputs[5];
  const double			analog_inputs[2];
  bool				digital_outputs[8];
  double			analog_outputs[2];
}				t_bunny_hardware;

t_bunny_hardware		*bunny_new_hardware(size_t			id);
void				bunny_delete_hardware(t_bunny_hardware		*hrd);

bool				bunny_hardware_read(t_bunny_hardware		*hrd);
bool				bunny_hardware_write(const t_bunny_hardware	*hdr);

# ifdef				__cplusplus
#  include			"lapin/cpp_guard_end.hpp"
# endif
#endif	/*			__LAPIN_EXTRA_H__				*/

