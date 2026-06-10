// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		<sstream>
#include		"lapin_private.h"

#define			PATTERN		"%p(%s) conf, %zu index -> %p"

/**
 * @doc
 * @doc-symbol bunny_configuration_get_case
 * @doc-kind function
 * @doc-module configuration
 * @doc-order 230
 * @doc-since 0
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Returns an indexed case of a configuration node.
 * @param config Node to inspect.
 * @param i Index of the case to fetch.
 * @return-success Returns the matching case.
 * @return-failure Returns $CNULL@ if it does not exist and create mode is disabled, or if allocation fails.
 * @log "configuration"
 *
 * @doc-lang fr
 * @brief Renvoie une case indexée d’un nœud de configuration.
 * @param config Node to inspect.
 * @param i Index of the case to fetch.
 * @return-success Renvoie la case correspondante.
 * @return-failure Renvoie $CNULL@ si elle n’existe pas et que le mode création est désactivé, ou si l’allocation échoue.
 * @log "configuration"
 */
t_bunny_configuration	*bunny_configuration_get_case(t_bunny_configuration	*conf,
						      ssize_t			n)
{
  SmallConf		*c = (SmallConf*)conf;
  t_bunny_configuration	*cnf = NULL;

  try
    {
      if ((cnf = (t_bunny_configuration*)&(*c)[n]) == NULL)
	scream_error_if
	  (return (cnf), bunny_errno, PATTERN, "configuration",
	   conf, c->name.c_str(), n, cnf);
      scream_log_if(PATTERN, "configuration", conf, c->name.c_str(), n, cnf);
      return (cnf);
    }
  catch (...)
    {}
  scream_error_if
    (return (cnf), bunny_errno, PATTERN, "configuration", conf, c->name.c_str(), n, cnf);
  return (NULL);
}

