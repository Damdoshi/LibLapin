// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include	"lapin_private.h"

bool		bunny_configuration_getf_node(t_bunny_configuration	*cnf,
					      t_bunny_configuration	**data,
					      const char		*pat,
					      ...)
{
  t_bunny_configuration *got;
  char		buffer[1024 * 4];
  va_list	lst;

  va_start(lst, pat);
  vsnprintf(&buffer[0], sizeof(buffer), pat, lst);
  if ((got = bunny_configuration_go_get_node(cnf, &buffer[0])) == NULL)
    return (false);
  *data = got;
  return (true);
}

bool		bunny_configuration_getf_string(t_bunny_configuration	*cnf,
						const char		**data,
						const char		*pat,
						...)
{
  const char	*got;
  char		buffer[1024 * 4];
  va_list	lst;

  va_start(lst, pat);
  vsnprintf(&buffer[0], sizeof(buffer), pat, lst);
  if (bunny_configuration_go_get_string(cnf, &got, &buffer[0]) == false)
    return (false);
  *data = got;
  return (true);
}

bool		bunny_configuration_getf_int(t_bunny_configuration	*cnf,
					     int			*data,
					     const char			*pat,
					     ...)
{
  int		got;
  char		buffer[1024 * 4];
  va_list	lst;

  va_start(lst, pat);
  vsnprintf(&buffer[0], sizeof(buffer), pat, lst);
  if (bunny_configuration_go_get_int(cnf, &got, &buffer[0]) == false)
    return (false);
  *data = got;
  return (true);
}

bool		bunny_configuration_getf_double(t_bunny_configuration	*cnf,
						double			*data,
						const char		*pat,
						...)
{
  double	got;
  char		buffer[1024 * 4];
  va_list	lst;

  va_start(lst, pat);
  vsnprintf(&buffer[0], sizeof(buffer), pat, lst);
  if (bunny_configuration_go_get_double(cnf, &got, &buffer[0]) == false)
    return (false);
  *data = got;
  return (true);
}

