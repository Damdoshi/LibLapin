// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Bibliothèque Lapin

#include		"lapin_private.h"

const char		*bunny_ini_field_name(const t_bunny_ini_scope	*scope,
					      const t_bunny_ini_field	*field)
{
  const bpt::Ini::Scope	*scop = (const bpt::Ini::Scope*)scope;
  std::map<std::string, bpt::Ini::FieldValue>::const_iterator it;

  for (it = scop->begin(); it != scop->end() &&
	 (t_bunny_ini_field*)&it->second != field; ++it);
  if (it == scop->end())
    return (NULL);
  return (it->first.c_str());
}

