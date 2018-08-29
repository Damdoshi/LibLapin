// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

t_bunny_configuration	*_bunny_configuration_go_get_node_va(const t_bunny_configuration *config,
							     size_t			nbr,
							     va_list			*lst);

#define			PATTERN		"%p config, %d value, %zu params, ... -> %s"

bool			bunny_configuration_go_set_int_va(t_bunny_configuration		*config,
							  int				val,
							  size_t			nbr,
							  ...)
{
  t_bunny_configuration	*cnf;
  va_list		lst;

  va_start(lst, nbr);
  if ((cnf = _bunny_configuration_go_get_node_va(config, nbr, &lst)) == NULL)
    scream_error_if
      (return (false), bunny_errno, PATTERN, "configuration", config, val, nbr, "false");
  va_end(lst);
  bunny_configuration_set_int(cnf, val);
  scream_log_if(PATTERN, "configuration", config, val, nbr, "true");
  return (true);
}

#undef			PATTERN
#define			PATTERN		"%p config, %f value, %zu params, ... -> %s"

bool			bunny_configuration_go_set_double_va(t_bunny_configuration	*config,
							     double			val,
							     size_t			nbr,
							     ...)
{
  t_bunny_configuration	*cnf;
  va_list		lst;

  va_start(lst, nbr);
  if ((cnf = _bunny_configuration_go_get_node_va(config, nbr, &lst)) == NULL)
    scream_error_if
      (return (false), bunny_errno, PATTERN, "configuration", config, val, nbr, "false");
  va_end(lst);
  bunny_configuration_set_double(cnf, val);
  scream_log_if(PATTERN, "configuration", config, val, nbr, "true");
  return (true);
}

#undef			PATTERN
#define			PATTERN		"%p config, %s value, %zu params, ... -> %s"

bool			bunny_configuration_go_set_string_va(t_bunny_configuration	*config,
							     const char			*val,
							     size_t			nbr,
							     ...)
{
  t_bunny_configuration	*cnf;
  va_list		lst;

  va_start(lst, nbr);
  if ((cnf = _bunny_configuration_go_get_node_va(config, nbr, &lst)) == NULL)
    scream_error_if
      (return (false), bunny_errno, PATTERN, "configuration", config, val, nbr, "false");
  va_end(lst);
  bunny_configuration_set_string(cnf, val);
  scream_log_if(PATTERN, "configuration", config, val, nbr, "true");
  return (true);
}

t_bunny_configuration	*_bunny_configuration_go_get_node(const t_bunny_configuration	*config,
							  const char			*addr,
							  ssize_t			&i);

#undef			PATTERN
#define			PATTERN		"%p config, %s value, %s address -> %s"

bool			bunny_configuration_go_set_string(t_bunny_configuration		*config,
							  const char			*val,
							  const char			*addr)
{
  t_bunny_configuration	*cnf;

  if ((cnf = bunny_configuration_go_get_node(config, addr)) == NULL)
    scream_error_if
      (return (false), bunny_errno, PATTERN, "configuration", config, val, addr, "false");
  bunny_configuration_set_string(cnf, val);
  scream_log_if(PATTERN, "configuration", config, val, addr, "true");
  return (true);
}

#undef			PATTERN
#define			PATTERN		"%p config, %f value, %s address -> %s"

bool			bunny_configuration_go_set_double(t_bunny_configuration		*config,
							  double			val,
							  const char			*addr)
{
  t_bunny_configuration	*cnf;

  if ((cnf = bunny_configuration_go_get_node(config, addr)) == NULL)
    scream_error_if
      (return (false), bunny_errno, PATTERN, "configuration", config, val, addr, "false");
  bunny_configuration_set_double(cnf, val);
  scream_log_if(PATTERN, "configuration", config, val, addr, "true");
  return (true);
}

#undef			PATTERN
#define			PATTERN		"%p config, %d value, %s address -> %s"

bool			bunny_configuration_go_set_int(t_bunny_configuration		*config,
						       int				val,
						       const char			*addr)
{
  t_bunny_configuration	*cnf;

  if ((cnf = bunny_configuration_go_get_node(config, addr)) == NULL)
    scream_error_if
      (return (false), bunny_errno, PATTERN, "configuration", config, val, addr, "false");
  bunny_configuration_set_int(cnf, val);
  scream_log_if(PATTERN, "configuration", config, val, addr, "true");
  return (true);
}


