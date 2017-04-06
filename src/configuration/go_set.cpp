// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		"lapin_private.h"

t_bunny_configuration	*_bunny_configuration_go_get_node_va(const t_bunny_configuration *config,
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

t_bunny_configuration	*_bunny_configuration_go_get_node(const t_bunny_configuration	*config,
							  const char			*addr);

bool			bunny_configuration_go_set_string(t_bunny_configuration		*config,
							  const char			*val,
							  const char			*addr)
{
  t_bunny_configuration	*cnf;

  if ((cnf = _bunny_configuration_go_get_node(config, addr)) == NULL)
    return (false);
  bunny_configuration_set_string(cnf, val);
  return (true);
}

bool			bunny_configuration_go_set_double(t_bunny_configuration		*config,
							  double			val,
							  const char			*addr)
{
  t_bunny_configuration	*cnf;

  if ((cnf = _bunny_configuration_go_get_node(config, addr)) == NULL)
    return (false);
  bunny_configuration_set_double(cnf, val);
  return (true);
}

bool			bunny_configuration_go_set_int(t_bunny_configuration		*config,
						       int				val,
						       const char			*addr)
{
  t_bunny_configuration	*cnf;

  if ((cnf = _bunny_configuration_go_get_node(config, addr)) == NULL)
    return (false);
  bunny_configuration_set_int(cnf, val);
  return (true);
}


