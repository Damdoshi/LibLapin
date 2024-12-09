// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2025
//
// Bibliotheque Lapin

#include	"lapin_private.h"

bool		bunny_network_write(const t_bunny_network_info	*info,
				    const void			*data,
				    size_t			len)
{
  if (!info || !data)
    return (false);
  return (gl_network.SetMessage
	  (*(network::Info*)info,
	   (const char*)data,
	   len));
}

