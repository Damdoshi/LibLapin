// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		<string.h>
#include		"lapin_private.h"

void			SmallConf::SetString(const std::string	&in,
					     bool		raw)
{
  if (alias_on)
    {
      alias_on->SetString(in, raw);
      return;
    }
  original_value = in;
  have_value = true;
  if (raw)
    last_type = RAWSTRING;
  else
    last_type = STRING;
  if (distant_string)
    {
      if (*distant_string)
	bunny_free(*distant_string);
      *distant_string = bunny_strdup(original_value.c_str());
    }
}

bool			SmallConf::GetString(const char		**out,
					     SmallConf		*root,
					     SmallConf		*local,
					     SmallConf		*artif,
					     SmallConf		*param) const

{
  if (alias_on)
    return (alias_on->GetString(out, root, local, artif, param));

  if (distant_string)
    {
      *out = *distant_string;
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
	  if (array[0]->GetString(out, root, local, artif, param) == false)
	    return (false);
	  original_value = *out;
	  return (true);
	}
      return (false);
    }
  *out = original_value.c_str();
  return (true);
}
