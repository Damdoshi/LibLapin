// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2020
//
// Lapin library

#include	"lapin_private.h"

/**
 * @doc
 * @doc-symbol bunny_clear_configuration
 * @doc-kind function
 * @doc-module configuration
 * @doc-order 135
 * @doc-since 0
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Removes every child and scalar value from a configuration node.
 * @param config Configuration node to clear.
 * @return-success The node remains valid and empty.
 * @log "configuration"
 *
 * @doc-lang fr
 * @brief Retire tous les enfants et la valeur scalaire d’un nœud de configuration.
 * @param config Configuration node to clear.
 * @return-success Le nœud reste valide et vide.
 * @log "configuration"
 */
void		bunny_clear_configuration(t_bunny_configuration	*cnf)
{
  SmallConf	*c = (SmallConf*)cnf;
  std::map<std::string, SmallConf*>::iterator	it;
  std::map<std::string, SmallConf*> dup = c->nodes;
  std::vector<SmallConf*> dupx = c->array;
  std::vector<SmallConf*>::iterator itx;

  delete c->sequence;
  c->sequence = NULL;
  delete c->expression;
  c->expression = NULL;
  delete c->function;
  c->function = NULL;

  for (it = dup.begin(); it != dup.end(); ++it)
    {
      it->second->father = NULL; // Isolate the node from its tree so it does not destroy it
      delete it->second;
    }
  c->nodes.clear();

  for (itx = dupx.begin(); itx != dupx.end(); ++itx)
    delete *itx;
  c->array.clear();
}
