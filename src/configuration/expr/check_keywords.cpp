// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin Library

#include		"lapin_private.h"

bool			check_keywords(const std::string		&str)
{
  const char		*cstr = str.c_str();

  if (strcasecmp(cstr, "then") == 0)
    return (false);
  if (strcasecmp(cstr, "else") == 0)
    return (false);
  return (true);
}

