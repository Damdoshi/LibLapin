// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

bool			expr_test_type(SmallConf		&ope,
				       int			a,
				       int			b,
				       int			c)
{
  if (ope.have_value == false || ope.last_type == SmallConf::RAWSTRING)
    return (true);
  if (a >= 0 && ope.last_type == a)
    return (true);
  if (b >= 0 && ope.last_type == b)
    return (true);
  if (c >= 0 && ope.last_type == c)
    return (true);
  return (false);
}
