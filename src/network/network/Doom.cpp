// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2024
// EFRITS SAS 2022-2024
// Pentacle Technologie 2008-2024
//
// Bibliothèque Lapin

#include		"lapin_private.h"

bool			Network::Doom(const Info	&info)
{
  bool			doomed = false;
  auto			it = peers.find(info);

  if (it != peers.end())
    doomed = it->second.Doom() || doomed;
  for (size_t i = 0; i < nbr; ++i)
    if (descriptors[i].info == info && descriptors[i].active)
      {
	descriptors[i].Doom();
	doomed = true;
      }
  return (doomed);
}

bool			Network::Doom(int		fd)
{
  for (size_t i = 0; i < nbr; ++i)
    if ((int)descriptors[i] == fd)
      {
	descriptors[i].Doom();
	return (true);
      }
  return (false);
}
