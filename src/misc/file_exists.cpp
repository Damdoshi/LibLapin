// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		<sys/stat.h>
#include		"lapin_private.h"


/**
 * @doc
 * @doc-symbol bunny_file_exists
 * @doc-kind function
 * @doc-module misc
 * @doc-order 259
 * @doc-since 12
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Checks whether a path exists.
 * @param file Path to inspect.
 * @return-success Returns true if file exists.
 * @return-failure Returns false otherwise.
 * @see bunny_is_directory
 *
 * @doc-lang fr
 * @brief Vérifie si un chemin existe.
 * @param file Chemin à inspecter.
 * @return-success Renvoie true si file existe.
 * @return-failure Renvoie false sinon.
 * @see bunny_is_directory
 */
bool			bunny_file_exists(const char		*file)
{
  return (access(file, F_OK) == 0);
}

