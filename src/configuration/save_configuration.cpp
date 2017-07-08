// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		"lapin_private.h"

#define			PATTERN		"%d type, %s file, %p config -> %s"

bool			bunny_save_configuration(t_bunny_configuration_type		type,
						 const char				*file,
						 t_bunny_configuration			*config)
{
  char			*code;
  bool			out;

  if ((code = bunny_write_configuration(type, config)) == NULL)
    scream_error_if(return (false), bunny_errno, PATTERN, type, file, config, "false");
  out = bunny_save_file(file, code, strlen(code));
  bunny_free(code);
  if (!out)
    scream_error_if(return (false), bunny_errno, PATTERN, type, file, config, "false");
  scream_log_if(PATTERN, type, file, config, "true");
  return (out);
}

