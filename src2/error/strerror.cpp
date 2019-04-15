// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2019
//
// Lapin library

#include		<string.h>
#define			__LAPIN_H__
#include		"private2/logs.hpp"

namespace
{
  const char * const	gl_bunny_error_msg[LAST_ERROR - BE_CANT_GENERATE_RESSOURCE] =
    {
      "Cannot generated ressource",
      "Syntax error",
      "Bad address or variable",
      "Type mismatch",
      "Container is empty",
      "Duplication failed",
      "Cannot find requested element",
      "No embedded key found",
      "No display device available",
      "Missing function in plugin",
      "Too many parameters",
      "Context or something in context is missing"
    };
}

const char		*bunny_strerror(int		ercode)
{
  if (ercode >= BE_CANT_GENERATE_RESSOURCE)
    return (gl_bunny_error_msg[ercode - BE_CANT_GENERATE_RESSOURCE]);
  return ((const char*)strerror(ercode));
}

