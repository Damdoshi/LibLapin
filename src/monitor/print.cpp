// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin Library

#include		<unistd.h>
#include		"lapin_private.h"

/**
 * @doc
 * @doc-symbol bunny_print_monitored_value
 * @doc-kind function
 * @doc-module monitor
 * @doc-order 180
 * @doc-since 12
 * @doc-until latest
 * @doc-level 30
 *
 * @doc-lang en
 * @brief Writes monitored values to a file descriptor.
 * @description bunny_print_monitored_value prepares a textual representation of one or several monitored values and writes it to fd.
 * @param fd The file descriptor used for writing.
 * @param n The name of the monitored value to print. NULL or * prints all values. A name ending with * prints every value whose name starts with the preceding prefix.
 * @return-case success On $Bsuccess@, returns the number of bytes written by write.
 * @return-case failure On $Bfailure@, returns -1 when write fails and system errno is set by write.
 * @see bunny_add_monitored_value
 * @see bunny_display_monitored_value
 * @see bunny_remove_monitored_value
 *
 * @doc-lang fr
 * @brief Écrit des valeurs surveillées dans un descripteur de fichier.
 * @description bunny_print_monitored_value prépare une représentation textuelle d'une ou plusieurs valeurs surveillées et l'écrit dans fd.
 * @param fd Le descripteur de fichier utilisé pour l'écriture.
 * @param n Le nom de la valeur surveillée à imprimer. NULL ou * imprime toutes les valeurs. Un nom terminé par * imprime chaque valeur dont le nom commence par le préfixe précédent.
 * @return-case success En cas de $Bsuccès@, renvoie le nombre d'octets écrits par write.
 * @return-case failure En cas d'$Béchec@, renvoie -1 lorsque write échoue et que l'errno système est renseignée par write.
 * @see bunny_add_monitored_value
 * @see bunny_display_monitored_value
 * @see bunny_remove_monitored_value
 */
ssize_t			bunny_print_monitored_value(int			fd,
						    const char		*n)
{
  ssize_t		l;

  l = _bunny_monitor_prepare_buffer(&bunny_big_buffer[0], sizeof(bunny_big_buffer), n);
  if (l <= 0)
    return (l);
  return (write(fd, bunny_big_buffer, l));
}

