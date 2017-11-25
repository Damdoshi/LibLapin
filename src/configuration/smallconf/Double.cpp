// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		"lapin_private.h"

void			SmallConf::SetDouble(double			v)
{
  std::stringstream	ss;

  ss << v;
  original_value = ss.str();
  converted_2 = converted = v;
  is_converted = true;
  have_value = true;
  last_type = DOUBLE;
}

bool			SmallConf::GetDouble(double			*v) const
{
  if (expression)
    {
      if (expr_compute(*expression, false, NULL, NULL, NULL, NULL) == false)
	return (false);
      if (expression->val.GetDouble(v) == false)
	return (false);
      converted = *v;
      is_converted = true;
      have_value = true;
    }
  if (have_value == false)
    {
      if (array.size() == 1)
	{
	  if (array[0]->GetDouble(v) == false)
	    return (false);
	  converted = *v;
	  return (true);
	}
      return (false);
    }
  if (is_converted == false)
    {
      ssize_t		i = 0;

      if (readdouble(original_value.c_str(), i, converted) == false)
	return (false);
      is_converted = true;
    }
  *v = converted;
  return (true);
}
