// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		<string.h>
#include		"lapin_private.h"

void			SmallConf::SetString(const std::string		&in,
					     bool			raw)
{
  original_value = in;
  have_value = true;
  if (raw)
    last_type = RAWSTRING;
  else
    last_type = STRING;
}

bool			SmallConf::GetString(const char			**out) const
{
  if (expression)
    {
      if (expr_compute(*expression, false, NULL, NULL, NULL, NULL) == false)
	return (false);
      if (expression->val.GetString(out) == false)
	return (false);
      original_value = *out;
      have_value = true;
    }
  if (have_value == false)
    {
      if (array.size() == 1)
	{
	  if (array[0]->GetString(out) == false)
	    return (false);
	  original_value = *out;
	  return (true);
	}
      return (false);
    }
  *out = original_value.c_str();
  return (true);
}
