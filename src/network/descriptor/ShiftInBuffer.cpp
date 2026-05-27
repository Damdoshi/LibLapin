// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2024
// EFRITS SAS 2022-2024
// Pentacle Technologie 2008-2024
//
// Bibliothèque Lapin

#include		"lapin.h"
#include		"private/network/network.hpp"

bool			network::Descriptor::ShiftInBuffer(const Info		&info,
							   const ProtoSpec	&specs,
							   size_t		len)
{
  // On est potentiellement en UDP.
  // On est susceptible de rencontrer de nouveaux pairs par cette socket
  // Donc on doit créer des peer en fonction de la dispo de certains info.

  if (len == (size_t)-1)
    len = inbuffer_size;
  try
    {
      inqueue.emplace_back(info);
    }
  catch (...)
    {
      return (false);
    }
  inqueue.back().data = inbuffer;
  inqueue.back().size = len;

  inbuffer = NULL;
  inbuffer_size = 0;
  rcursor = 0;
  spdbuffer = NULL;
  if ((inbuffer = (char*)bunny_malloc(specs.size)) == NULL)
    return (false);
  spdbuffer = (struct size_plus_data*)inbuffer;
  inbuffer_size = specs.size;
  return (true);
}

