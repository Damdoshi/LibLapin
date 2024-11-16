// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2025
// EFRITS SAS 2022-2025
// Pentacle Technologie 2008-2025
//
// Bibliothèque Lapin

#include		"private/network/network.hpp"

bool			network::Peer::Write(const char		*data,
					     size_t		len)
{
  try {
    outqueue.emplace_back(data, data + len);
  } catch (...) {
    return (false);
  }
  return (true);
}

bool			network::Peer::Write(void)
{
  auto it = std::advance(outqueue.begin(), rand() % descriptors.size());

  return (it->Write(outqueue.front().data(), outqueue.front().size(), info));
}

