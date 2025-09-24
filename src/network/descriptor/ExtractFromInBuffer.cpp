// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2024
// EFRITS SAS 2022-2024
// Pentacle Technologie 2008-2024
//
// Bibliothèque Lapin

#include		"lapin.h"
#include		"private/network/network.hpp"

bool			network::Descriptor::ExtractFromInBuffer(const Info	&info,
								 const ProtoSpec &spec,
								 size_t		len)
{
  try {
    inqueue.emplace_back(info, len);
  } catch (...) {
    return (false);
  }
  size_t		i;
  size_t		j;

  for (i = 0; i < len; ++i)
    inqueue.back().data[i] = inbuffer[i];
  i += sizeof(spec.terminator);
  for (j = 0; i < inbuffer_size; ++i, ++j)
    inbuffer[j] = inbuffer[i];
  rcursor -= len;
  rcursor -= sizeof(spec.terminator);
  return (true);
}

