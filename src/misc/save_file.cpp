// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		<fcntl.h>
#include		"lapin_private.h"

#define			PATTERN		"%s file, %p data, %zu data length -> %s"


/**
 * @doc
 * @doc-symbol bunny_save_file
 * @doc-kind function
 * @doc-module misc
 * @doc-order 120
 * @doc-since 0
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Writes a memory block into a file.
 * @param file Destination path.
 * @param data Data to write.
 * @param len Number of bytes to write.
 * @return-success Returns true if the file was written entirely.
 * @return-failure Returns false on open or write error.
 * @log "ressource,file"
 * @see bunny_load_file
 *
 * @doc-lang fr
 * @brief Écrit un bloc mémoire dans un fichier.
 * @param file Chemin de destination.
 * @param data Données à écrire.
 * @param len Nombre d'octets à écrire.
 * @return-success Renvoie true si le fichier a été écrit entièrement.
 * @return-failure Renvoie false en cas d'erreur d'ouverture ou d'écriture.
 * @log "ressource,file"
 * @see bunny_load_file
 */
bool			bunny_save_file(const char		*file,
					const void		*data,
					size_t			len)
{
  int			fd;

  if ((fd = open(file, O_CREAT | O_TRUNC | O_WRONLY | O_BINARY, 0644)) == -1)
    scream_error_if(return (false), bunny_errno, PATTERN, "ressource,file", file, data, len, "false");
  if (write(fd, data, len) != (ssize_t)len)
    {
      close(fd);
      scream_error_if(return (false), bunny_errno, PATTERN, "ressource,file", file, data, len, "false");
    }
  close(fd);
  scream_log_if(PATTERN, "ressource,file", file, data, len, "true");
  return (true);
}

