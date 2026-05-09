// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		<sstream>
#include		"lapin_private.h"

/**
 * @doc
 * @doc-symbol bunny_configuration_get_nbr_case
 * @doc-kind function
 * @doc-module configuration
 * @doc-order 240
 * @doc-since 0
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Counts indexed cases in a configuration node.
 * @param config Node to inspect.
 * @return-success Returns the number of cases.
 * @log "configuration"
 *
 * @doc-lang fr
 * @brief Compte les cases indexées d’un nœud de configuration.
 * @param config Node to inspect.
 * @return-success Renvoie le nombre de cases.
 * @log "configuration"
 */
size_t			bunny_configuration_get_nbr_case(const t_bunny_configuration	*_conf)
{
  SmallConf		*conf = (SmallConf*)_conf;

  scream_log_if("%p -> %zu", "configuration", conf, conf->Size());
  return (conf->Size());
}

