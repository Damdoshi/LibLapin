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
  ssize_t		len;
  Info			rinfo;

  // Si le buffer n'est pas établi, on l'établi. Si ca ne marche pas, on re essayera la prochaine fois
  if (inbuffer_size == 0)
    {
      if ((inbuffer = (char*)bunny_malloc(size)) == NULL)
	return (false);
      inbuffer_size = size;
    }

  // Si il reste de la place dans le buffer, on lit, sinon on indique qu'on a rien lu
  if (inbuffer_size - rcursor > 0)
    {
      if ((len = recvfrom
	   (fd,
	    &inbuffer[rcursor],
	    inbuffer_size - rcursor,
	    0,
	    (struct sockaddr*)&rinfo.sockaddr,
	    &rinfo.socklen
	    )) == -1)
	return (false);
      
      // La connexion est perdue
      if (len == 0 && protocol != IMMEDIATE_RETRIEVE)
	return (Close());
    }
  else
    len = 0;

  // UDP
  if (protocol == IMMEDIATE_RETRIEVE)
    {
      // Aucun traitement n'est à faire ici: on a ce qu'on veut
      // On fait l'ajout, même si len est vide, car on
      // peut recevoir un datagramme de longueur 0.
      return (ShiftInBuffer(rinfo));
    }

  /// TCP
  if (protocol == FIXED_SIZE)
    {
      // Normalement, on ne peut pas dépasser inbufer.size()
      // Car la lecture dans le buffer est conditionné à cette taille
      if (len + rcursor == inbuffer_size)
	return (ShiftInBuffer(rinfo));
      rcursor += len;
    }

  /// TCP
  if (protocol == SIZE_PLUS_DATA)
    {
      rcursor += len;
      if (rcursor < sizeof(spdbuffer->size))
	return (true);
      // Infraction au protocole
      if (spdbuffer->size > size)
	{
	  Close();
	  return (false);
	}
      // Si le buffer ne permet pas d'enregistrer le paquet entier, on augmente sa taille
      if (spdbuffer->size > inbuffer_size)
	{
	  char *tmp;

	  if ((tmp = (char*)bunny_realloc(inbuffer, spdbuffer->size)) == NULL)
	    return (false);
	  while (inbuffer_size < spdbuffer->size)
	    tmp[inbuffer_size++] = 0;
	  inbuffer = tmp;
	}
      // Au cas où l'on ai recu plusieurs paquets d'un coup
      // ce que la LibLapin ne fait *pas* - donc en face,
      while (rcursor > spdbuffer->size)
	if (ExtractFromInBuffer(rinfo, spdbuffer->size) == false)
	  return (false);
      return (true);
    }

  /// TCP
  if (protocol == TERMINATED)
    {
      char		*term;

      rcursor += len;
      while ((term = (char*)memchr(&inbuffer[0], terminator, rcursor)) != NULL)
	if (ExtractFromInBuffer(rinfo, term - &inbuffer[0]) == false)
	  return (false);
      // Infraction au protocole
      if (rcursor >= size && size != 0)
	{
	  Close();
	  return (false);
	}
      return (true);
    }
  return (true);
}

