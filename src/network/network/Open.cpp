// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2024
// EFRITS SAS 2022-2024
// Pentacle Technologie 2008-2024
//
// Bibliothèque Lapin

#include		"lapin_private.h"
#include		"private/network/network.hpp"

network::Info		Network::Open(network::ProtoSpec const	&spec,
				      uint16_t			port,
				      const std::string		&ip)
{
  network::Info		inf;
  size_t		tmp;
  size_t		i;

  for (i = 0; i < descriptors.size(); ++i)
    if (!descriptors[i])
      {
	if (!(inf = descriptors[i].Open(spec, port, ip)))
	  goto Failure;
	// Si c'est une écoute, ce n'est pas un pair.
	if (ip != "")
	  {
	    auto it = peers.find(inf);

	    if (it == peers.end())
	      it = peers.emplace(inf, Peer{}).first;
	    if (it->second.AttachDescriptor(descriptors[i], descriptors[i].protocol, &inf) == false)
	      {
		peers.erase(it);
		goto Close;
	      }
	    it->second.SetProtocol(descriptors[i].protocol);
	  }
	tmp = nbr;
	if (!descriptors[i].Declare())
	  goto Detach;
	if (i == nbr)
	  nbr++;
	return (inf);
      }
  return (Info{});
 Detach:
  nbr = tmp;
  {
    auto it = peers.find(inf);

    if (it != peers.end())
      it->second.DetachDescriptor(descriptors[i]);
  }
 Close:
  descriptors[i].Close();
 Failure:
  return (Info{});
}

