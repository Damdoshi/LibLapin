// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2015
//
// Bibliothèque Lapin

#include		"lapin_private.h"

void			bunny_ini_scope_set_field(t_bunny_ini_scope		*sc,
						  const char			*field,
						  unsigned int			index,
						  const char			*value)
{
  bpt::Ini::Scope		*scope;
  std::vector<bpt::string>	*vec;

  scope = (bpt::Ini::Scope*)sc;
  vec = &(*scope)[bpt::string(field)];
  if (vec->size() < index)
    return ;
  (*vec)[index] = value;
}

