// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		"lapin_private.h"

bool			bunny_save_configuration(t_bunny_configuration_type		type,
						 const char				*file,
						 t_bunny_configuration			*config)
{
  char			*code;
  bool			out;

  if ((code = bunny_write_configuration(type, config)) == NULL)
    return (false);
  out = bunny_save_file(file, code, strlen(code));
  bunny_free(code);
  return (out);
}

