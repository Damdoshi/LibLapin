// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include			<fcntl.h>
#include			<string.h>
#include			"lapin_private.h"

#define				PATTERN		"%s program, %p key -> %s"

/**
 * @doc
 * @doc-symbol bunny_fill_default_key
 * @doc-kind function
 * @doc-module security
 * @doc-order 200
 * @doc-since 11
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Writes a replacement embedded key into a program file.
 * @description The function searches bunny_program for the current embedded default key and replaces it with key. The replacement key must have the same total serialized size as the embedded key.
 * @param bunny_program The program file in which the embedded key must be replaced.
 * @param key The key to write into bunny_program. It must not be NULL.
 * @return-success true if the key was found and replaced.
 * @return-failure false if the file cannot be read or written, or if the embedded key cannot be found.
 * @error BE_CANNOT_FIND_EMBEDDED_KEY The embedded key could not be found in bunny_program.
 * @error errno An error reported by file loading, opening, seeking or writing was propagated.
 * @log This function writes log entries in the "security" log domain.
 * @see bunny_default_key, t_bunny_cipher_key, bunny_new_key
 *
 * @doc-lang fr
 * @brief Écrit une clé embarquée de remplacement dans un fichier de programme.
 * @description La fonction cherche la clé par défaut embarquée actuelle dans bunny_program et la remplace par key. La clé de remplacement doit avoir la même taille sérialisée totale que la clé embarquée.
 * @param bunny_program Le fichier de programme dans lequel la clé embarquée doit être remplacée.
 * @param key La clé à écrire dans bunny_program. Elle ne doit pas valoir NULL.
 * @return-success true si la clé a été trouvée et remplacée.
 * @return-failure false si le fichier ne peut pas être lu ou écrit, ou si la clé embarquée est introuvable.
 * @error BE_CANNOT_FIND_EMBEDDED_KEY La clé embarquée n'a pas été trouvée dans bunny_program.
 * @error errno Une erreur signalée par le chargement, l'ouverture, le déplacement ou l'écriture du fichier a été propagée.
 * @log Cette fonction écrit des entrées de log dans le domaine "security".
 * @see bunny_default_key, t_bunny_cipher_key, bunny_new_key
 */
bool				bunny_fill_default_key(const char	*bunny_prog,
						       const t_bunny_cipher_key *key)
{
  int32_t			buflen;
  const t_bunny_cipher_key	*def;
  char				*file;
  size_t			siz;
  size_t			i;
  int				fd;

  def = bunny_default_key();
  buflen = def->length + sizeof(def->length);

  if (bunny_load_file(bunny_prog, (void**)&file, &siz) == false)
    scream_error_if(return (false), bunny_errno, PATTERN, "security", bunny_prog, key, "false");
  for (i = 0; i < siz - buflen; ++i)
    if (memcmp(file, def, buflen) == 0)
      {
	if ((fd = open(bunny_prog, O_WRONLY)) == -1)
	  {
	    i = errno;
	    bunny_delete_file(file, bunny_prog);
	    scream_error_if(return (false), i, PATTERN, "security", bunny_prog, key, "false");
	  }
	lseek(fd, i, SEEK_SET);
	if (write(fd, key, key->length + sizeof(key->length)) != buflen)
	  {
	    i = errno;
	    close(fd);
	    bunny_free(file);
	    scream_error_if(return (false), i, PATTERN, "security", bunny_prog, key, "false");
	  }
	close(fd);
	bunny_delete_file(file, bunny_prog);
	scream_log_if(PATTERN, "security", bunny_prog, key, "true");
	return (true);
      }
  bunny_delete_file(file, bunny_prog);
  scream_error_if(return (false), BE_CANNOT_FIND_EMBEDDED_KEY, PATTERN, "security", bunny_prog, key, "false");
  return (false);
}

