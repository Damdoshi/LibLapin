// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

/**
 * @doc
 * @doc-symbol bunny_configuration_push_path
 * @doc-kind function
 * @doc-module configuration
 * @doc-order 600
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Pushes an additional search path for nested configuration loading.
 * @param file Path to push.
 * @return-success The path is added to the configuration search stack.
 * @log "configuration"
 *
 * @doc-lang fr
 * @brief Ajoute un chemin de recherche supplémentaire pour les chargements imbriqués.
 * @param file Path to push.
 * @return-success Le chemin est ajouté à la pile de recherche de configuration.
 * @log "configuration"
 */
void			bunny_configuration_push_path(const char	*file)
{
  SmallConf::file_path.push_back(file);
}
