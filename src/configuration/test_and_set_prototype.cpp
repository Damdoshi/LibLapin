// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2024
// Pentacle Technologie 2008-2024
// EFRITS 2022-2024
//
// Lapin library

#include		"lapin_private.h"

static SmallConf	*restore(int				cmode,
				 SmallConf			*ptr = NULL)
{
  SmallConf::create_mode = cmode;
  return (ptr);
}

SmallConf		*test_and_set_prototype(SmallConf	&function,
						SmallConf	*parameters)
{
  std::stringstream	varnodess;
  std::string		varnode;
  int			cmode = SmallConf::create_mode;

  if (!function.Access(".prototype"))
    return (restore(cmode, parameters));
  SmallConf::create_mode = true;
  varnodess << ".c" << function.NbrChild();
  varnode = varnodess.str();
  SmallConf		&vars = function[varnode];

  // On établi le noeud de toutes les variables définie dans le cadre de la fonction
  if (function.function)
    SmallConf::RecursiveAssign(vars, function.function->local_variables);
  if (parameters == NULL)
    return (restore(cmode, &vars));
  SmallConf		&gparameters = *parameters;
  SmallConf		&proto = function[".prototype"];
  size_t		i;
  
  // Méthode classique d'appel
  if (parameters->Size())
    {
      if (gparameters.Size() > proto.Size())
	scream_error_if
	  (return (restore(cmode)), BE_SYNTAX_ERROR,
	   "Too many parameters for function or expression %s, %d was expected,"
	   "%d given, on line %d",
	   "ressource,configuration,syntax",
	   function.name.c_str(), proto.Size(), gparameters.Size(), function.line
	   );
      for (i = 0; i < gparameters.Size(); ++i)
	SmallConf::RecursiveAssign(vars[proto[i].name], gparameters[i]);
      for (i = 0; i < proto.Size(); ++i)
	if (vars[proto[i].name].have_value)
	  continue ;
	else if (!proto[i].have_value)
	  scream_error_if
	    (return (restore(cmode)), BE_SYNTAX_ERROR,
	     "Missing parameters for function %s, "
	     "parameter %d (%s) on line %d",
	     "ressource,configuration,syntax",
	     function.name.c_str(), i, proto[i].name.c_str(), function.line
	     );
	else
	  SmallConf::RecursiveAssign(vars[proto[i].name], proto[i]);
      SmallConf::create_mode = cmode;
      return (&vars);
    }
  // Méthode d'appel par nom
  std::set<std::string> params; // Servira à vérifier les paramètres excedentaires

  for (auto it = gparameters.nodes.begin(); it != gparameters.nodes.end(); ++it)
    params.insert(it->first);
  for (i = 0; i < proto.Size(); ++i)
    if (gparameters.Access(proto[i].name))
      {
	params.erase(proto[i].name);
	SmallConf::RecursiveAssign(vars[proto[i].name], gparameters[proto[i].name]);
	continue ;
      }
    else if (!proto[i].have_value)
      scream_error_if
	(return (restore(cmode)), BE_SYNTAX_ERROR,
	 "Missing parameters for function %s, "
	 "parameter %d (%s) on line %d",
	 "ressource,configuration,syntax",
	 function.name.c_str(), i, proto[i].name.c_str(), function.line
	 );
    else
      SmallConf::RecursiveAssign(vars[proto[i].name], proto[i]);
  // On a passé des paramètres qu'avaient rien à foutre la?
  for (auto it = params.begin(); it != params.end(); ++it)
    scream_error_if
      (/* Rien, car l'erreur peut se produire plusieurs fois */, BE_SYNTAX_ERROR,
       "Unknown parameter %s sent to function %s on line %d",
       it->c_str(), function.name.c_str(), function.line
       );
  SmallConf::create_mode = cmode;
  if (params.size())
    return (NULL);
  return (&vars);
}

