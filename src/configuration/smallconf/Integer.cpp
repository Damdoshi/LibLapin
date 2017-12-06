// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		"lapin_private.h"

void			SmallConf::SetInt(int			i)
{
  std::stringstream	ss;

  ss << i;
  original_value = ss.str();
  converted_2 = converted = i;
  is_converted = true;
  have_value = true;
  last_type = INTEGER;
}

bool			SmallConf::GetInt(int			*i,
					  SmallConf		*root,
					  SmallConf		*local,
					  SmallConf		*artif,
					  SmallConf		*param) const
{
  double		d;

  if (GetDouble(&d, root, local, artif, param) == false)
    {
      if (array.size() == 1)
	{
	  if (array[0]->GetInt(i, root, local, artif, param) == false)
	    return (false);
	  converted = *i;
	  return (true);
	}
      return (false);
    }
  converted_2 = converted;
  *i = converted_2;
  return (true);
}

