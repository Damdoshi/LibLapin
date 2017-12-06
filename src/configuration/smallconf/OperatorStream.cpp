// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		"lapin_private.h"

std::ostream		&operator<<(std::ostream		&os,
				    const SmallConf		&cnf)
{
  int			a;
  double		b;
  const char		*c;

  if (cnf.last_type == SmallConf::INTEGER)
    {
      if (cnf.GetInt(&a))
	os << a;
    }
  else if (cnf.last_type == SmallConf::DOUBLE)
    {
      if (cnf.GetDouble(&b))
	os << b;
    }
  else if (cnf.last_type == SmallConf::STRING)
    {
      if (cnf.GetString(&c))
	os << c;
    }
  return (os);
}

