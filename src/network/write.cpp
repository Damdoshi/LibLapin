// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2025
//
// Bibliotheque Lapin

#include	"lapin_private.h"

bool		bunny_network_writec(t_bunny_network_info	info,
				     const void			*data,
				     size_t			len,
				     t_bunny_written		wt,
				     void			*wtdata)
{
  if (!data)
    return (false); 
  return (gl_network.SetMessage
	  (*(network::Info*)&info,
	   (const char*)data,
	   len, wt, wtdata)
	  );
}

