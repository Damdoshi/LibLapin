// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2024
//
// Lapin library

#include		"lapin_private.h"

bool			bunny_configuration_execute(t_bunny_configuration	*cnf,
						    bool			rec,
						    t_bunny_configuration	*par)
{
  bool			cmode = SmallConf::create_mode;
  bool			ret;
  SmallConf		*root = (SmallConf*)bunny_configuration_get_root(cnf);
  SmallConf		*artif = (SmallConf*)cnf;
  SmallConf		*param = (SmallConf*)par;

  SmallConf::create_mode = true;
  if (artif->expression)
    {
      ret = expr_compute(*artif, false, root, NULL, artif->father, param);
      SmallConf::create_mode = cmode;
      return (ret);
    }

  if (artif->function)
    {
      ret = dabsic_compute(*artif, false, root, artif->father, param);
      SmallConf::create_mode = cmode;
      return (ret);
    }

  if (rec)
    {
      std::map<std::string, SmallConf*>::iterator it;
      size_t		i;

      for (it = artif->Begin(); it != artif->End(); ++it)
	if (bunny_configuration_execute
	    ((t_bunny_configuration*)it->second, rec, par)
	    == false)
	  {
	    SmallConf::create_mode = cmode;
	    return (false);
	  }
      for (i = 0; i < artif->Size(); ++i)
	if (bunny_configuration_execute
	    ((t_bunny_configuration*)&(*artif)[i], rec, par)
	    == false)
	  {
	    SmallConf::create_mode = cmode;
	    return (false);
	  }
    }
  SmallConf::create_mode = cmode;
  return (true);
}

bool			bunny_configuration_executef_node(t_bunny_configuration		*conf,
							  t_bunny_configuration		**data,
							  bool				rec,
							  t_bunny_configuration		*params,
							  const char			*pat,
							  ...)
{
  t_bunny_configuration *got;
  char		buffer[1024 * 4];
  va_list	lst;
  bool		cmode;

  cmode = SmallConf::create_mode;
  SmallConf::create_mode = false;

  va_start(lst, pat);
  vsnprintf(&buffer[0], sizeof(buffer), pat, lst);
  if ((got = bunny_configuration_go_get_node(conf, &buffer[0])) == NULL)
    {
      SmallConf::create_mode = cmode;
      return (false);
    }
  SmallConf::create_mode = cmode;
  if (bunny_configuration_execute(got, rec, params) == false)
    return (false);
  if (data == NULL)
    return (true);
  SmallConf	*res = (SmallConf*)got;
  const char	*addr = res->original_value.c_str();

  return (bunny_configuration_getf_node(conf, data, "%s", addr));
}

bool			bunny_configuration_executef_string(t_bunny_configuration	*conf,
							    const char			**data,
							    bool			rec,
							    t_bunny_configuration	*params,
							    const char			*pat,
							    ...)
{
  t_bunny_configuration *got;
  char		buffer[1024 * 4];
  va_list	lst;
  bool		cmode;

  cmode = SmallConf::create_mode;
  SmallConf::create_mode = false;

  va_start(lst, pat);
  vsnprintf(&buffer[0], sizeof(buffer), pat, lst);
  if ((got = bunny_configuration_go_get_node(conf, &buffer[0])) == NULL)
    {
      SmallConf::create_mode = cmode;
      return (false);
    }
  SmallConf::create_mode = cmode;
  
  if (bunny_configuration_execute(got, rec, params) == false)
    return (false);
  SmallConf	*res = (SmallConf*)got;

  *data = res->original_value.c_str();
  return (true);
}

bool			bunny_configuration_executef_double(t_bunny_configuration	*conf,
							    double			*data,
							    bool			rec,
							    t_bunny_configuration	*params,
							    const char			*pat,
							    ...)
{
  t_bunny_configuration *got;
  char		buffer[1024 * 4];
  va_list	lst;
  bool		cmode;

  cmode = SmallConf::create_mode;
  SmallConf::create_mode = false;

  va_start(lst, pat);
  vsnprintf(&buffer[0], sizeof(buffer), pat, lst);
  if ((got = bunny_configuration_go_get_node(conf, &buffer[0])) == NULL)
    {
      SmallConf::create_mode = cmode;
      return (false);
    }
  SmallConf::create_mode = cmode;
  
  if (bunny_configuration_execute(got, rec, params) == false)
    return (false);
  SmallConf	*res = (SmallConf*)got;

  *data = res->converted;
  return (true);
}

bool			bunny_configuration_executef_int(t_bunny_configuration		*conf,
							 int				*data,
							 bool				rec,
							 t_bunny_configuration		*params,
							 const char			*pat,
							 ...)
{
  t_bunny_configuration *got;
  char		buffer[1024 * 4];
  va_list	lst;
  bool		cmode;

  cmode = SmallConf::create_mode;
  SmallConf::create_mode = false;

  va_start(lst, pat);
  vsnprintf(&buffer[0], sizeof(buffer), pat, lst);
  if ((got = bunny_configuration_go_get_node(conf, &buffer[0])) == NULL)
    {
      SmallConf::create_mode = cmode;
      return (false);
    }
  SmallConf::create_mode = cmode;
  
  if (bunny_configuration_execute(got, rec, params) == false)
    return (false);
  SmallConf	*res = (SmallConf*)got;

  *data = res->converted_2 = res->converted;
  return (true);
}

bool			bunny_configuration_executef_bool(t_bunny_configuration		*conf,
							  bool				*data,
							  bool				rec,
							  t_bunny_configuration		*params,
							  const char			*pat,
							  ...)
{
  t_bunny_configuration *got;
  char		buffer[1024 * 4];
  va_list	lst;
  bool		cmode;

  cmode = SmallConf::create_mode;
  SmallConf::create_mode = false;

  va_start(lst, pat);
  vsnprintf(&buffer[0], sizeof(buffer), pat, lst);
  if ((got = bunny_configuration_go_get_node(conf, &buffer[0])) == NULL)
    {
      SmallConf::create_mode = cmode;
      return (false);
    }
  SmallConf::create_mode = cmode;
  
  if (bunny_configuration_execute(got, rec, params) == false)
    return (false);
  SmallConf	*res = (SmallConf*)got;

  *data = !!(res->converted_2 = res->converted);
  return (true);
}

