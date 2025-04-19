// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2025
// EFRITS SAS 2022-2025
// Pentacle Technologie 2008-2025
//
// Bibliothèque Lapin

#include	"lapin.h"
#include	"private/network/network.hpp"

bool		network::Peer::SetMessage(const char		*data,
					  size_t		len,
					  t_bunny_written	wt,
					  void			*wtdata)
{
  try {
    outqueue.emplace_back(data, data + len, wt, wtdata);
  } catch (...) {
    return (false);
  }
  return (true);
}
