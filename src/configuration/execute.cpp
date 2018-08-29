// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

bool			bunny_configuration_execute(t_bunny_configuration	*cnf,
						    bool			rec,
						    t_bunny_configuration	*par)
{
  bool			ret;
  SmallConf		*root = (SmallConf*)cnf;
  SmallConf		*artif = (SmallConf*)cnf;
  SmallConf		*param = (SmallConf*)par;
  SmallConf		*proto;

  while (root->father)
    root = root->father;
  if (artif->Access(".parameters") == false)
    proto = NULL;
  else
    proto = &(*artif)[".parameters"];

  if (artif->expression)
    {
      ret = expr_compute(*artif, NULL, false, root, NULL, artif->father, param);
      return (ret);
    }

  if (artif->function)
    {
      ret = dabsic_compute(*artif, proto, false, root, artif->father, param);
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
	  return (false);
      for (i = 0; i < artif->Size(); ++i)
	if (bunny_configuration_execute
	    ((t_bunny_configuration*)&(*artif)[i], rec, par)
	    == false)
	  return (false);
    }
  return (true);
}

bool			bunny_configuration_executef(t_bunny_configuration		*conf,
						     bool				rec,
						     t_bunny_configuration		*params,
						     const char				*pat,
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
  return (bunny_configuration_execute(got, rec, params));
}

