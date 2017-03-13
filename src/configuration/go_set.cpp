// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		"lapin_private.h"

t_bunny_configuration	*_bunny_configuration_go_get_node_va(t_bunny_configuration	*config,
							     size_t			nbr,
							     va_list			*lst);


bool			bunny_configuration_go_set_int_va(t_bunny_configuration		*config,
							  int				val,
							  size_t			nbr,
							  ...)
{
  t_bunny_configuration	*cnf;
  va_list		lst;

  va_start(lst, nbr);
  if ((cnf = _bunny_configuration_go_get_node_va(config, nbr, &lst)) == NULL)
    return (false);
  va_end(lst);
  bunny_configuration_set_int(cnf, val);
  return (true);
}

bool			bunny_configuration_go_set_double_va(t_bunny_configuration	*config,
							     double			val,
							     size_t			nbr,
							     ...)
{
  t_bunny_configuration	*cnf;
  va_list		lst;

  va_start(lst, nbr);
  if ((cnf = _bunny_configuration_go_get_node_va(config, nbr, &lst)) == NULL)
    return (false);
  va_end(lst);
  bunny_configuration_set_double(cnf, val);
  return (true);
}

bool			bunny_configuration_go_set_string_va(t_bunny_configuration	*config,
							     const char			*val,
							     size_t			nbr,
							     ...)
{
  t_bunny_configuration	*cnf;
  va_list		lst;

  va_start(lst, nbr);
  if ((cnf = _bunny_configuration_go_get_node_va(config, nbr, &lst)) == NULL)
    return (false);
  va_end(lst);
  bunny_configuration_set_string(cnf, val);
  return (true);
}


