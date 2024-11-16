// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2024
// EFRITS SAS 2022-2024
// Pentacle Technologie 2008-2024
//
// Bibliothèque Lapin

#include		"lapin_private.h"

bool			Network::GetMessage(Communication	&com,
					    std::string		&id)
{
  auto			it = descriptors.find(id);

  if (it == descriptors.end())
    return (false);
  return (it->second->GetMessage(com));
}

bool			Network::GetMessage(Communication	&com,
					    const Info		&info)
{
  std::string		id = info.identity;

  return (GetMessage(com, id));
}

