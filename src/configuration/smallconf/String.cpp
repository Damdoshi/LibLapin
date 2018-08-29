// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		<string.h>
#include		"lapin_private.h"

void			SmallConf::SetString(const std::string	&in,
					     bool		raw)
{
  original_value = in;
  have_value = true;
  if (raw)
    last_type = RAWSTRING;
  else
    last_type = STRING;
}

bool			SmallConf::GetString(const char		**out,
					     SmallConf		*root,
					     SmallConf		*local,
					     SmallConf		*artif,
					     SmallConf		*param) const

{
  if (expression && (root || local || artif || param))
    {
      if (expr_compute((SmallConf&)*this, NULL, false, root, local, artif, param) == false)
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
