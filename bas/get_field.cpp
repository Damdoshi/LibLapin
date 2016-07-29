// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Bibliotheque Lapin

#include		"lapin_private.h"

const char		*bunny_ini_get_field(const t_bunny_ini		*ini,
					     const char			*scope,
					     const char			*field,
					     unsigned int		index)
{
  const bpt::Ini	*in = (bpt::Ini*)ini;
  bpt::string		scop;
  bpt::string		fiel = field;

  if (scope != NULL)
    scop = scope;

  const bpt::string	&rep = in->Access(scop, fiel, index);

  if (&rep == &in->npos)
    return (NULL);
  return (rep.c_str());
}

