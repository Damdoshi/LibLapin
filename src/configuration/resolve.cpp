// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include	"lapin_private.h"

bool		bunny_configuration_resolve(t_bunny_configuration	*par)
{
  SmallConf	&cnf = *(SmallConf*)par;
  bool		bad = false;

  if (par == NULL)
    return (false);
  SmallConf	*root = (SmallConf*)bunny_configuration_get_root(par);
  SmallConf	*parent = (SmallConf*)bunny_configuration_get_parent(par);
  const char	*str;
  int		integer;
  double	dbl;

  if (cnf.expression != NULL)
    {
      if (expr_compute(cnf, NULL, false, root, NULL, parent, NULL) == false)
	return (false);
      if (cnf.expression->val.last_type == SmallConf::INTEGER)
	{
	  if (cnf.GetInt(&integer, root, parent))
	    cnf.SetInt(integer);
	}
      else if (cnf.expression->val.last_type == SmallConf::DOUBLE)
	{
	  if (cnf.GetDouble(&dbl, root, parent))
	    cnf.SetDouble(dbl);
	}
      else
	{
	  if (cnf.GetString(&str, root, parent))
	    cnf.SetString(std::string(str));
	}
      delete cnf.expression;
      cnf.expression = NULL;
    }

  std::map<std::string, SmallConf*>::iterator itn;
  std::vector<SmallConf*>::iterator itv;

  for (itn = cnf.nodes.begin(); itn != cnf.nodes.end(); ++itn)
    if (bunny_configuration_resolve(itn->second) == false)
      bad = true;
  for (itv = cnf.array.begin(); itv != cnf.array.end(); ++itv)
    if (bunny_configuration_resolve(*itv) == false)
      bad = true;
  return (!bad);
}

