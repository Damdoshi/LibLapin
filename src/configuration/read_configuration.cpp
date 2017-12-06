// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		"lapin_private.h"

// TODO:
// Create a function pointer table and remove all this mess...

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
    _bunny_read_lisp
  };

#define			PATTERN		"%d type, %s code, %p config -> %p"

t_bunny_configuration	*bunny_read_configuration(t_bunny_configuration_type type,
						  const char		*code,
						  t_bunny_configuration	*config)
{
  t_bunny_configuration	*nw = NULL;
  bool			local;

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

