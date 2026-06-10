// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

/**
 * @doc
 * @doc-symbol bunny_delete_node
 * @doc-kind function
 * @doc-module configuration
 * @doc-order 140
 * @doc-since 0
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Deletes the node selected by an address below another node.
 * @param config Root node used for address resolution.
 * @param addr C-like address of the node to delete.
 * @return-success The selected node is removed when it exists.
 * @log "configuration"
 * @see bunny_configuration_go_get_node
 *
 * @doc-lang fr
 * @brief Détruit le nœud sélectionné par une adresse sous un autre nœud.
 * @param config Root node used for address resolution.
 * @param addr C-like address of the node to delete.
 * @return-success Le nœud sélectionné est retiré quand il existe.
 * @log "configuration"
 * @see bunny_configuration_go_get_node
 */
void			bunny_delete_node(t_bunny_configuration		*conf,
					  const char			*str)
{
  SmallConf		*c = (SmallConf*)bunny_configuration_go_get_node(conf, str);

  if (!c)
    return ;
  scream_log_if("%p", "ressource,configuration", c);
  delete c;
}

