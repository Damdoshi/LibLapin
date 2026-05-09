// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2025
//
// Bibliotheque Lapin

#include	"lapin_private.h"


/**
 * @doc
 * @doc-symbol bunny_network_doom
 * @doc-kind function
 * @doc-module network
 * @doc-order 320
 * @doc-since 12
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Marks a network endpoint or peer for disconnection.
 * @param a Endpoint or peer to doom.
 * @return-success Returns true if the endpoint was found and marked.
 * @return-failure Returns false otherwise.
 * @see bunny_network_close
 *
 * @doc-lang fr
 * @brief Marque une extrémité ou un pair réseau pour déconnexion.
 * @param a Extrémité ou pair à condamner.
 * @return-success Renvoie true si l'extrémité a été trouvée et marquée.
 * @return-failure Renvoie false sinon.
 * @see bunny_network_close
 */
bool		bunny_network_doom(t_bunny_network_info		a)
{
  return (gl_network.Doom(*(network::Info*)&a));
}

