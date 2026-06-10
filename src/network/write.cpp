// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2025
//
// Bibliotheque Lapin

#include	"lapin_private.h"


/**
 * @doc
 * @doc-symbol bunny_network_writec
 * @doc-kind function
 * @doc-module network
 * @doc-order 375
 * @doc-since 12
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Queues data to be sent to a network endpoint or peer.
 * @param a Target endpoint or peer.
 * @param data Data to send.
 * @param len Data size in bytes.
 * @param wt Optional callback called when the write request completes.
 * @param wtdata User data passed to wt.
 * @return-success Returns true if the write request was accepted.
 * @return-failure Returns false on error.
 * @see bunny_network_write, t_bunny_written
 *
 * @doc-lang fr
 * @brief Met des données en file d'envoi vers une extrémité ou un pair réseau.
 * @param a Extrémité ou pair cible.
 * @param data Données à envoyer.
 * @param len Taille des données en octets.
 * @param wt Callback optionnel appelé lorsque la demande d'écriture se termine.
 * @param wtdata Donnée utilisateur passée à wt.
 * @return-success Renvoie true si la demande d'écriture a été acceptée.
 * @return-failure Renvoie false en cas d'erreur.
 * @see bunny_network_write, t_bunny_written
 */
bool		bunny_network_writec(t_bunny_network_info	info,
				     const void			*data,
				     size_t			len,
				     t_bunny_written		wt,
				     void			*wtdata)
{
  if (!data && len != 0)
    return (false); 
  return (gl_network.SetMessage
	  (*(network::Info*)&info,
	   (const char*)data,
	   len, wt, wtdata)
	  );
}

