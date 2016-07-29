// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2015
//
// Bibliothèque Lapin

#include		"lapin_private.h"

const char		*bunny_ini_scope_get_field(const t_bunny_ini_scope	*sc,
						   const char			*field,
						   unsigned int			index)
{
  const bpt::Ini::Scope								*scope;
  std::map<bpt::string, bpt::Ini::FieldValue>::const_iterator			it;

  scope = (const bpt::Ini::Scope*)sc;
  if ((it = scope->find(bpt::string(field))) == scope->end())
    return (NULL);
  const std::vector<bpt::string>	&tab = it->second;

  if (tab.size() <= index)
    return (NULL);
  return (tab[index].c_str());
}

