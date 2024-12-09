// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2024
// EFRITS SAS 2022-2024
// Pentacle Technologie 2008-2024
//
// Bibliothèque Lapin

#include		"lapin_private.h"

const network::Info	*Network::Open(Protocol			protocol,
				       size_t			size,
				       char			terminator,
				       uint16_t			port,
				       const std::string	&ip)
{
  for (size_t i = 0; i < descriptors.size(); ++i)
    if (!descriptors[i])
      {
	const network::Info *inf;
	
	if (!(inf = descriptors[i].Open(protocol, size, terminator, port, ip)))
	  return (NULL);
	if (peers[*inf].AttachDescriptor(descriptors[i]) == false)
	  {
	    descriptors[i].Close();
	    return (NULL);
	  }
	return (inf);
      }
  return (NULL);
}

