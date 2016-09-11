// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Bibliothèque Lapin

#include		"lapin_private.h"

t_bunny_ini_field	*bunny_ini_first_field(t_bunny_ini_scope	*scope)
{
  bpt::Ini::Scope	*scop = (bpt::Ini::Scope*)scope;
  std::map<bpt::string, bpt::Ini::FieldValue>::iterator	it;

  if (scop->empty())
    return (NULL);
  return (&scop->begin()->second);
}

