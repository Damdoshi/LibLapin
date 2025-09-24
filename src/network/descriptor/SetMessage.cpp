// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2025
// EFRITS SAS 2022-2025
// Pentacle Technologie 2008-2025
//
// Bibliothèque Lapin

#include	<limits.h>
#include	"lapin.h"
#include	"private/network/network.hpp"

bool		network::Descriptor::SetMessage(const char	*data,
						size_t		len,
						const Info	&info,
						const ProtoSpec	&specs,
						t_bunny_written	wt,
						void		*wtdata)
{
  if (len > specs.size && specs.size != 0)
    return (false);
  try {
    if (specs.protocol <= BP_UDP_RELIABLE)
      outqueue.emplace_back(info, data, len, wt, wtdata);
    else if (specs.protocol == BP_TCP_FIXED_SIZE)
      {
	if (specs.size == len)
	  outqueue.emplace_back(info, data, len, wt, wtdata);
	else
	  {
	    outqueue.emplace_back(info, specs.size, wt, wtdata);
	    memcpy(outqueue.back().data, data, len);
	    memset(&outqueue.back().data[len], 0, specs.size - len);
	  }
      }
    else if (specs.protocol == BP_TCP_SIZED_PLUS_DATA)
      {
	struct size_plus_data *spd = NULL;

	if (len > UINT32_MAX)
	  return (false);
	outqueue.emplace_back(info, len + sizeof(spd->size), wt, wtdata);
	spd = (struct size_plus_data*)outqueue.back().data;
	spd->size = len;
	memcpy(spd->data, data, len);
      }
    else // BP_TCP_TERMINATED_DATA
      {
	outqueue.emplace_back(info, len + sizeof(specs.terminator), wt, wtdata);
	memcpy(outqueue.back().data, data, len);
	memcpy(&outqueue.back().data[len], &specs.terminator, sizeof(specs.terminator));
      }
    pollfd->events |= POLLOUT;
  } catch (...) {
    return (false);
  }
  return (true);
}
