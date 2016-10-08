// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Bibliotheque Lapin

#include		"lapin_private.h"

void			bunny_ini_set_field(t_bunny_ini		*ini,
					    const char		*scope,
					    const char		*field,
					    unsigned int	index,
					    const char		*value)
{
  bpt::Ini		*in = (bpt::Ini*)ini;
  bpt::string		scop;
  bpt::string		fiel;

  if (scope != NULL)
    scop = scope;
  if (field != NULL)
    fiel = field;
  if (value != NULL)
    {
      bpt::string	&val = in->Access(scop, fiel, index);

      val = value;
    }
  else if (field == ERASE_SCOPE)
    in->GetData().erase(scop);
  else if (index == ERASE_FIELD)
    in->GetData()[scop].erase(fiel);
  else
    {
      /// That's shit. Why can't I create an iterator from an integer ?
      std::vector<bpt::string>	&dt = in->GetData()[scop][fiel];
      std::vector<bpt::string>::iterator	it;

      it = dt.begin() + index;
      if (it == dt.end())
	return ;
      dt.erase(it);
    }
}

