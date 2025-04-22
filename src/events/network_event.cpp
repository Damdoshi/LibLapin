// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliotheque Lapin

#include		"lapin_private.h"

t_bunny_response	network_event(double			v,
				      void			*data)
{
  network::Communication	com;

  if (v < 0)
    v = 1;
  if (!bunny_network_poll(v) <= 0)
    return (GO_ON);
  while (bunny_network_inbox() && gl_network.GetMessage(com))
    {
      if ((com.type == network::Communication::CONNECTED ||
	   com.type == network::Communication::DISCONNECTED) &&
	  gl_callback.netconnect)
	gl_callback.netconnect((t_bunny_network_info *)&com.info,
			       com.type == network::Communication::CONNECTED ?
			       ::CONNECTED : ::DISCONNECTED,
			       data);
      else if (com.type == network::Communication::DATA)
	gl_callback.netmessage((t_bunny_network_info *)&com.info,
			       com.datas.data(),
			       com.datas.size(),
			       data);
      else
	return (GO_ON); // Erreur... bunny_set_network_error_response?
    }
  return (GO_ON);
}

