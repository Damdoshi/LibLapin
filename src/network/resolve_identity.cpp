// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2025
//
// Bibliotheque Lapin

#include		"lapin_private.h"

t_bunny_identity	*bunny_resolve_identity(t_bunny_identity	*id,
						const t_bunny_network_info *in)
{
  for (size_t i = 0; id[i].identity[0]; ++i)
    if (bunny_infocmp(&id[i].info, in) == 0)
      return (&id[i]);
  return (NULL);
}

