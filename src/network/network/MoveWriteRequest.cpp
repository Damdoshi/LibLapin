// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2026
// EFRITS SAS 2022-2026
// Pentacle Technologie 2008-2026
//
// Bibliothèque Lapin

#include                "lapin_private.h"

void                    Network::MoveWriteRequest(void)
{
  std::map<Info, Peer>::iterator itp;
  std::set<Descriptor*>::iterator itd;
  double                now = bunny_get_time() / 1e9;

  for (itp = peers.begin(); itp != peers.end(); ++itp)
    {
      bool              fnd = false;

      // Le pair est il deja pris en charge?
      for (itd = itp->second.descriptors.begin(); itd != itp->second.descriptors.end(); ++itd)
        if ((*itd)->IsWritingFor(itp->second.info))
          {
            fnd = true;
            break ;
          }

      // RUDP: tant qu'un ACK manque, on peut devoir réémettre même si
      // l'application n'a plus de nouvelle WriteRequest en attente.
      if (!fnd)
        if (itp->second.ReliableUdpTick(now))
          continue;

      // Le pair a t il quelque chose a ecrire?
      if (0 == itp->second)
        continue ;

      // Personne ne gère son paquet, on l'ajoute
      // => Peer::Write écrit dans l'un de ses descripteurs associés <=
      // Si cela echoue, on re essayera, comme ca
      if (!fnd)
        itp->second.TransfertWriteRequest();
    }
}
