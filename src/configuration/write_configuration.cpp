// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

/**
 * @doc
 * @doc-symbol gl_bunny_my_write_configuration
 * @doc-kind variable
 * @doc-module configuration
 * @doc-order 120
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Custom writer callback used by $Sbunny_write_configuration@ for $CBC_CUSTOM@ and later formats.
 * @see t_bunny_my_write_configuration
 * @see bunny_write_configuration
 *
 * @doc-lang fr
 * @brief Callback d’écriture personnalisée utilisée par $Sbunny_write_configuration@ pour $CBC_CUSTOM@ et les formats suivants.
 * @see t_bunny_my_write_configuration
 * @see bunny_write_configuration
 */
t_bunny_my_write_configuration gl_bunny_my_write_configuration = NULL;

#define			PATTERN		"%d type, %p config -> %.30s"

typedef char		*(*write_func)(const t_bunny_configuration	*cnf);

static const write_func	gl_write_func[BC_CUSTOM] =
  {
    &_bunny_write_ini,
    &_bunny_write_dabsic,
    &_bunny_write_dabsic_sequence,
    &_bunny_write_dabsic_function,
    &_bunny_write_expression,
    &_bunny_write_xml,
    &_bunny_write_lua,
    &_bunny_write_csv,
    &_bunny_write_json,
    &_bunny_write_lisp,
    NULL,
    NULL
  };

/**
 * @doc
 * @doc-symbol bunny_write_configuration
 * @doc-kind function
 * @doc-module configuration
 * @doc-order 100
 * @doc-since 0
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Serializes a configuration tree into a newly allocated string.
 * @param type Format used to serialize $Sconfig@.
 * @param config Configuration tree to serialize.
 * @return-success Returns a newly allocated string.
 * @return-failure Returns $CNULL@ on error.
 * @log "ressource,configuration"
 * @see gl_bunny_my_write_configuration
 *
 * @doc-lang fr
 * @brief Sérialise un arbre de configuration en chaîne nouvellement allouée.
 * @param type Format used to serialize $Sconfig@.
 * @param config Configuration tree to serialize.
 * @return-success Renvoie une chaîne nouvellement allouée.
 * @return-failure Renvoie $CNULL@ en cas d’erreur.
 * @log "ressource,configuration"
 * @see gl_bunny_my_write_configuration
 */
char			*bunny_write_configuration(t_bunny_configuration_type		type,
						   const t_bunny_configuration		*config)
{
  char			*ret = NULL;

  if (type == BC_DATA)
    scream_error_if
      (return (NULL), EINVAL, PATTERN, "ressource,configuration",
       type, config, ret);
  if (type < BC_CUSTOM)
    {
      if ((ret = gl_write_func[type](config)) == NULL)
	scream_error_if
	  (return (NULL), bunny_errno, PATTERN, "ressource,configuration",
	   type, config, ret);
    }
  else
    {
      if (gl_bunny_my_write_configuration)
	{
	  if ((ret = gl_bunny_my_write_configuration(type, config)) == NULL)
	    scream_error_if
	      (return (NULL), bunny_errno, PATTERN, "ressource,configuration",
	       type, config, ret);
	}
      else
	scream_error_if
	  (return (NULL), EINVAL, PATTERN, "ressource,configuration",
	   type, config, ret);
    }
  scream_log_if(PATTERN, "ressource,configuration", type, config, ret);
  return (ret);
}

