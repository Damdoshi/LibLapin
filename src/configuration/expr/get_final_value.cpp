// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
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
  t_bunny_configuration	*cnf;
  ssize_t		i;

  if (dry)
    return (&variable);
  if (variable.last_type != SmallConf::RAWSTRING)
    return (&variable);

  i = 0;
  if (artif && (cnf = _bunny_configuration_go_get_node
		(artif, variable.original_value.c_str(), i)))
    return (expr_get_variable(*(SmallConf*)cnf, dry, root, local, artif, params));

  i = 0;
  if (local && (cnf = _bunny_configuration_go_get_node
		(local, variable.original_value.c_str(), i)))
    return (expr_get_variable(*(SmallConf*)cnf, dry, root, local, artif, params));

  i = 0;
  if (params && (cnf = _bunny_configuration_go_get_node
		 (params, variable.original_value.c_str(), i)))
    return (expr_get_variable(*(SmallConf*)cnf, dry, root, local, artif, params));

  i = 0;
  if (root && (cnf = _bunny_configuration_go_get_node
	       (root, variable.original_value.c_str(), i)))
    return (expr_get_variable(*(SmallConf*)cnf, dry, root, local, artif, params));

  return (NULL);
}

