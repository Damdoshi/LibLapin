// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2025
//
// Bibliotheque Lapin

#include		"lapin.h"

int			bunny_infocmp(const t_bunny_network_info	*a,
				      const t_bunny_network_info	*b)
{
  socklen_t		i;
  int			diff;

  i = 0;
  while (i < a->socklen && i < b->socklen)
    if ((diff = ((char*)&a->sockaddr)[i] - ((char*)&b->sockaddr)[i]) != 0)
      return (diff);
  if (i == a->socklen && i == b->socklen)
    return (0);
  return (((char*)&a->sockaddr)[i] - ((char*)&b->sockaddr)[i]);
}
