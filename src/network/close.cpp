// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2025
//
// Bibliotheque Lapin

#include	"lapin_private.h"


/**
 * @doc
 * @doc-symbol bunny_network_close
 * @doc-kind function
 * @doc-module network
 * @doc-order 340
 * @doc-since 12
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Closes a network endpoint or peer immediately.
 * @param a Endpoint or peer to close.
 * @return-success Returns true if the endpoint was found and closed.
 * @return-failure Returns false otherwise.
 * @see bunny_network_doom, bunny_network_open
 *
 * @doc-lang fr
 * @brief Ferme immédiatement une extrémité ou un pair réseau.
 * @param a Extrémité ou pair à fermer.
 * @return-success Renvoie true si l'extrémité a été trouvée et fermée.
 * @return-failure Renvoie false sinon.
 * @see bunny_network_doom, bunny_network_open
 */
bool		bunny_network_close(t_bunny_network_info		inf)
{
  return (gl_network.Close(*(network::Info*)&inf));
}

