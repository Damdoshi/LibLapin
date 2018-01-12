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
  int			len;

  if ((code = bunny_write_configuration(type, config)) == NULL)
    scream_error_if
      (return (false), bunny_errno, PATTERN, "ressource,configuration",
       type, file, config, "false");
  len = strlen(code);
  if (gl_bunny_ressource_ciphering)
    gl_bunny_ressource_ciphering
      (code, len, gl_bunny_ressource_data, true);
  out = bunny_save_file(file, code, len);
  bunny_free(code);
  if (!out)
    scream_error_if
      (return (false), bunny_errno, PATTERN, "ressource,configuration",
       type, file, config, "false");
  scream_log_if(PATTERN, "ressource,configuration", type, file, config, "true");
  return (out);
}

