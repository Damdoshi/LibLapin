// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

/**
 * @doc
 * @doc-symbol bunny_configuration_pop_path
 * @doc-kind function
 * @doc-module configuration
 * @doc-order 610
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Pops the last additional configuration search path.
 * @return-success The last pushed path is removed.
 * @log "configuration"
 *
 * @doc-lang fr
 * @brief Retire le dernier chemin de recherche de configuration ajouté.
 * @return-success Le dernier chemin ajouté est retiré.
 * @log "configuration"
 */
void			bunny_configuration_pop_path(void)
{
  SmallConf::file_path.pop_back();
}
