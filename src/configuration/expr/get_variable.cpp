// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"


SmallConf		*expr_get_variable(SmallConf		&var,
					   bool			dry,
					   SmallConf		*root,
					   SmallConf		*local,
					   SmallConf		*artif,
					   SmallConf		*variables)
{
  const char		*name;
  int			cmode;
  t_bunny_configuration	*cnf;
  ssize_t		i;

  // Si c'était un bloc [Text, alors on rassemble tout dans une même chaine de caractères
  // Il pourrait être interessant de permettre une option pour l'éviter
  if (var.was_text_block)
    if (_bunny_resolve_text_block(var, root, local, artif, variables) == false)
      return (NULL);

  if (var.expression && var.expression->optor_family != -1)
    {
      if (bunny_configuration_resolve(var) == false)
	return (NULL);
    }

  if (var.symbol == false)
    return (&var);

  cmode = SmallConf::create_mode;
  SmallConf::create_mode = false;

  if (var.name != "")
    name = var.name.c_str();
  else
    name = var.original_value.c_str();

  t_bunny_configuration	*contexts[4];
  int nbrctx = 0;

  if (local) contexts[nbrctx++] = local; // D'abord les vars locales
  if (variables) contexts[nbrctx++] = variables; // Puis les paramètres de la fonction
  if (artif) contexts[nbrctx++] = artif; // Puis le noeud contennat la fonction/le contexte artificiel
  if (root) contexts[nbrctx++] = root; // La racine

  i = 0;
  if (nbrctx && (cnf = bunny_configuration_resolve_address(contexts, nbrctx, name, i)))
    {
      SmallConf::create_mode = cmode;
      return (expr_get_variable(*(SmallConf*)cnf, dry, root, local, artif, variables));
    }

  SmallConf::create_mode = cmode;
  if (dry)
    return (&var);
  return (NULL);
}

