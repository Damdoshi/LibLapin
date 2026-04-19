// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2024
// EFRITS SAS 2022-2024
// Pentacle Technologie 2008-2024
//
// Bibliothèque Lapin

#include		<poll.h>
#include		"lapin.h"
#include		"private/network/network.hpp"

bool			network::Descriptor::Read(void)
{
  ProtoSpec		specs{protocol};
  ssize_t		len;
  Info			rinfo;

  // Si le buffer n'est pas établi, on l'établi. Si ca ne marche pas, on re essayera la prochaine fois
  if (inbuffer_size == 0)
    {
      if ((inbuffer = (char*)bunny_malloc(specs.size)) == NULL)
	return (false);
      spdbuffer = (struct size_plus_data*)inbuffer;
      inbuffer_size = specs.size; // Default len
    }

  // Si il reste de la place dans le buffer, on lit, sinon on indique qu'on a rien lu
  if (inbuffer_size - rcursor > 0)
    {
      rinfo.socklen = sizeof(rinfo.sockaddr);
      if ((len = recvfrom
	   (fd,
	    &inbuffer[rcursor],
	    inbuffer_size - rcursor,
	    0,
	    (struct sockaddr*)&rinfo.sockaddr,
	    &rinfo.socklen
	    )) == -1)
	return (false);

      // On regarde si le pair dont on a recu un message est deja present
      auto it = network->peers.find(rinfo);
      if (it == network->peers.end())
	// On indique qu'il y a un nouveau pair
	inqueue.emplace_back(rinfo, true);

      // Création eventuelle du nouveau pair - ou récupération de l'existant
      auto &peer = network->peers[rinfo];

      // Récupération du protocole du pair
      specs = peer.protocol;

      // La connexion est perdue
      if (len == 0 && istcp(specs.protocol))
	{
	  // Préviens la déconnexion d'un client
	  inqueue.emplace_back(rinfo, false);
	  return (Close());
	}

      // On ajoute le pair au descripteur si ce n'est pas deja fait
      if (peer.descriptors.find(this) == peer.descriptors.end())
	if (peer.AttachDescriptor(*this, specs, &rinfo) == false && peer.descriptors.size() == 0)
	  network->peers.erase(rinfo);

      // Purement indicatif - non exploité actuellement
      peer.last_message = bunny_get_time() / 1e9;
    }
  else
    len = 0;

  // UDP, RDM ou TCP IMMEDIATE
  if (isimmediate(specs.protocol))
    {
      // Aucun traitement n'est à faire ici: on a ce qu'on veut
      // On fait l'ajout, même si len est vide, car on
      // peut recevoir un datagramme de longueur 0.
      return (ShiftInBuffer(rinfo, specs, len));
    }

  /// TCP
  if (specs.protocol == BP_TCP_FIXED_SIZE)
    {
      // Normalement, on ne peut pas dépasser inbufer.size()
      // Car la lecture dans le buffer est conditionné à cette taille
      if (len + rcursor == inbuffer_size)
	return (ShiftInBuffer(rinfo, specs));
      rcursor += len;
    }

  /// TCP
  if (specs.protocol == BP_TCP_SIZED_PLUS_DATA)
    {
      size_t total;

      rcursor += len;
      // Si on a pas encore recu toute la taille, on ne fait rien, on l'attend
      if (rcursor < sizeof(spdbuffer->size))
	return (true);
      // Infraction au protocole
      if (spdbuffer->size > specs.size)
	{
	  Close();
	  return (false);
	}
      total = spdbuffer->size + sizeof(spdbuffer->size);
      // Si le buffer ne permet pas d'enregistrer le paquet entier, on augmente sa taille
      if (total > inbuffer_size)
	{
	  char *tmp;

	  if ((tmp = (char*)bunny_realloc(inbuffer, total)) == NULL)
	    return (false);
	  while (inbuffer_size < total)
	    tmp[inbuffer_size++] = 0;
	  inbuffer = tmp;
	  spdbuffer = (struct size_plus_data*)inbuffer;
	}
      // Au cas où l'on ai recu plusieurs paquets d'un coup
      // ce que la LibLapin ne fait *pas* - donc en face,
      while (rcursor >= (total = spdbuffer->size + sizeof(spdbuffer->size)))
	if (ExtractFromInBuffer(rinfo, specs, total) == false)
	  return (false);
      return (true);
    }

  /// TCP
  if (specs.protocol == BP_TCP_TERMINATED_DATA)
    {
      char		*begin = &inbuffer[rcursor];
      char		*term;

      rcursor += len; /// On gèrera tous les paquets qu'on a recu.
      while ((term = (char*)memchr(begin, specs.terminator, rcursor)) != NULL)
	if (ExtractFromInBuffer(rinfo, specs, term - begin) == false)
	  return (false);
      // Infraction au protocole
      if (rcursor >= specs.size && specs.size != 0)
	{
	  Close();
	  return (false);
	}
      return (true);
    }
  return (true);
}
