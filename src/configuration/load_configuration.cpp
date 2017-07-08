// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		"lapin_private.h"

#define			PATTERN		"%d type, %s file, %p config -> %p"

t_bunny_configuration	*bunny_load_configuration(t_bunny_configuration_type		type,
						  const char				*file,
						  t_bunny_configuration			*config)
{
  t_bunny_configuration	*outconf = NULL;
  char			*code;

  if (bunny_load_file(file, &code, NULL) == -1)
    scream_error_if(return (NULL), bunny_errno, PATTERN, type, file, config, outconf);
  outconf = bunny_read_configuration(type, code, config);
  bunny_free(code);
  if (!outconf)
    scream_error_if(, bunny_errno, PATTERN, type, file, config, outconf);
  scream_log_if(PATTERN, type, file, config, outconf);
  return (outconf);
}

