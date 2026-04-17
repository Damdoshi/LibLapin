// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2024
// EFRITS SAS 2022-2024
// Pentacle Technologie 2008-2024
//
// Bibliothèque Lapin

#include		"lapin.h"
#include		"private/network/network.hpp"

bool			network::Descriptor::ExtractFromInBuffer(const Info	&rinfo,
								 const ProtoSpec &spec,
								 size_t		len)
{
  size_t		i;
  size_t		j;

  try
    {
      if (spec.protocol == BP_TCP_SIZED_PLUS_DATA)
	inqueue.emplace_back(rinfo, len - sizeof(((struct size_plus_data*)inbuffer)->size));
      else
	inqueue.emplace_back(rinfo, len);
    }
  catch (...)
    {
      return (false);
    }

  if (spec.protocol == BP_TCP_SIZED_PLUS_DATA)
    {
      struct size_plus_data	*spdbuffer = (struct size_plus_data*)inbuffer;

      for (i = 0; i < spdbuffer->size; ++i)
	inqueue.back().data[i] = spdbuffer->data[i];
      for (i = spdbuffer->size + sizeof(spdbuffer->size), j = 0; i < rcursor; ++i, ++j)
	inbuffer[j] = inbuffer[i];
      rcursor -= spdbuffer->size + sizeof(spdbuffer->size);
      return (true);
    }

  for (i = 0; i < len; ++i)
    inqueue.back().data[i] = inbuffer[i];
  i += sizeof(spec.terminator);
  for (j = 0; i < rcursor; ++i, ++j)
    inbuffer[j] = inbuffer[i];
  rcursor -= len;
  rcursor -= sizeof(spec.terminator);
  return (true);
}
