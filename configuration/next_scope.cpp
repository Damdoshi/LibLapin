// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2015
//
// Bibliothèque Lapin

#include		"lapin_private.h"

t_bunny_ini_scope	*bunny_ini_next_scope(t_bunny_ini		*in,
					      t_bunny_ini_scope		*scope)
{
  std::map<bpt::string, bpt::Ini::Scope>::iterator			it;
  bpt::Ini		*ini = (bpt::Ini*)in;

  for (it = ini->GetData().begin(); it != ini->GetData().end() &&
	 (t_bunny_ini_scope*)&it->second != scope; ++it);
  if (it == ini->GetData().end())
    return (NULL);
  if (++it == ini->GetData().end())
    return (NULL);
  return (&it->second);
}

