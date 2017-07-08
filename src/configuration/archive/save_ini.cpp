// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Bibliotheque Lapin

#include		"lapin_private.h"

#define			PATTERN		"%p ini, %s file -> %s"

bool			bunny_save_ini(t_bunny_ini		*ini,
				       const char		*file)
{
  bool			b;

  if ((b = bunny_save_configuration(BC_INI, file, ini)) == false)
    scream_error_if(return (false), bunny_errno, PATTERN, ini, file, "false");
  scream_log_if(PATTERN, ini, file, "true");
  return (true);
}

