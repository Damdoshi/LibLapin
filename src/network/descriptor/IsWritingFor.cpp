// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2025
// EFRITS SAS 2022-2025
// Pentacle Technologie 2008-2025
//
// Bibliothèque Lapin

#include		"lapin_private.h"

bool			network::Descriptor::IsWritingFor(const Info	&info)
{
  for (auto it = outqueue.begin(); it != outqueue.end(); ++it)
    if (it->info == info)
      return (true);
  return (false);
}
