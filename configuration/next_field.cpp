// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Bibliothèque Lapin

#include		"lapin_private.h"

t_bunny_ini_field	*bunny_ini_next_field(t_bunny_ini_scope		*scope,
					      t_bunny_ini_field		*field)
{
  bpt::Ini::Scope	*scop = (bpt::Ini::Scope*)scope;
  std::map<std::string, bpt::Ini::FieldValue>::iterator	it;

  for (it = scop->begin(); it != scop->end() &&
	 (t_bunny_ini_field*)&it->second != field; ++it);
  if (it == scop->end())
    return (NULL);
  if (++it == scop->end())
    return (NULL);
  return (&it->second);
}

