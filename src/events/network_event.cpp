// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Bibliotheque Lapin

#include		"lapin_private.h"

static t_bunny_response	notify(const t_bunny_communication	*com,
			       void				*data)
{
  if (com->comtype == MESSAGE && gl_callback.netmessage)
    return (gl_callback.netmessage
	    (com->message.fd, (const void*)com->message.buffer, com->message.size, data));

  if (gl_callback.netconnect)
    {
      if (com->comtype == NETCONNECTED)
	return (gl_callback.netconnect(com->connected.fd, CONNECTED, data));
      
      if (com->comtype == NETDISCONNECTED)
	return (gl_callback.netconnect(com->connected.fd, DISCONNECTED, data));
    }

  return (GO_ON);
}

t_bunny_response	network_event(unsigned int		v,
				     void			*data)
{
  t_bunny_response	res;

  if (*(size_t*)gl_callback.netcom == false)
    do
      if ((res = notify(bunny_client_poll((t_bunny_client*)gl_callback.netcom, v), data)) != GO_ON)
	return (res);
    while (bunny_client_packet_ready((t_bunny_client*)gl_callback.netcom));
  else
    do
      if ((res = notify(bunny_server_poll((t_bunny_server*)gl_callback.netcom, v), data)) != GO_ON)
	return (res);
    while ((bunny_server_packet_ready((t_bunny_server*)gl_callback.netcom)));
  return (GO_ON);
}

