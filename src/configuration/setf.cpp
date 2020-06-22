// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include	"lapin_private.h"

bool		bunny_configuration_vsetf_node(t_bunny_configuration	*cnf,
					       const t_bunny_configuration *data,
					       const char		*pat,
					       va_list			lst)
{
  bool		cmode = bunny_configuration_get_create_mode();
  t_bunny_configuration *got;
  char		buffer[1024 * 4];

  vsnprintf(&buffer[0], sizeof(buffer), pat, lst);
  bunny_configuration_create_mode(true);
  if ((got = bunny_configuration_go_get_node(cnf, &buffer[0])) == NULL)
    {
      bunny_configuration_create_mode(cmode);
      return (false);
    }
  if (data == NULL)
    {
      bunny_configuration_create_mode(cmode);
      bunny_delete_configuration(got);
      return (true);
    }
  SmallConf	*a;
  const SmallConf *b;

  a = (SmallConf*)got;
  b = (const SmallConf*)data;
  *a = *b;
  bunny_configuration_create_mode(cmode);
  return (true);
}

bool		bunny_configuration_setf_node(t_bunny_configuration	*cnf,
					      const t_bunny_configuration *data,
					      const char		*pat,
					      ...)
{
  va_list	lst;

  va_start(lst, pat);
  return (bunny_configuration_vsetf_node(cnf, data, pat, lst));
}

bool		bunny_configuration_vsetf_string(t_bunny_configuration	*cnf,
						 const char		*data,
						 const char		*pat,
						 va_list		lst)
{
  bool		cmode = bunny_configuration_get_create_mode();
  char		buffer[1024 * 4];
  bool		ret;

  vsnprintf(&buffer[0], sizeof(buffer), pat, lst);
  bunny_configuration_create_mode(true);
  ret = (bunny_configuration_go_set_string(cnf, data, &buffer[0]));
  bunny_configuration_create_mode(cmode);
  return (ret);
}

bool		bunny_configuration_setf_string(t_bunny_configuration	*cnf,
						const char		*data,
						const char		*pat,
						...)
{
  va_list	lst;

  va_start(lst, pat);
  return (bunny_configuration_vsetf_string(cnf, data, pat, lst));
}

bool		bunny_configuration_vsetf_int(t_bunny_configuration	*cnf,
					      int			data,
					      const char		*pat,
					      va_list			lst)
{
  bool		cmode = bunny_configuration_get_create_mode();
  char		buffer[1024 * 4];
  bool		ret;

  vsnprintf(&buffer[0], sizeof(buffer), pat, lst);
  bunny_configuration_create_mode(true);
  ret = (bunny_configuration_go_set_int(cnf, data, &buffer[0]));
  bunny_configuration_create_mode(cmode);
  return (ret);
}

bool		bunny_configuration_setf_int(t_bunny_configuration	*cnf,
					     int			data,
					     const char			*pat,
					     ...)
{
  va_list	lst;

  va_start(lst, pat);
  return (bunny_configuration_vsetf_int(cnf, data, pat, lst));
}

bool		bunny_configuration_vsetf_double(t_bunny_configuration	*cnf,
						 double			data,
						 const char		*pat,
						 va_list		lst)
{
  bool		cmode = bunny_configuration_get_create_mode();
  char		buffer[1024 * 4];
  bool		ret;

  vsnprintf(&buffer[0], sizeof(buffer), pat, lst);
  bunny_configuration_create_mode(true);
  ret = (bunny_configuration_go_set_double(cnf, data, &buffer[0]));
  bunny_configuration_create_mode(cmode);
  return (ret);
}

bool		bunny_configuration_setf_double(t_bunny_configuration	*cnf,
						double			data,
						const char		*pat,
						...)
{
  va_list	lst;

  va_start(lst, pat);
  return (bunny_configuration_vsetf_double(cnf, data, pat, lst));
}

