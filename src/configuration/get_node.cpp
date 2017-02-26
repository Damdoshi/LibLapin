// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		"lapin_private.h"

t_bunny_configuration	*bunny_configuration_go_get_node_va(t_bunny_configuration	*config,
							    size_t			nbr,
							    ...)
{
  t_bunny_configuration	*cnf = config;
  va_list		lst;
  union
  {
    int			i;
    const char		*p;
  }			buf;
  size_t		i;

  va_start(lst, nbr);
  for (i = 0; i < nbr; ++i)
    {
      buf.p = va_arg(lst, const char*);
      if (buf.i <= 0)
	cnf = bunny_configuration_get_case(cnf, -buf.i);
      else
	cnf = bunny_configuration_get_child(cnf, buf.p);
      if (cnf == NULL)
	return (NULL);
    }
  va_end(lst);
  return (cnf);
}

