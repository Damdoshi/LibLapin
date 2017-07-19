// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		"lapin_private.h"

t_bunny_configuration	*_bunny_configuration_go_get_node_va(const t_bunny_configuration *config,
							     size_t			nbr,
							     va_list			*lst)
{
  t_bunny_configuration	*cnf = (t_bunny_configuration*)config;
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

#define			PATTERN		"%p conf, %zu params, ... -> %p"

t_bunny_configuration	*bunny_configuration_go_get_node_va(t_bunny_configuration	*config,
							    size_t			nbr,
							    ...)
{
  t_bunny_configuration	*cnf;
  va_list		lst;

  va_start(lst, nbr);
  cnf = _bunny_configuration_go_get_node_va(config, nbr, &lst);
  va_end(lst);
  if (!cnf)
    scream_error_if(return (NULL), bunny_errno, PATTERN, config, nbr, cnf);
  scream_log_if(PATTERN, config, nbr, cnf);
  return (cnf);
}

#undef			PATTERN
#define			PATTERN		"%p config, %p target, %zu params, ... -> %s (%d)"

bool			bunny_configuration_go_get_int_va(const t_bunny_configuration	*config,
							  int				*val,
							  size_t			nbr,
							  ...)
{
  const t_bunny_configuration *cnf;
  va_list		lst;

  va_start(lst, nbr);
  if ((cnf = _bunny_configuration_go_get_node_va(config, nbr, &lst)) == NULL)
    scream_error_if(return (false), bunny_errno, PATTERN, config, val, nbr, "false", 0);
  va_end(lst);
  if (bunny_configuration_get_int(cnf, val) == false)
    scream_error_if(return (false), bunny_errno, PATTERN, config, val, nbr, "false", 0);
  scream_log_if(PATTERN, config, val, nbr, "true", *val);
  return (true);
}

#undef			PATTERN
#define			PATTERN		"%p config, %p target, %zu param, ... -> %s (%f)"

bool			bunny_configuration_go_get_double_va(const t_bunny_configuration *config,
							     double			*val,
							     size_t			nbr,
							     ...)
{
  const t_bunny_configuration *cnf;
  va_list		lst;

  va_start(lst, nbr);
  if ((cnf = _bunny_configuration_go_get_node_va(config, nbr, &lst)) == NULL)
    scream_error_if(return (false), bunny_errno, PATTERN, config, val, nbr, "false", nan(""));
  va_end(lst);
  if (bunny_configuration_get_double(cnf, val) == false)
    scream_error_if(return (false), bunny_errno, PATTERN, config, val, nbr, "false", nan(""));
  scream_log_if(PATTERN, config, val, nbr, "true", *val);
  return (true);
}

#undef			PATTERN
#define			PATTERN		"%p config, %p target, %zu param, ... -> %s (%s)"

bool			bunny_configuration_go_get_string_va(const t_bunny_configuration *config,
							     const char			**val,
							     size_t			nbr,
							     ...)
{
  const t_bunny_configuration *cnf;
  va_list		lst;

  va_start(lst, nbr);
  if ((cnf = _bunny_configuration_go_get_node_va(config, nbr, &lst)) == NULL)
    scream_error_if(return (false), bunny_errno, PATTERN, config, val, nbr, "false", "");
  va_end(lst);
  if (bunny_configuration_get_string(cnf, val) == false)
    scream_error_if(return (false), bunny_errno, PATTERN, config, val, nbr, "false", "");
  scream_log_if(PATTERN, config, val, nbr, "true", *val);
  return (true);
}

t_bunny_configuration	*_bunny_configuration_go_get_node(const t_bunny_configuration	*config,
							  const char			*addr)
{
  t_bunny_configuration	*cnf = (t_bunny_configuration*)config;
  const char		*str;
  char			buffer[4096];
  ssize_t		i, j;

  i = j = 0;
  while (addr[i])
    {
      if (readchar(addr, j, fieldname) == false)
	return (NULL);
      if (j - i >= (ssize_t)sizeof(buffer) - 1)
	return (NULL);
      strncpy(&buffer[0], &addr[i], j - i);
      buffer[j - i] = '\0';
      if ((cnf = bunny_configuration_get_child(cnf, &buffer[0])) == NULL)
	return (NULL);
      while (readtext(addr, j, "["))
	{
	  i = j;
	  j = strtol(&addr[i], (char**)&str, 0);
	  if (str == &addr[i])
	    return (NULL);
	  if ((cnf = bunny_configuration_get_case(cnf, j)) == NULL)
	    return (NULL);
	  i += str - &addr[i];
	  if (readtext(addr, i, "]") == false)
	    return (NULL);
	  j = i;
	}
      if (readtext(addr, j, "->"))
	{
	  if (bunny_configuration_get_string(cnf, &str) == false)
	    return (NULL);
	  cnf = bunny_configuration_get_root(cnf);
	  if ((cnf = _bunny_configuration_go_get_node(cnf, str)) == NULL)
	    return (NULL);
	}
      else if (readtext(addr, j, ".") == false)
	return (cnf);
      i = j;
    }
  return (cnf);
}

#undef			PATTERN
#define			PATTERN		"%p config, %s address -> %p"

t_bunny_configuration	*bunny_configuration_go_get_node(t_bunny_configuration		*config,
							 const char			*addr)
{
  t_bunny_configuration	*cnf;

  if ((cnf = _bunny_configuration_go_get_node(config, addr)) == NULL)
    scream_error_if(return (NULL), bunny_errno, PATTERN, config, addr, cnf);
  scream_log_if(PATTERN, config, addr, cnf);
  return (cnf);
}

#undef			PATTERN
#define			PATTERN		"%p config, %p target, %s address -> %s (%s)"

bool			bunny_configuration_go_get_string(t_bunny_configuration		*config,
							  const char			**val,
							  const char			*addr)
{
  t_bunny_configuration	*cnf = bunny_configuration_go_get_node(config, addr);

  if (cnf == NULL)
    scream_error_if(return (false), bunny_errno, PATTERN, config, val, addr, "false", "");
  if (bunny_configuration_get_string(cnf, val) == false)
    scream_error_if(return (false), bunny_errno, PATTERN, config, val, addr, "false", "");
  scream_log_if(PATTERN, config, val, addr, "true", *val);
  return (true);
}

#undef			PATTERN
#define			PATTERN		"%p config, %p target, %s address -> %s (%f)"

bool			bunny_configuration_go_get_double(t_bunny_configuration		*config,
							  double			*val,
							  const char			*addr)
{
  t_bunny_configuration	*cnf = bunny_configuration_go_get_node(config, addr);

  if (cnf == NULL)
    scream_error_if(return (false), bunny_errno, PATTERN, config, val, addr, "false", nan(""));
  if (bunny_configuration_get_double(cnf, val) == false)
    scream_error_if(return (false), bunny_errno, PATTERN, config, val, addr, "false", nan(""));
  scream_log_if(PATTERN, config, val, addr, "true", *val);
  return (true);
}

#undef			PATTERN
#define			PATTERN		"%p config, %p target, %s address -> %s (%d)"

bool			bunny_configuration_go_get_int(t_bunny_configuration		*config,
						       int				*val,
						       const char			*addr)
{
  t_bunny_configuration	*cnf = bunny_configuration_go_get_node(config, addr);

  if (cnf == NULL)
    scream_error_if(return (false), bunny_errno, PATTERN, config, val, addr, "false", 0);
  if (bunny_configuration_get_int(cnf, val) == false)
    scream_error_if(return (false), bunny_errno, PATTERN, config, val, addr, "false", 0);
  scream_log_if(PATTERN, config, val, addr, "true", *val);
  return (true);
}

