// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2024
// EFRITS SAS 2022-2024
// Pentacle Technologie 2008-2024
//
// Bibliothèque Lapin

#include		"lapin_private.h"

bool			Network::Close(const Info		&info)
{
  return (peers[info].Close());
}

bool			Network::Close(int			fd)
{
#warning verifier ce fd qui ne doit pas etre un fd normalement - ou chercher le fd dans descriptors
  descriptors[fd].Close();
  return (true);
}

