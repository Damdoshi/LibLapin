// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		"lapin_private.h"

t_bunny_configuration	*bunny_load_configuration(t_bunny_configuration_type		type,
						  const char				*file,
						  t_bunny_configuration			*config)
{
  t_bunny_configuration	*outconf;
  char			*code;

  if (bunny_load_file(file, &code, NULL) == -1)
    return (NULL);
  outconf = bunny_read_configuration(type, code, config);
  bunny_free(code);
  return (outconf);
}

