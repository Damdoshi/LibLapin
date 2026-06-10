// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

/**
 * @doc
 * @doc-symbol bunny_configuration_is_last
 * @doc-kind function
 * @doc-module configuration
 * @doc-order 580
 * @doc-since 0
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Tests whether a node is the last child of its parent.
 * @param config Node to test.
 * @return-success Returns $Ctrue@ when the node is last.
 * @return-failure Returns $Cfalse@ otherwise.
 * @log "configuration"
 *
 * @doc-lang fr
 * @brief Teste si un nœud est le dernier enfant de son parent.
 * @param config Node to test.
 * @return-success Renvoie $Ctrue@ quand le nœud est dernier.
 * @return-failure Renvoie $Cfalse@ sinon.
 * @log "configuration"
 */
bool			bunny_configuration_is_last(t_bunny_configuration	*cnf)
{
  std::map<std::string, SmallConf*>::iterator it;
  SmallConf		*conf = (SmallConf*)cnf;

  it = conf->father->iterator;
  return (++it == conf->father->End());
}
