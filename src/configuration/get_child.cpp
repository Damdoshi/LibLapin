// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

#define			PATTERN		"%p conf, %s child -> %p"

/**
 * @doc
 * @doc-symbol bunny_configuration_get_child
 * @doc-kind function
 * @doc-module configuration
 * @doc-order 210
 * @doc-since 0
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Returns a named child of a configuration node.
 * @param config Node to inspect.
 * @param child Name of the child to fetch.
 * @return-success Returns the matching child.
 * @return-failure Returns $CNULL@ if it does not exist and create mode is disabled, or if allocation fails.
 * @log "configuration"
 *
 * @doc-lang fr
 * @brief Renvoie un enfant nommé d’un nœud de configuration.
 * @param config Node to inspect.
 * @param child Name of the child to fetch.
 * @return-success Renvoie l’enfant correspondant.
 * @return-failure Renvoie $CNULL@ s’il n’existe pas et que le mode création est désactivé, ou si l’allocation échoue.
 * @log "configuration"
 */
t_bunny_configuration	*bunny_configuration_get_child(t_bunny_configuration	*conf,
						       const char		*child)
{
  SmallConf		*c = (SmallConf*)conf;
  t_bunny_configuration	*cnf = NULL;
  std::string		str = child;

  try
    {
      if ((cnf = ((t_bunny_configuration*)&(*c)[str])) == NULL)
	scream_error_if
	  (return (cnf), bunny_errno, PATTERN, "configuration", conf, child, cnf);
      scream_log_if(PATTERN, "configuration", conf, child, cnf);
      return (cnf);
    }
  catch (...)
    {}
  scream_error_if(return (cnf), bunny_errno, PATTERN, "configuration", conf, child, cnf);
  return (NULL);
}

