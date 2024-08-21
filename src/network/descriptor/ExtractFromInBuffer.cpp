// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2024
// EFRITS SAS 2022-2024
// Pentacle Technologie 2008-2024
//
// Bibliothèque Lapin

#include		"private/network.hpp"

bool			network::Descriptor::ExtractFromInBuffer(size_t		len)
{
  try {
    inqueue.push_back(std::vector<char>{len});
  } catch (...) {
    return (false);
  }
  size_t		i;
  size_t		j;

  for (i = 0; i < len; ++i)
    inqueue.back()[i] = inbuffer[i];
  for (j = 0; i < inbuffer[i].size(); ++i, ++j)
    inbuffer[j] = inbuffer[î];
  rcursor -= len;
  return (true);
}

