// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

void			SmallConf::SetInt(int			i)
{
  if (alias_on)
    {
      alias_on->SetInt(i);
      return;
    }
  std::stringstream	ss;

  ss << i;
  original_value = ss.str();
  converted_2 = converted = i;
  is_converted = true;
  have_value = true;
  last_type = INTEGER;
  if (distant_int)
    *distant_int = i;
  if (distant_char)
    *distant_char = (char)(i & 0xFF);
  if (distant_bool)
    *distant_bool = !!i;
}

bool			SmallConf::GetInt(int			*i,
					  SmallConf		*root,
					  SmallConf		*local,
					  SmallConf		*artif,
					  SmallConf		*param) const
{
  double		d;

  if (alias_on)
    return (alias_on->GetInt(i, root, local, artif, param));
  if (distant_bool)
    {
      *i = *distant_bool;
      return (true);
    }
  if (distant_int)
    {
      *i = *distant_int;
      return (true);
    }
  if (distant_char)
    {
      *i = *distant_char;
      return (true);
    }

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

