// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include	"lapin_private.h"

bool		bunny_configuration_bindf_int(t_bunny_configuration	*cnf,
					      int			*i,
					      const char		*pat,
					      ...)
{
  char		buffer[1024 * 4];
  t_bunny_configuration *got;
  va_list	lst;
  bool		cmode;

  cmode = SmallConf::create_mode;
  SmallConf::create_mode = true;

  va_start(lst, pat);
  vsnprintf(&buffer[0], sizeof(buffer), pat, lst);
  if ((got = bunny_configuration_go_get_node(cnf, &buffer[0])) == NULL)
    {
      SmallConf::create_mode = cmode;
      return (false);
    }
  ((SmallConf*)got)->Bind(i);
  SmallConf::create_mode = cmode;
  return (true);
}

bool		bunny_configuration_bindf_bool(t_bunny_configuration	*cnf,
					       bool			*i,
					       const char		*pat,
					       ...)
{
  char		buffer[1024 * 4];
  t_bunny_configuration *got;
  va_list	lst;
  bool		cmode;

  cmode = SmallConf::create_mode;
  SmallConf::create_mode = true;

  va_start(lst, pat);
  vsnprintf(&buffer[0], sizeof(buffer), pat, lst);
  if ((got = bunny_configuration_go_get_node(cnf, &buffer[0])) == NULL)
    {
      SmallConf::create_mode = cmode;
      return (false);
    }
  ((SmallConf*)got)->Bind(i);
  SmallConf::create_mode = cmode;
  return (true);
}

bool		bunny_configuration_bindf_char(t_bunny_configuration	*cnf,
					       char			*i,
					       const char		*pat,
					       ...)
{
  char		buffer[1024 * 4];
  t_bunny_configuration *got;
  va_list	lst;
  bool		cmode;

  cmode = SmallConf::create_mode;
  SmallConf::create_mode = true;

  va_start(lst, pat);
  vsnprintf(&buffer[0], sizeof(buffer), pat, lst);
  if ((got = bunny_configuration_go_get_node(cnf, &buffer[0])) == NULL)
    {
      SmallConf::create_mode = cmode;
      return (false);
    }
  ((SmallConf*)got)->Bind(i);
  SmallConf::create_mode = cmode;
  return (true);
}

bool		bunny_configuration_bindf_double(t_bunny_configuration	*cnf,
						 double			*i,
						 const char		*pat,
						 ...)
{
  char		buffer[1024 * 4];
  t_bunny_configuration *got;
  va_list	lst;
  bool		cmode;

  cmode = SmallConf::create_mode;
  SmallConf::create_mode = true;

  va_start(lst, pat);
  vsnprintf(&buffer[0], sizeof(buffer), pat, lst);
  if ((got = bunny_configuration_go_get_node(cnf, &buffer[0])) == NULL)
    {
      SmallConf::create_mode = cmode;
      return (false);
    }
  ((SmallConf*)got)->Bind(i);
  SmallConf::create_mode = cmode;
  return (true);
}

bool		bunny_configuration_bindf_string(t_bunny_configuration	*cnf,
						 char			**i,
						 const char		*pat,
						 ...)
{
  char		buffer[1024 * 4];
  t_bunny_configuration *got;
  va_list	lst;
  bool		cmode;

  cmode = SmallConf::create_mode;
  SmallConf::create_mode = true;

  va_start(lst, pat);
  vsnprintf(&buffer[0], sizeof(buffer), pat, lst);
  if ((got = bunny_configuration_go_get_node(cnf, &buffer[0])) == NULL)
    {
      SmallConf::create_mode = cmode;
      return (false);
    }
  ((SmallConf*)got)->Bind(i);
  SmallConf::create_mode = cmode;
  return (true);
}

bool		bunny_configuration_unbindf(t_bunny_configuration	*cnf,
					    const char			*pat,
					    ...)
{
  char		buffer[1024 * 4];
  t_bunny_configuration *got;
  va_list	lst;
  bool		cmode;

  cmode = SmallConf::create_mode;
  SmallConf::create_mode = false;

  va_start(lst, pat);
  vsnprintf(&buffer[0], sizeof(buffer), pat, lst);
  if ((got = bunny_configuration_go_get_node(cnf, &buffer[0])) == NULL)
    {
      SmallConf::create_mode = cmode;
      return (false);
    }
  ((SmallConf*)got)->Unbind();
  SmallConf::create_mode = cmode;
  return (true);
}

