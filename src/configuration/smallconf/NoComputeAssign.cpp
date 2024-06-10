// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2024
//
// Lapin library

#include		"lapin_private.h"

SmallConf		&SmallConf::NoComputeAssign(const SmallConf	&o)
{
  if (&o == this)
    return (*this);
  if (!(have_value = o.have_value))
    return (*this);
  switch (last_type = o.last_type)
    {
    case STRING:
    case RAWSTRING:
      original_value = o.original_value;
      if (distant_string)
	{
	  if (*distant_string)
	    bunny_free(*distant_string);
	  *distant_string = bunny_strdup(original_value.c_str());
	}
      if (!o.is_converted)
	break ;
    case INTEGER:
    case DOUBLE:
      converted_2 = o.converted_2;
      converted = o.converted;
      original_value = o.original_value;
      if (distant_bool)
	*distant_bool = !!converted;
      if (distant_int)
	*distant_int = converted;
      if (distant_double)
	*distant_double = converted_2;
    }
  // is_const = o.is_const;
  return (*this);
}

