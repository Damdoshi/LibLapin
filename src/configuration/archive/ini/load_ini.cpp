// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Bibliotheque Lapin

#include		<string.h>
#include		"lapin_private.h"

extern char		*ini_last_error;

#define			PATTERN		"%s -> %p"

t_bunny_ini		*bunny_load_ini(const char		*file)
{
  t_bunny_ini		*ini;

  if ((ini = bunny_load_configuration(BC_INI, file, NULL)) == NULL)
    scream_error_if(return (NULL), bunny_errno, PATTERN, "ressource,configuration", file, ini);
  scream_log_if(PATTERN, "ressource,configuration", file, ini);
  return (ini);
}

