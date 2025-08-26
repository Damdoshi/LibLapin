// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2025
// EFRITS SAS 2022-2025
// Pentacle Technologie 2008-2025
//
// Bibliothèque Lapin

#include	"lapin_private.h"

#define		PAT "%p data, %zu len, %p wt, %p wtdata -> %s"

bool		network::Peer::SetMessage(const char		*data,
					  size_t		len,
					  t_bunny_written	wt,
					  void			*wtdata)
{
  try {
    //// CE TRUC FAIT QU'ON NE PEUT PAS AVOIR DE "SERVER" UDP.
    //// HORS CETTE LIMITATION NE CONCERNE QUE LES SERVEURS TCP
    //// => LES SERVEURS TCPS NE DEVRAIENT PAS AVOIR DE PEER CREE, TOUT SIMPLEMENT.
    // if (info.sockaddr.sin_addr.s_addr == htonl(INADDR_ANY))
    //  scream_error_if(return (false), BE_PEER_IS_A_SERVER, PAT, "network", data, len, wt, wtdata, "false");
    outqueue.emplace_back(data, data + len, wt, wtdata);
  } catch (...) {
    return (false);
  }
  return (true);
}
