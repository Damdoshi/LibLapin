// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"


SmallConf		*expr_get_variable(SmallConf		&variable,
					   bool			dry,
					   SmallConf		*root,
					   SmallConf		*local,
					   SmallConf		*artif,
					   SmallConf		*params)
{
  const char		*name;
  int			cmode;
  t_bunny_configuration	*cnf;
  ssize_t		i;

  // Si c'était un bloc [Text, alors on rassemble tout dans une même chaine de caractères
  // Il pourrait être interessant de permettre une option pour l'éviter
  if (variable.was_text_block)
    if (_bunny_resolve_text_block(variable, root, local, artif, params) == false)
      return (NULL);

  if (variable.expression && variable.expression->optor_family != -1)
    {
      if (bunny_configuration_resolve(variable) == false)
	return (NULL);
    }

  if (variable.symbol == false)
    return (&variable);

  cmode = SmallConf::create_mode;
  SmallConf::create_mode = false;

  if (variable.name != "")
    name = variable.name.c_str();
  else
    name = variable.original_value.c_str();

  i = 0;
  if (artif && (cnf = _bunny_configuration_go_get_node(artif, name, i)))
    {
      SmallConf::create_mode = cmode;
      return (expr_get_variable(*(SmallConf*)cnf, dry, root, local, artif, params));
    }

  i = 0;
  if (local && (cnf = _bunny_configuration_go_get_node(local, name, i)))
    {
      SmallConf::create_mode = cmode;
      return (expr_get_variable(*(SmallConf*)cnf, dry, root, local, artif, params));
    }

  i = 0;
  if (params && (cnf = _bunny_configuration_go_get_node(params, name, i)))
    {
      SmallConf::create_mode = cmode;
      return (expr_get_variable(*(SmallConf*)cnf, dry, root, local, artif, params));
    }

  i = 0;
  if (root && (cnf = _bunny_configuration_go_get_node(root, name, i)))
    {
      SmallConf::create_mode = cmode;
      return (expr_get_variable(*(SmallConf*)cnf, dry, root, local, artif, params));
    }

  SmallConf::create_mode = cmode;
  if (dry)
    return (&variable);
  return (NULL);
}

