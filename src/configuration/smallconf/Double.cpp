// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

void			SmallConf::SetDouble(double		v)
{
  if (alias_on)
    {
      alias_on->SetDouble(v);
      return;
    }

  std::stringstream	ss;

  ss << v;
  original_value = ss.str();
  converted_2 = converted = v;
  is_converted = true;
  have_value = true;
  last_type = DOUBLE;
  if (distant_double)
    *distant_double = v;
}

bool			SmallConf::GetDouble(double		*v,
					     SmallConf		*root,
					     SmallConf		*local,
					     SmallConf		*artif,
					     SmallConf		*param) const
{
  if (alias_on)
    return (alias_on->GetDouble(v, root, local, artif, param));

  if (distant_double)
    {
      *v = *distant_double;
      return (true);
    }

  if (expression && (root || local || artif || param))
    {
      if (root == NULL)
	root = (SmallConf*)bunny_configuration_get_root((t_bunny_configuration*)this);
      if (local == NULL)
	local = (SmallConf*)bunny_configuration_get_parent((t_bunny_configuration*)this);
      if (artif == NULL)
	artif = local;
      if (expr_compute((SmallConf&)*this, false, root, local, artif, param) == false)
	return (false);
    }
  if (have_value == false)
    {
      if (array.size() == 1)
	{
	  if (array[0]->GetDouble(v, root, local, artif, param) == false)
	    return (false);
	  converted = *v;
	  return (true);
	}
      return (false);
    }
  if (is_converted == false)
    {
      int		tmp;
      ssize_t		i = 0;

      if (readdouble(original_value.c_str(), i, converted) == false)
	{
	  if (readinteger(original_value.c_str(), i, tmp) == false)
	    return (false);
	  converted = tmp;
	}
      is_converted = true;
    }
  *v = converted;
  return (true);
}
