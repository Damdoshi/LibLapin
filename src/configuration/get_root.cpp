// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

#define			PATTERN		"%p -> %p"

/**
 * @doc
 * @doc-symbol bunny_configuration_get_root
 * @doc-kind function
 * @doc-module configuration
 * @doc-order 170
 * @doc-since 0
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Returns the root of a configuration tree.
 * @param config Node from which to climb.
 * @return-success Returns the root node.
 * @return-failure Returns $CNULL@ if $Sconfig@ is $CNULL@.
 * @log "configuration"
 *
 * @doc-lang fr
 * @brief Renvoie la racine d’un arbre de configuration.
 * @param config Node from which to climb.
 * @return-success Renvoie le nœud racine.
 * @return-failure Renvoie $CNULL@ si $Sconfig@ vaut $CNULL@.
 * @log "configuration"
 */
t_bunny_configuration	*bunny_configuration_get_root(t_bunny_configuration	*conf)
{
  t_bunny_configuration	*cnf;

  if (conf == NULL)
    return (NULL);
  if ((cnf = bunny_configuration_get_parent(conf)) == NULL || conf == cnf)
    {
      scream_log_if(PATTERN, "configuration", conf, conf);
      return (conf);
    }
  cnf = bunny_configuration_get_root(cnf);
  scream_log_if(PATTERN, "configuration", conf, cnf);
  return (cnf);
}

