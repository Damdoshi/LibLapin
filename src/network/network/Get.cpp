// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2024
// EFRITS SAS 2022-2024
// Pentacle Technologie 2008-2024
//
// Bibliothèque Lapin

#include			"lapin_private.h"

network::Descriptor		*Network::Get(const std::string		&id)
{
  auto				it = descriptors.find(id);

  return (it->second);
}

network::Descriptor		*Network::Get(const Info		&info)
{
  auto				it = descriptors.find(info.identity);

  return (it->second);
}


const network::Descriptor	*Network::Get(const std::string		&id) const
{
  auto				it = descriptors.find(id);

  return (it->second);
}

const network::Descriptor	*Network::Get(const Info		&info) const
{
  auto				it = descriptors.find(info.identity);

  return (it->second);
}

