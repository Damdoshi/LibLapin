// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

t_bunny_configuration	*_bunny_configuration_go_get_node_va(const t_bunny_configuration *config,
							     size_t			nbr,
							     va_list			*lst);

#define			PATTERN		"%p config, %d value, %zu params, ... -> %s"

/**
 * @doc
 * @doc-symbol bunny_configuration_go_set_int_va
 * @doc-kind function
 * @doc-module configuration
 * @doc-order 540
 * @doc-since 0
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Walks counted address components and stores a integer scalar value.
 * @param config Configuration tree to modify.
 * @param val Value to store.
 * @param nbr Number of address components.
 * @param ... Address components, either strings or indexes.
 * @return-success Returns $Ctrue@ when the value is stored.
 * @return-failure Returns $Cfalse@ if the path cannot be resolved.
 * @log "configuration"
 *
 * @doc-lang fr
 * @brief Parcourt des composants d’adresse comptés et stocke une valeur scalaire integer.
 * @param config Configuration tree to modify.
 * @param val Value to store.
 * @param nbr Number of address components.
 * @param ... Address components, either strings or indexes.
 * @return-success Renvoie $Ctrue@ quand la valeur est stockée.
 * @return-failure Renvoie $Cfalse@ si le chemin ne peut pas être résolu.
 * @log "configuration"
 */
bool			bunny_configuration_go_set_int_va(t_bunny_configuration		*config,
							  int				val,
							  size_t			nbr,
							  ...)
{
  bool			cmode = SmallConf::create_mode;
  t_bunny_configuration	*cnf;
  va_list		lst;

  va_start(lst, nbr);
  SmallConf::create_mode = true;
  if ((cnf = _bunny_configuration_go_get_node_va(config, nbr, &lst)) == NULL)
    {
      SmallConf::create_mode = cmode;
      scream_error_if
	(return (false), bunny_errno, PATTERN, "configuration", config, val, nbr, "false");
    }
  va_end(lst);
  bunny_configuration_set_int(cnf, val);
  scream_log_if(PATTERN, "configuration", config, val, nbr, "true");
  SmallConf::create_mode = cmode;
  return (true);
}

#undef			PATTERN
#define			PATTERN		"%p config, %f value, %zu params, ... -> %s"

/**
 * @doc
 * @doc-symbol bunny_configuration_go_set_double_va
 * @doc-kind function
 * @doc-module configuration
 * @doc-order 530
 * @doc-since 0
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Walks counted address components and stores a double scalar value.
 * @param config Configuration tree to modify.
 * @param val Value to store.
 * @param nbr Number of address components.
 * @param ... Address components, either strings or indexes.
 * @return-success Returns $Ctrue@ when the value is stored.
 * @return-failure Returns $Cfalse@ if the path cannot be resolved.
 * @log "configuration"
 *
 * @doc-lang fr
 * @brief Parcourt des composants d’adresse comptés et stocke une valeur scalaire double.
 * @param config Configuration tree to modify.
 * @param val Value to store.
 * @param nbr Number of address components.
 * @param ... Address components, either strings or indexes.
 * @return-success Renvoie $Ctrue@ quand la valeur est stockée.
 * @return-failure Renvoie $Cfalse@ si le chemin ne peut pas être résolu.
 * @log "configuration"
 */
bool			bunny_configuration_go_set_double_va(t_bunny_configuration	*config,
							     double			val,
							     size_t			nbr,
							     ...)
{
  bool			cmode = SmallConf::create_mode;
  t_bunny_configuration	*cnf;
  va_list		lst;

  va_start(lst, nbr);
  SmallConf::create_mode = true;
  if ((cnf = _bunny_configuration_go_get_node_va(config, nbr, &lst)) == NULL)
    {
      SmallConf::create_mode = cmode;
      scream_error_if
	(return (false), bunny_errno, PATTERN, "configuration", config, val, nbr, "false");
    }
  va_end(lst);
  bunny_configuration_set_double(cnf, val);
  scream_log_if(PATTERN, "configuration", config, val, nbr, "true");
  SmallConf::create_mode = cmode;
  return (true);
}

#undef			PATTERN
#define			PATTERN		"%p config, %s value, %zu params, ... -> %s"

/**
 * @doc
 * @doc-symbol bunny_configuration_go_set_string_va
 * @doc-kind function
 * @doc-module configuration
 * @doc-order 520
 * @doc-since 0
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Walks counted address components and stores a string scalar value.
 * @param config Configuration tree to modify.
 * @param val Value to store.
 * @param nbr Number of address components.
 * @param ... Address components, either strings or indexes.
 * @return-success Returns $Ctrue@ when the value is stored.
 * @return-failure Returns $Cfalse@ if the path cannot be resolved.
 * @log "configuration"
 *
 * @doc-lang fr
 * @brief Parcourt des composants d’adresse comptés et stocke une valeur scalaire string.
 * @param config Configuration tree to modify.
 * @param val Value to store.
 * @param nbr Number of address components.
 * @param ... Address components, either strings or indexes.
 * @return-success Renvoie $Ctrue@ quand la valeur est stockée.
 * @return-failure Renvoie $Cfalse@ si le chemin ne peut pas être résolu.
 * @log "configuration"
 */
bool			bunny_configuration_go_set_string_va(t_bunny_configuration	*config,
							     const char			*val,
							     size_t			nbr,
							     ...)
{
  bool			cmode = SmallConf::create_mode;
  t_bunny_configuration	*cnf;
  va_list		lst;

  va_start(lst, nbr);
  SmallConf::create_mode = true;
  if ((cnf = _bunny_configuration_go_get_node_va(config, nbr, &lst)) == NULL)
    {
      SmallConf::create_mode = cmode;
      scream_error_if
	(return (false), bunny_errno, PATTERN, "configuration", config, val, nbr, "false");
    }
  va_end(lst);
  bunny_configuration_set_string(cnf, val);
  scream_log_if(PATTERN, "configuration", config, val, nbr, "true");
  SmallConf::create_mode = cmode;
  return (true);
}

t_bunny_configuration	*_bunny_configuration_go_get_node(const t_bunny_configuration	*config,
							  const char			*addr,
							  ssize_t			&i);

#undef			PATTERN
#define			PATTERN		"%p config, %s value, %s address -> %s"

/**
 * @doc
 * @doc-symbol bunny_configuration_go_set_string
 * @doc-kind function
 * @doc-module configuration
 * @doc-order 480
 * @doc-since 0
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Follows a C-like address and stores a string scalar value.
 * @param config Configuration tree to modify.
 * @param val Value to store.
 * @param addr C-like address to resolve.
 * @return-success Returns $Ctrue@ when the value is stored.
 * @return-failure Returns $Cfalse@ if the address cannot be resolved.
 * @log "configuration"
 *
 * @doc-lang fr
 * @brief Suit une adresse de style C et stocke une valeur scalaire string.
 * @param config Configuration tree to modify.
 * @param val Value to store.
 * @param addr C-like address to resolve.
 * @return-success Renvoie $Ctrue@ quand la valeur est stockée.
 * @return-failure Renvoie $Cfalse@ si l’adresse ne peut pas être résolue.
 * @log "configuration"
 */
bool			bunny_configuration_go_set_string(t_bunny_configuration		*config,
							  const char			*val,
							  const char			*addr)
{
  bool			cmode = SmallConf::create_mode;
  t_bunny_configuration	*cnf;

  SmallConf::create_mode = true;
  if ((cnf = bunny_configuration_go_get_node(config, addr)) == NULL)
    {
      SmallConf::create_mode = cmode;
      scream_error_if
	(return (false), bunny_errno, PATTERN, "configuration", config, val, addr, "false");
    }
  bunny_configuration_set_string(cnf, val);
  scream_log_if(PATTERN, "configuration", config, val, addr, "true");
  SmallConf::create_mode = cmode;
  return (true);
}

#undef			PATTERN
#define			PATTERN		"%p config, %f value, %s address -> %s"

/**
 * @doc
 * @doc-symbol bunny_configuration_go_set_double
 * @doc-kind function
 * @doc-module configuration
 * @doc-order 490
 * @doc-since 0
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Follows a C-like address and stores a double scalar value.
 * @param config Configuration tree to modify.
 * @param val Value to store.
 * @param addr C-like address to resolve.
 * @return-success Returns $Ctrue@ when the value is stored.
 * @return-failure Returns $Cfalse@ if the address cannot be resolved.
 * @log "configuration"
 *
 * @doc-lang fr
 * @brief Suit une adresse de style C et stocke une valeur scalaire double.
 * @param config Configuration tree to modify.
 * @param val Value to store.
 * @param addr C-like address to resolve.
 * @return-success Renvoie $Ctrue@ quand la valeur est stockée.
 * @return-failure Renvoie $Cfalse@ si l’adresse ne peut pas être résolue.
 * @log "configuration"
 */
bool			bunny_configuration_go_set_double(t_bunny_configuration		*config,
							  double			val,
							  const char			*addr)
{
  bool			cmode = SmallConf::create_mode;
  t_bunny_configuration	*cnf;

  SmallConf::create_mode = true;
  if ((cnf = bunny_configuration_go_get_node(config, addr)) == NULL)
    {
      SmallConf::create_mode = cmode;
      scream_error_if
	(return (false), bunny_errno, PATTERN, "configuration", config, val, addr, "false");
    }
  bunny_configuration_set_double(cnf, val);
  scream_log_if(PATTERN, "configuration", config, val, addr, "true");
  SmallConf::create_mode = cmode;
  return (true);
}

#undef			PATTERN
#define			PATTERN		"%p config, %d value, %s address -> %s"

/**
 * @doc
 * @doc-symbol bunny_configuration_go_set_int
 * @doc-kind function
 * @doc-module configuration
 * @doc-order 500
 * @doc-since 0
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Follows a C-like address and stores a integer scalar value.
 * @param config Configuration tree to modify.
 * @param val Value to store.
 * @param addr C-like address to resolve.
 * @return-success Returns $Ctrue@ when the value is stored.
 * @return-failure Returns $Cfalse@ if the address cannot be resolved.
 * @log "configuration"
 *
 * @doc-lang fr
 * @brief Suit une adresse de style C et stocke une valeur scalaire integer.
 * @param config Configuration tree to modify.
 * @param val Value to store.
 * @param addr C-like address to resolve.
 * @return-success Renvoie $Ctrue@ quand la valeur est stockée.
 * @return-failure Renvoie $Cfalse@ si l’adresse ne peut pas être résolue.
 * @log "configuration"
 */
bool			bunny_configuration_go_set_int(t_bunny_configuration		*config,
						       int				val,
						       const char			*addr)
{
  bool			cmode = SmallConf::create_mode;
  t_bunny_configuration	*cnf;

  SmallConf::create_mode = true;
  if ((cnf = bunny_configuration_go_get_node(config, addr)) == NULL)
    {
      SmallConf::create_mode = cmode;
      scream_error_if
	(return (false), bunny_errno, PATTERN, "configuration", config, val, addr, "false");
    }
  bunny_configuration_set_int(cnf, val);
  scream_log_if(PATTERN, "configuration", config, val, addr, "true");
  SmallConf::create_mode = cmode;
  return (true);
}


