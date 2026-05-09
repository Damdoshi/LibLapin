// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

/**
 * @doc
 * @doc-symbol bunny_configuration_set_string
 * @doc-kind function
 * @doc-module configuration
 * @doc-order 440
 * @doc-since 0
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Stores a string scalar value in a configuration node.
 * @param config Node to modify.
 * @param str Value to store.
 * @return-success The node value is replaced.
 * @log "configuration"
 *
 * @doc-lang fr
 * @brief Stocke une valeur scalaire string dans un nœud de configuration.
 * @param config Node to modify.
 * @param str Value to store.
 * @return-success La valeur du nœud est remplacée.
 * @log "configuration"
 */
void			bunny_configuration_set_string(t_bunny_configuration	*config,
						       const char		*val)
{
  SmallConf		*conf = (SmallConf*)config;

  if (val == NULL)
    conf->SetString(std::string());
  else
    conf->SetString(std::string(val));
  if (conf->expression)
    {
      delete conf->expression;
      conf->expression = NULL;
    }
  scream_log_if("%p config, %s value", "configuration", config, val);
}

/**
 * @doc
 * @doc-symbol bunny_configuration_set_int
 * @doc-kind function
 * @doc-module configuration
 * @doc-order 460
 * @doc-since 0
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Stores a integer scalar value in a configuration node.
 * @param config Node to modify.
 * @param val Value to store.
 * @return-success The node value is replaced.
 * @log "configuration"
 *
 * @doc-lang fr
 * @brief Stocke une valeur scalaire integer dans un nœud de configuration.
 * @param config Node to modify.
 * @param val Value to store.
 * @return-success La valeur du nœud est remplacée.
 * @log "configuration"
 */
void			bunny_configuration_set_int(t_bunny_configuration	*config,
						    int				val)
{
  SmallConf		*conf = (SmallConf*)config;

  conf->SetInt(val);
  if (conf->expression)
    {
      delete conf->expression;
      conf->expression = NULL;
    }
  scream_log_if("%p config, %d value", "configuration", config, val);
}

/**
 * @doc
 * @doc-symbol bunny_configuration_set_double
 * @doc-kind function
 * @doc-module configuration
 * @doc-order 450
 * @doc-since 0
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Stores a double scalar value in a configuration node.
 * @param config Node to modify.
 * @param val Value to store.
 * @return-success The node value is replaced.
 * @log "configuration"
 *
 * @doc-lang fr
 * @brief Stocke une valeur scalaire double dans un nœud de configuration.
 * @param config Node to modify.
 * @param val Value to store.
 * @return-success La valeur du nœud est remplacée.
 * @log "configuration"
 */
void			bunny_configuration_set_double(t_bunny_configuration	*config,
						       double			val)
{
  SmallConf		*conf = (SmallConf*)config;

  conf->SetDouble(val);
  if (conf->expression)
    {
      delete conf->expression;
      conf->expression = NULL;
    }
  scream_log_if("%p config, %f value", "configuration", config, val);
}

