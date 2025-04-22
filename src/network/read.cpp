// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2025
//
// Bibliotheque Lapin

#include	"lapin_private.h"

bool		bunny_network_read(t_bunny_communication	*com)
{
  if (!com)
    return (false);
  network::Communication	cppCom;
  bool				success;

  success = gl_network.GetMessage(cppCom);
  com->comtype = (t_bunny_comtype)cppCom.type;
  com->info = (t_bunny_network_info)cppCom.info;
  com->time = cppCom.time;
  com->data = cppCom.data;
  com->size = cppCom.size;
  com->errno_code = cppCom.errno_code;
  return (success);
}

