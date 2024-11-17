// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2024
// EFRITS SAS 2022-2024
// Pentacle Technologie 2008-2024
//
// Bibliothèque Lapin

#include		"private/network/network.hpp"

bool			network::Descriptor::ExtractFromInBuffer(const Info	&info,
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
    inqueue.back().datas[i] = inbuffer[i];
  for (j = 0; i < inbuffer.size(); ++i, ++j)
    inbuffer[j] = inbuffer[i];
  rcursor -= len;
  return (true);
}

