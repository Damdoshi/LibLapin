// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliotheque Lapin

#include			"lapin_private.h"

t_bunny_response		network_event(double			v,
					      void			*data)
{
  network::Communication	com;
  sf::Clock			poll_clock;

  if (v < 0)
    v = 1;
  poll_clock.restart();
  (void)bunny_network_poll(v);
  gl_bunny_loop_sleep_time = poll_clock.getElapsedTime().asSeconds();
  while (bunny_network_inbox() && gl_network.GetMessage(com))
    {
      if ((com.type == ::BCT_NETCONNECTED
	   || com.type == ::BCT_NETDISCONNECTED) &&
	  gl_callback.net_connect)
	{
	  return (gl_callback.net_connect(com.info,
					  com.type == ::BCT_NETCONNECTED ? ::CONNECTED : ::DISCONNECTED,
					  data));
	}
      else if (com.type == ::BCT_MESSAGE)
	{
	  com.DoNotFreeData();
	  return (gl_callback.net_message(com.info, com.data, com.size, data));
	}
      else
	{
	  printf("type : %d\n", com.type);
	  return (GO_ON); // Erreur... bunny_set_network_error_response?
	}
    }
  return (GO_ON);
}

