// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		"lapin_private.h"

bool			bunny_configuration_execute(t_bunny_configuration	*cnf,
						    bool			rec,
						    t_bunny_configuration	*par)
{
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
    return (expr_compute
	    (*artif,
	     false,
	     root,
	     NULL,
	     artif,
	     param
	     ));

  if (artif->function)
    return (dabsic_compute
	    (*artif,
	     proto,
	     false,
	     root,
	     artif,
	     param
	     ));

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

