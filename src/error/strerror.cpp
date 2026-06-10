// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

static const char	*bunny_errors[LAST_ERROR - BE_CANT_GENERATE_RESSOURCE] =
  {
    "Cannot generate dynamic ressource",
    "Syntax error encountered",
    "Bad address or variable",
    "Type mismatch",
    "Container is empty and cannot supply any value",
    "Duplication of the stored element failed.",
    "Cannot find requested element",
    "No embedded key found. The program was not made with LibLapin or its key is already prepared.",
    "No display device specified in environment",
    "A function described in the plugin table cannot be found.",
    "Too many parameters for a bunny plugin function. Maximum is 4.",
    "Something in the current context or environment is missing.",
    "You tried to write a message on the server !"
  };


/**
 * @doc
 * @doc-symbol bunny_strerror
 * @doc-kind function
 * @doc-module error
 * @doc-order 140
 * @doc-since 0
 * @doc-until latest
 * @doc-level 20
 *
 * @doc-lang en
 * @brief Returns a human-readable description of an error code.
 * @param errorcode Error code, usually bunny_errno.
 * @return-success Returns a static string describing errorcode.
 * @see bunny_errno, bunny_perror
 *
 * @doc-lang fr
 * @brief Renvoie une description lisible d’un code d’erreur.
 * @param errorcode Code d’erreur, généralement bunny_errno.
 * @return-success Renvoie une chaîne statique décrivant errorcode.
 * @see bunny_errno, bunny_perror
 */
const char		*bunny_strerror(int		errorid)
{
  if (errorid <= BE_CANT_GENERATE_RESSOURCE)
    return (strerror(errorid));
  if (errorid >= LAST_ERROR)
    return (NULL);
  return (bunny_errors[errorid - BE_CANT_GENERATE_RESSOURCE]);
}

