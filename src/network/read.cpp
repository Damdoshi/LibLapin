// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2025
//
// Bibliotheque Lapin

#include		"lapin_private.h"

t_bunny_communication	bunny_network_read(void)
{
  t_bunny_communication		packet;
  network::Communication	com;

  memset(&packet, 0, sizeof(packet));
  gl_network.GetMessage(com);
  memcpy(&packet, &com, sizeof(packet));
  return (packet);
}

