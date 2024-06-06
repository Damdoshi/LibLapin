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

  // Si il y a une expression à résoudre et qui ne prend aucun paramètres...
  if (cnf.expression != NULL && cnf.nodes.find(".parameters") == cnf.nodes.end())
    {
      if (expr_compute(cnf, false, root, &cnf, parent, NULL) == false)
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
      else if (cnf.expression->val.last_type == SmallConf::STRING)
	{
	  if (cnf.GetString(&str, root, parent))
	    cnf.SetString(std::string(str));
	}
      else
	{
	  if (cnf.GetString(&str, root, parent))
	    cnf.SetString(std::string(str, true));
	  // Ceci indique qu'on a un pointeur, en fait, car une RAWSTRING
	  // est une sorte de pointeur.
	  // Il faudrait formaliser plus fortement cet aspect, car il est crucial.
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

  // Si c'était un bloc [Text, alors on rassemble tout dans une même chaine de caractères
  // Il pourrait être interessant de permettre une option pour l'éviter
  if (cnf.was_text_block)
    if (_bunny_resolve_text_block(cnf, root, parent, &cnf, NULL) == false)
      return (NULL);
  return (!bad);
}

