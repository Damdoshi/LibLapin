// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2025
//
// Bibliotheque Lapin

#include			"lapin_private.h"


/**
 * @doc
 * @doc-symbol bunny_network_open
 * @doc-kind function
 * @doc-module network
 * @doc-order 300
 * @doc-since 12
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Opens a network endpoint using the selected protocol mode.
 * @param pcol Protocol and framing mode to use.
 * @param size Fixed packet size for BP_TCP_FIXED_SIZE, otherwise protocol-dependent.
 * @param terminator Packet terminator for BP_TCP_TERMINATED_DATA.
 * @param timeout Timeout in milliseconds.
 * @param resend Whether resend logic is enabled for reliable modes.
 * @param port Local or remote port.
 * @param ip Address to bind or connect to, depending on usage. NULL can be used for local listening endpoints.
 * @return-success Returns the endpoint information used by later network calls.
 * @return-failure Returns an invalid endpoint on failure.
 * @see t_bunny_protocol, bunny_network_close, bunny_network_write
 *
 * @doc-lang fr
 * @brief Ouvre une extrémité réseau avec le mode de protocole choisi.
 * @param pcol Protocole et mode de tramage à utiliser.
 * @param size Taille fixe des paquets pour BP_TCP_FIXED_SIZE, sinon dépend du protocole.
 * @param terminator Terminateur de paquet pour BP_TCP_TERMINATED_DATA.
 * @param timeout Timeout en millisecondes.
 * @param resend Indique si la logique de renvoi est activée pour les modes fiables.
 * @param port Port local ou distant.
 * @param ip Adresse à binder ou à contacter selon l'usage. NULL peut être utilisé pour les extrémités locales en écoute.
 * @return-success Renvoie les informations d'extrémité utilisées par les appels réseau suivants.
 * @return-failure Renvoie une extrémité invalide en cas d'échec.
 * @see t_bunny_protocol, bunny_network_close, bunny_network_write
 */
t_bunny_network_info		bunny_network_open(t_bunny_protocol	pcol,
						   size_t		size,
						   char			term,
						   int			tmout,
						   bool			resend,
						   uint16_t		port,
						   const char		*ip)
{
  if (!ip)
    ip = "";
  return (gl_network.Open({true, pcol, size, term, tmout, resend}, port, ip));
}

