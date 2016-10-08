// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Bibliothèque Lapin

#include		"lapin_private.h"

t_bunny_ini_scope	*bunny_ini_get_scope(t_bunny_ini		*ini,
					     const char			*scope)
{
  bpt::Ini		*in = (bpt::Ini*)ini;
  std::map<std::string, bpt::Ini::Scope>::iterator it;

  if ((it = in->GetData().find(std::string(scope))) == in->GetData().end())
    return (NULL);
  return (&it->second);
}

