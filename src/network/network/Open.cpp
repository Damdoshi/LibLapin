// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2024
// EFRITS SAS 2022-2024
// Pentacle Technologie 2008-2024
//
// Bibliothèque Lapin

#include		"lapin_private.h"

const network::Info	*Network::Open(const std::string	&name,
				       Protocol			protocol,
				       size_t			size,
				       char			terminator,
				       uint16_t			port,
				       const std::string	&domain)
{
  if (descriptors[name] != NULL)
    return (NULL);
  Descriptor		*desc;

  desc = new Descriptor(*this, protocol, size, terminator, port, domain);
  descriptors[name] = desc;
  descriptorsfd[(int)*desc] = desc;
  *desc = name;
  return (*desc);
}

