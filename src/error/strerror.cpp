// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
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
    "Too many parameters for a bunny plugin function. Maximum is 4."
  };

const char		*bunny_strerror(int		errorid)
{
  if (errorid <= BE_CANT_GENERATE_RESSOURCE)
    return (strerror(errorid));
  if (errorid >= LAST_ERROR)
    return (NULL);
  return (bunny_errors[errorid - BE_CANT_GENERATE_RESSOURCE]);
}

