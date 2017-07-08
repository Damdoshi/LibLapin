// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
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
    &_bunny_write_xml,
    &_bunny_write_lua,
    &_bunny_write_csv
  };

char			*bunny_write_configuration(t_bunny_configuration_type		type,
						   const t_bunny_configuration		*config)
{
  char			*ret = NULL;

  if (type <= BC_CSV)
    {
      if ((ret = gl_write_func[type](config)) == NULL)
	scream_error_if(return (NULL), bunny_errno, PATTERN, type, config, ret);
    }
  else
    {
      if (gl_bunny_my_write_configuration)
	{
	  if ((ret = gl_bunny_my_write_configuration(type, config)) == NULL)
	    scream_error_if(return (NULL), bunny_errno, PATTERN, type, config, ret);
	}
      else
	scream_error_if(return (NULL), EINVAL, PATTERN, type, config, ret);
    }
  scream_log_if(PATTERN, type, config, ret);
  return (ret);
}

