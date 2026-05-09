// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2024
//
// Lapin library

#include		"lapin_private.h"

/**
 * @doc
 * @doc-symbol bunny_configuration_execute
 * @doc-kind function
 * @doc-module configuration
 * @doc-order 550
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Executes Dabsic scripts and expressions stored in a configuration node.
 * @param config Configuration node to execute.
 * @param parameters Optional parameter configuration.
 * @param art Optional artificial context.
 * @return-success Returns $Ctrue@ when execution succeeds.
 * @return-failure Returns $Cfalse@ on execution error.
 * @log "configuration"
 *
 * @doc-lang fr
 * @brief Exécute les scripts et expressions Dabsic stockés dans un nœud de configuration.
 * @param config Configuration node to execute.
 * @param parameters Optional parameter configuration.
 * @param art Optional artificial context.
 * @return-success Renvoie $Ctrue@ quand l’exécution réussit.
 * @return-failure Renvoie $Cfalse@ en cas d’erreur d’exécution.
 * @log "configuration"
 */
bool			bunny_configuration_execute(t_bunny_configuration	*cnf,
						    t_bunny_configuration	*par,
						    t_bunny_configuration	*art)
{
  bool			cmode = SmallConf::create_mode;
  bool			ret;
  SmallConf		*local = (SmallConf*)cnf;
  SmallConf		*root = (SmallConf*)bunny_configuration_get_root(cnf);
  SmallConf		*artif = (SmallConf*)(art ? ((SmallConf*)art)->father : local->father);
  SmallConf		*param = (SmallConf*)par;

  SmallConf::create_mode = true;
  // Si on a une fonction rattachée, on a QUE ca
  if (local->function)
    {
      ret = dabsic_compute(*local, false, root, artif, param);
      SmallConf::create_mode = cmode;
      return (ret);
    }

  // Sinon on peut avoir une expression dans la valeur
  if (local->expression)
    {
      ret = expr_compute(*local, false, root, local, artif, param);
      SmallConf::create_mode = cmode;
      // Une fois le calcul effectué, on dégage.
      delete artif->expression;
      artif->expression = NULL;
      if (!ret)
	return (ret);
    }

  // On peut même avoir tout plein de noeuds en dessous qui sont aussi
  // des prototypes (mais ne sont pas des fonctions) grace a dabsic_functionize
  std::map<std::string, SmallConf*>::iterator it;
  size_t		i;

  for (it = local->Begin(); it != local->End(); ++it)
    if (bunny_configuration_execute
	((t_bunny_configuration*)it->second, par, art)
	== false)
      {
	SmallConf::create_mode = cmode;
	return (false);
      }
  for (i = 0; i < local->Size(); ++i)
    if (bunny_configuration_execute
	((t_bunny_configuration*)&(*local)[i], par, art)
	== false)
      {
	SmallConf::create_mode = cmode;
	return (false);
      }
  SmallConf::create_mode = cmode;
  return (true);
}

/**
 * @doc
 * @doc-symbol bunny_configuration_executef_node
 * @doc-kind function
 * @doc-module configuration
 * @doc-order 661
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Executes a selected Dabsic node and reads its node result.
 * @param config Configuration tree to inspect.
 * @param data Typed output storage.
 * @param parameters Optional execution parameters.
 * @param pattern Printf-like address pattern.
 * @param ... Values consumed by $Spattern@.
 * @return-success Returns $Ctrue@ on success.
 * @return-failure Returns $Cfalse@ on error.
 * @log "configuration"
 *
 * @doc-lang fr
 * @brief Exécute un nœud Dabsic sélectionné et lit son résultat node.
 * @param config Configuration tree to inspect.
 * @param data Typed output storage.
 * @param parameters Optional execution parameters.
 * @param pattern Printf-like address pattern.
 * @param ... Values consumed by $Spattern@.
 * @return-success Renvoie $Ctrue@ en cas de succès.
 * @return-failure Renvoie $Cfalse@ en cas d’erreur.
 * @log "configuration"
 */
bool			bunny_configuration_executef_node(t_bunny_configuration		*conf,
							  t_bunny_configuration		**data,
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
  if (bunny_configuration_execute(got, params, NULL) == false)
    return (false);
  if (data == NULL)
    return (true);
  SmallConf	*res = (SmallConf*)got;
  const char	*addr = res->original_value.c_str();

  return (bunny_configuration_getf_node(conf, data, "%s", addr));
}

/**
 * @doc
 * @doc-symbol bunny_configuration_executef_string
 * @doc-kind function
 * @doc-module configuration
 * @doc-order 662
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Executes a selected Dabsic node and reads its string result.
 * @param config Configuration tree to inspect.
 * @param data Typed output storage.
 * @param parameters Optional execution parameters.
 * @param pattern Printf-like address pattern.
 * @param ... Values consumed by $Spattern@.
 * @return-success Returns $Ctrue@ on success.
 * @return-failure Returns $Cfalse@ on error.
 * @log "configuration"
 *
 * @doc-lang fr
 * @brief Exécute un nœud Dabsic sélectionné et lit son résultat string.
 * @param config Configuration tree to inspect.
 * @param data Typed output storage.
 * @param parameters Optional execution parameters.
 * @param pattern Printf-like address pattern.
 * @param ... Values consumed by $Spattern@.
 * @return-success Renvoie $Ctrue@ en cas de succès.
 * @return-failure Renvoie $Cfalse@ en cas d’erreur.
 * @log "configuration"
 */
bool			bunny_configuration_executef_string(t_bunny_configuration	*conf,
							    const char			**data,
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
  
  if (bunny_configuration_execute(got, params, NULL) == false)
    return (false);
  SmallConf	*res = (SmallConf*)got;

  *data = res->original_value.c_str();
  return (true);
}

/**
 * @doc
 * @doc-symbol bunny_configuration_executef_double
 * @doc-kind function
 * @doc-module configuration
 * @doc-order 663
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Executes a selected Dabsic node and reads its double result.
 * @param config Configuration tree to inspect.
 * @param data Typed output storage.
 * @param parameters Optional execution parameters.
 * @param pattern Printf-like address pattern.
 * @param ... Values consumed by $Spattern@.
 * @return-success Returns $Ctrue@ on success.
 * @return-failure Returns $Cfalse@ on error.
 * @log "configuration"
 *
 * @doc-lang fr
 * @brief Exécute un nœud Dabsic sélectionné et lit son résultat double.
 * @param config Configuration tree to inspect.
 * @param data Typed output storage.
 * @param parameters Optional execution parameters.
 * @param pattern Printf-like address pattern.
 * @param ... Values consumed by $Spattern@.
 * @return-success Renvoie $Ctrue@ en cas de succès.
 * @return-failure Renvoie $Cfalse@ en cas d’erreur.
 * @log "configuration"
 */
bool			bunny_configuration_executef_double(t_bunny_configuration	*conf,
							    double			*data,
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
  
  if (bunny_configuration_execute(got, params, NULL) == false)
    return (false);
  SmallConf	*res = (SmallConf*)got;

  *data = res->converted;
  return (true);
}

/**
 * @doc
 * @doc-symbol bunny_configuration_executef_int
 * @doc-kind function
 * @doc-module configuration
 * @doc-order 664
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Executes a selected Dabsic node and reads its integer result.
 * @param config Configuration tree to inspect.
 * @param data Typed output storage.
 * @param parameters Optional execution parameters.
 * @param pattern Printf-like address pattern.
 * @param ... Values consumed by $Spattern@.
 * @return-success Returns $Ctrue@ on success.
 * @return-failure Returns $Cfalse@ on error.
 * @log "configuration"
 *
 * @doc-lang fr
 * @brief Exécute un nœud Dabsic sélectionné et lit son résultat integer.
 * @param config Configuration tree to inspect.
 * @param data Typed output storage.
 * @param parameters Optional execution parameters.
 * @param pattern Printf-like address pattern.
 * @param ... Values consumed by $Spattern@.
 * @return-success Renvoie $Ctrue@ en cas de succès.
 * @return-failure Renvoie $Cfalse@ en cas d’erreur.
 * @log "configuration"
 */
bool			bunny_configuration_executef_int(t_bunny_configuration		*conf,
							 int				*data,
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
  
  if (bunny_configuration_execute(got, params, NULL) == false)
    return (false);
  SmallConf	*res = (SmallConf*)got;

  *data = res->converted_2 = res->converted;
  return (true);
}

/**
 * @doc
 * @doc-symbol bunny_configuration_executef_bool
 * @doc-kind function
 * @doc-module configuration
 * @doc-order 665
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Executes a selected Dabsic node and reads its boolean result.
 * @param config Configuration tree to inspect.
 * @param data Typed output storage.
 * @param parameters Optional execution parameters.
 * @param pattern Printf-like address pattern.
 * @param ... Values consumed by $Spattern@.
 * @return-success Returns $Ctrue@ on success.
 * @return-failure Returns $Cfalse@ on error.
 * @log "configuration"
 *
 * @doc-lang fr
 * @brief Exécute un nœud Dabsic sélectionné et lit son résultat boolean.
 * @param config Configuration tree to inspect.
 * @param data Typed output storage.
 * @param parameters Optional execution parameters.
 * @param pattern Printf-like address pattern.
 * @param ... Values consumed by $Spattern@.
 * @return-success Renvoie $Ctrue@ en cas de succès.
 * @return-failure Renvoie $Cfalse@ en cas d’erreur.
 * @log "configuration"
 */
bool			bunny_configuration_executef_bool(t_bunny_configuration		*conf,
							  bool				*data,
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
  
  if (bunny_configuration_execute(got, params, NULL) == false)
    return (false);
  SmallConf	*res = (SmallConf*)got;

  *data = !!(res->converted_2 = res->converted);
  return (true);
}

