// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2024
// EFRITS SAS 2022-2024
// Pentacle Technologie 2008-2024
//
// Bibliothèque Lapin

#include		"lapin_private.h"

void			Network::MoveWriteRequest(void)
{
  std::map<Info, Peer>::iterator itp;
  std::set<Descriptor*>::iterator itd;
  
  for (itp = peers.begin(); itp != peers.end(); ++itp)
    {
      // Le pair a t il quelque chose a ecrire?
      if (0 == itp->second)
	continue ;
      bool		fnd = false;

      // Le pair est il deja pris en charge?
      for (itd = itp->descriptors.begin(); itd != itp->descriptors.end(); ++itd)
	if (itd->IsWritingFor(itp->second.info))
	  {
	    fnd = true;
	    break ;
	  }
      // Personne ne gère son paquet, on l'ajoute
      if (!fnd)
	itp->second.Write(); // Si cela echoue, on re essayera
    }
}

