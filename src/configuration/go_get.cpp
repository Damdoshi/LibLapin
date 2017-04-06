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

bool			bunny_configuration_go_get_int_va(const t_bunny_configuration	*config,
							  int				*val,
							  size_t			nbr,
							  ...)
{
  const t_bunny_configuration *cnf;
  va_list		lst;

  va_start(lst, nbr);
  if ((cnf = _bunny_configuration_go_get_node_va(config, nbr, &lst)) == NULL)
    return (false);
  va_end(lst);
  return (bunny_configuration_get_int(cnf, val));
}

bool			bunny_configuration_go_get_double_va(const t_bunny_configuration *config,
							     double			*val,
							     size_t			nbr,
							     ...)
{
  const t_bunny_configuration *cnf;
  va_list		lst;

  va_start(lst, nbr);
  if ((cnf = _bunny_configuration_go_get_node_va(config, nbr, &lst)) == NULL)
    return (false);
  va_end(lst);
  return (bunny_configuration_get_double(cnf, val));
}

bool			bunny_configuration_go_get_string_va(const t_bunny_configuration *config,
							     const char			**val,
							     size_t			nbr,
							     ...)
{
  const t_bunny_configuration *cnf;
  va_list		lst;

  va_start(lst, nbr);
  if ((cnf = _bunny_configuration_go_get_node_va(config, nbr, &lst)) == NULL)
    return (false);
  va_end(lst);
  return (bunny_configuration_get_string(cnf, val));
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
    }
  return (cnf);
}

t_bunny_configuration	*bunny_configuration_go_get_node(t_bunny_configuration		*config,
							 const char			*addr)
{
  return (_bunny_configuration_go_get_node(config, addr));
}

bool			bunny_configuration_go_get_string(t_bunny_configuration		*config,
							  const char			**val,
							  const char			*addr)
{
  t_bunny_configuration	*cnf = bunny_configuration_go_get_node(config, addr);

  if (cnf == NULL)
    return (false);
  return (bunny_configuration_get_string(cnf, val));
}

bool			bunny_configuration_go_get_double(t_bunny_configuration		*config,
							  double			*val,
							  const char			*addr)
{
  t_bunny_configuration	*cnf = bunny_configuration_go_get_node(config, addr);

  if (cnf == NULL)
    return (false);
  return (bunny_configuration_get_double(cnf, val));
}

bool			bunny_configuration_go_get_int(t_bunny_configuration		*config,
						       int				*val,
						       const char			*addr)
{
  t_bunny_configuration	*cnf = bunny_configuration_go_get_node(config, addr);

  if (cnf == NULL)
    return (false);
  return (bunny_configuration_get_int(cnf, val));
}

