// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

#define			PATTERN		"%p -> %p"

/**
 * @doc
 * @doc-symbol bunny_configuration_first
 * @doc-kind function
 * @doc-module configuration
 * @doc-order 550
 * @doc-since 0
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Returns the first child of a configuration node.
 * @param config Configuration node to browse.
 * @return-success Returns the first child.
 * @return-failure Returns $CNULL@ if there is no child.
 * @log "configuration"
 *
 * @doc-lang fr
 * @brief Renvoie le premier enfant d’un nœud de configuration.
 * @param config Configuration node to browse.
 * @return-success Renvoie le premier enfant.
 * @return-failure Renvoie $CNULL@ s’il n’y a pas d’enfant.
 * @log "configuration"
 */
t_bunny_configuration	*bunny_configuration_first(t_bunny_configuration	*config)
{
  SmallConf		*conf = (SmallConf*)config;
  t_bunny_configuration	*cnf;

  if (conf->Begin() == conf->End())
    {
      scream_log_if(PATTERN, "configuration", config, (void*)NULL);
      return (NULL);
    }
  cnf = (t_bunny_configuration*)conf->Begin()->second;
  scream_log_if(PATTERN, "configuration", config, cnf);
  return (cnf);
}

/**
 * @doc
 * @doc-symbol bunny_configuration_firstf
 * @doc-kind function
 * @doc-module configuration
 * @doc-order 551
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Returns the first child of a node selected by a formatted address.
 * @param config Configuration tree to browse.
 * @param pattern Printf-like address pattern.
 * @param ... Values consumed by $Spattern@.
 * @return-success Returns the first child.
 * @return-failure Returns $CNULL@ if the path is missing or empty.
 * @log "configuration"
 *
 * @doc-lang fr
 * @brief Renvoie le premier enfant d’un nœud sélectionné par adresse formatée.
 * @param config Configuration tree to browse.
 * @param pattern Printf-like address pattern.
 * @param ... Values consumed by $Spattern@.
 * @return-success Renvoie le premier enfant.
 * @return-failure Renvoie $CNULL@ si le chemin est absent ou vide.
 * @log "configuration"
 */
t_bunny_configuration	*bunny_configuration_firstf(t_bunny_configuration	*cnf,
						    const char			*pattern,
						    ...)
{
  va_list		lst;

  va_start(lst, pattern);
  if (!bunny_configuration_vgetf_node(cnf, &cnf, pattern, lst))
    return (NULL);
  return (bunny_configuration_first(cnf));
}

/**
 * @doc
 * @doc-symbol bunny_configuration_next
 * @doc-kind function
 * @doc-module configuration
 * @doc-order 560
 * @doc-since 0
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Returns the next sibling during configuration iteration.
 * @param config Current child node.
 * @return-success Returns the next child.
 * @return-failure Returns $CNULL@ after the last child.
 * @log "configuration"
 *
 * @doc-lang fr
 * @brief Renvoie le frère suivant pendant l’itération de configuration.
 * @param config Current child node.
 * @return-success Renvoie l’enfant suivant.
 * @return-failure Renvoie $CNULL@ après le dernier enfant.
 * @log "configuration"
 */
t_bunny_configuration	*bunny_configuration_next(t_bunny_configuration		*config)
{
  SmallConf		*conf = (SmallConf*)config;
  t_bunny_configuration	*cnf;

  ++conf->father->It();
  if (conf->father->It() == conf->father->End())
    {
      scream_log_if(PATTERN, "configuration", config, (void*)NULL);
      return (NULL);
    }
  cnf = (t_bunny_configuration*)conf->father->It()->second;
  scream_log_if(PATTERN, "configuration", config, cnf);
  return (cnf);
}

/**
 * @doc
 * @doc-symbol bunny_configuration_end
 * @doc-kind function
 * @doc-module configuration
 * @doc-order 570
 * @doc-since 0
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Returns the sentinel used to stop configuration iteration.
 * @param config Configuration node, unused.
 * @return-success Always returns $CNULL@.
 * @log "configuration"
 *
 * @doc-lang fr
 * @brief Renvoie la sentinelle utilisée pour arrêter l’itération de configuration.
 * @param config Configuration node, unused.
 * @return-success Renvoie toujours $CNULL@.
 * @log "configuration"
 */
t_bunny_configuration	*bunny_configuration_end(t_bunny_configuration		*config)
{
  (void)config;
  scream_log_if(PATTERN, "configuration", config, (void*)NULL);
  return (NULL);
}

