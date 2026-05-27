// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

// TODO:
// Create a function pointer table and remove all this mess...

/**
 * @doc
 * @doc-symbol gl_bunny_my_read_configuration
 * @doc-kind variable
 * @doc-module configuration
 * @doc-order 90
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Custom parser callback used by $Sbunny_read_configuration@ for $CBC_CUSTOM@ and later formats.
 * @see t_bunny_my_read_configuration
 * @see bunny_read_configuration
 *
 * @doc-lang fr
 * @brief Callback de lecture personnalisée utilisée par $Sbunny_read_configuration@ pour $CBC_CUSTOM@ et les formats suivants.
 * @see t_bunny_my_read_configuration
 * @see bunny_read_configuration
 */
t_bunny_my_read_configuration gl_bunny_my_read_configuration = NULL;

typedef t_bunny_configuration
*(*t_bunny_read_file)(const char		*code,
		      t_bunny_configuration	*c);

t_bunny_read_file	parser[BC_CUSTOM] =
  {
    _bunny_read_ini,
    _bunny_read_dabsic,
    _bunny_read_sequence,
    _bunny_read_function,
    _bunny_read_expression,
    _bunny_read_xml,
    _bunny_read_lua,
    _bunny_read_csv,
    _bunny_read_json,
    _bunny_read_lisp,
    _bunny_read_text,
    NULL // _data
  };

#define			PATTERN		"%d type, '%.5s...' code, %p config -> %p"

/**
 * @doc
 * @doc-symbol bunny_read_configuration
 * @doc-kind function
 * @doc-module configuration
 * @doc-order 70
 * @doc-since 0
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Parses a string into a configuration tree.
 * @param type Format used to parse $Scode@.
 * @param code String to parse.
 * @param config Existing configuration to fill, or $CNULL@ to allocate one.
 * @return-success Returns the filled or newly allocated configuration.
 * @return-failure Returns $CNULL@ on parsing or allocation error.
 * @log "ressource,configuration"
 * @see gl_bunny_my_read_configuration
 *
 * @doc-lang fr
 * @brief Analyse une chaîne pour produire un arbre de configuration.
 * @param type Format used to parse $Scode@.
 * @param code String to parse.
 * @param config Existing configuration to fill, or $CNULL@ to allocate one.
 * @return-success Renvoie la configuration remplie ou nouvellement allouée.
 * @return-failure Renvoie $CNULL@ en cas d’erreur d’analyse ou d’allocation.
 * @log "ressource,configuration"
 * @see gl_bunny_my_read_configuration
 */
t_bunny_configuration	*bunny_read_configuration(t_bunny_configuration_type type,
						  const char		*code,
						  t_bunny_configuration	*config)
{
  t_bunny_configuration	*nw = NULL;
  bool			local;

  if (type == BC_DATA)
    scream_error_if(return (NULL), EINVAL, PATTERN, "ressource,configuration", type, code, config, nw);

  if ((local = (config == NULL)))
    if ((config = bunny_new_configuration()) == NULL)
      scream_error_if(return (NULL), bunny_errno, PATTERN, "ressource,configuration", type, code, config, nw);

  if (type < BC_CUSTOM)
    {
      if ((nw = parser[type](code, config)) == NULL && local)
	bunny_delete_configuration(config);
      if (!nw)
	scream_error_if(return (NULL), bunny_errno, PATTERN, "ressource,configuration", type, code, config, nw);
      scream_log_if(PATTERN, "ressource,configuration", type, code, config, nw);
      return (nw);
    }

  if (gl_bunny_my_read_configuration)
    {
      if ((nw = gl_bunny_my_read_configuration(type, code, config)) == NULL && local)
	bunny_delete_configuration(config);
      if (!nw)
	scream_error_if(return (NULL), bunny_errno, PATTERN, "ressource,configuration", type, code, config, nw);
      scream_log_if(PATTERN, "ressource,configuration", type, code, config, nw);
      return (nw);
    }

  scream_error_if(return (NULL), EINVAL, PATTERN, "ressource,configuration", type, code, config, nw);
  return (NULL);
}

