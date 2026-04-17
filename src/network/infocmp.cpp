// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2025
//
// Bibliotheque Lapin

#include		"lapin.h"

int			bunny_infocmp(t_bunny_network_info	a,
				      t_bunny_network_info	b)
{
  socklen_t		i;
  int			diff;

  i = 0;
  while (i < a.socklen && i < sizeof(a.sockaddr) &&
	 i < b.socklen && i < sizeof(b.sockaddr))
    if ((diff = ((char*)&a.sockaddr)[i] - ((char*)&b.sockaddr)[i]) != 0)
      return (diff);
    else
      i = i + 1;
  if ((i == a.socklen || i == sizeof(a.sockaddr)) &&
      (i == b.socklen || i == sizeof(b.sockaddr)))
    return (0);
  return (((char*)&a.sockaddr)[i] - ((char*)&b.sockaddr)[i]);
}
