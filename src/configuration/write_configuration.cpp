// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

t_bunny_my_write_configuration gl_bunny_my_write_configuration = NULL;

#define			PATTERN		"%d type, %p config -> %s"

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
    &_bunny_write_lisp
  };

char			*bunny_write_configuration(t_bunny_configuration_type		type,
						   const t_bunny_configuration		*config)
{
  char			*ret = NULL;

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

