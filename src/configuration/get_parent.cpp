// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

/**
 * @doc
 * @doc-symbol bunny_configuration_get_parent
 * @doc-kind function
 * @doc-module configuration
 * @doc-order 160
 * @doc-since 0
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Returns the parent of a configuration node.
 * @param config Node to inspect.
 * @return-success Returns the parent node, or $CNULL@ for a root.
 * @log "configuration"
 *
 * @doc-lang fr
 * @brief Renvoie le parent d’un nœud de configuration.
 * @param config Node to inspect.
 * @return-success Renvoie le nœud parent, ou $CNULL@ pour une racine.
 * @log "configuration"
 */
t_bunny_configuration	*bunny_configuration_get_parent(t_bunny_configuration	*conf)
{
  SmallConf		*c = (SmallConf*)conf;
  t_bunny_configuration	*cnf = (t_bunny_configuration*)c->father;

  scream_log_if("%p -> %p", "configuration", conf, cnf);
  return (cnf);
}

