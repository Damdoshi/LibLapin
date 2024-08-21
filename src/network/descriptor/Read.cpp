// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2024
// EFRITS SAS 2022-2024
// Pentacle Technologie 2008-2024
//
// Bibliothèque Lapin

#include		"private/network.hpp"

bool			network::Descriptor::Read(void)
{
  ssize_t		len;
  Info			info;

  // Si le buffer n'est pas établi, on l'établi. Si ca ne marche pas, on re essayera la prochaine fois
  try {
    if (inbuffer.size() == 0)
      inbuffer.resize(size);
  }
  catch (...) {
    return (false);
  }

  // Si il reste de la place dans le buffer, on lit, sinon on indique qu'on a rien lu
  if (inbuffer.size() - rcursor)
    {
      if ((len = recvfrom
	   (fd,
	    &inbuffer[rcursor],
	    inbuffer.size() - rcursor,
	    0,
	    &info.sockaddr,
	    &info.socklen
	    )) == -1)
	return (false);
      // La connexion est perdue
      if (len == 0)
	{
	  pollfd->fd *= -1;
	  close(fd);
	  fd = -1;
	  active = false;
	  return (true);
	}
    }
  else
    len = 0;

  // UDP
  if (protocol == IMMEDIATE_RETRIEVE)
    return (ShiftInBuffer(info));

  /// TCP
  if (protocol == FIXED_SIZE)
    {
      if (len + rcursor == inbuffer.size())
	return (ShiftInBuffer());
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
      if (spdbuffer->size() > inbuffer.size())
	inbuffer.resize(spdbuffer->size(), 0);
      // Au cas où l'on ai recu plusieurs paquets d'un coup
      // ce que la LibLapin ne fait *pas*
      while (rcursor > spdbuffer->size)
	if (ExtractFromInBuffer(spdbuffer->size) == false)
	  return (false);
      return (true);
    }

  /// TCP
  if (protocol == TERMINATED)
    {
      char		*term;

      rcursor += len;
      while ((term = memchr(&inbuffer[0], size & 0xFF, rcursor)) != NULL)
	if (ExtractFromInBuffer(term - &inbuffer[0]) == false)
	  return (false);
      // Infraction au protocole
      if (rcursor >= size)
	{
	  Close();
	  return (false);
	}
      return (true);
    }
  return (true);
}

