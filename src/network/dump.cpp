// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2025
//
// Bibliotheque Lapin

#include	"lapin_private.h"


/**
 * @doc
 * @doc-symbol bunny_network_dump
 * @doc-kind function
 * @doc-module network
 * @doc-order 360
 * @doc-since 12
 * @doc-until latest
 * @doc-level expert
 *
 * @doc-lang en
 * @brief Writes a textual dump of current network state to a file descriptor.
 * @param fd Destination file descriptor.
 * @return-success Returns the number of dumped network objects or an implementation-defined status value.
 * @see bunny_network_open
 *
 * @doc-lang fr
 * @brief Écrit un dump textuel de l'état réseau courant dans un descripteur de fichier.
 * @param fd Descripteur de fichier de destination.
 * @return-success Renvoie le nombre d'objets réseau dumpés ou une valeur d'état propre à l'implémentation.
 * @see bunny_network_open
 */
int		bunny_network_dump(int		fd)
{
  return (gl_network.Dump(fd));
}
