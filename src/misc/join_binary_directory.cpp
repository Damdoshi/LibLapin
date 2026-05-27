// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin Library

#include	<string.h>
#include	<libgen.h>
#include	"lapin_private.h"

#ifdef		__GNUC__
# include	<unistd.h>
# define	change_directory	chdir
#else
# define	change_directory	_chdir
#endif


/**
 * @doc
 * @doc-symbol bunny_join_binary_directory
 * @doc-kind function
 * @doc-module misc
 * @doc-order 259
 * @doc-since 12
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Changes the current working directory to the executable directory.
 * @param argv0 Program path, usually argv[0].
 * @return-success Returns true if the directory change succeeded.
 * @return-failure Returns false otherwise.
 *
 * @doc-lang fr
 * @brief Place le répertoire courant sur le dossier de l'exécutable.
 * @param argv0 Chemin du programme, généralement argv[0].
 * @return-success Renvoie true si le changement de dossier réussit.
 * @return-failure Renvoie false sinon.
 */
bool		bunny_join_binary_directory(const char	*argv0)
{
  char		buf[strlen(argv0) + 1];
  char		*dir;

  memcpy(&buf[0], argv0, sizeof(buf));
  dir = dirname(&buf[0]);

  return (change_directory(dir) != -1);
}
