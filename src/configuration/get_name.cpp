// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

#define			PATTERN		"%p -> %s"

/**
 * @doc
 * @doc-symbol bunny_configuration_get_name
 * @doc-kind function
 * @doc-module configuration
 * @doc-order 180
 * @doc-since 0
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Returns the local name of a configuration node.
 * @param config Node to inspect.
 * @return-success Returns a valid string.
 * @log "configuration"
 *
 * @doc-lang fr
 * @brief Renvoie le nom local d’un nœud de configuration.
 * @param config Node to inspect.
 * @return-success Renvoie une chaîne valide.
 * @log "configuration"
 */
const char		*bunny_configuration_get_name(const t_bunny_configuration	*config)
{
  SmallConf		*conf = (SmallConf*)config;

  if (conf->name == "@")
    {
      scream_log_if(PATTERN, "configuration", config, "");
      return ("");
    }
  scream_log_if(PATTERN, "configuration", config, conf->name.c_str());
  return (conf->name.c_str());
}

