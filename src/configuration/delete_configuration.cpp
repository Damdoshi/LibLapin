// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

/**
 * @doc
 * @doc-symbol bunny_delete_configuration
 * @doc-kind function
 * @doc-module configuration
 * @doc-order 130
 * @doc-since 0
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Deletes a complete configuration tree.
 * @param config Configuration tree to destroy.
 * @return-success The tree and its children are released.
 * @log "ressource,configuration"
 *
 * @doc-lang fr
 * @brief Détruit un arbre de configuration complet.
 * @param config Configuration tree to destroy.
 * @return-success L’arbre et ses enfants sont libérés.
 * @log "ressource,configuration"
 */
void			bunny_delete_configuration(t_bunny_configuration	*conf)
{
  SmallConf		*c = (SmallConf*)conf;

  scream_log_if("%p", "ressource,configuration", c);
  delete c;
}

