// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include	"lapin_private.h"

bool		bunny_configuration_vgetf_node(t_bunny_configuration	*cnf,
					       t_bunny_configuration	**data,
					       const char		*pat,
					       va_list			lst)
{
  t_bunny_configuration *got;
  char		buffer[1024 * 4];

  vsnprintf(&buffer[0], sizeof(buffer), pat, lst);
  if ((got = bunny_configuration_go_get_node(cnf, &buffer[0])) == NULL)
    return (false);
  if (data)
    *data = got;
  return (true);
}

bool		bunny_configuration_getf_node(t_bunny_configuration	*cnf,
					      t_bunny_configuration	**data,
					      const char		*pat,
					      ...)
{
  va_list	lst;

  va_start(lst, pat);
  return (bunny_configuration_vgetf_node(cnf, data, pat, lst));
}

bool		bunny_configuration_vgetf_string(t_bunny_configuration	*cnf,
						 const char		**data,
						 const char		*pat,
						 va_list		lst)
{
  const char	*got;
  char		buffer[1024 * 4];

  vsnprintf(&buffer[0], sizeof(buffer), pat, lst);
  if (bunny_configuration_go_get_string(cnf, &got, &buffer[0]) == false)
    return (false);
  if (data)
    *data = got;
  return (true);
}

bool		bunny_configuration_getf_string(t_bunny_configuration	*cnf,
						const char		**data,
						const char		*pat,
						...)
{
  va_list	lst;

  va_start(lst, pat);
  return (bunny_configuration_vgetf_string(cnf, data, pat, lst));
}

bool		bunny_configuration_vgetf_int(t_bunny_configuration	*cnf,
					      int			*data,
					      const char		*pat,
					      va_list			lst)
{
  int		got;
  char		buffer[1024 * 4];

  vsnprintf(&buffer[0], sizeof(buffer), pat, lst);
  if (bunny_configuration_go_get_int(cnf, &got, &buffer[0]) == false)
    return (false);
  if (data)
    *data = got;
  return (true);
}

bool		bunny_configuration_getf_int(t_bunny_configuration	*cnf,
					     int			*data,
					     const char			*pat,
					     ...)
{
  va_list	lst;

  va_start(lst, pat);
  return (bunny_configuration_vgetf_int(cnf, data, pat, lst));
}

bool		bunny_configuration_vgetf_bool(t_bunny_configuration	*cnf,
					       bool			*data,
					       const char		*pat,
					       va_list			lst)
{
  int		got;
  char		buffer[1024 * 4];

  vsnprintf(&buffer[0], sizeof(buffer), pat, lst);
  if (bunny_configuration_go_get_int(cnf, &got, &buffer[0]) == false)
    return (false);
  if (data)
    *data = !!got;
  return (true);
}

bool		bunny_configuration_getf_bool(t_bunny_configuration	*cnf,
					      bool			*data,
					      const char		*pat,
					      ...)
{
  va_list	lst;

  va_start(lst, pat);
  return (bunny_configuration_vgetf_bool(cnf, data, pat, lst));
}

bool		bunny_configuration_vgetf_double(t_bunny_configuration	*cnf,
						 double			*data,
						 const char		*pat,
						 va_list		lst)
{
  double	got;
  char		buffer[1024 * 4];

  vsnprintf(&buffer[0], sizeof(buffer), pat, lst);
  if (bunny_configuration_go_get_double(cnf, &got, &buffer[0]) == false)
    return (false);
  if (data)
    *data = got;
  return (true);
}


bool		bunny_configuration_getf_double(t_bunny_configuration	*cnf,
						 double			*data,
						 const char		*pat,
						 ...)
{
  va_list	lst;

  va_start(lst, pat);
  return (bunny_configuration_vgetf_double(cnf, data, pat, lst));
}
