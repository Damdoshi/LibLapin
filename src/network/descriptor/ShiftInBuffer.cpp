// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2024
// EFRITS SAS 2022-2024
// Pentacle Technologie 2008-2024
//
// Bibliothèque Lapin

#include		"lapin.h"
#include		"private/network/network.hpp"

bool			network::Descriptor::ShiftInBuffer(const Info		&info,
							   size_t		len)
{
  // On est en UDP.
  // On est susceptible de rencontrer de nouveaux pairs par cette socket
  // Donc on doit créer des peer en fonction de la dispo de certains info.

  try
    {
      inqueue.push_back(Communication{info});
    }
  catch (...)
    {
      return (false);
    }
  inqueue.back().data = inbuffer;
  if (len == 0)
    inqueue.back().size = inbuffer_size;
  else
    inqueue.back().size = len;

  inbuffer = NULL;
  inbuffer_size = 0;
  rcursor = 0;
  if ((inbuffer = (char*)bunny_malloc(size)) == NULL)
    return (false);
  inbuffer_size = size;
  return (true);
}

