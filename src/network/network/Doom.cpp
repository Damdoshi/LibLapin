// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2024
// EFRITS SAS 2022-2024
// Pentacle Technologie 2008-2024
//
// Bibliothèque Lapin

#include		"lapin_private.h"

bool			Network::Doom(const Info	&info)
{
  auto			it = peers.find(info);

  if (it == peers.end())
    return (false);
  return (it->second.Doom());
}

bool			Network::Doom(int		fd)
{
  descriptors[fd].Doom();
  return (true);
}
