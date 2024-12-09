// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2025
// EFRITS SAS 2022-2025
// Pentacle Technologie 2008-2025
//
// Bibliothèque Lapin

#include	"private/network/network.hpp"

bool		network::Descriptor::Write(const char		*data,
					   size_t		len,
					   const Info		&info)
{
  if (size < len && size != 0)
    return (false);
  try {
    if (protocol == IMMEDIATE_RETRIEVE)
      outqueue.emplace_back(info, data, len);
    else if (protocol == FIXED_SIZE)
      {
	outqueue.emplace_back(info, size);
	memcpy(outqueue.back().datas.data(), data, len);
      }
    else if (protocol == SIZE_PLUS_DATA)
      {
	struct size_plus_data *spd = NULL;
	
	outqueue.emplace_back(info, len + sizeof(spd->size));
	*((decltype(&spd->size))outqueue.back().datas.data()) = len;
	memcpy(&outqueue.back().datas.data()[sizeof(spd->size)], data, len);
      }
    else
      {
	outqueue.emplace_back(info, data, len + 1);
	outqueue.back().datas.data()[len] = terminator;
      }
  } catch (...) {
    return (false);
  }
  return (true);
}
