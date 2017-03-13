// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		"lapin_private.h"

t_bunny_configuration	*_bunny_configuration_go_get_node_va(t_bunny_configuration	*config,
							     size_t			nbr,
							     va_list			*lst)
{
  t_bunny_configuration	*cnf = config;
  union
  {
    int			i;
    const char		*p;
  }			buf;
  size_t		i;

  for (i = 0; i < nbr; ++i)
    {
      buf.p = va_arg(*lst, const char*);
      if (buf.i <= 0)
	cnf = bunny_configuration_get_case(cnf, -buf.i);
      else
	cnf = bunny_configuration_get_child(cnf, buf.p);
      if (cnf == NULL)
	return (NULL);
    }
  return (cnf);
}

t_bunny_configuration	*bunny_configuration_go_get_node_va(t_bunny_configuration	*config,
							    size_t			nbr,
							    ...)
{
  t_bunny_configuration	*cnf;
  va_list		lst;

  va_start(lst, nbr);
  cnf = _bunny_configuration_go_get_node_va(config, nbr, &lst);
  va_end(lst);
  return (cnf);
}

bool			bunny_configuration_go_get_int_va(t_bunny_configuration		*config,
							  int				*val,
							  size_t			nbr,
							  ...)
{
  t_bunny_configuration	*cnf;
  va_list		lst;

  va_start(lst, nbr);
  if ((cnf = _bunny_configuration_go_get_node_va(config, nbr, &lst)) == NULL)
    return (false);
  va_end(lst);
  return (bunny_configuration_get_int(cnf, val));
}

bool			bunny_configuration_go_get_double_va(t_bunny_configuration	*config,
							     double			*val,
							     size_t			nbr,
							     ...)
{
  t_bunny_configuration	*cnf;
  va_list		lst;

  va_start(lst, nbr);
  if ((cnf = _bunny_configuration_go_get_node_va(config, nbr, &lst)) == NULL)
    return (false);
  va_end(lst);
  return (bunny_configuration_get_double(cnf, val));
}

bool			bunny_configuration_go_get_string_va(t_bunny_configuration	*config,
							     const char			**val,
							     size_t			nbr,
							     ...)
{
  t_bunny_configuration	*cnf;
  va_list		lst;

  va_start(lst, nbr);
  if ((cnf = _bunny_configuration_go_get_node_va(config, nbr, &lst)) == NULL)
    return (false);
  va_end(lst);
  return (bunny_configuration_get_string(cnf, val));
}

