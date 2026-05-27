// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include	"lapin_private.h"

/**
 * @doc
 * @doc-symbol bunny_configuration_bindf_int
 * @doc-kind function
 * @doc-module configuration
 * @doc-order 691
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Binds a integer C variable to a formatted configuration field.
 * @param c Configuration tree to modify.
 * @param i Address of the C variable to bind.
 * @param pat Printf-like address pattern.
 * @param ... Values consumed by $Spat@.
 * @return-success Returns $Ctrue@ when binding succeeds.
 * @return-failure Returns $Cfalse@ on error.
 * @log "configuration"
 *
 * @doc-lang fr
 * @brief Lie une variable C integer à un champ de configuration formaté.
 * @param c Configuration tree to modify.
 * @param i Address of the C variable to bind.
 * @param pat Printf-like address pattern.
 * @param ... Values consumed by $Spat@.
 * @return-success Renvoie $Ctrue@ quand le binding réussit.
 * @return-failure Renvoie $Cfalse@ en cas d’erreur.
 * @log "configuration"
 */
bool		bunny_configuration_bindf_int(t_bunny_configuration	*cnf,
					      int			*i,
					      const char		*pat,
					      ...)
{
  char		buffer[1024 * 4];
  t_bunny_configuration *got;
  va_list	lst;
  bool		cmode;

  cmode = SmallConf::create_mode;
  SmallConf::create_mode = true;

  va_start(lst, pat);
  vsnprintf(&buffer[0], sizeof(buffer), pat, lst);
  if ((got = bunny_configuration_go_get_node(cnf, &buffer[0])) == NULL)
    {
      SmallConf::create_mode = cmode;
      return (false);
    }
  ((SmallConf*)got)->Bind(i);
  SmallConf::create_mode = cmode;
  return (true);
}

/**
 * @doc
 * @doc-symbol bunny_configuration_bindf_bool
 * @doc-kind function
 * @doc-module configuration
 * @doc-order 692
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Binds a boolean C variable to a formatted configuration field.
 * @param c Configuration tree to modify.
 * @param i Address of the C variable to bind.
 * @param pat Printf-like address pattern.
 * @param ... Values consumed by $Spat@.
 * @return-success Returns $Ctrue@ when binding succeeds.
 * @return-failure Returns $Cfalse@ on error.
 * @log "configuration"
 *
 * @doc-lang fr
 * @brief Lie une variable C boolean à un champ de configuration formaté.
 * @param c Configuration tree to modify.
 * @param i Address of the C variable to bind.
 * @param pat Printf-like address pattern.
 * @param ... Values consumed by $Spat@.
 * @return-success Renvoie $Ctrue@ quand le binding réussit.
 * @return-failure Renvoie $Cfalse@ en cas d’erreur.
 * @log "configuration"
 */
bool		bunny_configuration_bindf_bool(t_bunny_configuration	*cnf,
					       bool			*i,
					       const char		*pat,
					       ...)
{
  char		buffer[1024 * 4];
  t_bunny_configuration *got;
  va_list	lst;
  bool		cmode;

  cmode = SmallConf::create_mode;
  SmallConf::create_mode = true;

  va_start(lst, pat);
  vsnprintf(&buffer[0], sizeof(buffer), pat, lst);
  if ((got = bunny_configuration_go_get_node(cnf, &buffer[0])) == NULL)
    {
      SmallConf::create_mode = cmode;
      return (false);
    }
  ((SmallConf*)got)->Bind(i);
  SmallConf::create_mode = cmode;
  return (true);
}

/**
 * @doc
 * @doc-symbol bunny_configuration_bindf_char
 * @doc-kind function
 * @doc-module configuration
 * @doc-order 693
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Binds a byte C variable to a formatted configuration field.
 * @param c Configuration tree to modify.
 * @param i Address of the C variable to bind.
 * @param pat Printf-like address pattern.
 * @param ... Values consumed by $Spat@.
 * @return-success Returns $Ctrue@ when binding succeeds.
 * @return-failure Returns $Cfalse@ on error.
 * @log "configuration"
 *
 * @doc-lang fr
 * @brief Lie une variable C byte à un champ de configuration formaté.
 * @param c Configuration tree to modify.
 * @param i Address of the C variable to bind.
 * @param pat Printf-like address pattern.
 * @param ... Values consumed by $Spat@.
 * @return-success Renvoie $Ctrue@ quand le binding réussit.
 * @return-failure Renvoie $Cfalse@ en cas d’erreur.
 * @log "configuration"
 */
bool		bunny_configuration_bindf_char(t_bunny_configuration	*cnf,
					       char			*i,
					       const char		*pat,
					       ...)
{
  char		buffer[1024 * 4];
  t_bunny_configuration *got;
  va_list	lst;
  bool		cmode;

  cmode = SmallConf::create_mode;
  SmallConf::create_mode = true;

  va_start(lst, pat);
  vsnprintf(&buffer[0], sizeof(buffer), pat, lst);
  if ((got = bunny_configuration_go_get_node(cnf, &buffer[0])) == NULL)
    {
      SmallConf::create_mode = cmode;
      return (false);
    }
  ((SmallConf*)got)->Bind(i);
  SmallConf::create_mode = cmode;
  return (true);
}

/**
 * @doc
 * @doc-symbol bunny_configuration_bindf_double
 * @doc-kind function
 * @doc-module configuration
 * @doc-order 694
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Binds a double C variable to a formatted configuration field.
 * @param c Configuration tree to modify.
 * @param i Address of the C variable to bind.
 * @param pat Printf-like address pattern.
 * @param ... Values consumed by $Spat@.
 * @return-success Returns $Ctrue@ when binding succeeds.
 * @return-failure Returns $Cfalse@ on error.
 * @log "configuration"
 *
 * @doc-lang fr
 * @brief Lie une variable C double à un champ de configuration formaté.
 * @param c Configuration tree to modify.
 * @param i Address of the C variable to bind.
 * @param pat Printf-like address pattern.
 * @param ... Values consumed by $Spat@.
 * @return-success Renvoie $Ctrue@ quand le binding réussit.
 * @return-failure Renvoie $Cfalse@ en cas d’erreur.
 * @log "configuration"
 */
bool		bunny_configuration_bindf_double(t_bunny_configuration	*cnf,
						 double			*i,
						 const char		*pat,
						 ...)
{
  char		buffer[1024 * 4];
  t_bunny_configuration *got;
  va_list	lst;
  bool		cmode;

  cmode = SmallConf::create_mode;
  SmallConf::create_mode = true;

  va_start(lst, pat);
  vsnprintf(&buffer[0], sizeof(buffer), pat, lst);
  if ((got = bunny_configuration_go_get_node(cnf, &buffer[0])) == NULL)
    {
      SmallConf::create_mode = cmode;
      return (false);
    }
  ((SmallConf*)got)->Bind(i);
  SmallConf::create_mode = cmode;
  return (true);
}

/**
 * @doc
 * @doc-symbol bunny_configuration_bindf_string
 * @doc-kind function
 * @doc-module configuration
 * @doc-order 695
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Binds a string pointer C variable to a formatted configuration field.
 * @param c Configuration tree to modify.
 * @param i Address of the C variable to bind.
 * @param pat Printf-like address pattern.
 * @param ... Values consumed by $Spat@.
 * @return-success Returns $Ctrue@ when binding succeeds.
 * @return-failure Returns $Cfalse@ on error.
 * @log "configuration"
 *
 * @doc-lang fr
 * @brief Lie une variable C string pointer à un champ de configuration formaté.
 * @param c Configuration tree to modify.
 * @param i Address of the C variable to bind.
 * @param pat Printf-like address pattern.
 * @param ... Values consumed by $Spat@.
 * @return-success Renvoie $Ctrue@ quand le binding réussit.
 * @return-failure Renvoie $Cfalse@ en cas d’erreur.
 * @log "configuration"
 */
bool		bunny_configuration_bindf_string(t_bunny_configuration	*cnf,
						 char			**i,
						 const char		*pat,
						 ...)
{
  char		buffer[1024 * 4];
  t_bunny_configuration *got;
  va_list	lst;
  bool		cmode;

  cmode = SmallConf::create_mode;
  SmallConf::create_mode = true;

  va_start(lst, pat);
  vsnprintf(&buffer[0], sizeof(buffer), pat, lst);
  if ((got = bunny_configuration_go_get_node(cnf, &buffer[0])) == NULL)
    {
      SmallConf::create_mode = cmode;
      return (false);
    }
  ((SmallConf*)got)->Bind(i);
  SmallConf::create_mode = cmode;
  return (true);
}

/**
 * @doc
 * @doc-symbol bunny_configuration_unbindf
 * @doc-kind function
 * @doc-module configuration
 * @doc-order 696
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Removes a binding selected by a formatted configuration path.
 * @param c Configuration tree to modify.
 * @param fmt Printf-like address pattern.
 * @param ... Values consumed by $Sfmt@.
 * @return-success Returns $Ctrue@ when unbinding succeeds.
 * @return-failure Returns $Cfalse@ on error.
 * @log "configuration"
 *
 * @doc-lang fr
 * @brief Retire un binding sélectionné par un chemin de configuration formaté.
 * @param c Configuration tree to modify.
 * @param fmt Printf-like address pattern.
 * @param ... Values consumed by $Sfmt@.
 * @return-success Renvoie $Ctrue@ quand l’unbinding réussit.
 * @return-failure Renvoie $Cfalse@ en cas d’erreur.
 * @log "configuration"
 */
bool		bunny_configuration_unbindf(t_bunny_configuration	*cnf,
					    const char			*pat,
					    ...)
{
  char		buffer[1024 * 4];
  t_bunny_configuration *got;
  va_list	lst;
  bool		cmode;

  cmode = SmallConf::create_mode;
  SmallConf::create_mode = false;

  va_start(lst, pat);
  vsnprintf(&buffer[0], sizeof(buffer), pat, lst);
  if ((got = bunny_configuration_go_get_node(cnf, &buffer[0])) == NULL)
    {
      SmallConf::create_mode = cmode;
      return (false);
    }
  ((SmallConf*)got)->Unbind();
  SmallConf::create_mode = cmode;
  return (true);
}

