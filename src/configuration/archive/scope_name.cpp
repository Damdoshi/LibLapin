// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2015
//
// Bibliothèque Lapin

#include		"lapin_private.h"

const char		*bunny_ini_scope_name(const t_bunny_ini		*in,
					      const t_bunny_ini_scope	*sc)
{
  std::map<bpt::string, bpt::Ini::Scope>::const_iterator		it;
  const bpt::Ini	*ini;
  const bpt::Ini::Scope	*scope;

  ini = (const bpt::Ini*)in;
  scope = (const bpt::Ini::Scope*)sc;
  for (it = ini->GetData().begin(); it != ini->GetData().end() &&
	 (t_bunny_ini_scope*)&it->second != scope; ++it);
  if (it == ini->GetData().end())
    return (NULL);
  return (it->first.c_str());
}
