// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		<sys/stat.h>
#include		"lapin_private.h"


/**
 * @doc
 * @doc-symbol bunny_is_directory
 * @doc-kind function
 * @doc-module misc
 * @doc-order 258
 * @doc-since 12
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Checks whether a path is an existing directory.
 * @param file Path to inspect.
 * @return-success Returns true if file exists and is a directory.
 * @return-failure Returns false otherwise.
 * @see bunny_file_exists
 *
 * @doc-lang fr
 * @brief Vérifie si un chemin est un dossier existant.
 * @param file Chemin à inspecter.
 * @return-success Renvoie true si file existe et est un dossier.
 * @return-failure Renvoie false sinon.
 * @see bunny_file_exists
 */
bool			bunny_is_directory(const char		*file)
{
  struct stat		st;

  if (stat(file, &st))
    return (false);
  return (S_ISDIR(st.st_mode));
}

