// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2024
// EFRITS SAS 2022-2024
// Pentacle Technologie 2008-2024
//
// Bibliothèque Lapin

#include		<arpa/inet.h>
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
	{
	  struct size_plus_data *spd = (struct size_plus_data*)inbuffer;
	  inqueue.emplace_back(rinfo, (size_t)ntohl(spd->size));
	}
      else
	inqueue.emplace_back(rinfo, len);
    }
  catch (...)
    {
      return (false);
    }

  if (spec.protocol == BP_TCP_SIZED_PLUS_DATA)
    {
      struct size_plus_data	*spd = (struct size_plus_data*)inbuffer;
      size_t			payload_size = (size_t)ntohl(spd->size);

      for (i = 0; i < payload_size; ++i)
	inqueue.back().data[i] = spd->data[i];
      for (i = payload_size + sizeof(spd->size), j = 0; i < rcursor; ++i, ++j)
	inbuffer[j] = inbuffer[i];
      rcursor -= payload_size + sizeof(spd->size);
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
