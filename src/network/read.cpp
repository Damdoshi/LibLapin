// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2025
//
// Bibliotheque Lapin

#include			"lapin_private.h"

t_bunny_communication		bunny_network_read(void)
{
  network::Communication	com;

  gl_network.GetMessage(com);
  com.DoNotFreeData();
  return (t_bunny_communication
	  {
	   com.type,
	   com.info,
	   com.time,
	   com.data,
	   com.size,
	   com.errno_code
	  });
}
