// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2024
// EFRITS SAS 2022-2024
// Pentacle Technologie 2008-2024
//
// Bibliothèque Lapin

#include		"lapin_private.h"

bool			Network::GetMessage(Communication	&com)
{
  for (size_t i = 0; i < nbr; ++i)
    {
      Descriptor	&desc = descriptors[i];

      if (desc.GetMessage(com))
	return (true);
    }
  return (false);
}

