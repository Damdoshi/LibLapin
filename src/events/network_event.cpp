// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliotheque Lapin

#include		"lapin_private.h"

t_bunny_response	network_event(double			v,
				      void			*data)
{
  t_bunny_communication com;

  if (!bunny_network_poll(v) <= 0)
    return (GO_ON);
  while (bunny_network_inbox() && bunny_network_read(&com))
    {
      if ((com.type == CONNECTED || com.type == DISCONNECTED) && gl_callback.netconnect)
	gl_callback.netconnect(&com.info,
			       com.type == network::Communication::CONNECTED ?
			       ::CONNECTED : ::DISCONNECTED,
			       data);
      else if (com.type == DATA)
	gl_callback.netmessage(&com.info, com.datas.data(), com.datas.size(), data);
      else
	return (GO_ON); // Erreur... bunny_set_network_error_response?
    }
  return (GO_ON);
}

