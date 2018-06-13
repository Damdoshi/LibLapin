// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include	"lapin_private.h"

bool		bunny_configuration_setf_node(t_bunny_configuration	*cnf,
					      const t_bunny_configuration *data,
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
  SmallConf	*a;
  const SmallConf *b;

  a = (SmallConf*)got;
  b = (const SmallConf*)data;
  *a = *b;
  return (true);
}

bool		bunny_configuration_setf_string(t_bunny_configuration	*cnf,
						const char		*data,
						const char		*pat,
						...)
{
  char		buffer[1024 * 4];
  va_list	lst;

  va_start(lst, pat);
  vsnprintf(&buffer[0], sizeof(buffer), pat, lst);
  return (bunny_configuration_go_set_string(cnf, data, &buffer[0]));
}

bool		bunny_configuration_setf_int(t_bunny_configuration	*cnf,
					     int			data,
					     const char			*pat,
					     ...)
{
  char		buffer[1024 * 4];
  va_list	lst;

  va_start(lst, pat);
  vsnprintf(&buffer[0], sizeof(buffer), pat, lst);
  return (bunny_configuration_go_set_int(cnf, data, &buffer[0]));
}


bool		bunny_configuration_setf_double(t_bunny_configuration	*cnf,
						double			data,
						const char		*pat,
						...)
{
  char		buffer[1024 * 4];
  va_list	lst;

  va_start(lst, pat);
  vsnprintf(&buffer[0], sizeof(buffer), pat, lst);
  return (bunny_configuration_go_set_double(cnf, data, &buffer[0]));
}

