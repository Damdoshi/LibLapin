// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include	"lapin_private.h"

#define		PATTERN		"%p -> %s"

/**
 * @doc
 * @doc-symbol bunny_configuration_get_address
 * @doc-kind function
 * @doc-module configuration
 * @doc-order 190
 * @doc-since 0
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Returns the full address of a configuration node.
 * @param config Node to inspect.
 * @return-success Returns a valid string, empty for the root.
 * @log "configuration"
 *
 * @doc-lang fr
 * @brief Renvoie l’adresse complète d’un nœud de configuration.
 * @param config Node to inspect.
 * @return-success Renvoie une chaîne valide, vide pour la racine.
 * @log "configuration"
 */
const char	*bunny_configuration_get_address(const t_bunny_configuration *config)
{
  SmallConf	*conf = (SmallConf*)config;

  return (conf->address.c_str());
}

/**
 * @doc
 * @doc-symbol bunny_configuration_addressf
 * @doc-kind function
 * @doc-module configuration
 * @doc-order 191
 * @doc-since 0
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Stores the address of a node selected by a formatted path.
 * @param config Configuration tree to inspect.
 * @param addr Output pointer receiving the address string.
 * @param format Printf-like address pattern.
 * @param ... Values consumed by $Sformat@.
 * @return-success Returns $Ctrue@ when the node exists.
 * @return-failure Returns $Cfalse@ when the path cannot be resolved.
 * @log "configuration"
 *
 * @doc-lang fr
 * @brief Stocke l’adresse d’un nœud sélectionné par un chemin formaté.
 * @param config Configuration tree to inspect.
 * @param addr Output pointer receiving the address string.
 * @param format Printf-like address pattern.
 * @param ... Values consumed by $Sformat@.
 * @return-success Renvoie $Ctrue@ quand le nœud existe.
 * @return-failure Renvoie $Cfalse@ quand le chemin ne peut pas être résolu.
 * @log "configuration"
 */
bool			bunny_configuration_addressf(t_bunny_configuration		*config,
						     const char				**addr,
						     const char				*pat,
						     ...)
{
  t_bunny_configuration *got;
  char		buffer[1024 * 4];
  va_list	lst;

  va_start(lst, pat);
  vsnprintf(&buffer[0], sizeof(buffer), pat, lst);
  if ((got = bunny_configuration_go_get_node(config, &buffer[0])) == NULL)
    return (false);
  if (addr)
    *addr = bunny_configuration_get_address(got);
  return (true);
}

