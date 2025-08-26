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
  const network::Info	*inf;
  size_t		tmp;
  size_t		i;
  
  for (i = 0; i < descriptors.size(); ++i)
    if (!descriptors[i])
      {	
	if (!(inf = descriptors[i].Open(protocol, size, terminator, port, ip)))
	  goto Failure;
	// Si c'est une écoute, ce n'est pas un pair.
	if (ip != "")
	  if (peers[*inf].AttachDescriptor(descriptors[i], inf) == false)
	    goto Close;
	tmp = nbr;
	if (!descriptors[i].Declare())
	  goto Detach;
	if (i == nbr)
	  nbr++;
	return (inf);
      }
  return (NULL);
 Detach:
  nbr = tmp;
  peers[*inf].DetachDescriptor(descriptors[i]);
 Close:
  descriptors[i].Close();
 Failure:
  return (NULL);
}

