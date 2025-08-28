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
						t_bunny_written	wt,
						void		*wtdata)
{
  if (len > size && size != 0)
    return (false);
  try {
    if (protocol == IMMEDIATE_RETRIEVE)
      outqueue.emplace_back(info, data, len, wt, wtdata);
    else if (protocol == FIXED_SIZE)
      {
	if (size == len)
	  outqueue.emplace_back(info, data, len, wt, wtdata);
	else
	  {
	    outqueue.emplace_back(info, size, wt, wtdata);
	    memcpy(outqueue.back().data, data, len);
	    memset(&outqueue.back().data[len], 0, size - len);
	  }
      }
    else if (protocol == SIZE_PLUS_DATA)
      {
	struct size_plus_data *spd = NULL;

	if (len > UINT32_MAX)
	  return (false);
	outqueue.emplace_back(info, len + sizeof(spd->size), wt, wtdata);
	spd = (struct size_plus_data*)outqueue.back().data;
	spd->size = len;
	memcpy(spd->data, data, len);
      }
    else
      {
	outqueue.emplace_back(info, len + sizeof(terminator), wt, wtdata);
	memcpy(outqueue.back().data, data, len);
	memcpy(&outqueue.back().data[len], &terminator, sizeof(terminator));
      }
    pollfd->events |= POLLOUT;
  } catch (...) {
    return (false);
  }
  return (true);
}
